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
CHAPTER_ID = "artificial_neural_network";

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


def perceptron_iris():
    from sklearn.datasets import load_iris
    from sklearn.linear_model import Perceptron

    iris = load_iris();
    X = iris.data[:, (2, 3)];
    y = (iris.target == 0).astype(np.int);

    per_clf = Perceptron(random_state=42);
    per_clf.fit(X, y);

    w = -per_clf.coef_[0][0] / per_clf.coef_[0][1];
    b = -per_clf.intercept_ / per_clf.coef_[0][1];

    axes = [0, 5, 0, 2];

    mesh_x, mesh_y = np.meshgrid(
        np.linspace(axes[0], axes[1], 500).reshape(-1, 1),
        np.linspace(axes[1], axes[2], 500).reshape(-1, 1)
    );

    test_x = np.c_[mesh_x.ravel(), mesh_y.ravel()];
    test_pred = per_clf.predict(test_x);
    test_pred = test_pred.reshape(mesh_x.shape);

    plt.figure(figsize=(10, 4));

    plt.plot(X[y==0, 0], X[y==0, 1], "bs", label="Not Iris-Setosa");
    plt.plot(X[y==1, 0], X[y==1, 1], "yo", label="Iris-Setosa");

    plt.plot([axes[0], axes[1]], [w*axes[0] + b, w*axes[1] + b], "k-", linewidth=3);

    from matplotlib.colors import ListedColormap
    custom_cmap = ListedColormap(['#9898ff', '#fafab0'])

    plt.contourf(mesh_x, mesh_y, test_pred, cmap=custom_cmap);
    plt.xlabel("Sepal length", fontsize=14)
    plt.ylabel("Sepal width", fontsize=14);
    plt.legend(loc="lower right", fontsize=14);
    plt.axis(axes);

    save_fig("Perceptron_Iris");
    plt.show();





def activation_examples():
    def logit(z):
        return 1 / (1 + np.exp(-z));

    def relu(z):
        return np.maximum(0, z);

    def numerical_derivative(f, z, eps=0.000001):
        return (f(z + eps) - f(z - eps)) /(2*eps);

    def heaviside(z):
        return (z >= 0).astype(z.dtype);

    def sigmoid(z):
        return logit(z);

    def mlp_xor(x1, x2, activation=heaviside):
        return activation(-activation(x1 + x2 - 1.5) + activation(x1 + x2 -0.5) -0.5);


    z = np.linspace(-5, 5, 200);

    plt.figure(figsize=(11, 8));

    plt.subplot(2, 2, 1);
    plt.plot(z, np.sign(z), "r--", linewidth=2, label="Step");
    plt.plot(z, logit(z), "g--", linewidth=2, label="Logistic");
    plt.plot(z, np.tanh(z), "b-", linewidth=2, label="Tanh");
    plt.plot(z, relu(z), "m-.", linewidth=2, label="ReLU");

    plt.grid(True);
    plt.legend(loc="center right", fontsize=14);
    plt.title("Activation Function", fontsize=14);
    plt.axis([-5, 5, -1.2, 1.2]);

    plt.subplot(2, 2, 2);
    plt.plot(0, 0, "ro", markersize=5);
    plt.plot(0, 0, "rx", markersize=10);

    plt.plot(z, numerical_derivative(np.sign, z), "r-", linewidth=2, label="Step");
    plt.plot(z, numerical_derivative(logit, z), "g--", linewidth=2, label="Logistic");
    plt.plot(z, numerical_derivative(np.tanh, z), "b-", linewidth=2, label="Tanh");
    plt.plot(z, numerical_derivative(relu, z), "m-.", linewidth=2, label="ReLU");

    plt.grid(True);
    plt.legend(loc="center right", fontsize=14);
    plt.title("Derivatives", fontsize=14);
    plt.axis([-5, 5, -0.2, 1.2]);

    axes = [-0.2, 1.2, -0.2, 1.2];

    mesh_x, mesh_y = np.meshgrid(
        np.linspace(axes[0], axes[1], 500),
        np.linspace(axes[1], axes[2], 500)
    );

    xor_heaviside = mlp_xor(mesh_x, mesh_y, heaviside);
    xor_sigmoid = mlp_xor(mesh_x, mesh_y, sigmoid);

    plt.subplot(2, 2, 3);
    plt.contourf(mesh_x, mesh_y, xor_heaviside);
    plt.plot([0, 1], [0, 1], "gs", markersize=20);
    plt.plot([0, 1], [1, 0], "y^", markersize=20);
    plt.title("Activation : Heaviside", fontsize=14);
    plt.grid(True);

    plt.subplot(2, 2, 4);
    plt.contourf(mesh_x, mesh_y, xor_sigmoid);
    plt.plot([0, 1], [0, 1], "gs", markersize=20);
    plt.plot([0, 1], [1, 0], "y^", markersize=20);
    plt.title("Activation : Heaviside", fontsize=14);
    plt.grid(True);

    save_fig("activation_functions_examples")
    plt.show();






def tf_estimator_MNIST():
    (train_x, train_y), (test_x, test_y) = tf.keras.datasets.mnist.load_data()


    train_x = train_x.astype(np.float32).reshape(-1, 28*28) / 255.0;
    train_y = train_y.astype(np.int32);

    valid_x, train_x = train_x[:5000], train_x[5000:];
    valid_y, train_y = train_y[:5000], train_y[5000:];


    test_x = test_x.astype(np.float32).reshape(-1, 28*28) / 255.0;
    test_y = test_y.astype(np.int32);

    feature_cols = [tf.feature_column.numeric_column("X", shape=[28*28])];
    dnn_clf = tf.estimator.DNNClassifier(hidden_units=[300, 100], n_classes=10,
                                         feature_columns=feature_cols);
    input_fn = tf.estimator.inputs.numpy_input_fn(
        x={"X": train_x}, y=train_y, num_epochs=40, batch_size=50, shuffle=True
    );
    dnn_clf.train(input_fn=input_fn);

    input_fn_test =tf.estimator.inputs.numpy_input_fn(
        x={"X":test_x}, y=test_y, shuffle=False
    );
    eval_results = dnn_clf.evaluate(input_fn_test);
    print("Evaluation Result : \n{}".format(eval_results));


def tf_contrib_MNSIT():
    (train_x, train_y), (test_x, test_y) = tf.keras.datasets.mnist.load_data()

    train_x = train_x.astype(np.float32).reshape(-1, 28 * 28) / 255.0;
    train_y = train_y.astype(np.int32);

    valid_x, train_x = train_x[:5000], train_x[5000:];
    valid_y, train_y = train_y[:5000], train_y[5000:];

    test_x = test_x.astype(np.float32).reshape(-1, 28 * 28) / 255.0;
    test_y = test_y.astype(np.int32);

    config = tf.contrib.learn.RunConfig(tf_random_seed=42);
    feature_cols = tf.contrib.learn.infer_real_valued_columns_from_input(train_x);


    dnn_clf = tf.contrib.learn.DNNClassifier(hidden_units=[300, 100], n_classes=10,
                                             feature_columns=feature_cols,
                                             config=config);
    dnn_clf = tf.contrib.learn.SKCompat(dnn_clf);

    tf.logging.set_verbosity(tf.logging.INFO);
    dnn_clf.fit(train_x, train_y, batch_size=50, steps=40000);

    from sklearn.metrics import accuracy_score, log_loss
    pred_y = dnn_clf.predict(test_x);
    acc_test = accuracy_score(pred_y['classes'], test_y);
    print("Test Accuracy : {}".format(acc_test));






def my_dnn_mnist():
    (train_x, train_y), (test_x, test_y) = tf.keras.datasets.mnist.load_data()

    train_x = train_x.astype(np.float32).reshape(-1, 28 * 28) / 255.0;
    train_y = train_y.astype(np.int32);

    valid_x, train_x = train_x[:5000], train_x[5000:];
    valid_y, train_y = train_y[:5000], train_y[5000:];

    test_x = test_x.astype(np.float32).reshape(-1, 28 * 28) / 255.0;
    test_y = test_y.astype(np.int32);

    n_inputs = train_x.shape[1];
    n_hidden1, n_hidden2 = 300, 100;
    n_outputs = 10;

    reset_graph();

    X = tf.placeholder(tf.float32, shape=(None, n_inputs), name="X");
    y = tf.placeholder(tf.int32, shape=(None), name="y");

    def neuron_layer(X, n_neurons, name, activation=None):
        with tf.name_scope(name):
            n_inputs = int(X.get_shape()[1]);
            stddev = 2 / np.sqrt(n_inputs);

            init = tf.truncated_normal((n_inputs, n_neurons), stddev=stddev);

            W = tf.Variable(init, name="kernel");
            b = tf.Variable(tf.zeros([n_neurons]), name="bias");
            Z = tf.matmul(X, W) + b;

            if activation is not None:
                return activation(Z);
            else:
                return Z;

    # Make a DNN
    with tf.name_scope("dnn"):
        hidden1 = neuron_layer(X, n_hidden1, name="hidden1",
                               activation=tf.nn.relu);
        hidden2 = neuron_layer(hidden1, n_hidden2, name="hidden2",
                               activation=tf.nn.relu);
        logits = neuron_layer(hidden2, n_outputs, name="outputs");

    # with tf.name_scope("dnn"):
    #     hidden1 = tf.layers.dense(X, n_hidden1, name="hidden1",
    #                               activation=tf.nn.relu);
    #     hidden2 = tf.layers.dense(hidden1, n_hidden2, name="hidden2",
    #                               activation=tf.nn.relu);
    #     logits = tf.layers.dense(hidden2, n_outputs, name="outputs");

    with tf.name_scope("loss"):
        entropy = tf.nn.sparse_softmax_cross_entropy_with_logits(labels=y,
                                                                 logits=logits);
        loss = tf.reduce_mean(entropy, name="loss");

    learning_rate = 0.01;

    with tf.name_scope("train"):
        optimizer = tf.train.GradientDescentOptimizer(learning_rate=learning_rate);
        training_op = optimizer.minimize(loss);

    with tf.name_scope("eval"):
        correct = tf.nn.in_top_k(logits, y, 1);
        accuracy = tf.reduce_mean(tf.cast(correct, tf.float32));

    init = tf.global_variables_initializer();
    saver = tf.train.Saver();

    n_epochs = 40;
    batch_size = 50;

    def shuffle_batch(X, y, batch_size):
        random_idx = np.random.permutation(len(X));
        n_batches = len(X) // batch_size;
        for batch_idx in np.array_split(random_idx, n_batches):
            batch_x, batch_y = X[batch_idx], y[batch_idx];
            yield batch_x, batch_y;

    log_dir = "./my_logs/my_dnn_mnist";
    file_writer = tf.summary.FileWriter(log_dir, tf.get_default_graph());

    with tf.Session() as sess:
        init.run();

        for epoch in range(n_epochs):
            for batch_x, batch_y in shuffle_batch(train_x, train_y, batch_size):
                sess.run(training_op, feed_dict={X: batch_x, y: batch_y});

            acc_batch = accuracy.eval(feed_dict={X: batch_x, y: batch_y});
            acc_valid = accuracy.eval(feed_dict={X: valid_x, y: valid_y});
            print("{}-epoch - batch acc : {}, valid acc : {}".format(epoch, acc_batch, acc_valid));

        save_path = saver.save(sess, "./myModel/my_dnn_mnist_model.ckpt");

        acc_test = accuracy.eval(feed_dict={X: test_x, y: test_y});
        print("test acc :{}".format(acc_test));

    file_writer.close();




def exercise_10_9_dnn():
    (train_x, train_y), (test_x, test_y) = tf.keras.datasets.mnist.load_data()

    train_x = train_x.astype(np.float32).reshape(-1, 28 * 28) / 255.0;
    train_y = train_y.astype(np.int32);

    valid_x, train_x = train_x[:5000], train_x[5000:];
    valid_y, train_y = train_y[:5000], train_y[5000:];

    test_x = test_x.astype(np.float32).reshape(-1, 28 * 28) / 255.0;
    test_y = test_y.astype(np.int32);

    n_data = train_x.shape[0];
    n_inputs = train_x.shape[1];
    n_hidden1, n_hidden2 = 300, 100;
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
        loss_summary = tf.summary.scalar("log_loss", loss);

    learning_rate = 0.01;

    with tf.name_scope("train"):
        optimizer = tf.train.GradientDescentOptimizer(learning_rate=learning_rate);
        training_op = optimizer.minimize(loss);

    with tf.name_scope("eval"):
        correct = tf.nn.in_top_k(logits, y, 1);
        accuracy = tf.reduce_mean(tf.cast(correct, tf.float32));
        accuracy_summary = tf.summary.scalar("accuracy", accuracy);

    init = tf.global_variables_initializer();
    saver = tf.train.Saver();

    n_epochs = 10001;
    batch_size = 50;
    n_batches = int(np.ceil(n_data/batch_size));

    checkPoint_path = "./myModel/ch10_ANN/exercise_my_dnn_model.ckpt"
    checkPoint_epoch_path = checkPoint_path + ".epoch";
    final_model_path = "./myModel/ch10_ANN/exercise_my_dnn_model_final";

    # for early stopping
    best_loss = np.infty;
    epochs_without_progress = 0;
    max_epochs_without_progress = 50;

    def shuffle_batch(X, y, batch_size):
        random_idx = np.random.permutation(len(X));
        n_batches = len(X) // batch_size;
        for batch_idx in np.array_split(random_idx, n_batches):
            batch_x, batch_y = X[batch_idx], y[batch_idx];
            yield batch_x, batch_y;

    log_dir = "./my_logs/exercise_my_dnn_mnist";
    file_writer = tf.summary.FileWriter(log_dir, tf.get_default_graph());

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
            for batch_x, batch_y in shuffle_batch(train_x, train_y, batch_size):
                sess.run(training_op, feed_dict={X: batch_x, y: batch_y});

            acc_valid, loss_val, accuracy_summary_str, loss_summary_str = sess.run([accuracy, loss,
                                                                                    accuracy_summary, loss_summary],
                                                                                    feed_dict={X: valid_x, y: valid_y});
            file_writer.add_summary(accuracy_summary_str, epoch);
            file_writer.add_summary(loss_summary_str);

            if epoch % 5 == 0:
                print("{}-epoch - valid acc : {:.3f}%, valid loss : {:.5f}".format(epoch, acc_valid*100, loss_val));
                saver.save(sess, checkPoint_path);

                with open(checkPoint_epoch_path, 'wb') as file:
                    file.write(b"%d" %(epoch+1));

                if loss_val < best_loss:
                    saver.save(sess, final_model_path);
                    best_loss = loss_val;
                else:
                    epochs_without_progress += 5;
                    if epochs_without_progress > max_epochs_without_progress:
                        print("Early Stopping");
                        break;




    with tf.Session() as sess:
        saver.restore(sess, final_model_path);
        acc_test = accuracy.eval(feed_dict={X: test_x, y: test_y});
        print("test acc :{}".format(acc_test));

















if __name__ == "__main__":
    print("Chapter 10 : ANN");
    #perceptron_iris();
    #activation_examples();
    #tf_estimator_MNIST();
    #tf_contrib_MNSIT();
    #my_dnn_mnist();
    exercise_10_9_dnn();

