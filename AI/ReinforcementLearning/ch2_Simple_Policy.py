""" Simple Multi-armed bandit (손잡이가 n개인 슬롯머신)
    - 솔롯머신의 갯수는 1개.
    - 각각의 손잡이는 다른 확률로 보상 제공
    - 액션마다 다른 보상
    - 환경에 상태(state)이 주어지지 않음 
      => 액션에 대한 보상이 상태에 의존하지 않음
    - 액션이 시간이 지연되지 않는다

"""

import tensorflow as tf
import tensorflow.contrib.slim as slim
import numpy as np


""" Define the Bandit
 - 4-armed bandit
 - 4-th arm(idx=3) is set to provide a positive reward at most
 - input : the index of arm to pull

"""
bandit_arms = [0.2, 0, -0.2, -2];
num_arms = len(bandit_arms);

def pullBandit(action):
    # Get a random number from the normal distribution
    result = np.random.randn(1);

    # Positive reward :
    if result > bandit_arms[action]:
        return 1;
    # Negative reward :
    else:
        return -1;



""" Define Agent : simple neural network
 - Use Policy Gradient to maximize the reward for a selected action
 
"""
tf.reset_default_graph();

# Feed-forward part of the network
weights = tf.Variable(tf.ones([num_arms]));
output = tf.nn.softmax(weights);

# Training Procedure
# feed the reward and chosen action into network to compute the loss
# then, use the loss to update the network
reward_holder = tf.placeholder(shape=[1], dtype=tf.float32);
action_holder = tf.placeholder(shape=[1], dtype=tf.int32);

# responsible_output : output with the specific action in the action_holder
responsible_output = tf.slice(output, action_holder, [1]);

# Loss : -log(policy)*Advantage
#       , where policy : sequence of actions
#               advantage : criteria of action
loss = -(tf.log(responsible_output)*reward_holder);

optimizer = tf.train.AdamOptimizer(learning_rate=1e-3);
update = optimizer.minimize(loss);

""" Train the agent 
 - train the agent by taking actions in our environment and by receiving rewards
 - using rewards and actions, update the network so that the chosen actions provide larger rewards
"""
# the number of episodes to train the agent
total_epochs = 1000;

# the constant for tracking the training
num_track = 50;

# the score(reward) of each bandit arm
total_reward = np.zeros(num_arms);

init = tf.global_variables_initializer();

with tf.Session() as sess:
    sess.run(init);

    for i in range(total_epochs):
        # Choose an action according to Boltzmann distribution
        actions = sess.run(output);
        a = np.random.choice(actions, p=actions);
        action = np.argmax(actions == a);

        # Get a reward w.r.t the chosen action
        reward = pullBandit(action);

        # Update the network
        _, resp, ww = sess.run([update, responsible_output, weights],
                               feed_dict={reward_holder:[reward], action_holder:[action]});

        # Update the total reward
        total_reward[action] += reward;

        if i % num_track == 0:
            print("Running reward for the {}-arms of the bandit : {}".format(num_arms, total_reward));



print("\nThe agent thinks the arm-{} is the most promising.....".format(np.argmax(ww)+1));

print("\nCompare the agent action with the original setting.....");
if np.argmax(ww) == np.argmax(-np.array(bandit_arms)):
    print("The action of the agent is right!");
else:
    print("The action of the agent is wrong!");
    print("The action : {}".format(ww));
    print("The setting : {}".format(np.argmax(-np.array(bandit_arms))));

























