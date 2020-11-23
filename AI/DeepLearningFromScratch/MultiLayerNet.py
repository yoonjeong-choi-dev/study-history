# Library
from collections import OrderedDict
import pickle
# User-defined modules
from Layers import *
from Gradient import numerical_gradient


class MultiLayerNet:
    """ Fully connected Multi Layer Network
    ----------------------------------------------------------------------

    Input layer     ->  Hidden layer : Affine + activation
    Hidden layer    ->  Hidden layer : Affine + activation
    Hidden layer    ->  Output layer : Affine + Softmax layers
    ----------------------------------------------------------------------
    Parameters :
    1. input_size : the size of each data (e.g in MNIST, 784)

    2. hidden_size_list : list of the number of neurons in each hidden layer (e.g [100,100,100])

    3. output_size : the size of output (e.g in MNIST, 10)

    4. activation : activation function ('relu' or 'sigmoid')

    5. weight_init_std : variance of initial weight parameter
        - 'relu' : 'He initialization' == sqrt(2/batch_size)
        - 'sigmoid' or 'xavier' : 'Xavier initialization' == sqrt(1/batch_size)

    6. weight_decay_lambda : the scale of weight decay(L2-norm)
        - use for cost function (loss)
        - loss <- original loss + weight_decay_lambda * L2_norm(weight)

    7. use_dropout : true for using dropout / false for not using dropout

    8. dropout_ratio : the ratio of dropout when use_dropout == True

    9. use_batchNorm : true for using batchNormalization
    ----------------------------------------------------------------------
    Instance variables :
    0. Common Instances :
        -input_size = input_size;
        -output_size = output_size;
        -hidden_size_list = hidden_size_list;
        -hidden_layer_num = len(hidden_size_list);
        -use_dropout = use_dropout;
        -weight_decay_lambda = weight_decay_lambda;
        -use_batchNorm = use_batchNorm;

    1. params
        - dictionary variables for parameters of the model
        - params['W_i'], params['b_i'] : weight and bias in the i-th layer

    2. layers
        - ordered dictionary variables for layers
        - e.g layers['Affine1'], layers['Relu1'] etc

    3. lastLayer
        - the final layer i.e output layer
        - Here, we use SoftmaxWithLoss layer
    ----------------------------------------------------------------------
    Methods :
    1. __init__(self, input_size, hidden_size_list, output_size,
                 activation="relu", weight_init_std='relu', weight_decay_lambda=0,
                 use_dropout=False, dropout_ratio=0.5, use_batchNorm=False)

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

    def __init__(self, input_size, hidden_size_list, output_size,
                 activation="relu", weight_init_std='relu', weight_decay_lambda=0,
                 use_dropout=False, dropout_ratio=0.5, use_batchNorm=False):
        """
        :param input_size: the size of each data (e.g in MNIST, 784)
        :param hidden_size_list: list of the number of neurons in each hidden layer (e.g [100,100,100])
        :param output_size: the size of output (e.g in MNIST, 10)
        :param activation: activation function ('relu' or 'sigmoid')
        :param weight_init_std: variance of weight
            - 'relu' : 'He initialization' == sqrt(2/batch_size)
            - 'sigmoid' or 'xavier' : 'Xavier initialization' == sqrt(1/batch_size)
        :param weight_decay_lambda: the scale of reducing L2-norm of weight params
            - use for cost function (loss)
            - loss <- original loss + 0.5*weight_decay_lambda * L2_norm(weight)
        :param use_dropout: true for using dropout / false for not using dropout
        :param dropout_ratio: the ratio of dropout when use_dropout == True
        :param use_batchNorm: true for using batchNormalization
        """
        # Initialize the instances
        self.input_size = input_size;
        self.output_size = output_size;
        self.hidden_size_list = hidden_size_list;
        self.hidden_layer_num = len(hidden_size_list);
        self.use_dropout = use_dropout;
        self.weight_decay_lambda = weight_decay_lambda;
        self.use_batchNorm = use_batchNorm;
        self.params = dict();

        self.activation = activation;
        self.dropout_ratio = dropout_ratio;

        # Initialize the parameters
        self.__init_weight(weight_init_std);

        # Make hidden layers
        activation_layer = {'sigmoid': Sigmoid, 'relu': ReLU};
        self.layers = OrderedDict();
        for idx in range(1, self.hidden_layer_num + 1):
            # Make an affine map
            self.layers['Affine' + str(idx)] = Affine(self.params['W' + str(idx)], self.params['b' + str(idx)]);

            # if we use batchNormalization layer
            if self.use_batchNorm:
                self.params['gamma' + str(idx)] = np.ones(hidden_size_list[idx - 1]);
                self.params['beta' + str(idx)] = np.zeros(hidden_size_list[idx - 1]);
                self.layers['BatchNorm' + str(idx)] = BatchNormalization(self.params['gamma' + str(idx)],
                                                                         self.params['beta' + str(idx)]);
            # update activation function for each layer
            self.layers['Activation_function' + str(idx)] = activation_layer[activation.lower()]();  # 변경부분

            # if we use dropout
            if self.use_dropout:
                self.layers['Dropout' + str(idx)] = Dropout(dropout_ratio);

        # Make the the Affine layer of the output layer
        idx = self.hidden_layer_num + 1
        self.layers['Affine' + str(idx)] = Affine(self.params['W' + str(idx)], self.params['b' + str(idx)]);

        # Make the output layer with SoftmaxWithLoss
        self.lastLayer = SoftmaxWithLoss();


    def __init_weight(self, weight_init_std):
        """
        Initialize weight with respect to the type of layer
        :param weight_init_std: the type of layers
            - 'relu' : 'He initialization' == sqrt(2/batch_size)
            - 'sigmoid' or 'xavier' : 'Xavier initialization' == sqrt(1/batch_size)

        --------------------------------------------------------------------------------
        Implementation :

        Consider the idx-th layer
        The input data size is the number of neurons in the (idx-1)-th layer
        The output data size is the number of neurons in the (idx)-th layer
        i.e W has the form of (all_size_list[idx-1], all_size_list[idx])
            b has the form of (all_size_list[idx-1])
        """
        # batch_size : the size of input data
        #             i.e all_size_list[idx-1] in the idx-th layer
        all_size_list = [self.input_size] + self.hidden_size_list + [self.output_size];

        for idx in range(1, len(all_size_list)):

            scale = weight_init_std;
            # relu
            if str(weight_init_std).lower() in ('relu', 'he'):
                scale = np.sqrt(2.0 / all_size_list[idx-1]);

            # sigmoid or xavier
            elif str(weight_init_std).lower() in ('sigmoid', 'xavier'):
                scale = np.sqrt(1.0 / all_size_list[idx-1]);

            self.params['W'+str(idx)] = scale*np.random.randn(all_size_list[idx-1], all_size_list[idx]);
            self.params['b'+str(idx)] = np.zeros(all_size_list[idx]);

    def predict(self, x, train_flag=False):
        """
        :param x : input data
        :param train_flag: true(for updating params) / false(for testing)
                            - for BatchNormalization/Dropout Layer
        :return: prediction
        """
        # forward propagation
        for key, layer in self.layers.items():
            # if dropout or batch normalization layer :
            if "Dropout" in key or "BatchNorm" in key:
                x = layer.forward(x, train_flag);
            else:
                x = layer.forward(x);

        return x;

    def loss(self, x, t, train_flag=False):
        """
        :param x: input data
        :param t: input label
        :param train_flag: true(for updating params) / false(for testing)
                           - for BatchNormalization/Dropout Layer when backpropagation
        :return: the error between predict(x) and t w.r.t cost function
        ----------------------------------------------------------------------
        Here, we use 'weight decay' for avoiding overfitting
         : For cost(loss) function, add weight_decay_lambda *(0.5 * L2_norm(weight))
        i.e loss <- original loss + 0.5*weight_decay_lambda * L2_norm(weight)
        """

        y = self.predict(x, train_flag);

        weight_decay = 0;
        # 1 ~ self.hidden_layer_num+2 : input layer ~ last hidden layer
        for idx in range(1, self.hidden_layer_num + 2):
            weight = self.params['W'+str(idx)];
            weight_decay +=0.5*self.weight_decay_lambda*np.sum(weight**2);


        return self.lastLayer.forward(y, t) + weight_decay;

    def accuracy(self, x, t):
        y = self.predict(x, train_flag=False);
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
        loss_W = lambda W: self.loss(x, t, train_flag=True);

        grads = dict();

        # Calculate numerical_gradient of each layer
        # 1 ~ self.hidden_layer_num+2 : input layer ~ last hidden layer
        for idx in range(1, self.hidden_layer_num+2):
            grads['W'+str(idx)] = numerical_gradient(loss_W, self.params['W'+str(idx)]);
            grads['b'+str(idx)] = numerical_gradient(loss_W, self.params['b'+str(idx)]);

            # if we use batchNormalization layer
            if self.use_batchNorm and idx != self.hidden_layer_num+1:
                grads['gamma'+str(idx)] = numerical_gradient(loss_W, self.params['gamma'+str(idx)]);
                grads['beta' + str(idx)] = numerical_gradient(loss_W, self.params['beta' + str(idx)]);

        return grads;

    def gradient(self, x, t):
        # Forward-propagation
        self.loss(x, t, train_flag=True);

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
        for idx in range(1, self.hidden_layer_num+2):
            # self.weight_decay_lambda * self.params['W'+str(idx)] : a backpropagation term for 'weight decay'
            grads['W'+str(idx)] = self.layers['Affine'+str(idx)].dW + self.weight_decay_lambda * self.params['W'+str(idx)];
            grads['b'+str(idx)] = self.layers['Affine'+str(idx)].db;

            # if we use batchNormalization layer
            if self.use_batchNorm and idx != self.hidden_layer_num + 1:
                grads['gamma' + str(idx)] = self.layers['BatchNorm' + str(idx)].dgamma;
                grads['beta' + str(idx)] = self.layers['BatchNorm' + str(idx)].dbeta;

        return grads;

    def setNetwork(self, file_name="MultiLayer_Info.pkl"):
        """
        Reset the Network
        """

    def showNetwork(self):
        print("==========================Network=====================================");
        print("1. Layer ");
        for key in self.layers.keys():
            print(key);
        print("======================================================================")
        print("2. Parameters shape")
        for key in self.params.keys():
            print("Parameter : {}".format(key));
            print(self.params[key].shape);
        print("======================================================================")
        print("3. List of Hidden layer size ");
        print(self.hidden_size_list);
        print("======================================================================")

    def save_params(self, file_name="MultiLayer_Info.pkl"):
        # Save the constructor input
        constructor = dict();
        constructor['input_size'] = self.input_size;
        constructor['hidden_size_list'] = self.hidden_size_list;
        constructor['output_size'] = self.output_size
        constructor['activation'] = self.activation;
        constructor['weight_decay_lambda'] = self.weight_decay_lambda;
        constructor['use_dropout'] = self.use_dropout;
        constructor['dropout_ratio'] = self.dropout_ratio;
        constructor['use_batchNorm'] = self.use_batchNorm;

        params = dict();
        for key, val in self.params.items():
            params[key] = val;
        batchNorm = dict();
        if constructor['use_batchNorm']:
            for idx in range(1, self.hidden_layer_num+1):
                batchNorm['momentum' + str(idx)] = self.layers['BatchNorm' + str(idx)].momentum;
                batchNorm['running_mean' + str(idx)] = self.layers['BatchNorm' + str(idx)].running_mean;
                batchNorm['running_var' + str(idx)] = self.layers['BatchNorm' + str(idx)].running_var;
        else:
            batchNorm = None;

        # save trained parameters as *.pkl
        with open(file_name, 'wb') as f:
            pickle.dump(constructor, f);
            pickle.dump(params, f);
            pickle.dump(batchNorm, f);


    def load_params(self, file_name="Multilayer_params.pkl"):
        # load trained parameters
        with open(file_name, 'rb') as f:
            constructor = pickle.load(f);
            params = pickle.load(f);
            batchNorm = pickle.load(f);

        input_size = constructor['input_size'];
        hidden_size_list = constructor['hidden_size_list']
        output_size = constructor['output_size']
        activation = constructor['activation']

        weight_decay_lambda = constructor['weight_decay_lambda']
        use_dropout = constructor['use_dropout']
        dropout_ratio = constructor['dropout_ratio']
        use_batchNorm = constructor['use_batchNorm']

        # if use_batchNorm:
        #     with open(file_name, 'rb') as f:
        #         temp = pickle.load(f);
        #         params = pickle.load(f);
        #         batchNorm = pickle.load(f);

        self.__init__(input_size, hidden_size_list, output_size, activation=activation, weight_init_std='relu',
                      weight_decay_lambda=weight_decay_lambda, use_dropout=use_dropout, dropout_ratio=dropout_ratio,
                      use_batchNorm=use_batchNorm);

        for key, val in params.items():
            self.params[key] = val;




        for idx in range(1, self.hidden_layer_num + 1):
            # Make an affine map
            self.layers['Affine' + str(idx)] = Affine(self.params['W' + str(idx)], self.params['b' + str(idx)]);

            # if we use batchNormalization layer
            if self.use_batchNorm:
                self.layers['BatchNorm' + str(idx)] = BatchNormalization(self.params['gamma' + str(idx)],
                                                                         self.params['beta' + str(idx)],
                                                                         batchNorm['momentum' + str(idx)],
                                                                         batchNorm['running_mean' + str(idx)],
                                                                         batchNorm['running_var' + str(idx)]);

            # if we use dropout
            if self.use_dropout:
                self.layers['Dropout' + str(idx)] = Dropout(dropout_ratio);

        # Make the the Affine layer of the output layer
        idx = self.hidden_layer_num + 1
        self.layers['Affine' + str(idx)] = Affine(self.params['W' + str(idx)], self.params['b' + str(idx)]);





def test():
    from dataset.mnist import load_mnist
    (x_train, t_train), (x_test, t_test) = load_mnist(normalize=True, one_hot_label=True);

    network = MultiLayerNet(input_size=784, hidden_size_list=[150, 100], output_size=10, activation="relu",
                            weight_init_std='relu', weight_decay_lambda=0, use_dropout=True, dropout_ratio=0.5,
                            use_batchNorm=True);
    #network.showNetwork();


    print("Load the network information....................");
    network.load_params("MultiLayer_params_SGD_01.pkl");
    print("loaded parameters");

    train_acc = network.accuracy(x_train, t_train)
    test_acc = network.accuracy(x_test, t_test)
    print("\n=========== Result===================");
    print("train accuracy : {}".format(train_acc));
    print("test accuracy : {}".format(test_acc));
    print("=======================================\n");



def MultiLayerNet_gradient_check():
    from dataset.mnist import load_mnist
    (x_train, t_train), (x_test, t_test) = load_mnist(normalize=True, one_hot_label=True);

    network = MultiLayerNet(input_size=784, hidden_size_list=[50], output_size=10);

    x_batch = x_train[:3];
    t_batch = t_train[:3];

    grad_numerical = network.numerical_gradient(x_batch, t_batch);
    grad_backprop = network.gradient(x_batch, t_batch);

    for key in grad_numerical.keys():
        diff = np.average(np.abs(grad_backprop[key] - grad_numerical[key]));
        print(key + " : {}".format(diff));



def MultiLayerNet_MNIST_example():
    from dataset.mnist import load_mnist
    import Optimizer as op

    (x_train, t_train), (x_test, t_test) = load_mnist(normalize=True, one_hot_label=True);

    network = MultiLayerNet(input_size=784, hidden_size_list=[150, 100], output_size=10,activation="relu",
                            weight_init_std='relu', weight_decay_lambda=0, use_dropout=True, dropout_ratio=0.5,
                            use_batchNorm=True);




    # hyper-parameter
    iters_num = 10000;


    train_size = x_train.shape[0];
    batch_size = 100;
    learning_rate = 0.1

    optimizer = op.SGD(learning_rate);

    # data memory during training
    train_loss_list = [];
    train_acc_list = [];
    test_acc_list = [];

    # epoch
    iter_per_epoch = max(train_size / batch_size, 1)

    network.showNetwork()

    for i in range(iters_num):

        batch_mask = np.random.choice(train_size, batch_size);
        x_batch = x_train[batch_mask];
        t_batch = t_train[batch_mask];

        # grad = network.numerical_gradient(x_batch, t_batch);
        grad = network.gradient(x_batch, t_batch);
        params = network.params;

        # update parameters by SGD
        optimizer.update(params, grad);

        # for key in network.params.keys():
        #     network.params[key] -= learning_rate * grad[key];


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
    print("The number of neurons in the hidden layer : {}".format(network.hidden_size_list))
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

    print("Save the network information....................");
    network.save_params("MultiLayer_params_SGD_01.pkl");
    print("saved parameters!!!!");

if __name__ == '__main__':
    #MultiLayerNet_MNIST_example()
    test();

