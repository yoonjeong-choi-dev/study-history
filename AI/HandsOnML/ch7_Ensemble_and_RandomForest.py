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
CHAPTER_ID = "ensemble_and_randomforest";

# Save the graph
def save_fig(fig_id, tight_layout=True):

    path = os.path.join(PROJECT_ROOT_DIR, "My_images", CHAPTER_ID, fig_id+".png");
    if tight_layout:
        plt.tight_layout();

    if not (os.path.isdir(os.path.join(PROJECT_ROOT_DIR, "My_images", CHAPTER_ID))):
        os.makedirs(os.path.join(PROJECT_ROOT_DIR, "My_images", CHAPTER_ID));

    plt.savefig(path, format='png', dpi=300);
    print("figure is saved...........................!")



def plot_decision_boundary_tree(clf, X, y, axes=[-1.5, 2.5, -1, 1.5], alpha=0.5, contour=True, data=True):
    from matplotlib.colors import ListedColormap

    x1 = np.linspace(axes[0], axes[1], 100);
    x2 = np.linspace(axes[2], axes[3], 100);

    mesh_x, mesh_y = np.meshgrid(x1, x2);
    mesh = np.c_[mesh_x.ravel(), mesh_y.ravel()];
    pred = clf.predict(mesh).reshape(mesh_x.shape);

    custom_cmap = ListedColormap(['#fafab0', '#9898ff', '#a0faa0']);
    plt.contourf(mesh_x, mesh_y, pred, alpha=0.3, cmap=custom_cmap);

    if contour:
        custom_cmap2 = ListedColormap(['#7d7d58', '#4c4c7f', '#507d50']);
        plt.contour(mesh_x, mesh_y, pred, alpha=0.8, cmap=custom_cmap2);

    if data:
        plt.plot(X[:, 0][y==0], X[:, 1][y==0], "yo", alpha=alpha);
        plt.plot(X[:, 0][y == 1], X[:, 1][y == 1], "bs", alpha=alpha);

    plt.axis(axes);
    plt.xlabel(r"$x_1$", fontsize=18);
    plt.ylabel(r"$x_2$", fontsize=18);


def plot_prediction(regressors, X, y, axes, label=None, style="r-", data_style="b.", data_label=None):
    x = np.linspace(axes[0], axes[1], 500);
    pred = sum(regressor.predict(x.reshape(-1, 1)) for regressor in regressors);
    plt.plot(X[:, 0], y, data_style, label=data_label);
    plt.plot(x, pred, style, linewidth=2, label=label);
    if label or data_label:
        plt.legend(loc="upper center", fontsize=16);
    plt.axis(axes);


""" Main Code """
def stochastic_unbalanced_coin_toss():
    head_prob = 0.51;
    coin_toss = (np.random.rand(10000, 10) < head_prob).astype(np.int32);
    cumulative_head_ratio = np.cumsum(coin_toss, axis=0) / np.arange(1, 10001).reshape(-1, 1);

    plt.figure(figsize=(8, 3.5));
    plt.plot(cumulative_head_ratio);
    plt.plot([0, 10000], [0.51, 0.51], "k--", linewidth=2, label="51%");
    plt.plot([0, 10000], [0.5, 0.5], "k-", linewidth=2, label="50%");
    plt.xlabel("Number of toss");
    plt.ylabel("Ratio of head coins");
    plt.legend(loc="lower right");
    plt.axis([0, 10000, 0.42, 0.58]);
    save_fig("stochastic_unbalanced_coin_toss")
    plt.show();


def vote_based_classifier():
    from sklearn.datasets import make_moons
    from sklearn.model_selection import train_test_split
    from sklearn.ensemble import RandomForestClassifier, VotingClassifier
    from sklearn.linear_model import LogisticRegression
    from sklearn.svm import SVC
    from sklearn.metrics import accuracy_score

    X, y =make_moons(n_samples=500, noise=0.30, random_state=42);
    train_x, test_x, train_y, test_y = train_test_split(X, y, random_state=42);

    log_clf = LogisticRegression(solver="liblinear", random_state=42);
    rdf_clf = RandomForestClassifier(n_estimators=10, random_state=42);
    svm_clf = SVC(gamma="auto", probability=True, random_state=42);

    voting_clf_soft = VotingClassifier(
        estimators=[("lr", log_clf), ("rf", rdf_clf), ("svm", svm_clf)],
        voting="soft");

    voting_clf_hard = VotingClassifier(
        estimators=[("lr", log_clf), ("rf", rdf_clf), ("svm", svm_clf)],
        voting="hard");

    for clf in (log_clf, rdf_clf, svm_clf):
        clf.fit(train_x, train_y);
        test_pred = clf.predict(test_x);
        test_acc = accuracy_score(test_pred, test_y);
        print("{} -  accuracy : {}".format(clf.__class__.__name__, test_acc));

    voting_clf_hard.fit(train_x, train_y);
    voting_clf_soft.fit(train_x, train_y);

    hard_pred = voting_clf_hard.predict(test_x);
    soft_pred = voting_clf_soft.predict(test_x);

    hard_acc = accuracy_score(hard_pred, test_y);
    soft_acc = accuracy_score(soft_pred, test_y);

    print("Hard voting - accuracy : {}".format(hard_acc));
    print("Soft voting - accuracy : {}".format(soft_acc));


def bagging_decision_tree():
    from sklearn.datasets import make_moons
    from sklearn.model_selection import train_test_split
    from sklearn.tree import DecisionTreeClassifier
    from sklearn.ensemble import BaggingClassifier
    from sklearn.metrics import accuracy_score

    X, y = make_moons(n_samples=500, noise=0.30, random_state=42);
    train_x, test_x, train_y, test_y = train_test_split(X, y, random_state=42);

    tree_clf = DecisionTreeClassifier(random_state=42);
    bag_clf = BaggingClassifier(
        DecisionTreeClassifier(random_state=42), n_estimators=500,
        max_samples=100, bootstrap=True, n_jobs=-1, random_state=42
    );

    tree_clf.fit(train_x, train_y);
    bag_clf.fit(train_x, train_y);

    tree_pred = tree_clf.predict(test_x);
    bag_pred = bag_clf.predict(test_x);

    tree_acc = accuracy_score(tree_pred, test_y);
    bag_acc = accuracy_score(bag_pred, test_y);

    print("Tree Accuracy : {}".format(tree_acc));
    print("Bagging Tree Accuracy : {}".format(bag_acc));

    plt.figure(figsize=(11, 4));

    plt.subplot(121);
    plot_decision_boundary_tree(tree_clf, X, y);
    plt.title("Decision Tree", fontsize=14);

    plt.subplot(122);
    plot_decision_boundary_tree(bag_clf, X, y);
    plt.title("Decision Tree(Bagging)", fontsize=14);

    save_fig("bagging_decision_tree");
    plt.show();


def out_of_bag_sample():
    from sklearn.datasets import make_moons
    from sklearn.model_selection import train_test_split
    from sklearn.tree import DecisionTreeClassifier
    from sklearn.ensemble import BaggingClassifier
    from sklearn.metrics import accuracy_score

    X, y = make_moons(n_samples=500, noise=0.30, random_state=42);
    train_x, test_x, train_y, test_y = train_test_split(X, y, random_state=42);


    bag_clf = BaggingClassifier(
        DecisionTreeClassifier(random_state=42), n_estimators=500,
        max_samples=100, bootstrap=True, n_jobs=-1, random_state=40,
        oob_score=True
    );

    bag_clf.fit(train_x, train_y);

    print("oob(out of bag) score : {}".format(bag_clf.oob_score_))
    print("Test Accuracy : {}".format(bag_clf.score(test_x, test_y)));


def random_forest():
    from sklearn.datasets import load_iris
    from sklearn.ensemble import RandomForestClassifier

    iris = load_iris();
    X = iris["data"];
    y= iris["target"];

    rdf = RandomForestClassifier(n_estimators=400, n_jobs=-1, random_state=42);
    rdf.fit(X, y);

    for name, score in zip(iris["feature_names"], rdf.feature_importances_):
        print("feature - {}  : {}".format(name, score));


def RDF_feature_importance():
    from sklearn.datasets import fetch_mldata
    from sklearn.ensemble import RandomForestClassifier

    mnist = fetch_mldata("MNIST original", data_home="./");
    X, y = mnist["data"], mnist["target"];

    rdf = RandomForestClassifier(n_estimators=10, random_state=42, n_jobs=-1);
    rdf.fit(X, y);

    def plot_digit(data):
        image = data.reshape(28, 28);
        plt.imshow(image, cmap=matplotlib.cm.hot, interpolation="nearest");
        plt.axis("off");

    plot_digit(rdf.feature_importances_);

    cbar = plt.colorbar(ticks=[rdf.feature_importances_.min(), rdf.feature_importances_.max()]);
    cbar.ax.set_yticklabels(['unimportant', 'important']);

    save_fig("mnist_feature_importance_by_rdf");
    plt.show();


def ada_boost_tree():
    from sklearn.datasets import make_moons
    from sklearn.model_selection import train_test_split
    from sklearn.ensemble import AdaBoostClassifier
    from sklearn.tree import DecisionTreeClassifier

    X, y = make_moons(n_samples=500, noise=0.30, random_state=42);
    train_x, test_x, train_y, test_y = train_test_split(X, y, random_state=42);

    ada_tree = AdaBoostClassifier(
        DecisionTreeClassifier(max_depth=1), n_estimators=200,
        algorithm="SAMME.R", learning_rate=0.5, random_state=42
    );

    ada_tree.fit(train_x, train_y);
    plot_decision_boundary_tree(ada_tree, X, y);
    save_fig("ada_boost_with_tree");
    plt.show();


def ada_boost_svm():
    from sklearn.datasets import make_moons
    from sklearn.model_selection import train_test_split
    from sklearn.svm import SVC

    X, y = make_moons(n_samples=500, noise=0.30, random_state=42);
    train_x, test_x, train_y, test_y = train_test_split(X, y, random_state=42);

    size = len(train_x);

    plt.figure(figsize=(11, 4));
    for subplot, learning_rate in ((121, 1), (122, 0.5)):
        sample_weight = np.ones(size);

        plt.subplot(subplot);

        if subplot==121:
            plt.text(-0.7, -0.65, "1", fontsize=14);
            plt.text(-0.6, -0.10, "2", fontsize=14);
            plt.text(-0.5, 0.10, "3", fontsize=14);
            plt.text(-0.4, 0.55, "4", fontsize=14);
            plt.text(-0.3, 0.90, "5", fontsize=14);

        for i in range(5):
            svm_clf = SVC(kernel="rbf", C=0.05, gamma="auto", random_state=42);
            svm_clf.fit(train_x, train_y, sample_weight=sample_weight);
            pred = svm_clf.predict(train_x);

            # Add weight to wrong predicted data
            sample_weight[pred!=train_y] *= (1+learning_rate);
            plot_decision_boundary_tree(svm_clf, X, y, alpha=0.2);
            plt.title("learning_rate = {}".format(learning_rate), fontsize=16);


    save_fig("ada_boosting_with_svm");
    plt.show();


def gradient_boosting_tree_regression():
    from sklearn.tree import DecisionTreeRegressor


    np.random.seed(42);
    # X ~ uniform(-0.5, 0.5)
    X = np.random.rand(100, 1) - 0.5;
    # y = 3*x^2 + noise where noise ~ N(0, 0.05)
    y = 3*X[:, 0]**2 + 0.05*np.random.randn(100);

    tree_reg1 = DecisionTreeRegressor(max_depth=2, random_state=42);
    tree_reg1.fit(X, y);

    y2 = y - tree_reg1.predict(X);
    tree_reg2 = DecisionTreeRegressor(max_depth=2, random_state=42);
    tree_reg2.fit(X, y2);

    y3 = y2 - tree_reg2.predict(X);
    tree_reg3 = DecisionTreeRegressor(max_depth=2, random_state=42);
    tree_reg3.fit(X, y3);

    plt.figure(figsize=(11, 11));

    plt.subplot(321);
    plot_prediction([tree_reg1], X, y, axes=[-0.5, 0.5, -0.1, 0.8],
                    label="$h_1(x_1)$", style="g-", data_label="Train set");
    plt.ylabel("$y$", fontsize=16, rotation=0);
    plt.title("Residual error and Tree prediction");

    plt.subplot(322);
    plot_prediction([tree_reg1], X, y, axes=[-0.5, 0.5, -0.1, 0.8],
                    label="$h(x_1) = h_1(x_1)$", data_label="Train set");
    plt.ylabel("$y$", fontsize=16, rotation=0);
    plt.title("Ensemble prediction");

    plt.subplot(323);
    plot_prediction([tree_reg2], X, y2, axes=[-0.5, 0.5, -0.5, 0.5],
                    label="$h_2(x_1)$", style="g-", data_style="k+",
                     data_label="Residual Error");
    plt.ylabel("$y - h_1(x_1)$", fontsize=16);

    plt.subplot(324);
    plot_prediction([tree_reg1, tree_reg2], X, y,
                    axes=[-0.5, 0.5, -0.1, 0.8],
                    label="$h(x_1) = h_1(x_1) + h_2(x_1)$");
    plt.ylabel("$y$", fontsize=16, rotation=0);

    plt.subplot(325);
    plot_prediction([tree_reg3], X, y3, axes=[-0.5, 0.5, -0.5, 0.5],
                    label="$h_3(x_1)$", style="g-", data_style="k+");
    plt.ylabel("$y - h_1(x_1) - h_2(x_1)$", fontsize=16);
    plt.xlabel("$x_1$", fontsize=16);

    plt.subplot(326)
    plot_prediction([tree_reg1, tree_reg2, tree_reg3], X, y,
                    axes=[-0.5, 0.5, -0.1, 0.8],
                     label="$h(x_1) = h_1(x_1) + h_2(x_1) + h_3(x_1)$");
    plt.xlabel("$x_1$", fontsize=16);
    plt.ylabel("$y$", fontsize=16, rotation=0);

    save_fig("gradient_boosting_tree_regression");
    plt.show();


def gradient_boosting_scikit_learn():
    from sklearn.ensemble import GradientBoostingRegressor

    np.random.seed(42);
    # X ~ uniform(-0.5, 0.5)
    X = np.random.rand(100, 1) - 0.5;
    # y = 3*x^2 + noise where noise ~ N(0, 0.05)
    y = 3 * X[:, 0] ** 2 + 0.05 * np.random.randn(100);

    gbrt_fast = GradientBoostingRegressor(max_depth=2, n_estimators=3, learning_rate=0.1, random_state=42);
    gbrt_slow = GradientBoostingRegressor(max_depth=2, n_estimators=200, learning_rate=0.1, random_state=42);

    gbrt_fast.fit(X, y);
    gbrt_slow.fit(X, y);


    plt.figure(figsize=(11, 4));

    plt.subplot(121);
    plot_prediction([gbrt_fast], X, y,
                    axes=[-0.5, 0.5, -0.1, 0.8], label="Ensemble Prediction");
    plt.title("learning_rate={}, n_estimators={}".format(gbrt_fast.learning_rate, gbrt_fast.n_estimators));

    plt.subplot(122);
    plot_prediction([gbrt_slow], X, y,
                    axes=[-0.5, 0.5, -0.1, 0.8], label="Ensemble Prediction");
    plt.title("learning_rate={}, n_estimators={}".format(gbrt_slow.learning_rate, gbrt_slow.n_estimators));

    save_fig("gradient_boosting_learning_rate");
    plt.show();


def gradient_boosting_early_stopping():
    from sklearn.ensemble import GradientBoostingRegressor
    from sklearn.model_selection import train_test_split
    from sklearn.metrics import mean_squared_error

    np.random.seed(42);
    # X ~ uniform(-0.5, 0.5)
    X = np.random.rand(100, 1) - 0.5;
    # y = 3*x^2 + noise where noise ~ N(0, 0.05)
    y = 3 * X[:, 0] ** 2 + 0.05 * np.random.randn(100);

    train_x, val_x, train_y, val_y = train_test_split(X, y, random_state=49);

    gbrt = GradientBoostingRegressor(n_estimators=120, max_depth=2, random_state=42);
    gbrt.fit(train_x, train_y);

    errors = [mean_squared_error(val_y, val_pred)
              for val_pred in gbrt.staged_predict(val_x)];
    best_n_estimators = np.argmin(errors);

    gbrt_best = GradientBoostingRegressor(max_depth=2, n_estimators=best_n_estimators,
                                          random_state=42);
    gbrt_best.fit(train_x, train_y);


    min_error = np.min(errors);


    plt.figure(figsize=(11, 4));

    plt.subplot(121);
    plt.plot(errors, "b.-");
    plt.plot([best_n_estimators, best_n_estimators], [0, min_error], "k--");
    plt.plot([0, 120], [min_error, min_error], "k--");
    plt.plot(best_n_estimators, min_error, "ko");
    plt.text(best_n_estimators, min_error*1.2, s="minimum", ha="center", fontsize=14);
    plt.axis([0, 120, 0, 0.01]);
    plt.xlabel("number of trees");
    plt.ylabel("Validation error", fontsize=14);

    plt.subplot(122);
    plot_prediction([gbrt_best], X, y, axes=[-0.5, 0.5, -0.1, 0.8]);
    plt.title("Best model (Tree : %d)" %best_n_estimators, fontsize=14);

    save_fig("gradient_boosting_early_stopping");
    plt.show();


def gradient_boosting_early_stopping_implementation():
    from sklearn.ensemble import GradientBoostingRegressor
    from sklearn.model_selection import train_test_split
    from sklearn.metrics import mean_squared_error

    np.random.seed(42);
    # X ~ uniform(-0.5, 0.5)
    X = np.random.rand(100, 1) - 0.5;
    # y = 3*x^2 + noise where noise ~ N(0, 0.05)
    y = 3 * X[:, 0] ** 2 + 0.05 * np.random.randn(100);

    train_x, val_x, train_y, val_y = train_test_split(X, y, random_state=49);

    gbrt = GradientBoostingRegressor(max_depth=2, warm_start=True, random_state=42);

    min_val_error = float("inf");
    error_going_up = 0;

    for n_estimator in range(1, 120):
        gbrt.n_estimators = n_estimator;
        gbrt.fit(train_x, train_y);

        pred = gbrt.predict(val_x);
        val_error = mean_squared_error(pred, val_y);

        if val_error < min_val_error:
            min_val_error = val_error;
            error_going_up = 0;
        else:
            error_going_up += 1;
            if error_going_up == 5:
                break;

    print("Best n_estimators : {}".format(gbrt.n_estimators));
    print("Minimum validation mse error : {}".format(min_val_error));









""" Exercise 8 : """
def exercise7_8_pre():
    from sklearn.datasets import fetch_mldata
    from sklearn.model_selection import train_test_split
    from sklearn.ensemble import RandomForestClassifier, ExtraTreesClassifier
    from sklearn.neural_network import MLPClassifier

    mnist = fetch_mldata("MNIST original", data_home="./");
    X, y = mnist["data"], mnist["target"];

    train_val_x, test_x, train_val_y, test_y = train_test_split(X, y, test_size=10000,
                                                                random_state=42);
    train_x, val_x, train_y, val_y = train_test_split(train_val_x, train_val_y,
                                                      test_size=10000,
                                                      random_state=42);

    # Make models
    rdf_clf = RandomForestClassifier(n_estimators=10, random_state=42, n_jobs=-1);
    et_clf = ExtraTreesClassifier(n_estimators=10, random_state=42, n_jobs=-1);

    mlp_clf = MLPClassifier(random_state=42);

    models = ["Random Forest", "Extra Tree", "MLP"];
    estimators = [rdf_clf, et_clf, mlp_clf];

    # Train the models
    for i, estimator in enumerate(estimators):
        print("{} is fitting..............".format(models[i]));
        estimator.fit(train_x, train_y);
        print("{} is fitted !!!".format(models[i]));

    val_score = [estimator.score(val_x, val_y) for estimator in estimators];

    print("===============Validation errors===============");
    for i in range(len(models)):
        print("{} : {}".format(models[i], val_score[i]));


def exercise7_8():
    from sklearn.datasets import fetch_mldata
    from sklearn.model_selection import train_test_split
    from sklearn.ensemble import RandomForestClassifier, ExtraTreesClassifier
    from sklearn.neural_network import MLPClassifier

    mnist = fetch_mldata("MNIST original", data_home="./");
    X, y = mnist["data"], mnist["target"];

    train_val_x, test_x, train_val_y, test_y = train_test_split(X, y, test_size=10000,
                                                                random_state=42);
    train_x, val_x, train_y, val_y = train_test_split(train_val_x, train_val_y,
                                                      test_size=10000,
                                                      random_state=42);

    # Make models
    rdf_clf = RandomForestClassifier(n_estimators=10, random_state=42, n_jobs=-1);
    et_clf = ExtraTreesClassifier(n_estimators=10, random_state=42, n_jobs=-1);

    mlp_clf = MLPClassifier(random_state=42);

    models = ["Random Forest", "Extra Tree", "MLP"];
    estimators = [rdf_clf, et_clf, mlp_clf];


    from sklearn.ensemble import VotingClassifier

    named_estimators = [];

    for i in range(len(models)):
        named_estimators.append((models[i], estimators[i]));

    voting_clf = VotingClassifier(named_estimators, voting="soft");
    voting_clf.fit(train_x, train_y);

    validation_score = voting_clf.score(val_x, val_y);
    test_score = voting_clf.score(test_x, test_y);

    print("Best validation score : {}".format(validation_score));
    print("Test score : {}".format(test_score));









def exercise7_9():
    from sklearn.datasets import fetch_mldata
    from sklearn.model_selection import train_test_split
    from sklearn.ensemble import RandomForestClassifier, ExtraTreesClassifier
    from sklearn.neural_network import MLPClassifier

    mnist = fetch_mldata("MNIST original", data_home="./");
    X, y = mnist["data"], mnist["target"];

    train_val_x, test_x, train_val_y, test_y = train_test_split(X, y, test_size=10000,
                                                                random_state=42);
    train_x, val_x, train_y, val_y = train_test_split(train_val_x, train_val_y,
                                                      test_size=10000,
                                                      random_state=42);

    # Make models
    rdf_clf = RandomForestClassifier(n_estimators=10, random_state=42, n_jobs=-1);
    et_clf = ExtraTreesClassifier(n_estimators=10, random_state=42, n_jobs=-1);

    mlp_clf = MLPClassifier(random_state=42);

    models = ["Random Forest", "Extra Tree", "MLP"];
    estimators = [rdf_clf, et_clf, mlp_clf];


    # Train each model
    for model, estimator in zip(models, estimators):
        estimator.fit(train_x, train_y);
        test_acc = estimator.score(test_x, test_y);
        print("{}-test accuracy : {}".format(model, test_acc));



    # make predictions with estimators
    val_x_pred = np.empty((len(val_x), len(estimators)), dtype=np.float32);

    for idx, estimator in enumerate(estimators):
        val_x_pred[:, idx] = estimator.predict(val_x);

    # Make a random forest blender
    # We can use any model(e.g MLP, SVC...) for a blender
    rdf_blender = RandomForestClassifier(n_estimators=200, oob_score=True, random_state=42, n_jobs=-1);
    rdf_blender.fit(val_x_pred, val_y);

    print("oob score of rdf_blender : {}".format(rdf_blender.oob_score_));

    # Predict and Evaluate the test data set
    test_x_pred = np.empty((len(test_x), len(estimators)), dtype=np.float32);

    for idx, estimator in enumerate(estimators):
        test_x_pred[:, idx] = estimator.predict(test_x);

    pred = rdf_blender.predict(test_x_pred);

    from sklearn.metrics import accuracy_score
    test_score = accuracy_score(pred, test_y);

    print("Test accuracy of Stacking model : {}".format(test_score));



if __name__== '__main__':
    print("Chapter 7 : Ensemble learning and Random Forest ");
    #stochastic_unbalanced_coin_toss();
    #vote_based_classifier();
    #bagging_decision_tree();
    #out_of_bag_sample();
    #random_forest();
    #RDF_feature_importance();
    #ada_boost_tree();
    #ada_boost_svm();
    #gradient_boosting_tree_regression();
    #gradient_boosting_scikit_learn();
    #gradient_boosting_early_stopping();
    #gradient_boosting_early_stopping_implementation();
    #exercise7_8_pre();
    #exercise7_8();
    exercise7_9();