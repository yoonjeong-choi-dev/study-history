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
CHAPTER_ID = "dimensionality_reduction";

# Save the graph
def save_fig(fig_id, tight_layout=True):

    path = os.path.join(PROJECT_ROOT_DIR, "My_images", CHAPTER_ID, fig_id+".png");
    if tight_layout:
        plt.tight_layout();

    if not (os.path.isdir(os.path.join(PROJECT_ROOT_DIR, "My_images", CHAPTER_ID))):
        os.makedirs(os.path.join(PROJECT_ROOT_DIR, "My_images", CHAPTER_ID));

    plt.savefig(path, format='png', dpi=300);
    print("figure is saved...........................!");


# Draw 3-dimensional arrows
from matplotlib.patches import FancyArrowPatch
from mpl_toolkits.mplot3d import proj3d
class Arrow3D(FancyArrowPatch):
    def __init__(self, x, y, z, *args, **kwargs):
        FancyArrowPatch.__init__(self, (0,0), (0, 0), *args, **kwargs);
        self._verts3d = x, y, z;


    def draw(self, renderer):
        x3d, y3d, z3d = self._verts3d;
        x, y, z = proj3d.proj_transform(x3d, y3d, z3d, renderer.M);
        self.set_positions((x[0], y[0]), (x[1], y[1]));
        FancyArrowPatch.draw(self, renderer);

# Plot the mnist digit
def plot_digits(instances, images_per_row=5, **options):
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




""" Main code """
def singular_value_decomposition():
    np.random.seed(42);
    size = 60;
    w1, w2 = 0.1, 0.3;
    noise = 0.1

    angles = np.random.rand(size) *3 * np.pi / 2 - 0.5;
    X = np.empty((size, 3));
    X[:, 0] = np.cos(angles) + np.sin(angles)/2 + noise*np.random.rand(size)/2;
    X[:, 1] = np.sin(angles)*0.7 + noise*np.random.randn(size)/2;
    X[:, 2] = X[:, 0]*w1 + X[:, 1]*w2 + noise*np.random.randn(size);

    X_centered = X - X.mean(axis=0);
    # X_centered = U*s*V^T
    # s : diagonal with eigenvalues
    # V : column vectors are eigenvectors
    U, s, Vt = np.linalg.svd(X_centered);
    V = Vt.T

    # Check the pca is correct
    rows, cols = X.shape;
    S = np.zeros(X_centered.shape);
    S[:cols, :cols] = np.diag(s);

    isSame = np.allclose(X_centered, U.dot(S).dot(Vt));
    print("Is the svd correct ? : {}".format(isSame));

    # Choose 2 principal component(pc)
    pc = V[:, :2];

    # Project X into 2-dimensional space whose basis are pc.
    X_2d = X_centered.dot(pc);


def pca_scikit():
    from sklearn.decomposition import PCA
    from mpl_toolkits.mplot3d import Axes3D

    np.random.seed(42);
    size = 60;
    w1, w2 = 0.1, 0.3;
    noise = 0.1

    angles = np.random.rand(size) * 3 * np.pi / 2 - 0.5;
    X = np.empty((size, 3));
    X[:, 0] = np.cos(angles) + np.sin(angles) / 2 + noise * np.random.rand(size) / 2;
    X[:, 1] = np.sin(angles) * 0.7 + noise * np.random.randn(size) / 2;
    X[:, 2] = X[:, 0] * w1 + X[:, 1] * w2 + noise * np.random.randn(size);

    pca = PCA(n_components=2);
    X_2d = pca.fit_transform(X);

    X_3d_inv = pca.inverse_transform(X_2d);
    isSame = np.allclose(X, X_3d_inv);
    print("Are original X and inverse X_3d_inv same ? {}".format(isSame));

    reconstruction_error = np.mean(np.sum(np.square(X_3d_inv-X), axis=1));
    print("Reconstruction error : {}".format(reconstruction_error));
    print("Principal Components : \n{}".format(pca.components_));
    print(" ");
    print("Explained variance ratio : {}".format(pca.explained_variance_ratio_));
    print("Ratio of variance lost : {}".format(1 - pca.explained_variance_ratio_.sum()));
    print(" ");

    # Draw a figure
    axes = [-1.8, 1.8, -1.3, 1.3, -1.0, 1.0];

    x1 = np.linspace(axes[0], axes[1], 10);
    x2 = np.linspace(axes[2], axes[3], 10);
    mesh_x, mesh_y = np.meshgrid(x1, x2);

    pc = pca.components_;
    pc_squared = pc.T.dot(pc);
    hyper_plane_with_pc = (pc_squared[0, 2] * mesh_x + pc_squared[1, 2]*mesh_y) / (1 - pc_squared[2, 2]);
    hyper_plane_with_pc.reshape(mesh_x.shape);

    fig = plt.figure(figsize=(6, 3.8));
    ax = fig.add_subplot(111, projection='3d');

    X_3d_above = X[X[:, 2] > X_3d_inv[:, 2]];
    X_3d_below = X[X[:, 2] <= X_3d_inv[:, 2]];

    ax.plot(X_3d_below[:, 0], X_3d_below[:, 1], X_3d_below[:, 2], "bo", alpha=0.5);

    ax.plot_surface(mesh_x, mesh_y, hyper_plane_with_pc, alpha=0.2, color="k");


    np.linalg.norm(pc, axis=0);
    ax.add_artist(Arrow3D([0, pc[0, 0]], [0, pc[0, 1]], [0, pc[0, 2]],
                          mutation_scale=15, lw=1, arrowstyle="-|>", color="k"));
    ax.add_artist(Arrow3D([0, pc[1, 0]], [0, pc[1, 1]], [0, pc[1, 2]],
                          mutation_scale=15, lw=1, arrowstyle="-|>", color="k"));

    ax.plot([0], [0], [0], "k.");

    for i in range(size):
        if X[i, 2] > X_3d_inv[i, 2]:
            ax.plot([X[i][0], X_3d_inv[i][0]], [X[i][1], X_3d_inv[i][1]],
                    [X[i][2], X_3d_inv[i][2]], "k-");

        else:
            ax.plot([X[i][0], X_3d_inv[i][0]], [X[i][1], X_3d_inv[i][1]],
                    [X[i][2], X_3d_inv[i][2]], "k-", color="#505050");

    ax.plot(X_3d_inv[:, 0], X_3d_inv[:, 1], X_3d_inv[:, 2], "k+");
    ax.plot(X_3d_inv[:, 0], X_3d_inv[:, 1], X_3d_inv[:, 2], "k.");
    ax.plot(X_3d_above[:, 0], X_3d_above[:, 1], X_3d_above[:, 2], "bo");

    ax.set_xlabel("$x_1$", fontsize=18, labelpad=7);
    ax.set_ylabel("$x_2$", fontsize=18, labelpad=7);
    ax.set_zlabel("$x_3$", fontsize=18, labelpad=4);
    ax.set_xlim(axes[0:2]);
    ax.set_ylim(axes[2:4]);
    ax.set_zlim(axes[4:6]);

    save_fig("2d_like_datasets_in_3d_space");
    #plt.show();

    fig = plt.figure();
    ax = fig.add_subplot(111, aspect='equal');

    ax.plot(X_2d[:, 0], X_2d[:, 1], "k+");
    ax.plot(X_2d[:, 0], X_2d[:, 1], "k.");
    ax.plot([0],[0], 'ko');

    ax.arrow(0, 0, 0, 1, head_width=0.05, length_includes_head=True, head_length=0.1, fc='k', ec='k')
    ax.arrow(0, 0, 1, 0, head_width=0.05, length_includes_head=True, head_length=0.1, fc='k', ec='k')

    ax.set_xlabel("$z_1$", fontsize=18);
    ax.set_ylabel("$z_2$", fontsize=18, rotation=0);
    ax.axis([-1.5, 1.5, -1.2, 1.2]);
    ax.grid(True);
    save_fig("pca_projection_of_3d_data");
    plt.show();


def swiss_roll_dataset():
    from sklearn.datasets import make_swiss_roll

    X, t = make_swiss_roll(n_samples=1000, noise=0.2, random_state=42);

    axes = [-11.5, 14, -2, 23, -12, 15];

    """ Plot the Swiss-roll data """
    fig = plt.figure(figsize=(6, 5));
    ax = fig.add_subplot(111, projection='3d');
    ax.scatter(X[:, 0], X[:, 1], X[:, 2], c=t, cmap=plt.cm.hot);
    ax.view_init(10, -70);
    ax.set_xlabel("$x_1$", fontsize=18, labelpad=7);
    ax.set_ylabel("$x_2$", fontsize=18, labelpad=7);
    ax.set_zlabel("$x_3$", fontsize=18);
    ax.set_xlim(axes[0:2]);
    ax.set_ylim(axes[2:4]);
    ax.set_zlim(axes[4:6]);

    save_fig("Swiss_roll_data");
    #plt.show();


    """ Plot the squished Swiss-roll """
    plt.figure(figsize=(11, 4));

    plt.subplot(121);
    plt.scatter(X[:, 0], X[:, 1], c=t, cmap=plt.cm.hot);
    plt.axis(axes[:4]);
    plt.xlabel("$x_1$", fontsize=18);
    plt.ylabel("$x_2$", fontsize=18, rotation=0, labelpad=10);
    plt.grid(True);
    plt.title("Projection to xy-plane")

    plt.subplot(122);
    plt.scatter(t, X[:, 1], c=t, cmap=plt.cm.hot);
    plt.axis([4, 15, axes[2], axes[3]]);
    plt.xlabel("$z_1$", fontsize=18);
    plt.grid(True);
    plt.title("Unfolding of the roll");

    save_fig("Squished_Swiss_roll");
    plt.show();


def manifold_decision_boundary_with_swiss():
    from sklearn.datasets import make_swiss_roll

    X, t = make_swiss_roll(n_samples=1000, noise=0.2, random_state=42);

    axes = [-11.5, 14, -2, 23, -12, 15];

    x2 = np.linspace(axes[2], axes[3], 10);
    x3 = np.linspace(axes[4], axes[5], 10);
    mesh_y, mesh_z = np.meshgrid(x2, x3);

    fig = plt.figure(figsize=(12, 10));

    """ Plot the binary Swiss roll w.r.t x1-axis """
    ax = plt.subplot(221, projection='3d');

    positive_class = X[:, 0] > 5;
    X_pos = X[positive_class];
    X_neg = X[~positive_class];

    ax.view_init(10, -70);

    ax.plot(X_neg[:, 0], X_neg[:, 1], X_neg[:, 2], "y^");
    ax.plot(X_pos[:, 0], X_pos[:, 1], X_pos[:, 2], "gs");
    ax.plot_wireframe(5, mesh_y, mesh_z, alpha=0.5);

    ax.set_xlabel("$x_1$", fontsize=18, labelpad=7);
    ax.set_ylabel("$x_2$", fontsize=18, labelpad=7);
    ax.set_zlabel("$x_3$", fontsize=18, labelpad=4);

    ax.set_xlim(axes[0:2]);
    ax.set_ylim(axes[2:4]);
    ax.set_zlim(axes[4:6]);

    ax.set_title("Boundary with x1-axis");

    """ Plot the 2-d manifold of 3d data"""
    ax = plt.subplot(222);

    ax.plot(t[positive_class], X[positive_class, 1], "gs");
    ax.plot(t[~positive_class], X[~positive_class, 1], "y^");

    ax.set_xlim([4, 15]);
    ax.set_ylim(axes[2:4]);

    ax.set_xlabel("$z_1$", fontsize=18);
    ax.set_ylabel("$z_2$", fontsize=18,rotation=0, labelpad=7);

    ax.set_title("Unfolding of the roll");

    """ Plot the binary Swiss roll w.r.t t and x2-axis """
    ax = plt.subplot(223, projection='3d');
    positive_class = 2*(t[:] - 4) > X[:, 1];

    X_pos = X[positive_class];
    X_neg = X[~positive_class];

    ax.view_init(10, -70);

    ax.plot(X_neg[:, 0], X_neg[:, 1], X_neg[:, 2], "y^");
    ax.plot(X_pos[:, 0], X_pos[:, 1], X_pos[:, 2], "gs");

    ax.set_xlabel("$x_1$", fontsize=18, labelpad=7);
    ax.set_ylabel("$x_2$", fontsize=18, labelpad=7);
    ax.set_zlabel("$x_3$", fontsize=18, labelpad=4);

    ax.set_xlim(axes[0:2]);
    ax.set_ylim(axes[2:4]);
    ax.set_zlim(axes[4:6]);

    ax.set_title("Boundary with t");

    """ Plot the 2-d manifold of 3d data"""
    ax = plt.subplot(224);

    ax.plot(t[positive_class], X[positive_class, 1], "gs");
    ax.plot(t[~positive_class], X[~positive_class, 1], "y^");
    ax.plot([4, 15], [0, 22], "b-", linewidth=2);

    ax.set_xlim([4, 15]);
    ax.set_ylim(axes[2:4]);

    ax.set_xlabel("$z_1$", fontsize=18);
    ax.set_ylabel("$z_2$", fontsize=18, rotation=0, labelpad=7);

    ax.set_title("Unfolding of the roll");

    plt.grid(True);

    save_fig("manifold_decision_boundary_with_swiss")
    plt.show();


def pca_projections():
    np.random.seed(3);

    angle = np.pi/5;
    stretch = 5;
    size = 200;

    # original X ~ 0.1 * N(0, 1)
    X = np.random.randn(size, 2)/10;

    # Stretch X with value stretch(5)
    vec_stretch = np.array([[stretch, 0], [0, 1]]);
    X = X.dot(vec_stretch);

    # Rotate X with angle(180/5)
    rotate = np.array([[np.cos(angle), np.sin(angle)], [-np.sin(angle), np.cos(angle)]]);
    X = X.dot(rotate);

    pc1 = np.array([np.cos(angle), np.sin(angle)]);
    pc2 = np.array([np.cos(angle - 2 * np.pi / 6), np.sin(angle - 2 * np.pi / 6)]);
    pc3 = np.array([np.cos(angle - np.pi / 2), np.sin(angle - np.pi / 2)]);

    # projection : X*(pc.T)
    X_proj1 = X.dot(pc1.reshape(-1, 1));
    X_proj2 = X.dot(pc2.reshape(-1, 1));
    X_proj3 = X.dot(pc3.reshape(-1, 1));

    plt.figure(figsize=(8, 4));

    plt.subplot2grid((3, 2), (0, 0), rowspan=3);
    plt.plot(X[:, 0], X[:, 1], "bo", alpha=0.5);
    plt.plot([-1.4, 1.4], [-1.4 * pc1[1] / pc1[0], 1.4 * pc1[1] / pc1[0]], "k-", linewidth=1);
    plt.plot([-1.4, 1.4], [-1.4 * pc2[1] / pc2[0], 1.4 * pc2[1] / pc2[0]], "k--", linewidth=1);
    plt.plot([-1.4, 1.4], [-1.4 * pc3[1] / pc3[0], 1.4 * pc3[1] / pc3[0]], "k:", linewidth=2);

    plt.axis([-1.4, 1.4, -1.4, 1.4]);

    plt.arrow(0, 0, pc1[0], pc1[1], head_width=0.1, linewidth=5,
              length_includes_head=True, head_length=0.1, fc='k', ec='k');
    plt.arrow(0, 0, pc3[0], pc3[1], head_width=0.1, linewidth=5,
              length_includes_head=True, head_length=0.1, fc='k', ec='k');

    plt.text(pc1[0] + 0.1, pc1[1] - 0.05, r"$\mathbf{c_1}$", fontsize=22);
    plt.text(pc3[0] + 0.1, pc3[1], r"$\mathbf{c_2}$", fontsize=22);

    plt.xlabel("$x_1$", fontsize=18);
    plt.ylabel("$x_2$", fontsize=18, rotation=0);
    plt.grid(True);

    plt.subplot2grid((3, 2), (0, 1));
    plt.plot([-2, 2], [0, 0], "k-", linewidth=1);
    plt.plot(X_proj1[:, 0], np.zeros(size), "bo", alpha=0.3);
    plt.gca().get_yaxis().set_ticks([]);
    plt.gca().get_xaxis().set_ticklabels([]);
    plt.axis([-2, 2, -1, 1]);
    plt.grid(True);

    plt.subplot2grid((3,2), (1, 1));
    plt.plot([-2, 2], [0, 0], "k--", linewidth=1);
    plt.plot(X_proj2[:, 0], np.zeros(size), "bo", alpha=0.3);
    plt.gca().get_yaxis().set_ticks([]);
    plt.gca().get_xaxis().set_ticklabels([]);
    plt.axis([-2, 2, -1, 1]);
    plt.grid(True);

    plt.subplot2grid((3,2), (2, 1));
    plt.plot([-2, 2], [0, 0], "k--", linewidth=1);
    plt.plot(X_proj3[:, 0], np.zeros(size), "bo", alpha=0.3);
    plt.gca().get_yaxis().set_ticks([]);
    plt.gca().get_xaxis().set_ticklabels([]);
    plt.axis([-2, 2, -1, 1]);
    plt.grid(True);
    plt.xlabel("$z_1$", fontsize=18);

    save_fig("component_projection_example");
    plt.show();


def mnist_compression():
    from sklearn.datasets import fetch_mldata
    from sklearn.model_selection import train_test_split
    from sklearn.decomposition import PCA

    mnist = fetch_mldata("MNIST original", data_home="./");

    X, y = mnist["data"], mnist["target"];

    train_x, test_x, train_y, test_y = train_test_split(X, y, random_state=42);

    # Find the minimum number of principal components
    # so that the ratio of compressed variance is > 0.95
    ratio = 0.9501;
    pca = PCA();
    pca.fit(train_x);

    cumulative_sum = np.cumsum(pca.explained_variance_ratio_);
    num_pc = np.argmax(cumulative_sum >= ratio) + 1;

    print("minimum number of principal components : {}".format(num_pc));

    # Make a pca with component ratio==ratio(0.95)
    pca = PCA(n_components=ratio);
    pca.fit(train_x);
    print("the sum of compressed variance ratio : {}".format(np.sum(pca.explained_variance_ratio_)));

    # Make the appropriate pca
    pca = PCA(n_components=num_pc);
    reduced_x = pca.fit_transform(train_x);
    recovered_x = pca.inverse_transform(reduced_x);

    plt.figure(figsize=(7, 4));

    plt.subplot(121);
    plot_digits(train_x[::2100]);
    plt.title("Original");

    plt.subplot(122);
    plot_digits(recovered_x[::2100]);
    plt.title("Compression -> Reconstruction");

    save_fig("Compression_of_MNIST_with_PCA");
    plt.show();


def mnist_compression_incremental_pca_scikit():
    from sklearn.datasets import fetch_mldata
    from sklearn.model_selection import train_test_split
    from sklearn.decomposition import IncrementalPCA

    mnist = fetch_mldata("MNIST original", data_home="./");

    X, y = mnist["data"], mnist["target"];

    train_x, test_x, train_y, test_y = train_test_split(X, y, random_state=42);

    batch_size = 100;
    inc_pca = IncrementalPCA(n_components=154);

    for batch in np.array_split(train_x, batch_size):
        print(".", end="");
        inc_pca.partial_fit(batch);

    reduced_x = inc_pca.transform(train_x);
    recovered_x = inc_pca.inverse_transform(reduced_x);

    plt.figure(figsize=(7, 4));

    plt.subplot(121);
    plot_digits(train_x[::2100]);
    plt.title("Original");

    plt.subplot(122);
    plot_digits(recovered_x[::2100]);
    plt.title("Compression -> Reconstruction");

    save_fig("Compression_of_MNIST_incremental_pca");
    plt.show();


def kernel_pca_with_swiss():
    from sklearn.datasets import make_swiss_roll
    from sklearn.decomposition import KernelPCA

    X, t = make_swiss_roll(n_samples=1000, noise=0.2, random_state=42);

    n_component = 2;
    # Make PCAs with some kernels
    linear_pca = KernelPCA(n_components=n_component, kernel="linear",
                           fit_inverse_transform=True);
    rbf_pca = KernelPCA(n_components=n_component, kernel="rbf",
                        gamma=0.0433, fit_inverse_transform=True);
    sigmoid_pca = KernelPCA(n_components=n_component, kernel="sigmoid",
                            gamma=0.001, coef0=1, fit_inverse_transform=True);

    y = t > 6.9;

    plt.figure(figsize=(11, 4));

    for subplot, pca, title in ((131, linear_pca, "linear kernel"),
                                (132, rbf_pca, "RBF kernel, $\gamma=0.04$"),
                                (133, sigmoid_pca, "Sigmoid kernel, $\gamma=10^{-3}, r=1$")):
        reduced_x = pca.fit_transform(X);
        if subplot == 132:
            reduced_x_rbf = reduced_x;

        plt.subplot(subplot);
        plt.title(title, fontsize=14);
        plt.scatter(reduced_x[:, 0], reduced_x[:, 1], c=t, cmap=plt.cm.hot);
        plt.xlabel("$z_1$", fontsize=18);

        if subplot == 131:
            plt.ylabel("$z_2$", fontsize=18, rotation=0);
        plt.grid(True);

    #save_fig("kernel_pca_transform_with_swiss");


    plt.figure(figsize=(12, 5));

    ax = plt.subplot(121, projection='3d');
    inverse_rbf_x = rbf_pca.inverse_transform(reduced_x_rbf);

    ax.view_init(10, -70);
    ax.scatter(inverse_rbf_x[:, 0], inverse_rbf_x[:, 1], inverse_rbf_x[:, 2],
               c=t, cmap=plt.cm.hot, marker="x");
    ax.set_xlabel("$x_1$", fontsize=18, labelpad=7);
    ax.set_ylabel("$x_2$", fontsize=18, labelpad=7);
    ax.set_zlabel("$x_3$", fontsize=18, labelpad=4);
    ax.set_xticklabels([])
    ax.set_yticklabels([])
    ax.set_zticklabels([])
    ax.set_title("Inverse transform of RBF");

    plt.subplot(122);
    reduced_x = rbf_pca.fit_transform(X);
    plt.scatter(reduced_x[:, 0], reduced_x[:, 1], c=t, cmap=plt.cm.hot, marker="x");
    plt.xlabel("$z_1$", fontsize=18);
    plt.ylabel("$z_2$", fontsize=18, rotation=0);
    plt.title("Transform of RBF");
    plt.grid(True);
    save_fig("inverse_transform_rbf");
    plt.show();


def hyper_parameter_tuning_kernel():
    from sklearn.datasets import make_swiss_roll
    from sklearn.decomposition import KernelPCA
    from sklearn.model_selection import GridSearchCV
    from sklearn.linear_model import LogisticRegression
    from sklearn.pipeline import Pipeline

    X, t = make_swiss_roll(n_samples=1000, noise=0.2, random_state=42);
    y = t > 6.9;

    n_component = 2;

    clf = Pipeline([
        ("kpca", KernelPCA(n_components=n_component)),
        ("log_reg", LogisticRegression(solver="liblinear"))
    ]);

    param_grid = [{
        "kpca__kernel": ["rbf", "sigmoid"],
        "kpca__gamma": np.linspace(0.03, 0.05, 10)
    }];

    grid_cv = GridSearchCV(clf, param_grid, cv=3, n_jobs=-1);
    grid_cv.fit(X, y);

    best_param = grid_cv.best_params_;
    best_kernel = best_param["kpca__kernel"];
    best_gamma = best_param["kpca__gamma"];

    best_pca = KernelPCA(n_components=n_component, kernel=best_kernel,
                         gamma=best_gamma, fit_inverse_transform=True);

    reduced_x = best_pca.fit_transform(X);
    preimage_x = best_pca.inverse_transform(reduced_x);

    from sklearn.metrics import mean_squared_error
    preimage_error = mean_squared_error(preimage_x, X);

    print("Best hyperparameter : {}".format(best_param));
    print("Preimage error of best model : {}".format(preimage_error));


def locally_linear_embedding_LLE():
    from sklearn.datasets import make_swiss_roll
    from sklearn.manifold import LocallyLinearEmbedding

    X, t = make_swiss_roll(n_samples=1000, noise=0.2, random_state=41);

    lle = LocallyLinearEmbedding(n_components=2, n_neighbors=10, random_state=42);
    reduced_x = lle.fit_transform(X);

    plt.title("Swiss roll with LLE");
    plt.scatter(reduced_x[:, 0], reduced_x[:, 1], c=t, cmap=plt.cm.hot);
    plt.xlabel("$z_1$", fontsize=18);
    plt.ylabel("$z_2$", fontsize=18, rotation=0);
    plt.axis([-0.065, 0.055, -0.1, 0.12]);
    plt.grid(True);

    save_fig("locally_linear_embedding_unrolling");
    plt.show();


def other_dimensional_reduction():
    from sklearn.datasets import make_swiss_roll
    from sklearn.manifold import MDS, Isomap, TSNE

    X, t = make_swiss_roll(n_samples=1000, noise=0.2, random_state=41);

    mds = MDS(n_components=2);
    mds_reduced_x = mds.fit_transform(X);

    isomap = Isomap(n_components=2);
    iso_reduced_x = isomap.fit_transform(X);

    tsne = TSNE(n_components=2, random_state=42);
    tsne_reduced_x = tsne.fit_transform(X);

    titles = ["MDS", "Isomap", "t-SNE"];
    reduced_x = [mds_reduced_x, iso_reduced_x, tsne_reduced_x];

    plt.figure(figsize=(11, 4));

    for subplot, title, reduced in zip((131, 132, 133), titles, reduced_x):
        plt.subplot(subplot);
        plt.title(title, fontsize=14);
        plt.scatter(reduced[:, 0], reduced[:, 1], c=t, cmap=plt.cm.hot);
        plt.xlabel("$z_1$", fontsize=18);

        if subplot == 131:
            plt.ylabel("$z_2$", fontsize=18, rotation=0);
        plt.grid(True);

    save_fig("other_dimensional_reduction");
    plt.show();





if __name__ == "__main__":
    print("Chapter 8 : Dimensionality Reduction");
    #singular_value_decomposition();
    #pca_scikit();
    #swiss_roll_dataset();
    #manifold_decision_boundary_with_swiss();
    #pca_projections();
    #mnist_compression();
    #mnist_compression_incremental_pca_scikit();
    #kernel_pca_with_swiss();
    #hyper_parameter_tuning_kernel();
    #locally_linear_embedding_LLE();
    other_dimensional_reduction();
