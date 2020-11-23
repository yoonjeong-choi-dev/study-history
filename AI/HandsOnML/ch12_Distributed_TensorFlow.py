from __future__ import division, print_function, unicode_literals

import os

import numpy as np
import matplotlib.pyplot as plt
import matplotlib

import tensorflow as tf

# To avoid CPU error message
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'

""" Setting of matplotlib """
plt.rcParams['axes.labelsize'] = 14;
plt.rcParams['xtick.labelsize'] = 12;
plt.rcParams['ytick.labelsize'] = 12;

""" Useful function """
PROJECT_ROOT_DIR = ".";
CHAPTER_ID = "distributed_tensorflow";

# Save the graph
def save_fig(fig_id, tight_layout=True):

    path = os.path.join(PROJECT_ROOT_DIR, "My_images", CHAPTER_ID, fig_id+".png");
    if tight_layout:
        plt.tight_layout();

    if not (os.path.isdir(os.path.join(PROJECT_ROOT_DIR, "My_images", CHAPTER_ID))):
        os.makedirs(os.path.join(PROJECT_ROOT_DIR, "My_images", CHAPTER_ID));

    plt.savefig(path, format='png', dpi=300);
    print("figure is saved...........................!")


# Initialize the graph
def reset_graph(seed=42):
    tf.reset_default_graph();
    tf.set_random_seed(seed);
    np.random.seed(42);

import warnings
#warnings.simplefilter(action='ignore', category=FutureWarning)





def local_server():
    c = tf.constant("Hello~ Distributed TensorFlow!");
    server = tf.train.Server.create_local_server();

    with tf.Session(server.target) as sess:
        print(sess.run(c));
























































if __name__ == "__main__":
    print("Chapter 12 : Distributed TensorFlow");
    local_server();