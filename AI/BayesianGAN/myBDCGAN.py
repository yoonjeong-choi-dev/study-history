""" Reference
    1. https://github.com/carpedm20/DCGAN-tensorflow/blob/master/model.py
    2.

"""

import numpy as np
import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec
import os
import math
import time

from collections import OrderedDict, defaultdict
import tensorflow as tf
from sklearn import mixture

import warnings
warnings.simplefilter(action='ignore', category=FutureWarning)


# Function to plot an MNIST image generated
#   - plot 8*8 images
def plot_generated_mnist_images(samples, size=(8, 8)):
    fig = plt.figure(figsize=size);
    gs = gridspec.GridSpec(size[0], size[1]);
    gs.update(wspace=0.05, hspace=0.05);

    for i, sample in enumerate(samples):
        ax = plt.subplot(gs[i]);
        plt.axis("off");
        plt.imshow(sample.reshape(28, 28));

    return fig;







def one_hot_encoder(class_numbers, num_classes):
    return np.eye(num_classes, dtype=float)[class_numbers];


class AttributeDict(dict):
    """
    A class to use Dictionary in convenient way
    i.e object["key"] => object.key
    """
    def __getattr__(self, attr):
        return self[attr];

    def __setattr__(self, attr, value):
        self[attr] = value;

    def __hash__(self):
        return hash(tuple(sorted(self.items())));


def print_images(sampled_images, label, index, directory, save_all_samples=False):
    import matplotlib as mpl;
    mpl.use("Agg");

    def un_normalize(img, cdim):
        img_out = np.zeros_like(img);
        for i in range(cdim):
            img_out[:, :, i] = 255.*((img[:, :, i] +1.)/2.0);

        img_out = img_out.astype(np.uint8);
        return img_out;

    if type(sampled_images) == np.ndarray:
        N, h, w, cdim = sampled_images.shape;
        idxs = np.random.choice(np.arange(N), size=(5, 5), replace=False);
    else:
        sampled_imgs, sampled_probs = sampled_images;
        sampled_images = sampled_imgs[sampled_probs.argsort()[::-1]];
        idxs = np.arange(5*5).reshape((5,5));
        N, h, w, cdim = sampled_images.shape;


    fig, axes = plt.subplots(5, 5);
    for i in range(5):
        for j in range(5):
            if cdim == 1:
                axes[i, j].imshow(un_normalize(sampled_images[idxs[i, j]], cdim)[:, :, 0], cmap="gray");
            else:
                axes[i, j].imshow(un_normalize(sampled_images[idxs[i, j]], cdim));

            axes[i, j].axis("off");
            axes[i, j].set_xticklabels([]);
            axes[i, j].set_yticklabels([]);
            axes[i, j].set_aspect("equal");


    if not os.path.exists(directory):
        os.makedirs(directory);

    fig.savefig(os.path.join(directory + "{}_{}.png".format(label, index)),
                bbox_inches="tight");
    plt.close("all");

    if "raw" not in label.lower() and save_all_samples:
        np.savez_compressed(os.path.join(directory, "samples_{}_{}.npz".format(label, index)),
                            samples=sampled_images);


class FigPrinter:

    def __init__(self, subplot_arg):
        import matplotlib as mpl
        mpl.use("Agg");
        self.fig, self.axes = plt.subplots(*subplot_arg);

    def print_to_file(self, file_name, close_on_exit=True):
        import matplotlib as mpl
        mpl.use("Agg");

        self.fig.savefig(file_name, bbox_inches="tight");
        if close_on_exit:
            plt.close("all");






""" A function for batch normalization layer """
class batch_norm(object):
    def __init__(self, epsilon=1e-5, momentum=0.9, name="batch_norm"):
        with tf.variable_scope(name,reuse=tf.AUTO_REUSE):
            self.epsilon = epsilon;
            self.momentum = momentum;
            self.name = name;

    def __call__(self, x, train=True):
        return tf.contrib.layers.batch_norm(x,
                                            decay=self.momentum,
                                            updates_collections=None,
                                            epsilon=self.epsilon,
                                            scale=True,
                                            is_training=train,
                                            scope=self.name);


""" Functions for Convolution/inverse_Convolution/Full-connected layers """
def conv2d(input_, output_dim, k_h=5, k_w=5, d_h=2, d_w=2, stddev=0.02,
           w=None, biases=None, name="conv2d"):
    """ Make a convolution layer
    :param input_: input data
    :param output_dim: dim of output
    :param k_h: height of kernel(window)
    :param k_w: width of kernel(window)
    :param d_h: height of stride
    :param d_w: width of stride
    :param stddev: standard deviation for initializing w
    :param w: weight variables for convolution layer
    :param biases: bias variables for convolution layer
    :param name: variable name for tensorflow graph
    :return: output of convolution layer
    """
    with tf.variable_scope(name,reuse=tf.AUTO_REUSE):
        if w is None:
            w = tf.get_variable('w', [k_h, k_w, input_.get_shape()[-1], output_dim],
                                initializer=tf.truncated_normal_initializer(stddev=stddev));

        conv = tf.nn.conv2d(input_, w, strides=[1, d_h, d_w, 1], padding="SAME");

        if biases is None:
            biases = tf.get_variable('biases', [output_dim],
                                     initializer=tf.constant_initializer(0.0));

        conv = tf.reshape(tf.nn.bias_add(conv, biases), conv.get_shape());
        return conv;


def deconv2d(input_, output_shape, k_h=5, k_w=5, d_h=2, d_w=2, stddev=0.02,
             name="deconv2d", with_w=False, w=None, biases=None):
    """ Make a transposed_convolution layer
    :param input_: input data
    :param output_shape:  shape of output
    :param k_h: height of kernel(window)
    :param k_w: width of kernel(window)
    :param d_h: height of stride
    :param d_w: width of stride
    :param stddev: standard deviation for initializing w
    :param name:  variable name for tensorflow graph
    :param with_w: True => return w and biases also
    :param w: weight variables for convolution layer
    :param biases: bias variables for convolution layer
    :return: output of transposed_convolution layer
    """

    with tf.variable_scope(name,reuse=tf.AUTO_REUSE):
        # filter = [h, w, output_channels, in_channels]
        if w is None:
            w = tf.get_variable('w', [k_h, k_w, output_shape[-1], input_.get_shape()[-1]],
                                initializer=tf.random_normal_initializer(stddev=stddev));

        deconv = tf.nn.conv2d_transpose(input_, w, output_shape=output_shape,
                                        strides=[1, d_h, d_w, 1]);

        if biases is None:
            biases = tf.get_variable('biases', [output_shape[-1]],
                                     initializer=tf.constant_initializer(0.0));

        deconv = tf.reshape(tf.nn.bias_add(deconv, biases), deconv.get_shape());

        if with_w:
            return deconv, w, biases;
        else:
            return deconv;


def linear(input_, output_size, scope=None, stddev=0.02, bias_start=0.0,
           with_w=False, matrix=None, bias=None):

    """ Make a full-connected layer
    :param input_: input data
    :param output_size: size of output
    :param scope: variable scope for tensorflow graph
    :param stddev: standard deviation for initializing w
    :param bias_start:
    :param with_w: True => return w and biases also
    :param matrix:  weight variables for full-connected layer
    :param bias: bias variables for full-connected layer
    :return: output of full-connected layer
    """
    shape = input_.get_shape().as_list();

    with tf.variable_scope(scope or "Linear",reuse=tf.AUTO_REUSE):
        if matrix is None:
            matrix = tf.get_variable("Matrix", [shape[1], output_size], tf.float32,
                                     tf.random_normal_initializer(stddev=stddev));

        if bias is None:
            bias = tf.get_variable("bias", [output_size],
                                   initializer=tf.constant_initializer(bias_start))

        if with_w:
            return tf.matmul(input_, matrix) + bias, matrix, bias;
        else:
            return tf.matmul(input_, matrix) + bias;


""" Some util functions for Convolution
out_size = (input_size + 2padding - kernel_size)/stride + 1
"""
def conv_out_size(size, stride):
    co = int(math.ceil(size / float(stride)));
    return co;


def kernel_sizer(size, stride):
    ko = int(math.ceil(size / float(stride)));

    if ko % 2 == 0:
        ko = ko+1;
    return ko;


def get_strides(num_layers, num_pool):
    interval = int(math.floor(num_layers/float(num_pool)));
    strides = np.array([1]*num_layers);
    strides[0:interval*num_pool:interval] = 2;
    return strides;

#TODO
""" Huber loss 
Reference : https://en.wikipedia.org/wiki/Huber_loss(다시보기)
 - a loss function used in robust regression
   , which is less sensitive to outliers in data than the squared error loss
 1. Original Definition
    : L_delta(a) 
        = 0.5*pow(a, 2)                             ,if abs(a) < delta
        = delta(abs(a) - 0.5delta)                  ,otherwise
        
 2. Let a = y - f(x) where y: real value(label) and f(x): predicted value.
    Then the Huber loss between real and predicted values is given by
    : L_delta(real, pred)
        = 0.5*pow(real - pred, 2)                   ,if abs(real-pred) < delta
        = delta(abs(real - pred) -0.5pow(delta, 2)  ,otherwise
    
    : L_delta(real, pred)
        = 0.5*pow(res, 2)                           ,if res < delta
        = delta*res - 0.5pow(delta, 2)              ,otherwise
        where res = abs(real - pred) 
"""
def huber_loss(labels, predictions, delta=1.0):
    residual = tf.abs(predictions - labels);
    condition = tf.less(residual, delta);
    ret1 = 0.5 * tf.square(residual);
    ret2 = delta*residual - 0.5*tf.square(delta);

    return tf.where(condition, ret1, ret2);


""" Classes for datasets"""
class MNIST:
    def __init__(self, data_dir="./mnist/data/"):
        from tensorflow.examples.tutorials.mnist import input_data;
        self.mnist = input_data.read_data_sets(data_dir, one_hot=True);
        self.x_dim = [28, 28, 1];
        self.num_classes = 10;
        self.dataset_size = self.mnist.train.images.shape[0];


    def next_batch(self, batch_size, class_id=None):
        """
        :param batch_size: batch size
        :param class_id: an integer for the digit to sample images from mnist
        :return: batch data
        """
        if class_id is None:
            image_batch, labels = self.mnist.train.next_batch(batch_size);
            new_image_batch = np.array([(image_batch[n] * 2. - 1.).reshape((28, 28, 1))
                                       for n in range(image_batch.shape[0])]);

            return new_image_batch, labels;
        else:
            class_id_batch = np.array([]);
            while class_id_batch.shape[0] < batch_size:
                image_batch, labels = self.mnist.train.next_batch(batch_size);
                image_batch = np.array([(image_batch[n]*2. - 1.).reshape((28, 28, 1))
                                        for n in range(image_batch.shape[0])]);

                class_id_idx = np.argmax(labels, axis=1) == class_id;

                if len(class_id_idx) > 0:
                    if class_id_batch.shape[0] == 0:
                        class_id_batch = image_batch[class_id_batch];
                    else:
                        class_id_batch = np.concatenate([class_id_batch, image_batch[class_id_idx]]);

            labels = np.zeros((batch_size, 10));
            labels[:, class_id] = 1.0;
            return class_id_batch[:batch_size], labels;


    def test_batch(self, batch_size):
        image_batch, labels = self.mnist.test.next_batch(batch_size);
        new_image_batch = np.array([(image_batch[n] * 2. - 1.).reshape((28, 28, 1))
                                    for n in range(image_batch.shape[0])]);

        return new_image_batch, labels;

    def get_test_set(self):
        test_imgs = self.mnist.test.images;
        test_images = np.array([(test_imgs[n]*2. - 1.).reshape((28, 28, 1))
                                for n in range(test_imgs.shape[0])]);
        test_labels = self.mnist.test.labels;

        return test_images, test_labels;





""" Main : Bayesian GAN """
class BDCGAN(object):
    def __init__(self, x_dim, z_dim, dataset_size, batch_size=64,
                 g_filter=64, d_filter=64,prior_std=1.0, num_layer=4,
                 num_classes=2,
                 J=1, M=1, J_d=None, eta=2e-4,
                 alpha=0.01, lr=0.0002, optimizer="adam",
                 DCGAN=False):
        """
        ================================================================
        <Networks for Generator and Discriminator>
        :param x_dim: dim of input data(e.g mnist) for D
        :param z_dim: dim of input data(noise) for G
        :param dataset_size: the size of data in real data distribution
        :param batch_size: batch size for mini-batch training
        :param g_filter: dimension of convolution filter for G
        :param d_filter: dimension of convolution filter for D
        :param prior_std: Neural network prior std
        :param num_layer: the number of layers in the network (G or D)
        ================================================================
        # TODO
        <Hyper-parameters for SGHMC>
          : (Stochastic Gradient Hamiltonian Monte Carlo)
        :param J: the number of MC-samples of z to integrate in G (paper J_g)
        :param M: the number of samplings in SGHMC
        :param J_d: the number of MC-samples of z to integrate in D
        :param eta:
        :param alpha:
        ================================================================
        <Optimizer before applying SGHMC to speed up the training
        :param lr: learning rate for the input optimizer
        :param optimizer: "adam" or "sgd"
        ================================================================
        :param DCGAN: True=> Classic DCGAN / False=>Bayesian GAN
        """
        channels = x_dim[2];

        self.is_gray = (channels==1);
        self.optimizer = optimizer.lower();
        self.dataset_size = dataset_size;
        self.batch_size = batch_size;

        self.K = num_classes          #Fake or real classes
        self.x_dim = x_dim;
        self.z_dim = z_dim;

        self.g_filter = g_filter;
        self.d_filter = d_filter;
        self.channels = channels;

        self.lr = lr;


        # Information for Bayes GAN
        self.prior_std = prior_std;
        self.num_G = J;
        self.num_D = J_d if J_d is not None else 1;
        self.num_mcmc = M;
        self.eta = eta;
        self.alpha = alpha;

        # Information for classic DCGAN
        self.DCGAN = DCGAN;
        if self.DCGAN:
            assert self.num_G == 1 and self.num_D == 1 and self.num_mcmc == 1, \
                "Invalid settings(J, J_d, M) for Classic DCGAN";
        # TODO
        self.noise_std = np.sqrt(2*self.alpha*self.eta);
        # TODO
        self.num_pool = 4;
        # max_num_dfs : maximum number of filters
        self.max_num_dfs = 512;
        # G_strides : stride for G
        self.G_strides = get_strides(num_layer, self.num_pool);
        # D_strides = stride for D
        self.D_strides = self.G_strides;



        num_dfs = np.cumprod(np.array([self.d_filter] + list(self.D_strides)))[:-1];

        num_dfs[num_dfs >= self.max_num_dfs] = self.max_num_dfs;

        # num_d_features : list of the number of features in layers for D
        self.num_d_features = list(num_dfs);
        # num_g_features : list of the number of features in layers for G
        #              : inverse of num_d_filters
        self.num_g_features = self.num_d_features[::-1];

        # D_batch_norm : Dictionary for Batch normalization layers for D
        self.D_batch_norm = None;
        # D_weight_dims : List of dimensions for W in each layer of D
        self.D_weight_dims = OrderedDict();
        # D_kernel_sizes : List of kernel size in Convolution layer in D
        self.D_kernel_sizes = None;

        # G_batch_norm : Dictionary for Batch normalization layers for G
        self.G_batch_norm = None;
        self.G_output_dims = OrderedDict();
        # G_weight_dims : dimensions for W in each layer of G
        self.G_weight_dims = OrderedDict();
        # G_kernel_sizes : List of kernel size in Convolution layer in G
        self.G_kernel_sizes = None;

        self.inputs = None;
        self.z = None;
        self.z_sampler = None;
        self.G_param_list = None;
        self.D_param_list = None;

        self.D_learning_rate = None;
        self.D_vars = None;

        # d_losses : list of d_loss of each D in SGHMC
        # d_train_ops : list minimizing operator of each D in SGHMC
        # d_train_ops_adam :
        self.d_losses, self.d_train_ops, self.d_train_ops_adam = None, None, None;

        self.G_learning_rate = None;
        self.G_vars = None;
        # g_losses : list of d_loss of each G in SGHMC
        # g_train_ops : list minimizing operator of each G in SGHMC
        # g_train_ops_adam :
        self.g_losses, self.g_train_ops, self.g_train_ops_adam = None, None, None;

        self.G_sampler = None;

        self.construct_from_hypers(g_kernel_size=5, g_strides=[2,2,2,2],
                                   d_kernel_size=5, d_strides=[2,2,2,2],
                                   num_dfs=self.num_d_features,
                                   num_gfs=self.num_g_features);



        self.build_graph();

    def construct_from_hypers(self,
                              g_kernel_size=5, g_strides=[2,2,2,2],
                              d_kernel_size=5, d_strides=[2,2,2,2],
                              num_dfs=None, num_gfs=None):
        """
        1. _batch_norm : a list of batch normalization layer
        2. _weight_dims : a ordered dict of tuples of the shape of W and b in each layer
        3.
        :param g_kernel_size: starting kernel size of G
        :param g_strides: a list of strides of layers in G
        :param d_kernel_size: starting kernel size of D
        :param d_strides: a list of strides of layers in D
        :param num_dfs: list of the number of filters in Convolution layers for D
        :param num_gfs: list of the number of filters in Convolution layers for G
        """



        self.D_batch_norm = AttributeDict([("d_bn"+str(i), batch_norm(name="d_bn"+str(i)))
                                           for i in range(len(d_strides))]);
        self.G_batch_norm = AttributeDict([("g_bn"+str(i), batch_norm(name="g_bn"+str(i)))
                                           for i in range(len(g_strides))]);

        if num_dfs is None:
            # Default : 64 -> 128 -> 256 -> 512
            num_dfs = [self.d_filter, self.d_filter*2, self.d_filter*4, self.d_filter*8];

        if num_gfs is None:
            # Default : 512 -> 256 -> 128 -> 64
            num_gfs = [self.g_filter*8, self.g_filter*4, self.g_filter*2, self.g_filter];


        # Check the validation of hyper-parameters
        assert len(g_strides) == len(num_gfs), "Invalid Hyper-parameters"
        assert len(d_strides) == len(num_dfs), "Invalid Hyper-parameters"



        # Generator
        g_h, g_w = self.x_dim[0], self.x_dim[1];
        ks = g_kernel_size;
        self.G_kernel_sizes = [ks];

        num_gfs = num_gfs + [self.channels];

        # Add shape of weights for convolution layer
        for layer in range(len(g_strides))[::-1]:
            self.G_output_dims["g_h"+str(layer+1)+"_out"] = (g_h, g_w);

            assert g_strides[layer] <=2, "Invalid Stride";
            assert ks % 2 == 1, "Invalid Kernel Size";

            self.G_weight_dims["g_h"+str(layer+1)+"_W"] = (ks, ks, num_gfs[layer+1], num_gfs[layer]);
            self.G_weight_dims["g_h" + str(layer + 1) + "_b"] = (num_gfs[layer+1],);
            g_h, g_w = conv_out_size(g_h, g_strides[layer]), conv_out_size(g_w, g_strides[layer]);
            ks = kernel_sizer(ks, g_strides[layer]);
            self.G_kernel_sizes.append(ks);

        # Add shape of weights for a full connected layer
        self.G_weight_dims.update(OrderedDict([("g_h0_lin_W", (self.z_dim, num_gfs[0] * g_h * g_w)),
                                               ("g_h0_lin_b", (num_gfs[0] * g_h * g_w,))]))

        self.G_output_dims["g_h0_out"] = (g_h, g_w);


        # Discriminator
        d_h, d_w = self.x_dim[0], self.x_dim[1];
        num_dfs = [self.channels] + num_dfs;

        ks = d_kernel_size;
        self.D_kernel_sizes = [ks];

        for layer in range(len(d_strides)):
            assert d_strides[layer]<=2, "Invalid Stride";
            assert ks % 2 == 1, "Invalid Kernel Size";

            self.D_weight_dims["d_h"+str(layer)+"_W"] = (ks, ks, num_dfs[layer], num_dfs[layer+1]);
            self.D_weight_dims["d_h"+str(layer)+"_b"] = (num_dfs[layer+1],);
            d_h, d_w = conv_out_size(d_h, d_strides[layer]), conv_out_size(d_w, d_strides[layer]);
            ks = kernel_sizer(ks, d_strides[layer]);
            self.D_kernel_sizes.append(ks);

        self.D_weight_dims.update(OrderedDict([("d_h_end_lin_W", (num_dfs[-1] * d_h * d_w, num_dfs[-1])),
                                                ("d_h_end_lin_b", (num_dfs[-1],)),
                                                ("d_h_out_lin_W", (num_dfs[-1], self.K)),
                                                ("d_h_out_lin_b", (self.K,))]))

    def Discriminator(self, image, K, d_params, train=True):
        """
        Image
        => (Convolution => Batch Norm => Leaky ReLU)
        => (Convolution => Batch Norm => Leaky ReLU)
        => ......
        => Full connected => Leaky ReLU                 : h_end
        => Full connected                               : h_out = logit
        => output                                       : softmax(h_out) = prob
        :param image: image data
        :param K: output size of D (unsupervised : 2)
        :param d_params: Discriminator parameters for training/evaluation
        :param train: True for train(update the params) (why? Batch norm)
        :return: softmax(h_out), h_out, [h_end]
        """

        with tf.variable_scope("discriminator",reuse=tf.AUTO_REUSE) as scope:

            h = image;


            for layer in range(len(self.D_strides)):

                # self.D_weight_dims[layer_W] : (kernel_h, kernel_w, features in layer+1, features in layer)
                if layer == 0:
                    h = tf.nn.leaky_relu(conv2d(h,
                                                self.D_weight_dims["d_h" + str(layer) + "_W"][-1],
                                                name="d_h" + str(layer) + "_conv",
                                                k_h=self.D_kernel_sizes[layer],
                                                k_w=self.D_kernel_sizes[layer],
                                                d_h=self.D_strides[layer],
                                                d_w=self.D_strides[layer],
                                                w=d_params["d_h" + str(layer) + "_W"],
                                                biases=d_params["d_h" + str(layer) + "_b"]));
                else:
                    h = tf.nn.leaky_relu(self.D_batch_norm["d_bn"+str(layer)](
                        conv2d(h,
                               self.D_weight_dims["d_h" + str(layer) + "_W"][-1],
                               name="d_h" + str(layer) + "_conv",
                               k_h=self.D_kernel_sizes[layer],
                               k_w=self.D_kernel_sizes[layer],
                               d_h=self.D_strides[layer],
                               d_w=self.D_strides[layer],
                               w=d_params["d_h" + str(layer) + "_W"],
                               biases=d_params["d_h" + str(layer) + "_b"]),train=train));


            h_end = tf.nn.leaky_relu(linear(input_=tf.reshape(h, [self.batch_size, -1]),
                                            output_size=self.d_filter*4,
                                            scope="d_h_end_lin",
                                            matrix=d_params.d_h_end_lin_W,
                                            bias=d_params.d_h_end_lin_b));
            h_out = linear(input_=h_end, output_size=K,
                           scope="d_h_out_lin",
                           matrix=d_params.d_h_out_lin_W, bias=d_params.d_h_out_lin_b);

            return tf.nn.softmax(h_out), h_out, [h_end];

    def Generator(self, z, g_params):
        """
        Noise
        => Full connected
        => (Transpose Convolution => Batch norm => ReLU)
        => (Transpose Convolution => Batch norm => ReLU)
        => ......
        => Transpose Convolution
        => tanh(h)
        :param z: input noise
        :param g_params: Generator parameters for training/evaluation
        :return: generated image
        """

        with tf.variable_scope("generator",reuse=tf.AUTO_REUSE) as scope:
            h = linear(input_=z, output_size=self.G_weight_dims["g_h0_lin_W"][-1],
                       scope="g_h0_lin", matrix=g_params.g_h0_lin_W, bias=g_params.g_h0_lin_b);
            h = tf.nn.relu(self.G_batch_norm.g_bn0(h));

            h = tf.reshape(h, [self.batch_size, self.G_output_dims["g_h0_out"][0],
                               self.G_output_dims["g_h0_out"][1], -1]);

            for layer in range(1, len(self.G_strides)+1):
                # self.G_weight_dims[layer_W] : (kernel_h, kernel_w, features in layer+1, features in layer)
                # self.G_output_dims[layer] : (output_h, output_w)
                # out_shape = [batch, output_h, output_w, features in next layer]
                out_shape = [self.batch_size, self.G_output_dims["g_h"+str(layer)+"_out"][0],
                             self.G_output_dims["g_h" + str(layer) + "_out"][1],
                             self.G_weight_dims["g_h"+str(layer)+"_W"][-2]];

                h = deconv2d(input_=h,
                             output_shape=out_shape,
                             k_h=self.G_kernel_sizes[layer-1], k_w=self.G_kernel_sizes[layer-1],
                             d_h=self.G_strides[layer-1], d_w=self.G_strides[layer-1],
                             name="g_h"+str(layer),
                             w=g_params["g_h"+str(layer)+"_W"],
                             biases=g_params["g_h"+str(layer)+"_b"]);

                if layer < len(self.G_strides):
                    h = tf.nn.relu(self.G_batch_norm["g_bn"+str(layer)](h));


            return tf.nn.tanh(h);


    def _get_optimizer(self, lr):
        if self.optimizer == 'adam':
            return tf.train.AdamOptimizer(learning_rate=lr, beta1=0.5);
        elif self.optimizer =='sgd':
            return tf.train.MomentumOptimizer(learning_rate=lr, momentum=0.5);
        else:
            raise ValueError("Optimizer must be either 'adam' or 'sgd'");


    def initialize_weights(self, scope_str):
        """ Initialize the weights with normal distribution
        To use SGHMC algorithm, there are (# MC samples)*(# SGHMC samples) set of
        parameters in G/D
        :param scope_str: 'generator' or 'discriminator'
        :return: parameters list
        """

        if scope_str == "generator":
            weight_dims = self.G_weight_dims;
            numz = self.num_G
        elif scope_str == "discriminator":
            weight_dims = self.D_weight_dims;
            numz = self.num_D
        else:
            raise RuntimeError("invalid scope! : 'generator' or 'discriminator' ");

        param_list = [];

        with tf.variable_scope(scope_str,reuse=tf.AUTO_REUSE) as scope:
            # numz : MC samples
            for i in range(numz):
                # num_mcmc : SGHMC samples
                for m in range(self.num_mcmc):
                    wgts = AttributeDict();
                    for name, shape in weight_dims.items():
                        wgts[name] = tf.get_variable("%s_%04d_%04d" %(name, i, m),
                                                     shape,
                                                     initializer=tf.random_normal_initializer(stddev=0.02));
                    param_list.append(wgts);

            return param_list;

    def build_graph(self):
        """
        Make BDCGAN graph
        """

        """ Make input placeholders for D and G"""
        self.inputs = tf.placeholder(tf.float32,
                                     [self.batch_size] + self.x_dim,
                                     name="real_images");

        self.z = tf.placeholder(tf.float32,
                                [self.batch_size, self.z_dim, self.num_G], name="z");
        self.z_sampler = tf.placeholder(tf.float32,
                                        [self.batch_size, self.z_dim], name="z_sampler");

        """ Initialize Generator/Discriminator weights """
        self.G_param_list = self.initialize_weights("generator");
        self.D_param_list = self.initialize_weights("discriminator");

        """ Algorithm 1 : Second Iteration - Update params in D's
                        - 1) Make a list of variables of all D's to train
                        - 2) Make a list of learning rate 
        """
        self.D_learning_rate = tf.placeholder(tf.float32, shape=[]);

        train_vars = tf.trainable_variables();
        self.D_vars = [];

        for i in range(self.num_D):
            for m in range(self.num_mcmc):
                self.D_vars.append(
                    [var for var in train_vars if 'd_' in var.name and "_%04d_%04d" % (i, m) in var.name]);



        """ Algorithm 1 : Second Iteration - Update params in D's
                        - Make d_losses and optimizers
        """

        self.d_losses, self.d_train_ops, self.d_train_ops_adam = [], [], [];


        for di, d_params in enumerate(self.D_param_list):
            d_probs, d_logits, _ = self.Discriminator(self.inputs, self.K, d_params);


            # const_label[:, 1] = 1.0 <= data sampled from the real distribution
            const_labels = np.zeros((self.batch_size, self.K));
            const_labels[:, 1] = 1.0;

            # d_loss_real : same for DCGAN
            d_loss_real = tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(
                logits=d_logits, labels=tf.constant(const_labels)
            ));


            d_loss_fakes = [];
            """ Algorithm 1 : Second Iteration 
                - sum_{i,k} p(theta_d|z^{(i)}, theta_d^{k,m})
            """
            for gi, g_params in enumerate(self.G_param_list):
                # D(G(z))
                d_probs, d_logits, _ = self.Discriminator(self.Generator(self.z[:, :, gi % self.num_G], g_params),
                                                          self.K, d_params);
                # const_label[:, 0]=0.0 <= data sample from the fake distribution
                const_labels = np.zeros((self.batch_size, self.K));
                const_labels[:, 0] = 1.0;

                # d_fake_loss_ : same for DCGAN
                #              : there are J_G*num_MCMC(total number of G) d_fake_loss for each discriminator
                d_loss_fake_ = tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(
                    logits=d_logits, labels=tf.constant(const_labels)
                ));

                d_loss_fakes.append(d_loss_fake_);


            d_losses = [];
            for d_loss_fake_ in d_loss_fakes:
                # d_loss = d_real + d_loss in DCGAN
                # there is only one d_loss_real
                # there are num_G d_loss_fake
                #  => d_loss_real*float(self.num_G)
                d_loss_ = d_loss_real*float(self.num_G) + d_loss_fake_;


                if not self.DCGAN:
                    # SGHMC part : Add prior and noise
                    d_loss_ += self.D_prior(d_params) + self.D_noise(d_params);

                d_losses.append(tf.reshape(d_loss_, [1]));

            """
            tf.reduce_logsumexp(input_tensor, axis)
             :  log(sum(exp(elements across dimensions of a tensor)))
            """
            d_loss = tf.reduce_logsumexp(tf.concat(d_losses, 0));

            self.d_losses.append(d_loss);

            d_optimizer = self._get_optimizer(self.D_learning_rate);
            self.d_train_ops.append(
                d_optimizer.minimize(d_loss, var_list=self.D_vars[di]));
            d_optimizer_adam = tf.train.AdamOptimizer(learning_rate=self.D_learning_rate,
                                                      beta1=0.5);
            self.d_train_ops_adam.append(
                d_optimizer_adam.minimize(d_loss, var_list=self.D_vars[di]));


        """ REPEAT THE CODE for Algorithm 1 : Second Iteration w.r.t G"""
        """ Algorithm 1 : First Iteration - Update params in G's
                        - 1) Make a list of variables of all G's to train
                        - 2) Make a list of learning rate 
        """
        self.G_learning_rate = tf.placeholder(tf.float32, shape=[]);
        self.G_vars = [];

        for i in range(self.num_G):
            for m in range(self.num_mcmc):
                self.G_vars.append(
                    [var for var in train_vars if 'g_' in var.name and "_%04d_%04d" % (i, m) in var.name]);

        """ Algorithm 1 : First Iteration - Update params in G's
                        - Make g_losses and optimizers
        """
        self.g_losses, self.g_train_ops, self.g_train_ops_adam = [], [], [];

        for gi, g_params in enumerate(self.G_param_list):
            gi_losses = [];

            for d_params in self.D_param_list:
                # D(G(z))
                d_prob, d_logit, d_feature_fake = self.Discriminator(
                    self.Generator(self.z[:, :, gi % self.num_G], g_params),
                    self.K, d_params
                );
                _, _, d_feature_real = self.Discriminator(self.inputs, self.K, d_params);

                # const_label[:, 1] = 1.0 <= data sampled from the real distribution
                const_labels = np.zeros((self.batch_size, self.K));
                const_labels[:, 1] = 1.0;

                # g_loss_ : classic loss
                g_loss_ = tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(
                    logits=d_logit, labels=tf.constant(const_labels)
                ));

                g_loss_ += tf.reduce_mean(
                    huber_loss(d_feature_real[-1], d_feature_fake[-1]));

                if not self.DCGAN:
                    # SGHMC part : Add prior and noise
                    g_loss_ += self.G_prior(g_params) + self.G_noise(g_params);

                gi_losses.append(tf.reshape(g_loss_, [1]));

            """
               tf.reduce_logsumexp(input_tensor, axis)
               :  log(sum(exp(elements across dimensions of a tensor)))
            """
            g_loss = tf.reduce_logsumexp(tf.concat(gi_losses, 0));
            self.g_losses.append(g_loss);

            g_optimizer = self._get_optimizer(self.G_learning_rate);
            self.g_train_ops.append(
                g_optimizer.minimize(g_loss, var_list=self.G_vars[gi]));

            g_optimizer_adam = tf.train.AdamOptimizer(learning_rate=self.G_learning_rate,
                                                      beta1=0.5);
            self.g_train_ops_adam.append(
                g_optimizer_adam.minimize(g_loss, var_list=self.G_vars[gi]));




        """ Make samplers """
        self.G_sampler = [];

        for gi, g_params in enumerate(self.G_param_list):
            self.G_sampler.append(self.Generator(self.z_sampler, g_params));

    """ For g_loss and d_loss (Bayesian)"""

    def G_prior(self, g_params):
        """
        Let W be a weight parameter in g_params
        W_normal = W/prior_std (element wise)
        loss_W = average sum of square of entries of W_normal

        prior_loss = sum of loss_W along W : params in g_params

        """
        with tf.variable_scope("generator",reuse=tf.AUTO_REUSE) as scope:
            prior_loss = 0.0;
            for var in g_params.values():
                nn = tf.divide(var, self.prior_std);
                prior_loss += tf.reduce_mean(tf.multiply(nn, nn));

            prior_loss /= self.dataset_size;

            return prior_loss;

    def G_noise(self, g_params):
        """
        A noise for SGHMC
         : noise is sampled from N(0, self.noise_std)
           where self.noise_std = np.sqrt(2 * self.alpha * self.eta) (in Algorithm 1)

        To use gradient descent,
        define noise_loss = W*noise where W is a parameter in g_params
        """
        with tf.variable_scope("generator",reuse=tf.AUTO_REUSE) as scope:
            noise_loss = 0.0;

            for name, var in g_params.items():
                # noise_ ~ N(0, noise_std*shape of var)
                # noise_.sample() : a single sample from the noise
                noise_ = tf.contrib.distributions.Normal(loc=0., scale=self.noise_std*tf.ones(var.get_shape()));
                noise_loss += tf.reduce_mean(var*noise_.sample());

            noise_loss /= self.dataset_size;
            return noise_loss;

    def D_prior(self, d_params):
        with tf.variable_scope("discriminator",reuse=tf.AUTO_REUSE) as scope:
            prior_loss = 0.0;
            for var in d_params.values():
                nn = tf.divide(var, self.prior_std);
                prior_loss += tf.reduce_mean(tf.multiply(nn, nn));

            prior_loss /= self.dataset_size;

            return prior_loss;

    def D_noise(self, d_params):
        """
        A noise for SGHMC
          : noise is sampled from N(0, self.noise_std)
            where self.noise_std = np.sqrt(2 * self.alpha * self.eta) (in Algorithm 1)

        To use gradient descent,
        define noise_loss = W*noise where W is a parameter in g_params
        """
        with tf.variable_scope("discriminator",reuse=tf.AUTO_REUSE) as scope:
            noise_loss = 0.0;

            for name, var in d_params.items():
                # noise_ ~ N(0, noise_std*shape of var)
                # noise_.sample() : a single sample from the noise
                noise_ = tf.contrib.distributions.Normal(loc=0., scale=self.noise_std * tf.ones(var.get_shape()));
                noise_loss += tf.reduce_mean(var * noise_.sample());

            noise_loss /= self.dataset_size;
            return noise_loss;

    """ Information for the Network """
    def print_Weight_info(self):
        print("===============================================================")
        print(" Generator ");
        print(" 1. Weight dims");
        for k, v in self.G_weight_dims.items():
            print("{} : ".format(k), end=" ");
            print(v);
        print(" 2. kernel size ");
        print(self.G_kernel_sizes);

        print(" 3. output dims ");
        for k, v in self.G_output_dims.items():
            print("{} : ".format(k), end=" ");
            print(v);

        print(" 4. num_gfs ");
        print(self.num_g_features)
        print("===============================================================")
        print(" Discriminator");
        print(" 1. Weight dims");
        for k, v in self.D_weight_dims.items():
            print("{} : ".format(k), end=" ");
            print(v);
        print(" 2. kernel size ");
        print(self.D_kernel_sizes);

        print(" 3. num_dfs")
        print(self.num_d_features);
        print("===============================================================")





def get_session_MNIST():
    if tf.get_default_session() is None:
        print("Create new session");
        tf.reset_default_graph();
        _SESSION = tf.InteractiveSession();
    else:
        print("Use old session");
        _SESSION = tf.get_default_session();

    return _SESSION;



def BGAN_example_MNIST():
    """ Set the path to save the result"""
    data = "/MNIST/";
    path = "./GAN/BDCGAN/" + data;
    model_path = path + "model/";
    fig_path = path + "image/";

    if not os.path.exists(model_path):
        os.makedirs(model_path);

    if not os.path.exists(fig_path):
        os.makedirs(fig_path);

    z_dim = 100;
    g_filters = 64;
    d_filters = 96;
    batch_size = 64;
    num_layer = 4;
    J = 10;  # number of samples of z/generators
    J_d = 1;  # number of discriminator weight samples
    num_mcmc = 2;



    train_iter = 75000;
    base_lr = 0.005;
    lr_decay = 3.0;
    optimizer = 'sgd'

    n_save = 100;

    dataset = MNIST();
    x_dim = dataset.x_dim;
    datasize = dataset.dataset_size;

    random_seed = 2222;

    session = get_session_MNIST();
    tf.set_random_seed(random_seed);

    dcgan = BDCGAN(x_dim=x_dim, z_dim=z_dim,
                   batch_size=batch_size,dataset_size=datasize,
                   g_filter=g_filters, d_filter=d_filters,
                   J=J, J_d=J_d, M=num_mcmc, num_layer=num_layer,
                   lr=base_lr, optimizer=optimizer);

    print("BDCGAN : ");
    dcgan.print_Weight_info();

    print("Start session");
    session.run(tf.global_variables_initializer());

    optimizer_dict = {"D":dcgan.d_train_ops_adam,
                      "G":dcgan.g_train_ops_adam};

    num_D = J_d;
    saver = tf.train.Saver();

    for itr in range(train_iter):

        if itr == 5000:
            print("Switching to user-specified optimizer");
            optimizer_dict = {"D":dcgan.d_train_ops,
                              "G":dcgan.g_train_ops};

        learning_rate = base_lr*np.exp(-lr_decay*min(1.0, (itr*batch_size)/float(datasize)));

        image_batch, _ = dataset.next_batch(batch_size, class_id=None);

        # Compute d_loss
        batch_z = np.random.uniform(-1, 1, [batch_size, z_dim, dcgan.num_G]);
        d_info = session.run(optimizer_dict["D"] + dcgan.d_losses,
                             feed_dict={dcgan.inputs: image_batch,
                                        dcgan.z: batch_z,
                                        dcgan.D_learning_rate: learning_rate});

        d_losses = d_info[num_D:num_D*2];

        # Compute g_loss
        batch_z = np.random.uniform(-1, 1, [batch_size, z_dim, dcgan.num_G]);
        g_info = session.run(optimizer_dict["G"] + dcgan.g_losses,
                             feed_dict={dcgan.z: batch_z,
                                        dcgan.inputs: image_batch,
                                        dcgan.G_learning_rate: learning_rate});
        g_losses = [g_ for g_ in g_info if g_ is not None];


        if itr > 0 and itr % n_save == 0:
            print("Iteration: {}".format(itr));
            print("D loss : ");
            print(d_losses);
            print("G loss : ");
            print(g_losses);

            # results = {"d_losses": map(float, d_losses),
            #            "g_losses": map(float, g_losses),
            #            "timestamp": time.time()};

            saver.save(session, model_path+"model_" + str(itr) + ".ckpt");

            for zi in range(dcgan.num_G):
                _imgs, _ps = [], [];

                for _ in range(10):
                    z_sampler = np.random.uniform(-1, 1, size=(batch_size, z_dim));
                    sampled_imgs = session.run(dcgan.G_sampler[zi*dcgan.num_mcmc],
                                               feed_dict={dcgan.z_sampler: z_sampler});
                    _imgs.append(sampled_imgs);

                sampled_imgs = np.concatenate(_imgs);
                print_images(sampled_imgs,
                             "BDCGAN_%i_%.2f" % (zi, g_losses[zi * dcgan.num_mcmc]),
                             itr, fig_path);

            print_images(image_batch, "RAW", itr, fig_path);


















if __name__ == "__main__":
    print("My DCGAN");
    X = BDCGAN([28, 28, 1], 128, 60000, 64, g_filter=64, d_filter=96);
    # #X = BDCGAN([28, 28, 1], 128, 60000, 64, g_filter=64, d_filter=64);
    X.print_Weight_info();
    #BGAN_example_MNIST()
