import tensorflow as tf
import tensorflow.contrib.slim as slim
import numpy as np
import matplotlib.pyplot as plt
import gym
import random
import scipy.misc
import os
from matplotlib import animation

from GridWorld import gameEnvironment


env = gameEnvironment(partial=False, size=5);



class Q_Network:
    """ Double-Dueling DQN
     1. Input : flattened array of states
    """
    def __init__(self, hidden_size):
        """
         About tf.contrib.layers.convolution2d
         - num_outputs : number of filters
         - kernel_size : the size of the window
         - stride :  the size of slide of the window
         - padding : 'VALID'(apply with the original) // 'SAME'(make the size of output == the size of input)
        """
        self.input_scalar = tf.placeholder(shape=[None, 84*84*3], dtype=tf.float32);
        self.input_image = tf.reshape(self.input_scalar, shape=[-1, 84, 84, 3]);

        # Convolution Layers
        filters = [32, 64, 64];
        self.conv_layer1 = slim.conv2d(
            inputs=self.input_image, num_outputs=filters[0], kernel_size=[8, 8], stride=[4, 4], padding='VALID',
            biases_initializer=None);
        self.conv_layer2 = slim.conv2d(
            inputs=self.conv_layer1, num_outputs=filters[1], kernel_size=[4, 4], stride=[2,2], padding='VALID',
            biases_initializer=None);
        self.conv_layer3 = slim.conv2d(
            inputs=self.conv_layer2, num_outputs=filters[2], kernel_size=[3, 3], stride=[1,1], padding='VALID',
            biases_initializer=None);
        self.conv_layer4 = slim.conv2d(
            inputs=self.conv_layer3, num_outputs=hidden_size, kernel_size=[7,7], stride=[1,1], padding='VALID',
            biases_initializer=None);

        """Dueling step - split the final outputs of the final convolution layer
         1. Q(s, a) = V(s) + A(a) where the input state s is fixed
         2. V(s) : value function which measures how good the state s is
         3. A(a) : advantage which measures how better the action a is 
        """
        # self.conv_layer4[data][output-x][output-y][filter]
        # tf.split(array, num_split, axis)
        #  => split the outputs with the filters
        self.streamAC, self.streamVC = tf.split(self.conv_layer4, 2, 3);

        # slim.flatten : Flatten the input maintaining the batch_size
        # self.stream_advantage : (batch_size, rows*cols*hidden_size//2)
        self.stream_advantage = slim.flatten(self.streamAC);
        self.stream_value = slim.flatten(self.streamVC);

        # Make 2 affine networks for advantage and value
        xavier_init = tf.contrib.layers.xavier_initializer();
        self.advantage_W = tf.Variable(xavier_init([hidden_size//2, env.actions]));
        self.value_W = tf.Variable(xavier_init([hidden_size//2, 1]));

        # Advantage[data][action] = A(action)
        self.Advantage = tf.matmul(self.stream_advantage, self.advantage_W);

        # Value[data] = V(input state)
        self.Value = tf.matmul(self.stream_value, self.value_W);

        # Finally, make the output Q_output
        # Q_output[action] = Q(input_state, action)
        # In batch, Q_output[data][action] = Q(input_state[data], action)
        # Q_output = Value + (Advantage - mean_Advantage)
        self.Q_output = self.Value + \
            tf.subtract(self.Advantage, tf.reduce_mean(self.Advantage, axis=1, keep_dims=True));
        self.predict_action = tf.argmax(self.Q_output, axis=1);



        """ Loss and Training Step
        1. Double DQN equation
         : Q_target = reward + gammaQ(s', argmax(Q(s', a, theta)), theta')
        """
        # Q_target : solution for DDQN equation
        self.Q_target = tf.placeholder(shape=[None], dtype=tf.float32);

        self.actions = tf.placeholder(shape=[None], dtype=tf.int32);
        self.actions_onehot = tf.one_hot(self.actions, env.actions, dtype=tf.float32);
        self.Q = tf.reduce_sum(tf.multiply(self.Q_output, self.actions_onehot), axis=1);

        self.square_error = tf.square(self.Q_target-self.Q);
        self.loss = tf.reduce_mean(self.square_error);
        self.trainer = tf.train.AdamOptimizer(learning_rate=0.0001);
        self.optimizer = self.trainer.minimize(self.loss);


class experience_buffer:
    """ Experience replay (경험 리플레이)
     - Save some experience of the agent.
     - Then use some part of experience to train
     - Save recent experience and remove old one when new experience is added
     - here, experience is a tuple (state, action, reward, next state)
    """
    def __init__(self, buffer_size=50000):
        self.buffer = [];
        self.buffer_size = buffer_size;

    def add(self, experience):

        # if buffer is full, remove old experience
        if len(self.buffer) + len(experience) >= self.buffer_size:
            self.buffer[0:(len(experience)+len(self.buffer))-self.buffer_size] = [];

        self.buffer.extend(experience);

    def sample(self, size):
        return np.reshape(np.array(random.sample(self.buffer, size)), [size, 5]);


def processState(states):
    return np.reshape(states, [84*84*3]);


""" Train the target network which is for target Q in the Bellman equation 
 -tau : Ratio to update target network toward primary network
"""
def updateTarget_network(target_variables, tau):
    total_variables = len(target_variables);
    operation_holder = [];

    for idx, variable in enumerate(target_variables[0:total_variables//2]):
        operation_holder.append(target_variables[idx+total_variables//2].assign(
            (variable.value()*tau) + ((1-tau)*target_variables[idx+total_variables//2].value())
        ));

    return operation_holder;


def updateTarget(op_holders, session):
    for op in op_holders:
        session.run(op);

def train_Double_Duel_DQN():
    size_grid = 5;
    env = gameEnvironment(partial=False,size=size_grid);

    """ Set hyper-parameters """
    num_episodes = 10000;
    max_len_epi = 50;

    batch_size = 32;
    update_freq = 4;

    # discount factor on the target Q_values
    gamma = 0.99;

    # greedy-epsilon
    annealing_step = 10000;
    start_epsilon, end_epsilon = 1, 0.1;

    # number of random actions before training the network
    pre_train_steps = 10000;


    # Save the model
    load_model = True;
    path = "./dqn_gridworld"+str(size_grid);
    h_size = 512;
    tau = 0.001;

    """ Make networks """
    tf.reset_default_graph();
    main_network = Q_Network(h_size);
    target_network = Q_Network(h_size);

    init = tf.global_variables_initializer();

    saver = tf.train.Saver();

    trainables = tf.trainable_variables();
    target_ops = updateTarget_network(trainables, tau);

    myBuffer = experience_buffer();

    # Set the rate of random action
    greedy_epsilon = start_epsilon;
    step_drop = (start_epsilon - end_epsilon)/annealing_step;

    reward_list = [];
    ending_step_list = [];
    total_steps = 0;



    with tf.Session() as sess:
        init.run();

        if load_model is True:
            print("Loading model..........");
            ckpt = tf.train.get_checkpoint_state(path);
            saver.restore(sess, ckpt.model_checkpoint_path);

        for i in range(num_episodes):
            episodeBuffer = experience_buffer();

            state = env.reset();
            state = processState(state);
            is_Exit = False;
            reward_all = 0;

            j = 0;

            # Train the network
            while j < max_len_epi:
                j += 1;
                # Choose an action by greedily picking (or pre-train)
                if np.random.rand(1) < greedy_epsilon or total_steps < pre_train_steps:
                    chosen_action = np.random.randint(4);
                else:
                    chosen_action = sess.run(main_network.predict_action,
                                             feed_dict={main_network.input_scalar: [state]})[0];

                next_state, reward, is_Exit = env.step(chosen_action);
                next_state = processState(next_state);

                total_steps += 1;

                # Save the experience in the buffer
                episodeBuffer.add(np.reshape(np.array([state, chosen_action,reward, next_state, is_Exit]), [1, 5]));

                if total_steps > pre_train_steps:
                    if greedy_epsilon > end_epsilon:
                        greedy_epsilon -= step_drop;

                    # update the network
                    if total_steps % update_freq == 0:
                        # Choose batch train data from experience
                        # train_batch
                        train_batch = myBuffer.sample(batch_size);

                        Q_main = sess.run(main_network.predict_action,
                                          feed_dict={main_network.input_scalar: np.vstack(train_batch[:, 3])});
                        Q_target = sess.run(target_network.Q_output,
                                            feed_dict={target_network.input_scalar:np.vstack(train_batch[:, 3])});

                        # if new_state is end point => end_multiplier 0
                        # if new_state is not end => end_multiplier 1
                        end_multiplier = -(train_batch[:, 4] -1);

                        double_Q = Q_target[range(batch_size), Q_main];
                        target_Q = train_batch[:, 2] + gamma*double_Q*end_multiplier;

                        # Update the main network
                        sess.run(main_network.optimizer,
                                 feed_dict={main_network.input_scalar: np.vstack(train_batch[:, 0]),
                                            main_network.Q_target: target_Q,
                                            main_network.actions: train_batch[:, 1]});

                        # Update the target network with the main network
                        updateTarget(target_ops, sess);

                reward_all += reward;
                state = next_state;

                if is_Exit is True:
                    break;


            myBuffer.add(episodeBuffer.buffer);
            ending_step_list.append(j);
            reward_list.append(reward_all);

            # Show reward and save the model periodically
            if i % 100 == 0:
                saver.save(sess, path+"/model_"+str(i)+".ckpt");
                print("Save the {}-th model".format(i));

            if len(reward_list) % 10 == 0:
                print("{}-th episode, {}-steps mean reward : {}".format(
                    i, total_steps, np.mean(reward_list[-10:])
                ));


        saver.save(sess, path+"/final_model"+".ckpt");

    print("Percent of successful episodes : {}".format(
        sum(reward_list) /num_episodes
    ));

def train_Double_Duel_DQN_re():
    size_grid = 5;
    env = gameEnvironment(partial=False,size=size_grid);

    """ Set hyper-parameters """
    num_episodes = 10000;
    max_len_epi = 50;

    batch_size = 32;
    update_freq = 4;

    # discount factor on the target Q_values
    gamma = 0.99;

    # greedy-epsilon
    annealing_step = 10000;
    start_epsilon, end_epsilon = 1, 0.1;

    # number of random actions before training the network
    pre_train_steps = 10000;


    # Save the model
    load_model = False;
    path = "./dqn_gridworld"+str(size_grid);
    h_size = 512;
    tau = 0.001;

    """ Make networks """
    tf.reset_default_graph();
    main_network = Q_Network(h_size);
    target_network = Q_Network(h_size);

    init = tf.global_variables_initializer();

    saver = tf.train.Saver();

    trainables = tf.trainable_variables();
    target_ops = updateTarget_network(trainables, tau);

    myBuffer = experience_buffer();

    # Set the rate of random action
    greedy_epsilon = start_epsilon;
    step_drop = (start_epsilon - end_epsilon)/annealing_step;


    reward_list = [];
    ending_step_list = [];

    total_steps = 0;



    with tf.Session() as sess:
        init.run();


        print("Loading model..........");
        #ckpt = tf.train.get_checkpoint_state(path);
        #saver.restore(sess, ckpt.model_checkpoint_path);
        i = 5500;
        total_steps = 275000;
        greedy_epsilon = end_epsilon;


        saver.restore(sess, path+"/model_"+str(i)+".ckpt")
        print("The model is loaded ");

        while i < num_episodes:
            i += 1;
            episodeBuffer = experience_buffer();

            state = env.reset();
            state = processState(state);
            is_Exit = False;
            reward_all = 0;

            j = 0;

            # Train the network
            while j < max_len_epi:
                j += 1;
                # Choose an action by greedily picking (or pre-train)
                if np.random.rand(1) < greedy_epsilon or total_steps < pre_train_steps+275000:
                    chosen_action = np.random.randint(4);
                else:
                    chosen_action = sess.run(main_network.predict_action,
                                             feed_dict={main_network.input_scalar: [state]})[0];

                next_state, reward, is_Exit = env.step(chosen_action);
                next_state = processState(next_state);

                total_steps += 1;

                # Save the experience in the buffer
                episodeBuffer.add(np.reshape(np.array([state, chosen_action,reward, next_state, is_Exit]), [1, 5]));

                if total_steps > pre_train_steps+275000:


                    # update the network
                    if total_steps % update_freq == 0:
                        # Choose batch train data from experience
                        # train_batch
                        train_batch = myBuffer.sample(batch_size);

                        Q_main = sess.run(main_network.predict_action,
                                          feed_dict={main_network.input_scalar: np.vstack(train_batch[:, 3])});
                        Q_target = sess.run(target_network.Q_output,
                                            feed_dict={target_network.input_scalar:np.vstack(train_batch[:, 3])});

                        # if new_state is end point => end_multiplier 0
                        # if new_state is not end => end_multiplier 1
                        end_multiplier = -(train_batch[:, 4] -1);

                        double_Q = Q_target[range(batch_size), Q_main];
                        target_Q = train_batch[:, 2] + gamma*double_Q*end_multiplier;

                        # Update the main network
                        sess.run(main_network.optimizer,
                                 feed_dict={main_network.input_scalar: np.vstack(train_batch[:, 0]),
                                            main_network.Q_target: target_Q,
                                            main_network.actions: train_batch[:, 1]});

                        # Update the target network with the main network
                        updateTarget(target_ops, sess);

                reward_all += reward;
                state = next_state;

                if is_Exit is True:
                    break;


            myBuffer.add(episodeBuffer.buffer);
            ending_step_list.append(j);
            reward_list.append(reward_all);

            # Show reward and save the model periodically
            if i % 100 == 0:
                saver.save(sess, path+"/model_"+str(i)+".ckpt");
                print("Save the {}-th model".format(i));

            if len(reward_list) % 10 == 0:
                print("{}-th episode, {}-steps mean reward : {}".format(
                    i, total_steps, np.mean(reward_list[-10:])
                ));


        saver.save(sess, path+"/final_model"+".ckpt");

    print("Percent of successful episodes : {}".format(
        sum(reward_list) /num_episodes
    ));


def Verification_Double_Duel_DQN():
    size_grid = 5;
    env = gameEnvironment(partial=False, size=size_grid);

    """ Set hyper-parameters """
    num_episodes = 10000;
    max_len_epi = 50;

    batch_size = 32;
    update_freq = 4;

    # discount factor on the target Q_values
    gamma = 0.99;


    # number of random actions before training the network
    pre_train_steps = 100;

    # Save the model
    path = "./dqn_gridworld" + str(size_grid);
    h_size = 512;

    """ Make networks """
    tf.reset_default_graph();
    main_network = Q_Network(h_size);

    init = tf.global_variables_initializer();

    saver = tf.train.Saver();

    #myBuffer = experience_buffer();
    reward_list = [];
    ending_step_list = [];

    total_steps = 0;

    with tf.Session() as sess:
        init.run();


        print("Loading model..........");
        saver.restore(sess, path+"/final_model.ckpt")
        print("The model is loaded ");

        for i in range(num_episodes):

            #episodeBuffer = experience_buffer();

            state = env.reset();
            state = processState(state);
            reward_all = 0;

            j = 0;

            # Train the network
            while j < max_len_epi:
                j += 1;

                chosen_action = sess.run(main_network.predict_action,
                                         feed_dict={main_network.input_scalar: [state]})[0];

                next_state, reward, is_Exit = env.step(chosen_action);
                next_state = processState(next_state);

                total_steps += 1;

                # Save the experience in the buffer
                #episodeBuffer.add(np.reshape(np.array([state, chosen_action,reward, next_state, is_Exit]), [1, 5]));



                reward_all += reward;
                state = next_state;


            ending_step_list.append(j);
            reward_list.append(reward_all);


            if i % 10 == 0:
                print("{}-th episode reward : {}".format(i, reward_all));




    print("Average Reward : {}".format(sum(reward_list) /num_episodes));


def example_DQN(num_goal=2, num_fire=4):
    size_grid = 5;
    env = gameEnvironment(partial=False, size=size_grid, num_goal=num_goal, num_fire=num_fire);

    """ Set hyper-parameters """
    num_travel = 50;


    # Save the model
    path = "./dqn_gridworld_final";
    h_size = 512;

    """ Make networks """
    tf.reset_default_graph();
    main_network = Q_Network(h_size);

    init = tf.global_variables_initializer();

    saver = tf.train.Saver();

    state_list = [];
    action_list = [];

    with tf.Session() as sess:
        init.run();

        print("Loading model..........");
        saver.restore(sess, path + "/final_model.ckpt")
        print("The model is loaded ");

        state = env.reset();
        state_list.append(state);

        state = processState(state);
        reward_all = 0;

        # Train the network
        for i in range(num_travel):

            chosen_action = sess.run(main_network.predict_action,
                                     feed_dict={main_network.input_scalar: [state]})[0];

            next_state, reward, is_Exit = env.step(chosen_action);
            state_list.append(next_state);
            action_list.append(chosen_action);

            next_state = processState(next_state);




            reward_all += reward;
            state = next_state;

    print("Reward : {}".format(reward_all));
    print("Action : \n{}".format(action_list));

    frames = [];
    fig = plt.figure();

    for i in range(len(state_list)):
        frames.append([plt.imshow(state_list[i], interpolation="nearest", animated=True)]);

    ani = animation.ArtistAnimation(fig, frames, repeat=False);
    filename = "my_DQN_action_goal"+str(num_goal)+"_fire"+str(num_fire)+".gif";
    ani.save(filename, writer='imagemagick');

    plt.show()
























































if __name__ == "__main__":
    print("Chapter 6 : Deep Q Learning");
    #env = gameEnvironment(partial=False, size=6);
    #plt.show();
    #train_Double_Duel_DQN();
    #train_Double_Duel_DQN_re();
    #Verification_Double_Duel_DQN();
    example_DQN(num_goal=1, num_fire=6);