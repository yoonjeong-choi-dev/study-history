from __future__ import division, print_function, unicode_literals

import os

import numpy as np
import matplotlib.pyplot as plt
import matplotlib



""" Useful function """
# Save the graph
def save_fig(fig_id, tight_layout=True):
    PROJECT_ROOT_DIR = ".";
    CHAPTER_ID = "classification";


    path = os.path.join(PROJECT_ROOT_DIR, "My_images", CHAPTER_ID, fig_id+".png");
    if tight_layout:
        plt.tight_layout();

    if not (os.path.isdir(os.path.join(PROJECT_ROOT_DIR, "My_images", CHAPTER_ID))):
        os.makedirs(os.path.join(PROJECT_ROOT_DIR, "My_images", CHAPTER_ID));

    plt.savefig(path, format='png', dpi=300);
    print("figure is saved...........................!")

def plot_digit(data):
    image = data.reshape(28, 28);
    plt.imshow(image, cmap=matplotlib.cm.binary, interpolation="nearest");
    plt.axis("off");

def plot_digits(instances, images_per_row=10, **options):
    size = 28;
    images_per_row = min(len(instances), images_per_row);
    images = [instance.reshape(size, size) for instance in instances];

    n_rows = (len(instances) - 1) // images_per_row + 1;
    row_images = [];
    n_empty = n_rows * images_per_row - len(instances);
    images.append(np.zeros((size, size * n_empty)))

    for row in range(n_rows):
        rimages = images[row * images_per_row: (row + 1) * images_per_row];
        row_images.append(np.concatenate(rimages, axis=1));

    image = np.concatenate(row_images, axis=0);
    plt.imshow(image, cmap=matplotlib.cm.binary, **options);
    plt.axis("off");

def mnist_data():
    from sklearn.datasets import fetch_mldata
    mnist = fetch_mldata("MNIST original", data_home="./");

    return mnist;


def mnist_train_data(shuffle_flag=True):
    from sklearn.datasets import fetch_mldata
    mnist = fetch_mldata("MNIST original", data_home="./");
    x, t = mnist["data"], mnist["target"];

    train_x, train_t = x[:60000], t[:60000];

    if shuffle_flag:
        shuffle_idx = np.random.permutation(60000);
        train_x, train_t = train_x[shuffle_idx], train_t[shuffle_idx];

    return train_x, train_t;


def mnist_test_data():
    from sklearn.datasets import fetch_mldata
    mnist = fetch_mldata("MNIST original", data_home="./");
    x, t = mnist["data"], mnist["target"];

    test_x, test_t = x[60000:], t[:60000:];

    return test_x, test_t;


""" Classification """
def binary_classifier_check_5():
    train_x, train_t = mnist_train_data();
    test_x, test_t = mnist_test_data();

    train_t_5 = (train_t == 5);
    test_t_5 = (test_t==5);

    # Make SGD-classifier
    from sklearn.linear_model import SGDClassifier
    sgd_clf = SGDClassifier(max_iter=5, random_state=42);
    sgd_clf.fit(train_x, train_t_5);

    # Evaluation
    print("=========================Binary Classification================================\n");



    print("=========================1. Accuracy  : ======================================");
    from sklearn.model_selection import cross_val_score
    cv_score = cross_val_score(sgd_clf, train_x, train_t_5, cv=3, scoring="accuracy");
    print("cv_score(3-fold) : {}".format(cv_score));

    # Dummy Classifier
    from sklearn.base import BaseEstimator

    class Never5Classifier(BaseEstimator):
        def fit(self, X, y=None):
            pass

        def predict(self, X):
            return np.zeros((len(X), 1), dtype=bool);

    never_5_clf = Never5Classifier();
    cv_dummy_score = cross_val_score(never_5_clf, train_x, train_t_5, cv=3, scoring="accuracy");
    print("cv_dummy_score : {}".format(cv_dummy_score));
    print("==============================================================================");



    print("==========================2. Confusion Matrix  : =============================");
    from sklearn.model_selection import cross_val_predict
    train_pred = cross_val_predict(sgd_clf, train_x, train_t_5, cv=3);

    from sklearn.metrics import confusion_matrix
    conf_mat = confusion_matrix(train_t_5, train_pred);
    print("confusion matrix : \n{}".format(conf_mat));
    precision = conf_mat[1][1]/(conf_mat[1][1] + conf_mat[0][1]);
    recall = conf_mat[1][1]/(conf_mat[1][1] + conf_mat[1][0]);
    print("precision : {}".format(precision));
    print("sensitivity(recall) : {}".format(recall));
    print("==============================================================================");

    print("==========================3. Precision and Recall : ==========================");
    from sklearn.metrics import precision_score, recall_score, f1_score
    precision = precision_score(train_t_5, train_pred);
    recall = recall_score(train_t_5, train_pred);
    score_f1 = f1_score(train_t_5, train_pred)
    print("precision : {}".format(precision));
    print("sensitivity(recall) : {}".format(recall));
    print("F1-score (harmonic mean of precision and recall : {}".format(score_f1));
    print("==============================================================================");



    print("==========================4. Decision Function================================");
    t_scores = cross_val_predict(sgd_clf, train_x, train_t_5, cv=3, method="decision_function");

    from sklearn.metrics import precision_recall_curve
    precisions, recalls, thresholds = precision_recall_curve(train_t_5, t_scores);

    def plot_precision_recall_vs_threshold(precisions, recalls, thresholds):
        plt.plot(thresholds, precisions[:-1], "b--", label="precision");
        plt.plot(thresholds, recalls[:-1], "g-", label="recall");
        plt.xlabel("threshold");
        plt.ylim([0, 1]);
        plt.legend(loc="center left");

    def plot_precision_vs_recall(precisions, recalls):
        plt.plot(recalls, precisions, "b-", linewidth=2);
        plt.xlabel("recall");
        plt.ylabel("precision");
        plt.axis([0, 1, 0, 1]);


    print("See the graph.....");
    plt.figure(figsize=(8, 4));
    plot_precision_recall_vs_threshold(precisions, recalls, thresholds);
    plt.xlim([-700000, 700000]);
    save_fig("precision_recall_vs_threshold_plot");
    plt.show();

    plt.figure(figsize=(8, 6))
    plot_precision_vs_recall(precisions, recalls);
    save_fig("precision_vs_recall_plot");
    plt.show();
    print("==============================================================================");



    print("==========================5. Set Threshold by 4===============================");
    threshold = 70000;
    train_t_acc_90 = (t_scores > threshold);
    precision_90 = precision_score(train_t_5, train_t_acc_90);
    recall_90 = recall_score(train_t_5, train_t_acc_90);
    print("precision with the threshold: {}".format(precision_90));
    print("sensitivity(recall) with the threshold : {}".format(recall_90));
    print("==============================================================================");


    print("==========================6. Receiver operating characteristics(See 3)========");
    from sklearn.metrics import roc_curve
    fpr, tpr, thresholds = roc_curve(train_t_5, t_scores);

    def plot_roc_curve(fpr, tpr, label=None):
        plt.plot(fpr, tpr, linewidth=2, label=label);
        plt.plot([0,1], [0, 1], 'k--');
        plt.axis([0, 1, 0, 1]);
        plt.xlabel("False Positive Ratio");
        plt.ylabel("True Positive Ratio(Recall)");

    print("See the graph.....");
    plt.figure(figsize=(8, 6));
    plot_roc_curve(fpr, tpr);
    save_fig("roc_curve_plot_SGD");
    plt.show();
    print("==============================================================================");


    print("==========================7. Compare with Random Forest=======================");
    from sklearn.ensemble import RandomForestClassifier
    forest_clf = RandomForestClassifier(random_state=42);
    t_proba_forest = cross_val_predict(forest_clf, train_x, train_t_5, cv=3, method="predict_proba");
    t_scores_forest = t_proba_forest[:, 1];
    fpr_forest, tpr_forest, thresholds_forest = roc_curve(train_t_5, t_scores_forest);


    from sklearn.metrics import roc_auc_score
    roc_score_SGD = roc_auc_score(train_t_5, t_scores);
    roc_score_RF = roc_auc_score(train_t_5, t_scores_forest);
    print("The area under the roc_curve : ");
    print("SGD : {}".format(roc_score_SGD));
    print("Random Forest : {}".format(roc_score_RF));

    print("See the graph.....");
    plt.plot(fpr, tpr, "b:", label="SGD");
    plot_roc_curve(fpr_forest, tpr_forest, "Random Forest");
    plt.legend(loc="lower right");
    save_fig("roc_curve_plot_Random_Forest_vs_SGD");
    plt.show();
    print("==============================================================================");


def multiple_classifier():
    train_x, train_t = mnist_train_data();
    test_x, test_t = mnist_test_data();

    print("=========================Multiple Classification===============================\n");

    from sklearn.linear_model import SGDClassifier
    from sklearn.multiclass import OneVsOneClassifier

    ovo_clf = OneVsOneClassifier(SGDClassifier(max_iter=5, random_state=42));
    ovo_clf.fit(train_x, train_t);

    print("=========================1. Basic  : =========================================");
    from sklearn.model_selection import cross_val_score
    cv_score = cross_val_score(ovo_clf, train_x, train_t, cv=3, scoring="accuracy");
    print("cv_score(3-fold) : {}".format(cv_score));
    print("==============================================================================");

    print("=========================2. With scaled data  : ==============================");
    from sklearn.preprocessing import StandardScaler
    scaler = StandardScaler();
    train_x_scaled = scaler.fit_transform(train_x.astype(np.float64));
    cv_score = cross_val_score(ovo_clf, train_x_scaled, train_t, cv=3, scoring="accuracy");
    print("cv_score(3-fold) : {}".format(cv_score));
    print("==============================================================================");


def analyze_error_multi_classifier_SGD():
    train_x, train_t = mnist_train_data();
    test_x, test_t = mnist_test_data();

    print("=========================Multiple Classification improved======================\n");

    # Make a model
    from sklearn.linear_model import SGDClassifier
    sgd_clf = SGDClassifier(max_iter=5, random_state=42);

    # Preprocess the train data
    from sklearn.preprocessing import StandardScaler
    scaler = StandardScaler();
    train_x_scaled = scaler.fit_transform(train_x.astype(np.float64));

    from sklearn.model_selection import cross_val_score, cross_val_predict
    from sklearn.metrics import confusion_matrix

    train_pred = cross_val_predict(sgd_clf, train_x_scaled, train_t, cv=3);
    conf_mat = confusion_matrix(train_t, train_pred);

    print("Confusion matrix : .........................");
    print(conf_mat);

    print("Confusion matrix image................");
    plt.matshow(conf_mat, cmap=plt.cm.gray);
    plt.show();

    print("Error ratio image......................")
    row_sums = conf_mat.sum(axis=1, keepdims=True);
    norm_conf_mat = conf_mat / row_sums;
    np.fill_diagonal(norm_conf_mat, 0);
    plt.matshow(norm_conf_mat, cmap=plt.cm.gray);
    plt.show();

    print("======================Image for 3 and 5=======================================")
    cl_a, cl_b = 3, 5
    X_aa = train_x[(train_t == cl_a) & (train_pred == cl_a)]
    X_ab = train_x[(train_t == cl_a) & (train_pred == cl_b)]
    X_ba = train_x[(train_t == cl_b) & (train_pred == cl_a)]
    X_bb = train_x[(train_t == cl_b) & (train_pred == cl_b)]




    plt.figure(figsize=(8, 8))
    plt.subplot(221);
    plot_digits(X_aa[:25], images_per_row=5)
    plt.subplot(222);
    plot_digits(X_ab[:25], images_per_row=5)
    plt.subplot(223);
    plot_digits(X_ba[:25], images_per_row=5)
    plt.subplot(224);
    plot_digits(X_bb[:25], images_per_row=5)
    save_fig("error_analysis_digits_plot")
    plt.show()






""" Exercise """
# TOO SLOW!!!!
def MNIST_KNN_gridSearch():
    train_x, train_t = mnist_train_data();
    test_x, test_t = mnist_test_data();

    from sklearn.neighbors import KNeighborsClassifier
    knn_clf = KNeighborsClassifier();

    from sklearn.model_selection import GridSearchCV
    param_grid = [{'weights': ["uniform", "distance"], 'n_neighbors': [3, 4, 5]}];

    grid_search = GridSearchCV(knn_clf, param_grid, cv=5, verbose=3, n_jobs=-1);
    grid_search.fit(train_x, train_t);

    print("Best parameter : \n{}".format(grid_search.best_params_));
    print("Best estimator : \n{}".format(grid_search.best_estimator_));




















if __name__== '__main__':
    np.random.seed(42);

    MNIST_KNN_gridSearch();






































