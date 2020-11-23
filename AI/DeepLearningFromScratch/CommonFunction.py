import numpy as np

# Activation function for hidden layers
def step_function(x):
    y = x > 0;
    return y.astype(np.int);

def sigmoid(x):
    return 1/(1+np.exp(-x));

def relu(x):
    return np.maximum(0,x);

def identity_function(x):
    """ Use for Regression
    :param x: vector
    :return: x
    """
    return x;

# Activation function for the output layer
def softmax(x):
    """ use for Classification
        :param x: vector
        :return: vector of softmax
        """
    if x.ndim == 2:
        x = x.T;
        x = x - np.max(x, axis=0);
        y = np.exp(x) / np.sum(np.exp(x), axis=0);      # y[i] = softmax(x[i]) when x[i].ndim == 1
        return y.T;

    x = x - np.max(x);    # to avoid overflow
    return np.exp(x) / np.sum(np.exp(x));




# Loss Function
def mean_squared_error(y, t):
    return 0.5*np.sum((y-t)**2);

def cross_entropy_error(y, t):


    if y.ndim == 1:
        t = t.reshape(1, t.size);
        y = y.reshape(1, y.size);
    delta = 1e-7;        # to avoid log(0)


    #error = -np.sum(t * np.log(y + delta))/batch_size if t is one-hot encoding

    #if t is one-hot encoding
    if y.size==t.size:
        t = t.argmax(axis=1);
    batch_size = y.shape[0];

    # Now we just consider y[0~batch_size-1][t] where t is a array of len batch_size
    # i.e y[i][t[i]] for i=0~batch_size-1


    return -np.sum(np.log(y[np.arange(batch_size), t]+delta)) / batch_size;

def loss_function_example():
    t = np.array([0,0,1,0,0,0,0,0,0,0]);
    y1 = np.array([0.1,0.05,0.6,0.0,0.05,0.1,0.0,0.1,0.0,0.0]);
    y2 = np.array([0.1,0.05,0.1,0.0,0.05,0.1,0.0,0.6,0.0,0.0]);

    print("mean_squared_error : ");
    print(mean_squared_error(y1, t));
    print(mean_squared_error(y2, t));
    print("cross_entropy_error : ");
    print(cross_entropy_error(y1, t));
    print(cross_entropy_error(y2, t));

