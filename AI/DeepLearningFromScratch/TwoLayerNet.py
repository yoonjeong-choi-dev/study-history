# Library
from collections import OrderedDict

# User-defined modules
from Layers import *
from Gradient import numerical_gradient


class TwoLayerNet:
    """
    ----------------------------------------------------------------------
    Input layer     ->  Hidden layer : Affine + ReLU layers
    Hidden layer    ->  Output layer : Affine + Softmax layers
    ----------------------------------------------------------------------
    Instance variables :
    1. params
        - dictionary variables for parameters of the model
        - params['W1'], params['b1'] : weight and bias in the 1st layer
        - params['W2'], params['b2'] : weight and bias in the 2st layer

    2. layers
        - ordered dictionary variables for layers
        - e.g layers['Affine1'], layers['Relu1'] etc

    3. lastLayer
        - the final layer i.e output layer
        - Here, we use SoftmaxWithLoss layer
    ----------------------------------------------------------------------
    Methods :
    1. __init__(self, input_size, hidden_size, output_size, weight_init_std=0.01)

    2. predict(self, x)
        - predict the value at x

    3. loss(self, x, t)
        - error between the predict value at x and real label of x

    4. accuracy(self, x, t)
        - accuracy for a set of data x with real label t

    5. numerical_gradient(self, x, t)
        - Calculate gradients of parameters by numerical_gradient
        - this method is too slow to train the model
        - this method is used to check whether the back-propagation is valid

    6. gradient(self, x, t)
        - Calculate gradients of parameters by Back-propagation
        - this method is much faster than numerical_gradient
    ----------------------------------------------------------------------
    """

    def __init__(self, input_size, hidden_size, output_size, activation="Relu", weight_init_std=0.01):
        """
        :param input_size: the size of a data i.e the number of features in data
        :param hidden_size:
        :param output_size: the number of labels
        :param activation: (Relu, Sigmoid) activation function used in the hidden layer
        :param weight_init_std: the derivation for weight distribution
        """
        # Initialize the parameters

        self.params = dict();
        self.params['W1'] = weight_init_std * np.random.randn(input_size, hidden_size);
        self.params['b1'] = np.zeros(hidden_size);
        self.params['W2'] = weight_init_std * np.random.randn(hidden_size, output_size);
        self.params['b2'] = np.zeros(output_size);

        # Make hidden layers with ReLU
        self.layers = OrderedDict();
        self.layers['Affine1'] = Affine(self.params['W1'], self.params['b1']);

        if activation == "Relu":
            self.layers['Relu1'] = ReLU();
        elif activation == "Sigmoid":
            self.layers['Sigmoid'] = Sigmoid();
        else:
            print("Activation input is not valid");
            exit(-1);

        self.layers['Affine2'] = Affine(self.params['W2'], self.params['b2']);

        # Make the output layer with SoftmaxWithLoss
        self.lastLayer = SoftmaxWithLoss();


    def showNetwork(self):
        print("====================Network=====================")
        for key in self.layers.keys():
            print(key);
        print("================================================")
        for key in self.params.keys():
            print(key);
        print("================================================")

    def predict(self, x):
        """
        :param x: test data
        :return: prediction of test data
        """
        for layer in self.layers.values():
            x = layer.forward(x);

        return x;

    def loss(self, x, t):
        y = self.predict(x);
        return self.lastLayer.forward(y, t);

    def accuracy(self, x, t):
        y = self.predict(x);
        y = np.argmax(y, axis=1);       # y[i] = np.argmax(y[i]) for training a mini batch

        # if t is a matrix where t[i] is the label of x[i] for training a mini batch
        if t.ndim != 1:
            t = np.argmax(t, axis=1)    # t[i] = np.argmax(t[i]) for training a mini batch

        acc = np.sum(y==t) / float(x.shape[0]);     # x.shape[0] = number of batch
        return acc;

    # Too slow
    def numerical_gradient(self, x, t):
        # Since 'numerical_gradient' has a function f as an input,
        # we set a dummy function which is actually the loss function
        loss_W = lambda W: self.loss(x, t);

        grads = dict();
        grads['W1'] = numerical_gradient(loss_W, self.params['W1'])
        grads['b1'] = numerical_gradient(loss_W, self.params['b1'])
        grads['W2'] = numerical_gradient(loss_W, self.params['W2'])
        grads['b2'] = numerical_gradient(loss_W, self.params['b2'])

        return grads;

    def gradient(self, x, t):
        # Forward-propagation
        self.loss(x, t);

        # Backward-propagation in the output layer(softmax)
        dout = 1;
        dout = self.lastLayer.backward(dout);

        # Backward-propagation in the other layer(affine+ReLU)
        layers = list(self.layers.values());
        layers.reverse()        # layer is defined for forward, so we need to reverse the layer
        for layer in layers:
            dout = layer.backward(dout);

        # update the parameters
        grads = dict();
        grads['W1'] = self.layers['Affine1'].dW;
        grads['b1'] = self.layers['Affine1'].db;
        grads['W2'] = self.layers['Affine2'].dW;
        grads['b2'] = self.layers['Affine2'].db;

        return grads;


def TwoLayerNet_gradient_check():
    from dataset.mnist import load_mnist
    (x_train, t_train), (x_test, t_test) = load_mnist(normalize=True, one_hot_label=True);

    network = TwoLayerNet(input_size=784, hidden_size=50, output_size=10);

    x_batch = x_train[:3];
    t_batch = t_train[:3];

    grad_numerical = network.numerical_gradient(x_batch, t_batch);
    grad_backprop = network.gradient(x_batch, t_batch);

    for key in grad_numerical.keys():
        diff = np.average(np.abs(grad_backprop[key] - grad_numerical[key]));
        print(key + " : {}".format(diff));

def TwoLayerNet_MNIST(hidden=50):
    from dataset.mnist import load_mnist
    (x_train, t_train), (x_test, t_test) = load_mnist(normalize=True, one_hot_label=True);

    network = TwoLayerNet(input_size=784, hidden_size=hidden, output_size=10);

    # hyper-parameter
    iters_num = 10000;
    train_size = x_train.shape[0];
    batch_size = 100;
    learning_rate = 0.1

    # data memory during training
    train_loss_list = [];
    train_acc_list = [];
    test_acc_list = [];

    # epoch
    iter_per_epoch = max(train_size / batch_size, 1)

    for i in range(iters_num):
        batch_mask = np.random.choice(train_size, batch_size);
        x_batch = x_train[batch_mask];
        t_batch = t_train[batch_mask];

        # grad = network.numerical_gradient(x_batch, t_batch);
        grad = network.gradient(x_batch, t_batch)

        # update parameters
        for key in ('W1', 'b1', 'W2', 'b2'):
            network.params[key] -= learning_rate * grad[key];

        # record the train procedure
        loss = network.loss(x_batch, t_batch);
        train_loss_list.append(loss);


        if i % iter_per_epoch == 0:
            train_acc = network.accuracy(x_train, t_train)
            test_acc = network.accuracy(x_test, t_test)
            train_acc_list.append(train_acc)
            test_acc_list.append(test_acc)
            print("\n===========Iter_per_epoch===================")
            print("Iteration : {}".format(i));
            print("train accuracy : {}".format(train_acc));
            print("test accuracy : {}".format(test_acc));
            print("============================================\n");

    # Final Report
    train_acc = network.accuracy(x_train, t_train)
    test_acc = network.accuracy(x_test, t_test)
    print("\n===========Final Result===================");
    print("The number of neurons in the hidden layer : {}".format(hidden))
    print("train accuracy : {}".format(train_acc));
    print("test accuracy : {}".format(test_acc));
    print("============================================\n");

    # plot the graph
    import matplotlib.pyplot as plt
    f, (ax1, ax2) = plt.subplots(1, 2, figsize=(10, 20));

    x = np.arange(len(train_acc_list));
    ax1.plot(x, train_acc_list, label='train acc')
    ax1.plot(x, test_acc_list, label='test acc', linestyle='--')
    ax1.set_xlabel("epochs");
    ax1.set_ylabel("accuracy");
    ax1.set_ylim(0, 1.0);
    ax1.legend(loc='lower right');
    ax1.set_title("Accuracy");

    num_itr = np.arange(len(train_loss_list));
    ax2.plot(num_itr, train_loss_list);
    ax2.set_xlabel("iteration");
    ax2.set_ylabel("loss");
    ax2.set_ylim(0, 3.0);
    ax2.set_title("Loss per iteration");

    plt.show()




if __name__ == '__main__':
    TwoLayerNet_MNIST();

