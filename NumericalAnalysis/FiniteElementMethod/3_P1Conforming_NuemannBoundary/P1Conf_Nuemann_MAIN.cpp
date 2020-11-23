//2017 FEM Mid_term project(2)
//20173595 Choi Yoonjeong

#include "class17_.h"


//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
//�̢�					 Problem								      �̢�
//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�

// - div (p grad u) = f


//Problem (6)
double p(FVector_double &p)
{
	double x = p[0];	double y = p[1];
	return 1+x+2*y*y ;
}

double u(FVector_double &p,double alpha)
{
	double x = p[0];	double y = p[1];
	return pow(x*x+y*y,alpha/2);
}

double g(FVector_double &p,double alpha)
{
	double x = p[0];	double y = p[1];
	return pow(x*x + y*y, alpha / 2);
}

double ux(FVector_double &p, double alpha)
{
	double x = p[0];	double y = p[1];
	return alpha*x*pow(x*x + y*y, alpha / 2 - 1);
}

double uy(FVector_double &p, double alpha)
{
	double x = p[0];	double y = p[1];
	return alpha*y*pow(x*x + y*y, alpha / 2 - 1);
}

double F(FVector_double &p,double alpha)
{
	double x = p[0]; double y = p[1];
	double f = -(alpha*pow(x*x + y*y, alpha / 2 - 1) + alpha*(alpha - 2)*(x*x)*pow(x*x + y*y, alpha / 2 - 2));
	//f -= (alpha*pow(x*x + y*y, alpha / 2 - 1) + alpha*(alpha - 2)*(y*y)*pow(x*x + y*y, alpha / 2 - 2));
	f = -pow(alpha, 2)*pow(pow(x, 2) + pow(y, 2), alpha / 2. - 1)*(1 + x + 2 * y*y) - (x + 4 * y*y)*alpha*pow(pow(x, 2) + pow(y, 2), alpha / 2. - 1);
	return f;
}



double FEM_Problem6(double alpha, int lev);



//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
//�̢�			 Basic Functions								      �̢�
//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
void Make_realP_and_DF(FVector_double & vRealP, FMatrix_double & DF, FMatrix_double & coordN, FVector_double& psi, FVector_int & index)
// For each element, find centroid vRealP and mapping DF
{
	int i;
	vRealP.clear();

	for (i = 0; i<3; i++) {

		vRealP[0] = vRealP[0] + psi[i] * coordN[index[i]][0];
		vRealP[1] = vRealP[1] + psi[i] * coordN[index[i]][1];

	}


	DF.clear();															// DF = B
	DF[0][0] = coordN[index[1]][0] - coordN[index[0]][0];
	DF[1][0] = coordN[index[1]][1] - coordN[index[0]][1];
	DF[0][1] = coordN[index[2]][0] - coordN[index[0]][0];
	DF[1][1] = coordN[index[2]][1] - coordN[index[0]][1];

}

double inverse(FMatrix_double & DF, FMatrix_double & DFIT) {				// 2 by 2 matrix inverse. Return determinent
	double det;
	det = DF[0][0] * DF[1][1] - DF[1][0] * DF[0][1];
	DFIT[0][0] = DF[1][1] / det;
	DFIT[1][0] = -DF[1][0] / det;
	DFIT[0][1] = -DF[0][1] / det;
	DFIT[1][1] = DF[0][0] / det;

	return det;
}

void transpose(FMatrix_double & A) {										// 2 by 2 matrix transpose
	double temp;
	temp = A[1][0];
	A[1][0] = A[0][1];
	A[0][1] = temp;
}

void	CG(FMatrix_double& A, FVector_double& x, FVector_double& b, double epsilon) {				// conjugate gradient method

	int i, j = 0;
	int size = b._size;
	double c, t, d;
	FVector_double Ax(size), v(size), Av(size), r(size);

	if (size != b._size) {						// Efficient Form on Reiteration 
		size = b._size;
		Ax.make(size);	v.make(size);	Av.make(size);	r.make(size);	// Memory Allocation
	}

	Ax.op("=", A, x);							// Ax = A*x;
	for (i = 0; i<size; i++) {
		r[i] = b[i] - Ax[i];					// r = b - Ax;
	}

	v = r;
	c = (r, r);

	if (sqrt(c) < epsilon) return;

	for (j = 1;; j++) {
		Av.op("=", A, v);						// Av = A*v;
		t = c / (v, Av);
		for (i = 0; i<size; i++) {
			x._vec[i] += t*v._vec[i];
			r._vec[i] -= t*Av._vec[i];
		}
		d = (r, r);
		if (sqrt(d) < epsilon) break;
		for (i = 0; i<size; i++) {					// v = r + (d/c)*v;
			v[i] = r[i] + (d / c)*v[i];
		}

		c = d;

	}

}

int main()
{
	int choice;
	cout << "1.gamma=positive intger		2.gamma >= 2	3.gamma <2 :";
	cin >> choice;
	if (choice == 1)
	{
		double int_al[5] = { 2.0, 3.0, 4.0, 5.0, 6.0 };
		double int_error[5][5];
		double int_order[5][4];

		// Error
		for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			int_error[i][j] = FEM_Problem6(int_al[i], j + 2);
		//convergence order
		for (int i = 0; i < 5; i++)
		for (int j = 0; j < 4; j++)
			int_order[i][j] = log(int_error[i][j] / int_error[i][j + 1]) / log(2);



		for (int j = 0; j < 5; j++)
		{
			cout << "--------gamma = " << int_al[j] << "--------" << endl;
			cout << "<Error>" << endl;
			for (int i = 0; i < 5; i++)
			{
				cout << "level = " << i + 2 << " : " << int_error[j][i] << endl;
			}
			cout << "convergence order : ";
			for (int i = 0; i < 4; i++)
			{
				cout << " " << int_order[j][i] << " ";
			}

			cout << endl << endl;
		}
	}
	else if (choice == 2)
	{
		double al[5] = { 2.3, 3.4, 2.5, 2.8, 3.7 };
		double error1[5][5];
		double order1[5][4];

		// Error
		for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			error1[i][j] = FEM_Problem6(al[i], j + 2);
		//convergence order
		for (int i = 0; i < 5; i++)
		for (int j = 0; j < 4; j++)
			order1[i][j] = log(error1[i][j] / error1[i][j + 1]) / log(2);



		for (int j = 0; j < 5; j++)
		{
			cout << "--------gamma = " << al[j] << "--------" << endl;
			cout << "<Error>" << endl;
			for (int i = 0; i < 5; i++)
			{
				cout << "level = " << i + 2 << " : " << error1[j][i] << endl;
			}
			cout << "convergence order : ";
			for (int i = 0; i < 4; i++)
			{
				cout << " " << order1[j][i] << " ";
			}

			cout << endl << endl;
		}
	}
	else if (choice == 3)
	{
		double alpha[19];
		for (int i = 0; i < 19; i++)
			alpha[i] = (i + 1)*0.1;
		double error[19][5];
		double order[19][4];
		// Error
		for (int i = 0; i < 19; i++)
		for (int j = 0; j < 5; j++)
			error[i][j] = FEM_Problem6(alpha[i], j + 2);
		//convergence order
		for (int i = 0; i < 19; i++)
		for (int j = 0; j < 4; j++)
			order[i][j] = log(error[i][j] / error[i][j + 1]) / log(2);

		for (int j = 0; j < 19; j++)
		{
			cout << "--------gamma = " << alpha[j] << "--------" << endl;
			cout << "<Error>" << endl;
			for (int i = 0; i < 5; i++)
			{
				cout << "level = " << i + 2 << " : " << error[j][i] << endl;
			}
			cout << "convergence order : ";
			for (int i = 0; i < 4; i++)
			{
				cout << " " << order[j][i] << " ";
			}

			cout << endl << endl;
		}

		double X[19];
		for (int i = 0; i < 19; i++)
			X[i] = 0.1*(i + 1);
		double Y[100];
		for (int i = 0; i < 19; i++)
			Y[i] = order[i][3];
		FILE *fp = fopen("convergence_order.m", "w");
		fprintf(fp, "X = [");

		for (int i = 0; i < 19; i++)
			fprintf(fp, "%f,", X[i]);

		fprintf(fp, "]\n");
		fprintf(fp, "Y = [");
		for (int i = 0; i < 19; i++)
			fprintf(fp, "%f,", Y[i]);
		fprintf(fp, "]\n");
		fprintf(fp, "plot(X,Y,'-ok')\n");
		fprintf(fp, "xlabel('gamma')\n");
		fprintf(fp, "ylabel('convergence order')\n");
		fprintf(fp, "grid\n");
		fclose(fp);
	}
	else
		cout << "Unvalid Choice" << endl;

	int test;
	cout << "test"; cin >> test;
	return 0;
}

double FEM_Problem6(double alpha, int lev)
{
	// - div (p grad u) = f

	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	//�̢�	             Set number of meshrefinement					  �̢�
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�

	int level = lev;
	double a = alpha;

	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	//�̢�					Some Common Variables					      �̢�
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�

	int i, j, e, k, node;				// Common variables

	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	//�̢�					Mesh Generation	(Triangular Mesh)   		    �̢�
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	// Generate uniform grid with K by K element
	double ax, bx, ay, by;
	ax = -1; bx = 1; ay = -1; by = 1;

	// Declation
	int nsN;						// Number of side node
	double h;						// Meshsize in case of regtangular domain
	int neT;						// Number of element total
	int nnT;						// Number of node total  (not used in this code)
	int nsR;						// Number of side rectangular
	int nsE;						// Number of element total (not used in this code)
	double dx;						// Meshsize x direction  (not used in this code)
	double dy;						// Meshsize y direction	 (not used in this code)
	int npT;						// Number of unknown total
	int nbT_d;						// Number of Dirichlet boundary node total
	int nbT_n;						// Number of Neumann boundary node total


	FMatrix_double coordN;			// Coordinate ( coordN[global node][x-coord][y-coord]  ) 	

	// Definition

	nsN = 1;
	for (int i = 0; i<level; i++)
	{
		nsN = nsN * 2;
	}
	nsN = nsN + 1;
	nsR = nsN - 1;

	h = 2.;
	for (int i = 0; i<level; i++)
	{
		h = h / 2;
	}


	neT = (nsN - 1)*(nsN - 1) * 3 / 4 * 2;		//nsR*nsR*2 *(3/4)
	npT = nsN*nsN;
	npT -= (nsR / 2)*(nsR / 2);
	nbT_n = nsN - 2;
	nbT_d = (nsN - 1) * 4 - nbT_n;


	coordN.make(npT, 2);										// lexicograhic order from bottom to top
	for (int i = 0; i < nsN*(nsR / 2 + 1); i++)
	{
		coordN[i][0] = ax + (i % nsN)*h;
		coordN[i][1] = ay + (i / nsN)*h;
	}
	for (int i = nsN*(nsR / 2 + 1); i < npT; i++)
	{
		coordN[i][0] = ax + (i - nsN*(nsR / 2 + 1)) % (nsR / 2 + 1)*h;
		coordN[i][1] = h + (i - nsN*(nsR / 2 + 1)) / (nsR / 2 + 1)*h;
	}

	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	//�̢�						 Index Set Generation 	             	  �̢�
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�

	// Declation

	FMatrix_int indexP;				// Index from local number to global number
	FMatrix_int indexB_d;			// Dirichlet Boundary Node Information
	FMatrix_int indexB_n;			// Neumann Boundary Node Information


	// Definition
	indexP.make(neT, 3);					// indexP[of element][of local element] = global numbering
	indexB_d.make(nbT_d, 2);				// indexB_d[of nodes on boundary][0] = element, [1] = local numbering 
	indexB_n.make(nbT_n, 2);

	//indexP
	for (int i = 0; i < (neT * 2) / 3 + nsR; i++)
	{
		int row; int col;
		col = i / (2 * nsR); row = i % (2 * nsR);
		if (row % 2 == 0)
		{
			indexP[i][0] = col*nsN + row / 2;
			indexP[i][1] = indexP[i][0] + 1;
			indexP[i][2] = indexP[i][0] + nsN;
		}
		else
		{
			indexP[i][1] = (col + 1)*nsN + row / 2;
			indexP[i][0] = indexP[i][1] + 1;
			indexP[i][2] = indexP[i][0] - nsN;
		}
	}

	for (int i = neT * 2 / 3 + nsR; i < neT; i++)
	{
		int row; int col;
		col = (i - (neT * 2 / 3 + nsR)) / nsR; row = (i - (neT * 2 / 3 + nsR)) % nsR;	//nsR=(2*nsR)/2

		if (row % 2 == 0)
		{
			indexP[i][0] = nsN*(nsN / 2 + 1) + col*(nsR / 2 + 1) + row / 2;
			indexP[i][1] = indexP[i][0] + 1;
			indexP[i][2] = indexP[i][0] + (nsR / 2 + 1);
		}
		else
		{
			indexP[i][1] = nsN*(nsN / 2 + 1) + (col + 1)*(nsR / 2 + 1) + row / 2;
			indexP[i][0] = indexP[i][1] + 1;
			indexP[i][2] = indexP[i][0] - (nsR / 2 + 1);
		}

	}

	//indexB_d
	for (int i = 0; i < nsN / 2; i++)
	{
		//right : index starts 0
		indexB_d[i][0] = (2 * nsR - 1) + i*(2 * nsR);
		indexB_d[i][1] = 0;
		//upper : index starts nsN/2
		indexB_d[nsN / 2 + i][0] = (neT - 1) - 2 * i;
		indexB_d[nsN / 2 + i][1] = 0;
	}
	for (int i = 0; i < nsN - 1; i++)
	{
		//lower : index starts nsN-1
		indexB_d[nsN - 1 + i][0] = (2 * i + 1);
		indexB_d[nsN - 1 + i][1] = 2;
		//left : index starts 2nsN-2
		if (i < nsR / 2 + 1)
			indexB_d[2 * nsN - 2 + i][0] = i*(2 * nsR);
		else
			indexB_d[2 * nsN - 2 + i][0] = nsR*nsR + (i - nsR / 2)*nsR;

		indexB_d[2 * nsN - 2 + i][1] = 2;
	}
	indexB_d[3 * nsN - 3][0] = 0;
	indexB_d[3 * nsN - 3][1] = 0;

	//indexB_n
	//indexB_n[i] = (0,0) if i=0 , xaxis if i is even, yaxis if i is odd
	indexB_n[0][0] = (nsR*nsR + 1) + (nsR / 2 - 1) * 2;
	indexB_n[0][1] = 2;
	for (int i = 0; i < nbT_n / 2; i++)
	{
		indexB_n[1 + 2 * i][0] = indexB_n[0][0] + (i + 1)*nsR;
		indexB_n[1 + 2 * i][1] = 2;
		indexB_n[1 + 2 * i + 1][0] = indexB_n[0][0] - 2 * nsR + 2 * (i + 1);
		indexB_n[1 + 2 * i + 1][1] = 0;
	}
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	//�̢�					   Memory Allocation				    	  �̢�
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�

	// Declation 
	FMatrix_double mA;				// Matrix
	FVector_double vCP;				// Unknown( = uh)
	FVector_double vF;				// Load Vector
	FVector_double sol;				// Solution

	// Initialization
	mA.make(npT, npT);
	vCP.make(npT);
	vF.make(npT);
	sol.make(npT);

	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	//�̢�						Matrix Generation						  �̢�
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�

	// Declaration
	int pi, pj;						// indexP[e][i], indexP[e][j]
	double f = 0;					// Load Vector
	FVector_double pre_psi;			// Basis function value at mid point
	FMatrix_double pre_dpsi;		// Diffential basis function value at mid point
	FVector_double vRealP;			// Element MidPoint Coordinate
	FMatrix_double DF;				// Mapping
	FMatrix_double DFIT;			// Inverse and transpose of DF
	FVector_double v1;
	FVector_double v2;
	double det;						// Determinant
	double jacobian;				// Jacobian of integral
	double jacoweight;				// Jacobian * weight


	// 1. Set Prevalues								// pre_psi and pre_dpsi are calculated on reference trangle

	pre_psi.make(3);									// make(row size, column size) : specify the size of matrix and initialize
	pre_dpsi.make(3, 2);

	pre_psi[0] = 1. / 3;							// pre_psi[# of local index][basis values at coordinate of centroid on the reference triangle]
	pre_psi[1] = 1. / 3;
	pre_psi[2] = 1. / 3;

	pre_dpsi[0][0] = -1.;							// pre_psi[#of local index][differential of basis values at coordinate of centroid on the reference triangle]
	pre_dpsi[0][1] = -1.;
	pre_dpsi[1][0] = 1.;
	pre_dpsi[1][1] = 0.;
	pre_dpsi[2][0] = 0.;
	pre_dpsi[2][1] = 1.;

	vRealP.make(2);
	DF.make(2, 2);
	DFIT.make(2, 2);
	v1.make(2);
	v2.make(2);

	// 2. Make Matrix Part.	--- mA, vF

	for (int e = 0; e<neT; e++)
	{

		Make_realP_and_DF(vRealP, DF, coordN, pre_psi, indexP[e]);
		det = inverse(DF, DFIT);
		transpose(DFIT); jacobian = fabs(det); jacoweight = jacobian*(1 / 2.);
		for (int j = 0; j<3; j++)
		{
			pj = indexP[e][j];
			for (int i = 0; i<3; i++)
			{
				pi = indexP[e][i];
				// Fill-in here. "Multiply matrix DFIT and vector pre_dpsi[i]. Assign values to matrix mA. "
				v1[0] = (DFIT[0], pre_dpsi[j]);
				v1[1] = (DFIT[1], pre_dpsi[j]);
				v2[0] = (DFIT[0], pre_dpsi[i]);
				v2[1] = (DFIT[1], pre_dpsi[i]);
				mA[pi][pj] += p(vRealP)*(v1, v2)*jacoweight;
			}

			// Fill-in here. compute vF ;
			f = F(vRealP, a);
			vF[pj] += f*pre_psi[j] * jacoweight;
		}

	}


	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	//�̢�							Boundary Process					  �̢�
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�

	int ln;									// local number
	double mv, bv;							// mv = mA[][], bv = values on boundary

	FVector_double mid; mid.make(2);

	//Neumann Condition
	//At (0,0)
	ln = indexP[indexB_n[0][0]][indexB_n[0][1]];
	mid[0] = h / 2; mid[1] = 0;
	vF[ln] += h*p(mid)*uy(mid, a)*0.5;
	mid[0] = 0; mid[1] = h / 2;
	vF[ln] += h*p(mid)*ux(mid, a)*0.5;

	for (int j = 1; j < nbT_n; j++)
	{
		ln = indexP[indexB_n[j][0]][indexB_n[j][1]];
		if (j % 2 == 0)		//x-axis
		{
			mid[0] = coordN[ln][0] + h / 2; mid[1] = coordN[ln][1];
			vF[ln] += h*p(mid)*uy(mid, a)*0.5;
			mid[0] -= h;
			vF[ln] += h*p(mid)*uy(mid, a)*0.5;
		}
		//y-axis
		else
		{
			mid[0] = coordN[ln][0]; mid[1] = coordN[ln][1] + h / 2;
			vF[ln] += h*p(mid)*ux(mid, a)*0.5;
			mid[1] -= h;
			vF[ln] += h*p(mid)*ux(mid, a)*0.5;
		}
	}


	//Dirichlet Condition
	for (int j = 0; j < nbT_d; j++)
	{
		ln = indexP[indexB_d[j][0]][indexB_d[j][1]];
		bv = g(coordN[ln], a);
		for (int i = 0; i < npT; i++)
		{
			mv = mA[i][ln];
			vF[i] -= bv*mv;
			mA[i][ln] = 0;
			mA[ln][i] = 0;
		}
		vF[ln] = bv;
		mA[ln][ln] = 1;
	}



	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	//�̢�		 					Conjugate Gradient					  �̢�
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�

	CG(mA, vCP, vF, 1.0E-14);


	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	//�̢�								Error					          �̢�
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�

	//  

	double error = 0.;
	double cv = 0.;			// cv = u(centroid) - uh(centroid) 
	FVector_double cent;
	cent.make(2);			// coordinate of centroid

	for (int e = 0; e < neT; e++)
	{
		cent.clear();
		double uh_cent = 0;
		for (int i = 0; i < 3; i++)
		{
			uh_cent += vCP[indexP[e][i]] / 3;
			cent[0] += coordN[indexP[e][i]][0] / 3;
			cent[1] += coordN[indexP[e][i]][1] / 3;
		}
		cv += pow(u(cent, a) - uh_cent, 2);
	}
	error = cv*pow(h, 2);
	error = sqrt(error);

	return error;
}