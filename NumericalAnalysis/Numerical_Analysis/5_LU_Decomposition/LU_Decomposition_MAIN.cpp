#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <typeinfo>


#include "Vector_Matrix.h"
using namespace std;

class LU_Decomposition {
private:
	static void Permutation(FVector<double>& b, FVector<int>& p) {
		FVector<double> temp(b);
		for (int i = 0; i < b._size; i++)
			b[i] = temp[p[i]];

		temp.clear();
		
	}

	
private: // Back and Forward Substitution
	// Solve Ax=b with backward i.e A : upper triangle
	static void BackwardSubstitution(FMatrix<double>& matrix , FVector<double>&x, FVector<double>& b ) {
		
		double sum;
		int i, j;
		int size = matrix._row;
		x.resize(size, 0);

		for (i = size - 1; i >= 0; i--) {
			sum = 0.;
			for (j = i + 1; j < size; j++) {
				sum += matrix[i][j] * x[j];
			}
			x[i] = (b[i] - sum) / matrix[i][i];
		}

	}
	// Solve AX=b with forward i.e A : lower triangle
	static void ForwardSubstitution(FMatrix<double>& matrix, FVector<double>&x, FVector<double>& b) {
		// Assumption : diagonal entries of A are 1.

		double sum;
		int i, j;
		int size = matrix._row;
		x.resize(size, 0);
		
		for (i = 0; i < size; i++) {
			sum = 0.;
			for (j = 0; j < i; j++) {
				sum += matrix[i][j] * x[j];
			}
			x[i] = (b[i] - sum);
		}

	}

	static void BackwardSubstitution(FMatrix<double>& matrix, FVector<double>&x, FVector<double>& b, FVector<int>& p) {
		double sum;
		int i, j;
		int size = matrix._row;
		x.resize(size, 0);

		for (i = size - 1; i >= 0; i--) {
			sum = 0.;
			for (j = i + 1; j < size; j++) {
				sum += matrix[p[i]][j] * x[p[j]];
			}
			x[p[i]] = (b[p[i]] - sum) / matrix[p[i]][i];
		}
	}
	
	static void ForwardSubstitution(FMatrix<double>& matrix, FVector<double>&x, FVector<double>& b, FVector<int>& p) {
		// Assumption : diagonal entries of A are 1.

		double sum;
		int i, j;
		int size = matrix._row;
		x.resize(size, 0);

		for (i = 0; i < size; i++) {
			sum = 0.;
			for (j = 0; j < i; j++) {
				sum += matrix[p[i]][j] * x[p[j]];
			}
			x[p[i]] = (b[p[i]] - sum);
		}
	}
public:	// LU decomposition
	static void LU(FMatrix<double>& matrix) {
		if (matrix._row != matrix._col) {
			cout << "LU_Decomposition - LU(matrix) : not square" << endl;
			exit(1);
		}

		int size = matrix._row;
		int i, j,k;

		for (j = 0; j < size-1; j++) {
			// Fix j-th column
			for (i = j+1; i < size; i++) {				
				// Find the component of L
				matrix[i][j] = matrix[i][j] / matrix[j][j];
				// Row operator : i-th row -= matrix[i][j]*j-th row
				//				: just consider k(>j)-th column of each row
				for (k = j+1; k < size; k++) {
					matrix[i][k] -= matrix[i][j] * matrix[j][k];
				}
			}
		}
	}

	static void LU(const FMatrix<double>& matrix, FMatrix<double>& lu) {
		if (matrix._row != matrix._col) {
			cout << "LU_Decomposition - LU(matrix, lu) : not square" << endl;
			exit(1);
		}

		lu.copy(matrix);

		LU(lu);
	}

	static void LU(const FMatrix<double>& matrix, FMatrix<double>& L, FMatrix<double>& U) {
		if (matrix._row != matrix._col) {
			cout << "LU_Decomposition - LU(matrix,l,u) : not square" << endl;
			exit(1);
		}

		int size = matrix._row;
		int i, j, k;

		L.resize(size, size, 0);
		U.copy(matrix);

		for (j = 0; j < size - 1; j++) {
			// Fix j-th column
			L[j][j] = 1.;
			for (i = j + 1; i < size; i++) {
				// Find the component of L
				L[i][j] = U[i][j] / U[j][j];
				// Row operator : i-th row -= matrix[i][j]*j-th row
				//				: just consider k(>j)-th column of each row
				for (k = j + 1; k < size; k++) {
					U[i][k] -= L[i][j] * U[j][k];
				}
				U[i][j] = 0.;
			}
		}
		L[size - 1][size - 1] = 1.;

	}

public: // LU decomposition with pivoting : PA = LU
	static void LU_pivot(FMatrix<double>& matrix, FVector<int>& permutation) {
		if (matrix._row != matrix._col) {
			cout << "LU_Decomposition - LU(matrix) : not square" << endl;
			exit(1);
		}

		int size = matrix._row;
		int i, j, k;
		int max_idx;

		permutation.resize(size, 0);
		for (i = 0; i < size; i++) {
			permutation[i] = i;
		}

		for (j = 0; j < size - 1; j++) {
			// Fix j-th column
			max_idx = j;

			// Find the max entries along 0~i-th rows
			for (i = j; i < size; i++) {
				if (abs(matrix[permutation[max_idx]][j] < abs(matrix[permutation[i]][j]))) {
					max_idx = i;
				}
			}
			permutation.swap(j, max_idx);

			for (i = j + 1; i < size; i++) {
				// Find the component of L
				matrix[permutation[i]][j] = matrix[permutation[i]][j] / matrix[permutation[j]][j];
				// Row operator : i-th row -= matrix[i][j]*j-th row
				//				: just consider k(>j)-th column of each row
				for (k = j + 1; k < size; k++) {
					//matrix[i][k] -= matrix[i][j] * matrix[j][k];
					matrix[permutation[i]][k] -= matrix[permutation[i]][j] * matrix[permutation[j]][k];
				}
			}
		}

	}

	static void LU_pivot(const FMatrix<double>& matrix, FMatrix<double>& lu, FVector<int>& permutation) {
		if (matrix._row != matrix._col) {
			cout << "LU_Decomposition - LU(matrix) : not square" << endl;
			exit(1);
		}

		lu.copy(matrix);
		LU_pivot(lu, permutation);

	}
	
	static void LU_pivot(const FMatrix<double>& matrix, FMatrix<double>& L, FMatrix<double>& U, FVector<int>& permutation) {
		if (matrix._row != matrix._col) {
			cout << "LU_Decomposition - LU(matrix) : not square" << endl;
			exit(1);
		}

		int size = matrix._row;
		int i, j, k;
		int max_idx;

		permutation.resize(size, 0);
		for (i = 0; i < size; i++) {
			permutation[i] = i;
		}

		L.resize(size, size, 0);
		U.copy(matrix);

		for (j = 0; j < size - 1; j++) {
			// Fix j-th column
			max_idx = j;

			// Find the max entries along 0~i-th rows
			for (i = j; i < size; i++) {
				if (abs(U[permutation[max_idx]][j] < abs(U[permutation[i]][j]))) {
					max_idx = i;
				}
			}
			permutation.swap(j, max_idx);

			L[permutation[j]][j] = 1.;

			for (i = j + 1; i < size; i++) {
				// Find the component of L
				L[permutation[i]][j] = U[permutation[i]][j] / U[permutation[j]][j];
				// Row operator : i-th row -= matrix[i][j]*j-th row
				//				: just consider k(>j)-th column of each row
				for (k = j + 1; k < size; k++) {
					//matrix[i][k] -= matrix[i][j] * matrix[j][k];
					U[permutation[i]][k] -= L[permutation[i]][j] * U[permutation[j]][k];
				}
				U[permutation[i]][j] = 0.;
			}
		}

		L[permutation[size - 1]][size - 1] = 1.;
	}

public: // GE-solver
	static void GE_Solver(FMatrix<double>& matrix, FVector<double>&x, FVector<double>& b, bool pivot=false, bool copy = false) {
		if (matrix._row != matrix._col) {
			cout << "LU_Decomposition - GE_Solver : not square" << endl;
			exit(1);
		}
		if (matrix._row != b._size) {
			cout << "LU_Decomposition - GE_Solver : b has wrong size" << endl;
			exit(1);
		}
		
		
		x.resize(b._size, 0);

		if (pivot == false) {
			if (copy == false) {
				LU(matrix);
				ForwardSubstitution(matrix, x, b);
				b.copy(x);
				BackwardSubstitution(matrix, x, b);
			}
			else {
				FMatrix<double> copyA;
				FVector<double> copyb(b);
				

				LU(matrix, copyA);
				
				ForwardSubstitution(copyA, x, copyb);
				copyb.copy(x);
				BackwardSubstitution(copyA, x, copyb);
				copyA.release();
				copyb.release();
			}
		}
		else {
			if (copy == false) {
				FVector<int> p;
				LU_pivot(matrix, p);

				ForwardSubstitution(matrix, x, b, p);
				b.copy(x);
				BackwardSubstitution(matrix, x, b, p);
				Permutation(x, p);
			}
			else {
				FVector<int> p;
				FMatrix<double> copyA;
				FVector<double> copy_b(b);

				LU_pivot(matrix, copyA, p);
				

				ForwardSubstitution(copyA, x, copy_b,p);
				copy_b.copy(x);
				BackwardSubstitution(copyA, x, copy_b,p);
				Permutation(x, p);
			}
		}
	}

public:	// Validation examples for the code
	static void validation_Example() {
		FMatrix<double> mat1({ { 2,1,1,0 },{ 4,3,3,1 },{ 8,8,9,5 },{ 6,7,9,8 } });
		FMatrix<double> mat2({ { 2,1,3,5 },{ 0,7,7,4 },{ -11,12,6,9 },{ 3,-3,6,-6 } });
		FVector<double> b2({ 48,111,156,-42 }), x2, ans_b2;
		FVector<double> b1({ 19,56,155,153 });
		// x2 = {3, 11, 2, 5}


		cout << "=============================================================" << endl;
		cout << "GE-Solver : not pivot " << endl;
		LU_Decomposition::GE_Solver(mat1, x2, b1, false, true);
		cout << "A :" << endl; mat1.print();
		cout << "b :" << endl; b1.print();
		cout << "x : " << endl; x2.print();
		ans_b2.mult(mat1, x2);
		cout << endl << "Vaidation : " << endl;
		if (b1.isSame(ans_b2))
			cout << "Valid GE-solver(not pivot)" << endl;
		cout << endl;

		x2.clear();

		cout << "GE-Solver : pivot " << endl;
		LU_Decomposition::GE_Solver(mat1, x2, b1, true, true);
		cout << "A :" << endl; mat1.print();
		cout << "b :" << endl; b1.print();
		cout << "x : " << endl; x2.print();
		ans_b2.mult(mat1, x2);
		cout << endl << "Vaidation : " << endl;
		if (b1.isSame(ans_b2))
			cout << "Valid GE-solver(pivot)" << endl;


		cout << endl << "======================================================" << endl;
		cout << "GE-Solver : not pivot " << endl;
		LU_Decomposition::GE_Solver(mat2, x2, b2, false, true);
		cout << "A :" << endl; mat2.print();
		cout << "b :" << endl; b2.print();
		cout << "x : " << endl; x2.print();
		ans_b2.mult(mat2, x2);
		cout << endl << "Vaidation : " << endl;
		if (b2.isSame(ans_b2))
			cout << "Valid GE-solver(not pivot)" << endl;
		cout << endl;

		x2.clear();

		cout << "GE-Solver : pivot " << endl;
		LU_Decomposition::GE_Solver(mat2, x2, b2, true, true);
		cout << "A :" << endl; mat2.print();
		cout << "b :" << endl; b2.print();
		cout << "x : " << endl; x2.print();
		ans_b2.mult(mat2, x2);
		cout << endl << "Vaidation : " << endl;
		if (b2.isSame(ans_b2))
			cout << "Valid GE-solver(pivot)" << endl;

	}
};



class Assignment5 {
private:
	static void make_Hilbert_matrix(FMatrix<double>& mA,FVector<double>& vf, int order) {
		
		mA.resize(order + 1, order + 1, 0);
		vf.resize(order + 1, 0);
		int i, j;
		double sum;
		for (i = 0; i < order + 1; i++) {
			sum = 0.;
			for (j = 0; j < order + 1; j++) {
				mA[i][j] = 1. / (i + j + 1);
				sum += 1. / (i + j + 1);
			}
			vf[i] = sum;
		}
	}

	static double u(double x) {
		return -pow(x, 4) / 12 + pow(x, 3) / 6 - x / 12;
	}

	static double f(double x) {
		return x*(x - 1);
	}

	static void Dirichlet(double(*f)(double x), double(*u)(double x), int order, double& l2_err, double& max_err) {
		int n = order - 1;
		double h = 1.0 / order;
		double square_h = pow(h, 2);

		FMatrix<double> mA(n,n,0);
		FVector<double> vF(n, 0),mesh(n,0), sol,exact_sol(n,0);

		int i;

		// mesh[i] = x_i = (i+1)*h
		for (i = 0; i < n; i++)
			mesh[i] = (i + 1)*h;

		// Calculate the exact solution
		for (i = 0; i < n; i++)
			exact_sol[i] = u(mesh[i]);

		// Make mA with FDM shceme
		for (i = 0; i < n-1; i++) {
			mA[i][i] = 2. / square_h;
			mA[i][i + 1] = -1. / square_h;
			mA[i + 1][i] = -1. / square_h;
		}
		mA[n - 1][n - 1] = 2. / square_h;

		// [f_1,.......,f_(n-1)]
		for (i = 0; i < n; i++)
			vF[i] = f(mesh[i]);

		// Boundary condition
		vF[0] += u(0) / square_h;
		vF[n - 1] += u(1) / square_h;

		// Solve the system with LU-pivoting
		LU_Decomposition::GE_Solver(mA, sol, vF, false, false);

		max_err = L_infinite_error(exact_sol, sol);
		l2_err = L_2_error(exact_sol, sol)*sqrt(h);

		
	}

	static double L_infinite_error(FVector<double>& real, FVector<double>& estimate) {
		int size = real._size;

		vector<double> errors(size);

		for (int i = 0; i < size; i++)
			errors[i] = abs(real[i] - estimate[i]);

		vector<double>::iterator max_itr;
		max_itr = max_element(errors.begin(), errors.end());

		double max_error = *max_itr;

		return max_error;
	}

	static double L_2_error(FVector<double>& real, FVector<double>& estimate) {
		int size = real._size;

		FVector<double> errors(size);

		for (int i = 0; i < size; i++)
			errors[i] = real[i] - estimate[i];

		
		double error;
		error = errors.norm_l2();
		

		return error;
	}
public:
	static void Exercise5_2_28_8() {
		FMatrix<double> mA;
		FVector<double> vF, sol, exact_sol;

		FVector<int> order_list({ 5,10,15,20,25 });

		int i, order;
		double error;

		cout << " Exercise5_2_28_8 : Hilbert matrix " << endl;

		for (i = 0; i < order_list._size; i++) {
			cout << " =========================================" << endl;
			cout << " Order : " << order_list[i] << endl;
			
			order = order_list[i];
			exact_sol.resize(order + 1, 1);
			make_Hilbert_matrix(mA, vF, order);

			cout << " 1. Without pivoting" << endl;
			LU_Decomposition::GE_Solver(mA, sol, vF, false, true);
			error = L_infinite_error(sol, exact_sol);
			//cout << " Solution without pivoting : " << endl;
			//sol.print();
			cout << " Error : " << error << endl;

			cout << endl << " 2. With pivoting" << endl;
			LU_Decomposition::GE_Solver(mA, sol, vF, true, true);
			error = L_infinite_error(sol, exact_sol);
			//cout << " Solution with pivoting : " << endl;
			//sol.print();
			cout << " Error : " << error << endl;
		}
		
	}

	static void Exercise5_2_28_9() {
		cout << " Exercise5_2_28_9 : Two point boundary value problem" << endl;

		FVector<int> order_list({ 5,10,20,40,80,160,320 });

		int i;
		FVector<double> errors_max(order_list._size), conv_orders(order_list._size-1);
		FVector<double> errors_l2(order_list._size), conv_orders_l2(order_list._size-1);
		for (i = 0; i < order_list._size; i++) {
			Dirichlet(f, u, order_list[i], errors_l2[i], errors_max[i]);
			//cout << order_list[i] << "-order : " << errors[i] << endl;
		}

		for (i = 0; i < conv_orders._size; i++) {
			conv_orders[i] = log(errors_max[i] / errors_max[i+1])/log(2);
			conv_orders_l2[i] = log(errors_l2[i] / errors_l2[i+1])/log(2);
		}

		cout << " =========================================" << endl;
		for (i = 0; i < order_list._size; i++) {
			cout << " Order : " << order_list[i] << endl;
			cout << " L2 error  : " << errors_l2[i] << endl;
			cout << " Max error : " << errors_max[i] << endl;
			cout << " =========================================" << endl;
		}

		cout << " Convergence order(L2 error)  : ";
		for (i = 0; i < conv_orders_l2._size; i++)
			cout << conv_orders_l2[i] << " ";
		cout << endl;

		cout << " Convergence order(max error) : " ; 
		for (i = 0; i < conv_orders._size; i++)
			cout << conv_orders[i] << " ";
		cout << endl;
	}

	static void MAIN() {
		Exercise5_2_28_8();
		cout << endl << endl;
		Exercise5_2_28_9();
		cout << endl;
	}


	
};

int main() {
	
	
	Assignment5::MAIN();
	return 0;
}

