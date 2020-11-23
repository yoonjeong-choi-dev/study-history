//2017 FEM P1_Discontinuous Galerkin Method (SIPG)
//20173595 Choi Yoonjeong

#include "t_sparse.h"
#include <cstdlib>


//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
//�̢�					 Problem					 �̢�
//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�

// - div (p grad u) = f



double u(FVector_double & p)											//exact solution
{
	double x = p[0];	double y = p[1];
	if (y >= 0)
		return exp(x + 2 * y) - exp(x);
	else
		return 0.01*(exp(x + 2 * y) - exp(x));
	
	
}

double p(FVector_double & p)
{
	double x = p[0];	double y = p[1];
	if (y >= 0)
		return 1;
	else
		return 100;

	//return 1;
}

double g(FVector_double &p)											// boundary condition 	
{
	double x = p[0];	double y = p[1];
	if (y >= 0)
		return exp(x + 2 * y) - exp(x);
	else
		return 0.01*(exp(x + 2 * y) - exp(x));
	
	//return exp(x + 2 * y)-exp(x);
}
double F(FVector_double& p)
{
	double x = p[0];	double y = p[1];
	
	return -5*exp(x + 2 * y) + exp(x);
		
}



//choice =1 : save solution as ch.m file
double DG_SIPG(double(*u)(FVector_double &p), double(*p)(FVector_double &p), double(*g)(FVector_double& p), double(*F)(FVector_double &p), FMatrix_double& domain, int lev, int choice, char *ch);


//void	DDu			(FVector_double& p, FMatrix_double& mDDP) {

//}

//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
//�̢�			 Basic Functions				     �̢�
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

void IMatrix_multiple(IMatrix_double &A, FVector_double &x, FVector_double &b)	//Ax=b
{
	if (A._col != x._size)
	{
		cout << "IMatrix_multiple : A*x is not well_defined" << endl;
		exit(-1);
	}
	b.make(A._row);

	for (int i = 0; i < A._row; i++)
	{
		b._vec[i] = (A[i], x);
	}
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
		if (j % 100 == 0)
		{
			for (int i = 0; i<70; i++)
				cout << '\b';
			printf("Iteration: %6d   Residual: %20.15f", j, sqrt(d));
		}
		for (i = 0; i<size; i++) {					// v = r + (d/c)*v;
			v[i] = r[i] + (d / c)*v[i];
		}

		c = d;

	}
	for (int i = 0; i<70; i++)
		cout << '\b';
	printf("Iteration: %6d   Residual: %20.15f", j, sqrt(d));
	cout << endl;
}

void	CG(IMatrix_double& A, FVector_double& x, FVector_double& b, double epsilon) {				// conjugate gradient method

	int i, j = 0;
	int size = b._size;
	double c, t, d;
	FVector_double Ax(size), v(size), Av(size), r(size);

	if (size != b._size) {						// Efficient Form on Reiteration 
		size = b._size;
		Ax.make(size);	v.make(size);	Av.make(size);	r.make(size);	// Memory Allocation
	}
	IMatrix_multiple(A, x, Ax);					// Ax = A*x;
	for (i = 0; i<size; i++) {
		r[i] = b[i] - Ax[i];					// r = b - Ax;
	}

	v = r;
	c = (r, r);

	if (sqrt(c) < epsilon) return;

	for (j = 1;; j++) {
		IMatrix_multiple(A, v, Av);				// Av = A*v;
		t = c / (v, Av);
		for (i = 0; i<size; i++) {
			x._vec[i] += t*v._vec[i];
			r._vec[i] -= t*Av._vec[i];
		}
		d = (r, r);
		if (sqrt(d) < epsilon) break;
		if (j % 10 == 0)
		{
			for (int i = 0; i<70; i++)
				cout << '\b';
			printf("Iteration: %6d   Residual: %20.15f", j, sqrt(d));
		}
		for (i = 0; i<size; i++) {					// v = r + (d/c)*v;
			v[i] = r[i] + (d / c)*v[i];
		}

		c = d;

	}
	for (int i = 0; i<70; i++)
		cout << '\b';
	printf("Iteration: %6d   Residual: %20.15f", j, sqrt(d));
	cout << endl;
}

int main()
{

	cout << "[ P1-DG : SIPG ]" << endl;

	FMatrix_double domain;
	//domain= [-1 1]*[-1 1];
	domain.make(2, 2);
	domain[0][0] = -1; domain[0][1] = 1;
	domain[1][0] = -1; domain[1][1] = 1;


	char *null = "notcopy";
	char prob[5][25] = { "DG_level_2.m", "DG_level_3.m", "DG_level_4.m", "DG_level_5.m", "DG_level_6.m" };
	int start, end;
	int step;
	cout << "Start level : "; cin >> start;
	cout << "End level : "; cin >> end;
	step = end - start + 1;

	double *error = new double[step];
	double *order = new double[step - 1];

	cout << endl;

	for (int i = 0; i < step; i++)
	{
		cout << "Level : " << i + start << endl;
		if (i <= 6)
			error[i] = DG_SIPG(u, p, g, F, domain, i + start, 1, prob[i]);
		else
			error[i] = DG_SIPG(u, p, g, F, domain, i + start, 0, null);
		cout << endl;
	}

	cout << endl;
	//convergence order
	for (int i = 0; i < step - 1; i++)
	{
		order[i] = log(error[i] / error[i + 1]) / log(2);
	}

	cout << "----------------------Result----------------------" << endl;

	cout << "<Error>" << endl;
	for (int i = 0; i < step; i++)
	{
		cout << "level = " << i + start << " : " << error[i] << endl;
	}
	cout << "convergence order : ";
	for (int i = 0; i < step - 1; i++)
	{
		cout << " " << order[i] << " ";
	}
	cout << endl << endl;


	int test;
	cout << "test"; cin >> test;
	return 0;
}

double DG_SIPG(double(*u)(FVector_double &p), double(*p)(FVector_double &p), double(*g)(FVector_double& p), double(*F)(FVector_double &p), FMatrix_double& domain, int lev, int choice, char *ch)
{
	// - div (p grad u) = f
	// domain = [x1 x2]*[y1 y2]
	// i.e domain = | x1  x2 |
	//				| y1  y2 |

	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	//�̢�	        Set sigma in DG schmeme				 �̢�
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�

	double gamma = 1000;


	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	//�̢�	        Set number of meshrefinement			 �̢�
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�

	int level = lev;

	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	//�̢�				Some Common Variables		     �̢�
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	int i, j, k,l;
	int e, eN, edge;

	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	//�̢�		 Mesh Generation(Triangular Mesh)		�̢� 
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	// Generate uniform grid with K by K element
	double ax, bx, ay, by;
	// Domain: x=[ax bx], y=[ay by]
	ax = domain[0][0]; bx = domain[0][1];
	ay = domain[1][0]; by = domain[1][1];

	// Declation
	int nsN;						// Number of side node->grid in P1 nonconforming
	double h;						// Meshsize in case of regtangular domain
	int neT;						// Number of element total
	int nnT;						// Number of node total  (not used in this code)
	int nsR;						// Number of side rectangular
	int nsE;						// Number of element total (not used in this code)
	int nlt;						// number of total edges
	double dx;						// Meshsize x direction  (not used in this code)
	double dy;						// Meshsize y direction	 (not used in this code)
	int npT;						// Number of unknown total
	int nbT_d;						// Number of Dirichlet boundary node total
	int nbT_n;						// Number of Neumann boundary node total

	FMatrix_double coordN;			// Coordinate ( coordN[global node][x-coord][y-coord]  ) 	
	FMatrix_double edge_coordN;		// Coordinate ( coordN[global grid][x-coord][y-coord]  )



	// Definition

	nsN = 1;
	for (i = 0; i < level; i++)
	{
		nsN = nsN * 2;
	}
	nsN = nsN + 1;
	nsR = nsN - 1;
	nnT = nsN*nsN;
	neT = (nsN - 1)*(nsN - 1) * 2;
	nlt = 2 * nsR*nsN + neT / 2;

	h = bx - ax;
	for (i = 0; i < level; i++)
	{
		h = h / 2;
	}
	

	npT = 3 * neT;					// each element has 3 degree of freedom



	coordN.make(nnT, 2);				// lexicograhic order from bottom to top
	for (i = 0; i < nsN; i++)
	{
		for (j = 0; j < nsN; j++)
		{

			coordN[i*nsN + j][0] = ax + j*h;
			coordN[i*nsN + j][1] = ay + i*h;
		}
	}





	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	//�̢�				Index Set Generation 	         �̢�
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�

	// Declation
	FMatrix_int indexP;				// Index from local number to global number
	FMatrix_int indexL;
	FMatrix_int indexN;

	// Definition
	indexP.make(neT, 3);					// indexP[of element][of local element] = global numbering
	indexL.make(nlt, 3);					// indexL[of edge][0]=element e, [1]=element eN, [2]=local numbering
	indexN.make(neT, 3);					// indexN[of element][of local element] = global grid  numbering

	//indexP
	for (e = 0; e < neT; e++)
	{
		for (int i = 0; i < 3; i++)
			indexP[e][i] = 3 * e + i;
	}

	//indexN
	int row; int col;
	for (i = 0; i < neT; i++)
	{
		
		col = i / (2 * nsR); row = i % (2 * nsR);
		if (row % 2 == 0)
		{
			indexN[i][0] = col*nsN + row / 2;
			indexN[i][1] = col*nsN + row / 2 + 1;
			indexN[i][2] = (col + 1)*nsN + row / 2;
		}
		else
		{
			indexN[i][1] = (col + 1)*nsN + row / 2;
			indexN[i][0] = (col + 1)*nsN + row / 2 + 1;
			indexN[i][2] = col*nsN + row / 2 + 1;
		}
	}



	//indexL
	//horizontal edge : 
	for (i = 0; i < nsN; i++)
	{
		for (j = 0; j < nsR; j++)
		{
			edge = i*nsR + j;
			indexL[edge][2] = 0;
			if (i == 0)
			{
				indexL[edge][0] = -1;
				indexL[edge][1] = 2*j;
			}
			else if (i == nsN - 1)
			{
				indexL[edge][0] = ((i - 1)*nsR + j) * 2 + 1;
				indexL[edge][1] = -1;
			}
			else
			{
				indexL[edge][0] = ((i - 1)*nsR + j) * 2 + 1;
				indexL[edge][1] = (i*nsR + j) * 2;
			}
		}
	}

	//vertical edge :
	for (i = 0; i < nsR; i++)
	{
		for (j = 0; j < nsN; j++)
		{
			edge = (nsN*nsR) + i*nsN + j;
			indexL[edge][2] = 2;
			
			if (j == 0)
			{
				indexL[edge][0] = -1;
				indexL[edge][1] = (i*nsR + j) * 2;
			}
			else if (j == nsN - 1)
			{
				indexL[edge][0] = (i*nsR + j) * 2 - 1;
				indexL[edge][1] = -1;
			}
			else
			{
				indexL[edge][0] = (i*nsR + j) * 2 - 1;
				indexL[edge][1] = (i*nsR + j) * 2;
			}
		}
	}

	//diagonal edge : 
	for (i = 0; i < nsR; i++)
	{
		for (j = 0; j < nsR; j++)
		{
			edge = (2 * nsN*nsR) + i*nsR + j;
			indexL[edge][0] = (i*nsR + j) * 2;
			indexL[edge][1] = (i*nsR + j) * 2 + 1;
			indexL[edge][2] = 1;

		}
	}

	

	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	//�̢�				Memory Allocation				 �̢�
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�

	// Declation 
	IMatrix_double mA;				// Matrix
	FVector_double vCP;				// Unknown( = uh)
	FVector_double vF;				// Load Vector
	FVector_double sol;				// Solution
	
									// Initialization
	mA.make(npT, npT,15);
	vCP.make(npT);
	vF.make(npT);
	sol.make(npT);

	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	//�̢�				Matrix Generation				 �̢�
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�

	// Declaration
	int pi, pj;						// indexP[e][i], indexP[e][j]
	double f = 0;					// Load Vector

	FVector_double pre_psi;			// Basis function value at mid point
	FMatrix_double pre_dpsi;		// Diffential basis function value at mid point
	FMatrix_double pre_epsi;		// Basis function value at mid point of edge
	FMatrix_double pre_edpsi_x;		// Diffential basis function x-value at mid point of edge 
	FMatrix_double pre_edpsi_y;		// Diffential basis function y-value at mid point of edge
	
	FVector_double vRealP;			// Element e :  MidPoint Coordinate
	FVector_double vRealP_N;		// Element eN : MidPoint Coordinate

	FMatrix_double DF;				// Mapping
	FMatrix_double DFIT;			// Inverse and transpose of DF
	FVector_double v1;
	FVector_double v2;
	double det;						// Determinant
	double jacobian;				// Jacobian of integral
	double jacoweight;				// Jacobian * weight

	double ni, nj, e_len;			// 2 nodes index of an edge , length of the edge
	double t1, t2;
	FVector_double val_i;			// 2 points of an edge
	FVector_double val_j;				
	FVector_double normal_v;		// normal vector of an edge

	FVector_double vDOF;			// global index of degree of freedom in the element e(0~2) and eN(3~5)
	FVector_double PSI_JUMP;		// jump value of basis functions in e(0~2) and eN(3~5)
	FMatrix_double DPSI_AVE;		// average value of basis functions in e(0~2) and eN(3~5)

	FVector_double PSI, PSI_N;		// Basis function value at mid point in the element e/eN
	FMatrix_double DPSI, DPSI_N;	// Diffential basis function value at mid point in the element e/eN


	// 1. Set Prevalues								// pre_psi and pre_dpsi are calculated on reference trangle

	pre_psi.make(3);									// make(row size, column size) : specify the size of matrix and initialize
	pre_dpsi.make(3, 2);
	
	pre_epsi.make(3, 3);
	pre_edpsi_x.make(3, 3);
	pre_edpsi_y.make(3, 3);

	vDOF.make(6);
	PSI_JUMP.make(6);
	DPSI_AVE.make(6,2);

	PSI.make(3);
	PSI_N.make(3);
	DPSI.make(3, 2);
	DPSI_N.make(3, 2);



	vRealP.make(2);
	vRealP_N.make(2);
	DF.make(2, 2);
	DFIT.make(2, 2);
	v1.make(2);
	v2.make(2);

	val_i.make(2); val_j.make(2);
	normal_v.make(2);

	/*
	phi_0=1-x-y	 phi_1=x	 phi_2=y
	*/

	// pre_psi[# of local index][basis values at coordinate of centroid on the reference triangle]
	pre_psi[0] = 1. / 3;							
	pre_psi[1] = 1. / 3;
	pre_psi[2] = 1. / 3;

	// pre_psi[#of local index][differential of basis values at coordinate of centroid on the reference triangle]
	pre_dpsi[0][0] = -1.;							
	pre_dpsi[0][1] = -1.;
	pre_dpsi[1][0] = 1.;
	pre_dpsi[1][1] = 0.;
	pre_dpsi[2][0] = 0.;
	pre_dpsi[2][1] = 1.;

	// pre_epsi[local index of edge][ basis function pre_psi ]
	pre_epsi[0][0] = 0.5;
	pre_epsi[0][1] = 0.5;
	pre_epsi[0][2] = 0.;
	pre_epsi[1][0] = 0.;
	pre_epsi[1][1] = 0.5;
	pre_epsi[1][2] = 0.5;
	pre_epsi[2][0] = 0.5;
	pre_epsi[2][1] = 0.;
	pre_epsi[2][2] = 0.5;

	//pre_edpsi_x[local index of edge][basis function pre_psi]
	pre_edpsi_x[0][0] = -1.; pre_edpsi_y[0][0] = -1.;
	pre_edpsi_x[0][1] = 1.; pre_edpsi_y[0][1] = 0.;
	pre_edpsi_x[0][2] = 0.; pre_edpsi_y[0][2] = 1.;

	pre_edpsi_x[1][0] = -1.; pre_edpsi_y[1][0] = -1.;
	pre_edpsi_x[1][1] = 1.; pre_edpsi_y[1][1] = 0.;
	pre_edpsi_x[1][2] = 0.; pre_edpsi_y[1][2] = 1.;

	pre_edpsi_x[2][0] = -1.; pre_edpsi_y[2][0] = -1.;
	pre_edpsi_x[2][1] = 1.; pre_edpsi_y[2][1] = 0.;
	pre_edpsi_x[2][2] = 0.; pre_edpsi_y[2][2] = 1.;





	

	// 2. Make Matrix Part.	--- mA, vF

	for (e = 0; e<neT; e++)
	{

		Make_realP_and_DF(vRealP, DF, coordN, pre_psi, indexN[e]);
		det = inverse(DF, DFIT);
		transpose(DFIT); jacobian = fabs(det); jacoweight = jacobian*(1 / 2.);
		for (j = 0; j<3; j++)
		{
			pj = indexP[e][j];
			for (i = 0; i<3; i++)
			{
				pi = indexP[e][i];

				v1[0] = (DFIT[0], pre_dpsi[j]);
				v1[1] = (DFIT[1], pre_dpsi[j]);
				v2[0] = (DFIT[0], pre_dpsi[i]);
				v2[1] = (DFIT[1], pre_dpsi[i]);
				mA[pi][pj] += p(vRealP)*(v1, v2)*jacoweight;
			}

			f = F(vRealP);
			vF[pj] += f*pre_psi[j] * jacoweight;
		}

	}

	
	// Additional part of a(u,v) for DG Scheme
	for (edge = 0; edge < nlt; edge++)
	{
		e = indexL[edge][0];
		eN = indexL[edge][1];
		l = indexL[edge][2];
		
		if (e == -1)
		{
			int temp = e;
			e = eN;
			eN = temp;
		}



		//normal vector and the length of the edge
		ni = indexN[e][l];
		nj = indexN[e][(l + 1) % 3];

		val_i[0] = coordN[ni][0];
		val_i[1] = coordN[ni][1];
		val_j[0] = coordN[nj][0];
		val_j[1] = coordN[nj][1];

		
		
		t1 = val_j[0] - val_i[0];
		t2 = val_j[1] - val_i[1];
		e_len = sqrt(t1*t1 + t2*t2);
		normal_v[0] = t2 / sqrt(t1*t1 + t2*t2);
		normal_v[1]=-t1/ sqrt(t1*t1 + t2*t2);


		//jump and average : 

		//jump and average w.r.t element e
		Make_realP_and_DF(vRealP, DF, coordN, pre_psi, indexN[e]);
		det = inverse(DF, DFIT);
		transpose(DFIT); jacobian = fabs(det); jacoweight = jacobian*(1 / 2.);
		for (i = 0; i < 3; i++)
		{
			PSI[i] = pre_epsi[l][i];
			DPSI[i][0]=DFIT[0][0]*pre_edpsi_x[l][i]+ DFIT[0][1] * pre_edpsi_y[l][i];
			DPSI[i][1] = DFIT[1][0] * pre_edpsi_x[l][i] + DFIT[1][1] * pre_edpsi_y[l][i];
		}

		//jump and average w.r.t element eN if the edge is in the interior
		if (eN >= 0)
		{
			Make_realP_and_DF(vRealP_N, DF, coordN, pre_psi, indexN[eN]);
			det = inverse(DF, DFIT);
			transpose(DFIT); jacobian = fabs(det); jacoweight = jacobian*(1 / 2.);
			for (int i = 0; i < 3; i++)
			{
				PSI_N[i] = pre_epsi[l][i];
				DPSI_N[i][0] = DFIT[0][0] * pre_edpsi_x[l][i] + DFIT[0][1] * pre_edpsi_y[l][i];
				DPSI_N[i][1] = DFIT[1][0] * pre_edpsi_x[l][i] + DFIT[1][1] * pre_edpsi_y[l][i];
			}
		}

		vDOF[0] = -1;
		vDOF[1] = -1;
		vDOF[2] = -1;
		vDOF[3] = -1;
		vDOF[4] = -1;
		vDOF[5] = -1;

		PSI_JUMP.clear();
		DPSI_AVE.clear();
		
		
		// interior edge
		if (eN >= 0)
		{
			for (i = 0; i < 3; i++)
			{
				vDOF[i] = indexP[e][i];
				vDOF[3 + i] = indexP[eN][i];

				PSI_JUMP[i] = PSI[i];
				PSI_JUMP[3 + i] = -PSI_N[i];

				DPSI_AVE[i][0] = p(vRealP)*0.5*DPSI[i][0];
				DPSI_AVE[i][1] = p(vRealP)*0.5*DPSI[i][1];

				DPSI_AVE[3 + i][0] =p(vRealP_N)* 0.5*DPSI_N[i][0];
				DPSI_AVE[3 + i][1] = p(vRealP_N)*0.5*DPSI_N[i][1];
				
			}

		}
		// boudary edge
		else
		{
			for (i = 0; i < 3; i++)
			{
				vDOF[i] = indexP[e][i];
				

				PSI_JUMP[i] = PSI[i];

				DPSI_AVE[i][0] = p(vRealP)*DPSI[i][0];
				DPSI_AVE[i][1] = p(vRealP)*DPSI[i][1];
			}

		} 

		
		for (j = 0; j<6; j++)
		{
			if (vDOF[j] >= 0) 
			{
				pj = vDOF[j];
				for (int i = 0; i < 6; i++) 
				{ 
					if (vDOF[i] >= 0)
					{
						pi = vDOF[i];
						mA[pi][pj] -= e_len*(DPSI_AVE[i], normal_v)*PSI_JUMP[j];
						mA[pi][pj] -= e_len*(DPSI_AVE[j], normal_v)*PSI_JUMP[i];
						mA[pi][pj] += 1000*PSI_JUMP[j]*PSI_JUMP[i];
					} 
				} // vDOF[i]
			}  
		} // vDOF[j]

	  //�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	  //�̢�		 	Boundary	Process					   �̢�
	  //�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢� 
		
		FVector_double e_mid;
		e_mid.make(2);

		if (eN == -1)
		{
			for (j = 0; j < 3; j++)
			{
				pj = vDOF[j];
				e_mid[0] = (val_i[0] + val_j[0]) / 2;
				e_mid[1] = (val_i[1] + val_j[1]) / 2;

				vF[pj] += gamma* g(e_mid)*PSI_JUMP[j];
				vF[pj] -= e_len*(DPSI_AVE[j], normal_v)*g(e_mid);
				
			}
		}
	
	}

	
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	//�̢�		 	Conjugate Gradient					 �̢�
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢� 
	CG(mA, vCP, vF, 1.0E-10);


	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	//�̢�				Error					         �̢�
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�


	double error = 0.;
	double cv = 0.;			// cv = u(centroid) - uh(centroid) 
	FVector_double cent;
	cent.make(2);			// coordinate of centroid

	for (e = 0; e < neT; e++)
	{
		cent.clear();
		double uh_cent = 0;
		for (i = 0; i < 3; i++)
		{
			uh_cent += vCP[indexP[e][i]] / 3;
			cent[0] += coordN[indexN[e][i]][0] / 3;
			cent[1] += coordN[indexN[e][i]][1] / 3;
		}
		cv += pow(u(cent) - uh_cent, 2);
	}
	error = cv*pow(h, 2);
	error = sqrt(error);


	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	//�̢�				Drawing Graph				     �̢�
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�


	if (choice == 1)
	{
		FILE *fp = fopen(ch, "w");

		double x, y, z;
		int e;
		int pi;

		// [node][basis_i]
		FMatrix_double gpre_psi;

		gpre_psi.make(3, 3);
		//   -1 + (2 * x) + (2 * y), 1 - (2 * x), 1 - (2 * y)

		gpre_psi[0][0] = 1.;
		gpre_psi[0][1] = 0.;
		gpre_psi[0][2] = 0.;

		gpre_psi[1][0] = 0.;
		gpre_psi[1][1] = 1.;
		gpre_psi[1][2] = 0.;

		gpre_psi[2][0] = 0.;
		gpre_psi[2][1] = 0.;
		gpre_psi[2][2] = 1.;

		/* X coordinate*/
		fprintf(fp, "x0= [");
		for (e = 0; e<neT; e++) {
			pi = indexN[e][0];
			x = coordN[pi][0];
			fprintf(fp, "%6.10f  ", x);
			fprintf(fp, " ");

		}
		fprintf(fp, "; \n");
		for (e = 0; e<neT; e++) {
			pi = indexN[e][1];
			x = coordN[pi][0];
			fprintf(fp, "%6.10f  ", x);
			fprintf(fp, " ");

		}
		fprintf(fp, "; \n");
		for (e = 0; e<neT; e++) {
			pi = indexN[e][2];
			x = coordN[pi][0];
			fprintf(fp, "%6.10f  ", x);
			fprintf(fp, " ");

		}
		fprintf(fp, "];\n");

		/* Y coordinate*/
		fprintf(fp, "y0= [");
		for (e = 0; e<neT; e++) {
			pi = indexN[e][0];
			y = coordN[pi][1];
			fprintf(fp, "%6.10f  ", y);
			fprintf(fp, " ");

		}
		fprintf(fp, "; \n");
		for (e = 0; e<neT; e++) {
			pi = indexN[e][1];
			y = coordN[pi][1];
			fprintf(fp, "%6.10f  ", y);
			fprintf(fp, " ");

		}
		fprintf(fp, "; \n");
		for (e = 0; e<neT; e++) {
			pi = indexN[e][2];
			y = coordN[pi][1];
			fprintf(fp, "%6.10f  ", y);
			fprintf(fp, " ");

		}
		fprintf(fp, "];\n");


		/* z coordinate*/
		fprintf(fp, "z0= [");
		for (e = 0; e<neT; e++) {

			z = 0;
			for (int i = 0; i < 3; i++) {
				pi = indexP[e][i];
				z = z + vCP[pi] * gpre_psi[0][i];
			}
			fprintf(fp, "%6.10f  ", z);
			fprintf(fp, " ");

		}
		fprintf(fp, "; \n");
		for (e = 0; e<neT; e++) {

			z = 0;
			for (int i = 0; i < 3; i++) {
				pi = indexP[e][i];
				z = z + vCP[pi] * gpre_psi[1][i];
			}
			fprintf(fp, "%6.10f  ", z);
			fprintf(fp, " ");

		}
		fprintf(fp, "; \n");
		for (e = 0; e<neT; e++) {

			z = 0;
			for (int i = 0; i < 3; i++) {
				pi = indexP[e][i];
				z = z + vCP[pi] * gpre_psi[2][i];
			}
			fprintf(fp, "%6.10f  ", z);
			fprintf(fp, " ");

		}
		fprintf(fp, "];\n");
		fprintf(fp, "c0 = z0; \n  ");
		fprintf(fp, "figure(1) \n  ");
		fprintf(fp, "fill3(x0, y0, z0, c0) \n  ");
		fprintf(fp, "view(30.000000, 30.000000) \n  ");
		fprintf(fp, "grid on \n  ");
		fprintf(fp, "xlabel 'X'; \n  ");
		fprintf(fp, "ylabel 'Y'; \n  ");
		fprintf(fp, "colormap jet; \n  ");
		fprintf(fp, "drawnow; \n  ");
		fprintf(fp, "colorbar; \n  ");




		fclose(fp);
	}


	return error;
}