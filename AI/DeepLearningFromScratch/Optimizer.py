import numpy as np
import matplotlib.pyplot as plt

class SGD:
    def __init__(self, lr=0.01):
        self.lr = lr;

    def update(self, params, grads):
        for key in params.keys():
            params[key] -= self.lr * grads[key];

class Momentum:
    """
    Algorithm :
        - V <- mV - lambda*df(W)
        - W <- W +V (= W -lambda*df(W) + mV)
    Instance :
    1. lr = learning rate
    2. momentum = rate for updating velocity
    3. v : dictionary for keys of parameters
        - v[key] = velocity of a parameter

    """
    def __init__(self, lr=0.01, momentum=0.9):
        self.lr = lr;
        self.momentum = momentum;
        self.v = None;

    def update(self, params, grads):
        if self.v is None:
            self.v = dict();
            for key, val in params.items():
                self.v[key] = np.zeros_like(val);

        for key in params.keys():
            self.v[key] = self.momentum*self.v[key] - self.lr*grads[key];
            params[key] += self.v[key];

class NAG:
    """ (Nesterov's Accelerated Gradient Descent)
     : improved method of Momentum
    1.Original algorithm
     - V <- mV - lambda*df(W+mV)
     - W <- W -V

    2. Improved algorithm
     - V <- mV - lambda*df(W)
     - W <- W -lambda*df(W) + m*V
       i.e W <- W - m^2*V -(1+m)*lambda*df(W)


     -Reference : https://tensorflow.blog/2017/03/22/momentum-nesterov-momentum/
    """
    def __init__(self, lr=0.01, momentum=0.9):
        self.lr = lr;
        self.momentum = momentum;
        self.v = None;

    def update(self, params, grads):
        if self.v is None:
            self.v = dict();
            for key, val in params.items():
                self.v[key] = np.zeros_like(val);

        for key in params.keys():
            # update self.v
            self.v[key] *= self.momentum;
            self.v[key] -= self.lr * grads[key];
            params[key] += self.momentum*self.momentum*self.v[key];
            params[key] -= (1+self.momentum) * self.lr * grads[key];

class AdaGrad:
    """
    Algorithm
     - h <- h + df(W)*df(W) (element wise)
     - W <- W - lamda*(1/sqrt(h))*df
    """
    def __init__(self, lr=0.01):
        self.lr = lr;
        self.history_grad = None;

    def update(self, params, grads):
        if self.history_grad is None:
            self.history_grad = dict();
            for key, val in params.items():
                self.history_grad[key] = np.zeros_like(val);

        for key in params.keys():
            self.history_grad[key] += grads[key]*grads[key];
            params[key] -= self.lr * grads[key] / (np.sqrt(self.history_grad[key]) + 1e-7);



class RMSDrop:
    """ Improved algorithm of AdaGrad
     1. h <- decay*h + (1-dacay)*df(W)*df(W)   # update h with decay proportion in AdaGrad
     2. W <- W - lr*(1/(sqrt(h))*df(W)
    """
    def __init__(self, lr=0.01, decay_rate=0.99):
        self.lr = lr;
        self.decay_rate = decay_rate;
        self.history_grad = None

    def update(self, params, grads):
        if self.history_grad is None:
            self.history_grad = dict();
            for key, val in params.items():
                self.history_grad[key] = np.zeros_like(val);

        for key in params.keys():
            self.history_grad[key] *= self.decay_rate;
            self.history_grad[key] += (1-self.decay_rate)*grads[key]*grads[key];
            params[key] -= self.lr *grads[key] / (np.sqrt(self.history_grad[key]) +1e-7);

class Adam:
    """ Adagrad + RMSDrop
    1. Adagrad Algorithm
     - h <- h + df(W)*df(W) (element wise)
     - W <- W - lamda*(1/sqrt(h))*df

    2. RMSDrop Algorithm
     - h <- decay*h + (1-dacay)*df(W)*df(W)   # update h with decay proportion in AdaGrad
     - W <- W - lr*(1/(sqrt(h))*df(W)
    """

    def __init__(self, lr=0.001, decay1=0.9, decay2=0.999):
        self.lr = lr;
        self.decay1 = decay1;
        self.decay2 = decay2;
        self.iter = 0;
        self.momentum = None;
        self.velocity = None;

    def update(self, params, grads):
        if self.momentum is None:
            self.momentum = dict();
            self.velocity = dict();

            for key, val in params.items():
                self.momentum[key] = np.zeros_like(val);
                self.velocity[key] = np.zeros_like(val);

        self.iter += 1
        lr_t = self.lr*np.sqrt(1.0 - self.decay2**self.iter) / (1.0 - self.decay1**self.iter);

        for key in params.keys():
            # 1. Update momentum (first moment)
            # m <- decay1*m + (1-decay1)*grad
            # i.e m <- m + (1-decay1)(grad - m)
            self.momentum[key] += (1 - self.decay1)*(grads[key] - self.momentum[key]);

            # 2. Update velocity (second moment)
            # v <- decay2*v + (1-decay2)*grad^2
            # i.e v<- v + (1-decay2)(grad^2 - v)
            self.velocity[key] += (1- self.decay2)*(grads[key]**2 - self.velocity[key]);

            params[key] -= lr_t*self.momentum[key] / (np.sqrt(self.velocity[key]) + 1e-7);


def SGD_Two_layers(hidden=50):
    from TwoLayerNet import TwoLayerNet
    from dataset.mnist import load_mnist
    (x_train, t_train), (x_test, t_test) = load_mnist(normalize=True, one_hot_label=True);

    network = TwoLayerNet(input_size=784, hidden_size=hidden, output_size=10);
    optimizer = SGD(0.1);

    # hyper-parameter
    iters_num = 10000;
    train_size = x_train.shape[0];
    batch_size = 100;

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
        params = network.params;
        # update parameters by using SGD
        optimizer.update(params, grad);

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

def Optimizer_compare_example():
    from collections import OrderedDict;
    def f(x, y):
        return x ** 2 / 20.0 + y ** 2

    def df(x, y):
        return x / 10.0, 2.0 * y

    init = (-7.0, 2.0);
    params = dict();
    params['x'], params['y'] = init[0], init[1];
    grads = dict();
    grads['x'], grads['y'] = 0, 0;

    optimizer = OrderedDict();
    optimizer['SGD'] = SGD(lr=0.95);
    optimizer['Momentum'] = Momentum(lr=0.1);
    optimizer['NAG'] = NAG(lr=0.1);
    optimizer['AdaGrad'] = AdaGrad(lr=1.5);
    optimizer['RMSDrop'] = RMSDrop(lr=1.5);
    optimizer['Adam'] = Adam(lr=0.3);

    idx = 1;

    for key in optimizer:
        opt = optimizer[key];
        x_his = [];
        y_his = [];
        params['x'], params['y'] = init[0], init[1];

        for i in range(30):
            x_his.append(params['x']);
            y_his.append(params['y']);

            grads['x'],grads['y'] = df(params['x'], params['y']);
            opt.update(params, grads);


        x = np.arange(-10, 10, 0.01);
        y = np.arange(-5, 5, 0.01);

        X, Y = np.meshgrid(x, y);
        Z = f(X, Y);

        mask = Z>7
        Z[mask] = 0;

        plt.subplot(3,2, idx);
        idx +=1;

        plt.plot(x_his, y_his, 'o-', color="red");
        plt.contour(X, Y, Z);
        plt.ylim(-10, 10);
        plt.xlim(-10, 10);
        plt.plot(0,0,'+');
        plt.title(key);
        plt.xlabel('x')
        plt.ylabel('y');

    plt.show()


