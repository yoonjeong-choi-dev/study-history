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
warnings.filterwarnings(action='ignore', category=DeprecationWarning)





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
    # import matplotlib as mpl;
    # mpl.use("Agg");

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
        # import matplotlib as mpl
        # mpl.use("Agg");
        self.fig, self.axes = plt.subplots(*subplot_arg);

    def print_to_file(self, file_name, close_on_exit=True):
        # import matplotlib as mpl
        # mpl.use("Agg");

        self.fig.savefig(file_name, bbox_inches="tight");
        if close_on_exit:
            plt.close("all");






""" Functions for Full-connected layers """
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





class Synthetic_Dataset:

    def __init__(self, x_dim=100, num_clusters=10, random_seed=1234):

        if random_seed is not None:
            np.random.seed(random_seed);

        self.x_dim = x_dim;
        self.N = 10000;
        self.true_z_dim = 2;

        self.Xs = [];

        for _ in range(num_clusters):
            cluster_mean = np.random.randn(self.true_z_dim)*5;
            A = np.random.randn(self.x_dim, self.true_z_dim)*5;
            X = np.dot(np.random.randn(self.N//num_clusters, self.true_z_dim) + cluster_mean,
                       A.T);
            self.Xs.append(X);

        X_raw = np.concatenate(self.Xs);
        self.X = (X_raw - X_raw.mean(0)) / X_raw.std(0);
        print(self.X.shape);


    def next_batch(self, batch_size):
        rand_idx = np.random.choice(range(self.N), size=(batch_size, ), replace=False);
        return self.X[rand_idx];





class BDCGAN(object):
    def __init__(self, x_dim, z_dim, dataset_size, batch_size=64,
                 prior_std=1.0, J=1, M=1, num_classes=1, alpha=0.01,
                 lr=0.0002, optimizer="adam", ml=False):
        """
        ================================================================
        <Networks for Generator and Discriminator>
        :param x_dim: dim of input data(e.g mnist) for D
        :param z_dim: dim of input data(noise) for G
        :param dataset_size: the size of data in real data distribution
        :param batch_size: batch size for mini-batch training
        :param prior_std: Neural network prior std
        ================================================================
        # TODO
        <Hyper-parameters for SGHMC>
          : (Stochastic Gradient Hamiltonian Monte Carlo)
        :param J: the number of MC-samples of z to integrate in G (paper J_g)
        :param M: the number of samplings in SGHMC
        :param num_classes:
        :param alpha:
        :param lr: learning rate
        :param optimizer: optimizer
        :param ml: True for classic DCGAN
        """

        self.dataset_size = dataset_size;
        self.batch_size = batch_size;

        self.x_dim = x_dim;
        self.z_dim = z_dim;

        self.prior_std = prior_std;
        self.num_G = J;
        self.num_mcmc = M;
        self.alpha = alpha;

        self.lr = lr;
        self.optimizer = optimizer.lower();

        self.ml = ml;

        if self.ml:
            assert self.num_G*self.num_mcmc ==1, "cannot have multiple G's in ML mode";

        self.G_weight_dims = OrderedDict([("g_h0_lin_W", (self.z_dim, 1000)),
                                          ("g_h0_lin_b", (1000,)),
                                          ("g_lin_W", (1000, self.x_dim[0])),
                                          ("g_lin_b", (self.x_dim[0],))]);

        self.SGHMC_noise = {};
        self.noise_std = np.sqrt(2*self.alpha);

        for name, dim in self.G_weight_dims.items():
            self.SGHMC_noise[name] = tf.contrib.distributions.Normal(
                loc=0.,
                scale=self.noise_std*tf.ones(self.G_weight_dims[name]));

        self.K = num_classes;

        self.x_ = None;

        self.inputs = None;
        self.labeled_inputs = None;
        self.labels = None;
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

        self.D, self.D_logits = None, None;
        self.d_loss_real = None;

        self.generation = None;

        self.clip_d = None;


        self.build_graph();




    def _get_optimizer(self, lr):
        if self.optimizer == 'adam':
            return tf.train.AdamOptimizer(learning_rate=lr, beta1=0.5);
        elif self.optimizer =='sgd':
            return tf.train.MomentumOptimizer(learning_rate=lr, momentum=0.5);
        else:
            raise ValueError("Optimizer must be either 'adam' or 'sgd'");




    def Discriminator(self, x, K, reuse=False):
        with tf.variable_scope("discriminator") as scope:
            if reuse:
                scope.reuse_variables();
            h0 = tf.nn.leaky_relu(linear(x, 1000, "d_lin_0"));
            h1 = linear(h0, K, "d_lin_1");

            return tf.nn.softmax(h1), h1;


    def Generator(self, z, g_params):
        with tf.variable_scope("generator", reuse=tf.AUTO_REUSE) as scope:
        #with tf.variable_scope("generator") as scope:
            h0 = tf.nn.leaky_relu(linear(z, 1000, "g_h0_lin",
                                         matrix=g_params.g_h0_lin_W,
                                         bias=g_params.g_h0_lin_b));
            self.x_ = linear(h0, self.x_dim[0], 'g_lin',
                             matrix=g_params.g_lin_W,
                             bias=g_params.g_lin_b);

            return self.x_;


    def sampler(self, z, g_params):
        with tf.variable_scope("generator", reuse=tf.AUTO_REUSE) as scope:
            scope.reuse_variables();
            return self.Generator(z, g_params);

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
                noise_loss += tf.reduce_mean(var*self.SGHMC_noise[name].sample());

            noise_loss /= self.dataset_size;
            return noise_loss;

    def D_prior(self):
        with tf.variable_scope("discriminator",reuse=tf.AUTO_REUSE) as scope:
            prior_loss = 0.0;
            for var in self.D_vars:
                nn = tf.divide(var, self.prior_std);
                prior_loss += tf.reduce_mean(tf.multiply(nn, nn));

            prior_loss /= self.dataset_size;

            return prior_loss;

    def D_noise(self):
        """
        A noise for SGHMC
          : noise is sampled from N(0, self.noise_std)
            where self.noise_std = np.sqrt(2 * self.alpha * self.eta) (in Algorithm 1)

        To use gradient descent,
        define noise_loss = W*noise where W is a parameter in g_params
        """
        with tf.variable_scope("discriminator",reuse=tf.AUTO_REUSE) as scope:
            noise_loss = 0.0;

            for var in self.D_vars:
                # noise_ ~ N(0, noise_std*shape of var)
                # noise_.sample() : a single sample from the noise
                noise_ = tf.contrib.distributions.Normal(loc=0., scale=self.noise_std * tf.ones(var.get_shape()));
                noise_loss += tf.reduce_mean(var * noise_.sample());

            noise_loss /= self.dataset_size;
            return noise_loss;





    def build_graph(self):

        """ Make input placeholders for D and G"""
        self.inputs = tf.placeholder(tf.float32,
                                     [self.batch_size] + self.x_dim,
                                     name="real_images");
        self.labeled_inputs = tf.placeholder(tf.float32,
                                             [self.batch_size] + self.x_dim,
                                             name="real_images_w_labels");
        self.labels = tf.placeholder(tf.float32,
                                     [self.batch_size, self.K+1],
                                     name="real_targets");

        self.z = tf.placeholder(tf.float32,
                                [None, self.z_dim], name="z");



        self.G_param_list = [];

        with tf.variable_scope("generator", reuse=tf.AUTO_REUSE) as scope:
            for gi in range(self.num_G):
                for m in range(self.num_mcmc):
                    g_params = AttributeDict();

                    for name, shape in self.G_weight_dims.items():
                        g_params[name] = tf.get_variable("%s_%04d_%04d" % (name, gi, m),
                                                         shape,
                                                         initializer=tf.random_normal_initializer(stddev=0.02));
                    self.G_param_list.append(g_params);

        self.D, self.D_logits = self.Discriminator(self.inputs, self.K+1);

        const_labels = np.zeros((self.batch_size, 2));
        const_labels[:, 1] = 1.0;
        self.d_loss_real = tf.reduce_mean(
            tf.nn.softmax_cross_entropy_with_logits(
                logits=self.D_logits, labels=tf.constant(const_labels)
            )
        )

        self.generation = defaultdict(list);
        for g_params in self.G_param_list:
            self.generation["g_prior"].append(self.G_prior(g_params));
            self.generation["g_noise"].append(self.G_noise(g_params));
            self.generation["generators"].append(self.Generator(self.z, g_params));
            self.generation["gen_samplers"].append(self.sampler(self.z, g_params));
            D_, D_logits_ = self.Discriminator(self.Generator(self.z, g_params), self.K + 1, reuse=True);
            self.generation["d_logits"].append(D_logits_);
            self.generation["d_probs"].append(D_);


        d_loss_fakes = [];

        const_labels = np.zeros((self.batch_size, self.K+1));
        const_labels[:, 0] = 1.0;
        for d_logit in self.generation["d_logits"]:
            d_loss_fakes.append(
                tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(
                    logits=d_logit,
                    labels=tf.constant(const_labels)
                ))
            );

        train_vars = tf.trainable_variables();
        self.D_vars = [var for var in train_vars if "d_" in var.name];

        d_losses = [];

        for d_loss_fake in d_loss_fakes:
            d_loss_ = self.d_loss_real + d_loss_fake;
            if not self.ml:
                d_loss_ += self.D_prior() + self.D_noise();

            d_losses.append(tf.reshape(d_loss_, [1]));

        self.d_losses = tf.reduce_logsumexp(tf.concat(d_losses, 0));


        self.G_vars = [];
        for i in range(self.num_G):
            for m in range(self.num_mcmc):
                self.G_vars.append(
                    [var for var in train_vars if 'g_' in var.name and "_%04d_%04d" % (i, m) in var.name]);

        self.D_learning_rate = tf.placeholder(tf.float32, shape=[]);
        d_opt = self._get_optimizer(self.D_learning_rate);
        self.d_train_ops = d_opt.minimize(self.d_losses, var_list=self.D_vars);

        d_opt_adam = tf.train.AdamOptimizer(learning_rate=self.D_learning_rate,
                                            beta1=0.5);
        self.d_train_ops_adam = d_opt_adam.minimize(self.d_losses, var_list=self.D_vars);

        clip_d = [w.assign(tf.clip_by_value(w, -0.01, 0.01)) for w in self.D_vars];
        self.clip_d = clip_d;


        self.g_train_ops, self.g_train_ops_adam = [], [];
        self.G_learning_rate = tf.placeholder(tf.float32, shape=[]);

        for gi in range(self.num_G*self.num_mcmc):
            g_loss = -tf.reduce_mean(
                tf.log((1.0 - self.generation["d_probs"][gi][:, 0]) + 1e-8)
            );

            if not self.ml:
                g_loss += self.generation["g_prior"][gi] + self.generation["g_noise"][gi];

            self.generation["g_losses"].append(g_loss);

            g_opt = self._get_optimizer(self.G_learning_rate);
            self.g_train_ops.append(g_opt.minimize(g_loss, var_list=self.G_vars[gi]));

            g_opt_adam = tf.train.AdamOptimizer(learning_rate=self.G_learning_rate,
                                                beta1=0.5);
            self.g_train_ops_adam.append(g_opt_adam.minimize(g_loss, var_list=self.G_vars[gi]));





""" Synthetic Data Example"""
def gmm_mx(X):
    # a Gaussian mixture model probability distribution
    ret = [];
    #n_components_range = range(1, 20);
    for n_component in range(1, 20):
        gmm = mixture.GMM(n_components=n_component,
                          covariance_type="full");
        # Estimate model parameters with the EM algorithm
        # => Find maximum likelihood
        gmm.fit(X);
        # aic(X) : Akaike Information Criterion for the current model on X
        # AIC estimates the quality of each model, relative to each of the other models.
        ret.append(gmm.aic(X));

    return np.array(ret);



def analyze_div(real_X, sample_X):

    # Kullback-Leibler divergence
    def KL_div(p, q):
        # To avoid over-flow/round-off
        eps = 1e-10;
        p_safe = np.copy(p);
        p_safe[p_safe < eps] = eps;
        q_safe = np.copy(q);
        q_safe[q_safe <eps] = eps;
        return np.sum(p_safe*(np.log(p_safe) - np.log(q_safe)));

    # Jensen–Shannon divergence
    def JS_div(p, q):
        m = (p+q) / 2.;
        return (KL_div(p, m) + KL_div(q, m))/2.;


    from sklearn.decomposition import PCA
    pca = PCA(n_components=2);
    trans_real_X = pca.fit_transform(real_X);
    trans_fake_X = pca.transform(sample_X);

    from scipy import stats

    def cartesian_product(x, y):
        return np.dstack(np.meshgrid(x, y)).reshape(-1, 2);

    dx = 0.1;
    dy = 0.1;

    xmin1 = np.min(trans_real_X[:, 0]) - 3.0;
    xmax1 = np.max(trans_real_X[:, 0]) + 3.0;

    xmin2 = np.min(trans_real_X[:, 1]) - 3.0;
    xmax2 = np.max(trans_real_X[:, 1]) + 3.0;

    space = cartesian_product(np.arange(xmin1, xmax1, dx),
                              np.arange(xmin2, xmax2, dy)).T;

    """
    stats.gaussian_kde(data) 
        : Representation of a kernel-density estimate using Gaussian kernels.
    Kernel density estimation is a way to estimate the probability density function (PDF) 
    of a random variable in a non-parametric way
    """

    real_kde = stats.gaussian_kde(trans_real_X.T);
    real_density = real_kde(space) *dx*dy;

    fake_kde = stats.gaussian_kde(trans_fake_X.T);
    fake_density = fake_kde(space) *dx*dy;

    return JS_div(real_density, fake_density), trans_real_X, trans_fake_X;


def get_session_Synth():
    global _SESSION
    if tf.get_default_session() is None:
        _SESSION = tf.InteractiveSession();
    else:
        _SESSION = tf.get_default_session();

    return _SESSION;


def BGAN_example_synth(synth_dataset, z_dim=10, batch_size=64, numz=10,
                       num_itr=1000,
                       base_lr=0.01, lr_decay=3., save_weight=False):


    if numz == 1:
        data = "/Synthetic/";
        path = "./GAN/BDCGAN/" + data;
        model_path = path + "model/Classic/";
        fig_path = path + "image/Classic/";
    else:
        data = "/Synthetic/";
        path = "./GAN/BDCGAN/" + data;
        model_path = path + "model/Bayes/";
        fig_path = path + "image/Bayes/";



    if not os.path.exists(model_path):
        os.makedirs(model_path);

    if not os.path.exists(fig_path):
        os.makedirs(fig_path);

    bgan = BDCGAN([synth_dataset.x_dim], z_dim,
                  synth_dataset.N, batch_size=batch_size,
                  prior_std=10.0, alpha=1e-3,
                  J=numz, M=1, ml=(numz==1),
                  num_classes=1
                  );

    print("Starting session");
    session = get_session_Synth();
    tf.global_variables_initializer().run();

    num_train_iter = num_itr;

    sample_z = np.random.uniform(-1, 1, size=(batch_size, z_dim));

    all_aics_fake, all_data_fake, all_dists = [], [], [];


    saver = tf.train.Saver();
    for train_itr in range(num_train_iter):

        learning_rate = base_lr*np.exp(-lr_decay*
                                       min(1.0, (train_itr*batch_size)/float(synth_dataset.N)));


        batch_z = np.random.uniform(-1, 1, [batch_size, z_dim]);

        input_batch = synth_dataset.next_batch(batch_size);

        _, d_loss = session.run([bgan.d_train_ops, bgan.d_losses],
                                feed_dict={bgan.inputs: input_batch,
                                           bgan.z: batch_z,
                                           bgan.D_learning_rate: learning_rate});

        g_losses = [];

        for gi in range(bgan.num_G):

            batch_z = np.random.uniform(-1, 1, [batch_size, z_dim]);
            _, g_loss = session.run([bgan.g_train_ops[gi], bgan.generation["g_losses"][gi]],
                                    feed_dict={bgan.z: batch_z,
                                               bgan.G_learning_rate: learning_rate});

            g_losses.append(g_loss);


        if (train_itr % 100) == 0:
            print("Iteration: {}".format(train_itr));
            print("D loss : ");
            print(d_loss);
            print("G loss : ");
            print(g_losses);

            saver.save(session, model_path+"model_" + str(train_itr) + ".ckpt");

            fake_data = [];

            for num_samples in range(10):
                for gi in range(bgan.num_G):
                    sample_z = np.random.uniform(-1, 1, size=(batch_size, z_dim));
                    sampled_data = session.run(bgan.generation["gen_samplers"][gi], feed_dict={bgan.z: sample_z});
                    fake_data.append(sampled_data);

            real_X = synth_dataset.X;
            sample_X = np.concatenate(fake_data);

            all_data_fake.append(sample_X);

            aics_fake = gmm_mx(sample_X);
            print("Fake number of clusters (AIC estimate) : {}".format(aics_fake.argmin()));

            dist, trans_real_X, trans_fake_X = analyze_div(real_X, sample_X);
            print("Jensen–Shannon divergence : {}".format(dist));

            fp = FigPrinter((1,2));
            xmin1 = np.min(trans_real_X[:, 0]) - 1.0;
            xmax1 = np.max(trans_real_X[:, 0]) + 1.0;

            xmin2 = np.min(trans_real_X[:, 1]) - 1.0;
            xmax2 = np.max(trans_real_X[:, 1]) + 1.0;


            fp.axes[0].plot(trans_real_X[:, 0], trans_real_X[:, 1], ".r");
            fp.axes[0].set_xlim([xmin1, xmax1]);
            fp.axes[0].set_ylim([xmin2, xmax2]);

            fp.axes[1].plot(trans_fake_X[:, 0], trans_fake_X[:, 1], '.g')
            fp.axes[1].set_xlim([xmin1, xmax1]);
            fp.axes[1].set_ylim([xmin2, xmax2]);

            fp.axes[0].set_aspect("equal", adjustable="box");
            fp.axes[1].set_aspect("equal", adjustable="box");
            fp.axes[1].set_title("Iter {}".format(train_itr));
            fp.print_to_file(os.path.join(fig_path,"pca_distribution_%i_%i.png" % (numz, train_itr)));

            all_aics_fake.append(aics_fake)
            all_dists.append(dist)

    print("end")
    return {"data_fake": all_data_fake,
            "data_real": synth_dataset.X,
            "z_dim": z_dim,
            "numz": numz,
            "num_iter": num_itr,
            "divergences": all_dists,
            "all_aics_fake": np.array(all_aics_fake)}





def BGAN_example_synth_train():
    x_dim = 100;
    z_dim = 2;
    train_iter = 1000;
    numz = 10;
    random_seed = 2222;

    np.random.seed(random_seed);
    tf.set_random_seed(random_seed);

    data = "/Synthetic/";
    path = "./GAN/BDCGAN/" + data;
    result_path = path + "result/";

    if not os.path.exists(result_path):
        os.makedirs(result_path);


    datasets = Synthetic_Dataset(x_dim);

    results = BGAN_example_synth(datasets, z_dim,
                                 num_itr=train_iter,
                                 numz=numz);

    np.savez(os.path.join(result_path, "run_bayes.npz"),**results);


def Classic_GAN_example_synth_train():
    x_dim = 100;
    z_dim = 2;
    train_iter = 1000;
    numz = 1;
    random_seed = 2222;

    np.random.seed(random_seed);
    tf.set_random_seed(random_seed);

    data = "/Synthetic/";
    path = "./GAN/BDCGAN/" + data;
    result_path = path + "result/";

    if not os.path.exists(result_path):
        os.makedirs(result_path);

    datasets = Synthetic_Dataset(x_dim);

    results = BGAN_example_synth(datasets, z_dim,
                                 num_itr=train_iter,
                                 numz=numz);

    np.savez(os.path.join(result_path, "run_classic.npz"), **results);





def Compare_result():
    data = "/Synthetic/";
    path = "./GAN/BDCGAN/" + data;
    result_path = path + "result/";
    bgan_path = result_path+"run_bayes.npz";
    classic_path = result_path+"run_classic.npz";

    bgan = np.load(bgan_path);
    classic = np.load(classic_path);

    div_bgan = bgan["divergences"];
    div_classic = classic["divergences"];

    fake_bgan = bgan["all_aics_fake"];
    fake_classic = classic["all_aics_fake"];

    fake_num_bgan = [];
    fake_num_classic = [];

    for i in range(fake_bgan.shape[0]):
        fake_num_bgan.append(fake_bgan[i].argmin());
        fake_num_classic.append(fake_classic[i].argmin());

    print("1. Bayesian GAN")
    print("Jensen–Shannon divergence :");
    print(div_bgan);
    # print("Fake number of clusters (AIC estimate) :")
    # print(fake_num_bgan);
    print("==============================================");
    print("2. Classic GAN")
    print("Jensen–Shannon divergence :");
    print(div_classic);

    plt.figure();
    plt.plot(div_bgan, "r-", label="Bayes");
    plt.plot(div_classic, "b-", label="Classic");
    plt.legend();
    plt.show();







































































if __name__ =="__main__":
    print("Bayesian DCGAN for synthetic data");

    #BGAN_example_synth_train()
    #Classic_GAN_example_synth_train();
    Compare_result();