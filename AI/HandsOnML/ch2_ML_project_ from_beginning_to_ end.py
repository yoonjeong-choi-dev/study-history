"""
1. Goal : Make a model for California Housing Price
          Then predict the median housing price for each block group(region)
2. data : (population, median income, median housing price,....) for each block group
3. Make a model
    - supervised learning
    - (multivariate) regression model
    - batch learning (since teh data has no continuous flow)
    - cost function : RMSE(root mean square error)
"""

""" Download and Load the data"""


def download_housing_data():
    import os
    import tarfile
    from six.moves import urllib

    # URL for downloading the data
    DOWNLOAD_ROOT = "https://raw.githubusercontent.com/ageron/handson-ml/master/";
    HOUSING_URL = DOWNLOAD_ROOT + "datasets/housing/housing.tgz";
    # HOUSING_PATH : 현재 디렉토리에서 원하는 폴더 설정 가능
    HOUSING_PATH = os.path.join("datasets", "housing");

    def fetch_housing_data(housing_url=HOUSING_URL, housing_path=HOUSING_PATH):
        if not os.path.isdir(housing_path):
            os.makedirs(housing_path);

        tgz_path = os.path.join(housing_path, "housing.tgz");
        urllib.request.urlretrieve(housing_url, tgz_path);

        housing_tgz = tarfile.open(tgz_path);
        housing_tgz.extractall(path=housing_path);
        housing_tgz.close();

    fetch_housing_data();


def load_housing_data():
    import os
    import pandas as pd

    HOUSING_PATH = os.path.join("datasets", "housing");

    def load_path(housing_path=HOUSING_PATH):
        csv_path = os.path.join(housing_path, "housing.csv");
        return pd.read_csv(csv_path);

    # load csv file of housing
    housing = load_path();

    return housing;


# Split the data into train/test data respectively
def split_train_test(data, test_ratio=0.2, random_seed=-1):
    import numpy as np

    # Set the seed
    if random_seed < 0:
        pass
    else:
        np.random.seed(random_seed);

    # shuffle the data
    shuffled_indices = np.random.permutation(len(data));
    test_set_size = int(len(data) * test_ratio);
    test_indices = shuffled_indices[:test_set_size];
    train_indices = shuffled_indices[test_set_size:];

    return data.iloc[train_indices], data.iloc[test_indices];


""" Chapter 2.3 : Analyze the data - make appropriate train/test data """


def load_analyze_housing_data():
    import os
    import pandas as pd

    HOUSING_PATH = os.path.join("datasets", "housing");

    def load_path(housing_path=HOUSING_PATH):
        csv_path = os.path.join(housing_path, "housing.csv");
        return pd.read_csv(csv_path);

    # load csv file of housing
    housing = load_path();

    print("===============5 data===================");
    # save the first 5 data of housing
    housing_head = housing.head();
    print(housing_head);
    print('========================================');

    print("=======Information of housing data======");
    housing.info();
    print('========================================');

    print("=============ocean_proximity ===========");
    ocean_proximity = housing['ocean_proximity'].value_counts();
    print(ocean_proximity);
    print('========================================');

    print('=============Numeric feature============');
    describe = housing.describe();
    for key in describe.keys():
        print("==========={}===============".format(key))
        print(describe[key]);
    print('========================================');

    print("==============Histogram=================");
    import matplotlib.pyplot as plt
    housing.hist(bins=50, figsize=(20, 15));
    plt.show();
    print("Check the histogram!!");
    print('========================================');


# To avoid sampling bias, we need to make appropriate stratified sampling
def make_sampling_by_median_income(housing=load_housing_data(), show_flag=False):
    import numpy as np
    import matplotlib.pyplot as plt;

    numeric_feature = housing.describe();

    median_income_stat = numeric_feature['median_income'];
    median_income = housing['median_income'];

    if show_flag:
        print("Median income stat");
        print(median_income_stat);

        print("\nHistogram");
        median_income.hist(bins=50);
        plt.show();

    # Make a stratified sampling of 5 strata(계층)
    housing["income_cat"] = np.ceil(median_income / 1.5);
    housing["income_cat"].where(housing["income_cat"] < 5, 5.0, inplace=True);

    if show_flag:
        print("The number of data in each strata");
        print(housing["income_cat"].value_counts());

        print("\nHistogram");
        housing["income_cat"].hist()
        plt.show()

    return housing;


# Split the data into train/test data by StratifiedShuffleSplit
def split_data_Stratified(housing=make_sampling_by_median_income(), show_flag=False):
    from sklearn.model_selection import StratifiedShuffleSplit

    split = StratifiedShuffleSplit(n_splits=1, test_size=0.2, random_state=42);

    for train_index, test_index in split.split(housing, housing["income_cat"]):
        strat_train_set = housing.loc[train_index];
        strat_test_set = housing.loc[test_index];

    if show_flag:
        print("Ratio of median income category over total data set");
        print(housing["income_cat"].value_counts() / len(housing));

    return strat_train_set, strat_test_set;


def compare_sampling_bias():
    def income_cat_proportions(data):
        return data["income_cat"].value_counts() / len(data);

    housing = make_sampling_by_median_income();

    # stratified sampling
    strat_train_set, strat_test_set = split_data_Stratified(housing);

    # random sampling
    from sklearn.model_selection import train_test_split;
    train_set, test_set = train_test_split(housing, test_size=0.2, random_state=42);

    # Comparing
    import pandas as pd
    compare_props = pd.DataFrame({
        "Overall": income_cat_proportions(housing),
        "Stratified": income_cat_proportions(strat_test_set),
        "Random": income_cat_proportions(test_set),
    }).sort_index();

    compare_props["Rand. %error"] = 100 * compare_props["Random"] / compare_props["Overall"] - 100;
    compare_props["Strat. %error"] = 100 * compare_props["Stratified"] / compare_props["Overall"] - 100;

    print(compare_props);


# Summary : Chapter 2.3 - make appropriate train/test data
def chapter2_3():
    housing = load_housing_data();

    print("==============make sampling by median income==============");
    housing = make_sampling_by_median_income(housing, True);
    print("==========================================================");
    print("==============split data by stratified====================");
    strat_train_set, strat_test_set = split_data_Stratified(housing, True);
    print("==========================================================");
    print("==============compare sampling bias=======================");
    compare_sampling_bias();


""" Chapter 2.4 : Visualize and then Analyze the data """


def copy_train_set():
    housing = load_housing_data();
    housing = make_sampling_by_median_income(housing);
    strat_train_set, strat_test_set = split_data_Stratified(housing, False);

    return strat_train_set.copy();


def geographical_visualize_train_set(housing=copy_train_set()):
    import matplotlib.pyplot as plt
    housing.plot(kind="scatter", x="longitude", y="latitude", alpha=0.1);
    plt.title("longitude - latitude")
    plt.show();

    housing.plot(kind="scatter", x="longitude", y="latitude", alpha=0.4,
                 s=housing["population"] / 100, label="population", figsize=(10, 7),
                 c="median_house_value", cmap=plt.get_cmap("jet"),
                 colorbar=True, sharex=False);
    plt.title("Housing price with population");
    plt.show();


def standard_correlation_coefficient(housing=copy_train_set()):
    print("=============standard_correlation_coefficient w.r.t median income=============");
    corr_matrix = housing.corr();
    median_income_coef = corr_matrix["median_house_value"].sort_values(ascending=False);
    print(median_income_coef);
    print("==============================================================================");


def scatter_correlation(housing=copy_train_set()):
    from pandas.plotting import scatter_matrix
    import matplotlib.pyplot as plt

    print("==========================scatter correlation=================================");

    # Choose some attributes to compare
    attributes = ["median_house_value", "median_income", "total_rooms", "housing_median_age"];

    scatter_matrix(housing[attributes], figsize=(12, 8));
    plt.show();
    print("==============================================================================");


def scatter_median_housing_and_income(housing=copy_train_set()):
    import matplotlib.pyplot as plt

    print("======================scatter median income and housing=======================");

    housing.plot(kind="scatter", x="median_income", y="median_house_value", alpha=0.1);
    plt.show();

    print("==============================================================================");


""" Chapter 2.5 : Prepare the data for Machine Learning algorithm """


def strat_data_by_median_housing(housing=make_sampling_by_median_income(), train_flag=True):
    strat_train_set, strat_test_set = split_data_Stratified(housing, False);

    # split the strat_train_set into data points and data labels
    if train_flag:
        housing = strat_train_set.drop("median_house_value", axis=1);
        housing_label = strat_train_set["median_house_value"].copy();
    else:
        housing = strat_test_set.drop("median_house_value", axis=1);
        housing_label = strat_test_set["median_house_value"].copy();

    return housing, housing_label;


def strat_housing_data(housing=make_sampling_by_median_income(), train_flag=True):
    housing, housing_label = strat_data_by_median_housing(housing, train_flag=train_flag);
    return housing;


def strat_housing_label(housing=make_sampling_by_median_income(), train_flag=True):
    housing, housing_label = strat_data_by_median_housing(housing, train_flag=train_flag);
    return housing_label;


def handle_omitted_data_mine():
    housing, housing_label = strat_data_by_median_housing();

    print("Note that housing['total_bedrooms'] has some omitted data");

    housing1 = housing.copy();
    housing2 = housing.copy();
    housing3 = housing.copy();

    # Method 1 : Remove data whose 'total_bedrooms' feature is omitted
    housing1.dropna(subset=["total_bedrooms"]);

    # Method 2 : Remove 'total_bedrooms' feature
    #            i.e remove the corresponding column
    housing2.drop("total_bedrooms", axis=1);

    # Method 3 : Add the median to omitted data in housing['total_bedrooms']
    median = housing3["total_bedrooms"].median();
    housing3["total_bedrooms"].fillna(median, inplace=True);


def add_omitted_data_Imputer(housing=strat_housing_data()):
    from sklearn.preprocessing import Imputer
    import pandas as pd

    # imputer : save medians of features in statistics_
    imputer = Imputer(strategy="median");

    # ocean_proximity is not a numeric feature
    housing_num = housing.drop("ocean_proximity", axis=1);

    imputer.fit(housing_num);

    print("==============================================================================");
    print("Median of each feature by imputer");
    print(imputer.statistics_);
    print("==============================================================================");
    print("Median of each feature from data");
    print(housing_num.median().values);
    print("==============================================================================");

    # Replace the omitted data by median
    X = imputer.transform(housing_num);
    housing_tr = pd.DataFrame(X, columns=housing_num.columns,
                              index=list(housing.index.values));

    return housing_tr;


def handle_text_categorical_feature(housing=strat_housing_data()):
    # extract data whose feature is categorical
    housing_cat = housing["ocean_proximity"];
    housing_cat_encoded, housing_categories = housing_cat.factorize();

    # Transform housing_cat_encoded to One-hot-encoding
    from sklearn.preprocessing import OneHotEncoder
    encoder = OneHotEncoder();
    housing_cat_1hot = encoder.fit_transform(housing_cat_encoded.reshape(-1, 1));
    # print(type(housing_cat_1hot));
    # print(housing_cat_1hot.shape);

    return housing_cat_1hot;


def encoding_categorical_feature(housing=strat_housing_data()):
    from Encoder import CategoricalEncoder
    # extract data whose feature is categorical
    housing_cat = housing["ocean_proximity"];
    cat_encoder = CategoricalEncoder();
    housing_cat_reshaped = housing_cat.values.reshape(-1, 1);
    housing_cat_1hot = cat_encoder.fit_transform(housing_cat_reshaped);
    print(housing_cat_1hot.shape);
    print(cat_encoder.categories_);


""" User-defined Encoder"""
from sklearn.base import BaseEstimator, TransformerMixin
import numpy as np


class CombinedAttributesAdder(BaseEstimator, TransformerMixin):
    """
    Make some combinations of attributes in housing data

    """
    from sklearn.base import BaseEstimator, TransformerMixin
    import numpy as np

    def __init__(self, add_bedrooms_per_room=True):
        self.add_bedrooms_per_room = add_bedrooms_per_room;
        self.rooms_ix, self.bedrooms_ix, self.population_ix, self.household_ix = 3, 4, 5, 6;

    def fit(self, X, y=None):
        return self;

    def transform(self, X, y=None):
        rooms_per_household = X[:, self.rooms_ix] / X[:, self.household_ix];
        population_per_household = X[:, self.population_ix] / X[:, self.household_ix];

        if self.add_bedrooms_per_room:
            bedrooms_per_room = X[:, self.bedrooms_ix] / X[:, self.rooms_ix];
            return np.c_[X, rooms_per_household, population_per_household, bedrooms_per_room];
        else:
            return np.c_[X, rooms_per_household, population_per_household];


def CombinedAttributesAdder_example():
    import pandas as pd
    housing = strat_housing_data();

    attr_adder = CombinedAttributesAdder(add_bedrooms_per_room=False);
    housing_extra_att = attr_adder.transform(housing.values);

    housing_extra_att = pd.DataFrame(
        housing_extra_att,
        columns=list(housing.columns) + ["rooms_per_household", "population_per_household"])

    print(housing_extra_att.head());


""" Final data for training"""


def refine_data(data=load_housing_data(), train_flag=True):
    from sklearn.pipeline import Pipeline
    from sklearn.preprocessing import Imputer, StandardScaler
    from Encoder import DataFrameSelector, CategoricalEncoder
    from sklearn.pipeline import FeatureUnion

    housing = make_sampling_by_median_income(housing=data);
    housing, housing_label = strat_data_by_median_housing(housing=housing, train_flag=train_flag);

    # ocean_proximity is not a numeric feature
    housing_num = housing.drop("ocean_proximity", axis=1);

    num_attribs = list(housing_num);
    cat_attribs = ["ocean_proximity"];

    # Make a pipeline for numerical feature data
    num_pipeline = Pipeline([
        ('selector', DataFrameSelector(num_attribs)),
        ('imputer', Imputer(strategy="median")),
        ('attribs_adder', CombinedAttributesAdder()),
        ('std_scaler', StandardScaler()),
    ]);

    # Make a pipeline for categorical feature data
    cat_pipeline = Pipeline([
        ('selector', DataFrameSelector(cat_attribs)),
        ('cat_encoder', CategoricalEncoder(encoding="onehot-dense")),
    ]);

    # Combine pipelines
    full_pipeline = FeatureUnion(transformer_list=
                                 [("num_pipeline", num_pipeline),
                                  ("cat_pipeline", cat_pipeline),
                                  ]);

    housing_prepared = full_pipeline.fit_transform(housing);
    # print(housing_prepared);
    # print(housing_prepared.shape);

    return housing_prepared, housing_label;


""" Chapter 2.6 : Model selection and training """


def display_scores(scores):
    print("Scores : {}".format(scores));
    print("Mean : {}".format(scores.mean()));
    print("Standard deviation : {}".format(scores.std()));


def linear_regression():
    from sklearn.linear_model import LinearRegression
    from sklearn.metrics import mean_squared_error

    train_x, train_t = refine_data(load_housing_data());
    test_x, test_t = refine_data(load_housing_data(), False);

    lin_reg = LinearRegression();

    lin_reg.fit(train_x, train_t);

    print("======================Linear Regression=======================================");
    acc_train = lin_reg.score(train_x, train_t)
    print("train acc : {}".format(acc_train));
    acc_test = lin_reg.score(test_x, test_t)
    print("test acc : {}".format(acc_test));

    pred_train = lin_reg.predict(train_x);
    mse_train = mean_squared_error(train_t, pred_train);

    print("Train RMSE : {}".format(np.sqrt(mse_train)));

    pred_test = lin_reg.predict(test_x);
    mse_test = mean_squared_error(test_t, pred_test);
    print("Test RMSE : {}".format(np.sqrt(mse_test)));
    print("==============================================================================");

    print("==============================Cross Validation=================================");
    print("");
    from sklearn.model_selection import cross_val_score
    scores = cross_val_score(lin_reg, train_x, train_t, scoring="neg_mean_squared_error",
                             cv=10);
    tree_rmse_scores = np.sqrt(-scores);
    display_scores(tree_rmse_scores);
    print("==============================================================================");


def decision_tree():
    from sklearn.tree import DecisionTreeRegressor
    from sklearn.metrics import mean_squared_error

    train_x, train_t = refine_data(load_housing_data());
    test_x, test_t = refine_data(load_housing_data(), False);

    tree_reg = DecisionTreeRegressor();

    tree_reg.fit(train_x, train_t);

    print("========================Decision Tree=========================================");

    acc_train = tree_reg.score(train_x, train_t)
    print("train acc : {}".format(acc_train));
    acc_test = tree_reg.score(test_x, test_t)
    print("test acc : {}".format(acc_test));

    pred_train = tree_reg.predict(train_x);
    mse_train = mean_squared_error(train_t, pred_train);

    print("Train RMSE : {}".format(np.sqrt(mse_train)));

    pred_test = tree_reg.predict(test_x);
    mse_test = mean_squared_error(test_t, pred_test);
    print("Test RMSE : {}".format(np.sqrt(mse_test)));
    print("==============================================================================");

    print("==============================Cross Validation=================================");
    print("");
    from sklearn.model_selection import cross_val_score
    scores = cross_val_score(tree_reg, train_x, train_t, scoring="neg_mean_squared_error",
                             cv=10);
    tree_rmse_scores = np.sqrt(-scores);
    display_scores(tree_rmse_scores);
    print("==============================================================================");


def random_forest():
    from sklearn.ensemble import RandomForestRegressor
    from sklearn.metrics import mean_squared_error

    train_x, train_t = refine_data(load_housing_data());
    test_x, test_t = refine_data(load_housing_data(), False);

    forest_reg = RandomForestRegressor();

    forest_reg.fit(train_x, train_t);

    print("========================Random Forest=========================================");

    acc_train = forest_reg.score(train_x, train_t)
    print("train acc : {}".format(acc_train));
    acc_test = forest_reg.score(test_x, test_t)
    print("test acc : {}".format(acc_test));

    pred_train = forest_reg.predict(train_x);
    mse_train = mean_squared_error(train_t, pred_train);

    print("Train RMSE : {}".format(np.sqrt(mse_train)));

    pred_test = forest_reg.predict(test_x);
    mse_test = mean_squared_error(test_t, pred_test);
    print("Test RMSE : {}".format(np.sqrt(mse_test)));
    print("==============================================================================");

    print("==============================Cross Validation=================================");
    print("");
    from sklearn.model_selection import cross_val_score
    scores = cross_val_score(forest_reg, train_x, train_t, scoring="neg_mean_squared_error",
                             cv=10);
    tree_rmse_scores = np.sqrt(-scores);
    display_scores(tree_rmse_scores);
    print("==============================================================================");


""" Chapter 2.7 : Tuning the hyperparameters in model """


def grid_search_random_forest():
    from sklearn.ensemble import RandomForestRegressor

    train_x, train_t = refine_data(load_housing_data());
    test_x, test_t = refine_data(load_housing_data(), False);

    from sklearn.model_selection import GridSearchCV
    param_grid = [{'n_estimators': [3, 10, 30], 'max_features': [2, 4, 6, 8], },
                  {'bootstrap': [False], 'n_estimators': [3, 10], 'max_features': [2, 3, 4]}];

    forest_reg = RandomForestRegressor(random_state=42);

    grid_search = GridSearchCV(forest_reg, param_grid, cv=5,
                               scoring='neg_mean_squared_error',
                               return_train_score=True);

    grid_search.fit(train_x, train_t);

    print("=========================Best parameters======================================");
    print(grid_search.best_params_);
    print("==============================================================================");

    print("=========================Best estimator=======================================");
    print(grid_search.best_estimator_);
    print("==============================================================================");

    print("=========================Score for each params================================");
    cv_res = grid_search.cv_results_;
    for mean_score, params in zip(cv_res["mean_test_score"], cv_res["params"]):
        print("Score : {}".format(np.sqrt(-mean_score)) + "     Params : {}".format(params));
    print("==============================================================================");


def best_random_forest_by_grid():
    from sklearn.ensemble import RandomForestRegressor
    from sklearn.metrics import mean_squared_error

    train_x, train_t = refine_data(load_housing_data());
    test_x, test_t = refine_data(load_housing_data(), False);

    forest_reg = RandomForestRegressor(
        bootstrap=True, criterion='mse', max_depth=None,
        max_features=6, max_leaf_nodes=None, min_impurity_decrease=0.0,
        min_impurity_split=None, min_samples_leaf=1,
        min_samples_split=2, min_weight_fraction_leaf=0.0,
        n_estimators=30, n_jobs=1, oob_score=False, random_state=42,
        verbose=0, warm_start=False)

    forest_reg.fit(train_x, train_t);

    print("========================Random Forest=========================================");

    acc_train = forest_reg.score(train_x, train_t)
    print("train acc : {}".format(acc_train));
    acc_test = forest_reg.score(test_x, test_t)
    print("test acc : {}".format(acc_test));

    pred_train = forest_reg.predict(train_x);
    mse_train = mean_squared_error(train_t, pred_train);

    print("Train RMSE : {}".format(np.sqrt(mse_train)));

    pred_test = forest_reg.predict(test_x);
    mse_test = mean_squared_error(test_t, pred_test);
    print("Test RMSE : {}".format(np.sqrt(mse_test)));
    print("==============================================================================");



def random_search_random_forest():
    from sklearn.ensemble import RandomForestRegressor

    train_x, train_t = refine_data(load_housing_data());
    test_x, test_t = refine_data(load_housing_data(), False);

    from sklearn.model_selection import RandomizedSearchCV
    from scipy.stats import randint

    param_distribution = {
        'n_estimators': randint(low=1, high=200),
        'max_features': randint(low=1, high=8),
    };

    forest_reg = RandomForestRegressor(random_state=42);
    rnd_search = RandomizedSearchCV(forest_reg, param_distributions=param_distribution,
                                    n_iter=10, cv=5, scoring='neg_mean_squared_error',
                                    random_state=42, n_jobs=1);

    rnd_search.fit(train_x, train_t);

    print("=========================Best parameters======================================");
    print(rnd_search.best_params_);
    print("==============================================================================");

    print("=========================Best estimator=======================================");
    print(rnd_search.best_estimator_);
    print("==============================================================================");

    print("=========================Score for each params================================");
    cv_res = rnd_search.cv_results_;
    for mean_score, params in zip(cv_res["mean_test_score"], cv_res["params"]):
        print("Score : {}".format(np.sqrt(-mean_score)) + "     Params : {}".format(params));
    print("==============================================================================");


def best_random_forest_by_random():
    from sklearn.ensemble import RandomForestRegressor
    from sklearn.metrics import mean_squared_error

    train_x, train_t = refine_data(load_housing_data());
    test_x, test_t = refine_data(load_housing_data(), False);

    forest_reg = RandomForestRegressor(
        bootstrap=True, criterion='mse', max_depth=None,
        max_features=7, max_leaf_nodes=None, min_impurity_decrease=0.0,
        min_impurity_split=None, min_samples_leaf=1,
        min_samples_split=2, min_weight_fraction_leaf=0.0,
        n_estimators=180, n_jobs=1, oob_score=False, random_state=42,
        verbose=0, warm_start=False)

    forest_reg.fit(train_x, train_t);

    print("========================Random Forest=========================================");

    acc_train = forest_reg.score(train_x, train_t)
    print("train acc : {}".format(acc_train));
    acc_test = forest_reg.score(test_x, test_t)
    print("test acc : {}".format(acc_test));

    pred_train = forest_reg.predict(train_x);
    mse_train = mean_squared_error(train_t, pred_train);

    print("Train RMSE : {}".format(np.sqrt(mse_train)));

    pred_test = forest_reg.predict(test_x);
    mse_test = mean_squared_error(test_t, pred_test);
    print("Test RMSE : {}".format(np.sqrt(mse_test)));
    print("==============================================================================");

    print("==============================Cross Validation=================================");
    from sklearn.model_selection import cross_val_score
    scores = cross_val_score(forest_reg, train_x, train_t, scoring="neg_mean_squared_error",
                             cv=10);
    tree_rmse_scores = np.sqrt(-scores);
    display_scores(tree_rmse_scores);
    print("==============================================================================");



""" Exercise """

def svm_grid_search():
    from sklearn.svm import SVR
    from sklearn.metrics import mean_squared_error

    train_x, train_t = refine_data(load_housing_data());
    test_x, test_t = refine_data(load_housing_data(), False);

    from sklearn.model_selection import GridSearchCV
    param_grid = [
        {'kernel':['linear'], 'C':[10., 20., 30., 40., 50.], 'gamma':[0.01, 0.03, 0.1, 0.3, 1.0]},
        {'kernel':['rbf'], 'C':[1.0, 3.0, 10., 30., 100], 'gamma':[0.01, 0.03, 0.1, 0.3, 1.0]}
    ];

    svr_reg = SVR();

    grid_search = GridSearchCV(svr_reg, param_grid, cv=5,
                               scoring='neg_mean_squared_error', verbose=True,
                               return_train_score=True);

    grid_search.fit(train_x, train_t);

    print("=========================Best parameters======================================");
    print(grid_search.best_params_);
    print("==============================================================================");

    print("=========================Best estimator=======================================");
    print(grid_search.best_estimator_);
    print("==============================================================================");

    print("=========================Score for each params================================");
    cv_res = grid_search.cv_results_;
    for mean_score, params in zip(cv_res["mean_test_score"], cv_res["params"]):
        print("Score : {}".format(np.sqrt(-mean_score)) + "     Params : {}".format(params));
    print("==============================================================================");











if __name__ == '__main__':
    print("==============================================================================");
    print("Chapter2 : ML project from beginning to end");
    print("==============================================================================");
    svm_grid_search();


