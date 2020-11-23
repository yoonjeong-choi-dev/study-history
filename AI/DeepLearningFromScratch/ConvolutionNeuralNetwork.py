import numpy as np
import matplotlib.pyplot as plt
import pickle

from collections import OrderedDict
from Layers import *
from Gradient import numerical_gradient


class SimpleConvNet:
    """ A simple convolution network
     ----------------------------------------------------------------------
    Input layer -> Convolution -> ReLU -> MaxPool
    -> Affine -> ReLU -> Affine -> Softmax
    -----------------------------------------------------------------------
    Parameters :
    1.  input_dim : the shape of data (e.g in MNIST, (1, 28, 28))

    2. conv_params : hyper-parameters for convolution layer
        - filter_num : the number of filters
        - filter_size : the size of each filters
        - stride : stride
        - padding : padding

    3. hidden_size : the number of neurons in the hidden layer(fully connected)

    4. output_size : the size of output (fully connected)

    5. weight_init_std : variance of initial weight parameter
    -----------------------------------------------------------------------
    Instance variables :
    1. params
        - dictionary variables for parameters of the model
        - params['W_i'], params['b_i'] : weight and bias in the i-th layer including paramters to train
        - 1st layer : Convolution layer
        - 2nd layer : Affine layer1 for the hidden layer
        - 3rd layer : Affine layer2 for connecting the output layer

    2. layers
        - ordered dictionary variables for layers
        - e.g layers['Affine1'], layers['Relu1'] etc

    3. lastLayer
        - the final layer i.e output layer
        - Here, we use SoftmaxWithLoss layer
    ----------------------------------------------------------------------
    """

    def __init__(self, input_dim=(1, 28, 28),
                 conv_params={'filter_num': 30, 'filter_size': 5, 'padding': 0, 'stride': 1},
                 hidden_size=100, output_size=10, weight_init_std=0.01):
        # Constructor parameters
        self.input_dim = input_dim;
        self.conv_params = conv_params;
        self.hidden_size = hidden_size;
        self.output_size = output_size;

        # Convolution Parameters

        self.filter_num = conv_params['filter_num'];
        self.filter_size = conv_params['filter_size'];
        self.filter_padding = conv_params['padding'];
        self.filter_stride = conv_params['stride'];

        self.input_size = input_dim[1];
        self.conv_output_size =(self.input_size - self.filter_size + 2*self.filter_padding) / self.filter_stride + 1;
        self.pool_output_size = int(self.filter_num * (self.conv_output_size/2) * (self.conv_output_size/2));



        # Initialize parameters
        self.params = dict();

        # Convolution parameters
        self.params['W1'] = weight_init_std * \
                            np.random.randn(self.filter_num, input_dim[0], self.filter_size, self.filter_size);
        self.params['b1'] = np.zeros(self.filter_num);

        # 1st Affine parameters for the hidden layer
        self.params['W2'] = weight_init_std * \
                            np.random.randn(self.pool_output_size, hidden_size);
        self.params['b2'] = np.zeros(hidden_size);

        # 2nd Affine parameters for the output layer
        self.params['W3'] = weight_init_std * \
                            np.random.randn(hidden_size, output_size);
        self.params['b3'] = np.zeros(output_size);

        # Make layers
        self.layers = OrderedDict();
        self.layers['Conv1'] = Convolution(self.params['W1'], self.params['b1'],
                                           conv_params['stride'], conv_params['padding']);
        self.layers['Relu1'] = ReLU();
        self.layers['Pool1'] = MaxPooling(pool_height=2, pool_width=2, stride=2);
        self.layers['Affine1'] = Affine(self.params['W2'], self.params['b2']);
        self.layers['Relu2'] = ReLU();
        self.layers['Affine2'] = Affine(self.params['W3'], self.params['b3']);

        self.lastLayer = SoftmaxWithLoss();

    def showNetwork(self):
        print("==========================Network=====================================");
        print("1st layer : Convolution layer\n2nd layer : Affine layer1 for the hidden layer \
                            \n3rd layer : Affine layer2 for connecting the output layer")
        print("======================================================================")
        print("1. Layer ");
        for key in self.layers.keys():
            print(key);
        print("======================================================================")
        print("2. Parameters shape")
        for key in self.params.keys():
            print("Parameter : {}".format(key));
            print(self.params[key].shape);
        print("======================================================================")
        print("=======================Convolution Information========================");
        print("filter_num : {}".format(self.filter_num));
        print("filter_size : {}".format(self.filter_size));
        print("filter_stride : {}".format(self.filter_stride));
        print("filter_padding : {}".format(self.filter_padding));
        print("input_size : {}".format(self.input_size));
        print("conv_output_size : {}".format(self.conv_output_size));
        print("pool_output_size : {}".format(self.pool_output_size));
        print("======================================================================")

    def predict(self, x):
        for layer in self.layers.values():
            x = layer.forward(x);

        return x;

    def loss(self, x, t):
        y = self.predict(x);

        return self.lastLayer.forward(y, t);

    def accuracy(self, x, t, batch_size=100):
        # if t is a matrix where t[i] is the label of x[i] for training a mini batch
        if t.ndim != 1:
            t = np.argmax(t, axis=1)  # t[i] = np.argmax(t[i]) for training a mini batch

        acc = 0.0;

        for i in range(int(x.shape[0] / batch_size)):
            batch_x = x[i * batch_size: (i + 1) * batch_size];
            batch_t = t[i * batch_size: (i + 1) * batch_size];
            y = self.predict(batch_x);
            y = np.argmax(y, axis=1);  # y[i] = np.argmax(y[i]) for training a mini batch
            acc += np.sum(y == batch_t);

        acc = acc / x.shape[0];  # x.shape[0] = number of batch
        return acc;

    def numerical_gradient(self, x, t):
        loss_w = lambda w: self.loss(x, t);

        grads = dict();
        for idx in (1, 2, 3):
            grads['W' + str(idx)] = numerical_gradient(loss_w, self.params['W' + str(idx)]);
            grads['b' + str(idx)] = numerical_gradient(loss_w, self.params['b' + str(idx)]);

        return grads;

    def gradient(self, x, t):
        # Forward-propagation
        self.loss(x, t);

        # Backward-propagation in the output layer(softmax)
        dout = 1;
        dout = self.lastLayer.backward(dout);

        # Backward-propagation in the other layer
        layers = list(self.layers.values());

        # layer is defined for forward, so we need to reverse the layer
        layers.reverse()
        for layer in layers:
            dout = layer.backward(dout);

        # update the parameters
        grads = dict();
        grads['W1'], grads['b1'] = self.layers['Conv1'].dW, self.layers['Conv1'].db;
        grads['W2'], grads['b2'] = self.layers['Affine1'].dW, self.layers['Affine1'].db;
        grads['W3'], grads['b3'] = self.layers['Affine2'].dW, self.layers['Affine2'].db;

        return grads;

    def save_params(self, file_name="simple_CNN_params.pkl"):

        # Save the constructor input
        constructor = dict();
        constructor['input_dim'] = self.input_dim;
        constructor['conv_params'] = self.conv_params;
        constructor['hidden_size'] = self.hidden_size;
        constructor['output_size'] = self.output_size;

        params = dict();
        for key, val in self.params.items():
            params[key] = val;



        # save trained parameters as *.pkl
        with open(file_name, 'wb') as f:
            pickle.dump(constructor, f);
            pickle.dump(params, f);


    def load_params(self, file_name="simple_CNN_params.pkl"):
        # load trained parameters
        with open(file_name, 'rb') as f:
            constructor = pickle.load(f);
            params = pickle.load(f);

        self.__init__(input_dim=constructor['input_dim'], conv_params=constructor['conv_params'],
                      hidden_size=constructor['hidden_size'], output_size=constructor['output_size'])

        for key, val in params.items():
            self.params[key] = val;

        for i, key in enumerate(['Conv1', 'Affine1', 'Affine2']):
            self.layers[key].W = self.params['W' + str(i + 1)];
            self.layers[key].b = self.params['b' + str(i + 1)];










""" Visualize a filter in Convolution Neural Network """
def filter_show(filters, nx=4, show_num=16):
    """ https://gist.github.com/aidiary/07d530d5e08011832b12#file-draw_weight-py
    Visualize a filter in Convolution Neural Network
    """

    FN, C, FH, FW = filters.shape;
    nv = int(np.ceil(show_num / nx));

    fig = plt.figure();
    fig.subplots_adjust(left=0, right=1, bottom=0, top=1, hspace=0.05, wspace=0.05);

    for i in range(show_num):
        ax = fig.add_subplot(4, 4, i+1, xticks=[], yticks=[]);
        ax.imshow(filters[i, 0], cmap=plt.cm.gray_r, interpolation='nearest');








"""Example usage of simple CNN"""
def SimpleConvNet_gradient_check():
    from dataset.mnist import load_mnist
    (x_train, t_train), (x_test, t_test) = load_mnist(flatten=False);

    network = SimpleConvNet(input_dim=(1, 28, 28),
                            conv_params={'filter_num': 30, 'filter_size': 5, 'padding': 0, 'stride': 1},
                            hidden_size=100, output_size=10, weight_init_std=0.01);




    x_batch = x_train[:3];
    t_batch = t_train[:3];

    grad_numerical = network.numerical_gradient(x_batch, t_batch);
    grad_backprop = network.gradient(x_batch, t_batch);

    for key in grad_backprop.keys():
        diff = np.average(np.abs(grad_backprop[key] - grad_numerical[key]));
        print(key + " : {}".format(diff));

def SimpleConvNet_MNIST_example():
    from Trainer import Trainer
    from dataset.mnist import load_mnist

    (x_train, t_train), (x_test, t_test) = load_mnist(flatten=False);

    max_epochs = 20;

    network = SimpleConvNet(input_dim=(1, 28, 28),
                            conv_params={'filter_num': 30, 'filter_size': 5, 'padding': 0, 'stride': 1},
                            hidden_size=100, output_size=10, weight_init_std=0.01);

    trainer = Trainer(network, x_train, t_train, x_test, t_test, epochs=max_epochs,
                      mini_batch_size=100, optimizer='Adam', optimizer_param={'lr':0.001},
                      evaluate_sample_num_per_epoch=1000);

    #network.showNetwork();

    print("======================================================================")
    print("Max Iteration : {}".format(trainer.max_iter));
    print("======================================================================")

    trainer.train();

    # Save the trained parameters
    # network.save_params("Adam_MNIST_parameter_0001.pkl");
    # print("Saved network parameters!!!");


    # Plot
    # markers = {'train':'o', 'test':'s'};
    # x = np.arange(max_epochs);
    # plt.plot(x, trainer.train_acc_list, markers='o', label='train', markevery=2);
    # plt.plot(x, trainer.test_acc_list, markers='s', label='test', markevery=2);
    # plt.xlabel("epochs");
    # plt.ylabel("accuracy");
    # plt.ylim(0, 1.0);
    # plt.legend(loc='lower right');
    # plt.show();

def SimpleConvNet_MNIST_example_load():
    from dataset.mnist import load_mnist

    (x_train, t_train), (x_test, t_test) = load_mnist(flatten=False);

    network = SimpleConvNet(input_dim=(1, 28, 28),
                            conv_params={'filter_num': 30, 'filter_size': 5, 'padding': 0, 'stride': 1},
                            hidden_size=100, output_size=10, weight_init_std=0.01);

    print("Load the network parameters......................");
    network.load_params("Adam_MNIST_parameter_0001.pkl");
    print("Loaded the network parameters!!!\n")
    print("Train accuracy : {}".format(network.accuracy(x_train, t_train)));
    print("Test accuracy : {}".format(network.accuracy(x_test, t_test)));

def SimpleConvNet_MNIST_visualize():
    from matplotlib.image import imread
    network = SimpleConvNet(input_dim=(1, 28, 28),
                            conv_params={'filter_num': 30, 'filter_size': 5, 'padding': 0, 'stride': 1},
                            hidden_size=100, output_size=10, weight_init_std=0.01);

    print("Load the network parameters......................")
    network.load_params("Adam_MNIST_parameter_0001.pkl");
    print("Loaded the network parameters!!!\n")

    filter_show(network.params['W1'], 16);
    img = imread('dataset/lena_gray.png');
    img = img.reshape(1, 1, *img.shape);

    fig = plt.figure();

    w_idx = 1;

    for i in range(16):
        w = network.params['W1'][i];
        b = network.params['b1'][i];

        w = w.reshape(1, *w.shape);
        b = b.reshape(1, *b.shape);

        conv_layer = Convolution(w, b);
        out = conv_layer.forward(img);
        out = out.reshape(out.shape[2], out.shape[3]);

        ax = fig.add_subplot(4, 4, i + 1, xticks=[], yticks=[]);
        ax.imshow(out, cmap=plt.cm.gray_r, interpolation='nearest');


    plt.show()

def test():
    from Trainer import Trainer
    from dataset.mnist import load_mnist
    (x_train, t_train), (x_test, t_test) = load_mnist(flatten=False);

    max_epochs = 1;

    network = SimpleConvNet(input_dim=(1, 28, 28),
                            conv_params={'filter_num': 30, 'filter_size': 5, 'padding': 0, 'stride': 1},
                            hidden_size=100, output_size=10, weight_init_std=0.01);

    trainer = Trainer(network, x_train, t_train, x_test, t_test, epochs=max_epochs,
                      mini_batch_size=100, optimizer='Adam', optimizer_param={'lr': 0.001},
                      evaluate_sample_num_per_epoch=1000);

    # network.showNetwork();

    print("======================================================================")
    print("Max Iteration : {}".format(trainer.max_iter));
    print("======================================================================")

    trainer.train();

    # Save the trained parameters
    print("save .........................")
    network.save_params("ttt.pkl");
    print("Saved network parameters!!!");


def test1():
    from dataset.mnist import load_mnist
    (x_train, t_train), (x_test, t_test) = load_mnist(flatten=False);

    network = SimpleConvNet(input_dim=(1, 14, 14),
                            conv_params={'filter_num': 10, 'filter_size': 2, 'padding': 0, 'stride': 1},
                            hidden_size=100, output_size=10, weight_init_std=0.01);
    network.showNetwork()
    network.load_params("ttt.pkl");
    network.showNetwork();

    train_acc = network.accuracy(x_train, t_train)
    test_acc = network.accuracy(x_test, t_test)
    print("\n=========== Result===================");
    print("train accuracy : {}".format(train_acc));
    print("test accuracy : {}".format(test_acc));
    print("=======================================\n");






if __name__ == '__main__':
    test1();










