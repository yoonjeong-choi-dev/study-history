#ifndef __CGMETHOD_H__
#define __CGMETHOD_H__
#include "MatrixClass.h"

#define EPSILON 1.0e-16
#define MAXLOOP 100

//Condition : a matrix is symmetric and positive definite

void Con_Grad(Matrix& matrix, Vector& b, Vector& x)
{
	if (matrix.Col() != b.Col() || b.Col() != x.Col())
	{
		cout << "Dimension Error" << endl;
		exit(1);
	}

	int DIM = matrix.Col();

	double alpha, beta, norm;
	Vector r(DIM);
	Vector s(DIM);
	Vector temp(DIM);
	
	Mult(matrix, x, temp);

	for (int i = 0; i < DIM; i++)
	{
		r[i] = b[i] - temp[i];
	}

	Copy(s, r);

	for (int i = 0; i < MAXLOOP; i++)
	{
		norm = Norm(r);
		if (norm < EPSILON)
		{
			//cout << "# of Loop : " << i + 1 << endl;
			break;
		}


		alpha = Inner(r, r) / Inner_Mat(s, s, matrix);
		Mult(matrix, s, temp);
		for (int j = 0; j < DIM; j++)
		{
			x[j] += alpha*s[j];		//update solution
			r[j] = r[j] - alpha*temp[j];
		}
		beta = Inner(r, r) / pow(norm, 2);
		for (int j = 0; j < DIM; j++)
			s[j] = r[j] + beta*s[j];

	}
}



#endif
