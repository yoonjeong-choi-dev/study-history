""" Contextual Bandit Problem
    - 환경에 상태가 주어진다.
    - 현재 상태에 따라 액션에 대한 보상이 달라진다.
    - 단, 상태가 이전 상태나 액션에 의해 결정되지 않는다.
    - 지연된 보상은 고려하지 않는다.

    => 1. m개의 손잡이가 있는 n개의 벤딧
       2. state : 손잡이를 당길 벤딧
"""


import tensorflow as tf
import tensorflow.contrib.slim as slim
import numpy as np


class contextual_bandit:
    def __init__(self):
        self.state = 0;

        # Set the list of arms in each bandit
        # 3 bandit with 4 handles
        self.bandits = np.array([[0.2,0,-0.0,-5],[0.1,-5,1,0.25],[-5,5,5,5]]);
        self.num_bandits = self.bandits.shape[0];
        self.num_actions = self.bandits.shape[1];


    def getBandit(self):
        # Return random state for each episode
        self.state = np.random.randint(0, len(self.bandits));
        return self.state;

    def pullArm(self, action):
        bandit = self.bandits[self.state, action];
        result = np.random.randn(1);

        if result > bandit:
            return 1;
        else:
            return -1;



class agent:
    """ The policy-based agent
    1. 입력 : 현재 상태 -> 반환 : 액션
            => 에이전트는 환경의 상태를 조건으로 액션을 취한다.
               이때, output 액션은 1층짜리 신경망을 통해 반환되는 값들의 argmax
    2. 1개의 가중치 세트
            : 각 가중치의 값은 주어진 밴딧의 특정 손잡이를 선택할 때 반환되는 값의 추정값
    3. 정책 경사 방법 사용
    """
    def __init__(self, lr, s_size, a_size):
        """
        :param lr: learning rate
        :param s_size: number of states
        :param a_size: number of actions
        """

        " Feed-forward part : input-current state / output - action"
        self.state_in = tf.placeholder(shape=[1], dtype=tf.int32);
        state_in_OH = slim.one_hot_encoding(self.state_in, s_size);
        # output : a single layer neural network
        #
        output = slim.fully_connected(state_in_OH, a_size,
                                      biases_initializer=None,
                                      activation_fn=tf.nn.sigmoid,
                                      weights_initializer=tf.ones_initializer());
        self.output = tf.reshape(output, [-1]);
        self.chosen_action = tf.argmax(self.output, axis=0);

        " Training Procedure "
        # feed the reward and chosen action into network to compute the loss
        # then, use the loss to update the network
        self.reward_holder = tf.placeholder(shape=[1], dtype=tf.float32);
        self.action_holder = tf.placeholder(shape=[1], dtype=tf.int32);
        self.responsible_weight = tf.slice(self.output, self.action_holder, [1]);
        self.loss = -(tf.log(self.responsible_weight)*self.reward_holder);
        optimizer = tf.train.GradientDescentOptimizer(learning_rate=lr);
        self.update = optimizer.minimize(self.loss);




def train_agent():
    tf.reset_default_graph();

    cBandit = contextual_bandit();
    myAgent = agent(lr=0.001, s_size=cBandit.num_bandits, a_size=cBandit.num_actions);

    weights = tf.trainable_variables()[0];

    # number of episodes for training the agent
    total_episodes = 10000;

    # total_reward[bandit][handle]
    total_reward = np.zeros([cBandit.num_bandits, cBandit.num_actions]);

    # probability to choose random action
    e = 0.1;

    # Initializer of tenser
    init = tf.global_variables_initializer();

    with tf.Session() as sess:
        sess.run(init);

        for i in range(total_episodes):
            # Get state from the environment
            state = cBandit.getBandit();

            # Greedy-epsilon policy
            if np.random.rand(1) < e:
                action = np.random.randint(cBandit.num_actions);
            else:
                action = sess.run(myAgent.chosen_action, feed_dict={myAgent.state_in: [state]});

            reward = cBandit.pullArm(action);

            # Update the network
            feed_dict = {myAgent.reward_holder:[reward],
                         myAgent.action_holder:[action],
                         myAgent.state_in:[state]};
            _, ww = sess.run([myAgent.update, weights], feed_dict=feed_dict);

            # Update total reward
            total_reward[state, action] += reward;


            if i % 500 == 0:
                print("Mean reward for each of the {}-bandits : {}".
                      format(cBandit.num_bandits, np.mean(total_reward, axis=1)));

    for bandit in range(cBandit.num_bandits):
        print("======={}-bandit=======".format(bandit+1));
        print("The agent thinks the arm-{} is most promising........".format(np.argmax(ww[bandit]+1)));
        if np.argmax(ww[bandit]) == np.argmin(cBandit.bandits[bandit]):
            print("..........and it was right");
        else:
            print("..........and it was wrong");
            print("The agent action : {}".format(ww[bandit]));
            print("The setting : {}".format(cBandit.bandits[bandit]));





train_agent();


















