#include "CGMethod.h""

double f(double x);
double u(double x);

//DIM=ÆÄÆ¼¼Ç °¹¼ö
double Dirichlet(double(*f)(double x), double(*u)(double x), int DIM);
double Mixed_Backward(double(*f)(double x), double(*u)(double x), int DIM);
double Mixed_Central(double(*f)(double x), double(*u)(double x), int DIM);


int main()
{
	int loop = 4;
	Vector err(loop);
	Vector order(loop - 1);
	int choice;
	cout << "Exericse 1.3.2" << endl;
	cout << "1.Dirichlet Problem" << endl << "2.Mixed with Backward" << endl << "3.Mixed with Central" << endl;
	cout << "My choice :"; cin >> choice;

	switch (choice)
	{
	case 1:
		cout << endl;
		cout << " Dirichlet Problem " << endl;
		for (int i = 0; i < loop; i++)
		{
			int n = pow(2, i) * 5;
			err[i] = Dirichlet(f, u, n);
			cout << " error : " << err[i] << " (n = " << n << ")" << endl;
		}

		for (int i = 0; i < loop - 1; i++)
			order[i] = log(err[i] / err[i + 1]) / log(2);

		//convergence order
		cout << " Convergence order : ";
		for (int i = 0; i < loop - 1; i++)
			cout << order[i] << " ";
		cout << endl;
		break;

	case 2:
		cout << endl;
		cout << " Mixed with Backward Difference" << endl;
		for (int i = 0; i < loop; i++)
		{
			int n = pow(2, i) * 5;
			err[i] = Mixed_Backward(f, u, n);
			cout << " error : " << err[i] << " (n = " << n << ")" << endl;
		}

		for (int i = 0; i < loop - 1; i++)
			order[i] = log(err[i] / err[i + 1]) / log(2);

		//convergence order
		cout << " Convergence order : ";
		for (int i = 0; i < loop - 1; i++)
			cout << order[i] << " ";
		cout << endl;
		break;

	case 3:
		cout << endl;
		cout << " Mixed with Central Difference" << endl;
		for (int i = 0; i < loop; i++)
		{
			int n = pow(2, i) * 5;
			err[i] = Mixed_Central(f, u, n);
			cout << " error : " << err[i] << " (n = " << n << ")" << endl;
		}

		for (int i = 0; i < loop - 1; i++)
			order[i] = log(err[i] / err[i + 1]) / log(2);

		//convergence order
		cout << " Convergence order : ";
		for (int i = 0; i < loop - 1; i++)
			cout << order[i] << " ";
		cout << endl;
		break;

	default:
		cout << " Choice is unavailable" << endl;
	}
	cout << endl;
	return 0;
}



double f(double x)
{
	return 2 - 6 * x;
}

double u(double x)
{
	return x - pow(x, 2) + pow(x, 3);
}

double Dirichlet(double(*f)(double x), double(*u)(double x), int DIM)
{
	int N = DIM-1;					// N = n-1
	double h = 1.0 / (DIM );		// h= mesh

	Matrix A(N, N);
	Vector x(N);						//solution
	Vector b(N);						//boundary 		

	Vector mesh(N);
	for (int i = 0; i < N; i++)
		mesh[i] = (i + 1)*h;

	// A is the matrix in the FDM sheme
	for (int i = 0; i < N - 1; i++)
	{
		A[i][i] = 2 / pow(h, 2);
		A[i][i + 1] = -1 / pow(h, 2);
		A[i + 1][i] = -1 / pow(h, 2);
	}
	A[N - 1][N - 1] = 2 / pow(h, 2);

	//[f1,......,f(N-1)]
	for (int i = 0; i < N; i++)
		b[i] = f(mesh[i]);

	//boundary condition
	b[0] += u(0) / pow(h, 2);
	b[N - 1] += u(1) / pow(h, 2);

	//Solve
	Con_Grad(A, b, x);

	//Find error
	double error = abs(x[0] - u(mesh[0]));

	for (int i = 1; i < N; i++)
	{
		if (error < abs(x[i] - u(mesh[i])))
			error = abs(x[i] - u(mesh[i]));
	}

	// Compare approximation values and real values
	/*
	Show(x);
	cout << "[ ";
	for (int i = 0; i < N; i++)
	cout << u(mesh[i]) << " ";
	cout << "]" << endl;
	cout << endl;
	*/

	return error;
}

double Mixed_Backward(double(*f)(double x), double(*u)(double x), int DIM)
{
	int N = DIM-1;				// N = n-1
	double h = 1.0 / (DIM );		// h= mesh
	Matrix A(N, N);
	Vector x(N);					//solution
	Vector b(N);					//boundary 		

	Vector mesh(N);
	for (int i = 0; i < N; i++)
		mesh[i] = (i + 1)*h;

	// A is the matrix in the FDM sheme
	for (int i = 0; i < N - 1; i++)
	{
		A[i][i] = 2 / pow(h, 2);
		A[i][i + 1] = -1 / pow(h, 2);
		A[i + 1][i] = -1 / pow(h, 2);
	}
	A[N - 1][N - 1] = 1 / pow(h, 2);

	//[f1,......,f(N-1)]
	for (int i = 0; i < N; i++)
		b[i] = f(mesh[i]);

	//boundary condition
	b[0] += u(0) / pow(h, 2);
	b[N - 1] += h * 2 / pow(h, 2);	//f'(1)=d=1

	//Solve
	Con_Grad(A, b, x);

	//Find error
	double error = abs(x[0] - u(mesh[0]));
	for (int i = 1; i < N; i++)
	{
		if (error < abs(x[i] - u(mesh[i])))
			error = abs(x[i] - u(mesh[i]));
	}


	// Compare approximation values and real values
	/*
	Show(x);
	cout << "[ ";
	for (int i = 0; i < N; i++)
	cout << u(mesh[i]) << " ";
	cout << "]" << endl;
	cout << endl;
	*/

	return error;
}

double Mixed_Central(double(*f)(double x), double(*u)(double x), int DIM)
{
	int N = DIM;				// N = n
	double h = 1.0 / (DIM);		// h= mesh
	Matrix A(N, N);
	Vector x(N);					//solution
	Vector b(N);					//boundary 		

	Vector mesh(N);
	for (int i = 0; i < N; i++)
		mesh[i] = (i + 1)*h;

	// A is the matrix in the FDM sheme
	for (int i = 0; i < N - 1; i++)
	{
		A[i][i] = 2 / pow(h, 2);
		A[i][i + 1] = -1 / pow(h, 2);
		A[i + 1][i] = -1 / pow(h, 2);
	}
	A[N - 1][N - 1] = 1 / pow(h, 2);

	//[f1,......,f(N-1)]
	for (int i = 0; i < N - 1; i++)
		b[i] = f(mesh[i]);
	b[N - 1] = f(mesh[N - 1]) / 2;

	//boundary condition
	b[0] += u(0) / pow(h, 2);
	b[N - 1] += h * 2 / pow(h, 2);		//f'(1)=d=2

	//Solve
	Con_Grad(A, b, x);

	//Find error(including boudary u(1))
	double error = abs(x[0] - u(mesh[0]));
	for (int i = 1; i < N; i++)
	{
	if (error < abs(x[i] - u(mesh[i])))
	error = abs(x[i] - u(mesh[i]));
	}

	//Find error(excluding boudary u(1))
	/*double error = abs(x[0] - u(mesh[0]));
	for (int i = 1; i < N - 1; i++)
	{
		if (error < abs(x[i] - u(mesh[i])))
			error = abs(x[i] - u(mesh[i]));
	}*/

	// Compare approximation values and real values
	/*
	Show(x);
	cout << "[ ";
	for (int i = 0; i < N; i++)
	cout << u(mesh[i]) << " ";
	cout << "]" << endl;
	cout << endl;
	*/

	return error;
}

