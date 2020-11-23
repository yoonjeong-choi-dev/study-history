import numpy as np

""" Smoothing the cost function """
def smooth_curve(x, beta=2):
    """ Kaiser window smoothing
    :param x: points to smooth
    :param beta: shape parameter for window

    reference : https://glowingpython.blogspot.com/2012/02/convolution-with-numpy.html
    """
    window_len = 11;
    s = np.r_[x[window_len-1:0:-1], x, x[-1:-window_len:-1]];
    w = np.kaiser(window_len, beta);
    y = np.convolve(w/w.sum(), s, mode='valid');
    return y[5:len(y)-5];




""" Shuffle data for Validation data"""
def shuffle_dataset(x, t):
    """
    Shuffle train data set so that we can make a validation set for evaluating hyper-parameters
    :param x: train data
    :param t: train label
    :return: shuffled x and t
    """
    permutation = np.random.permutation(x.shape[0]);
    if x.ndim == 2:
        x = x[permutation, :];
    else:
        x = x[permutation, :, :, :];

    t = t[permutation];

    return x, t;



""" Transformation of image data for Convolution"""
def im2col(input_data, filter_height, filter_width, stride=1, padding=0):
    """
    Transform multiple images(4 dimension) into 2-dimensional array(flatten)
    --------------------------------------------------------------------------
    Parameters :
    1. input_data : 4-dimensional input data
            - (number of images i.e batch_num, number of channels, height(# of row), width(# of columns)

    2. filter_height : the height of the filter
    3. filer_width   : the width of the filter

    4. stride : the gap of position to apply the filter to the input_data

    5. padding : the size of the (one side) length to increase the input_data(image) to apply convolution

    6. return : 2-dimensional array to compute Convolution easily
    --------------------------------------------------------------------------
    Let H be the height of one input image = input_data[0][0].shape[0]
    Let W be the width of one input image = input_data[0][0].shape[1]

    Let OH be the height of one output data
    Let OW be the width of one output data

    Then,
    OH = (H + 2*padding - filter_height)/stride + 1
    OW = (W + 2*padding - filter_width)/stride + 1
    --------------------------------------------------------------------------
    numpy.pad(tensor, paddings, mode='CONSTANT', name=None) :
    이 함수는 지정한 paddings에 따라 tensor에 패딩을 적용합니다.

    padding은 구조(shape)가 [n, 2]인 정수형 텐서이고, 여기서 n은 tensor의 랭크(rank)입니다.

    input의 각각의 차원 D에 대해, paddings[D, 0]은 tensor의 원소 앞에 몇 개의 값을 넣을 것인지,
    paddings[D, 1]은 tensor의 원소 뒤에 몇 개의 값을 넣을 것인지를 나타냅니다.

    만약 mode가 "REFLECT"라면, paddings[D, 0]과 paddings[D, 1] 모두 tensor.dim_size(D) - 1보다 크지 않아야 합니다.

    mode가 "SYMMETRIC"이라면, paddings[D, 0]과 paddings[D, 1] 모두 tensor.dim_size(D)보다 크지 않아야 합니다.

    자세한 내용은 help(numpy.pad)를 참고.
    --------------------------------------------------------------------------
    여기서 우리는 4차원 input data를 다룬다.
    코드에 있는 np.pad(input_data, [(0, 0), (0, 0), (padding, padding), (padding, padding)], 'constant')에서
    paddings 은  [(0, 0), (0, 0), (padding, padding), (padding, padding)] 이다.

    우리는 각각의 데이터(이미지)의 채널에 대한 2차원 이미지를 생각한다.
    즉, 컨볼루션은 각각의 데이터의 채널을 고정한 채(e.g RGB), 하나의 2차원 데이터에 대해서 계산을 한다.
    따라서, padding은 각각의 데이터의 채널을 고정한 채, 하나의 2차원 데이터에 대해서만 적용을 한다

    paddings 에서 첫번째에 해당하는 (0, 0)은 배치 데이터에서 각 데이터들을 의미한다.
    즉 데이터들은 padding을 할 필요가 없다.

    paddings 에서 두번째에 해당하는 (0, 0)은 데이터의 채널을 의미한다.
    첫번째와 마찬가지로, 채널에 대해서도 padding을 할 필요가 없다.

    paddings 에서 세번째에 해당하는 (padding, padding)은 이미지의 높이를 의미한다.
    (padding, padding)에서 첫번째 요소는 윗방향으로 padding만큼 0값을 추가한다는 의미이다.
    (padding, padding)에서 두번째 요소는 아랫방향으로 padding만큼 0값을 추가한다는 의미이다.
    즉 세로축(높이)에 대해서 양방향으로 padding만큼 0값을 추가한다.

    paddings 에서 네번째에 해당하는 (padding, padding)은 이미지의 너비를 의미한다.
    (padding, padding)에서 첫번째 요소는 오른쪽 방향으로 padding만큼 0값을 추가한다는 의미이다.
    (padding, padding)에서 두번째 요소는 왼쪽 방향으로 padding만큼 0값을 추가한다는 의미이다.
    즉 가로축(너비)에 대해서 양방향으로 padding만큼 0값을 추가한다.
    --------------------------------------------------------------------------
    IDEA :

    """

    # N=batch_num, C=channel_num, H=height, W=width
    N, C, H, W = input_data.shape;
    OH = (H + 2 * padding - filter_height) // stride + 1
    OW = (W + 2 * padding - filter_width) // stride + 1

    # padding the images when the data of mini-batch data and the channel are fixed
    img = np.pad(input_data, [(0, 0), (0, 0), (padding, padding), (padding, padding)], 'constant');

    col = np.zeros((N, C, filter_height, filter_width, OH, OW));

    # From now on, fix the data and the channel
    # i.e consider 2-dim image.
    # We consider each position of each window

    # y : index for row
    # for each filter, we have copy of the 2-dim image
    for y in range(filter_height):
        # y_max : the maximum row idx for the lowest window
        y_max = y + stride * OH;

        # x : index of col
        for x in range(filter_width):
            # x_max : the maximum col idx for the most right window
            x_max = x + stride * OW;

            #  y:y_max:stride : pixel of each window
            # col[data,channel,y,x] : set of pixels of each window(복사본들)
            col[:, :, y, x, :, :] = img[:, :, y:y_max:stride, x:x_max:stride];

    # col.transpose => col[data][output row][output col][channel][filter row][filter col]
    col = col.transpose(0, 4, 5, 1, 2, 3);
    # col[data,output][channel, filter]
    col = col.reshape(N * OH * OW, -1);
    return col;

def col2im(col, input_shape, filter_height, filter_width, stride=1, padding=0):
    """
    Transform 2-dimensional array(flatten) into multiple images(4 dimension)
    This function is used for Back Propagation in the convolution layer
    --------------------------------------------------------------------------
    Parameters :
    1. col : 2-dimensional array(flatten) which is the output of im2col
            - (data/output, channel/filter)

    2. input_shape : the shape of the original data i.e previous input of im2col
            - (number of images i.e batch_num, number of channels, height(# of row), width(# of columns)

    3. filter_height : the height of the filter
    4. filer_width   : the width of the filter

    5. stride : the gap of position to apply the filter to the input_data

    6. padding : the size of the (one side) length to increase the input_data(image) to apply convolution

    7. return : 4-dimensional input data
            - (number of images i.e batch_num, number of channels, height(# of row), width(# of columns)
    --------------------------------------------------------------------------
    """
    # N=batch_num, C=channel_num, H=height, W=width
    N, C, H, W = input_shape;
    OH = (H + 2 * padding - filter_height) // stride + 1
    OW = (W + 2 * padding - filter_width) // stride + 1

    # Recall the im2col : col[data,output][channel, filter]
    # => col[data][output row][output col][channel][filter row][filter col]
    col = col.reshape(N, OH, OW, C, filter_height, filter_width);

    # The result : col[data][channel][filter row][filter col][output row][output col]
    col = col.transpose(0, 3, 4, 5, 1, 2);

    img = np.zeros((N, C, H + 2 * padding + stride - 1, W + 2 * padding + stride - 1));

    # From now on, fix the data and the channel
    # i.e consider 2-dim image.
    # We consider each position of each window

    # y : index for row
    for y in range(filter_height):
        # y_max : the maximum row idx for the lowest window
        y_max = y + stride * OH;

        # x : index of col
        for x in range(filter_width):
            # x_max : the maximum col idx for the most right window
            x_max = x + stride * OW;

            #  y:y_max:stride : pixel of each window
            # col[data,channel,y,x] : set of pixels of each window
            img[:, :, y:y_max:stride, x:x_max:stride] = col[:, :, y, x, :, :];

    # remove the extended area by padding
    img = img[:, :, padding:H + padding, padding:W + padding];
    return img;


""" Output size of a convolution layer """
def conv_output_size(input_size, filter_size, stride=1, padding=0):
    return (input_size + 2*padding - filter_size) / stride + 1;



""" Examples for Functions"""

def shuffle_MNIST_example():
    from dataset.mnist import load_mnist

    (x_train, t_train), (x_test, t_test) = load_mnist();
    datasize = len(t_train);
    x_train, t_train = shuffle_dataset(x_train, t_train);

    validation_rate = 0.20;
    validation_num = int(x_train.shape[0] * validation_rate);

    x_val = x_train[:validation_num];
    t_val = t_train[:validation_num];

    x_train = x_train[validation_num:];
    t_train = t_train[validation_num:];

    print("Total data size : {}".format(datasize));
    print("validation size : {}".format(len(t_val)));
    print("train size : {}".format(len(t_train)));


def numpy_padding_example():
    padding = 2;
    data = np.array([[1, 2], [3, 4]]);
    print('data')
    print(data);

    x = np.pad(data, [(padding, padding), (padding, padding)], 'constant');
    print(x);
    print(x.shape)


def im2col_example():
    print("====================Example 1===========================")
    x1 = np.random.rand(1, 3, 7, 7);
    col1 = im2col(x1, 5, 5, stride=1, padding=0);
    print("x1 shape : {}".format(x1.shape));
    print("col1 shape : {}".format(col1.shape));
    x1_restore = col2im(col1, (1, 3, 7, 7), 5, 5, stride=1, padding=0);
    print("x1_restore shape : {}".format(x1_restore.shape))

    if (x1 == x1_restore).all():
        print("Restoration is successful")

    print("========================================================")

    print("====================Example 2===========================")
    x2 = np.random.rand(10, 3, 7, 7);
    col2 = im2col(x2, 5, 5, stride=1, padding=0);
    print("x2 shape : {}".format(x2.shape));
    print("col2 shape : {}".format(col2.shape));
    x2_restore = col2im(col2, (10, 3, 7, 7), 5, 5, stride=1, padding=0);
    print("x1_restore shape : {}".format(x2_restore.shape))

    if (x2 == x2_restore).all():
        print("Restoration is successful")

    print("========================================================")