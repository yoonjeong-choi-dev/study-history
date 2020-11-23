from CommonFunction import *
from Util import *
"""
Activation Layer for Hidden Layers
1. Relu
2. Sigmoid
"""

class ReLU:
    def __init__(self):
        self.mask = None;  # save the input value

    def forward(self, x):
        self.mask = (x <= 0);  # mask[iter] = true if x[iter]<=0 // false if x[iter]>=0
        out = x.copy();
        out[self.mask] = 0;  # out[iter] = 0 if x[iter]<=0
        return out;

    def backward(self, dout):
        dout[self.mask] = 0;
        dx = dout;
        return dx;

class Sigmoid:
    def __init__(self):
        self.out = None;  # save the output value

    def forward(self, x):
        out = 1 / (1 + np.exp(-x));
        self.out = out;

        return out;

    def backward(self, dout):
        # a benefit of sigmoid : derivative can be expressed by sigmoid function i.e the output
        dx = dout * self.out * (1 - self.out);

        return dx;

"""
Affine Layer for fully connected network
"""
class Affine:
    # handle the matrix multiplication of weight matrix
    # Y = np.dot(X, W) + b
    def __init__(self, W, b):
        self.W = W;
        self.b = b;

        # Temp variable for Back propagation
        self.x = None;
        self.original_x_shape = None;

        # partial derivatives of parameters W and b
        self.dW = None;
        self.db = None;

    def forward(self, x):
        # x can be a tensor
        self.original_x_shape = x.shape;


        # Transfer x to a matrix so that we can calculate Affine map
        # x.shape : (a_1,a_2,...,a_n)  => self.x.shape : (a_1, a_2*a_3*...*a_n)
        # e.g x is a batch and x[data] is a form of matrix
        x = x.reshape(x.shape[0], -1);
        self.x = x;

        out = np.dot(x, self.W) + self.b;

        return out;

    def backward(self, dout):
        dx = np.dot(dout, self.W.T);
        self.dW = np.dot(self.x.T, dout);
        self.db = np.sum(dout, axis=0);

        # Reshape x to original shape because x has been transferred in forward procedure
        dx = dx.reshape(*self.original_x_shape)

        return dx;


"""
Softmax Layer for the last output layer
"""
class SoftmaxWithLoss:
    # composition of Softmax and Cross entropy error
    def __init__(self):
        self.loss = None;
        self.y = None;  # output of softmax
        self.t = None;  # real label (one-hot vector)

    def forward(self, x, t):
        self.t = t;
        self.y = softmax(x);

        self.loss = cross_entropy_error(self.y, self.t);

        return self.loss;

    def backward(self, dout=1):
        batch_size = self.t.shape[0];  # t.shape = (batch size, number of labels)

        # if the label self.t is of the form - one hot encoding
        if self.t.size == self.y.size:
            dx = (self.y - self.t) / batch_size;
        # if the label self.t is not one-hot encoder
        else:
            dx= self.y.copy();
            dx[np.arange(batch_size), self.t] -= 1;
            dx = dx / batch_size;

        return dx;

"""
Technique to avoid Over-fitting
1. BatchNormalization
2. Dropout

3. Weight_decay(defined in the MultilayerNet) 
"""
class BatchNormalization:
    """ Reference :
        - http://arxiv.org/abs/1502.03167
        - https://shuuki4.wordpress.com/2016/01/13/batch-normalization-%EC%84%A4%EB%AA%85-%EB%B0%8F-%EA%B5%AC%ED%98%84/
    Normalize the data so that the distribution ~ N(0, 1)

    Algorithm:
    1. mini batch mean
        - running_mean = mean of mini batch data
    2. mini batch variance
        - running_var = variance of mini batch data
    3. normalize
        - x'[i] = (x[i] - mean) / sqrt(var + epsil)
    4. scaling and shifting : to avoid constraint of expression(표현력 제한)
        - y[i] = gamma*x'[i] + beta

    Summary:
    1. For training, normalize by mean and variance of mini batch
    2. For testing, transform the data by scale factor(gamma) and shift factor(beta)

    Method:
    1.forward(self, x, train_flag=True)
        - train_flag = true for training(update parameter) / false for test(accuracy)
    """
    def __init__(self, gamma, beta, momentum=0.9, running_mean=None, running_var=None):
        self.gamma = gamma;         # scale factor
        self.beta = beta;           # shift factor
        self.momentum = momentum;   # the ratio for remaining self.running_mean and self.running_var
        self.input_shape = None;    # CNN_layer=4, Complete connected layer=2

        # mean and variable for testing e.g get accuracy
        self.running_mean = running_mean;
        self.running_var = running_var;

        # temporary data for backward propagation
        self.batch_size = None;
        self.x_center = None;     # (x - mean)
        self.std = None;
        self.dgamma = None;
        self.dbeta = None;


    def __forward(self, x, train_flag):
        """
        a temporary method for forward
        :param x: input data (not for CNN)
        :param train_flag: true(for updating params) / false(for testing)
        :return: forward propagation
        """
        if self.running_mean is None:
            N, D = x.shape;
            self.running_mean = np.zeros(D);
            self.running_var = np.zeros(D);

        if train_flag:
            mu = x.mean(axis=0);
            x_center = x - mu;
            var = np.mean(x_center**2, axis=0);
            std = np.sqrt(var + 10e-7);
            x_normalized = x_center/std;

            self.batch_size = x.shape[0];
            self.x_center = x_center;
            self.std = std;
            self.x_normalized = x_normalized;
            self.running_mean = self.momentum*self.running_mean + (1-self.momentum)*mu;
            self.running_var = self.momentum*self.running_var+(1-self.momentum)*var;

        else:
            x_center = x - self.running_mean;
            x_normalized = x_center/(np.sqrt(self.running_var + 10e-7));


        out = self.gamma*x_normalized + self.beta;
        return out;


    def forward(self, x, train_flag=True):
        """
        :param x: input data (also for CNN)
        :param train_flag: true(for updating params) / false(for testing)
        :return: forward propagation
        """
        self.input_shape = x.shape;
        #if x is a tensor i.e a layer for CNN
        if x.ndim !=2:
            N, C, H, W = x.shape;
            x = x.reshape(N, -1);

        out = self.__forward(x, train_flag);
        return out.reshape(*self.input_shape);

    def __backward(self, dout):
        """
        :param dout: derivative for output layer (not for CNN)
        :return: backward propagation
        """
        dbeta = dout.sum(axis=0);
        dgamma = np.sum(self.x_normalized*dout, axis=0);

        dx_normalized = self.gamma*dout;
        dx_center = dx_normalized / self.std;
        dstd = -np.sum((dx_normalized * self.x_center) / (self.std * self.std), axis=0);
        dvar = 0.5 * dstd / self.std;
        dx_center += (2.0 / self.batch_size) * self.x_center * dvar;
        dmu = np.sum(dx_center, axis=0);
        dx = dx_center - dmu / self.batch_size;

        self.dgamma = dgamma;
        self.dbeta = dbeta;

        return dx;

    def backward(self, dout):
        """
        :param dout: derivative for output layer (also for CNN)
        :return: backward propagation
        """
        # if x is a tensor i.e a layer for CNN
        if dout.ndim != 2:
            N, C, H, W = dout.shape;
            dout = dout.reshape(N, -1);

        dx = self.__backward(dout);

        dx.reshape(*self.input_shape);

        return dx;


class Dropout:
    """
    Reference:
       - http://arxiv.org/abs/1207.0580

    Idea :
        - For training, select some neurons in the hidden layer randomly
        - For testing, use all neurons in the hidden layer
        - For testing, multiply ratio of deletion(1-dropout_ratio) into output of each neurons in the hidden layer
    """
    def __init__(self, dropout_ratio=0.5):
        self.dropout_ratio = dropout_ratio;
        self.mask = None;

    def forward(self, x, train_flag=True):
        # For training
        if train_flag:
            self.mask = np.random.rand(*x.shape) > self.dropout_ratio;
            return x * self.mask;
        # For testing
        else:
            return x*(1.0 - self.dropout_ratio);

    def backward(self, dout):
        return dout*self.mask;




"""
Layers for CNN
1. Convolution Layer
2. MaxPooling Layer 
"""
class Convolution:
    def __init__(self, W, b, stride=1, padding=0):
        # filter information
        self.W = W;
        self.b = b;
        self.stride = stride;
        self.padding = padding;

        # temp data (for backward propagation)
        self.x = None;  # input data(4-dim)
        self.col = None;  # flattened input data(2-dim)
        self.col_W = None;  # flattened filter

        # gradients for parameters
        self.dW = None;
        self.db = None;

    def forward(self, x):
        """
        x : 4-dimensional tensor
        """
        FN, C, FH, FW = self.W.shape;
        N, C, H, W = x.shape;
        OH = 1 + int((H + 2*self.padding - FH) / self.stride);
        OW = 1 + int((W + 2*self.padding - FW) / self.stride);

        # flatten the input x into 2-dimension array
        col = im2col(x, FH, FW, self.stride, self.padding);

        # flatten the filter
        col_W = self.W.reshape(FN, -1).T;

        # Compute the convolution of x and the filters
        # col[data, output][channel, filter]
        out = np.dot(col, col_W) + self.b;

        # Transform the output into 4-dim tensor
        out = out.reshape(N, OH, OW, -1);

        # out[data][row][col][channel] => out[data][channel][row][col]
        out = out.transpose(0, 3, 1, 2);

        # Save temp data for backpropagation
        self.x = x;
        self.col = col;
        self.col_W = col_W;

        return out;

    def backward(self, dout):
        """
        Similar to the backward method of Affine class
        i.e
        def backward(self, dout):
            dx = np.dot(dout, self.W.T);
            self.dW = np.dot(self.x.T, dout);
            self.db = np.sum(dout, axis=0);

            # Reshape x to original shape because x has been transferred in forward procedure
            dx = dx.reshape(*self.original_x_shape)

            return dx;
        """
        FN, C, FH, FW = self.W.shape;

        # Flatten dout
        dout = dout.transpose(0, 2, 3, 1);
        dout = dout.reshape(-1, FN);

        # Affine : self.db = np.sum(dout, axis=0);
        self.db = np.sum(dout, axis=0);

        # Affine : self.dW = np.dot(self.x.T, dout)
        self.dW = np.dot(self.col.T, dout);

        # Since self.dW has data in each col, we have to transpose self.dW so that it has data in each row
        self.dW = self.dW.transpose(1, 0);

        # Transform self.dw to a 4-dimensional tensor
        self.dW = self.dW.reshape(FN, C, FH, FW);

        # Affine : dx = np.dot(dout, self.W.T)
        dcol = np.dot(dout, self.col_W.T);

        # Affine : dx = dx.reshape(*self.original_x_shape)
        dx = col2im(dcol, self.x.shape, FH, FW, self.stride, self.padding);

        return dx;


class MaxPooling:
    def __init__(self, pool_height, pool_width, stride=1, padding=0):
        """
        :param pool_height: height of pooling window
        :param pool_width: width of pooling window
        :param stride: stride = size(length) of pooling window in general
        :param padding:
        -----------------------------------------------------------------
        1. There are no parameters to train
        2. The number of channels in input data remains the same
        """
        self.pool_h = pool_height;
        self.pool_w = pool_width;
        self.stride = stride;
        self.padding = padding;

        self.x = None;
        self.arg_max = None;

    def forward(self, x):
        """
        x : 4-dimensional tensor
        """
        N, C, H, W = x.shape;
        OH = int(1 + (H - self.pool_h) / self.stride);
        OW = int(1 + (W - self.pool_w) / self.stride);

        # flatten the input x into 2-dimension array
        col = im2col(x, self.pool_h, self.pool_w, self.stride, self.padding);

        # flatten each window of the input as a row
        col = col.reshape(-1, self.pool_h * self.pool_w);

        # Max Pooling : max element along the row
        arg_max = np.argmax(col, axis=1);
        out = np.max(col, axis=1);

        # Transform the output into 4-dim tensor
        out = out.reshape(N, OH, OW, C);

        # out[data][row][col][channel] => out[data][channel][row][col]
        out = out.transpose(0, 3, 1, 2);

        # Save temp data for backpropagation
        self.x = x;
        self.arg_max = arg_max;

        return out;

    def backward(self, dout):
        """
        Similar to the backward method of ReLU class
        i.e
        def backward(self, dout):
            dout[self.mask] = 0;
            dx = dout;
            return dx;
        """

        dout = dout.transpose(0, 2, 3, 1);

        pool_size = self.pool_h * self.pool_w;

        dmax = np.zeros((dout.size, pool_size));
        dmax[np.arange(self.arg_max.size), self.arg_max.flatten()] = dout.flatten();

        dmax = dmax.reshape(dout.shape + (pool_size,));

        dcol = dmax.reshape(dmax.shape[0] * dmax.shape[1] * dmax.shape[2], -1);
        dx = col2im(dcol, self.x.shape, self.pool_h, self.pool_w, self.stride, self.padding);

        return dx;
















