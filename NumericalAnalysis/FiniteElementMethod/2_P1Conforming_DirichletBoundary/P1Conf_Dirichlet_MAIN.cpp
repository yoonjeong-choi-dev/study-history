//2017 FEM Mid_term project
//20173595 Choi Yoonjeong

#include "class17_.h"


//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
//�̢�					 Problem								      �̢�
//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�

// - div (p grad u) = f

//(1) , (2)
double p(FVector_double & p)											
{
	double x = p[0];	double y = p[1];
	return 1 + x + 2 * pow(y, 2); 
}

double g(FVector_double & p)											// boundary condition 
{
	double x = p[0];	double y = p[1];
	return 1 + x + y;
}


double F(FVector_double & p)											// f 
{
	double x = p[0];	double y = p[1];
	double f;
	f = -(1 + 4 * y);

	return f;
}

// Problme (3),(5)
double u3(FVector_double & p)											//exact solution
{
	double x = p[0];	double y = p[1];
	return x*(1 - x)*y*(1 - y);
}

double p3(FVector_double & p)											
{
	double x = p[0];	double y = p[1];
	return 1 + x + 2 * pow(y, 2);
}

double g3(FVector_double &p)											// boundary condition 	
{
	return 0;
}
double F3(FVector_double& p)											
{
	double x = p[0];	double y = p[1];
	double f;

	f = (1 + x + 2 * pow(y, 2)) * 2 * (x*(1 - x) + y*(1 - y)) - (1 - 2 * x)*y*(1 - y) - 4 * x*(1 - x)*y*(1 - 2 * y);

	return f;
}

//Problem (4) 
double p4(FVector_double &p)
{
	double x = p[0];	double y = p[1];
	return 1;
}

double u4(FVector_double &p)
{
	double x = p[0];	double y = p[1];
	return 1 + x + 9 * y;
}

double g4(FVector_double &p)
{
	double x = p[0];	double y = p[1];
	return 1 + x + 9 * y;
}

double F4(FVector_double &p)
{
	double x = p[0]; double y = p[1];
	return 0;
}

//Problem (6)
double p6(FVector_double &p)
{
	double x = p[0];	double y = p[1];
	return 1 + x*y;
}

double u6(FVector_double &p)
{
	double x = p[0];	double y = p[1];
	return exp(x + 3 * y);
}

double g6(FVector_double &p)
{
	double x = p[0];	double y = p[1];
	return exp(x + 3 * y);
}

double F6(FVector_double &p)
{
	double x = p[0]; double y = p[1];
	return -10 * (1 + x*y)*exp(x + 3 * y) - (3*x+y) * exp(x + 3 * y);
}


//Du : not use in this problem
void	Du(FVector_double& p, FVector_double& vDP)					// used when we calculate H1 error
{
	double x = p[0];	double y = p[1];
	vDP[0] = (1 - 2 * x)*y*(1 - y);
	vDP[1] = (1 - 2 * y)*x*(1 - x);
}


//choice =1 : save solution as ch.m file
double FEM_Dirichlet(double(*u)(FVector_double &p), double(*p)(FVector_double &p), double(*g)(FVector_double& p), double(*F)(FVector_double &p), FMatrix_double& domain, int lev, int choice,char *ch);


//void	DDu			(FVector_double& p, FMatrix_double& mDDP) {

//}

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
	FMatrix_double domain;
	//domain= [0 1]*[0 1];
	domain.make(2, 2);
	domain[0][0] = 0; domain[0][1] = 1;
	domain[1][0] = 0; domain[1][1] = 1;



	// (1)~(2)
	int level = 2;
	int element = 10;		// 11th element
	double ax, bx, ay, by;								// Domain: x=[ax bx], y=[ay by]
	ax = domain[0][0]; bx = domain[0][1];
	ay = domain[1][0]; by = domain[1][1];

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

	h = 1.;
	for (int i = 0; i<level; i++)
	{
		h = h / 2;
	}

	neT = (nsN - 1)*(nsN - 1) * 2;		//nsR*nsR*2

	npT = nsN*nsN;

	nbT_d = (nsN - 1) * 4;

	coordN.make(npT, 2);										// lexicograhic order from bottom to top
	for (int i = 0; i<nsN; i++)
	{
		for (int j = 0; j<nsN; j++)
		{

			coordN[i*nsN + j][0] = ax + j*h;
			coordN[i*nsN + j][1] = ay + i*h;
		}
	}


	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	//�̢�			       Index Set Generation 	    				  �̢�
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�

	// Declation

	FMatrix_int indexP;				// Index from local number to global number
	FMatrix_int indexB_d;			// Dirichlet Boundary Node Information
	FMatrix_int indexB_n;			// Neumann Boundary Node Information


	// Definition
	indexP.make(neT, 3);					// indexP[of element][of local element] = global numbering
	indexB_d.make(nbT_d, 2);				// indexB_d[of nodes on boundary][0] = element, [1] = local numbering 

	//indexP
	for (int i = 0; i < neT; i++)
	{
		int row; int col;
		col = i / (2 * nsR); row = i % (2 * nsR);
		if (row % 2 == 0)
		{
			indexP[i][0] = col*nsN + row / 2;
			indexP[i][1] = col*nsN + row / 2 + 1;
			indexP[i][2] = (col + 1)*nsN + row / 2;
		}
		else
		{
			indexP[i][1] = (col + 1)*nsN + row / 2;
			indexP[i][0] = (col + 1)*nsN + row / 2 + 1;
			indexP[i][2] = col*nsN + row / 2 + 1;
		}
	}

	//indexB_d
	for (int i = 0; i < nsN - 1; i++)
	{
		//lower
		indexB_d[i][0] = 2 * i;
		indexB_d[i][1] = 0;
		//left
		indexB_d[(nsN - 1) + i][0] = 2 * (nsN - 1)*i;
		indexB_d[(nsN - 1) + i][1] = 2;
		//right
		indexB_d[(nsN - 1) * 2 + i][0] = 2 * (nsN - 1)*(i + 1) - 1;
		indexB_d[(nsN - 1) * 2 + i][1] = 2;
		//upper
		indexB_d[(nsN - 1) * 3 + i][0] = 2 * (nsN - 1)*(nsN - 2) + 2 * i + 1;
		indexB_d[(nsN - 1) * 3 + i][1] = 0;
	}


	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	//�̢�						  Memory Allocation			   			  �̢�
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�

	// Declation 
	FMatrix_double mA;				// Matrix
	FVector_double vF;				// Load Vector
	FMatrix_double K11;				//stiffness matrix of 11th element

	// Initialization
	mA.make(npT, npT);
	vF.make(npT);
	K11.make(3, 3);
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	//�̢�						Matrix Generation		                  �̢�
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

	Make_realP_and_DF(vRealP, DF, coordN, pre_psi, indexP[element]);
	det = inverse(DF, DFIT);
	transpose(DFIT); jacobian = fabs(det); jacoweight = jacobian*(1 / 2.);
	for (int j = 0; j<3; j++)
	{
		for (int i = 0; i<3; i++)
		{
			v1[0] = (DFIT[0], pre_dpsi[j]);
			v1[1] = (DFIT[1], pre_dpsi[j]);
			v2[0] = (DFIT[0], pre_dpsi[i]);
			v2[1] = (DFIT[1], pre_dpsi[i]);
			K11[i][j] += p(vRealP)*(v1, v2)*jacoweight;
		}
	}
	cout << "--------------(1)--------------" << endl;
	cout << "global index of 11th element "; indexP[element].print();
	cout << "stiffness matrix of 11th element"; K11.print();
	cout << endl<<endl;

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
			f = F(vRealP);
			vF[pj] += f*pre_psi[j] * jacoweight;
		}
	}

	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	//�̢�				Boundary Process							      �̢�
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�

	int ln;									// local number
	double mv, bv;							// mv = mA[][], bv = values on boundary

	for (int j = 0; j < nbT_d; j++)
	{
		ln = indexP[indexB_d[j][0]][indexB_d[j][1]];
		bv = g(coordN[ln]);
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

	cout << "--------------(2)--------------" << endl;
	cout << "Case 1 : F(i)= Information of i-th node " << endl;
	for (int i = 3; i < 7; i++)
		cout << "F(" << i + 1 << ") : " << vF[i] << endl;
	cout << endl;
	cout << "Case 2 : the order of F(i) = (2.86) in Ch2 p30." << endl;
	cout << "F(" << 4 << ") : " << vF[11] << endl;
	cout << "F(" << 5 << ") : " << vF[12] << endl;
	cout << "F(" << 6 << ") : " << vF[13] << endl;
	cout << "F(" << 7 << ") : " << vF[16] << endl;
	cout << endl;

	//Declaration error & order
	double error[5];
	double order[4];
	char *null = "notcopy";

	//(3),(5)
	cout << "--------------(3)--------------" << endl;
	char prob3[5][20] = { "problem3_level_2.m", "problem3_level_3.m", "problem3_level_4.m", "problem3_level_5.m", "problem3_level_6.m" };

	
	for (int i = 2; i < 7; i++)
		error[i - 2] = FEM_Dirichlet(u3, p3, g3, F3, domain, i,1,prob3[i-2]);

	//convergence order
	for (int i = 0; i < 4; i++)
	{
		order[i] = log(error[i] / error[i + 1]) / log(2);
	}
	
	cout << "<Error>" << endl;
	for (int i = 0; i < 5; i++)
	{
		cout << "level = " << i + 2 << " : " << error[i] << endl;
	}
	cout << "convergence order : ";
	for (int i = 0; i < 4; i++)
	{
		cout << " " << order[i] << " ";
	}
	cout << endl << endl;

	//(4)
	cout << "--------------(4)--------------" << endl;
	char prob4[5][20] = { "problem4_level_2.m", "problem4_level_3.m", "problem4_level_4.m", "problem4_level_5.m", "problem4_level_6.m" };
	//char prob4[20] = "test";
	for (int i = 2; i < 7; i++)
		//error[i - 2] = FEM_Dirichlet(u4, p4, g4, F4, domain, i,1,prob4[i-2]);		// save m.file
		error[i - 2] = FEM_Dirichlet(u4, p4, g4, F4, domain, i, 0, null);	// not save m.file

	//convergence order
	for (int i = 0; i < 4; i++)
	{
		order[i] = log(error[i] / error[i + 1]) / log(2);
	}

	cout << "<Error>" << endl;
	for (int i = 0; i < 5; i++)
	{
		cout << "level = " << i + 2 << " : " << error[i] << endl;
	}

	cout << "convergence order : ";
	for (int i = 0; i < 4; i++)
	{
		cout << " " << order[i] << " ";
	}

	cout << endl << endl;


	//(6)
	char prob6[5][20] = { "problem6_level_2.m","problem6_level_3.m","problem6_level_4.m","problem6_level_5.m","problem6_level_6.m" };
	cout << "--------------(6)--------------" << endl;
	
	//problem : 
	cout << "Problem : -div(p grad(u))=f " << endl;
	cout << "exact solution u=exp(x+3y)" << endl;
	cout << "p=1+xy" << endl;
	cout << "boundary condition : g=exp(x+3y)" << endl;
	cout << "F=-10 * (1 + x*y)*exp(x + 3 * y) - (3*x+y) * exp(x + 3 * y)" << endl;
	cout << endl;


	for (int i = 2; i < 7; i++)
		error[i - 2] = FEM_Dirichlet(u6, p6, g6, F6, domain, i, 1,prob6[i-2]);

	//convergence order
	for (int i = 0; i < 4; i++)
	{
		order[i] = log(error[i] / error[i + 1]) / log(2);
	}

	cout << "<Error>" << endl;
	for (int i = 0; i < 5; i++)
	{
		cout << "level = " << i + 2 << " : " << error[i] << endl;
	}

	cout << "convergence order : ";
	for (int i = 0; i < 4; i++)
	{
		cout << " " << order[i] << " ";
	}

	cout << endl << endl; 

	
	/*int test;
	cout << "test"; cin >> test;*/
	return 0;
}

double FEM_Dirichlet(double(*u)(FVector_double &p), double(*p)(FVector_double &p), double(*g)(FVector_double& p), double(*F)(FVector_double &p), FMatrix_double& domain, int lev, int choice,char *ch)
{
	// - div (p grad u) = f
	// domain = [x1 x2]*[y1 y2]
	// i.e domain = | x1  x2 |
	//				| y1  y2 |

	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	//�̢�	             Set number of meshrefinement					  �̢�
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�

	int level = lev;

	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	//�̢�					Some Common Variables					      �̢�
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�

	int i, j, e, k, node;				// Common variables

	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	//�̢�					Mesh Generation	(Triangular Mesh)   		    �̢�
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	// Generate uniform grid with K by K element
	double ax, bx, ay, by;
	// Domain: x=[ax bx], y=[ay by]
	ax = domain[0][0]; bx = domain[0][1];
	ay = domain[1][0]; by = domain[1][1];

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

	h = 1.;
	for (int i = 0; i<level; i++)
	{
		h = h / 2;
	}

	neT = (nsN - 1)*(nsN - 1) * 2;		//nsR*nsR*2

	npT = nsN*nsN;

	nbT_d = (nsN - 1) * 4;

	coordN.make(npT, 2);										// lexicograhic order from bottom to top
	for (int i = 0; i<nsN; i++)
	{
		for (int j = 0; j<nsN; j++)
		{

			coordN[i*nsN + j][0] = ax + j*h;
			coordN[i*nsN + j][1] = ay + i*h;
		}
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

	//indexP
	for (int i = 0; i < neT; i++)
	{
		int row; int col;
		col = i / (2 * nsR); row = i % (2 * nsR);
		if (row % 2 == 0)
		{
			indexP[i][0] = col*nsN + row / 2;
			indexP[i][1] = col*nsN + row / 2 + 1;
			indexP[i][2] = (col + 1)*nsN + row / 2;
		}
		else
		{
			indexP[i][1] = (col + 1)*nsN + row / 2;
			indexP[i][0] = (col + 1)*nsN + row / 2 + 1;
			indexP[i][2] = col*nsN + row / 2 + 1;
		}
	}

	//indexB_d
	for (int i = 0; i < nsN - 1; i++)
	{
		//lower
		indexB_d[i][0] = 2 * i;
		indexB_d[i][1] = 0;
		//left
		indexB_d[(nsN - 1) + i][0] = 2 * (nsN - 1)*i;
		indexB_d[(nsN - 1) + i][1] = 2;
		//right
		indexB_d[(nsN - 1) * 2 + i][0] = 2 * (nsN - 1)*(i + 1) - 1;
		indexB_d[(nsN - 1) * 2 + i][1] = 2;
		//upper
		indexB_d[(nsN - 1) * 3 + i][0] = 2 * (nsN - 1)*(nsN - 2) + 2 * i + 1;
		indexB_d[(nsN - 1) * 3 + i][1] = 0;
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
			for (i = 0; i<3; i++)
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
			f = F(vRealP);
			vF[pj] += f*pre_psi[j] * jacoweight;
		}

	}


	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	//�̢�							Boundary Process					  �̢�
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�

	int ln;									// local number
	double mv, bv;							// mv = mA[][], bv = values on boundary


	// Fill-in here.
	for (int j = 0; j < nbT_d; j++)
	{
		ln = indexP[indexB_d[j][0]][indexB_d[j][1]];
		bv = g(coordN[ln]);
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
		cv += pow(u(cent) - uh_cent, 2);
	}
	error = cv*pow(h, 2);
	error = sqrt(error);

	// save as m file
	if (choice == 1)
	{
		FILE *fp = fopen(ch, "w");

		fprintf(fp, "clear all\nclose all\nclc\n");

		fprintf(fp, "x = %f:%f:%f;\n",ax,h,bx);
		fprintf(fp, "y = %f:%f:%f;\n",ay,h,by);

		fprintf(fp, "Z = [");
		for (int i = 0; i < nsN-1; i++)
		{
			for (int j = 0; j < nsN; j++){fprintf(fp, "%f,", vCP(nsN*i + j));}
			fprintf(fp, ";");
		}
		for (int j = 0; j < nsN-1; j++)
		{
			fprintf(fp, "%f,", vCP(nsN*(nsN-1) + j));
		}
		fprintf(fp, "%f", vCP((nsN+1)*(nsN-1)));
		fprintf(fp, "];\n");

		

		fprintf(fp, "figure(1)\n");
		fprintf(fp, "meshc(x,y,Z)\n");
		
		fprintf(fp, "grid on\n");
		fprintf(fp, "title('%d level')\n", level);

		fclose(fp);
	}

	return error;
}