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
CHAPTER_ID = "deep_learning";

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
warnings.simplefilter(action='ignore', category=FutureWarning)



def Xavier_and_He_init():
    reset_graph();
    n_inputs = 28 * 28;
    n_hidden1 = 300;

    X = tf.placeholder(tf.float32, shape=(None, n_inputs), name="X");

    he_init = tf.variance_scaling_initializer();

    # tf.layer.dense : default == Xavier
    hidden1_Xavier = tf.layers.dense(X, n_hidden1, activation=tf.nn.relu,
                                      name="hidden1");
    hidden1_he = tf.layers.dense(X, n_hidden1, activation=tf.nn.relu,
                                 kernel_initializer=he_init, name="hidden1");


def LeakyReLU_plot():
    def leacky_relu(z, alpha=0.01):
        return np.maximum(alpha*z, z);

    z = np.linspace(-5, 5, 200);
    plt.plot(z, leacky_relu(z, 0.05), "b-", linewidth=2);
    plt.plot([-5, 5], [0,0], 'k-');
    plt.plot([0,0], [-0.5, 4.2], 'k-');
    plt.grid(True);

    props = dict(facecolor="black", shrink=0.1);
    plt.annotate("Penetration", xytext=(-3.5, 0.5), xy=(-5, -0.2), arrowprops=props,
                 fontsize=14, ha="center");
    plt.title("Leaky ReLU activation", fontsize=14);
    plt.axis([-5, 5, -0.5, 4.2]);

    save_fig("leaky_relu_plot");
    plt.show();



def LeakyReLU_dnn():
    def leacky_relu(z, name=None):
        return tf.maximum(0.01*z, z, name=name);

    reset_graph();

    n_inputs = 28*28;
    n_hidden1, n_hidden2 = 300, 100;
    n_outputs = 10;

    n_epochs = 40;
    batch_size = 50;

    X = tf.placeholder(tf.float32, shape=(None, n_inputs), name="X");
    y = tf.placeholder(tf.int32, shape=(None), name="y");

    with tf.name_scope("dnn"):
        hidden1 = tf.layers.dense(X, n_hidden1, activation=leacky_relu, name="hidden1");
        hidden2 = tf.layers.dense(hidden1, n_hidden2, activation=leacky_relu, name="hidden2");
        logits = tf.layers.dense(hidden2, n_outputs, name="outputs");

    with tf.name_scope("loss"):
        entropy = tf.nn.sparse_softmax_cross_entropy_with_logits(labels=y, logits=logits);
        loss = tf.reduce_mean(entropy, name="loss");

    learning_rate = 0.01;

    with tf.name_scope("train"):
        optimizer = tf.train.GradientDescentOptimizer(learning_rate);
        training_op = optimizer.minimize(loss);

    with tf.name_scope("eval"):
        correct = tf.nn.in_top_k(logits, y, 1);
        accuracy = tf.reduce_mean(tf.cast(correct, tf.float32),name="accuracy");

    init = tf.global_variables_initializer();
    saver = tf.train.Saver();

    (train_x, train_y), (test_x, test_y) = tf.keras.datasets.mnist.load_data();

    train_x = train_x.astype(np.float32).reshape(-1, 28 * 28) / 255.0;
    train_y = train_y.astype(np.int32);

    valid_x, train_x = train_x[:5000], train_x[5000:];
    valid_y, train_y = train_y[:5000], train_y[5000:];

    test_x = test_x.astype(np.float32).reshape(-1, 28 * 28) / 255.0;
    test_y = test_y.astype(np.int32);


    def shuffle_batch(X, y, batch_size):
        random_idx = np.random.permutation(len(X));
        n_batches = len(X) // batch_size;
        for batch_idx in np.array_split(random_idx, n_batches):
            batch_x, batch_y = X[batch_idx], y[batch_idx];
            yield batch_x, batch_y;



    with tf.Session() as sess:
        init.run();

        for epoch in range(n_epochs):
            for batch_x, batch_y in shuffle_batch(train_x, train_y, batch_size):
                sess.run(training_op, feed_dict={X: batch_x, y: batch_y});


            acc_valid = accuracy.eval(feed_dict={X: valid_x, y: valid_y});
            print("{}-epoch valid acc : {}".format(epoch, acc_valid));

        save_path = saver.save(sess, "./myModel/ch11_DL/Leacky_relu_dnn_mnist_model.ckpt");

        acc_test = accuracy.eval(feed_dict={X: test_x, y: test_y});
        print("test acc :{}".format(acc_test));


def ELU_plot():
    def elu(z, alpha=1.0):
        return np.where(z<0, alpha*(np.exp(z) - 1), z);

    z = np.linspace(-5, 5, 200);

    plt.plot(z, elu(z, 1.5), "b-", linewidth=2);
    plt.plot([-5, 5], [0, 0], 'k-');
    plt.plot([-5, 5], [-1.5, -1.5], 'k--');
    plt.plot([0, 0], [-2.2, 3.2], "k-");
    plt.grid(True);
    plt.title(r"my ELU activation($\alpha=1.5$)", fontsize=14);
    plt.axis([-5, 5, -2.2, 3.2]);

    save_fig("elu_plot");
    plt.show();


def batch_normalization_repeated_code():
    reset_graph();


    n_inputs = 28 * 28;
    n_hidden1 = 300;
    n_hidden2 = 100;
    n_outputs = 10;
    momentum = 0.9;

    X = tf.placeholder(tf.float32, shape=(None, n_inputs), name="X");

    # batch_normalization - training
    # True for training / False  for prediction
    training = tf.placeholder_with_default(False, shape=(), name="training");

    hidden1 = tf.layers.dense(X, n_hidden1, name="hidden1");
    batch_norm1 = tf.layers.batch_normalization(hidden1, training=training, momentum=momentum);
    batch_norm1_act = tf.nn.elu(batch_norm1);

    hidden2 = tf.layers.dense(batch_norm1_act, n_hidden2, name="hidden2");
    batch_norm2 = tf.layers.batch_normalization(hidden2, training=training, momentum=momentum);
    batch_norm2_act = tf.nn.elu(batch_norm2);

    logits_before_batch_norm = tf.layers.dense(batch_norm2, n_outputs, name="outputs");
    logits = tf.layers.batch_normalization(logits_before_batch_norm,
                                           training=training, momentum=momentum);


def batch_normalization_not_repeated():
    from functools import partial
    reset_graph();
    n_inputs = 28 * 28;
    n_hidden1 = 300;
    n_hidden2 = 100;
    n_outputs = 10;
    momentum = 0.9;

    X = tf.placeholder(tf.float32, shape=(None, n_inputs), name="X");

    # batch_normalization - training
    # True for training / False  for prediction
    training = tf.placeholder_with_default(False, shape=(), name="training");

    my_batch_norm_layer = partial(tf.layers.batch_normalization,
                                  training=training,
                                  momentum=momentum);

    hidden1 = tf.layers.dense(X, n_hidden1, name="hidden1");
    batch_norm1 = my_batch_norm_layer(hidden1);
    batch_norm1_act = tf.nn.elu(batch_norm1);

    hidden2 = tf.layers.dense(batch_norm1_act, n_hidden2, name="hidden2");
    batch_norm2 = my_batch_norm_layer(hidden2);
    batch_norm2_act = tf.nn.elu(batch_norm2);

    logits_before_batch_norm = tf.layers.dense(batch_norm2, n_outputs, name="outputs");
    logits = my_batch_norm_layer(logits_before_batch_norm);


def batch_normalization_mnist():
    from functools import partial

    reset_graph();

    n_inputs = 28 * 28;
    n_hidden1 = 300;
    n_hidden2 = 100;
    n_outputs = 10;
    batch_norm_momentum = 0.9;

    X = tf.placeholder(tf.float32, shape=(None, n_inputs), name="X");
    y = tf.placeholder(tf.int32, shape=(None), name="y");
    training = tf.placeholder_with_default(False, shape=(), name='training');


    with tf.name_scope("dnn"):
        he_init = tf.variance_scaling_initializer();
        my_batch_norm_layer = partial(tf.layers.batch_normalization,
                                      training=training,
                                      momentum=batch_norm_momentum);

        my_dense_layer = partial(tf.layers.dense,
                                 kernel_initializer=he_init);

        hidden1 = my_dense_layer(X, n_hidden1, name="hidden1");
        batch_norm1 = tf.nn.elu(my_batch_norm_layer(hidden1));

        hidden2 = my_dense_layer(batch_norm1, n_hidden2, name="hidden2");
        batch_norm2 = tf.nn.elu(my_batch_norm_layer(hidden2));

        logits_before_batch_norm = tf.layers.dense(batch_norm2, n_outputs, name="outputs");
        logits = my_batch_norm_layer(logits_before_batch_norm);


    with tf.name_scope("loss"):
        entropy = tf.nn.sparse_softmax_cross_entropy_with_logits(labels=y,
                                                                 logits=logits);
        loss = tf.reduce_mean(entropy, name="loss");
        #loss_summary = tf.summary.scalar("log_loss", loss);



    learning_rate = 0.01;

    with tf.name_scope("train"):
        optimizer = tf.train.GradientDescentOptimizer(learning_rate);
        extra_update_ops = tf.get_collection(tf.GraphKeys.UPDATE_OPS);

        with tf.control_dependencies(extra_update_ops):
            training_op = optimizer.minimize(loss);





    with tf.name_scope("eval"):
        correct = tf.nn.in_top_k(logits, y, 1);
        accuracy = tf.reduce_mean(tf.cast(correct, tf.float32));


    init = tf.global_variables_initializer();
    saver = tf.train.Saver();

    n_epochs = 20;
    batch_size = 200;

    # UPDATE_OPS :  이동 평균과 분사을 계산하는 연산들의 콜렉션
    # extra_update_ops = tf.get_collection(tf.GraphKeys.UPDATE_OPS);


    # Set MNIST data
    (train_x, train_y), (test_x, test_y) = tf.keras.datasets.mnist.load_data();

    train_x = train_x.astype(np.float32).reshape(-1, 28 * 28) / 255.0;
    train_y = train_y.astype(np.int32);

    valid_x, train_x = train_x[:5000], train_x[5000:];
    valid_y, train_y = train_y[:5000], train_y[5000:];

    test_x = test_x.astype(np.float32).reshape(-1, 28 * 28) / 255.0;
    test_y = test_y.astype(np.int32);

    def shuffle_batch(X, y, batch_size):
        random_idx = np.random.permutation(len(X));
        n_batches = len(X) // batch_size;
        for batch_idx in np.array_split(random_idx, n_batches):
            batch_x, batch_y = X[batch_idx], y[batch_idx];
            yield batch_x, batch_y;



    with tf.Session() as sess:
        init.run();

        for epoch in range(n_epochs):
            for batch_x, batch_y in shuffle_batch(train_x, train_y, batch_size):
                sess.run(training_op,
                         feed_dict={training: True, X:batch_x, y:batch_y});


            acc_valid = accuracy.eval(feed_dict={X: valid_x, y: valid_y});
            print("{}-th epoch Validation accuracy : {}".format(epoch, acc_valid));

        save_path = saver.save(sess, "./myModel/ch11_DL/batch_norm_model.ckpt");
        acc_test = accuracy.eval(feed_dict={X: test_x, y: test_y});
        print("Test Accuracy : {}".format(acc_test));

        trainable_var = [v.name for v in tf.trainable_variables()];
        global_var = [v.name for v in tf.global_variables()];

        print("\nTrain variables : \n{}".format(trainable_var));
        print("\nGlobal variables : \n{}".format(global_var));


def gradient_clipping():
    reset_graph();

    n_inputs = 28 * 28;
    n_hidden1 = 300;
    n_hidden2 = 500;
    n_hidden3 = 50;
    n_hidden4 = 50;
    n_hidden5 = 50;
    n_outputs = 10;

    X = tf.placeholder(tf.float32, shape=(None, n_inputs), name="X");
    y = tf.placeholder(tf.int32, shape=(None), name="y");

    with tf.name_scope("dnn"):
        hidden1 = tf.layers.dense(X, n_hidden1, activation=tf.nn.relu, name="hidden1");
        hidden2 = tf.layers.dense(hidden1, n_hidden2, activation=tf.nn.relu, name="hidden2");
        hidden3 = tf.layers.dense(hidden2, n_hidden3, activation=tf.nn.relu, name="hidden3");
        hidden4 = tf.layers.dense(hidden3, n_hidden4, activation=tf.nn.relu, name="hidden4");
        hidden5 = tf.layers.dense(hidden4, n_hidden5, activation=tf.nn.relu, name="hidden5");
        logits = tf.layers.dense(hidden5, n_outputs, name="outputs");

    with tf.name_scope("loss"):
        entropy = tf.nn.sparse_softmax_cross_entropy_with_logits(labels=y, logits=logits);
        loss = tf.reduce_mean(entropy, name="loss");

    learning_rate = 0.01;
    threshold = 1.0;

    with tf.name_scope("train"):
        optimizer = tf.train.GradientDescentOptimizer(learning_rate);

        # grads_and_vars :  list for gradient w.r.t a variable
        grads_and_vars = optimizer.compute_gradients(loss);
        clipped_op = [(tf.clip_by_value(grad, -threshold, threshold), var)
                      for grad, var in grads_and_vars];
        training_op = optimizer.apply_gradients(clipped_op);


    with tf.name_scope("eval"):
        correct = tf.nn.in_top_k(logits, y, 1);
        accuracy = tf.reduce_mean(tf.cast(correct, tf.float32), name="accuracy");

    init = tf.global_variables_initializer();
    saver = tf.train.Saver();

    n_epochs = 20;
    batch_size = 200;

    # UPDATE_OPS :  이동 평균과 분사을 계산하는 연산들의 콜렉션
    # extra_update_ops = tf.get_collection(tf.GraphKeys.UPDATE_OPS);

    # Set MNIST data
    (train_x, train_y), (test_x, test_y) = tf.keras.datasets.mnist.load_data();

    train_x = train_x.astype(np.float32).reshape(-1, 28 * 28) / 255.0;
    train_y = train_y.astype(np.int32);

    valid_x, train_x = train_x[:5000], train_x[5000:];
    valid_y, train_y = train_y[:5000], train_y[5000:];

    test_x = test_x.astype(np.float32).reshape(-1, 28 * 28) / 255.0;
    test_y = test_y.astype(np.int32);

    def shuffle_batch(X, y, batch_size):
        random_idx = np.random.permutation(len(X));
        n_batches = len(X) // batch_size;
        for batch_idx in np.array_split(random_idx, n_batches):
            batch_x, batch_y = X[batch_idx], y[batch_idx];
            yield batch_x, batch_y;


    with tf.Session() as sess:
        init.run();

        for epoch in range(n_epochs):
            for batch_x, batch_y in shuffle_batch(train_x, train_y, batch_size):
                sess.run(training_op, feed_dict={X: batch_x, y:batch_y});

            acc_val = sess.run(accuracy, feed_dict={X: valid_x, y:valid_y});
            print("{}-epoch validation acc : {}".format(epoch, acc_val));

        save_path = saver.save(sess, "./myModel/ch11_DL/gradient_clipping_model.ckpt");
        acc_test = accuracy.eval(feed_dict={X: test_x, y: test_y});
        print("Test Accuracy : {}".format(acc_test));


def retrain_tensorflow_model():
    reset_graph();
    path_dir = "./myModel/ch11_DL/retrain_model/reuse_model.ckpt";
    saver = tf.train.import_meta_graph(path_dir+".meta");

    # for op in tf.get_default_graph().get_operations():
    #     print(op.name);

    #logdir = "./my_logs/leaky_relu";
    #file_writer = tf.summary.FileWriter(logdir, tf.get_default_graph());


    X = tf.get_default_graph().get_tensor_by_name("X:0");
    y = tf.get_default_graph().get_tensor_by_name("y:0");
    accuracy = tf.get_default_graph().get_tensor_by_name("eval/accuracy:0");
    training_op = tf.get_default_graph().get_operation_by_name("train/GradientDescent");

    for op in (X, y, accuracy, training_op):
        tf.add_to_collection("my_important_ops", op);

    X, y, accuracy, training_op = tf.get_collection("my_important_ops");


    """Test with real data set"""
    n_epochs = 20;
    batch_size = 200;
    # Set MNIST data
    (train_x, train_y), (test_x, test_y) = tf.keras.datasets.mnist.load_data();

    train_x = train_x.astype(np.float32).reshape(-1, 28 * 28) / 255.0;
    train_y = train_y.astype(np.int32);

    valid_x, train_x = train_x[:5000], train_x[5000:];
    valid_y, train_y = train_y[:5000], train_y[5000:];

    test_x = test_x.astype(np.float32).reshape(-1, 28 * 28) / 255.0;
    test_y = test_y.astype(np.int32);

    def shuffle_batch(X, y, batch_size):
        random_idx = np.random.permutation(len(X));
        n_batches = len(X) // batch_size;
        for batch_idx in np.array_split(random_idx, n_batches):
            batch_x, batch_y = X[batch_idx], y[batch_idx];
            yield batch_x, batch_y;

    with tf.Session() as sess:
        saver.restore(sess, path_dir);

        for epoch in range(n_epochs):
            for batch_x, batch_y in shuffle_batch(train_x, train_y, batch_size):
                sess.run(training_op, feed_dict={X: batch_x, y: batch_y});

            valid_acc = sess.run(accuracy, feed_dict={X: valid_x, y:valid_y});
            print("{}-epoch validation acc : {}".format(epoch, valid_acc));

        test_acc = sess.run(accuracy, feed_dict={X: test_x, y: test_y});
        print("Test acc : {}".format(test_acc));
        saver.save(sess, "./myModel/ch11_DL/retrain_model/new_model.ckpt");


def reuse_create_new_model_with_meta():
    reset_graph();
    model_path = "./myModel/ch11_DL/reuse_model/";
    trained_model =model_path + "gradient_clipping_model.ckpt";

    n_hidden4 = 20;
    n_outputs = 10;

    learning_rate = 0.01;

    saver = tf.train.import_meta_graph(trained_model+".meta");

    # for op in tf.get_default_graph().get_operations():
    #     print(op.name);

    # Call placeholder for input data and labels
    X = tf.get_default_graph().get_tensor_by_name("X:0");
    y = tf.get_default_graph().get_tensor_by_name("y:0");

    # Call the last layer to reuse
    hidden3 = tf.get_default_graph().get_tensor_by_name("dnn/hidden3/Relu:0");

    # make new layers
    new_hidden4 = tf.layers.dense(hidden3, n_hidden4, activation=tf.nn.relu, name="new_hidden4");
    new_logits = tf.layers.dense(new_hidden4, n_outputs, name="new_outputs");

    with tf.name_scope("new_loss"):
        entropy = tf.nn.sparse_softmax_cross_entropy_with_logits(labels=y, logits=new_logits);
        loss = tf.reduce_mean(entropy, name="loss");

    with tf.name_scope("new_eval"):
        correct = tf.nn.in_top_k(new_logits, y, 1);
        accuracy = tf.reduce_mean(tf.cast(correct, tf.float32), name="accuracy");

    with tf.name_scope("new_train"):
        optimizer = tf.train.GradientDescentOptimizer(learning_rate);
        training_op = optimizer.minimize(loss);

    init = tf.global_variables_initializer();

    # Make new saver to save new model
    new_saver = tf.train.Saver();

    """Test with real data set"""
    n_epochs = 20;
    batch_size = 200;
    # Set MNIST data
    (train_x, train_y), (test_x, test_y) = tf.keras.datasets.mnist.load_data();

    train_x = train_x.astype(np.float32).reshape(-1, 28 * 28) / 255.0;
    train_y = train_y.astype(np.int32);

    valid_x, train_x = train_x[:5000], train_x[5000:];
    valid_y, train_y = train_y[:5000], train_y[5000:];

    test_x = test_x.astype(np.float32).reshape(-1, 28 * 28) / 255.0;
    test_y = test_y.astype(np.int32);

    def shuffle_batch(X, y, batch_size):
        random_idx = np.random.permutation(len(X));
        n_batches = len(X) // batch_size;
        for batch_idx in np.array_split(random_idx, n_batches):
            batch_x, batch_y = X[batch_idx], y[batch_idx];
            yield batch_x, batch_y;

    with tf.Session() as sess:
        init.run();
        saver.restore(sess, trained_model);

        for epoch in range(n_epochs):
            for batch_x, batch_y in shuffle_batch(train_x, train_y, batch_size):
                sess.run(training_op, feed_dict={X: batch_x, y: batch_y});

            valid_acc = sess.run(accuracy, feed_dict={X: valid_x, y: valid_y});
            print("{}-epoch validation acc : {}".format(epoch, valid_acc));

        test_acc = sess.run(accuracy, feed_dict={X: test_x, y: test_y});
        print("Test acc : {}".format(test_acc));
        new_saver.save(sess, model_path+"new_model_with_meta.ckpt");


def reuse_create_new_model_with_code():
    reset_graph();
    model_path = "./myModel/ch11_DL/reuse_model/";
    trained_model =model_path + "gradient_clipping_model.ckpt";

    """ Copy some part of the code in gradient_clipping() """
    # n_inputs ~ n_hidden3 : reuse
    n_inputs = 28 * 28;
    n_hidden1 = 300;
    n_hidden2 = 500;
    n_hidden3 = 50;
    # From here, change the model
    n_hidden4 = 20;
    n_outputs = 10;

    X = tf.placeholder(tf.float32, shape=(None, n_inputs), name="X");
    y = tf.placeholder(tf.int32, shape=(None), name="y");

    with tf.name_scope("dnn"):
        hidden1 = tf.layers.dense(X, n_hidden1, activation=tf.nn.relu, name="hidden1");
        hidden2 = tf.layers.dense(hidden1, n_hidden2, activation=tf.nn.relu, name="hidden2");
        hidden3 = tf.layers.dense(hidden2, n_hidden3, activation=tf.nn.relu, name="hidden3");

        # Change the code
        hidden4 = tf.layers.dense(hidden3, n_hidden4, activation=tf.nn.relu, name="hidden4");
        logits = tf.layers.dense(hidden4, n_outputs, name="outputs");

    with tf.name_scope("loss"):
        entropy = tf.nn.sparse_softmax_cross_entropy_with_logits(labels=y, logits=logits);
        loss = tf.reduce_mean(entropy, name="loss");

    learning_rate = 0.01;
    threshold = 1.0;

    with tf.name_scope("train"):
        optimizer = tf.train.GradientDescentOptimizer(learning_rate);

        # grads_and_vars :  list for gradient w.r.t a variable
        grads_and_vars = optimizer.compute_gradients(loss);
        clipped_op = [(tf.clip_by_value(grad, -threshold, threshold), var)
                      for grad, var in grads_and_vars];
        training_op = optimizer.apply_gradients(clipped_op);

    with tf.name_scope("eval"):
        correct = tf.nn.in_top_k(logits, y, 1);
        accuracy = tf.reduce_mean(tf.cast(correct, tf.float32), name="accuracy");

    # Restore the model with partial variables to use
    reuse_variables = tf.get_collection(tf.GraphKeys.GLOBAL_VARIABLES,
                                        scope="hidden[123]");
    # restore_saver : restore only 1~3th layers
    restore_saver = tf.train.Saver(reuse_variables);

    init = tf.global_variables_initializer();
    saver = tf.train.Saver();

    """Test with real data set"""
    n_epochs = 20;
    batch_size = 200;
    # Set MNIST data
    (train_x, train_y), (test_x, test_y) = tf.keras.datasets.mnist.load_data();

    train_x = train_x.astype(np.float32).reshape(-1, 28 * 28) / 255.0;
    train_y = train_y.astype(np.int32);

    valid_x, train_x = train_x[:5000], train_x[5000:];
    valid_y, train_y = train_y[:5000], train_y[5000:];

    test_x = test_x.astype(np.float32).reshape(-1, 28 * 28) / 255.0;
    test_y = test_y.astype(np.int32);

    def shuffle_batch(X, y, batch_size):
        random_idx = np.random.permutation(len(X));
        n_batches = len(X) // batch_size;
        for batch_idx in np.array_split(random_idx, n_batches):
            batch_x, batch_y = X[batch_idx], y[batch_idx];
            yield batch_x, batch_y;

    with tf.Session() as sess:
        init.run();
        restore_saver.restore(sess, trained_model);

        for epoch in range(n_epochs):
            for batch_x, batch_y in shuffle_batch(train_x, train_y, batch_size):
                sess.run(training_op, feed_dict={X: batch_x, y: batch_y});

            valid_acc = sess.run(accuracy, feed_dict={X: valid_x, y: valid_y});
            print("{}-epoch validation acc : {}".format(epoch, valid_acc));

        test_acc = sess.run(accuracy, feed_dict={X: test_x, y: test_y});
        print("Test acc : {}".format(test_acc));
        saver.save(sess, model_path+"new_model_with_code.ckpt");


def reuse_different_framework_model():
    reset_graph();

    n_inputs = 2;
    n_hidden1 = 3;

    # Load the model from different framework
    original_w = [[1.,2.,3.],[4.,5.,6.]];
    original_b = [7., 8., 9.];

    X = tf.placeholder(tf.float32, shape=(None, n_inputs), name="X");
    hidden1 = tf.layers.dense(X, n_hidden1, activation=tf.nn.relu, name="hidden1");

    graph = tf.get_default_graph();


    """
    # Note that hidden1 is a variable to be trained
    # i.e hidden1 has two variable weight(kernel) w and bias b 
    # Thus hidden1 has some assign operations(handles) to initialize
    
    Suppose a tf.Variable v is made.
    Then 2 nodes are added to the graph.
        -1) v/read : read the variable
        -2) v/Assign : assign the initial value(v/initial_value) to the variable
    
    # Some inputs of v/Assign
    v/Assign.inputs[0] = variable itself
    v/Assign.inputs[1] = initial value assigned to v
    """
    assign_kernel = graph.get_operation_by_name("hidden1/kernel/Assign");
    assign_bias = graph.get_operation_by_name("hidden1/bias/Assign");
    init_kernel = assign_kernel.inputs[1];
    init_bias = assign_bias.inputs[1];

    init = tf.global_variables_initializer();

    with tf.Session() as sess:
        sess.run(init, feed_dict={init_kernel: original_w, init_bias: original_b});
        print(hidden1.eval(feed_dict={X: [[10.0, 11.0]]}));


def freezing_lower_layer():
    reset_graph();

    model_path = "./myModel/ch11_DL/freezing_lower_layers/";
    trained_model = model_path + "gradient_clipping_model.ckpt";

    """ Copy some part of the code in gradient_clipping() """
    # n_inputs ~ n_hidden3 : reuse
    n_inputs = 28 * 28;
    n_hidden1 = 300;
    n_hidden2 = 500;
    n_hidden3 = 50;
    # From here, change the model
    n_hidden4 = 20;
    n_outputs = 10;

    X = tf.placeholder(tf.float32, shape=(None, n_inputs), name="X");
    y = tf.placeholder(tf.int32, shape=(None), name="y");

    with tf.name_scope("dnn"):
        hidden1 = tf.layers.dense(X, n_hidden1, activation=tf.nn.relu, name="hidden1");
        hidden2 = tf.layers.dense(hidden1, n_hidden2, activation=tf.nn.relu, name="hidden2");
        hidden3 = tf.layers.dense(hidden2, n_hidden3, activation=tf.nn.relu, name="hidden3");

        # Change the code
        hidden4 = tf.layers.dense(hidden3, n_hidden4, activation=tf.nn.relu, name="hidden4");
        logits = tf.layers.dense(hidden4, n_outputs, name="outputs");

    with tf.name_scope("loss"):
        entropy = tf.nn.sparse_softmax_cross_entropy_with_logits(labels=y, logits=logits);
        loss = tf.reduce_mean(entropy, name="loss");

    learning_rate = 0.01;
    threshold = 1.0;

    """New line"""
    with tf.name_scope("train"):
        optimizer = tf.train.GradientDescentOptimizer(learning_rate);

        # Choose variables(layers) to update
        train_vars = tf.get_collection(tf.GraphKeys.TRAINABLE_VARIABLES,
                                       scope="hidden[34]|outputs");

        # grads_and_vars :  list for gradient w.r.t a variable
        grads_and_vars = optimizer.compute_gradients(loss=loss, var_list=train_vars);
        clipped_op = [(tf.clip_by_value(grad, -threshold, threshold), var)
                      for grad, var in grads_and_vars];
        training_op = optimizer.apply_gradients(clipped_op);


    with tf.name_scope("eval"):
        correct = tf.nn.in_top_k(logits, y, 1);
        accuracy = tf.reduce_mean(tf.cast(correct, tf.float32), name="accuracy");

    # Restore the model with partial variables to use
    reuse_variables = tf.get_collection(tf.GraphKeys.GLOBAL_VARIABLES,
                                        scope="hidden[123]");
    # restore_saver : restore only 1~3th layers
    restore_saver = tf.train.Saver(reuse_variables);

    init = tf.global_variables_initializer();
    saver = tf.train.Saver();

    """Test with real data set"""
    n_epochs = 20;
    batch_size = 200;
    # Set MNIST data
    (train_x, train_y), (test_x, test_y) = tf.keras.datasets.mnist.load_data();

    train_x = train_x.astype(np.float32).reshape(-1, 28 * 28) / 255.0;
    train_y = train_y.astype(np.int32);

    valid_x, train_x = train_x[:5000], train_x[5000:];
    valid_y, train_y = train_y[:5000], train_y[5000:];

    test_x = test_x.astype(np.float32).reshape(-1, 28 * 28) / 255.0;
    test_y = test_y.astype(np.int32);

    def shuffle_batch(X, y, batch_size):
        random_idx = np.random.permutation(len(X));
        n_batches = len(X) // batch_size;
        for batch_idx in np.array_split(random_idx, n_batches):
            batch_x, batch_y = X[batch_idx], y[batch_idx];
            yield batch_x, batch_y;

    with tf.Session() as sess:
        init.run();
        restore_saver.restore(sess, trained_model);

        for epoch in range(n_epochs):
            for batch_x, batch_y in shuffle_batch(train_x, train_y, batch_size):
                sess.run(training_op, feed_dict={X: batch_x, y: batch_y});

            valid_acc = sess.run(accuracy, feed_dict={X: valid_x, y: valid_y});
            print("{}-epoch validation acc : {}".format(epoch, valid_acc));

        test_acc = sess.run(accuracy, feed_dict={X: test_x, y: test_y});
        print("Test acc : {}".format(test_acc));
        saver.save(sess, model_path + "new_model_with_freezing.ckpt");


def caching_frozen_layer():
    reset_graph();
    model_path = "./myModel/ch11_DL/freezing_lower_layers/";
    trained_model = model_path + "gradient_clipping_model.ckpt";

    """ Copy some part of the code in gradient_clipping() """
    # n_inputs ~ n_hidden3 : reuse
    n_inputs = 28 * 28;
    n_hidden1 = 300;
    n_hidden2 = 500;
    n_hidden3 = 50;
    # From here, change the model
    n_hidden4 = 20;
    n_outputs = 10;

    X = tf.placeholder(tf.float32, shape=(None, n_inputs), name="X");
    y = tf.placeholder(tf.int32, shape=(None), name="y");

    with tf.name_scope("dnn"):
        hidden1 = tf.layers.dense(X, n_hidden1, activation=tf.nn.relu, name="hidden1");
        hidden2 = tf.layers.dense(hidden1, n_hidden2, activation=tf.nn.relu, name="hidden2");

        # Freeze layers up to 2-ed layer
        hidden2_stop = tf.stop_gradient(hidden2);

        hidden3 = tf.layers.dense(hidden2_stop, n_hidden3, activation=tf.nn.relu, name="hidden3");
        hidden4 = tf.layers.dense(hidden3, n_hidden4, activation=tf.nn.relu, name="hidden4");
        logits = tf.layers.dense(hidden4, n_outputs, name="outputs");

    with tf.name_scope("loss"):
        entropy = tf.nn.sparse_softmax_cross_entropy_with_logits(labels=y, logits=logits);
        loss = tf.reduce_mean(entropy, name="loss");

    learning_rate = 0.01;
    threshold = 1.0;

    with tf.name_scope("train"):
        optimizer = tf.train.GradientDescentOptimizer(learning_rate);

        # Choose variables(layers) to update
        train_vars = tf.get_collection(tf.GraphKeys.TRAINABLE_VARIABLES,
                                       scope="hidden[34]|outputs");

        # grads_and_vars :  list for gradient w.r.t a variable
        grads_and_vars = optimizer.compute_gradients(loss=loss, var_list=train_vars);
        clipped_op = [(tf.clip_by_value(grad, -threshold, threshold), var)
                      for grad, var in grads_and_vars];
        training_op = optimizer.apply_gradients(clipped_op);

    with tf.name_scope("eval"):
        correct = tf.nn.in_top_k(logits, y, 1);
        accuracy = tf.reduce_mean(tf.cast(correct, tf.float32), name="accuracy");

    # Restore the model with partial variables to use
    reuse_variables = tf.get_collection(tf.GraphKeys.GLOBAL_VARIABLES,
                                        scope="hidden[123]");
    # restore_saver : restore only 1~3th layers
    restore_saver = tf.train.Saver(reuse_variables);

    init = tf.global_variables_initializer();
    saver = tf.train.Saver();

    """Test with real data set"""
    n_epochs = 20;
    batch_size = 200;
    # Set MNIST data
    (train_x, train_y), (test_x, test_y) = tf.keras.datasets.mnist.load_data();

    train_x = train_x.astype(np.float32).reshape(-1, 28 * 28) / 255.0;
    train_y = train_y.astype(np.int32);

    valid_x, train_x = train_x[:5000], train_x[5000:];
    valid_y, train_y = train_y[:5000], train_y[5000:];

    test_x = test_x.astype(np.float32).reshape(-1, 28 * 28) / 255.0;
    test_y = test_y.astype(np.int32);

    n_batches = len(train_x) // batch_size;

    with tf.Session() as sess:
        init.run();
        restore_saver.restore(sess, trained_model);

        # Make cache
        hidden2_cache = sess.run(hidden2, feed_dict={X: train_x});
        hidden2_cache_valid = sess.run(hidden2, feed_dict={X: valid_x});


        for epoch in range(n_epochs):
            shuffled_idx = np.random.permutation(len(train_x));
            cache_batches = np.array_split(hidden2_cache[shuffled_idx], n_batches);
            y_batches = np.array_split(train_y[shuffled_idx], n_batches);

            for batch_x, batch_y in zip(cache_batches, y_batches):
                sess.run(training_op, feed_dict={hidden2: batch_x, y: batch_y});

            # Accuracy is also computed from 2ed hidden layer
            valid_acc= sess.run(accuracy, feed_dict={hidden2: hidden2_cache_valid,
                                                     y: valid_y});
            print("{}-epoch validation acc : {}".format(epoch, valid_acc));

        test_acc = sess.run(accuracy, feed_dict={X: test_x, y: test_y});
        print("Test acc : {}".format(test_acc));
        saver.save(sess, model_path + "new_model_with_caching_frozen_layer.ckpt");


def how_to_use_optimizers():
    learning_rate = 0.01;
    momentum = 0.9;
    decay = 0.9;

    momentum_opt = tf.train.MomentumOptimizer(learning_rate=learning_rate,
                                              momentum=momentum);

    nesterov_momentum_opt = tf.train.MomentumOptimizer(learning_rate=learning_rate,
                                                       momentum=momentum,
                                                       use_nesterov=True);

    rmsProp_opt = tf.train.RMSPropOptimizer(learning_rate=learning_rate,
                                            momentum=momentum,
                                            decay=decay,
                                            epsilon=1e-10);
    adam_opt = tf.train.AdamOptimizer(learning_rate=learning_rate,
                                      beta1=momentum, beta2=0.99,
                                      epsilon=1e-8);



def training_schedule_based_on_exponential_decay():
    reset_graph();

    model_path = "./myModel/ch11_DL/training_schedule/";

    n_inputs = 28*28;
    n_hidden1, n_hidden2 = 300, 50;
    n_outputs = 10;

    reset_graph();

    X = tf.placeholder(tf.float32, shape=(None, n_inputs), name="X");
    y = tf.placeholder(tf.int32, shape=(None), name="y");

    # Make a DNN
    with tf.name_scope("dnn"):
        hidden1 = tf.layers.dense(X, n_hidden1, name="hidden1",
                                  activation=tf.nn.relu);
        hidden2 = tf.layers.dense(hidden1, n_hidden2, name="hidden2",
                                  activation=tf.nn.relu);
        logits = tf.layers.dense(hidden2, n_outputs, name="outputs");

    with tf.name_scope("loss"):
        entropy = tf.nn.sparse_softmax_cross_entropy_with_logits(labels=y,
                                                                 logits=logits);
        loss = tf.reduce_mean(entropy, name="loss");

    with tf.name_scope("eval"):
        correct = tf.nn.in_top_k(logits, y, 1);
        accuracy = tf.reduce_mean(tf.cast(correct, tf.float32), name="accuracy");

    # New : momentum + exponential decay learning rate
    with tf.name_scope("train"):
        initial_learning_rate = 0.01;
        decay_steps = 10000;
        decay_rate = 0.1;
        global_step = tf.Variable(0, trainable=False, name="global_step");
        learning_rate = tf.train.exponential_decay(initial_learning_rate,
                                                   global_step,
                                                   decay_steps, decay_rate);
        optimizer = tf.train.MomentumOptimizer(learning_rate, momentum=0.9);
        training_op = optimizer.minimize(loss, global_step=global_step);

    init = tf.global_variables_initializer();
    saver = tf.train.Saver();

    """Test with real data set"""
    n_epochs = 20;
    batch_size = 200;
    # Set MNIST data
    (train_x, train_y), (test_x, test_y) = tf.keras.datasets.mnist.load_data();

    train_x = train_x.astype(np.float32).reshape(-1, 28 * 28) / 255.0;
    train_y = train_y.astype(np.int32);

    valid_x, train_x = train_x[:5000], train_x[5000:];
    valid_y, train_y = train_y[:5000], train_y[5000:];

    test_x = test_x.astype(np.float32).reshape(-1, 28 * 28) / 255.0;
    test_y = test_y.astype(np.int32);

    def shuffle_batch(X, y, batch_size):
        random_idx = np.random.permutation(len(X));
        n_batches = len(X) // batch_size;
        for batch_idx in np.array_split(random_idx, n_batches):
            batch_x, batch_y = X[batch_idx], y[batch_idx];
            yield batch_x, batch_y;

    with tf.Session() as sess:
        init.run();

        for epoch in range(n_epochs):
            for batch_x, batch_y in shuffle_batch(train_x, train_y, batch_size):
                sess.run(training_op, feed_dict={X: batch_x, y: batch_y});

            valid_acc = sess.run(accuracy, feed_dict={X: valid_x, y: valid_y});
            print("{}-epoch validation acc : {}".format(epoch, valid_acc));

        test_acc = sess.run(accuracy, feed_dict={X: test_x, y: test_y});
        print("Test acc : {}".format(test_acc));
        saver.save(sess, model_path + "my_model.ckpt");









def regularization_l1():
    reset_graph();
    model_path = "./myModel/ch11_DL/regularizations/";

    n_inputs = 28*28;
    n_hidden1 = 300;
    n_outputs = 10;

    X = tf.placeholder(tf.float32, shape=(None, n_inputs), name="X");
    y = tf.placeholder(tf.int32, shape=(None), name="y");


    with tf.name_scope("dnn"):
        hidden1 = tf.layers.dense(X, n_hidden1, activation=tf.nn.relu, name="hidden1");
        logits = tf.layers.dense(hidden1, n_outputs, name="outputs");

    # Regularization with l1-norm
    W1 = tf.get_default_graph().get_tensor_by_name("hidden1/kernel:0");
    W2 = tf.get_default_graph().get_tensor_by_name("outputs/kernel:0");

    l1_regularization = 0.001;

    with tf.name_scope("loss"):
        entropy = tf.nn.sparse_softmax_cross_entropy_with_logits(labels=y,
                                                                 logits=logits);

        base_loss = tf.reduce_mean(entropy, name="average_entropy");
        weight_loss = tf.reduce_sum(tf.abs(W1)) + tf.reduce_sum(tf.abs(W2));
        loss = tf.add(base_loss, l1_regularization*weight_loss, name="loss");


    with tf.name_scope("eval"):
        correct = tf.nn.in_top_k(logits, y, 1);
        accuracy = tf.reduce_mean(tf.cast(correct, tf.float32), name="accuracy");


    learning_rate = 0.01;

    with tf.name_scope("train"):
        optimizer = tf.train.GradientDescentOptimizer(learning_rate=learning_rate);
        training_op = optimizer.minimize(loss);


    init = tf.global_variables_initializer();
    saver = tf.train.Saver();

    """Test with real data set"""
    n_epochs = 20;
    batch_size = 200;
    # Set MNIST data
    (train_x, train_y), (test_x, test_y) = tf.keras.datasets.mnist.load_data();

    train_x = train_x.astype(np.float32).reshape(-1, 28 * 28) / 255.0;
    train_y = train_y.astype(np.int32);

    valid_x, train_x = train_x[:5000], train_x[5000:];
    valid_y, train_y = train_y[:5000], train_y[5000:];

    test_x = test_x.astype(np.float32).reshape(-1, 28 * 28) / 255.0;
    test_y = test_y.astype(np.int32);

    def shuffle_batch(X, y, batch_size):
        random_idx = np.random.permutation(len(X));
        n_batches = len(X) // batch_size;
        for batch_idx in np.array_split(random_idx, n_batches):
            batch_x, batch_y = X[batch_idx], y[batch_idx];
            yield batch_x, batch_y;

    with tf.Session() as sess:
        init.run();

        for epoch in range(n_epochs):
            for batch_x, batch_y in shuffle_batch(train_x, train_y, batch_size):
                sess.run(training_op, feed_dict={X: batch_x, y: batch_y});

            valid_acc = sess.run(accuracy, feed_dict={X: valid_x, y: valid_y});
            print("{}-epoch validation acc : {}".format(epoch, valid_acc));

        test_acc = sess.run(accuracy, feed_dict={X: test_x, y: test_y});
        print("Test acc : {}".format(test_acc));
        saver.save(sess, model_path + "l1_regularization.ckpt");



def regularization_l2():
    """ Different implementation from regularization_l1()
        - define regularization 'layers' instead of defining regularization directly
    """
    from functools import partial

    reset_graph();
    model_path = "./myModel/ch11_DL/regularizations/";

    n_inputs = 28 * 28;
    n_hidden1 = 300;
    n_hidden2 = 50;
    n_outputs = 10;

    X = tf.placeholder(tf.float32, shape=(None, n_inputs), name="X");
    y = tf.placeholder(tf.int32, shape=(None), name="y");

    l2_regularization = 0.001;


    my_dense_layer_l2 = partial(
        tf.layers.dense, activation=tf.nn.relu,
        kernel_regularizer=tf.contrib.layers.l2_regularizer(l2_regularization)
    );

    with tf.name_scope("dnn"):
        hidden1 = my_dense_layer_l2(X, n_hidden1, name="hidden1");
        hidden2 = my_dense_layer_l2(hidden1, n_hidden2, name="hidden2");
        logits = my_dense_layer_l2(hidden2, n_outputs, activation=None,
                                   name="outputs");


    with tf.name_scope("loss"):
        entropy = tf.nn.sparse_softmax_cross_entropy_with_logits(labels=y,
                                                                 logits=logits);
        base_loss = tf.reduce_mean(entropy, name="average_entropy");
        weight_loss = tf.get_collection(tf.GraphKeys.REGULARIZATION_LOSSES);
        loss = tf.add_n([base_loss]+weight_loss, name="loss");


    with tf.name_scope("eval"):
        correct = tf.nn.in_top_k(logits, y, 1);
        accuracy = tf.reduce_mean(tf.cast(correct, tf.float32), name="accuracy");


    learning_rate = 0.01;

    with tf.name_scope("train"):
        optimizer = tf.train.GradientDescentOptimizer(learning_rate=learning_rate);
        training_op = optimizer.minimize(loss);


    init = tf.global_variables_initializer();
    saver = tf.train.Saver();

    """Test with real data set"""
    n_epochs = 20;
    batch_size = 200;
    # Set MNIST data
    (train_x, train_y), (test_x, test_y) = tf.keras.datasets.mnist.load_data();

    train_x = train_x.astype(np.float32).reshape(-1, 28 * 28) / 255.0;
    train_y = train_y.astype(np.int32);

    valid_x, train_x = train_x[:5000], train_x[5000:];
    valid_y, train_y = train_y[:5000], train_y[5000:];

    test_x = test_x.astype(np.float32).reshape(-1, 28 * 28) / 255.0;
    test_y = test_y.astype(np.int32);

    def shuffle_batch(X, y, batch_size):
        random_idx = np.random.permutation(len(X));
        n_batches = len(X) // batch_size;
        for batch_idx in np.array_split(random_idx, n_batches):
            batch_x, batch_y = X[batch_idx], y[batch_idx];
            yield batch_x, batch_y;

    with tf.Session() as sess:
        init.run();

        for epoch in range(n_epochs):
            for batch_x, batch_y in shuffle_batch(train_x, train_y, batch_size):
                sess.run(training_op, feed_dict={X: batch_x, y: batch_y});

            valid_acc = sess.run(accuracy, feed_dict={X: valid_x, y: valid_y});
            print("{}-epoch validation acc : {}".format(epoch, valid_acc));

        test_acc = sess.run(accuracy, feed_dict={X: test_x, y: test_y});
        print("Test acc : {}".format(test_acc));
        saver.save(sess, model_path + "l2_regularization.ckpt");




def drop_out():
    reset_graph();
    model_path = "./myModel/ch11_DL/regularizations/";

    n_inputs = 28 * 28;
    n_hidden1 = 300;
    n_hidden2 = 50;
    n_outputs = 10;

    X = tf.placeholder(tf.float32, shape=(None, n_inputs), name="X");
    y = tf.placeholder(tf.int32, shape=(None), name="y");

    # training : True => drop out / False => drop out X
    training = tf.placeholder_with_default(False, shape=(), name="training");
    dropout_ratio = 0.5;

    with tf.name_scope("dnn"):
        X_drop = tf.layers.dropout(X, dropout_ratio, training=training);
        hidden1 = tf.layers.dense(X_drop, n_hidden1, activation=tf.nn.relu,
                                  name="hidden1");
        hidden1_drop = tf.layers.dropout(hidden1, dropout_ratio, training=training);
        hidden2 = tf.layers.dense(hidden1_drop, n_hidden2, activation=tf.nn.relu,
                                  name="hidden2");
        hidden2_drop = tf.layers.dropout(hidden2, dropout_ratio, training=training);
        logits = tf.layers.dense(hidden2_drop, n_outputs, name="outputs");

    with tf.name_scope("loss"):
        entropy = tf.nn.sparse_softmax_cross_entropy_with_logits(labels=y,logits=logits);
        loss = tf.reduce_mean(entropy, name="loss");

    learning_rate = 0.001;
    with tf.name_scope("train"):
        optimizer = tf.train.MomentumOptimizer(learning_rate=learning_rate,
                                               momentum=0.9);
        training_op = optimizer.minimize(loss);

    with tf.name_scope("eval"):
        correct = tf.nn.in_top_k(logits, y, 1);
        accuracy = tf.reduce_mean(tf.cast(correct, tf.float32), name="accuracy");

    init = tf.global_variables_initializer();
    saver = tf.train.Saver();

    """Test with real data set"""
    n_epochs = 50;
    batch_size = 50;
    # Set MNIST data
    (train_x, train_y), (test_x, test_y) = tf.keras.datasets.mnist.load_data();

    train_x = train_x.astype(np.float32).reshape(-1, 28 * 28) / 255.0;
    train_y = train_y.astype(np.int32);

    valid_x, train_x = train_x[:5000], train_x[5000:];
    valid_y, train_y = train_y[:5000], train_y[5000:];

    test_x = test_x.astype(np.float32).reshape(-1, 28 * 28) / 255.0;
    test_y = test_y.astype(np.int32);

    def shuffle_batch(X, y, batch_size):
        random_idx = np.random.permutation(len(X));
        n_batches = len(X) // batch_size;
        for batch_idx in np.array_split(random_idx, n_batches):
            batch_x, batch_y = X[batch_idx], y[batch_idx];
            yield batch_x, batch_y;

    with tf.Session() as sess:
        init.run();

        for epoch in range(n_epochs):
            for batch_x, batch_y in shuffle_batch(train_x, train_y, batch_size):
                sess.run(training_op, feed_dict={training:True, X: batch_x, y: batch_y});

            valid_acc = sess.run(accuracy, feed_dict={X: valid_x, y: valid_y});
            print("{}-epoch validation acc : {}".format(epoch, valid_acc));

        test_acc = sess.run(accuracy, feed_dict={X: test_x, y: test_y});
        print("Test acc : {}".format(test_acc));
        saver.save(sess, model_path + "drop_out.ckpt");





def max_norm_regularization():

    """ Define a regularization function
     - input 에 대한 특정 함수를 반환하는 함수
    """
    def max_norm_regularizer(threshold, axes=1, name="max_norm", collection="max_norm"):

        def max_norm(weights):
            clipped = tf.clip_by_norm(weights, clip_norm=threshold, axes=axes);

            # clip_weights : 각 훈련스텝이 끝나고 반드시 실행 시켜줘야 하는 부분
            # 이것을 실행시켜줘야 규제가 가능함.
            clip_weights = tf.assign(weights, clipped, name=name);
            # 그래프에 추가하기 위해 add_to_collection을 사용
            tf.add_to_collection(collection, clip_weights);
            return None;

        return max_norm;


    reset_graph();

    model_path = "./myModel/ch11_DL/regularizations/";

    n_inputs = 28 * 28;
    n_hidden1 = 300;
    n_hidden2 = 50;
    n_outputs = 10;

    learning_rate = 0.01;
    momentum = 0.9;

    X = tf.placeholder(tf.float32, shape=(None, n_inputs), name="X");
    y = tf.placeholder(tf.int32, shape=(None), name="y");

    # threshold : the max norm of the weights about hidden layers
    threshold = 1.0;
    max_norm_reg = max_norm_regularizer(threshold=threshold);


    with tf.name_scope("dnn"):
        hidden1 = tf.layers.dense(X, n_hidden1, activation=tf.nn.relu,
                                  kernel_regularizer=max_norm_reg,
                                  name="hidden1");
        hidden2 = tf.layers.dense(hidden1, n_hidden2, activation=tf.nn.relu,
                                  kernel_regularizer=max_norm_reg,
                                  name="hidden2");
        logits = tf.layers.dense(hidden2, n_outputs, name="outputs");

    with tf.name_scope("loss"):
        entropy = tf.nn.sparse_softmax_cross_entropy_with_logits(labels=y, logits=logits);
        loss = tf.reduce_mean(entropy, name="loss");

    with tf.name_scope("train"):
        optimizer = tf.train.MomentumOptimizer(learning_rate, momentum=momentum);
        training_op = optimizer.minimize(loss);

    with tf.name_scope("eval"):
        correct = tf.nn.in_top_k(logits, y, 1);
        accuracy = tf.reduce_mean(tf.cast(correct, tf.float32));

    init = tf.global_variables_initializer();
    saver = tf.train.Saver();

    """Test with real data set"""
    n_epochs = 20;
    batch_size = 50;

    # Set MNIST data
    (train_x, train_y), (test_x, test_y) = tf.keras.datasets.mnist.load_data();

    train_x = train_x.astype(np.float32).reshape(-1, 28 * 28) / 255.0;
    train_y = train_y.astype(np.int32);

    valid_x, train_x = train_x[:5000], train_x[5000:];
    valid_y, train_y = train_y[:5000], train_y[5000:];

    test_x = test_x.astype(np.float32).reshape(-1, 28 * 28) / 255.0;
    test_y = test_y.astype(np.int32);

    def shuffle_batch(X, y, batch_size):
        random_idx = np.random.permutation(len(X));
        n_batches = len(X) // batch_size;
        for batch_idx in np.array_split(random_idx, n_batches):
            batch_x, batch_y = X[batch_idx], y[batch_idx];
            yield batch_x, batch_y;


    clip_all_weights = tf.get_collection("max_norm");

    with tf.Session() as sess:
        init.run();

        for epoch in range(n_epochs):
            for batch_x, batch_y in shuffle_batch(train_x, train_y, batch_size):
                sess.run(training_op, feed_dict={X: batch_x, y: batch_y});
                sess.run(clip_all_weights);     # 추가 부분!

            valid_acc = sess.run(accuracy, feed_dict={X: valid_x, y: valid_y});
            print("{}-epoch validation acc : {}".format(epoch, valid_acc));

        test_acc = sess.run(accuracy, feed_dict={X: test_x, y: test_y});
        print("Test acc : {}".format(test_acc));
        saver.save(sess, model_path + "max_norm_regularization.ckpt");
































if __name__ == "__main__":
    print("Chapter11 : Deep Learning");
    #LeakyReLU_plot();
    #LeakyReLU_dnn();
    #ELU_plot();
    #batch_normalization_mnist();
    #gradient_clipping();
    #retrain_tensorflow_model();
    #reuse_create_new_model_with_meta();
    #reuse_create_new_model_with_code();
    #reuse_different_framework_model();
    #freezing_lower_layer()
    #caching_frozen_layer();
    #training_schedule_based_on_exponential_decay();
    #regularization_l1();
    #regularization_l2();
    #drop_out();
    max_norm_regularization();
