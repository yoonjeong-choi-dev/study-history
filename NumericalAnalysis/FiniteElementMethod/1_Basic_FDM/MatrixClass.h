#ifndef __MATRIXCLASS_H__
#define __MATRIXCLASS_H__

#include <iostream>
#include <cmath>
#include <cstdlib>

#define PI 3.14159265358979

using namespace std;

class Vector
{
private:
	int col;
	double *vector;
	//Vector(const Vector& v) { };
	//Vector& operator=(const Vector v) { };

public:
	Vector(int n = 1);		//v := zero vector 로 초기화
	~Vector();				//소멸자

	double& operator[] (int idx);
	double& operator[] (int idx) const;
	int Col() const { return col; }
};

class Matrix
{
private:
	int row;
	int col;
	Vector **matrix;
public:
	Matrix(int n = 1, int m = 1);
	~Matrix();
	int Row() const { return row; }
	int Col() const { return col; }

	Vector& operator[](int idx);
};


void Show(Vector& v);
void Copy(Vector& v1, Vector& v2);							//v1=v2
void Mult(double s, Vector& v1, Vector& v2);
double Inner(Vector& v1, Vector& v2);
double Norm(Vector& v1);
double Dist(Vector& v1, Vector& v2);

void Show(Matrix& mat);
void Copy(Matrix& mat1, Matrix& mat2);						//mat1=mat2
void Mult(double s, Matrix& mat1, Matrix& mat2);				//mat2=s*mat1
void Mult(Matrix& mat1, Matrix& mat2, Matrix& result);		//result=mat1*mat2
void Add(Matrix& mat1, Matrix& mat2, Matrix& result);		//result=mat1+mat2
void Transpose(Matrix& mat1, Matrix& mat2);					//mat2=tranpose of mat1
double Maxnorm(Matrix& mat1, Matrix& mat2);

void Mult(Matrix& A, Vector& x, Vector& b);				//b=Ax
double Inner_Mat(Vector&v1, Vector&v2, Matrix& A);

//Vector class 멤버 함수 정의
Vector::Vector(int n) : col(n)
{
	vector = new double[n];
	for (int i = 0; i < col; i++)
		vector[i] = 0;
}

Vector::~Vector()
{
	delete[]vector;
}

double& Vector::operator[] (int idx)
{
	if (idx < 0 || idx >= col)
	{
		cout << "Array index out of bound " << endl;
		exit(1);
	}
	return vector[idx];
}

double& Vector::operator[] (int idx) const
{
	if (idx < 0 || idx >= col)
	{
		cout << "Array index out of bound " << endl;
		exit(1);
	}
	return vector[idx];
}

//Matrix class 멤버함수 정의
Matrix::Matrix(int n, int m) :row(n), col(m)
{
	matrix = new Vector*[n];
	for (int i = 0; i < n; i++)
		matrix[i] = new Vector(m);

}
Matrix::~Matrix()
{
	for (int i = 0; i < row; i++)
		delete matrix[i];
	delete[]matrix;

}

Vector& Matrix::operator[](int idx)
{
	if (idx < 0 || idx >= row)
	{
		cout << "Array index out of bound" << endl;
		exit(1);
	}
	return *(matrix[idx]);
}


// 외장 함수 정의
void Show(Vector& v)
{
	cout << "[ ";
	for (int i = 0; i < v.Col(); i++)
		cout << v[i] << ' ';
	cout << ']' << endl;
}

void Copy(Vector& v1, Vector& v2)
{
	if (v1.Col() != v2.Col())
	{
		cout << "Dimensions are not equal" << endl;
		exit(1);
	}
	for (int i = 0; i < v1.Col(); i++)
		v1[i] = v2[i];
}

void Mult(double s, Vector& v1, Vector& v2)
{
	if (v1.Col() != v2.Col())
	{
		cout << "Dimensions are not equal" << endl;
		exit(1);
	}
	for (int i = 0; i < v1.Col(); i++)
		v2[i] = s*v1[i];
}

double Inner(Vector& v1, Vector& v2)
{
	if (v1.Col() != v2.Col())
	{
		cout << "Dimensions are not equal" << endl;
		exit(1);
	}

	double sum = 0;

	for (int i = 0; i < v1.Col(); i++)
		sum += v1[i] * v2[i];

	return sum;
}
double Norm(Vector& v1)
{
	double sum = 0;
	for (int i = 0; i < v1.Col(); i++)
		sum += v1[i] * v1[i];
	return sqrt(sum);
}

double Dist(Vector& v1, Vector& v2)
{
	if (v1.Col() != v2.Col())
	{
		cout << "Dimensions are not equal" << endl;
		exit(1);
	}

	double sum = 0;
	for (int i = 0; i<v1.Col(); i++)
		sum += pow(v1[i] - v2[i], 2);
	return sqrt(sum);
}

void Show(Matrix& mat)
{
	for (int i = 0; i < mat.Row(); i++)
	{
		for (int j = 0; j < mat.Col(); j++)
			cout << mat[i][j] << " ";
		cout << endl;
	}
}

void Copy(Matrix& mat1, Matrix& mat2)
{
	if (mat1.Col() != mat2.Col() || mat1.Row() != mat2.Row())
	{
		cout << "Dimensions are not equal" << endl;
		exit(1);
	}

	int row = mat1.Row(); int col = mat1.Col();

	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			mat1[i][j] = mat2[i][j];

}

void Mult(double s, Matrix& mat1, Matrix& mat2)
{
	if (mat1.Col() != mat2.Col() || mat1.Row() != mat2.Row())
	{
		cout << "Dimensions are not equal" << endl;
		exit(1);
	}
	int row = mat1.Row(); int col = mat1.Col();

	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			mat1[i][j] = s*mat2[i][j];
}

void Mult(Matrix& mat1, Matrix& mat2, Matrix& result)
{
	if (mat1.Col() != mat2.Row())
	{
		cout << "Dimensions(Input) Error" << endl;
		exit(1);
	}

	if (result.Row() != mat1.Row() || result.Col() != mat2.Col())
	{
		cout << "Dimension(Output) Error" << endl;
		exit(1);
	}

	for (int i = 0; i < result.Row(); i++)
	{
		for (int j = 0; j < result.Col(); j++)
		{
			double sum = 0;
			for (int k = 0; k < mat1.Col(); k++)
				sum += mat1[i][k] * mat2[k][j];
			result[i][j] = sum;
		}
	}
}


void Add(Matrix& mat1, Matrix& mat2, Matrix& result)
{
	if (mat1.Col() != mat2.Col() || mat1.Row() != mat2.Row())
	{
		cout << "Dimensions(Input) Error" << endl;
		exit(1);
	}

	if (mat1.Col() != result.Col() || mat1.Row() != result.Row())
	{
		cout << "Dimensions(Output) Error" << endl;
		exit(1);
	}

	for (int i = 0; i < result.Row(); i++)
	{
		for (int j = 0; j < result.Col(); j++)
		{
			result[i][j] = mat1[i][j] + mat2[i][j];
		}
	}

}
void Transpose(Matrix& mat1, Matrix& mat2)
{
	if (mat1.Col() != mat2.Row() || mat1.Row() != mat2.Col())
	{
		cout << "Dimensions are not equal" << endl;
		exit(1);
	}
	for (int i = 0; i < mat2.Row(); i++)
		for (int j = 0; j < mat2.Col(); j++)
			mat2[i][j] = mat1[j][i];

}


double Maxnorm(Matrix& mat1, Matrix& mat2)
{
	if (mat1.Col() != mat2.Col() || mat1.Row() != mat2.Row())
	{
		cout << "Dimensions are not equal" << endl;
		exit(1);
	}

	double max = abs(mat1[0][0] - mat2[0][0]);
	for (int i = 0; i < mat1.Row(); i++)
	{
		for (int j = 0; j < mat1.Col(); j++)
		{
			if (max < abs(mat1[i][j] - mat2[i][j]))
				max = abs(mat1[i][j] - mat2[i][j]);
		}
	}
	return max;
}

void Mult(Matrix& A, Vector& x, Vector& b)
{
	if (A.Col() != x.Col() || A.Row() != b.Col())
	{
		cout << "Dimensions Error" << endl;
		exit(1);
	}

	for (int i = 0; i < b.Col(); i++)
		b[i] = Inner(A[i], x);
}

double Inner_Mat(Vector&v1, Vector&v2, Matrix& A)
{
	Vector w(A.Row());
	double sum = 0;

	for (int i = 0; i < A.Row(); i++)
		w[i] = Inner(A[i], v2);

	for (int i = 0; i < A.Row(); i++)
		sum += v1[i] * w[i];
	return sum;
}


#endif