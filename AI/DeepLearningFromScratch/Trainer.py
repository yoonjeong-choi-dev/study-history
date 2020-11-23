from Optimizer import *


class Trainer:
    """
    Class for training a neural network
    """
    def __init__(self, network, x_train, t_train, x_test, t_test,
                 epochs=20, mini_batch_size=100, optimizer='SGD',
                 optimizer_param={'lr':0.01},
                 evaluate_sample_num_per_epoch=None, verbose=True,
                 plot_graph=False):
        """
        :param network: a neural network to train
        :param x_train: train data
        :param t_train: train label
        :param x_test: test data
        :param t_test: test label
        :param epochs: the number of train iterations
        :param mini_batch_size: the size of the mini batch
        :param optimizer: training optimizer
        :param optimizer_param: parameters(e.g learning rate) for optimizer
        :param evaluate_sample_num_per_epoch:
        :param verbose: True for printing accuracy in each epoch
        :param plot_graph: True for plotting loss function and accuracy
        """
        self.network = network;
        self.verbose = verbose;
        self.x_train = x_train;
        self.t_train = t_train;
        self.x_test = x_test;
        self.t_test = t_test;
        self.epochs = epochs;
        self.batch_size = mini_batch_size;
        self.evaluate_sample_num_per_epoch = evaluate_sample_num_per_epoch;
        self.plot_graph = plot_graph;

        #optimizer
        optimizer_class_dict = {'sgd':SGD, 'momentum':Momentum, 'nesterov':NAG,
                                'adagrad':AdaGrad, 'rmsprop':RMSDrop, 'adam':Adam};
        self.optimizer = optimizer_class_dict[optimizer.lower()](**optimizer_param);

        #epoch
        self.train_size = x_train.shape[0];
        self.iter_per_epoch = max(self.train_size / mini_batch_size, 1);
        self.max_iter = int(epochs * self.iter_per_epoch);
        self.current_iter = 0;
        self.current_epoch = 0;

        self.train_loss_list = [];
        self.train_acc_list = [];
        self.test_acc_list = [];
        self.final_train_acc = 0;
        self.final_test_acc = 0;

    def train_step(self):
        batch_mask = np.random.choice(self.train_size, self.batch_size);
        x_batch = self.x_train[batch_mask];
        t_batch = self.t_train[batch_mask];

        grads = self.network.gradient(x_batch, t_batch);
        self.optimizer.update(self.network.params, grads);

        loss = self.network.loss(x_batch, t_batch);
        self.train_loss_list.append(loss);

        if self.verbose:
            print("=========Step : {}==========".format(self.current_iter))
            print("train loss : {}".format(loss));

        if self.current_iter % self.iter_per_epoch == 0:
            self.current_epoch += 1;

            x_train_sample, t_train_sample = self.x_train, self.t_train
            x_test_sample, t_test_sample = self.x_test, self.t_test

            if not self.evaluate_sample_num_per_epoch is None:
                t = self.evaluate_sample_num_per_epoch;
                x_train_sample, t_train_sample = self.x_train[:t], self.t_train[:t];
                x_test_sample, t_test_sample = self.x_test[:t], self.t_test[:t];

            train_acc = self.network.accuracy(x_train_sample, t_train_sample);
            test_acc = self.network.accuracy(x_test_sample, t_test_sample);
            self.train_acc_list.append(train_acc);
            self.test_acc_list.append(test_acc);


            print("\n===========Iter_per_epoch===================")
            print("Iteration : {}".format(self.current_iter));
            print("train accuracy : {}".format(train_acc));
            print("test accuracy : {}".format(test_acc));
            print("============================================\n");

        self.current_iter +=1;

    def train(self):
        for i in range(self.max_iter):
            self.train_step();

        self.final_train_acc = self.network.accuracy(self.x_train, self.t_train);
        self.final_test_acc = self.network.accuracy(self.x_test, self.t_test);


        self.network.showNetwork();
        print("======================================================================");
        print("===========================Final Result===============================");
        print("train accuracy : {}".format(self.final_train_acc));
        print("test accuracy : {}".format(self.final_test_acc));
        print("======================================================================")

        if self.plot_graph:
            import matplotlib.pyplot as plt
            f, (ax1, ax2) = plt.subplots(1, 2, figsize=(10, 20));

            x = np.arange(len(self.train_acc_list));
            ax1.plot(x, self.train_acc_list, label='train acc')
            ax1.plot(x, self.test_acc_list, label='test acc', linestyle='--')
            ax1.set_xlabel("epochs");
            ax1.set_ylabel("accuracy");
            ax1.set_ylim(0, 1.0);
            ax1.legend(loc='lower right');
            ax1.set_title("Accuracy");

            num_itr = np.arange(len(self.train_loss_list));
            ax2.plot(num_itr, self.train_loss_list);
            ax2.set_xlabel("iteration");
            ax2.set_ylabel("loss");
            ax2.set_ylim(0, 3.0);
            ax2.set_title("Loss per iteration");

            plt.show()



def Trainer_MNIST_Example():
    from dataset.mnist import load_mnist
    from MultiLayerNet import MultiLayerNet

    (x_train, t_train), (x_test, t_test) = load_mnist(normalize=True, one_hot_label=True);

    network = MultiLayerNet(input_size=784, hidden_size_list=[150, 100], output_size=10,activation="sigmoid",
                            weight_init_std='sigmoid', weight_decay_lambda=0, use_dropout=True, dropout_ratio=0.5,
                            use_batchNorm=False);


    #network.showNetwork()
    optimizer = 'adam';
    optimizer_params = {'lr':0.01,'decay1':0.9,'decay2':0.999};
    #optimizer_params = {'lr':0.01};
    batch_size = 100;
    epochs= 20;

    trainer = Trainer(network,x_train,t_train,x_test,t_test,epochs=epochs,
                      mini_batch_size=batch_size,optimizer=optimizer,
                      optimizer_param=optimizer_params,verbose=False,
                      plot_graph=True);


    print(trainer.max_iter)
    trainer.train();


if __name__ == '__main__':
    Trainer_MNIST_Example()

































