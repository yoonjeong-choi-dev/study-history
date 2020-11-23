import tensorflow as tf
import tensorflow.contrib.slim as slim
import numpy as np
import matplotlib.pyplot as plt
import gym


env = gym.make('CartPole-v0');

# gamma : 각각의 액션이 즉각적인 보상뿐만 아니라 추후에 오게 될  모든 보상에 대해서도
#         어느 정도씩 책임을 지게하는 효과를 만들기위한 계수 (할인계수)
gamma = 0.99;



def discount_rewards(reward):
    """
    :param reward: a 1-D array of rewards
    :return: discounted reward
    """
    discounted_reward = np.zeros_like(reward);
    running_add = 0;

    for time in reversed(range(0, reward.size)):
        running_add = running_add*gamma + reward[time];
        discounted_reward[time] = running_add;

    return discounted_reward;


class agent:
    """ The policy-based agent

    """

    def __init__(self, lr, s_size, a_size, h_size):
        """
        :param lr: learning rate
        :param s_size: number of states
        :param a_size: number of actions
        :param h_size: number of hidden neurons
        """

        " Feed-forward part : input-current state / output - action "
        self.state_in = tf.placeholder(shape=[None, s_size], dtype=tf.float32);

        hidden = slim.fully_connected(self.state_in, h_size,
                                      biases_initializer=None,
                                      activation_fn=tf.nn.relu);
        self.output = slim.fully_connected(hidden, a_size,
                                           biases_initializer=None,
                                           activation_fn=tf.nn.softmax);
        self.chosen_action = tf.argmax(self.output, axis=1);

        " Training Procedure "
        # feed the reward and chosen action into network to compute the loss
        # then, use the loss to update the network
        self.reward_holder = tf.placeholder(shape=[None], dtype=tf.float32);
        self.action_holder = tf.placeholder(shape=[None], dtype=tf.int32);

        # tf.shape(self.output)[0] =
        # tf.shape(self.output)[1] =
        self.indices = tf.range(0, tf.shape(self.output)[0]) * \
            tf.shape(self.output)[1] + self.action_holder;
        self.responsible_outputs = tf.gather(tf.reshape(self.output, [-1]), self.indices);

        self.loss = -tf.reduce_mean(tf.log(self.responsible_outputs)*self.reward_holder);

        train_variable = tf.trainable_variables();
        self.gradient_holders = [];

        for idx, var in enumerate(train_variable):
            placeholder = tf.placeholder(tf.float32, name=str(idx)+'_holder');
            self.gradient_holders.append(placeholder);

        self.gradients = tf.gradients(self.loss, train_variable);

        optimizer = tf.train.AdamOptimizer(learning_rate=lr);
        self.update_batch = optimizer.apply_gradients(zip(self.gradient_holders, train_variable));



def train_agent():
    tf.reset_default_graph();

    myAgent = agent(lr=0.01, s_size=4, a_size=2, h_size=8);

    # number of episodes for training the agent
    total_episodes = 5000;
    max_ep = 999;
    update_frequency = 5;

    init = tf.global_variables_initializer();

    with tf.Session() as sess:
        sess.run(init);
        total_reward = [];
        total_length = [];

        gradBuffer = sess.run(tf.trainable_variables());
        for ix, grad in enumerate(gradBuffer):
            gradBuffer[ix] = grad*0;

        for i in range(total_episodes):
            state = env.reset();
            running_reward = 0;
            ep_history = [];

            for j in range(max_ep):
                # Choose the output action of the network with some probability
                action_dist = sess.run(myAgent.output, feed_dict={myAgent.state_in: [state]});
                action = np.random.choice(action_dist[0], p=action_dist[0]);
                action = np.argmax(action_dist==action);

                #
                state1, reward, d, _ = env.step(action);
                ep_history.append([state, action, reward, state1]);
                state = state1;
                running_reward += reward;

                if d == True:
                    # update the network
                    ep_history= np.array(ep_history);
                    ep_history[:, 2] = discount_rewards(ep_history[:, 2]);
                    feed_dict = {myAgent.reward_holder: ep_history[:, 2],
                                 myAgent.action_holder: ep_history[:, 1],
                                 myAgent.state_in: np.vstack(ep_history[:, 0])};
                    grads = sess.run(myAgent.gradients, feed_dict=feed_dict);

                    for idx, grad in enumerate(grads):
                        gradBuffer[idx] += grad;


                    if i % update_frequency == 0 and i != 0:
                        feed_dict = dictionary = dict(zip(myAgent.gradient_holders, gradBuffer));
                        _ = sess.run(myAgent.update_batch, feed_dict=feed_dict);

                        for ix, grad in enumerate(gradBuffer):
                            gradBuffer[ix] = grad * 0;

                    total_reward.append(running_reward);
                    total_length.append(j);
                    break;



            if i % 100 == 0:
                print(np.mean(total_reward[-100:]));

















train_agent();




















