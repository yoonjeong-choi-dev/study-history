from __future__ import division, print_function, unicode_literals

import os

import numpy as np
import matplotlib.pyplot as plt
import matplotlib


""" Setting of matplotlib """
plt.rcParams['axes.labelsize'] = 14;
plt.rcParams['xtick.labelsize'] = 12;
plt.rcParams['ytick.labelsize'] = 12;

""" Useful function """
# Save the graph
def save_fig(fig_id, tight_layout=True):
    PROJECT_ROOT_DIR = ".";
    CHAPTER_ID = "support_vector_machine";


    path = os.path.join(PROJECT_ROOT_DIR, "My_images", CHAPTER_ID, fig_id+".png");
    if tight_layout:
        plt.tight_layout();

    if not (os.path.isdir(os.path.join(PROJECT_ROOT_DIR, "My_images", CHAPTER_ID))):
        os.makedirs(os.path.join(PROJECT_ROOT_DIR, "My_images", CHAPTER_ID));

    plt.savefig(path, format='png', dpi=300);
    print("figure is saved...........................!")

def plot_svc_decision_boundary(model, x_min, x_max):
    weight = model.coef_[0];
    bias = model.intercept_[0];

    # Decision boundary : w0*x0 + w1*x1 + b = 0
    #                   => x1 = -w0/w1 * x0 - b/w1
    x0 = np.linspace(x_min, x_max, 200);
    decision_boundary = -weight[0] / weight[1] * x0 - bias / weight[1];

    margin = 1 / weight[1];
    gutter_up = decision_boundary + margin;
    gutter_down = decision_boundary - margin;

    support_vectors = model.support_vectors_;
    plt.scatter(support_vectors[:, 0], support_vectors[:, 1], s=180,
                facecolors="#FFAAAA");
    plt.plot(x0, decision_boundary, "k-", linewidth=2);
    plt.plot(x0, gutter_up, "k--", linewidth=2);
    plt.plot(x0, gutter_down, "k--", linewidth=2);

def plot_binary_dataset(X, y,axes):
    plt.plot(X[:, 0][y == 1], X[:, 1][y == 1], "g^");
    plt.plot(X[:, 0][y == 0], X[:, 1][y == 0], "bs");
    plt.axis(axes);
    plt.grid(True, which="both");
    plt.xlabel(r"$x_1$", fontsize=20);
    plt.ylabel(r"$x_2$", fontsize=20, rotation=0);


def plot_predictions(clf, axes):
    x0 = np.linspace(axes[0], axes[1], 100);
    x1 = np.linspace(axes[2], axes[3], 100);
    mesh_x, mesh_y = np.meshgrid(x0, x1);

    test_x = np.c_[mesh_x.ravel(), mesh_y.ravel()];
    pred = clf.predict(test_x).reshape(mesh_x.shape);

    decision = clf.decision_function(test_x).reshape(mesh_x.shape);
    plt.contourf(mesh_x, mesh_y, pred, cmap=plt.cm.brg, alpha=0.2);
    plt.contourf(mesh_x, mesh_y, decision, cmap=plt.cm.brg, alpha=0.1);


def plot_svm_regression(reg, X, y, axes):
    x = np.linspace(axes[0], axes[1], 100).reshape(100, 1);
    pred_y = reg.predict(x);

    plt.plot(x, pred_y, "k-", linewidth=2, label=r"$\hat{y}$");
    plt.plot(x, pred_y + reg.epsilon, "k--");
    plt.plot(x, pred_y - reg.epsilon, "k--");
    plt.scatter(X[reg.support_], y[reg.support_], s=180, facecolors="#FFAAAA");
    plt.plot(X, y, "bo");
    plt.xlabel(r"$x_1$", fontsize=18);
    plt.legend(loc="upper left", fontsize=18);
    plt.axis(axes);


""" Main code """
def large_margin_classification():
    from sklearn.datasets import load_iris
    from sklearn.svm import SVC

    iris = load_iris();
    X = iris["data"][:, (2, 3)];
    y = iris["target"];

    setosa_or_versicolor_idx = (y==0) | (y==1);
    X = X[setosa_or_versicolor_idx];
    y = y[setosa_or_versicolor_idx];

    svm_clf = SVC(kernel="linear", C=float("inf"));
    svm_clf.fit(X, y);

    plt.figure(figsize=(12, 2.7));

    plt.subplot(121);
    x0 = np.linspace(0, 5.5, 200);
    boundary1 = 5*x0 - 20;
    boundary2 = x0 - 1.8;
    boundary3 = 0.1 * x0 +0.5;

    plt.plot(x0, boundary1, "g--", linewidth=2);
    plt.plot(x0, boundary2, "m--", linewidth=2);
    plt.plot(x0, boundary3, "r--", linewidth=2);
    plt.plot(X[:, 0][y==1], X[:, 1][y==1], "bs", label="Iris-Versicolor");
    plt.plot(X[:, 0][y== 0], X[:, 1][y == 0], "yo", label="Iris-Setosa");
    plt.xlabel("Petal Length(cm)", fontsize=14);
    plt.ylabel("Petal Width(cm)", fontsize=14);
    plt.legend(loc="upper left", fontsize=14);
    plt.axis([0, 5.5, 0, 2]);
    plt.title("Some decision boundaries");

    plt.subplot(122);
    plot_svc_decision_boundary(svm_clf, 0, 5.5);
    plt.plot(X[:, 0][y == 1], X[:, 1][y == 1], "bs", label="Iris-Versicolor");
    plt.plot(X[:, 0][y == 0], X[:, 1][y == 0], "yo", label="Iris-Setosa");
    plt.xlabel("Petal Length(cm)", fontsize=14);
    plt.ylabel("Petal Width(cm)", fontsize=14);

    plt.axis([0, 5.5, 0, 2]);
    plt.title("Support Vector Machine");
    save_fig("Large_margin_classification");
    plt.show();

def necessity_scaling_SVM():
    from sklearn.svm import SVC

    X = np.array([[1, 50], [5, 20], [3, 80], [5, 60]]).astype(np.float64);
    y = np.array([0, 0, 1, 1]);
    svm_clf = SVC(kernel="linear", C=100);
    svm_clf.fit(X, y);

    plt.figure(figsize=(12, 3.2));

    plt.subplot(121);
    plt.plot(X[:, 0][y==1], X[:, 1][y==1], "bo");
    plt.plot(X[:, 0][y == 0], X[:, 1][y == 0], "ms");
    plot_svc_decision_boundary(svm_clf, 0, 6);
    plt.xlabel("$x_0$", fontsize=20);
    plt.ylabel("$x_1$", fontsize=20, rotation=0);
    plt.title("Before Scaling", fontsize=16);
    plt.axis([0, 6, 0, 90]);

    from sklearn.preprocessing import StandardScaler
    scaler = StandardScaler();
    X_scaled = scaler.fit_transform(X);
    svm_clf.fit(X_scaled, y);

    plt.subplot(122);
    plt.plot(X_scaled[:, 0][y == 1], X_scaled[:, 1][y == 1], "bo");
    plt.plot(X_scaled[:, 0][y == 0], X_scaled[:, 1][y == 0], "ms");
    plot_svc_decision_boundary(svm_clf, -2, 2);
    plt.xlabel("$x_0$", fontsize=20);
    plt.ylabel("$x_1$", fontsize=20, rotation=0);
    plt.title("After Scaling", fontsize=16);
    plt.axis([-2, 2, -2, 2]);

    save_fig("Necessity_scaling_in_SVM");

    plt.show();

def outlier_SVM():
    from sklearn.datasets import load_iris
    from sklearn.svm import SVC

    iris = load_iris();
    X = iris["data"][:, (2, 3)];
    y = iris["target"];

    setosa_or_versicolor_idx = (y == 0) | (y == 1);
    X = X[setosa_or_versicolor_idx];
    y = y[setosa_or_versicolor_idx];

    X_outliers = np.array([[3.4, 1.3], [3.2, 0.8]]);
    y_outliers = np.array([0, 0]);

    X_outlier1 = np.concatenate([X, X_outliers[:1]], axis=0);
    y_outlier1 = np.concatenate([y, y_outliers[:1]], axis=0);
    X_outlier2 = np.concatenate([X, X_outliers[1:]], axis=0);
    y_outlier2 = np.concatenate([y, y_outliers[1:]], axis=0);

    svm_clf2 = SVC(kernel="linear", C=10**9);
    svm_clf2.fit(X_outlier2, y_outlier2);

    plt.figure(figsize=(12, 2.7));

    plt.subplot(121);
    plt.plot(X_outlier1[:, 0][y_outlier1==1], X_outlier1[:, 1][y_outlier1==1], "bs");
    plt.plot(X_outlier1[:, 0][y_outlier1 == 0], X_outlier1[:, 1][y_outlier1 == 0], "yo");
    plt.text(0.3, 1.0, "Not Separable!", fontsize=24, color="red");
    plt.xlabel("Petal Length(cm)", fontsize=14);
    plt.ylabel("Petal Width(cm)", fontsize=14);
    plt.annotate("Outlier",
                 xy=(X_outliers[0][0], X_outliers[0][1]),
                 xytext=(2.5, 1.7),
                 ha="center",
                 arrowprops=dict(facecolor="black", shrink=0.1),
                 fontsize=16,);
    plt.axis([0, 5.5, 0, 2]);

    plt.subplot(122);
    plt.plot(X_outlier2[:, 0][y_outlier2 == 1], X_outlier2[:, 1][y_outlier2 == 1], "bs");
    plt.plot(X_outlier2[:, 0][y_outlier2 == 0], X_outlier2[:, 1][y_outlier2 == 0], "yo");
    plot_svc_decision_boundary(svm_clf2, 0, 5.5);
    plt.xlabel("Petal Length(cm)", fontsize=14);
    plt.ylabel("Petal Width(cm)", fontsize=14);
    plt.annotate("Outlier",
                 xy=(X_outliers[1][0], X_outliers[1][1]),
                 xytext=(3.2, 0.08),
                 ha="center",
                 arrowprops=dict(facecolor="black", shrink=0.1),
                 fontsize=16, );
    plt.axis([0, 5.5, 0, 2]);
    save_fig("Existence_Outliers_in_SVM")
    plt.show();


def soft_margin_SVM():
    from sklearn.svm import LinearSVC
    from sklearn.preprocessing import StandardScaler
    from sklearn.pipeline import Pipeline
    from sklearn.datasets import load_iris

    iris = load_iris();
    X = iris["data"][:, (2, 3)];
    y = (iris["target"] == 2).astype(np.float64);


    scaler = StandardScaler();

    svm_clf1 = LinearSVC(C=1, loss="hinge", random_state=42);
    svm_clf100 = LinearSVC(C=100, loss="hinge", random_state=42);

    clf1 = Pipeline([
        ("scaler", scaler),
        ("linear_svc", svm_clf1),
    ]);

    clf100 = Pipeline([
        ("scaler", scaler),
        ("linear_svc", svm_clf100),
    ]);

    clf1.fit(X, y);
    clf100.fit(X, y);

    # Transform parameters of SVM to unscaled ones
    bias1 = svm_clf1.decision_function([-scaler.mean_/scaler.scale_]);
    weight1 = svm_clf1.coef_[0] / scaler.scale_;
    bias2 = svm_clf100.decision_function([-scaler.mean_ / scaler.scale_]);
    weight2 = svm_clf100.coef_[0] / scaler.scale_;

    svm_clf1.intercept_ = np.array([bias1]);
    svm_clf1.coef_ = np.array([weight1]);
    svm_clf100.intercept_ = np.array([bias2]);
    svm_clf100.coef_ = np.array([weight2]);

    # Find support vectors in each svm (because Scikit-learn does not supply)

    # t : -1 if False(==0) / 1 if True(==1)
    t = 2*y - 1;
    margin = 1;     # max distance between support vector and decision boundary
    support_vec_idx1 = (t*(X.dot(weight1) + bias1) < margin).ravel();
    support_vec_idx2 = (t*(X.dot(weight2) + bias2) < margin).ravel();

    svm_clf1.support_vectors_ = X[support_vec_idx1];
    svm_clf100.support_vectors_ = X[support_vec_idx2];

    plt.figure(figsize=(12, 3.2));

    plt.subplot(121);
    plt.plot(X[:, 0][y==1], X[:, 1][y==1], "g^", label="Iris-Virginica");
    plt.plot(X[:, 0][y == 0], X[:, 1][y == 0], "bs", label="Iris-Versicolor");
    plot_svc_decision_boundary(svm_clf1, 4, 6);
    plt.xlabel("Petal Length(cm)", fontsize=14);
    plt.ylabel("Petal Width(cm)", fontsize=14);
    plt.legend(loc="upper left", fontsize=14);
    plt.title("$C = {}$".format(svm_clf1.C), fontsize=16);
    plt.axis([4, 6, 0.8, 2.8]);

    plt.subplot(122);
    plt.plot(X[:, 0][y == 1], X[:, 1][y == 1], "g^", label="Iris-Virginica");
    plt.plot(X[:, 0][y == 0], X[:, 1][y == 0], "bs", label="Iris-Versicolor");
    plot_svc_decision_boundary(svm_clf100, 4, 6);
    plt.xlabel("Petal Length(cm)", fontsize=14);
    plt.ylabel("Petal Width(cm)", fontsize=14);
    plt.title("$C = {}$".format(svm_clf100.C), fontsize=16);
    plt.axis([4, 6, 0.8, 2.8]);
    save_fig("Soft_svm_regularization");
    plt.show();


def add_polynomial_features():
    from sklearn.datasets import make_moons
    from sklearn.preprocessing import PolynomialFeatures, StandardScaler
    from sklearn.svm import LinearSVC
    from sklearn.pipeline import Pipeline

    X, y = make_moons(n_samples=100, noise=0.15, random_state=42);

    clf = Pipeline([
        ("poly_feature", PolynomialFeatures(degree=3)),
        ("scaler", StandardScaler()),
        ("svm", LinearSVC(C=10, loss="hinge", max_iter=2000, random_state=42)),
    ]);

    clf.fit(X, y);

    plot_predictions(clf, [-1.5, 2.5, -1, 1.5]);
    plot_binary_dataset(X, y, [-1.5, 2.5, -1, 1.5]);


    plt.show();


def polynomial_kernel_SVC():
    from sklearn.datasets import make_moons
    from sklearn.preprocessing import StandardScaler
    from sklearn.svm import SVC
    from sklearn.pipeline import Pipeline

    X, y = make_moons(n_samples=100, noise=0.15, random_state=42);

    svm_clf1 = Pipeline([
        ("scaler", StandardScaler()),
        ("svm", SVC(kernel="poly", degree=3, coef0=1, C=5)),
    ]);
    svm_clf2 = Pipeline([
        ("scaler", StandardScaler()),
        ("svm", SVC(kernel="poly", degree=10, coef0=100, C=5))
    ]);

    svm_clf1.fit(X, y);
    svm_clf2.fit(X ,y);

    plt.figure(figsize=(11, 4));

    plt.subplot(121);
    plot_predictions(svm_clf1, [-1.5, 2.5, -1, 1.5]);
    plot_binary_dataset(X, y, [-1.5, 2.5, -1, 1.5]);
    plt.title(r"$d=3, r=1, C=5$", fontsize=18);

    plt.subplot(122);
    plot_predictions(svm_clf2, [-1,5, 2.5, -1, 1.5]);
    plot_binary_dataset(X, y, [-1.5, 2.5, -1, 1.5]);
    plt.title(r"$d=10, r=100, C=5$", fontsize=18);

    save_fig("moon_classification_poly_kernel_svc");
    plt.show();


def gaussian_rbf_kernel():
    def gaussian_rbf(x, landmark, gamma):
        return np.exp(-gamma * np.linalg.norm(x - landmark, axis=1)**2);

    gamma = 0.3;

    x1 = np.linspace(-4.5, 4.5, 200).reshape(-1, 1);
    x2 = gaussian_rbf(x1, -2, gamma);
    x3 = gaussian_rbf(x1, 1, gamma);

    X1D = np.linspace(-4, 4, 9).reshape(-1, 1)
    X1 = np.c_[gaussian_rbf(X1D, -2, gamma), gaussian_rbf(X1D, 1, gamma)];
    y1 = np.array([0, 0, 1, 1, 1, 1, 1, 0, 0]);

    plt.figure(figsize=(11, 4));

    plt.subplot(121);
    plt.grid(True, which="both");
    plt.axhline(y=0, color='k');
    plt.scatter(x=[-2, 1], y=[0,0], s=150, alpha=0.5, c="red");
    plt.plot(X1D[:, 0][y1==0], np.zeros(4), "bs");
    plt.plot(X1D[:, 0][y1==1], np.zeros(5), "g^");
    plt.plot(x1, x2, "g--");
    plt.plot(x1, x3, "b:");
    plt.gca().get_yaxis().set_ticks([0, 0.25, 0.5, 0.75, 1]);
    plt.xlabel(r"$x_1$", fontsize=20);
    plt.ylabel(r"similarity", fontsize=14);
    plt.annotate(r"$\mathbf{x}$",
                 xy=(X1D[3, 0], 0),
                 xytext=(-0.5, 0.20),
                 ha="center",
                 arrowprops=dict(facecolor="black", shrink=0.1),
                 fontsize=18,);
    plt.text(-2, 0.9, "$x_2$", ha="center", fontsize=20);
    plt.text(1, 0.9, "$x_3$", ha="center", fontsize=20);
    plt.axis([-4.5, 4.5, -0.1, 1.1]);

    plt.subplot(122);
    plt.grid(True, which="both");
    plt.axhline(y=0, color="k");
    plt.axvline(x=0, color="k");
    plt.plot(X1[:, 0][y1==0], X1[:, 1][y1==0], "bs");
    plt.plot(X1[:, 0][y1==1], X1[:, 1][y1==1], "g^");
    plt.xlabel(r"$x_2$", fontsize=20);
    plt.ylabel(r"$x_3$", fontsize=20, rotation=0);
    plt.annotate(r"$\phi=\left(\mathbf{x}\right)$",
                 xy=(X1[3, 0], X1[3, 1]),
                 xytext=(0.65, 0.50),
                 ha="center",
                 arrowprops=dict(facecolor="black", shrink=0.1),
                 fontsize=18,
                 );
    plt.plot([-0.1, 1.1], [0.57, -0.1], "r--", linewidth=3);
    plt.axis([-0.1, 1.1, -0.1, 1.1]);
    plt.subplots_adjust(right=1);
    save_fig("example_for_Gaussian_RBF_kernel");
    plt.show();


def gaussian_kernel_SVC():
    from sklearn.datasets import make_moons
    from sklearn.preprocessing import StandardScaler
    from sklearn.svm import SVC
    from sklearn.pipeline import Pipeline

    X, y = make_moons(n_samples=100, noise=0.15, random_state=42);


    gamma1, gamma2 = 0.1, 5;
    C1, C2 = 0.001, 1000;

    hyperparams = (gamma1, C1), (gamma1, C2), (gamma2, C1), (gamma2, C2)
    svm_clf = [];

    for gamma, C in hyperparams:
        rbf_svm = Pipeline([
            ("scaler", StandardScaler()),
            ("svm", SVC(kernel="rbf", gamma=gamma, C=C))
        ]);
        rbf_svm.fit(X, y);
        svm_clf.append(rbf_svm);

    plt.figure(figsize=(11, 7));

    for i, model in enumerate(svm_clf):
        plt.subplot(221 + i);
        plot_predictions(model, [-1.5, 2.5, -1, 1.5]);
        plot_binary_dataset(X, y, [-1.5, 2.5, -1, 1.5]);
        gamma, C = hyperparams[i];
        plt.title(r"$\gamma = {}, C={}$".format(gamma, C), fontsize=16);

    save_fig("rbf_kernel_SVC_moons");
    plt.show();



def regression_linear_svm():
    from sklearn.svm import LinearSVR

    np.random.seed(42);
    size = 50;
    theta = np.array([4.0, 3.0]);

    # X ~ uniform(0, 2)
    X = 2 * np.random.rand(size, 1);
    # y = 3X + 4 + noise where noise ~ gaussian(0, 1)
    y = theta[0] + theta[1]*X + np.random.randn(size, 1);
    y = y.ravel();


    reg1 = LinearSVR(epsilon=1.5, random_state=42);
    reg2 = LinearSVR(epsilon=0.5, random_state=42);

    reg1.fit(X, y);
    reg2.fit(X, y);


    def find_support_vectors(model, X, y):
        pred = model.predict(X);
        off_margin = (np.abs(y - pred) >= model.epsilon);
        return np.argwhere(off_margin);

    reg1.support_ = find_support_vectors(reg1, X, y);
    reg2.support_ = find_support_vectors(reg2, X, y);

    eps_x1 = 1;
    eps_y1 = reg1.predict([[eps_x1]]);

    plt.figure(figsize=(9, 4));

    plt.subplot(121);
    plot_svm_regression(reg1, X, y, [0, 2, 3, 11]);
    plt.title(r"$\epsilon = {}$".format(reg1.epsilon), fontsize=18);
    plt.ylabel(r"$y$", fontsize=18, rotation=0);
    plt.annotate("",
                 xy=(eps_x1, eps_y1), xycoords='data',
                 xytext=(eps_x1, eps_y1 - reg1.epsilon),
                 textcoords='data',
                 arrowprops=dict(arrowstyle="<->", linewidth=1.5));
    plt.text(0.91, 5.6, r"$\epsilon$", fontsize=20);

    plt.subplot(122);
    plot_svm_regression(reg2, X, y, [0, 2, 3, 11]);
    plt.title(r"$\epsilon = {}$".format(reg2.epsilon), fontsize=18);
    save_fig("svm_linear_regression");
    plt.show();


def regression_nonlinear_svm():
    from sklearn.svm import SVR

    np.random.seed(42);
    size = 100;
    theta = [0.2, 0.1, 0.5];
    # X ~ uniform(-1, 1)
    X = 2 * np.random.rand(size, 1) -1;
    # y = <theta, [1, x, x^2] > + noise where noise ~ N(0, 1/10)
    y = (theta[0] + theta[1]*X + theta[2]*X**2 + np.random.randn(size, 1)/10).ravel();

    reg1 = SVR(kernel="poly", gamma='auto', degree=2, C=100, epsilon=0.1);
    reg2 = SVR(kernel="poly", gamma='auto', degree=2, C=0.01, epsilon=0.1);

    reg1.fit(X, y);
    reg2.fit(X, y);

    plt.figure(figsize=(9, 4));

    plt.subplot(121);
    plot_svm_regression(reg1, X, y, [-1, 1, 0, 1]);
    plt.title(r"$degree={}, C={}, \epsilon={}$".format(reg1.degree, reg1.C, reg1.epsilon), fontsize=18);
    plt.ylabel(r"$y", fontsize=18, rotation=0);

    plt.subplot(122);
    plot_svm_regression(reg2, X, y, [-1, 1, 0, 1]);
    plt.title(r"$degree={}, C={}, \epsilon={}$".format(reg2.degree, reg2.C, reg2.epsilon), fontsize=18);

    save_fig("svm_nonlinear_regression");
    plt.show();




""" Some Additional contents"""
def training_time_svm():
    from sklearn.datasets import make_moons
    from sklearn.svm import SVC
    import time

    X, y = make_moons(n_samples=1000, noise=0.4, random_state=42);

    tol = 10;
    tols = [];
    times = [];

    for i in range(13):
        svm_clf = SVC(kernel="poly", gamma=3, C=10, tol=tol);

        start = time.time();
        svm_clf.fit(X, y);
        end = time.time();

        times.append(end-start);
        tols.append(tol);
        print("{}-th iteration : tol - {}, time - {}".format(i, tol, end-start));
        tol /= 10;

    plt.rcParams["font.family"] = "stixgeneral";
    plt.semilogx(tols, times);
    plt.rcParams["font.family"] = "NanumBarunGothic";
    save_fig("training_time");
    plt.show();




""" Implementation of Binary Linear SVM by using bath gradient descent """
from sklearn.base import BaseEstimator

class MyBinaryLinearSVC(BaseEstimator):
    def __init__(self, C=1, eta0=0.1, eta_d=10000, n_epochs=1000, random_state=None):
        self.C = C;
        self.eta0 = eta0;
        self.eta_d = eta_d;
        self.n_epochs = n_epochs;
        self.random_state = random_state;

        self.loss = [];
        self.intercept_ = None;
        self.coef_ = None;
        self.support_vectors_ = None;


    def eta(self, epoch):
        return self.eta0 / (epoch + self.eta_d);

    def fit(self, X, y):
        if self.random_state:
            np.random.seed(self.random_state);

        # X.shape = (n_data, n_feature)
        n_data = len(X);
        W = np.random.randn(X.shape[1], 1);
        b = 0;

        # y : 0 or 1 => t : -1 or 1
        t = 2*y -1;
        X_t = X * t;

        # Training
        for epoch in range(self.n_epochs):
            # not satisfy the constraint of margin linear SVM
            support_vector_idx = (X_t.dot(W) + t*b < 1).ravel();
            X_t_support = X_t[support_vector_idx];
            t_support = t[support_vector_idx];

            loss = 1/2 * np.sum(W*W) + self.C * (np.sum(1 - X_t_support.dot(W)) - b*np.sum(t_support));
            self.loss.append(loss);

            # Calculate gradient of the loss
            grad_W = W - self.C *np.sum(X_t_support, axis=0).reshape(-1, 1);
            grad_b = -self.C * np.sum(t_support);

            # Apply Gradient descent
            W = W - self.eta(epoch) * grad_W;
            b = b - self.eta(epoch) * grad_b;


        self.intercept_ = np.array([b]);
        self.coef_ = np.array([W]);
        support_vector_idx = (X_t.dot(W) + t*b<1).ravel();
        self.support_vectors_ = X[support_vector_idx];
        return self;

    def decision_function(self, X):
        return X.dot(self.coef_[0]) + self.intercept_[0];

    def predict(self, X):
        return (self.decision_function(X)>=0).astype(np.float64);


def iris_mySVC():
    from sklearn.datasets import load_iris
    iris = load_iris();

    X = iris["data"][:, (2, 3)];
    y = (iris["target"]==2).astype(np.float64).reshape(-1, 1);

    C = 2;

    clf = MyBinaryLinearSVC(C=C, eta0=10, eta_d=1000, n_epochs=60000, random_state=42);
    clf.fit(X, y);

    plt.plot(range(clf.n_epochs), clf.loss);
    plt.axis([0, clf.n_epochs, 0, 100]);
    save_fig("mySVC_model_loss_function");
    plt.show();


def mySVC_vs_scikit():
    from sklearn.svm import SVC
    from sklearn.linear_model import SGDClassifier
    from sklearn.datasets import load_iris
    iris = load_iris();

    X = iris["data"][:, (2, 3)];
    y = (iris["target"] == 2).astype(np.float64).reshape(-1, 1);

    C = 2;
    my_clf = MyBinaryLinearSVC(C=C, eta0=10, eta_d=1000, n_epochs=60000, random_state=42);
    my_clf.fit(X, y);

    scikit_svc = SVC(kernel="linear", C=C);
    scikit_svc.fit(X, y.ravel());

    scikit_SGD = SGDClassifier(loss="hinge", alpha=0.017, max_iter=50, random_state=42);
    scikit_SGD.fit(X, y.ravel());

    m = len(X);
    t = y * 2 - 1;
    X_b = np.c_[np.ones((m, 1)), X];
    X_b_t = X_b * t;
    sgd_theta = np.r_[scikit_SGD.intercept_[0], scikit_SGD.coef_[0]];
    support_vectors_idx = (X_b_t.dot(sgd_theta) < 1).ravel();
    scikit_SGD.support_vectors_ = X[support_vectors_idx];
    scikit_SGD.C = C;

    print("Parameters of my SVC model - ");
    print("weight : {}, bias : {}".format(np.squeeze(my_clf.coef_, axis=0), my_clf.intercept_));
    print("Parameters of scikit SVC model - ");
    print("weight : {}, bias : {}".format(scikit_svc.coef_, scikit_svc.intercept_));
    print("Parameters of scikit SGD model - ");
    print("weight : {}, bias : {}".format(scikit_SGD.coef_[0], scikit_SGD.intercept_[0]));

    y_ravel = y.ravel();

    plt.figure(figsize=(12, 4.8));

    plt.subplot(131);
    plt.plot(X[:, 0][y_ravel==1], X[:, 1][y_ravel==1], "g^", label="Iris-Virginica");
    plt.plot(X[:, 0][y_ravel == 0], X[:, 1][y_ravel == 0], "bs", label="Not Iris-Virginica");
    plt.xlabel("Petal Length(cm)", fontsize=14);
    plt.ylabel("Petal Width(cm)", fontsize=14);
    plot_svc_decision_boundary(my_clf, 4, 6);
    plt.title("MyLinearSVM")
    plt.axis([4, 6, 0.8, 2.8]);

    plt.subplot(132);
    plt.plot(X[:, 0][y_ravel == 1], X[:, 1][y_ravel == 1], "g^", label="Iris-Virginica");
    plt.plot(X[:, 0][y_ravel == 0], X[:, 1][y_ravel == 0], "bs", label="Not Iris-Virginica");
    plt.xlabel("Petal Length(cm)", fontsize=14);
    plot_svc_decision_boundary(scikit_svc, 4, 6);
    plt.title("scikit LinearSVC");
    plt.axis([4, 6, 0.8, 2.8]);

    plt.subplot(133);
    plt.plot(X[:, 0][y_ravel == 1], X[:, 1][y_ravel == 1], "g^", label="Iris-Virginica");
    plt.plot(X[:, 0][y_ravel == 0], X[:, 1][y_ravel == 0], "bs", label="Not Iris-Virginica");
    plt.xlabel("Petal Length(cm)", fontsize=14);
    plot_svc_decision_boundary(scikit_SGD, 4, 6);
    plt.title("SGDClassifier");
    plt.axis([4, 6, 0.8, 2.8]);
    save_fig("Comparison_mySVM_vs_Scikit");
    plt.show();



""" Exercise 8 : Apply LinearSVC and compare it with SVC and SGDClassifier"""
def exercise5_8():
    from sklearn.datasets import load_iris
    from sklearn.svm import LinearSVC, SVC
    from sklearn.linear_model import SGDClassifier
    from sklearn.preprocessing import StandardScaler

    iris = load_iris();
    X = iris["data"][:, (2, 3)];
    y = iris["target"];

    setosa_or_versicolor_idx = (y==0) | (y==1);
    X = X[setosa_or_versicolor_idx];
    y = y[setosa_or_versicolor_idx];

    scaler = StandardScaler();
    X_scaled = scaler.fit_transform(X, y);

    C = 5;
    alpha = 1 / (C*len(X));

    lin_clf = LinearSVC(loss="hinge", C=C, random_state=42);
    svm_clf = SVC(kernel="linear", C=C);
    sgd_clf = SGDClassifier(loss="hinge", learning_rate="constant", eta0=0.001,
                            alpha=alpha, max_iter=100000, random_state=42);

    lin_clf.fit(X_scaled, y);
    svm_clf.fit(X_scaled, y);
    sgd_clf.fit(X_scaled, y);


    print("LinearSVC               : ", lin_clf.intercept_, lin_clf.coef_);
    print("SVM                     : ", svm_clf.intercept_, svm_clf.coef_);
    print("SGDClassifier(alpha={:.5f}) : ".format(sgd_clf.alpha), sgd_clf.intercept_, sgd_clf.coef_);

    # find the decision boundary
    w1 = -lin_clf.coef_[0, 0]/lin_clf.coef_[0, 1];
    b1 = -lin_clf.intercept_[0] / lin_clf.coef_[0, 1];
    line1 = [[-10, -10*w1 + b1],[10, 10*w1 + b1]];

    w2 = -svm_clf.coef_[0, 0] / svm_clf.coef_[0, 1];
    b2 = -svm_clf.intercept_[0] / svm_clf.coef_[0, 1];
    line2 = [[-10, -10 * w2 + b2], [10, 10 * w2 + b2]];

    w3 = -sgd_clf.coef_[0, 0] / sgd_clf.coef_[0, 1];
    b3 = -sgd_clf.intercept_[0] / sgd_clf.coef_[0, 1];
    line3 = [[-10, -10 * w3 + b3], [10, 10 * w3 + b3]];

    # Inverse transform of scaled parameters
    inverse_line1 = scaler.inverse_transform(line1);
    inverse_line2 = scaler.inverse_transform(line2);
    inverse_line3 = scaler.inverse_transform(line3);

    plt.figure(figsize=(11, 4));
    plt.plot(inverse_line1[:, 0], inverse_line1[:, 1], "k:", label="LinearSVC");
    plt.plot(inverse_line2[:, 0], inverse_line2[:, 1], "b--", label="SVC");
    plt.plot(inverse_line3[:, 0], inverse_line3[:, 1], "r-", label="SGD");
    plt.plot(X[:, 0][y==1], X[:, 1][y==1], "bs");
    plt.plot(X[:, 0][y==0], X[:, 1][y==0], "yo");
    plt.xlabel("Petal length", fontsize=14);
    plt.ylabel("Petal width", fontsize=14);
    plt.legend(loc="upper center", fontsize=14);
    plt.axis([0, 5.5, 0, 2]);
    plt.title("Comparison SVM");

    save_fig("Exercise5_8_comparison_SVM");

    plt.show();


""" Exercise 9 : Apply SVM with OvA to MNIST data(Not finished)"""
def exercise5_9():
    from sklearn.datasets import fetch_mldata
    from sklearn.preprocessing import StandardScaler
    from sklearn.svm import SVC, LinearSVC
    from sklearn.model_selection import RandomizedSearchCV
    from sklearn.metrics import accuracy_score
    from scipy.stats import reciprocal, uniform

    mnist = fetch_mldata("MNIST original", data_home="./");
    x, t = mnist["data"], mnist["target"];
    train_x, train_t = x[:60000], t[:60000];
    test_x, test_t = x[60000:], t[:60000:];

    np.random.seed(42);
    random_idx = np.random.permutation(60000);
    train_x = train_x[random_idx];
    train_t = train_t[random_idx];

    print("1. Linear SVM ");
    lin_clf = LinearSVC(max_iter=10000, random_state=42);
    lin_clf.fit(train_x, train_t);
    pred = lin_clf.predict(test_x);
    score_linear = accuracy_score(pred, test_t);
    print("Test Accuracy(without scaling) : {}".format(score_linear));

    scaler = StandardScaler();
    train_x_scaled = scaler.fit_transform(train_x.astype(np.float32));
    test_x_scaled = scaler.transform(test_x.astype(np.float32));

    lin_clf = LinearSVC(max_iter=10000, random_state=42);
    lin_clf.fit(train_x_scaled, train_t);
    pred = lin_clf.predict(test_x_scaled);
    score = accuracy_score(test_t, pred);
    print("Test Accuracy(with scaling : {}".format(score));







def exercise5_9_svc():
    from sklearn.datasets import fetch_mldata
    from sklearn.preprocessing import StandardScaler
    from sklearn.svm import SVC, LinearSVC
    from sklearn.model_selection import RandomizedSearchCV
    from sklearn.metrics import accuracy_score
    from scipy.stats import reciprocal, uniform

    mnist = fetch_mldata("MNIST original", data_home="./");
    x, t = mnist["data"], mnist["target"];
    train_x, train_t = x[:60000], t[:60000];
    test_x, test_t = x[60000:], t[:60000:];

    np.random.seed(42);
    random_idx = np.random.permutation(60000);
    train_x = train_x[random_idx];
    train_t = train_t[random_idx];

    scaler = StandardScaler();
    train_x_scaled = scaler.fit_transform(train_x.astype(np.float32));
    test_x_scaled = scaler.transform(test_x.astype(np.float32));

    svm_clf = SVC(gamma='auto', decision_function_shape="ovr");



""" Exercise 10 : Apply SVM regression to California housing data """
def exercise5_10():
    from sklearn.datasets import fetch_california_housing
    from sklearn.model_selection import train_test_split, RandomizedSearchCV
    from sklearn.preprocessing import StandardScaler
    from sklearn.svm import SVR
    from sklearn.metrics import mean_squared_error
    from scipy.stats import reciprocal, uniform

    housing = fetch_california_housing();
    X = housing["data"];
    y = housing["target"];

    train_x, test_x, train_y, test_y = train_test_split(X, y, test_size=0.2, random_state=42);

    scaler = StandardScaler();
    train_x_scaled = scaler.fit_transform(train_x);
    test_x_scaled = scaler.transform(test_x);

    rnd_param = {"gamma": reciprocal(0.001, 0.1), "C": uniform(1, 10)};
    rnd_search = RandomizedSearchCV(SVR(), rnd_param, cv=3, n_iter=10, verbose=2, random_state=42, n_jobs=-1);
    rnd_search.fit(train_x_scaled, train_y);

    best_estimator = rnd_search.best_estimator_
    print("Best estimator : \n{}".format(best_estimator));

    train_pred = best_estimator.predict(train_x_scaled);
    train_mse = mean_squared_error(train_y, train_pred);
    train_rmse = np.sqrt(train_mse);

    print("Train RMSE : {}".format(train_rmse));

    test_pred = best_estimator.predict(test_x_scaled);
    test_mse = mean_squared_error(test_y, test_pred);
    test_rmse = np.sqrt(test_mse);

    print("Test RMSE : {}".format(test_rmse));













if __name__== '__main__':
    print("Chapter 5 : Support Vector Machine");
    #large_margin_classification();
    # necessity_scaling_SVM();
    #outlier_SVM();
    #soft_margin_SVM();
    #add_polynomial_features();
    #polynomial_kernel_SVC();
    #gaussian_rbf_kernel();
    #gaussian_kernel_SVC();
    #regression_linear_svm();
    #regression_nonlinear_svm();
    #training_time_svm();
    #iris_mySVC();
    #mySVC_vs_scikit();
    #exercise5_8();
    #exercise5_9();
    exercise5_10();