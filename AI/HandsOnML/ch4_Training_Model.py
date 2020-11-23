from __future__ import division, print_function, unicode_literals

import os

import numpy as np
import matplotlib.pyplot as plt
import matplotlib



""" Useful function """
# Save the graph
def save_fig(fig_id, tight_layout=True):
    PROJECT_ROOT_DIR = ".";
    CHAPTER_ID = "training_linear_models";


    path = os.path.join(PROJECT_ROOT_DIR, "My_images", CHAPTER_ID, fig_id+".png");
    if tight_layout:
        plt.tight_layout();

    if not (os.path.isdir(os.path.join(PROJECT_ROOT_DIR, "My_images", CHAPTER_ID))):
        os.makedirs(os.path.join(PROJECT_ROOT_DIR, "My_images", CHAPTER_ID));

    plt.savefig(path, format='png', dpi=300);
    print("figure is saved...........................!")



def normal_equation():

    theta = [4, 3];
    x = 2 * np.random.rand(100, 1);
    y = theta[0] + theta[1]* x + np.random.randn(100, 1);  # y = 3x+4 + noise

    # Add x_0=1 to each sample
    x_b = np.c_[np.ones((100, 1)), x];

    # theta_best = (X.T * X).inverse * X.T * y
    theta_best = np.linalg.inv(x_b.T.dot(x_b)).dot(x_b.T).dot(y);

    print("The actual parameter : {}".format(theta));
    print("The best parameter : {}, {}".format(theta_best[0], theta_best[1]));

    x_new = np.array([[0], [2]]);
    x_new_b = np.c_[np.ones((2, 1)), x_new];
    y_predict = x_new_b.dot(theta_best);

    plt.plot(x, y, "o", label="noisy data");
    plt.plot(x_new, y_predict, "r-", label="predict");
    plt.axis([0, 2, 0, 15]);
    plt.legend();

    save_fig("normal_equation_example");

    plt.show();


def normal_equation_scikit():
    from sklearn.linear_model import LinearRegression

    theta = [4, 3];
    x = 2 * np.random.rand(100, 1);
    y = theta[0] + theta[1] * x + np.random.randn(100, 1);  # y = 3x+4 + noise

    lin_reg = LinearRegression();
    lin_reg.fit(x, y);

    print("The actual parameter : {}".format(theta));
    print("The best parameter : {}, {}".format(lin_reg.intercept_, lin_reg.coef_));

    x_new = np.array([[0], [2]]);
    y_predict = lin_reg.predict(x_new);

    plt.plot(x, y, "o", label="noisy data");
    plt.plot(x_new, y_predict, "r-", label="predict");
    plt.axis([0, 2, 0, 15]);
    plt.legend();

    save_fig("linear_regression_example");

    plt.show();


def gradient_descent_example():

    theta = [4, 3];
    x = 2 * np.random.rand(100, 1);
    y = theta[0] + theta[1] * x + np.random.randn(100, 1);  # y = 3x+4 + noise

    # Add x_0=1 to each sample
    x_b = np.c_[np.ones((100, 1)), x];



    learning_rate = 0.1;
    n_iter = 1000;
    m = x.shape[0];

    theta_best = np.random.randn(2, 1);

    for i in range(n_iter):
        grad = 2./m * x_b.T.dot(x_b.dot(theta_best) - y);
        theta_best = theta_best - learning_rate * grad;

    print("The actual parameter : {}".format(theta));
    print("The best parameter : {}, {}".format(theta_best[0], theta_best[1]));



def gradient_descent_compare_learning_rate():
    theta = [4, 3];
    x = 2 * np.random.rand(100, 1);
    y = theta[0] + theta[1] * x + np.random.randn(100, 1);  # y = 3x+4 + noise

    # Add x_0=1 to each sample
    x_b = np.c_[np.ones((100, 1)), x];

    # For predict data
    x_new = np.array([[0], [2]]);
    x_new_b = np.c_[np.ones((2, 1)), x_new];

    theta_path_bgd = [];

    def plot_gradient_descent(theta, eta, theta_path=None):
        m = x.shape[0];
        plt.plot(x, y, "b.");
        n_iter = 10000;

        for i in range(n_iter):
            if i < 10:
                y_pred = x_new_b.dot(theta);
                style = "b-" if i >0 else "r--";
                plt.plot(x_new, y_pred, style);

            grad = 2./m * x_b.T.dot(x_b.dot(theta) - y);
            theta = theta - eta*grad;

            if theta_path is not None:
                theta_path.append(theta);

        plt.xlabel("$x_1$");
        plt.axis([0, 2, 0, 15]);
        plt.title(r"$\eta = {}$".format(eta), fontsize=16);

    theta_best = np.random.randn(2, 1);

    plt.figure(figsize=(10, 4));
    plt.subplot(131);

    plot_gradient_descent(theta_best, eta=0.02);
    plt.ylabel("$y$", rotation=0, fontsize=18);


    plt.subplot(132);
    plot_gradient_descent(theta_best, eta=0.1, theta_path=theta_path_bgd);
    plt.subplot(133);
    plot_gradient_descent(theta_best, eta=0.5);

    save_fig("gradient_descent_compare_learning_rate");
    plt.show();

    return theta_path_bgd;



def stochastic_gradient_descent_example():
    theta_ori = [4, 3];
    x = 2 * np.random.rand(100, 1);
    y = theta_ori[0] + theta_ori[1] * x + np.random.randn(100, 1);  # y = 3x+4 + noise

    # Add x_0=1 to each sample
    x_b = np.c_[np.ones((100, 1)), x];

    # For predict data
    x_new = np.array([[0], [2]]);
    x_new_b = np.c_[np.ones((2, 1)), x_new];

    m = x.shape[0];

    n_epoch = 50;
    t0, t1 = 5.0, 50.0;

    def learning_schedule(t):
        return t0/(t+t1);

    theta = np.random.randn(2, 1);
    theta_path_sgd = [];


    for epoch in range(n_epoch):

        for i in range(m):
            if epoch == 0 and i < 20:
                y_predict = x_new_b.dot(theta)
                style = "b-" if i > 0 else "r--";
                plt.plot(x_new, y_predict, style);

            rand_idx = np.random.randint(m);
            xi = x_b[rand_idx:rand_idx+1];
            yi = y[rand_idx:rand_idx+1];

            grad = 2*xi.T.dot(xi.dot(theta) - yi);
            learning_rate = learning_schedule(epoch*m + 1);
            theta = theta - learning_rate*grad;

            theta_path_sgd.append(theta);

    print(theta);


    plt.plot(x, y, "b.");
    plt.xlabel("$x_1$");
    plt.axis([0, 2, 0, 15]);
    plt.ylabel("$y$", rotation=0, fontsize=18);
    save_fig("stochastic_gradient_descent_example");
    plt.show();

    return theta_path_sgd;


def SGD_scikit():
    from sklearn.linear_model import SGDRegressor

    theta_ori = [4, 3];
    x = 2 * np.random.rand(100, 1);
    y = theta_ori[0] + theta_ori[1] * x + np.random.randn(100, 1);  # y = 3x+4 + noise
    y = y.ravel();
    n_epoch = 50;
    learning_rate = 0.1

    sgd_reg = SGDRegressor(max_iter=n_epoch, penalty=None, eta0=learning_rate);
    sgd_reg.fit(x, y);

    print("theta : {}, bias : {}".format(sgd_reg.intercept_, sgd_reg.coef_));

    x_new = np.array([[0], [2]]);
    y_predict = sgd_reg.predict(x_new);
    plt.plot(x_new, y_predict, 'r--');

    plt.plot(x, y, "b.");
    plt.xlabel("$x_1$");
    plt.axis([0, 2, 0, 15]);
    plt.ylabel("$y$", rotation=0, fontsize=18);
    save_fig("stochastic_gradient_descent_scikit_example");
    plt.show();


def minibatch_gradient_descent_example():
    theta_ori = [4, 3];
    x = 2 * np.random.rand(100, 1);
    y = theta_ori[0] + theta_ori[1] * x + np.random.randn(100, 1);  # y = 3x+4 + noise

    # Add x_0=1 to each sample
    x_b = np.c_[np.ones((100, 1)), x];

    # For predict data
    x_new = np.array([[0], [2]]);
    x_new_b = np.c_[np.ones((2, 1)), x_new];

    m = x.shape[0];

    theta_path_mgd = [];
    n_iter = 50;
    minibatch_size = 50;

    theta = np.random.randn(2, 1);
    t0, t1 = 200., 1000.;

    def learning_schedule(t):
        return t0 / (t + t1);

    t= 0;

    for epoch in range(n_iter):
        shuffled_idx = np.random.permutation(m);
        x_b_shuffled = x_b[shuffled_idx];
        y_shuffled = y[shuffled_idx];

        for i in range(0, m, minibatch_size):
            t+=1;
            xi = x_b_shuffled[i:i+minibatch_size];
            yi = y_shuffled[i:i+minibatch_size];
            grad = 2*xi.T.dot(xi.dot(theta) - yi) / minibatch_size;
            learning_rate = learning_schedule(epoch*m + 1);
            theta = theta - learning_rate*grad;
            theta_path_mgd.append(theta);

    print(theta);
    return theta_path_mgd



def compare_gradient_descent():
    theta_path_bgd = np.array(gradient_descent_compare_learning_rate());
    theta_path_sgd = np.array(stochastic_gradient_descent_example());
    theta_path_mgd = np.array(minibatch_gradient_descent_example());


    plt.figure(figsize=(7, 4))
    plt.plot(theta_path_sgd[:, 0], theta_path_sgd[:, 1], "r-s", linewidth=1, label="SGD")
    plt.plot(theta_path_mgd[:, 0], theta_path_mgd[:, 1], "g-+", linewidth=2, label="miniBatch")
    plt.plot(theta_path_bgd[:, 0], theta_path_bgd[:, 1], "b-o", linewidth=3, label="Batch")
    plt.legend(loc="upper left", fontsize=16)
    plt.xlabel(r"$\theta_0$", fontsize=20)
    plt.ylabel(r"$\theta_1$   ", fontsize=20, rotation=0)
    plt.axis([2.5, 4.5, 2.3, 3.9])
    save_fig("compare_gradient_descent")
    plt.show()


""" Linear regression for nonlinear function """


def quadratic_equation_regression():
    np.random.seed(42);

    m = 100;
    theta_ori = [0.5, 1.0, 2.0];

    # x ~ uniform(-3, 3)
    x = 6 * np.random.rand(m, 1) - 3;
    # y = <theta_ori, [x^2, x, 1]> + noise
    y = theta_ori[0] * x ** 2 + theta_ori[1] * x + theta_ori[2] + np.random.randn(m, 1);

    def plot_data(X, Y):
        plt.plot(X, Y, "b.");
        plt.xlabel("$x_1$", fontsize=18);
        plt.ylabel("$y$", rotation=0, fontsize=18);
        plt.axis([-3, 3, 0, 10]);
        save_fig("quadratic_data_plot");
        plt.show();

    from sklearn.preprocessing import PolynomialFeatures
    poly_features = PolynomialFeatures(degree=2, include_bias=False);

    # x_poly[i] = [x[i], x[i]^2]
    # => we can apply linear models
    x_poly = poly_features.fit_transform(x);

    from sklearn.linear_model import LinearRegression
    lin_reg = LinearRegression();
    lin_reg.fit(x_poly, y);

    print("weight : {}".format(lin_reg.coef_));
    print("bias : {}".format(lin_reg.intercept_));

    # plot the graph
    test_x = np.linspace(-3, 3, 100).reshape(100, 1);
    test_x_poly = poly_features.transform(test_x);
    pred_y = lin_reg.predict(test_x_poly);

    plt.plot(x, y, "b.");
    plt.plot(test_x, pred_y, 'r--', linewidth=2, label="prediction");
    plt.xlabel("$x_1$", fontsize=18);
    plt.ylabel("$y$", rotation=0, fontsize=18);
    plt.legend(loc="upper left", fontsize=14);
    plt.axis([-3, 3, 0, 10]);
    save_fig("quadratic_prediction_plot");
    plt.show();


def comparison_degree_of_polynomial_regression():
    from sklearn.preprocessing import PolynomialFeatures, StandardScaler
    from sklearn.linear_model import LinearRegression
    from sklearn.pipeline import Pipeline

    np.random.seed(42);

    m = 100;
    theta_ori = [0.5, 1.0, 2.0];

    # x ~ uniform(-3, 3)
    x = 6 * np.random.rand(m, 1) - 3;
    # y = <theta_ori, [x^2, x, 1]> + noise
    y = theta_ori[0] * x ** 2 + theta_ori[1] * x + theta_ori[2] + np.random.randn(m, 1);

    test_x = np.linspace(-3, 3, 100).reshape(100, 1);

    for style, width, degree in (("g-", 1, 300), ("b--", 2, 2), ("r-+", 2, 1)):
        poly_feature = PolynomialFeatures(degree=degree, include_bias=False);
        std_scaler = StandardScaler();
        lin_reg = LinearRegression();
        poly_reg = Pipeline([
            ("poly_features", poly_feature),
            ("std_scaler", std_scaler),
            ("lin_reg", lin_reg)
        ]);

        poly_reg.fit(x, y);
        pred_y = poly_reg.predict(test_x);
        plt.plot(test_x, pred_y, label=str(degree), linewidth=width);

    plt.plot(x, y, "b.", linewidth=3);
    plt.legend(loc="upper left");
    plt.xlabel("$x_1$", fontsize=18);
    plt.ylabel("$y$", rotation=0, fontsize=18);
    plt.axis([-3, 3, 0, 10]);
    save_fig("compare_degree_polynomial_plot");
    plt.show();


def learning_curve():
    from sklearn.metrics import mean_squared_error
    from sklearn.model_selection import train_test_split

    def plot_learning_curve(model, X, y):
        train_x, test_x, train_y, test_y = train_test_split(X, y, test_size=0.2);
        train_errors, test_errors = [], [];

        for m in range(1, len(train_x)):
            model.fit(train_x[:m], train_y[:m]);
            train_pred = model.predict(train_x[:m]);
            test_pred = model.predict(test_x);
            train_errors.append(mean_squared_error(train_pred, train_y[:m]));
            test_errors.append(mean_squared_error(test_pred, test_y));

        plt.plot(np.sqrt(train_errors), "r-+", linewidth=2, label="Train set");
        plt.plot(np.sqrt(test_errors), "b-", linewidth=3, label="Test set");
        plt.xlabel("Train set size", fontsize=14);
        plt.ylabel("RMSE", fontsize=14);
        plt.legend(loc="upper right", fontsize=14);

    np.random.seed(42);

    m = 100;
    theta_ori = [0.5, 1.0, 2.0];

    # x ~ uniform(-3, 3)
    x = 6 * np.random.rand(m, 1) - 3;
    # y = <theta_ori, [x^2, x, 1]> + noise
    y = theta_ori[0] * x ** 2 + theta_ori[1] * x + theta_ori[2] + np.random.randn(m, 1);

    from sklearn.linear_model import LinearRegression
    # lin_reg = LinearRegression();
    # plot_learning_curve(lin_reg, x, y);
    # plt.axis([0, 80, 0, 3]);
    # save_fig("underfitting_learning_curve");
    # plt.show();

    from sklearn.pipeline import Pipeline
    from sklearn.preprocessing import PolynomialFeatures
    poly_reg = Pipeline([
        ("poly_features", PolynomialFeatures(degree=10, include_bias=False)),
        ("lin_reg", LinearRegression()),
    ]);

    plot_learning_curve(poly_reg, x, y);
    plt.axis([0, 80, 0, 3]);
    save_fig("overfitting_learning_curve");
    plt.show()


def Ridge_regression():
    from sklearn.linear_model import Ridge, LinearRegression
    from sklearn.preprocessing import PolynomialFeatures, StandardScaler
    from sklearn.pipeline import Pipeline

    np.random.seed(42);

    m = 20;
    theta_ori = [1., 0.5];

    # x ~ uniform(0, 3)
    x = 3 * np.random.rand(m, 1);
    # y = <theta_ori, [1, x]> + noise where noise ~ N(0, 1/1.5)
    y = theta_ori[0] + theta_ori[1] * x + np.random.randn(m, 1) / 1.5;

    test_x = np.linspace(0, 3, 100).reshape(100, 1);

    def plot_model(model_class, polynomial, alphas, **model_kargs):
        for alpha, style in zip(alphas, ("b-", "g--", "r:")):
            model = model_class(alpha, **model_kargs) if alpha > 0 else LinearRegression();

            if polynomial:
                model = Pipeline([
                    ("poly_feature", PolynomialFeatures(degree=10, include_bias=False)),
                    ("std_scaler", StandardScaler()),
                    ("reg", model)
                ]);

            model.fit(x, y);
            pred_y = model.predict(test_x);
            lw = 2 if alpha > 0 else 1
            plt.plot(test_x, pred_y, style, linewidth=lw, label=r"$\alpha = {}$".format(alpha));

        plt.plot(x, y, 'b.', linewidth=3);
        plt.legend(loc="upper left", fontsize=15);
        plt.xlabel("$x_1$", fontsize=18);
        plt.axis([0, 3, 0, 4]);

    plt.figure(figsize=(8, 4));
    plt.subplot(121);
    plot_model(model_class=Ridge, polynomial=False, alphas=(0, 10, 100), random_state=42);
    plt.ylabel("$y$", rotation=0, fontsize=18);
    plt.title("Linear model")

    plt.subplot(122);
    plot_model(Ridge, polynomial=True, alphas=(0, 10 ** -5, 1), random_state=42);
    plt.title("Polynomial model");
    save_fig("ridge_regression_with_alpha");
    plt.show();


def Ridge_with_normal_equation():
    from sklearn.linear_model import Ridge

    np.random.seed(42);

    m = 20;
    theta_ori = [1., 0.5];

    # x ~ uniform(0, 3)
    x = 3 * np.random.rand(m, 1);
    # y = <theta_ori, [1, x]> + noise where noise ~ N(0, 1/1.5)
    y = theta_ori[0] + theta_ori[1] * x + np.random.randn(m, 1) / 1.5;

    test_x = np.linspace(0, 3, 100).reshape(100, 1);

    ridge_reg = Ridge(alpha=1, solver="cholesky", random_state=42);
    ridge_reg.fit(x, y);

    pred_y = ridge_reg.predict(test_x);

    plt.plot(x, y, "b.");
    plt.plot(test_x, pred_y, 'r--', linewidth=2, label="prediction");
    plt.xlabel("$x_1$", fontsize=18);
    plt.ylabel("$y$", rotation=0, fontsize=18);
    plt.legend(loc="upper left", fontsize=14);
    plt.axis([0, 3, 0, 4]);
    plt.title("Ridge_with_normal_equation_alpha_1");
    save_fig("Ridge_with_normal_equation");
    plt.show();


def Ridge_with_SGD():
    from sklearn.linear_model import SGDRegressor

    np.random.seed(42);

    m = 20;
    theta_ori = [1., 0.5];

    # x ~ uniform(0, 3)
    x = 3 * np.random.rand(m, 1);
    # y = <theta_ori, [1, x]> + noise where noise ~ N(0, 1/1.5)
    y = theta_ori[0] + theta_ori[1] * x + np.random.randn(m, 1) / 1.5;
    y = y.ravel();

    test_x = np.linspace(0, 3, 100).reshape(100, 1);

    sgd_reg = SGDRegressor(max_iter=5, penalty="l2");
    sgd_reg.fit(x, y);

    pred_y = sgd_reg.predict(test_x);

    plt.plot(x, y, "b.");
    plt.plot(test_x, pred_y, 'r--', linewidth=2, label="prediction");
    plt.xlabel("$x_1$", fontsize=18);
    plt.ylabel("$y$", rotation=0, fontsize=18);
    plt.legend(loc="upper left", fontsize=14);
    plt.axis([0, 3, 0, 4]);
    plt.title("Ridge_with_SGD");
    save_fig("Ridge_with_SGD");
    plt.show();


def Lasso_regression():
    from sklearn.linear_model import Lasso, LinearRegression
    from sklearn.preprocessing import PolynomialFeatures, StandardScaler
    from sklearn.pipeline import Pipeline

    np.random.seed(42);

    m = 20;
    theta_ori = [1., 0.5];

    # x ~ uniform(0, 3)
    x = 3 * np.random.rand(m, 1);
    # y = <theta_ori, [1, x]> + noise where noise ~ N(0, 1/1.5)
    y = theta_ori[0] + theta_ori[1] * x + np.random.randn(m, 1) / 1.5;

    test_x = np.linspace(0, 3, 100).reshape(100, 1);

    def plot_model(model_class, polynomial, alphas, **model_kargs):
        for alpha, style in zip(alphas, ("b-", "g--", "r:")):
            model = model_class(alpha, **model_kargs) if alpha > 0 else LinearRegression();

            if polynomial:
                model = Pipeline([
                    ("poly_feature", PolynomialFeatures(degree=10, include_bias=False)),
                    ("std_scaler", StandardScaler()),
                    ("reg", model)
                ]);

            model.fit(x, y);
            pred_y = model.predict(test_x);
            lw = 2 if alpha > 0 else 1
            plt.plot(test_x, pred_y, style, linewidth=lw, label=r"$\alpha = {}$".format(alpha));

        plt.plot(x, y, 'b.', linewidth=3);
        plt.legend(loc="upper left", fontsize=15);
        plt.xlabel("$x_1$", fontsize=18);
        plt.axis([0, 3, 0, 4]);

    plt.figure(figsize=(8, 4));
    plt.subplot(121);
    plot_model(model_class=Lasso, polynomial=False, alphas=(0, 0.1, 1.0), random_state=42);
    plt.ylabel("$y$", rotation=0, fontsize=18);
    plt.title("Linear model")

    plt.subplot(122);
    plot_model(Lasso, polynomial=True, alphas=(0, 10 ** -7, 1), random_state=42);
    plt.title("Polynomial model");
    save_fig("Lasso_regression_with_alpha");
    plt.show();
    from sklearn.linear_model import SGDRegressor

    np.random.seed(42);

    m = 20;
    theta_ori = [1., 0.5];

    # x ~ uniform(0, 3)
    x = 3 * np.random.rand(m, 1);
    # y = <theta_ori, [1, x]> + noise where noise ~ N(0, 1/1.5)
    y = theta_ori[0] + theta_ori[1] * x + np.random.randn(m, 1) / 1.5;
    y = y.ravel();

    test_x = np.linspace(0, 3, 100).reshape(100, 1);

    sgd_reg = SGDRegressor(max_iter=5, penalty="l2");
    sgd_reg.fit(x, y);

    pred_y = sgd_reg.predict(test_x);

    plt.plot(x, y, "b.");
    plt.plot(test_x, pred_y, 'r--', linewidth=2, label="prediction");
    plt.xlabel("$x_1$", fontsize=18);
    plt.ylabel("$y$", rotation=0, fontsize=18);
    plt.legend(loc="upper left", fontsize=14);
    plt.axis([0, 3, 0, 4]);
    plt.title("Ridge_with_SGD");
    save_fig("Ridge_with_SGD");
    plt.show();


def Compare_Ridge_Lasso():
    from sklearn.linear_model import Ridge, Lasso, SGDRegressor
    x1, x2, y1, y2 = -1, 3, -1.5, 1.5;


    x_point = np.linspace(x1, x2, 500);
    y_point = np.linspace(y1, y2, 500);
    mesh_x, mesh_y = np.meshgrid(x_point, y_point)
    T = np.c_[mesh_x.ravel(), mesh_y.ravel()];

    Xr = np.array([[-1, 1], [-0.3, -1], [1, 0.1]]);
    yr = 2 * Xr[:, :1] + 0.5 * Xr[:, 1:];
    
    
    loss_mse = (1/len(Xr) * np.sum((T.dot(Xr.T) - yr.T)**2, axis=1)).reshape(mesh_x.shape);

    N1 = np.linalg.norm(T, ord=1, axis=1).reshape(mesh_x.shape);
    N2 = np.linalg.norm(T, ord=2, axis=1).reshape(mesh_x.shape);

    t_min_idx = np.unravel_index(np.argmin(loss_mse), loss_mse.shape);
    mesh_x_min, mesh_y_min = mesh_x[t_min_idx], mesh_y[t_min_idx];

    theta_init = np.array([[0.25], [-1]]);


    def bgd_path(theta, X, y, l1, l2, core=1, eta=0.1, n_iterations=50):
        path = [theta];

        for itr in range(n_iterations):

            # loss function : MSE(theta) + l1*l1-norm(theta) + l2*l2-norm(theta)
            # grad = 2*size(X) * core* X.T*(X.T-y) + l1*sign(theta) + 2*l2*theta
            grad = core * 2/len(X) * X.T.dot(X.dot(theta)-y) +l1*np.sign(theta) + 2*l2*theta;

            theta = theta - eta*grad;
            path.append(theta);

        return np.array(path);

    plt.figure(figsize=(12, 8));

    for i, N, l1, l2, title in ((0, N1, 0.5, 0, "Lasso"), (1, N2, 0, 0.1, "Ridge")):
        # JR : Loss function for Lasso/Ridge
        loss_regulation = loss_mse + l1*N1 + l2*N2**2;
        tr_min_idx = np.unravel_index(np.argmin(loss_regulation), loss_regulation.shape);
        tr_x_min, tr_y_min = mesh_x[tr_min_idx], mesh_y[tr_min_idx];

        # level set for loss_mse
        level_set_J = (np.exp(np.linspace(0, 1, 20))-1) * (np.max(loss_mse) - np.min(loss_mse)) + np.min(loss_mse);
        # level set for loss_regulation
        level_set_JR = (np.exp(np.linspace(0, 1, 20)) - 1) * (np.max(loss_regulation) - np.min(loss_regulation)) + np.min(loss_regulation);
        level_set_N = np.linspace(0, np.max(N), 10);


        path_J = bgd_path(theta_init, Xr, yr, l1=0,l2=0);
        path_JR = bgd_path(theta_init, Xr, yr, l1, l2);
        path_N = bgd_path(theta_init, Xr, yr, np.sign(l1)/3, np.sign(l2), core=0);


        plt.subplot(221 + i*2);
        plt.grid(True);
        plt.axhline(y=0, color='k');
        plt.axvline(x=0, color='k');
        plt.contourf(mesh_x, mesh_y, loss_mse, levels=level_set_J, alpha=0.9);
        plt.contour(mesh_x, mesh_y, N, levels=level_set_N);
        plt.plot(path_J[:, 0], path_J[:, 1], "w-o");
        plt.plot(path_N[:, 0], path_N[:, 1], "y-^");
        plt.plot(mesh_x_min, mesh_y_min, "rs");
        plt.title(r"$\ell_{}$ penalty".format(i+1), fontsize=16);
        plt.axis([x1, x2, y1, y2]);

        if i==1:
            plt.xlabel(r"$\theta_1$", fontsize=20);


        plt.subplot(222 +i*2);
        plt.grid(True);
        plt.axhline(y=0, color='k');
        plt.axvline(x=0, color='k');
        plt.contourf(mesh_x, mesh_y, loss_regulation, levels=level_set_JR, alpha=0.9);
        plt.plot(path_JR[:, 0], path_JR[:, 1], "w-o");

        plt.plot(tr_x_min, tr_y_min, "rs");
        plt.title(title, fontsize=16);
        plt.axis([x1, x2, y1, y2]);

        if i == 1:
            plt.xlabel(r"$\theta_1$", fontsize=20);

    save_fig("lasso_vs_ridge");
    plt.show();


def ElasticNet_scikit():
    from sklearn.linear_model import ElasticNet
    np.random.seed(42);

    m = 20;
    theta_ori = [1., 0.5];

    # x ~ uniform(0, 3)
    x = 3 * np.random.rand(m, 1);
    # y = <theta_ori, [1, x]> + noise where noise ~ N(0, 1/1.5)
    y = theta_ori[0] + theta_ori[1] * x + np.random.randn(m, 1) / 1.5;
    y = y.ravel();

    test_x = np.linspace(0, 3, 100).reshape(100, 1);

    elastic_net = ElasticNet(alpha=0.1, l1_ratio=0.5);

    elastic_net.fit(x, y);

    pred_y = elastic_net.predict(test_x);

    plt.plot(x, y, "b.");
    plt.plot(test_x, pred_y, 'r--', linewidth=2, label="prediction");
    plt.xlabel("$x_1$", fontsize=18);
    plt.ylabel("$y$", rotation=0, fontsize=18);
    plt.legend(loc="upper left", fontsize=14);
    plt.axis([0, 3, 0, 4]);
    plt.title("Elastic_net - alpha {}, l1-ratio {}".format(0.1, 0.5));
    save_fig("Elastic_net_with_ratio_05");
    plt.show();


def Plot_early_stopping():
    from sklearn.linear_model import SGDRegressor
    from sklearn.preprocessing import StandardScaler, PolynomialFeatures
    from sklearn.model_selection import train_test_split
    from sklearn.metrics import mean_squared_error
    from sklearn.pipeline import Pipeline

    np.random.seed(42);

    m = 100;

    theta_ori = [0.5, 1.0, 2.0];

    # x ~ uniform(-3, 3)
    x = 6 * np.random.rand(m, 1) - 3;
    # y = <theta_ori, [x^2, x, 1]> + noise
    y = theta_ori[0] * x ** 2 + theta_ori[1] * x + theta_ori[2] + np.random.randn(m, 1);

    train_x, val_x, train_y, val_y = train_test_split(x[:50], y[:50].ravel(), test_size=0.5, random_state=10);
    poly_scaler = Pipeline([
        ("poly_features", PolynomialFeatures(degree=90, include_bias=False)),
        ("std_scaler", StandardScaler()),
    ]);

    train_x_poly_scaled = poly_scaler.fit_transform(train_x, train_y);
    val_x_poly_scaled = poly_scaler.transform(val_x);

    sgd_reg = SGDRegressor(max_iter=1, penalty=None, eta0=0.0005,
                           warm_start=True, learning_rate="constant",
                           random_state=42);

    n_epochs = 500;
    train_errors, val_errors = [], [];

    for epoch in range(n_epochs):
        sgd_reg.fit(train_x_poly_scaled, train_y);
        train_pred = sgd_reg.predict(train_x_poly_scaled);
        val_pred = sgd_reg.predict(val_x_poly_scaled);
        train_errors.append(mean_squared_error(train_pred, train_y));
        val_errors.append(mean_squared_error(val_pred, val_y));


    #Find the smallest rmse of val_error
    best_epoch = np.argmin(val_errors);
    best_val_rmse = np.sqrt(val_errors[best_epoch]);

    plt.annotate("Best Model",
                 xy=(best_epoch, best_val_rmse),
                 xytext=(best_epoch, best_val_rmse + 0.5),
                 ha="center",
                 arrowprops=dict(facecolor='black', shrink=0.05),
                 fontsize=16);

    best_val_rmse -=0.03;
    plt.plot([0, n_epochs], [best_val_rmse, best_val_rmse], "k:", linewidth=2);
    plt.plot(np.sqrt(val_errors), "b--", linewidth=3, label="Validation");
    plt.plot(np.sqrt(train_errors), "r--", linewidth=2, label="Train");
    plt.legend(loc="upper right", fontsize=14);
    plt.xlabel("epoch", fontsize=14);
    plt.ylabel("RMSE", fontsize=14);
    save_fig("Early_Stopping_Graph");
    plt.show();


def Basic_early_stopping():
    from sklearn.linear_model import SGDRegressor
    from sklearn.preprocessing import StandardScaler, PolynomialFeatures
    from sklearn.model_selection import train_test_split
    from sklearn.metrics import mean_squared_error
    from sklearn.pipeline import Pipeline

    from sklearn.base import clone

    np.random.seed(42);

    m = 100;

    theta_ori = [0.5, 1.0, 2.0];

    # x ~ uniform(-3, 3)
    x = 6 * np.random.rand(m, 1) - 3;
    # y = <theta_ori, [x^2, x, 1]> + noise
    y = theta_ori[0] * x ** 2 + theta_ori[1] * x + theta_ori[2] + np.random.randn(m, 1);

    train_x, val_x, train_y, val_y = train_test_split(x[:50], y[:50].ravel(), test_size=0.5, random_state=10);
    poly_scaler = Pipeline([
        ("poly_features", PolynomialFeatures(degree=90, include_bias=False)),
        ("std_scaler", StandardScaler()),
    ]);

    train_x_poly_scaled = poly_scaler.fit_transform(train_x, train_y);
    val_x_poly_scaled = poly_scaler.transform(val_x);

    sgd_reg = SGDRegressor(max_iter=1, penalty=None, eta0=0.0005,
                           warm_start=True, learning_rate="constant",
                           random_state=42);


    minimum_val_error = float("inf");
    best_epoch = None;
    best_model = None;

    for epoch in range(1000):
        sgd_reg.fit(train_x_poly_scaled, train_y);
        val_pred = sgd_reg.predict(val_x_poly_scaled);
        val_error = mean_squared_error(val_y, val_pred);

        if val_error < minimum_val_error:
            minimum_val_error = val_error;
            best_epoch = epoch;
            best_model = clone(sgd_reg);

    print("Best epoch : {}".format(best_epoch));
    print("Best model by early stopping : \n{}".format(best_model))


def Logistic_Binary_Iris():
    from sklearn.datasets import load_iris
    from sklearn.linear_model import LogisticRegression

    iris = load_iris();

    # X has 1 feature, petal width
    X = iris["data"][:, 3:];
    # y : True if Virginica / False otherwise
    y = (iris["target"] == 2).astype(np.int);

    log_reg = LogisticRegression();
    log_reg.fit(X, y);

    mesh_x = np.linspace(0, 3, 1000).reshape(-1, 1);
    pred_proba = log_reg.predict_proba(mesh_x);
    decision_boundary = mesh_x[pred_proba[:, 1]>=0.5][0];

    plt.figure(figsize=(16, 8));

    plt.subplot(121);
    plt.plot(X[y==0], y[y==0], "bs");
    plt.plot(X[y==1], y[y==1], "g^");
    plt.plot([decision_boundary, decision_boundary], [-1, 2], "k:", linewidth=2);
    plt.plot(mesh_x, pred_proba[:, 1], "g-", label="Iris-Virginica");
    plt.plot(mesh_x, pred_proba[:, 0], "b--", label="Otherwise");

    plt.text(decision_boundary+0.02, 0.15, "Decision Boundary", fontsize=14, color="k", ha="center");
    plt.arrow(decision_boundary, 0.08, -0.3, 0, head_width=0.05, head_length=0.1, fc='b', ec='b');
    plt.arrow(decision_boundary, 0.92, 0.3, 0, head_width=0.05, head_length=0.1, fc='g', ec='g');
    plt.xlabel("Petal Width(cm)");
    plt.ylabel("Probability");
    plt.legend(loc="center left", fontsize=14);
    plt.axis([0, 3, -0.02, 1.02]);

    # X has 2 features, petal width/petal length
    X = iris["data"][:, (2, 3)];

    log_reg = LogisticRegression(solver="liblinear", C=10**10, random_state=42);
    log_reg.fit(X, y);

    mesh_x, mesh_y = np.meshgrid(
        np.linspace(2.9, 7, 500).reshape(-1, 1),
        np.linspace(0.8, 2.7, 200).reshape(-1, 1),);

    test_x = np.c_[mesh_x.ravel(), mesh_y.ravel()];

    pred_proba = log_reg.predict_proba(test_x);

    plt.subplot(122);
    plt.plot(X[y == 0, 0], X[y == 0, 1], "bs");
    plt.plot(X[y == 1, 0], X[y == 1, 1], "g^");

    zz = pred_proba[:, 1].reshape(mesh_x.shape);
    contour = plt.contour(mesh_x, mesh_y, zz, cmap=plt.cm.brg);

    left_right = np.array([2.9, 7]);
    boundary = -(log_reg.coef_[0][0]*left_right + log_reg.intercept_[0]) / log_reg.coef_[0][1];

    plt.clabel(contour, inline=1, fontsize=12);
    plt.plot(left_right, boundary, "k--", linewidth=3);
    plt.text(3.5, 1.5, "Not Iris-Virginica", fontsize=14, color="b", ha="center");
    plt.text(6.5, 2.3, "Iris-Virginica", fontsize=14, color="g", ha="center");
    plt.xlabel("Petal Length(cm)", fontsize=14);
    plt.ylabel("Petal Width(cm)", fontsize=14);
    plt.axis([2.9, 7, 0.8, 2.7]);

    save_fig("Logistic_regression_Binary_Classification");
    plt.show();


def Softmax_Multi_Iris():
    from sklearn.datasets import load_iris
    from sklearn.linear_model import LogisticRegression

    iris = load_iris();
    X = iris["data"][:, (2, 3)];
    y = iris["target"];

    softmax_reg = LogisticRegression(multi_class="multinomial", solver="lbfgs", C=10, random_state=42);
    softmax_reg.fit(X, y);

    mesh_x, mesh_y = np.meshgrid(
        np.linspace(0, 8, 500).reshape(-1, 1),
        np.linspace(0, 3.5, 200).reshape(-1, 1), );

    test_x = np.c_[mesh_x.ravel(), mesh_y.ravel()];

    pred = softmax_reg.predict(test_x);
    pred_proba = softmax_reg.predict_proba(test_x);

    zz1 = pred_proba[:, 1].reshape(mesh_x.shape);
    zz = pred.reshape(mesh_x.shape);

    plt.figure(figsize=(10, 4));
    plt.plot(X[y == 2, 0], X[y == 2, 1], "g^", label="Iris-Virginica");
    plt.plot(X[y == 1, 0], X[y == 1, 1], "bs", label="Iris-Versicolor");
    plt.plot(X[y == 0, 0], X[y == 0, 1], "yo", label="Iris-Setosa");

    from matplotlib.colors import ListedColormap
    custom_cmap = ListedColormap(['#fafab0', '#9898ff', '#a0faa0']);

    plt.contourf(mesh_x, mesh_y, zz, cmap=custom_cmap);

    contour = plt.contour(mesh_x, mesh_y, zz1, cmap=plt.cm.brg);
    plt.clabel(contour, inline=1, fontsize=12);
    plt.xlabel("Petal Length(cm)", fontsize=14);
    plt.ylabel("Petal Width(cm)", fontsize=14);
    plt.axis([0, 7, 0, 3.5]);
    plt.legend(loc="center left", fontsize=14);
    save_fig("softmax_regression_Iris_Classification");
    plt.show();

# TODO
def Early_Stopping_Iris_Classification():
    """
    Exercise 4.12 :
        Apply Early Stopping to Softmax Regression without Scikit module
    """
    from sklearn.datasets import load_iris

    iris = load_iris();
    X = iris["data"][:, (2, 3)];
    y = iris["target"];

    # Add Bias(theta_0=0) to X
    bias = np.ones([len(X), 1]);
    X_with_bias = np.c_[bias, X];
    # print(X.shape);print(X_with_bias.shape);

    # Fix the seed of Random
    np.random.seed(2042);

    "Split data for Training, Validation, Test"
    total_size = len(X_with_bias);
    test_ratio = 0.2;
    validation_ratio = 0.2;

    test_size = int(test_ratio*total_size);
    validation_size = int(validation_ratio*total_size);
    train_size= total_size - (test_size + validation_size);

    # Split data
    random_idx = np.random.permutation(total_size);

    train_x = X_with_bias[random_idx[:train_size]];
    train_y = y[random_idx[:train_size]];
    valid_x = X_with_bias[random_idx[train_size:train_size+validation_size]];
    valid_y = y[random_idx[train_size:train_size+validation_size]];
    test_x = X_with_bias[random_idx[train_size+validation_size:]];
    test_y = y[random_idx[train_size+validation_size:]];

    # Encoder for One-Hot encoding
    # i.e label=1 => [0, 1, 0]
    def one_hot_encoder(target):
        n_classes = target.max() + 1;
        size = len(target);
        one_hot = np.zeros([size, n_classes]);
        one_hot[np.arange(size), target] = 1;
        return one_hot;

    train_y_one_hot = one_hot_encoder(train_y);
    valid_y_one_hot = one_hot_encoder(valid_y);
    test_y_one_hot = one_hot_encoder(test_y);


    # Softmax function
    def softmax(logits):
        exp = np.exp(logits);
        exp_sum = np.sum(exp, axis=1, keepdims=True);

        return exp / exp_sum;

    n_input = train_x.shape[1];
    n_output = len(np.unique(train_y));


    "Train with Gradient Descent"
    # Set Hyper-parameters
    learning_rate = 0.1;
    n_iter = 5001;
    intermediate_check = 500;
    alpha = 0.1  # Hyper-parameter for l2 i.e model-regulation

    # Set some parameters for training
    train_size = len(train_x);
    epsilon = 1e-7  # avoid NaN

    # Set some variable for Early-stopping
    best_loss = np.infty;


    # Initialize the parameters with Gaussian distribution
    theta = np.random.randn(n_input, n_output);




    # Apply Gradient Descent with Early Stopping and l2-penalty
    for itr in range(n_iter):

        # Calculation for training set
        train_logits = train_x.dot(theta);
        train_proba = softmax(train_logits);

        # Calculate the cost function of Softmax Regression
        train_entropy_loss= -np.mean(np.sum(train_y_one_hot * np.log(train_proba + epsilon), axis=1));
        train_l2_loss = 1/2 * np.sum(np.square(theta[1:]));   # theta[0] : just a bias
        train_cost_func = train_entropy_loss + alpha * train_l2_loss;

        error = train_proba - train_y_one_hot;

        grad = 1 /train_size * train_x.T.dot(error) + np.r_[np.zeros([1, n_output]), alpha * theta[1:]];

        # Use Gradient Descent
        theta = theta - learning_rate * grad;

        # Calculation for validation set
        valid_logits = valid_x.dot(theta);
        valid_proba = softmax(valid_logits);
        valid_entropy_loss = -np.mean(np.sum(valid_y_one_hot * np.log(valid_proba + epsilon), axis=1));
        valid_l2_loss = 1/2 * np.sum(np.square(theta[1:]));
        valid_cost_func = valid_entropy_loss + alpha * valid_l2_loss;

        if itr % intermediate_check == 0:
            print("Iteration : {} - Validation Loss : {}".format(itr, valid_cost_func));
            print("Train loss : {}".format(train_cost_func));

        # Save the best cost function value
        if valid_cost_func < best_loss:
            best_loss = valid_cost_func;
        else:
            print("Best iteration : {} - Best loss - {}".format(itr, valid_cost_func));
            print("early Stopping");
            break;


    logits = valid_x.dot(theta);
    Y_proba = softmax(logits)
    y_predict = np.argmax(Y_proba, axis=1)

    accuracy_score = np.mean(y_predict == valid_y)
    print("Validation Acc : {}".format(accuracy_score));



    test_logits = test_x.dot(theta);
    pred_proba = softmax(test_logits);
    pred = np.argmax(pred_proba, axis=1);
    acc = np.mean(pred == test_y);
    print("Test acc : {}".format(acc));



    mesh_x, mesh_y = np.meshgrid(
        np.linspace(0, 8, 500).reshape(-1, 1),
        np.linspace(0, 3.5, 200).reshape(-1, 1),
    );
    X_new = np.c_[mesh_x.ravel(), mesh_y.ravel()];
    X_new_with_bias = np.c_[np.ones([len(X_new), 1]), X_new];

    logits = X_new_with_bias.dot(theta);
    Y_proba = softmax(logits);
    y_predict = np.argmax(Y_proba, axis=1);

    zz1 = Y_proba[:, 1].reshape(mesh_x.shape);
    zz = y_predict.reshape(mesh_x.shape);

    plt.figure(figsize=(10, 4))
    plt.plot(X[y == 2, 0], X[y == 2, 1], "g^", label="Iris-Virginica");
    plt.plot(X[y == 1, 0], X[y == 1, 1], "bs", label="Iris-Versicolor");
    plt.plot(X[y == 0, 0], X[y == 0, 1], "yo", label="Iris-Setosa");

    from matplotlib.colors import ListedColormap
    custom_cmap = ListedColormap(['#fafab0', '#9898ff', '#a0faa0']);

    plt.contourf(mesh_x, mesh_y, zz, cmap=custom_cmap);
    contour = plt.contour(mesh_x, mesh_y, zz1, cmap=plt.cm.brg);
    plt.clabel(contour, inline=1, fontsize=12);
    plt.xlabel("Petal Length(cm)", fontsize=14);
    plt.ylabel("Petal Width(cm)", fontsize=14);
    plt.legend(loc="upper left", fontsize=14);
    plt.axis([0, 7, 0, 3.5]);
    plt.show();








def test():
    from sklearn.datasets import load_iris
    iris = load_iris()
    X = iris["data"][:, (2, 3)]  # 꽃잎 길이, 꽃잎 넓이
    y = iris["target"]

    X_with_bias = np.c_[np.ones([len(X), 1]), X]
    np.random.seed(2042)
    test_ratio = 0.2
    validation_ratio = 0.2
    total_size = len(X_with_bias)

    test_size = int(total_size * test_ratio)
    validation_size = int(total_size * validation_ratio)
    train_size = total_size - test_size - validation_size

    rnd_indices = np.random.permutation(total_size)

    X_train = X_with_bias[rnd_indices[:train_size]]
    y_train = y[rnd_indices[:train_size]]
    X_valid = X_with_bias[rnd_indices[train_size:-test_size]]
    y_valid = y[rnd_indices[train_size:-test_size]]
    X_test = X_with_bias[rnd_indices[-test_size:]]
    y_test = y[rnd_indices[-test_size:]]

    def to_one_hot(y):
        n_classes = y.max() + 1
        m = len(y)
        Y_one_hot = np.zeros((m, n_classes))
        Y_one_hot[np.arange(m), y] = 1
        return Y_one_hot

    Y_train_one_hot = to_one_hot(y_train)
    Y_valid_one_hot = to_one_hot(y_valid)
    Y_test_one_hot = to_one_hot(y_test)

    def softmax(logits):
        exps = np.exp(logits)
        exp_sums = np.sum(exps, axis=1, keepdims=True)
        return exps / exp_sums

    n_inputs = X_train.shape[1]  # == 3 (특성 2와 편향)
    n_outputs = len(np.unique(y_train))  # == 3 (3개의 붓꽃 클래스)

    eta = 0.1
    n_iterations = 5001
    m = len(X_train)
    epsilon = 1e-7
    alpha = 0.1  # 규제 하이퍼파라미터

    Theta = np.random.randn(n_inputs, n_outputs)



    eta = 0.1
    n_iterations = 5001
    m = len(X_train)
    epsilon = 1e-7
    alpha = 0.1  # 규제 하이퍼파라미터
    best_loss = np.infty

    Theta = np.random.randn(n_inputs, n_outputs)

    for iteration in range(n_iterations):
        logits = X_train.dot(Theta)
        Y_proba = softmax(logits)
        xentropy_loss = -np.mean(np.sum(Y_train_one_hot * np.log(Y_proba + epsilon), axis=1))
        l2_loss = 1 / 2 * np.sum(np.square(Theta[1:]))
        loss = xentropy_loss + alpha * l2_loss
        error = Y_proba - Y_train_one_hot
        gradients = 1 / m * X_train.T.dot(error) + np.r_[np.zeros([1, n_outputs]), alpha * Theta[1:]]
        Theta = Theta - eta * gradients

        logits = X_valid.dot(Theta)
        Y_proba = softmax(logits)
        xentropy_loss = -np.mean(np.sum(Y_valid_one_hot * np.log(Y_proba + epsilon), axis=1))
        l2_loss = 1 / 2 * np.sum(np.square(Theta[1:]))
        loss = xentropy_loss + alpha * l2_loss
        if iteration % 500 == 0:
            print(iteration, loss)
        if loss < best_loss:
            best_loss = loss
        else:
            print(iteration - 1, best_loss)
            print(iteration, loss, "early stopping!")
            break

    logits = X_valid.dot(Theta)
    Y_proba = softmax(logits)
    y_predict = np.argmax(Y_proba, axis=1)

    accuracy_score = np.mean(y_predict == y_valid)
    print("valid acc : {}".format(accuracy_score))
    # x0, x1 = np.meshgrid(
    #     np.linspace(0, 8, 500).reshape(-1, 1),
    #     np.linspace(0, 3.5, 200).reshape(-1, 1),
    # )
    # X_new = np.c_[x0.ravel(), x1.ravel()]
    # X_new_with_bias = np.c_[np.ones([len(X_new), 1]), X_new]
    #
    # logits = X_new_with_bias.dot(Theta)
    # Y_proba = softmax(logits)
    # y_predict = np.argmax(Y_proba, axis=1)
    #
    # zz1 = Y_proba[:, 1].reshape(x0.shape)
    # zz = y_predict.reshape(x0.shape)
    #
    # plt.figure(figsize=(10, 4))
    # plt.plot(X[y == 2, 0], X[y == 2, 1], "g^", label="Iris-Virginica")
    # plt.plot(X[y == 1, 0], X[y == 1, 1], "bs", label="Iris-Versicolor")
    # plt.plot(X[y == 0, 0], X[y == 0, 1], "yo", label="Iris-Setosa")
    #
    # from matplotlib.colors import ListedColormap
    # custom_cmap = ListedColormap(['#fafab0', '#9898ff', '#a0faa0'])
    #
    # plt.contourf(x0, x1, zz, cmap=custom_cmap)
    # contour = plt.contour(x0, x1, zz1, cmap=plt.cm.brg)
    # plt.clabel(contour, inline=1, fontsize=12)
    # plt.xlabel("꽃잎 길이", fontsize=14)
    # plt.ylabel("꽃잎 폭", fontsize=14)
    # plt.legend(loc="upper left", fontsize=14)
    # plt.axis([0, 7, 0, 3.5])
    # plt.show()
    #
    # logits = X_test.dot(Theta)
    # Y_proba = softmax(logits)
    # y_predict = np.argmax(Y_proba, axis=1)
    #
    # accuracy_score = np.mean(y_predict == y_test)
    # print("test acc : {}".format(accuracy_score))


if __name__== '__main__':
    print("Chapter 4 : Training Models");
    #stochastic_gradient_descent_example();
    #SGD_scikit();
    #quadratic_equation_regression();
    #comparison_degree_of_polynomial_regression();
    #learning_curve();
    #Ridge_regression();
    #Ridge_with_normal_equation();
    #Ridge_with_SGD();
    #Lasso_regression();
    #Compare_Ridge_Lasso();
    #ElasticNet_scikit()
    #Plot_early_stopping();
    #Basic_early_stopping();
    #Logistic_Binary_Iris();
    #Softmax_Multi_Iris();


    Early_Stopping_Iris_Classification();

