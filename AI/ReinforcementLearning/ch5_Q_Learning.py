import tensorflow as tf
import tensorflow.contrib.slim as slim
import numpy as np
import matplotlib.pyplot as plt
import gym




def Q_table_Learning():
    env = gym.make('FrozenLake-v0');

    # Q_table[state][action] : measure how the action is good at the state
    Q_table = np.zeros([env.observation_space.n, env.action_space.n]);

    # hyper-parameters
    learning_rate = 0.8;
    gamma = 0.99;
    num_episodes = 2000;

    reward_list = [];

    for i in range(num_episodes):
        # Reset the environment
        state = env.reset();
        reward_all = 0;
        is_Exit = False;

        for step in range(99):
            # Choose an action by greedily picking from Q table with noise
            # i.e chosen_action = argmax(Q(state, action))
            chosen_action = np.argmax(Q_table[state, :] + np.random.randn(1, env.action_space.n)*(1./(i+1)));

            # Get new state and reward from environment with the chosen_action
            new_state, reward, is_Exit, _ = env.step(chosen_action);

            # Update Q-table with new information
            # lr(learning rate) : (1-lr)-ratio to remain Q(current_state, chosen_action)
            # Q(s,a) = (1-lr)*Q(s,a) + lr*{reward + gamma*max_a(Q(next_state, a))}
            Q_table[state, chosen_action] += learning_rate*\
                                             (reward + gamma*np.max(Q_table[new_state, :])
                                              - Q_table[state, chosen_action]);
            reward_all += reward;
            state = new_state;

            # if we reach the exit, stop
            if is_Exit:
                break;

        reward_list.append(reward_all);


    print("Score over time : {}".format(sum(reward_list) / num_episodes));
    print("Final Q-Table : ");
    print(Q_table);



def Q_network_Learning():
    env = gym.make('FrozenLake-v0');

    num_state = env.observation_space.n;
    num_action = env.action_space.n;

    """ Make the Network """
    # Make a network : state -> a function Q(state, action) w.r.t action
    # input : one-hot vector for all states
    input_state = tf.placeholder(shape=[1, num_state], dtype=tf.float32)
    W = tf.Variable(tf.random_uniform([num_state, num_action], 0, 0.01));
    Q_output = tf.matmul(input_state, W);
    predict_action = tf.argmax(Q_output, 1);

    # Q_bellman : solution for Bellman equation
    Q_bellman = tf.placeholder(shape=[1, num_action], dtype=tf.float32);

    # loss : l2 norm of the difference Q_output and Q_bellman
    loss = tf.reduce_sum(tf.square(Q_output - Q_bellman));

    trainer = tf.train.GradientDescentOptimizer(learning_rate=0.1);
    optimizer = trainer.minimize(loss);

    init = tf.global_variables_initializer();

    """ Train the model """
    gamma = 0.99;
    greedy_epsilon = 0.2;
    num_episodes = 2000;
    train_num = 99;

    reward_list = [];
    ending_step_list = [];

    # np.identity(num_state) : num_state-onehot vectors for state
    # np.identity(num_state)[state] : a vector with only state-th coordinate 1.
    one_hot_states = np.identity(num_state);

    with tf.Session() as sess:
        init.run();

        for i in range(num_episodes):
            state = env.reset();
            reward_all = 0;
            is_Exit = False;
            j = 0;
            # Train the Q-network
            while j < train_num:
                j += 1;

                # chosen_action = [best action from the network]
                chosen_action, Q_out = sess.run([predict_action, Q_output],
                                                feed_dict={input_state: one_hot_states[state:state+1]});

                # Choose an action by greedily picking
                if np.random.rand(1) < greedy_epsilon:
                    chosen_action[0] = env.action_space.sample();


                next_state, reward, is_Exit, _ = env.step(chosen_action[0]);

                # Calculate Bellman equation
                # Q_next=Q(next_state, *) : output of the network with the 'next_state'
                # target_Q(s, a) = reward + gamma*max_a{Q(next_state, a)}
                Q_next = sess.run(Q_output, feed_dict={input_state: one_hot_states[next_state:next_state+1]});
                max_Q_next = np.max(Q_next);
                target_Q = Q_out;
                target_Q[0, chosen_action[0]] = reward + gamma*max_Q_next;

                # Train the network with the loss
                _, W1 = sess.run([optimizer, W], feed_dict={input_state: one_hot_states[state:state+1],
                                                                Q_bellman: target_Q});

                reward_all += reward;
                state = next_state;

                # if we reach the exit, stop
                if is_Exit:
                    # Reduce the chance of random action
                    greedy_epsilon = 1. /((i/50) + 10);
                    break;

            reward_list.append(reward_all);
            ending_step_list.append(j);

    print("Percent of successful episodes : {}".format(sum(reward_list)/num_episodes));

    plt.subplot(1,2,1);
    plt.plot(reward_list);
    plt.title("Reward");

    plt.subplot(1,2,2);
    plt.plot(ending_step_list);
    plt.title("Ending step");

    plt.show();




















































if __name__ == "__main__":
    print("Chapter 5 : Q Learning");
    #Q_table_Learning();
    Q_network_Learning();
