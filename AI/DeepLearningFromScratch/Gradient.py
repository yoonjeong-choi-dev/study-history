import numpy as np
import matplotlib.pyplot as plt



# Gradient
def _numerical_gradient_1d(f, x):
    """
    :param f: a function
    :param x: a point which is an input of f
    :return: gradient of f at x
    """
    h = 1e-4;
    grad = np.zeros_like(x);

    # differentiate f w.r.t x_idx
    for idx in range(x.size):
        tmp_val = x[idx]
        # f(x+h)
        x[idx] = tmp_val + h;
        fxh1 = f(x);

        # f(x-h)
        x[idx] = tmp_val - h;
        fxh2 = f(x);

        grad[idx] = (fxh1 - fxh2) / (2*h);
        x[idx] = tmp_val;

    return grad;

def numerical_gradient_2d(f, X):
    """
    :param f: a function
    :param X: a list of points which are inputs of f
    :return: a list of gradients of f at X
    """
    # if X is a vector
    if X.ndim == 1:
        return _numerical_gradient_1d(f, X);
    else:
        grad = np.zeros_like(X);
        for idx, x in enumerate(X):
            grad[idx] = _numerical_gradient_1d(f, x);

        return grad

def numerical_gradient(f, W):
    """
    :param f: a function
    :param W: a matrix
    :return: a matrix whose entries are partial derivatives of f w.r.t W
    """
    h = 1e-4;
    grad = np.zeros_like(W);

    # iterator of W
    itr = np.nditer(W, flags=['multi_index'], op_flags=['readwrite']);

    while not itr.finished:
        idx = itr.multi_index;
        tmp_val = W[idx];

        # f(x+h)
        W[idx] = float(tmp_val) + h;
        fxh1 = f(W);

        # f(x-h)
        W[idx] = float(tmp_val) - h;
        fxh2 = f(W);

        grad[idx] = (fxh1 - fxh2) / (2*h);
        W[idx] = tmp_val;
        itr.iternext();

    return grad;


# Gradient Descent
def gradient_descent(f, init_x, learning_rate=0.01, step_num=100):
    """
    :param f: function
    :param init_x: starting point
    :param learning_rate: learning rate
    :param step_num: the number of iteration
    :return: point that minimizes f
    """
    x = init_x;
    x_history = [];     # save the move
    for i in range(step_num):
        x_history.append(x.copy());

        grad = numerical_gradient_2d(f, x);
        x = x - learning_rate*grad;
    return x, np.array(x_history);







"""
Example
"""
def numerical_gradient_example():

    def func(x):
        if x.ndim==1:
            return np.sum(x**2);
        else:
            return np.sum(x**2, axis=1);

    x0 = np.arange(-2,2.5,0.25);
    x1 = np.arange(-2, 2.5, 0.25);
    X, Y = np.meshgrid(x0, x1);

    X = X.flatten();
    Y = Y.flatten();

    grad = numerical_gradient_2d(func, np.array([X, Y]));

    plt.figure();
    plt.quiver(X, Y, -grad[0], -grad[1], angles="xy", color="#666666");
    plt.xlim([-2, 2]);
    plt.ylim([-2,2]);
    plt.xlabel('x0'); plt.ylabel('y0');
    plt.grid();
    plt.legend();
    plt.draw();
    plt.show();

def _gradient_descent_example():
    def func(x):
        return x[0]**2 + x[1]**2;

    init_x = np.array([-3.0, 4.0]);
    x_01, his_01 = gradient_descent(func, init_x, 0.1,100);
    x_10, his_10 = gradient_descent(func, init_x, 10.0, 100);
    x_000001, his_0000001 = gradient_descent(func, init_x, 1e-10, 100);
    print("learning rate : 0.01");
    print(x_01);
    print("learning rate : 10.0");
    print(x_10);
    print("learning rate : 1e-10");
    print(x_000001);

    #draw graph
    fig, axes = plt.subplots(1, 3,figsize=(18, 6));
    fig.suptitle("Gradient descent with different learning rate");
    axes[0].plot([-5, 5], [0, 0], '--b');
    axes[0].plot([0,0],[-5,5], '--b');
    axes[0].plot(his_01[:,0],his_01[:,1], 'o');
    axes[1].plot([-5, 5], [0, 0], '--b');
    axes[1].plot([0, 0], [-5, 5], '--b');
    axes[1].plot(his_10[:,0], his_10[:,1], 'o');
    axes[2].plot([-5, 5], [0, 0], '--b');
    axes[2].plot([0, 0], [-5, 5], '--b');
    axes[2].plot(his_0000001[:,0], his_0000001[:,1], 'o');

    for i in range(3):
        axes[i].set_xlim(-5, 5);
        axes[i].set_ylim(-5,5);
        axes[i].set_xlabel("X0");
        axes[i].set_ylabel("X1");

    plt.show();