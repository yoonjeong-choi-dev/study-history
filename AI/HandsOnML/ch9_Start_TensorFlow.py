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
CHAPTER_ID = "start_Tensor_Flow";

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




""" Main code """
def first_computation_graph():
    x = tf.Variable(3, name="constant_x");
    y = tf.Variable(4, name="constant_y");
    f = x*x*y + y + 2;

    with tf.Session() as sess:
        x.initializer.run();
        y.initializer.run();
        result = f.eval();

    print("x : {}".format(x));
    print("x name : {}".format(x.name));
    print("First Result : {}".format(result));


def second_computation_graph():
    x = tf.Variable(3, name="x");
    y = tf.Variable(4, name="y");
    f = x * x * y + y + 2;

    init = tf.global_variables_initializer();

    with tf.Session() as sess:
        init.run();
        result = f.eval();

    print("Second Result : {}".format(result));
    print(x);


def normal_equation_tf():
    from sklearn.datasets import fetch_california_housing
    from sklearn.linear_model import LinearRegression

    housing = fetch_california_housing();
    n_data, n_feature = housing.data.shape;
    housing_data_with_bias = np.c_[np.ones((n_data, 1)), housing.data];

    # normal equation : (X.T * X)^(-1) * X.T * y

    # 1. Tensor flow
    X = tf.constant(housing_data_with_bias, dtype=tf.float32, name="X");
    y = tf.constant(housing.target.reshape(-1, 1), dtype=tf.float32, name="y");
    X_transpose = tf.transpose(X);
    theta = tf.matmul(tf.matmul(tf.matrix_inverse(tf.matmul(X_transpose, X)),
                                X_transpose), y);

    with tf.Session() as sess:
        theta_tf = theta.eval();

    # 2. Numpy
    X = housing_data_with_bias;
    y = housing.target.reshape(-1, 1);
    theta_numpy = np.linalg.inv(X.T.dot(X)).dot(X.T).dot(y);

    # 3. LinearRegression with scikit learn
    lin_reg = LinearRegression();
    lin_reg.fit(X, y);
    theta_lin_reg = np.r_[lin_reg.intercept_.reshape(-1, 1), lin_reg.coef_.T];

    print("1. Tensor flow : \n{}".format(theta_tf.T));
    print("2. Numpy       : \n{}".format(theta_numpy.T));
    print("3. Scikit learn: \n{}".format(theta_lin_reg.T));


def gradient_descent_in_handle():
    from sklearn.datasets import fetch_california_housing
    from sklearn.preprocessing import StandardScaler

    housing = fetch_california_housing();
    n_data, n_feature = housing.data.shape;

    scaler = StandardScaler();
    scaled_housing_data = scaler.fit_transform(housing.data);
    scaled_housing_data_with_bias = np.c_[np.ones((n_data, 1)), scaled_housing_data];

    reset_graph();

    n_epochs = 1000;
    learning_rate = 0.1;

    X = tf.constant(scaled_housing_data_with_bias, dtype=tf.float32, name="X");
    y = tf.constant(housing.target.reshape(-1, 1), dtype=tf.float32, name="y");
    theta = tf.Variable(tf.random_uniform([n_feature+1, 1], -1.0, 1.0, seed=42),
                        dtype=tf.float32,
                        name="theta");
    pred = tf.matmul(X, theta, name="prediction");
    error = pred - y;
    mse = tf.reduce_mean(tf.square(error), name="mse");

    gradient = 2/n_data * tf.matmul(tf.transpose(X), error);
    training_op = tf.assign(theta, theta - learning_rate*gradient);

    initializer = tf.global_variables_initializer();

    with tf.Session() as sess:
        initializer.run();

        for epoch in range(n_epochs):
            if epoch % 100 == 0:
                print("Epoch : {}   - MSE : {}".format(epoch, mse.eval()));

            sess.run(training_op);

        best_theta = theta.eval();

    print("Best theta : \n{}".format(best_theta));




def gradient_descent_with_auto_diff():
    from sklearn.datasets import fetch_california_housing
    from sklearn.preprocessing import StandardScaler

    housing = fetch_california_housing();
    n_data, n_feature = housing.data.shape;

    scaler = StandardScaler();
    scaled_housing_data = scaler.fit_transform(housing.data);
    scaled_housing_data_with_bias = np.c_[np.ones((n_data, 1)), scaled_housing_data];

    reset_graph();

    n_epochs = 1000;
    learning_rate = 0.1;

    X = tf.constant(scaled_housing_data_with_bias, dtype=tf.float32, name="X");
    y = tf.constant(housing.target.reshape(-1, 1), dtype=tf.float32, name="y");
    theta = tf.Variable(tf.random_uniform([n_feature + 1, 1], -1.0, 1.0, seed=42),
                        dtype=tf.float32,
                        name="theta");
    pred = tf.matmul(X, theta, name="prediction");
    error = pred - y;
    mse = tf.reduce_mean(tf.square(error), name="mse");

    " only different !! "
    gradient = tf.gradients(mse, [theta])[0];

    training_op = tf.assign(theta, theta - learning_rate * gradient);

    initializer = tf.global_variables_initializer();

    with tf.Session() as sess:
        initializer.run();

        for epoch in range(n_epochs):
            if epoch % 100 == 0:
                print("Epoch : {}   - MSE : {}".format(epoch, mse.eval()));

            sess.run(training_op);

        best_theta = theta.eval();

    print("Best theta : \n{}".format(best_theta));


def gradient_descent_with_tf_optimizer():
    from sklearn.datasets import fetch_california_housing
    from sklearn.preprocessing import StandardScaler

    housing = fetch_california_housing();
    n_data, n_feature = housing.data.shape;

    scaler = StandardScaler();
    scaled_housing_data = scaler.fit_transform(housing.data);
    scaled_housing_data_with_bias = np.c_[np.ones((n_data, 1)), scaled_housing_data];

    reset_graph();

    n_epochs = 1000;
    learning_rate = 0.1;

    X = tf.constant(scaled_housing_data_with_bias, dtype=tf.float32, name="X");
    y = tf.constant(housing.target.reshape(-1, 1), dtype=tf.float32, name="y");
    theta = tf.Variable(tf.random_uniform([n_feature + 1, 1], -1.0, 1.0, seed=42),
                        dtype=tf.float32,
                        name="theta");
    pred = tf.matmul(X, theta, name="prediction");
    error = pred - y;
    mse = tf.reduce_mean(tf.square(error), name="mse");

    " only different !! "
    optimizer = tf.train.GradientDescentOptimizer(learning_rate=learning_rate);
    training_op = optimizer.minimize(mse);

    initializer = tf.global_variables_initializer();

    with tf.Session() as sess:
        initializer.run();

        for epoch in range(n_epochs):
            if epoch % 100 == 0:
                print("Epoch : {}   - MSE : {}".format(epoch, mse.eval()));

            sess.run(training_op);

        best_theta = theta.eval();

    print("Best theta : \n{}".format(best_theta));


def gradient_descent_with_moment_optimizer():
    from sklearn.datasets import fetch_california_housing
    from sklearn.preprocessing import StandardScaler

    housing = fetch_california_housing();
    n_data, n_feature = housing.data.shape;

    scaler = StandardScaler();
    scaled_housing_data = scaler.fit_transform(housing.data);
    scaled_housing_data_with_bias = np.c_[np.ones((n_data, 1)), scaled_housing_data];

    reset_graph();

    n_epochs = 1000;
    learning_rate = 0.1;

    X = tf.constant(scaled_housing_data_with_bias, dtype=tf.float32, name="X");
    y = tf.constant(housing.target.reshape(-1, 1), dtype=tf.float32, name="y");
    theta = tf.Variable(tf.random_uniform([n_feature + 1, 1], -1.0, 1.0, seed=42),
                        dtype=tf.float32,
                        name="theta");
    pred = tf.matmul(X, theta, name="prediction");
    error = pred - y;
    mse = tf.reduce_mean(tf.square(error), name="mse");

    " only different !! "
    optimizer = tf.train.MomentumOptimizer(learning_rate=learning_rate,
                                           momentum=0.9);
    training_op = optimizer.minimize(mse);

    initializer = tf.global_variables_initializer();

    with tf.Session() as sess:
        initializer.run();

        for epoch in range(n_epochs):
            if epoch % 100 == 0:
                print("Epoch : {}   - MSE : {}".format(epoch, mse.eval()));

            sess.run(training_op);

        best_theta = theta.eval();

    print("Best theta : \n{}".format(best_theta));


def basic_placeholder_example():
    reset_graph();

    A = tf.placeholder(tf.int32, shape=(None, 3));
    B = A + 5;

    A1 = [[1, 2, 3]];
    A2 = [[4, 5, 6], [7, 8, 9]];

    with tf.Session() as sess:
        B1 = B.eval(feed_dict={A: A1});
        B2 = B.eval(feed_dict={A: A2});

    print("A1 : \n{}".format(A1));
    print("B1 = A1 + 5 : \n{}".format(B1));
    print("A2 : \n{}".format(A2));
    print("B2 = A2 + 5 : \n{}".format(B2));



def gradient_descent_with_mini_batch():
    from sklearn.datasets import fetch_california_housing
    from sklearn.preprocessing import StandardScaler

    housing = fetch_california_housing();
    n_data, n_feature = housing.data.shape;

    scaler = StandardScaler();
    scaled_housing_data = scaler.fit_transform(housing.data);
    scaled_housing_data_with_bias = np.c_[np.ones((n_data, 1)), scaled_housing_data];

    reset_graph();

    n_epochs = 10;
    batch_size = 100;
    n_batch = int(np.ceil(n_data / batch_size));
    learning_rate = 0.01;

    X = tf.placeholder(tf.float32, shape=(None, n_feature+1), name="X");
    y = tf.placeholder(tf.float32, shape=(None, 1), name="y");

    theta = tf.Variable(tf.random_uniform([n_feature + 1, 1], -1.0, 1.0, seed=42),
                        name="theta");
    pred = tf.matmul(X, theta, name="prediction");
    error = pred - y;
    mse = tf.reduce_mean(tf.square(error), name="mse");

    optimizer = tf.train.GradientDescentOptimizer(learning_rate=learning_rate);
    training_op = optimizer.minimize(mse);

    initializer = tf.global_variables_initializer();

    def fetch_batch(epoch, batch_idx, batch_size):
        np.random.seed(epoch*n_batch + batch_idx);
        indices = np.random.randint(n_data, size=batch_size);
        batch_x = scaled_housing_data_with_bias[indices];
        batch_y = housing.target.reshape(-1, 1)[indices];

        return batch_x, batch_y;

    with tf.Session() as sess:
        initializer.run();

        for epoch in range(n_epochs):
            for batch_idx in range(n_batch):
                batch_x, batch_y = fetch_batch(epoch, batch_idx, batch_size);
                sess.run(training_op, feed_dict={X: batch_x, y:batch_y});
            mse_error = sess.run(mse,
                                 feed_dict={X: scaled_housing_data_with_bias, y:housing.target.reshape(-1, 1)})
            print("Epoch : {}   - MSE : {}".format(epoch+1, mse_error));

        best_theta = theta.eval();

    print("Best Theta : {}".format(best_theta));



def save_model():
    from sklearn.datasets import fetch_california_housing
    from sklearn.preprocessing import StandardScaler

    housing = fetch_california_housing();
    n_data, n_feature = housing.data.shape;

    scaler = StandardScaler();
    scaled_housing_data = scaler.fit_transform(housing.data);
    scaled_housing_data_with_bias = np.c_[np.ones((n_data, 1)), scaled_housing_data];

    reset_graph();
    n_epochs = 1000;
    learning_rate = 0.1;

    X = tf.constant(scaled_housing_data_with_bias, dtype=tf.float32, name="X");
    y = tf.constant(housing.target.reshape(-1, 1), dtype=tf.float32, name="y");
    theta = tf.Variable(tf.random_uniform([n_feature + 1, 1], -1.0, 1.0, seed=42),
                        dtype=tf.float32,
                        name="theta");
    pred = tf.matmul(X, theta, name="prediction");
    error = pred - y;
    mse = tf.reduce_mean(tf.square(error), name="mse");


    optimizer = tf.train.GradientDescentOptimizer(learning_rate=learning_rate);
    training_op = optimizer.minimize(mse);

    initializer = tf.global_variables_initializer();

    " save the data "
    saver = tf.train.Saver();

    with tf.Session() as sess:
        initializer.run();

        for epoch in range(n_epochs):
            if epoch % 100 == 0:
                print("Epoch : {}   - MSE : {}".format(epoch, mse.eval()));
                save_path = saver.save(sess, "./myModel/gradient_descent_california.ckpt");

            sess.run(training_op);

        best_theta = theta.eval();
        save_path = saver.save(sess, "./myModel/gradient_descent_california.ckpt");


    print("Best theta : \n{}".format(best_theta));

    with tf.Session() as sess:
        saver.restore(sess, "./myModel/gradient_descent_california.ckpt");
        best_theta_restore = theta.eval();

    print("Best theta restore : \n{}".format(best_theta_restore));

    if np.array_equal(best_theta_restore, best_theta):
        print("Restoration is successful");
    else:
        print("Something is wrong for restoration");



def visualize_with_Tensor_board():
    from datetime import datetime
    now = datetime.utcnow().strftime("%Y%m%d%H%M%S");
    root_logdir = "./my_logs";
    logdir = "{}/run-{}/.".format(root_logdir, now);

    # Same part for mini-batch gradient descent
    from sklearn.datasets import fetch_california_housing
    from sklearn.preprocessing import StandardScaler

    housing = fetch_california_housing();
    n_data, n_feature = housing.data.shape;

    scaler = StandardScaler();
    scaled_housing_data = scaler.fit_transform(housing.data);
    scaled_housing_data_with_bias = np.c_[np.ones((n_data, 1)), scaled_housing_data];

    reset_graph();

    n_epochs = 1000;
    batch_size = 200;
    n_batch = int(np.ceil(n_data / batch_size));
    learning_rate = 0.01;

    X = tf.placeholder(tf.float32, shape=(None, n_feature + 1), name="X");
    y = tf.placeholder(tf.float32, shape=(None, 1), name="y");

    theta = tf.Variable(tf.random_uniform([n_feature + 1, 1], -1.0, 1.0, seed=42),
                        name="theta");
    pred = tf.matmul(X, theta, name="prediction");
    error = pred - y;
    mse = tf.reduce_mean(tf.square(error), name="mse");

    optimizer = tf.train.GradientDescentOptimizer(learning_rate=learning_rate);
    training_op = optimizer.minimize(mse);

    initializer = tf.global_variables_initializer();

    # different part
    mse_summary = tf.summary.scalar("MSE", mse);
    file_writer = tf.summary.FileWriter(logdir, tf.get_default_graph());

    def fetch_batch(epoch, batch_idx, batch_size):
        np.random.seed(epoch * n_batch + batch_idx);
        indices = np.random.randint(n_data, size=batch_size);
        batch_x = scaled_housing_data_with_bias[indices];
        batch_y = housing.target.reshape(-1, 1)[indices];

        return batch_x, batch_y;

    with tf.Session() as sess:
        initializer.run();

        for epoch in range(n_epochs):
            for batch_idx in range(n_batch):
                batch_x, batch_y = fetch_batch(epoch, batch_idx, batch_size);

                if batch_idx % 10 == 0:
                    summary_str = mse_summary.eval(feed_dict={X: batch_x, y: batch_y});
                    step = epoch * n_batch + batch_idx;
                    file_writer.add_summary(summary_str, step);

                sess.run(training_op, feed_dict={X: batch_x, y: batch_y});

            mse_error = sess.run(mse,
                                 feed_dict={X: scaled_housing_data_with_bias, y: housing.target.reshape(-1, 1)})

            if epoch % 50 ==0:
                print("Epoch : {}   - MSE : {}".format(epoch + 1, mse_error));

        best_theta = theta.eval();

    file_writer.close();
    print("Best Theta : {}".format(best_theta));


def relu_example1():
    reset_graph();

    def relu(X):
        with tf.name_scope("relu"):
            w_shape = (int(X.get_shape()[1]), 1);
            w = tf.Variable(tf.random_normal(w_shape), name="weights");
            b = tf.Variable(0.0, name="bias");
            z = tf.add(tf.matmul(X, w), b, name="z");
            return tf.maximum(z, 0., name="max");

    n_features = 3;
    X = tf.placeholder(tf.float32, shape=(None, n_features), name="X");
    relus = [relu(X) for i in range(5)];
    output = tf.add_n(relus, name="output");

    file_writer = tf.summary.FileWriter("./my_logs/relu2", tf.get_default_graph());
    file_writer.close();




def relu_example2():
    """ Use attributes of a function"""
    reset_graph();

    def relu(X):
        with tf.name_scope("relu"):
            if not hasattr(relu, "threshold"):
                relu.threshold = tf.Variable(0.0, name="threshold");

            w_shape = (int(X.get_shape()[1]), 1);
            w = tf.Variable(tf.random_normal(w_shape), name="weights");
            b = tf.Variable(0.0, name="bias");
            z = tf.add(tf.matmul(X, w), b, name="z");
            return tf.maximum(z, relu.threshold, name="max");

    n_features = 3;
    X = tf.placeholder(tf.float32, shape=(None, n_features), name="X");
    relus = [relu(X) for i in range(5)];
    output = tf.add_n(relus, name="output");

    reset_graph();
    with tf.variable_scope("relu"):
        threshold_init = tf.get_variable("threshold", shape=(),
                                         initializer=tf.constant_initializer(0.0));
    with tf.variable_scope("relu", reuse=True):
        threshold_reuse = tf.get_variable("threshold");



def relu_example3():
    reset_graph();

    def relu(X):
        with tf.variable_scope("relu", reuse=True):
            threshold = tf.get_variable("threshold");
            w_shape = (int(X.get_shape()[1]), 1);
            w = tf.Variable(tf.random_normal(w_shape), name="weights");
            b = tf.Variable(0.0, name="bias");
            z = tf.add(tf.matmul(X, w), b, name="z");

            return tf.maximum(z, threshold, name="max");

    n_features = 3;
    X = tf.placeholder(tf.float32, shape=(None, n_features), name="X");

    with tf.variable_scope("relu"):
        threshold = tf.get_variable("threshold", shape=(),
                                    initializer=tf.constant_initializer(0.0));

    relus = [relu(X) for i in range(5)];
    output = tf.add_n(relus, name="output");

    file_writer = tf.summary.FileWriter("./my_logs/relu3", tf.get_default_graph());
    file_writer.close();





def relu_example4():
    reset_graph();

    def relu(X):

        threshold = tf.get_variable("threshold", shape=(),
                                        initializer=tf.constant_initializer(0.0));
        w_shape = (int(X.get_shape()[1]), 1);
        w = tf.Variable(tf.random_normal(w_shape), name="weights");
        b = tf.Variable(0.0, name="bias");
        z = tf.add(tf.matmul(X, w), b, name="z");

        return tf.maximum(z, threshold, name="max");

    n_features = 3;
    X = tf.placeholder(tf.float32, shape=(None, n_features), name="X");

    relus = [];
    for i in range(5):
        with tf.variable_scope("relu", reuse=(i>=1)) as scope:
            relus.append(relu(X));

    output = tf.add_n(relus, name="output");

    file_writer = tf.summary.FileWriter("./my_logs/relu4", tf.get_default_graph());
    file_writer.close();





def exercise9_12():
    from sklearn.datasets import make_moons
    data_size = 1000;
    moons_X, moons_y = make_moons(data_size, noise=0.1, random_state=42);




    moons_X_biased = np.c_[np.ones((data_size, 1)), moons_X];
    moons_y_column = moons_y.reshape(-1, 1);

    # split train/test data
    test_ratio = 0.2;
    test_size = int(data_size*test_ratio);

    train_x = moons_X_biased[:-test_size];
    test_x = moons_X_biased[-test_size:];
    train_y = moons_y_column[:-test_size];
    test_y = moons_y_column[-test_size:];

    def random_batch(train_x, train_y, batch_size):
        rnd_indices = np.random.randint(0, len(train_x), batch_size);
        batch_x = train_x[rnd_indices];
        batch_y = train_y[rnd_indices];

        return batch_x, batch_y;

    # Train
    reset_graph();
    n_inputs = 2;   # 2-dim

    # shape of X : n_inputs + 1 == dim + bias(1)
    X = tf.placeholder(tf.float32, shape=(None, n_inputs+1), name="X");
    y = tf.placeholder(tf.float32, shape=(None, 1), name="y");

    # theta : weight which is the goal to optimize
    theta = tf.Variable(tf.random_uniform([n_inputs+1, 1], -1.0, 1.0, seed=42), name="theta");

    # logits : theta^T * X
    logits = tf.matmul(X, theta, name="logits");

    # y_proba = 1 / (1 + tf.exp(-logits));
    y_proba = tf.sigmoid(logits);

    # epsilon : constant to avoid overflow
    epsilon = 1e-7;

    # loss = -tf.reduce_mean(y * tf.log(y_proba + epsilon) + (1 - y) * tf.log(1 - y_proba + epsilon))
    # i.e -1/data_size * sum(y[i]*log(y_proba[i] + epsilon) + (1-y[i])*(1-y_proba[i] + epsilon)
    loss = tf.losses.log_loss(y, y_proba);

    learning_rate = 0.01;
    optimizer = tf.train.GradientDescentOptimizer(learning_rate=learning_rate);
    training_op = optimizer.minimize(loss);

    init = tf.global_variables_initializer();

    n_epochs = 1000;
    batch_size = 50;
    n_batches = int(np.ceil(data_size/batch_size));

    with tf.Session() as sess:
        sess.run(init);

        for epoch in range(n_epochs):
            for batch_idx in range(n_batches):
                batch_x, batch_y = random_batch(train_x, train_y, batch_size);
                sess.run(training_op, feed_dict={X: batch_x, y: batch_y});
            test_loss = loss.eval({X: test_x, y: test_y});

            if epoch % 100 == 0:
                print("{}-epoch, test_loss : {}".format(epoch, test_loss));

        test_y_proba = y_proba.eval(feed_dict={X: test_x, y: test_y});

    from sklearn.metrics import precision_score, recall_score, accuracy_score
    pred_y = (test_y_proba >= 0.5);
    test_acc = accuracy_score(pred_y, test_y);
    precision = precision_score(pred_y, test_y);
    recall = recall_score(pred_y, test_y);

    print("========================Test score ========================");
    print("Accuracy : {}".format(test_acc));
    print("Precision : {}".format(precision));
    print("Recall : {}".format(recall));
    print("============================================================");


    plt.subplot(1,2,1);
    plt.plot(moons_X[moons_y == 1, 0], moons_X[moons_y == 1, 1], 'go', label="Positive");
    plt.plot(moons_X[moons_y == 0, 0], moons_X[moons_y == 0, 1], 'r^', label="Negative");
    plt.legend();
    plt.title("Original data");

    plt.subplot(1,2,2);
    y_pred_idx = pred_y.reshape(-1);
    plt.plot(test_x[y_pred_idx, 1], test_x[y_pred_idx, 2], 'go', label="Positive");
    plt.plot(test_x[~y_pred_idx, 1], test_x[~y_pred_idx, 2], 'r^', label="Negative");
    plt.legend();
    plt.title("Prediction");

    plt.show();


""" Make a function for logistic regression"""

def logistic_regression(X, y, initializer=None, rand_state=42, learning_rate=0.01):
    n_inputs_including_bias = int(X.get_shape()[1]);

    with tf.name_scope("logistic_regression"):
        with tf.name_scope("model"):
            if initializer is None:
                initializer = tf.random_uniform([n_inputs_including_bias, 1], -1.0, 1.0, seed=rand_state);
            theta = tf.Variable(initializer, name="theta");
            logits = tf.matmul(X, theta, name="logits");
            y_proba = tf.sigmoid(logits);

        """
            oss = tf.losses.log_loss(y, y_proba);

            learning_rate = 0.01;
            optimizer = tf.train.GradientDescentOptimizer(learning_rate=learning_rate);
            training_op = optimizer.minimize(loss);

            init = tf.global_variables_initializer();
            """

        with tf.name_scope("train"):
            loss = tf.losses.log_loss(y, y_proba, scope="loss");
            optimizer = tf.train.GradientDescentOptimizer(learning_rate=learning_rate);
            training_op = optimizer.minimize(loss);
            loss_summary = tf.summary.scalar("log_loss", loss);

        with tf.name_scope("init"):
            init = tf.global_variables_initializer();

        with tf.name_scope("save"):
            saver = tf.train.Saver();

        return y_proba, loss, training_op, loss_summary, init, saver;


def exercise9_12_revised():
    from sklearn.datasets import make_moons
    data_size = 1000;
    moons_X, moons_y = make_moons(data_size, noise=0.1, random_state=42);

    moons_X_biased = np.c_[np.ones((data_size, 1)), moons_X];
    moons_y_column = moons_y.reshape(-1, 1);

    # split train/test data
    test_ratio = 0.2;
    test_size = int(data_size * test_ratio);

    train_x = moons_X_biased[:-test_size];
    test_x = moons_X_biased[-test_size:];
    train_y = moons_y_column[:-test_size];
    test_y = moons_y_column[-test_size:];


    # Add some features into data to make non-linear model
    train_x_enhanced = np.c_[train_x, np.square(train_x[:, 1]), np.square(train_x[:, 2]),
                             train_x[:,1]**3, train_x[:, 2]**3];
    test_x_enhanced = np.c_[test_x, np.square(test_x[:, 1]), np.square(test_x[:, 2]),
                            test_x[:, 1] ** 3, test_x[:, 2] ** 3];


    def random_batch(train_x, train_y, batch_size):
        rnd_indices = np.random.randint(0, len(train_x), batch_size);
        batch_x = train_x[rnd_indices];
        batch_y = train_y[rnd_indices];

        return batch_x, batch_y;


    n_inputs = 2 + 4;
    log_dir = "./my_logs/log_regression";

    X = tf.placeholder(tf.float32, shape=(None, n_inputs +1), name="X");
    y = tf.placeholder(tf.float32, shape=(None, 1), name="y");

    y_proba, loss, training_op, loss_summary, init, saver = logistic_regression(X, y);

    file_writer = tf.summary.FileWriter(log_dir, tf.get_default_graph());

    n_epochs = 10001;
    batch_size = 50;
    n_batches = int(np.ceil(data_size / batch_size));

    checkPoint_path = "./myModel/ch9_LogisticRegression/my_logreg_model.ckpt"
    #checkPoint_epoch_path = "./myModel/ch9_LogisticRegression/my_logreg_model_epoch.txt";
    checkPoint_epoch_path = checkPoint_path +".epoch";
    final_model_path = "./myModel/ch9_LogisticRegression/my_logreg_model_final";

    with tf.Session() as sess:
        if os.path.isfile(checkPoint_epoch_path):
            # 체크포인트 파일이 있으면 모델을 복원하고 에포크 횟수 로드
            with open(checkPoint_epoch_path, "rb") as file:
                start_epoch = int(file.read());
            print("The {}-training is restarted ".format(start_epoch));
            saver.restore(sess, checkPoint_path);

        else:
            start_epoch = 0;
            sess.run(init);

        for epoch in range(start_epoch, n_epochs):
            for batch_idx in range(n_batches):
                batch_x, batch_y = random_batch(train_x_enhanced, train_y, batch_size);
                sess.run(training_op, feed_dict={X: batch_x, y: batch_y});
            test_loss, summary_str = sess.run([loss, loss_summary],
                                              feed_dict={X: test_x_enhanced, y: test_y});

            file_writer.add_summary(summary_str, epoch);

            if epoch % 500 == 0:
                print("{}-epoch, test_loss : {}".format(epoch, test_loss));
                saver.save(sess, checkPoint_path);
                with open(checkPoint_epoch_path, 'wb') as file:
                    file.write(b"%d" %(epoch+1));

        saver.save(sess, final_model_path);
        test_y_proba = y_proba.eval(feed_dict={X: test_x_enhanced, y: test_y});
        os.remove(checkPoint_epoch_path);

    from sklearn.metrics import precision_score, recall_score, accuracy_score
    pred_y = (test_y_proba >= 0.5);
    test_acc = accuracy_score(pred_y, test_y);
    precision = precision_score(pred_y, test_y);
    recall = recall_score(pred_y, test_y);

    print("========================Test score ========================");
    print("Accuracy : {}".format(test_acc));
    print("Precision : {}".format(precision));
    print("Recall : {}".format(recall));
    print("============================================================");

    plt.subplot(1, 2, 1);
    plt.plot(moons_X[moons_y == 1, 0], moons_X[moons_y == 1, 1], 'go', label="Positive");
    plt.plot(moons_X[moons_y == 0, 0], moons_X[moons_y == 0, 1], 'r^', label="Negative");
    plt.legend();
    plt.title("Original data");

    plt.subplot(1, 2, 2);
    y_pred_idx = pred_y.reshape(-1);
    plt.plot(test_x[y_pred_idx, 1], test_x[y_pred_idx, 2], 'go', label="Positive");
    plt.plot(test_x[~y_pred_idx, 1], test_x[~y_pred_idx, 2], 'r^', label="Negative");
    plt.legend();
    plt.title("Prediction");

    plt.show();

def exercise9_12_restore_model():
    from sklearn.datasets import make_moons
    data_size = 1000;
    moons_X, moons_y = make_moons(data_size, noise=0.1, random_state=42);

    moons_X_biased = np.c_[np.ones((data_size, 1)), moons_X];
    moons_y_column = moons_y.reshape(-1, 1);

    # split train/test data
    test_ratio = 0.2;
    test_size = int(data_size * test_ratio);

    train_x = moons_X_biased[:-test_size];
    test_x = moons_X_biased[-test_size:];
    train_y = moons_y_column[:-test_size];
    test_y = moons_y_column[-test_size:];

    # Add some features into data to make non-linear model
    train_x_enhanced = np.c_[train_x, np.square(train_x[:, 1]), np.square(train_x[:, 2]),
                             train_x[:, 1] ** 3, train_x[:, 2] ** 3];
    test_x_enhanced = np.c_[test_x, np.square(test_x[:, 1]), np.square(test_x[:, 2]),
                            test_x[:, 1] ** 3, test_x[:, 2] ** 3];

    def random_batch(train_x, train_y, batch_size):
        rnd_indices = np.random.randint(0, len(train_x), batch_size);
        batch_x = train_x[rnd_indices];
        batch_y = train_y[rnd_indices];

        return batch_x, batch_y;

    n_inputs = 2 + 4;
    log_dir = "./my_logs/log_regression";

    X = tf.placeholder(tf.float32, shape=(None, n_inputs + 1), name="X");
    y = tf.placeholder(tf.float32, shape=(None, 1), name="y");

    y_proba, loss, training_op, loss_summary, init, saver = logistic_regression(X, y);

    file_writer = tf.summary.FileWriter(log_dir, tf.get_default_graph());

    final_model_path = "./myModel/ch9_LogisticRegression/my_logreg_model_final";

    with tf.Session() as sess:
        saver.restore(sess, final_model_path);
        y_proba_restored = y_proba.eval(feed_dict={X: test_x_enhanced, y: test_y});

    from sklearn.metrics import precision_score, recall_score, accuracy_score
    pred_y = (y_proba_restored >= 0.5);
    test_acc = accuracy_score(pred_y, test_y);
    precision = precision_score(pred_y, test_y);
    recall = recall_score(pred_y, test_y);

    print("========================Test score ========================");
    print("Accuracy : {}".format(test_acc));
    print("Precision : {}".format(precision));
    print("Recall : {}".format(recall));
    print("============================================================");



if __name__ == "__main__":
    print("Chapter 9 : Start TensorFlow");
    #first_computation_graph();
    #second_computation_graph();
    #normal_equation_tf();
    #gradient_descent_in_handle();
    #gradient_descent_with_auto_diff();
    #gradient_descent_with_tf_optimizer();
    #gradient_descent_with_moment_optimizer();
    #basic_placeholder_example();
    #test()
    #gradient_descent_with_mini_batch();
    #save_model();
    #visualize_with_Tensor_board();
    #relu_example1();
    #relu_example4();
    #exercise9_12_revised();
    exercise9_12_restore_model();