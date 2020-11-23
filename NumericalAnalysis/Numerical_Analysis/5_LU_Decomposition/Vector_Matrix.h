#ifndef __VECTOR_MATRIX_H__
#define __VECTOR_MATRIX_H__


#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <typeinfo>

using namespace std;

template<typename T>
class FVector;

template<typename T>
class FMatrix;



//�ƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢ�
//============================================================================
//                                FVector(Full vector)
//============================================================================
//�ƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢ�

/*
void -> FVector<T>& 
*/

template<typename T>
class FVector {
// Member variables
public:
	int _size;
	T *_vec;

// Member Function : Initializer and Destroyer
public:
	// Initializer
	FVector();
	FVector(int size, T element=0);
	FVector(const vector<T>& arr);
	FVector(FVector<T>& arr);

	// Destroyer
	~FVector();

// Member Function : Operation Overload
public:
	T& operator[] (int idx);
	T operator,(FVector<T>& vec);

// Member Function : Useful Function
public:
	int getSize() const { return _size; };
	void print(bool option=false);
	void release();
	void clear();
	void resize(int size, T element=0);
	void copy(const FVector<T>& vec);
	void setAll(const FVector<T>& vec);
	void setAll(const vector<T>& vec);
	bool isSame(const FVector<T>& vec);



// Member Function : Usuful Functions for linear algebra
public:
	void swap(int i, int j); // swap(_vec[i], _vec[j])
	void add(FVector<T>& vec);	// vector += vec
	void add(T scalar, FVector<T>& vec);//vector += scalar*vec
	void add(FVector<T>& vec1, FVector<T>& vec2); // vector = vec1+vec2;
	void add(T scalar1, FVector<T>& vec1, T scalar2, FVector<T>& vec2); // vector = scalarl1*vec1+scalar2*vec2;
	void scalar_mult(T scalar);		//vector = scalar*vector
	void scalar_mult(T scalar, FVector<T>& vec ); //vector = scalar*vec
	void mult(FMatrix<T>& mat, FVector<T>& vec); // vector = mat*vec
	T norm_l1();
	T norm_l2();
	void normalize();
};




//�ƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢ�
//============================================================================
//                                FMatrix(Full matrix)
//============================================================================
//�ƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢ�

template<typename T>
class FMatrix {
// Member variables
public:
	int _row;
	int _col;
	FVector<T> *_mat;

// Member Function : Initializer and Destroyer
public:
	// Initializer
	FMatrix();
	FMatrix(int row, int col, T element = 0);
	FMatrix(const vector<vector<T>>& mat);

	// Destroyer
	~FMatrix();

//  Member Function : Operation Overload
public:
	FVector<T>& operator[] (int idx);
	T& operator()(int i, int j);

// Member Function : Useful Function
public:
	int getrow() const { return _row; };
	int getcol() const { return _col; };
	void print(bool option = false);
	void release();
	void clear();
	void resize(int row, int col, T element = 0);
	void identiy(int size);	// make an identity matrix of size 
	void copy(const FMatrix<T>& mat);
	void setAll(const FMatrix<T>& mat);
	void setAll(const vector<vector<T>>& mat);
	bool isSame(const FMatrix<T>& mat);



// Member Function : Usuful Functions for linear algebra
public:
	void add(FMatrix<T>& mat);	// matrix += mat
	void add(T scalar, FMatrix<T>& mat); //matrix += scalar*mat
	void add(FMatrix<T>& mat1, FMatrix<T>& mat2); // matrix = mat1 + mat2
	void add(T scalar1, FMatrix<T>& mat1, T scalar2, FMatrix<T>& mat2); // matrix = scalar1*matrix1 + scalar2*matrix2
	void scalar_mult(T scalar);		//matrix = scalar*matrix
	void scalar_mult(T scalar, FMatrix<T>& mat); //matrix = scalar*mat
	void mult(FMatrix<T>& mat1, FMatrix<T>& mat2); // matrix = mat1*mat2
	void transpose();
	void transpose(FMatrix<T>& mat);
	T trace();
};



//�ƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢ�
//============================================================================
//             FVector(Full vector) - Definition
//============================================================================
//�ƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢ�
// Definition of FVector member function
template<typename T>
FVector<T>::FVector() {

	_size = 0;
	_vec = NULL;
}

template<typename T>
FVector<T>::FVector(int size, T element = 0) {
	_size = size;
	_vec = new T[size];
	for (int i = 0; i < _size; i++)
		_vec[i] = element;
}

template<typename T>
FVector<T>::FVector(const vector<T>& arr) {
	_size = arr.size();
	_vec = new T[_size];

	for (int i = 0; i < _size; i++)
		_vec[i] = arr[i];
}

template<typename T>
FVector<T>::FVector(FVector<T>& arr) {
	_size = arr._size;
	_vec = new T[_size];
	for (int i = 0; i < _size; i++) {
		_vec[i] = arr._vec[i];
	}
}

template<typename T>
FVector<T>::~FVector() {
	_size = 0;
	delete[] _vec;
	_vec = NULL;
}

template<typename T>
T& FVector<T>::operator[](int idx) {
	if (idx < 0 || idx >= _size) {
		cout << "FVector - operator[] : index out of bound" << endl;
		exit(1);
	}
	return _vec[idx];
}

template<typename T>
T FVector<T>::operator,(FVector<T>& vec)

{
	if (_size != vec._size) {
		cout << "FVector - operator, : different size" << endl;
		exit(1);
	}

	T sum = 0;

	for (int i = 0; i < _size; i++) {
		sum += _vec[i] * vec[i];
	}

	return sum;
}

template<typename T>
void FVector<T>::print(bool option = false) {
	if (option)
		cout << "FVector : " << endl;

	if (_size == 0) {
		cout << "NUll vector" << endl;
		return;
	}
	cout << " [";
	for (int i = 0; i < _size - 1; i++)
		cout << _vec[i] << " ";
	cout << _vec[_size - 1];
	cout << "]" << endl;
	//system("pause");
}

template<typename T>
void FVector<T>::release() {
	_size = 0;
	delete[] _vec;
	_vec = NULL;
}

template<typename T>
void FVector<T>::clear() {
	for (int i = 0; i < _size; i++) {
		_vec[i] = 0;
	}
}

template<typename T>
void FVector<T>::resize(int size, T element = 0) {
	release();
	_size = size;
	_vec = new T[size];

	for (int i = 0; i < size; i++)
		_vec[i] = element;
}

template<typename T>
void FVector<T>::copy(const FVector<T>& vec) {
	if (_size != vec._size) {
		release(); //cout << "Release" << endl;
		_size = vec.getSize();
		_vec = new T[_size];
	}
	

	for (int i = 0; i < _size; i++) {
		_vec[i] = vec._vec[i];
	}
}

template<typename T>
void FVector<T>::setAll(const FVector<T>& vec) {
	copy(vec);
}

template<typename T>
void FVector<T>::setAll(const vector<T>& vec) {
	if (_size != vec.size()) {
		release();
		_size = vec.size();
		_vec = new T[_size];
	}
	

	for (int i = 0; i < _size; i++) {
		_vec[i] = vec[i];
	}
}

template<typename T>
bool FVector<T>::isSame(const FVector<T>& vec){
	if (_size != vec._size)
		return false;

	for (int i = 0; i < _size; i++) {
		if (_vec[i] != vec._vec[i])
			return false;
	}

	return true;
}



template<typename T>
void FVector<T>::add(FVector<T>& vec) {
	if (_size != vec._size) {
		cout << "FVector - add(vec) : different size" << endl;
		exit(1);
	}

	for (int i = 0; i < _size; i++) {
		_vec[i] += vec[i];
	}
}

template<typename T>
void FVector<T>::swap(int i, int j) {
	if (0 > i || 0 > j || i >= _size || j >= _size) {
		cout << "FVector - swap : out of range" << endl;
		exit(1);
	}
	T temp = _vec[i];
	_vec[i] = _vec[j];
	_vec[j] = temp;
}

template<typename T>
void FVector<T>::add(T scalar, FVector<T>& vec) {
	if (_size != vec._size) {
		cout << "FVector - add(scalar, vec) : different size" << endl;
		exit(1);
	}

	for (int i = 0; i < _size; i++) {
		_vec[i] += (scalar*vec[i]);
	}
}

template<typename T>
void FVector<T>::add(FVector<T>& vec1, FVector<T>& vec2) {
	if (vec1._size != vec2._size) {
		cout << "FVector - add(vec, vec) : different size" << endl;
		exit(1);
	}

	if (_size != vec1._size) {
		release();
		_size = vec1._size;
		_vec = new T[_size];
	}

	for (int i = 0; i < _size; i++) {
		_vec[i] = vec1[i] + vec2[i];
	}
}

template<typename T>
void FVector<T>::add(T scalar1, FVector<T>& vec1, T scalar2, FVector<T>& vec2) {
	if (vec1._size != vec2._size) {
		cout << "FVector - add(vec, vec) : different size" << endl;
		exit(1);
	}

	if (_size != vec1._size) {
		release();
		_size = vec1._size;
		_vec = new T[_size];
	}
	

	for (int i = 0; i < _size; i++) {
		_vec[i] = scalar1*vec1[i] + scalar2*vec2[i];
	}
}

template<typename T>
void FVector<T>::scalar_mult(T scalar) {
	for (int i = 0; i < _size; i++) {
		_vec[i] *= scalar;
	}
}

template<typename T>
void FVector<T>::scalar_mult(T scalar, FVector<T>& vec) {

	if (_size != vec._size) {
		release();
		_size = vec._size;
		_vec = new T[_size];
	}
	

	for (int i = 0; i < _size; i++) {
		_vec[i] = scalar*vec[i];
	}
}

template<typename T>
T FVector<T>::norm_l1() {
	T norm = 0;
	for (int i = 0; i < _size; i++) {
		norm += abs(_vec[i]);
	}

	return norm;
}

template<typename T>
T FVector<T>::norm_l2() {
	T norm = 0;
	for (int i = 0; i < _size; i++) {
		norm += pow(_vec[i], 2);
	}

	norm = sqrt(norm);
	return norm;
}

template<typename T>
void FVector<T>::normalize() {
	T norm = this->norm_l2();

	for (int i = 0; i < _size; i++)
		_vec[i] /= norm;
}




//�ƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢ�
//============================================================================
//             FMatrix(Full matrix) - Definition
//============================================================================
//�ƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢ�

template<typename T>
FMatrix<T>::FMatrix() {
	_row = 0;
	_col = 0;
	_mat = NULL;
}

template<typename T>
FMatrix<T>::FMatrix(int row, int col, T element = 0) {
	_row = row;
	_col = col;

	_mat = new FVector<T>[_row];
	for (int i = 0; i < _row; i++)
		_mat[i].resize(_col, element);
}

template<typename T>
FMatrix<T>::FMatrix(const vector<vector<T>>& mat) {
	_row = mat.size();
	_col = mat[0].size();
	_mat = new FVector<T>[_row];

	for (int i = 0; i < _row; i++)
		_mat[i].setAll(mat[i]);
}

template<typename T>
FMatrix<T>::~FMatrix() {
	if (_mat != NULL) {
		for (int i = 0; i < _row; i++) {
			_mat[i].release();
		}
		_mat = NULL;
	}
}

template<typename T>
FVector<T>& FMatrix<T>::operator[](int idx) {
	if (_row < 0 || _row <= idx) {
		cout << "FMatrix - opearotor[] : index out of bound" << endl;
		exit(1);
	}

	return _mat[idx];
}

template<typename T>
T& FMatrix<T>::operator()(int i, int j) {
	if (_row < 0 || _row <= i || j < 0 || _col <= j) {
		cout << "FMatrix - opearotor() : index out of bound" << endl;
		exit(1);
	}

	return _mat[i][j];
}

template<typename T>
void FMatrix<T>::print(bool option = false) {
	if (option) {
		cout << "FMatrix : " << endl;
	}

	if (_mat == NULL) {
		cout << "Null matrix" << endl;
		return;
	}

	for (int i = 0; i < _row; i++) {
		for (int j = 0; j < _col; j++) {
			cout << _mat[i][j] << " ";
		}
		cout << endl;
	}

	cout << endl;
}

template<typename T>
void FMatrix<T>::release() {
	if (_mat != NULL) {
		for (int i = 0; i < _row; i++) {
			_mat[i].release();
		}
		_mat = NULL;
	}
	_row = 0;
	_col = 0;
}

template<typename T>
void FMatrix<T>::clear() {
	for (int i = 0; i < _row; i++)
		_mat[i].clear();
}

template<typename T>
void FMatrix<T>::resize(int row, int col, T element = 0) {
	release();

	_row = row;
	_col = col;
	_mat = new FVector<T>[_row];

	for (int i = 0; i < _row; i++) {
		_mat[i].resize(_col, element);
	}

}

template<typename T>
void FMatrix<T> ::identiy(int size) {
	resize(size, size, 0);

	for (int i = 0; i < _row; i++) {
		_mat[i][i] = 1;
	}
}

template<typename T>
void FMatrix<T>::copy(const FMatrix<T>& mat) {
	
	if (_row != mat._row || _col != mat._col) {
		release();

		_row = mat._row;
		_col = mat._col;
		_mat = new FVector<T>[_row];
	}


	for (int i = 0; i < _row; i++) {
		_mat[i].copy(mat._mat[i]);
	}
}

template<typename T>
void FMatrix<T>::setAll(const FMatrix<T>& mat) {
	if (_row != mat._row || _col != mat._col) {
		release();

		_row = mat._row;
		_col = mat._col;
		_mat = new FVector<T>[_row];
	}

	for (int i = 0; i < _row; i++) {
		_mat[i].setAll(mat._mat[i]);
	}
}

template<typename T>
void FMatrix<T>::setAll(const vector<vector<T>>& mat) {

	if (_row != mat.size() || _col != mat[0].size()) {
		release();

		_row = mat.size();
		_col = mat[0].size();
		_mat = new FVector<T>[_row];
	}
	

	for (int i = 0; i < _row; i++) {
		_mat[i].setAll(mat[i]);
	}
}

template<typename T>
bool FMatrix<T>::isSame(const FMatrix<T>& mat) {
	if (_row != mat._row || _col != mat._col) {
		return false;
	}

	for (int i = 0; i < _row; i++) {
		if (!_mat[i].isSame(mat._mat[i])) {
			return false;
		}
	}

	return true;
}

template<typename T>
void FMatrix<T>::add(FMatrix<T>& mat) {
	if (_row != mat._row || _col != mat._col) {
		cout << "FMatrix - add(FMatrix<T>& mat) : different size" << endl;
		exit(1);
	}

	for (int i = 0; i < _row; i++) {
		for (int j = 0; j < _col; j++) {
			_mat[i][j] += mat[i][j];
		}
	}
}

template<typename T>
void FMatrix<T>::add(T scalar, FMatrix<T>& mat) {
	if (_row != mat._row || _col != mat._col) {
		cout << "FMatrix - add(T scalar, FMatrix<T>& mat) : different size" << endl;
		exit(1);
	}

	for (int i = 0; i < _row; i++) {
		for (int j = 0; j < _col; j++) {
			_mat[i][j] += scalar*mat[i][j];
		}
	}
}

template<typename T>
void FMatrix<T>::add(FMatrix<T>& mat1, FMatrix<T>& mat2) {
	if (mat1._row != mat2._row || mat1._col != mat2._col) {
		cout << "FMatrix - add(FMatrix<T>& mat1, FMatrix<T>& mat2) : different size for inputs" << endl;
		exit(1);
	}

	if (_row != mat1._row || _col != mat1._col) {
		resize(mat1._row, mat1._col);
	}

	for (int i = 0; i < _row; i++) {
		for (int j = 0; j < _col; j++) {
			_mat[i][j] = mat1[i][j] + mat2[i][j];
		}
	}
}

template<typename T>
void FMatrix<T>::add(T scalar1, FMatrix<T>& mat1, T scalar2, FMatrix<T>& mat2) {
	if (mat1._row != mat2._row || mat1._col != mat2._col) {
		cout << "FMatrix - add(FMatrix<T>& mat1, FMatrix<T>& mat2) : different size for inputs" << endl;
		exit(1);
	}
	if (_row != mat1._row || _col != mat1._col) {
		resize(mat1._row, mat1._col);
	}

	for (int i = 0; i < _row; i++) {
		for (int j = 0; j < _col; j++) {
			_mat[i][j] = scalar1*mat1[i][j] + scalar2*mat2[i][j];
		}
	}
}

template<typename T>
void FMatrix<T>::scalar_mult(T scalar) {
	for (int i = 0; i < _row; i++) {
		for (int j = 0; j < _col; j++) {
			_mat[i][j] *= scalar;
		}
	}
}

template<typename T>
void FMatrix<T>::scalar_mult(T scalar, FMatrix<T>& mat) {

	if (_row != mat._row || _col != mat._col) {
		resize(mat._row, mat._col);
	}

	for (int i = 0; i < _row; i++) {
		for (int j = 0; j < _col; j++) {
			_mat[i][j] = scalar*mat[i][j];
		}
	}

}

// Something wrong.......................................
template<typename T>
void FMatrix<T>::mult(FMatrix<T>& mat1, FMatrix<T>& mat2) {
	if (mat1._col != mat2._row) {
		cout << "FMatrix - mult(FMatrix<T>& mat1, FMatrix<T>& mat2) : wrong dimension" << endl;
		exit(1);
	}

	/*if (_row != mat1._row || _col != mat2._col) {
	resize(mat1._row, mat2._col);
	}*/

	T sum;
	FMatrix<T> temp(mat1._row, mat2._col);
	for (int i = 0; i < mat1._row; i++) {
		for (int j = 0; j < mat2._col; j++) {
			sum = 0;

			for (int k = 0; k < mat1._col; k++) {
				sum += mat1[i][k] * mat2[k][j];
			}
			//cout << i << ", " << j << " : " << sum;
			temp[i][j] = sum;
		}
	}

	copy(temp);
	temp.release();
}

template<typename T>
void FMatrix<T>::transpose() {
	if (_row != _col) {
		FMatrix<T> temp;
		temp.copy(*this);
		resize(_col, _row);

		for (int i = 0; i < _row; i++) {
			for (int j = 0; j < _col; j++) {
				_mat[i][j] = temp[j][i];
			}
		}
		temp.release();
	}
	else {
		T temp;

		for (int i = 0; i < _row; i++) {
			for (int j = i + 1; j < _col; j++) {

				temp = _mat[i][j];
				_mat[i][j] = _mat[j][i];
				_mat[j][i] = temp;
			}
		}
	}

}

template<typename T>
void FMatrix<T>::transpose(FMatrix<T>& mat) {
	if (_row != mat._col || _col != mat._row) {
		resize(mat._col, mat._row);
	}

	for (int i = 0; i < _row; i++) {
		for (int j = 0; j < _col; j++) {
			_mat[i][j] = mat[j][i];
		}
	}
}

template<typename T>
T FMatrix<T>::trace() {
	if (_row != _col) {
		cout << "FMatrix - trace() : the matrix is not square" << endl;
		exit(1);
	}

	T sum = 0;
	for (int i = 0; i < _row; i++) {
		sum += _mat[i][i];
	}

	return sum;
}



template<typename T>
void FVector<T>::mult(FMatrix<T>& mat, FVector<T>& vec) {
	if (mat._col != vec._size) {
		cout << "FVector<T> - mult(FMatrix<T>& mat, FVector<T>& vec) : different size" << endl;
		exit(1);
	}

	if (_size != mat._row) {
		release();
		_size = mat._row;
		_vec = new T[_size];
	}

	FVector<T> temp(mat._row);
	temp.copy(vec);

	T sum;
	int i, j;
	for (i = 0; i < _size; i++) {
		sum = 0;
		for (j = 0; j < vec._size; j++) {
			sum += mat[i][j] * temp[j];
		}
		_vec[i] = sum;
	}

	temp.release();
}







#endif
