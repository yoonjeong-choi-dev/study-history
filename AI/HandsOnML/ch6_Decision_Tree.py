from __future__ import division, print_function, unicode_literals

import os

import numpy as np
import matplotlib.pyplot as plt
import matplotlib

""" Modules for visualization of trees"""
from sklearn.tree import export_graphviz
import graphviz

""" Setting of matplotlib """
plt.rcParams['axes.labelsize'] = 14;
plt.rcParams['xtick.labelsize'] = 12;
plt.rcParams['ytick.labelsize'] = 12;

""" Useful function """
PROJECT_ROOT_DIR = ".";
CHAPTER_ID = "decision_tree";

# Save the graph
def save_fig(fig_id, tight_layout=True):

    path = os.path.join(PROJECT_ROOT_DIR, "My_images", CHAPTER_ID, fig_id+".png");
    if tight_layout:
        plt.tight_layout();

    if not (os.path.isdir(os.path.join(PROJECT_ROOT_DIR, "My_images", CHAPTER_ID))):
        os.makedirs(os.path.join(PROJECT_ROOT_DIR, "My_images", CHAPTER_ID));

    plt.savefig(path, format='png', dpi=300);
    print("figure is saved...........................!")

def image_path(fig_id):
    return os.path.join(PROJECT_ROOT_DIR, "My_images", CHAPTER_ID, fig_id)

def read_decision_tree(filename):
    file = filename + ".png";
    plt.figure(figsize=(14, 18));
    file_dir = "My_images/decision_tree/"+file;
    plt.imshow(plt.imread(file_dir));
    plt.axis("off");


def save_decision_tree(tree, filename,feature_names=None, class_name=None, max_depth=None):
    file = filename + ".dot";
    export_graphviz(tree, out_file=image_path(file),
                    feature_names=feature_names,
                    class_names=class_name, max_depth=max_depth,
                    rounded=True, filled=True);

    file_dir = "My_images/decision_tree/"+file;
    print(file_dir)
    with open(file_dir) as f:
        dot_graph = f.read();

    dot = graphviz.Source(dot_graph);
    dot.format = "png";
    dot.render(filename=filename, directory="My_images/decision_tree", cleanup=True);


def plot_decision_boundary_tree(tree, X, y, axes=[0, 7.5, 0, 3], iris=True,
                                legend=False, plot_training=True):
    from matplotlib.colors import ListedColormap

    x1 = np.linspace(axes[0], axes[1], 100);
    x2 = np.linspace(axes[2], axes[3], 100);
    mesh_x, mesh_y = np.meshgrid(x1, x2);
    mesh = np.c_[mesh_x.ravel(), mesh_y.ravel()];
    pred = tree.predict(mesh).reshape(mesh_x.shape);

    custom_cmap = ListedColormap(['#fafab0', '#9898ff', '#a0faa0']);
    plt.contourf(mesh_x, mesh_y, pred, alpha=0.3, cmap=custom_cmap);

    if not iris:
        custom_cmap2 = ListedColormap(['#7d7d58','#4c4c7f','#507d50']);
        plt.contour(x1, x2, pred, cmap=custom_cmap2, alpha=0.8);

    if plot_training:
        plt.plot(X[:, 0][y == 0], X[:, 1][y == 0], "yo", label="Iris-Setosa");
        plt.plot(X[:, 0][y == 1], X[:, 1][y == 1], "bs", label="Iris-Versicolor");
        plt.plot(X[:, 0][y == 2], X[:, 1][y == 2], "g^", label="Iris-Virginica");
        plt.axis(axes);

    if iris:
        plt.xlabel("Petal length(cm)", fontsize=14);
        plt.ylabel("Petal width(cm)", fontsize=14);
    else:
        plt.xlabel(r"$x_0$", fontsize=18);
        plt.ylabel(r"$x_1$", fontsize=18);

    if legend:
        plt.legend(loc="lower right", fontsize=14);


def plot_regression_prediction(tree, X, y, axes=[0, 1, -0.2, 1], ylabel="$y$"):
    test_x = np.linspace(axes[0], axes[1], 500).reshape(-1, 1);
    pred = tree.predict(test_x);

    plt.axis(axes);
    plt.xlabel("$x_1$", fontsize=18);
    if ylabel:
        plt.ylabel(ylabel, fontsize=18, rotation=0);
    plt.plot(X, y, "b.");
    plt.plot(test_x, pred, "r.-", linewidth=2, label=r"$\hat{y}$");



""" Main Code """
def training_and_visualization():
    from sklearn.datasets import load_iris
    from sklearn.tree import DecisionTreeClassifier

    iris = load_iris();
    X = iris.data[:, 2:];
    y = iris.target;

    tree_clf = DecisionTreeClassifier(max_depth=2, random_state=42);
    tree_clf.fit(X, y);
    export_graphviz(tree_clf, out_file=image_path("iris_tree.dot"),
                    feature_names=["Petal length(cm)", "Petal width(cm)"],
                    class_names=iris.target_names,
                    rounded=True, filled=True);

    with open("My_images/decision_tree/iris_tree.dot") as f:
        dot_graph = f.read();

    dot = graphviz.Source(dot_graph);
    dot.format = "png";
    dot.render(filename="iris_tree", directory="My_images/decision_tree", cleanup=True);

    read_decision_tree("iris_tree");


def my_visualization_tree():
    from sklearn.datasets import load_iris
    from sklearn.tree import DecisionTreeClassifier

    iris = load_iris();
    X = iris.data[:, 2:];
    y = iris.target;

    tree_clf = DecisionTreeClassifier(max_depth=2, random_state=42);
    tree_clf.fit(X, y);

    save_decision_tree(tree_clf, "my_tree_fig", ["Petal length(cm)", "Petal width(cm)"],
                       iris.target_names);
    read_decision_tree("my_tree_fig");



def decision_boundary_tree():
    from sklearn.datasets import load_iris
    from sklearn.tree import DecisionTreeClassifier

    iris = load_iris();
    X = iris.data[:, 2:];
    y = iris.target;

    tree_clf = DecisionTreeClassifier(max_depth=2, random_state=42);
    tree_clf.fit(X, y);

    plt.figure(figsize=(8, 4));
    plot_decision_boundary_tree(tree_clf, X, y);
    plt.plot([2.45, 2.45], [0, 3], "k-", linewidth=2);
    plt.plot([2.45, 7.5], [1.75, 1.75], "k--", linewidth=2);
    plt.plot([4.95, 4.95], [0, 1.75], "k:", linewidth=2);
    plt.plot([4.85, 4.85], [1.75, 3], "k:", linewidth=2);
    plt.text(1.40, 1.0, "depth=0", fontsize=15);
    plt.text(3.2, 1.80, "depth=1", fontsize=13);
    plt.text(4.05, 0.5, "(depth=2)", fontsize=11);
    save_fig("decision_boundary_of_tree_in_IRIS");
    plt.show();



def constraint_tree_classification():
    from sklearn.datasets import make_moons
    from sklearn.tree import DecisionTreeClassifier

    X, y =make_moons(n_samples=100, noise=0.25, random_state=53);

    tree1 = DecisionTreeClassifier(random_state=42);
    tree2 = DecisionTreeClassifier(min_samples_leaf=4, random_state=42);

    tree1.fit(X, y);
    tree2.fit(X, y);

    plt.figure(figsize=(11, 4));

    plt.subplot(121);
    plot_decision_boundary_tree(tree1, X, y, axes=[-1.5, 2.5, -1, 1.5], iris=False);
    plt.title("No Constraint");

    plt.subplot(122);
    plot_decision_boundary_tree(tree2, X, y, axes=[-1.5, 2.5, -1, 1.5], iris=False);
    plt.title("min_sample_leaf = 4");
    save_fig("constraint_min_sample_leaf");

    plt.show();


def tree_regression():
    from sklearn.tree import DecisionTreeRegressor

    np.random.seed(42);
    size = 200;
    X = np.random.rand(size, 1);
    y = 4 * (X -0.5)**2;
    noise = np.random.randn(size, 1) /10;
    y = y + noise;

    tree_reg1 = DecisionTreeRegressor(max_depth=2, random_state=42);
    tree_reg2 = DecisionTreeRegressor(max_depth=3, random_state=42);

    tree_reg1.fit(X, y);
    tree_reg2.fit(X, y);

    plt.figure(figsize=(11, 4));

    plt.subplot(121);
    plot_regression_prediction(tree_reg1, X, y);

    for split, style in ((0.1973, "k-"), (0.0917, "k--"), (0.7718, "k--")):
        plt.plot([split, split], [-0.2, 1], style, linewidth=2);
    plt.text(0.21, 0.65, "depth=0", fontsize=15);
    plt.text(0.01, 0.2, "depth=1", fontsize=13);
    plt.text(0.65, 0.8, "depth=1", fontsize=13);
    plt.legend(loc="upper center", fontsize=18);
    plt.title("max_depth=2", fontsize=14);

    plt.subplot(122);
    plot_regression_prediction(tree_reg2, X, y, ylabel=None);

    for split, style in ((0.1973, "k-"), (0.0917, "k--"), (0.7718, "k--")):
        plt.plot([split, split], [-0.2, 1], style, linewidth=2);
    for split in (0.0458, 0.1298, 0.2873, 0.9040):
        plt.plot([split, split], [-0.2, 1], "k:", linewidth=1);

    plt.text(0.3, 0.5, "depth=2", fontsize=13);
    plt.title("max_depth=3", fontsize=14);
    save_fig("tree_regression");

    save_decision_tree(tree_reg1, "tree_regression_decision_tree", feature_names=["x1"]);


    read_decision_tree("tree_regression_decision_tree");

    plt.show();


def constraint_tree_regression():
    from sklearn.tree import DecisionTreeRegressor

    np.random.seed(42);
    size = 200;
    X = np.random.rand(size, 1);
    y = 4 * (X - 0.5) ** 2;
    noise = np.random.randn(size, 1) / 10;
    y = y + noise;

    tree_reg1 = DecisionTreeRegressor(random_state=42);
    tree_reg2 = DecisionTreeRegressor(min_samples_leaf=10, random_state=42);

    tree_reg1.fit(X, y);
    tree_reg2.fit(X, y);

    test_x = np.linspace(0, 1, 500).reshape(-1, 1);
    pred1 = tree_reg1.predict(test_x);
    pred2 = tree_reg2.predict(test_x);

    plt.figure(figsize=(11, 4));

    plt.subplot(121);
    plt.plot(X, y, "b.");
    plt.plot(test_x, pred1, "r.-", linewidth=2, label=r"$\hat{y}$");
    plt.axis([0, 1, -0.2, 1.1]);
    plt.xlabel("$x_1$", fontsize=18);
    plt.ylabel("$y$", fontsize=18, rotation=0);
    plt.legend(loc="upper center", fontsize=18);
    plt.title("No constraint", fontsize=14);

    plt.subplot(122);
    plt.plot(X, y, "b.");
    plt.plot(test_x, pred2, "r.-", linewidth=2, label=r"$\hat{y}$");
    plt.axis([0, 1, -0.2, 1.1]);
    plt.xlabel("$x_1$", fontsize=18);
    plt.title("min_sample_leaf={}".format(tree_reg2.min_samples_leaf), fontsize=14);
    save_fig("tree_regression_regularization");
    plt.show();



""" Exercise 7 : hyper-parameters tuning of Decision Tree with moons-dataset"""
def exercise6_7():
    from sklearn.datasets import make_moons
    from sklearn.model_selection import train_test_split, GridSearchCV
    from sklearn.tree import DecisionTreeClassifier
    from sklearn.metrics import accuracy_score

    np.random.seed(42);
    X, y = make_moons(n_samples=10000, noise=0.4, random_state=42);

    train_x, test_x, train_y, test_y = train_test_split(X, y, test_size=0.2, random_state=42);


    params_grid = {"max_leaf_nodes": list(range(2, 100)), "min_samples_split": [2, 3, 4]};
    grid_cv = GridSearchCV(DecisionTreeClassifier(random_state=42), params_grid, cv=3, verbose=1, n_jobs=-1);

    grid_cv.fit(train_x, train_y);

    best_estimator = grid_cv.best_estimator_
    best_params = grid_cv.best_params_;
    test_pred = best_estimator.predict(test_x);
    test_acc = accuracy_score(test_pred, test_y);

    print("Best parameters : {}".format(best_params));
    print("Test Accuracy : {}".format(test_acc));


""" Exercise 8 : Make Random Forest Model """
def exercise6_8():
    from sklearn.datasets import make_moons
    from sklearn.model_selection import train_test_split, ShuffleSplit
    from sklearn.tree import DecisionTreeClassifier
    from sklearn.metrics import accuracy_score
    from sklearn.base import clone


    params = {'max_leaf_nodes': 17, 'min_samples_split': 2};

    np.random.seed(42);
    X, y = make_moons(n_samples=10000, noise=0.4, random_state=42);

    train_x, test_x, train_y, test_y = train_test_split(X, y, test_size=0.2, random_state=42);

    n_tree = 1000;
    n_samples = 100;

    mini_sets = [];

    shuffle = ShuffleSplit(n_splits=n_tree, test_size=len(train_x)-n_samples, random_state=42);
    for train_idx, test_idx in shuffle.split(train_x):
        mini_train_x = train_x[train_idx];
        mini_train_y = train_y[train_idx];
        mini_sets.append((mini_train_x, mini_train_y));

    best_tree = DecisionTreeClassifier(random_state=42, **params);

    forest = [clone(best_tree) for _ in range(n_tree)];

    test_acc = [];

    # Train each tree
    for tree, (mini_train_x, mini_train_y) in zip(forest, mini_sets):
        tree.fit(mini_train_x, mini_train_y);

        pred = tree.predict(test_x);
        acc = accuracy_score(pred, test_y);
        test_acc.append(acc);

    mean_acc = np.mean(test_acc);
    print("original mean accuracy : {}".format(mean_acc));

    pred = np.empty([n_tree, len(test_x)], dtype=np.uint8);

    for idx, tree in enumerate(forest):
        pred[idx] = tree.predict(test_x);

    from scipy.stats import mode;

    pred_majority_vote, n_vote = mode(pred, axis=0);
    majority_acc = accuracy_score(test_y, pred_majority_vote.reshape([-1]));
    print("Majority vote accuracy : {}".format(majority_acc));




























if __name__== '__main__':
    print("Chapter 6 : Decision Tree");
    #training_and_visualization();
    #my_visualization_tree();
    #decision_boundary_tree();
    #constraint_tree_classification();
    #tree_regression();
    #constraint_tree_regression();
    #exercise6_7();
    exercise6_8();