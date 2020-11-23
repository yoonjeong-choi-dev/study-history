#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <typeinfo>

#include <time.h>

#define _USE_MATH_DEFINES
#include <math.h>



#include "Vector_Matrix.h"
using namespace std;

class Norms {
public:
	static double L2(FVector<double>& real, FVector<double>& estimate) {
		int size = real._size;

		FVector<double> errors(size);

		for (int i = 0; i < size; i++)
			errors[i] = real[i] - estimate[i];


		double error;
		error = errors.norm_l2();


		return error;
	}

	static double L_inf(FVector<double>& real, FVector<double>& estimate) {
		int size = real._size;

		vector<double> errors(size);

		for (int i = 0; i < size; i++)
			errors[i] = abs(real[i] - estimate[i]);

		vector<double>::iterator max_itr;
		max_itr = max_element(errors.begin(), errors.end());

		double max_error = *max_itr;

		return max_error;
	}
};

class HouseholderTransformation {
private:
	static int sgn(double x) {
		if (x >= 0)
			return 1;
		else 
			return -1;
	}

public:

	static void Tridiagonalization(FMatrix<double>& mA) {
		// mA : symmetric matrix
		if (mA._row != mA._col) {
			cout << "HouseholderTransformation - UpperHessenberg(FMatrix<double>& mA) : not square" << endl;
			exit(1);
		}

		int size = mA._row;


		double sum, alpha;
		FVector<double> w, u;

		int len;	// size of the vector w in each iteration
		int start_entry;	// starting entry in each iteration
		int sign;

		int i, j, k;

		// Fix j-th column
		for (j = 0; j < size - 2; j++) {
			len = size - 1 - j;
			start_entry = j + 1;

			w.resize(len);
			u.resize(len);

			// alpha_j = mA[start_entry][j] ~ mA[size-1][j]
			// Sign of the first entry of alpha_j
			sign = sgn(mA[start_entry][j]);


			// Calculate w
			for (k = 0; k < len; k++) {
				w[k] = mA[start_entry + k][j];
			}
			alpha = -sign*w.norm_l2();
			w[0] -= alpha;
			w.normalize();

			// Update the matrix mA : 
			// 1) Update alpha_j entries
			mA[start_entry][j] = alpha;
			for (k = 1; k < len; k++) {
				mA[start_entry + k][j] = 0;
			}

			// 2) Update alpha_j^' : mA[j][j+1] ~ mA[j][size-1]
			//    Do the same procedure in 1) Update alpha_j entries by symmetricity

			mA[j][start_entry] = alpha;
			for (k = 1; k < len; k++) {
				mA[j][start_entry + k] = 0;
			}

			// 3) Update submatrix : mA[start_entry][start_entry] ~ mA[size-1][size-1]
			//	  mA <- (I - 2ww*)mA(I - 2ww*)

			// 3-1) mA <- (I-2ww*)mA
			//		u.T = w.T*mA
			//		mA <- mA - 2wu.T
			for (i = 0; i < len; i++) {
				//Update u[i]
				sum = 0.;
				for (k = 0; k < len; k++) {
					sum += w[k] * mA[start_entry + k][start_entry + i];
				}
				u[i] = sum;
			}

			for (i = 0; i < len; i++) {
				for (k = 0; k < len; k++) {
					//Update mA[j+1+i][j+1+k]
					mA[start_entry + i][start_entry + k] -= 2 * w[i] * u[k];
				}
			}

			// 3-2) mA <- mA(I-2ww*)
			//		u = mA*w
			//		mA <- mA - 2uw*
			for (i = 0; i < len; i++) {
				//Update u[i]
				sum = 0.;
				for (k = 0; k < len; k++) {
					sum += mA[start_entry + i][start_entry + k] * w[k];
				}
				u[i] = sum;
			}

			for (i = 0; i < len; i++) {
				for (k = 0; k < len; k++) {
					//Update mA[j+1+i][j+1+k]
					mA[start_entry + i][start_entry + k] -= 2 * u[i] * w[k];
				}
			}
		}
	}

	static void Tridiagonalization(FMatrix<double>& mA, FMatrix<double>& tri) {
		tri.copy(mA);
		Tridiagonalization(tri);
	}

	static void UpperHessenberg(FMatrix<double>& mA) {
		if (mA._row != mA._col) {
			cout << "HouseholderTransformation - UpperHessenberg(FMatrix<double>& mA) : not square" << endl;
			exit(1);
		}

		int size = mA._row;
		

		double sum, alpha,dot;
		FVector<double> w,u;
		
		int len;	// size of the vector w in each iteration
		int start_entry;	// starting entry in each iteration
		int sign;
		
		int i, j, k;

		// Fix j-th column
		for (j = 0; j < size - 2; j++) {
			len = size - 1 - j;
			start_entry = j + 1;

			w.resize(len);
			u.resize(len);

			// alpha_j = mA[start_entry][j] ~ mA[size-1][j]
			// Sign of the first entry of alpha_j
			sign = sgn(mA[start_entry][j]);

			
			// Calculate w
			for (k = 0; k < len; k++) {
				w[k] = mA[start_entry + k][j];
			}
			alpha = -sign*w.norm_l2();
			w[0] -= alpha;
			w.normalize();

			// Update the matrix mA : 
			// 1) Update alpha_j entries
			mA[start_entry][j] = alpha;
			for (k = 1; k < len; k++) {
				mA[start_entry+k][j] = 0;
			}

			// 2) Update alpha_j^' : mA[j][j+1] ~ mA[j][size-1]
			//    alpha_j^' <- alpha_j^' - 2(alpha_j^', w)w.T
			dot = 0.;
			for (k = 0; k < len; k++) {
				dot += mA[j][start_entry + k] * w[k];
			}
			for (k = 0; k < len; k++) {
				mA[j][start_entry + k] -= 2.*dot*w[k];
			}

			// 3) Update submatrix : mA[start_entry][start_entry] ~ mA[size-1][size-1]
			//	  mA <- (I - 2ww*)mA(I - 2ww*)
			
			// 3-1) mA <- (I-2ww*)mA
			//		u.T = w.T*mA
			//		mA <- mA - 2wu.T
			for (i = 0; i < len; i++) {
				//Update u[i]
				sum = 0.;
				for (k = 0; k < len; k++) {
					sum += w[k] * mA[start_entry + k][start_entry + i];
				}
				u[i] = sum;
			}
			
			for (i = 0; i < len; i++) {
				for (k = 0; k < len; k++) {
					//Update mA[j+1+i][j+1+k]
					mA[start_entry + i][start_entry + k] -= 2 * w[i] * u[k];
				}
			}

			// 3-2) mA <- mA(I-2ww*)
			//		u = mA*w
			//		mA <- mA - 2uw*
			for (i = 0; i < len; i++) {
				//Update u[i]
				sum = 0.;
				for (k = 0; k < len; k++) {
					sum += mA[start_entry + i][start_entry + k] * w[k];
				}
				u[i] = sum;
			}

			for (i = 0; i < len; i++) {
				for (k = 0; k < len; k++) {
					//Update mA[j+1+i][j+1+k]
					mA[start_entry + i][start_entry + k] -= 2 * u[i] * w[k];
				}
			}
		}

	}

	static void UpperHessenberg(FMatrix<double>& mA, FMatrix<double>& tri) {
		tri.copy(mA);
		UpperHessenberg(tri);
	}

	static void example() {
		FMatrix<double> mA1({ { 4,2,2,1 },{ 2,-3,1,1 },{ 2,1,3,1 },{ 1,1,1,2 } });
		FMatrix<double> mA2({ { 4,1,2,-5,1,4 },{ 1,2,0,4,5,3 },{ 2,0,3,-1,2,1 },{ -5,4,-1,1,5,2 },{ 1,5,2,5,-2,4 },{ 4,3,1,2,4,1 } });

		cout << " ======================================" << endl;
		cout << " Example 1" << endl;

		cout << " Original matrix : " << endl;
		mA1.print(true);
		cout << " Transformation : " << endl;
		//HouseholderTransformation::UpperHessenberg(mA1);
		HouseholderTransformation::Tridiagonalization(mA1);
		mA1.print(true);
		cout << " ======================================" << endl;
		cout << " ======================================" << endl;
		cout << " Example 2" << endl;

		cout << " Original matrix : " << endl;
		mA2.print(true);
		cout << " Transformation : " << endl;
		//HouseholderTransformation::UpperHessenberg(mA2);
		HouseholderTransformation::Tridiagonalization(mA2);
		mA2.print(true);
		cout << " ======================================" << endl;
	}
};

class Solver {
public:
	static void CG(FMatrix<double>& mA, FVector<double>& x, FVector<double>& b, double epsilon = 1.0e-16, bool verbose = true) {
		if (mA._row != b._size) {
			cout << "Solver - CG : b has wrong size" << endl;
			exit(1);
		}
		
		if (verbose)
			cout << endl << " SOLVER : Conjugate Gradient Method" << endl;

		int size = b._size;
		

		double alpha, beta,r_norm,d_norm,r_next_norm;
		FVector<double> Ax(size), d(size), Ad(size), r(size);
		//v == d

		int i, j;

		x.resize(size, 0);		// Initialize x
		Ax.mult(mA, x);			// Ax = A*x
		r.add(1., b, -1., Ax);	// r = b - Ax
		d.copy(r);
		r_norm = (r,r);

		if (sqrt(r_norm) < epsilon)
			return;

		for (j = 1;; j++) {
			Ad.mult(mA, d);		//Ad = A*d

			d_norm = (Ad, d);	// d_norm = d.T*A*d = <A*d, d>
			alpha = r_norm / d_norm;

			for (i = 0; i < size; i++) {
				x[i] += alpha*d[i];		//x = x + alpha*d
				r[i] -= alpha*Ad[i];	//r = r - alpha*A*d
			}

			r_next_norm = (r, r);		// r_next_norm = norm^2 for updated r

			// Stopping Criteria
			if (sqrt(r_next_norm) < epsilon) {
				break;
			}

			beta = r_next_norm / r_norm;
			for (i = 0; i < size; i++) {
				d[i] = r[i] + beta*d[i];	// d = r + beta*d
			}

			r_norm = r_next_norm;

			if (verbose) {
				if (j % 10 == 0) {
					for (i = 0; i < 100; i++) {
						cout << "\b";
					}
					printf(" Iteration: %6d		Residual: %20.15f", j, sqrt(r_norm));
					
				}
			}
		}

		if (verbose) {
			for (i = 0; i < 100; i++) {
				cout << "\b";
			}
			printf(" Iteration: %6d		Residual: %20.15f", j, sqrt(r_norm));
			cout << endl << endl;
		}
	}

	static void example_CG() {
		FMatrix<double> mA(16, 16, 0);

		mA[0][0] = 4.;
		mA[0][1] = -1.;
		mA[mA._row - 1][mA._row - 1] = 4.;
		mA[mA._row - 1][mA._row - 2] = -1.;

		for (int i = 1; i < mA._row - 1; i++) {
			mA[i][i] = 4.;
			mA[i][i - 1] = -1.;
			mA[i][i + 1] = -1.;
		}

		FVector<double> real(16, 1);
		FVector<double> b, x;
		b.mult(mA, real);
		b.print();

		Solver::CG(mA, x, b);
		x.print();
	}
};

class QR_Decomposition {
/*	A = QR
 1. A : m*n matrix
	- m : dimension for column vectors
	- n : number of column vectors

 2. Q : m*n orthogonal matrix
	- columns form an orthonormal basis for span({columns of A})
	- if A has k-independent column vectors
	  => fisrt k columns of Q form an ONB

 3. R : m*n upper triangular matrix
	- Suppose A is of full column rank s.t A = [w_1,w_2,....,w_n]
	- Write Q=[q_1,q_2,.....,q_n], which is an ONB
	- Then R[i][j] = (q_i, w_j)
*/

private:
	static int sgn(double x) {
		if (x > 0)
			return 1;
		else if (x < 0)
			return -1;
		else
			return 0;
	}

public:
	//Gram-Schmidt Process
	static void CGS(FMatrix<double>&A, FMatrix<double>& Q, FMatrix<double>& R) {
		// Classic Gram-Schmidt
		int dim = A._row;
		int n_vec = A._col;

		if (Q._row != dim || Q._col != dim)
			Q.resize(dim, dim, 0);

		if (R._row != dim || R._col != n_vec)
			R.resize(dim, n_vec, 0);
		else {
			// Set zero 
			for (int i = 0; i < dim; i++) {
				for (int j = 0; j < n_vec; j++) {
					R[i][j] = 0.;
				}
			}
		}
		
		int i, j, k;

		for (j = 0; j < n_vec; j++) {
			
			// Copy the j-th column of  A to Q
			for (i = 0; i < dim; i++) {
				Q[i][j] = A[i][j];
			}

			// GS-process : find k-th orthonormal basis
			for (k = 0; k < j; k++) {
				//  R[j][k] = (A_j, Q_k) 
				for (i = 0; i < dim; i++) {
					R[k][j] += A[i][j] * Q[i][k];
				}
				
				// Q_j <- Q_j - (A_j, Q_k)Q_k
				for (i = 0; i < dim; i++) {
					Q[i][j] -= R[k][j]*Q[i][k];
				}
			}

				
			// Normalize j-th col of Q
			// norm = (Q_j',Q_j') = (A_j, Q_j') by construnction of Q_k
			// Q_k = Q_k' / norm
			// => R[j][j] = (A_j, Q_j) = (A_j, Q_j'/sqrt(norm))
			//			  = (Q_j', Q_j')/sqrt(norm)

			for (i = 0; i < dim; i++)
				R[j][j] += pow(Q[i][j], 2);

			
			R[j][j] = sqrt(R[j][j]);
			for (i = 0; i < dim; i++)
				Q[i][j] = Q[i][j] / R[j][j];



		}
		
	}

	static void MGS(FMatrix<double>&A, FMatrix<double>& Q, FMatrix<double>& R) {
		// Modified Gram-Schmidt
		// Q and R is reduced form
		int dim = A._row;
		int n_vec = A._col;

		Q.copy(A);

		// Set R as a zero matrix
		if (R._row != n_vec || R._col != n_vec)
			R.resize(n_vec, n_vec, 0);
		else {
			// Set zero 
			for (int i = 0; i < n_vec; i++) {
				for (int j = 0; j < n_vec; j++) {
					R[i][j] = 0.;
				}
			}
		}

		double sum, norm;
		int i, j, k;

		for (j = 0; j < n_vec; j++) {
			
			//R[j][j] : sqrt(norm(A_j))
			for (i = 0; i < dim; i++) {
				R[j][j] += pow(Q[i][j], 2);
			}
			R[j][j] = sqrt(R[j][j]);

			//Q_j : normalize A_j with the norm R[j][j]
			for (i = 0; i < dim; i++) {
				Q[i][j] = Q[i][j] / R[j][j];
			}
			
			// Row wise
			for (k = j + 1; k < n_vec; k++) {
				//R[j][k] : (Q_j, A_k)
				for (i = 0; i < dim; i++) {
					R[j][k] += Q[i][j] * Q[i][k];
				}

				// Projection : Q_k = Q_k - R[j][k]Q_j
				for (i = 0; i < dim; i++) {
					Q[i][k] = Q[i][k] - R[j][k] * Q[i][j];
				}
			}
		}

	}

	static void MGS(FMatrix<double>&A, FMatrix<double>& R) {
		// Modified Gram-Schmidt
		int dim = A._row;
		int n_vec = A._col;

		// Set R as a zero matrix
		if (R._row != n_vec || R._col != n_vec)
			R.resize(n_vec, n_vec, 0);
		else {
			// Set zero 
			for (int i = 0; i < n_vec; i++) {
				for (int j = 0; j < n_vec; j++) {
					R[i][j] = 0.;
				}
			}
		}
		
		int i, j, k;

		for (j = 0; j < n_vec; j++) {

			//R[j][j] : sqrt(norm(A_j))
			for (i = 0; i < dim; i++) {
				R[j][j] += pow(A[i][j], 2);
			}
			R[j][j] = sqrt(R[j][j]);

			//Q_j : normalize A_j with the norm R[j][j]
			for (i = 0; i < dim; i++) {
				A[i][j] = A[i][j] / R[j][j];
			}

			// Row wise
			for (k = j + 1; k < n_vec; k++) {
				//R[j][k] : (Q_j, A_k)
				for (i = 0; i < dim; i++) {
					R[j][k] += A[i][j] * A[i][k];
				}

				// Projection : A_k = A_k - R[j][k]A_j
				for (i = 0; i < dim; i++) {
					A[i][k] = A[i][k] - R[j][k] * A[i][j];
				}
			}
			
		}
	}
	
	// Householder transformation
	static void Householder(FMatrix<double>&A, FMatrix<double>& W) {
		// Householder Reflection : A -> R(upper triangular)
		int dim = A._row;
		int n_vec = A._col;

		double alpha, beta, gamma;
		FVector<double> w(dim);
		// W[i] : i-th Householder vector
		W.resize(n_vec, dim);

		int i, j, k;

		for (k = 0; k < n_vec; k++) {
			// alpha : -sgn(A[k][k])*l2_norm(A[k][k]~A[dim-1][k])
			alpha = 0;
			for (i = k; i < dim; i++) {
				alpha += A[i][k] * A[i][k];
			}

			alpha = -sgn(A[k][k])*sqrt(alpha);

			// w : (0, 0 ,..., a[k][k]-alpha, a[k+1][k], ....,a[dim-1][k])
			// beta = (w,w)
			beta = 0.;
			for (i = 0; i < dim; i++) {
				if (i < k) {
					w[i] = 0.;
				}
				else if (i == k) {
					w[i] = A[k][k] - alpha;
					beta += w[i] * w[i];
				}
				else {
					w[i] = A[i][k];
					beta += w[i] * w[i];
				}
			}

			
			if (beta == 0)
				continue;

			// Copy w into W[k]
			for (i = 0; i < dim; i++)
				W[k][i] = w[i] / beta;

			for (j = k; j < n_vec; j++) {
				// gamma = (w, A_j)
				// here, w[i]=0 for i<k
				gamma = 0.;
				for (i = k; i < dim; i++)
					gamma += w[i] * A[i][j];

				// A = (I-2ww*)A = I - 2ww*A where w is already normalized
				//  => we have to divide beta=(w,w)
				// A_j = A_j - 2ww*A_j = A_j - 2(w,A_j)w = A_j - 2gamma*w
				// A_j = A_j - 2*gamma/beta*w
				// A_j = A_j - 2*(w, A_j)/(w,w)w
				for (i = 0; i < dim; i++) {
					A[i][j] -= 2 * gamma / beta*w[i];
				}
			}
			A.print(1);

		}
	}

	static void Householder(FMatrix<double>& A) {
		// Householder Reflection : A -> R(upper triangular)
		int dim = A._row;
		int n_vec = A._col;
		
		double alpha, beta, gamma;
		FVector<double> w(dim);

		int i, j, k;

		for (k = 0; k < n_vec; k++) {
			// alpha : -sgn(A[k][k])*l2_norm(A[k][k]~A[dim-1][k])
			alpha = 0;
			for (i = k; i < dim; i++) {
				alpha += A[i][k] * A[i][k];
			}
		
			alpha = -sgn(A[k][k])*sqrt(alpha);

			// w : (0, 0 ,..., a[k][k]-alpha, a[k+1][k], ....,a[dim-1][k])
			// beta = (w,w)
			beta = 0.;
			for (i = 0; i < dim; i++) {
				if (i < k) {
					w[i] = 0.;
				}
				else if (i == k) {
					w[i] = A[k][k] - alpha;
					beta += w[i] * w[i];
				}
				else {
					w[i] = A[i][k];
					beta += w[i] * w[i];
				}
			}
			
			if (beta == 0)
				continue;

			for (j = k; j < n_vec; j++) {
				// gamma = (w, A_j)
				// here, w[i]=0 for i<k
				gamma = 0.;
				for (i = k; i < dim; i++)
					gamma += w[i] * A[i][j];

				// A = (I-2ww*)A = I - 2ww*A where w is already normalized
				//  => we have to divide beta=(w,w)
				// A_j = A_j - 2ww*A_j = A_j - 2(w,A_j)w = A_j - 2gamma*w
				// A_j = A_j - 2*gamma/beta*w
				// A_j = A_j - 2*(w, A_j)/(w,w)w
				for (i = 0; i < dim; i++) {
					A[i][j] -= 2 * gamma / beta*w[i];
				}
			}
			
		}
	}

public:
	static void example_CGS() {
		cout << " =============================================" << endl;
		cout << "Example 1 :" << endl;
		FMatrix<double> A1, Q1, R1;
		A1.setAll({ { 12,-51,4 },{ 6,167,-68 },{ -4,24,-41 } });
		R1.resize(A1._row, A1._col, 1);
		QR_Decomposition::CGS(A1, Q1, R1);
		A1.print(1);
		Q1.print(1);
		R1.print(1);
		cout << " =============================================" << endl;
		cout << " =============================================" << endl;
		cout << "Example 2 : " << endl;
		FMatrix<double> A2, Q2, R2;
		A2.setAll({ { 1,-1,0 },{ 0,1,1 },{ 1,1,1 } });
		R1.resize(A2._row, A2._col, 2);
		QR_Decomposition::CGS(A2, Q2, R2);
		A2.print(true);
		Q2.print(true);
		R2.print(true);
		cout << " =============================================" << endl;
	}

	static void example_MGS() {
		cout << " =============================================" << endl;
		cout << " example_MGS " << endl;
		cout << " =============================================" << endl;
		cout << " Example 1 :" << endl;
		FMatrix<double> A1, Q1, R1;
		A1.setAll({ { 12,-51,4 },{ 6,167,-68 },{ -4,24,-41 } });
		R1.resize(A1._row, A1._col, 1);
		QR_Decomposition::MGS(A1,Q1, R1);
		A1.print(1);
		Q1.print(1);
		R1.print(1);
		cout << " =============================================" << endl;
		cout << " =============================================" << endl;
		cout << " Example 2 : " << endl;
		FMatrix<double> A2, Q2, R2;
		A2.setAll({ { 1,-1,0 },{ 0,1,1 },{ 1,1,1 } });
		R1.resize(A2._row, A2._col, 2);
		QR_Decomposition::MGS(A2,Q2, R2);
		A2.print(true);
		Q2.print(true);
		R2.print(true);
		cout << " =============================================" << endl;
	}

	static void example_MGS2() {
		cout << " =============================================" << endl;
		cout << " example_MGS2 " << endl;
		cout << " =============================================" << endl;

		FMatrix<double> A, Q, R;
		A.setAll({ {1,0,0},{0,1,0},{0,0,1},{-1,1,0},{-1,0,1,},{0,-1,1} });
		

		MGS(A, Q, R);

		cout << "A :" << endl; A.print(1);
		cout << "Q :" << endl; Q.print(1);
		cout << "R :" << endl; R.print(1);



	}

	static void example_CGS_MGS() {
		FMatrix<double> A1, Q1, R1;
		double epsilon = 1e-7;
		double a1, a2;

		A1.setAll({ {1,1, 1},{epsilon,epsilon ,0},{ epsilon,0,epsilon } });

		cout << " =============================================" << endl;
		QR_Decomposition::CGS(A1, Q1, R1);
		a1 = Q1[2][2];
		A1.print(1);
		Q1.print();
		R1.print();
		cout << " =============================================" << endl;
		cout << " =============================================" << endl;
		QR_Decomposition::MGS(A1, Q1, R1);
		a2 = Q1[2][2];
		A1.print(1);
		Q1.print();
		R1.print();
		cout << " =============================================" << endl;

		cout << " Check Q1" << endl;
		cout << " CGS - Q[2][2] : " << a1 << endl;
		cout << " MGS - Q[2][2] : " << a2 << endl;
	}

	static void exmaple_Householder() {
		cout << " =============================================" << endl;
		cout << "Example 1 :" << endl;
		FMatrix<double> A1, Q1, R1;
		A1.setAll({ { 12,-51,4 },{ 6,167,-68 },{ -4,24,-41 } });
		R1.resize(A1._row, A1._col, 1);

		//QR_Decomposition::Householder(A1);
		QR_Decomposition::Householder(A1, Q1);
		A1.print(1);
		Q1.print(1);
		//R1.print(1);
		cout << " =============================================" << endl;
		cout << " =============================================" << endl;
		cout << "Example 2 : " << endl;
		FMatrix<double> A2, Q2, R2;
		A2.setAll({ { 1,-1,0 },{ 0,1,1 },{ 1,1,1 } });
		R1.resize(A2._row, A2._col, 2);
		
		//QR_Decomposition::Householder(A2);
		QR_Decomposition::Householder(A2, Q2);
		A2.print(true);
		Q2.print(true);
		//R2.print(true);
		cout << " =============================================" << endl;
	}
};

class FinalProject1 {
private:
	static void GaussianQuadrature(FVector<double>& points, FVector<double>& weights, int num_points) {
		// Returns GaussianQuadrature points and weights for [-1, 1]
		// Only for num_points = 2,3,4,5

		points.resize(num_points);
		weights.resize(num_points);

		if (num_points == 2) {
			points[0] = 1. / sqrt(3.);
			points[1] = -1. / sqrt(3.);

			weights[0] = 1.;
			weights[1] = 1.;
		}
		else if (num_points == 3) {
			points[0] = 0;
			points[1] = sqrt(3. / 5);
			points[2] = -sqrt(3. / 5);

			weights[0] = 8. / 9;
			weights[1] = 5. / 9;
			weights[2] = 5. / 9;
		}
		else if (num_points == 4) {
			points[0] = sqrt(3. / 7 - 2. / 7 * sqrt(6. / 5));
			points[1] = -sqrt(3. / 7 - 2. / 7 * sqrt(6. / 5));
			points[2] = sqrt(3. / 7 + 2. / 7 * sqrt(6. / 5));
			points[3] = -sqrt(3. / 7 + 2. / 7 * sqrt(6. / 5));

			weights[0] = (18. + sqrt(30.)) / 36;
			weights[1] = (18. + sqrt(30.)) / 36;
			weights[2] = (18. - sqrt(30.)) / 36;
			weights[3] = (18. - sqrt(30.)) / 36;
		}
		else if (num_points == 5) {
			points[0] = 0.;
			points[1] = 1. / 3 * sqrt(5. - 2.*sqrt(10. / 7));
			points[2] = -1. / 3 * sqrt(5. - 2.*sqrt(10. / 7));
			points[3] = 1. / 3 * sqrt(5. + 2.*sqrt(10. / 7));
			points[4] = -1. / 3 * sqrt(5. + 2.*sqrt(10. / 7));

			weights[0] = 128. / 225;
			weights[1] = (322. + 13 * sqrt(70.)) / 900;
			weights[2] = (322. + 13 * sqrt(70.)) / 900;
			weights[3] = (322. - 13 * sqrt(70.)) / 900;
			weights[4] = (322. - 13 * sqrt(70.)) / 900;
		}
		else {
			cout << "GaussianQuadrature : Wrong input " << endl;
		}
	}


private:
	// Problem setting
	static double f(double x) {
		return pow(x, 2)*exp(x);
	}

	static double F(double x) {
		return exp(x)*(pow(x, 2) - 2 * x + 2);
	}

public:
	static void MAIN() {
		cout << endl;
		cout << " =============================================" << endl;
		cout << " Problem 1 : Gaussian Quadarture " << endl;
		FVector<double> points, weights;
		FVector<double> interval({ -2., 0. });

		int order, i;
		double error, real_value, estimate;
		double scaling, moving;

		real_value = F(interval[1]) - F(interval[0]);
		cout << " Integrand : exp(x)*x^2" << endl;
		cout << " Interval : "; interval.print();
		cout << " Real value : " << real_value << endl;

		// We have to scale and move the Gaussian points 
		// if the interval for integration is not [-1, 1]
		scaling = (interval[1] - interval[0]) / 2;
		moving = (interval[1] + interval[0]) / 2;

		cout << " scaling, moving : " << scaling << ", " << moving << endl;

		for (order = 2; order <= 5; order++) {
			cout << " =============================================" << endl;
			cout << " Order : " << order << endl;
			GaussianQuadrature(points, weights, order);

			estimate = 0.;
			for (i = 0; i < order; i++) {
				estimate += weights[i] * f(scaling*points[i] + moving);
				estimate *= scaling;
			}

			error = abs(real_value - estimate);
			cout << " Gaussian Points :"; points.print();
			cout << " Gaussian Weights :"; weights.print();
			cout << " Estimate value : " << estimate << endl;
			cout << " Absolute Error : " << error << endl;

		}
		
		cout << " =============================================" << endl << endl;
	}
};

class FinalProject2 {
private:
	static double exact_x(double t) {
		return -0.5*t + 7. / 20 * exp(2 * t) - 7. / 20;
	}

	static double equation_f(double t, double x) {
		return 2.*x + 0.2 + t;
	}

	static void Heun_Method(FVector<double>& x, FVector<double>& t, int order) {
		double h = 1. / order;
		x.resize(order, 0);
		t.resize(order, 0);

		int i;
		double init_x = 0., init_t = 0.;
		double F1, F2;

		for (i = 0; i < order; i++) {
			t[i] = h*(i + 1);
		}

		// Initialize with the initial condition
		F1 = h*equation_f(init_t, init_x);
		F2 = h*equation_f(init_t + h, init_x + F1);
		x[0] = init_x + 0.5*(F1 + F2);

		for (i = 1; i < order; i++) {
			F1 = h*equation_f(t[i - 1], x[i - 1]);
			F2 = h*equation_f(t[i - 1] + h, x[i - 1] + F1);
			x[i] = x[i - 1] + 0.5*(F1 + F2);
		}
	}

public:
	static void MAIN() {
		FVector<double> sol, t;
		FVector<double> exact_sol;

		FVector<int> orders({ 5,10,20,40,80 });
		//FVector<int> orders({ 5,10,20});
		FVector<double> l2_errors(orders._size), max_errors(orders._size);
		FVector<double> l2_order(orders._size - 1), max_order(orders._size - 1);

		cout << endl;
		cout << " =============================================" << endl;
		cout << " Problem 2 : Huen's Method " << endl;

		int i, j, order;
		cout << " =========================================" << endl;
		for (i = 0; i < orders._size; i++) {
			order = orders[i];

			Heun_Method(sol, t, order);
			// Calculate the exact solution
			exact_sol.resize(order);
			for (j = 0; j < order; j++) {
				exact_sol[j] = exact_x(t[j]);
			}
			//cout << order <<" check" << endl;
			l2_errors[i] = Norms::L2(exact_sol, sol) * sqrt(1. / order);
			max_errors[i] = Norms::L_inf(exact_sol, sol);

			cout << " Order     : " << order << endl;
			//cout << " Estimate :"; sol.print();
			//cout << " Exact sol:"; exact_sol.print();
			cout << " L2 error  : " << l2_errors[i] << endl;
			cout << " Max error : " << max_errors[i] << endl;
			cout << " =========================================" << endl;
		}

		for (i = 0; i < orders._size - 1; i++) {
			l2_order[i] = log(l2_errors[i] / l2_errors[i + 1]) / log(2);
			max_order[i] = log(max_errors[i] / max_errors[i + 1]) / log(2);
		}

		cout << " Convergence order(L2 error)  : ";
		for (i = 0; i < l2_order._size; i++)
			cout << l2_order[i] << " ";
		cout << endl;

		cout << " Convergence order(max error) : ";
		for (i = 0; i < max_order._size; i++)
			cout << max_order[i] << " ";
		cout << endl;
		cout << " =========================================" << endl << endl;

	}
};

class FinalProject3 {
private:
	// Problem setting
	static double u1(FVector<double>& point) {
		// u1(x, y) = xy(1-x)(1-y)
		return point[0] * (1. - point[0])*point[1] * (1. - point[1]);
	}

	static double f1(FVector<double>& point) {
		// f1 = -div (grad u1)
		// f1(x, y) = -2(y(1-y) + x(1-x))
		return 2 * (point[0] * (1. - point[0]) + point[1] * (1. - point[1]));
	}

	static double u2(FVector<double>& point) {
		// u2(x, y) = (5x+y)exp(x+2y)
		return (5 * point[0] + point[1])*exp(point[0] + 2 * point[1]);
	}

	static double f2(FVector<double>& point) {
		// f2 = -div (grad u2)
		// f2(x, y) = -(14+25x+5y)exp(x+2y)
		return -1 * (14 + 25 * point[0] + 5 * point[1])*exp(point[0] + 2 * point[1]);
	}


public:
	static void make_Stiffeness(FMatrix<double> &mA, int order, bool h_term = false) {
		// order : the number of unknowns in one-side
		//  => mA : (order*order) by (order*order) matrix

		mA.resize(order*order, order*order, 0);


		int i, j, e, m;
		double mult;
		if (h_term) {
			mult = pow(order + 1, 2);
		}
		else {
			mult = 1.;
		}


		// 1st diagonal submatrix B
		e = 0;
		mA[e + 0][e + 0] = 4.*mult;
		for (i = 1; i < order; i++) {
			mA[e + i][e + i] = 4.*mult;
			mA[e + i - 1][e + i] = -1.*mult;
			mA[e + i][e + i - 1] = -1.*mult;
		}


		for (i = 1; i < order; i++) {
			e = order*i;
			// i-th diagonal submatrix B
			mA[e + 0][e + 0] = 4.*mult;
			for (j = 1; j < order; j++) {
				mA[e + j][e + j] = 4.*mult;
				mA[e + j - 1][e + j] = -1.*mult;
				mA[e + j][e + j - 1] = -1.*mult;
			}

			// upper and left part of i-th diagonal submatrix B
			m = order*(i - 1);
			for (j = 0; j < order; j++) {
				//upper 
				mA[m + j][e + j] = -1.*mult;
				//left
				mA[e + j][m + j] = -1.*mult;
			}


		}
	}

	static void FDM_Dirichlet(double(*u)(FVector<double> &p), double(*f)(FVector<double>& p), FVector<double>& interval, int level, double& l2_error, double& max_error) {

		//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
		//�̢�				Some Common Variables		     �̢�
		//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�

		double startp = interval[0], endp = interval[1];
		int nsN = pow(2, level) + 1;					// # of side node
		int nsT = nsN - 2;							// # of side unknwons
		int npT = nsT*nsT;							// # of total unknowns
		double h = (endp - startp) / (nsN - 1);		// mesh size
		double h_2 = pow(h, 2);

		/*cout << "Interval : " << startp << ", " << endp << endl;
		cout << "nsN(# of side node) : " << nsN << endl;
		cout << "npT(# of unknowns) : " << npT << endl;
		cout << "mesh size : " << h << endl;*/


		//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
		//�̢�				Declare  Variables		         �̢�
		//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
		// Goal : Solve mA*vX = vF 
		//		  Ax = h^2F
		FMatrix<double> mA;			// Stiffness Matrix
		FVector<double> vF;			// Boundary information
		FVector<double> vX;			// FDM Solution

		FVector<double> vExact;		// exact solution
		FVector<double> realP(2);
		// indexN[x-index][y-index] : global node index(lexicograhic order from bottom to top)
		FMatrix<int> indexN;
		// coordN[global index][0,1] = x/y
		FMatrix<double> coordN;
		// indexB[direction][] = global index node for boundary process
		// 0: down(-1,0)  1: up(+1,0)  2: left(0,-1) 3: right(0, +1)
		FMatrix<int> indexB;
		FMatrix<double> boundary;
		int i, j, k, e;
		double x, y;
		//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
		//�̢�	     Memory Allocation & Generation		     �̢�
		//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�

		make_Stiffeness(mA, nsT);
		vF.resize(npT, 0.);

		indexN.resize(nsT, nsT);
		for (i = 0; i < nsT; i++) {
			for (j = 0; j < nsT; j++) {
				indexN[i][j] = i*nsT + j;
			}
		}

		coordN.resize(npT, 2);
		for (i = 0; i < nsT; i++) {
			for (j = 0; j < nsT; j++) {
				coordN[indexN[i][j]][0] = (i + 1)*h;
				coordN[indexN[i][j]][1] = (j + 1)*h;
			}
		}

		indexB.resize(4, nsT);
		for (i = 0; i < nsT; i++) {
			indexB[0][i] = indexN[0][i];
			indexB[1][i] = indexN[nsT - 1][i];
			indexB[2][i] = indexN[i][0];
			indexB[3][i] = indexN[i][nsT - 1];
		}

		boundary.resize(4, 2, 0.);
		boundary[0][0] = -h;
		boundary[1][0] = h;
		boundary[2][1] = -h;
		boundary[3][1] = h;


		// Update vF with f = -div (grad u)
		for (i = 0; i < npT; i++)
			vF[i] = h_2*f(coordN[i]);

		//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
		//�̢�				Boundary Process				 �̢�
		//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�


		for (j = 0; j < 4; j++) {
			for (i = 0; i < nsT; i++) {
				e = indexB[j][i];
				realP.copy(coordN[e]);
				realP.add(boundary[j]);
				vF[e] += u(realP);
			}
		}



		//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
		//�̢�		 	Conjugate Gradient					 �̢�
		//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�

		Solver::CG(mA, vX, vF, 1e-16, false);

		//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
		//�̢�				Error					         �̢�
		//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�


		vExact.resize(npT);
		for (i = 0; i < npT; i++)
			vExact[i] = u(coordN[i]);

		l2_error = Norms::L2(vX, vExact)*h;
		max_error = Norms::L_inf(vX, vExact);







	}

	static void MAIN() {
		FVector<double> interval({ 0.,1. });
		FVector<int> orders({ 2,3,4,5, 6 });
		FVector<double> l2_errors(orders._size), max_errors(orders._size);
		FVector<double> l2_order(orders._size - 1), max_order(orders._size - 1);

		int i, j, order;

		cout << endl;
		cout << " =============================================" << endl;
		cout << " Problem 3 : Finite Difference Method " << endl;
		cout << " =============================================" << endl;
		cout << " =========================================" << endl;
		cout << " Example 1 : no boundary process " << endl;
		cout << " u(x,y) = x(1-x)y(1-y)" << endl;
		for (i = 0; i < orders._size; i++) {
			order = orders[i];
			cout << " Order     : " << order << endl;

			//cout << order <<" check" << endl;
			FDM_Dirichlet(u1, f1, interval, order, l2_errors[i], max_errors[i]);


			//cout << " Estimate :"; sol.print();
			//cout << " Exact sol:"; exact_sol.print();
			cout << " L2 error  : " << l2_errors[i] << endl;
			cout << " Max error : " << max_errors[i] << endl;
			cout << " =========================================" << endl;
		}

		for (i = 0; i < orders._size - 1; i++) {
			l2_order[i] = log(l2_errors[i] / l2_errors[i + 1]) / log(2);
			max_order[i] = log(max_errors[i] / max_errors[i + 1]) / log(2);
		}

		cout << " Convergence order(L2 error)  : ";
		for (i = 0; i < l2_order._size; i++)
			cout << l2_order[i] << " ";
		cout << endl;

		cout << " Convergence order(max error) : ";
		for (i = 0; i < max_order._size; i++)
			cout << max_order[i] << " ";
		cout << endl;
		cout << " =========================================" << endl << endl;

		cout << " =========================================" << endl;
		cout << " Example 2 : boundary process " << endl;
		cout << " u(x,y) = (5x+y)exp(x+2y)" << endl;
		for (i = 0; i < orders._size; i++) {
			order = orders[i];
			cout << " Order     : " << order << endl;

			//cout << order <<" check" << endl;
			FDM_Dirichlet(u2, f2, interval, order, l2_errors[i], max_errors[i]);


			//cout << " Estimate :"; sol.print();
			//cout << " Exact sol:"; exact_sol.print();
			cout << " L2 error  : " << l2_errors[i] << endl;
			cout << " Max error : " << max_errors[i] << endl;
			cout << " =========================================" << endl;
		}

		for (i = 0; i < orders._size - 1; i++) {
			l2_order[i] = log(l2_errors[i] / l2_errors[i + 1]) / log(2);
			max_order[i] = log(max_errors[i] / max_errors[i + 1]) / log(2);
		}

		cout << " Convergence order(L2 error)  : ";
		for (i = 0; i < l2_order._size; i++)
			cout << l2_order[i] << " ";
		cout << endl;

		cout << " Convergence order(max error) : ";
		for (i = 0; i < max_order._size; i++)
			cout << max_order[i] << " ";
		cout << endl;
		cout << " =========================================" << endl << endl;

	}


};

class FinalProject4_5_6_7 {
private:
private:
	static int sgn(double x) {
		if (x >= 0)
			return 1;
		else 
			return -1;
		
	}
public:
	static void make_Stiffeness(FMatrix<double> &mA, int order, bool h_term = true) {
		// order : the number of unknowns in one-side
		//  => mA : (order*order) by (order*order) matrix

		mA.resize(order*order, order*order, 0);


		int i, j, e, m;
		double mult;
		if (h_term) {
			mult = pow(order + 1, 2);
		}
		else {
			mult = 1.;
		}


		// 1st diagonal submatrix B
		e = 0;
		mA[e + 0][e + 0] = 4.*mult;
		for (i = 1; i < order; i++) {
			mA[e + i][e + i] = 4.*mult;
			mA[e + i - 1][e + i] = -1.*mult;
			mA[e + i][e + i - 1] = -1.*mult;
		}



		for (i = 1; i < order; i++) {
			e = order*i;
			// i-th diagonal submatrix B
			mA[e + 0][e + 0] = 4.*mult;
			for (j = 1; j < order; j++) {
				mA[e + j][e + j] = 4.*mult;
				mA[e + j - 1][e + j] = -1.*mult;
				mA[e + j][e + j - 1] = -1.*mult;
			}

			// upper and left part of i-th diagonal submatrix B
			m = order*(i - 1);
			for (j = 0; j < order; j++) {
				//upper 
				mA[m + j][e + j] = -1.*mult;
				//left
				mA[e + j][m + j] = -1.*mult;
			}


		}
	}

	
	static void showALLeigenvalues() {
		int n = 15;
		double h = 1. / (n + 1);
		double h_inv = 1 / h;
		

		int i, j;

		
		FMatrix<double> mA, eigen;
		eigen.resize(n, n);
		make_Stiffeness(mA, n, true);
		
		
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				eigen[i][j] = 4 * pow(h_inv, 2)*(pow(sin((i + 1)*h*M_PI / 2.), 2) + pow(sin((j+1)*h*M_PI / 2.), 2));
			}
		}

		cout << endl;
		cout << " All eigenvalues : " << endl;
		eigen.print(1);
		cout << endl;
	}



	static void Problem4(bool verbose = true) {
		// Use MGS
		// Problem setting
		const int order = 16;
		const int n = (order - 1) * (order - 1);
		const int p = 10;
		const int max_loop = 10000;
		const double epsil = 1e-10;



		int i, j, k, loop;

		FMatrix<double> A, X, next_X, Q, R;
		FVector<double> eigens;
		double diff_norm, norm, relative_error;

		clock_t start, end;
		double duration;

		eigens.resize(p, 0);
		//Set A and the initial X=X_0
		make_Stiffeness(A, order - 1, true);

		X.resize(n, p, 0);
		for (i = 0; i < p; i++)
			X[i][i] = 1.;


		loop = 0;


		start = clock();
		while (loop < max_loop) {
			loop++;
			//cout << loop << endl;
			// X = QR
			QR_Decomposition::MGS(X, Q, R);


			// Check the stopping criteria
			norm = 0.;
			diff_norm = 0.;
			for (i = 0; i < p; i++) {
				norm += abs(R[i][i]);
				diff_norm += abs(eigens[i] - R[i][i]);
			}
			relative_error = diff_norm / norm;

			if (relative_error < epsil)
				break;


			// X <- AQ where Q are reduced forms
			// i.e X: (n,p), A : (n, n) Q: (n, p) 
			for (i = 0; i < n; i++) {
				for (j = 0; j < p; j++) {

					X[i][j] = 0.;
					for (k = 0; k < n; k++) {
						X[i][j] += A[i][k] * Q[k][j];
					}

				}
			}


			// Save the eigenvalues
			for (i = 0; i < p; i++) {
				eigens[i] = R[i][i];
			}

			if (verbose && (loop % 100 == 0)) {
				cout << " Loop : " << loop << endl;
				cout << " Diff : " << relative_error << endl;
				eigens.print();
			}
		}
		end = clock();
		duration = (end - start) / CLOCKS_PER_SEC;

		cout << endl;
		cout << " =========================================" << endl;
		cout << " Problem 4 : Orthogonal Iteration " << endl;
		cout << " Total Iteration : " << loop << endl;
		cout << " Duration(s) : " << duration << endl;
		cout << " Eigenvalues : " << endl; eigens.print();
		cout << " =========================================" << endl << endl;
	}

	static void Problem5(double shifting=50, bool verbose = true) {
		// Use MGS
		// Problem setting
		const int order = 16;
		const int n = (order - 1) * (order - 1);
		const int p = 10;
		const int max_loop = 10000;
		const double epsil = 1e-10;
		double shift = shifting;
		

		int i, j, k, loop;

		FMatrix<double> A, X, next_X, Q, R;
		FVector<double> eigens;
		double diff_norm, norm, relative_error;

		clock_t start, end;
		double duration;

		eigens.resize(p, 0);
		//Set A and the initial X=X_0
		make_Stiffeness(A, order - 1, true);

		X.resize(n, p, 0);
		for (i = 0; i < p; i++)
			X[i][i] = 1.;


		loop = 0;


		start = clock();
		while (loop < max_loop) {
			loop++;
			//cout << loop << endl;
			// X = QR
			QR_Decomposition::MGS(X, Q, R);


			// Check the stopping criteria
			norm = 0.;
			diff_norm = 0.;
			for (i = 0; i < p; i++) {
				norm += abs(R[i][i]);
				diff_norm += abs(eigens[i] - R[i][i]);
			}
			relative_error = diff_norm / norm;

			if (relative_error < epsil)
				break;


			// X <- (A-shift*I)Q where Q are reduced forms
			// X <- AQ - shift*Q
			// i.e X: (n,p), A : (n, n) Q: (n, p) 

			for (i = 0; i < n; i++) {
				for (j = 0; j < p; j++) {

					X[i][j] = 0.;
					for (k = 0; k < n; k++) {
						X[i][j] += A[i][k] * Q[k][j];
					}
					X[i][j] -= shift*Q[i][j];
				}
			}


			// Save the eigenvalues
			for (i = 0; i < p; i++) {
				eigens[i] = R[i][i];
			}

			if (verbose && (loop % 100 == 0)) {
				cout << " Loop : " << loop << endl;
				cout << " Diff : " << relative_error << endl;
				eigens.print();
			}
		}
		end = clock();
		duration = (end - start) / CLOCKS_PER_SEC;

		cout << endl;

		//Shift
		for (i = 0; i < p; i++) {
			eigens[i] += shift;
		}

		cout << " =========================================" << endl;
		cout << " Problem 5 : Orthogonal Iteration(shift=50)" << endl;
		cout << " Total Iteration : " << loop << endl;
		cout << " Duration(s) : " << duration << endl;
		cout << " Eigenvalues : " << endl; eigens.print();
		cout << " =========================================" << endl << endl;
	}

	static void Problem6() {

		int num_show = 5;

		FMatrix<double> mA;
		int order = 15;
		int i, j;

		cout << endl;
		cout << " =========================================" << endl;
		cout << " Problem 6 : Tridiagnoalization of A " << endl;

		make_Stiffeness(mA, order);
		HouseholderTransformation::Tridiagonalization(mA);
		for (int i = 0; i < num_show; i++) {
			cout << " ";
			for (int j = 0; j < num_show; j++) {
				//cout << mA[i][j] << " ";
				printf("%9.3f ", mA[i][j]);
			}
			cout << endl;
		}
		cout << " =========================================" << endl;
		cout << endl;
	}

	static void Problem7(bool verbose=true) {
		const int order = 16;
		const int n = order - 1;
		const double epsil = 1e-16;

		FMatrix<double> A;
		vector<double> eigens;

		clock_t start, end;
		double duration;




		make_Stiffeness(A, n, true);
		
		HouseholderTransformation::Tridiagonalization(A);

		cout << "Tridiagonalization success" << endl;
	

		int size = A._row;
		int i, j, k, loop;
		int min_, max_;

		double alpha, beta, gamma, shift,d;
		FVector<double> w(2), u(size),v(size);
		FMatrix<double> Q(size, 2);
		int num;


		eigens.resize(size, 0);

		num = size - 1;
		loop = 0;


		start = clock();
		while (num > 0) {
			loop++;
			// Case : There are only 2 eigens to find
			// eigenvalues of the submatrix are the eigenvalues of A
			// since A[2:size-1][2:size-1] is upper triangular
			if (num == 1) {
				eigens[0] = 0.5*(A[0][0] + A[1][1] + sqrt(pow(A[0][0] - A[1][1], 2) + 4 * A[0][1] * A[0][1]));
				eigens[1] = 0.5*(A[0][0] + A[1][1] - sqrt(pow(A[0][0] - A[1][1], 2) + 4 * A[0][1] * A[0][1]));

			
				if (verbose) {
					cout << " num : 1  eigen : " << eigens[1] << endl;
					cout << " num : 0  eigen : " << eigens[0] << endl;
				}

				break;
			}

			

			//Householder QR
			shift = A[num][num];
			for (i =0; i <=num ; i++)
				A[i][i] -= shift;

			// QR-decomposition
			for (k = 0; k < num; k++) {
				// alpha : -sgn(A[k][k])*l2_norm(A[k][k]~A[num-1][k])
				alpha = pow(A[k][k], 2) + pow(A[k + 1][k], 2);
				alpha = -sgn(A[k][k])*sqrt(alpha);

				w[0] = A[k][k] - alpha;
				beta = w[0] * w[0];
				w[1] = A[k + 1][k];
				beta += w[1] * w[1];

				Q[k][0] = w[0];
				Q[k][1] = w[1];

				if (beta == 0)
					continue;

				// A = (I-2ww*)A = A - 2ww*A where w is already normalized
				//  => we have to divide beta=(w,w)
				// A_j = A_j - 2ww*A_j = A_j - 2(w,A_j)w = A_j - 2gamma*w
				// A_j = A_j - 2*gamma/beta*w
				// A_j = A_j - 2*(w, A_j)/(w,w)w

				// gamma = (w, A_j)
				// w[k]*A[k][j] + w[k+1]A[k+1][j]
				// j = k, k+1, k+2

				max_ = min(num, k + 2);
				for (j = k; j <= max_; j++) {
					gamma = A[k][j] * w[0] + A[k+1][j] * w[1];
					A[k][j] -= 2 * gamma / beta*w[0];
					A[k+1][j] -= 2 * gamma / beta*w[1];
				}

				
			}
			
			// A <- QR 
			for (k = 0; k < num; k++) {
			
				w[0] = Q[k][0];
				w[1] = Q[k][1];
				beta = w[0] * w[0] + w[1]*w[1];

				// A = A(I-2ww*) = A - 2Aww*
				// A_j = A_j - 2*(A_j, w)w*    where A_j : j-th row
				// A_j = A_j - 2*(A_j, w)/(w,w) w*

				// gamma = (A_j, w)
				// w[k]*A[j][k] + w[k+1]*A[j][k+1]
				
				min_ = max(0, k - 2);
				max_ = min(num, k + 2);
				//min_ = 0; max_ = num;
				for (j = min_; j <=max_; j++) {
					gamma = A[j][k] * w[0] + A[j][k + 1] * w[1];
					A[j][k] -= 2 * gamma / beta*w[0];
					A[j][k + 1] -= 2 * gamma / beta*w[1];
				}
			}

			

			for (i = 0; i <=num; i++)
				A[i][i] += shift;

			

			if (verbose && (loop % 1000 == 0)) {
				cout << " Loop : " << loop << endl;
				cout << " num : " << num << endl;
				cout << " A[num][num-1] : " << A[num][num - 1] << endl;
				
			}

			

			if (abs(A[num][num - 1]) < epsil*A[num][num] ) {
				eigens[num] = A[num][num];
				cout << " num : " << num << "  eigen : " << eigens[num] << endl;
				num--;
			}
		}

		end = clock();
		duration = (end - start) / CLOCKS_PER_SEC;

		cout << endl;
		sort(eigens.begin(), eigens.end());

		cout << " =========================================" << endl;
		cout << " Problem 7 : QR Iteration" << endl;
		cout << " Total Iteration : " << loop << endl;
		cout << " Duration(s) : " << duration << endl;
		cout << " Eigenvalues(smallest) : " ; 
		for (i = 0; i < 10; i++)
			cout << eigens[i] << " ";
		cout << endl;
		cout << " =========================================" << endl << endl;
		
	}
public:
	static void MAIN() {
		showALLeigenvalues();
		Problem4(false);
		Problem5(50, false);
		Problem6();
		Problem7(false);
	}
};



class Multiplication_Execution {
private:
	static void operation_time1() {
		FMatrix<double> A, B, C;
		int size = 225;
		A.resize(size, size, 1);
		B.resize(size, size, 1);
		C.resize(size, size, 0);

		int loop = 100;

		time_t start, end;
		double duration;

		int l = 0;
		int i, j, k;

		start = clock();
		for (l = 0; l < loop; l++) {

			for (i = 0; i < size; i++) {
				for (j = 0; j < size; j++) {
					C[i][j] = 0.;

					for (k = 0; k < size; k++) {
						C[i][j] += A[i][k] * B[k][j];
					}
				}
			}

		}
		end = clock();

		duration = (end - start) / CLOCKS_PER_SEC;

		cout << endl;
		cout << " =============================================" << endl;
		cout << " Use FMatrix class  " << endl;
		cout << " Matrix size : " << size << endl;
		cout << " Repeation number of multiplication : " << loop << endl;
		cout << " Duration(s) : " << duration << endl;
		cout << " =============================================" << endl;
		cout << endl;
	}

	static void operation_time2() {


		int size = 225;
		int loop = 100;

		time_t start, end;
		double duration;

		int l = 0;
		int i, j, k;

		double **A, **B, **C;
		for (i = 0; i < size; i++) {
			A = new double*[size];
			B = new double*[size];
			C = new double*[size];

			for (j = 0; j < size; j++) {
				A[j] = new double[size];
				B[j] = new double[size];
				C[j] = new double[size];
			}
		}

		for (i = 0; i < size; i++) {
			for (j = 0; j < size; j++) {
				A[i][j] = 1.;
				B[i][j] = 1.;
				C[i][j] = 0.;
			}
		}



		start = clock();
		for (l = 0; l < loop; l++) {

			for (i = 0; i < size; i++) {
				for (j = 0; j < size; j++) {
					C[i][j] = 0.;

					for (k = 0; k < size; k++) {
						C[i][j] += A[i][k] * B[k][j];
					}
				}
			}

		}
		end = clock();

		duration = (end - start) / CLOCKS_PER_SEC;

		cout << endl;
		cout << " =============================================" << endl;
		cout << " Dynamic memeory allocation " << endl;
		cout << " Matrix size : " << size << endl;
		cout << " Repeation number of multiplication : " << loop << endl;
		cout << " Duration(s) : " << duration << endl;
		cout << " =============================================" << endl;
		cout << endl;
	}
public:
	static void MAIN() {
		operation_time1();
		operation_time2();
	}
};





int main() {
	


	//FinalProject1::MAIN();
	//FinalProject2::MAIN();
	//FinalProject3::MAIN();
	//FinalProject4_5_6_7::MAIN();
	FinalProject4_5_6_7::Problem7();

	//Multiplication_Execution::MAIN();
	//FinalProject4_5_6_7::showALLeigenvalues();
	return 0;
}

 