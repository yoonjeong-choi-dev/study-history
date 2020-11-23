#ifndef ____fem_problems_2008
#define ____fem_problems_2008

#include "standard_2015.h"
#include "fem_variables_2015.h"

class FEM_PROBLEM {
public:
	int dim;
	int np, nv;
	int nInterface;
	int nFunction;
	int nBasis;
	double mu;							// Elliptic part의 계수를 의미: 상수일 경우만 먼저 지정하는 것이 의미가 있다. 함수이면 항상호출해야 함
	double k;
	double wave_;	//maxwell constant wave	
	double eps_;	//maxwell constant epsilon
	double eps_m;	//maxwell constant epsilon
	double eps_p;	//maxwell constant epsilon
	double d0;

	double q;		//electrionic charge
	double ni;		//intrinsic concentration
	double ni_hat;		//intrinsic concentration
	double Vth;		//thermal voltage
	
	double kappa_ficititious;	//fictitious kappa constant wave
	double r0, rB, r1, r2, r3, r4;
	double x2, y2, x1, y1, x3, x4, y3, y4;
	double mum, mup, mug;
	double lambdam, lambdap, nu;
	double jump;
	double line;
	double radius;
	double theta;
	double slope;
	double perturbed;
	double y_intercept, x_intercept;

	double phi;
	double K_p;							// Permeability
	double eps;
	double rho_n;
	double rho_w;
	double mu_w;
	double mu_n;
	double mu_p;
	double Dn;
	double Dp;
	double phi_w;
	double phi_n;
	double mu0;
	double M;
	double c_in;
	double snr;
	double s_critical;

	double Cp;
	double Cm;
	double Cp_hat;
	double Cm_hat;
	double Vp;
	double Vm;
	double NA;
	double ND;
	double Tau_n;
	double Tau_p; 
	double Cn_over_q_square;
	double Cp_over_q_square;
	double En_crit;
	double Ep_crit;
	double alpha_n;
	double alpha_p;
	double tau;

	int time_step;
	double time_real;
	double ini_time, ter_time;

	double alpha, beta;
	double a,b,alpha_0;
	double beta_x, beta_y;
	double varAlpha; //this is for the problem in the case of variable alpha
	double A2,B2; // this is for the ellipsolidal interface coefficient
	double gap;

	double c0;  //for the solution with the peanut shape inteface
	double c1;  //for the solution with the peanut shape inteface

	double V0;

	double alpha_t;
	double alpha_l;
	double cl;
	double cr;
	double D_m;
	double pd;
	double pd_in;
	FVector_double	vDirection;
	FVector_double	vCenter;
	FVector_double	vOp;
	FMatrix_double	RX;
	FVector_int	boundary_inf_n;
	FVector_int	boundary_inf_w;
	FVector_double	vMum;

	FVector_double	vFirst_intersec_point, vSecond_intersec_point;
	enum interfaces { CIRCLE = 10, ELIPSE = 11, LINE = 12 };

public:

	double		(*Interfaces[10])	(FVector_double& vRealP); 

	virtual void		input			() {}
	virtual void		initialize		(FEM_VARIABLES::ENTIRE& __) {}
	virtual double		coef_mu(FVector_double& p, FVector_double& ps) { return 0; }
	virtual double		coef_mu(FVector_double& p, FVector_double& ps, double t) { return 0; }
	virtual double		coef_mu(FVector_double& p, int io) { return 0; }
	virtual double		coef_mu(FVector_double& p, int io, double t) { return 0; }
	virtual double		coef_mu(FVector_double& p) { return 0; }
	virtual double		coef_mu(FVector_double& p, double t) { return 0; }
	virtual double		coef_k(FVector_double& p) { return 0; }
	virtual void		coef_beta(FVector_double& p, FVector_double& vBeta) { }
	virtual void		coef_Dmu(FVector_double& p, FVector_double& vDmu) {}
	virtual double		coef_lambda(FVector_double& p) { return 0; }
	virtual double		coef_lambda(FVector_double& p, FVector_double& ps) { return 0; }
	virtual double		coef_lambda(FVector_double& p, double io) { return 0; }
	virtual void		coef_mMu(FVector_double& p, FMatrix_double& mMu) {}
	virtual void		coef_cDMu		(FVector_double& p, FCube_double& cDMu) {}
	
	virtual double		P				(FVector_double& p, double t) { return 0; }
	virtual double		P				(FVector_double& p, FVector_double& ps) { return 0; }
	virtual double		P				(FVector_double& p, FVector_double& ps, double t) { return 0; }
	virtual double		P				(FVector_double& p) { return 0; }
	virtual double		P_Jump			(FVector_double& p) { return 0; }
	virtual void		DP(FVector_double& p, FVector_double& vDP)	{}
	virtual void		DP(FVector_double& p, FVector_double& vDP, double t) {}
	virtual void		DP(FVector_double& p, FMatrix_double& mDPs) {}
	virtual void		DP(FVector_double& p, FMatrix_double& mDPs, double t) {}
	virtual double		DP_Jump			(FVector_double& p, FVector_double& vN)	{ return 0; }
	virtual double		Flux_Jump(FVector_double& p, FVector_double& vN)	{ return 0; }
	virtual double		Robin_Boundary (FVector_double& p, FVector_double& vN)	{ return 0; }
	virtual double		g				(FVector_double& p, FVector_double& vN)	{ return 0; }
	virtual double		g(FVector_double& p, FVector_double& vN, FVector_double& ps)	{ return 0; }
	virtual double		Flux_Jump(FVector_double& p, FVector_double& vN, double t) { return 0; }
	virtual double		P_Flux_Jump		(FVector_double& p, FVector_double& vN)	{ return 0; }
	virtual void		DDP				(FVector_double& p, FMatrix_double& mDDP) {}
	virtual void		V				(FVector_double& p, FMatrix_double& mVs) {}
	virtual void		V				(FVector_double& p, FVector_double& vV)	{}
	virtual void		GRADV(FVector_double& p, FMatrix_double& GRAD) {}
	virtual void		GRADV(FVector_double& p, FCube_double& cGRAD) {} 
	virtual void		DV(FVector_double& p, FCube_double& cDVs) {}
	virtual void		DV(FVector_double& p, FMatrix_double& mDV) {}
	virtual void		DDV(FVector_double& p, FCube4_double& c4DDVs) {}
	virtual void		DDV(FVector_double& p, FCube_double& cDDV) {}
	virtual void		V_Flux_Jump		(FVector_double& p, FVector_double& vN, FVector_double& vFlux)	{}
	virtual void		V_Flux_T_Jump	(FVector_double& p, FVector_double& vN, FVector_double& vFlux)	{} 
	virtual void		V_STRESS_Jump	(FVector_double& p, FVector_double& vN, FVector_double& vFlux)	{} 
	virtual double		curlV_2D		(FVector_double& p) { return 0; }
	virtual void		curlV_2D_both	(FVector_double& p, FVector_double& vCurl) {}
	virtual double		div				(FVector_double& p) { return 0; }
	virtual void		div				(FVector_double& p, FVector_double& div) {}
	virtual double		F(FVector_double& p, FVector_double& fs) { return 0; }
	virtual double		F(FVector_double& p, FMatrix_double& fs) { return 0; }
	virtual double		F(FVector_double& p, FVector_double& fs, double t) { return 0; }
	virtual double		F(FVector_double& p) { return 0; }
	virtual double		F(FVector_double& p, double t) { return 0; }

	virtual double		Saturation_Point_Jump			(FVector_double& Sw, FVector_double& pre, int e, FVector_double & vRealP) { return 0; }
	virtual double		Pressure_Point_Jump				(FVector_double& Sw, FVector_double& pre, int e, FVector_double & vRealP) { return 0; }
	virtual void		Saturation_Flux_Jump			(FVector_double& Sw, FVector_double& pre, int e, FVector_double & vRealP, FVector_double & vJump) {}
	virtual void		Pressure_Flux_Jump				(FVector_double& Sw, FVector_double& pre, int e, FVector_double & vRealP, FVector_double & vJump) {}
	virtual double		Jump_Saturation_In				(double s) { return 0; }

	virtual void		VF				(FVector_double& p, FMatrix_double	& vF)	{}
	virtual void		VF				(FVector_double& p, FVector_double	& vF)	{}
	virtual void		VF				(FVector_double& p, FCube_double	& vF)	{}
	virtual double		Interface(double r, double t) { return 0; }
	virtual double		Interface(double r) { return 0; }
	virtual double		Interface(FVector_double& p, double t) { return 0; }
	virtual double		Interface(FVector_double& p) { return 0; }
	virtual double		DOPING(FVector_double& p) { return 0; }
	virtual double		DOPING_HAT(FVector_double& p) { return 0; }

	virtual double		Interface0(FVector_double& p) { return 0; }
	virtual double		Interface1(FVector_double& p) { return 0; }
	virtual double		Interface2(FVector_double& p) { return 0; }
	virtual double		Interface3(FVector_double& p) { return 0; }

	virtual double		InterfaceGrad(FVector_double& p, FVector_double& df) { return 0; }
	
	virtual double		iniP(FVector_double& p) { return 0; }
	virtual void		iniP(FVector_double& p, FVector_double& ps) {}
	virtual double		endP(FVector_double& p) { return 0; }
	virtual void		endP(FVector_double& p, FVector_double& ps) {}
	virtual double		Boundary(FVector_double& p) { return 0; }
	virtual double		div_2D(FVector_double& p) { return 0; }
	virtual void        normal(FVector_double&, FVector_double&) {}
	virtual double		coef_alpha(FVector_double&) { return 0; }
	virtual double		value_varAlpha(FVector_double& p) { return 0; }
	virtual double		value_varAlpha(FVector_double& p, int t) { return 0; }

	virtual void		R(FVector_double& p, FVector_double& vR)	{}
	virtual double		mu_				(double c) { return 0; }
	virtual double		k_n				(double s){	return	0;}
	virtual double		k_w				(double s){	return	0;}
	virtual double		dk_n			(double s){	return	0;}
	virtual double		dk_w			(double s){	return	0;}
	virtual double		Lamda			(double s){	return	0;}
	virtual double		Lamdad			(double s){	return	0;}
	virtual double		Lamda_n			(double s){	return	0;}
	virtual double		Lamda_w			(double s){	return	0;}
	virtual double		Lamdad_n		(double s){	return	0;}
	virtual double		Lamdad_w		(double s){	return	0;}
	
	virtual double		k_n				(FVector_double &p, double s){	return	0;}
	virtual double		k_w				(FVector_double &p,double s){	return	0;}
	virtual double		dk_n			(FVector_double &p,double s){	return	0;}
	virtual double		dk_w			(FVector_double &p,double s){	return	0;}
	virtual double		Lamda			(FVector_double &p,double s){	return	0;}
	virtual double		Lamdad			(FVector_double &p,double s){	return	0;}
	virtual double		Lamda_n			(FVector_double &p,double s){	return	0;}
	virtual double		Lamda_w			(FVector_double &p,double s){	return	0;}
	virtual double		Lamdad_n		(FVector_double &p,double s){	return	0;}
	virtual double		Lamdad_w		(FVector_double &p,double s){	return	0;}

	virtual double		k_n				(int io, double s){ return	0; }
	virtual double		k_w				(int io, double s){ return	0; }
	virtual double		dk_n			(int io, double s){ return	0; }
	virtual double		dk_w			(int io, double s){ return	0; }
	virtual double		Lamda			(int io, double s){ return	0; }
	virtual double		Lamdad			(int io, double s){ return	0; }
	virtual double		Lamda_n			(int io, double s){ return	0; }
	virtual double		Lamda_w			(int io, double s){ return	0; }
	virtual double		Lamdad_n		(int io, double s){ return	0; }
	virtual double		Lamdad_w		(int io, double s){ return	0; }
	
	virtual double		flux_n			(FVector_double& p){ return	0;}
	virtual double		flux_w			(FVector_double& p){ return	0;}
	virtual double		flux_t			(FVector_double& p){ return	0;}

	virtual double		flux_p			(FVector_double& p){ return	0; }
	virtual double		flux_c			(FVector_double& p){ return	0; }
	
	virtual double		saturation		(FVector_double& p) { return 0; }
	virtual double		pressure		(FVector_double& p) { return 0; }
	virtual double		sn				(FVector_double& p) { return 0; }
	virtual double		pw				(FVector_double& p) { return 0; }
	virtual double		sw				(FVector_double& p) { return 0; }
	virtual double		pn				(FVector_double& p) { return 0; }
	virtual double		fw				(double s) { return 0; }
	virtual double		fn				(double s) { return 0; } 
	virtual double		Dfw				(double s) {	return 0;	}

	virtual double		EP				(FVector_double& p) { return 0; }
	virtual double		PN				(FVector_double& p) { return 0; }
	virtual double		PP				(FVector_double& p) { return 0; }
	virtual double		N_HAT			(FVector_double& p) { return 0; }
	virtual double		P_HAT			(FVector_double& p) { return 0; }

	virtual double		qt				(double s, FVector_double& p) { return 0; }
	virtual double		qn				(double s, FVector_double& p) { return 0; }
	virtual double		qw				(double s, FVector_double& p) { return 0; }

	virtual double		gp				(double s, FVector_double& p) { return 0; }
	virtual double		sw				(double s, FVector_double& p) { return 0; }
	virtual double		sn				(double s, FVector_double& p) { return 0; }

	virtual double		gp				(double s, FVector_double& p, FVector_double& vgp) { return 0; }
	virtual double		sw				(double s, FVector_double& sw, FVector_double & vsw) { return 0; }
	virtual double		sn				(double s, FVector_double& sn, FVector_double& vsn) { return 0; }

	virtual void		tv				(double s, FVector_double& p, FVector_double& vDV) {}

	virtual void		Dsw				(double s, FVector_double& p, FVector_double& vDPs) {}
	virtual void		DDsw			(double s, FVector_double& p, FMatrix_double& mDP) {}
	virtual double		Dtsw			(double s, FVector_double& p) { return 0; }
	virtual void		Dgp				(double s, FVector_double& p, FVector_double& vDP)	{}
	virtual void		Dtv				(double s, FVector_double& p, FMatrix_double& mDV) {}
	virtual void		DDgp			(double s, FVector_double& p, FMatrix_double& mDP)	{}

	virtual void		Dsw				(double s, FVector_double& p, FMatrix_double& mDPs) {}
	virtual void		DDsw			(double s, FVector_double& p, FCube_double& CDP) {}
	virtual double		Dtsw			(double s, FVector_double& p, FVector_double & vswt) { return 0; }
	virtual void		Dgp				(double s, FVector_double& p, FMatrix_double& mDP)	{}
	virtual void		DDgp			(double s, FVector_double& p, FCube_double& cDDP)	{} 

	virtual void		DInterface		(FVector_double& p, FVector_double& vDI)	{}
	virtual void		DDInterface		(FVector_double& p, FMatrix_double& mDDI)	{}
	
	virtual double		fw				(FVector_double& p,double s) { return 0; }
	virtual double		fn				(FVector_double& p,double s) { return 0; }

	virtual double		fw				(int io, double s) { return 0; }
	virtual double		fn				(int io, double s) { return 0; }
	virtual double		dfn				(int io, double s) { return 0; }
	virtual double		reduced_fn		(int io, double s) { return 0; }
	virtual double		pc				(double s) { return 0; }
	virtual double		dpc				(double s) { return 0; }
	virtual double		ddpc			(double s) { return 0; }
	virtual double		pc_in_inv		(double s) { return 0; }
	
	virtual double		pc				(FVector_double& p,double s) { return 0; }
	virtual double		dpc				(FVector_double& p,double s) { return 0; }
	virtual double		ddpc			(FVector_double& p,double s) { return 0; }

	virtual double		pc				(int io, double s) { return 0; }
	virtual double		dpc				(int io, double s) { return 0; }
	virtual double		ddpc			(int io, double s) { return 0; }
	
	virtual double		K_p_			(FVector_double& p) { return 0; }
	virtual double		K_p_			(FVector_double& p, FVector_double & vp) { return 0; }
	virtual double		K_p_			(int io, FVector_double & vp) { return 0; }
	virtual double		K_p_			(int io) { return 0; }
	virtual double		Phi_			(FVector_double& p) { return 0; }
	virtual double		Phi_			(int io)  { return 0; }
	virtual double		Initial_Val		(FVector_double& p) { return 0; }
	virtual double		Initial_PHI		(FVector_double& p) { return 0; }

	virtual double		dirichlet_t		(FVector_double& p) { return 0; }
	virtual double		dirichlet_w		(FVector_double& p) { return 0; }
	virtual double		dirichlet_n		(FVector_double& p) { return 0; }

	virtual double		dirichlet_p		(FVector_double& p) { return 0; }
	virtual double		gamma			(double s) { return 0; }
	virtual double		dgamma			(double s) { return 0; }

	virtual double		gamma(int io, double s) { return 0; }
	virtual double		dgamma(int io, double s) { return 0; }

	virtual double		beta_			(FVector_double & p){ return 0; }
	virtual void		Dbeta_			(FVector_double & p, FVector_double & vDB){}
	virtual void		DDbeta_			(FVector_double & p, FMatrix_double & mDB){}

	virtual int			boundary_indicator_t	(FVector_double& p) { return 0; }
	virtual int			boundary_indicator_w	(FVector_double& p) { return 0; }
	virtual int			boundary_indicator_n	(FVector_double& p) { return 0; }

	virtual int			boundary_indicator		(FVector_double& p) { return 0; }

	virtual int			boundary_indicator_p(FVector_double& p) { return 0; }
	virtual int			boundary_indicator_c(FVector_double& p) { return 0; }


} *_problem;

class FEM_PROBLEMS {
public:
	class ELLIPTIC {
	public:
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		//============================================================================
		//                                ID
		//============================================================================
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		class ID {
		public:
			enum {P_ELEMENTARY, P_SINCOS, P_X, P_IIM_CONST_CIRCLE, P_IIM_LINE, P_IIM_VARIOUS, P_IIM_J12_SINCOS};
		};
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		//============================================================================
		//                           ELLIPTIC_ELEMENTARINESS
		//============================================================================
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		class P_ELEMENTARY: public FEM_PROBLEM {
		public:
			void	initialize	(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(0.,0., 1., 1.);
			}

			double	P			(FVector_double& p) {
				double x=p[0], y=p[1];
				return x*y*(1-x)*(1-y);	
			}

			void	DP			(FVector_double& p, FVector_double& vDP) {
				double x=p[0], y=p[1];
				vDP.setAll(y*(1-y)*(1-2*x), x*(1-x)*(1-2*y));
			}
			
			void	DDP			(FVector_double& p, FMatrix_double& mDDP) {
				double x=p[0], y=p[1];
				mDDP.setAll(2*y*(y-1), (-1+2*x)*(-1+2*y), (-1+2*x)*(-1+2*y), 2*x*(x-1));
			}

			void	coef_mMu	(FVector_double& p, FMatrix_double& mMu) {
				double x=p[0], y=p[1];
				mMu.setAll(1., 0., 0., 1.);
			}

			void	coef_cDMu	(FVector_double& p, FCube_double& cDMu) {
				double x=p[0], y=p[1];
				cDMu.setAll(0., 0., 0., 0., 0., 0., 0., 0.);
			}

			double	F			(FVector_double& p) {
				double x=p[0], y=p[1];
				return 2*(x*(1-x) + y*(1-y));	
			}
			
			// 자동결정 함수들
			void	V			(FVector_double& p, FVector_double& vV) {
				// vV = -μ▽p
				static FVector_double vDP(dim);
				static FMatrix_double mMu(dim,dim);

				coef_mMu(p, mMu);
				DP(p, vDP);
				vV.op("=", -1., mMu, vDP);
			}

			void	DV			(FVector_double& p, FMatrix_double& mDV) {
				// mDV = ▽(-μ▽p) = -(▽μ▽p + μ▽▽p)   μ:matrix  p:vector
				// 참고: div(mDV) = div(-μ▽p) = tr(-▽(μ▽p)) = (tr(-▽μ▽p) - tr(μ▽▽p)) = (tr(-▽μ▽p) - μ:▽▽p)
				static FVector_double	vDP(dim);
				static FMatrix_double	mMu(dim,dim), mDDP(dim,dim), mIm1(dim,dim), mIm2(dim,dim);
				static FCube_double		cDMu(dim,dim,dim);

				coef_mMu(p, mMu);
				coef_cDMu(p, cDMu);
				DP(p, vDP);
				DDP(p, mDDP);

				// 첫번째 식을 기반으로 계산한다.
				mIm1.op("=", "kfcfv", 1., cDMu, vDP);
				mIm2.op("=", mMu, mDDP);
				mDV.op("=", "kfm+kfm", -1., mIm1, -1., mIm2); 
			}
		

		};
		class P_ELEMENTARY_3D : public FEM_PROBLEM {
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 3;
				RX = __.RX.make(__.dim, __.dim).setAll(0., 0.,0., 1., 1., 1.);
			}

			double	P(FVector_double& p) {
				double x = p[0], y = p[1], z=p[2];
				return x*y*(1 - x)*(1 - y)*z*(1-z);
			}

			void	DP(FVector_double& p, FVector_double& vDP) {
				double x = p[0], y = p[1], z=p[2];
				vDP.setAll(y*(1 - y)*(1 - 2 * x)*z*(1 - z), x*(1 - x)*(1 - 2 * y)*z*(1 - z), x*y*(1 - x)*(1 - y)*(1-2*z));
			}

			void	DDP(FVector_double& p, FMatrix_double& mDDP) {
				double x = p[0], y = p[1], z = p[2];
				mDDP[0][0] = -2 * y*(1 - y)*z*(1 - z);
				mDDP[1][1] = -2 * x*(1 - x)*z*(1 - z);
				mDDP[2][2] = -2 * y*(1 - y)*x*(1 - x);

			}
			void	coef_mMu(FVector_double& p, FMatrix_double& mMu) {
				double x = p[0], y = p[1];
				mMu[0][0] = 1;
				mMu[1][1] = 1;
				mMu[2][2] = 1;
			}

			void	coef_cDMu(FVector_double& p, FCube_double& cDMu) {
				double x = p[0], y = p[1];
				cDMu.setAll(0., 0., 0., 0., 0., 0., 0., 0.);
			}

			double	F(FVector_double& p) {
				double x = p[0], y = p[1], z=p[2];
				return 2 * (x*(1 - x)*y*(1-y) + y*(1 - y)*z*(1-z)+z*(1-z)*x*(1-x) );
			}

			// 자동결정 함수들
			void	V(FVector_double& p, FVector_double& vV) {
				// vV = -μ▽p
				static FVector_double vDP(dim);
				static FMatrix_double mMu(dim, dim);

				coef_mMu(p, mMu);
				DP(p, vDP);
				vV.op("=", -1., mMu, vDP);
			}

			void	DV(FVector_double& p, FMatrix_double& mDV) {
				// mDV = ▽(-μ▽p) = -(▽μ▽p + μ▽▽p)   μ:matrix  p:vector
				// 참고: div(mDV) = div(-μ▽p) = tr(-▽(μ▽p)) = (tr(-▽μ▽p) - tr(μ▽▽p)) = (tr(-▽μ▽p) - μ:▽▽p)
				static FVector_double	vDP(dim);
				static FMatrix_double	mMu(dim, dim), mDDP(dim, dim), mIm1(dim, dim), mIm2(dim, dim);
				static FCube_double		cDMu(dim, dim, dim);

				coef_mMu(p, mMu);
				coef_cDMu(p, cDMu);
				DP(p, vDP);
				DDP(p, mDDP);

				// 첫번째 식을 기반으로 계산한다.
				mIm1.op("=", "kfcfv", 1., cDMu, vDP);
				mIm2.op("=", mMu, mDDP);
				mDV.op("=", "kfm+kfm", -1., mIm1, -1., mIm2);
			}

		};
		class P_ELEMENTARY_U: public FEM_PROBLEM { // Governing Equation:  -div(μ▽p) + p = f
		public:
			void	initialize	(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(0.,0., 1.,1.);
			}

			double	P			(FVector_double& p) {
				double x=p[0], y=p[1];
				return x*y*(1-x)*(1-y);	
			}

			void	DP			(FVector_double& p, FVector_double& vDP) {
				double x=p[0], y=p[1];
				vDP.setAll(y*(1-y)*(1-2*x), x*(1-x)*(1-2*y));
			}
			
			void	DDP			(FVector_double& p, FMatrix_double& mDDP) {
				double x=p[0], y=p[1];
				mDDP.setAll(2*y*(y-1), (-1+2*x)*(-1+2*y), (-1+2*x)*(-1+2*y), 2*x*(x-1));
			}

			void	coef_mMu	(FVector_double& p, FMatrix_double& mMu) {
				double x=p[0], y=p[1];
				mMu.setAll(1., 0., 0., 1.);
			}

			void	coef_cDMu	(FVector_double& p, FCube_double& cDMu) {
				double x=p[0], y=p[1];
				cDMu.setAll(0., 0., 0., 0., 0., 0., 0., 0.);
			}

			double	F			(FVector_double& p) {
				double x=p[0], y=p[1];
				return 2*(x*(1-x) + y*(1-y)) + x*y*(1-x)*(1-y);	
			}
			
			// 자동결정 함수들
			void	V			(FVector_double& p, FVector_double& vV) {
				// vV = -μ▽p
				static FVector_double vDP(dim);
				static FMatrix_double mMu(dim,dim);

				coef_mMu(p, mMu);
				DP(p, vDP);
				vV.op("=", -1., mMu, vDP);
			}

			void	DV			(FVector_double& p, FMatrix_double& mDV) {
				// mDV = ▽(-μ▽p) = -(▽μ▽p + μ▽▽p)   μ:matrix  p:vector
				// 참고: div(mDV) = div(-μ▽p) = tr(-▽(μ▽p)) = (tr(-▽μ▽p) - tr(μ▽▽p)) = (tr(-▽μ▽p) - μ:▽▽p)
				static FVector_double	vDP(dim);
				static FMatrix_double	mMu(dim,dim), mDDP(dim,dim), mIm1(dim,dim), mIm2(dim,dim);
				static FCube_double		cDMu(dim,dim,dim);

				coef_mMu(p, mMu);
				coef_cDMu(p, cDMu);
				DP(p, vDP);
				DDP(p, mDDP);

				// 첫번째 식을 기반으로 계산한다.
				mIm1.op("=", "kfcfv", 1., cDMu, vDP);
				mIm2.op("=", mMu, mDDP);
				mDV.op("=", "kfm+kfm", -1., mIm1, -1., mIm2); 
			}

		};
		class SMOOTH_SOL_2: public FEM_PROBLEM { // Governing Equation:  -div(μ▽p) = f
		public:
			void initialize	(FEM_VARIABLES::ENTIRE& __) 
			{
				mu = 1.;
				dim=__.dim = 2;
				RX=__.RX.make(__.dim, __.dim).setAll(0.,0., 1.,1.);
			}
			int	boundary_indicator	(FVector_double	& p) { 
				double x = p[0];
				double y = p[1];
				// ret=1. normal. ret=0. dirichlet.
				double rt = 1;
				if (x == 1.)
					rt = 0;
			//	rt = 0.;
				return rt; 
			}
			double	P	(FVector_double& p) 
			{
				double x=p[0], y=p[1];
				return (x+1.)*(x+1.)*(y+1.)*(y+1.);
			}
			void	DP	(FVector_double& p, FVector_double& dp) 
			{	 
				double x=p[0], y=p[1];
				dp.setAll(2.*(x+1.)*(y+1.)*(y+1.), 2.*(x+1.)*(x+1.)*(y+1.) );
			}

			void DDP (FVector_double & p, FMatrix_double & ddp)
			{
				double x=p[0], y=p[1];
				ddp[0].setAll(2.*(y+1)*(y+1),4*(x+1)*(y+1));
				ddp[1].setAll(4*(x+1)*(y+1),2.*(x+1)*(x+1));
			}
			
			void	coef_mMu	(FVector_double& p, FMatrix_double& mMu) 
			{
				double x=p[0], y=p[1];
				mMu.setAll(1., 0., 0., 1.);
			}

			void	coef_cDMu	(FVector_double& p, FCube_double& cDMu) {
				double x=p[0], y=p[1];
				cDMu.setAll(0., 0., 0., 0., 0., 0., 0., 0.);
			}

			void	V			(FVector_double& p, FVector_double& vV) 
			{
			// vV = -μ▽p
				static FVector_double vDP(dim);
				static FMatrix_double mMu(dim,dim);
				coef_mMu(p, mMu);
				DP(p, vDP);
				vV.op("=", -1., mMu, vDP);
			}
			void	DV			(FVector_double& p, FMatrix_double& mDV) 
			{
				// mDV = ▽(-μ▽p) = -(▽μ▽p + μ▽▽p)   μ:matrix  p:vector
				// 참고: div(mDV) = div(-μ▽p) = tr(-▽(μ▽p)) = (tr(-▽μ▽p) - tr(μ▽▽p)) = (tr(-▽μ▽p) - μ:▽▽p)
				static FVector_double	vDP(dim);
				static FMatrix_double	mMu(dim,dim), mDDP(dim,dim), mIm1(dim,dim), mIm2(dim,dim);
				static FCube_double		cDMu(dim,dim,dim);
				coef_mMu(p, mMu);
				coef_cDMu(p, cDMu);
				DP(p, vDP);
				DDP(p, mDDP);
				// 첫번째 식을 기반으로 계산한다.
				mIm1.op("=", "kfcfv", 1., cDMu, vDP);
				mIm2.op("=", mMu, mDDP);
				mDV.op("=", "kfm+kfm", -1., mIm1, -1., mIm2); 
			}
			double	F	(FVector_double& p) 
			{

				double x=p[0], y=p[1];
				FMatrix_double ddp(2,2);	FVector_double dp(2);	FVector_double vR(2);
				double ret_;
				DDP (p, ddp);	DP(p,dp);	//R(p,vR);
				ret_=-mu*ddp[0][0]-mu*ddp[1][1];
				ddp.release();	dp.release();	vR.release();
				return ret_;
			}
		};
		class P_SIN_TEST: public FEM_PROBLEM { // Governing Equation:  -div(μ▽p) + p = f
		public:
			void initialize (FEM_VARIABLES::ENTIRE& __) 
			{
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(0.,0., 1.,1.);
			}
			double P (FVector_double& p) 
			{
				double x = p[0], y=p[1];
				return sin(2*CV.PI*x)*sin(2*CV.PI*y);
			}
			void DP (FVector_double &p, FVector_double &dp) 
			{
				double x=p[0], y=p[1];
				dp.setAll(2*CV.PI*cos(2*CV.PI*x)*sin(2*CV.PI*y), 2*CV.PI*cos(2*CV.PI*y)*sin(2*CV.PI*x));
			}
			void	DDP			(FVector_double& p, FMatrix_double& mDDP) {
				double x=p[0], y=p[1];
				mDDP.setAll(-4*CV.PI*CV.PI*sin(2*CV.PI*x)*sin(2*CV.PI*y), 4*CV.PI*CV.PI*cos(2*CV.PI*x)*cos(2*CV.PI*y), 4*CV.PI*CV.PI*cos(2*CV.PI*y)*cos(2*CV.PI*x), -4*CV.PI*CV.PI*sin(2*CV.PI*y)*sin(2*CV.PI*x));
			}
			double F (FVector_double& p) 
			{
				double x=p[0], y=p[1];
				return (8*CV.PI*CV.PI+1)*sin(2*CV.PI*x)*sin(2*CV.PI*y);
			}
			void	coef_mMu	(FVector_double& p, FMatrix_double& mMu) {
				double x=p[0], y=p[1];
				mMu.setAll(1., 0., 0., 1.);
			}

			void	coef_cDMu	(FVector_double& p, FCube_double& cDMu) {
				double x=p[0], y=p[1];
				cDMu.setAll(0., 0., 0., 0., 0., 0., 0., 0.);
			}
			void	V			(FVector_double& p, FVector_double& vV) {
				// vV = -μ▽p
				static FVector_double vDP(dim);

				DP(p, vDP);
				vV.op("=", -1., vDP);
			}

			void	DV			(FVector_double& p, FMatrix_double& mDV) {
				// mDV = ▽(-μ▽p) = -(▽μ▽p + μ▽▽p)   μ:matrix  p:vector
				// 참고: div(mDV) = div(-μ▽p) = tr(-▽(μ▽p)) = (tr(-▽μ▽p) - tr(μ▽▽p)) = (tr(-▽μ▽p) - μ:▽▽p)
				static FVector_double	vDP(dim);
				static FMatrix_double	mMu(dim,dim), mDDP(dim,dim), mIm1(dim,dim), mIm2(dim,dim);
				static FCube_double		cDMu(dim,dim,dim);

				coef_mMu(p, mMu);
				coef_cDMu(p, cDMu);
				DP(p, vDP);
				DDP(p, mDDP);

				// 첫번째 식을 기반으로 계산한다.
				mIm1.op("=", "kfcfv", 1., cDMu, vDP);
				mIm2.op("=", mMu, mDDP);
				mDV.op("=", "kfm+kfm", -1., mIm1, -1., mIm2); 
			}
		};
		class P_TEST2: public FEM_PROBLEM { // Governing Equation:  -div(μ▽p) = f
		public:
			void initialize (FEM_VARIABLES::ENTIRE& __) 
			{
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(0.,0., 1.,1.);
			}
			double P (FVector_double& p) 
			{
				double x = p[0], y=p[1];
				return sin(2*CV.PI*x)*sin(2*CV.PI*y);
			}
			void DP (FVector_double &p, FVector_double &dp) 
			{
				double x=p[0], y=p[1];
				dp.setAll(2*CV.PI*cos(2*CV.PI*x)*sin(2*CV.PI*y), 2*CV.PI*cos(2*CV.PI*y)*sin(2*CV.PI*x));
			}
			void	DDP			(FVector_double& p, FMatrix_double& mDDP) {
				double x=p[0], y=p[1];
				mDDP.setAll(-4*CV.PI*CV.PI*sin(2*CV.PI*x)*sin(2*CV.PI*y), 4*CV.PI*CV.PI*cos(2*CV.PI*x)*cos(2*CV.PI*y), 4*CV.PI*CV.PI*cos(2*CV.PI*y)*cos(2*CV.PI*x), -4*CV.PI*CV.PI*sin(2*CV.PI*y)*sin(2*CV.PI*x));
			}
			double F (FVector_double& p) 
			{
				double x=p[0], y=p[1];
				return 8*CV.PI*CV.PI*sin(2*CV.PI*x)*sin(2*CV.PI*y);
			}
			void	coef_mMu	(FVector_double& p, FMatrix_double& mMu) {
				double x=p[0], y=p[1];
				mMu.setAll(1., 0., 0., 1.);
			}

			void	coef_cDMu	(FVector_double& p, FCube_double& cDMu) {
				double x=p[0], y=p[1];
				cDMu.setAll(0., 0., 0., 0., 0., 0., 0., 0.);
			}
			void	V			(FVector_double& p, FVector_double& vV) {
				// vV = -μ▽p
				static FVector_double vDP(dim);

				DP(p, vDP);
				vV.op("=", -1., vDP);
			}

			void	DV			(FVector_double& p, FMatrix_double& mDV) {
				// mDV = ▽(-μ▽p) = -(▽μ▽p + μ▽▽p)   μ:matrix  p:vector
				// 참고: div(mDV) = div(-μ▽p) = tr(-▽(μ▽p)) = (tr(-▽μ▽p) - tr(μ▽▽p)) = (tr(-▽μ▽p) - μ:▽▽p)
				static FVector_double	vDP(dim);
				static FMatrix_double	mMu(dim,dim), mDDP(dim,dim), mIm1(dim,dim), mIm2(dim,dim);
				static FCube_double		cDMu(dim,dim,dim);

				coef_mMu(p, mMu);
				coef_cDMu(p, cDMu);
				DP(p, vDP);
				DDP(p, mDDP);

				// 첫번째 식을 기반으로 계산한다.
				mIm1.op("=", "kfcfv", 1., cDMu, vDP);
				mIm2.op("=", mMu, mDDP);
				mDV.op("=", "kfm+kfm", -1., mIm1, -1., mIm2); 
			}
		};
		class P_TEST3: public FEM_PROBLEM { // Governing Equation:  -div(μ▽p) = f
		public:
			void initialize (FEM_VARIABLES::ENTIRE& __) 
			{
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(0.,0., 1.,1.);
			}
			double P (FVector_double& p) 
			{
				double x = p[0], y=p[1];
				return x*x*y*y;
			}
			void DP (FVector_double &p, FVector_double &dp) 
			{
				double x=p[0], y=p[1];
				dp.setAll(2.*x*y*y, 2.*y*x*x);
			}
			void	DDP			(FVector_double& p, FMatrix_double& mDDP) {
				double x=p[0], y=p[1];
				mDDP.setAll(2.*y*y, 4.*x*y, 4.*x*y, 2.*x*x);
			}
			double F (FVector_double& p) 
			{

				double x=p[0], y=p[1];
				return -2.*(y*y+20.*x*y*y+y*y*y+x*x+10.*x*x*x+2.*y*x*x);
			}
			void	coef_mMu	(FVector_double& p, FMatrix_double& mMu) {
				double x=p[0], y=p[1];
				mMu.setAll(1.+10.*x+y, 0., 0., 1.+10.*x+y);
			}

			void	coef_cDMu	(FVector_double& p, FCube_double& cDMu) {
				double x=p[0], y=p[1];
				cDMu.setAll(10., 0., 0., 10., 1., 0., 0., 1.);
			}
			void	V			(FVector_double& p, FVector_double& vV) {
				// vV = -μ▽p
				FVector_double vDP(dim);
				FMatrix_double mMu(dim,dim);
				DP(p, vDP);
				coef_mMu(p,mMu);
				vV.op("=",-1.,mMu,vDP);
				mMu.release(); vDP.release();
			}

			void	DV			(FVector_double& p, FMatrix_double& mDV) {
				// mDV = ▽(-μ▽p) = -(▽μ▽p + μ▽▽p)   μ:matrix  p:vector
				// 참고: div(mDV) = div(-μ▽p) = tr(-▽(μ▽p)) = (tr(-▽μ▽p) - tr(μ▽▽p)) = (tr(-▽μ▽p) - μ:▽▽p)
				FVector_double	vDP(dim);
				FMatrix_double	mMu(dim,dim), mDDP(dim,dim), mIm1(dim,dim), mIm2(dim,dim);
				FCube_double	cDMu(dim,dim,dim);

				coef_mMu(p, mMu);
				coef_cDMu(p, cDMu);
				DP(p, vDP);
				DDP(p, mDDP);
				//cDMu.print();
				// 첫번째 식을 기반으로 계산한다.
				mIm1.op("=", "kfcfv", 1., cDMu, vDP);
				mIm2.op("=", mMu, mDDP);
				mDV.op("=", "kfm+kfm", -1., mIm1, -1., mIm2); 

				vDP.release(); mMu.release(); mDDP.release(); mIm1.release(); mIm2.release(); cDMu.release();
			}
		};
		class P_TEST5: public FEM_PROBLEM { // Governing Equation:  -div(μ▽p) = f
		public:
			void initialize (FEM_VARIABLES::ENTIRE& __) 
			{
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(0.,0., 1.,1.);
			}
			double P (FVector_double& p) 
			{
				double x = p[0], y=p[1];
				return x*(x-1.)*(x-1./2.)*y*(y-1.);
			}
			void DP (FVector_double &p, FVector_double &dp) 
			{
				double x=p[0], y=p[1];
				dp.setAll(y*(y-1.)*(3.*x*(x-1.)+1./2.), x*(x-1.)*(x-1./2.)*(2.*y-1.));
			}
			/*void	DDP			(FVector_double& p, FMatrix_double& mDDP) {
				double x=p[0], y=p[1];
				mDDP.setAll(2.*y*y, 4.*x*y, 4.*x*y, 2.*x*x);
			}*/
			double F (FVector_double& p) 
			{
				double x=p[0], y=p[1];
				return -(2*x*(x-1./2.)*(x-1.)+(6.*x-3.)*y*(y-1));
			}
			void	coef_mMu	(FVector_double& p, FMatrix_double& mMu) {
				double x=p[0], y=p[1];
				mMu.setAll(1., 0., 0., 1.);
			}

			void	coef_cDMu	(FVector_double& p, FCube_double& cDMu) {
				double x=p[0], y=p[1];
				cDMu.setAll(0., 0., 0., 0., 0., 0., 0., 0.);
			}
			void	V			(FVector_double& p, FVector_double& vV) {
				// vV = -μ▽p
				static FVector_double vDP(dim);

				DP(p, vDP);
				vV.op("=", -1., vDP);
			}

			void	DV			(FVector_double& p, FMatrix_double& mDV) {
				// mDV = ▽(-μ▽p) = -(▽μ▽p + μ▽▽p)   μ:matrix  p:vector
				// 참고: div(mDV) = div(-μ▽p) = tr(-▽(μ▽p)) = (tr(-▽μ▽p) - tr(μ▽▽p)) = (tr(-▽μ▽p) - μ:▽▽p)
				static FVector_double	vDP(dim);
				static FMatrix_double	mMu(dim,dim), mDDP(dim,dim), mIm1(dim,dim), mIm2(dim,dim);
				static FCube_double		cDMu(dim,dim,dim);

				coef_mMu(p, mMu);
				coef_cDMu(p, cDMu);
				DP(p, vDP);
				DDP(p, mDDP);

				// 첫번째 식을 기반으로 계산한다.
				mIm1.op("=", "kfcfv", 1., cDMu, vDP);
				mIm2.op("=", mMu, mDDP);
				mDV.op("=", "kfm+kfm", -1., mIm1, -1., mIm2); 
			}

		};	
		class P_WOO: public FEM_PROBLEM { // Governing Equation:  -div(μ▽p) = f
		public:
			void	initialize	(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1.,-1., 1.,1.);
			}

			double	P			(FVector_double& p) {
				double x=p[0], y=p[1];
				return exp(CV.PI*x)*sin(CV.PI*y)+x*x*y*y/2.;
			}

			void	DP			(FVector_double& p, FVector_double& vDP) {
				double x=p[0], y=p[1];
				vDP.setAll(CV.PI*exp(CV.PI*x)*sin(CV.PI*y) + x*y*y, CV.PI*exp(CV.PI*x)*cos(CV.PI*y) + x*x*y);
			}

			void	coef_mMu	(FVector_double& p, FMatrix_double& mMu) {
				double x=p[0], y=p[1];
				mMu.setAll(1., 0., 0., 1.);
			}

			void	coef_cDMu	(FVector_double& p, FCube_double& cDMu) {
				double x=p[0], y=p[1];
				cDMu.setAll(0., 0., 0., 0., 0., 0., 0., 0.);
			}

			double	F			(FVector_double& p) {
				double x=p[0], y=p[1];
				return -(x*x+y*y);
			}
			
			// 자동결정 함수들
			void	V			(FVector_double& p, FVector_double& vV) {
				// vV = -μ▽p
				static FVector_double vDP(dim);
				static FMatrix_double mMu(dim,dim);

				coef_mMu(p, mMu);
				DP(p, vDP);
				vV.op("=", -1., mMu, vDP);
			}

			void	DV			(FVector_double& p, FMatrix_double& mDV) {
				// mDV = ▽(-μ▽p) = -(▽μ▽p + μ▽▽p)   μ:matrix  p:vector
				// 참고: div(mDV) = div(-μ▽p) = tr(-▽(μ▽p)) = (tr(-▽μ▽p) - tr(μ▽▽p)) = (tr(-▽μ▽p) - μ:▽▽p)
				static FVector_double	vDP(dim);
				static FMatrix_double	mMu(dim,dim), mDDP(dim,dim), mIm1(dim,dim), mIm2(dim,dim);
				static FCube_double		cDMu(dim,dim,dim);

				coef_mMu(p, mMu);
				coef_cDMu(p, cDMu);
				DP(p, vDP);
				DDP(p, mDDP);

				// 첫번째 식을 기반으로 계산한다.
				mIm1.op("=", "kfcfv", 1., cDMu, vDP);
				mIm2.op("=", mMu, mDDP);
				mDV.op("=", "kfm+kfm", -1., mIm1, -1., mIm2); 
			}

		};
		class P_TEST_NonZeroBoundary: public FEM_PROBLEM { // Governing Equation:  -div(μ▽p) = f
		public:
			void initialize (FEM_VARIABLES::ENTIRE& __) 
			{
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(0.,0., 1.,1.);
			}
			double P (FVector_double& p) 
			{
				double x = p[0], y=p[1];
				return (1.+x*x)*(1.+y*y);
			}
			void DP (FVector_double &p, FVector_double &dp) 
			{
				double x=p[0], y=p[1];
				dp.setAll(2.*x*(1.+y*y), 2.*y*(1.+x*x));
			}
			void	DDP			(FVector_double& p, FMatrix_double& mDDP) {
				double x=p[0], y=p[1];
				mDDP.setAll(2.*(1.+y*y), 4.*x*y, 4.*x*y, 2.*(1.+x*x));
			}
			double F (FVector_double& p) 
			{

				double x=p[0], y=p[1];
				return -2.*(1.+x*x+1.+y*y);
				
			}
			void	coef_mMu	(FVector_double& p, FMatrix_double& mMu) {
				double x=p[0], y=p[1];
				mMu.setAll(1., 0., 0., 1.);
			}

			void	coef_cDMu	(FVector_double& p, FCube_double& cDMu) {
				double x=p[0], y=p[1];
				cDMu.setAll(0., 0., 0., 0., 0., 0., 0., 0.);
			}
			void	V			(FVector_double& p, FVector_double& vV) {
				// vV = -μ▽p
				FVector_double vDP(dim);
				FMatrix_double mMu(dim,dim);
				DP(p, vDP);
				coef_mMu(p,mMu);
				vV.op("=",-1.,mMu,vDP);
				mMu.release(); vDP.release();
			}

			void	DV			(FVector_double& p, FMatrix_double& mDV) {
				// mDV = ▽(-μ▽p) = -(▽μ▽p + μ▽▽p)   μ:matrix  p:vector
				// 참고: div(mDV) = div(-μ▽p) = tr(-▽(μ▽p)) = (tr(-▽μ▽p) - tr(μ▽▽p)) = (tr(-▽μ▽p) - μ:▽▽p)
				FVector_double	vDP(dim);
				FMatrix_double	mMu(dim,dim), mDDP(dim,dim), mIm1(dim,dim), mIm2(dim,dim);
				FCube_double	cDMu(dim,dim,dim);

				coef_mMu(p, mMu);
				coef_cDMu(p, cDMu);
				DP(p, vDP);
				DDP(p, mDDP);
				//cDMu.print();
				// 첫번째 식을 기반으로 계산한다.
				mIm1.op("=", "kfcfv", 1., cDMu, vDP);
				mIm2.op("=", mMu, mDDP);
				mDV.op("=", "kfm+kfm", -1., mIm1, -1., mIm2); 

				vDP.release(); mMu.release(); mDDP.release(); mIm1.release(); mIm2.release(); cDMu.release();
			}
		};
		class P_ELEMENTARY_reaction_sinh: public FEM_PROBLEM {
		public:
			void	initialize	(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(0.,0., 1., 1.);

				r0 = 0.14241;
				Input("mum", mum);
				Input("mup", mup);

			}
			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				double r = sqrt( (x-0.5)*(x-0.5) + (y-0.5)*(y-0.5));

				return (r - r0);

			}
			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];

				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}
			double	coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) < 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}


			double	P			(FVector_double& p) {
				double x=p[0], y=p[1];
				return x*y*(x-2)*(y-2);	
			}

			double	B			(FVector_double& p) {
				double x=p[0], y=p[1];
				return 1.;	
			}
			void	DP			(FVector_double& p, FVector_double& vDP) {
				double x=p[0], y=p[1];
				vDP.setAll(y*(y-2)*(2*x-2), x*(x-2)*(2*y-2));
			}
			
			void	DDP			(FVector_double& p, FMatrix_double& mDDP) {
				double x=p[0], y=p[1];
				mDDP.setAll(2*y*(y-1), (-1+2*x)*(-1+2*y), (-1+2*x)*(-1+2*y), 2*x*(x-1));
			}

			void	coef_mMu	(FVector_double& p, FMatrix_double& mMu) {
				double x=p[0], y=p[1];
				mMu.setAll(1., 0., 0., 1.);
			}

			void	coef_cDMu	(FVector_double& p, FCube_double& cDMu) {
				double x=p[0], y=p[1];
				cDMu.setAll(0., 0., 0., 0., 0., 0., 0., 0.);
			}

			double	F			(FVector_double& p) {
				double x=p[0], y=p[1];	
				return -2*x*(x-2) - 2*y*(y-2) + sinh(x*y*(x-2)*(y-2));	
			}
			
			// 자동결정 함수들
			void	V			(FVector_double& p, FVector_double& vV) {
				// vV = -μ▽p
				static FVector_double vDP(dim);
				static FMatrix_double mMu(dim,dim);

				coef_mMu(p, mMu);
				DP(p, vDP);
				vV.op("=", -1., mMu, vDP);
			}

			void	DV			(FVector_double& p, FMatrix_double& mDV) {
				// mDV = ▽(-μ▽p) = -(▽μ▽p + μ▽▽p)   μ:matrix  p:vector
				// 참고: div(mDV) = div(-μ▽p) = tr(-▽(μ▽p)) = (tr(-▽μ▽p) - tr(μ▽▽p)) = (tr(-▽μ▽p) - μ:▽▽p)
				static FVector_double	vDP(dim);
				static FMatrix_double	mMu(dim,dim), mDDP(dim,dim), mIm1(dim,dim), mIm2(dim,dim);
				static FCube_double		cDMu(dim,dim,dim);

				coef_mMu(p, mMu);
				coef_cDMu(p, cDMu);
				DP(p, vDP);
				DDP(p, mDDP);

				// 첫번째 식을 기반으로 계산한다.
				mIm1.op("=", "kfcfv", 1., cDMu, vDP);
				mIm2.op("=", mMu, mDDP);
				mDV.op("=", "kfm+kfm", -1., mIm1, -1., mIm2); 
			}
		

		};

		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		//============================================================================
		//                           ELLIPTIC_SINCOS
		//============================================================================
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		class P_SEMPLE : public FEM_PROBLEM {
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(0., 0., 1., 1.);
			}

			void	coef_mMu(FVector_double& p, FMatrix_double& mMu) {
				double x = p[0], y = p[1];
				mMu.setAll(1., 0., 0., 1.);
			}

			double	P(FVector_double& p) {
				double x = p[0], y = p[1];
				return x*x*x*x*x + y*y*y*y*y;
			}

			void	DP(FVector_double& p, FVector_double& vDP) {
				double x = p[0], y = p[1];
				vDP.setAll(5 * x*x*x*x, 5 * y*y*y*y);
			}
			void	DDP(FVector_double& p, FMatrix_double& mDDP){
				double x = p[0], y = p[1];
				mDDP.setAll(20 * x*x*x, 0, 0, 20 * y*y*y);
			}

			double	F(FVector_double& p) {
				double x = p[0], y = p[1];
				return -20 * x*x*x - 20 * y*y*y;
			}
		};
		class P_SEMPLE1 : public FEM_PROBLEM { //-div(▽p) = f
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(0., 0., 1., 1.);
			}
			void	coef_mMu(FVector_double& p, FMatrix_double& mMu) {
				double x = p[0], y = p[1];
				mMu.setAll(1., 0., 0., 1.);
			}

			double	P(FVector_double& p) {
				double x = p[0], y = p[1];
				return x*x*x + y*y*y;
			}

			void	DP(FVector_double& p, FVector_double& vDP) {
				double x = p[0], y = p[1];
				vDP.setAll(3.*x*x, 3.*y*y);
			}
			void	DDP(FVector_double& p, FMatrix_double& mDDP){
				double x = p[0], y = p[1];
				mDDP.setAll(6.*x, 0, 0, 6.*y);
			}

			double	F(FVector_double& p) {
				double x = p[0], y = p[1];
				return -6.*x - 6.*y;
			}
		};
		class P_SEMPLE2 : public FEM_PROBLEM { //-div(▽p) = f
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(0., 0., 1., 1.);
			}
			void	coef_mMu(FVector_double& p, FMatrix_double& mMu) {
				double x = p[0], y = p[1];
				mMu.setAll(1., 0., 0., 1.);
			}

			double	P(FVector_double& p) {
				double x = p[0], y = p[1];
				return x*x*x*(1 - x)*(1 - x) + y*y*y*(1 - y)*(1 - y);
			}

			void	DP(FVector_double& p, FVector_double& vDP) {
				double x = p[0], y = p[1];
				vDP.setAll(3 * x*x*(1 - x)*(1 - x) - 2 * x*x*x*(1 - x), 3 * y*y*(1 - y)*(1 - y) - 2 * y*y*y*(1 - y));
			}
			void	DDP(FVector_double& p, FMatrix_double& mDDP) {
				double x = p[0], y = p[1];
				mDDP.setAll(6 * x*(1 - x)*(1 - x) - 12 * x*x*(1 - x) + 2 * x*x*x, 0, 0, 6 * y*(1 - y)*(1 - y) - 12 * y*y*(1 - y) + 2 * y*y*y);
			}

			double	F(FVector_double& p) {
				double x = p[0], y = p[1];
				return -(6 * x*(1 - x)*(1 - x) - 12 * x*x*(1 - x) + 2 * x*x*x + 6 * y*(1 - y)*(1 - y) - 12 * y*y*(1 - y) + 2 * y*y*y);
			}
		};
		class P_SEMPLE3 : public FEM_PROBLEM { //-div(▽p) = f
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(0., 0., 1., 1.);
			}
			void	coef_mMu(FVector_double& p, FMatrix_double& mMu) {
				double x = p[0], y = p[1];
				mMu.setAll(1., 0., 0., 1.);
			}
			double	P(FVector_double& p) {
				double x = p[0], y = p[1];
				return x*x*(1 - x)*(1 - x)*y*y*(1 - y)*(1 - y);
			}

			void	DP(FVector_double& p, FVector_double& vDP) {
				double x = p[0], y = p[1];
				vDP.setAll(2 * x*(1 - x)*(1 - x)*y*y*(1 - y)*(1 - y) - 2 * x*x*(1 - x)*y*y*(1 - y)*(1 - y), 2 * x*x*(1 - x)*(1 - x)*y*(1 - y)*(1 - y) - 2 * x*x*(1 - x)*(1 - x)*y*y*(1 - y));
			}
			void	DDP(FVector_double& p, FMatrix_double& mDDP) {
				double x = p[0], y = p[1];
				mDDP.setAll(2 * (1 - x)*(1 - x)*y*y*(1 - y)*(1 - y) - 8 * x*(1 - x)*y*y*(1 - y)*(1 - y) + 2 * x*x*y*y*(1 - y)*(1 - y),
					4 * x*(1 - x)*(1 - x)*y*(1 - y)*(1 - y) - 4 * x*(1 - x)*(1 - x)*y*y*(1 - y) - 4 * x*x*(1 - x)*y*(1 - y)*(1 - y) + 4 * x*x*(1 - x)*y*y*(1 - y),
					4 * x*(1 - x)*(1 - x)*y*(1 - y)*(1 - y) - 4 * x*(1 - x)*(1 - x)*y*y*(1 - y) - 4 * x*x*(1 - x)*y*(1 - y)*(1 - y) + 4 * x*x*(1 - x)*y*y*(1 - y),
					2 * x*x*(1 - x)*(1 - x)*(1 - y)*(1 - y) - 8 * x*x*(1 - x)*(1 - x)*y*(1 - y) + 2 * x*x*(1 - x)*(1 - x)*y*y);
			}

			double	F(FVector_double& p) {
				double x = p[0], y = p[1];
				return -(24 * x * x * y * y - 24 * x*x*x * y * y + 2 * x * x + 2 * y * y - 4 * x*x*x - 4 * y*y*y - 24 * x * x * y*y*y - 12 * x * y * y + 24 * x * y*y*y - 12 * x * x * y + 24 * x*x*x * y - 12 * x*x*x*x * y + 12 * x*x*x*x * y * y + 2 * x*x*x*x + 2 * y*y*y*y - 12 * y*y*y*y * x + 12 * y*y*y*y * x * x);
			}
		};
		class P_SEMPLE4 : public FEM_PROBLEM { //-div(▽p) = f
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(0., 0., 1., 1.);
			}
			void	coef_mMu(FVector_double& p, FMatrix_double& mMu) {
				double x = p[0], y = p[1];
				mMu.setAll(1., 0., 0., 1.);
			}

			double	P(FVector_double& p) {
				double x = p[0], y = p[1];
				return x*x*x*x*x*y*y*y*y*y;
			}

			void	DP(FVector_double& p, FVector_double& vDP) {
				double x = p[0], y = p[1];
				vDP.setAll(5 * x*x*x*x*y*y*y*y*y, 5 * x*x*x*x*x*y*y*y*y);
			}
			void	DDP(FVector_double& p, FMatrix_double& mDDP){
				double x = p[0], y = p[1];
				mDDP.setAll(20 * x*x*x*y*y*y*y*y, 25 * x*x*x*x*y*y*y*y, 25 * x*x*x*x*y*y*y*y, 20 * x*x*x*x*x*y*y*y);
			}

			double	F(FVector_double& p) {
				double x = p[0], y = p[1];
				return -20 * x*x*x*y*y*y*y*y - 20 * x*x*x*x*x*y*y*y;
			}
		};
		class P_SEMPLE5 : public FEM_PROBLEM { //-div(▽p) = f
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(0., 0., 10., 10.);
			}
			void	coef_mMu(FVector_double& p, FMatrix_double& mMu) {
				double x = p[0], y = p[1];
				mMu.setAll(1., 0., 0., 1.);
			}

			double	P(FVector_double& p) {
				double x = p[0], y = p[1];
				return x*x*(10 - x)*(10 - x)*y*y*(10 - y)*(10 - y);
			}

			void	DP(FVector_double& p, FVector_double& vDP) {
				double x = p[0], y = p[1];
				vDP.setAll(2 * x*(10 - x)*(10 - x)*y*y*(10 - y)*(10 - y) - 2 * x*x*(10 - x)*y*y*(10 - y)*(10 - y), 2 * x*x*(10 - x)*(10 - x)*y*(10 - y)*(10 - y) - 2 * x*x*(10 - x)*(10 - x)*y*y*(10 - y));
			}
			void	DDP(FVector_double& p, FMatrix_double& mDDP) {
				double x = p[0], y = p[1];
				mDDP.setAll(2 * (10 - x)*(10 - x)*y*y*(10 - y)*(10 - y) - 8 * x*(10 - x)*y*y*(10 - y)*(10 - y) + 2 * x*x*y*y*(10 - y)*(10 - y),
					4 * x*(10 - x)*(10 - x)*y*(10 - y)*(10 - y) - 4 * x*(10 - x)*(10 - x)*y*y*(10 - y) - 4 * x*x*(10 - x)*y*(10 - y)*(10 - y) + 4 * x*x*(10 - x)*y*y*(10 - y),
					4 * x*(10 - x)*(10 - x)*y*(10 - y)*(10 - y) - 4 * x*(10 - x)*(10 - x)*y*y*(10 - y) - 4 * x*x*(10 - x)*y*(10 - y)*(10 - y) + 4 * x*x*(10 - x)*y*y*(10 - y),
					2 * x*x*(10 - x)*(10 - x)*(10 - y)*(10 - y) - 8 * x*x*(10 - x)*(10 - x)*y*(10 - y) + 2 * x*x*(10 - x)*(10 - x)*y*y
					);
			}

			double	F(FVector_double& p) {
				double x = p[0], y = p[1];
				return -(2 * (10 - x)*(10 - x)*y*y*(10 - y)*(10 - y) - 8 * x*(10 - x)*y*y*(10 - y)*(10 - y) + 2 * x*x*y*y*(10 - y)*(10 - y) + 2 * x*x*(10 - x)*(10 - x)*(10 - y)*(10 - y) - 8 * x*x*(10 - x)*(10 - x)*y*(10 - y) + 2 * x*x*(10 - x)*(10 - x)*y*y);
			}
		};
		class P_SEMPLE6 : public FEM_PROBLEM { //-div(mu▽p) = f
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(0., 0., 1., 1.);
			}
			double	coef_mu(FVector_double& p) {
				double x = p[0], y = p[1];
				return exp(x*y)*sin(x*y) + 3.;
			}
			void 	coef_Dmu(FVector_double& p, FVector_double& vDmu){
				double x = p[0], y = p[1];
				vDmu.setAll(y*exp(x*y)*sin(x*y) + exp(x*y)*y*cos(x*y), x*exp(x*y)*sin(x*y) + exp(x*y)*x*cos(x*y));
			}
			void	coef_mMu(FVector_double& p, FMatrix_double& mMu) {
				double x = p[0], y = p[1];
				mMu.setAll(exp(x*y)*sin(x*y) + 3., 0., 0., exp(x*y)*sin(x*y) + 3.);
			}

			double	P(FVector_double& p) {
				double x = p[0], y = p[1];
				return x*(1 - x)*y*(1 - y);
			}

			void	DP(FVector_double& p, FVector_double& vDP) {
				double x = p[0], y = p[1];
				vDP.setAll(y*(1 - y)*(1 - 2 * x), x*(1 - x)*(1 - 2 * y));
			}

			void	DDP(FVector_double& p, FMatrix_double& mDDP) {
				double x = p[0], y = p[1];
				mDDP.setAll(2 * y*(y - 1), (-1 + 2 * x)*(-1 + 2 * y), (-1 + 2 * x)*(-1 + 2 * y), 2 * x*(x - 1));
			}

			double	F(FVector_double& p) {
				double x = p[0], y = p[1];
				return -((y * exp(x * y) * sin(x * y) + exp(x * y) * cos(x * y) * y) * ((0.1e1 - x) * y * (0.1e1 - y) - x * y * (0.1e1 - y)) - 0.2e1 * (exp(x * y) * sin(x * y) + 0.3e1) * y * (0.1e1 - y) + (x * exp(x * y) * sin(x * y) + exp(x * y) * cos(x * y) * x) * (x * (0.1e1 - x) * (0.1e1 - y) - x * (0.1e1 - x) * y) - 0.2e1 * (exp(x * y) * sin(x * y) + 0.3e1) * x * (0.1e1 - x));


			}

		};

		class P_SEMPLE7 : public FEM_PROBLEM { //-div(▽p) = f
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(0., 0., 1., 1.);
			}
			void	coef_mMu(FVector_double& p, FMatrix_double& mMu) {
				double x = p[0], y = p[1];
				mMu.setAll(1., 0., 0., 1.);
			}

			double	P(FVector_double& p) {
				double x = p[0], y = p[1];
				return exp(x)*cos(y) - 0.5*x*x;
			}

			void	DP(FVector_double& p, FVector_double& vDP) {
				double x = p[0], y = p[1];
				vDP.setAll(exp(x)*cos(y) - x, -exp(x)*sin(y));
			}
			void	DDP(FVector_double& p, FMatrix_double& mDDP) {
				double x = p[0], y = p[1];
				mDDP.setAll(exp(x)*cos(y) - 1, -exp(x)*sin(y), -exp(x)*sin(y), -exp(x)*cos(y)
					);
			}

			double	F(FVector_double& p) {
				double x = p[0], y = p[1];
				return 1;
			}
		};
		class P_SINCOS: public FEM_PROBLEM {	 // Governing Equation:  -div(μ▽p) = f
		public:
			void	initialize	(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1.,-1., 1.,1.);
			}

			double	P	(FVector_double& p) {
				double x=p[0], y=p[1];
				return sin(2*CV.PI*x)*cos(CV.PI*y);	
			}

			void	DP	(FVector_double &p, FVector_double &dp) {
				double x=p[0], y=p[1];
				dp.setAll(2*CV.PI*cos(2*CV.PI*x)*cos(CV.PI*y), -CV.PI*sin(2*CV.PI*x)*sin(CV.PI*y));
			}
			void	coef_mMu	(FVector_double& p, FMatrix_double& mMu) {
				double x=p[0], y=p[1];
				mMu.setAll(1., 0., 0., 1.);
			}

			void	coef_cDMu	(FVector_double& p, FCube_double& cDMu) {
				double x=p[0], y=p[1];
				cDMu.setAll(0., 0., 0., 0., 0., 0., 0., 0.);
			}
			double	F	(FVector_double& p) {
				double x=p[0], y=p[1];
				return 5*CV.PI*CV.PI*cos(CV.PI*y)*sin(2*CV.PI*x);	
			}
		};
		class P_SINCOS2 : public FEM_PROBLEM {	// △△u = f
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(0., 0., 1., 1.);
			}
			void	coef_mMu(FVector_double& p, FMatrix_double& mMu) {
				double x = p[0], y = p[1];
				mMu.setAll(1., 0., 0., 1.);
			}

			double	P(FVector_double& p) {
				double x = p[0], y = p[1];
				return sin(2 * CV.PI*x)*cos(CV.PI*y);
			}

			void	DP(FVector_double &p, FVector_double &dp) {
				double x = p[0], y = p[1];
				dp.setAll(2 * CV.PI*cos(2 * CV.PI*x)*cos(CV.PI*y), -CV.PI*sin(2 * CV.PI*x)*sin(CV.PI*y));
			}
			void	DDP(FVector_double &p, FMatrix_double &mDDP){
				double x = p[0], y = p[1];
				mDDP.setAll(-4 * $(CV.PI, 2)*cos(CV.PI*y)*sin(2 * CV.PI*x),
					-2 * $(CV.PI, 2)*sin(CV.PI*y)*cos(2 * CV.PI*x),
					-2 * $(CV.PI, 2)*sin(CV.PI*y)*cos(2 * CV.PI*x),
					-$(CV.PI, 2)*cos(CV.PI*y)*sin(2 * CV.PI*x)
					);
			}
			double	F(FVector_double& p) {
				double x = p[0], y = p[1];
				return 5 * $(CV.PI, 2)*cos(CV.PI*y)*sin(2 * CV.PI*x);
			}
		};
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		//============================================================================
		//                                 ELLIPTIC_X
		//============================================================================
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		class P_Eigen : public FEM_PROBLEM { //-div(▽u) = lambda u
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(0., 0., CV.PI, CV.PI);
				//RX = __.RX.make(__.dim, __.dim).setAll(-CV.PI,-CV.PI, CV.PI,CV.PI);
			}
			void	coef_mMu(FVector_double& p, FMatrix_double& mMu) {
				double x = p[0], y = p[1];
				mMu.setAll(1., 0., 0., 1.);
			}

			double	P(FVector_double& p) {
				double x = p[0], y = p[1];
				return sin(x)*sin(y);
			}
		};
		class P_X: public FEM_PROBLEM { // Governing Equation:  -div(μ▽p) = f
		public:
			void	initialize	(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(0.,0., 1.,1.);
			}

			double	P	(FVector_double& p) {
				double x=p[0], y=p[1];
				return x;	
			}

			void	DP	(FVector_double &p, FVector_double &dp) {
				double x=p[0], y=p[1];
				dp.setAll(1., 0.);
			}
			void	coef_mMu	(FVector_double& p, FMatrix_double& mMu) {
				double x=p[0], y=p[1];
				mMu.setAll(1., 0., 0., 1.);
			}

			void	coef_cDMu	(FVector_double& p, FCube_double& cDMu) {
				double x=p[0], y=p[1];
				cDMu.setAll(0., 0., 0., 0., 0., 0., 0., 0.);
			}
			double	F	(FVector_double& p) {
				double x=p[0], y=p[1];
				return 0;	
			}
		};

		class P_ZERO: public FEM_PROBLEM {
		public:
			void	initialize	(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(0.,0.,1.,1.);
			}
			
			double	P			(FVector_double& p) {
				double x=p[0], y=p[1];
				return 0.;
			}

			void	DP			(FVector_double& p, FVector_double& vDP) {
				double x=p[0], y=p[1];
				vDP.setAll(0., 0.);
			}
			
			void	coef_mMu	(FVector_double& p, FMatrix_double& mMu) {
				double x=p[0], y=p[1];
				mMu.setAll(1., 0., 0., 1.);
			}

			void	coef_cDMu	(FVector_double& p, FCube_double& cDMu) {
				double x=p[0], y=p[1];
				cDMu.setAll(0., 0., 0., 0., 0., 0., 0., 0.);
			}

			double	F			(FVector_double& p) {
				double x=p[0], y=p[1];
				return 0.;
			}
		};

		class P_IM_CIRCLE1 : public FEM_PROBLEM { //-div(mu▽p) = f
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				Input("r0", r0);
				Input("mum", mum);
				Input("mup", mup);
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);
			}
			double CIRCLE(FVector_double& p) {                             //p가 interface 내부이면 -를 외부이면 +가 return 된다.
				double x = p[0], y = p[1];
				return x*x + y*y - r0*r0;
			}

			double	Interface(double r) {												// 내부에서 음수의 값을 가지도록 한다.
				return (r - r0);
			}

			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);

				return (r - r0);
			}
			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}
			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) < 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}
			double	P(FVector_double& p) {
				double x = p[0], y = p[1];
				if (Interface(p) > 0)
					return mum*CIRCLE(p)*(1 + x)*(1 + y)*(1 - x)*(1 - y);
				else
					return mup*CIRCLE(p)*(1 + x)*(1 + y)*(1 - x)*(1 - y);
			}
			double	P(FVector_double& p, FVector_double& vp) {
				double x = p[0], y = p[1];
				vp.setAll(mup*CIRCLE(p)*(1 + x)*(1 + y)*(1 - x)*(1 - y), mum*CIRCLE(p)*(1 + x)*(1 + y)*(1 - x)*(1 - y));
				return 0;
			}

			void	DP(FVector_double& p, FVector_double& vDP) {
				double x = p[0], y = p[1];
				if (Interface(p) >0)
					vDP.setAll(mum*(1 + x)*(1 + y)*(1 - x)*(1 - y) * 2 * x - mum*CIRCLE(p) * 2 * x*(1 + y)*(1 - y), mum*(1 + x)*(1 + y)*(1 - x)*(1 - y) * 2 * y - mum * 2 * y*(1 - x)*(1 + x)*CIRCLE(p));
				else
					vDP.setAll(mup*(1 + x)*(1 + y)*(1 - x)*(1 - y) * 2 * x - mup*CIRCLE(p) * 2 * x*(1 + y)*(1 - y), mup*(1 + x)*(1 + y)*(1 - x)*(1 - y) * 2 * y - mup * 2 * y*(1 - x)*(1 + x)*CIRCLE(p));
			}

			void	DP(FVector_double& p, FMatrix_double& mDPs){
				double x = p[0], y = p[1];
				mDPs.setAll(mup*(1 + x)*(1 + y)*(1 - x)*(1 - y) * 2 * x - mup*CIRCLE(p) * 2 * x*(1 + y)*(1 - y), mup*(1 + x)*(1 + y)*(1 - x)*(1 - y) * 2 * y - mup * 2 * y*(1 - x)*(1 + x)*CIRCLE(p),
					mum*(1 + x)*(1 + y)*(1 - x)*(1 - y) * 2 * x - mum*CIRCLE(p) * 2 * x*(1 + y)*(1 - y), mum*(1 + x)*(1 + y)*(1 - x)*(1 - y) * 2 * y - mum * 2 * y*(1 - x)*(1 + x)*CIRCLE(p));
			}

			double	F(FVector_double& p) {
				double x = p[0], y = p[1];
				if (Interface(p) > 0)
					return mum*mup*((1 + y)*(1 - y)*(6 * x*x - 2) + 2 * (1 + y)*(1 - y)*CIRCLE(p) + 4 * x*x*(1 + y)*(1 - y) + (1 + x)*(1 - x)*(6 * y*y - 2) + 2 * (1 + x)*(1 - x)*CIRCLE(p) + 4 * y*y*(1 + x)*(1 - x));
				else
					return mum*mup*((1 + y)*(1 - y)*(6 * x*x - 2) + 2 * (1 + y)*(1 - y)*CIRCLE(p) + 4 * x*x*(1 + y)*(1 - y) + (1 + x)*(1 - x)*(6 * y*y - 2) + 2 * (1 + x)*(1 - x)*CIRCLE(p) + 4 * y*y*(1 + x)*(1 - x));
			}
			double	F(FVector_double& p, FVector_double& vF) {
				double x = p[0], y = p[1];
				vF.setAll(mum*mup*((1 + y)*(1 - y)*(6 * x*x - 2) + 2 * (1 + y)*(1 - y)*CIRCLE(p) + 4 * x*x*(1 + y)*(1 - y) + (1 + x)*(1 - x)*(6 * y*y - 2) + 2 * (1 + x)*(1 - x)*CIRCLE(p) + 4 * y*y*(1 + x)*(1 - x)),
					mum*mup*((1 + y)*(1 - y)*(6 * x*x - 2) + 2 * (1 + y)*(1 - y)*CIRCLE(p) + 4 * x*x*(1 + y)*(1 - y) + (1 + x)*(1 - x)*(6 * y*y - 2) + 2 * (1 + x)*(1 - x)*CIRCLE(p) + 4 * y*y*(1 + x)*(1 - x)));
				return 0;
			}
		};

		class P_IM_CIRCLE2 : public FEM_PROBLEM { //-div(mu▽p) = f
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				Input("r0", r0);
				Input("mum", mum);
				Input("mup", mup);
				Input("k", k);
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);
			}
			double CIRCLE(FVector_double& p) {                             //p가 interface 내부이면 -를 외부이면 +가 return 된다.
				double x = p[0], y = p[1];
				return x*x + y*y - r0*r0;
			}

			double	Interface(double r) {												// 내부에서 음수의 값을 가지도록 한다.
				return (r - r0);
			}

			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);

				return (r - r0);
			}
			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}
			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) < 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}
			double	P(FVector_double& p) {
				double x = p[0], y = p[1];
				if (Interface(p) > 0)
					return mum*CIRCLE(p)*sin(k*(x + y));
				else
					return mup*CIRCLE(p)*sin(k*(x + y));
			}

			double	P(FVector_double& p, FVector_double& vp) {
				double x = p[0], y = p[1];
				vp.setAll(mup*CIRCLE(p)*sin(k*(x + y)), mum*CIRCLE(p)*sin(k*(x + y)));
				return 0;
			}

			void	DP(FVector_double& p, FVector_double& vDP) {
				double x = p[0], y = p[1];
				if (Interface(p) >0)
					vDP.setAll(mum*(2 * x*sin(k*(x + y)) + (x*x + y*y - r0*r0)*k*cos(k*(x + y))), mum*(2 * y*sin(k*(x + y)) + (x*x + y*y - r0*r0)*k*cos(k*(x + y))));
				else
					vDP.setAll(mup*(2 * x*sin(k*(x + y)) + (x*x + y*y - r0*r0)*k*cos(k*(x + y))), mup*(2 * y*sin(k*(x + y)) + (x*x + y*y - r0*r0)*k*cos(k*(x + y))));
			}
			void	DP(FVector_double& p, FMatrix_double& mDPs){
				double x = p[0], y = p[1];
				mDPs.setAll(mup*(2 * x*sin(k*(x + y)) + (x*x + y*y - r0*r0)*k*cos(k*(x + y))), mup*(2 * y*sin(k*(x + y)) + (x*x + y*y - r0*r0)*k*cos(k*(x + y))),
					mum*(2 * x*sin(k*(x + y)) + (x*x + y*y - r0*r0)*k*cos(k*(x + y))), mum*(2 * y*sin(k*(x + y)) + (x*x + y*y - r0*r0)*k*cos(k*(x + y))));
			}

			double	F(FVector_double& p) {
				double x = p[0], y = p[1];
				if (Interface(p) > 0)
					return mum*mup*(2 * (x*x + y*y - r0*r0)*k*k*sin(k*(x + y)) - 4 * k*(x + y)*cos(k*(x + y)) - 4 * sin(k*(x + y)));
				else
					return mum*mup*(2 * (x*x + y*y - r0*r0)*k*k*sin(k*(x + y)) - 4 * k*(x + y)*cos(k*(x + y)) - 4 * sin(k*(x + y)));
			}
			double	F(FVector_double& p, FVector_double& vF) {
				double x = p[0], y = p[1];
				vF.setAll(mum*mup*(2 * (x*x + y*y - r0*r0)*k*k*sin(k*(x + y)) - 4 * k*(x + y)*cos(k*(x + y)) - 4 * sin(k*(x + y))),
					mum*mup*(2 * (x*x + y*y - r0*r0)*k*k*sin(k*(x + y)) - 4 * k*(x + y)*cos(k*(x + y)) - 4 * sin(k*(x + y))));
				return 0;
			}
		};

		class P_IM_DOUBLE_CIRCLE : public FEM_PROBLEM { //-div(mu▽p) = f
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				Input("mum", mum);
				Input("mup", mup);
				Input("r0", r0); // 오른쪽 원
				Input("r1", r1); // 왼쪽 원
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);
			}

			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				return ((x - 0.5)*(x - 0.5) + y*y - r0*r0)*((x + 0.5)*(x + 0.5) + y*y - r1*r1);
			}
			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}
			double	coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) < 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}
			double	P(FVector_double& p) {
				double x = p[0], y = p[1];
				if (Interface(p) > 0)
					return Interface(p) / mup;
				else
					return Interface(p) / mum;
			}

			double	P(FVector_double& p, FVector_double& vp) {
				double x = p[0], y = p[1];
				vp.setAll(Interface(p) / mum, Interface(p) / mup);
				return 0;
			}

			void	DP(FVector_double& p, FVector_double& vDP) {
				double x = p[0], y = p[1];
				if (Interface(p) >0)
					vDP.setAll((((x - 0.5)*(x - 0.5) + y*y - r0*r0)*2.*(x + 0.5) + ((x + 0.5)*(x + 0.5) + y*y - r1*r1)*2.*(x - 0.5)) / mup,
					(((x - 0.5)*(x - 0.5) + y*y - r0*r0)*2.*y + ((x + 0.5)*(x + 0.5) + y*y - r1*r1)*2.*y) / mup);
				else
					vDP.setAll((((x - 0.5)*(x - 0.5) + y*y - r0*r0)*2.*(x + 0.5) + ((x + 0.5)*(x + 0.5) + y*y - r1*r1)*2.*(x - 0.5)) / mum,
					(((x - 0.5)*(x - 0.5) + y*y - r0*r0)*2.*y + ((x + 0.5)*(x + 0.5) + y*y - r1*r1)*2.*y) / mum);
			}
			void	DP(FVector_double& p, FMatrix_double& mDPs){
				double x = p[0], y = p[1];
				mDPs.setAll((((x - 0.5)*(x - 0.5) + y*y - r0*r0)*2.*(x + 0.5) + ((x + 0.5)*(x + 0.5) + y*y - r1*r1)*2.*(x - 0.5)) / mum, (((x - 0.5)*(x - 0.5) + y*y - r0*r0)*2.*y + ((x + 0.5)*(x + 0.5) + y*y - r1*r1)*2.*y) / mum,
					(((x - 0.5)*(x - 0.5) + y*y - r0*r0)*2.*(x + 0.5) + ((x + 0.5)*(x + 0.5) + y*y - r1*r1)*2.*(x - 0.5)) / mup, (((x - 0.5)*(x - 0.5) + y*y - r0*r0)*2.*y + ((x + 0.5)*(x + 0.5) + y*y - r1*r1)*2.*y) / mup);
			}

			double	F(FVector_double& p) {
				double x = p[0], y = p[1];
				if (Interface(p) > 0)
					return -(2.*2.*(x - 0.5)*2.*(x + 0.5) + ((x - 0.5)*(x - 0.5) + y*y - r0*r0)*4. + ((x + 0.5)*(x + 0.5) + y*y - r1*r1)*4. + 8.*y*y);
				else
					return -(2.*2.*(x - 0.5)*2.*(x + 0.5) + ((x - 0.5)*(x - 0.5) + y*y - r0*r0)*4. + ((x + 0.5)*(x + 0.5) + y*y - r1*r1)*4. + 8.*y*y);
			}
			double	F(FVector_double& p, FVector_double& vF) {
				double x = p[0], y = p[1];
				vF.setAll(-(2.*2.*(x - 0.5)*2.*(x + 0.5) + ((x - 0.5)*(x - 0.5) + y*y - r0*r0)*4. + ((x + 0.5)*(x + 0.5) + y*y - r1*r1)*4. + 8.*y*y),
					-(2.*2.*(x - 0.5)*2.*(x + 0.5) + ((x - 0.5)*(x - 0.5) + y*y - r0*r0)*4. + ((x + 0.5)*(x + 0.5) + y*y - r1*r1)*4. + 8.*y*y));
				return 0;
			}
		};

		class P_IM_SHARP_EDGE : public FEM_PROBLEM { //-div(mu▽p) = f
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				Input("theta", theta);
				theta = theta*CV.ANGLE_TO_RADIAN;
				Input("mum", mum);
				Input("mup", mup);
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);
			}

			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				return y*y - ((x - 1)*tan(theta))*((x - 1)*tan(theta))*x;
			}
			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}
			double	coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) < 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}
			double	P(FVector_double& p) {
				double x = p[0], y = p[1];
				if (Interface(p) > 0)
					return Interface(p) / mup;
				else
					return Interface(p) / mum;
			}
			double	P(FVector_double& p, FVector_double& vp) {
				double x = p[0], y = p[1];
				vp.setAll(Interface(p) / mum, Interface(p) / mup);
				return 0;
			}

			void	DP(FVector_double& p, FVector_double& vDP) {
				double x = p[0], y = p[1];
				if (Interface(p) >0)
					vDP.setAll(-(3 * x*x - 4 * x + 1)*tan(theta)*tan(theta) / mup, 2 * y / mup);
				else
					vDP.setAll(-(3 * x*x - 4 * x + 1)*tan(theta)*tan(theta) / mum, 2 * y / mum);
			}
			void	DP(FVector_double& p, FMatrix_double& mDPs){
				double x = p[0], y = p[1];
				mDPs.setAll(-(3 * x*x - 4 * x + 1)*tan(theta)*tan(theta) / mum, 2 * y / mum,
					-(3 * x*x - 4 * x + 1)*tan(theta)*tan(theta) / mup, 2 * y / mup);
			}

			double	F(FVector_double& p) {
				double x = p[0], y = p[1];
				if (Interface(p) > 0)
					return ((6 * x - 4)*tan(theta)*tan(theta) - 2);
				else
					return ((6 * x - 4)*tan(theta)*tan(theta) - 2);
			}
			double	F(FVector_double& p, FVector_double& vF) {
				double x = p[0], y = p[1];
				vF.setAll((6 * x - 4)*tan(theta)*tan(theta) - 2,
					(6 * x - 4)*tan(theta)*tan(theta) - 2);
				return 0;
			}
		};
		class P_IM_SHARP_EDGE_INSIDE : public FEM_PROBLEM { //-div(mu▽p) = f
		public:
			void initialize(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
			//	Input("theta", theta);
				theta = 30;
				theta = theta / 180.*CV.PI;
				Input("mum", mum);
				Input("mup", mup);
			//	Input("x_shift", x_intercept);
				x_intercept = -0.3;
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);
			}
			double Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				//return y*y - ((x-0.5)*tan(theta))*((x-0.5)*tan(theta))*(x+0.5);
				if (x <= 1 + x_intercept) 	return y*y - ((x - 1. - x_intercept)*tan(theta))*((x - 1. - x_intercept)*tan(theta))*(x - x_intercept);
				else			return 1.;

			}
			double coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);              // (Interior, Exterior)
				return 0;
			}
			double coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) <= 0) 		return mus[0];
				else						return mus[1];
			}
			double P(FVector_double& p) {
				double x = p[0], y = p[1];
				if (Interface(p) > 0)		return (y*y - ((x - 1. - x_intercept)*tan(theta))*((x - 1. - x_intercept)*tan(theta))*(x - x_intercept)) / mup;
				else						return (y*y - ((x - 1. - x_intercept)*tan(theta))*((x - 1. - x_intercept)*tan(theta))*(x - x_intercept)) / mum;
			}
			double	P(FVector_double& p, FVector_double& vp) {
				double x = p[0], y = p[1];
				vp.setAll((y*y - ((x - 1. - x_intercept)*tan(theta))*((x - 1. - x_intercept)*tan(theta))*(x - x_intercept)) / mum,
					(y*y - ((x - 1. - x_intercept)*tan(theta))*((x - 1. - x_intercept)*tan(theta))*(x - x_intercept)) / mup);
				return 0;
			}
			void DP(FVector_double& p, FVector_double& vDP) {
				double x = p[0], y = p[1];
				if (Interface(p) >0)		vDP.setAll(-(3 * (x - x_intercept)*(x - x_intercept) - 4 * (x - x_intercept) + 1)*tan(theta)*tan(theta) / mup, 2 * y / mup);
				else					vDP.setAll(-(3 * (x - x_intercept)*(x - x_intercept) - 4 * (x - x_intercept) + 1)*tan(theta)*tan(theta) / mum, 2 * y / mum);
			}
			void	DP(FVector_double& p, FMatrix_double& mDPs){
				double x = p[0], y = p[1];
				mDPs.setAll(-(3 * (x - x_intercept)*(x - x_intercept) - 4 * (x - x_intercept) + 1)*tan(theta)*tan(theta) / mum, 2 * y / mum,
					-(3 * (x - x_intercept)*(x - x_intercept) - 4 * (x - x_intercept) + 1)*tan(theta)*tan(theta) / mup, 2 * y / mup);
			}
			double F(FVector_double& p) {
				double x = p[0], y = p[1];
				if (Interface(p) > 0)	return ((6 * (x - x_intercept) - 4)*tan(theta)*tan(theta) - 2);
				else					return ((6 * (x - x_intercept) - 4)*tan(theta)*tan(theta) - 2);
			}
			double	F(FVector_double& p, FVector_double& vF) {
				double x = p[0], y = p[1];
				vF.setAll((6 * (x - x_intercept) - 4)*tan(theta)*tan(theta) - 2,
					(6 * (x - x_intercept) - 4)*tan(theta)*tan(theta) - 2);
				return 0;
			}
		};
		class Interface_Smooth_Sol_Curve_Interface_DISCON_DIVU : public FEM_PROBLEM {
		public:
			// Exact Solution.
			// Line Interface
			void		initialize(FEM_VARIABLES::ENTIRE& __) {  
				K_p = pow(10., 0.);	 
				__.dim = 2; 
				__.RX.make(__.dim, __.dim).setAll(0., 0., CV.PI / 2., CV.PI / 2.);
				RX = __.RX;
				nInterface = 1;
				nFunction = 101;
				r0 = 1. / 4.;
				mum = pow(10., -3.);
				mup = pow(10., 0.);
			}
			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				double rt = (x - 0.5)*(x - 0.5) + (y - 0.5)*(y - 0.5) - r0*r0;
				return rt;
			}

			void	DInterface(FVector_double& p, FVector_double& vDI) {
				double x = p[0], y = p[1];
				vDI[0] = 2.*(x - 0.5);
				vDI[1] = 2.*(y - 0.5);
			}
			void	DDInterface(FVector_double& p, FMatrix_double& mDDI)	{
				double x = p[0], y = p[1];
				mDDI[0][0] = 2.;
				mDDI[1][1] = 2.;
			}

			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);
				return 0;
			}
			double	coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.
				if (Interface(p) < 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			} 
			double	sw(double t, FVector_double& p) {
				t = 0.;
				double x = p[0], y = p[1]; 
				double rt;
				rt = cos(x)*(0.2 + 0.5*t);  
				return rt; 
			} 
			void	Dsw(double t, FVector_double& p, FVector_double & vDS) {
				t = 0.;
				double x = p[0], y = p[1];
				vDS[0] = -sin(x)*(0.2 + 0.5*t);
				vDS[1] = 0; 
			}
			double	k_n(double s)	{
				return (1. - s)*(1. - s)*(1. - s*s);
			}
			double	k_w(double s){
				return s*s*s*s;
			}
			double	Lamda_n(double s){
				double k = k_n(s);
				return k;
			}
			double	Lamda_w(double s){
				double k = k_w(s);
				return k;
			}
			double	Lamda(double s){
				double t1;	double t2;
				t1 = Lamda_n(s);
				t2 = Lamda_w(s);
				return t1 + t2;
			}
			double	Lamdad(double s){
				double t1;	double t2;
				t1 = Lamdad_n(s);
				t2 = Lamdad_w(s);
				return t1 + t2;
			}
			double Lamdad_n(double s){
				return (2.*(s - 1.)*(1. - s*s) + (s - 1.)*(s - 1.)*(-2.*s));
			}
			double Lamdad_w(double s){
				return 4.*s*s*s;
			}
			double P(FVector_double& p) {
				double x = p[0], y = p[1];
				return gp(0., p);
			}
			double	P(FVector_double& p, FVector_double& vp) {
				double x = p[0], y = p[1];
				vp.setAll(gp(0., p), gp(0.,  p));
				return 0;
			}
			void DP(FVector_double& p, FVector_double& vDP) {
				double x = p[0], y = p[1];
				Dgp(0., p, vDP);
			}
			void DP(FVector_double& p, FMatrix_double& mDPs){
				double x = p[0], y = p[1];
				static FVector_double stv_vDP(2);
				Dgp(0., p, stv_vDP);
				mDPs[0] = stv_vDP;
				mDPs[1] = stv_vDP;
			}
			double	gp(double t, FVector_double& p) {
				t = 0.;
				double x = p[0], y = p[1];
				double rt;
				double L = Interface(p);
				double e = 2.7182818284590452353602874;
				if (L > 0){
					rt = -L*(x - 1);
					rt = rt*mum*(2 - t) + 0.1;
				}
				if (L <= 0){
					rt = -pow(e, L*(x - 1)) + 1;
					rt = rt*(2 - t) + 0.1;
				}
				rt = 10 * rt;
				return rt;
			}
			void	Dgp(double t, FVector_double& p, FVector_double& vDP)	{
				t = 0.;
				double x = p[0], y = p[1];
				double L = Interface(p);
				double DLx = 2.*(x - 0.5);
				double DLy = 2.*(y - 0.5);
				double e = 2.7182818284590452353602874;
				if (L > 0){
					vDP[0] = (x - 1)*DLx + L;
					vDP[1] = DLy*(x - 1);
					vDP[0] = -vDP[0] * mum * (2. - t);
					vDP[1] = -vDP[1] * mum * (2. - t);
				}
				if (L <= 0){
					vDP[0] = (x - 1)*DLx*pow(e, L*(x - 1)) + L*pow(e, L* (x - 1));
					vDP[1] = DLy*(x - 1)*pow(e, L*(x - 1));
					vDP[0] = -vDP[0] * (2 - t);
					vDP[1] = -vDP[1] * (2 - t);
				}
				vDP[0] = vDP[0] * 10;
				vDP[1] = vDP[1] * 10;
			}
			void	DDgp(double t, FVector_double& p, FMatrix_double& mDP)	{
				t = 0.;
				double x = p[0], y = p[1];
				double L = Interface(p);
				double DLx = 2.*(x - 0.5);
				double DLy = 2.*(y - 0.5);
				double DDL = 2.;
				double e = 2.7182818284590452353602874;

				if (Interface(p) > 0){
					mDP[0][0] = 2 * DLx + (x - 1)*DDL;
					mDP[1][1] = DDL * (x - 1);
					mDP[0][0] = -mDP[0][0] * mum*(2 - t);
					mDP[1][1] = -mDP[1][1] * mum*(2 - t);
				}
				if (Interface(p) <= 0){
					mDP[0][0] = DLx*pow(e, L*(x - 1)) + (x - 1)*DDL*pow(e, L*(x - 1)) + (x - 1)*DLx*((x - 1)*DLx*pow(e, L*(x - 1)) + L*pow(e, L* (x - 1))) + DLx*pow(e, L*(x - 1)) + L*((x - 1)*DLx*pow(e, L*(x - 1)) + L*pow(e, L* (x - 1)));

					// -DLx*pow(e, L*(x - 1)) - (x - 1)*DDL*pow(e, L*(x - 1)) - (x - 1)*DLx*((x - 1)*DLx*pow(e, L*(x - 1)) + L*pow(e, L* (x - 1)))-DLx*pow(e,L*(x-1))-L*(DLx*(x-1)+L)*pow(e,L*(x-1));
					mDP[1][1] = DDL*(x - 1)*pow(e, L*(x - 1)) + DLy*DLy*(x - 1)*(x - 1)*pow(e, L*(x - 1));
					mDP[0][0] = -mDP[0][0] * (2 - t);
					mDP[1][1] = -mDP[1][1] * (2 - t);
				}
				mDP[0][0] = mDP[0][0] * 10;
				mDP[1][1] = mDP[1][1] * 10;
			}
			void	tv(double t, FVector_double& p, FVector_double& vDV) {
				t = 0.;
				double x = p[0], y = p[1];
				double sw_ = sw(t, p);
				double K_ = K_p_(p);;
				double gp_ = gp(t, p);
				double lambda = Lamda(sw_);
				static FVector_double stv_vDP(2);
				Dgp(t, p, stv_vDP);

				vDV[0] = -lambda*stv_vDP[0] * K_;
				vDV[1] = -lambda*stv_vDP[1] * K_;
			}
			void	Dtv(double t, FVector_double& p, FMatrix_double& mDV) {

			}
			double	F(FVector_double& p) {
				double t = 0.;
				double x = p[0], y = p[1]; 
				double rt;
				double L = Interface(p);
				double sw_ = sw(t, p);
				double lamda_ = Lamda(sw_);
				double lamdad_ = Lamdad(sw_);
				double K_;
				double lap_p;

				static FVector_double sqt_DL(2);
				static FMatrix_double sqt_DDP(2, 2);
				static FVector_double sqt_DP(2);
				static FVector_double sqt_DS(2);
				 
				Dgp(t, p, sqt_DP);
				DDgp(t, p, sqt_DDP);
				Dsw(t, p, sqt_DS);

				K_ = K_p_(p);

				lap_p = sqt_DDP[0][0] + sqt_DDP[1][1];
				rt = -lap_p*K_*lamda_ - lamdad_*K_*(sqt_DS, sqt_DP);

				return rt;
			}
			double	F(FVector_double& p, FVector_double& vF) {
				double x = p[0], y = p[1];
				vF.setAll(F(p), F(p));
				return F(p);
			}
			double	K_p_(FVector_double & p) {
				double x = p[0], y = p[1];
				double rt = 0;
				if (Interface(p) <= 0) {
					rt = mum;
				}
				if (Interface(p) > 0){
					rt = mup;
				}
				return rt;
			}  
		};
		class P_IIM_ELLIPSE : public FEM_PROBLEM { //-div(mu▽p) = f
		public:
			void initialize(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);
				a = 0.65;
				b = 0.65;
			//	Input("a", a);
			//	Input("b", b);
			//	Input("mum", mum);
			//	Input("mup", mup);
				mum = 1.;
				mup = 1000.;
			}
			double Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				return x*x / a/ a + y*y / b / b - 1.0;
			}
			void DInterface(FVector_double& p, FVector_double& vDI)	{
				double x = p[0], y = p[1];
				vDI.setAll(2.*x/a/a, 2.*y/b/b);
			}
			void DDInterface(FVector_double& p, FMatrix_double& mDDI)	{
				double x = p[0], y = p[1];
				mDDI[0][0] = 2. / a /a;
				mDDI[0][1] = 0.;
				mDDI[1][0] = 0.;
				mDDI[1][1] = 2. / b / b;
			}
			double coef_mu(FVector_double& p, FVector_double& mus) {
				double beta = beta_(p);
				mus.setAll(mum, mup);              // (Interior, Exterior)
				return 0;
			}
			double coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.
				if (Interface(p) <= 0) 		return mus[0];
				else						return mus[1];
			}
			double P(FVector_double& p) {
				double x = p[0], y = p[1];
				static FVector_double vp(2);
				P(p, vp);
				if (Interface(p) > 0)	return vp(1);
				else					return vp(0);
			}
			double	P(FVector_double& p, FVector_double& vp) {
				double L = Interface(p);
				vp.setAll(L/mum, L/mup);
				return 0;
			}
			void DP(FVector_double& p, FVector_double& vDP) {
				double x = p[0], y = p[1];
				static FMatrix_double mDPS(2,2);
				DP(p, mDPS);
				if (Interface(p) > 0)		vDP = mDPS[1];
				else						vDP = mDPS[0];
			}
			void	DP(FVector_double& p, FMatrix_double& mDPs){
				double x = p[0], y = p[1];
				static FVector_double st_vDInterface(2);
				static FVector_double st_vDbeta(2);

				double L = Interface(p);
				DInterface(p, st_vDInterface);

				mDPs[0].op("=", 1 / mum, st_vDInterface);
				mDPs[1].op("=", 1 / mup, st_vDInterface);

			}
			double F(FVector_double& p) {
				static FVector_double vp(2);
				F(p, vp);
				if (Interface(p) > 0)	return vp[1];
				else					return vp[0];
			}
			double	F(FVector_double& p, FVector_double& vF) {
				static FMatrix_double st_mDDInterface(2,2);
				
				DDInterface(p, st_mDDInterface);
				
				vF[0] = (-st_mDDInterface[0][0] - st_mDDInterface[1][1]);
				vF[1] = (-st_mDDInterface[0][0] - st_mDDInterface[1][1]);
				
				return 0;
			}
		};
		class P_IIM_ELLIPSE_old : public FEM_PROBLEM { //-div(mu▽p) = f
		public:
			void initialize(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);
				a = 0.7;
				b = 0.4;
			}
			double Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				return x*x / a / a + y*y / b / b - 1.0;
			}
			void DInterface(FVector_double& p, FVector_double& vDI)	{
				double x = p[0], y = p[1];
				vDI.setAll(2.*x / a / a, 2.*y / b / b);
			}
			void DDInterface(FVector_double& p, FMatrix_double& mDDI)	{
				double x = p[0], y = p[1];
				mDDI[0][0] = 2. / a / a;
				mDDI[0][1] = 0.;
				mDDI[1][0] = 0.;
				mDDI[1][1] = 2. / b / b;
			}
			double beta_(FVector_double & p){
				// Omega^- 에서 beta
				double x = p[0], y = p[1];
				return 0.1*(x*x + y*y - 1.)*(x*x + y*y - 1.);
			}
			void Dbeta_(FVector_double & p, FVector_double & vDB){
				// Omega^- 에서 beta
				double x = p[0], y = p[1];
				vDB.setAll(0.1*2.*(x*x + y*y - 1.)*2.*x, 0.1*2.*(x*x + y*y - 1.)*2.*y);
			}
			void DDbeta_(FVector_double & p, FMatrix_double & mDB){
				double x = p[0], y = p[1];
				mDB[0][0] = 0.1 * 4 * (x*x + y*y - 1.) + 0.1 * 8 * x *x;
				mDB[0][1] = 0.1 * 8 * x * y;
				mDB[1][0] = 0.1 * 8 * x * y;
				mDB[1][1] = 0.1 * 4 * (x*x + y*y - 1.) + 0.1 * 8 * y *y;
			}
			double coef_mu(FVector_double& p, FVector_double& mus) {
				double beta = beta_(p);
				mus.setAll(beta, 1.);              // (Interior, Exterior)
				return 0;
			}
			double coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.
				if (Interface(p) <= 0) 		return mus[0];
				else						return mus[1];
			}
			double P(FVector_double& p) {
				double x = p[0], y = p[1];
				static FVector_double vp(2);
				P(p, vp);
				if (Interface(p) > 0)	return vp(1);
				else					return vp(0);
			}
			double	P(FVector_double& p, FVector_double& vp) {
				double L = Interface(p);
				double beta = beta_(p);
				vp.setAll(L / beta, L);
				return 0;
			}
			void DP(FVector_double& p, FVector_double& vDP) {
				double x = p[0], y = p[1];
				static FMatrix_double mDPS(2, 2);
				DP(p, mDPS);
				if (Interface(p) > 0)		vDP = mDPS[1];
				else						vDP = mDPS[0];
			}
			void	DP(FVector_double& p, FMatrix_double& mDPs){
				double x = p[0], y = p[1];
				static FVector_double st_vDInterface(2);
				static FVector_double st_vDbeta(2);

				double L = Interface(p);
				double beta = beta_(p);
				Dbeta_(p, st_vDbeta);
				DInterface(p, st_vDInterface);

				// (L'beta-L beta'     ) / beta^2

				mDPs[0][0] = st_vDInterface[0] * beta - L*st_vDbeta[0];
				mDPs[0][1] = st_vDInterface[1] * beta - L*st_vDbeta[1];
				mDPs[0][0] = mDPs[0][0] / beta / beta;
				mDPs[0][1] = mDPs[0][1] / beta / beta;

				mDPs[1] = st_vDInterface;

			}
			double F(FVector_double& p) {
				static FVector_double vp(2);
				F(p, vp);
				if (Interface(p) > 0)	return vp[1];
				else					return vp[0];
			}
			double	F(FVector_double& p, FVector_double& vF) {

				static FVector_double st_vDInterface(2);
				static FVector_double st_vDbeta(2);
				static FMatrix_double st_mDDInterface(2, 2);
				static FMatrix_double st_mDDbeta(2, 2);

				double L = Interface(p);
				double beta = beta_(p);

				double Numerator = 0;

				Dbeta_(p, st_vDbeta);
				DDbeta_(p, st_mDDbeta);
				DInterface(p, st_vDInterface);
				DDInterface(p, st_mDDInterface);

				Numerator = st_mDDInterface[0][0] * beta*beta - L*st_mDDbeta[0][0] * beta - st_vDInterface[0] * beta*st_vDbeta[0] + L*st_vDbeta[0] * st_vDbeta[0];
				Numerator += st_mDDInterface[1][1] * beta*beta - L*st_mDDbeta[1][1] * beta - st_vDInterface[1] * beta*st_vDbeta[1] + L*st_vDbeta[1] * st_vDbeta[1];

				vF[0] = -Numerator / beta / beta;
				vF[1] = -st_mDDInterface[0][0] - st_mDDInterface[1][1];

				return 0;
			}
		};
		class P_IIM_CUBIC_CURVE : public FEM_PROBLEM { //-div(mu▽p) = f
		public:
			void initialize(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);
			//	Input("mum", mum);
			//	Input("mup", mup);
				mum = 1.;
				mup = 1000.;
			}
			double Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				return y-3*x*(x-0.3)*(x-0.8)-0.38;
			}
			void DInterface(FVector_double& p, FVector_double& vDI)	{
				double x = p[0], y = p[1];
				vDI.setAll(-9.*x*x+6.6*x-0.72 , 1.);
			}
			void DDInterface(FVector_double& p, FMatrix_double& mDDI)	{
				double x = p[0], y = p[1];
				mDDI[0][0] = -18.*x+6.6;
				mDDI[0][1] = 0.;
				mDDI[1][0] = 0.;
				mDDI[1][1] = 0.;
			}
			double coef_mu(FVector_double& p, FVector_double& mus) {
				double beta = beta_(p);
				mus.setAll(mum, mup);              // (Interior, Exterior)
				return 0;
			}
			double coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.
				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.
				if (Interface(p) <= 0) 		return mus[0];
				else						return mus[1];
			}
			double P(FVector_double& p) {
				double x = p[0], y = p[1];
				static FVector_double vp(2);
				P(p, vp);
				if (Interface(p) > 0)	return vp(1);
				else					return vp(0);
			}
			double	P(FVector_double& p, FVector_double& vp) {
				double L = Interface(p);
				vp.setAll(L / mum, L / mup);
				return 0;
			}
			void DP(FVector_double& p, FVector_double& vDP) {
				double x = p[0], y = p[1];
				static FMatrix_double mDPS(2, 2);
				DP(p, mDPS);
				if (Interface(p) > 0)		vDP = mDPS[1];
				else						vDP = mDPS[0];
			}
			void	DP(FVector_double& p, FMatrix_double& mDPs){
				double x = p[0], y = p[1];
				static FVector_double st_vDInterface(2);
				DInterface(p, st_vDInterface);

				mDPs[0][0] = st_vDInterface[0] / mum;
				mDPs[0][1] = st_vDInterface[1] / mum;

				mDPs[1][0] = st_vDInterface[0] / mup;
				mDPs[1][1] = st_vDInterface[1] / mup;
	
			}
			double F(FVector_double& p) {
				static FVector_double vp(2);
				F(p, vp);
				if (Interface(p) > 0)	return vp[1];
				else					return vp[0];
			}
			double	F(FVector_double& p, FVector_double& vF) {

				static FMatrix_double st_mDDInterface(2, 2);

				DDInterface(p, st_mDDInterface);

				vF[0] = -st_mDDInterface[0][0] - st_mDDInterface[1][1];
				vF[1] = -st_mDDInterface[0][0] - st_mDDInterface[1][1];

				return 0;
			}
		};
		class P_IIM_CUBIC_CURVE_DB_ : public FEM_PROBLEM { //-div(mu▽p) = f
		public:
			void initialize(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);
				//	Input("mum", mum);
				//	Input("mup", mup);
				mum = 1.;
				mup = 10.;
			}
			double Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				return y - 3 * x*(x - 0.3)*(x - 0.8) - 0.4;
			}
			void DInterface(FVector_double& p, FVector_double& vDI)	{
				double x = p[0], y = p[1];
				vDI.setAll(-9.*x*x + 6.6*x - 0.72, 1.);
			}
			void DDInterface(FVector_double& p, FMatrix_double& mDDI)	{
				double x = p[0], y = p[1];
				mDDI[0][0] = -18.*x + 6.6;
				mDDI[0][1] = 0.;
				mDDI[1][0] = 0.;
				mDDI[1][1] = 0.;
			}
			double coef_mu(FVector_double& p, FVector_double& mus) {
				double beta = beta_(p);
				mus.setAll(mum, mup);              // (Interior, Exterior)
				return 0;
			}
			double coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.
				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.
				if (Interface(p) <= 0) 		return mus[0];
				else						return mus[1];
			}
			double P(FVector_double& p) {
				double x = p[0], y = p[1];
				static FVector_double vp(2);
				P(p, vp);
				if (Interface(p) > 0)	return vp(1);
				else					return vp(0);
			}
			double	P(FVector_double& p, FVector_double& vp) {
				double x = p[0], y = p[1]; 
				double L = Interface(p);
				vp.setAll( (x*x+y*y) / mum, sin(x+y) / mup); 
				return 0;
			}
			void DP(FVector_double& p, FVector_double& vDP) {
				double x = p[0], y = p[1];
				static FMatrix_double mDPS(2, 2);
				DP(p, mDPS);
				if (Interface(p) > 0)		vDP = mDPS[1];
				else						vDP = mDPS[0];
			}
			void	DP(FVector_double& p, FMatrix_double& mDPs){
				double x = p[0], y = p[1];
			 
				mDPs[0][0] = 2.*x / mum;
				mDPs[0][1] = 2.*y / mum;

				mDPs[1][0] = cos(x+y) / mup;
				mDPs[1][1] = cos(x + y) / mup; 

			}
			double F(FVector_double& p) {
				static FVector_double vp(2);
				F(p, vp);
				if (Interface(p) > 0)	return vp[1];
				else					return vp[0];
			}
			double	F(FVector_double& p, FVector_double& vF) {
				double x = p[0], y = p[1]; 

				vF[0] = -4. ;
				vF[1] = sin(x+y)*2. ; 

				return 0;
			} 
			double	P_Jump(FVector_double& p) {
				//static FVector_double ps(2);
				//P(p, ps);
				//return (ps[0] - ps[1]);
				static FVector_double ps(2);
				P(p, ps);
				double x = p[0], y = p[1];
				double r2 = x*x + y*y;
				double r = sqrt(r2);
				static FVector_double mus(2);

				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				return (ps[0] - ps[1]);
			} 
			double	Flux_Jump(FVector_double& p, FVector_double& vN) {
				static FMatrix_double dps(2, 2);
				static FVector_double mus(2);
				static FVector_double dp_exact(2);
				double x = p[0], y = p[1];
				DP(p, dps);
				coef_mu(p, mus);

				return (mus[0] * dps[0] - mus[1] * dps[1], vN); 
			}
			 
		};
		class P_IIM_PEANUT_DB_ : public FEM_PROBLEM { //-div(mu▽p) = f
		public:
			void initialize(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);
				//	Input("mum", mum);
				//	Input("mup", mup);
				mum = 1.;
				mup = 10.;
				r0 = 0.06;
			}
			double Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				return x*x*x*x / 2.0 - x*x / 4.0 + y*y - r0;
			} 
			double coef_mu(FVector_double& p, FVector_double& mus) {
				double beta = beta_(p);
				mus.setAll(mum, mup);              // (Interior, Exterior)
				return 0;
			}
			double coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.
				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.
				if (Interface(p) <= 0) 		return mus[0];
				else						return mus[1];
			}
			double P(FVector_double& p) {
				double x = p[0], y = p[1];
				static FVector_double vp(2);
				P(p, vp);
				if (Interface(p) > 0)	return vp(1);
				else					return vp(0);
			}
			double	P(FVector_double& p, FVector_double& vp) {
				double x = p[0], y = p[1];
				double L = Interface(p);
				vp.setAll( (4. - x*x-y*y ) / mum, 2*cos(x + y) / mup);
				return 0;
			}
			void DP(FVector_double& p, FVector_double& vDP) {
				double x = p[0], y = p[1];
				static FMatrix_double mDPS(2, 2);
				DP(p, mDPS);
				if (Interface(p) > 0)		vDP = mDPS[1];
				else						vDP = mDPS[0];
			}
			void	DP(FVector_double& p, FMatrix_double& mDPs){
				double x = p[0], y = p[1];

				mDPs[0][0] = -2.*x / mum;
				mDPs[0][1] = -2.*y / mum;

				mDPs[1][0] = -2*sin(x + y) / mup;
				mDPs[1][1] = -2 * sin(x + y) / mup;

			}
			double F(FVector_double& p) {
				static FVector_double vp(2);
				F(p, vp);
				if (Interface(p) > 0)	return vp[1];
				else					return vp[0];
			}
			double	F(FVector_double& p, FVector_double& vF) {
				double x = p[0], y = p[1];

				vF[0] = 4.;
				vF[1] = cos(x + y)*4.;

				return 0;
			}
			double	P_Jump(FVector_double& p) {
				//static FVector_double ps(2);
				//P(p, ps);
				//return (ps[0] - ps[1]);
				static FVector_double ps(2);
				P(p, ps);
				double x = p[0], y = p[1];
				double r2 = x*x + y*y;
				double r = sqrt(r2);
				static FVector_double mus(2);

				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				return (ps[0] - ps[1]);
			}
			double	Flux_Jump(FVector_double& p, FVector_double& vN) {
				static FMatrix_double dps(2, 2);
				static FVector_double mus(2);
				static FVector_double dp_exact(2);
				double x = p[0], y = p[1];
				DP(p, dps);
				coef_mu(p, mus);

				return (mus[0] * dps[0] - mus[1] * dps[1], vN);
			}

		};
		class P_IIM_CIRCLE_U_REFLECT : public FEM_PROBLEM { //-div(mu▽p) = f
		public:
			void	input() {
				Input("mum", mum);
				Input("mup", mup);
				Input("rO", r0);
			}
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				__.dim = 2;
				__.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);
				input();
			}

			double	Interface(double r) {												// 내부에서 음수의 값을 가지도록 한다.
				return (r - r0);
			}

			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);

				return (r - r0);
			}

			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}
			double	coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) <= 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}
			double	P(FVector_double& p, FVector_double& ps) {
				double x = p[0], y = p[1];
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.
				mus.setAll(mum, mup);														// (Interior, Exterior)
				ps.setAll(
					1 / mus[0] * (x*x + y*y - r0*r0) * 2 * y, -1 / mus[1] * (x*x + y*y - r0*r0) * 2 * y
					);
				return 0;
			}

			double	P(FVector_double& p) {
				static FVector_double ps(2);
				P(p, ps);																	// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) <= 0) {
					return ps[0];
				}
				else {
					return ps[1];
				}
			}

			double	P_Jump(FVector_double& p) {
				static FVector_double ps(2);
				P(p, ps);
				return (ps[0] - ps[1]);
			}

			void	DP(FVector_double& p, FMatrix_double& dps) {
				double x = p[0], y = p[1];
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.
				mus.setAll(mum, mup);														// (Interior, Exterior)

				dps.setAll( //  -1/mus[0]*(x*x+y*y-r0*r0)*2*x
					1 / mus[0] * 2 * x * 2 * y, 1 / mus[0] * ((x*x + y*y - r0*r0) * 2 + 2 * y * 2 * y),
					-1 / mus[1] * 2 * x * 2 * y, -1 / mus[1] * ((x*x + y*y - r0*r0) * 2 + 2 * y * 2 * y)
					);
			}

			void	DP(FVector_double& p, FVector_double& dp) {
				static FMatrix_double dps(2, 2);
				DP(p, dps);

				if (Interface(p) <= 0) {
					dp = dps[0];
				}
				else {
					dp = dps[1];
				}
			}

			double	Flux_Jump(FVector_double& p, FVector_double& vN) {
				static FMatrix_double dps(2, 2);
				static FVector_double mus(2);
				DP(p, dps);
				coef_mu(p, mus);
				return (mus[0] * dps[0] - mus[1] * dps[1], vN);
			}



			double	F(FVector_double& vRealP, FVector_double& fs) {
				double x = vRealP[0], y = vRealP[1];
				static FVector_double mus(2);


				// f -= μ△U 
				coef_mu(vRealP, mus);
				fs.setAll(-16 * y, 16 * y);

				return 0;
			}

			double	F(FVector_double& p) {
				static FVector_double fs(2);
				F(p, fs);
				if (Interface(p) < 0) {
					return fs[0];
				}
				else {
					return fs[1];
				}
			}

		};
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		//============================================================================
		//              ELLIPTIC: P_IIM_CONST_CIRCLE (J1: Jump    J2: Flux Jump)
		//============================================================================
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
	
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		//============================================================================
		//              ELLIPTIC: P_IIM_CONST_CIRCLE (J1: Jump    J2: Flux Jump)
		//============================================================================
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		class P_IIM_CONST_CIRCLE: public FEM_PROBLEM {
		public:
			void	initialize	(FEM_VARIABLES::ENTIRE& __) {
			//	Input("r0",	r0);
				r0 = 1.04032;
				mum = 1.;
				mup = 10000.;
			//	Input("mum", mum);
			//	Input("mup", mup);

				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1.,-1., 1.,1.);
			}
			double	Interface	(double r) {												// 내부에서 음수의 값을 가지도록 한다.
				return (r - r0);
			}

			double	Interface	(FVector_double& p) {
				double x=p[0], y=p[1];
				double r = sqrt(x*x + y*y);

				return (r - r0);
			}
			double	coef_mu		(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}
			double	coef_mu		(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if(Interface(p) <= 0) {
					return mus[0];
				} else { 
					return mus[1];
				}
			}
			double	P			(FVector_double& p, FVector_double& ps) {
				double x = p[0], y = p[1];
				ps.setAll(1., 0.);															// (Interior, Exterior)
				return 0;
			}
			double	P			(FVector_double& p) {
				static FVector_double ps(2);
				P(p, ps);																	// 두 값을 호출해서 알맞게 돌려준다.

				if(Interface(p) <= 0) {
					return ps[0];
				} else { 
					return ps[1];
				}
			}
			double	P_Jump		(FVector_double& p) {
				static FVector_double ps(2);
				P(p, ps);
				return (ps[0] - ps[1]);
			}
			void	DP			(FVector_double& p, FMatrix_double& dps) {
				double x = p[0], y = p[1];
				dps.setAll(
					0.,	0.,
					0.,	0.
				);
			}
			void	DP			(FVector_double& p, FVector_double& dp) {
				static FMatrix_double dps(2,2);
				DP(p, dps);

				if(Interface(p) <= 0) {
					dp = dps[0];
				} else {
					dp = dps[1];
				}
			}
			void	V(FVector_double& p, FVector_double& dp) {
				static FMatrix_double dps(2, 2);
				DP(p, dps);

				if (Interface(p) <= 0) {
					dp.op("=", -mum, dps[0]);
				}
				else {
					dp.op("=", -mup, dps[1]);
				}
			}
			double	Flux_Jump	(FVector_double& p, FVector_double& vN) {
				static FMatrix_double dps(2,2);
				static FVector_double mus(2);
				DP(p, dps);
				coef_mu(p, mus);
				return ( mus[0]*dps[0] - mus[1]*dps[1], vN );
			}
			double	F			(FVector_double& p, FVector_double& fs) {
				double x=p[0], y=p[1];
				fs.setAll(0., 0.);
				return 0;
			}
			double	F			(FVector_double& p) {
				static FVector_double fs(2);
				F(p, fs);
				if(Interface(p) <= 0) {
					return fs[0];
				} else {
					return fs[1];
				}
			}
		};

		class P_IIM_GH_LINE_INTERFACE : public FEM_PROBLEM {
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				cout << "GH Example " << endl;
				mum = 0.001;
				mup = 1.;
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(0., 0.,  CV.PI / 2, CV.PI / 2);
				phi =0.;
			}
			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				double t = x + y;
				double r = (t - 1.)*(t - 3.);
				return r;
			}

			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);
				return 0;
			}
			double	coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double	coef_mu(FVector_double & p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.
				if (Interface(p) < 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}
			
			double	P(FVector_double& p) {
				double t = 1.;
				double x = p[0], y = p[1];
				double s = x + y;
				double rt;
				double red_;
				if (Interface(p) > 0){
					if (s < 1.)
						rt = (-(s - 1.) + (s - 1.)*(s - 1.))*(2. - t)*mum + 100.;
					if (s > 3.){
						red_ = -(2. / 3.)*(2 - t);
						rt = (-(s - 3.) - (s - 3.)*(s - 3.))*(2. - t)*mum + 100. + red_;
					}
				}
				if (Interface(p) <= 0)
					rt = (-1. / 3. * (s - 1.)*(s - 1.)*(s - 1.) + (s - 1.)*(s - 1.) - (s - 1.))  * (2. - t) + 100 + phi;
				rt = rt * 10;
				//	rt = rt/100;
				return rt;
			}
			double	P(FVector_double& p, FVector_double& vp) {
				double t = 1.;
				double x = p[0], y = p[1];
				double s = x + y;
				double red_ = 0;
				

				if ( abs(s-3) <= abs(s-1) ){
					red_ = -(2. / 3.)*(2 - t);
					vp[1] = (-(s - 3.) - (s - 3.)*(s - 3.))*(2. - t)*mum + 100. + red_;
				}
				if (abs(s - 1) <= abs(s - 3)){
					vp[1] = (-(s - 1.) + (s - 1.)*(s - 1.))*(2. - t)*mum + 100.;
				} 
				vp[0] = (-1. / 3. * (s - 1.)*(s - 1.)*(s - 1.) + (s - 1.)*(s - 1.) - (s - 1.))  * (2. - t) + 100;

				vp.op("=",10.,vp);;
	
				return 0.;
			}

			void	DP(FVector_double& p, FVector_double& vDP)	{
				double t = 1.;
				double x = p[0], y = p[1];
				double s = x + y;

				if (Interface(p) > 0){
					if (s < 1){
						vDP[0] = (-1. + 2.*(s - 1.))*(2. - t) *mum;
						vDP[1] = (-1. + 2.*(s - 1.))*(2. - t) *mum;
					}
					if (s > 3){
						vDP[0] = (-1. - 2.*(s - 3.))*(2. - t) *mum;
						vDP[1] = (-1. - 2.*(s - 3.))*(2. - t) *mum;
					}
				}
				if (Interface(p) <= 0){
					vDP[0] = (-(s - 1.)*(s - 1.) + 2.* (s - 1.) - 1.) *(2. - t);
					vDP[1] = (-(s - 1.)*(s - 1.) + 2.* (s - 1.) - 1.)  *(2. - t);
				}
				vDP[0] = vDP[0] * 10;
				vDP[1] = vDP[1] * 10;
			}
			void	DP(FVector_double& p, FMatrix_double& mDP)	{
				double t = 1.;
				double x = p[0], y = p[1];
				double s = x + y;

				if (abs(s - 1) <= abs(s - 3)){
					mDP[1][0] = (-1. + 2.*(s - 1.))*(2. - t) *mum;
					mDP[1][1] = (-1. + 2.*(s - 1.))*(2. - t) *mum;
				}
				if (abs(s - 3) <= abs(s - 1)){
					mDP[1][0] = (-1. - 2.*(s - 3.))*(2. - t) *mum;
					mDP[1][1] = (-1. - 2.*(s - 3.))*(2. - t) *mum;
				}

				mDP[0][0] = (-(s - 1.)*(s - 1.) + 2.* (s - 1.) - 1.) *(2. - t);
				mDP[0][1] = (-(s - 1.)*(s - 1.) + 2.* (s - 1.) - 1.)  *(2. - t);

				mDP[0].op("=", 10., mDP[0]);
				mDP[1].op("=", 10., mDP[1]);
			}
			void	DDP(FVector_double& p, FMatrix_double& mDP)	{
				double t = 1.;
				double x = p[0], y = p[1];
				double s = x + y;

				if (Interface(p) > 0){
					if (s < 1){
						mDP[0][0] = 2.*(2. - t)*mum;
						mDP[1][1] = 2.*(2. - t)*mum;
					}
					if (s > 3){
						mDP[0][0] = -2.*(2. - t)*mum;
						mDP[1][1] = -2.*(2. - t)*mum;
					}
				}
				if (Interface(p) <= 0){
					mDP[0][0] = (-2. * (s - 1.) + 2.) *(2. - t);
					mDP[1][1] = (-2. * (s - 1.) + 2.) *(2. - t);;
				}
				mDP[0][0] = mDP[0][0] * 10;
				mDP[1][1] = mDP[1][1] * 10;
				
			}
			void	DDP(FVector_double& p, FCube_double& cDP)	{
				double t = 1.;
				double x = p[0], y = p[1];
				double s = x + y;

				if (abs(s - 1) <= abs(s - 3)){
					cDP[1][0][0] = 2.*(2. - t)*mum * 10;
					cDP[1][1][1] = 2.*(2. - t)*mum * 10;
				}
				if (abs(s - 3) <= abs(s - 1)){
					cDP[1][0][0] = -2.*(2. - t)*mum * 10;
					cDP[1][1][1] = -2.*(2. - t)*mum * 10;
				}
				cDP[0][0][0] = (-2. * (s - 1.) + 2.) *(2. - t) * 10;
				cDP[0][1][1] = (-2. * (s - 1.) + 2.) *(2. - t) * 10;
				
			}

			void	V(FVector_double& p, FVector_double& vDV) {
				double t = 1.;
				double x = p[0], y = p[1];
				
				static FVector_double stv_vDP(2);
				DP(p, stv_vDP);

				vDV[0] = -stv_vDP[0] * coef_mu(p);
				vDV[1] = -stv_vDP[1] * coef_mu(p);
			}
			void	V(FVector_double& p, FMatrix_double & vDV) {
				double t = 1.;
				double x = p[0], y = p[1];

				static FMatrix_double stv_mDP(2);
				static FVector_double stv_mus(2);
				coef_mu(p, stv_mus);
		
				DP(p, stv_mDP);

				vDV[0][0] = -stv_mDP[0][0] * stv_mus[0];
				vDV[0][1] = -stv_mDP[0][1] * stv_mus[0];

				vDV[1][0] = -stv_mDP[1][0] * stv_mus[1];
				vDV[1][1] = -stv_mDP[1][1] * stv_mus[1];
			}

			void	DV(FVector_double& p, FMatrix_double & vDV) {
				double t = 1.;
				double x = p[0], y = p[1];

				static FVector_double stv_vDP(2);
				static FMatrix_double sqt_DDP(2, 2);

				DDP(p, sqt_DDP);

				vDV[0][0] = -sqt_DDP[0][0] * coef_mu(p);
				vDV[1][1] = -sqt_DDP[1][1] * coef_mu(p);
			}

			double	F(FVector_double& p) {

				double x = p[0], y = p[1];
				double rt;
				double lap_p;

				static FMatrix_double sqt_DDP(2, 2);
				
				DDP(p, sqt_DDP);
				
				lap_p = sqt_DDP[0][0] + sqt_DDP[1][1];
				rt = -lap_p*coef_mu(p);;

				return rt;

			}
			double	F(FVector_double& p, FVector_double& vF) {

				double x = p[0], y = p[1];

				static FCube_double sqt_cDDP(2, 2, 2);

				DDP(p, sqt_cDDP);

				vF[0] = -mum*(sqt_cDDP[0][0][0] + sqt_cDDP[0][1][1]);
				vF[1] = -mup*(sqt_cDDP[1][0][0] + sqt_cDDP[1][1][1]);

				return 0.;

			}
		};
		class P_IIM_Eigen : public FEM_PROBLEM { //-div(mu▽p) = lambda u
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __){
				dim = __.dim = 2;
				//RX = __.RX.make(__.dim, __.dim).setAll(-CV.PI/2.,-CV.PI/2.,CV.PI/2.,CV.PI/2.);
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);

				Input("Boundary", rB);
				Input("Radious", r0);

				Input("mum", mum);
				Input("mup", mup);
			}
			double	Boundary(FVector_double& p) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				double theta = MATH::slope_to_radian(x, y);

				return (r - rB);
			}
			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				double theta = MATH::slope_to_radian(x, y);

				return (r - r0);
			}
			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}
			double	coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) < 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}
		};
		class P_IIM_Eigen2 : public FEM_PROBLEM { //-div(mu▽p) = lambda u 
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);
				//RX = __.RX.make(__.dim, __.dim).setAll(-CV.PI,-CV.PI, CV.PI,CV.PI);
				//RX = __.RX.make(__.dim, __.dim).setAll(0,0, CV.PI,CV.PI);

				printf("\n[0] Circle");
				printf("\n[1] Sharp edge");
				printf("\n[2] Star shape");
				printf("\n[3] Line");
				printf("\n[4] Sharp edge inside");
				printf("\n[5] Ellipse");

				Input("\nChoose a Interface", nInterface);

				Input("mum", mum);
				Input("mup", mup);

				switch (nInterface){
				case 0:
					Input("r", r0);
					break;
				case 1:
					Input("theta", k);
					k = k / 180.*CV.PI;
					break;
				case 3:
					vDirection.make(__.dim);													// 방향벡터의 왼쪽이 Omega^- 가 되도록 한다.
					vCenter.make(__.dim);														// 직선의 중심이 어디인지를 나타낸다.

					Input("center-x", vCenter[0]);
					Input("center-y", vCenter[1]);
					Input("x-direction", vDirection[0]);
					Input("y-direction", vDirection[1]);

					vDirection.normalize();
					MATH::rotate2D(vDirection, 0., 1., false);									// -90도 회전시킨다.
					break;
				case 5:
					Input("a", a);
					Input("b", b);
					break;
				}
			}
			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				double theta = MATH::slope_to_radian(x, y);

				switch (nInterface) {
				case 0:	// kink(left)

					return r - r0;
				case 1:
					return y*y - (x - 1)*(x - 1)*tan(k)*tan(k)*x;
				case 2: // star shape
					return (r - 0.2*sin(5 * theta - CV.PI / 5) - 0.5);
				case 3:
					return (vDirection, p - vCenter);
				case 4:
					if (x <= 1 + x_intercept) 	return y*y - ((x - 1. - x_intercept)*tan(k))*((x - 1. - x_intercept)*tan(k))*(x - x_intercept);
					else			return 1.;
				case 5:
					r = sqrt(x*x / a / a + y*y / b / b);
					return(r - 1.);
				}
				return 0;
			}
			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}
			double	coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) < 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}
		};



		class P_IIM_Boundary : public FEM_PROBLEM {
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __){
				dim = __.dim = 2;
				//RX = __.RX.make(__.dim, __.dim).setAll(-CV.PI/2.,-CV.PI/2.,CV.PI/2.,CV.PI/2.);
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);
				Input("Boundary", rB);
				Input("Radious", r0);

				Input("mum", mum);
				Input("mup", mup);
			}
			double	Boundary(FVector_double& p) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				double theta = MATH::slope_to_radian(x, y);

				return (r - rB);
			}
			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				double theta = MATH::slope_to_radian(x, y);

				return (r - r0);
			}
			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}
			double	coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (Boundary(p) < 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}
			/*double	P	(FVector_double& p) {
			double x=p[0], y=p[1];
			return sin(x);//sin(2*CV.PI*x)*cos(CV.PI*y);
			}

			void	DP	(FVector_double &p, FVector_double &dp) {
			double x=p[0], y=p[1];
			dp.setAll(cos(x), 0);
			//dp.setAll(2*CV.PI*cos(2*CV.PI*x)*cos(CV.PI*y), -CV.PI*sin(2*CV.PI*x)*sin(CV.PI*y));
			}

			double	F	(FVector_double& p) {
			double x=p[0], y=p[1];
			return sin(x);//5*$(CV.PI,2)*cos(CV.PI*y)*sin(2*CV.PI*x);
			}*/

			double	P(FVector_double& p) {
				double x = p[0], y = p[1];
				return x*y*(1 - x)*(1 - y);
			}

			void	DP(FVector_double& p, FVector_double& vDP) {
				double x = p[0], y = p[1];
				vDP.setAll(y*(1 - y)*(1 - 2 * x), x*(1 - x)*(1 - 2 * y));
			}

			double	F(FVector_double& p) {
				double x = p[0], y = p[1];
				return 2 * (x*(1 - x) + y*(1 - y));
			}


		};



		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		//============================================================================
		//              ELLIPTIC: P_IIM_LINE (J1: Jump    J2: Flux Jump)
		//============================================================================
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		class P_IIM_LINE: public FEM_PROBLEM {
		public:
			void	initialize	(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1.,-1., 1.,1.);
				
				vOp.make(3);

				printf("\n[0] -:c, +:0");
				printf("\n[1] -:x, +:0");
				printf("\n[2] -:cx^2, +:y");
				printf("\n[3] -:x^3+y^3, +:sin(x-y)");
				Input("\nChoose a function", nFunction);
				switch(nFunction) {
					case 0: 
						Input("Choose negative part constant(pasitive zero)", vOp[0]);
						break;
					case 2: 
						Input("Constant multiplication", vOp[0]);
						break;

				}
				Input("mum", mum);
				Input("mup", mup);

				vDirection.make(__.dim);													// 방향벡터의 왼쪽이 Omega^- 가 되도록 한다.
				vCenter.make(__.dim);														// 직선의 중심이 어디인지를 나타낸다.

				Input("center-x", vCenter[0]);
				Input("center-y", vCenter[1]);
				Input("x-direction", vDirection[0]);
				Input("y-direction", vDirection[1]);
				Input("Save type(0:fill3d 1:patch)", VAR.nData[0]);
				
				vDirection.normalize();
				MATH::rotate2D(vDirection, 0., 1., false);									// -90도 회전시킨다.
			}
			double	Interface	(FVector_double& p) {
				//double x=p[0], y=p[1];
				//double r = sqrt(x*x + y*y);

				return (vDirection, p-vCenter);												// 내적값을 준다.
			}
			double	coef_mu		(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}
			double	coef_mu		(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if(io == CV.IN) return mus[0];
				return mus[1];
			}
			double	coef_mu		(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if(Interface(p) < 0) {
					return mus[0];
				} else { 
					return mus[1];
				}
			}
			double	P			(FVector_double& p, FVector_double& ps) {
				double x = p[0], y = p[1];
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.
				
				switch(nFunction) {
					case -1:	ps.setAll(x*x/mus[0], x*x/mus[1]);							// jump가 없는 경우
						break;
					case 0:		ps.setAll(vOp[0], 0.);															// (Interior, Exterior)
						break;
					case 1:		ps.setAll(x, 0.);
						break;
					case 2:		ps.setAll(vOp[0]*x*x, y);
						break;
					case 3:		ps.setAll((x*x*x + y*y*y)/mus[0], (sin(x-y) - 1)/mus[1]);
						break;
				}
				return 0;
			}
			double	P			(FVector_double& p) {
				static FVector_double ps(2);
				P(p, ps);																	// 두 값을 호출해서 알맞게 돌려준다.

				if(Interface(p) < 0) {
					return ps[0];
				} else { 
					return ps[1];
				}
			}
			double	P_Jump		(FVector_double& p) {
				static FVector_double ps(2);
				P(p, ps);
				return (ps[0] - ps[1]);
			}
			void	DP			(FVector_double& p, FMatrix_double& dps) {
				double x = p[0], y = p[1];
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				switch(nFunction) {
					case -1:	dps.setAll(2*x/mus[0], 0.,		2*x/mus[1], 0);
						break;
					case 0:		dps.setAll(0., 0.,		0.,	0.);
						break;
					case 1:		dps.setAll(1., 0.,		0., 0.);
						break;
					case 2:		dps.setAll(vOp[0]*2*x, 0.,		0., 1.);
						break;
					case 3:		dps.setAll(3*x*x/mus[0], 3*y*y/mus[0],		cos(x-y)/mus[1], -cos(x-y)/mus[1]);
						break;
				}
			}
			void	DP			(FVector_double& p, FVector_double& dp) {
				static FMatrix_double dps(2,2);
				DP(p, dps);

				if(Interface(p) < 0) {
					dp = dps[0];
				} else {
					dp = dps[1];
				}
			}
			double	Flux_Jump	(FVector_double& p, FVector_double& vN) {
				static FMatrix_double dps(2,2);
				static FVector_double mus(2);
				DP(p, dps);
				coef_mu(p, mus);
				return ( mus[0]*dps[0] - mus[1]*dps[1], vN );
			}
			double	F			(FVector_double& p, FVector_double& fs) {
				static FVector_double mus(2);
				double x=p[0], y=p[1];

				coef_mu(p, mus);
				switch(nFunction) {
					case -1:	fs.setAll(-2., -2.);
						break;
					case 0:		fs.setAll(0., 0.);
						break;
					case 1:		fs.setAll(0., 0.);
						break;
					case 2:		fs.setAll(vOp[0]*-2.*mus[0], 0.);
						break;
					case 3:		fs.setAll(-6.*(x+y), 2*sin(x-y));
						break;
				}

				return 0;
			}
			double	F			(FVector_double& p) {
				static FVector_double fs(2);
				F(p, fs);
				if(Interface(p) < 0) {
					return fs[0];
				} else {
					return fs[1];
				}
			}
		};
		class P_IIM_LINE2: public FEM_PROBLEM { // Governing Equation:  -div(μ▽p) = f
		public:
			void	initialize	(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1.,-1., 1.,1.);
				
				Input("mum", mum);
				Input("mup", mup);
				Input("line", line);
							
			}
			double	Interface	(FVector_double& p) {
				double x=p[0], y=p[1];
				return y + line;
			}
			double	coef_mu		(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}
			double	coef_mu		(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if(io == CV.IN) return mus[0];
				return mus[1];
			}
			double	coef_mu		(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if(Interface(p) < 0) {
					return mus[0];
				} else { 
					return mus[1];
				}
			}
			double	P			(FVector_double& p, FVector_double& ps) {
				double x = p[0], y = p[1];
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.
				ps.setAll(x*x*x*(y+line)/mus[0], x*x*x*(y+line)/mus[1]);
				return 0;
			}
			double	P			(FVector_double& p) {
				static FVector_double ps(2);
				P(p, ps);																	// 두 값을 호출해서 알맞게 돌려준다.

				if(Interface(p) < 0) {
					return ps[0];
				} else { 
					return ps[1];
				}
			}
			void	DP			(FVector_double& p, FMatrix_double& dps) {
				double x = p[0], y = p[1];
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.
				dps.setAll(3.*x*x*(y+line)/mus[0], x*x*x/mus[0], 3.*x*x*(y+line)/mus[1], x*x*x/mus[1]); 				
			}
			void	DP			(FVector_double& p, FVector_double& dp) {
				static FMatrix_double dps(2,2);
				DP(p, dps);

				if(Interface(p) < 0) {
					dp = dps[0];
				} else {
					dp = dps[1];
				}
			}
		
			double	F			(FVector_double& p, FVector_double& fs) {
				static FVector_double mus(2);
				double x=p[0], y=p[1];

				coef_mu(p, mus);
				fs.setAll(-6.*x*(y+line), -6.*x*(y+line));
				return 0;
			}
			double	F			(FVector_double& p) {
				static FVector_double fs(2);
				F(p, fs);
				if(Interface(p) < 0) {
					return fs[0];
				} else {
					return fs[1];
				}
			}
		};
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		//============================================================================
		//              ELLIPTIC: P_IIM_LINE3 
		//============================================================================
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		class P_IIM_LINE3: public FEM_PROBLEM { // Governing Equation:  -div(μ▽p) = f  
		public:
			void	initialize	(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1.,-1., 1.,1.);
				
				Input("mum", mum);
				Input("mup", mup);
				Input("line", line);
							
			}
			double	Interface	(FVector_double& p) {
				double x=p[0], y=p[1];
				return y + line;
			}
			double	coef_mu		(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}
			double	coef_mu		(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if(io == CV.IN) return mus[0];
				return mus[1];
			}
			double	coef_mu		(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if(Interface(p) < 0) {
					return mus[0];
				} else { 
					return mus[1];
				}
			}
			double	P			(FVector_double& p, FVector_double& ps) {
				double x = p[0], y = p[1];
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.
				ps.setAll((x+1)*(x-1)*(y+line)/mus[0], (x+1)*(x-1)*(y+line)/mus[1]);
				return 0;
			}
			double	P			(FVector_double& p) {
				static FVector_double ps(2);
				P(p, ps);																	// 두 값을 호출해서 알맞게 돌려준다.

				if(Interface(p) < 0) {
					return ps[0];
				} else { 
					return ps[1];
				}
			}
			void	DP			(FVector_double& p, FMatrix_double& dps) {
				double x = p[0], y = p[1];
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.
				dps.setAll(2*x*(y+line)/mus[0], (x+1)*(x-1)/mus[0], 2*x*(y+line)/mus[1], (x+1)*(x-1)/mus[1]); 				
			}
			void	DP			(FVector_double& p, FVector_double& dp) {
				static FMatrix_double dps(2,2);
				DP(p, dps);

				if(Interface(p) < 0) {
					dp = dps[0];
				} else {
					dp = dps[1];
				}
			}
		
			double	F			(FVector_double& p, FVector_double& fs) {
				static FVector_double mus(2);
				double x=p[0], y=p[1];

				coef_mu(p, mus);
				fs.setAll(-2.*(y+line), -2.*(y+line));
				return 0;
			}
			double	F			(FVector_double& p) {
				static FVector_double fs(2);
				F(p, fs);
				if(Interface(p) < 0) {
					return fs[0];
				} else {
					return fs[1];
				}
			}
		};
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		//============================================================================
		//              ELLIPTIC: P_IIM_SECTOR
		//============================================================================
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		class P_IIM_SECTOR : public FEM_PROBLEM { // Governing Equation:  -div(μ▽p) = f
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);

				Input("mum", mum);
				Input("mup", mup);
				Input("radius", radius);
				alpha = 2.;
				beta = 1.;
			}
			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				double r = sqrt((x - 1)*(x - 1) + (y + 1)*(y + 1));
				return r - radius;
			}
			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}
			double	coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) < 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}
			double	P(FVector_double& p, FVector_double& ps) {
				double x = p[0], y = p[1];
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.
				ps.setAll(((x - 1)*(x - 1) + (y + 1)*(y + 1) - radius*radius)*sin(CV.PI*x)*sin(CV.PI*y) / mus[0], ((x - 1)*(x - 1) + (y + 1)*(y + 1) - radius*radius)*sin(CV.PI*x)*sin(CV.PI*y) / mus[1]);
				return 0.;
			}
			double	P(FVector_double& p) {
				static FVector_double ps(2);
				P(p, ps);																	// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) < 0) {
					return ps[0];
				}
				else {
					return ps[1];
				}
			}
			void	DP(FVector_double& p, FMatrix_double& dps) {
				double x = p[0], y = p[1];
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.
				dps.setAll((2 * (x - 1)*sin(CV.PI*x)*sin(CV.PI*y) + CV.PI*((x - 1)*(x - 1) + (y + 1)*(y + 1) - radius*radius)*cos(CV.PI*x)*sin(CV.PI*y)) / mus[0], (2 * (y + 1)*sin(CV.PI*x)*sin(CV.PI*y) + CV.PI*((x - 1)*(x - 1) + (y + 1)*(y + 1) - radius*radius)*sin(CV.PI*x)*cos(CV.PI*y)) / mus[0], (2 * (x - 1)*sin(CV.PI*x)*sin(CV.PI*y) + CV.PI*((x - 1)*(x - 1) + (y + 1)*(y + 1) - radius*radius)*cos(CV.PI*x)*sin(CV.PI*y)) / mus[1], (2 * (y + 1)*sin(CV.PI*x)*sin(CV.PI*y) + CV.PI*((x - 1)*(x - 1) + (y + 1)*(y + 1) - radius*radius)*sin(CV.PI*x)*cos(CV.PI*y)) / mus[1]);
			}
			void	DP(FVector_double& p, FVector_double& dp) {
				static FMatrix_double dps(2, 2);
				DP(p, dps);

				if (Interface(p) < 0) {
					dp = dps[0];
				}
				else {
					dp = dps[1];
				}
			}

			double	F(FVector_double& p, FVector_double& fs) {
				static FVector_double mus(2);
				double x = p[0], y = p[1];

				coef_mu(p, mus);
				fs.setAll(-(2 * sin(CV.PI*x)*sin(CV.PI*y) + 2 * (x - 1)*CV.PI*cos(CV.PI*x)*sin(CV.PI*y) + 2 * (x - 1)*CV.PI*cos(CV.PI*x)*sin(CV.PI*y) - CV.PI*CV.PI*((x - 1)*(x - 1) + (y + 1)*(y + 1) - radius*radius)*sin(CV.PI*x)*sin(CV.PI*y) + 2 * sin(CV.PI*x)*sin(CV.PI*y) + 2 * (y + 1)*CV.PI*sin(CV.PI*x)*cos(CV.PI*y) + 2 * (y + 1)*CV.PI*sin(CV.PI*x)*cos(CV.PI*y) - CV.PI*CV.PI*((x - 1)*(x - 1) + (y + 1)*(y + 1) - radius*radius)*sin(CV.PI*x)*sin(CV.PI*y)), -(2 * sin(CV.PI*x)*sin(CV.PI*y) + 2 * (x - 1)*CV.PI*cos(CV.PI*x)*sin(CV.PI*y) + 2 * (x - 1)*CV.PI*cos(CV.PI*x)*sin(CV.PI*y) - CV.PI*CV.PI*((x - 1)*(x - 1) + (y + 1)*(y + 1) - radius*radius)*sin(CV.PI*x)*sin(CV.PI*y) + 2 * sin(CV.PI*x)*sin(CV.PI*y) + 2 * (y + 1)*CV.PI*sin(CV.PI*x)*cos(CV.PI*y) + 2 * (y + 1)*CV.PI*sin(CV.PI*x)*cos(CV.PI*y) - CV.PI*CV.PI*((x - 1)*(x - 1) + (y + 1)*(y + 1) - radius*radius)*sin(CV.PI*x)*sin(CV.PI*y)));
				return 0;
			}
			double	F(FVector_double& p) {
				static FVector_double fs(2);
				F(p, fs);
				if (Interface(p) < 0) {
					return fs[0];
				}
				else {
					return fs[1];
				}
			}
		};
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		//============================================================================
		//              ELLIPTIC: P_IIM_VARIOUS (J1: Jump    J2: Flux Jump)
		//============================================================================
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒

		class P_IIM_VARIOUS: public FEM_PROBLEM { // Governing Equation:  -div(μ▽p) = f
		public:
			void	initialize	(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1.,-1., 1.,1.);
				
		//		Input("\nView (x,y) direction", VAR.nData[0]>>VAR.nData[1]);
				VAR.nData[0] = 30;
				VAR.nData[1] = 30;

				printf("\n[0] Kink");
				printf("\n[1] Circle");
				printf("\n[2] Star Shape");
				printf("\n[3] Cardioid");
				printf("\n[4] Heart");
				printf("\n[5] Straight Line");
				printf("\n[6] Interface Edge");
				printf("\n[7] Kink Hou");
				printf("\n[100] Homogeneous");
		 		Input("\nChoose a Interface", nInterface);
		//		nInterface = 1;

				switch(nInterface) {
					case 1: //circle
						Input("Radious", r0);
					//	r0 = 0.48;
						cout << endl;
						break;

					case 5:	// straight line
						vDirection.make(__.dim);													// 방향벡터의 왼쪽이 Omega^- 가 되도록 한다.
						vCenter.make(__.dim);														// 직선의 중심이 어디인지를 나타낸다.

						Input("center-x", vCenter[0]);
						Input("center-y", vCenter[1]);
						Input("x-direction", vDirection[0]);
						Input("y-direction", vDirection[1]);
						
						vDirection.normalize();
						MATH::rotate2D(vDirection, 0., 1., false);									// -90도 회전시킨다.
						break;

					case 6: // interface edge
						vOp.make(1);
						Input("perturbation: ", perturbed);
						break;
					
					case 7: // Kink Hou
						//__.RX.make(__.dim, __.dim).setAll(-1.,-1., 3.,1.);
						RX = __.RX.make(__.dim, __.dim).setAll(-1.,-1., 3., 1.);
						
						Input("perturbation: ", perturbed);
						break;
				}

				printf("\n");
				printf("\n[0] Complicated Sin");
				printf("\n[1] -:6 x^2 + 7 y^2      +:Sin[3 x y] + Cos[5 x^2 y^2]       beta-:sin(x*y + 3)   beta+:cos(x*x - y*y + 2)");
				printf("\n[2] -:4-x*x-y*y,         +:x*x + y*y");
				printf("\n[3] -:4-x*x-y*y,         +:x*x + y*y    beta-:r^2  beta+:constant");
				printf("\n[4] -:6 x^2 + 7 y^2      +:Sin[3 x y] + Cos[5 x^2 y^2]    beta-:r^2  beta+:constant");
				printf("\n[5] -:x*x + y*y + 2      +:1 - x*x - y*y    beta-:x*y + 3     beta+:x*x - y*y + 3");
				printf("\n[6] -:x*x + y*y + 2      +:1 - x*x - y*y    beta-:mum      beta+:x*x - y*y + x*y +3");
				printf("\n[7] -:sin(2*x*x + y*y + 2)/mum + x      +:cos(1 - x*x - y*y)/mup    beta-:mum      beta+:mup");
				printf("\n[8] -:pow(r*r, 5./6) + sin(x+y)   +:8         beta-:2 + sin(x + y)     beat+:1");
				printf("\n[9] -:const1/mus[0]				+:const2/mus[1]");
				printf("\n[10] -:sin(10xy)/mus[0]			+:cos(y)/mus[1]");
				printf("\n[11] -:x			+:0");
				printf("\n[[ Homogeneous Jumps ]]");
				printf("\n[100] -LevelSet/beta- +:*LevelSet/beta+");
				printf("\n[101] Zilin Lee -:r^3/mum    +:r^3/mup + (1/mum - 1/mup)r0^3");

				Input("\nChoose a Function", nFunction);
			//	nFunction = 101;
				switch(nFunction) {
					case 0:	case 2: case 7: case 10: case 100: case 101:
						Input("mum", mum);
						Input("mup", mup);
				//		mum = 1.;
				//		mup = 1.;
						break;

					case 3: case 4:
						Input("beta+", mup);
						break;

					case 6:
						Input("beta-", mum);
						break;

					case 9:
						//mum = mup = 1;
						Input("mum", mum);
						Input("mup", mup);
						vOp.make(2);
						Input("const1", vOp[0]);
						Input("const2", vOp[1]);
						break;
				}
			}
			double	Interface	(FVector_double& p) {
				double x=p[0], y=p[1];
				double r = sqrt(x*x + y*y);
				double theta = MATH::slope_to_radian(x, y);
								
				switch(nInterface) {
					case 0:	// kink(left)
						if(y>0) return (y+2*x);
						else return (x-2*y);

					case 1: // circle
						return (r - r0);

					case 2: // star shape
						return (r - 0.2*sin(5*theta - CV.PI/5) - 0.5);

					case 3: // cardioid
						return pow(3*r*r - x, 2.) - r*r;

					case 4: // heart
						return pow(3*r*r - x, 2.) - r*r + 0.2;

					case 5: // straight line
						return (vDirection, p-vCenter);	

					case 6: // interface edge
						if(y>=0) return (x+y+perturbed);
						else return (x+perturbed);

					case 7: // Kink Hou
						if(x+y>0) return (y-2*x+perturbed);
						else return (y+0.5*x+perturbed);

					case 100: // homogeneous
						return sin(4*(x*x-y*y));
					//case 5: // kink(upper)
					//	if(y>0
					//	return 
				}
				return 0;												// 내적값을 준다.
			}
			double	coef_mu		(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];

				switch(nFunction) {
					case 0: case 7:	case 9: case 10: case 100: case 101:
						mus.setAll(mum, mup);														// (Interior, Exterior)
						break;

					case 1:
						mus.setAll(sin(x*y + 3), cos(x*x - y*y + 2)); 
						break;

					case 2:
						mus.setAll(x*y+2, x*x-y*y+3);
						mus.setAll(mum, mup);
						break;

					case 3: case 4:
						mus.setAll(x*x + y*y, mup);
						break;

					case 5:
						mus.setAll(x*y + 3, x*x - y*y + 3);
						break;

					case 6:
						mus.setAll(mum, x*x - y*y + x*y + 3);
						break;

					case 8:
						mus.setAll(2 + sin(x+y), 1.);
						break;

					default:
						mus.setAll(1., 1.);
						break;
				}
				return 0;
			}
			double	coef_mu		(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if(io == CV.IN) return mus[0];
				return mus[1];
			}
			double	coef_mu		(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if(Interface(p) < 0) {
					return mus[0];
				} else { 
					return mus[1];
				}
			}
			double	P			(FVector_double& p, FVector_double& ps) {
				double x = p[0], y = p[1];
				double r2 = x*x + y*y;
				double r = sqrt(r2);
				static FVector_double mus(2);
				
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				switch(nFunction) {
					case 0:		ps.setAll(sin(10*x*(-2 + y))/mus[0], x*x/mus[1]);															// (Interior, Exterior)
						break;

					case 1:		ps.setAll(6*x*x + 7*y*y, sin(3*x*y) + cos(5*x*x*y*y));
						break;

					case 2: case 3:
						ps.setAll(x*x - y*y + 3, 1 - x*x - y*y); // / mus[1]);
						break;

					case 4:
						ps.setAll(6*x*x + 7*y*y, (sin(3*x*y) + cos(5*x*x*y*y))/mus[1]);
						break;

					case 5: case 6:
						ps.setAll(x*x + y*y + 2, 1 - x*x - y*y);
						break;

					case 7:
						ps.setAll(sin(2*x*x + y*y + 2)/mus[0]+x, cos(1 - x*x - y*y)/mus[1]);
						break;

					case 8:
						ps.setAll(pow(r2, 5./6) + sin(x+y), 8.);
						break;

					case 9:
						ps.setAll(vOp[0]/mus[0], vOp[1]/mus[1]);
						break;

					case 10:		
						ps.setAll(sin(10*x*y)/mus[0], cos(y)/mus[1]);															// (Interior, Exterior)
						break;

					case 11:
						ps.setAll(x, 0.);
						break;

					case 100:	// homogeneous case
						//ps.setAll((r - 0.2*sin(5*theta - CV.PI/5) + 0.5)/mus[0], (r - 0.2*sin(5*theta - CV.PI/5) + 0.5)/mus[1]);
						ps.setAll(sin(4*(x*x-y*y))/mus[0], sin(4*(x*x-y*y))/mus[1]);
						break;

					case 101:
						ps.setAll(pow(r,3.)/mus[0], pow(r,3.)/mus[1] + (1/mus[0]-1/mus[1])*pow(r0,3.));
						break;
				}
				return 0;
			}
			double	P			(FVector_double& p) {
				static FVector_double ps(2);
				P(p, ps);																	// 두 값을 호출해서 알맞게 돌려준다.

				if(Interface(p) < 0) {
					return ps[0];
				} else { 
					return ps[1];
				}
			}
			double	P_Jump		(FVector_double& p) {
				//static FVector_double ps(2);
				//P(p, ps);
				//return (ps[0] - ps[1]);
				static FVector_double ps(2);
				P(p, ps);
				double x = p[0], y = p[1];
				double r2 = x*x + y*y;
				double r = sqrt(r2);
				static FVector_double mus(2);
				
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.
				
				// 정확히 0이 나와야 하는 경우도(즉, 수학적으로 동일한 식도) 계산과정에서 round off error가 발생한다.
				// 따라서 직접적으로 계산해서 함수를 대입해주어야 한다.
				// -. 되도록이면 계산과정이 적도록
				// -. 위험도: 1.나눗셈 2.곱셈
				switch(nFunction) {
					case 9:
						return (vOp[0]/mus[0] - vOp[1]/mus[1]);

					case 101:
						return 0;

					default:
						return (ps[0] - ps[1]);	
				}
			}
			void	DP			(FVector_double& p, FMatrix_double& dps) {
				double x = p[0], y = p[1];
				double r2 = x*x + y*y;
				double r = sqrt(r2);
				static FVector_double mus(2);
				static FVector_double vDLevelSet(2);	// derivative levelset

				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.
				switch(nFunction) {
					case 0:		
						dps.setAll(10*(-2 + y)*cos(10*x*(-2 + y))/mus[0], 10*x*cos(10*x*(-2 + y))/mus[0],		2*x/mus[1],	0.);
						break;

					case 1:		
						dps.setAll(12*x, 14*y, y*(3*cos(3*x*y) - 10*x*y*sin(5*x*x*y*y)), x*(3*cos(3*x*y) - 10*x*y*sin(5*x*x*y*y)));
						break;	

					case 2:	case 3:
					//	dps.setAll(-2*x, -2*y, 2*x/mus[1], 2*y/mus[1]);
						dps.setAll(-2 * x, -2 * y, 2 * x, 2 * y);
						dps.setAll(2 * x, -2 * y, -2 * x, -2 * y);
						break;

					case 4:		
						dps.setAll(12*x, 14*y, (y*(3*cos(3*x*y) - 10*x*y*sin(5*x*x*y*y)))/mus[1], (x*(3*cos(3*x*y) - 10*x*y*sin(5*x*x*y*y)))/mus[1]);
						break;

					case 5: case 6:
						dps.setAll(2*x, 2*y, -2*x, -2*y);
						break;

					case 7:
						dps.setAll(4*x*cos(2 + 2*x*x + y*y)/mus[0]+1., 2*y*cos(2 + 2*x*x + y*y)/mus[0], 2*x*sin(1 - x*x - y*y)/mus[1], 2*y*sin(1 - x*x - y*y)/mus[1]);
						break;

					case 8:
						dps.setAll((5*x)/(3*pow(r2, 1./6)) + cos(x+y), (5*y)/(3*pow(r2, 1./6)) + cos(x+y), 0., 0.);
						break;

					case 9:
						dps.clear();
						break;

					case 10:
						dps.setAll(10*y*cos(10*x*y)/mus[0], 10*x*cos(10*x*y)/mus[0], 0., -sin(y)/mus[1]);
						break;

					case 11:
						dps.setAll(1., 0., 0., 0.);
						break;

					case 100: // Homogeneous Case (Starfish)
						//dps[0].setAll(x/r + (y/r2)*cos(5*theta - CV.PI/5), y/r - (x/r2)*cos(5*theta - CV.PI/5)) /= (mus[0]);
						//dps[1].setAll(x/r + (y/r2)*cos(5*theta - CV.PI/5), y/r - (x/r2)*cos(5*theta - CV.PI/5)) /= (mus[1]);
						dps[0].setAll(8*x*cos(4*(x*x-y*y)), -8*y*cos(4*(x*x-y*y))) /= mus[0];
						dps[1].setAll(8*x*cos(4*(x*x-y*y)), -8*y*cos(4*(x*x-y*y))) /= mus[1];
						break;

					case 101:
						dps.setAll(3*x*r/mus[0], 3*y*r/mus[0], 3*x*r/mus[1], 3*y*r/mus[1]);
						break;
				}
			}
			void	DP			(FVector_double& p, FVector_double& dp) {
				static FMatrix_double dps(2,2);
				DP(p, dps);

				if(Interface(p) < 0) {
					dp = dps[0];
				} else {
					dp = dps[1];
				}
			}
			void	V(FVector_double& p, FVector_double& dp) {
				static FMatrix_double dps(2, 2);
				static FVector_double mus(2);
				double x = p[0];
				double y = p[1];
				double r2 = x*x + y*y;
				double r = sqrt(r2);
				switch (nFunction) {
				case 101:
					dps.setAll(3 * x*r, 3 * y*r);
				default:
					DP(p, dps);
					coef_mu(p, mus);

					if (Interface(p) <= 0) {
						dp.op("=", -mum, dps[0]);
					}
					else {
						dp.op("=", -mup, dps[1]);
					} 
				}
			}
			double	Flux_Jump	(FVector_double& p, FVector_double& vN) {
				static FMatrix_double dps(2,2);
				static FVector_double mus(2);
				static FVector_double dp_exact(2);
				double x=p[0], y=p[1];
				DP(p, dps);
				coef_mu(p, mus);

				switch(nFunction) {
					case 9: case 101:
						return 0;

					case 10:
						dp_exact.setAll(10*y*cos(10*x*y), 10*x*cos(10*x*y)+sin(y));
						return (dp_exact, vN);

					default:
						return ( mus[0]*dps[0] - mus[1]*dps[1], vN );
				}
				//double fjump = fabs(( mus[0]*dps[0] - mus[1]*dps[1], vN));
				//if(fjump < 1.0E-16) return 0;
				//else return fjump;
			}
			double	F			(FVector_double& p, FVector_double& fs) {
				static FVector_double mus(2);
				double x=p[0], y=p[1];
				double r2 = x*x + y*y;
				double r = sqrt(r2);

				coef_mu(p, mus);
				switch(nFunction) {
					case 0:		fs.setAll(100*(x*x + pow((-2 + y),2.))*sin(10*x*(-2 + y)), -2.);
						break;
					case 1:		fs.setAll(-26*(x*y*cos(3 + x*y) + sin(3 + x*y)), (x*x + y*y)*cos(2 + x*x - y*y)*(100*x*x*y*y*cos(5*x*x*y*y) + 9*sin(3*x*y) + 10*sin(5*x*x*y*y)));
						break;
					case 2:		fs.setAll( 0.*mus[0], 4.*mus[1]);
						break;
					case 3:		fs.setAll(8*(x*x + y*y), -4.);
						break;
					case 4:		fs.setAll(-50*x*x - 54*y*y, (x*x + y*y)*(100*x*x*y*y*cos(5*x*x*y*y) + 9*sin(3*x*y) + 10*sin(5*x*x*y*y)));
						break;
					case 5:		fs.setAll(-12 - 8*x*y, 12 + 8*x*x - 8*y*y);
						break;
					case 6:		fs.setAll(-4*mus[0], 4*(3 + 2*x*x + 2*x*y - 2*y*y));
						break;
					case 7:		fs.setAll(2*(-3*cos(2 + 2*x*x + y*y) + 2*(4*x*x + y*y)*sin(2 + 2*x*x + y*y)),
									4*((x*x + y*y)*cos(1 - x*x - y*y) - sin(1 - x*x - y*y)));
						break;
					case 8:		fs.setAll(-1./(9*pow(r2, 1./6))*(50 + 15*(x+y)*cos(x+y) + 18*pow(r2, 1./6)*cos(2*(x+y)) + 25*sin(x+y) - 36*pow(r2, 1./6)*sin(x+y)), 0.);
						break;
					case 9:		fs.setAll(0., 0.);
						break;
					case 10:	fs.setAll(100*r2*sin(10*x*y), cos(y));
						break;
					case 11:	fs.setAll(0., 0.);
						break;
					case 100:	//fs.setAll((-1/r - 5/r2*sin(5*theta - CV.PI/5))/mus[0], (-1/r - 5/r2*sin(5*theta - CV.PI/5))/mus[1]);
						fs.setAll(64*r2*sin(4*(x*x-y*y))/mus[0], 64*r2*sin(4*(x*x-y*y))/mus[1]);
						break;
					case 101:
						fs.setAll(-9*r, -9*r);
						break;
				}

				return 0;
			}
			double	F			(FVector_double& p) {
				static FVector_double fs(2);
				F(p, fs);
				if(Interface(p) < 0) {
					return fs[0];
				} else {
					return fs[1];
				}
			}
		};
		class P_IIM_EXOTIC_DISCONTINUOUS_ : public FEM_PROBLEM {
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				double A, B;
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);
				//Input("\nView (x,y) direction", VAR.nData[0] >> VAR.nData[1]);
			//	Input("\n\nCircle Radius", r0);
				r0=0.5;

				// case1.
				mum=10.;
				mup=1;

				// case2.
				mum=10;
				mup=1;

			}
			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				double r; 
				
				//Circular Interface 
				r = sqrt(x*x + y*y) - r0;
				
				return r;
			}
 
			int		IO(FVector_double& p) {
				if (Interface(p) < 0.0)	return CV.IN;
				else return CV.OUT;
				return 0;
			}

			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, middle, Exterior)

				return 0;
			}

			double	coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}

			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p)<0.0)	return mus[0];
				return mus[1];
			}

			double	value_varAlpha(FVector_double& p) {
				double x = p[0], y = p[1];
				double value, d ; 
				d = gap; 

				value = d*mup / mug;
				return value;
			}
			double	value_varAlpha(FVector_double& p, int type) {
				double x = p[0], y = p[1];
				double value, d;  
				value = 1.;
				return value;
			}
			double	P(FVector_double& p, FVector_double& ps) {
				double x = p[0], y = p[1], d;
				double q; 
				static FVector_double mus(2) ;
				d = gap;
				coef_mu(p, mus);// 두 값을 호출해서 알맞게 돌려준다.
			
				q = (x*x + y*y) / 2.0;
				ps.setAll(q / mum - r0 / mup + (1. / mup - 1. / mum)*r0*r0 / 2., q / mup); 
				  
				// case1
			//	ps[0] = ps[0] + x*x + y*y;
				// case2s
				ps[0] = ps[0] + 1.5 - x*x - y*y;
			
				return 0.;
			}
			double	P_Jump(FVector_double& p) { 
				double x, y;
				x = p[0];
				y = p[1];
				static FVector_double ps(2);
				P(p, ps);

				// case1
				// return x*x + y*y;
				// case 2
				return  1.5 - x*x - y*y;
			//	return 10.; 
			//	return 0.;
			}
			double	Flux_Jump(FVector_double& p, FVector_double& vN) {

				// case1
			//	return 2.*r0*mum;

				// case 2
				return -2.*r0*mum;
			//	return 0.;
			}
			double	P(FVector_double& p) {
				static FVector_double ps(2);
				P(p, ps);																	// 두 값을 호출해서 알맞게 돌려준다.
				if (Interface(p) >= 0.0)	return ps[1];
				return ps[0];
			}

			void	DP(FVector_double& p, FMatrix_double& dps) {
				double x = p[0], y = p[1];
				double d, dxP, dyP, L1, L2, L3, L4;
				static FVector_double mus(2), dq(dim);
				d = gap;
				coef_mu(p, mus);
		
			//	dps.setAll(x / mum, y / mum, x / mup, y / mup); 
				// case 1.
			//	dps.setAll(x / mum +2.*x, y / mum + 2.*y, x / mup, y / mup);

				// case 2.
				dps.setAll(x / mum - 2.*x, y / mum - 2.*y, x / mup, y / mup);
			}

			void	DP(FVector_double& p, FVector_double& dp) {
				static FMatrix_double dps(2, 2);
				DP(p, dps);

				if (Interface(p)<0.0)	 dp = dps[0];
				else	dp = dps[1];
			}
			double	F(FVector_double& p, FVector_double& fs) {
				double x = p[0], y = p[1], d; 
				static FVector_double mus(2) ;
				d = gap;
				coef_mu(p, mus);
			//	fs.setAll(-2.0, -2.0);
				// case 1.
			//	fs.setAll(-2.0-4.*mum, -2.0);
 				// case 2.
				fs.setAll(-2.0+4.*mum, -2.0);
				return 0;
			}
			double	F(FVector_double& p) {
				static FVector_double fs(2);
				F(p, fs);
				if (Interface(p)<0.0)	 return fs[0];
				else	return fs[1];
			}
		};
		class P_IIM_EXOTIC_DISCONTINUOUS_PEANUT_ : public FEM_PROBLEM {
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				double A, B;
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);
 
				VAR.nData[0] = 30; VAR.nData[1] = 60; 

				r0=0.04; 

				mum=1.;
				mup=1.;
			} 
			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				double r;
				double L1, L2, L3, L4, L5, L6, L7, L8, L9;
				double theta = MATH::slope_to_radian(x, y);
				
				// peanut-shaped
				r = x*x*x*x / 2.0 - x*x / 4.0 + y*y - r0; 
				return r;
			}

			double	InterfaceGrad(FVector_double& p, FVector_double& df) {
				double x = p[0], y = p[1];
				double dLx, dLy;
				double theta = MATH::slope_to_radian(x, y);
				 
				dLx = 2.0*x*x*x - x / 2.0;
				dLy = 2.0*y;
				df.setAll(dLx, dLy);
				 
				return 0.0;
			}

			int		IO(FVector_double& p) {
				if (Interface(p) < 0.0)	return CV.IN;
				else return CV.OUT;
				return 0;
			}

			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, middle, Exterior)

				return 0;
			}

			double	coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}

			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p)<0.0)	return mus[0];
				return mus[1];
			}

			double	value_varAlpha(FVector_double& p) {
				double x = p[0], y = p[1];
				double value, d, tempx, tempy;
				static FVector_double vMus(2);
				
				value = sqrt((x*x*x - x / 4.0)*(x*x*x - x / 4.0) + y*y);
				value = 0.2 / value;
				return value;
			} 

			double	P(FVector_double& p, FVector_double& ps) {
				double x = p[0], y = p[1], d;
				double q;
				double L1, L2, L3, L4;
				static FVector_double mus(2), dq(dim);
				d = gap;
				coef_mu(p, mus);// 두 값을 호출해서 알맞게 돌려준다.

				//the solutions with "Peanut" shape interface with variable alpha
				q = x*x*x*x / 2.0 - x*x / 4.0 + y*y;
				q = q / 2.0;
				ps.setAll(q - 0.2, q );
				return 0;
			}
			double	P(FVector_double& p) {
				static FVector_double ps(2);
				P(p, ps);																	// 두 값을 호출해서 알맞게 돌려준다.
				if (Interface(p) >= 0.0)	return ps[1];
				return ps[0];
			}

			void	DP(FVector_double& p, FMatrix_double& dps) {
				double x = p[0], y = p[1];
				double d, dxP, dyP, L1, L2, L3, L4;
				static FVector_double mus(2), dq(dim);
				d = gap;
				coef_mu(p, mus);
				
				dxP = x*x*x - x / 4.0;
				dyP = y;
				dps.setAll(dxP, dyP, dxP, dyP); 
			}

			void	DP(FVector_double& p, FVector_double& dp) {
				static FMatrix_double dps(2, 2);
				DP(p, dps);

				if (Interface(p)<0.0)	 dp = dps[0];
				else	dp = dps[1];
			}
			double	F(FVector_double& p, FVector_double& fs) {
				double x = p[0], y = p[1];
				double fx, fy, d, L1, L2, L3, L4, dxL1, dyL1, dxL2, dyL2, dxL3, dyL3, dxL4, dyL4;
				static FVector_double mus(2), dq(dim);
				d = gap;
				coef_mu(p, mus);
				
				fx = -1.0* 3.0*(x*x + 1.0 / 4.0);
				fy = fx;
				fs.setAll(fx, fy);
				
				return 0;
			}
			double	F(FVector_double& p) {
				static FVector_double fs(2);
				F(p, fs);
				if (Interface(p)<0.0)	 return fs[0];
				else	return fs[1];
			}
		};
		class P_IIM_EXOTIC_DISCONTINUOUS_PEANUT_REGULAR : public FEM_PROBLEM {
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				double A, B;
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);
 
				VAR.nData[0] = 30; VAR.nData[1] = 60; 
			//	Input("\n\nCoefficient of the solution functions (<0.03)", r0);
			//	cout << "r0=" << r0 << endl; 
				r0=0.02;
				//cout << "r0=" << r0 << endl; 
				Input("mu_inside", mum);
				Input("mu_outside", mup); 
			//	Input("nBasis : 3(4) or 5(6)", nBasis);
				nBasis=5.;
				cout << "mum=" << mum << endl;
				cout << "mup=" << mup << endl;
				a=0.;
			} 
			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				double r;
				double L1, L2, L3, L4, L5, L6, L7, L8, L9;
				double theta = MATH::slope_to_radian(x, y);
				
				// peanut-shaped
				r = x*x*x*x / 2.0 -a * x*x + y*y - r0; 
				return r;
			}  
			int		IO(FVector_double& p) {
				if (Interface(p) < 0.0)	return CV.IN;
				else return CV.OUT;
				return 0;
			}

			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, middle, Exterior)

				return 0;
			}

			double	coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}

			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p)<0.0)	return mus[0];
				return mus[1];
			}

			double	value_varAlpha(FVector_double& p) {
				double x = p[0], y = p[1];
				double value, d, tempx, tempy;
				static FVector_double vMus(2);
				
				value = sqrt((x*x*x - x * a)*(x*x*x - x * a) + y*y);
				value = 0.2 / value;
				return value;
			} 

			double	P(FVector_double& p, FVector_double& ps) {
				double x = p[0], y = p[1], d;
				double q;
				double L1, L2, L3, L4;
				static FVector_double mus(2), dq(dim);
				d = gap;
				coef_mu(p, mus);// 두 값을 호출해서 알맞게 돌려준다.

				//the solutions with "Peanut" shape interface with variable alpha
				q = x*x*x*x / 2.0 - x*x *a + y*y;
				q = q / 2.0;
				ps.setAll(q - 0.2, q );
				return 0;
			}
			double	P(FVector_double& p) {
				static FVector_double ps(2);
				P(p, ps);																	// 두 값을 호출해서 알맞게 돌려준다.
				if (Interface(p) >= 0.0)	return ps[1];
				return ps[0];
			}

			void	DP(FVector_double& p, FMatrix_double& dps) {
				double x = p[0], y = p[1];
				double d, dxP, dyP, L1, L2, L3, L4;
				static FVector_double mus(2), dq(dim);
				d = gap;
				coef_mu(p, mus);
				
				dxP = x*x*x - x * a;
				dyP = y;
				dps.setAll(dxP, dyP, dxP, dyP); 
			}

			void	DP(FVector_double& p, FVector_double& dp) {
				static FMatrix_double dps(2, 2);
				DP(p, dps);

				if (Interface(p)<0.0)	 dp = dps[0];
				else	dp = dps[1];
			}
			double	F(FVector_double& p, FVector_double& fs) {
				double x = p[0], y = p[1];
				double fx, fy, d, L1, L2, L3, L4, dxL1, dyL1, dxL2, dyL2, dxL3, dyL3, dxL4, dyL4;
				static FVector_double mus(2), dq(dim);
				d = gap;
				coef_mu(p, mus);
				
				fx = -1.0* 3.0*(x*x + (1.-a)/3.);
				fy = fx;
				fs.setAll(fx, fy);
				
				return 0;
			}
			double	F(FVector_double& p) {
				static FVector_double fs(2);
				F(p, fs);
				if (Interface(p)<0.0)	 return fs[0];
				else	return fs[1];
			}
		};
		class P_IIM_EXOTIC_DISCONTINUOUS_PEANUT_LIKE_: public FEM_PROBLEM {
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				double A, B;
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);
 
				VAR.nData[0] = 30;
				VAR.nData[1] = 60; 
			//	Input("\n\nCoefficient of the solution functions (<0.03)", r0);
			//	cout << "r0=" << r0 << endl; 
				r0=0.03;
				//cout << "r0=" << r0 << endl; 
				Input("mu_inside", mum);
				Input("mu_outside", mup); 
			//	Input("nBasis : 3(4) or 5(6)", nBasis);
				nBasis=5.;
				cout << "mum=" << mum << endl;
				cout << "mup=" << mup << endl;
				a=1.;
			} 
			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				double r;
				double L1, L2, L3, L4, L5, L6, L7, L8, L9;
				double theta = MATH::slope_to_radian(x, y);
				
				// peanut-shaped
				r = x*x*x*x / 2.0 +  x*x*a + y*y - r0; 
				return r;
			}  
			int		IO(FVector_double& p) {
				if (Interface(p) < 0.0)	return CV.IN;
				else return CV.OUT;
				return 0;
			}

			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, middle, Exterior)

				return 0;
			}

			double	coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}

			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p)<0.0)	return mus[0];
				return mus[1];
			}

			double	value_varAlpha(FVector_double& p) {
				double x = p[0], y = p[1];
				double value, d, tempx, tempy;
				static FVector_double vMus(2);
				 
				value = sqrt((x*x*x + x * a)*(x*x*x + x * a) + y*y);
				value = 0.2 / value;
				return value;
			} 

			double	P(FVector_double& p, FVector_double& ps) {
				double x = p[0], y = p[1], d;
				double q;
				double L1, L2, L3, L4;
				static FVector_double mus(2), dq(dim);
				d = gap;
				coef_mu(p, mus);// 두 값을 호출해서 알맞게 돌려준다.

				//the solutions with "Peanut" shape interface with variable alpha
				q =  x*x*x*x / 2.0 +  x*x*a + y*y - r0; 
				q = q / 2.0;
				ps.setAll(q - 0.2, q );
				return 0;
			}
			double	P(FVector_double& p) {
				static FVector_double ps(2);
				P(p, ps);																	// 두 값을 호출해서 알맞게 돌려준다.
				if (Interface(p) >= 0.0)	return ps[1];
				return ps[0];
			}

			void	DP(FVector_double& p, FMatrix_double& dps) {
				double x = p[0], y = p[1];
				double d, dxP, dyP, L1, L2, L3, L4;
				static FVector_double mus(2), dq(dim);
				d = gap;
				coef_mu(p, mus);
				 
				dxP = x*x*x + x * a;
				dyP = y;
				dps.setAll(dxP, dyP, dxP, dyP); 
			}

			void	DP(FVector_double& p, FVector_double& dp) {
				static FMatrix_double dps(2, 2);
				DP(p, dps);

				if (Interface(p)<0.0)	 dp = dps[0];
				else	dp = dps[1];
			}
			double	F(FVector_double& p, FVector_double& fs) {
				double x = p[0], y = p[1];
				double fx, fy, d, L1, L2, L3, L4, dxL1, dyL1, dxL2, dyL2, dxL3, dyL3, dxL4, dyL4;
				static FVector_double mus(2), dq(dim);
				d = gap;
				coef_mu(p, mus);
				
				fx = -1.0* 3.0*(x*x + (1.+a)/3.);
				fy = fx;
				fs.setAll(fx, fy);
				
				return 0;
			}
			double	F(FVector_double& p) {
				static FVector_double fs(2);
				F(p, fs);
				if (Interface(p)<0.0)	 return fs[0];
				else	return fs[1];
			}
		};
		class P_IIM_EXOTIC_DISCONTINUOUS_ELLIPSE : public FEM_PROBLEM {
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				double A, B;
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);
 
				VAR.nData[0] = 30; VAR.nData[1] = 60; 
			//	Input("\n\nCoefficient of the solution functions (<0.03)", r0);
			//	cout << "r0=" << r0 << endl; 
				r0=0.4;
				A2=1;
				B2=2; 
				//cout << "r0=" << r0 << endl; 
			//	Input("mu_inside", mum); 
				
				// case 1.
				a=0.5;
				mum=1;
				mup=10.; 

				// Case 2
			//	a=1.;
			//	mum=0.1;
			//	mup=10.;
			} 
			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				double r;
				double L1, L2, L3, L4, L5, L6, L7, L8, L9;
				double theta = MATH::slope_to_radian(x, y);
				
				// peanut-shaped
				r = sqrt(x*x / A2 + y*y / B2) - r0;
				return r;
			}  
			int		IO(FVector_double& p) {
				if (Interface(p) < 0.0)	return CV.IN;
				else return CV.OUT;
				return 0;
			}

			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, middle, Exterior)

				return 0;
			}

			double	coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}

			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p)<0.0)	return mus[0];
				return mus[1];
			}

			double	value_varAlpha(FVector_double& p) {
				double x = p[0], y = p[1];
				double value, d, tempx, tempy;
				static FVector_double vMus(2);
				
				value =  sqrt(x*x / (A2*A2) + y*y / (B2*B2));
				value = a / value;
				return value;
			} 

			double	P(FVector_double& p, FVector_double& ps) {
				double x = p[0], y = p[1], d;
				double q;
				double L1, L2, L3, L4;
				static FVector_double mus(2), dq(dim);
				d = gap;
				coef_mu(p, mus);// 두 값을 호출해서 알맞게 돌려준다.

				//the solutions with "Peanut" shape interface with variable alpha
				
				q = (x*x / A2 + y*y / B2) / 2.0; 
				// case1.
				ps.setAll(q / mum -a/mup + (1. / mup - 1. / mum)*r0*r0 / 2. + x*y, q / mup);

				// case2.
			//	ps.setAll(q / mum -a/mup + (1. / mup - 1. / mum)*r0*r0 / 2. + (x*x+y*y), q / mup);

				return 0;
			}
			double	P_Jump(FVector_double& p) { 
				double x, y;
				x = p[0];
				y = p[1];
				static FVector_double ps(2);
				P(p, ps);

				// case1.
				return x*y; 

				// case2.
			//	return (x*x+y*y);
			}
			double	Flux_Jump(FVector_double& p, FVector_double& vN) {
				double x=p[0];
				double y=p[1];

				double Px=x/A2;
				double Py=y/B2;

				double vN_x=Px/sqrt(Px*Px+Py*Py);
				double vN_y=Py/sqrt(Px*Px+Py*Py);


				// case 1.
				return (y*vN_x+x*vN_y)*mum;

				// case 2.
			//	return (2.*x*vN_x + 2.*y*vN_y)*mum;
			}
			double	P(FVector_double& p) {
				static FVector_double ps(2);
				P(p, ps);																	// 두 값을 호출해서 알맞게 돌려준다.
				if (Interface(p) >= 0.0)	return ps[1];
				return ps[0];
			}

			void	DP(FVector_double& p, FMatrix_double& dps) {
				double x = p[0], y = p[1];
				double d, dxP, dyP, L1, L2, L3, L4;
				static FVector_double mus(2), dq(dim);
				d = gap;
				coef_mu(p, mus);
				 
				// case1.
				dps.setAll(x / A2 / mum+ y , y / B2 / mum+ x , x / A2 / mup, y / B2 / mup); 
				// case2.
			//	dps.setAll(x / A2 / mum + 2.*x , y / B2 / mum+ 2.*y , x / A2 / mup, y / B2 / mup); 
			}

			void	DP(FVector_double& p, FVector_double& dp) {
				static FMatrix_double dps(2, 2);
				DP(p, dps);

				if (Interface(p)<0.0)	 dp = dps[0];
				else	dp = dps[1];
			}
			double	F(FVector_double& p, FVector_double& fs) {
				double x = p[0], y = p[1];
				double fx, fy, d, L1, L2, L3, L4, dxL1, dyL1, dxL2, dyL2, dxL3, dyL3, dxL4, dyL4;
				static FVector_double mus(2), dq(dim);
				d = gap;
				coef_mu(p, mus);
				

				//case 1
				fx = 1.0 / A2 + 1.0 / B2;
				fy = fx;
				fs.setAll(-1.0* fx, -1.0* fy);

				// case 2
			//	fx = 1.0 / A2 + 1.0 / B2 + 4.*mum;
			//	fy = 1.0 / A2 + 1.0 / B2;
			//	fs.setAll(-1.0* fx, -1.0* fy);
				
				return 0;
			}
			double	F(FVector_double& p) {
				static FVector_double fs(2);
				F(p, fs);
				if (Interface(p)<0.0)	 return fs[0];
				else	return fs[1];
			}
		};
		class P_IIM_EXOTIC_DISCONTINUOUS_CUBIC_CURVE_ : public FEM_PROBLEM {
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				double A, B;
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);
 
				VAR.nData[0] = 30; VAR.nData[1] = 60;  
				//cout << "r0=" << r0 << endl;
				Input("gap", gap);
				Input("mu_inside", mum);
				Input("mu_outside", mup);
				Input("mu_gap ", mug);
			//	Input("nBasis : 3(4) or 5(6)", nBasis);
				nBasis=5.;
			//	//nBasis = 5;
				cout << "gap=" << gap << endl;
				cout << "mum=" << mum << endl;
				cout << "mup=" << mup << endl;
				cout << "mug=" << mug << endl;
				cout << "alpha=" << gap*mup / mug << endl;
			//	cout << "nBasis=" << nBasis << endl;
			} 
			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				double r;
				double L1, L2, L3, L4, L5, L6, L7, L8, L9;
				double theta = MATH::slope_to_radian(x, y);
				
				// peanut-shaped
				return y-3*x*(x-0.3)*(x-0.8)-0.38; 
			} 
			int		IO(FVector_double& p) {
				if (Interface(p) < 0.0)	return CV.IN;
				else return CV.OUT;
				return 0;
			}

			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, middle, Exterior)

				return 0;
			}

			double	coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}

			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p)<0.0)	return mus[0];
				return mus[1];
			}

			double	value_varAlpha(FVector_double& p) {
				double x = p[0], y = p[1];
				double value, d, tempx, tempy;
				static FVector_double vMus(2);
				// y-3*x*(x-0.3)*(x-0.8)-0.38;
				// vDI.setAll(-9.*x*x+6.6*x-0.72 , 1.);
				value = sqrt(1.+ (-9.*x*x+6.6*x-0.72)*(-9.*x*x+6.6*x-0.72)  );
				value = 0.2 / value;
				return value;
			} 

			double	P(FVector_double& p, FVector_double& ps) {
				double x = p[0], y = p[1], d;
				double q;
				double L1, L2, L3, L4;
				static FVector_double mus(2), dq(dim);
				d = gap;
				coef_mu(p, mus);// 두 값을 호출해서 알맞게 돌려준다.

				//the solutions with "Peanut" shape interface with variable alpha
				q=y-3*x*(x-0.3)*(x-0.8)-0.38; 
				ps.setAll(q - 0.2, q );
				return 0;
			}
			double	P(FVector_double& p) {
				static FVector_double ps(2);
				P(p, ps);																	// 두 값을 호출해서 알맞게 돌려준다.
				if (Interface(p) >= 0.0)	return ps[1];
				return ps[0];
			}
			void	DP(FVector_double& p, FMatrix_double& dps) {
				double x = p[0], y = p[1];
				double d, dxP, dyP, L1, L2, L3, L4;
				static FVector_double mus(2), dq(dim);
				d = gap;
				coef_mu(p, mus);
				
				dxP = -9.*x*x+6.6*x-0.72;
				dyP = 1.;
				dps.setAll(dxP, dyP, dxP, dyP); 

			}
			void	DP(FVector_double& p, FVector_double& dp) {
				static FMatrix_double dps(2, 2);
				DP(p, dps);

				if (Interface(p)<0.0)	 dp = dps[0];
				else	dp = dps[1];
			}
			double	F(FVector_double& p, FVector_double& fs) {
				double x = p[0], y = p[1];
				double fx, fy, d, L1, L2, L3, L4, dxL1, dyL1, dxL2, dyL2, dxL3, dyL3, dxL4, dyL4;
				static FVector_double mus(2), dq(dim);
				d = gap;
				coef_mu(p, mus);
				
				double temp_=18.*x-6.6;
				 
				fs.setAll(temp_, temp_);
				
				return 0;
			}
			double	F(FVector_double& p) {
				static FVector_double fs(2);
				F(p, fs);
				if (Interface(p)<0.0)	 return fs[0];
				else	return fs[1];
			}
		};

		class P_IIM_HEART_ : public FEM_PROBLEM { // Governing Equation:  -div(μ▽p) = f
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);

				//		Input("\nView (x,y) direction", VAR.nData[0]>>VAR.nData[1]);
				VAR.nData[0] = 30;
				VAR.nData[1] = 30;   
				
				Input("mum", mum);
				Input("mup", mup);

				Input("r0", r0);
				
			}
			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);

				return pow(3 * r*r - x, 2.) - r*r + r0;

			}
			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0.;

			}
			double	coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) < 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}
			double	P(FVector_double& p, FVector_double& ps) {
				double x = p[0], y = p[1];
				double r2 = x*x + y*y;
				double r = sqrt(r2);
				static FVector_double mus(2);

				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.				
				ps.setAll(sin(2 * x*x + y*y + 2) / mus[0] + x, cos(1 - x*x - y*y) / mus[1]);

				ps.setAll((1.3 - x*x - y*y) / mus[0], cos(x*x + y*y) / mus[1]);
				
				return 0.;
			}
			double	P(FVector_double& p) {
				static FVector_double ps(2);
				P(p, ps);																	// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) < 0) {
					return ps[0];
				}
				else {
					return ps[1];
				}
			}
			double	P_Jump(FVector_double& p) {
				//static FVector_double ps(2);
				//P(p, ps);
				//return (ps[0] - ps[1]);
				static FVector_double ps(2);
				P(p, ps);
				double x = p[0], y = p[1];
				double r2 = x*x + y*y;
				double r = sqrt(r2);
				static FVector_double mus(2);

				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				return (ps[0] - ps[1]);
			}
			void	DP(FVector_double& p, FMatrix_double& dps) {
				double x = p[0], y = p[1];
				double r2 = x*x + y*y;
				double r = sqrt(r2);
				static FVector_double mus(2);
				static FVector_double vDLevelSet(2);	// derivative levelset

				// ps.setAll((3 - x*x - y*y) / mus[0] + x, cos(x*x + y*y) / mus[1]);
				coef_mu(p, mus);		
				dps.setAll(4 * x*cos(2 + 2 * x*x + y*y) / mus[0] + 1., 2 * y*cos(2 + 2 * x*x + y*y) / mus[0], 2 * x*sin(1 - x*x - y*y) / mus[1], 2 * y*sin(1 - x*x - y*y) / mus[1]);
				dps.setAll(-2 * x / mus[0], -2 * y / mus[0], -sin(x*x + y*y) * 2 * x / mus[1], -sin(x*x + y*y) * 2 * y / mus[1]);
			}
			void	DP(FVector_double& p, FVector_double& dp) {
				static FMatrix_double dps(2, 2);
				DP(p, dps);

				if (Interface(p) < 0) {
					dp = dps[0];
				}
				else {
					dp = dps[1];
				}
			}
			void	V(FVector_double& p, FVector_double& dp) {
				static FMatrix_double dps(2, 2);
				static FVector_double mus(2);
				double x = p[0];
				double y = p[1];
				double r2 = x*x + y*y;
				double r = sqrt(r2);
				switch (nFunction) {
				case 101:
					dps.setAll(3 * x*r, 3 * y*r);
				default:
					DP(p, dps);
					coef_mu(p, mus);

					if (Interface(p) <= 0) {
						dp.op("=", -mum, dps[0]);
					}
					else {
						dp.op("=", -mup, dps[1]);
					}
				}
			}
			double	Flux_Jump(FVector_double& p, FVector_double& vN) {
				static FMatrix_double dps(2, 2);
				static FVector_double mus(2);
				static FVector_double dp_exact(2);
				double x = p[0], y = p[1];
				DP(p, dps);
				coef_mu(p, mus);

				return (mus[0] * dps[0] - mus[1] * dps[1], vN);

			}
			double	F(FVector_double& p, FVector_double& fs) {
				static FVector_double mus(2);
				double x = p[0], y = p[1];
				double r2 = x*x + y*y;
				double r = sqrt(r2);

				coef_mu(p, mus);
				fs.setAll(2 * (-3 * cos(2 + 2 * x*x + y*y) + 2 * (4 * x*x + y*y)*sin(2 + 2 * x*x + y*y)),
							4 * ((x*x + y*y)*cos(1 - x*x - y*y) - sin(1 - x*x - y*y)));
				// -2 * x / mus[0] + 1., -2 * y / mus[0], -sin(x*x + y*y) * 2 * x / mus[1], -sin(x*x + y*y) * 2 * y / mus[1]
				fs.setAll(4., cos(x*x + y*y) * 4 * x*x + sin(x*x + y*y) * 2 + cos(x*x + y*y) * 4 * y*y + sin(x*x + y*y) * 2);
				return 0;
			}
			double	F(FVector_double& p) {
				static FVector_double fs(2);
				F(p, fs);
				if (Interface(p) < 0) {
					return fs[0];
				}
				else {
					return fs[1];
				}
			}
		};
		class P_IIM_FICTITIOUS_CIRCLE : public FEM_PROBLEM { // Governing Equation:  -div(μ▽p) = f
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);

				//		Input("\nView (x,y) direction", VAR.nData[0]>>VAR.nData[1]);
				VAR.nData[0] = 30;
				VAR.nData[1] = 30;

				kappa_ficititious = 10;
				r0 = 0.44;
  			//	Input("mum", mum);
				Input("mup", mup);
				mum = 1.;
			//	mup = 10000.;
			}
			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				return (r - r0);
			}
			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}
			double	coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) < 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}
			double	P(FVector_double& p, FVector_double& ps) {
				double x = p[0], y = p[1];
				double r2 = x*x + y*y;
				double r = sqrt(r2);
				static FVector_double mus(2);

				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				ps.setAll(pow(r, 3.) / mus[0], -pow(r, 3.) / mus[1] + (1 / mus[0] + 1 / mus[1])*pow(r0, 3.));
				ps.setAll(pow(r, 3.) / mus[0], 0.);
			//	ps.setAll(pow(r, 3.) / mus[0], pow(r0,3.)/mus[0]);
				return 0;
			}
			double	P(FVector_double& p) {
				static FVector_double ps(2);
				P(p, ps);																	// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) < 0) {
					return ps[0];
				}
				else {
					return ps[1];
				}
			}
			double	P_Jump(FVector_double& p) {
				//static FVector_double ps(2);
				//P(p, ps);
				//return (ps[0] - ps[1]);
				static FVector_double ps(2);
				P(p, ps);
				double x = p[0], y = p[1];
				double r2 = x*x + y*y;
				double r = sqrt(r2);
				static FVector_double mus(2);

				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.
				return (ps[0] - ps[1]);

			}
			void	DP(FVector_double& p, FMatrix_double& dps) {
				double x = p[0], y = p[1];
				double r2 = x*x + y*y;
				double r = sqrt(r2);
				static FVector_double mus(2);
				static FVector_double vDLevelSet(2);	// derivative levelset

				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.
				dps.setAll(3 * x*r / mus[0], 3 * y*r / mus[0], -3 * x*r / mus[1], -3 * y*r / mus[1]);
				dps.setAll(3 * x*r / mus[0], 3 * y*r / mus[0], 0., 0.);
			}
			void	DP(FVector_double& p, FVector_double& dp) {
				static FMatrix_double dps(2, 2);
				DP(p, dps);

				if (Interface(p) < 0) {
					dp = dps[0];
				}
				else {
					dp = dps[1];
				}
			}
			void	V(FVector_double& p, FVector_double& dp) {
				static FMatrix_double dps(2, 2);
				static FVector_double mus(2);
				double x = p[0];
				double y = p[1];
				double r2 = x*x + y*y;
				double r = sqrt(r2);

				dps.setAll(3 * x*r, 3 * y*r);
				dps.setAll(3 * x*r, 0.);
			}
			double	Flux_Jump(FVector_double& p, FVector_double& vN) {
				static FMatrix_double dps(2, 2);
				static FVector_double mus(2);
				static FVector_double dp_exact(2);
				double x = p[0], y = p[1];
				DP(p, dps);
				coef_mu(p, mus);

				return (mus[0] * dps[0] - mus[1] * dps[1], vN);
			}
		 
			double Robin_Boundary	(FVector_double& p, FVector_double& vN) {

				static FMatrix_double dps(2, 2);
				static FVector_double mus(2); 
				static FVector_double ps(2);
				double x = p[0], y = p[1];

				P(p, ps);  
				DP(p, dps);
				coef_mu(p, mus);

				return (mus[0] * dps[0], vN) + kappa_ficititious * ps[0] ;
			}
			double g(FVector_double& p, FVector_double& vN, FVector_double& g) {

				static FMatrix_double dps(2, 2);
				static FVector_double mus(2);
				static FVector_double ps(2);
				double x = p[0], y = p[1];

				P(p, ps);
				DP(p, dps);
				coef_mu(p, mus);

				g[0]=(mus[0] * dps[0], vN) + kappa_ficititious * ps[0];
				g[1] = -(mus[1] * dps[1], vN) + kappa_ficititious * ps[1];

				g[0] = 3 * r0*r0 + kappa_ficititious * pow(r0, 3.) / mus[0];
				g[1] = kappa_ficititious * pow(r0, 3.) / mus[0];
				g[1] = 0.;
				return 0.;
			}
			double	F(FVector_double& p, FVector_double& fs) {
				static FVector_double mus(2);
				double x = p[0], y = p[1];
				double r2 = x*x + y*y;
				double r = sqrt(r2);

				coef_mu(p, mus);
				fs.setAll(-9 * r, -9 * r);
				fs.setAll(-9 * r, 0.);
			//	fs.setAll(-9 * r, 9 * r);

				return 0;
			}
			double	F(FVector_double& p) {
				static FVector_double fs(2);
				F(p, fs);
				if (Interface(p) < 0) {
					return fs[0];
				}
				else {
					return fs[1];
				}
			}
		};
		class P_IIM_FICTITIOUS_CIRCLE_CONTINUOUS : public FEM_PROBLEM { // Governing Equation:  -div(μ▽p) = f
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);

				//		Input("\nView (x,y) direction", VAR.nData[0]>>VAR.nData[1]);
				VAR.nData[0] = 30;
				VAR.nData[1] = 30;

				kappa_ficititious = 5;
				r0 = 0.546;
				//	Input("mum", mum);
				//	Input("mup", mup);
				mum = 1.;
				mup = 1.;
			}
			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				return (r - r0);
			}
			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}
			double	coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) < 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}
			double	P(FVector_double& p, FVector_double& ps) {
				double x = p[0], y = p[1];
				double r2 = x*x + y*y;
				double r = sqrt(r2);
				static FVector_double mus(2);

				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				ps.setAll(pow(r, 3.) / mus[0], pow(r, 3.) / mus[1] + (1 / mus[0] - 1 / mus[1])*pow(r0, 3.));
			//	ps.setAll(pow(r, 3.) / mus[0], 0.);
				return 0;
			}
			double	P(FVector_double& p) {
				static FVector_double ps(2);
				P(p, ps);																	// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) < 0) {
					return ps[0];
				}
				else {
					return ps[1];
				}
			}
			double	P_Jump(FVector_double& p) {
				//static FVector_double ps(2);
				//P(p, ps);
				//return (ps[0] - ps[1]);
				static FVector_double ps(2);
				P(p, ps);
				double x = p[0], y = p[1];
				double r2 = x*x + y*y;
				double r = sqrt(r2);
				static FVector_double mus(2);

				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.
				return (ps[0] - ps[1]);

			}
			void	DP(FVector_double& p, FMatrix_double& dps) {
				double x = p[0], y = p[1];
				double r2 = x*x + y*y;
				double r = sqrt(r2);
				static FVector_double mus(2);
				static FVector_double vDLevelSet(2);	// derivative levelset

				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.
				dps.setAll(3 * x*r / mus[0], 3 * y*r / mus[0], 3 * x*r / mus[1], 3 * y*r / mus[1]);
			//	dps.setAll(3 * x*r / mus[0], 3 * y*r / mus[0], 0., 0.);
			}
			void	DP(FVector_double& p, FVector_double& dp) {
				static FMatrix_double dps(2, 2);
				DP(p, dps);

				if (Interface(p) < 0) {
					dp = dps[0];
				}
				else {
					dp = dps[1];
				}
			}
			void	V(FVector_double& p, FVector_double& dp) {
				static FMatrix_double dps(2, 2);
				static FVector_double mus(2);
				double x = p[0];
				double y = p[1];
				double r2 = x*x + y*y;
				double r = sqrt(r2);

				dps.setAll(3 * x*r, 3 * y*r);
			//	dps.setAll(3 * x*r, 0.);
			}
			double	Flux_Jump(FVector_double& p, FVector_double& vN) {
				static FMatrix_double dps(2, 2);
				static FVector_double mus(2);
				static FVector_double dp_exact(2);
				double x = p[0], y = p[1];
				DP(p, dps);
				coef_mu(p, mus);

				return (mus[0] * dps[0] - mus[1] * dps[1], vN);
			}

			double Robin_Boundary(FVector_double& p, FVector_double& vN) {

				static FMatrix_double dps(2, 2);
				static FVector_double mus(2);
				static FVector_double ps(2);
				double x = p[0], y = p[1];

				P(p, ps);
				DP(p, dps);
				coef_mu(p, mus);

				return (mus[0] * dps[0], vN) + kappa_ficititious * ps[0];
			}
			double g(FVector_double& p, FVector_double& vN, FVector_double& g) {

				static FMatrix_double dps(2, 2);
				static FVector_double mus(2);
				static FVector_double ps(2);
				double x = p[0], y = p[1];

				P(p, ps);
				DP(p, dps);
				coef_mu(p, mus);
				g[0] = mus[0] * (dps[0], vN) + kappa_ficititious * ps[0];
				g[1] = -mus[1] * (dps[1], vN) + kappa_ficititious * ps[1];
			//	g[1] = 0.;

				return 0.;
			}
			double	F(FVector_double& p, FVector_double& fs) {
				static FVector_double mus(2);
				double x = p[0], y = p[1];
				double r2 = x*x + y*y;
				double r = sqrt(r2);

				coef_mu(p, mus);
				fs.setAll(-9 * r, -9 * r);
			//	fs.setAll(-9 * r, 0.);

				return 0;
			}
			double	F(FVector_double& p) {
				static FVector_double fs(2);
				F(p, fs);
				if (Interface(p) < 0) {
					return fs[0];
				}
				else {
					return fs[1];
				}
			}
		};
		class P_IIM_VARIOUS_3D : public FEM_PROBLEM { // Governing Equation:  -div(μ▽p) = f
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 3;
				RX = __.RX.make(2, __.dim).setAll(-1., -1., -1., 1., 1., 1.);

				//		Input("\nView (x,y) direction", VAR.nData[0]>>VAR.nData[1]);
				VAR.nData[0] = 30;
				VAR.nData[1] = 30;

				printf("\n[0] Kink");
				printf("\n[1] Circle");
				printf("\n[2] Star Shape");
				printf("\n[3] Cardioid");
				printf("\n[4] Heart");
				printf("\n[5] Straight Line");
				printf("\n[6] Interface Edge");
				printf("\n[7] Kink Hou");
				printf("\n[100] Homogeneous");
			//	Input("\nChoose a Interface", nInterface);
				nInterface = 1;

				switch (nInterface) {
				case 1: //circle
			//		Input("Radious", r0);
					r0 = 0.63;
					cout << endl;
					break;

				case 5:	// straight line
					vDirection.make(__.dim);													// 방향벡터의 왼쪽이 Omega^- 가 되도록 한다.
					vCenter.make(__.dim);														// 직선의 중심이 어디인지를 나타낸다.

					Input("center-x", vCenter[0]);
					Input("center-y", vCenter[1]);
					Input("x-direction", vDirection[0]);
					Input("y-direction", vDirection[1]);

					vDirection.normalize();
					MATH::rotate2D(vDirection, 0., 1., false);									// -90도 회전시킨다.
					break;

				case 6: // interface edge
					vOp.make(1);
					Input("perturbation: ", perturbed);
					break;

				case 7: // Kink Hou
					//__.RX.make(__.dim, __.dim).setAll(-1.,-1., 3.,1.);
					RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 3., 1.);

					Input("perturbation: ", perturbed);
					break;
				}

				printf("\n");
				printf("\n[0] Complicated Sin");
				printf("\n[1] -:6 x^2 + 7 y^2      +:Sin[3 x y] + Cos[5 x^2 y^2]       beta-:sin(x*y + 3)   beta+:cos(x*x - y*y + 2)");
				printf("\n[2] -:4-x*x-y*y,         +:x*x + y*y");
				printf("\n[3] -:4-x*x-y*y,         +:x*x + y*y    beta-:r^2  beta+:constant");
				printf("\n[4] -:6 x^2 + 7 y^2      +:Sin[3 x y] + Cos[5 x^2 y^2]    beta-:r^2  beta+:constant");
				printf("\n[5] -:x*x + y*y + 2      +:1 - x*x - y*y    beta-:x*y + 3     beta+:x*x - y*y + 3");
				printf("\n[6] -:x*x + y*y + 2      +:1 - x*x - y*y    beta-:mum      beta+:x*x - y*y + x*y +3");
				printf("\n[7] -:sin(2*x*x + y*y + 2)/mum + x      +:cos(1 - x*x - y*y)/mup    beta-:mum      beta+:mup");
				printf("\n[8] -:pow(r*r, 5./6) + sin(x+y)   +:8         beta-:2 + sin(x + y)     beat+:1");
				printf("\n[9] -:const1/mus[0]				+:const2/mus[1]");
				printf("\n[10] -:sin(10xy)/mus[0]			+:cos(y)/mus[1]");
				printf("\n[11] -:x			+:0");
				printf("\n[[ Homogeneous Jumps ]]");
				printf("\n[100] -LevelSet/beta- +:*LevelSet/beta+");
				printf("\n[101] Zilin Lee -:r^3/mum    +:r^3/mup + (1/mum - 1/mup)r0^3");

			//	Input("\nChoose a Function", nFunction);
				nFunction = 101;
				switch (nFunction) {
				case 0: case 7: case 10: case 100: case 101:
				//	Input("mum", mum);
				//	Input("mup", mup);
					mum = 1.;
					mup = 100.;
					break;

				case 3: case 4:
					Input("beta+", mup);
					break;

				case 6:
					Input("beta-", mum);
					break;

				case 9:
					//mum = mup = 1;
					Input("mum", mum);
					Input("mup", mup);
					vOp.make(2);
					Input("const1", vOp[0]);
					Input("const2", vOp[1]);
					break;
				}
			}
			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1], z = p[2];
				double r = sqrt(x*x + y*y + z*z);
				//double theta = MATH::slope_to_radian(x, y);

				switch (nInterface) {
				case 0:	// kink(left)
					if (y > 0) return (y + 2 * x);
					else return (x - 2 * y);

				case 1: // circle
					return (r - r0);

				case 2: // star shape
					return (r - 0.2*sin(5 * theta - CV.PI / 5) - 0.5);

				case 3: // cardioid
					return pow(3 * r*r - x, 2.) - r*r;

				case 4: // heart
					return pow(3 * r*r - x, 2.) - r*r + 0.01;

				case 5: // straight line
					return (vDirection, p - vCenter);

				case 6: // interface edge
					if (y >= 0) return (x + y + perturbed);
					else return (x + perturbed);

				case 7: // Kink Hou
					if (x + y > 0) return (y - 2 * x + perturbed);
					else return (y + 0.5*x + perturbed);

				case 100: // homogeneous
					return sin(4 * (x*x - y*y));
					//case 5: // kink(upper)
					//	if(y>0
					//	return
					//case 101:
					//	return r*r - r0*r0;
				}
				return 0;												// 내적값을 준다.
			}
			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1], z = p[2];

				switch (nFunction) {
				case 0: case 7:	case 9: case 10: case 100: case 101:
					mus.setAll(mum, mup);														// (Interior, Exterior)
					break;

				case 1:
					mus.setAll(sin(x*y + 3), cos(x*x - y*y + 2));
					break;

				case 2:
					mus.setAll(x*y + 2, x*x - y*y + 3);
					break;

				case 3: case 4:
					mus.setAll(x*x + y*y, mup);
					break;

				case 5:
					mus.setAll(x*y + 3, x*x - y*y + 3);
					break;

				case 6:
					mus.setAll(mum, x*x - y*y + x*y + 3);
					break;

				case 8:
					mus.setAll(2 + sin(x + y), 1.);
					break;

				default:
					mus.setAll(1., 1.);
					break;
				}
				return 0;
			}
			double	coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) < 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}
			double	P(FVector_double& p, FVector_double& ps) {
				double x = p[0], y = p[1], z = p[2];
				double r2 = x*x + y*y + z*z;
				double r = sqrt(r2);
				static FVector_double mus(2);

				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				switch (nFunction) {
				case 0:		ps.setAll(sin(10 * x*(-2 + y)) / mus[0], x*x / mus[1]);															// (Interior, Exterior)
					break;

				case 1:		ps.setAll(6 * x*x + 7 * y*y, sin(3 * x*y) + cos(5 * x*x*y*y));
					break;

				case 2: case 3:
					ps.setAll(4 - x*x - y*y, (x*x + y*y) / mus[1]);
					break;

				case 4:
					ps.setAll(6 * x*x + 7 * y*y, (sin(3 * x*y) + cos(5 * x*x*y*y)) / mus[1]);
					break;

				case 5: case 6:
					ps.setAll(x*x + y*y + 2, 1 - x*x - y*y);
					break;

				case 7:
					ps.setAll(sin(2 * x*x + y*y + 2) / mus[0] + x, cos(1 - x*x - y*y) / mus[1]);
					break;

				case 8:
					ps.setAll(pow(r2, 5. / 6) + sin(x + y), 8.);
					break;

				case 9:
					ps.setAll(vOp[0] / mus[0], vOp[1] / mus[1]);
					break;

				case 10:
					ps.setAll(sin(10 * x*y) / mus[0], cos(y) / mus[1]);															// (Interior, Exterior)
					break;

				case 11:
					ps.setAll(x, 0.);
					break;

				case 100:	// homogeneous case
					//ps.setAll((r - 0.2*sin(5*theta - CV.PI/5) + 0.5)/mus[0], (r - 0.2*sin(5*theta - CV.PI/5) + 0.5)/mus[1]);
					ps.setAll(sin(4 * (x*x - y*y)) / mus[0], sin(4 * (x*x - y*y)) / mus[1]);
					break;

				case 101:
					ps.setAll(pow(r, 3.) / mus[0], pow(r, 3.) / mus[1] + (1 / mus[0] - 1 / mus[1])*pow(r0, 3.));
					break;
				}
				return 0;
			}
			double	P(FVector_double& p) {
				static FVector_double ps(2);
				P(p, ps);																	// 두 값을 호출해서 알맞게 돌려준다.
				if (Interface(p) < 0) {
					return ps[0];
				}
				else {
					return ps[1];
				}
			}
			double	P_Jump(FVector_double& p) {
				//static FVector_double ps(2);
				//P(p, ps);
				//return (ps[0] - ps[1]);
				static FVector_double ps(2);
				P(p, ps);
				double x = p[0], y = p[1], z = p[2];
				double r2 = x*x + y*y + z*z;
				double r = sqrt(r2);
				static FVector_double mus(2);

				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				// 정확히 0이 나와야 하는 경우도(즉, 수학적으로 동일한 식도) 계산과정에서 round off error가 발생한다.
				// 따라서 직접적으로 계산해서 함수를 대입해주어야 한다.
				// -. 되도록이면 계산과정이 적도록
				// -. 위험도: 1.나눗셈 2.곱셈
				switch (nFunction) {
				case 9:
					return (vOp[0] / mus[0] - vOp[1] / mus[1]);

				case 101:
					return 0;

				default:
					return (ps[0] - ps[1]);
				}
			}
			void	DP(FVector_double& p, FMatrix_double& dps) {
				double x = p[0], y = p[1], z = p[2];
				double r2 = x*x + y*y + z*z;
				double r = sqrt(r2);
				static FVector_double mus(2);
				static FVector_double vDLevelSet(2);	// derivative levelset

				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.
				switch (nFunction) {
				case 0:
					dps.setAll(10 * (-2 + y)*cos(10 * x*(-2 + y)) / mus[0], 10 * x*cos(10 * x*(-2 + y)) / mus[0], 2 * x / mus[1], 0.);
					break;

				case 1:
					dps.setAll(12 * x, 14 * y, y*(3 * cos(3 * x*y) - 10 * x*y*sin(5 * x*x*y*y)), x*(3 * cos(3 * x*y) - 10 * x*y*sin(5 * x*x*y*y)));
					break;

				case 2:	case 3:
					dps.setAll(-2 * x, -2 * y, 2 * x / mus[1], 2 * y / mus[1]);
					break;

				case 4:
					dps.setAll(12 * x, 14 * y, (y*(3 * cos(3 * x*y) - 10 * x*y*sin(5 * x*x*y*y))) / mus[1], (x*(3 * cos(3 * x*y) - 10 * x*y*sin(5 * x*x*y*y))) / mus[1]);
					break;

				case 5: case 6:
					dps.setAll(2 * x, 2 * y, -2 * x, -2 * y);
					break;

				case 7:
					dps.setAll(4 * x*cos(2 + 2 * x*x + y*y) / mus[0] + 1., 2 * y*cos(2 + 2 * x*x + y*y) / mus[0], 2 * x*sin(1 - x*x - y*y) / mus[1], 2 * y*sin(1 - x*x - y*y) / mus[1]);
					break;

				case 8:
					dps.setAll((5 * x) / (3 * pow(r2, 1. / 6)) + cos(x + y), (5 * y) / (3 * pow(r2, 1. / 6)) + cos(x + y), 0., 0.);
					break;

				case 9:
					dps.clear();
					break;

				case 10:
					dps.setAll(10 * y*cos(10 * x*y) / mus[0], 10 * x*cos(10 * x*y) / mus[0], 0., -sin(y) / mus[1]);
					break;

				case 11:
					dps.setAll(1., 0., 0., 0.);
					break;

				case 100: // Homogeneous Case (Starfish)
					//dps[0].setAll(x/r + (y/r2)*cos(5*theta - CV.PI/5), y/r - (x/r2)*cos(5*theta - CV.PI/5)) /= (mus[0]);
					//dps[1].setAll(x/r + (y/r2)*cos(5*theta - CV.PI/5), y/r - (x/r2)*cos(5*theta - CV.PI/5)) /= (mus[1]);
					dps[0].setAll(8 * x*cos(4 * (x*x - y*y)), -8 * y*cos(4 * (x*x - y*y))) /= mus[0];
					dps[1].setAll(8 * x*cos(4 * (x*x - y*y)), -8 * y*cos(4 * (x*x - y*y))) /= mus[1];
					break;

				case 101:
					dps.setAll(3 * x*r / mus[0], 3 * y*r / mus[0], 3 * z*r / mus[0], 3 * x*r / mus[1], 3 * y*r / mus[1], 3 * z*r / mus[1]);
					break;
				}
			}
			void	DP(FVector_double& p, FVector_double& dp) {
				static FMatrix_double dps(2, 3);
				DP(p, dps);

				if (Interface(p) < 0) {
					dp = dps[0];
				}
				else {
					dp = dps[1];
				}
			}
			void	V(FVector_double& p, FVector_double& dp) {

				static FMatrix_double dps(2, 3);
				static FVector_double mus(2);
				double x = p[0];
				double y = p[1];
				double z = p[2];
				double r2 = x*x + y*y + z*z;
				double r = sqrt(r2);
				switch (nFunction) {
				case 101:
					dps.setAll(3 * x*r, 3 * y*r, 3 * z*r);
				default:
					DP(p, dps);
					coef_mu(p, mus);

					if (Interface(p) <= 0) {
						dp.op("=", -mum, dps[0]);
					}
					else {
						dp.op("=", -mup, dps[1]);
					}
				}
			}
			double	Flux_Jump(FVector_double& p, FVector_double& vN) {
				static FMatrix_double dps(2, 3);
				static FVector_double mus(2);
				//static FVector_double dp_exact(2);
				double x = p[0], y = p[1], z = p[2];
				DP(p, dps);
				coef_mu(p, mus);

				switch (nFunction) {
				case 9: case 101:
					return 0;

					//case 10:
					//	dp_exact.setAll(10 * y*cos(10 * x*y), 10 * x*cos(10 * x*y) + sin(y));
					//	return (dp_exact, vN);

				default:
					return (mus[0] * dps[0] - mus[1] * dps[1], vN);
				}
				//double fjump = fabs(( mus[0]*dps[0] - mus[1]*dps[1], vN));
				//if(fjump < 1.0E-16) return 0;
				//else return fjump;
			}
			double	F(FVector_double& p, FVector_double& fs) {
				static FVector_double mus(2);
				double x = p[0], y = p[1], z = p[2];
				double r2 = x*x + y*y + z*z;
				double r = sqrt(r2);

				coef_mu(p, mus);
				switch (nFunction) {
				case 0:		fs.setAll(100 * (x*x + pow((-2 + y), 2.))*sin(10 * x*(-2 + y)), -2.);
					break;
				case 1:		fs.setAll(-26 * (x*y*cos(3 + x*y) + sin(3 + x*y)), (x*x + y*y)*cos(2 + x*x - y*y)*(100 * x*x*y*y*cos(5 * x*x*y*y) + 9 * sin(3 * x*y) + 10 * sin(5 * x*x*y*y)));
					break;
				case 2:		fs.setAll(8 * (1 + x*y), -12 - 8 * x*x - 8 * y*y);
					break;
				case 3:		fs.setAll(8 * (x*x + y*y), -4.);
					break;
				case 4:		fs.setAll(-50 * x*x - 54 * y*y, (x*x + y*y)*(100 * x*x*y*y*cos(5 * x*x*y*y) + 9 * sin(3 * x*y) + 10 * sin(5 * x*x*y*y)));
					break;
				case 5:		fs.setAll(-12 - 8 * x*y, 12 + 8 * x*x - 8 * y*y);
					break;
				case 6:		fs.setAll(-4 * mus[0], 4 * (3 + 2 * x*x + 2 * x*y - 2 * y*y));
					break;
				case 7:		fs.setAll(2 * (-3 * cos(2 + 2 * x*x + y*y) + 2 * (4 * x*x + y*y)*sin(2 + 2 * x*x + y*y)),
					4 * ((x*x + y*y)*cos(1 - x*x - y*y) - sin(1 - x*x - y*y)));
					break;
				case 8:		fs.setAll(-1. / (9 * pow(r2, 1. / 6))*(50 + 15 * (x + y)*cos(x + y) + 18 * pow(r2, 1. / 6)*cos(2 * (x + y)) + 25 * sin(x + y) - 36 * pow(r2, 1. / 6)*sin(x + y)), 0.);
					break;
				case 9:		fs.setAll(0., 0.);
					break;
				case 10:	fs.setAll(100 * r2*sin(10 * x*y), cos(y));
					break;
				case 11:	fs.setAll(0., 0.);
					break;
				case 100:	//fs.setAll((-1/r - 5/r2*sin(5*theta - CV.PI/5))/mus[0], (-1/r - 5/r2*sin(5*theta - CV.PI/5))/mus[1]);
					fs.setAll(64 * r2*sin(4 * (x*x - y*y)) / mus[0], 64 * r2*sin(4 * (x*x - y*y)) / mus[1]);
					break;
				case 101:
					fs.setAll(-12 * r, -12 * r);
					break;
				}

				return 0;
			}
			double	F(FVector_double& p) {
				static FVector_double fs(2);
				F(p, fs);

				if (Interface(p) < 0) {
					return fs[0];
				}
				else {
					return fs[1];
				}
			}
		};
		class P_IIM_ZIN_LIN_LI_3D : public FEM_PROBLEM { // Governing Equation:  -div(μ▽p) = f
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 3;
				RX = __.RX.make(2, __.dim).setAll(-1., -1., -1., 1., 1., 1.);

				//		Input("\nView (x,y) direction", VAR.nData[0]>>VAR.nData[1]);
				VAR.nData[0] = 30;
				VAR.nData[1] = 30;
				 
				r0 = 0.63;  
				 
				mum = 1.;
				mup = 100.;
			 
			}
			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1], z = p[2];
				double r = sqrt(x*x + y*y + z*z);

				return (r - r0);

			}
			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1], z = p[2];

				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}
			double	coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) < 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}
			double	P(FVector_double& p, FVector_double& ps) {
				double x = p[0], y = p[1], z = p[2];
				double r2 = x*x + y*y + z*z;
				double r = sqrt(r2);
				static FVector_double mus(2);

				coef_mu(p, mus);	 
				ps.setAll(pow(r, 3.) / mus[0], pow(r, 3.) / mus[1] + (1 / mus[0] - 1 / mus[1])*pow(r0, 3.));

			}
			double	P(FVector_double& p) {
				static FVector_double ps(2);
				P(p, ps);																	// 두 값을 호출해서 알맞게 돌려준다.
				if (Interface(p) < 0) {
					return ps[0];
				}
				else {
					return ps[1];
				}
			}
			double	P_Jump(FVector_double& p) {
				//static FVector_double ps(2);
				//P(p, ps);
				//return (ps[0] - ps[1]);
				static FVector_double ps(2);
				P(p, ps);
				double x = p[0], y = p[1], z = p[2];
				double r2 = x*x + y*y + z*z;
				double r = sqrt(r2);
				static FVector_double mus(2); 
				 
				return (ps[0] - ps[1]);
			}
			void	DP(FVector_double& p, FMatrix_double& dps) {
				double x = p[0], y = p[1], z = p[2];
				double r2 = x*x + y*y + z*z;
				double r = sqrt(r2);
				static FVector_double mus(2);
				static FVector_double vDLevelSet(2);	// derivative levelset

				coef_mu(p, mus);		 
				dps.setAll(3 * x*r / mus[0], 3 * y*r / mus[0], 3 * z*r / mus[0], 3 * x*r / mus[1], 3 * y*r / mus[1], 3 * z*r / mus[1]);

			}
			void	DP(FVector_double& p, FVector_double& dp) {
				static FMatrix_double dps(2, 3);
				DP(p, dps);

				if (Interface(p) < 0) {
					dp = dps[0];
				}
				else {
					dp = dps[1];
				}
			}
			void	V(FVector_double& p, FVector_double& dp) {

				static FMatrix_double dps(2, 3);
				static FVector_double mus(2);
				double x = p[0];
				double y = p[1];
				double z = p[2];
				double r2 = x*x + y*y + z*z;
				double r = sqrt(r2);

				DP(p, dps);
				coef_mu(p, mus);

				if (Interface(p) <= 0) {
					dp.op("=", -mum, dps[0]);
				}
				else {
					dp.op("=", -mup, dps[1]); 
				}
			}
			double	Flux_Jump(FVector_double& p, FVector_double& vN) {
				static FMatrix_double dps(2, 3);
				static FVector_double mus(2);
				//static FVector_double dp_exact(2);
				double x = p[0], y = p[1], z = p[2];
				DP(p, dps);
				coef_mu(p, mus);

				return (mus[0] * dps[0] - mus[1] * dps[1], vN);
			}
			double	F(FVector_double& p, FVector_double& fs) {
				static FVector_double mus(2);
				double x = p[0], y = p[1], z = p[2];
				double r2 = x*x + y*y + z*z;
				double r = sqrt(r2);

				coef_mu(p, mus);
				 
				fs.setAll(-12 * r, -12 * r);

				return 0;
			}
			double	F(FVector_double& p) {
				static FVector_double fs(2);
				F(p, fs);

				if (Interface(p) < 0) {
					return fs[0];
				}
				else {
					return fs[1];
				}
			}
		};
		class P_IIM_CIRCLE_DB_3D : public FEM_PROBLEM { // Governing Equation:  -div(μ▽p) = f
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 3;
				RX = __.RX.make(2, __.dim).setAll(-1., -1., -1., 1., 1., 1.);

				//		Input("\nView (x,y) direction", VAR.nData[0]>>VAR.nData[1]);
				VAR.nData[0] = 30;
				VAR.nData[1] = 30;

				r0 = 0.63;

				mum = 100.;
				mup = 1.;

			}
			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1], z = p[2];
				double r = sqrt(x*x + y*y + z*z);

				return (r - r0);

			}
			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1], z = p[2];

				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}
			double	coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) < 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}
			double	P(FVector_double& p, FVector_double& ps) {
				double x = p[0], y = p[1], z = p[2];
				double r2 = x*x + y*y + z*z;
				double r = sqrt(r2);
				static FVector_double mus(2);

				coef_mu(p, mus);
				ps.setAll(x*x/mus[0] +100. , x*x/mus[1]);
				return 0;
			}
			double	P(FVector_double& p) {
				static FVector_double ps(2);
				P(p, ps);																	// 두 값을 호출해서 알맞게 돌려준다.
				if (Interface(p) < 0) {
					return ps[0];
				}
				else {
					return ps[1];
				}
			}
			double	P_Jump(FVector_double& p) {
				//static FVector_double ps(2);
				//P(p, ps);
				//return (ps[0] - ps[1]);
				static FVector_double ps(2);
				P(p, ps);
				double x = p[0], y = p[1], z = p[2];
				double r2 = x*x + y*y + z*z;
				double r = sqrt(r2);
				static FVector_double mus(2);

				return (ps[0] - ps[1]);
			}
			void	DP(FVector_double& p, FMatrix_double& dps) {
				double x = p[0], y = p[1], z = p[2];
				double r2 = x*x + y*y + z*z;
				double r = sqrt(r2);
				static FVector_double mus(2);
				static FVector_double vDLevelSet(2);	// derivative levelset

				coef_mu(p, mus);  
				dps.setAll(2 * x / mus[0], 0., 0., 2 * x / mus[1], 0., 0.);

			}
			void	DP(FVector_double& p, FVector_double& dp) {
				static FMatrix_double dps(2, 3);
				DP(p, dps);

				if (Interface(p) < 0) {
					dp = dps[0];
				}
				else {
					dp = dps[1];
				}
			}
			void	V(FVector_double& p, FVector_double& dp) {

				static FMatrix_double dps(2, 3);
				static FVector_double mus(2);
				double x = p[0];
				double y = p[1];
				double z = p[2];
				double r2 = x*x + y*y + z*z;
				double r = sqrt(r2);

				DP(p, dps);
				coef_mu(p, mus);

				if (Interface(p) <= 0) {
					dp.op("=", -mum, dps[0]);
				}
				else {
					dp.op("=", -mup, dps[1]);
				}
			}
			double	Flux_Jump(FVector_double& p, FVector_double& vN) {
				static FMatrix_double dps(2, 3);
				static FVector_double mus(2);
				//static FVector_double dp_exact(2);
				double x = p[0], y = p[1], z = p[2];
				DP(p, dps);
				coef_mu(p, mus); 
				double rt;

				return (mus[0] * dps[0] - mus[1] * dps[1], vN);
			}
			double	F(FVector_double& p, FVector_double& fs) {
				static FVector_double mus(2);
				double x = p[0], y = p[1], z = p[2];
				double r2 = x*x + y*y + z*z;
				double r = sqrt(r2);

				coef_mu(p, mus);

				fs.setAll(-2., -2.);

				return 0;
			}
			double	F(FVector_double& p) {
				static FVector_double fs(2);
				F(p, fs);

				if (Interface(p) < 0) {
					return fs[0];
				}
				else {
					return fs[1];
				}
			}
		};
		class P_IIM_HYUN_DIFF_BETA : public FEM_PROBLEM {
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				double A, B;
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);

				//Input("\nView (x,y) direction", VAR.nData[0] >> VAR.nData[1]);
				VAR.nData[0] = 30; VAR.nData[1] = 60;
				cout << "\n View direction is (30,60) " << endl;
				printf("\n--------------------------------------");
				printf("\n|       Interfaces for Solution      |");
				printf("\n--------------------------------------");
				printf("\n(0) Circle");
				printf("\n(1) Ellipsoid, mu+=mu-");
				printf("\n(2) Ellipsoid with variable alpha");
				printf("\n(3) Heart Shape with variable alpha, all data =1");
				printf("\n(4) Peanut Shape with variable alpha, mup mum= 1 ");
				printf("\n(5) Circle with unknown solution");
				printf("\n(6) Line with test");
				printf("\n(7) Line test 2");
				printf("\n(8) Line test 3");
				printf("\n(9) Line test 3");
				printf("\n(10) Two circles , mu=gap= all 1");
				printf("\n(11) Four circles, mu=gap= all 1");
				printf("\n(12) Nine circles");
				printf("\n--------------------------------------");
				Input("\nChoose Interface: ", nInterface);
				switch (nInterface){
				case 0:
					Input("\n\nCircle Radius", r0);
					break;
				case 1:
					A = 0.7; B = 0.3;
					r0 = 1.0;
					break;
				case 2:
					cout << "Ellipsoidal Interface with Radius(default: r0=1)" << endl;
					Input("r0", r0);
					//r0 = 1.0;
					Input("\n\nThe first axis (a^2=A2=0.49)", A2);
					Input("\n\nThe second axis (b^2=B2=0.09)", B2);
					cout << "A2(a^2)=" << A2 << endl;
					cout << "B2(b^2)=" << B2 << endl;
					A = sqrt(A2); B = sqrt(B2);
					break;
				case 3:
					cout << "Heart Shape Interface is chosen." << endl;
					Input("\n\nCoefficient of the solution functions", c0);
					Input("\n\nr0", r0);
					break;
				case 4:
					cout << "Peanut Shape Interface is chosen." << endl;
					Input("\n\nCoefficient of the solution functions (<0.03)", r0);
					cout << "r0=" << r0 << endl;
					break;
				case 5:
					Input("\n\nCircle Radius", r0);
					break;
				case 6: case 7: case 8: case 9:
					Input("\n\n r0", r0);
					vFirst_intersec_point.make(2);
					vSecond_intersec_point.make(2);
					if (nInterface == 6)
					{
						vFirst_intersec_point.setAll(1. / 3., -1.);
						vSecond_intersec_point.setAll(1. / 3., 1.);
					}
					else if (nInterface == 7)
					{
						vFirst_intersec_point.setAll((-1. - r0) / 2., -1.);
						vSecond_intersec_point.setAll((1. - r0) / 2., 1.);
					}
					else if (nInterface == 8)
					{
						if (r0>0)
						{
							vFirst_intersec_point.setAll(-1., -1. + r0);
							vSecond_intersec_point.setAll((1. - r0), 1.);
						}
						else
						{
							vFirst_intersec_point.setAll((-1. - r0), -1.);
							vSecond_intersec_point.setAll(1., 1. + r0);
						}
					}
					else if (nInterface == 9)
					{
						if (r0>0)
						{
							vFirst_intersec_point.setAll(1., (r0 - 1.));
							vSecond_intersec_point.setAll((r0 - 1.), 1.);
						}
						else
						{
							vFirst_intersec_point.setAll((r0 + 1.), -1.);
							vSecond_intersec_point.setAll(-1., (r0 + 1.));
						}
					}
					else
					{
						printf("\nThere is no such a interface,yet!!");
					}
					break;
				case 10:
					Input("\nCircle 1 Radius", r1);
					Input("\nCircle 2 Radius", r2);
					x1 = 0.5;
					y1 = 0.5;
					x2 = -0.5;
					y2 = -0.5;
					break;
				case 11:
					Input("\nCircle 1 Radius", r1);
					Input("\nCircle 2 Radius", r2);
					Input("\nCircle 3 Radius", r3);
					Input("\nCircle 4 Radius", r4);
					x1 = 0.5;
					y1 = 0.5;
					x2 = -0.5;
					y2 = 0.5;
					x3 = -0.5;
					y3 = -0.5;
					x4 = 0.5;
					y4 = -0.5;
					break;
				case 12:
					r0 = 0.15;
					x1 = 0.6;
					y1 = 0.6;
					break;
				default:
					printf("\nThere is no such a interface,yet!!");
					break;
				}
				//cout << "r0=" << r0 << endl;
				Input("gap", gap);
				Input("mu_inside", mum);
				Input("mu_outside", mup);
				Input("mu_gap ", mug);
				Input("nBasis : 3(4) or 5(6)", nBasis);
				//nBasis = 5;
				cout << "gap=" << gap << endl;
				cout << "mum=" << mum << endl;
				cout << "mup=" << mup << endl;
				cout << "mug=" << mug << endl;
				cout << "alpha=" << gap*mup / mug << endl;
				cout << "nBasis=" << nBasis << endl;

			}
			interfaces interface_type()
			{
				switch (nInterface){
				case 0: case 5:
					return CIRCLE;
				case 1: case 2:
					return ELIPSE;
				case 6: case 7: case 8: case 9:
					return LINE;
				default:
					printf("\nThere is no such a interface,yet!!");
					return CIRCLE;
				}
			}
			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				double r;
				double L1, L2, L3, L4, L5, L6, L7, L8, L9;
				double theta = MATH::slope_to_radian(x, y);
				switch (nInterface){
				case 0:
					//Circular Interface 
					r = sqrt(x*x + y*y) - r0;
					//r = sqrt((x-1.)*(x-1.) + (y-1.)*(y-1.)) - r0;
					break;
				case 1:
					//Circular Interface
					r = sqrt(x*x / 0.49 + y*y / 0.09) - r0;
					break;
				case 2:
					//Ellipsoidal Interface with variable alpha
					r = sqrt(x*x / A2 + y*y / B2) - r0;
					break;
				case 3:
					//Heart shaped Interface with variable alpha
					r = x*x + y*y;
					r = (3.0*r - x)*(3.0*r - x) - r + 0.01;
					break;
				case 4:
					// peanut-shaped
					r = x*x*x*x / 2.0 - x*x / 4.0 + y*y - r0;
					break;
				case 5:
					//Circular Interface 
					r = sqrt(x*x + y*y) - r0;
					break;
				case 6:
					r = x - 1. / 3.;
					break;
				case 7:
					r = y - 2.*x - r0;
					break;
				case 8:
					r = y - x - r0;
					break;
				case 9:
					r = y + x - r0;
					break;
				case 10: // Two circles
					r = ((x - x1)*(x - x1) + (y - y1)*(y - y1) - r1*r1)*((x - x2)*(x - x2) + (y - y2)*(y - y2) - r2*r2);
					break;
				case 11:
					L1 = (x - x1)*(x - x1) + (y - y1)*(y - y1) - r1*r1;
					L2 = (x - x2)*(x - x2) + (y - y2)*(y - y2) - r2*r2;
					L3 = (x - x3)*(x - x3) + (y - y3)*(y - y3) - r3*r3;
					L4 = (x - x4)*(x - x4) + (y - y4)*(y - y4) - r4*r4;
					r = L1*L2*L3*L4;
					break;
				case 12:
					L1 = x*x + y*y - r0*r0;
					L2 = (x - x1)*(x - x1) + y*y - r0*r0;
					L3 = (x - x1)*(x - x1) + (y - y1)*(y - y1) - r0*r0;
					L4 = x*x + (y - y1)*(y - y1) - r0*r0;
					L5 = (x + x1)*(x + x1) + (y - y1)*(y - y1) - r0*r0;
					L6 = (x + x1)*(x + x1) + y*y - r0*r0;
					L7 = (x + x1)*(x + x1) + (y + y1)*(y + y1) - r0*r0;
					L8 = x*x + (y + y1)*(y + y1) - r0*r0;
					L9 = (x - x1)*(x - x1) + (y + y1)*(y + y1) - r0*r0;
					r = L1*L2*L3*L4*L5*L6*L7*L8*L9;
					break;
				default:
					printf("\nThere is no such a interface,yet!!");
					break;
				}
				return r;
			}

			double	InterfaceGrad(FVector_double& p, FVector_double& df) {
				double x = p[0], y = p[1];
				double dLx, dLy;
				double theta = MATH::slope_to_radian(x, y);
				switch (nInterface){
				case 0:
					df.setAll(2.0*x, 2.0*y);
					break;
				case 1:
					df.setAll(2.0*x / 0.49, 2.0*y / 0.09);
					break;
				case 2:	//Ellipsoidal Interface with variable alpha
					df.setAll(2.0*x / A2, 2.0*y / B2);
					break;
				case 3: //Heart Shaped Interface with variable alpha
					/*dLx = exp(x)*(-sin(y) + y*cos(y) + y*(2.0*cos(x) -2.0*x*sin(x) -2.0*sin(x)));
					dLy = exp(x)*(-y*sin(y) + x*cos(x) + cos(x) -x*sin(x));*/
					dLx = 2.0*(3.0*(x*x + y*y) - x)*(6.0*x - 1.0) - 2.0*x;
					dLy = 2.0*(3.0*(x*x + y*y) - x)*(6.0*y) - 2.0*y;
					df.setAll(dLx, dLy);
					break;
				case 4:
					dLx = 2.0*x*x*x - x / 2.0;
					dLy = 2.0*y;
					df.setAll(dLx, dLy);
					break;
				case 5:
					df.setAll(2.0*x, 2.0*y);
					break;
				case 6:
					df.setAll(1., 0.);
					break;
				case 7:
					df.setAll(-2., 1.);
					break;
				case 8:
					df.setAll(-1., 1.);
					break;
				case 9:
					df.setAll(1., 1.);
					break;
				case 10:
					dLx = 2.*(x - x1)*((x - x2)*(x - x2) + (y - y2)*(y - y2) - r2*r2) + 2.*(x - x2)*((x - x1)*(x - x1) + (y - y1)*(y - y1) - r1*r1);
					dLy = 2.*(y - y1)*((x - x2)*(x - x2) + (y - y2)*(y - y2) - r2*r2) + 2.*(y - y2)*((x - x1)*(x - x1) + (y - y1)*(y - y1) - r1*r1);
					df.setAll(dLx, dLy);
					break;
				default:
					printf("\nThere is no such a interface,yet!!");
					break;
				}
				return 0.0;
			}

			int		IO(FVector_double& p) {
				if (Interface(p) < 0.0)	return CV.IN;
				else return CV.OUT;
				return 0;
			}

			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, middle, Exterior)

				return 0;
			}

			double	coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}

			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p)<0.0)	return mus[0];
				return mus[1];
			}

			double	value_varAlpha(FVector_double& p) {
				double x = p[0], y = p[1];
				double value, d, tempx, tempy;
				static FVector_double vMus(2);
				d = gap;
				switch (nInterface)
				{
				case 1:
					value = sqrt(x*x / (0.49*0.49) + y*y / (0.09*0.09));
					break;
				case 2:
					value = sqrt(x*x / (A2*A2) + y*y / (B2*B2));
					break;
				case 3:
					tempx = (3.0*(x*x + y*y) - x)*(6.0*x - 1.0) - x;
					tempy = (3.0*(x*x + y*y) - x)*(6.0*y) - y;
					value = sqrt(tempx*tempx + tempy*tempy);
					break;
				case 4:
					value = sqrt((x*x*x - x / 4.0)*(x*x*x - x / 4.0) + y*y);
					break;
				case 9:
					value = d*mup / mug / (sqrt(2.) / 4.*r0);
					break;
				default:
					value = 1.0;
					break;
				}
				value = d*mup / mug / value;
			//	value = 0.;
				return value;
			}
			double	value_varAlpha(FVector_double& p, int type) {
				double x = p[0], y = p[1];
				double value, d, tempx, tempy;
				double L1, L2, L3, L4;
				static FVector_double vMus(2);
				d = gap;
				switch (nInterface)
				{
				case 1:
					value = sqrt(x*x / (0.49*0.49) + y*y / (0.09*0.09));
					break;
				case 2:
					value = sqrt(x*x / (A2*A2) + y*y / (B2*B2));
					break;
				case 3:
					tempx = (3.0*(x*x + y*y) - x)*(6.0*x - 1.0) - x;
					tempy = (3.0*(x*x + y*y) - x)*(6.0*y) - y;
					value = sqrt(tempx*tempx + tempy*tempy);
					break;
				case 4:
					value = sqrt((x*x*x - x / 4.0)*(x*x*x - x / 4.0) + y*y);
					break;
				case 9:
					value = d*mup / mug / (sqrt(2.) / 4.*r0);
					break;
				case 10:
					if (type == 1)
						value = (x - x2)*(x - x2) + (y - y2)*(y - y2) - r2*r2;
					else
						value = (x - x1)*(x - x1) + (y - y1)*(y - y1) - r1*r1;
					break;
				case 11:
					L1 = (x - x1)*(x - x1) + (y - y1)*(y - y1) - r1*r1;
					L2 = (x - x2)*(x - x2) + (y - y2)*(y - y2) - r2*r2;
					L3 = (x - x3)*(x - x3) + (y - y3)*(y - y3) - r3*r3;
					L4 = (x - x4)*(x - x4) + (y - y4)*(y - y4) - r4*r4;
					switch (type){
					case 1:
						value = L2*L3*L4 / 10.;
						break;
					case 2:
						value = L1*L3*L4 / 10.;
						break;
					case 3:
						value = L1*L2*L4 / 10.;
						break;
					case 4:
						value = L1*L2*L3 / 10.;
						break;
					}
					break;
				default:
					value = 1.0;
					break;
				}
				value = d*mup / mug / value;
				return value;
			}

			double	P(FVector_double& p, FVector_double& ps) {
				double x = p[0], y = p[1], d;
				double q;
				double L1, L2, L3, L4;
				static FVector_double mus(2), dq(dim);
				d = gap;
				coef_mu(p, mus);// 두 값을 호출해서 알맞게 돌려준다.
				switch (nInterface){

				case 0: //Circular Interface Case
					q = (x*x + y*y) / 2.0;
					ps.setAll(q / mum - d*mup / mug * r0 / mup + (1. / mup - 1. / mum)*r0*r0 / 2., q / mup);
					break;

				case 1: //Ellipsoidal Interface Case
					q = (x*x / 0.49 + y*y / 0.09) / 2.;
					ps.setAll(q / mum - d*mup / mug / mup + (1. / mup - 1. / mum)*r0*r0, q / mup);
					break;
				case 2: //Ellipsoidal Interface with variable alpha
					q = (x*x / A2 + y*y / B2) / 2.0;
					ps.setAll(q / mum - d*mup / mug / mup + (1. / mup - 1. / mum)*r0*r0 / 2., q / mup);
					break;
				case 3:
					//the solutions with "Heart" shape interface with variable alpha
					q = x*x + y*y;
					q = (3.0*q - x)*(3.0*q - x) - q + 0.01;
					q = q / 2.0;
					ps.setAll(q - d*mus[1] / mus[0] * r0, q);
					break;
				case 4:
					//the solutions with "Peanut" shape interface with variable alpha
					q = x*x*x*x / 2.0 - x*x / 4.0 + y*y;
					q = q / 2.0;
					ps.setAll(q / mum - d*mup / mug + (1. / mup - 1. / mum) / 2., q / mup);
					break;
				case 5:
					ps.setAll(0., 0.);
					break;
				case 6:
					ps.setAll(x*sin(2.*CV.PI*y) - sin(2.*CV.PI*y), x*sin(2.*CV.PI*y));
					break;
				case 7:
					ps.setAll(-x*x / 4. + y*y, -x*x / 4. + y*y + d*mup / mug / sqrt(5.)*(x + 2.*y));
					break;
				case 8:
					ps.setAll(x*x / 2. - y*y / 2., x*x / 2. - y*y / 2. - d*mup / mug / sqrt(2.)*(x + y));
					break;
				case 9:
					ps.setAll(2.*(x + y)*(x + y) - 2.*r0*(x + y), (x + y)*(x + y));
					break;
				case 10:
					L1 = (x - x1)*(x - x1) + (y - y1)*(y - y1) - r1*r1;
					L2 = (x - x2)*(x - x2) + (y - y2)*(y - y2) - r2*r2;
					if (Interface(p) >0.) ps.setAll(L1*L2 - 2.*r1, L1*L2);
					else if (L1 <= 0.) ps.setAll(L1*L2 - 2.*r1, L1*L2);
					else ps.setAll(L1*L2 - 2.*r2, L1*L2);
					break;
				case 11:
					L1 = (x - x1)*(x - x1) + (y - y1)*(y - y1) - r1*r1;
					L2 = (x - x2)*(x - x2) + (y - y2)*(y - y2) - r2*r2;
					L3 = (x - x3)*(x - x3) + (y - y3)*(y - y3) - r3*r3;
					L4 = (x - x4)*(x - x4) + (y - y4)*(y - y4) - r4*r4;
					if (Interface(p) >0.) ps.setAll(L1*L2*L3*L4 - 2.*r1*10., L1*L2*L3*L4);
					else if (L1 <= 0.) ps.setAll(L1*L2*L3*L4 - 2.*r1*10., L1*L2*L3*L4);
					else if (L2 <= 0.) ps.setAll(L1*L2*L3*L4 - 2.*r2*10., L1*L2*L3*L4);
					else if (L3 <= 0.) ps.setAll(L1*L2*L3*L4 - 2.*r3*10., L1*L2*L3*L4);
					else ps.setAll(L1*L2*L3*L4 - 2.*r4*10., L1*L2*L3*L4);
					break;
				case 12:
					ps.setAll(sin(x*y), sin(x*y));
					break;
				default:
					printf("\nThere is no such a interface,yet!!");
					break;
				}
				return 0;
			}
			double	P(FVector_double& p) {
				static FVector_double ps(2);
				P(p, ps);																	// 두 값을 호출해서 알맞게 돌려준다.
				if (Interface(p) >= 0.0)	return ps[1];
				return ps[0];
			}

			void	DP(FVector_double& p, FMatrix_double& dps) {
				double x = p[0], y = p[1];
				double d, dxP, dyP, L1, L2, L3, L4;
				static FVector_double mus(2), dq(dim);
				d = gap;
				coef_mu(p, mus);
				switch (nInterface){
				case 0: //Circular Interface Case
					dps.setAll(x / mum, y / mum, x / mup, y / mup);
					break;
				case 1: //Ellipsoidal Interface Case
					dps.setAll(x / 0.49 / mum, y / 0.09 / mum, x / 0.49 / mup, y / 0.09 / mup);
					break;
				case 2: //Ellipsoidal Interface with variable alpha
					dps.setAll(x / A2 / mum, y / B2 / mum, x / A2 / mup, y / B2 / mup);
					break;
				case 3: //Heart Shaped Interface with variable alpha
					dxP = (3.0*(x*x + y*y) - x)*(6.0*x - 1.0) - x;
					dyP = (3.0*(x*x + y*y) - x)*6.0*y - y;
					dps.setAll(dxP, dyP, dxP, dyP);
					break;
				case 4: //Peanut Shaped Interface with variable alpha
					dxP = x*x*x - x / 4.0;
					dyP = y;
					dps.setAll(dxP, dyP, dxP, dyP);
					break;
				case 5:
					dps.setAll(0., 0., 0., 0.);
					break;
				case 6:
					dps.setAll(sin(2.*CV.PI*y), 2.*CV.PI*x*cos(2.*CV.PI*y) - 2.*CV.PI*cos(2.*CV.PI*y), sin(2.*CV.PI*y), x*2.*CV.PI*cos(2.*CV.PI*y));
					break;
				case 7:
					dps.setAll(-x / 2., 2.*y, -x / 2. + d*mup / mug / sqrt(5.), 2.*y + 2.*d*mup / mug / sqrt(5.));
					//cout << "al : "<<d*mup/mug;
					break;
				case 8:
					dps.setAll(x, -1.*y, x - d*mup / mug / sqrt(2.), -1.*y - d*mup / mug / sqrt(2.));
					break;
				case 9:
					dps.setAll(4.*(x + y) - 2.*r0, 4.*(x + y) - 2.*r0, 2.*(x + y), 2.*(x + y));
					break;
				case 10:
					L1 = (x - x1)*(x - x1) + (y - y1)*(y - y1) - r1*r1;
					L2 = (x - x2)*(x - x2) + (y - y2)*(y - y2) - r2*r2;
					dxP = 2.*(x - x1)*L2 + 2.*(x - x2)*L1;
					dyP = 2.*(y - y1)*L2 + 2.*(y - y2)*L1;
					dps.setAll(dxP, dyP, dxP, dyP);
					break;
				case 11:
					L1 = (x - x1)*(x - x1) + (y - y1)*(y - y1) - r1*r1;
					L2 = (x - x2)*(x - x2) + (y - y2)*(y - y2) - r2*r2;
					L3 = (x - x3)*(x - x3) + (y - y3)*(y - y3) - r3*r3;
					L4 = (x - x4)*(x - x4) + (y - y4)*(y - y4) - r4*r4;
					dxP = 2.*(x - x1)*L2*L3*L4 + 2.*(x - x2)*L1*L3*L4 + 2.*(x - x3)*L1*L2*L4 + 2.*(x - x4)*L1*L2*L3;
					dyP = 2.*(y - y1)*L2*L3*L4 + 2.*(y - y2)*L1*L3*L4 + 2.*(y - y3)*L1*L2*L4 + 2.*(y - y4)*L1*L2*L3;
					dps.setAll(dxP, dyP, dxP, dyP);
					break;
				case 12:
					dps.setAll(1., 1., 1., 1.);
					break;
				default:
					printf("\nThere is no such a interface,yet!!");
					break;
				}

			}

			void	DP(FVector_double& p, FVector_double& dp) {
				static FMatrix_double dps(2, 2);
				DP(p, dps);

				if (Interface(p)<0.0)	 dp = dps[0];
				else	dp = dps[1];
			}
			void	V(FVector_double& p, FVector_double& dp) {
				static FMatrix_double dps(2, 2);
				static FVector_double mus(2);
				double x = p[0];
				double y = p[1];
				double r2 = x*x + y*y;
				double r = sqrt(r2);
				switch (nFunction) {
				case 0:
					dps.setAll(-x,-y);
				default:
					DP(p, dps);
					coef_mu(p, mus);

					if (Interface(p) <= 0) {
						dp.op("=", -mum, dps[0]);
					}
					else {
						dp.op("=", -mup, dps[1]);
					}
				}
			}
			double	F(FVector_double& p, FVector_double& fs) {
				double x = p[0], y = p[1];
				double fx, fy, d, L1, L2, L3, L4, dxL1, dyL1, dxL2, dyL2, dxL3, dyL3, dxL4, dyL4;
				static FVector_double mus(2), dq(dim);
				d = gap;
				coef_mu(p, mus);
				switch (nInterface){
				case 0:
					fs.setAll(-2.0, -2.0);
					//fs.setAll(0., 0.);
					break;
				case 1:
					fx = 1.0 / 0.49 + 1.0 / 0.09;
					fy = fx;
					fs.setAll(-1.0* fx, -1.0* fy);
					break;
				case 2: //Ellipsoidal Interface with Circular Type Solution
					fx = 1.0 / A2 + 1.0 / B2;
					fy = fx;
					fs.setAll(-1.0* fx, -1.0* fy);
					break;
				case 3: //Heart Shaped Interface case with variable alpha
					fx = (6.0*x - 1.0)*(6.0*x - 1.0) + (6.0*y)*(6.0*y) + 12.0*(3.0*(x*x + y*y) - x) - 2.0;
					fx = -1.0*mus[1] * fx;
					fy = fx;
					fs.setAll(fx, fy);
					break;
				case 4: //Peanut Shaped Interface case with variable alpha
					fx = -1.0*mus[1] * 3.0*(x*x + 1.0 / 4.0);
					fy = fx;
					fs.setAll(fx, fy);
					break;
				case 5:
					fs.setAll(x*x + y*y - 3.*y, exp(x)*sin(y));
					break;
				case 6:
					fs.setAll(4 * CV.PI*CV.PI*x*sin(2.*CV.PI*y) - 4 * CV.PI*CV.PI*sin(2.*CV.PI*y), 4 * CV.PI*CV.PI*x*sin(2.*CV.PI*y));
					break;
				case 7:
					fs.setAll(-3. / 2., -3. / 2.);
					break;
				case 8:
					fs.setAll(0., 0.);
					break;
				case 9:
					fs.setAll(-8., -4.);
					break;
				case 10:
					L1 = (x - x1)*(x - x1) + (y - y1)*(y - y1) - r1*r1;
					L2 = (x - x2)*(x - x2) + (y - y2)*(y - y2) - r2*r2;
					fx = 2.*L2 + 8.*(x - x1)*(x - x2) + 2.*L1;
					fy = 2.*L2 + 8.*(y - y1)*(y - y2) + 2.*L1;
					fs.setAll(-fx - fy, -fx - fy);
					break;
				case 11:
					L1 = (x - x1)*(x - x1) + (y - y1)*(y - y1) - r1*r1;
					L2 = (x - x2)*(x - x2) + (y - y2)*(y - y2) - r2*r2;
					L3 = (x - x3)*(x - x3) + (y - y3)*(y - y3) - r3*r3;
					L4 = (x - x4)*(x - x4) + (y - y4)*(y - y4) - r4*r4;
					dxL1 = 2.*(x - x1);
					dyL1 = 2.*(y - y1);
					dxL2 = 2.*(x - x2);
					dyL2 = 2.*(y - y2);
					dxL3 = 2.*(x - x3);
					dyL3 = 2.*(y - y3);
					dxL4 = 2.*(x - x4);
					dyL4 = 2.*(y - y4);
					fx = 2.*L2*L3*L4 + 2.*L1*L2*L4 + 2.*L1*L3*L4 + 2.*L1*L2*L3 + 2.*(dxL1*dxL2*L3*L4 + dxL1*dxL3*L2*L4 + dxL1*dxL4*L2*L3 + dxL2*dxL3*L1*L4 + dxL2*dxL4*L1*L3 + dxL3*dxL4*L1*L2);
					fy = 2.*L2*L3*L4 + 2.*L1*L2*L4 + 2.*L1*L3*L4 + 2.*L1*L2*L3 + 2.*(dyL1*dyL2*L3*L4 + dyL1*dyL3*L2*L4 + dyL1*dyL4*L2*L3 + dyL2*dyL3*L1*L4 + dyL2*dyL4*L1*L3 + dyL3*dyL4*L1*L2);
					fs.setAll(-fx - fy, -fx - fy);
					break;
				case 12:
					fs.setAll(1., 1.);
					break;
				default:
					printf("\nThere is no such a interface,yet!!");
					break;
				}
				return 0;
			}
			double	F(FVector_double& p) {
				static FVector_double fs(2);
				F(p, fs);
				if (Interface(p)<0.0)	 return fs[0];
				else	return fs[1];
			}
		};
		class P_IIM_MULTI_LAYER_CIRCLE_GH : public FEM_PROBLEM {
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				double A, B;
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);

				//Input("\nView (x,y) direction", VAR.nData[0] >> VAR.nData[1]);
				VAR.nData[0] = 30; VAR.nData[1] = 60;
				r0=0.64;
				mum=1.;
				mup=1.;
			}
			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				double r;
				double theta = MATH::slope_to_radian(x, y);
				r = sqrt(x*x + y*y) - r0;
				return r;
			}

			double	InterfaceGrad(FVector_double& p, FVector_double& df) {
				double x = p[0], y = p[1];
				double dLx, dLy;
				double theta = MATH::slope_to_radian(x, y);
				df.setAll(2.0*x, 2.0*y);
				
				return 0.0;
			}

			int		IO(FVector_double& p) {
				if (Interface(p) < 0.0)	return CV.IN;
				else return CV.OUT;
				return 0;
			}

			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, middle, Exterior)

				return 0;
			}

			double	coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}

			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p)<0.0)	return mus[0];
				return mus[1];
			}

			double	value_varAlpha(FVector_double& p) {
				double x = p[0], y = p[1];
				double value, d, tempx, tempy;
				static FVector_double vMus(2);
				
				value = 1.;
			//	value = 0.;
				return value;
			}
			double	value_varAlpha(FVector_double& p, int type) {
				double x = p[0], y = p[1];
				double value, d, tempx, tempy;
				double L1, L2, L3, L4;
				static FVector_double vMus(2);
				value = 1.;
			//	value = 0.;
				return value;
			}

			double	P(FVector_double& p, FVector_double& ps) {
				double x = p[0], y = p[1], d;
				double q;
				double L1, L2, L3, L4;
				static FVector_double mus(2), dq(dim);
				d = gap;
				coef_mu(p, mus);// 두 값을 호출해서 알맞게 돌려준다.
				q = (x*x + y*y) / 2.0;
				ps.setAll(q / mum - 1. * r0 / mup + (1. / mup - 1. / mum)*r0*r0 / 2., q / mup);
				return 0;
			}
			double	P(FVector_double& p) {
				static FVector_double ps(2);
				P(p, ps);																	// 두 값을 호출해서 알맞게 돌려준다.
				if (Interface(p) >= 0.0)	return ps[1];
				return ps[0];
			}

			void	DP(FVector_double& p, FMatrix_double& dps) {
				double x = p[0], y = p[1];
				double d, dxP, dyP, L1, L2, L3, L4;
				static FVector_double mus(2), dq(dim);
				d = gap;
				coef_mu(p, mus);
				dps.setAll(x / mum, y / mum, x / mup, y / mup);
			
			}

			void	DP(FVector_double& p, FVector_double& dp) {
				static FMatrix_double dps(2, 2);
				DP(p, dps);

				if (Interface(p)<0.0)	 dp = dps[0];
				else	dp = dps[1];
			}
			void	V(FVector_double& p, FVector_double& dp) {
				static FMatrix_double dps(2, 2);
				static FVector_double mus(2);
				double x = p[0];
				double y = p[1];
				double r2 = x*x + y*y;
				double r = sqrt(r2);
				dps.setAll(-x,-y);
				
			}
			double	F(FVector_double& p, FVector_double& fs) {
				double x = p[0], y = p[1];
				double fx, fy, d, L1, L2, L3, L4, dxL1, dyL1, dxL2, dyL2, dxL3, dyL3, dxL4, dyL4;
				static FVector_double mus(2), dq(dim);
				d = gap;
				coef_mu(p, mus);
				
				fs.setAll(-2.0, -2.0);
				
				return 0;
			}
			double	F(FVector_double& p) {
				static FVector_double fs(2);
				F(p, fs);
				if (Interface(p)<0.0)	 return fs[0];
				else	return fs[1];
			}
		};
		class STAR_SHAPE_IIM_GH : public FEM_PROBLEM { // Governing Equation:  -div(μ▽p) = f
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);
				 
				VAR.nData[0] = 30;
				VAR.nData[1] = 30; 

			//	Input("mum", mum);
			//	Input("mup", mup);

				mum = 1.;
				mup = 100.;
			}
				 
			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y); 
				return pow(3 * r*r - x, 2.) - r*r + 0.03;
			}
			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
	 			return 0;
			}
			double	coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) < 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}
			double	P(FVector_double& p, FVector_double& ps) {
				double x = p[0], y = p[1];
				double r2 = x*x + y*y;
				double r = sqrt(r2);
				double L = Interface(p);
				static FVector_double mus(2);
				coef_mu(p, mus);

				ps.setAll(L*x / mus[0], L*x/ mus[1]);
			//	ps.setAll(L / mus[0], L  / mus[1]);
				return 0;
			}
			double	P(FVector_double& p) {
				static FVector_double ps(2);
				P(p, ps);																	// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) < 0) {
					return ps[0];
				}
				else {
					return ps[1];
				}
			}
			double	P_Jump(FVector_double& p) {
				return 0;
			}
			void	DP(FVector_double& p, FMatrix_double& dps) {
				double x = p[0], y = p[1];
				double r2 = x*x + y*y;
				double r = sqrt(r2);
				static FVector_double mus(2);
				double L = Interface(p);
				coef_mu(p, mus);
				double Ix;
				double Iy;

				Ix = 2 * (3 * r*r - x)*(6 * x - 1) - 2 * x;
				Iy = 2 * (3 * r*r - x)*(6 * y) - 2 * y;

				dps[0][0] = Ix * x / mus[0] + L / mus[0];
				dps[0][1] = Iy * x / mus[0];

				dps[1][0] = Ix * x / mus[1] + L / mus[1];
				dps[1][1] = Iy * x / mus[1];

			//	dps[0][0] = Ix / mus[0] ;
			//	dps[0][1] = Iy / mus[0];

			//	dps[1][0] = Ix / mus[1];
			//	dps[1][1] = Iy / mus[1];


			}
			void	DP(FVector_double& p, FVector_double& dp) {
				static FMatrix_double dps(2, 2);
				DP(p, dps);

				if (Interface(p) < 0) {
					dp = dps[0];
				}
				else {
					dp = dps[1];
				}
			}
			void	V(FVector_double& p, FVector_double& dp) {
				static FMatrix_double dps(2, 2);
				static FVector_double mus(2);
				double x = p[0];
				double y = p[1];
				double r2 = x*x + y*y;
				double r = sqrt(r2); 
				DP(p, dps);
				coef_mu(p, mus);

				if (Interface(p) <= 0) {
					dp.op("=", -mum, dps[0]);
				}
				else {
					dp.op("=", -mup, dps[1]);
				}
			}
			double	Flux_Jump(FVector_double& p, FVector_double& vN) {
				return 0.;
			}
			double	F(FVector_double& p, FVector_double& fs) {
				static FVector_double mus(2);
				double x = p[0], y = p[1];
				double r2 = x*x + y*y;
				double r = sqrt(r2);
				double L = Interface(p);
				double Ixx;
				double Iyy;
				double f;
				double Ix;
				double Iy;
				coef_mu(p, mus);

				Ix = 2 * (3 * r*r - x)*(6 * x - 1) - 2 * x;
				Iy = 2 * (3 * r*r - x)*(6 * y) - 2 * y;

				Ixx = 2 * (6 * x - 1) * (6 * x - 1) + 12 * (3 * r*r - x)- 2;
				Iyy = 2 * (6 * y)*(6 * y) + 12 * (3 * r*r - x) - 2;
				// I*x
				// (Ix*x + I, Iy*x)
				// (Ixx*x + 2Ix, Iyy*x) 
				// (Ixx*x + 2Ix + iyy*x)
				f = -(Ixx*x + 2*Ix + Iyy*x);
			//	f = -(Ixx + Iyy);
	
				fs.setAll(f, f); 
				return 0;
			}
			double	F(FVector_double& p) {
				static FVector_double fs(2);
				F(p, fs);
				if (Interface(p) < 0) {
					return fs[0];
				}
				else {
					return fs[1];
				}
			}
		};
		class P_IIM_MULTI_INTERFACE : public FEM_PROBLEM { // Governing Equation:  -div(μ▽p) = f
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(0., 0., 200., 200.);
				//		Input("\nView (x,y) direction", VAR.nData[0]>>VAR.nData[1]);
				VAR.nData[0] = 30;
				VAR.nData[1] = 30; 

				vMum.make(3);

				mup = pow(10., -9.);
				mum = pow(10., -12.);
				vMum[0] = pow(10., -12.);
				vMum[1] = 5.*pow(10., -13.);
				vMum[2] = 2.*pow(10., -12.); 

			}
			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				double rt = 0.00001*Interface0(p)*Interface1(p)*Interface2(p);
			//	cout << rt << endl;
				return rt;
			}
			double	Interface0(FVector_double& p) {
				double x = p[0], y = p[1];
				double rt = (x - 38)*(x - 38) + (y - 67)*(y - 67) - 24 * 24;
				return rt;
			}
			double	Interface1(FVector_double& p) {
				double x = p[0], y = p[1];
				double rt = (x - 119)*(x - 119) + (y - 57)*(y -57) - 20 * 20; 
				return rt;
			} 
			double	Interface2(FVector_double& p) {
				double x = p[0], y = p[1];
				double rt = (x - 68)*(x - 68) + (y - 134)*(y -134) - 20 * 20; 
			 	return rt;
			}
			double	coef_mu(FVector_double& p) {

				if (Interface(p) > 0){
					return mup;
				}
				else{
					if (Interface0(p) <= 0){
						return vMum[0];
					}
					if (Interface1(p) <= 0){
						return vMum[1];
					}
					if (Interface2(p) <= 0){
						return vMum[2];
					}
				}
			}
			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}
			double	coef_mu(FVector_double& p, int io) {
				  
				if (io == CV.OUT)
					return mup;
				if (io == CV.IN){
					if (Interface0(p) <= 4){
						return vMum[0];
					}
					if (Interface1(p) <= 4){
						return vMum[1];
					}	
					if (Interface2(p) <= 4){
						return vMum[2];
					}
				}				
			} 
			int		boundary_indicator(FVector_double& p) {	
				double x = p[0], y = p[1];
				int rt=1.;
				if (x == RX[1][1]){
					rt = 0.;
				}

				return rt;
			}
			double	P(FVector_double& p, FVector_double& ps) {
				double x = p[0], y = p[1];
			//	double r2 = x*x + y*y;
			//	double r = sqrt(r2);
			//	static FVector_double mus(2);

			//	coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.
			//	ps.setAll(pow(r, 3.) / mus[0], pow(r, 3.) / mus[1] + (1 / mus[0] - 1 / mus[1])*pow(r0, 3.));
				return 0;
			} 
			void	DP(FVector_double& p, FMatrix_double& dps) {
				static FVector_double mus(2);
				double x = p[0], y = p[1];
				double r2 = x*x + y*y;
				double r = sqrt(r2);

				coef_mu(p, mus);
				
				//	double r = sqrt(r2);
				//	static FVector_double mus(2);
				//	static FVector_double vDLevelSet(2);	// derivative levelset

			//	coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.
			//	dps.setAll(3 * x*r / mus[0], 3 * y*r / mus[0], 3 * x*r / mus[1], 3 * y*r / mus[1]);
			} 
			void	DP(FVector_double& p, FVector_double& dp) {
				double x = p[0];
				double y = p[1];
				static FMatrix_double dps(2, 2);
				DP(p, dps);

				if (Interface(p) < 0) {
					dp = dps[0];
				}
				else {
					dp = dps[1];
				}
			//	if (x == RX[0][0]){
				dp.setAll(pow(10., -7.), 0.);
			//	}
			}
			double	F(FVector_double& p, FVector_double& fs) {
				static FVector_double mus(2);
				double x = p[0], y = p[1];
				double r2 = x*x + y*y;
				double r = sqrt(r2);

			// 	fs.setAll(-9 * r, -9 * r);
				return 0;
			} 
			double	F(FVector_double& p) {
				static FVector_double fs(2);
				F(p, fs);
				if (Interface(p) < 0) {
					return fs[0];
				}
				else {
					return fs[1];
				}
			}
		};
		class P_IIM_CONSTNAT_JUMP_CIRCLE_GH : public FEM_PROBLEM { // Governing Equation:  -div(μ▽p) = f
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);

				VAR.nData[0] = 30;
				VAR.nData[1] = 30;
				phi=-1.;//2.;
				r0 = 0.5001;
				Input("mum", mum);
				Input("mup", mup);

			}
			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				return (r - r0);
			}
			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}
			double	coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.
				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) < 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}
			double	P(FVector_double& p, FVector_double& ps) {
				double x = p[0], y = p[1];
				double r2 = x*x + y*y;
				double r = sqrt(r2);
				static FVector_double mus(2);

				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.
				ps.setAll(pow(r, 3.) / mus[0] + phi, pow(r, 3.) / mus[1] + (1 / mus[0] - 1 / mus[1])*pow(r0, 3.));
				ps[0]=-ps[0];
				ps[1]=-ps[1];
				return 0;
			}
			double	P(FVector_double& p) {
				static FVector_double ps(2);
				P(p, ps);																	// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) < 0) {
					return ps[0];
				}
				else {
					return ps[1];
				}
			}
			double	P_Jump(FVector_double& p) {
				//static FVector_double ps(2);
				//P(p, ps);
				//return (ps[0] - ps[1]);
				static FVector_double ps(2);
				P(p, ps);
				return (ps[0] - ps[1]);
			}
			void	DP(FVector_double& p, FMatrix_double& dps) {
				double x = p[0], y = p[1];
				double r2 = x*x + y*y;
				double r = sqrt(r2);
				static FVector_double mus(2);
				coef_mu(p, mus);
				dps.setAll(3 * x*r / mus[0], 3 * y*r / mus[0], 3 * x*r / mus[1], 3 * y*r / mus[1]);
				dps[0][0]=-dps[0][0];
				dps[0][1]=-dps[0][1];
				dps[1][0]=-dps[1][0];
				dps[1][1]=-dps[1][1];
			}
			void	DP(FVector_double& p, FVector_double& dp) {
				static FMatrix_double dps(2, 2);
				DP(p, dps);

				if (Interface(p) < 0) {
					dp = dps[0];
				}
				else {
					dp = dps[1];
				}
			}
			void	V(FVector_double& p, FVector_double& dp) { 
				double x = p[0];
				double y = p[1];
				double r2 = x*x + y*y;
				double r = sqrt(r2);
		
				dp.setAll(3 * x*r, 3 * y*r);
			}
			double	Flux_Jump(FVector_double& p, FVector_double& vN) {
				return 0.;
			}
			double	F(FVector_double& p, FVector_double& fs) {
				static FVector_double mus(2);
				double x = p[0], y = p[1];
				double r2 = x*x + y*y;
				double r = sqrt(r2);

				coef_mu(p, mus);
				fs.setAll(9 * r, 9 * r);
				return 0;
			}
			double	F(FVector_double& p) {
				static FVector_double fs(2);
				F(p, fs);
				if (Interface(p) < 0) {
					return fs[0];
				}
				else {
					return fs[1];
				}
			}
		};
		class P_IIM_ZERO_FLUX_JUMP_CIRCLE : public FEM_PROBLEM { // Governing Equation:  -div(μ▽p) = f
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);

				VAR.nData[0] = 30;
				VAR.nData[1] = 30;
				r0 = 0.6;
				Input("mum", mum);
				Input("mup", mup);

			}
			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				return (r - r0);
			}
			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}
			double	coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.
				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) < 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}
			double	P(FVector_double& p, FVector_double& ps) {
				double x = p[0], y = p[1];
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.
				ps.setAll((3. + x + y)*(3. + x + y) / mus[0]+100000, (3. + x + y)*(3. + x + y) / mus[1]);
				return 0;
			}
			double	P(FVector_double& p) {
				static FVector_double ps(2);
				P(p, ps);																	// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) < 0) {
					return ps[0];
				}
				else {
					return ps[1];
				}
			}
			double	P_Jump(FVector_double& p) {
				//static FVector_double ps(2);
				//P(p, ps);
				//return (ps[0] - ps[1]);
				static FVector_double ps(2);
				P(p, ps);
				return (ps[0] - ps[1]);
			}
			void	DP(FVector_double& p, FMatrix_double& dps) {
				double x = p[0], y = p[1];
				static FVector_double mus(2);
				coef_mu(p, mus);
				dps.setAll(2 * (3. + x + y) / mus[0], 2 * (3. + x + y) / mus[0], 2 * (3. + x + y) / mus[1], 2 * (3. + x + y) / mus[1]);
			}
			void	DP(FVector_double& p, FVector_double& dp) {
				static FMatrix_double dps(2, 2);
				DP(p, dps);

				if (Interface(p) < 0) {
					dp = dps[0];
				}
				else {
					dp = dps[1];
				}
			}
			void	V(FVector_double& p, FVector_double& dp) {
				double x = p[0];
				double y = p[1];
				dp.setAll(-2 * (3. + x + y), -2 * (3. + x + y));
			}
			void	V(FVector_double& p, FMatrix_double & mp) {
				double x = p[0];
				double y = p[1];
				mp[0].setAll(-2 * (3. + x + y), -2 * (3. + x + y));
				mp[1].setAll(-2 * (3. + x + y), -2 * (3. + x + y));
			}
			double	Flux_Jump(FVector_double& p, FVector_double& vN) {

				//return (ps[0] - ps[1]);
				static FMatrix_double mps(2,2);
				V(p, mps);
				return ((mps[0], vN) - (mps[0], vN));

			//	return 0.;
			}
			double	F(FVector_double& p, FVector_double& fs) {
				static FVector_double mus(2);
				double x = p[0], y = p[1];
				fs.setAll(-4., -4.);
				return 0;
			}
			double	F(FVector_double& p) {
				static FVector_double fs(2);
				F(p, fs);
				if (Interface(p) < 0) {
					return fs[0];
				}
				else {
					return fs[1];
				}
			}
		};
		class P_IIM_ZERO_FLUX_JUMP_ELLIPSE : public FEM_PROBLEM { // Governing Equation:  -div(μ▽p) = f
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);

				VAR.nData[0] = 30;
				VAR.nData[1] = 30;
			//	Input("r0", r0);
				r0 = 0.42;
				mum = 1000.;
				mup = 1.;
			//	Input("mum", mum);
			//	Input("mup", mup);

			}
			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				return x*x + y*y / 2. - r0*r0;
			}
			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}
			double	coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.
				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) < 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}
			double	P(FVector_double& p, FVector_double& ps) {
				double x = p[0], y = p[1];
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.
				ps.setAll((3. + x + y)*(3. + x + y)*(3. + x + y) / mus[0]+10, (3. + x + y)*(3. + x + y)*(3. + x + y) / mus[1]);
				return 0;
			}
			double	P(FVector_double& p) {
				static FVector_double ps(2);
				P(p, ps);																	// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) < 0) {
					return ps[0];
				}
				else {
					return ps[1];
				}
			}
			double	P_Jump(FVector_double& p) {
				//static FVector_double ps(2);
				//P(p, ps);
				//return (ps[0] - ps[1]);
				static FVector_double ps(2);
				P(p, ps);
				return (ps[0] - ps[1]);
			}
			void	DP(FVector_double& p, FMatrix_double& dps) {
				double x = p[0], y = p[1];
				static FVector_double mus(2);
				coef_mu(p, mus);
				dps.setAll(3 * (3. + x + y)*(3. + x + y) / mus[0], 3 * (3. + x + y)*(3. + x + y) / mus[0], 3 * (3. + x + y)*(3. + x + y) / mus[1], 3 * (3. + x + y)*(3. + x + y) / mus[1]);
			}
			void	DP(FVector_double& p, FVector_double& dp) {
				static FMatrix_double dps(2, 2);
				DP(p, dps);

				if (Interface(p) < 0) {
					dp = dps[0];
				}
				else {
					dp = dps[1];
				}
			}
			void	V(FVector_double& p, FVector_double& dp) {
				double x = p[0];
				double y = p[1];
				dp.setAll(-3 * (3. + x + y)*(3. + x + y), -3 * (3. + x + y)*(3. + x + y));
			}
			void	V(FVector_double& p, FMatrix_double & mp) {
				double x = p[0];
				double y = p[1];
				mp[0].setAll(-3 * (3. + x + y)*(3. + x + y), -3 * (3. + x + y)*(3. + x + y));
				mp[1].setAll(-3 * (3. + x + y)*(3. + x + y), -3 * (3. + x + y)*(3. + x + y));
			}
			double	Flux_Jump(FVector_double& p, FVector_double& vN) {

				//return (ps[0] - ps[1]);
				static FMatrix_double mps(2, 2);
				V(p, mps);
				return ((mps[0], vN) - (mps[0], vN));

				//	return 0.;
			}
			double	F(FVector_double& p, FVector_double& fs) {
				static FVector_double mus(2);
				double x = p[0], y = p[1];
				fs.setAll(-12 * (3. + x + y), -12 * (3. + x + y));
				return 0;
			}
			double	F(FVector_double& p) {
				static FVector_double fs(2);
				F(p, fs);
				if (Interface(p) < 0) {
					return fs[0];
				}
				else {
					return fs[1];
				}
			}
		};
		class P_IIM_NONSMOOTH : public FEM_PROBLEM { // Governing Equation:  -div(μ▽p) = f
		public:
			void initialize(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);

			//	Input("mum", mum);
			//	Input("mup", mup);
			//	Input("k", k);
				mum = 1.;
				mup = 1000.;
				k = 0.3;

			}
			double Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				return y*x + k;
			}
			double coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);              // (Interior, Exterior)
				return 0;
			}
			double coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.
				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.
				if (Interface(p) < 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}
			double P(FVector_double& p, FVector_double& ps) {
				double x = p[0], y = p[1];
				static FVector_double mus(2);
				coef_mu(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.
				ps.setAll((x*y + k) / mus[0] + x*x - y*y, (x*y + k) / mus[1] + x*x - y*y);
				return 0;
			}
			double P(FVector_double& p) {
				static FVector_double ps(2);
				P(p, ps);                 // 두 값을 호출해서 알맞게 돌려준다.
				if (Interface(p) < 0) {
					return ps[0];
				}
				else {
					return ps[1];
				}
			}
			void DP(FVector_double& p, FMatrix_double& dps) {
				double x = p[0], y = p[1];
				static FVector_double mus(2);
				coef_mu(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.
				dps.setAll(y / mus[0] + 2.*x, x / mus[0] - 2.*y, y / mus[1] + 2.*x, x / mus[1] - 2.*y);
			}
			void DP(FVector_double& p, FVector_double& dp) {
				static FMatrix_double dps(2, 2);
				DP(p, dps);
				if (Interface(p) < 0) {
					dp = dps[0];
				}
				else {
					dp = dps[1];
				}
			}
			void  V(FVector_double& p, FVector_double& vV) {
				static FVector_double mus(2);
				static FMatrix_double dps(2, 2);
				DP(p, dps);
				coef_mu(p, mus);
				if (Interface(p)<0){
					vV.op("=", -1 * mus[0], dps[0]);
				}
				else{
					vV.op("=", -1 * mus[1], dps[1]);
				}
			}

			double F(FVector_double& p, FVector_double& fs) {
				static FVector_double mus(2);
				double x = p[0], y = p[1];
				coef_mu(p, mus);
				fs.setAll(0., 0.);
				return 0;
			}
			double F(FVector_double& p) {
				static FVector_double fs(2);
				F(p, fs);
				if (Interface(p) < 0) {
					return fs[0];
				}
				else {
					return fs[1];
				}
			}
		};
		class IIM_CIRCLE_FIXED : public FEM_PROBLEM { // Governing Equation:  -div(μ▽p) = f
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);

				//		Input("\nView (x,y) direction", VAR.nData[0]>>VAR.nData[1]);
				VAR.nData[0] = 30;
				VAR.nData[1] = 30;

				printf("\n[0] Kink");
				printf("\n[1] Circle");
				printf("\n[2] Star Shape");
				printf("\n[3] Cardioid");
				printf("\n[4] Heart");
				printf("\n[5] Straight Line");
				printf("\n[6] Interface Edge");
				printf("\n[7] Kink Hou");
				printf("\n[100] Homogeneous");
			//	Input("\nChoose a Interface", nInterface);
				nInterface = 1;

				
				switch (nInterface) {
				case 1: //circle
					//	Input("Radious", r0);
					r0 = 0.3111;
					//	cout << endl;
					break;

				case 5:	// straight line
					vDirection.make(__.dim);													// 방향벡터의 왼쪽이 Omega^- 가 되도록 한다.
					vCenter.make(__.dim);														// 직선의 중심이 어디인지를 나타낸다.

					Input("center-x", vCenter[0]);
					Input("center-y", vCenter[1]);
					Input("x-direction", vDirection[0]);
					Input("y-direction", vDirection[1]);

					vDirection.normalize();
					MATH::rotate2D(vDirection, 0., 1., false);									// -90도 회전시킨다.
					break;

				case 6: // interface edge
					vOp.make(1);
					Input("perturbation: ", perturbed);
					break;

				case 7: // Kink Hou
					//__.RX.make(__.dim, __.dim).setAll(-1.,-1., 3.,1.);
					RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 3., 1.);

					Input("perturbation: ", perturbed);
					break;
				}

				printf("\n");
				printf("\n[0] Complicated Sin");
				printf("\n[1] -:6 x^2 + 7 y^2      +:Sin[3 x y] + Cos[5 x^2 y^2]       beta-:sin(x*y + 3)   beta+:cos(x*x - y*y + 2)");
				printf("\n[2] -:4-x*x-y*y,         +:x*x + y*y");
				printf("\n[3] -:4-x*x-y*y,         +:x*x + y*y    beta-:r^2  beta+:constant");
				printf("\n[4] -:6 x^2 + 7 y^2      +:Sin[3 x y] + Cos[5 x^2 y^2]    beta-:r^2  beta+:constant");
				printf("\n[5] -:x*x + y*y + 2      +:1 - x*x - y*y    beta-:x*y + 3     beta+:x*x - y*y + 3");
				printf("\n[6] -:x*x + y*y + 2      +:1 - x*x - y*y    beta-:mum      beta+:x*x - y*y + x*y +3");
				printf("\n[7] -:sin(2*x*x + y*y + 2)/mum + x      +:cos(1 - x*x - y*y)/mup    beta-:mum      beta+:mup");
				printf("\n[8] -:pow(r*r, 5./6) + sin(x+y)   +:8         beta-:2 + sin(x + y)     beat+:1");
				printf("\n[9] -:const1/mus[0]				+:const2/mus[1]");
				printf("\n[10] -:sin(10xy)/mus[0]			+:cos(y)/mus[1]");
				printf("\n[11] -:x			+:0");
				printf("\n[[ Homogeneous Jumps ]]");
				printf("\n[100] -LevelSet/beta- +:*LevelSet/beta+");
				printf("\n[101] Zilin Lee -:r^3/mum    +:r^3/mup + (1/mum - 1/mup)r0^3");

			//	Input("\nChoose a Function", nFunction);
				nFunction = 101;
				switch (nFunction) {
				case 0: case 7: case 10: case 100: case 101:
				//	Input("mum", mum);
				//	Input("mup", mup);
					mum = 1;
					mup = 1000;
					break;

				case 3: case 4:
					Input("beta+", mup);
					break;

				case 6:
					Input("beta-", mum);
					break;

				case 9:
					//mum = mup = 1;
					Input("mum", mum);
					Input("mup", mup);
					vOp.make(2);
					Input("const1", vOp[0]);
					Input("const2", vOp[1]);
					break;
				}
			}
			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				double theta = MATH::slope_to_radian(x, y);

				switch (nInterface) {
				case 0:	// kink(left)
					if (y>0) return (y + 2 * x);
					else return (x - 2 * y);

				case 1: // circle
					return (r - r0);

				case 2: // star shape
					return (r - 0.2*sin(5 * theta - CV.PI / 5) - 0.5);

				case 3: // cardioid
					return pow(3 * r*r - x, 2.) - r*r;

				case 4: // heart
					return pow(3 * r*r - x, 2.) - r*r + 0.01;

				case 5: // straight line
					return (vDirection, p - vCenter);

				case 6: // interface edge
					if (y >= 0) return (x + y + perturbed);
					else return (x + perturbed);

				case 7: // Kink Hou
					if (x + y>0) return (y - 2 * x + perturbed);
					else return (y + 0.5*x + perturbed);

				case 100: // homogeneous
					return sin(4 * (x*x - y*y));
					//case 5: // kink(upper)
					//	if(y>0
					//	return 
				}
				return 0;												// 내적값을 준다.
			}
			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];

				switch (nFunction) {
				case 0: case 7:	case 9: case 10: case 100: case 101:
					mus.setAll(mum, mup);														// (Interior, Exterior)
					break;

				case 1:
					mus.setAll(sin(x*y + 3), cos(x*x - y*y + 2));
					break;

				case 2:
					mus.setAll(x*y + 2, x*x - y*y + 3);
					break;

				case 3: case 4:
					mus.setAll(x*x + y*y, mup);
					break;

				case 5:
					mus.setAll(x*y + 3, x*x - y*y + 3);
					break;

				case 6:
					mus.setAll(mum, x*x - y*y + x*y + 3);
					break;

				case 8:
					mus.setAll(2 + sin(x + y), 1.);
					break;

				default:
					mus.setAll(1., 1.);
					break;
				}
				return 0;
			}
			double	coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) < 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}
			int	boundary_indicator(FVector_double	& p) {
				double x = p[0];
				double y = p[1];
				// ret=1. normal. ret=0. dirichlet.
				double rt = 1;
				if (x == 1.)
					rt = 0;

			//	rt = 0.;
				return rt;
			}

			double	P(FVector_double& p, FVector_double& ps) {
				double x = p[0], y = p[1];
				double r2 = x*x + y*y;
				double r = sqrt(r2);
				static FVector_double mus(2);

				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				switch (nFunction) {
				case 0:		ps.setAll(sin(10 * x*(-2 + y)) / mus[0], x*x / mus[1]);															// (Interior, Exterior)
					break;

				case 1:		ps.setAll(6 * x*x + 7 * y*y, sin(3 * x*y) + cos(5 * x*x*y*y));
					break;

				case 2: case 3:
					ps.setAll(4 - x*x - y*y, (x*x + y*y) / mus[1]);
					break;

				case 4:
					ps.setAll(6 * x*x + 7 * y*y, (sin(3 * x*y) + cos(5 * x*x*y*y)) / mus[1]);
					break;

				case 5: case 6:
					ps.setAll(x*x + y*y + 2, 1 - x*x - y*y);
					break;

				case 7:
					ps.setAll(sin(2 * x*x + y*y + 2) / mus[0] + x, cos(1 - x*x - y*y) / mus[1]);
					break;

				case 8:
					ps.setAll(pow(r2, 5. / 6) + sin(x + y), 8.);
					break;

				case 9:
					ps.setAll(vOp[0] / mus[0], vOp[1] / mus[1]);
					break;

				case 10:
					ps.setAll(sin(10 * x*y) / mus[0], cos(y) / mus[1]);															// (Interior, Exterior)
					break;

				case 11:
					ps.setAll(x, 0.);
					break;

				case 100:	// homogeneous case
					//ps.setAll((r - 0.2*sin(5*theta - CV.PI/5) + 0.5)/mus[0], (r - 0.2*sin(5*theta - CV.PI/5) + 0.5)/mus[1]);
					ps.setAll(sin(4 * (x*x - y*y)) / mus[0], sin(4 * (x*x - y*y)) / mus[1]);
					break;

				case 101:
					ps.setAll(pow(r, 3.) / mus[0], pow(r, 3.) / mus[1] + (1 / mus[0] - 1 / mus[1])*pow(r0, 3.));
					break;
				}
				return 0;
			}
			double	P(FVector_double& p) {
				static FVector_double ps(2);
				P(p, ps);																	// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) < 0) {
					return ps[0];
				}
				else {
					return ps[1];
				}
			}
			double	P_Jump(FVector_double& p) {
				//static FVector_double ps(2);
				//P(p, ps);
				//return (ps[0] - ps[1]);
				static FVector_double ps(2);
				P(p, ps);
				double x = p[0], y = p[1];
				double r2 = x*x + y*y;
				double r = sqrt(r2);
				static FVector_double mus(2);

				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				// 정확히 0이 나와야 하는 경우도(즉, 수학적으로 동일한 식도) 계산과정에서 round off error가 발생한다.
				// 따라서 직접적으로 계산해서 함수를 대입해주어야 한다.
				// -. 되도록이면 계산과정이 적도록
				// -. 위험도: 1.나눗셈 2.곱셈
				switch (nFunction) {
				case 9:
					return (vOp[0] / mus[0] - vOp[1] / mus[1]);

				case 101:
					return 0;

				default:
					return (ps[0] - ps[1]);
				}
			}
			void	DP(FVector_double& p, FMatrix_double& dps) {
				double x = p[0], y = p[1];
				double r2 = x*x + y*y;
				double r = sqrt(r2);
				static FVector_double mus(2);
				static FVector_double vDLevelSet(2);	// derivative levelset

				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.
				switch (nFunction) {
				case 0:
					dps.setAll(10 * (-2 + y)*cos(10 * x*(-2 + y)) / mus[0], 10 * x*cos(10 * x*(-2 + y)) / mus[0], 2 * x / mus[1], 0.);
					break;

				case 1:
					dps.setAll(12 * x, 14 * y, y*(3 * cos(3 * x*y) - 10 * x*y*sin(5 * x*x*y*y)), x*(3 * cos(3 * x*y) - 10 * x*y*sin(5 * x*x*y*y)));
					break;

				case 2:	case 3:
					dps.setAll(-2 * x, -2 * y, 2 * x / mus[1], 2 * y / mus[1]);
					break;

				case 4:
					dps.setAll(12 * x, 14 * y, (y*(3 * cos(3 * x*y) - 10 * x*y*sin(5 * x*x*y*y))) / mus[1], (x*(3 * cos(3 * x*y) - 10 * x*y*sin(5 * x*x*y*y))) / mus[1]);
					break;

				case 5: case 6:
					dps.setAll(2 * x, 2 * y, -2 * x, -2 * y);
					break;

				case 7:
					dps.setAll(4 * x*cos(2 + 2 * x*x + y*y) / mus[0] + 1., 2 * y*cos(2 + 2 * x*x + y*y) / mus[0], 2 * x*sin(1 - x*x - y*y) / mus[1], 2 * y*sin(1 - x*x - y*y) / mus[1]);
					break;

				case 8:
					dps.setAll((5 * x) / (3 * pow(r2, 1. / 6)) + cos(x + y), (5 * y) / (3 * pow(r2, 1. / 6)) + cos(x + y), 0., 0.);
					break;

				case 9:
					dps.clear();
					break;

				case 10:
					dps.setAll(10 * y*cos(10 * x*y) / mus[0], 10 * x*cos(10 * x*y) / mus[0], 0., -sin(y) / mus[1]);
					break;

				case 11:
					dps.setAll(1., 0., 0., 0.);
					break;

				case 100: // Homogeneous Case (Starfish)
					//dps[0].setAll(x/r + (y/r2)*cos(5*theta - CV.PI/5), y/r - (x/r2)*cos(5*theta - CV.PI/5)) /= (mus[0]);
					//dps[1].setAll(x/r + (y/r2)*cos(5*theta - CV.PI/5), y/r - (x/r2)*cos(5*theta - CV.PI/5)) /= (mus[1]);
					dps[0].setAll(8 * x*cos(4 * (x*x - y*y)), -8 * y*cos(4 * (x*x - y*y))) /= mus[0];
					dps[1].setAll(8 * x*cos(4 * (x*x - y*y)), -8 * y*cos(4 * (x*x - y*y))) /= mus[1];
					break;

				case 101:
					dps.setAll(3 * x*r / mus[0], 3 * y*r / mus[0], 3 * x*r / mus[1], 3 * y*r / mus[1]);
					break;
				}
			}
			void	DP(FVector_double& p, FVector_double& dp) {
				static FMatrix_double dps(2, 2);
				DP(p, dps);

				if (Interface(p) < 0) {
					dp = dps[0];
				}
				else {
					dp = dps[1];
				}
			}
			double	Flux_Jump(FVector_double& p, FVector_double& vN) {
				static FMatrix_double dps(2, 2);
				static FVector_double mus(2);
				static FVector_double dp_exact(2);
				double x = p[0], y = p[1];
				DP(p, dps);
				coef_mu(p, mus);

				switch (nFunction) {
				case 9: case 101:
					return 0;

				case 10:
					dp_exact.setAll(10 * y*cos(10 * x*y), 10 * x*cos(10 * x*y) + sin(y));
					return (dp_exact, vN);

				default:
					return (mus[0] * dps[0] - mus[1] * dps[1], vN);
				}
				//double fjump = fabs(( mus[0]*dps[0] - mus[1]*dps[1], vN));
				//if(fjump < 1.0E-16) return 0;
				//else return fjump;
			}
			double	F(FVector_double& p, FVector_double& fs) {
				static FVector_double mus(2);
				double x = p[0], y = p[1];
				double r2 = x*x + y*y;
				double r = sqrt(r2);

				coef_mu(p, mus);
				switch (nFunction) {
				case 0:		fs.setAll(100 * (x*x + pow((-2 + y), 2.))*sin(10 * x*(-2 + y)), -2.);
					break;
				case 1:		fs.setAll(-26 * (x*y*cos(3 + x*y) + sin(3 + x*y)), (x*x + y*y)*cos(2 + x*x - y*y)*(100 * x*x*y*y*cos(5 * x*x*y*y) + 9 * sin(3 * x*y) + 10 * sin(5 * x*x*y*y)));
					break;
				case 2:		fs.setAll(8 * (1 + x*y), -12 - 8 * x*x - 8 * y*y);
					break;
				case 3:		fs.setAll(8 * (x*x + y*y), -4.);
					break;
				case 4:		fs.setAll(-50 * x*x - 54 * y*y, (x*x + y*y)*(100 * x*x*y*y*cos(5 * x*x*y*y) + 9 * sin(3 * x*y) + 10 * sin(5 * x*x*y*y)));
					break;
				case 5:		fs.setAll(-12 - 8 * x*y, 12 + 8 * x*x - 8 * y*y);
					break;
				case 6:		fs.setAll(-4 * mus[0], 4 * (3 + 2 * x*x + 2 * x*y - 2 * y*y));
					break;
				case 7:		fs.setAll(2 * (-3 * cos(2 + 2 * x*x + y*y) + 2 * (4 * x*x + y*y)*sin(2 + 2 * x*x + y*y)),
					4 * ((x*x + y*y)*cos(1 - x*x - y*y) - sin(1 - x*x - y*y)));
					break;
				case 8:		fs.setAll(-1. / (9 * pow(r2, 1. / 6))*(50 + 15 * (x + y)*cos(x + y) + 18 * pow(r2, 1. / 6)*cos(2 * (x + y)) + 25 * sin(x + y) - 36 * pow(r2, 1. / 6)*sin(x + y)), 0.);
					break;
				case 9:		fs.setAll(0., 0.);
					break;
				case 10:	fs.setAll(100 * r2*sin(10 * x*y), cos(y));
					break;
				case 11:	fs.setAll(0., 0.);
					break;
				case 100:	//fs.setAll((-1/r - 5/r2*sin(5*theta - CV.PI/5))/mus[0], (-1/r - 5/r2*sin(5*theta - CV.PI/5))/mus[1]);
					fs.setAll(64 * r2*sin(4 * (x*x - y*y)) / mus[0], 64 * r2*sin(4 * (x*x - y*y)) / mus[1]);
					break;
				case 101:
					fs.setAll(-9 * r, -9 * r);
					break;
				}

				return 0;
			}
			double	F(FVector_double& p) {
				static FVector_double fs(2);
				F(p, fs);
				if (Interface(p) < 0) {
					return fs[0];
				}
				else {
					return fs[1];
				}
			}
		};
		class P_IIM_HYONYK : public FEM_PROBLEM {
		public:

			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);

				printf("\n[0] Circle");
				printf("\n[1] Ellipse");
				printf("\n[2] peanut-shape");
				Input("\nChoose a Interface", nInterface);

				switch (nInterface) {
				case 0: //circle
					Input("Radious", r0);
					Input("alpha_0", alpha_0);
					break;
				case 1: //Ellipse
					Input("Radious", r0);
					Input("a", a);
					Input("b", b);
					Input("alpha_0", alpha_0);
					break;
				case 2: //peanut-shape
					Input("alpha_0", alpha_0);
					break;
				default:
					Input("Radious", r0);
					Input("alpha_0", alpha_0);
				}

				Input("mum", mum);
				Input("mup", mup);
			}
			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);

				switch (nInterface) {
				case 0: // circle
					return (r - r0);
				case 1: // ellipse
					return (x*x / (a*a) + y*y / (b*b) - r0*r0);
				case 2: // peanut-shape
					return x*x*x*x / 2. - x*x / 4. + y*y - 0.0371;
				default:
					return (r - r0);
				}
				return 0;												// 내적값을 준다.
			}
			double	coef_mu(FVector_double& p, FVector_double& mus) {
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}
			double	coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) < 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}
			double	P(FVector_double& p, FVector_double& ps) {
				double x = p[0], y = p[1];
				double r2 = x*x + y*y;
				double r = sqrt(r2);
				static FVector_double mus(2);

				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				switch (nInterface) {
				case 0:		ps.setAll((x*x + y*y) / 2. - alpha_0*r0, (x*x + y*y) / 2.);															// (Interior, Exterior)
					break;
				case 1:		ps.setAll((x*x / (a*a) + y*y / (b*b)) / 2. - alpha_0*r0, (x*x / (a*a) + y*y / (b*b)) / 2.);
					break;
				case 2:
					ps.setAll((x*x*x*x / 2. - x*x / 4. + y*y) / 2. - alpha_0, (x*x*x*x / 2. - x*x / 4. + y*y) / 2.);
					break;
				default:
					ps.setAll(0., 0.);
				}
				return 0;
			}
			double	P(FVector_double& p) {
				static FVector_double ps(2);
				P(p, ps);																	// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) < 0) {
					return ps[0];
				}
				else {
					return ps[1];
				}
			}
			double	P_Jump(FVector_double& p) {
				static FVector_double ps(2);
				P(p, ps);
				double x = p[0], y = p[1];
				double r2 = x*x + y*y;
				double r = sqrt(r2);
				static FVector_double mus(2);

				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				// 정확히 0이 나와야 하는 경우도(즉, 수학적으로 동일한 식도) 계산과정에서 round off error가 발생한다.
				// 따라서 직접적으로 계산해서 함수를 대입해주어야 한다.
				// -. 되도록이면 계산과정이 적도록
				// -. 위험도: 1.나눗셈 2.곱셈
				return (ps[0] - ps[1]);
			}
			void	DP(FVector_double& p, FMatrix_double& dps) {
				double x = p[0], y = p[1];
				double r2 = x*x + y*y;
				double r = sqrt(r2);
				static FVector_double mus(2);
				static FVector_double vDLevelSet(2);	// derivative levelset

				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.
				switch (nInterface) {
				case 0:		dps.setAll(x, y, x, y);															// (Interior, Exterior)
					break;
				case 1:		dps.setAll(x / (a*a), y / (b*b), x / (a*a), y / (b*b));
					break;
				case 2:
					dps.setAll(x*x*x - x / 4, y, x*x*x - x / 4, y);
					break;
				default:
					dps.setAll(x, y, x, y);
					break;
				}
			}
			void	DP(FVector_double& p, FVector_double& dp) {
				static FMatrix_double dps(2, 2);
				DP(p, dps);

				if (Interface(p) < 0) {
					dp = dps[0];
				}
				else {
					dp = dps[1];
				}
			}
			double	Flux_Jump(FVector_double& p, FVector_double& vN) {
				static FMatrix_double dps(2, 2);
				static FVector_double mus(2);
				static FVector_double dp_exact(2);
				double x = p[0], y = p[1];
				DP(p, dps);
				coef_mu(p, mus);

				return (mus[0] * dps[0] - mus[1] * dps[1], vN);
			}
			double	F(FVector_double& p, FVector_double& fs) {
				static FVector_double mus(2);
				double x = p[0], y = p[1];
				double r2 = x*x + y*y;
				double r = sqrt(r2);

				coef_mu(p, mus);
				switch (nInterface) {
				case 0:
					fs.setAll(-2., -2.);															// (Interior, Exterior)
					break;
				case 1:
					fs.setAll(-1. / (a*a) - 1. / (b*b), -1. / (a*a) - 1. / (b*b));
					break;
				case 2:
					fs.setAll(-3.*x*x - 3. / 4., -3.*x*x - 3. / 4.);
					break;
				default:
					fs.setAll(-2., -2.);
					break;
				}
				return 0;
			}
			double	F(FVector_double& p) {
				static FVector_double fs(2);
				F(p, fs);
				if (Interface(p) < 0) {
					return fs[0];
				}
				else {
					return fs[1];
				}
			}
			double  coef_alpha(FVector_double& p)
			{
				double x = p[0], y = p[1];
				switch (nInterface) {
				case 0:
					return alpha_0;															// (Interior, Exterior)
					break;
				case 1:
					return alpha_0;															// (Interior, Exterior)
					break;
				case 2:
					return alpha_0;															// (Interior, Exterior)
					break;
				default:
					return alpha_0;															// (Interior, Exterior)
					break;
				}
			}
		};
		class P_IIM_CIRCLE : public FEM_PROBLEM {
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);

				Input("\nView (x,y) direction", VAR.nData[0] >> VAR.nData[1]);
				printf("\n--------------------------------------");
				printf("\n|       Interfaces for Solution      |");
				printf("\n--------------------------------------");
				printf("\n(0) Circle");
				printf("\n(1) Ellipsoid");
				printf("\n(2) Ellipsoid with variable alpha");
				printf("\n(3) Heart Shape with variable alpha");
				printf("\n(4) Peanut Shape with variable alpha");
				printf("\n--------------------------------------");
				Input("\nChoose Interface: ", nInterface);
				switch (nInterface){
				case 0:
					Input("\n\nCircle Radius", r0);
					break;
				case 1:
					Input("\n\nEllipsoidal Radius(default: r0=1)", r0);
					r0 = 1.0;
					break;
				case 2:
					cout << "Ellipsoidal Interface with Radius(default: r0=1)" << endl;
					r0 = 1.0;
					Input("\n\nThe first axis (a^2=A2=0.49)", A2);
					Input("\n\nThe second axis (b^2=B2=0.09)", B2);
					cout << "A2(a^2)=" << A2 << endl;
					cout << "B2(b^2)=" << B2 << endl;
					break;
				case 3:
					cout << "Heart Shape Interface is chosen." << endl;
					Input("\n\nCoefficient of the solution functions", c0);
					Input("\n\nr0", r0);
					break;
				case 4:
					cout << "Peanut Shape Interface is chosen." << endl;
					Input("\n\nCoefficient of the solution functions (<0.03)", c0);
					Input("\n\nr0", r0);
					cout << "c0=" << c0 << endl;
					break;
				default:
					printf("\nThere is no such a interface,yet!!");
					break;
				}
				cout << "r0=" << r0 << endl;

				Input("gap", gap);
				Input("mu_inside", mum);
				Input("mu_outside", mup);
				cout << "mum=" << mum << endl;
				cout << "mup=" << mup << endl;
			}

			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				double r;
				double theta = MATH::slope_to_radian(x, y);
				switch (nInterface){
				case 0:
					//Circular Interface 
					r = sqrt(x*x + y*y) - r0;
					break;
				case 1:
					//Circular Interface
					r = sqrt(x*x / 0.49 + y*y / 0.09) - r0;
					break;
				case 2:
					//Ellipsoidal Interface with variable alpha
					r = sqrt(x*x / A2 + y*y / B2) - r0;
					break;
				case 3:
					//Heart shaped Interface with variable alpha
					r = x*x + y*y;
					r = (3.0*r - x)*(3.0*r - x) - r + 0.01;
					break;
				case 4:
					//r = exp(x)*( -sin(y) + y*cos(y) + y*( x*cos(x) + cos(x) -x*sin(x)) );
					//r = x*x*x*x/2.0 - x*x/4.0 + y*y - r0;
					r = x*x*x*x / 2.0 - x*x / 4.0 + y*y - c0;
					break;
				default:
					printf("\nThere is no such a interface,yet!!");
					break;
				}

				return r;

			}

			double	InterfaceGrad(FVector_double& p, FVector_double& df) {
				double x = p[0], y = p[1];
				double dLx, dLy;
				double theta = MATH::slope_to_radian(x, y);
				switch (nInterface){
				case 0:
					df.setAll(2.0*x, 2.0*y);
					break;
				case 1:
					df.setAll(2.0*x / 0.49, 2.0*y / 0.09);
					break;
				case 2:	//Ellipsoidal Interface with variable alpha
					df.setAll(2.0*x / A2, 2.0*y / B2);
					break;
				case 3: //Heart Shaped Interface with variable alpha
					/*dLx = exp(x)*(-sin(y) + y*cos(y) + y*(2.0*cos(x) -2.0*x*sin(x) -2.0*sin(x)));
					dLy = exp(x)*(-y*sin(y) + x*cos(x) + cos(x) -x*sin(x));*/
					dLx = 2.0*(3.0*(x*x + y*y) - x)*(6.0*x - 1.0) - 2.0*x;
					dLy = 2.0*(3.0*(x*x + y*y) - x)*(6.0*y) - 2.0*y;
					df.setAll(dLx, dLy);
					break;
				case 4:
					dLx = 2.0*x*x*x - x / 2.0;
					dLy = 2.0*y;
					df.setAll(dLx, dLy);
					break;
				default:
					printf("\nThere is no such a interface,yet!!");
					break;
				}
				return 0.0;
			}

			int		IO(FVector_double& p) {
				if (Interface(p) < 0.0)	return CV.IN;
				else return CV.OUT;
				return 0;
			}

			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, middle, Exterior)

				return 0;
			}

			double	coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}

			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p)<0.0)	return mus[0];
				return mus[1];
			}

			double	value_varAlpha(FVector_double& p) {
				double x = p[0], y = p[1];
				double value, d, tempx, tempy;
				static FVector_double vMus(2);
				d = gap;
				_problem->coef_mu(p, vMus);
				switch (nInterface){
				case 2:
					value = sqrt(x*x / (A2*A2) + y*y / (B2*B2));
					break;
				case 3:
					tempx = (3.0*(x*x + y*y) - x)*(6.0*x - 1.0) - x;
					tempy = (3.0*(x*x + y*y) - x)*(6.0*y) - y;
					value = sqrt(tempx*tempx + tempy*tempy);
				case 4:
					value = sqrt((x*x*x - x / 4.0)*(x*x*x - x / 4.0) + y*y);
					break;
				default:
					value = 1.0;
					break;
				}
				value = d*vMus[1] / vMus[0] * r0 / value;
				return value;
			}

			double	P(FVector_double& p, FVector_double& ps) {
				double x = p[0], y = p[1], d;
				double q;
				static FVector_double mus(2), dq(dim);
				d = gap;
				coef_mu(p, mus);// 두 값을 호출해서 알맞게 돌려준다.
				switch (nInterface){

				case 0: //Circular Interface Case
					q = (x*x + y*y) / 2.0;
					ps.setAll(q - d*mus[1] / mus[0] * r0, q);
					break;

				case 1: //Ellipsoidal Interface Case
					q = x*x / 0.49 + y*y / 0.09;
					ps.setAll(q - d*mus[1] / mus[0] * r0, q);
					break;
				case 2: //Ellipsoidal Interface with variable alpha
					q = (x*x / A2 + y*y / B2) / 2.0;
					ps.setAll(q - d*mus[1] / mus[0] * r0, q);
					break;
				case 3:
					//the solutions with "Heart" shape interface with variable alpha
					q = x*x + y*y;
					q = (3.0*q - x)*(3.0*q - x) - q + 0.01;
					q = q / 2.0;
					ps.setAll(q - d*mus[1] / mus[0] * r0, q);
					break;
				case 4:
					//the solutions with "Peanut" shape interface with variable alpha
					q = x*x*x*x / 2.0 - x*x / 4.0 + y*y;
					q = q / 2.0;
					ps.setAll(q - d*mus[1] / mus[0] * r0, q);
					break;
				default:
					printf("\nThere is no such a interface,yet!!");
					break;
				}
				return 0;
			}
			double	P(FVector_double& p) {
				static FVector_double ps(2);
				P(p, ps);																	// 두 값을 호출해서 알맞게 돌려준다.
				if (Interface(p)<0.0)	return ps[0];
				return ps[1];
			}

			void	DP(FVector_double& p, FMatrix_double& dps) {
				double x = p[0], y = p[1];
				double d, dxP, dyP;
				static FVector_double mus(2), dq(dim);
				d = gap;
				coef_mu(p, mus);
				switch (nInterface){
				case 0: //Circular Interface Case
					dps.setAll(x, y, x, y);
					break;
				case 1: //Ellipsoidal Interface Case
					dps.setAll(2.0*x / 0.49, 2.0*y / 0.09, 2.0*x / 0.49, 2.0*y / 0.09);
					break;
				case 2: //Ellipsoidal Interface with variable alpha
					dps.setAll(x / A2, y / B2, x / A2, y / B2);
					break;
				case 3: //Heart Shaped Interface with variable alpha
					dxP = (3.0*(x*x + y*y) - x)*(6.0*x - 1.0) - x;
					dyP = (3.0*(x*x + y*y) - x)*6.0*y - y;
					dps.setAll(dxP, dyP, dxP, dyP);
					break;
				case 4: //Peanut Shaped Interface with variable alpha
					dxP = x*x*x - x / 4.0;
					dyP = y;
					dps.setAll(dxP, dyP, dxP, dyP);
					break;
				default:
					printf("\nThere is no such a interface,yet!!");
					break;
				}

			}

			void	DP(FVector_double& p, FVector_double& dp) {
				static FMatrix_double dps(2, 2);
				DP(p, dps);

				if (Interface(p)<0.0)	 dp = dps[0];
				else	dp = dps[1];
			}
			double	F(FVector_double& p, FVector_double& fs) {
				double x = p[0], y = p[1];
				double fx, fy, d;
				static FVector_double mus(2), dq(dim);
				d = gap;
				coef_mu(p, mus);
				switch (nInterface){
				case 0:
					fs.setAll(-2.0*mus[1], -2.0*mus[1]);
					break;
				case 1:
					fx = 1.0 / 0.49 + 1.0 / 0.09;
					fy = fx;
					fs.setAll(-2.0*mus[1] * fx, -2.0*mus[1] * fy);
					break;
				case 2: //Ellipsoidal Interface with Circular Type Solution
					fx = 1.0 / A2 + 1.0 / B2;
					fy = fx;
					fs.setAll(-1.0*mus[1] * fx, -1.0*mus[1] * fy);
					break;
				case 3: //Heart Shaped Interface case with variable alpha
					fx = (6.0*x - 1.0)*(6.0*x - 1.0) + (6.0*y)*(6.0*y) + 12.0*(3.0*(x*x + y*y) - x) - 2.0;
					fx = -1.0*mus[1] * fx;
					fy = fx;
					fs.setAll(fx, fy);
					break;
				case 4: //Peanut Shaped Interface case with variable alpha
					fx = -1.0*mus[1] * 3.0*(x*x + 1.0 / 4.0);
					fy = fx;
					fs.setAll(fx, fy);
					break;
				default:
					printf("\nThere is no such a interface,yet!!");
					break;
				}

				return 0;
			}
			double	F(FVector_double& p) {
				static FVector_double fs(2);
				F(p, fs);
				if (Interface(p)<0.0)	 return fs[0];
				else	return fs[1];
			}
		};
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		//============================================================================
		//                         ELLIPTIC_IIM_J12_SINCOS (J1: Jump    J2: Flux Jump)
		//============================================================================
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		class P_IIM_J12_SINCOS: public FEM_PROBLEM {
		public:
			void	initialize	(FEM_VARIABLES::ENTIRE& __) {
				r0 = 0.53;
				mum = mup = 1;

				__.dim = 2;
				__.RX.make(__.dim, __.dim).setAll(-1.,-1., 1.,1.);
			}
			double	Interface	(double r) {			// 내부에서 음수의 값을 가지도록 한다.
				return (r - r0);
			}

			double	Interface	(FVector_double& p) {
				double x=p[0], y=p[1];
				double r = sqrt(x*x + y*y);

				return (r - r0);
			}
			double	P			(FVector_double& p, FVector_double& ps) {
				double x = p[0], y = p[1];
				ps.setAll(sin(CV.PI*x), sin(2*CV.PI*x)*cos(CV.PI*y));
				return 0;
			}
			double	P			(FVector_double& p) {
				static FVector_double ps(2);
				P(p, ps);	// 두 값을 호출해서 알맞게 돌려준다.

				if(Interface(p) <= 0) {
					return ps[0];
				} else { 
					return ps[1];
				}
			}
			double	P_Jump		(FVector_double& p) {
				static FVector_double ps(2);
				P(p, ps);
				return (ps[0] - ps[1]);
			}
			void	DP			(FVector_double& p, FMatrix_double& dps) {
				double x = p[0], y = p[1];
				dps.setAll(
					CV.PI*cos(CV.PI*x),	0.,
					2*CV.PI*cos(2*CV.PI*x)*cos(CV.PI*y),		-CV.PI*sin(2*CV.PI*x)*sin(CV.PI*y)
				);
			}
			void	DP			(FVector_double& p, FVector_double& dp) {
				static FMatrix_double dps(2,2);
				DP(p, dps);

				if(Interface(p) <= 0) {
					dp = dps[0];
				} else {
					dp = dps[1];
				}
			}
			double	Flux_Jump	(FVector_double& p, FVector_double& vN) {
				static FMatrix_double dps(2,2);
				static FVector_double vIm(2);
				DP(p, dps);
				return ( vIm.op("=", mum, dps[0], -mup, dps[1]), vN );
			}
			double	F			(FVector_double& p, FVector_double& fs) {
				double x=p[0], y=p[1];
				fs.setAll(mum*(-$(CV.PI,2)*sin(CV.PI*x)), mup*5*$(CV.PI,2)*cos(CV.PI*y)*sin(2*CV.PI*x));
				return 0;
			}
			double	F			(FVector_double& p) {
				static FVector_double fs(2);
				F(p, fs);
				if(Interface(p) <= 0) {
					return fs[0];
				} else {
					return fs[1];
				}
			}
		};
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		//============================================================================
		//                         ELLIPTIC_IIM_BOTH_SINCOS_TWO_CIRCLE
		//============================================================================
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		/*class P_IIM_BOTH_ELEMENTARY_TWO_CIRCLE: public FEM_PROBLEM {
		public:
			void	initialize	(FEM_VARIABLES::ENTIRE& __) {
				r0 = 0.25;
				mum = mup = 1;

				__.dim = 2;
				__.RX.make(__.dim, __.dim).setAll(-1.,-1., 1.,1.);
			}
			double	Interface	(FVector_double& p) {
				double x=p[0], y=p[1];
				double r1 = sqrt((x+0.5)*(x+0.5) + y*y);
				double r2 = sqrt((x-0.5)*(x-0.5) + y*y);

				return (r1 - r0)*(r2 - r0);
			}
			double	P			(FVector_double& p, FVector_double& ps) {
				double x = p[0], y = p[1];
				ps.setAll(exp(1+x), $(x,3)*y);
				return 0;
			}
			double	P			(FVector_double& p) {
				double r = p.norm2();
				static FVector_double ps(2);
				P(p, ps);	// 두 값을 호출해서 알맞게 돌려준다.

				if(Interface(r) <= 0) {
					return ps[0];
				} else { 
					return ps[1];
				}
			}
			double	P_Jump		(FVector_double& p) {
				static FVector_double ps(2);
				P(p, ps);
				return (ps[0] - ps[1]);
			}
			void	DP			(FVector_double& p, FMatrix_double& dps) {
				double x = p[0], y = p[1];
				dps.setAll(
					exp(x+1), 0.,
					3*x*x*y, $(x,3)
				);
			}
			void	DP			(FVector_double& p, FVector_double& dp) {
				double r = p.norm2();
				static FMatrix_double dps(2,2);
				DP(p, dps);

				if(Interface(r) <= 0) {
					dp = dps[0];
				} else {
					dp = dps[1];
				}
			}
			double	Flux_Jump	(FVector_double& p, FVector_double& vN) {
				static FMatrix_double dps(2,2);
				static FVector_double vIm(2);
				DP(p, dps);
				return ( vIm.op("=", mum, dps[0], -mup, dps[1]) * vN );
			}
			double	F			(FVector_double& p, FVector_double& fs) {
				double x=p[0], y=p[1];
				fs.setAll(-exp(x+1), -6*x*y);
				return 0;
			}
			double	F			(FVector_double& p) {
				double r = p.norm2();
				static FVector_double fs(2);
				F(p, fs);
				if(Interface(r) <= 0) {
					return fs[0];
				} else {
					return fs[1];
				}
			}
		};*/
		class P_IM_TEST_PROBLEM : public FEM_PROBLEM {
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				//Input("mu in interior = ", mum);                           //interior mu
				//Input("mu in exterior = ", mup);                           //exterior mu
				//r0 = 0.48;                                                 //radius of circle
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);

				Input("\nView (x,y) direction", VAR.nData[0] >> VAR.nData[1]);

				printf("\n[0] Kink");
				printf("\n[1] Circle");
				printf("\n[2] Star Shape");
				printf("\n[3] Cardioid");
				printf("\n[4] Heart");
				printf("\n[5] Straight Line");
				printf("\n[6] Interface Edge");
				printf("\n[7] Kink Hou");
				printf("\n[100] Homogeneous");
				Input("\nChoose a Interface", nInterface);

				switch (nInterface) {
				case 1: //circle
					Input("Radious", r0);
					break;

				case 5:	// straight line
					vDirection.make(__.dim);													// 방향벡터의 왼쪽이 Omega^- 가 되도록 한다.
					vCenter.make(__.dim);														// 직선의 중심이 어디인지를 나타낸다.

					Input("center-x", vCenter[0]);
					Input("center-y", vCenter[1]);
					Input("x-direction", vDirection[0]);
					Input("y-direction", vDirection[1]);

					vDirection.normalize();
					MATH::rotate2D(vDirection, 0., 1., false);									// -90도 회전시킨다.
					break;

				case 6: // interface edge
					vOp.make(1);
					Input("perturbation: ", perturbed);
					break;

				case 7: // Kink Hou
					//__.RX.make(__.dim, __.dim).setAll(-1.,-1., 3.,1.);
					RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 3., 1.);

					Input("perturbation: ", perturbed);
					break;
				}

				printf("\n");
				printf("\n[1] test problem");
				printf("\n[2] -:6 x^2 + 7 y^2      +:Sin[3 x y] + Cos[5 x^2 y^2]       beta-:sin(x*y + 3)   beta+:cos(x*x - y*y + 2)");
				printf("\n[3] -:150xy + 30,         +:150xy");
				printf("\n[4] -:jump      +:0.  ");
				printf("\n[5] -:20*sin(x*x*y)      +:y*x*x    beta-:1     beta+:1");
				/*printf("\n[3] -:4-x*x-y*y,         +:x*x + y*y    beta-:r^2  beta+:constant");
				printf("\n[4] -:6 x^2 + 7 y^2      +:Sin[3 x y] + Cos[5 x^2 y^2]    beta-:r^2  beta+:constant");
				printf("\n[5] -:x*x + y*y + 2      +:1 - x*x - y*y    beta-:x*y + 3     beta+:x*x - y*y + 3");
				printf("\n[6] -:x*x + y*y + 2      +:1 - x*x - y*y    beta-:mum      beta+:x*x - y*y + x*y +3");
				printf("\n[7] -:sin(2*x*x + y*y + 2)/mum + x      +:cos(1 - x*x - y*y)/mup    beta-:mum      beta+:mup");
				printf("\n[8] -:pow(r*r, 5./6) + sin(x+y)   +:8         beta-:2 + sin(x + y)     beat+:1");
				printf("\n[9] -:const1/mus[0]				+:const2/mus[1]");
				printf("\n[10] -:sin(10xy)/mus[0]			+:cos(y)/mus[1]");
				printf("\n[11] -:x			+:0");
				printf("\n[[ Homogeneous Jumps ]]");
				printf("\n[100] -LevelSet/beta- +:*LevelSet/beta+");
				printf("\n[101] Zilin Lee -:r^3/mum    +:r^3/mup + (1/mum - 1/mup)r0^3");*/

				Input("\nChoose a Function", nFunction);
				switch (nFunction) {
				case 1: case 2: case 3:
					Input("mum", mum);
					Input("mup", mup);
					break;
				case 4:
					Input("mum", mum);
					Input("mup", mup);
					Input("jump", jump);
					break;
				default:
					mum = 1;
					mup = 1;
					/*case 3: case 4:
					Input("beta+", mup);
					break;

					case 6:
					Input("beta-", mum);
					break;

					case 9:
					//mum = mup = 1;
					Input("mum", mum);
					Input("mup", mup);
					vOp.make(2);
					Input("const1", vOp[0]);
					Input("const2", vOp[1]);
					break;*/
				}
			}
			double  Interface(FVector_double& p)
			{
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				double theta = MATH::slope_to_radian(x, y);

				switch (nInterface) {
				case 0:	// kink(left)
					if (y>0) return (y + 2 * x);
					else return (x - 2 * y);

				case 1: // circle
					return (x*x + y*y - r0*r0);

				case 2: // star shape
					return (r - 0.2*sin(5 * theta - CV.PI / 5) - 0.5);

				case 3: // cardioid
					return pow(3 * r*r - x, 2.) - r*r;

				case 4: // heart
					return pow(3 * r*r - x, 2.) - r*r + 0.01;

				case 5: // straight line
					return (vDirection, p - vCenter);

				case 6: // interface edge
					if (y >= 0) return (x + y + perturbed);
					else return (x + perturbed);

				case 7: // Kink Hou
					if (x + y>0) return (y - 2 * x + perturbed);
					else return (y + 0.5*x + perturbed);

				case 100: // homogeneous
					return sin(4 * (x*x - y*y));
					//case 5: // kink(upper)
					//	if(y>0
					//	return 
				}
				return 0;
			}
			void	derivative_interface(FVector_double& p, FVector_double& dp)
			{
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				double theta = MATH::slope_to_radian(x, y);

				switch (nInterface) {
					//case 0:	// kink(left)
					//	if(y>0) return (y+2*x);
					//	else return (x-2*y);

				case 1: // circle
					dp.setAll(2 * x, 2 * y);

					/*case 2: // star shape
					return (r - 0.2*sin(5*theta - CV.PI/5) - 0.5);

					case 3: // cardioid
					return pow(3*r*r - x, 2.) - r*r;

					case 4: // heart
					return pow(3*r*r - x, 2.) - r*r + 0.01;

					case 5: // straight line
					return (vDirection, p-vCenter);

					case 6: // interface edge
					if(y>=0) return (x+y+perturbed);
					else return (x+perturbed);

					case 7: // Kink Hou
					if(x+y>0) return (y-2*x+perturbed);
					else return (y+0.5*x+perturbed);

					case 100: // homogeneous
					return sin(4*(x*x-y*y));
					//case 5: // kink(upper)
					//	if(y>0
					//	return */
				}
			}
			void    double_derivative_interface(FVector_double& p, FMatrix_double& ddp)
			{
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				double theta = MATH::slope_to_radian(x, y);

				switch (nInterface) {
					//case 0:	// kink(left)
					//	if(y>0) return (y+2*x);
					//	else return (x-2*y);

				case 1: // circle
					ddp.setAll(2., 0., 0., 2.);

					/*case 2: // star shape
					return (r - 0.2*sin(5*theta - CV.PI/5) - 0.5);

					case 3: // cardioid
					return pow(3*r*r - x, 2.) - r*r;

					case 4: // heart
					return pow(3*r*r - x, 2.) - r*r + 0.01;

					case 5: // straight line
					return (vDirection, p-vCenter);

					case 6: // interface edge
					if(y>=0) return (x+y+perturbed);
					else return (x+perturbed);

					case 7: // Kink Hou
					if(x+y>0) return (y-2*x+perturbed);
					else return (y+0.5*x+perturbed);

					case 100: // homogeneous
					return sin(4*(x*x-y*y));
					//case 5: // kink(upper)
					//	if(y>0
					//	return */
				}
			}
			double	P(FVector_double& p, FVector_double& ps) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				static FVector_double mus(2);

				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				switch (nFunction) {
				case 1:		ps.setAll(mus[1] * Interface(p)*(1 + x)*(1 + y)*(1 - x)*(1 - y), mus[0] * Interface(p)*(1 + x)*(1 + y)*(1 - x)*(1 - y));		// (Interior, Exterior)
					break;

				case 2:		ps.setAll((6 * x*x + 7 * y*y), (sin(3 * x*y) + cos(5 * x*x*y*y)));
					break;

				case 3:		ps.setAll(150 * x*y + 30., 150 * x*y);
					//ps.setAll(150*x*y, 150*x*y);
					break;
				case 4:     ps.setAll(jump, 0.);
					break;
				case 5:		ps.setAll(20 * sin(x*x*y), y*x*x);
					break;
				default:
					ps.setAll(0., 0.);
				}
				return 0;
			}
			double	P(FVector_double& p) {
				static FVector_double ps(2);
				P(p, ps);																	// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) < 0) {
					return ps[0];
				}
				else {
					return ps[1];
				}
			}
			double	P_Jump(FVector_double& p)
			{
				FVector_double ps(2);
				P(p, ps);
				double x = p[0], y = p[1];
				double r2 = x*x + y*y;
				double r = sqrt(r2);
				FVector_double mus(2);
				double jump;
				jump = ps[0] - ps[1];
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.
				mus.release();
				ps.release();
				// 정확히 0이 나와야 하는 경우도(즉, 수학적으로 동일한 식도) 계산과정에서 round off error가 발생한다.
				// 따라서 직접적으로 계산해서 함수를 대입해주어야 한다.
				// -. 되도록이면 계산과정이 적도록
				// -. 위험도: 1.나눗셈 2.곱셈
				switch (nFunction) {
				case 1: case 2:
					return jump;
				default:
					return jump;
				}

			}
			void	DP(FVector_double& p, FMatrix_double& dps) {
				double x = p[0], y = p[1];
				double r2 = x*x + y*y;
				double r = sqrt(r2);
				static FVector_double mus(2);
				//static FVector_double vDLevelSet(2);	// derivative levelset
				FVector_double de_inter_func(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.
				derivative_interface(p, de_inter_func);
				switch (nFunction) {
				case 1:
					dps.setAll(mus[1] * (1 + x)*(1 + y)*(1 - x)*(1 - y)*de_inter_func[0] - mus[1] * Interface(p) * 2 * x*(1 + y)*(1 - y), mus[1] * (1 + x)*(1 + y)*(1 - x)*(1 - y)*de_inter_func[1] - mus[1] * 2 * y*(1 - x)*(1 + x)*Interface(p),
						mus[0] * (1 + x)*(1 + y)*(1 - x)*(1 - y)*de_inter_func[0] - mus[0] * Interface(p) * 2 * x*(1 + y)*(1 - y), mus[0] * (1 + x)*(1 + y)*(1 - x)*(1 - y)*de_inter_func[1] - mus[0] * 2 * y*(1 - x)*(1 + x)*Interface(p));
					de_inter_func.release();
					break;
				case 2:
					dps.setAll(12 * x, 14 * y,
						3 * y*cos(3 * x*y) - 10 * x*y*y*sin(5 * x*x*y*y), 3 * x*cos(3 * x*y) - 10 * x*x*y*sin(5 * x*x*y*y));
					/*dps.setAll(12*x*Interface(p)+(6*x*x+7*y*y)*de_inter_func[0],14*y*Interface(p)+(6*x*x+7*y*y)*de_inter_func[1],
					(3*y*cos(3*x*y)-10*x*y*y*sin(5*x*x*y*y))*Interface(p) + (sin(3*x*y)+cos(5*x*x*y*y))*de_inter_func[0], (3*x*cos(3*x*y)-10*x*x*y*sin(5*x*x*y*y))*Interface(p) + (sin(3*x*y)+cos(5*x*x*y*y))*de_inter_func[1]);*/
					de_inter_func.release();
					break;
				case 3:
					dps.setAll(150 * y, 150 * x,
						150 * y, 150 * x);
					break;
				case 4:
					dps.setAll(0., 0., 0., 0.);
					break;
				case 5:
					dps.setAll(40 * cos(x*x*y)*x*y, 20 * x*x*cos(x*x*y),
						2 * x*y, x*x);
					break;
				default:
					dps.setAll(0., 0., 0., 0.);
				}
			}
			void	DP(FVector_double& p, FVector_double& dp) {
				static FMatrix_double dps(2, 2);
				DP(p, dps);

				if (Interface(p) < 0) {
					dp = dps[0];
				}
				else {
					dp = dps[1];
				}
			}
			double	coef_mu(FVector_double& p, FVector_double& mus)
			{
				double x = p[0], y = p[1];
				switch (nFunction)
				{
				case 1: case 2: case 3: case 4:
					mus.setAll(mum, mup);														// (Interior, Exterior)
					break;
					/*case 2:
					mus.setAll(sin(x*y + 3), cos(x*x - y*y + 2));
					break;*/
				default:
					mus.setAll(1., 1.);
					break;
				}
				return 0;
			}
			double	coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.
				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.
				if (Interface(p) < 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}
			double	Flux_Jump(FVector_double& p, FVector_double& vN) {
				FMatrix_double dps(2, 2);
				FVector_double mus(2);
				double x = p[0], y = p[1];
				DP(p, dps);
				coef_mu(p, mus);
				double flux_jump;
				flux_jump = (mus[0] * dps[0] - mus[1] * dps[1], vN);
				//dps.print("dps");
				//dps[0].print("dps0");
				//dps[1].print("dps1");
				dps.release(); mus.release();
				switch (nFunction)
				{
				case 1: case 2: case 3: case 4:
					return flux_jump;
				default:
					return flux_jump;
				}
			}
			double	F(FVector_double& p, FVector_double& fs) {
				FVector_double mus(2);
				double x = p[0], y = p[1];
				FVector_double de_inter_func(2);
				FMatrix_double dd_inter_func(2, 2);
				coef_mu(p, mus);
				derivative_interface(p, de_inter_func);
				double_derivative_interface(p, dd_inter_func);
				switch (nFunction) {
				case 1:
					fs.setAll(mus[0] * mus[1] * ((1 + y)*(1 - y)*(6 * x*x - 2) + 2 * (1 + y)*(1 - y)*Interface(p) + 4 * x*x*(1 + y)*(1 - y) + (1 + x)*(1 - x)*(6 * y*y - 2) + 2 * (1 + x)*(1 - x)*Interface(p) + 4 * y*y*(1 + x)*(1 - x)),
						mus[0] * mus[1] * ((1 + y)*(1 - y)*(6 * x*x - 2) + 2 * (1 + y)*(1 - y)*Interface(p) + 4 * x*x*(1 + y)*(1 - y) + (1 + x)*(1 - x)*(6 * y*y - 2) + 2 * (1 + x)*(1 - x)*Interface(p) + 4 * y*y*(1 + x)*(1 - x)));
					de_inter_func.release();
					dd_inter_func.release();
					break;
				case 2:
					fs.setAll(-mus[0] * 26, mus[1] * ((9 * x*x + 9 * y*y)*sin(3 * x*y) + 100 * x*x*y*y*(x*x + y*y)*cos(5 * x*x*y*y) + 10 * sin(5 * x*x*y*y)*(x*x + y*y)));
					/*fs.setAll(-mus[0]*(12*Interface(p)+12*x*de_inter_func(0)+12*x*de_inter_func(0)+(6*x*x+7*y*y)*dd_inter_func(0,0)+14*Interface(p)+14*y*de_inter_func(1)+14*y*de_inter_func(1)+(6*x*x+7*y*y)*dd_inter_func(1,1)),
					-mus[1]*((-9*y*y*sin(3*x*y)-10*y*y*sin(5*x*x*y*y)-50*x*x*y*y*y*y*cos(5*x*x*y*y))*Interface(p)+(3*y*cos(3*x*y)-10*x*y*y*sin(5*x*x*y*y))*de_inter_func(0)+(3*y*cos(3*x*y)-5*x*y*y*sin(5*x*x*y*y))*de_inter_func[0]+(sin(3*x*y)+cos(5*x*x*y*y))*dd_inter_func(0,0)
					+(-9*x*x*sin(3*x*y)-10*x*x*sin(5*x*x*y*y)-50*x*x*x*x*y*y*cos(5*x*x*y*y))*Interface(p)+(3*x*cos(3*x*y)-10*x*x*y*sin(5*x*x*y*y))*de_inter_func(1)+(3*x*cos(3*x*y)-5*x*x*y*sin(5*x*x*y*y))*de_inter_func[1]+(sin(3*x*y)+cos(5*x*x*y*y))*dd_inter_func(1,1)));*/
					de_inter_func.release();
					dd_inter_func.release();
					break;
				case 3:
					fs.setAll(0., 0.);
					break;
				case 4:
					fs.setAll(0., 0.);
					break;
				case 5:
					fs.setAll(80 * sin(x*x*y)*x*x*y*y - 40 * cos(x*x*y)*y + 20 * sin(x*x*y)*x*x*x*x, -2 * y);
					break;
				default:
					fs.setAll(0., 0.);
				}
				return 0;
			}
			double	F(FVector_double& p) {
				static FVector_double fs(2);
				F(p, fs);
				if (Interface(p) < 0) {
					return fs[0];
				}
				else {
					return fs[1];
				}
			}
		};
		class P_IM_Zilin_Lee : public FEM_PROBLEM
		{
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				Input("mu in interior = ", mum);                           //interior mu
				Input("mu in exterior = ", mup);                           //exterior mu
				Input("radius of interface = ", r0);
				//r0 = 0.2;                                                 //radius of circle
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);
			}
			double CIRCLE(FVector_double& p) {                             //p가 interface 내부이면 -를 외부이면 +가 return 된다.
				double x = p[0], y = p[1];
				double r;
				r = sqrt(x*x + y*y);
				return r - r0;
			}
			double	coef_mu(FVector_double& p, FVector_double& mus)
			{
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}
			double	coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.
				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.
				if (Interface(p) < 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}
			double	P(FVector_double& p, FVector_double& ps) {
				double x = p[0], y = p[1];
				double r;
				r = sqrt(x*x + y*y);
				ps.setAll(r*r*r / mum, r*r*r / mup + (1 / mum - 1 / mup)*r0*r0*r0);
			}
			double	P(FVector_double& p) {
				double x = p[0], y = p[1];
				double r;
				r = sqrt(x*x + y*y);
				if (CIRCLE(p) < 0)
					return r*r*r / mum;
				else
					return r*r*r / mup + (1 / mum - 1 / mup)*r0*r0*r0;
			}
			void	DP(FVector_double& p, FMatrix_double& dps) {
				double x = p[0], y = p[1];
				double r;
				r = sqrt(x*x + y*y);
				dps.setAll(3 * x*r / mum, 3 * y*r / mum,
					3 * x*r / mup, 3 * y*r / mup);
			}
			void	DP(FVector_double& p, FVector_double& vDP) {
				double x = p[0], y = p[1];
				double r;
				r = sqrt(x*x + y*y);
				if (CIRCLE(p) < 0)
					vDP.setAll(3 * x*r / mum, 3 * y*r / mum);
				else
					vDP.setAll(3 * x*r / mup, 3 * y*r / mup);
			}
			double	F(FVector_double& p, FVector_double& fs) {
				double x = p[0], y = p[1];
				double r;
				r = sqrt(x*x + y*y);
				fs.setAll(-9 * r, -9 * r);
			}

			double	F(FVector_double& p) {
				double x = p[0], y = p[1];
				double r;
				r = sqrt(x*x + y*y);
				if (CIRCLE(p) < 0)
					return -9 * r;
				else
					return -9 * r;
			}
		};
	};
	class STOKES {
	public:
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		//============================================================================
		//                                STOKES_TUREK
		//============================================================================
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		// ## RHS F-vector ##	// kappa = indentity
		class P_TUREK: public FEM_PROBLEM {
		public:
			void	initialize	(FEM_VARIABLES::ENTIRE& __) {
				mu = 1;
				__.dim = 2;
				__.RX.make(__.dim, __.dim).setAll(0.,0., 1.,1.);
			}

			double	P	(FVector_double& p) {
				double x=p[0], y=p[1];
				return 150*(x-.5)*(y-.5);
			}

			void	DP	(FVector_double& p, FVector_double& dp) {	 
				double x=p[0], y=p[1];
				dp.setAll(y-0.5, x-0.5) *= 150;
			}

			void	V	(FVector_double& p, FVector_double& V) {
				double x = p[0], y = p[1];
				V[0] = -256*x*x*(x-1)*(x-1)*y*(y-1)*(2*y-1);
				V[1] = 256*y*y*(y-1)*(y-1)*x*(x-1)*(2*x-1);
			}

			void	DV	(FVector_double& p, FMatrix_double& dV) {
				double x = p[0], y = p[1];
				dV.setAll(
					512*(1-2*x)*(-1+x)*x*(-1+y)*y*(-1+2*y), -256*pow((-1+x)*x,2.)*(1-6*y+6*y*y),
					256*(1-6*x+6*x*x)*pow((-1+y)*y,2.), 512*(-1+x)*x*(-1+2*x)*(-1+y)*y*(-1+2*y)
				);
			}

			void	VF (FVector_double& p, FVector_double& vF) {
				double x=p[0], y=p[1];
				vF[0]=(2*y-1)*(75 -3072*x*x*x +1536*x*x*x*x -512*y -3072*x*y*(y-1) +512*y*y +1536*x*x*(1-2*y+2*y*y));
				vF[1]=(1-2*x)*(512*x*(x-1)*(1-6*y+6*y*y) +3*(-25 +512*y*y -1024*y*y*y +512*y*y*y*y));
			}
		};
		class P_TUREK2: public FEM_PROBLEM {
		public:
			
			void	initialize	(FEM_VARIABLES::ENTIRE& __) {
				mu = 1;
				__.dim = 2;
				__.RX.make(__.dim, __.dim).setAll(0.,0., 1.,1.);
			}

			double	P	(FVector_double& p) {
				double x=p[0], y=p[1];
				return 1.0/3*x*x*x-1.0/12;
			}


			void	DP	(FVector_double& p, FVector_double& dp) {	 
				double x=p[0], y=p[1];
				dp.setAll(x*x,0.0);
			}

			void	V	(FVector_double& p, FVector_double& V) {
				double PI	= 3.141592653589793238462;
				double x = p[0], y = p[1];
				V[0] = (1-cos(2*PI*x))*sin(2*PI*y);
				V[1] = -(1-cos(2*PI*y))*sin(2*PI*x);
			}

			void	DV	(FVector_double& p, FMatrix_double& dV) {
				double PI	= 3.141592653589793238462;
				double x = p[0], y = p[1];
				dV.setAll(2*PI*sin(2*PI*x)*sin(2*PI*y), 2*PI*(1-cos(2*PI*x))*cos(2*PI*y),
					-2*PI*(1-cos(2*PI*y))*cos(2*PI*x),-2*PI*sin(2*PI*y)*sin(2*PI*x));
			}

			void	VF (FVector_double& p, FVector_double& vF) {
				double PI	= 3.141592653589793238462;
				double x=p[0], y=p[1];
				vF[0]=-4*PI*PI*(2*cos(2*PI*x)-1)*sin(2*PI*y)+x*x;
				vF[1]=4*PI*PI*(2*cos(2*PI*y)-1)*sin(2*PI*x);
			}
		};
		class P_TUREK3: public FEM_PROBLEM {
		public:
			
			void	initialize	(FEM_VARIABLES::ENTIRE& __) {
				mu = 1;
				__.dim = 2;
				__.RX.make(__.dim, __.dim).setAll(0.,0., 1.,1.);
			}

			double	P	(FVector_double& p) {
				double x=p[0], y=p[1];
				return 0;
			}


			void	DP	(FVector_double& p, FVector_double& dp) {	 
				double x=p[0], y=p[1];
				dp.setAll(x*x,0.0);
			}

			void	V	(FVector_double& p, FVector_double& V) {
				double PI	= 3.141592653589793238462;
				double x = p[0], y = p[1];
				V[0] = (1-cos(2*PI*x))*sin(2*PI*y);
				V[1] = -(1-cos(2*PI*y))*sin(2*PI*x);
			}

			void	DV	(FVector_double& p, FMatrix_double& dV) {
				double PI	= 3.141592653589793238462;
				double x = p[0], y = p[1];
				dV.setAll(2*PI*sin(2*PI*x)*sin(2*PI*y), 2*PI*(1-cos(2*PI*x))*cos(2*PI*y),
					-2*PI*(1-cos(2*PI*y))*cos(2*PI*x),-2*PI*sin(2*PI*y)*sin(2*PI*x));
			}

			void	VF (FVector_double& p, FVector_double& vF) {
				double PI	= 3.141592653589793238462;
				double x=p[0], y=p[1];
				vF[0]=-4*PI*PI*(2*cos(2*PI*x)-1)*sin(2*PI*y);
				vF[1]=4*PI*PI*(2*cos(2*PI*y)-1)*sin(2*PI*x);
			}
		};



		class P_TEST: public FEM_PROBLEM {
		public:
			void	initialize	(FEM_VARIABLES::ENTIRE& __) {
				mu = 1;
				__.dim = 2;
				__.RX.make(__.dim, __.dim).setAll(0.,0., 1.,1.);
			}

			double	P	(FVector_double& p) {
				double x=p[0], y=p[1];
				return 0.;
			}

			void	DP	(FVector_double& p, FVector_double& dp) {	 
				double x=p[0], y=p[1];
				dp.setAll(0., 0.);
			}

			void	V	(FVector_double& p, FVector_double& V) {
				double x = p[0], y = p[1];
				V[0] = -256*x*x*(x-1)*(x-1)*y*(y-1)*(2*y-1);
				V[1] = 256*y*y*(y-1)*(y-1)*x*(x-1)*(2*x-1);
			}

			void	DV	(FVector_double& p, FMatrix_double& dV) {
				double x = p[0], y = p[1];
				dV.setAll(
					512*(1-2*x)*(-1+x)*x*(-1+y)*y*(-1+2*y), -256*pow((-1+x)*x,2.)*(1-6*y+6*y*y),
					256*(1-6*x+6*x*x)*pow((-1+y)*y,2.), 512*(-1+x)*x*(-1+2*x)*(-1+y)*y*(-1+2*y)
				);
			}

			void	VF (FVector_double& p, FVector_double& vF) {
				double x=p[0], y=p[1];
				vF[0]=512*(x*x*x*(6 - 12*y) + x*x*x*x*(-3 + 6*y) + y*(1 - 3*y + 2*y*y) - 6*x*y*(1 - 3*y + 2*y*y) + 3*x*x*(-1 + 4*y - 6*y*y + 4*y*y*y));
				vF[1]=-512*(-3*(y-1)*(y-1)*y*y - 3*x*x*(1 - 6*y + 6*y*y) + 2*x*x*x*(1 - 6*y + 6*y*y) + x*(1 - 6*y + 12*y*y - 12*y*y*y + 6*y*y*y*y));
			}
		};
		class P_SIMPLES: public FEM_PROBLEM {
		public:
			void	initialize	(FEM_VARIABLES::ENTIRE& __) {
				mu = 1;
				__.dim = 2;

				Input("Choose Function", nFunction);

				__.RX.make(__.dim, __.dim).setAll(-1.,-1., 1.,1.);
			}

			double	P	(FVector_double& p) {
				double x=p[0], y=p[1];

				switch(nFunction) {
					case -1:
						return 1;
					case 0:		
						return sin(x);
					case 1:
						return sin(x);
				}
				return 0;
			}

			void	DP	(FVector_double& p, FVector_double& dp) {	 
				double x=p[0], y=p[1];

				switch(nFunction) {
					case -1:
						dp.setAll(0., 0.);
						break;
					case 0:		
						dp.setAll(cos(x), 0.);
						break;
					case 1:
						dp.setAll(cos(x), 0.);
						break;
				}
				
			}

			void	V	(FVector_double& p, FVector_double& vV) {
				double x = p[0], y = p[1];

				switch(nFunction) {
					case -1:
						vV.setAll(1., 0.);
						break;
					case 0:
						vV[0] = exp(x)*sin(y);
						vV[1] = exp(x)*cos(y);
						break;
					case 1:
						vV.setAll(2*x*y, -y*y);
						break;
				}
			}

			void	DV	(FVector_double& p, FMatrix_double& dV) {
				double x = p[0], y = p[1];

				switch(nFunction) {
					case -1:
						dV.setAll(0., 0., 0., 0.);
						break;
					case 0:
						dV.setAll(exp(x)*sin(y), exp(x)*cos(y), exp(x)*cos(y), -exp(x)*sin(y));
						break;
					case 1:
						dV.setAll(2*y, 2*x, 0., -2*y);
						break;
				}
			}

			void	VF (FVector_double& p, FVector_double& vF) {
				double x=p[0], y=p[1];

				switch(nFunction) {
					case -1:
						vF.setAll(0., 0.);
						break;
					case 0:
						vF.setAll(cos(x), 0.);
						break;
					case 1:
						vF.setAll(cos(x)+1., -2.);
						break;
				}
			}
		};
		class P_IIM_TUREK: public FEM_PROBLEM {
		public:
			void	input			() {
				// Choosing Pressure
				//printf("\n[0] p-:sin(10x(y-2)),    p+:turek   <== wrong result");
				printf("\n[-1] p-:turek,  p+:turek");
				printf("\n[0] p-:100, p+:100");
				printf("\n[1] p-:turek+40,  p+:turek");
				printf("\n[2] p-:turek+40sin(10x(y-2)),    p+:turek");
				printf("\n[3] p-:turek,  p+:0");
				Input("\nChoose an interiror pressure", np);

				// Choosing Velocity
				printf("\n[0] u-:turek,    u+:turek");
				printf("\n[1] u-:turek,    u+:0");
				printf("\n[2] u-:turek+(x*x+y),     u+:turek");
				Input("\nChoose an interiror pressure", nv);

				Input("mum", mum);
				Input("mup", mup);
				
			//	r0 = CV.PI/6.28/2.;
				r0 = 0.236;
			}
			void	initialize		(FEM_VARIABLES::ENTIRE& __) {
				mu = 1;
				__.dim = 2;
				__.RX.make(__.dim, __.dim).setAll(0.,0., 1.,1.);
			}

			double	Interface		(double r) {												// 내부에서 음수의 값을 가지도록 한다.
				return (r - r0);
			}

			double	Interface		(FVector_double& p) {
				double x=p[0], y=p[1];
				double r = sqrt((x-0.5)*(x-0.5) + (y-0.5)*(y-0.5));
			//	r=-1000;
				return (r - r0);
			}

			double	coef_mu			(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}
			double	coef_mu			(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if(io == CV.IN) return mus[0];
				return mus[1];
			}
			double	coef_mu			(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if(Interface(p) <= 0) {
					return mus[0];
				} else { 
					return mus[1];
				}
			}
			double	P				(FVector_double& p, FVector_double& ps) {
				double x = p[0], y = p[1];

				switch(np) {
					//case 0:
					//	ps.setAll(40*sin(10*x*(y-2)), 150*(x-.5)*(y-.5));
					//	break;
					case -1:
						ps.setAll(150*(x-.5)*(y-.5), 150*(x-.5)*(y-.5));
						break;
					case 0:
						ps.setAll(1*(x-0.5), 1*(x-0.5));
						break;
					case 1:
						ps.setAll(150*(x-.5)*(y-.5)+40., 150*(x-.5)*(y-.5));
						break;
					case 2:
						ps.setAll(150*(x-.5)*(y-.5) + 40*sin(10*x*(y-2)), 150*(x-.5)*(y-.5));
						break;
					case 3:
						ps.setAll(150*(x-.5)*(y-.5), 10.);
						break;
				}
				return 0;
			}

			double	P				(FVector_double& p) {
				static FVector_double ps(2);
				P(p, ps);																	// 두 값을 호출해서 알맞게 돌려준다.

				if(Interface(p) <= 0) {
					return ps[0];
				} else { 
					return ps[1];
				}
			}

			double	P_Jump			(FVector_double& p) {
				static FVector_double ps(2);
				P(p, ps);
				return (ps[0] - ps[1]);
			}

			void	DP				(FVector_double& p, FMatrix_double& dps) {
				double x = p[0], y = p[1];
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				switch(np) {
					//case 0:		dps.setAll(400*(y-2)*cos(10*x*(y-2)), 400*x*cos(10*x*(y-2)),		(y-0.5)*150, (x-0.5)*150);
					//	break;
					case -1:	dps.setAll((y-0.5)*150, (x-0.5)*150,		(y-0.5)*150, (x-0.5)*150);
						break;
					case 0:		dps.setAll(100., 0., 100., 0.);
						break;
					case 1:		dps.setAll((y-0.5)*150, (x-0.5)*150,		(y-0.5)*150, (x-0.5)*150);
						break;
					case 2:		dps.setAll((y-0.5)*150 + 400*(y-2)*cos(10*x*(y-2)), (x-0.5)*150 + 400*x*cos(10*x*(y-2)),		(y-0.5)*150, (x-0.5)*150);
						break;
					case 3:		dps.setAll((y-0.5)*150, (x-0.5)*150,		0., 0.);
						break;
				}
			}

			void	DP				(FVector_double& p, FVector_double& dp) {
				static FMatrix_double dps(2,2);
				DP(p, dps);

				if(Interface(p) <= 0) {
					dp = dps[0];
				} else {
					dp = dps[1];
				}
			}

			double	P_Flux_Jump		(FVector_double& p, FVector_double& vN) {
				static FMatrix_double dps(2,2);
				DP(p, dps);

				return ( dps[0]-dps[1], vN );
			}

			void	V				(FVector_double& p, FMatrix_double& mVs) {
				double x=p[0], y=p[1];
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				switch(nv) {
					case 0:
						mVs.setAll(
							-256*x*x*(x-1)*(x-1)*y*(y-1)*(2*y-1),256*y*y*(y-1)*(y-1)*x*(x-1)*(2*x-1),
							-256*x*x*(x-1)*(x-1)*y*(y-1)*(2*y-1),256*y*y*(y-1)*(y-1)*x*(x-1)*(2*x-1)
						);
						break;
					case 1:
						mVs.setAll(
							-256*x*x*(x-1)*(x-1)*y*(y-1)*(2*y-1) + x*x*y, 256*y*y*(y-1)*(y-1)*x*(x-1)*(2*x-1) - x*y*y,
							-256*x*x*(x-1)*(x-1)*y*(y-1)*(2*y-1), 256*y*y*(y-1)*(y-1)*x*(x-1)*(2*x-1)
						);
						break;
				}
			}

			void	V				(FVector_double& p, FVector_double& vV) {
				static FMatrix_double mVs(2,2);
				V(p, mVs);

				if(Interface(p) <= 0) {
					vV = mVs[0];
				} else { 
					vV = mVs[1];
				}
			}

			void	DV				(FVector_double& p, FCube_double& cDVs) {
				double x = p[0], y = p[1];
				switch(nv) {
					case 0:
						cDVs.setAll(
							512*(1-2*x)*(-1+x)*x*(-1+y)*y*(-1+2*y), -256*pow((-1+x)*x,2.)*(1-6*y+6*y*y),
							256*(1-6*x+6*x*x)*pow((-1+y)*y,2.), 512*(-1+x)*x*(-1+2*x)*(-1+y)*y*(-1+2*y),
							512*(1-2*x)*(-1+x)*x*(-1+y)*y*(-1+2*y), -256*pow((-1+x)*x,2.)*(1-6*y+6*y*y),
							256*(1-6*x+6*x*x)*pow((-1+y)*y,2.), 512*(-1+x)*x*(-1+2*x)*(-1+y)*y*(-1+2*y)
						);
						break;
					case 1:
						cDVs.setAll(
							512*(1-2*x)*(-1+x)*x*(-1+y)*y*(-1+2*y) + 2*x*y, -256*pow((-1+x)*x,2.)*(1-6*y+6*y*y) + x*x,
							256*(1-6*x+6*x*x)*pow((-1+y)*y,2.) - y*y, 512*(-1+x)*x*(-1+2*x)*(-1+y)*y*(-1+2*y) - 2*x*y,
							512*(1-2*x)*(-1+x)*x*(-1+y)*y*(-1+2*y), -256*pow((-1+x)*x,2.)*(1-6*y+6*y*y),
							256*(1-6*x+6*x*x)*pow((-1+y)*y,2.), 512*(-1+x)*x*(-1+2*x)*(-1+y)*y*(-1+2*y)
						);
						break;
					case 2:
						cDVs.setAll(
							512*(1-2*x)*(-1+x)*x*(-1+y)*y*(-1+2*y), -256*pow((-1+x)*x,2.)*(1-6*y+6*y*y),
							256*(1-6*x+6*x*x)*pow((-1+y)*y,2.), 512*(-1+x)*x*(-1+2*x)*(-1+y)*y*(-1+2*y),
							0., 0.,
							0., 0.
						);
						break;
				}
			}
			void	DV				(FVector_double& vRealP, FMatrix_double& mDV) {
				static FCube_double cDVs(2,2,2);
				DV(vRealP, cDVs);

				if(Interface(vRealP) <= 0) {
					mDV = cDVs[0];
				} else { 
					mDV = cDVs[1];
				}
			}
			/*void	DDV				(FVector_double& vRealP, FCube4_double& c4DDVs) {
				double x = vRealP[0], y = vRealP[1];
				switch(nv) {
					case 0:
						c4DDVs.setAll(
							-512*(1 - 6*x + 6*x*x)*y*(1 - 3*y + 2*y*y),		-512*x*(1 - 3*x + 2*x*x)*(1 - 6*y + 6*y*y),
							-512*x*(1 - 3*x + 2*x*x)*(1 - 6*y + 6*y*y),		-1536*(x-1)*(x-1)*x*x*(-1 + 2*y),
							1536*(-1 + 2*x)*(y-1)*(y-1)*y*y,				512*(1 - 6*x + 6*x*x)*y*(1 - 3*y + 2*y*y),
							512*(1 - 6*x + 6*x*x)*y*(1 - 3*y + 2*y*y),		512*(-1 + x)*x*(-1 + 2*x)*(1 - 6*y + 6*y*y),
							-512*(1 - 6*x + 6*x*x)*y*(1 - 3*y + 2*y*y),		-512*x*(1 - 3*x + 2*x*x)*(1 - 6*y + 6*y*y),
							-512*x*(1 - 3*x + 2*x*x)*(1 - 6*y + 6*y*y),		-1536*(x-1)*(x-1)*x*x*(-1 + 2*y),
							1536*(-1 + 2*x)*(y-1)*(y-1)*y*y,				512*(1 - 6*x + 6*x*x)*y*(1 - 3*y + 2*y*y),
							512*(1 - 6*x + 6*x*x)*y*(1 - 3*y + 2*y*y),		512*(-1 + x)*x*(-1 + 2*x)*(1 - 6*y + 6*y*y)
						);
						break;
					case 1:
						cDVs.setAll(
							512*(1-2*x)*(-1+x)*x*(-1+y)*y*(-1+2*y) + 2*x*y, -256*pow((-1+x)*x,2.)*(1-6*y+6*y*y) + x*x,
							256*(1-6*x+6*x*x)*pow((-1+y)*y,2.) - y*y, 512*(-1+x)*x*(-1+2*x)*(-1+y)*y*(-1+2*y) - 2*x*y,
							512*(1-2*x)*(-1+x)*x*(-1+y)*y*(-1+2*y), -256*pow((-1+x)*x,2.)*(1-6*y+6*y*y),
							512 (1 - 6 x + 6 x^2) y (1 - 3 y + 2 y^2), 512*(-1+x)*x*(-1+2*x)*(-1+y)*y*(-1+2*y)
						);
						break;
					case 2:
						cDVs.setAll(
							512*(1-2*x)*(-1+x)*x*(-1+y)*y*(-1+2*y), -256*pow((-1+x)*x,2.)*(1-6*y+6*y*y),
							256*(1-6*x+6*x*x)*pow((-1+y)*y,2.), 512*(-1+x)*x*(-1+2*x)*(-1+y)*y*(-1+2*y),
							0., 0.,
							0., 0.
						);
						break;
						
				}
			}
			void	DDV				(FVector_double& vRealP, FCube_double& cDDV) {
				static FCube4_double c4DDVs(2,2,2,2);
				DDV(vRealP, c4DDVs);

				if(Interface(vRealP) <= 0) {
					cDDV = c4DDVs[0];
				} else { 
					cDDV = c4DDVs[1];
				}
			}*/
			void	V_Flux_Jump		(FVector_double& vRealP, FVector_double& vNormal, FVector_double& vFlux) {
				static FCube_double cDVs(2,2,2);
				DV(vRealP, cDVs);

				for(int i=0; i<2; i++) vFlux[i] = (cDVs[0][i] - cDVs[1][i], vNormal);
			}
			void	VF				(FVector_double& vRealP, FMatrix_double& mFs) {
				double x=vRealP[0], y=vRealP[1];
				static FVector_double mus(2);

				DP(vRealP, mFs);		// f = ∇p

				// f -= μ△U 
				coef_mu(vRealP, mus);
				switch(nv) { 
					case 0:
						mFs.op("-=", "list", 0, 0, 2, 2,
							mus[0]*-512*(x*x*x*(6 - 12*y) + x*x*x*x*(-3 + 6*y) + y*(1 - 3*y + 2*y*y) - 6*x*y*(1 - 3*y + 2*y*y) + 3*x*x*(-1 + 4*y - 6*y*y + 4*y*y*y)), 
							mus[0]*512*(-3*(y-1)*(y-1)*y*y - 3*x*x*(1 - 6*y + 6*y*y) + 2*x*x*x*(1 - 6*y + 6*y*y) + x*(1 - 6*y + 12*y*y - 12*y*y*y + 6*y*y*y*y)),
							mus[1]*-512*(x*x*x*(6 - 12*y) + x*x*x*x*(-3 + 6*y) + y*(1 - 3*y + 2*y*y) - 6*x*y*(1 - 3*y + 2*y*y) + 3*x*x*(-1 + 4*y - 6*y*y + 4*y*y*y)), 
							mus[1]*512*(-3*(y-1)*(y-1)*y*y - 3*x*x*(1 - 6*y + 6*y*y) + 2*x*x*x*(1 - 6*y + 6*y*y) + x*(1 - 6*y + 12*y*y - 12*y*y*y + 6*y*y*y*y)));
						break;
					case 1:
						mFs.op("-=", "list", 0, 0, 2, 2,
							mus[0]*-512*(x*x*x*(6 - 12*y) + x*x*x*x*(-3 + 6*y) + y*(1 - 3*y + 2*y*y) - 6*x*y*(1 - 3*y + 2*y*y) + 3*x*x*(-1 + 4*y - 6*y*y + 4*y*y*y)), 
							mus[0]*512*(-3*(y-1)*(y-1)*y*y - 3*x*x*(1 - 6*y + 6*y*y) + 2*x*x*x*(1 - 6*y + 6*y*y) + x*(1 - 6*y + 12*y*y - 12*y*y*y + 6*y*y*y*y)),
							0., 0.);
						break;
				}
				/*switch(np) {
					case 0:		
						mFs.setAll(0., 0., 
							(2*y-1)*(75 -3072*x*x*x +1536*x*x*x*x -512*y -3072*x*y*(y-1) +512*y*y +1536*x*x*(1-2*y+2*y*y)),
							(1-2*x)*(512*x*(x-1)*(1-6*y+6*y*y) +3*(-25 +512*y*y -1024*y*y*y +512*y*y*y*y))
						);
						break;
					case 1:
						mFs.setAll(
							(2*y-1)*(75 -3072*x*x*x +1536*x*x*x*x -512*y -3072*x*y*(y-1) +512*y*y +1536*x*x*(1-2*y+2*y*y)),
							(1-2*x)*(512*x*(x-1)*(1-6*y+6*y*y) +3*(-25 +512*y*y -1024*y*y*y +512*y*y*y*y)),
							(2*y-1)*(75 -3072*x*x*x +1536*x*x*x*x -512*y -3072*x*y*(y-1) +512*y*y +1536*x*x*(1-2*y+2*y*y)),
							(1-2*x)*(512*x*(x-1)*(1-6*y+6*y*y) +3*(-25 +512*y*y -1024*y*y*y +512*y*y*y*y))
						);
						break;
					case 2:
						mFs.setAll(
							(2*y-1)*(75 -3072*x*x*x +1536*x*x*x*x -512*y -3072*x*y*(y-1) +512*y*y +1536*x*x*(1-2*y+2*y*y)) + 400*(y-2)*cos(10*x*(y-2)),
							(1-2*x)*(512*x*(x-1)*(1-6*y+6*y*y) +3*(-25 +512*y*y -1024*y*y*y +512*y*y*y*y)) + 400*x*cos(10*x*(y-2)),
							(2*y-1)*(75 -3072*x*x*x +1536*x*x*x*x -512*y -3072*x*y*(y-1) +512*y*y +1536*x*x*(1-2*y+2*y*y)),
							(1-2*x)*(512*x*(x-1)*(1-6*y+6*y*y) +3*(-25 +512*y*y -1024*y*y*y +512*y*y*y*y))
						);
						break;
				}*/
				//static FCube4_double c4DDVs(2,2,2,2);
				//DDV(vRealP, c4DDVs);
				// 
				/*switch(nv) {
					case 2:
						break;
				}*/
				/*switch(np) {
					case 0:		
						mFs.setAll(0., 0., 
							(2*y-1)*(75 -3072*x*x*x +1536*x*x*x*x -512*y -3072*x*y*(y-1) +512*y*y +1536*x*x*(1-2*y+2*y*y)),
							(1-2*x)*(512*x*(x-1)*(1-6*y+6*y*y) +3*(-25 +512*y*y -1024*y*y*y +512*y*y*y*y))
						);
						break;
					case 1: 
						mFs.setAll(
							(2*y-1)*(75 -3072*x*x*x +1536*x*x*x*x -512*y -3072*x*y*(y-1) +512*y*y +1536*x*x*(1-2*y+2*y*y)),
							(1-2*x)*(512*x*(x-1)*(1-6*y+6*y*y) +3*(-25 +512*y*y -1024*y*y*y +512*y*y*y*y)),
							(2*y-1)*(75 -3072*x*x*x +1536*x*x*x*x -512*y -3072*x*y*(y-1) +512*y*y +1536*x*x*(1-2*y+2*y*y)),
							(1-2*x)*(512*x*(x-1)*(1-6*y+6*y*y) +3*(-25 +512*y*y -1024*y*y*y +512*y*y*y*y))
						);
						break;
					case 2:
						mFs.setAll(
							(2*y-1)*(75 -3072*x*x*x +1536*x*x*x*x -512*y -3072*x*y*(y-1) +512*y*y +1536*x*x*(1-2*y+2*y*y)) + 400*(y-2)*cos(10*x*(y-2)),
							(1-2*x)*(512*x*(x-1)*(1-6*y+6*y*y) +3*(-25 +512*y*y -1024*y*y*y +512*y*y*y*y)) + 400*x*cos(10*x*(y-2)),
							(2*y-1)*(75 -3072*x*x*x +1536*x*x*x*x -512*y -3072*x*y*(y-1) +512*y*y +1536*x*x*(1-2*y+2*y*y)),
							(1-2*x)*(512*x*(x-1)*(1-6*y+6*y*y) +3*(-25 +512*y*y -1024*y*y*y +512*y*y*y*y))
						);
						break;
					case 3: 
						mFs.setAll(
							(2*y-1)*(75 -3072*x*x*x +1536*x*x*x*x -512*y -3072*x*y*(y-1) +512*y*y +1536*x*x*(1-2*y+2*y*y)),
							(1-2*x)*(512*x*(x-1)*(1-6*y+6*y*y) +3*(-25 +512*y*y -1024*y*y*y +512*y*y*y*y)),
							0.,
							0.
						);
						break;
				}*/
			}

			void	VF				(FVector_double& p, FVector_double& vF) {
				static FMatrix_double vFs(2, 2);
				VF(p, vFs);
				if(Interface(p) <= 0) {
					vF = vFs[0];
				} else {
					vF = vFs[1];
				}
			}
			/*
			void	VF (FVector_double& p, FVector_double& vF) {
				double x=p[0], y=p[1];
				vF[0]=(2*y-1)*(75 -3072*x*x*x +1536*x*x*x*x -512*y -3072*x*y*(y-1) +512*y*y +1536*x*x*(1-2*y+2*y*y));
				vF[1]=(1-2*x)*(512*x*(x-1)*(1-6*y+6*y*y) +3*(-25 +512*y*y -1024*y*y*y +512*y*y*y*y));

				switch(np) {
					case 1:

						vF[0] += 0;
						vF[1] += 0;
						break;
				}
			}*/
		};
		class P_IIM_LINE: public FEM_PROBLEM {
		public:
			void	initialize	(FEM_VARIABLES::ENTIRE& __) {
				__.dim = 2;
				__.RX.make(__.dim, __.dim).setAll(-1.,-1., 1.,1.);
				
				vOp.make(3);

				Input("Choose Function", nFunction);
				switch(nFunction) {
					case 0: 
						Input("Choose pressure negative part constant", vOp[0]);
						break;

				}
				Input("mum", mum);
				Input("mup", mup);

				vDirection.make(__.dim);													// 방향벡터의 왼쪽이 Omega^- 가 되도록 한다.
				vCenter.make(__.dim);														// 직선의 중심이 어디인지를 나타낸다.

				Input("center-x", vCenter[0]);
				Input("center-y", vCenter[1]);
				Input("x-direction", vDirection[0]);
				Input("y-direction", vDirection[1]);

				vDirection.normalize();
				MATH::rotate2D(vDirection, 0., 1., false);									// -90도 회전시킨다.
			}

			double	Interface	(FVector_double& p) {
				//double x=p[0], y=p[1];
				//double r = sqrt(x*x + y*y);

				return (vDirection, p-vCenter);												// 내적값을 준다.
			}

			double	coef_mu		(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}
			double	coef_mu		(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if(io == CV.IN) return mus[0];
				return mus[1];
			}
			double	coef_mu		(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if(Interface(p) <= 0) {
					return mus[0];
				} else { 
					return mus[1];
				}
			}

			double	P			(FVector_double& p, FVector_double& ps) {
				double x = p[0], y = p[1];
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.
				
				switch(nFunction) {
					case -1:	ps.setAll(x*x, y*y);							
						break;
					case 0:		ps.setAll(vOp[0], 1.);															// (Interior, Exterior)
						break;
					case 1:		ps.setAll(x, 0.);
						break;
					case 2:		ps.setAll(x*x, x*x);
						break;
				}
				return 0;
			}

			double	P			(FVector_double& p) {
				static FVector_double ps(2);
				P(p, ps);																	// 두 값을 호출해서 알맞게 돌려준다.

				if(Interface(p) <= 0) {
					return ps[0];
				} else { 
					return ps[1];
				}
			}

			double	P_Jump		(FVector_double& p) {
				static FVector_double ps(2);
				P(p, ps);
				return (ps[0] - ps[1]);
			}

			void	DP			(FVector_double& p, FMatrix_double& dps) {
				double x = p[0], y = p[1];
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				switch(nFunction) {
					case -1:	dps.setAll(2*x, 0.,		0., 2*y);
						break;
					case 0:		dps.setAll(0., 0.,		0.,	0.);
						break;
					case 1:		dps.setAll(1., 0.,		0., 0.);
						break;
					case 2:		dps.setAll(2*x, 0.,		2*x, 0.);
						break;
				}
			}
			void	DP			(FVector_double& p, FVector_double& dp) {
				static FMatrix_double dps(2,2);
				DP(p, dps);

				if(Interface(p) <= 0) {
					dp = dps[0];
				} else {
					dp = dps[1];
				}
			}

			void	V			(FVector_double& p, FMatrix_double& Vs) {
				double x = p[0], y = p[1];
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				switch(nFunction) {
					case -1:
					case 0:
					case 1:
					case 2:
						Vs.setAll(x, -y, x, -y);
						break;
				}
			}

			void	V			(FVector_double& p, FVector_double& vV) {
				double x = p[0], y = p[1];
				static FMatrix_double mVs(2,2);
				V(p, mVs);

				if(Interface(p) <= 0) {
					vV = mVs[0];
				} else {
					vV = mVs[1];
				}
			}

			void	DV			(FVector_double& p, FCube_double& dVs) {
				double x = p[0], y = p[1];
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				switch(nFunction) {
					case -1:
					case 0:
					case 1:
					case 2:
						dVs.setAll(1., 0., 0., -1.,    1., 0., 0., -1.);
						break;
				}
			}

			void	DV			(FVector_double& p, FMatrix_double& dV) {
				double x = p[0], y = p[1];
				static FCube_double dVs(2,2,2);
				DV(p, dVs);

				if(Interface(p) <= 0) {
					dV = dVs[0];
				} else {
					dV = dVs[1];
				}
			}

			void	VF			(FVector_double& p, FMatrix_double& mFs) {
				static FVector_double mus(2);
				double x=p[0], y=p[1];

				coef_mu(p, mus);
				switch(nFunction) {
					case -1:	mFs.setAll(2*x, 0., 0., 2*y);
						break;
					case 0:		mFs.setAll(0., 0.);
						break;
					case 1:		mFs.setAll(1., 0.);
						break;
					case 2:		mFs.setAll(2*x, 0., 2*x, 0.);
						break;
				}
			}
			void	VF			(FVector_double& p, FVector_double& vF) {
				static FMatrix_double vFs(2, 2);
				VF(p, vFs);
				if(Interface(p) <= 0) {
					vF = vFs[0];
				} else {
					vF = vFs[1];
				}
			}
		};
		class P_IIM_CIRCLE_V_REFLECT_WITH_P_JUMP: public FEM_PROBLEM {
		public:
			void	input			() {
				Input("mum", mum);
				Input("mup", mup);
				Input("rO", r0);
			}
			void	initialize		(FEM_VARIABLES::ENTIRE& __) {
				mu = 1;
				__.dim = 2;
				__.RX.make(__.dim, __.dim).setAll(-1.,-1., 1.,1.);
				input();
			}

			double	Interface		(double r) {												// 내부에서 음수의 값을 가지도록 한다.
				return (r - r0);
			}

			double	Interface		(FVector_double& p) {
				double x=p[0], y=p[1];
				double r = sqrt(x*x + y*y);

				return (r - r0);
			}

			double	coef_mu			(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}
			double	coef_mu			(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if(io == CV.IN) return mus[0];
				return mus[1];
			}
			double	coef_mu			(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if(Interface(p) <= 0) {
					return mus[0];
				} else { 
					return mus[1];
				}
			}
			double	P				(FVector_double& p, FVector_double& ps) {
				double x = p[0], y = p[1];
				ps.setAll(150*x*y + 40*sin(x*(y-2)), 150*x*y);
				return 0;
			}

			double	P				(FVector_double& p) {
				static FVector_double ps(2);
				P(p, ps);																	// 두 값을 호출해서 알맞게 돌려준다.

				if(Interface(p) <= 0) {
					return ps[0];
				} else { 
					return ps[1];
				}
			}

			double	P_Jump			(FVector_double& p) {
				static FVector_double ps(2);
				P(p, ps);
				return (ps[0] - ps[1]);
			}

			void	DP				(FVector_double& p, FMatrix_double& dps) {
				double x = p[0], y = p[1];
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.
				dps.setAll(y*150 + 40*(y-2)*cos(x*(y-2)), x*150 + 40*x*cos(x*(y-2)),		y*150, x*150);
			}

			void	DP				(FVector_double& p, FVector_double& dp) {
				static FMatrix_double dps(2,2);
				DP(p, dps);

				if(Interface(p) <= 0) {
					dp = dps[0];
				} else {
					dp = dps[1];
				}
			}

			double	P_Flux_Jump		(FVector_double& p, FVector_double& vN) {
				static FMatrix_double dps(2,2);
				DP(p, dps);

				return ( dps[0]-dps[1], vN );
			}

			void	V				(FVector_double& p, FMatrix_double& mVs) {
				double x=p[0], y=p[1];
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.
				mus.setAll(mum, mup);														// (Interior, Exterior)
				mVs.setAll(
					1/mus[0]*(x*x+y*y-r0*r0)*2*y, -1/mus[0]*(x*x+y*y-r0*r0)*2*x,
					-1/mus[1]*(x*x+y*y-r0*r0)*2*y, 1/mus[1]*(x*x+y*y-r0*r0)*2*x
				);
			}

			void	V				(FVector_double& p, FVector_double& vV) {
				static FMatrix_double mVs(2,2);
				V(p, mVs);

				if(Interface(p) <= 0) {
					vV = mVs[0];
				} else { 
					vV = mVs[1];
				}
			}

			void	DV				(FVector_double& p, FCube_double& cDVs) {
				double x = p[0], y = p[1];
				static FVector_double mus(2);
				mus.setAll(mum, mup);														// (Interior, Exterior)
				
				cDVs.setAll( //  -1/mus[0]*(x*x+y*y-r0*r0)*2*x
					1/mus[0]*2*x*2*y, 1/mus[0]*((x*x+y*y-r0*r0)*2+ 2*y*2*y),
					-1/mus[0]*((x*x+y*y-r0*r0)*2 + 2*x*2*x), -1/mus[0]*2*y*2*x,
					-1/mus[1]*2*x*2*y, -1/mus[1]*((x*x+y*y-r0*r0)*2+ 2*y*2*y),
					1/mus[1]*((x*x+y*y-r0*r0)*2 + 2*x*2*x), 1/mus[1]*2*y*2*x
				);
			}
			void	DV				(FVector_double& vRealP, FMatrix_double& mDV) {
				static FCube_double cDVs(2,2,2);
				DV(vRealP, cDVs);

				if(Interface(vRealP) <= 0) {
					mDV = cDVs[0];
				} else { 
					mDV = cDVs[1];
				}
			}
			/*void	DDV				(FVector_double& vRealP, FCube4_double& c4DDVs) {
				double x = vRealP[0], y = vRealP[1];
				switch(nv) {
					case 0:
						c4DDVs.setAll(
							-512*(1 - 6*x + 6*x*x)*y*(1 - 3*y + 2*y*y),		-512*x*(1 - 3*x + 2*x*x)*(1 - 6*y + 6*y*y),
							-512*x*(1 - 3*x + 2*x*x)*(1 - 6*y + 6*y*y),		-1536*(x-1)*(x-1)*x*x*(-1 + 2*y),
							1536*(-1 + 2*x)*(y-1)*(y-1)*y*y,				512*(1 - 6*x + 6*x*x)*y*(1 - 3*y + 2*y*y),
							512*(1 - 6*x + 6*x*x)*y*(1 - 3*y + 2*y*y),		512*(-1 + x)*x*(-1 + 2*x)*(1 - 6*y + 6*y*y),
							-512*(1 - 6*x + 6*x*x)*y*(1 - 3*y + 2*y*y),		-512*x*(1 - 3*x + 2*x*x)*(1 - 6*y + 6*y*y),
							-512*x*(1 - 3*x + 2*x*x)*(1 - 6*y + 6*y*y),		-1536*(x-1)*(x-1)*x*x*(-1 + 2*y),
							1536*(-1 + 2*x)*(y-1)*(y-1)*y*y,				512*(1 - 6*x + 6*x*x)*y*(1 - 3*y + 2*y*y),
							512*(1 - 6*x + 6*x*x)*y*(1 - 3*y + 2*y*y),		512*(-1 + x)*x*(-1 + 2*x)*(1 - 6*y + 6*y*y)
						);
						break;
					case 1:
						cDVs.setAll(
							512*(1-2*x)*(-1+x)*x*(-1+y)*y*(-1+2*y) + 2*x*y, -256*pow((-1+x)*x,2.)*(1-6*y+6*y*y) + x*x,
							256*(1-6*x+6*x*x)*pow((-1+y)*y,2.) - y*y, 512*(-1+x)*x*(-1+2*x)*(-1+y)*y*(-1+2*y) - 2*x*y,
							512*(1-2*x)*(-1+x)*x*(-1+y)*y*(-1+2*y), -256*pow((-1+x)*x,2.)*(1-6*y+6*y*y),
							512 (1 - 6 x + 6 x^2) y (1 - 3 y + 2 y^2), 512*(-1+x)*x*(-1+2*x)*(-1+y)*y*(-1+2*y)
						);
						break;
					case 2:
						cDVs.setAll(
							512*(1-2*x)*(-1+x)*x*(-1+y)*y*(-1+2*y), -256*pow((-1+x)*x,2.)*(1-6*y+6*y*y),
							256*(1-6*x+6*x*x)*pow((-1+y)*y,2.), 512*(-1+x)*x*(-1+2*x)*(-1+y)*y*(-1+2*y),
							0., 0.,
							0., 0.
						);
						break;
						
				}
			}
			void	DDV				(FVector_double& vRealP, FCube_double& cDDV) {
				static FCube4_double c4DDVs(2,2,2,2);
				DDV(vRealP, c4DDVs);

				if(Interface(vRealP) <= 0) {
					cDDV = c4DDVs[0];
				} else { 
					cDDV = c4DDVs[1];
				}
			}*/
			void	V_Flux_Jump		(FVector_double& vRealP, FVector_double& vNormal, FVector_double& vFlux) {
				static FCube_double cDVs(2,2,2);
				DV(vRealP, cDVs);

				for(int i=0; i<2; i++) vFlux[i] = (cDVs[0][i] - cDVs[1][i], vNormal);
			}
			void	V_Flux_T_Jump		(FVector_double& vRealP, FVector_double& vNormal, FVector_double& vFlux) {
				static FVector_double mus(2);
				coef_mu(vRealP, mus);

				static FCube_double cDVs(2,2,2);
				static FMatrix_double mGradU(2,2);
				static FMatrix_double mGradU_T(2,2);
				static FMatrix_double mInFlux(2,2);
				static FMatrix_double mOutFlux(2,2);
				static FMatrix_double mFluxJump(2,2);
				DV(vRealP, cDVs);
				
				mGradU = cDVs[0];
				mGradU_T.transposeFrom(mGradU);
				mInFlux.op("=","kfm+kfm", 0.5, mGradU, 0.5, mGradU_T);

				mGradU = cDVs[1];
				mGradU_T.transposeFrom(mGradU);
				mOutFlux.op("=","kfm+kfm", 0.5, mGradU, 0.5, mGradU_T);

				mFluxJump.op("=", "kfm+kfm", mus[0], mInFlux, -mus[1], mOutFlux);

				vFlux.op("=", mFluxJump, vNormal);
				
			}
			void	VF				(FVector_double& vRealP, FMatrix_double& mFs) {
				double x=vRealP[0], y=vRealP[1];
				static FVector_double mus(2);

				DP(vRealP, mFs);		// f = ∇p

				// f -= μ△U 
				coef_mu(vRealP, mus);
				mFs.op("-=", "list", 0, 0, 2, 2,
					16*y, -16*x, -16*y, 16*x);
				/*switch(nv) { 
					case 0:
						mFs.op("-=", "list", 0, 0, 2, 2,
							mus[0]*-512*(x*x*x*(6 - 12*y) + x*x*x*x*(-3 + 6*y) + y*(1 - 3*y + 2*y*y) - 6*x*y*(1 - 3*y + 2*y*y) + 3*x*x*(-1 + 4*y - 6*y*y + 4*y*y*y)), 
							mus[0]*512*(-3*(y-1)*(y-1)*y*y - 3*x*x*(1 - 6*y + 6*y*y) + 2*x*x*x*(1 - 6*y + 6*y*y) + x*(1 - 6*y + 12*y*y - 12*y*y*y + 6*y*y*y*y)),
							mus[1]*-512*(x*x*x*(6 - 12*y) + x*x*x*x*(-3 + 6*y) + y*(1 - 3*y + 2*y*y) - 6*x*y*(1 - 3*y + 2*y*y) + 3*x*x*(-1 + 4*y - 6*y*y + 4*y*y*y)), 
							mus[1]*512*(-3*(y-1)*(y-1)*y*y - 3*x*x*(1 - 6*y + 6*y*y) + 2*x*x*x*(1 - 6*y + 6*y*y) + x*(1 - 6*y + 12*y*y - 12*y*y*y + 6*y*y*y*y)));
						break;
					case 1:
						mFs.op("-=", "list", 0, 0, 2, 2,
							mus[0]*-512*(x*x*x*(6 - 12*y) + x*x*x*x*(-3 + 6*y) + y*(1 - 3*y + 2*y*y) - 6*x*y*(1 - 3*y + 2*y*y) + 3*x*x*(-1 + 4*y - 6*y*y + 4*y*y*y)), 
							mus[0]*512*(-3*(y-1)*(y-1)*y*y - 3*x*x*(1 - 6*y + 6*y*y) + 2*x*x*x*(1 - 6*y + 6*y*y) + x*(1 - 6*y + 12*y*y - 12*y*y*y + 6*y*y*y*y)),
							0., 0.);
						break;
				}*/
				/*switch(np) {
					case 0:		
						mFs.setAll(0., 0., 
							(2*y-1)*(75 -3072*x*x*x +1536*x*x*x*x -512*y -3072*x*y*(y-1) +512*y*y +1536*x*x*(1-2*y+2*y*y)),
							(1-2*x)*(512*x*(x-1)*(1-6*y+6*y*y) +3*(-25 +512*y*y -1024*y*y*y +512*y*y*y*y))
						);
						break;
					case 1:
						mFs.setAll(
							(2*y-1)*(75 -3072*x*x*x +1536*x*x*x*x -512*y -3072*x*y*(y-1) +512*y*y +1536*x*x*(1-2*y+2*y*y)),
							(1-2*x)*(512*x*(x-1)*(1-6*y+6*y*y) +3*(-25 +512*y*y -1024*y*y*y +512*y*y*y*y)),
							(2*y-1)*(75 -3072*x*x*x +1536*x*x*x*x -512*y -3072*x*y*(y-1) +512*y*y +1536*x*x*(1-2*y+2*y*y)),
							(1-2*x)*(512*x*(x-1)*(1-6*y+6*y*y) +3*(-25 +512*y*y -1024*y*y*y +512*y*y*y*y))
						);
						break;
					case 2:
						mFs.setAll(
							(2*y-1)*(75 -3072*x*x*x +1536*x*x*x*x -512*y -3072*x*y*(y-1) +512*y*y +1536*x*x*(1-2*y+2*y*y)) + 400*(y-2)*cos(10*x*(y-2)),
							(1-2*x)*(512*x*(x-1)*(1-6*y+6*y*y) +3*(-25 +512*y*y -1024*y*y*y +512*y*y*y*y)) + 400*x*cos(10*x*(y-2)),
							(2*y-1)*(75 -3072*x*x*x +1536*x*x*x*x -512*y -3072*x*y*(y-1) +512*y*y +1536*x*x*(1-2*y+2*y*y)),
							(1-2*x)*(512*x*(x-1)*(1-6*y+6*y*y) +3*(-25 +512*y*y -1024*y*y*y +512*y*y*y*y))
						);
						break;
				}*/
				//static FCube4_double c4DDVs(2,2,2,2);
				//DDV(vRealP, c4DDVs);
				// 
				/*switch(nv) {
					case 2:
						break;
				}*/
				/*switch(np) {
					case 0:		
						mFs.setAll(0., 0., 
							(2*y-1)*(75 -3072*x*x*x +1536*x*x*x*x -512*y -3072*x*y*(y-1) +512*y*y +1536*x*x*(1-2*y+2*y*y)),
							(1-2*x)*(512*x*(x-1)*(1-6*y+6*y*y) +3*(-25 +512*y*y -1024*y*y*y +512*y*y*y*y))
						);
						break;
					case 1: 
						mFs.setAll(
							(2*y-1)*(75 -3072*x*x*x +1536*x*x*x*x -512*y -3072*x*y*(y-1) +512*y*y +1536*x*x*(1-2*y+2*y*y)),
							(1-2*x)*(512*x*(x-1)*(1-6*y+6*y*y) +3*(-25 +512*y*y -1024*y*y*y +512*y*y*y*y)),
							(2*y-1)*(75 -3072*x*x*x +1536*x*x*x*x -512*y -3072*x*y*(y-1) +512*y*y +1536*x*x*(1-2*y+2*y*y)),
							(1-2*x)*(512*x*(x-1)*(1-6*y+6*y*y) +3*(-25 +512*y*y -1024*y*y*y +512*y*y*y*y))
						);
						break;
					case 2:
						mFs.setAll(
							(2*y-1)*(75 -3072*x*x*x +1536*x*x*x*x -512*y -3072*x*y*(y-1) +512*y*y +1536*x*x*(1-2*y+2*y*y)) + 400*(y-2)*cos(10*x*(y-2)),
							(1-2*x)*(512*x*(x-1)*(1-6*y+6*y*y) +3*(-25 +512*y*y -1024*y*y*y +512*y*y*y*y)) + 400*x*cos(10*x*(y-2)),
							(2*y-1)*(75 -3072*x*x*x +1536*x*x*x*x -512*y -3072*x*y*(y-1) +512*y*y +1536*x*x*(1-2*y+2*y*y)),
							(1-2*x)*(512*x*(x-1)*(1-6*y+6*y*y) +3*(-25 +512*y*y -1024*y*y*y +512*y*y*y*y))
						);
						break;
					case 3: 
						mFs.setAll(
							(2*y-1)*(75 -3072*x*x*x +1536*x*x*x*x -512*y -3072*x*y*(y-1) +512*y*y +1536*x*x*(1-2*y+2*y*y)),
							(1-2*x)*(512*x*(x-1)*(1-6*y+6*y*y) +3*(-25 +512*y*y -1024*y*y*y +512*y*y*y*y)),
							0.,
							0.
						);
						break;
				}*/
			}

			void	VF				(FVector_double& p, FVector_double& vF) {
				static FMatrix_double vFs(2, 2);
				VF(p, vFs);
				if(Interface(p) <= 0) {
					vF = vFs[0];
				} else {
					vF = vFs[1];
				}
			}
			/*
			void	VF (FVector_double& p, FVector_double& vF) {
				double x=p[0], y=p[1];
				vF[0]=(2*y-1)*(75 -3072*x*x*x +1536*x*x*x*x -512*y -3072*x*y*(y-1) +512*y*y +1536*x*x*(1-2*y+2*y*y));
				vF[1]=(1-2*x)*(512*x*(x-1)*(1-6*y+6*y*y) +3*(-25 +512*y*y -1024*y*y*y +512*y*y*y*y));

				switch(np) {
					case 1:

						vF[0] += 0;
						vF[1] += 0;
						break;
				}
			}*/
		};
		class P_IIM_CIRCLE: public FEM_PROBLEM {
		public:
			void	input			() {

				mum=1000.;
				mup=1.;
				r0=0.435;
			//	Input("mum", mum);
			//	Input("mup", mup);
			//	Input("rO", r0);
			}
			void	initialize		(FEM_VARIABLES::ENTIRE& __) {
				mu = 1;
				__.dim = 2;
				__.RX.make(__.dim, __.dim).setAll(-1.,-1., 1.,1.);
				input();
			}

			double	Interface		(double r) {												// 내부에서 음수의 값을 가지도록 한다.
				return (r - r0);
			}

			double	Interface		(FVector_double& p) {
				double x=p[0], y=p[1];
				double r = sqrt(x*x + y*y);

				return (r - r0);
			}

			double	coef_mu			(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}
			double	coef_mu			(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if(io == CV.IN) return mus[0];
				return mus[1];
			}
			double	coef_mu			(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if(Interface(p) <= 0) {
					return mus[0];
				} else { 
					return mus[1];
				}
			}
			double	P				(FVector_double& p, FVector_double& ps) {
				double x = p[0], y = p[1];
				ps.setAll(100*x*y, 100*x*y);
				ps[0] =0;
				return 0;
			}

			double	P				(FVector_double& p) {
				static FVector_double ps(2);
				P(p, ps);																	// 두 값을 호출해서 알맞게 돌려준다.

				if(Interface(p) <= 0) {
					return ps[0];
				} else { 
					return ps[1];
				}
			}

			double	P_Jump			(FVector_double& p) {
				static FVector_double ps(2);
				P(p, ps);
				return (ps[0] - ps[1]);
			}

			void	DP				(FVector_double& p, FMatrix_double& dps) {
				double x = p[0], y = p[1];
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.
				dps.setAll( y*100, x*100 , y*100, x*100 );
			}

			void	DP				(FVector_double& p, FVector_double& dp) {
				static FMatrix_double dps(2,2);
				DP(p, dps);

				if(Interface(p) <= 0) {
					dp = dps[0];
				} else {
					dp = dps[1];
				}
			}

			double	P_Flux_Jump		(FVector_double& p, FVector_double& vN) {
				static FMatrix_double dps(2,2);
				DP(p, dps);

				return ( dps[0]-dps[1], vN );
			}

			void	V				(FVector_double& p, FMatrix_double& mVs) {
				double x=p[0], y=p[1];
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.
				mus.setAll(mum, mup);														// (Interior, Exterior)
				mVs.setAll(
					1/mus[0]*(x*x+y*y-r0*r0)*2*y, -1/mus[0]*(x*x+y*y-r0*r0)*2*x,
					1/mus[1]*(x*x+y*y-r0*r0)*2*y, -1/mus[1]*(x*x+y*y-r0*r0)*2*x
				);
			}

			void	V				(FVector_double& p, FVector_double& vV) {
				static FMatrix_double mVs(2,2);
				V(p, mVs);

				if(Interface(p) <= 0) {
					vV = mVs[0];
				} else { 
					vV = mVs[1];
				}
			}

			void	DV				(FVector_double& p, FCube_double& cDVs) {
				double x = p[0], y = p[1];
				static FVector_double mus(2);
				mus.setAll(mum, mup);														// (Interior, Exterior)
				
				cDVs.setAll( //  -1/mus[0]*(x*x+y*y-r0*r0)*2*x
					1/mus[0]*2*x*2*y, 1/mus[0]*((x*x+y*y-r0*r0)*2+ 2*y*2*y),
					-1/mus[0]*((x*x+y*y-r0*r0)*2 + 2*x*2*x), -1/mus[0]*2*y*2*x,
					1/mus[1]*2*x*2*y, 1/mus[1]*((x*x+y*y-r0*r0)*2+ 2*y*2*y),
					-1/mus[1]*((x*x+y*y-r0*r0)*2 + 2*x*2*x), -1/mus[1]*2*y*2*x
				);
			}
			void	DV				(FVector_double& vRealP, FMatrix_double& mDV) {
				static FCube_double cDVs(2,2,2);
				DV(vRealP, cDVs);

				if(Interface(vRealP) <= 0) {
					mDV = cDVs[0];
				} else { 
					mDV = cDVs[1];
				}
			}
			void	V_Flux_Jump		(FVector_double& vRealP, FVector_double& vNormal, FVector_double& vFlux) {
				static FCube_double cDVs(2,2,2);
				DV(vRealP, cDVs);

				for(int i=0; i<2; i++) vFlux[i] = (cDVs[0][i] - cDVs[1][i], vNormal);
			}
			void	V_Flux_T_Jump		(FVector_double& vRealP, FVector_double& vNormal, FVector_double& vFlux) {
				static FVector_double mus(2);
				coef_mu(vRealP, mus);

				static FCube_double cDVs(2,2,2);
				static FMatrix_double mGradU(2,2);
				static FMatrix_double mGradU_T(2,2);
				static FMatrix_double mInFlux(2,2);
				static FMatrix_double mOutFlux(2,2);
				static FMatrix_double mFluxJump(2,2);
				DV(vRealP, cDVs);
				
				mGradU = cDVs[0];
				mGradU_T.transposeFrom(mGradU);
				mInFlux.op("=","kfm+kfm", 0.5, mGradU, 0.5, mGradU_T);

				mGradU = cDVs[1];
				mGradU_T.transposeFrom(mGradU);
				mOutFlux.op("=","kfm+kfm", 0.5, mGradU, 0.5, mGradU_T);

				mFluxJump.op("=", "kfm+kfm", mus[0], mInFlux, -mus[1], mOutFlux);

				vFlux.op("=", mFluxJump, vNormal);
				
			}
			void	VF				(FVector_double& vRealP, FMatrix_double& mFs) {
				double x=vRealP[0], y=vRealP[1];
				static FVector_double mus(2);

				DP(vRealP, mFs);		// f = ∇p

				// f -= μ△U 
				coef_mu(vRealP, mus);
				mFs.op("-=", "list", 0, 0, 2, 2,
					16*y, -16*x, 16*y, -16*x);
				 
			}

			void	VF				(FVector_double& p, FVector_double& vF) {
				static FMatrix_double vFs(2, 2);
				VF(p, vFs);
				if(Interface(p) <= 0) {
					vF = vFs[0];
				} else {
					vF = vFs[1];
				}
			} 
		};
		class P_IIM_CIRCLE_GH: public FEM_PROBLEM {
		public:
			void	input			() {

				mum=10.;
				mup=1.;
				r0=0.435;

				alpha=5.;
			//	Input("mum", mum);
			//	Input("mup", mup);
			//	Input("rO", r0);
			}
			void	initialize		(FEM_VARIABLES::ENTIRE& __) {
				mu = 1;
				__.dim = 2;
				__.RX.make(__.dim, __.dim).setAll(-1.,-1., 1.,1.);
				input();
			}

			double	Interface		(double r) {												// 내부에서 음수의 값을 가지도록 한다.
				return (r - r0);
			}

			double	Interface		(FVector_double& p) {
				double x=p[0], y=p[1];
				double r = sqrt(x*x + y*y);

				return (r - r0);
			}

			double	coef_mu			(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}
			double	coef_mu			(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if(io == CV.IN) return mus[0];
				return mus[1];
			}
			double	coef_mu			(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if(Interface(p) <= 0) {
					return mus[0];
				} else { 
					return mus[1];
				}
			}
			double	P				(FVector_double& p, FVector_double& ps) {
				double x = p[0], y = p[1];
				double area_in=r0*r0*CV.PI;
				double area_out=4-area_in;
				
				ps.setAll(100*x*y, 100*x*y); 
				ps[0]=ps[0]+alpha*area_out;
				ps[1]=ps[1]-alpha*area_in;

				return 0;
			}

			double	P				(FVector_double& p) {
				static FVector_double ps(2);
				P(p, ps);																	// 두 값을 호출해서 알맞게 돌려준다.
				  
				if(Interface(p) <= 0) {
					return ps[0];
				} 
				else { 
					return ps[1];
				}
			}

			double	P_Jump			(FVector_double& p) {
				static FVector_double ps(2);
				P(p, ps);
				return (ps[0] - ps[1]);
			}

			void	DP				(FVector_double& p, FMatrix_double& dps) {
				double x = p[0], y = p[1];
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.
				dps.setAll( y*100, x*100 , y*100, x*100 );
			}

			void	DP				(FVector_double& p, FVector_double& dp) {
				static FMatrix_double dps(2,2);
				DP(p, dps);

				if(Interface(p) <= 0) {
					dp = dps[0];
				} else {
					dp = dps[1];
				}
			}

			double	P_Flux_Jump		(FVector_double& p, FVector_double& vN) {
				static FMatrix_double dps(2,2);
				DP(p, dps);

				return ( dps[0]-dps[1], vN );
			}

			void	V				(FVector_double& p, FMatrix_double& mVs) {
				double x=p[0], y=p[1];
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.
				mus.setAll(mum, mup);														// (Interior, Exterior)
				mVs.setAll(
					1/mus[0]*(x*x+y*y-r0*r0)*2*y, -1/mus[0]*(x*x+y*y-r0*r0)*2*x,
					1/mus[1]*(x*x+y*y-r0*r0)*2*y, -1/mus[1]*(x*x+y*y-r0*r0)*2*x
				);
			}

			void	V				(FVector_double& p, FVector_double& vV) {
				static FMatrix_double mVs(2,2);
				V(p, mVs);

				if(Interface(p) <= 0) {
					vV = mVs[0];
				} else { 
					vV = mVs[1];
				}
			}

			void	DV				(FVector_double& p, FCube_double& cDVs) {
				double x = p[0], y = p[1];
				static FVector_double mus(2);
				mus.setAll(mum, mup);														// (Interior, Exterior)
				
				cDVs.setAll( //  -1/mus[0]*(x*x+y*y-r0*r0)*2*x
					1/mus[0]*2*x*2*y, 1/mus[0]*((x*x+y*y-r0*r0)*2+ 2*y*2*y),
					-1/mus[0]*((x*x+y*y-r0*r0)*2 + 2*x*2*x), -1/mus[0]*2*y*2*x,
					1/mus[1]*2*x*2*y, 1/mus[1]*((x*x+y*y-r0*r0)*2+ 2*y*2*y),
					-1/mus[1]*((x*x+y*y-r0*r0)*2 + 2*x*2*x), -1/mus[1]*2*y*2*x
				);
			}
			void	DV				(FVector_double& vRealP, FMatrix_double& mDV) {
				static FCube_double cDVs(2,2,2);
				DV(vRealP, cDVs);

				if(Interface(vRealP) <= 0) {
					mDV = cDVs[0];
				} else { 
					mDV = cDVs[1];
				} 
			}
			void	V_Flux_Jump		(FVector_double& vRealP, FVector_double& vNormal, FVector_double& vFlux) {
				static FCube_double cDVs(2,2,2);
				DV(vRealP, cDVs);

				for(int i=0; i<2; i++) vFlux[i] = (cDVs[0][i] - cDVs[1][i], vNormal);
			}
			void	V_Flux_T_Jump		(FVector_double& vRealP, FVector_double& vNormal, FVector_double& vFlux) {
				static FVector_double mus(2);
				coef_mu(vRealP, mus);

				static FCube_double cDVs(2,2,2);
				static FMatrix_double mGradU(2,2);
				static FMatrix_double mGradU_T(2,2);
				static FMatrix_double mInFlux(2,2);
				static FMatrix_double mOutFlux(2,2);
				static FMatrix_double mFluxJump(2,2);
				DV(vRealP, cDVs);
				
				mGradU = cDVs[0];
				mGradU_T.transposeFrom(mGradU);
				mInFlux.op("=","kfm+kfm", 0.5, mGradU, 0.5, mGradU_T);

				mGradU = cDVs[1];
				mGradU_T.transposeFrom(mGradU);
				mOutFlux.op("=","kfm+kfm", 0.5, mGradU, 0.5, mGradU_T);

				mFluxJump.op("=", "kfm+kfm", mus[0], mInFlux, -mus[1], mOutFlux);

				vFlux.op("=", mFluxJump, vNormal);
				
			}
			void		V_STRESS_Jump	(FVector_double& p, FVector_double& vN, FVector_double& vFlux)	{
			
				double p_scalar;
				V_Flux_T_Jump	 (p, vN, vFlux); 
				p_scalar=_problem->P_Jump (p);
				vFlux.setAll(vFlux[0]- p_scalar*vN[0],vFlux[1]-p_scalar*vN[1]);  
			
			} 


			void	VF				(FVector_double& vRealP, FMatrix_double& mFs) {
				double x=vRealP[0], y=vRealP[1];
				static FVector_double mus(2);

				DP(vRealP, mFs);		// f = ∇p

				// f -= μ△U 
				coef_mu(vRealP, mus);
				mFs.op("-=", "list", 0, 0, 2, 2,
					16*y, -16*x, 16*y, -16*x);

			}

			void	VF				(FVector_double& p, FVector_double& vF) {
				static FMatrix_double vFs(2, 2);
				VF(p, vFs);
				if(Interface(p) <= 0) {
					vF = vFs[0];
				} else {
					vF = vFs[1];
				}
			} 
		};
		class P_IIM_DUMBBELL_WITH_P_JUMP_SINE : public FEM_PROBLEM {
		public:
			void	input() {
				Input("mum", mum);
				Input("mup", mup);
				Input("y_intercept", y_intercept);
			}
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				mu = 1;
				__.dim = 2;
				__.RX.make(__.dim, __.dim).setAll(-2., -2., 2., 2.);
				input();
			}

			double	Interface(double r) {												// 내부에서 음수의 값을 가지도록 한다.
				return (r - r0);
			}

			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);

				return 8 * x*x*x*x - 4 * x*x + 4 * y*y - y_intercept*y_intercept;
			}

			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}
			double	coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) <= 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}
			double	P(FVector_double& p, FVector_double& ps) {
				double x = p[0], y = p[1];
				//ps.setAll(150*x*y + 40*sin(x*(y-2)), 150*x*y);
				ps.setAll(150 * x*y, 150 * x*y);
				return 0;
			}

			double	P(FVector_double& p) {
				static FVector_double ps(2);
				P(p, ps);																	// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) <= 0) {
					return ps[0];
				}
				else {
					return ps[1];
				}
			}

			double	P_Jump(FVector_double& p) {
				static FVector_double ps(2);
				P(p, ps);
				return (ps[0] - ps[1]);
			}

			void	DP(FVector_double& p, FMatrix_double& dps) {
				double x = p[0], y = p[1];
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.
				//dps.setAll(y*150 + 40*(y-2)*cos(x*(y-2)), x*150 + 40*x*cos(x*(y-2)),		y*150, x*150);
				dps.setAll(150 * y, 150 * x, 150 * y, 150 * x);

			}

			void	DP(FVector_double& p, FVector_double& dp) {
				static FMatrix_double dps(2, 2);
				DP(p, dps);

				if (Interface(p) <= 0) {
					dp = dps[0];
				}
				else {
					dp = dps[1];
				}
			}

			double	P_Flux_Jump(FVector_double& p, FVector_double& vN) {
				static FMatrix_double dps(2, 2);
				DP(p, dps);

				return (dps[0] - dps[1], vN);
			}

			void	V(FVector_double& p, FMatrix_double& mVs) {
				double x = p[0], y = p[1];
				static FVector_double mus(2);
				double L, Lx, Ly;
				L = Interface(p);
				Lx = 32 * x*x*x - 8 * x;
				Ly = 8 * y;
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.
				mus.setAll(mum, mup);														// (Interior, Exterior)
				mVs.setAll(
					1 / mus[0] * L*Ly, -1 / mus[0] * L*Lx,
					-1 / mus[1] * L*Ly, 1 / mus[1] * L*Lx
					);
			}

			void	V(FVector_double& p, FVector_double& vV) {
				static FMatrix_double mVs(2, 2);
				V(p, mVs);

				if (Interface(p) <= 0) {
					vV = mVs[0];
				}
				else {
					vV = mVs[1];
				}
			}

			void	DV(FVector_double& p, FCube_double& cDVs) {
				double x = p[0], y = p[1];
				static FVector_double mus(2);
				mus.setAll(mum, mup);														// (Interior, Exterior)
				double L, Lx, Ly, Lxx, Lxy, Lyy;
				L = Interface(p);
				Lx = 32 * x*x*x - 8 * x;
				Ly = 8 * y;
				Lxx = 96 * x*x - 8;
				Lxy = 0.;
				Lyy = 8.;

				cDVs.setAll( //  -1/mus[0]*(x*x+y*y-r0*r0)*2*x
					1 / mus[0] * (Lx*Ly + L*Lxy), 1 / mus[0] * (Ly*Ly + L*Lyy),
					1 / mus[0] * (-Lx*Lx - L*Lxx), 1 / mus[0] * (-Ly*Lx - L*Lxy),
					-1 / mus[1] * (Lx*Ly + L*Lxy), -1 / mus[1] * (Ly*Ly + L*Lyy),
					-1 / mus[1] * (-Lx*Lx - L*Lxx), -1 / mus[1] * (-Ly*Lx - L*Lxy)
					);
			}
			void	DV(FVector_double& vRealP, FMatrix_double& mDV) {
				static FCube_double cDVs(2, 2, 2);
				DV(vRealP, cDVs);

				if (Interface(vRealP) <= 0) {
					mDV = cDVs[0];
				}
				else {
					mDV = cDVs[1];
				}
			}
			void	V_Flux_Jump(FVector_double& vRealP, FVector_double& vNormal, FVector_double& vFlux) {
				static FCube_double cDVs(2, 2, 2);
				DV(vRealP, cDVs);

				for (int i = 0; i<2; i++) vFlux[i] = (cDVs[0][i] - cDVs[1][i], vNormal);
			}
			void	V_Flux_mu_Jump(FVector_double& vRealP, FVector_double& vNormal, FVector_double& vFlux) {
				static FVector_double mus(2);
				mus.setAll(mum, mup);														// (Interior, Exterior)

				static FCube_double cDVs(2, 2, 2);
				DV(vRealP, cDVs);

				for (int i = 0; i<2; i++) {
					vFlux[i] = (mus[0] * cDVs[0][i] - mus[1] * cDVs[1][i], vNormal);
					vFlux[i] -= P_Jump(vRealP) * vNormal[i];
				}
			}
			void	V_Flux_T_Jump(FVector_double& vRealP, FVector_double& vNormal, FVector_double& vFlux) {
				static FVector_double mus(2);
				coef_mu(vRealP, mus);

				static FCube_double cDVs(2, 2, 2);
				static FMatrix_double mGradU(2, 2);
				static FMatrix_double mGradU_T(2, 2);
				static FMatrix_double mInFlux(2, 2);
				static FMatrix_double mOutFlux(2, 2);
				static FMatrix_double mFluxJump(2, 2);
				DV(vRealP, cDVs);

				mGradU = cDVs[0];
				mGradU_T.transposeFrom(mGradU);
				mInFlux.op("=", "kfm+kfm", 0.5, mGradU, 0.5, mGradU_T);

				mGradU = cDVs[1];
				mGradU_T.transposeFrom(mGradU);
				mOutFlux.op("=", "kfm+kfm", 0.5, mGradU, 0.5, mGradU_T);

				mFluxJump.op("=", "kfm+kfm", 2 * mus[0], mInFlux, -2 * mus[1], mOutFlux);

				vFlux.op("=", mFluxJump, vNormal);

				for (int i = 0; i<2; i++) {
					vFlux[i] -= P_Jump(vRealP) * vNormal[i];
				}

			}
			void	VF(FVector_double& vRealP, FMatrix_double& mFs) {
				double x = vRealP[0], y = vRealP[1];
				static FVector_double mus(2);
				double L, Lx, Ly, Lxx, Lxy, Lyy, Lxxx, Lxxy, Lxyy, Lyyy;
				L = Interface(vRealP);
				Lx = 32.*x*x*x - 8.*x;
				Ly = 8.*y;
				Lxx = 96.*x*x - 8.;
				Lxy = 0.;
				Lyy = 8.;
				Lxxy = 0.;
				Lxyy = 0.;
				Lxxx = 192.*x;
				Lyyy = 0.;

				DP(vRealP, mFs);		// f = ∇p

				// f -= μ△U 
				coef_mu(vRealP, mus);
				mFs.op("-=", "list", 0, 0, 2, 2,
					Lxx*Ly + 2.*Lx*Lxy + L*Lxxy + Lyy*Ly + 2.*Ly*Lyy + L*Lyyy,
					-(Lxx*Lx + 2.*Lx*Lxx + L*Lxxx + Lyy*Lx + 2.*Ly*Lxy + L*Lxyy),
					-(Lxx*Ly + 2.*Lx*Lxy + L*Lxxy + Lyy*Ly + 2.*Ly*Lyy + L*Lyyy),
					(Lxx*Lx + 2.*Lx*Lxx + L*Lxxx + Lyy*Lx + 2.*Ly*Lxy + L*Lxyy)
					);
			}

			void	VF(FVector_double& p, FVector_double& vF) {
				static FMatrix_double vFs(2, 2);
				VF(p, vFs);
				if (Interface(p) <= 0) {
					vF = vFs[0];
				}
				else {
					vF = vFs[1];
				}
			}
		};
	};
	class NAVIER_STOKES { //steady state
	public:
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		//============================================================================
		//                                NAVIER_STOKES
		//============================================================================
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		// ## RHS F-vector ##	// kappa = indentity
		
		class P_TUREK: public FEM_PROBLEM {
		public:
			void	initialize	(FEM_VARIABLES::ENTIRE& __) {
				mu = 1.;
				__.dim = 2;
				__.RX.make(__.dim, __.dim).setAll(0.,0., 1.,1.);
			}

			double	P	(FVector_double& p) {
				double x=p[0], y=p[1];
				return 150*(x-.5)*(y-.5);
			}

			void	DP	(FVector_double& p, FVector_double& dp) {	 
				double x=p[0], y=p[1];
				dp.setAll(y-0.5, x-0.5) *= 150;
			}

			void	V	(FVector_double& p, FVector_double& V) {
				double x = p[0], y = p[1];
				V[0] = -256*x*x*(x-1)*(x-1)*y*(y-1)*(2*y-1)/mu;
				V[1] = 256*y*y*(y-1)*(y-1)*x*(x-1)*(2*x-1)/mu;
			}

			void	DV	(FVector_double& p, FMatrix_double& dV) {
				double x = p[0], y = p[1];
				dV.setAll(
					512*(1-2*x)*(-1+x)*x*(-1+y)*y*(-1+2*y)/mu, -256*pow((-1+x)*x,2.)*(1-6*y+6*y*y)/mu,
					256*(1-6*x+6*x*x)*pow((-1+y)*y,2.)/mu, 512*(-1+x)*x*(-1+2*x)*(-1+y)*y*(-1+2*y)/mu
				);
			}

			void	VF (FVector_double& p, FVector_double& vF) {
				double x=p[0], y=p[1];
				
				double u=-256*x*x*(x-1)*(x-1)*y*(y-1)*(2*y-1)/mu;
				double v=256*y*y*(y-1)*(y-1)*x*(x-1)*(2*x-1)/mu;
				
				double ux=512*(1-2*x)*(-1+x)*x*(-1+y)*y*(-1+2*y)/mu;
				double uy=-256*pow((-1+x)*x,2.)*(1-6*y+6*y*y)/mu;
				double vx=256*(1-6*x+6*x*x)*pow((-1+y)*y,2.)/mu;
				double vy= 512*(-1+x)*x*(-1+2*x)*(-1+y)*y*(-1+2*y)/mu;
				
				vF[0]=(2*y-1)*(75 -3072*x*x*x +1536*x*x*x*x -512*y -3072*x*y*(y-1) +512*y*y +1536*x*x*(1-2*y+2*y*y));
				vF[0] +=u*ux+v*uy;
				vF[1]=(1-2*x)*(512*x*(x-1)*(1-6*y+6*y*y) +3*(-25 +512*y*y -1024*y*y*y +512*y*y*y*y));
				vF[1] +=u*vx+v*vy;
			}
		};
		class POISEUILLE_FLOW: public FEM_PROBLEM {
		public:
			void	initialize	(FEM_VARIABLES::ENTIRE& __) {
				mu = 1;
				__.dim = 2;
				__.RX.make(__.dim, __.dim).setAll(-1.,-1., 1.,1.);
			}

			double	P	(FVector_double& p) {
				double x=p[0], y=p[1];
				return -x;
			}

			void	DP	(FVector_double& p, FVector_double& dp) {	 
				double x=p[0], y=p[1];
				dp.setAll(0., 0.);
			}

			void	V	(FVector_double& p, FVector_double& V) {
				double x = p[0], y = p[1];
				V[0] = 1./2./mu*(1.-y*y);
				V[1] = 0;
			}

			void	DV	(FVector_double& p, FMatrix_double& dV) {
				double x = p[0], y = p[1];
				dV.setAll(
					0, -2.*y,
					0, 0);
			}

			void	VF (FVector_double& p, FVector_double& vF) {
				double x=p[0], y=p[1];
				vF[0]=0;
				vF[1]=0;
			}
		};
	};
	class MAXWELL {
	public:
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		//============================================================================
		//                                ID
		//============================================================================
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		class ID {
		public:
			enum {P_ELEMENTARY, P_IIM_KWAK};
		};
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		//============================================================================
		//                              MAXWELL_SIMPLE
		//============================================================================
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		class P_SIMPLE: public FEM_PROBLEM {	// curl(curl E) - k^2 E = f
		public:
			void	initialize	(FEM_VARIABLES::ENTIRE& __) {
				k = 1;
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1.,-1., 1.,1.);
			}

			void	V			(FVector_double& p, FVector_double& V) {
				double x = p[0], y = p[1];
				V[0] = (y+1)*(y-1);
				V[1] = (x+1)*(x-1);
			}

			double	curlV_2D	(FVector_double& p) {
				double x = p[0], y = p[1];
				return (2*x - 2*y);
			}

			void	curlcurl	(FVector_double& p, FVector_double& v) {
				double x=p[0], y=p[1];
				v.setAll(-2., -2.);
			}

			void	VF			(FVector_double& p, FVector_double& vF) {
				double x=p[0], y=p[1];
				static FVector_double U(2);

				curlcurl(p, vF);
				V(p, U);

				vF.op("-=", $(k,2), U);
			}
		};
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		//============================================================================
		//                              MAXWELL_SIMPLE_R
		//============================================================================
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		class P_SIMPLE_R: public FEM_PROBLEM {	// curl(curl E) - k^2 E = f
		public:
			void	initialize	(FEM_VARIABLES::ENTIRE& __) {
				k = 1;
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1.,-1., 1.,1.);
			}

			void	V			(FVector_double& p, FVector_double& V) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);

				V[0] = (y+1)*(y-1)*r*r;
				V[1] = (x+1)*(x-1)*r*r;
			}

			double	curlV_2D	(FVector_double& p) {
				double x = p[0], y = p[1];
				return (2*(x-y)*(-1 + 2*x*x + x*y + 2*y*y));
			}

			void	curlcurl	(FVector_double& p, FVector_double& v) {
				double x=p[0], y=p[1];
				v.setAll(-2*(-1 + x*x - 2*x*y + 6*y*y), -2*(-1 + 6*x*x - 2*x*y + y*y));
			}

			void	VF			(FVector_double& p, FVector_double& vF) {
				double x=p[0], y=p[1];
				static FVector_double U(2);

				curlcurl(p, vF);
				V(p, U);

				vF.op("-=", $(k,2), U);
			}
		};
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		//============================================================================
		//                             MAXWELL_COMPLICATED_R
		//============================================================================
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		class P_COMPLICATED_R: public FEM_PROBLEM {	// curl(curl E) + k^2 E = f
		public:
			void	initialize	(FEM_VARIABLES::ENTIRE& __) {
				k = 1;
				r0 = CV.PI / 6.28;

				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1.,-1., 1.,1.);
			}

			void	V			(FVector_double& p, FVector_double& v) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				
				v.setAll((x+1)*(x-1)*(y+1)*(y-1), (x+1)*(x-1)*(y+1)*(y-1)) *= (r*r);
			}

			double	curlV_2D	(FVector_double& p) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);

				//return (-2*(x-y)*(-1 + $(x,3)*y + 2*$(y,2) + x*$(y,3) - $(x,2)*(-2 + y*y)));
				return (-2*(x-y)*(-1 + x*y*(r*r - x*y) + 2*r*r));
			}
			
			void	curlcurl	(FVector_double& p, FVector_double& v) {
				double x=p[0], y=p[1];
				double r = sqrt(x*x + y*y);

				//v.setAll(-2*(4*x*y*(1-r*r) + (1-x*x)*(1-x*x-6*y*y)), 2*(4*x*y*(1-r*r) - (1-y*y)*(1-y*y-6*x*x)));
				v.setAll(
					-2*(1 + $(x,4) - 4*$(x,3)*y - 6*y*y - 4*x*y*(-1 + $(y,2)) + x*x*(-2 + 6*y*y)), 
					2*(4*$(x,3)*y - 6*x*x*(-1 + y*y) + 4*x*y*(-1 + y*y) - $((-1 + y*y),2))
				);
			}

			void	VF			(FVector_double& p, FVector_double& vF) {
				double x=p[0], y=p[1];
				double r = sqrt(x*x + y*y);
				static FVector_double U(2);

				curlcurl(p, vF);
				V(p, U);

				vF.op("-=", $(k,2), U);
			}
		};
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		//============================================================================
		//                               MAXWELL_KWAK
		//============================================================================
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		class P_KWAK: public FEM_PROBLEM {	// curl(curl E) + k^2 E = f
		public:
			void	initialize	(FEM_VARIABLES::ENTIRE& __) {
				k = 1;
				r0 = CV.PI / 6.28;

				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1.,-1., 1.,1.);
			}

			void	V			(FVector_double& p, FVector_double& v) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				
				v.setAll((x+1)*(x-1)*(y+1)*(y-1), (x+1)*(x-1)*(y+1)*(y-1));
			}

			double	curlV_2D	(FVector_double& p) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);

				return (-2*(x - y + x*x*y - x*y*y));
			}
			
			void	curlcurl	(FVector_double& p, FVector_double& v) {
				double x=p[0], y=p[1];
				double r = sqrt(x*x + y*y);

				v.setAll(2 - 2*x*x + 4*x*y, 2 + 4*x*y - 2*y*y);
			}

			void	VF			(FVector_double& p, FVector_double& vF) {
				double x=p[0], y=p[1];
				double r = sqrt(x*x + y*y);
				static FVector_double U(2);

				curlcurl(p, vF);
				V(p, U);

				vF.op("-=", $(k,2), U);
			}
		};
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		//============================================================================
		//                              MAXWELL_ELEMENTARY
		//============================================================================
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		class P_ELEMENTARY: public FEM_PROBLEM {	// curl(curl E) - k^2 E = f
		public:
			void	initialize	(FEM_VARIABLES::ENTIRE& __) {
				k = 1;
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(0.,0., 1.,1.);
			}

			void	V			(FVector_double& p, FVector_double& V) {
				double x = p[0], y = p[1];
				V[0] = (1-y)*y*sin(y);
				V[1] = (1-x)*x*sin(x);
			}

			double	curlV_2D	(FVector_double& p) {
				double x = p[0], y = p[1];
				return ((1-x)*x*cos(x) + (y-1)*y*cos(y) + (1-2*x)*sin(x) - (1-2*y)*sin(y));
			}

			void	VF			(FVector_double& p, FVector_double& vF) {
				double x=p[0], y=p[1];
				vF[0] = (-2 + 4*y)*cos(y) + ( 2 + (1 - k*k)*y + (k*k - 1)*y*y )*sin(y);
				vF[1] = (-2 + 4*x)*cos(x) + ( 2 + (1 - k*k)*x + (k*k - 1)*x*x )*sin(x);
			}
		};
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		//============================================================================
		//                              MAXWELL_ELEMENTARY2
		//============================================================================
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		class P_ELEMENTARY2: public FEM_PROBLEM {	// curl(curl E) - k^2 E = f
		public:
			void	initialize	(FEM_VARIABLES::ENTIRE& __) {
				k = 1;
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(0.,0., 1.,1.);
			}

			void	V			(FVector_double& p, FVector_double& V) {
				double x = p[0], y = p[1];
				V[0] = (1-y)*y*exp(x+2*y);
				V[1] = (1-x)*x*(y+2*x);
			}

			double	curlV_2D	(FVector_double& p) {
				double x = p[0], y = p[1];
				return (-6*x*x - 2*x*(-2+y) + y + exp(x+2*y)*(-1 + 2*y*y));
			}

			void	curlcurl	(FVector_double& p, FVector_double& v) {
				double x=p[0], y=p[1];
				v.setAll(1 - 2*x + exp(x+2*y)*(-2 + 4*y + 4*y*y), 2*(-2 + 6*x + y) + exp(x + 2*y)*(1 - 2*y*y));
			}

			void	VF			(FVector_double& p, FVector_double& vF) {
				double x=p[0], y=p[1];
				static FVector_double U(2);

				curlcurl(p, vF);
				V(p, U);

				vF.op("-=", $(k,2), U);
			}
		};
		class P_ELEMENTARY3 : public FEM_PROBLEM {	// curl(curl E) - k^2 E = f
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				k = 1;
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(0., 0., 1., 1.);
			}

			void	V(FVector_double& p, FVector_double& V) {
				double x = p[0], y = p[1];
				V[0] = (1 - x)*x*sin(x);
				V[1] = (1 - y)*y*sin(y);
			}

			double	div_2D(FVector_double& p) {
				double x = p[0], y = p[1];
				return ((2 * x - 1)*sin(x) + (x*x - x)*cos(x) + (2 * y - 1)*sin(y) + (y*y - y)*cos(y));
			}

			void	VF(FVector_double& p, FVector_double& vF) {
				double x = p[0], y = p[1];
				vF[0] = -(-2 + x*x - x)*sin(x) + (4 * x - 2)*cos(x) + (1 - x)*x*sin(x);
				vF[1] = -(-2 + y*y - y)*sin(y) + (4 * y - 2)*cos(y) + (1 - y)*y*sin(y);
			}
		};
		class P_ELEMENTARY4 : public FEM_PROBLEM {	// curl(curl E) - k^2 E = f
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				k = 1;
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(0., 0., 1., 1.);
			}

			void	V(FVector_double& p, FVector_double& V) {
				double x = p[0], y = p[1];
				V[0] = (1 - x)*x*(1 - y)*y;
				V[1] = (1 - y)*y*(1 - x)*x;
			}

			double	div_2D(FVector_double& p) {
				double x = p[0], y = p[1];
				return ((2 * x - 1)*sin(x) + (x*x - x)*cos(x) + (2 * y - 1)*sin(y) + (y*y - y)*cos(y));
			}

			void	VF(FVector_double& p, FVector_double& vF) {
				double x = p[0], y = p[1];
				vF[0] = -(-2 + x*x - x)*sin(x) + (4 * x - 2)*cos(x) + (1 - x)*x*sin(x);
				vF[1] = -(-2 + y*y - y)*sin(y) + (4 * y - 2)*cos(y) + (1 - y)*y*sin(y);
			}
		};
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		//============================================================================
		//                              MAXWELL_SIM1
		//============================================================================
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		class P_SIM1: public FEM_PROBLEM {	// curl(curl E) - k^2 E = f
		public:
			void	initialize	(FEM_VARIABLES::ENTIRE& __) {
				k = 1;
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1.,-1., 1.,1.);
			}

			void	V			(FVector_double& p, FVector_double& V) {
				double x = p[0], y = p[1];
				V[0] = 1-y*y;
				V[1] = 1-x*x;
			}

			double	curlV_2D	(FVector_double& p) {
				double x = p[0], y = p[1];
				return (-2*x + 2*y);
			}

			void	curlcurl	(FVector_double& p, FVector_double& v) {
				double x=p[0], y=p[1];
				v.setAll(2., 2.);
			}

			void	VF			(FVector_double& p, FVector_double& vF) {
				double x=p[0], y=p[1];
				static FVector_double U(2);

				curlcurl(p, vF);
				V(p, U);

				vF.op("-=", $(k,2), U);
			}
		};
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		//============================================================================
		//                              MAXWELL_SIM2
		//============================================================================
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		class P_SIM2: public FEM_PROBLEM {	// curl(curl E) - k^2 E = f
		public:
			void	initialize	(FEM_VARIABLES::ENTIRE& __) {
				k = 1;
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1.,-1., 1.,1.);
			}

			void	V			(FVector_double& p, FVector_double& V) {
				double x = p[0], y = p[1];
				V[0] = cos(CV.PI*x)*sin(CV.PI*y);
				V[1] = -sin(CV.PI*x)*cos(CV.PI*y);
			}

			double	curlV_2D	(FVector_double& p) {
				double x = p[0], y = p[1];
				return (-2*CV.PI*cos(CV.PI*x)*cos(CV.PI*y));
			}

			void	curlcurl	(FVector_double& p, FVector_double& v) {
				double x=p[0], y=p[1];
				v.setAll(cos(CV.PI*x)*sin(CV.PI*y), -sin(CV.PI*x)*cos(CV.PI*y)) *= (2*$(CV.PI,2));
			}

			void	VF			(FVector_double& p, FVector_double& vF) {
				double x=p[0], y=p[1];
				static FVector_double U(2);

				curlcurl(p, vF);
				V(p, U);

				vF.op("-=", $(k,2), U);
			}
		};
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		//============================================================================
		//                            MAXWELL_ELEMENTARY_X
		//============================================================================
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		class P_SIM3 : public FEM_PROBLEM {	// curl(curl E) + k^2 E = f
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				k = 1.;
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);
			}

			void	V(FVector_double& p, FVector_double& V) {
				double x = p[0], y = p[1];
				V[0] = 1 - y*y;
				V[1] = 1 - x*x;
			}

			double	curlV_2D(FVector_double& p) {
				double x = p[0], y = p[1];
				return (-2 * x + 2 * y);
			}

			void	curlcurl(FVector_double& p, FVector_double& v) {
				double x = p[0], y = p[1];
				v.setAll(2., 2.);
			}

			void	VF(FVector_double& p, FVector_double& vF) {
				double x = p[0], y = p[1];
				/*static FVector_double U(2);

				curlcurl(p, vF);
				V(p, U);

				vF.op("-=", $(k,2), U);*/
				vF[0] = 2. + k*k*(1. - y*y);
				vF[1] = 2. + k*k*(1. - x*x);
			}
		};
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		//============================================================================
		//                              MAXWELL_ZERO
		//============================================================================
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		class P_ZERO : public FEM_PROBLEM {	// curl(curl E) + k^2 E = f
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				k = 1.;
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(0., 0., 1., 1.);
			}

			void	V(FVector_double& p, FVector_double& V) {
				double x = p[0], y = p[1];
				V[0] = 0.;
				V[1] = 0.;
			}

			double	curlV_2D(FVector_double& p) {
				double x = p[0], y = p[1];
				return 0.;
			}

			void	curlcurl(FVector_double& p, FVector_double& v) {
				double x = p[0], y = p[1];
				v.setAll(0., 0.);
			}

			void	VF(FVector_double& p, FVector_double& vF) {
				double x = p[0], y = p[1];
				vF[0] = 0.;
				vF[1] = 0.;
			}
		};
		class P_TEST : public FEM_PROBLEM {	// curl(curl E) + E = f
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);
			}

			void	V(FVector_double& p, FVector_double& V) {
				double x = p[0], y = p[1];
				V[0] = 1 - y*y;
				V[1] = 1 - x*x;
			}

			double	curlV_2D(FVector_double& p) {
				double x = p[0], y = p[1];
				return (-2 * x + 2 * y);
			}

			void	curlcurl(FVector_double& p, FVector_double& v) {
				double x = p[0], y = p[1];
				v.setAll(2., 2.);
			}

			void	VF(FVector_double& p, FVector_double& vF) {
				double x = p[0], y = p[1];
				/*static FVector_double U(2);

				curlcurl(p, vF);
				V(p, U);

				vF.op("-=", $(k,2), U);*/
				vF[0] = 3. - y*y;
				vF[1] = 3. - x*x;
			}
		};
		class P_Eigen : public FEM_PROBLEM { //-div(▽u) = lambda u
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(0., 0., CV.PI, CV.PI);
				//RX = __.RX.make(__.dim, __.dim).setAll(-CV.PI,-CV.PI, CV.PI,CV.PI);
			}
			void	coef_mMu(FVector_double& p, FMatrix_double& mMu) {
				double x = p[0], y = p[1];
				mMu.setAll(1., 0., 0., 1.);
			}

			double	P(FVector_double& p) {
				double x = p[0], y = p[1];
				return sin(x)*sin(y);
			}
		};
		class P_X: public FEM_PROBLEM {	// curl(curl E) - k^2 E = f
		public:
			void	initialize	(FEM_VARIABLES::ENTIRE& __) {
				k = 1;
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(0.,0., 1.,1.);
			}

			void	V			(FVector_double& p, FVector_double& V) {
				double x = p[0], y = p[1];
				V[0] = 0;
				V[1] = x;
			}

			double	curlV_2D	(FVector_double& p) {
				double x = p[0], y = p[1];
				return (1);
			}

			void	VF			(FVector_double& p, FVector_double& vF) {
				double x=p[0], y=p[1];
				vF[0] = 0;
				vF[1] = -k*k*x;
			}
		};
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		//============================================================================
		//                           MAXWELL_ELEMENTARY_1_1
		//============================================================================
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		class P_1_1: public FEM_PROBLEM {	// curl(curl E) - k^2 E = f
		public:
			void	initialize	(FEM_VARIABLES::ENTIRE& __) {
				k = 1;
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(0.,0., 1.,1.);
			}

			void	V			(FVector_double& p, FVector_double& V) {
				double x = p[0], y = p[1];
				V[0] = 1;
				V[1] = 1;
			}

			double	curlV_2D	(FVector_double& p) {
				double x = p[0], y = p[1];
				return (0);
			}

			void	VF			(FVector_double& p, FVector_double& vF) {
				double x=p[0], y=p[1];
				vF[0] = -k*k;
				vF[1] = -k*k;
			}
		};
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		//============================================================================
		//                     MAXWELL_ELEMENTARY_NONHOMOGENEOUS
		//============================================================================
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		class P_ELEMENTARY_NONHOMOGENEOUS: public FEM_PROBLEM {	// curl(curl E) - k^2 E = f
		public:
			void	initialize	(FEM_VARIABLES::ENTIRE& __) {
				k = 1;
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(0.,0., 1.,1.);
			}

			void	V			(FVector_double& p, FVector_double& V) {
				double x = p[0], y = p[1];
				V[0] = x*y;
				V[1] = x*y;
			}

			double	curlV_2D	(FVector_double& p) {
				double x = p[0], y = p[1];
				return (y-x);
			}

			void	VF			(FVector_double& p, FVector_double& vF) {
				double x=p[0], y=p[1];
				vF[0] = 1 - k*k*x*y;
				vF[1] = -1 - k*k*x*y;
			}
		};

		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		//============================================================================
		//                           MAXWELL_IIM_ELEMENTARY
		//============================================================================
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		class P_IIM_ELEMENTARY: public FEM_PROBLEM {	// curl(curl E) + k^2 E = f
		public:
			void	initialize	(FEM_VARIABLES::ENTIRE& __) {
				//k = 1;
				r0 = 3.;

				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(0.,0., 1.,1.);

				//Input("\nView (x,y) direction", VAR.nData[0]>>VAR.nData[1]);
				mum = 1.;
				mup = 1.;
				k = 1.;
			//	Input("mum", mum);
			//	Input("mup", mup);
			//	Input("Wavenumber", k);
			}

			double	Interface	(double r) {			// 내부에서 음수의 값을 가지도록 한다.
				return (r - r0);
			}

			double	Interface	(FVector_double& p) {
				double x=p[0], y=p[1];
				double r = sqrt(x*x + y*y);

				return (r - r0);
			}

			void	V			(FVector_double& p, FVector_double& v) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				
				if(Interface(r) <= 0) {
					v.setAll((1-y)*y*sin(y),  (1-x)*x*sin(x)) *= mum;
				} else { 
					v.setAll((1-y)*y*sin(y),  (1-x)*x*sin(x)) *= mup;
				}
			}

			double	curlV_2D	(FVector_double& p) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				double curl = (1-x)*x*cos(x) + (y-1)*y*cos(y) + (1-2*x)*sin(x) - (1-2*y)*sin(y);

				if(Interface(r) <= 0) {
					return mum*curl;
				} else {
					return mup*curl;
				}
			}
			
			void	VF			(FVector_double& p, FVector_double& vF) {
				double x=p[0], y=p[1];

				vF[0] = (-2 + 4*y)*cos(y) + ( 2 + (1 - k*k)*y + (k*k - 1)*y*y )*sin(y);
				vF[1] = (-2 + 4*x)*cos(x) + ( 2 + (1 - k*k)*x + (k*k - 1)*x*x )*sin(x);
			}
		};
		class P_IIM_ELEMENTARY_CONTI : public FEM_PROBLEM {	// mu-1*curl(curl E) - k E = f
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				//k = 1.;
				r0 = 0.6;
				//r0 = 0.;
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);

				//Input("\nView (x,y) direction", VAR.nData[0]>>VAR.nData[1]);
				Input("\nInterior Permeability mum", mum);
				Input("Exterior Permeability mup", mup);
				Input("Wavenumber", k);
			}

			double	Interface(double r) {			// 내부에서 음수의 값을 가지도록 한다.
				return (r - r0);
			}

			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);

				return (r - r0);
			}

			void	V(FVector_double& p, FVector_double& v) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);

				if (Interface(r) <= 0) {
					v.setAll((2 * y*(x*x - 1)*(x*x - 1)*(y*y - 1)*(y*y - 1) + 4 * y*(x*x - 1)*(x*x - 1)*(y*y - 1)*(x*x + y*y - r0*r0))*mum, (-2 * x*(y*y - 1)*(y*y - 1)*(x*x - 1)*(x*x - 1) - 4 * x*(y*y - 1)*(y*y - 1)*(x*x - 1)*(y*y + x*x - r0*r0))*mum);
				}
				else {
					v.setAll((2 * y*(x*x - 1)*(x*x - 1)*(y*y - 1)*(y*y - 1) + 4 * y*(x*x - 1)*(x*x - 1)*(y*y - 1)*(x*x + y*y - r0*r0))*mup, (-2 * x*(y*y - 1)*(y*y - 1)*(x*x - 1)*(x*x - 1) - 4 * x*(y*y - 1)*(y*y - 1)*(x*x - 1)*(y*y + x*x - r0*r0))*mup);
				}
			}

			double	curlV_2D(FVector_double& p) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				double curl = -4 * (x*x - 1)*(x*x - 1)*(y*y - 1)*(y*y - 1) - 16 * x*x*(x*x - 1)*(y*y - 1)*(y*y - 1) - 16 * y*y*(x*x - 1)*(x*x - 1)*(y*y - 1) - 8 * x*x*(y*y - 1)*(y*y - 1)*(-r0*r0 + x*x + y*y) - 8 * y*y*(x*x - 1)*(x*x - 1)*(-r0*r0 + x*x + y*y) - 4 * (x*x - 1)*(y*y - 1)*(y*y - 1)*(-r0*r0 + x*x + y*y) - 4 * (x*x - 1)*(x*x - 1)*(y*y - 1)*(-r0*r0 + x*x + y*y);

				if (Interface(r) <= 0) {
					return mum*curl;
				}
				else {
					return mup*curl;
				}
			}

			void curlV_2D_both(FVector_double& p, FVector_double& vCurl) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				double curl = -4 * (x*x - 1)*(x*x - 1)*(y*y - 1)*(y*y - 1) - 16 * x*x*(x*x - 1)*(y*y - 1)*(y*y - 1) - 16 * y*y*(x*x - 1)*(x*x - 1)*(y*y - 1) - 8 * x*x*(y*y - 1)*(y*y - 1)*(-r0*r0 + x*x + y*y) - 8 * y*y*(x*x - 1)*(x*x - 1)*(-r0*r0 + x*x + y*y) - 4 * (x*x - 1)*(y*y - 1)*(y*y - 1)*(-r0*r0 + x*x + y*y) - 4 * (x*x - 1)*(x*x - 1)*(y*y - 1)*(-r0*r0 + x*x + y*y);
				vCurl.setAll(mum*curl, mup*curl);
			}

			void	VF(FVector_double& p, FVector_double& vF) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				if (Interface(r) <= 0) {
					vF[0] = (-8)*y*(-3 * r0*r0*x*x*x*x - 6 * r0*r0*x*x*y*y + 12 * r0*r0*x*x + 2 * r0*r0*y*y - 5 * r0*r0 + 3 * x*x*x*x*x*x + 30 * x*x*x*x*y*y - 27 * x*x*x*x + 9 * x*x*y*y*y*y - 54 * x*x*y*y + 30 * x*x - 3 * y*y*y*y + 20 * y*y - 8) - k*(2 * y*(x*x - 1)*(x*x - 1)*(y*y - 1)*(y*y - 1) + 4 * y*(x*x - 1)*(x*x - 1)*(y*y - 1)*(x*x + y*y - r0*r0))*mum;
					vF[1] = 8 * x*(-6 * r0*r0*x*x*y*y + 2 * r0*r0*x*x - 3 * r0*r0*y*y*y*y + 12 * r0*r0*y*y - 5 * r0*r0 + 9 * x*x*x*x*y*y - 3 * x*x*x*x + 30 * x*x*y*y*y*y - 54 * x*x*y*y + 20 * x*x + 3 * y*y*y*y*y*y - 27 * y*y*y*y + 30 * y*y - 8) - k*(-2 * x*(y*y - 1)*(y*y - 1)*(x*x - 1)*(x*x - 1) - 4 * x*(y*y - 1)*(y*y - 1)*(x*x - 1)*(y*y + x*x - r0*r0))*mum;

				}
				if (Interface(r) > 0) {
					vF[0] = (-8)*y*(-3 * r0*r0*x*x*x*x - 6 * r0*r0*x*x*y*y + 12 * r0*r0*x*x + 2 * r0*r0*y*y - 5 * r0*r0 + 3 * x*x*x*x*x*x + 30 * x*x*x*x*y*y - 27 * x*x*x*x + 9 * x*x*y*y*y*y - 54 * x*x*y*y + 30 * x*x - 3 * y*y*y*y + 20 * y*y - 8) - k*(2 * y*(x*x - 1)*(x*x - 1)*(y*y - 1)*(y*y - 1) + 4 * y*(x*x - 1)*(x*x - 1)*(y*y - 1)*(x*x + y*y - r0*r0))*mup;
					vF[1] = 8 * x*(-6 * r0*r0*x*x*y*y + 2 * r0*r0*x*x - 3 * r0*r0*y*y*y*y + 12 * r0*r0*y*y - 5 * r0*r0 + 9 * x*x*x*x*y*y - 3 * x*x*x*x + 30 * x*x*y*y*y*y - 54 * x*x*y*y + 20 * x*x + 3 * y*y*y*y*y*y - 27 * y*y*y*y + 30 * y*y - 8) - k*(-2 * x*(y*y - 1)*(y*y - 1)*(x*x - 1)*(x*x - 1) - 4 * x*(y*y - 1)*(y*y - 1)*(x*x - 1)*(y*y + x*x - r0*r0))*mup;
				}
			}
			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}
			double	coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) < 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}




		};
		class P_IIM_ELEMENTARY_GH : public FEM_PROBLEM {	// mu-1*curl(curl E) - k E = f
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				//k = 1.;
				r0 = 0.6;
				//r0 = 0.;
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);

				//Input("\nView (x,y) direction", VAR.nData[0]>>VAR.nData[1]);
				//	Input("\nInterior Permeability mum", mum);
				//	Input("Exterior Permeability mup", mup);
				//	Input("Wavenumber", k);
				//	Input("Wavenumber", eps_m);
				//	Input("Wavenumber", eps_p);
				mum = 1;
				mup = 1;
				k = 1;
				eps_m = 1;
				eps_p = 1;
			}

			double	Interface(double r) {			// 내부에서 음수의 값을 가지도록 한다.
				return (r - r0);
			}

			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);

				return (r - r0);
			}

			void	V(FVector_double& p, FVector_double& v) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				double L = x*x + y*y - r0*r0;
				if (Interface(r) <= 0) {
					v.setAll((x*x - 1)*L*x / eps_m, (y*y-1)*L*y/ eps_m);
				}
				else {
					v.setAll((x*x - 1)*L*x / eps_p, (y*y - 1)*L*y / eps_p);
				}
			}
			void	V(FVector_double& p, FMatrix_double & v) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				double L = x*x + y*y - r0*r0;
				v[0].setAll((x*x - 1)*L*x / eps_m, (y*y - 1)*L*y / eps_m);
				v[1].setAll((x*x - 1)*L*x / eps_p, (y*y - 1)*L*y / eps_p);
			}
			double	curlV_2D(FVector_double& p) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				double curl = 2 * x*y*(y*y - 1) - 2 * x*y*(x*x - 1);

				if (Interface(r) <= 0) {
					return curl / eps_m;
				}
				else {
					return curl / eps_p;
				}
			} 

			void	VF(FVector_double& p, FVector_double& vF) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				double curl_curl_1;
				double curl_curl_2;
				double E_1;
				double E_2;

				
			}
			void	VF(FVector_double& p, FMatrix_double & vF) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				double curl_curl_1;
				double curl_curl_2;
				double E_1;
				double E_2;
				double L = x*x + y*y - r0*r0; 

				curl_curl_1 = 2 * x*(y*y - 1) - 2 * x*(x*x - 1) + 4 * x*y*y;
				curl_curl_2 = 2 * y*(x*x - 1) - 2 * y*(y*y - 1) + 4 * x*x*y;

				E_1 = (x*x - 1)*L*x;
				E_2 = (y*y - 1)*L*y;

				vF[0][0] = curl_curl_1 / eps_m/ mum - k * E_1;
				vF[0][1] = curl_curl_2 / eps_m/ mum - k * E_2;

				vF[1][0] = curl_curl_1 / eps_p / mup - k * E_1;
				vF[1][1] = curl_curl_2 / eps_p / mup - k * E_2;
			}
			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}
			double	coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) < 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}
		};
		class P_IIM_ELEMENTARY_GH_test : public FEM_PROBLEM {	// mu-1*curl(curl E) - k E = f
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				//k = 1.;
				r0 = 0.6;
				//r0 = 0.;
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);

				//Input("\nView (x,y) direction", VAR.nData[0]>>VAR.nData[1]);
			//	Input("\nInterior Permeability mum", mum);
			//	Input("Exterior Permeability mup", mup);
			//	Input("Wavenumber", k);
			//	Input("Wavenumber", eps_m);
			//	Input("Wavenumber", eps_p);
				mum =2;
				mup = 30;
				k = 1;
				eps_m = 30;
				eps_p = 2;
			}
			double	Interface(double r) {			// 내부에서 음수의 값을 가지도록 한다.
				return (r - r0);
			}

			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);

				return (r - r0);
			}

			void	V(FVector_double& p, FVector_double& v) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				double L = x*x + y*y - r0*r0;
				if (Interface(r) <= 0) {
					v.setAll(y*L/eps_m,-x*L/eps_m);
				}
				else {
					v.setAll(y*L / eps_p, -x*L / eps_p);
				}
			}
			void	V(FVector_double& p, FMatrix_double & v) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				double L = x*x + y*y - r0*r0;
				v[0].setAll(y*L / eps_m, -x*L / eps_m);
				v[1].setAll(y*L / eps_p, -x*L / eps_p);
			}
			double	curlV_2D(FVector_double& p) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				double eps_;
				double curl = (-4 * x * x - 4 * y * y + 2 * r0*r0) ;

				if (Interface(r) <= 0) {
					return  curl / eps_m;
				}
				else {
					return curl / eps_p;
				}
			} 
			void	VF(FVector_double& p, FVector_double& vF) {
				double x = p[0], y = p[1];
				
			}
			void	VF(FVector_double& p, FMatrix_double & vF) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				double L = x*x + y*y - r0*r0;

				double curl_curl_1;
				double curl_curl_2;
				double E_1;
				double E_2;

				curl_curl_1 =  -8*y / eps_m;
				curl_curl_2 =  8*x / eps_m;

				E_1 = y* L / eps_m;
				E_2 = -x*L / eps_m;

				vF[0][0] = curl_curl_1 / mum - k * E_1 * eps_m;
				vF[0][1] = curl_curl_2 / mum - k * E_2 * eps_m;

				curl_curl_1 = -8 * y / eps_p;
				curl_curl_2 = 8 * x / eps_p;

				E_1 = y* L / eps_p;
				E_2 = -x*L / eps_p;

				vF[1][0] = curl_curl_1 / mup - k * E_1 * eps_p;
				vF[1][1] = curl_curl_2 / mup - k * E_2 * eps_p;

			}
			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}
			double	coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) < 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			} 
		};
		class P_IIM_ELEMENTARY_LINES : public FEM_PROBLEM {	// mu-1*curl(curl E) - k E = f
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				//k = 1.;
				r0 = CV.PI / 8.;

				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(0., 0., 1., 1.);

				//Input("\nView (x,y) direction", VAR.nData[0]>>VAR.nData[1]);
				Input("\nInterior Permeability mum", mum);
				Input("Exterior Permeability mup", mup);
				Input("Wavenumber", k);
			}

			double Interface(double r) {
				return (r - r0);
			}

			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				double r = abs(x - 1. / 2.) + abs(y - 1. / 2.);
				return (r - r0);
			}
			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, middle, Exterior)

				return 0;
			}

			double	coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}

			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p)<0.0)	return mus[0];
				return mus[1];
			}
			void	V(FVector_double& p, FVector_double& v) {
				double x = p[0], y = p[1];
				double r = abs(x - 1. / 2.) + abs(y - 1. / 2.);

				if (Interface(r) <= 0) {
					v.setAll((1 - y)*y*(x*x + y*y - r0*r0)* mum, (1 - x)*x*(x*x + y*y - r0*r0) * mum);
				}
				else {
					v.setAll((1 - y)*y*(x*x + y*y - r0*r0)* mup, (1 - x)*x*(x*x + y*y - r0*r0) * mup);
				}
			}

			double	curlV_2D(FVector_double& p) {
				double x = p[0], y = p[1];
				double r = abs(x - 1. / 2.) + abs(y - 1. / 2.);
				double curl = 2 * r0*r0*x - 2 * r0*r0*y - 4 * x*x*x + 2 * x*x*y + 2 * x*x - 2 * x*y*y + 4 * y*y*y - 2 * y*y;

				if (Interface(r) <= 0) {
					return mum*curl;
				}
				else {
					return mup*curl;
				}
			}

			void curlV_2D_both(FVector_double& p, FVector_double& vCurl) {
				double x = p[0], y = p[1];
				double r = abs(x - 1. / 2.) + abs(y - 1. / 2.);
				double curl = (1 - x)*x*cos(x) + (y - 1)*y*cos(y) + (1 - 2 * x)*sin(x) - (1 - 2 * y)*sin(y);
				vCurl.setAll(mum*curl, mup*curl);
			}

			void	VF(FVector_double& p, FVector_double& vF) {
				double x = p[0], y = p[1];
				double r = abs(x - 1. / 2.) + abs(y - 1. / 2.);
				if (Interface(r) <= 0) {
					vF[0] = -2 * r0*r0 + 2 * x*x - 4 * x*y + 12 * y*y - 4 * y - k*(1 - y)*y*(x*x + y*y - r0*r0)*mum;
					vF[1] = -2 * r0*r0 + 2 * y*y - 4 * x*y + 12 * x*x - 4 * x - k*(1 - x)*x*(x*x + y*y - r0*r0)*mum;
				}
				if (Interface(r) > 0) {
					vF[0] = -2 * r0*r0 + 2 * x*x - 4 * x*y + 12 * y*y - 4 * y - k*(1 - y)*y*(x*x + y*y - r0*r0)*mup;
					vF[1] = -2 * r0*r0 + 2 * y*y - 4 * x*y + 12 * x*x - 4 * x - k*(1 - x)*x*(x*x + y*y - r0*r0)*mup;
				}
			}
		};
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		//============================================================================
		//                           MAXWELL_IIM_ZHILIN_LEE
		//============================================================================
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		class P_IIM_ZHILIN_LEE_TYPE: public FEM_PROBLEM {	// curl(curl E) + k^2 E = f
		public:
			void	initialize	(FEM_VARIABLES::ENTIRE& __) {
				k = 1;
				r0 = CV.PI/6.28;
				mum = mup = 1;

				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1.,-1., 1.,1.);
			}

			double	Interface	(double r) {			// 내부에서 음수의 값을 가지도록 한다.
				return (r - r0);
			}

			double	Interface	(FVector_double& p) {
				double x=p[0], y=p[1];
				double r = sqrt(x*x + y*y);

				return (r - r0);
			}

			void	V			(FVector_double& p, FVector_double& v) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				
				if(Interface(r) <= 0) {
					v.setAll($(r,3) + $(y,3)/3,  $(r,4) + x*$(y,2)) *= mum;
				} else { 
					v.setAll($(r,3) + $(y,3)/3 + (mum-mup)*$(r0,3),  $(r,4) + x*$(y,2) + (mum-mup)*$(r0,4)) *= mup;
				}
			}

			double	curlV_2D	(FVector_double& p) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				double curl = 4*x*$(r,2) - 3*y*r;

				if(Interface(r) <= 0) {
					return mum*curl;
				} else {
					return mup*curl;
				}
			}
			
			void	curlcurl	(FVector_double& p, FVector_double& v) {
				double x=p[0], y=p[1];
				double r = sqrt(x*x + y*y);

				v.setAll(8*x*y - (3*$(x,2) + 6*$(y,2))/r, -12*$(x,2) -4*$(y,2) + (3*x*y)/r);

				if(Interface(r) <= 0) {
					v *= mum;
				} else {
					v *= mup;
				}
			}

			void	VF			(FVector_double& p, FVector_double& vF) {
				double x=p[0], y=p[1];
				double r = sqrt(x*x + y*y);
				static FVector_double U(2);

				curlcurl(p, vF);
				V(p, U);

				vF.op("-=", $(k,2), U);
			}
		};
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		//============================================================================
		//                               MAXWELL_IIM_KWAK
		//============================================================================
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		class P_IIM_KWAK: public FEM_PROBLEM {	// curl(curl E) + k^2 E = f
		public:
			void	initialize	(FEM_VARIABLES::ENTIRE& __) {
				k = 1;
				r0 = CV.PI/6.28;
				mum = mup = 1;

				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1.,-1., 1.,1.);
			}

			double	Interface	(double r) {			// 내부에서 음수의 값을 가지도록 한다.
				return (r - r0);
			}

			double	Interface	(FVector_double& p) {
				double x=p[0], y=p[1];
				double r = sqrt(x*x + y*y);

				return (r - r0);
			}

			void	V			(FVector_double& p, FVector_double& v) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				
				if(Interface(r) <= 0) {
					v.setAll((y+1)*(y-1), (x+1)*(x-1)) *= ((r*r-r0*r0)*mum);
				} else { 
					v.setAll((y+1)*(y-1), (x+1)*(x-1)) *= ((r*r-r0*r0)*mup);
				}
			}

			double	curlV_2D	(FVector_double& p) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				double curl = 2*(x-y)*(-1 - r0*r0 + 2*x*x + x*y + 2*y*y);

				if(Interface(r) <= 0) {
					return mum*curl;
				} else {
					return mup*curl;
				}
			}
			
			void	curlcurl	(FVector_double& p, FVector_double& v) {
				double x=p[0], y=p[1];
				double r = sqrt(x*x + y*y);

				v.setAll(1 + r0*r0 - x*x + 2*x*y - 6*y*y, 1 + r0*r0 - 6*x*x + 2*x*y - y*y) *= 2;

				if(Interface(r) <= 0) {
					v *= mum;
				} else {
					v *= mup;
				}
			}

			void	VF			(FVector_double& p, FVector_double& vF) {
				double x=p[0], y=p[1];
				double r = sqrt(x*x + y*y);
				static FVector_double U(2);

				curlcurl(p, vF);
				if(Interface(r) <= 0) {
					vF /= mum;
				} else {
					vF /= mup;
				}
				V(p, U);

				vF.op("-=", $(k,2), U);
			}
		};
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		//============================================================================
		//                            MAXWELL_IIM_CUTTING
		//============================================================================
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		class P_IIM_CUTTING: public FEM_PROBLEM {	// curl(curl E) + k^2 E = f
		public:
			double _shift;

			void	initialize	(FEM_VARIABLES::ENTIRE& __) {
				k = 1;
				mum = mup = 1;
				slope = 1;
				_shift = CV.PI/6.28;

				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1.,-1., 1.,1.);
			}

			double	Interface	(FVector_double& p) {	// 좌측을 negative로 한다.
				double x=p[0], y=p[1];

				return (slope*x + _shift - y);
			}

			void	V			(FVector_double& p, FVector_double& v) {
				double x = p[0], y = p[1];
				
				if(Interface(p) <= 0) {
					v.setAll((y+1)*(y-1), (x+1)*(x-1)) *= ((slope*x + _shift - y)*mum);
				} else { 
					v.setAll((y+1)*(y-1), (x+1)*(x-1)) *= ((slope*x + _shift - y)*mup);
				}
			}

			double	curlV_2D	(FVector_double& p) {
				double x = p[0], y = p[1];
				double curl = -1 + 2*_shift*(x-y) + 3*y*y - slope + 3*x*x*slope - 2*x*y*(1 + slope);

				if(Interface(p) <= 0) {
					return mum*curl;
				} else {
					return mup*curl;
				}
			}
			
			void	curlV_2D_both	(FVector_double& p, FVector_double& vCurl) {
				double x = p[0], y = p[1];
				double curl = -1 + 2*_shift*(x-y) + 3*y*y - slope + 3*x*x*slope - 2*x*y*(1 + slope);

				vCurl.setAll(mum*curl, mup*curl);
			}

			void	curlcurl	(FVector_double& p, FVector_double& v) {
				double x=p[0], y=p[1];

				v.setAll(-2*(_shift + x - 3*y + x*slope), 2*(-_shift + y - 3*x*slope + y*slope));

				if(Interface(p) <= 0) {
					v *= mum;
				} else {
					v *= mup;
				}
			}

			void	VF			(FVector_double& p, FVector_double& vF) {
				double x=p[0], y=p[1];
				static FVector_double U(2);

				curlcurl(p, vF);
				if(Interface(p) <= 0) {
					vF /= mum;
				} else {
					vF /= mup;
				}
				V(p, U);

				vF.op("-=", $(k,2), U);
			}
		};
	}; 
	class ELASTICITY  {
	public:
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		//============================================================================
		//                                ID
		//============================================================================
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		class ID {
		public:
			enum {P_HOMOGENEOUS, P_HOMOGENEOUS_KWAK};
		};

		class P_HOMOGENEOUS: public FEM_PROBLEM {	
		public:
			void	initialize	(FEM_VARIABLES::ENTIRE& __) {
				//k = 1.;
				r0 = CV.PI/4.;

				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll( -1., -1., 1.,1.);

				//Input("\nView (x,y) direction", VAR.nData[0]>>VAR.nData[1]);
				Input("\nInterior mum, lambdam", mum);
				Input("Exterior mup, lambdap", mup);
				lambdam = 100*mum;
				lambdap = 100*mup;
			}
			
			double	coef_mu		(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}

			double	coef_mu		(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if(Interface(p) <= 0) {
					return mus[0];
				} else { 
					return mus[1];
				}
			}

			double	Interface	(double r) {			// 내부에서 음수의 값을 가지도록 한다.
				return (r - r0);
			}

			double	Interface	(FVector_double& p) {
				double x=p[0], y=p[1];
				double r = sqrt(x*x + y*y);

				return (r - r0);
			}

			void	V			(FVector_double& p, FVector_double& v) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				
				if(Interface(r) <= 0) {
					v.setAll(r*r, r*r);
				} else { 
					v.setAll(r*r*mum/mup + (1.-mum/mup)*(r0*r0), r*r*mum/mup + (1.-mum/mup)*(r0*r0));
				}
			}
			void	V			(FVector_double& p, FMatrix_double& mv) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				
				mv.setAll(r*r, r*r,
				          r*r*mum/mup + (1.-mum/mup)*(r0*r0), r*r*mum/mup + (1.-mum/mup)*(r0*r0));
			}
			void GRADV			(FVector_double& p, FMatrix_double& GRAD) {
				double x= p[0], y= p[1];
				double r=sqrt(x*x + y*y);
				if(Interface(r) <= 0) {
					GRAD.setAll(0., 0., 0., 0.);
				} else{
					GRAD.setAll(0., 0., 0., 0.);
				}
			}
			void GRADV			(FVector_double& p, FCube_double& cGRAD) {
				double x= p[0], y= p[1];
				double r=sqrt(x*x + y*y);
					cGRAD[0].setAll(0., 0., 0., 0.);
					cGRAD[1].setAll(0., 0., 0., 0.);
			}
			
			double div			(FVector_double& p) {
				double x = p[0], y=p[1];
				double divergence;
				double r = sqrt(x*x + y*y);
				if(Interface(r) <= 0 ) {
					divergence = 2.*x + 2.*y;
				} else {
					divergence = mum/mup * (2.*x + 2.*y);
				}
			return divergence;
			}

			void div			(FVector_double& p, FVector_double& div) {
				double x = p[0], y=p[1];
				double r = sqrt(x*x + y*y);
				div.setAll( 2.*x + 2.*y,mum/mup * (2.*x + 2.*y));
			}
			void	VF			(FVector_double& p, FVector_double& vF) {
				double x=p[0], y=p[1];
				double r = sqrt(x*x + y*y);
				if(Interface(r) <= 0) {
					vF[0] = -6.* mum - 2. * lambdam;
					vF[1] = -6.* mum - 2. * lambdam;
				}
				if(Interface(r) > 0) {
					vF[0] = -6.* mum - 2. * lambdap * mum /mup;
					vF[1] = -6.* mum - 2. * lambdap * mum /mup;
				}
			}
			void	VF			(FVector_double& p, FMatrix_double& mF) {
				double x=p[0], y=p[1];
				mF.setAll(-6.* mum - 2. * lambdam,-6.* mum - 2. * lambdam,-6.* mum - 2. * lambdap * mum /mup,-6.* mum - 2. * lambdap * mum /mup);
			}
		};	
		class P_HOMOGENEOUS_KWAK_Nointer : public FEM_PROBLEM {
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				k = 1.;
				//r0 = CV.PI/8.;
				//r0 = 0.5;
				r0 = 2.546;

				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);
				double nu;
				//mum = 1.; mup = 2.; r0 = 0.9; alpha = 0.; beta = 0.; lambdam = 99; lambdap = 198;
				//Input("\nView (x,y) direction", VAR.nData[0]>>VAR.nData[1]);
				//Input("Interior mum, lambdam", mum);
			//	Input("Exterior mup, lambdap", mup);
			//	Input("Poisson ratio", nu);
				//nu = 0.49;
				mup = 1;
				nu = 0.284;
				mum = mup;
				//Input("r0", r0);
				lambdam = nu *mum;
				lambdap = nu *mup;
			}

			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}

			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) <= 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}
			double coef_lambda(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(lambdam, lambdap);              // (Interior, Exterior)
				return 0;
			}
			double coef_lambda(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_lambda(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double coef_lambda(FVector_double& p) {
				static FVector_double mus(2);
				coef_lambda(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) < 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
				return 0.;
			}
			double	Interface(double r) {			// 내부에서 음수의 값을 가지도록 한다.
				return (r - r0);
			}
			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);

				return (r - r0);
			}
			void	V(FVector_double& p, FVector_double& v) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);

				if (Interface(r) <= 0) {
					v.setAll(1. / mum*(x*x + y*y - r0*r0)*x, 1. / mum*(x*x + y*y - r0*r0)*y);
				}
				else {
					v.setAll(1. / mup*(x*x + y*y - r0*r0)*x, 1. / mup*(x*x + y*y - r0*r0)*y);
				}
			}
			void	V(FVector_double& p, FMatrix_double& mv) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);

				mv.setAll(1. / mum*(x*x + y*y - r0*r0)*x, 1. / mum*(x*x + y*y - r0*r0)*y,
					1. / mup*(x*x + y*y - r0*r0)*x, 1. / mup*(x*x + y*y - r0*r0)*y);
			}
			void GRADV(FVector_double& p, FMatrix_double& GRAD) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				if (Interface(r) <= 0) {
					GRAD.setAll((2.*x*x) / mum + (-r0*r0 + x*x + y*y) / mum, (2.*x*y) / mum, (2.*x*y) / mum, (2.*y*y) / mum + (-r0*r0 + x*x + y*y) / mum);
				}
				else{
					GRAD.setAll((2.*x*x) / mup + (-r0*r0 + x*x + y*y) / mup, (2.*x*y) / mup, (2.*x*y) / mup, (2.*y*y) / mup + (-r0*r0 + x*x + y*y) / mup);
				}
			}
			void GRADV(FVector_double& p, FCube_double& cGRAD) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				cGRAD[0].setAll((2.*x*x) / mum + (-r0*r0 + x*x + y*y) / mum, (2.*x*y) / mum, (2.*x*y) / mum, (2.*y*y) / mum + (-r0*r0 + x*x + y*y) / mum);
				cGRAD[1].setAll((2.*x*x) / mup + (-r0*r0 + x*x + y*y) / mup, (2.*x*y) / mup, (2.*x*y) / mup, (2.*y*y) / mup + (-r0*r0 + x*x + y*y) / mup);
			}
			double div(FVector_double& p) {
				double x = p[0], y = p[1];
				double divergence;
				double r = sqrt(x*x + y*y);
				if (Interface(r) <= 0) {
					divergence = 1. / mum * (4.*x*x + 4.*y*y - 2 * r0*r0);
				}
				else {
					divergence = 1. / mup * (4.*x*x + 4.*y*y - 2 * r0*r0);
				}
				return divergence;
			}
			void div(FVector_double& p, FVector_double& div) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				div.setAll(1. / mum * (4.*x*x + 4.*y*y - 2 * r0*r0), 1. / mup * (4.*x*x + 4.*y*y - 2 * r0*r0));
			}
			void	VF(FVector_double& p, FVector_double& vF) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				if (Interface(r) <= r0) {
					vF[0] = (-16.*x - 8.*lambdam / mum*x);
					vF[1] = (-16.*y - 8.*lambdam / mum*y);
				}
				if (Interface(r) > 0) {
					vF[0] = (-16.*x - 8.*lambdap / mup*x);
					vF[1] = (-16.*y - 8.*lambdap / mup*y);
				}
			}
			void	VF(FVector_double& p, FMatrix_double& mF) {
				double x = p[0], y = p[1];
				mF.setAll(-16.*x - 8.*lambdam / mum*x, -16.*y - 8.*lambdam / mum*y, -16.*x - 8.*lambdap / mup*x, -16.*y - 8.*lambdap / mup*y);
			}
		};
		class P_HOMOGENEOUS_KWAK_Epsilon: public FEM_PROBLEM {
		public:
			void	initialize	(FEM_VARIABLES::ENTIRE& __) {
				//k = 1.;
				//r0 = CV.PI/8.;
				//r0 = 0.5;
				//r0 = 3.;
				
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll( -1., -1., 1.,1.);
				double nu;
				//mum = 1.; mup = 2.; r0 = 0.9; alpha = 0.; beta = 0.; lambdam = 99; lambdap = 198;
				//Input("\nView (x,y) direction", VAR.nData[0]>>VAR.nData[1]);
			//	Input("Interior mum, lambdam", mum);
			//	Input("Exterior mup, lambdap", mup);
			//	Input("Poisson ratio", nu);
			//	Input("r0", r0);
				mum = 1.;
				mup = 100.;
				nu = 0.499;
				r0 = 0.34;

				lambdam = mum*(2 * nu / (1 - 2 * nu));
				lambdap = mup*(2 * nu / (1 - 2 * nu));

			//	lambdam = mum* nu;
			//	lambdap = mup* nu;

				cout << "lambdam: " << lambdam << endl;
			//	lambdam = nu *mum;
			//	lambdap = nu *mup;
			}
			
			double	coef_mu		(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}

			double	coef_mu		(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if(Interface(p) <= 0) {
					return mus[0];
				} else { 
					return mus[1];
				}
			}
			double coef_lambda  (FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(lambdam, lambdap);              // (Interior, Exterior)
				return 0;
			}
			double coef_lambda (FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_lambda(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.

				if(io == CV.IN) return mus[0];
				return mus[1];
			}
			double coef_lambda  (FVector_double& p) {
				static FVector_double mus(2);
				coef_lambda(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.

				if(Interface(p) < 0) {
					return mus[0];
				} 
				else { 
					return mus[1];
				}
				return 0.;
			}
			double	Interface	(double r) {			// 내부에서 음수의 값을 가지도록 한다.
				return (r - r0);
			}
			double	Interface	(FVector_double& p) {
				double x=p[0], y=p[1];
				double r = sqrt(x*x + y*y);

				return (r - r0);
			}
			void	V			(FVector_double& p, FVector_double& v) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				
				if(Interface(r) <= 0) {
					v.setAll(1./mum*(x*x + y*y - r0*r0)*x, 1./mum*(x*x+y*y-r0*r0)*y);
				} else { 
					v.setAll(1./mup*(x*x + y*y - r0*r0)*x, 1./mup*(x*x+y*y-r0*r0)*y);
				}
			}
			void	V			(FVector_double& p, FMatrix_double& mv) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				
				mv.setAll(1./mum*(x*x + y*y - r0*r0)*x, 1./mum*(x*x+y*y-r0*r0)*y,
				1./mup*(x*x + y*y - r0*r0)*x, 1./mup*(x*x+y*y-r0*r0)*y);
			}
			void GRADV			(FVector_double& p, FMatrix_double& GRAD) {
				double x= p[0], y= p[1];
				double r=sqrt(x*x + y*y);
				if(Interface(r) <= 0) {
					GRAD.setAll((2.*x*x)/mum + (- r0*r0 + x*x + y*y)/mum, (2.*x*y)/mum, (2.*x*y)/mum, (2.*y*y)/mum + (- r0*r0 + x*x + y*y)/mum);
				} else{
					GRAD.setAll((2.*x*x)/mup + (- r0*r0 + x*x + y*y)/mup, (2.*x*y)/mup, (2.*x*y)/mup, (2.*y*y)/mup + (- r0*r0 + x*x + y*y)/mup);
				}
			}
			void GRADV			(FVector_double& p, FCube_double& cGRAD) {
				double x= p[0], y= p[1];
				double r=sqrt(x*x + y*y);
					cGRAD[0].setAll((2.*x*x)/mum + (- r0*r0 + x*x + y*y)/mum, (2.*x*y)/mum, (2.*x*y)/mum, (2.*y*y)/mum + (- r0*r0 + x*x + y*y)/mum);
					cGRAD[1].setAll((2.*x*x)/mup + (- r0*r0 + x*x + y*y)/mup, (2.*x*y)/mup, (2.*x*y)/mup, (2.*y*y)/mup + (- r0*r0 + x*x + y*y)/mup);
			}
			double div			(FVector_double& p) {
				double x = p[0], y=p[1];
				double divergence;
				double r = sqrt(x*x + y*y);
				if(Interface(r) <= 0 ) {
					divergence = 1./mum * (4.*x*x + 4.*y*y - 2*r0*r0);
				} else {
					divergence = 1./mup * (4.*x*x + 4.*y*y - 2*r0*r0);
				}
			return divergence;
			}
			void div			(FVector_double& p, FVector_double& div) {
				double x = p[0], y=p[1];
				double r = sqrt(x*x + y*y);
				div.setAll(1./mum * (4.*x*x + 4.*y*y - 2*r0*r0),1./mup * (4.*x*x + 4.*y*y - 2*r0*r0));
			}
			void	VF			(FVector_double& p, FVector_double& vF) {
				double x=p[0], y=p[1];
				double r = sqrt(x*x + y*y);
				if(Interface(r) <= r0) {
					vF[0] = (-16.*x - 8.*lambdam/mum*x);
					vF[1] = (-16.*y - 8.*lambdam/mum*y);
				}
				if(Interface(r) > 0) {
					vF[0] = (-16.*x - 8.*lambdap/mup*x);
					vF[1] = (-16.*y - 8.*lambdap/mup*y);
				}
			}
			void	VF			(FVector_double& p, FMatrix_double& mF) {
				double x=p[0], y=p[1];
				mF.setAll(-16.*x - 8.*lambdam/mum*x,-16.*y - 8.*lambdam/mum*y,-16.*x - 8.*lambdap/mup*x,-16.*y - 8.*lambdap/mup*y);
			}
		};
		class P_HOMOGENEOUS_ZERO_DIV_GH: public FEM_PROBLEM {
		public:
			void	initialize	(FEM_VARIABLES::ENTIRE& __) {
				//k = 1.;
				//r0 = CV.PI/8.;
				//r0 = 0.5;
				//r0 = 3.;
				
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll( -1., -1., 1.,1.);
				double nu;
				//mum = 1.; mup = 2.; r0 = 0.9; alpha = 0.; beta = 0.; lambdam = 99; lambdap = 198;
				//Input("\nView (x,y) direction", VAR.nData[0]>>VAR.nData[1]);
			//	Input("Interior mum, lambdam", mum);
			//	Input("Exterior mup, lambdap", mup);
			//	Input("Poisson ratio", nu);
			//	Input("r0", r0);
				mum = 100.;
				mup = 1.;
				nu = 0.499;
				r0 = 0.6;

				lambdam = mum*(2 * nu / (1 - 2 * nu));
				lambdap = mup*(2 * nu / (1 - 2 * nu));

			//	lambdam = mum* nu;
			//	lambdap = mup* nu;

			//	cout << "lambdam: " << lambdam << endl;
			//	lambdam = nu *mum;
			//	lambdap = nu *mup;
			}
			
			double	coef_mu		(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}

			double	coef_mu		(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if(Interface(p) <= 0) {
					return mus[0];
				} else { 
					return mus[1];
				}
			}
			double coef_lambda  (FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(lambdam, lambdap);              // (Interior, Exterior)
				return 0;
			}
			double coef_lambda (FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_lambda(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.

				if(io == CV.IN) return mus[0];
				return mus[1];
			}
			double coef_lambda  (FVector_double& p) {
				static FVector_double mus(2);
				coef_lambda(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.

				if(Interface(p) < 0) {
					return mus[0];
				} 
				else { 
					return mus[1];
				}
				return 0.;
			}
			double	Interface	(double r) {			// 내부에서 음수의 값을 가지도록 한다.
				return (r - r0);
			}
			double	Interface	(FVector_double& p) {
				double x=p[0], y=p[1];
				double r = sqrt(x*x + y*y);

				return (r - r0);
			}
			void	V			(FVector_double& p, FVector_double& v) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				
				if(Interface(r) <= 0) {
					v.setAll(1./mum*(x*x + y*y - r0*r0)*y, -1./mum*(x*x+y*y-r0*r0)*x);
				} else { 
					v.setAll(1./mup*(x*x + y*y - r0*r0)*y, -1./mup*(x*x+y*y-r0*r0)*x);
				}
			}
			void	V			(FVector_double& p, FMatrix_double& mv) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				
				mv.setAll(1./mum*(x*x + y*y - r0*r0)*y, -1./mum*(x*x+y*y-r0*r0)*x,
				1./mup*(x*x + y*y - r0*r0)*y, -1./mup*(x*x+y*y-r0*r0)*x);
			}
			void GRADV			(FVector_double& p, FMatrix_double& GRAD) {
				double x= p[0], y= p[1];
				double r=sqrt(x*x + y*y);
				if(Interface(r) <= 0) {
					GRAD.setAll((2.*x*y)/mum, (x*x+3*y*y-r0*r0)/mum, (-3*x*x-y*y+r0*r0)/mum, (-2*x*y)/mum);
				} else{
					GRAD.setAll((2.*x*y)/mup, (x*x+3*y*y-r0*r0)/mup, (-3*x*x-y*y+r0*r0)/mup, (-2*x*y)/mup);
				}
			}
			void GRADV			(FVector_double& p, FCube_double& cGRAD) {
				double x= p[0], y= p[1];
				double r=sqrt(x*x + y*y);
					cGRAD[0].setAll((2.*x*y)/mum, (x*x+3*y*y-r0*r0)/mum, (-3*x*x-y*y+r0*r0)/mum, (-2*x*y)/mum);
					cGRAD[1].setAll((2.*x*y)/mup, (x*x+3*y*y-r0*r0)/mup, (-3*x*x-y*y+r0*r0)/mup, (-2*x*y)/mup);
			}
			double div			(FVector_double& p) {
				double x = p[0], y=p[1];
				double divergence;
				double r = sqrt(x*x + y*y);
				if(Interface(r) <= 0 ) {
					divergence = 0.;
				} else {
					divergence = 0.;
				}
			return divergence;
			}
			void div			(FVector_double& p, FVector_double& div) {
				double x = p[0], y=p[1];
				double r = sqrt(x*x + y*y);
				div.setAll(0., 0.);
			}
			void	VF			(FVector_double& p, FVector_double& vF) {
				double x=p[0], y=p[1];
				double r = sqrt(x*x + y*y);
				if(Interface(r) <= 0) {
					vF[0] = -8.*y;
					vF[1] =  8.*x;
				}
				if(Interface(r) > 0) {
					vF[0] = -8.*y;
					vF[1] =  8.*x;
				}
			}
			void	VF			(FVector_double& p, FMatrix_double& mF) {
				double x=p[0], y=p[1];
				mF.setAll(-8.*y, 8.*x, -8.*y, 8.*x);
			}
		};
		class P_HOMOGENEOUS_ZERO_DIV_GH_NON_VANISHING_ON_INTERFACE_CUBIC_CURVE: public FEM_PROBLEM {
		public:
			void	initialize	(FEM_VARIABLES::ENTIRE& __) {
				//k = 1.;
				//r0 = CV.PI/8.;
				//r0 = 0.5;
				//r0 = 3.;
				
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll( -1., -1., 1.,1.);
				double nu;
				//mum = 1.; mup = 2.; r0 = 0.9; alpha = 0.; beta = 0.; lambdam = 99; lambdap = 198;
				//Input("\nView (x,y) direction", VAR.nData[0]>>VAR.nData[1]);
			//	Input("Interior mum, lambdam", mum);
			//	Input("Exterior mup, lambdap", mup);
			//	Input("Poisson ratio", nu);
			//	Input("r0", r0);
				mum = 10.;
				mup = 1.;
				nu = 0.4;
				r0 = 0.4;

				lambdam = mum*(2 * nu / (1 - 2 * nu));
				lambdap = mup*(2 * nu / (1 - 2 * nu));

			//	lambdam = mum* nu;
			//	lambdap = mup* nu;

			//	cout << "lambdam: " << lambdam << endl;
			//	lambdam = nu *mum;
			//	lambdap = nu *mup;
			}
			
			double	coef_mu		(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}

			double	coef_mu		(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if(Interface(p) <= 0) {
					return mus[0];
				} else { 
					return mus[1];
				}
			}
			double coef_lambda  (FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(lambdam, lambdap);              // (Interior, Exterior)
				return 0;
			}
			double coef_lambda (FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_lambda(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.

				if(io == CV.IN) return mus[0];
				return mus[1];
			}
			double coef_lambda  (FVector_double& p) {
				static FVector_double mus(2);
				coef_lambda(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.

				if(Interface(p) < 0) {
					return mus[0];
				} 
				else { 
					return mus[1];
				}
				return 0.;
			}
			double Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				return y-3*x*(x-0.3)*(x-0.8)-0.38;
			}
			void DInterface(FVector_double& p, FVector_double& vDI)	{
				double x = p[0], y = p[1];
				vDI.setAll(-9.*x*x+6.6*x-0.72 , 1.);
			}
			void DDInterface(FVector_double& p, FMatrix_double& mDDI)	{
				double x = p[0], y = p[1];
				mDDI[0][0] = -18.*x+6.6;
				mDDI[0][1] = 0.;
				mDDI[1][0] = 0.;
				mDDI[1][1] = 0.;
			}

			double	Interface	(double r) {			// 내부에서 음수의 값을 가지도록 한다.
				return (r - r0);
			}
			void	V			(FVector_double& p, FVector_double& v) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				
				if(Interface(r) <= 0) {
					v.setAll(1./mum*(-(y-3*x*(x-3)*(x-0.8)-0.38)) +2*y, 1./mum*(y-3*x*(x-3)*(x-0.8)-0.38)*(-9*x*x+22.8*x-7.2) -2*x);
				} else { 
					v.setAll(1./mup*(-(y-3*x*(x-3)*(x-0.8)-0.38)) +2*y, 1./mup*(y-3*x*(x-3)*(x-0.8)-0.38)*(-9*x*x+22.8*x-7.2) -2*x);
				}
			}
			void	V			(FVector_double& p, FMatrix_double& mv) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				
				mv.setAll(1./mum*(-(y-3*x*(x-3)*(x-0.8)-0.38)) +2*y, 1./mum*(y-3*x*(x-3)*(x-0.8)-0.38)*(-9*x*x+22.8*x-7.2) -2*x,
						  1./mup*(-(y-3*x*(x-3)*(x-0.8)-0.38)) +2*y, 1./mup*(y-3*x*(x-3)*(x-0.8)-0.38)*(-9*x*x+22.8*x-7.2) -2*x);
			}
			void GRADV			(FVector_double& p, FMatrix_double& GRAD) {
				double x= p[0], y= p[1];
				double r=sqrt(x*x + y*y);
				if(Interface(r) <= 0) {
					GRAD.setAll((9*x*x-22.8*x+7.2)/mum, -1/mum +2, (-9*x*x+22.8*x-7.2)*(-9*x*x+22.8*x-7.2)/mum + (y-3*x*(x-3)*(x-0.8)-0.38)*(-18*x+22.8)/mum -2, (-9*x*x+22.8*x-7.2)/mum);
				} else{
					GRAD.setAll((9*x*x-22.8*x+7.2)/mup, -1/mup +2, (-9*x*x+22.8*x-7.2)*(-9*x*x+22.8*x-7.2)/mup + (y-3*x*(x-3)*(x-0.8)-0.38)*(-18*x+22.8)/mup -2, (-9*x*x+22.8*x-7.2)/mup);
				}
			}
			void GRADV			(FVector_double& p, FCube_double& cGRAD) {
				double x= p[0], y= p[1];
				double r=sqrt(x*x + y*y);
					cGRAD[0].setAll((9*x*x-22.8*x+7.2)/mum, -1/mum +2, (-9*x*x+22.8*x-7.2)*(-9*x*x+22.8*x-7.2)/mum + (y-3*x*(x-3)*(x-0.8)-0.38)*(-18*x+22.8)/mum -2, (-9*x*x+22.8*x-7.2)/mum);
					cGRAD[1].setAll((9*x*x-22.8*x+7.2)/mup, -1/mup +2, (-9*x*x+22.8*x-7.2)*(-9*x*x+22.8*x-7.2)/mup + (y-3*x*(x-3)*(x-0.8)-0.38)*(-18*x+22.8)/mup -2, (-9*x*x+22.8*x-7.2)/mup);
			}
			double div			(FVector_double& p) {
				double x = p[0], y=p[1];
				double divergence;
				double r = sqrt(x*x + y*y);
				if(Interface(r) <= 0 ) {
					divergence = 0.;
				} else {
					divergence = 0.;
				}
				return divergence;
			}
			void div			(FVector_double& p, FVector_double& div) {
				double x = p[0], y=p[1];
				double r = sqrt(x*x + y*y);
				div.setAll(0., 0.);
			}
			void	VF			(FVector_double& p, FVector_double& vF) {
				double x=p[0], y=p[1];
				double r = sqrt(x*x + y*y);
				if(Interface(r) <= 0) {
					vF[0] = 114./5. - 18*x;
					vF[1] = - 540.*x*x*x + 2052.*x*x - 51948./25.*x + 18*y + 12141./25.;
				}
				if(Interface(r) > 0) {
					vF[0] = 114./5. - 18*x;
					vF[1] = - 540.*x*x*x + 2052.*x*x - 51948./25.*x + 18*y + 12141./25.;
				}
			}
			void	VF			(FVector_double& p, FMatrix_double& mF) {
				double x=p[0], y=p[1];
				mF[0].setAll(114./5. - 18*x,  - 540.*x*x*x + 2052.*x*x - 51948./25.*x + 18*y + 12483./25.);
				mF[1].setAll(114./5. - 18*x,  - 540.*x*x*x + 2052.*x*x - 51948./25.*x + 18*y + 12483./25.);
			}
		};
		class P_HOMOGENEOUS_ZERO_DIV_GH_NON_VANISHING_ON_INTERFACE_QUADRATIC_CURVE: public FEM_PROBLEM {
		public:
			void	initialize	(FEM_VARIABLES::ENTIRE& __) {
				//k = 1.;
				//r0 = CV.PI/8.;
				//r0 = 0.5;
				//r0 = 3.;
				
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll( -1., -1., 1.,1.);
				double nu;
				//mum = 1.; mup = 2.; r0 = 0.9; alpha = 0.; beta = 0.; lambdam = 99; lambdap = 198;
				//Input("\nView (x,y) direction", VAR.nData[0]>>VAR.nData[1]);
			//	Input("Interior mum, lambdam", mum);
			//	Input("Exterior mup, lambdap", mup);
			//	Input("Poisson ratio", nu);
			//	Input("r0", r0);
				mum = 10.;
				mup = 1.;
				nu = 0.4;
				r0 = 0.4;

				lambdam = mum*(2 * nu / (1 - 2 * nu));
				lambdap = mup*(2 * nu / (1 - 2 * nu));

			//	lambdam = mum* nu;
			//	lambdap = mup* nu;

			//	cout << "lambdam: " << lambdam << endl;
			//	lambdam = nu *mum;
			//	lambdap = nu *mup;
			}
			
			double	coef_mu		(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}

			double	coef_mu		(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if(Interface(p) <= 0) {
					return mus[0];
				} else { 
					return mus[1];
				}
			}
			double coef_lambda  (FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(lambdam, lambdap);              // (Interior, Exterior)
				return 0;
			}
			double coef_lambda (FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_lambda(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.

				if(io == CV.IN) return mus[0];
				return mus[1];
			}
			double coef_lambda  (FVector_double& p) {
				static FVector_double mus(2);
				coef_lambda(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.

				if(Interface(p) < 0) {
					return mus[0];
				} 
				else { 
					return mus[1];
				}
				return 0.;
			}
			double Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				return y-x*x/2-0.1;
			}
			void DInterface(FVector_double& p, FVector_double& vDI)	{
				double x = p[0], y = p[1];
				vDI.setAll(-x , 1.);
			}
			void DDInterface(FVector_double& p, FMatrix_double& mDDI)	{
				double x = p[0], y = p[1];
				mDDI[0][0] = -1.;
				mDDI[0][1] = 0.;
				mDDI[1][0] = 0.;
				mDDI[1][1] = 0.;
			}

			double	Interface	(double r) {			// 내부에서 음수의 값을 가지도록 한다.
				return (r - r0);
			}
			void	V			(FVector_double& p, FVector_double& v) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				
				if(Interface(r) <= 0) {
					v.setAll(1./mum*(y-x*x/2-0.1) +2*y/mum, 1./mum*(y-x*x/2-0.1)*x -2*x/mum);
				} else {
					v.setAll(1./mup*(y-x*x/2-0.1) +2*y/mup, 1./mup*(y-x*x/2-0.1)*x -2*x/mup);
				}

				if(Interface(r) <= 0) {
					v.setAll(1./mum*(y-x*x/2-0.1) , 1./mum*(y-x*x/2-0.1)*x );
				} else {
					v.setAll(1./mup*(y-x*x/2-0.1) , 1./mup*(y-x*x/2-0.1)*x );
				}
			}
			void	V			(FVector_double& p, FMatrix_double& mv) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				
				mv[0].setAll(1./mum*(y-x*x/2-0.1) +2*y/mum, 1./mum*(y-x*x/2-0.1)*x -2*x/mum);
				mv[1].setAll(1./mup*(y-x*x/2-0.1) +2*y/mup, 1./mup*(y-x*x/2-0.1)*x -2*x/mup);

				mv[0].setAll(1./mum*(y-x*x/2-0.1) , 1./mum*(y-x*x/2-0.1)*x );
				mv[1].setAll(1./mup*(y-x*x/2-0.1) , 1./mup*(y-x*x/2-0.1)*x );
			}
			void GRADV			(FVector_double& p, FMatrix_double& GRAD) {
				double x= p[0], y= p[1];
				double r=sqrt(x*x + y*y);
				if(Interface(r) <= 0) {
					GRAD.setAll(1./mum*(-x), 1/mum+2/mum,1/mum*(-x*x + y-x*x/2-0.1) -2./mum, 1/mum*x  );
				} else{
					GRAD.setAll(1./mup*(-x), 1/mup+2/mup,1/mup*(-x*x + y-x*x/2-0.1) -2./mup, 1/mup*x  );
				}

				if(Interface(r) <= 0) {
					GRAD.setAll(1./mum*(-x), 1/mum,1/mum*(-x*x + y-x*x/2-0.1) , 1/mum*x  );
				} else{
					GRAD.setAll(1./mup*(-x), 1/mup,1/mup*(-x*x + y-x*x/2-0.1) , 1/mup*x  );
				}
			}
			void GRADV			(FVector_double& p, FCube_double& cGRAD) {
				double x= p[0], y= p[1];
				double r=sqrt(x*x + y*y);
				cGRAD[0].setAll(1./mum*(-x), 1/mum+2/mum,1/mum*(-x*x + y-x*x/2-0.1) -2./mum, 1/mum*x  );
				cGRAD[1].setAll(1./mup*(-x), 1/mup+2/mup,1/mup*(-x*x + y-x*x/2-0.1) -2./mup, 1/mup*x  );

				cGRAD[0].setAll(1./mum*(-x), 1/mum,1/mum*(-x*x + y-x*x/2-0.1) , 1/mum*x  );
				cGRAD[1].setAll(1./mup*(-x), 1/mup,1/mup*(-x*x + y-x*x/2-0.1) , 1/mup*x  );
			}
			double div			(FVector_double& p) {
				double x = p[0], y=p[1];
				double divergence;
				double r = sqrt(x*x + y*y);
				if(Interface(r) <= 0 ) {
					divergence = 0.;
				} else {
					divergence = 0.;
				}
				return divergence;
			}
			void div			(FVector_double& p, FVector_double& div) {
				double x = p[0], y=p[1];
				double r = sqrt(x*x + y*y);
				div.setAll(0., 0.);
			}
			void	VF			(FVector_double& p, FVector_double& vF) {
				double x=p[0], y=p[1];
				double r = sqrt(x*x + y*y);
				if(Interface(r) <= 0) {
					vF[0] = 1;
					vF[1] = 3*x;
				}
				if(Interface(r) > 0) {
					vF[0] = 1;
					vF[1] = 3*x;
				}
			}
			void	VF			(FVector_double& p, FMatrix_double& mF) {
				double x=p[0], y=p[1];
				mF[0].setAll(1., 3.*x);
				mF[1].setAll(1., 3.*x);
			}
		};
		class P_HOMOGENEOUS_ZERO_DIV_GH_NON_VANISHING_ON_INTERFACE_ELLIPSE_CURVE_NONSMOOTH: public FEM_PROBLEM {
		public:
			void	initialize	(FEM_VARIABLES::ENTIRE& __) {
				//k = 1.;
				//r0 = CV.PI/8.;
				//r0 = 0.5;
				//r0 = 3.;
				
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll( -1., -1., 1.,1.);
				double nu;
				//mum = 1.; mup = 2.; r0 = 0.9; alpha = 0.; beta = 0.; lambdam = 99; lambdap = 198;
				//Input("\nView (x,y) direction", VAR.nData[0]>>VAR.nData[1]);
			//	Input("Interior mum, lambdam", mum);
			//	Input("Exterior mup, lambdap", mup);
			//	Input("Poisson ratio", nu);
			//	Input("r0", r0);
				mum = 100.;
				mup = 1.;
				nu = 0.4999;
				r0 = 0.3;

				lambdam = mum*(2 * nu / (1 - 2 * nu));
				lambdap = mup*(2 * nu / (1 - 2 * nu));

			//	lambdam = mum* nu;
			//	lambdap = mup* nu;

			//	cout << "lambdam: " << lambdam << endl;
			//	lambdam = nu *mum;
			//	lambdap = nu *mup;
			}
			
			double	coef_mu		(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}

			double	coef_mu		(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if(Interface(p) <= 0) {
					return mus[0];
				} else { 
					return mus[1];
				}
			}
			double coef_lambda  (FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(lambdam, lambdap);              // (Interior, Exterior)
				return 0;
			}
			double coef_lambda (FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_lambda(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.

				if(io == CV.IN) return mus[0];
				return mus[1];
			}
			double coef_lambda  (FVector_double& p) {
				static FVector_double mus(2);
				coef_lambda(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.

				if(Interface(p) < 0) {
					return mus[0];
				} 
				else { 
					return mus[1];
				}
				return 0.;
			}
			double Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				return (x*x+y*y/2.-0.3);
			}
			void DInterface(FVector_double& p, FVector_double& vDI)	{
				double x = p[0], y = p[1];
				vDI.setAll(-x , 1.);
			}
			void DDInterface(FVector_double& p, FMatrix_double& mDDI)	{
				double x = p[0], y = p[1];
				mDDI[0][0] = -1.;
				mDDI[0][1] = 0.;
				mDDI[1][0] = 0.;
				mDDI[1][1] = 0.;
			}

			double	Interface	(double r) {			// 내부에서 음수의 값을 가지도록 한다.
				return (r - r0);
			}
			void	V			(FVector_double& p, FVector_double& v) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				
				if(Interface(p) <= 0) {
					v.setAll(1/mum*(x*x+y*y/2.-0.3)*y + 2*y, 1./mum*(x*x+y*y/2.-0.3)*(-2.*x) - 2.*x);
				} else {
					v.setAll(1/mup*(x*x+y*y/2.-0.3)*y + 2*y, 1./mup*(x*x+y*y/2.-0.3)*(-2.*x) - 2.*x);
				}
			}
			void	V			(FVector_double& p, FMatrix_double& mv) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				
				mv[0].setAll(1/mum*(x*x+y*y/2.-0.3)*y + 2*y, 1./mum*(x*x+y*y/2.-0.3)*(-2.*x) - 2.*x);
				mv[1].setAll(1/mup*(x*x+y*y/2.-0.3)*y + 2*y, 1./mup*(x*x+y*y/2.-0.3)*(-2.*x) - 2.*x);
			}
			void GRADV			(FVector_double& p, FMatrix_double& GRAD) {
				double x= p[0], y= p[1];
				double r=sqrt(x*x + y*y); 

				if(Interface(p) <= 0) {
					GRAD.setAll(2*x*y/mum, (x*x + (3*y*y)/2 - r0)/mum +2, (- 6*x*x - y*y + 2*r0)/mum -2., -2*x*y/mum);
				} else{
					GRAD.setAll(2*x*y/mup, (x*x + (3*y*y)/2 - r0)/mup +2, (- 6*x*x - y*y + 2*r0)/mup -2., -2*x*y/mup);
				}
			}
			void GRADV			(FVector_double& p, FCube_double& cGRAD) {
				double x= p[0], y= p[1];
				double r=sqrt(x*x + y*y);

				cGRAD[0].setAll(2*x*y/mum, (x*x + (3*y*y)/2 - r0)/mum +2, (- 6*x*x - y*y + 2*r0)/mum -2., -2*x*y/mum);
				cGRAD[1].setAll(2*x*y/mup, (x*x + (3*y*y)/2 - r0)/mup +2, (- 6*x*x - y*y + 2*r0)/mup -2., -2*x*y/mup);
			}
			double div			(FVector_double& p) {
				double x = p[0], y=p[1];
				double divergence;
				double r = sqrt(x*x + y*y);
				if(Interface(p) <= 0 ) {
					divergence = 0.;
				} else {
					divergence = 0.;
				}
				return divergence;
			}
			void div			(FVector_double& p, FVector_double& div) {
				double x = p[0], y=p[1];
				double r = sqrt(x*x + y*y);
				div.setAll(0., 0.);
			}
			void	VF			(FVector_double& p, FVector_double& vF) {
				double x=p[0], y=p[1];
				double r = sqrt(x*x + y*y);
				if(Interface(p) <= 0) {
					vF[0] = 1;
					vF[1] = 3*x;
				}
				if(Interface(p) > 0) {
					vF[0] = 1;
					vF[1] = 3*x;
				}
			}
			void	VF			(FVector_double& p, FMatrix_double& mF) {
				double x=p[0], y=p[1];
				mF[0].setAll(-5*y, 14.*x);
				mF[1].setAll(-5*y, 14.*x);
			}
		};
		class P_HOMOGENEOUS_ZERO_DIV_GH_NON_VANISHING_ON_INTERFACE_ELLIPSE_CURVE_NONSMOOTH_SIMPLE: public FEM_PROBLEM {
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				//k = 1.;
				//r0 = CV.PI/8.;
				//r0 = 0.5;
				//r0 = 3.;

				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);
				double nu;
				//mum = 1.; mup = 2.; r0 = 0.9; alpha = 0.; beta = 0.; lambdam = 99; lambdap = 198;
				//Input("\nView (x,y) direction", VAR.nData[0]>>VAR.nData[1]);
				//	Input("Interior mum, lambdam", mum);
				//	Input("Exterior mup, lambdap", mup);
				//	Input("Poisson ratio", nu);
				//	Input("r0", r0);
				mum = 100.;
				mup = 1.;
				nu = 0.499;
				r0 = 0.6;

				lambdam = mum*(2 * nu / (1 - 2 * nu));
				lambdap = mup*(2 * nu / (1 - 2 * nu));
			//	lambdap = 100;

				//	lambdam = mum* nu;
				//	lambdap = mup* nu;

				//	cout << "lambdam: " << lambdam << endl;
				//	lambdam = nu *mum;
				//	lambdap = nu *mup;
			}

			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}

			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) <= 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}
			double coef_lambda(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(lambdam, lambdap);              // (Interior, Exterior)
				return 0;
			}
			double coef_lambda(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_lambda(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double coef_lambda(FVector_double& p) {
				static FVector_double mus(2);
				coef_lambda(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) < 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
				return 0.;
			}
			double Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				return (x*x + y*y / 2. - 0.3);
			}
			void DInterface(FVector_double& p, FVector_double& vDI) {
				double x = p[0], y = p[1];
				vDI.setAll(-x, 1.);
			}
			void DDInterface(FVector_double& p, FMatrix_double& mDDI) {
				double x = p[0], y = p[1];
				mDDI[0][0] = -1.;
				mDDI[0][1] = 0.;
				mDDI[1][0] = 0.;
				mDDI[1][1] = 0.;
			}

			double	Interface(double r) {			// 내부에서 음수의 값을 가지도록 한다.
				return (r - r0);
			}
			void	V(FVector_double& p, FVector_double& v) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);

				if (Interface(r) <= 0) {
					v.setAll(2 * y, - 2.*x);
				}
				else {
					v.setAll(2 * y, -2.*x);
				}
			}
			void	V(FVector_double& p, FMatrix_double& mv) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);

				mv[0].setAll(2 * y, -2.*x);
				mv[1].setAll(2 * y, -2.*x);
			}
			void GRADV(FVector_double& p, FMatrix_double& GRAD) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);

				if (Interface(r) <= 0) {
					GRAD.setAll(0.,  2., - 2., 0.);
				}
				else {
					GRAD.setAll(0., 2., -2., 0.);
				}
			}
			void GRADV(FVector_double& p, FCube_double& cGRAD) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);

				cGRAD[0].setAll(0., 2., -2., 0.);
				cGRAD[1].setAll(0., 2., -2., 0.);
			}
			double div(FVector_double& p) {
				double x = p[0], y = p[1];
				double divergence;
				double r = sqrt(x*x + y*y);
				if (Interface(r) <= 0) {
					divergence = 0.;
				}
				else {
					divergence = 0.;
				}
				return divergence;
			}
			void div(FVector_double& p, FVector_double& div) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				div.setAll(0., 0.);
			}
			void	VF(FVector_double& p, FVector_double& vF) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				if (Interface(r) <= 0) {
					vF[0] = 0.;
					vF[1] = 0.;
				}
				if (Interface(r) > 0) {
					vF[0] = 0.;
					vF[1] = 0.;
				}
			}
			void	VF(FVector_double& p, FMatrix_double& mF) {
				double x = p[0], y = p[1];
				mF[0].setAll(0., 0.);
				mF[1].setAll(0., 0.);
			}
		};
		class P_HOMOGENEOUS_ZERO_DIV_GH_NON_VANISHING_ON_INTERFACE_LINE_NONSMOOTH_SIMPLE: public FEM_PROBLEM {
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				//k = 1.;
				//r0 = CV.PI/8.;
				//r0 = 0.5;
				//r0 = 3.;

				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);
				double nu;
				//mum = 1.; mup = 2.; r0 = 0.9; alpha = 0.; beta = 0.; lambdam = 99; lambdap = 198;
				//Input("\nView (x,y) direction", VAR.nData[0]>>VAR.nData[1]);
				//	Input("Interior mum, lambdam", mum);
				//	Input("Exterior mup, lambdap", mup);
				//	Input("Poisson ratio", nu);
				//	Input("r0", r0);
				mum = 2;
				mup = 3.;
				nu = 10;
			//	r0 = 0.3;

				lambdam = 10.;
				lambdap = 10.;

				a=1.;

			//	lambdam = mum* nu;
			//	lambdap = mup* nu;

				//	cout << "lambdam: " << lambdam << endl;
				//	lambdam = nu *mum;
				//	lambdap = nu *mup;
			}

			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}

			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) <= 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}
			double coef_lambda(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(lambdam, lambdap);              // (Interior, Exterior)
				return 0;
			}
			double coef_lambda(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_lambda(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double coef_lambda(FVector_double& p) {
				static FVector_double mus(2);
				coef_lambda(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) < 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
				return 0.;
			}
			double Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				return (y + a*x +1.2111);
			}
			void DInterface(FVector_double& p, FVector_double& vDI) {
				double x = p[0], y = p[1];
				vDI.setAll(1., 1.);
			}
			void DDInterface(FVector_double& p, FMatrix_double& mDDI) {
				double x = p[0], y = p[1];
				mDDI[0][0] = 0.;
				mDDI[0][1] = 0.;
				mDDI[1][0] = 0.;
				mDDI[1][1] = 0.;
			}
			double	Interface(double r) {			// 내부에서 음수의 값을 가지도록 한다.
				return (r - r0);
			}
			void	V(FVector_double& p, FVector_double& v) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);

				if (Interface(p) <= 0) {
					v.setAll( x, a*a*y-2*a*x);
				}
				else {
					v.setAll( x, a*a*y-2*a*x);
				}
			}
			void	V(FVector_double& p, FMatrix_double& mv) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);

				mv[0].setAll( x, a*a*y-2*a*x);
				mv[1].setAll( x, a*a*y-2*a*x);
			}
			void GRADV(FVector_double& p, FMatrix_double& GRAD) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);

				if (Interface(p) <= 0) {
					GRAD.setAll(1.,  0., -2*a, a*a);
				}
				else {
					GRAD.setAll(1.,  0., -2*a, a*a);
				}
			}
			void GRADV(FVector_double& p, FCube_double& cGRAD) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);

				cGRAD[0].setAll(1.,  0., -2*a, a*a);
				cGRAD[1].setAll(1.,  0., -2*a, a*a);
			}
			double div(FVector_double& p) {
				double x = p[0], y = p[1];
				double divergence;
				double r = sqrt(x*x + y*y);
				if (Interface(p) <= 0) {
					divergence = 1.+a*a;
				}
				else {
					divergence = 1.+a*a;
				}
				return divergence;
			}
			void div(FVector_double& p, FVector_double& div) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				div.setAll(1. + a*a, 1. + a*a);
			}
			void	VF(FVector_double& p, FVector_double& vF) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				if (Interface(p) <= 0) {
					vF[0] = 0.;
					vF[1] = 0.;
				}
				if (Interface(p) > 0) {
					vF[0] = 0.;
					vF[1] = 0.;
				}
			}
			void	VF(FVector_double& p, FMatrix_double& mF) {
				double x = p[0], y = p[1];
				mF[0].setAll(0., 0.);
				mF[1].setAll(0., 0.);
			}
		};
		class P_HOMOGENEOUS_ZERO_DIV_GH_NON_VANISHING_ON_INTERFACE_LINE_SMOOTH_SIMPLE: public FEM_PROBLEM {
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				//k = 1.;
				//r0 = CV.PI/8.;
				//r0 = 0.5;
				//r0 = 3.;

				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);
				double nu;
				//mum = 1.; mup = 2.; r0 = 0.9; alpha = 0.; beta = 0.; lambdam = 99; lambdap = 198;
				//Input("\nView (x,y) direction", VAR.nData[0]>>VAR.nData[1]);
				//	Input("Interior mum, lambdam", mum);
				//	Input("Exterior mup, lambdap", mup);
				//	Input("Poisson ratio", nu);
				//	Input("r0", r0);
				mum = 1.;
				mup = 1.;
				nu = 10;
			//	r0 = 0.3;

			//	lambdam = 10.;
			//	lambdap = 10.;

				lambdam = mum* nu;
				lambdap = mup* nu;

				//	cout << "lambdam: " << lambdam << endl;
				//	lambdam = nu *mum;
				//	lambdap = nu *mup;
			}

			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}

			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) <= 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}
			double coef_lambda(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(lambdam, lambdap);              // (Interior, Exterior)
				return 0;
			}
			double coef_lambda(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_lambda(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double coef_lambda(FVector_double& p) {
				static FVector_double mus(2);
				coef_lambda(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) < 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
				return 0.;
			}
			double Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				return (x + y - 0.3);
			}
			void DInterface(FVector_double& p, FVector_double& vDI) {
				double x = p[0], y = p[1];
				vDI.setAll(1., 1.);
			}
			void DDInterface(FVector_double& p, FMatrix_double& mDDI) {
				double x = p[0], y = p[1];
				mDDI[0][0] = 0.;
				mDDI[0][1] = 0.;
				mDDI[1][0] = 0.;
				mDDI[1][1] = 0.;
			}
			double	Interface(double r) {			// 내부에서 음수의 값을 가지도록 한다.
				return (r - r0);
			}
			void	V(FVector_double& p, FVector_double& v) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);

				if (Interface(p) <= 0) {
					v.setAll( (x+y-0.3)/mum, (x+y-0.3)/mum);
				}
				else {
					v.setAll( (x+y-0.3)/mup, (x+y-0.3)/mup);
				}
			}
			void	V(FVector_double& p, FMatrix_double& mv) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);

				mv[0].setAll( (x+y-0.3)/mum, (x+y-0.3)/mum);
				mv[1].setAll( (x+y-0.3)/mup, (x+y-0.3)/mup);
			}
			void GRADV(FVector_double& p, FMatrix_double& GRAD) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);

				if (Interface(p) <= 0) {
					GRAD.setAll(1./mum,  1./mum, 1./mum, 1./mum);
				}
				else {
					GRAD.setAll(1./mup,  1./mup, 1./mup, 1./mup);
				}
			}
			void GRADV(FVector_double& p, FCube_double& cGRAD) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);

				cGRAD[0].setAll(1./mum,  1./mum, 1./mum, 1./mum);
				cGRAD[1].setAll(1./mup,  1./mup, 1./mup, 1./mup);
			}
			double div(FVector_double& p) {
				double x = p[0], y = p[1];
				double divergence;
				double r = sqrt(x*x + y*y);
				if (Interface(p) <= 0) {
					divergence = 2./mum;
				}
				else {
					divergence = 2./mup;
				}
				return divergence;
			}
			void div(FVector_double& p, FVector_double& div) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				div.setAll(2./mum, 2./mup);
			}
			void	VF(FVector_double& p, FVector_double& vF) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				if (Interface(p) <= 0) {
					vF[0] = 0.;
					vF[1] = 0.;
				}
				if (Interface(p) > 0) {
					vF[0] = 0.;
					vF[1] = 0.;
				}
			}
			void	VF(FVector_double& p, FMatrix_double& mF) {
				double x = p[0], y = p[1];
				mF[0].setAll(0., 0.);
				mF[1].setAll(0., 0.);
			}
		};
		class P_HOMOGENEOUS_ZERO_DIV_GH_NON_VANISHING_ON_INTERFACE_ELLIPSE_CURVE_SMOOTH: public FEM_PROBLEM {
		public:
			void	initialize	(FEM_VARIABLES::ENTIRE& __) {
				//k = 1.;
				//r0 = CV.PI/8.;
				//r0 = 0.5;
				//r0 = 3.;
				
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll( -1., -1., 1.,1.);
				double nu;
				//mum = 1.; mup = 2.; r0 = 0.9; alpha = 0.; beta = 0.; lambdam = 99; lambdap = 198;
				//Input("\nView (x,y) direction", VAR.nData[0]>>VAR.nData[1]);
			//	Input("Interior mum, lambdam", mum);
			//	Input("Exterior mup, lambdap", mup);
			//	Input("Poisson ratio", nu);
			//	Input("r0", r0);
				mum = 100.;
				mup = 1.;
				nu = 0.4999;
				r0 = 0.3;

				lambdam = mum*(2 * nu / (1 - 2 * nu));
				lambdap = mup*(2 * nu / (1 - 2 * nu));

			//	lambdam = mum* nu;
			//	lambdap = mup* nu;

			//	cout << "lambdam: " << lambdam << endl;
			//	lambdam = nu *mum;
			//	lambdap = nu *mup;
			}
			
			double	coef_mu		(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}

			double	coef_mu		(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if(Interface(p) <= 0) {
					return mus[0];
				} else { 
					return mus[1];
				}
			}
			double coef_lambda  (FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(lambdam, lambdap);              // (Interior, Exterior)
				return 0;
			}
			double coef_lambda (FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_lambda(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.

				if(io == CV.IN) return mus[0];
				return mus[1];
			}
			double coef_lambda  (FVector_double& p) {
				static FVector_double mus(2);
				coef_lambda(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.

				if(Interface(p) < 0) {
					return mus[0];
				} 
				else { 
					return mus[1];
				}
				return 0.;
			}
			double Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				return (x*x+y*y/2.-0.3);
			}
			void DInterface(FVector_double& p, FVector_double& vDI)	{
				double x = p[0], y = p[1];
				vDI.setAll(-x , 1.);
			}
			void DDInterface(FVector_double& p, FMatrix_double& mDDI)	{
				double x = p[0], y = p[1];
				mDDI[0][0] = -1.;
				mDDI[0][1] = 0.;
				mDDI[1][0] = 0.;
				mDDI[1][1] = 0.;
			}

			double	Interface	(double r) {			// 내부에서 음수의 값을 가지도록 한다.
				return (r - r0);
			}
			void	V			(FVector_double& p, FVector_double& v) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				
				if(Interface(p) <= 0) {
					v.setAll(1/mum*(x*x+y*y/2.-0.3)*y + 2*y/mum, 1./mum*(x*x+y*y/2.-0.3)*(-2.*x) - 2.*x/mum);
				} else {
					v.setAll(1/mup*(x*x+y*y/2.-0.3)*y + 2*y/mup, 1./mup*(x*x+y*y/2.-0.3)*(-2.*x) - 2.*x/mup);
				}
			}
			void	V			(FVector_double& p, FMatrix_double& mv) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				
				mv[0].setAll(1/mum*(x*x+y*y/2.-0.3)*y + 2*y/mum, 1./mum*(x*x+y*y/2.-0.3)*(-2.*x) - 2.*x/mum);
				mv[1].setAll(1/mup*(x*x+y*y/2.-0.3)*y + 2*y/mup, 1./mup*(x*x+y*y/2.-0.3)*(-2.*x) - 2.*x/mup);
			}
			void GRADV			(FVector_double& p, FMatrix_double& GRAD) {
				double x= p[0], y= p[1];
				double r=sqrt(x*x + y*y); 

				if(Interface(p) <= 0) {
					GRAD.setAll(2*x*y/mum, (x*x + (3*y*y)/2 - r0)/mum +2/mum, (- 6*x*x - y*y + 2*r0)/mum -2/mum, -2*x*y/mum);
				} else{
					GRAD.setAll(2*x*y/mup, (x*x + (3*y*y)/2 - r0)/mup +2/mup, (- 6*x*x - y*y + 2*r0)/mup -2/mup, -2*x*y/mup);
				}
			}
			void GRADV			(FVector_double& p, FCube_double& cGRAD) {
				double x= p[0], y= p[1];
				double r=sqrt(x*x + y*y);

				cGRAD[0].setAll(2*x*y/mum, (x*x + (3*y*y)/2 - r0)/mum +2/mup, (- 6*x*x - y*y + 2*r0)/mum -2./mum, -2*x*y/mum);
				cGRAD[1].setAll(2*x*y/mup, (x*x + (3*y*y)/2 - r0)/mup +2/mup, (- 6*x*x - y*y + 2*r0)/mup -2./mup, -2*x*y/mup);
			}
			double div			(FVector_double& p) {
				double x = p[0], y=p[1];
				double divergence;
				double r = sqrt(x*x + y*y);
				if(Interface(p) <= 0 ) {
					divergence = 0.;
				} else {
					divergence = 0.;
				}
				return divergence;
			}
			void div			(FVector_double& p, FVector_double& div) {
				double x = p[0], y=p[1];
				double r = sqrt(x*x + y*y);
				div.setAll(0., 0.);
			}
			void	VF			(FVector_double& p, FVector_double& vF) {
				double x=p[0], y=p[1];
				double r = sqrt(x*x + y*y);
				if(Interface(p) <= 0) {
					vF[0] = 1;
					vF[1] = 3*x;
				}
				if(Interface(p) > 0) {
					vF[0] = 1;
					vF[1] = 3*x;
				}
			}
			void	VF			(FVector_double& p, FMatrix_double& mF) {
				double x=p[0], y=p[1];
				mF[0].setAll(-5*y, 14.*x);
				mF[1].setAll(-5*y, 14.*x);
			}
		};
		class P_HOMOGENEOUS_non_interface : public FEM_PROBLEM {
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				//k = 1.;
				//r0 = CV.PI/8.;
				//r0 = 0.5;
				//r0 = 3.;

				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);
				double nu;
				//mum = 1.; mup = 2.; r0 = 0.9; alpha = 0.; beta = 0.; lambdam = 99; lambdap = 198;
				//Input("\nView (x,y) direction", VAR.nData[0]>>VAR.nData[1]);
				mu = 1.;
				mum = mu;
				mup = mu;
				r0 =4;
				nu = 1.;
			//	Input("Interior mum, lambdam", mum);
			//	Input("Exterior mup, lambdap", mup);
			//	Input("Poisson ratio", nu);
			//	Input("r0", r0);

				lambdam = nu *mum;
				lambdap = nu *mup;
			}

			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}

			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) <= 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}
			double coef_lambda(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(lambdam, lambdap);              // (Interior, Exterior)
				return 0;
			}
			double coef_lambda(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_lambda(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double coef_lambda(FVector_double& p) {
				static FVector_double mus(2);
				coef_lambda(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) < 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
				return 0.;
			}
			double	Interface(double r) {			// 내부에서 음수의 값을 가지도록 한다.
				return (r - r0);
			}
			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);

				return (r - r0);
			}
			void	V(FVector_double& p, FVector_double& v) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);

				if (Interface(r) <= 0) {
					v.setAll(1. / mum*(x*x + y*y - r0*r0)*x, 1. / mum*(x*x + y*y - r0*r0)*y);
				}
				else {
					v.setAll(1. / mup*(x*x + y*y - r0*r0)*x, 1. / mup*(x*x + y*y - r0*r0)*y);
				}
			}
			void	V(FVector_double& p, FMatrix_double& mv) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);

				mv.setAll(1. / mum*(x*x + y*y - r0*r0)*x, 1. / mum*(x*x + y*y - r0*r0)*y,
					1. / mup*(x*x + y*y - r0*r0)*x, 1. / mup*(x*x + y*y - r0*r0)*y);
			}
			void GRADV(FVector_double& p, FMatrix_double& GRAD) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				if (Interface(r) <= 0) {
					GRAD.setAll((2.*x*x) / mum + (-r0*r0 + x*x + y*y) / mum, (2.*x*y) / mum, (2.*x*y) / mum, (2.*y*y) / mum + (-r0*r0 + x*x + y*y) / mum);
				}
				else{
					GRAD.setAll((2.*x*x) / mup + (-r0*r0 + x*x + y*y) / mup, (2.*x*y) / mup, (2.*x*y) / mup, (2.*y*y) / mup + (-r0*r0 + x*x + y*y) / mup);
				}
			}
			void GRADV(FVector_double& p, FCube_double& cGRAD) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				cGRAD[0].setAll((2.*x*x) / mum + (-r0*r0 + x*x + y*y) / mum, (2.*x*y) / mum, (2.*x*y) / mum, (2.*y*y) / mum + (-r0*r0 + x*x + y*y) / mum);
				cGRAD[1].setAll((2.*x*x) / mup + (-r0*r0 + x*x + y*y) / mup, (2.*x*y) / mup, (2.*x*y) / mup, (2.*y*y) / mup + (-r0*r0 + x*x + y*y) / mup);
			}
			double div(FVector_double& p) {
				double x = p[0], y = p[1];
				double divergence;
				double r = sqrt(x*x + y*y);
				if (Interface(r) <= 0) {
					divergence = 1. / mum * (4.*x*x + 4.*y*y - 2 * r0*r0);
				}
				else {
					divergence = 1. / mup * (4.*x*x + 4.*y*y - 2 * r0*r0);
				}
				return divergence;
			}
			void div(FVector_double& p, FVector_double& div) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				div.setAll(1. / mum * (4.*x*x + 4.*y*y - 2 * r0*r0), 1. / mup * (4.*x*x + 4.*y*y - 2 * r0*r0));
			}
			void	VF(FVector_double& p, FVector_double& vF) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				if (Interface(r) <= r0) {
					vF[0] = (-16.*x - 8.*lambdam / mum*x);
					vF[1] = (-16.*y - 8.*lambdam / mum*y);
				}
				if (Interface(r) > 0) {
					vF[0] = (-16.*x - 8.*lambdap / mup*x);
					vF[1] = (-16.*y - 8.*lambdap / mup*y);
				}
			}
			void	VF(FVector_double& p, FMatrix_double& mF) {
				double x = p[0], y = p[1];
				mF.setAll(-16.*x - 8.*lambdam / mum*x, -16.*y - 8.*lambdam / mum*y, -16.*x - 8.*lambdap / mup*x, -16.*y - 8.*lambdap / mup*y);
			}
		};
		class P_HOMOGENEOUS_2D_CLOSED_DRIVEN_CAVITY : public FEM_PROBLEM {
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				//k = 1.;
				//r0 = CV.PI/8.;
				//r0 = 0.5;
				//r0 = 3.;

				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);
				double nu;
				//mum = 1.; mup = 2.; r0 = 0.9; alpha = 0.; beta = 0.; lambdam = 99; lambdap = 198;
				//Input("\nView (x,y) direction", VAR.nData[0]>>VAR.nData[1]);
				mu = 1.;
				mum = 1;
				mup = 100;
				r0 =0.4;
				nu = 0.49;
			//	Input("Interior mum, lambdam", mum);
			//	Input("Exterior mup, lambdap", mup);
			//	Input("Poisson ratio", nu);
			//	Input("r0", r0);

				lambdam = mum*(2 * nu / (1 - 2 * nu));
				lambdap = mup*(2 * nu / (1 - 2 * nu));

			//	lambdam = nu *mum;
			//	lambdap = nu *mup;
			}

			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}

			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) <= 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}
			double coef_lambda(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(lambdam, lambdap);              // (Interior, Exterior)
				return 0;
			}
			double coef_lambda(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_lambda(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double coef_lambda(FVector_double& p) {
				static FVector_double mus(2);
				coef_lambda(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) < 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
				return 0.;
			}
			double	Interface(double r) {			// 내부에서 음수의 값을 가지도록 한다.
				return (r - r0);
			}
			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);

				return (r - r0);
			}
			void	V(FVector_double& p, FVector_double& v) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);

				if (y==1){
					v[0]=1.;
					v[1]=0.;
				}
				if ( (x==-1) || (x==1) || (y==-1) ){
					v[0]=0.;
					v[1]=0.;
				}
				
			}
			void	V(FVector_double& p, FMatrix_double& mv) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);

				if (y==1){
					mv[1][0]=1.;
					mv[1][1]=0.;
				}
				if ( (x==-1) || (x==1) || (y==-1) ){
					mv[0][0]=0.;
					mv[0][1]=0.;
				}
				
				 
			}
			void GRADV(FVector_double& p, FMatrix_double& GRAD) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				GRAD.clear();
			}
			void GRADV(FVector_double& p, FCube_double& cGRAD) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				cGRAD.clear();
			}
			double div(FVector_double& p) {
				double x = p[0], y = p[1];
				double divergence;
				double r = sqrt(x*x + y*y);

				return 0.;
			}
			void div(FVector_double& p, FVector_double& div) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);

				div.clear();
			}
			void	VF(FVector_double& p, FVector_double& vF) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);

				vF.clear();
			}
			void	VF(FVector_double& p, FMatrix_double& mF) {
				double x = p[0], y = p[1];
				mF.clear();
			}
		};
		class P_HOMOGENEOUS_non_interface_3D : public FEM_PROBLEM {
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				//k = 1.;
				//r0 = CV.PI/8.;
				//r0 = 0.5;
				//r0 = 3.;

				dim = __.dim = 3;
				RX = __.RX.make(2, __.dim).setAll(-0.5, -0.5, -0.5, 0.5, 0.5, 0.5);

				double nu;
				//mum = 1.; mup = 2.; r0 = 0.9; alpha = 0.; beta = 0.; lambdam = 99; lambdap = 198;
				//Input("\nView (x,y) direction", VAR.nData[0]>>VAR.nData[1]);
				mu = 1.;
				mum = mu;
				mup = mu;
				r0 =1;
				nu = 49;
			//	Input("Interior mum, lambdam", mum);
			//	Input("Exterior mup, lambdap", mup);
			//	Input("Poisson ratio", nu);
			//	Input("r0", r0);

				lambdam = nu *mum;
				lambdap = nu *mup;
			}

			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1], z= p[2];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}

			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) <= 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}
			double coef_lambda(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1], z= p[2];
				mus.setAll(lambdam, lambdap);              // (Interior, Exterior)
				return 0;
			}
			double coef_lambda(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_lambda(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double coef_lambda(FVector_double& p) {
				static FVector_double mus(2);
				coef_lambda(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) < 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
				return 0.;
			}
			double	Interface(double r) {			// 내부에서 음수의 값을 가지도록 한다.
				return (r - r0);
			}
			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1], z= p[2];
				double r = sqrt(x*x + y*y + z*z);

				return (r - r0);
			}
			void	V(FVector_double& p, FVector_double& v) {
				double x = p[0], y = p[1], z= p[2];
				double r = sqrt(x*x + y*y + z*z);

				if (Interface(r) <= 0) {
					v.setAll(1. / mum*(x*x + y*y +z*z - r0*r0)*x, 1. / mum*(x*x + y*y +z*z - r0*r0)*y, 1. / mum*(x*x + y*y +z*z - r0*r0)*z);
				}
				else {
					v.setAll(1. / mup*(x*x + y*y +z*z - r0*r0)*x, 1. / mup*(x*x + y*y +z*z - r0*r0)*y, 1. / mup*(x*x + y*y +z*z - r0*r0)*z);
				}
			}
			void	V(FVector_double& p, FMatrix_double& mv) {
				double x = p[0], y = p[1], z= p[2];
				double r = sqrt(x*x + y*y + z*z);

				mv.setAll(1. / mum*(x*x + y*y +z*z - r0*r0)*x, 1. / mum*(x*x + y*y +z*z - r0*r0)*y, 1. / mum*(x*x + y*y +z*z - r0*r0)*z,
					1. / mup*(x*x + y*y +z*z - r0*r0)*x, 1. / mup*(x*x + y*y +z*z - r0*r0)*y, 1. / mup*(x*x + y*y +z*z - r0*r0)*z);
			}
			void GRADV(FVector_double& p, FMatrix_double& GRAD) {
				double x = p[0], y = p[1], z= p[2];
				double r = sqrt(x*x + y*y + z*z);
				if (Interface(r) <= 0) {
					GRAD[0].setAll(2.*x*x/ mum + (-r0*r0 + x*x + y*y+z*z) / mum, (2.*x*y) / mum, (2.*x*z) / mum);
					GRAD[1].setAll(2.*x*y/mum, 2.*y*y/mum + (-r0*r0 + x*x + y*y+z*z) / mum, 2*y*z/mum);
					GRAD[2].setAll(2.*x*z/mum, 2*y*z/mum, 2*z*z/mum + (-r0*r0 + x*x + y*y+z*z) / mum);
				}
				else{
					GRAD[0].setAll((2.*x*x)/mup + (-r0*r0 + x*x + y*y+z*z) / mup, (2.*x*y) / mup, (2.*x*z) / mup);
					GRAD[1].setAll(2.*x*y/mup, 2.*y*y/mup+ (-r0*r0 + x*x + y*y+z*z) / mup, 2*y*z/mup);
					GRAD[2].setAll(2.*x*z/mup, 2*y*z/mup, 2*z*z/mup + (-r0*r0 + x*x + y*y+z*z) / mup);
				}
			}
			void GRADV(FVector_double& p, FCube_double& cGRAD) {
				double x = p[0], y = p[1], z= p[2];
				double r = sqrt(x*x + y*y + z*z);

				cGRAD[0][0].setAll(2.*x*x/ mum + (-r0*r0 + x*x + y*y+z*z) / mum, (2.*x*y) / mum, (2.*x*z) / mum);
				cGRAD[0][1].setAll(2.*x*y/mum, 2.*y*y/mum + (-r0*r0 + x*x + y*y+z*z) / mum, 2*y*z/mum);
				cGRAD[0][2].setAll(2.*x*z/mum, 2*y*z/mum, 2*z*z/mum + (-r0*r0 + x*x + y*y+z*z) / mum);

				cGRAD[1][0].setAll((2.*x*x)/mup + (-r0*r0 + x*x + y*y+z*z) / mup, (2.*x*y) / mup, (2.*x*z) / mup);
				cGRAD[1][1].setAll(2.*x*y/mup, 2.*y*y/mup+ (-r0*r0 + x*x + y*y+z*z) / mup, 2*y*z/mup);
				cGRAD[1][2].setAll(2.*x*z/mup, 2*y*z/mup, 2*z*z/mup + (-r0*r0 + x*x + y*y+z*z) / mup);
			}
			double div(FVector_double& p) {
				double x = p[0], y = p[1], z= p[2];
				double r = sqrt(x*x + y*y + z*z);
				double divergence; 
				if (Interface(r) <= 0) {
					divergence = 1. / mum * (5.*x*x + 5.*y*y + 5.*z*z - 3 * r0*r0);
				}
				else {
					divergence = 1. / mup * (5.*x*x + 5.*y*y + 5.*z*z - 3 * r0*r0);
				}
				return divergence;
			}
			void div(FVector_double& p, FVector_double& div) {
				double x = p[0], y = p[1], z= p[2]; 
				double r = sqrt(x*x + y*y + z*z);
				div.setAll(1. / mum * (5.*x*x + 5.*y*y + 5.*z*z - 3 * r0*r0), 1. / mup * (5.*x*x + 5.*y*y + 5.*z*z - 3 * r0*r0));
			}
			void	VF(FVector_double& p, FVector_double& vF) {
				double x = p[0], y = p[1], z= p[2];
				double r = sqrt(x*x + y*y + z*z);
				if (Interface(r) <= r0) {
					vF[0] = (-20.*x - 10.*lambdam / mum*x);
					vF[1] = (-20.*y - 10.*lambdam / mum*y);
					vF[2] = (-20.*z - 10.*lambdam / mum*z);
				}
				if (Interface(r) > 0) {
					vF[0] = (-20.*x - 10.*lambdap / mup*x);
					vF[1] = (-20.*y - 10.*lambdap / mup*y);
					vF[2] = (-20.*z - 10.*lambdap / mum*z);
				}
			}
			void	VF(FVector_double& p, FMatrix_double& mF) {
				double x = p[0], y = p[1], z= p[2];
				double r = sqrt(x*x + y*y + z*z);
				mF[0].setAll(-20.*x - 10.*lambdam / mum*x, -20.*y - 10.*lambdam / mum*y, -20.*z - 10.*lambdam / mum*z);
				mF[1].setAll(-20.*x - 10.*lambdap / mup*x, -20.*y - 10.*lambdap / mup*y, -20.*z - 10.*lambdap / mup*z);

			}
		};
		class P_HOMOGENEOUS_non_interface_3D_GH_ZERO_DIV : public FEM_PROBLEM {
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				//k = 1.;
				//r0 = CV.PI/8.;
				//r0 = 0.5;
				//r0 = 3.;

				dim = __.dim = 3;
				RX = __.RX.make(2, __.dim).setAll(-0.5, -0.5, -0.5, 0.5, 0.5, 0.5);

				double nu;
				//mum = 1.; mup = 2.; r0 = 0.9; alpha = 0.; beta = 0.; lambdam = 99; lambdap = 198;
				//Input("\nView (x,y) direction", VAR.nData[0]>>VAR.nData[1]);
				mu = 1.;
				mum = mu;
				mup = mu;
				r0 =1;
				nu = 5;
			//	Input("Interior mum, lambdam", mum);
			//	Input("Exterior mup, lambdap", mup);
			//	Input("Poisson ratio", nu);
			//	Input("r0", r0);

				lambdam = nu *mum;
				lambdap = nu *mup;
			}

			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1], z= p[2];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}

			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) <= 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}
			double coef_lambda(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1], z= p[2];
				mus.setAll(lambdam, lambdap);              // (Interior, Exterior)
				return 0;
			}
			double coef_lambda(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_lambda(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double coef_lambda(FVector_double& p) {
				static FVector_double mus(2);
				coef_lambda(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) < 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
				return 0.;
			}
			double	Interface(double r) {			// 내부에서 음수의 값을 가지도록 한다.
				return (r - r0);
			}
			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1], z= p[2];
				double r = sqrt(x*x + y*y + z*z);

				return (r - r0);
			}
			void	V(FVector_double& p, FVector_double& v) {
				double x = p[0], y = p[1], z= p[2];
				double r = sqrt(x*x + y*y + z*z);

				if (Interface(r) <= 0) {
					v.setAll(1. / mum*(x*x + y*y +z*z - r0*r0)*(y-z), 1. / mum*(x*x + y*y +z*z - r0*r0)*(z-x), 1. / mum*(x*x + y*y +z*z - r0*r0)*(x-y));
				}
				else {
					v.setAll(1. / mup*(x*x + y*y +z*z - r0*r0)*(y-z), 1. / mup*(x*x + y*y +z*z - r0*r0)*(z-x), 1. / mup*(x*x + y*y +z*z - r0*r0)*(x-y));
				}
			}
			void	V(FVector_double& p, FMatrix_double& mv) {
				double x = p[0], y = p[1], z= p[2];
				double r = sqrt(x*x + y*y + z*z);

				mv.setAll(1. / mum*(x*x + y*y +z*z - r0*r0)*(y-z), 1. / mum*(x*x + y*y +z*z - r0*r0)*(z-x), 1. / mum*(x*x + y*y +z*z - r0*r0)*(x-y),
					1. / mup*(x*x + y*y +z*z - r0*r0)*(y-z), 1. / mup*(x*x + y*y +z*z - r0*r0)*(z-x), 1. / mup*(x*x + y*y +z*z - r0*r0)*(x-y));
			}
			void GRADV(FVector_double& p, FMatrix_double& GRAD) {
				double x = p[0], y = p[1], z= p[2];
				double r = sqrt(x*x + y*y + z*z);
				if (Interface(r) <= 0) {
					GRAD[0].setAll( 2*x*(y-z)/ mum, (2*y*(y-z)-r0*r0+x*x+y*y+z*z )/ mum, ( 2*z*(y - z) + r0*r0 - x*x - y*y - z*z) / mum);
					GRAD[1].setAll((r0*r0 - 2*x*(x - z) - x*x - y*y - z*z)/mum, -2*y*(x - z) / mum, (x*x - r0*r0 - 2*z*(x - z) + y*y + z*z)/mum);
					GRAD[2].setAll((2*x*(x - y) - r0*r0 + x*x + y*y + z*z)/mum, (2*y*(x - y) + r0*r0 - x*x - y*y - z*z)/mum, 2*z*(x - y)/ mum);
				}
				else{
					GRAD[0].setAll( 2*x*(y-z)/ mup, (2*y*(y-z)-r0*r0+x*x+y*y+z*z )/ mup, ( 2*z*(y - z) + r0*r0 - x*x - y*y - z*z) / mup);
					GRAD[1].setAll((r0*r0 - 2*x*(x - z) - x*x - y*y - z*z)/mup, -2*y*(x - z) / mup, (x*x - r0*r0 - 2*z*(x - z) + y*y + z*z)/mup);
					GRAD[2].setAll((2*x*(x - y) - r0*r0 + x*x + y*y + z*z)/mup, (2*y*(x - y) + r0*r0 - x*x - y*y - z*z)/mup, 2*z*(x - y)/ mup);
				}
			}
			void GRADV(FVector_double& p, FCube_double& cGRAD) {
				double x = p[0], y = p[1], z= p[2];
				double r = sqrt(x*x + y*y + z*z);

				cGRAD[0][0].setAll( 2*x*(y-z)/ mum, (2*y*(y-z)-r0*r0+x*x+y*y+z*z )/ mum, ( 2*z*(y - z) + r0*r0 - x*x - y*y - z*z) / mum);
				cGRAD[0][1].setAll((r0*r0 - 2*x*(x - z) - x*x - y*y - z*z)/mum, -2*y*(x - z) / mum, (x*x - r0*r0 - 2*z*(x - z) + y*y + z*z)/mum);
				cGRAD[0][2].setAll((2*x*(x - y) - r0*r0 + x*x + y*y + z*z)/mum, (2*y*(x - y) + r0*r0 - x*x - y*y - z*z)/mum, 2*z*(x - y)/ mum);

				cGRAD[1][0].setAll( 2*x*(y-z)/ mup, (2*y*(y-z)-r0*r0+x*x+y*y+z*z )/ mup, ( 2*z*(y - z) + r0*r0 - x*x - y*y - z*z) / mup);
				cGRAD[1][1].setAll((r0*r0 - 2*x*(x - z) - x*x - y*y - z*z)/mup, -2*y*(x - z) / mup, (x*x - r0*r0 - 2*z*(x - z) + y*y + z*z)/mup);
				cGRAD[1][2].setAll((2*x*(x - y) - r0*r0 + x*x + y*y + z*z)/mup, (2*y*(x - y) + r0*r0 - x*x - y*y - z*z)/mup, 2*z*(x - y)/ mup);
			}
			double div(FVector_double& p) {
				double x = p[0], y = p[1], z= p[2]; 
				 
				return 0.;
			}
			void div(FVector_double& p, FVector_double& div) {
				double x = p[0], y = p[1], z= p[2];  
				div.setAll(0., 0.);
			}
			void	VF(FVector_double& p, FVector_double& vF) {
				double x = p[0], y = p[1], z= p[2];
				double r = sqrt(x*x + y*y + z*z);
				if (Interface(r) <= r0) {
					vF[0] = 10*z - 10*y;
					vF[1] = 10*x - 10*z;
					vF[2] = 10*y - 10*x;
				}
				if (Interface(r) > 0) {
					vF[0] = 10*z - 10*y;
					vF[1] = 10*x - 10*z;
					vF[2] = 10*y - 10*x;
				}
			}
			void	VF(FVector_double& p, FMatrix_double& mF) {
				double x = p[0], y = p[1], z= p[2];
				double r = sqrt(x*x + y*y + z*z);
				mF[0].setAll(10*z - 10*y, 10*x - 10*z, 10*y - 10*x);
				mF[1].setAll(10*z - 10*y, 10*x - 10*z, 10*y - 10*x);

			}
		};
		class P_HOMOGENEOUS_non_interface_3D_GH_ZERO_DIV_EXAMPLE_2: public FEM_PROBLEM {
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				//k = 1.;
				//r0 = CV.PI/8.;
				//r0 = 0.5;
				//r0 = 3.;

				dim = __.dim = 3;
				RX = __.RX.make(2, __.dim).setAll(-0.5, -0.5, -0.5, 0.5, 0.5, 0.5);

				double nu;
				//mum = 1.; mup = 2.; r0 = 0.9; alpha = 0.; beta = 0.; lambdam = 99; lambdap = 198;
				//Input("\nView (x,y) direction", VAR.nData[0]>>VAR.nData[1]);
				mu = 1.;
				mum = mu;
				mup = mu;
				r0 =1;
				nu = 4999;
			//	Input("Interior mum, lambdam", mum);
			//	Input("Exterior mup, lambdap", mup);
			//	Input("Poisson ratio", nu);
			//	Input("r0", r0);

				lambdam = nu *mum;
				lambdap = nu *mup;
			}

			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1], z= p[2];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}

			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) <= 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}
			double coef_lambda(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1], z= p[2];
				mus.setAll(lambdam, lambdap);              // (Interior, Exterior)
				return 0;
			}
			double coef_lambda(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_lambda(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double coef_lambda(FVector_double& p) {
				static FVector_double mus(2);
				coef_lambda(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) < 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
				return 0.;
			}
			double	Interface(double r) {			// 내부에서 음수의 값을 가지도록 한다.
				return (r - r0);
			}
			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1], z= p[2];
				double r = sqrt(x*x + y*y + z*z);

				return (r - r0);
			}
			void	V(FVector_double& p, FVector_double& v) {
				double x = p[0], y = p[1], z= p[2];
				double r = sqrt(x*x + y*y + z*z);
				if (Interface(r) <= 0) {
					v.setAll(1./ mum* (x*z*sin(x + y + z) - x*y*sin(x + y + z)), 1./ mum*(x*y*sin(x + y + z) - y*z*sin(x + y + z)), 1./mum*(y*z*sin(x + y + z) - x*z*sin(x + y + z)));
				}
				else {
					v.setAll(1./ mup* (x*z*sin(x + y + z) - x*y*sin(x + y + z)), 1./ mup*(x*y*sin(x + y + z) - y*z*sin(x + y + z)), 1./mup*(y*z*sin(x + y + z) - x*z*sin(x + y + z)));
				}
			}
			void	V(FVector_double& p, FMatrix_double& mv) {
				double x = p[0], y = p[1], z= p[2];
				double r = sqrt(x*x + y*y + z*z);

				mv.setAll(1./ mum* (x*z*sin(x + y + z) - x*y*sin(x + y + z)), 1./ mum*(x*y*sin(x + y + z) - y*z*sin(x + y + z)), 1./mum*(y*z*sin(x + y + z) - x*z*sin(x + y + z)),
						1./ mup* (x*z*sin(x + y + z) - x*y*sin(x + y + z)), 1./ mup*(x*y*sin(x + y + z) - y*z*sin(x + y + z)), 1./mup*(y*z*sin(x + y + z) - x*z*sin(x + y + z)));
			}
			void GRADV(FVector_double& p, FMatrix_double& GRAD) {
				double x = p[0], y = p[1], z= p[2];
				double r = sqrt(x*x + y*y + z*z);
				if (Interface(r) <= 0) {
					GRAD[0][0]=-(sin(x + y + z) + x*cos(x + y + z))*(y - z);
					GRAD[0][1]=-x*(sin(x + y + z) + y*cos(x + y + z) - z*cos(x + y + z));
					GRAD[0][2]=x*(sin(x + y + z) - y*cos(x + y + z) + z*cos(x + y + z));

					GRAD[1][0]=y*sin(x + y + z) + x*y*cos(x + y + z) - y*z*cos(x + y + z);
					GRAD[1][1]=(sin(x + y + z) + y*cos(x + y + z))*(x - z);
					GRAD[1][2]=-y*(sin(x + y + z) - x*cos(x + y + z) + z*cos(x + y + z));

					GRAD[2][0]=-z*(sin(x + y + z) + x*cos(x + y + z) - y*cos(x + y + z));
					GRAD[2][1]=z*(sin(x + y + z) - x*cos(x + y + z) + y*cos(x + y + z));
					GRAD[2][2]=-(sin(x + y + z) + z*cos(x + y + z))*(x - y);

				}
				else{
					GRAD[0][0]=-(sin(x + y + z) + x*cos(x + y + z))*(y - z);
					GRAD[0][1]=-x*(sin(x + y + z) + y*cos(x + y + z) - z*cos(x + y + z));
					GRAD[0][2]=x*(sin(x + y + z) - y*cos(x + y + z) + z*cos(x + y + z));

					GRAD[1][0]=y*sin(x + y + z) + x*y*cos(x + y + z) - y*z*cos(x + y + z);
					GRAD[1][1]=(sin(x + y + z) + y*cos(x + y + z))*(x - z);
					GRAD[1][2]=-y*(sin(x + y + z) - x*cos(x + y + z) + z*cos(x + y + z));

					GRAD[2][0]=-z*(sin(x + y + z) + x*cos(x + y + z) - y*cos(x + y + z));
					GRAD[2][1]=z*(sin(x + y + z) - x*cos(x + y + z) + y*cos(x + y + z));
					GRAD[2][2]=-(sin(x + y + z) + z*cos(x + y + z))*(x - y);
				}
			}
			void GRADV(FVector_double& p, FCube_double& cGRAD) {
				double x = p[0], y = p[1], z= p[2];
				double r = sqrt(x*x + y*y + z*z);
				 
				cGRAD[0][0][0]=-(sin(x + y + z) + x*cos(x + y + z))*(y - z);
				cGRAD[0][0][1]=-x*(sin(x + y + z) + y*cos(x + y + z) - z*cos(x + y + z));
				cGRAD[0][0][2]=x*(sin(x + y + z) - y*cos(x + y + z) + z*cos(x + y + z));

				cGRAD[0][1][0]=y*sin(x + y + z) + x*y*cos(x + y + z) - y*z*cos(x + y + z);
				cGRAD[0][1][1]=(sin(x + y + z) + y*cos(x + y + z))*(x - z);
				cGRAD[0][1][2]=-y*(sin(x + y + z) - x*cos(x + y + z) + z*cos(x + y + z));

				cGRAD[0][2][0]=-z*(sin(x + y + z) + x*cos(x + y + z) - y*cos(x + y + z));
				cGRAD[0][2][1]=z*(sin(x + y + z) - x*cos(x + y + z) + y*cos(x + y + z));
				cGRAD[0][2][2]=-(sin(x + y + z) + z*cos(x + y + z))*(x - y);

				cGRAD[1][0][0]=-(sin(x + y + z) + x*cos(x + y + z))*(y - z);
				cGRAD[1][0][1]=-x*(sin(x + y + z) + y*cos(x + y + z) - z*cos(x + y + z));
				cGRAD[1][0][2]=x*(sin(x + y + z) - y*cos(x + y + z) + z*cos(x + y + z));

				cGRAD[1][1][0]=y*sin(x + y + z) + x*y*cos(x + y + z) - y*z*cos(x + y + z);
				cGRAD[1][1][1]=(sin(x + y + z) + y*cos(x + y + z))*(x - z);
				cGRAD[1][1][2]=-y*(sin(x + y + z) - x*cos(x + y + z) + z*cos(x + y + z));

				cGRAD[1][2][0]=-z*(sin(x + y + z) + x*cos(x + y + z) - y*cos(x + y + z));
				cGRAD[1][2][1]=z*(sin(x + y + z) - x*cos(x + y + z) + y*cos(x + y + z));
				cGRAD[1][2][2]=-(sin(x + y + z) + z*cos(x + y + z))*(x - y);
			}
			double div(FVector_double& p) {
				double x = p[0], y = p[1], z= p[2]; 
				 
				return 0.;
			}
			void div(FVector_double& p, FVector_double& div) {
				double x = p[0], y = p[1], z= p[2];  
				div.setAll(0., 0.);
			}
			void	VF(FVector_double& p, FVector_double& vF) {
				double x = p[0], y = p[1], z= p[2];
				double r = sqrt(x*x + y*y + z*z);
				if (Interface(r) <= r0) { 
					vF[0] = (2*cos(x + y + z) - 3*x*sin(x + y + z))*(y - z);
					vF[1] = -(2*cos(x + y + z) - 3*y*sin(x + y + z))*(x - z);
					vF[2] = (2*cos(x + y + z) - 3*z*sin(x + y + z))*(x - y);
				}
				if (Interface(r) > 0) {
					vF[0] = (2*cos(x + y + z) - 3*x*sin(x + y + z))*(y - z);
					vF[1] = -(2*cos(x + y + z) - 3*y*sin(x + y + z))*(x - z);
					vF[2] = (2*cos(x + y + z) - 3*z*sin(x + y + z))*(x - y);
				}
			}
			void	VF(FVector_double& p, FMatrix_double& mF) {
				double x = p[0], y = p[1], z= p[2];
				double r = sqrt(x*x + y*y + z*z);
				mF[0][0]=(2*cos(x + y + z) - 3*x*sin(x + y + z))*(y - z);
				mF[0][1]=-(2*cos(x + y + z) - 3*y*sin(x + y + z))*(x - z);
				mF[0][2]=(2*cos(x + y + z) - 3*z*sin(x + y + z))*(x - y);

				mF[1][0]=(2*cos(x + y + z) - 3*x*sin(x + y + z))*(y - z);
				mF[1][1]=-(2*cos(x + y + z) - 3*y*sin(x + y + z))*(x - z);
				mF[1][2]=(2*cos(x + y + z) - 3*z*sin(x + y + z))*(x - y);

			}
		};
		class P_HOMOGENEOUS_3D_CLOSED_DRIVEN_CAVITY: public FEM_PROBLEM {
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				//k = 1.;
				//r0 = CV.PI/8.;
				//r0 = 0.5;
				//r0 = 3.; 
				dim = __.dim = 3;
				RX = __.RX.make(2, __.dim).setAll(-1., -1., -1., 1., 1., 1.); 
				//mum = 1.; mup = 2.; r0 = 0.9; alpha = 0.; beta = 0.; lambdam = 99; lambdap = 198;
				//Input("\nView (x,y) direction", VAR.nData[0]>>VAR.nData[1]);
				mu = 1.;
				mum = mu;
				mup = mu;
				r0 = 4;
				nu = 49;
		 
				lambdam = nu *mum;
				lambdap = nu *mup;
			}

			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1], z= p[2];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			} 
			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) <= 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}
			double coef_lambda(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1], z= p[2];
				mus.setAll(lambdam, lambdap);              // (Interior, Exterior)
				return 0;
			}
			double coef_lambda(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_lambda(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double coef_lambda(FVector_double& p) {
				static FVector_double mus(2);
				coef_lambda(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) < 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
				return 0.;
			}
			double	Interface(double r) {			// 내부에서 음수의 값을 가지도록 한다.
				return (r - r0);
			}
			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1], z= p[2];
				double r = sqrt(x*x + y*y + z*z);

				return (r - r0);
			}
			void	V(FVector_double& p, FVector_double& v) {
				double x = p[0], y = p[1], z= p[2];
				double r = sqrt(x*x + y*y + z*z);
				if (z==1) {
					v.setAll(1., 0., 0.);
				}
				if (x==-1) {
					v.clear();
				}
				if (x==1) {
					v.clear();
				}
				if (y==-1) {
					v.clear();
				}
				if (y==1) {
					v.clear();
				}
				if (z==-1) {
					v.clear();
				}

			}
			void	V(FVector_double& p, FMatrix_double& mv) {
				double x = p[0], y = p[1], z= p[2];
				double r = sqrt(x*x + y*y + z*z);

				if (z==1) {
					mv[0].setAll(1., 0., 0.);
					mv[1].setAll(1., 0., 0.);
				}
				if (x==-1) {
					mv.clear();
				}
				if (x==1) {
					mv.clear();
				}
				if (y==-1) {
					mv.clear();
				}
				if (y==1) {
					mv.clear();
				}
				if (z==-1) {
					mv.clear();
				}
			}
			void GRADV(FVector_double& p, FMatrix_double& GRAD) {
				double x = p[0], y = p[1], z= p[2];
				double r = sqrt(x*x + y*y + z*z);
				GRAD.clear();
			}
			void GRADV(FVector_double& p, FCube_double& cGRAD) {
				double x = p[0], y = p[1], z= p[2];
				double r = sqrt(x*x + y*y + z*z);
				 
				cGRAD.clear();
			}
			double div(FVector_double& p) {
				double x = p[0], y = p[1], z= p[2]; 
				 
				return 0.;
			}
			void div(FVector_double& p, FVector_double& div) {
				double x = p[0], y = p[1], z= p[2];  
				div.setAll(0., 0.);
			}
			void	VF(FVector_double& p, FVector_double& vF) {
				double x = p[0], y = p[1], z= p[2];
				double r = sqrt(x*x + y*y + z*z);
				vF.clear();
			}
			void	VF(FVector_double& p, FMatrix_double& mF) {
				double x = p[0], y = p[1], z= p[2];
				double r = sqrt(x*x + y*y + z*z);
				mF.clear();

			}
		};
		class P_HOMOGENEOUS_KWAK_Epsilon_2: public FEM_PROBLEM {	
		public:
			void	initialize	(FEM_VARIABLES::ENTIRE& __) {
				alpha = 0.; beta = 0.;
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll( -2., -2., 2.,2.);
				double nu;

				//Input("\nView (x,y) direction", VAR.nData[0]>>VAR.nData[1]);
				Input("Interior mum, lambdam", mum);
				Input("Exterior mup, lambdap", mup);
				Input("Poisson ratio", nu);
				Input("r0", r0);
				lambdam = nu *mum;
				lambdap = nu *mup;
			}
			
			double	coef_mu		(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}

			double	coef_mu		(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if(Interface(p) <= 0) {
					return mus[0];
				} else { 
					return mus[1];
				}
			}
			double coef_lambda  (FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(lambdam, lambdap);              // (Interior, Exterior)
				return 0;
			}
			double coef_lambda (FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_lambda(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.

				if(io == CV.IN) return mus[0];
				return mus[1];
			}
			double coef_lambda  (FVector_double& p) {
				static FVector_double mus(2);
				coef_lambda(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.

				if(Interface(p) < 0) {
					return mus[0];
				} 
				else { 
					return mus[1];
				}
				return 0.;
			}
			double	Interface	(double r) {			// 내부에서 음수의 값을 가지도록 한다.
				return (r - r0);
			}

			double	Interface	(FVector_double& p) {
				double x=p[0], y=p[1];
				double r = (x*x/4. + y*y);

				return (r - r0*r0);
			}
			
			void	V			(FVector_double& p, FVector_double& v) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x/4. + y*y);
				
				if(Interface(r) <= 0) {
					v.setAll(1./mum*(x*x/4. + y*y - r0*r0)*x, 1./mum*(x*x/4.+y*y-r0*r0)*y);
				} else { 
					v.setAll(1./mup*(x*x/4. + y*y - r0*r0)*x, 1./mup*(x*x/4.+y*y-r0*r0)*y);
				}
			}
			void	V			(FVector_double& p, FMatrix_double& mv) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				
				mv.setAll(1./mum*(x*x/4. + y*y - r0*r0)*x, 1./mum*(x*x/4.+y*y-r0*r0)*y,
				        1./mup*(x*x/4. + y*y - r0*r0)*x, 1./mup*(x*x/4.+y*y-r0*r0)*y);
			}
			
			void GRADV			(FVector_double& p, FMatrix_double& GRAD) {
				double x= p[0], y= p[1];
				double r=sqrt(x*x/4. + y*y);
				if(Interface(r) <= 0) {
					GRAD.setAll((x*x)/mum/2. + (- r0*r0 + x*x/4. + y*y)/mum, (2.*x*y)/mum, (x*y)/mum/2., (2.*y*y)/mum + (- r0*r0 + x*x/4. + y*y)/mum);
				} else{
					GRAD.setAll((x*x)/mup/2. + (- r0*r0 + x*x/4. + y*y)/mup, (2.*x*y)/mup, (x*y)/mup/2., (2.*y*y)/mup + (- r0*r0 + x*x/4. + y*y)/mup);
				}
			}

			void GRADV			(FVector_double& p, FCube_double& cGRAD) {
				double x= p[0], y= p[1];
				double r=sqrt(x*x + y*y);
					cGRAD[0].setAll((x*x)/mum/2. + (- r0*r0 + x*x/4. + y*y)/mum, (2.*x*y)/mum, (x*y)/mum/2., (2.*y*y)/mum + (- r0*r0 + x*x/4. + y*y)/mum);
					cGRAD[1].setAll((x*x)/mup/2. + (- r0*r0 + x*x/4. + y*y)/mup, (2.*x*y)/mup, (x*y)/mup/2., (2.*y*y)/mup + (- r0*r0 + x*x/4. + y*y)/mup);
			}
		
			double div			(FVector_double& p) {
				double x = p[0], y=p[1];
				double divergence;
				double r = sqrt(x*x/4. + y*y);
				if(Interface(r) <= 0 ) {
					divergence = 1./mum * (x*x + 4.*y*y - 2*r0*r0);
				} else {
					divergence = 1./mup * (x*x + 4.*y*y - 2*r0*r0);
				}
			return divergence;
			}

			void div			(FVector_double& p, FVector_double& div) {
				double x = p[0], y=p[1];
				double r = sqrt(x*x + y*y);
				div.setAll(1./mum * (x*x + 4.*y*y - 2*r0*r0),1./mup * (x*x + 4.*y*y - 2*r0*r0));
			}
			
			void	VF			(FVector_double& p, FVector_double& vF) {
				double x=p[0], y=p[1];
				double r = sqrt(x*x/4. + y*y);
			
				if(Interface(r) <= 0) {
				vF[0] = (-11./4.*x - lambdam/mum*x)*2;
				vF[1] = (-29./4.*y - 4.*lambdam/mum*y)*2;
				}
				if(Interface(r) > 0) {
				vF[0] = (-11./4.*x - lambdap/mup*x)*2;
				vF[1] = (-29./4.*y - 4.*lambdap/mup*y)*2;
				}
			}
			void	VF			(FVector_double& p, FMatrix_double& mF) {
				double x=p[0], y=p[1];
				mF.setAll((-11./4.*x - lambdam/mum*x)*2,(-29./4.*y - 4.*lambdam/mum*y)*2,
					      (-11./4.*x - lambdap/mup*x)*2,(-29./4.*y - 4.*lambdap/mup*y)*2);
			}
		};
		class TEST_LINEAR: public FEM_PROBLEM {	
		public:
			void	initialize	(FEM_VARIABLES::ENTIRE& __) {
				//k = 1.;
				r0 = 0.48;

				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll( -1., -1., 1.,1.);

				//Input("\nView (x,y) direction", VAR.nData[0]>>VAR.nData[1]);
				Input("\nInterior mum, lambdam", mum);
				Input("Exterior mup, lambdap", mup);
				lambdam = mum;
				lambdap = mup;
			}
			
			double	coef_mu		(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}

			double	coef_mu		(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if(Interface(p) <= 0) {
					return mus[0];
				} else { 
					return mus[1];
				}
			}

			double	Interface	(double r) {			// 내부에서 음수의 값을 가지도록 한다.
				return (r - r0);
			}

			double	Interface	(FVector_double& p) {
				double x=p[0], y=p[1];
				double r = sqrt(x*x + y*y);

				return (r - r0);
			}

			void	V			(FVector_double& p, FVector_double& v) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				
				if(Interface(r) <= 0) {
					v.setAll(x,y);
				} else { 
					v.setAll(x,y);
				}
			}
			void	V			(FVector_double& p, FMatrix_double& mv) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				
				mv.setAll(x,y,
				          x,y);
			}
			void GRADV			(FVector_double& p, FMatrix_double& GRAD) {
				double x= p[0], y= p[1];
				double r=sqrt(x*x + y*y);
				if(Interface(r) <= 0) {
					GRAD.setAll(1., 0., 0., 1.);
				} else{
					GRAD.setAll(1., 0., 0., 1.);
				}
			}
			void GRADV			(FVector_double& p, FCube_double& cGRAD) {
				double x= p[0], y= p[1];
				double r=sqrt(x*x + y*y);
					cGRAD[0].setAll(1., 0., 0., 1.);
					cGRAD[1].setAll(1., 0., 0., 1.);
			}
		
			double div			(FVector_double& p) {
				double x = p[0], y=p[1];
				double divergence;
				double r = sqrt(x*x + y*y);
				if(Interface(r) <= 0 ) {
					divergence = 2.;
				} else {
					divergence = 2.;
				}
			return divergence;
			}
				
			void div			(FVector_double& p, FVector_double& div) {
				double x = p[0], y=p[1];
				double r = sqrt(x*x + y*y);
				div.setAll(2.,2.);
			}
			
			void	VF			(FVector_double& p, FVector_double& vF) {
				double x=p[0], y=p[1];
				double r = sqrt(x*x + y*y);
				if(Interface(r) <= 0) {
				vF[0] = 0.;
				vF[1] = 0.;
				}
				if(Interface(r) > 0) {
				vF[0] = 0.;
				vF[1] = 0.;
				}
			}
			
			void	VF			(FVector_double& p, FMatrix_double& mF) {
				double x=p[0], y=p[1];
				mF.setAll(0., 0.,
						  0., 0.);
			}
		};
		class P_HOMOGENEOUS_KYEONG_ZERO_EXAMPLE: public FEM_PROBLEM {	
		public:
			void	initialize	(FEM_VARIABLES::ENTIRE& __) {
				
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll( -1., -1., 1.,1.);
				double nu;
				Input("Interior mum, lambdam", mum);
				Input("Exterior mup, lambdap", mup);
				Input("Poisson ratio", nu);
				Input("r0", r0);
				lambdam = nu *mum;
				lambdap = nu *mup;
			}
			
			double	coef_mu		(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}

			double	coef_mu		(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if(Interface(p) <= 0) {
					return mus[0];
				} else { 
					return mus[1];
				}
			}
			double coef_lambda  (FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(lambdam, lambdap);              // (Interior, Exterior)
				return 0;
			}
			double coef_lambda (FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_lambda(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.

				if(io == CV.IN) return mus[0];
				return mus[1];
			}
			double coef_lambda  (FVector_double& p) {
				static FVector_double mus(2);
				coef_lambda(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.

				if(Interface(p) < 0) {
					return mus[0];
				} 
				else { 
					return mus[1];
				}
				return 0.;
			}
			double	Interface	(double r) {			// 내부에서 음수의 값을 가지도록 한다.
				return (r - r0);
			}
			double	Interface	(FVector_double& p) {
				double x=p[0], y=p[1];
				double r = sqrt(x*x + y*y);

				return (r - r0);
			}
			void	V			(FVector_double& p, FVector_double& v) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				
				if(Interface(r) <= 0) {
					v.setAll(0., 0.);
				} else { 
					v.setAll(0., 0.);
				}
			}
			void	V			(FVector_double& p, FMatrix_double& mv) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				
				mv.setAll(0., 0.,
				          0., 0.);
			}
			void GRADV			(FVector_double& p, FMatrix_double& GRAD) {
				double x= p[0], y= p[1];
				double r=sqrt(x*x + y*y);
				if(Interface(r) <= 0) {
					GRAD.setAll(0., 0., 0., 0.);
				} else{
					GRAD.setAll(0., 0., 0., 0.);
				}
			}
			void GRADV			(FVector_double& p, FCube_double& cGRAD) {
				double x= p[0], y= p[1];
				double r=sqrt(x*x + y*y);
					cGRAD[0].setAll(0., 0., 0., 0.);
					cGRAD[1].setAll(0., 0., 0., 0.);
			}
			double div			(FVector_double& p) {
				double x = p[0], y=p[1];
				double divergence;
				double r = sqrt(x*x + y*y);
				if(Interface(r) <= 0 ) {
					divergence = 0.;
				} else {
					divergence = 0.;
				}
			return divergence;
			}
			void div			(FVector_double& p, FVector_double& div) {
				double x = p[0], y=p[1];
				double r = sqrt(x*x + y*y);
				div.setAll(0.,0.);
			}
			void	VF			(FVector_double& p, FVector_double& vF) {
				double x=p[0], y=p[1];
				double r = sqrt(x*x + y*y);
				if(Interface(r) <= 0) {
				vF[0] = 0.;
				vF[1] = 0.;
				}
				if(Interface(r) > 0) {
				vF[0] = 0.;
				vF[1] = 0.;
				}
			}
			void	VF			(FVector_double& p, FMatrix_double& mF) {
				double x=p[0], y=p[1];
				double r = sqrt(x*x + y*y);
				mF.setAll(0., 0.,
				          0., 0.);
			}
		};
		class P_HOMOGENEOUS_KWAK_CURVE_INTERFACE: public FEM_PROBLEM {	
		public:
			void	initialize	(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll( -1., -1., 1.,1.);
				double nu;
				nu = 0.4;
				Input("Interior mum, lambdam", mum);
				Input("Exterior mup, lambdap", mup);
				lambdam = mum*(2*nu/(1-2*nu));
				lambdap = mup*(2*nu/(1-2*nu));
			}	
			
			double	coef_mu		(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}

			double	coef_mu		(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if(Interface(p) <= 0) {
					return mus[0];
				} else { 
					return mus[1];
				}
			}
			double coef_lambda  (FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(lambdam, lambdap);              // (Interior, Exterior)
				return 0;
			}
			double coef_lambda (FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_lambda(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.

				if(io == CV.IN) return mus[0];
				return mus[1];
			}
			double coef_lambda  (FVector_double& p) {
				static FVector_double mus(2);
				coef_lambda(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.

				if(Interface(p) < 0) {
					return mus[0];
				} 
				else { 
					return mus[1];
				}
				return 0.;
			}
			double	Interface	(FVector_double& p) {
				double x=p[0], y=p[1];
				return y-x*x*x/3.-0.2;
			}
			void	V			(FVector_double& p, FVector_double& v) {
				double x = p[0], y = p[1];
				
				if(Interface(p) <= 0) {
					v.setAll(1./mum*(y-x*x*x/3.-0.2), 1./mum*(y-x*x*x/3.-0.2));
				} else { 
					v.setAll(1./mup*(y-x*x*x/3.-0.2), 1./mup*(y-x*x*x/3.-0.2));
				}
			}
			void  V				(FVector_double& p, FMatrix_double& v)
			{
				double x = p[0], y = p[1];
				v.setAll(1./mum*(y-x*x*x/3.-0.2), 1./mum*(y-x*x*x/3.-0.2),
						1./mup*(y-x*x*x/3.-0.2), 1./mup*(y-x*x*x/3.-0.2));
			}
			void GRADV			(FVector_double& p, FMatrix_double& GRAD) {
				double x= p[0], y= p[1];
				double r=sqrt(x*x + y*y);
				if(Interface(p) <= 0) {
					GRAD.setAll(-x*x/mum, 1/mum, -x*x/mum, 1/mum);
				} else{
					GRAD.setAll(-x*x/mup, 1/mup, -x*x/mup, 1/mup);
				}
			}
			void GRADV			(FVector_double& p, FCube_double& cGRAD) {
				double x= p[0], y= p[1];
				double r=sqrt(x*x + y*y);
					cGRAD[0].setAll(-x*x/mum, 1/mum, -x*x/mum, 1/mum);
					cGRAD[1].setAll(-x*x/mup, 1/mup, -x*x/mup, 1/mup);
			}
		
			double div			(FVector_double& p) {
				double x = p[0], y=p[1];
				double divergence;
				if(Interface(p) <= 0 ) {
					divergence = 1./mum * (1-x*x);
				} else {
					divergence = 1./mup * (1-x*x);
				}
			return divergence;
			}
					
			void div			(FVector_double& p, FVector_double& div) {
				double x = p[0], y=p[1];
				double r = sqrt(x*x + y*y);
				div.setAll( 1./mum * (1-x*x),1./mup * (1-x*x));
			}
		
			void	VF			(FVector_double& p, FVector_double& vF) {
				double x=p[0], y=p[1];
				if(Interface(p) <= 0) {
				vF[0] = 2.*x*(2.+lambdam/mum);
				vF[1] = 2.*x;
				}
				if(Interface(p) > 0) {
				vF[0] = 2.*x*(2.+lambdap/mup);
				vF[1] = 2.*x;
				}
			}
			void	VF			(FVector_double& p, FMatrix_double& mF) {
				double x=p[0], y=p[1];
				mF.setAll(2.*x*(2.+lambdam/mum), 2.*x,
						  2.*x*(2.+lambdap/mup), 2.*x);
			}
		};
		class P_HOMOGENEOUS_Peanut: public FEM_PROBLEM {	
		public:
			void	initialize	(FEM_VARIABLES::ENTIRE& __) {
			
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll( -1., -1., 1., 1.);
				double nu;

				//Input("\nView (x,y) direction", VAR.nData[0]>>VAR.nData[1]);
				Input("\nInterior mum, lambdam", mum);
				Input("Exterior mup, lambdap", mup);
				Input("Poisson ratio", nu);
				Input("r0 ", r0);
				lambdam = nu *mum;
				lambdap = nu *mup;
			}
			
			double	coef_mu		(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}

			double	coef_mu		(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if(Interface(p) <= 0) {
					return mus[0];
				} else { 
					return mus[1];
				}
			}

			double	Interface	(double r) {			// 내부에서 음수의 값을 가지도록 한다.
				return (r - r0);
			}

			double	Interface	(FVector_double& p) {
				double x=p[0], y=p[1];
				return (8.*x*x*x*x - 4.*x*x + y*y - r0);
			}
			
			void	V			(FVector_double& p, FVector_double& v) {
				double x = p[0], y = p[1];
				double r = (8.*x*x*x*x - 4.*x*x + y*y);
				
				if(Interface(r) <= 0) {
					v.setAll(pow(0.8e1 * pow(x, 0.4e1) - 0.4e1 * x * x + y * y - r0, 0.2e1) * x * y / mum, pow(0.8e1 * pow(x, 0.4e1) - 0.4e1 * x * x + y * y - r0, 0.2e1) / mum);
				} else { 
					v.setAll(pow(0.8e1 * pow(x, 0.4e1) - 0.4e1 * x * x + y * y - r0, 0.2e1) * x * y / mup, pow(0.8e1 * pow(x, 0.4e1) - 0.4e1 * x * x + y * y - r0, 0.2e1) / mup);
				}
			}
			void  V				(FVector_double& p, FMatrix_double& v)
			{
				double x = p[0], y = p[1];
				double r = (8.*x*x*x*x - 4.*x*x + y*y);
				v.setAll(pow(0.8e1 * pow(x, 0.4e1) - 0.4e1 * x * x + y * y - r0, 0.2e1) * x * y / mum, pow(0.8e1 * pow(x, 0.4e1) - 0.4e1 * x * x + y * y - r0, 0.2e1) / mum,
						pow(0.8e1 * pow(x, 0.4e1) - 0.4e1 * x * x + y * y - r0, 0.2e1) * x * y / mup, pow(0.8e1 * pow(x, 0.4e1) - 0.4e1 * x * x + y * y - r0, 0.2e1) / mup);
			}
						
			void GRADV			(FVector_double& p, FMatrix_double& GRAD) {
				double x= p[0], y= p[1];
				double r = (2.*x*2.*x*2.*x*2.*x/2. - 2.*x*2.*x+ y*y);
				if(Interface(r) <= 0) {
					GRAD.setAll(0.2e1 * (0.8e1 * pow(x, 0.4e1) - 0.4e1 * x * x + y * y - r0) * x * y / mum * (0.32e2 * pow(x, 0.3e1) - 0.8e1 * x) + pow(0.8e1 * pow(x, 0.4e1) - 0.4e1 * x * x + y * y - r0, 0.2e1) * y / mum, 0.4e1 * (0.8e1 * pow(x, 0.4e1) - 0.4e1 * x * x + y * y - r0) * x * y * y / mum + pow(0.8e1 * pow(x, 0.4e1) - 0.4e1 * x * x + y * y - r0, 0.2e1) * x / mum, 0.2e1 * (0.8e1 * pow(x, 0.4e1) - 0.4e1 * x * x + y * y - r0) / mum * (0.32e2 * pow(x, 0.3e1) - 0.8e1 * x), 0.4e1 * (0.8e1 * pow(x, 0.4e1) - 0.4e1 * x * x + y * y - r0) / mum * y);
				} else{
					GRAD.setAll(0.2e1 * (0.8e1 * pow(x, 0.4e1) - 0.4e1 * x * x + y * y - r0) * x * y / mup * (0.32e2 * pow(x, 0.3e1) - 0.8e1 * x) + pow(0.8e1 * pow(x, 0.4e1) - 0.4e1 * x * x + y * y - r0, 0.2e1) * y / mup, 0.4e1 * (0.8e1 * pow(x, 0.4e1) - 0.4e1 * x * x + y * y - r0) * x * y * y / mup + pow(0.8e1 * pow(x, 0.4e1) - 0.4e1 * x * x + y * y - r0, 0.2e1) * x / mup, 0.2e1 * (0.8e1 * pow(x, 0.4e1) - 0.4e1 * x * x + y * y - r0) / mup * (0.32e2 * pow(x, 0.3e1) - 0.8e1 * x), 0.4e1 * (0.8e1 * pow(x, 0.4e1) - 0.4e1 * x * x + y * y - r0) / mup * y);
				}
			}
			void GRADV			(FVector_double& p, FCube_double& cGRAD) {
				double x= p[0], y= p[1];
				double r = (2.*x*2.*x*2.*x*2.*x/2. - 2.*x*2.*x+ y*y);
				cGRAD[0].setAll(0.2e1 * (0.8e1 * pow(x, 0.4e1) - 0.4e1 * x * x + y * y - r0) * x * y / mum * (0.32e2 * pow(x, 0.3e1) - 0.8e1 * x) + pow(0.8e1 * pow(x, 0.4e1) - 0.4e1 * x * x + y * y - r0, 0.2e1) * y / mum, 0.4e1 * (0.8e1 * pow(x, 0.4e1) - 0.4e1 * x * x + y * y - r0) * x * y * y / mum + pow(0.8e1 * pow(x, 0.4e1) - 0.4e1 * x * x + y * y - r0, 0.2e1) * x / mum, 0.2e1 * (0.8e1 * pow(x, 0.4e1) - 0.4e1 * x * x + y * y - r0) / mum * (0.32e2 * pow(x, 0.3e1) - 0.8e1 * x), 0.4e1 * (0.8e1 * pow(x, 0.4e1) - 0.4e1 * x * x + y * y - r0) / mum * y);
				cGRAD[1].setAll(0.2e1 * (0.8e1 * pow(x, 0.4e1) - 0.4e1 * x * x + y * y - r0) * x * y / mup * (0.32e2 * pow(x, 0.3e1) - 0.8e1 * x) + pow(0.8e1 * pow(x, 0.4e1) - 0.4e1 * x * x + y * y - r0, 0.2e1) * y / mup, 0.4e1 * (0.8e1 * pow(x, 0.4e1) - 0.4e1 * x * x + y * y - r0) * x * y * y / mup + pow(0.8e1 * pow(x, 0.4e1) - 0.4e1 * x * x + y * y - r0, 0.2e1) * x / mup, 0.2e1 * (0.8e1 * pow(x, 0.4e1) - 0.4e1 * x * x + y * y - r0) / mup * (0.32e2 * pow(x, 0.3e1) - 0.8e1 * x), 0.4e1 * (0.8e1 * pow(x, 0.4e1) - 0.4e1 * x * x + y * y - r0) / mup * y);
			}
		
			double div			(FVector_double& p) {
				double x = p[0], y=p[1];
				double divergence;
				double r = (2.*x*2.*x*2.*x*2.*x/2. - 2.*x*2.*x+ y*y);
				if(Interface(r) <= 0 ) {
					divergence = 0.2e1 * (0.8e1 * pow(x, 0.4e1) - 0.4e1 * x * x + y * y - r0) * x * y / mum * (0.32e2 * pow(x, 0.3e1) - 0.8e1 * x) + pow(0.8e1 * pow(x, 0.4e1) - 0.4e1 * x * x + y * y - r0, 0.2e1) * y / mum + 0.4e1 * (0.8e1 * pow(x, 0.4e1) - 0.4e1 * x * x + y * y - r0) / mum * y;
				} else {
					divergence = 0.2e1 * (0.8e1 * pow(x, 0.4e1) - 0.4e1 * x * x + y * y - r0) * x * y / mup * (0.32e2 * pow(x, 0.3e1) - 0.8e1 * x) + pow(0.8e1 * pow(x, 0.4e1) - 0.4e1 * x * x + y * y - r0, 0.2e1) * y / mup + 0.4e1 * (0.8e1 * pow(x, 0.4e1) - 0.4e1 * x * x + y * y - r0) / mup * y;
				}
				return divergence;
			}

			void div			(FVector_double& p, FVector_double& div) {
				double x = p[0], y=p[1];
				double r = (2.*x*2.*x*2.*x*2.*x/2. - 2.*x*2.*x+ y*y);
				div.setAll(0.2e1 * (0.8e1 * pow(x, 0.4e1) - 0.4e1 * x * x + y * y - r0) * x * y / mum * (0.32e2 * pow(x, 0.3e1) - 0.8e1 * x) + pow(0.8e1 * pow(x, 0.4e1) - 0.4e1 * x * x + y * y - r0, 0.2e1) * y / mum + 0.4e1 * (0.8e1 * pow(x, 0.4e1) - 0.4e1 * x * x + y * y - r0) / mum * y,0.2e1 * (0.8e1 * pow(x, 0.4e1) - 0.4e1 * x * x + y * y - r0) * x * y / mup * (0.32e2 * pow(x, 0.3e1) - 0.8e1 * x) + pow(0.8e1 * pow(x, 0.4e1) - 0.4e1 * x * x + y * y - r0, 0.2e1) * y / mup + 0.4e1 * (0.8e1 * pow(x, 0.4e1) - 0.4e1 * x * x + y * y - r0) / mup * y);
			}
		
			void	VF			(FVector_double& p, FVector_double& vF) {
				double x=p[0], y=p[1];
				double  r = (2.*x*2.*x*2.*x*2.*x/2. - 2.*x*2.*x+ y*y);
				if(Interface(r) <= 0) {
				vF[0] = 2.*(0.16e2 * x * y * (-0.288e3 * pow(x, 0.6e1) + 0.168e3 * pow(x, 0.4e1) - 0.20e2 * x * x - 0.20e2 * y * y * x * x + 0.3e1 * y * y + 0.20e2 * r0 * x * x - 0.3e1 * r0) + 0.8e1 * lambdam / mum * x * y * (-0.288e3 * pow(x, 0.6e1) + 0.168e3 * pow(x, 0.4e1) - 0.20e2 * x * x - 0.20e2 * y * y * x * x + 0.3e1 * y * y + 0.20e2 * r0 * x * x - 0.3e1 * r0) - 0.16e2 * lambdam / mum * x * (0.4e1 * x * x - 0.1e1) * y + 0.2e1 * x * y * (-0.5e1 * y * y - 0.24e2 * pow(x, 0.4e1) + 0.12e2 * x * x + 0.3e1 * r0) - 0.16e2 * x * (0.4e1 * x * x - 0.1e1) * y);
				vF[1] = 2.*(-0.1568e4 * pow(x, 0.6e1) + 0.888e3 * pow(x, 0.4e1) - 0.80e2 * x * x - 0.60e2 * y * y * x * x - 0.4e1 * y * y + 0.84e2 * r0 * x * x - 0.4e1 * r0 - 0.120e3 * y * y * pow(x, 0.4e1) - 0.5e1 / 0.2e1 * pow(y, 0.4e1) + 0.3e1 * y * y * r0 - 0.288e3 * pow(x, 0.8e1) + 0.40e2 * pow(x, 0.4e1) * r0 - r0 * r0 / 0.2e1 - lambdam / mum * (0.240e3 * y * y * pow(x, 0.4e1) - 0.72e2 * y * y * x * x + 0.5e1 * pow(y, 0.4e1) - 0.6e1 * y * y * r0 + 0.576e3 * pow(x, 0.8e1) - 0.448e3 * pow(x, 0.6e1) + 0.80e2 * pow(x, 0.4e1) - 0.80e2 * pow(x, 0.4e1) * r0 + 0.24e2 * r0 * x * x + r0 * r0) / 0.2e1 - lambdam / mum * (0.12e2 * y * y + 0.32e2 * pow(x, 0.4e1) - 0.16e2 * x * x - 0.4e1 * r0) / 0.2e1);
				}
				else {
				vF[0] = 2.*(0.16e2 * x * y * (-0.288e3 * pow(x, 0.6e1) + 0.168e3 * pow(x, 0.4e1) - 0.20e2 * x * x - 0.20e2 * y * y * x * x + 0.3e1 * y * y + 0.20e2 * r0 * x * x - 0.3e1 * r0) + 0.8e1 * lambdap / mup * x * y * (-0.288e3 * pow(x, 0.6e1) + 0.168e3 * pow(x, 0.4e1) - 0.20e2 * x * x - 0.20e2 * y * y * x * x + 0.3e1 * y * y + 0.20e2 * r0 * x * x - 0.3e1 * r0) - 0.16e2 * lambdap / mup * x * (0.4e1 * x * x - 0.1e1) * y + 0.2e1 * x * y * (-0.5e1 * y * y - 0.24e2 * pow(x, 0.4e1) + 0.12e2 * x * x + 0.3e1 * r0) - 0.16e2 * x * (0.4e1 * x * x - 0.1e1) * y);
				vF[1] = 2.*(-0.1568e4 * pow(x, 0.6e1) + 0.888e3 * pow(x, 0.4e1) - 0.80e2 * x * x - 0.60e2 * y * y * x * x - 0.4e1 * y * y + 0.84e2 * r0 * x * x - 0.4e1 * r0 - 0.120e3 * y * y * pow(x, 0.4e1) - 0.5e1 / 0.2e1 * pow(y, 0.4e1) + 0.3e1 * y * y * r0 - 0.288e3 * pow(x, 0.8e1) + 0.40e2 * pow(x, 0.4e1) * r0 - r0 * r0 / 0.2e1 - lambdap / mup * (0.240e3 * y * y * pow(x, 0.4e1) - 0.72e2 * y * y * x * x + 0.5e1 * pow(y, 0.4e1) - 0.6e1 * y * y * r0 + 0.576e3 * pow(x, 0.8e1) - 0.448e3 * pow(x, 0.6e1) + 0.80e2 * pow(x, 0.4e1) - 0.80e2 * pow(x, 0.4e1) * r0 + 0.24e2 * r0 * x * x + r0 * r0) / 0.2e1 - lambdap / mup * (0.12e2 * y * y + 0.32e2 * pow(x, 0.4e1) - 0.16e2 * x * x - 0.4e1 * r0) / 0.2e1);
				}
			}
			
			void	VF			(FVector_double& p, FMatrix_double& mF) {
				double x=p[0], y=p[1];
				mF.setAll(2.*(0.16e2 * x * y * (-0.288e3 * pow(x, 0.6e1) + 0.168e3 * pow(x, 0.4e1) - 0.20e2 * x * x - 0.20e2 * y * y * x * x + 0.3e1 * y * y + 0.20e2 * r0 * x * x - 0.3e1 * r0) + 0.8e1 * lambdam / mum * x * y * (-0.288e3 * pow(x, 0.6e1) + 0.168e3 * pow(x, 0.4e1) - 0.20e2 * x * x - 0.20e2 * y * y * x * x + 0.3e1 * y * y + 0.20e2 * r0 * x * x - 0.3e1 * r0) - 0.16e2 * lambdam / mum * x * (0.4e1 * x * x - 0.1e1) * y + 0.2e1 * x * y * (-0.5e1 * y * y - 0.24e2 * pow(x, 0.4e1) + 0.12e2 * x * x + 0.3e1 * r0) - 0.16e2 * x * (0.4e1 * x * x - 0.1e1) * y), 
					      2.*(-0.1568e4 * pow(x, 0.6e1) + 0.888e3 * pow(x, 0.4e1) - 0.80e2 * x * x - 0.60e2 * y * y * x * x - 0.4e1 * y * y + 0.84e2 * r0 * x * x - 0.4e1 * r0 - 0.120e3 * y * y * pow(x, 0.4e1) - 0.5e1 / 0.2e1 * pow(y, 0.4e1) + 0.3e1 * y * y * r0 - 0.288e3 * pow(x, 0.8e1) + 0.40e2 * pow(x, 0.4e1) * r0 - r0 * r0 / 0.2e1 - lambdam / mum * (0.240e3 * y * y * pow(x, 0.4e1) - 0.72e2 * y * y * x * x + 0.5e1 * pow(y, 0.4e1) - 0.6e1 * y * y * r0 + 0.576e3 * pow(x, 0.8e1) - 0.448e3 * pow(x, 0.6e1) + 0.80e2 * pow(x, 0.4e1) - 0.80e2 * pow(x, 0.4e1) * r0 + 0.24e2 * r0 * x * x + r0 * r0) / 0.2e1 - lambdam / mum * (0.12e2 * y * y + 0.32e2 * pow(x, 0.4e1) - 0.16e2 * x * x - 0.4e1 * r0) / 0.2e1),
						  2.*(0.16e2 * x * y * (-0.288e3 * pow(x, 0.6e1) + 0.168e3 * pow(x, 0.4e1) - 0.20e2 * x * x - 0.20e2 * y * y * x * x + 0.3e1 * y * y + 0.20e2 * r0 * x * x - 0.3e1 * r0) + 0.8e1 * lambdap / mup * x * y * (-0.288e3 * pow(x, 0.6e1) + 0.168e3 * pow(x, 0.4e1) - 0.20e2 * x * x - 0.20e2 * y * y * x * x + 0.3e1 * y * y + 0.20e2 * r0 * x * x - 0.3e1 * r0) - 0.16e2 * lambdap / mup * x * (0.4e1 * x * x - 0.1e1) * y + 0.2e1 * x * y * (-0.5e1 * y * y - 0.24e2 * pow(x, 0.4e1) + 0.12e2 * x * x + 0.3e1 * r0) - 0.16e2 * x * (0.4e1 * x * x - 0.1e1) * y), 
						  2.*(-0.1568e4 * pow(x, 0.6e1) + 0.888e3 * pow(x, 0.4e1) - 0.80e2 * x * x - 0.60e2 * y * y * x * x - 0.4e1 * y * y + 0.84e2 * r0 * x * x - 0.4e1 * r0 - 0.120e3 * y * y * pow(x, 0.4e1) - 0.5e1 / 0.2e1 * pow(y, 0.4e1) + 0.3e1 * y * y * r0 - 0.288e3 * pow(x, 0.8e1) + 0.40e2 * pow(x, 0.4e1) * r0 - r0 * r0 / 0.2e1 - lambdap / mup * (0.240e3 * y * y * pow(x, 0.4e1) - 0.72e2 * y * y * x * x + 0.5e1 * pow(y, 0.4e1) - 0.6e1 * y * y * r0 + 0.576e3 * pow(x, 0.8e1) - 0.448e3 * pow(x, 0.6e1) + 0.80e2 * pow(x, 0.4e1) - 0.80e2 * pow(x, 0.4e1) * r0 + 0.24e2 * r0 * x * x + r0 * r0) / 0.2e1 - lambdap / mup * (0.12e2 * y * y + 0.32e2 * pow(x, 0.4e1) - 0.16e2 * x * x - 0.4e1 * r0) / 0.2e1));
			}
		};			

		class P_HOMOGENEOUS_KWAK_Epsilon_Hansbo_Condition: public FEM_PROBLEM {	
		public:
			double nu;
			int ord;
			void	initialize	(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll( -1., -1., 1.,1.);
				Input("ord : " , ord);
				Input("r0 : ", r0);
				nBasis = 8;
				//r0 = CV.PI/6.28;
				//mum = 1.; mup = mum/(pow(10.,-ord)*mum+1); r0 = 0.36; alpha = 0.007; nu = 0.4; lambdam = 2*nu/(1-2*nu)*mum; lambdap = 2*nu/(1-2*nu)*mup;  beta = r0/2.*0.2*pow(10.,-ord);	
				mum = 1.; mup = mum/(pow(10.,-ord)*mum+1); alpha = 0.; nu = 0.4; lambdam = 2*nu/(1-2*nu)*mum; lambdap = 2*nu/(1-2*nu)*mup;  beta = r0/2.*0.2*pow(10.,-ord);	
				//mum = 1.; mup = 2.; r0 = 0.36; alpha = 0.; beta = 0.; lambdam = 99; lambdap = 396;
				//Input("Poisson ratio", nu);
				//Input("Interior mum, lambdam", mum);
				//Input("Exterior mup, lambdap", mup);
				//Input("r0", r0);
				//Input("alpha",alpha);
				//Input("beta",beta);
				//Input("lambdam", lambdam);// = nu *mum;
				//Input("lambdap", lambdap);// = nu *mup;*/
				//s = 2.*r0*r0*mum*beta*(2.*mup+lambdap)/mup;
				cout << "ord : " << ord << endl;
				cout << "beta : " << beta << endl;
				cout << "alpha : " << alpha << endl;
				cout << "r0 : " << r0 << " mum :" << mum << " mup : " << mup << " lambdap : " << lambdap  << " lambdam : " << lambdam <<endl;
			}		
			double	coef_mu		(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}
			double	coef_mu		(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if(Interface(p) <= 0) {
					return mus[0];
				} else { 
					return mus[1];
				}
			}
			double coef_lambda  (FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(lambdam, lambdap);              // (Interior, Exterior)
				return 0;
			}
			double coef_lambda (FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_lambda(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.

				if(io == CV.IN) return mus[0];
				return mus[1];
			}
			double coef_lambda  (FVector_double& p) {
				static FVector_double mus(2);
				coef_lambda(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.

				if(Interface(p) < 0) {
					return mus[0];
				} 
				else { 
					return mus[1];
				}
				return 0.;
			}
			double	Interface	(double r) {			// 내부에서 음수의 값을 가지도록 한다.
				return (r - r0);
			}
			double	Interface	(FVector_double& p) {
				double x=p[0], y=p[1];
				double r = sqrt(x*x + y*y);

				return (r - r0);
			}
			void	V			(FVector_double& p, FVector_double& v) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				if(Interface(r) <= 0) {
					v.setAll(x/(r0*mum), y/(r0*mum));
				} else { 
					v.setAll(x/(r0*mup), y/(r0*mup));					
				}
			}
			void    V			(FVector_double& p, FMatrix_double& v)
			{
				double x = p[0], y = p[1];
				v.setAll(x/(r0*mum), y/(r0*mum),
						x/(r0*mup), y/(r0*mup));
			}
			void GRADV			(FVector_double& p, FMatrix_double& GRAD) {
				double x= p[0], y= p[1];
				double r=sqrt(x*x + y*y);
				if(Interface(r) <= 0) {
					GRAD.setAll(1/(r0*mum), 0., 0., 1/(r0*mum));
				} else{
					GRAD.setAll(1/(r0*mup), 0., 0., 1/(r0*mup));	
				}
			}
			void GRADV			(FVector_double& p, FCube_double& cGRAD) {
				double x= p[0], y= p[1];
				cGRAD[0].setAll(1/(r0*mum), 0., 0., 1/(r0*mum));
				cGRAD[1].setAll(1/(r0*mup), 0., 0., 1/(r0*mup));	
			}
			double div			(FVector_double& p) {
				double x = p[0], y=p[1];
				double divergence;
				double r = sqrt(x*x + y*y);
				if(Interface(r) <= 0 ) {
					divergence = 2./(r0*mum);
				} else {
					divergence = 2./(r0*mup);			
				}
				return divergence;
			}
			void div			(FVector_double& p, FVector_double& div) {
				double x = p[0], y=p[1];
				div.setAll(2./(r0*mum),2./(r0*mup));
			}
			void	VF			(FVector_double& p, FVector_double& vF) {
				double x=p[0], y=p[1];
				double r = sqrt(x*x + y*y);
				if(Interface(r) <= 0) {
					vF[0] = 0.;
					vF[1] = 0.;
				}
				if(Interface(r) > 0) {
					vF[0] = 0.;
					vF[1] = 0.;
				}
			}
			void	VF			(FVector_double& p, FMatrix_double& vF) {
				double x=p[0], y=p[1];
				double r = sqrt(x*x + y*y);
				vF.setAll( 0., 0., 0., 0.);
			}
			void normal			(FVector_double& p, FVector_double& vN)
			{
				double x = p[0], y = p[1];
				vN.setAll(x/r0,y/r0);
			}
		};
		class P_HOMOGENEOUS_KWAK_Epsilon_Hansbo_Condition_KYEONG_BETA_ZERO: public FEM_PROBLEM {	
		public:
			double nu;
			int ord;
			double c;
			void	initialize	(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll( -1., -1., 1.,1.);
				Input("Poisson ratio", nu);
				Input("Interior mum, lambdam", mum);
				Input("Exterior mup, lambdap", mup);
				Input("alpha",alpha);
				Input("c",c);
				nBasis = 8;
				beta = 0; lambdam = mum * (2*nu/(1-2*nu)); lambdap = mup *(2*nu/(1-2*nu));
				cout << "beta : " << beta << endl;
				cout << "alpha : " << alpha << endl;
				cout << " mum :" << mum << " mup : " << mup << " lambdap : " << lambdap  << " lambdam : " << lambdam <<endl;
			}		
			double	coef_mu		(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}
			double	coef_mu		(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if(Interface(p) <= 0) {
					return mus[0];
				} else { 
					return mus[1];
				}
			}
			double coef_lambda  (FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(lambdam, lambdap);              // (Interior, Exterior)
				return 0;
			}
			double coef_lambda (FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_lambda(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.

				if(io == CV.IN) return mus[0];
				return mus[1];
			}
			double coef_lambda  (FVector_double& p) {
				static FVector_double mus(2);
				coef_lambda(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.

				if(Interface(p) < 0) {
					return mus[0];
				} 
				else { 
					return mus[1];
				}
				return 0.;
			}
			double	Interface	(FVector_double& p) {
				double x=p[0], y=p[1];
				return x/2.-y-c;
			}
			void	V			(FVector_double& p, FVector_double& v) {
				double x = p[0], y = p[1];
				if(Interface(p) <= 0) {
					v.setAll((x/2.-y)*(x/2.-y)/mum,(x/2.-y)*(x/2.-y)/mum);
				} else { 
					v.setAll((x/2.-y)*(x/2.-y)/mup - (1/mup-1/mum)*c*c+alpha*6./5.*c*sqrt(5.), (x/2.-y)*(x/2.-y)/mup - (1/mup-1/mum)*c*c+ alpha*3./5.*c*sqrt(5.));					
				}
			}
			void    V			(FVector_double& p, FMatrix_double& v)
			{
				double x = p[0], y = p[1];
				v.setAll((x/2.-y)*(x/2.-y)/mum,(x/2.-y)*(x/2.-y)/mum,
						(x/2.-y)*(x/2.-y)/mup - (1/mup-1/mum)*c*c+ alpha*6./5.*c*sqrt(5.), (x/2.-y)*(x/2.-y)/mup - (1/mup-1/mum)*c*c+alpha*3./5.*c*sqrt(5.));
			}
			void GRADV			(FVector_double& p, FMatrix_double& GRAD) {
				double x= p[0], y= p[1];
				if(Interface(p) <= 0) {
					GRAD.setAll((x/2.-y)/mum, -2.*(x/2.-y)/mum, (x/2.-y)/mum, -2.*(x/2.-y)/mum);
				} else{
					GRAD.setAll((x/2.-y)/mup, -2.*(x/2.-y)/mup, (x/2.-y)/mup, -2.*(x/2.-y)/mup);
				}
			}
			void GRADV			(FVector_double& p, FCube_double& cGRAD) {
				double x= p[0], y= p[1];
				cGRAD[0].setAll((x/2.-y)/mum, -2.*(x/2.-y)/mum, (x/2.-y)/mum, -2.*(x/2.-y)/mum);
				cGRAD[1].setAll((x/2.-y)/mup, -2.*(x/2.-y)/mup, (x/2.-y)/mup, -2.*(x/2.-y)/mup);	
			}
			double div			(FVector_double& p) {
				double x = p[0], y=p[1];
				double divergence;
				if(Interface(p) <= 0 ) {
					divergence = -(x/2.-y)/mum;
				} else {
					divergence = -(x/2.-y)/mup;			
				}
				return divergence;
			}
			void div			(FVector_double& p, FVector_double& div) {
				double x = p[0], y=p[1];
				div.setAll(-(x/2.-y)/mum,-(x/2.-y)/mup);
			}
			void	VF			(FVector_double& p, FVector_double& vF) {
				double x=p[0], y=p[1];
				if(Interface(p) <= 0) {
					vF[0] = -2+lambdam/(2*mum);
					vF[1] = -7./2.-lambdam/mum;
				}
				if(Interface(p) > 0) {
					vF[0] = -2+lambdam/(2*mum);
					vF[1] = -7./2.-lambdam/mum;
				}
			}
			void	VF			(FVector_double& p, FMatrix_double& vF) {
				double x=p[0], y=p[1];
				vF.setAll(-2+lambdam/(2*mum),-7./2.-lambdam/mum,-2+lambdam/(2*mum),-7./2.-lambdam/mum);
			}
			void normal			(FVector_double& p, FVector_double& vN)
			{
				double x = p[0], y = p[1];
				vN.clear(0.);
				vN.setAll(1./2.,-1.);
				vN.normalize();
			}
		};
		class P_HOMOGENEOUS_KWAK_Epsilon_Hansbo_Condition_KYEONG_ALPHA_ZERO: public FEM_PROBLEM {	
		public:
			double nu;
			int ord;
			double c;
			void	initialize	(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll( -1., -1., 1.,1.);
				Input("Poisson ratio", nu);
				Input("Interior mum, lambdam", mum);
				Input("Exterior mup, lambdap", mup);
				Input("beta",beta);
				Input("c",c);
				nBasis = 8;
				alpha=0; lambdam = mum * (2*nu/(1-2*nu)); lambdap = mup *(2*nu/(1-2*nu));
				cout << "beta : " << beta << endl;
				cout << "alpha : " << alpha << endl;
				cout << " mum :" << mum << " mup : " << mup << " lambdap : " << lambdap  << " lambdam : " << lambdam <<endl;
			}		
			double	coef_mu		(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}
			double	coef_mu		(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if(Interface(p) <= 0) {
					return mus[0];
				} else { 
					return mus[1];
				}
			}
			double coef_lambda  (FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(lambdam, lambdap);              // (Interior, Exterior)
				return 0;
			}
			double coef_lambda (FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_lambda(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.

				if(io == CV.IN) return mus[0];
				return mus[1];
			}
			double coef_lambda  (FVector_double& p) {
				static FVector_double mus(2);
				coef_lambda(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.

				if(Interface(p) < 0) {
					return mus[0];
				} 
				else { 
					return mus[1];
				}
				return 0.;
			}
			double	Interface	(FVector_double& p) {
				double x=p[0], y=p[1];
				return x-y/2.-c;
			}
			void	V			(FVector_double& p, FVector_double& v) {
				double x = p[0], y = p[1];
				if(Interface(p) <= 0) {
					v.setAll((x-y/2.)*(x-y/2.)/mum,(x-y/2.)*(x-y/2.)/mum);
				} else { 
					v.setAll((x-y/2.)*(x-y/2.)/mup - (1/mup-1/mum)*c*c+beta*sqrt(5.)/5.*(2*lambdam*c+4*mum*c)/mum, (x-y/2.)*(x-y/2.)/mup - (1/mup-1/mum)*c*c -beta*sqrt(5.)/10.*(2*lambdam*c+4*mum*c)/mum);					
				}
			}
			void    V			(FVector_double& p, FMatrix_double& v)
			{
				double x = p[0], y = p[1];
				v.setAll((x-y/2.)*(x-y/2.)/mum,(x-y/2.)*(x-y/2.)/mum,
						(x-y/2.)*(x-y/2.)/mup - (1/mup-1/mum)*c*c+beta*sqrt(5.)/5.*(2*lambdam*c+4*mum*c)/mum, (x-y/2.)*(x-y/2.)/mup - (1/mup-1/mum)*c*c -beta*sqrt(5.)/10.*(2*lambdam*c+4*mum*c)/mum);
			}
			void GRADV			(FVector_double& p, FMatrix_double& GRAD) {
				double x= p[0], y= p[1];
				if(Interface(p) <= 0) {
					GRAD.setAll(2.*(x-y/2.)/mum, -(x-y/2.)/mum, 2.*(x-y/2.)/mum, -(x-y/2.)/mum);
				} else{
					GRAD.setAll(2.*(x-y/2.)/mup, -(x-y/2.)/mup, 2.*(x-y/2.)/mup, -(x-y/2.)/mup);
				}
			}
			void GRADV			(FVector_double& p, FCube_double& cGRAD) {
				double x= p[0], y= p[1];
				cGRAD[0].setAll(2.*(x-y/2.)/mum, -(x-y/2.)/mum, 2.*(x-y/2.)/mum, -(x-y/2.)/mum);
				cGRAD[1].setAll(2.*(x-y/2.)/mup, -(x-y/2.)/mup, 2.*(x-y/2.)/mup, -(x-y/2.)/mup);	
			}
			double div			(FVector_double& p) {
				double x = p[0], y=p[1];
				double divergence;
				if(Interface(p) <= 0 ) {
					divergence = (x-y/2.)/mum;
				} else {
					divergence = (x-y/2.)/mup;			
				}
				return divergence;
			}
			void div			(FVector_double& p, FVector_double& div) {
				double x = p[0], y=p[1];
				div.setAll((x-y/2.)/mum,(x-y/2.)/mup);
			}
			void	VF			(FVector_double& p, FVector_double& vF) {
				double x=p[0], y=p[1];
				if(Interface(p) <= 0) {
					vF[0] = -7./2.-lambdam/mum;
					vF[1] = -2+lambdam/(2*mum);
				}
				if(Interface(p) > 0) {
					vF[0] = -7./2.-lambdam/mum;
					vF[1] = -2+lambdam/(2*mum);
				}
			}
			void	VF			(FVector_double& p, FMatrix_double& vF) {
				double x=p[0], y=p[1];
				vF.setAll(-7./2.-lambdam/mum,-2+lambdam/(2*mum),-7./2.-lambdam/mum,-2+lambdam/(2*mum));
			}
			void normal			(FVector_double& p, FVector_double& vN)
			{
				double x = p[0], y = p[1];
				vN.clear(0.);
				vN.setAll(1.,-1./2.);
				vN.normalize();
			}
		};
		class P_HOMOGENEOUS_KWAK_Epsilon_Hansbo_Condition_Constant: public FEM_PROBLEM {	
		public:
			double nu;
			int ord, numb;
			void	initialize	(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll( -1., -1., 1.,1.);
				Input("ord" , ord);
				mum = 1.; mup = 1.; r0 = 0.9; alpha = 0.7; nu = 0.4; lambdam = 2*nu/(1-2*nu)*mum; lambdap = 2*nu/(1-2*nu)*mup;  beta = alpha;	
				//mum = 1.; mup = mum/(pow(10.,-ord)*mum+1); r0 = 0.36;  nu = 0.4; lambdam = 0.; lambdap = 0.;  beta = r0/2.*pow(10.,-ord);	
				//alpha = 0.7;
				//mum = 1.; mup=1.;lambdam=4.; beta = 0.7; alpha = 0.7; lambdap=4.;r0=0.36;
				//mum = 1.; mup = 2.; r0 = 0.36; alpha = 0.7; beta = 0.; lambdam = 99; lambdap = 396;
				//Input("Poisson ratio", nu);
				//Input("Interior mum, lambdam", mum);
				//Input("Exterior mup, lambdap", mup);
				//Input("r0", r0);
				//Input("alpha",alpha);
				//Input("beta",beta);
				//Input("lambdam", lambdam);// = nu *mum;
				//Input("lambdap", lambdap);// = nu *mup;*/
				//s = 2.*r0*r0*mum*beta*(2.*mup+lambdap)/mup;
				//cout << "ord : " << ord << endl;
				Input("problem " , numb);
				if(numb==3)
				{
					mum = 1.; mup = mum/(pow(10.,-ord)*mum+1); r0 = 0.979; alpha = 0.007; nu = 0.4; lambdam = 2*nu/(1-2*nu)*mum; lambdap = 2*nu/(1-2*nu)*mup;  beta = r0/2.*0.2*pow(10.,-ord);	
				}
				if(numb==2)
				{
					Input("Interior mum, lambdam", mum);
					Input("r0", r0);
					Input("alpha",alpha);
					beta = 0.;
				}
				cout << "beta : " << beta << endl;
				cout << "r0 : " << r0 << " mum :" << mum << " mup : " << mup << " lambdap : " << lambdap  << " lambdam : " << lambdam <<endl;
			}
			
			double	coef_mu		(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}

			double	coef_mu		(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if(Interface(p) <= 0) {
					return mus[0];
				} else { 
					return mus[1];
				}
			}
			double coef_lambda  (FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(lambdam, lambdap);              // (Interior, Exterior)
				return 0;
			}
			double coef_lambda (FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_lambda(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.

				if(io == CV.IN) return mus[0];
				return mus[1];
			}
			double coef_lambda  (FVector_double& p) {
				static FVector_double mus(2);
				coef_lambda(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.

				if(Interface(p) < 0) {
					return mus[0];
				} 
				else { 
					return mus[1];
				}
				return 0.;
			}
			double	Interface	(FVector_double& p) {
				double x=p[0], y=p[1];
				double r = sqrt(x*x + y*y);
				switch(numb)
				{
					case 1:
						return x+y-0.216; break;
					case 2:
						return y-r0; break;
					case 3:
						return (r - r0); break;
					default:
						return 0.;
				}
			}
			void	V			(FVector_double& p, FVector_double& v) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				switch(numb)
				{
					case 1:
						if(Interface(p) <= 0)	v.setAll((x+y)/mum, 3*(x+y)/mum);
						else					v.setAll((x+y)/mum+alpha*(6+4*lambdam/mum)/sqrt(2.), 3*(x+y)/mum+alpha*(10+4*lambdam/mum)/sqrt(2.));
						break;
					case 2:
						if(Interface(p) <= 0)	v.setAll(y*y*y -3*r0*y*y, x);
						else 					v.setAll(y*y*y -3*r0*y*y +alpha*mum*(3*y*y-6*r0*y+1), x);					
						break;
					case 3:
						if(Interface(p) <= 0)	v.setAll(x/(r0*mum), y/(r0*mum));
						else					v.setAll(x/(r0*mup), y/(r0*mup));					
						break;
					default:
						v.setAll(0.,0.);
				}
			}
			void  V				(FVector_double& p, FMatrix_double& v)
			{
				double x = p[0], y = p[1];
				switch(numb)
				{
					case 1:
						v.setAll((x+y)/mum, 3*(x+y)/mum,
								(x+y)/mum+alpha*(6+4*lambdam/mum)/sqrt(2.), 3*(x+y)/mum+alpha*(10+4*lambdam/mum)/sqrt(2.));
						break;
					case 2:
						v.setAll(y*y*y -3*r0*y*y, x,
								y*y*y -3*r0*y*y +alpha*mum*(3*y*y-6*r0*y+1), x);					
						break;
					case 3:
						v.setAll(x/(r0*mum), y/(r0*mum),
								x/(r0*mup), y/(r0*mup));			
						break;
					default:
						v.setAll(0.,0., 0.,0.);
				}
			}
			void GRADV			(FVector_double& p, FMatrix_double& GRAD) {
				double x= p[0], y= p[1];
				double r=sqrt(x*x + y*y);
				switch(numb)
				{
					case 1:
						if(Interface(p) <= 0)	GRAD.setAll(1/mum, 1/mum, 3/mum, 3/mum);
						else					GRAD.setAll(1/mum, 1/mum, 3/mum, 3/mum);	
						break;
					case 2:
						if(Interface(p) <= 0)	GRAD.setAll(0., 3*y*y-6*r0*y, 1., 0.);
						else					GRAD.setAll(0., 3*y*y-6*r0*y+alpha*mum*(6.*y-6*r0), 1., 0.);	
						break;
					case 3:
						if(Interface(p) <= 0)	GRAD.setAll(1/(r0*mum), 0., 0., 1/(r0*mum));
						else					GRAD.setAll(1/(r0*mup), 0., 0., 1/(r0*mup));	
						break;
					default:
						GRAD.setAll(0.,0., 0.,0.);
				}
			}
			double div			(FVector_double& p) {
				double x = p[0], y=p[1];
				double divergence;
				double r = sqrt(x*x + y*y);
				switch(numb)
				{
				case 1:
					if(Interface(p) <= 0 )	divergence = 4/mum;
					else					divergence = 4/mum;	
					break;
				case 2:
					if(Interface(p) <= 0 )	divergence = 0.;
					else					divergence = 0.;
					break;
				case 3:
					if(Interface(p) <= 0 )	divergence = 2./(r0*mum);
					else					divergence = 2./(r0*mup);			
					break;
				default:
					divergence = 0.;
				}
			return divergence;
			}
			void	VF			(FVector_double& p, FVector_double& vF) {
				double x=p[0], y=p[1];
				double r = sqrt(x*x + y*y);
				switch(numb)
				{
					case 1:
						if(Interface(p) <= 0 ) {
							vF[0] = 0.;
							vF[1] = 0.;
						}
						else 
						{
							vF[0] = 0.;
							vF[1] = 0.;
						}
						break;
					case 2:
						if(Interface(p) <= 0 ) {
							vF[0] = (-3*y+3*r0)*mum;
							vF[1] = 0.;
						}
						else 
						{
							vF[0] = (-3*y+3*r0-alpha*3*mum)*mum;
							vF[1] = 0.;
						}
						break;
					case 3:
						if(Interface(p) <= 0 ) {
							vF[0] = 0.;
							vF[1] = 0.;
						}
						else 
						{
							vF[0] = 0.;
							vF[1] = 0.;
						}
						break;
					default:
						vF.setAll(0.,0.);
				}
			}
		};
		class P_HOMOGENEOUS_KWAK_Epsilon_Hansbo_Condition_LineInterface_HyperbolicEquation: public FEM_PROBLEM {	
		public:
			double nu,c;
			int numb;
			void	initialize	(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				//RX = __.RX.make(__.dim, __.dim).setAll(-1.36, -1.678, 1.14,1.);
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1.,1.);
				mum = 1.; mup = 1; c = 1.12; alpha = 0.007; nu = 0.4; beta = 0.05;	
				Input("Poisson ratio", nu);
				Input("Interior mum, lambdam", mum);
				Input("Exterior mup, lambdap", mup);
				Input("alpha",alpha);
				Input("beta",beta);
				c = sqrt(2.)*alpha/(1/mup-1/mum);
				lambdam = 2*nu/(1-2*nu)*mum; lambdap = 2*nu/(1-2*nu)*mup; 
				if(alpha == 0 || beta == 0)
					nBasis = 8;
				else
					nBasis = 10;
				cout << "beta : " << beta << endl;
				cout << "c : " << c << " mum :" << mum << " mup : " << mup << " lambdap : " << lambdap  << " lambdam : " << lambdam <<endl;
			}
			
			double	coef_mu		(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}

			double	coef_mu		(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if(Interface(p) <= 0) {
					return mus[0];
				} else { 
					return mus[1];
				}
			}
			double coef_lambda  (FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(lambdam, lambdap);              // (Interior, Exterior)
				return 0;
			}
			double coef_lambda (FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_lambda(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.

				if(io == CV.IN) return mus[0];
				return mus[1];
			}
			double coef_lambda  (FVector_double& p) {
				static FVector_double mus(2);
				coef_lambda(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.

				if(Interface(p) <= 0) {
					return mus[0];
				} 
				else { 
					return mus[1];
				}
				return 0.;
			}
			double	Interface	(FVector_double& p) {
				double x=p[0], y=p[1];
				return x-y-c;
			}
			
			void	V			(FVector_double& p, FVector_double& v) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				if(Interface(p) <= 0)	v.setAll((x*x-y*y)/mum, (x*x-y*y)/mum);
				else					v.setAll((x*x-y*y)/mup+sqrt(2.)*c*beta*lambdap/mup, (x*x-y*y)/mup-sqrt(2.)*c*beta*lambdap/mup);
			}
			void  V				(FVector_double& p, FMatrix_double& v)
			{
				double x = p[0], y = p[1];
				v.setAll((x*x-y*y)/mum, (x*x-y*y)/mum,
						(x*x-y*y)/mup+sqrt(2.)*c*beta*lambdap/mup, (x*x-y*y)/mup-sqrt(2.)*c*beta*lambdap/mup);
			}
			void GRADV			(FVector_double& p, FMatrix_double& GRAD) {
				double x= p[0], y= p[1];
				double r=sqrt(x*x + y*y);
				if(Interface(p) <= 0)	GRAD.setAll(2*x/mum, -2*y/mum, 2*x/mum, -2*y/mum);
				else					GRAD.setAll(2*x/mup, -2*y/mup, 2*x/mup, -2*y/mup);		
			}
			void GRADV			(FVector_double& p, FCube_double& GRAD) {
				double x= p[0], y= p[1];
				double r=sqrt(x*x + y*y);
				GRAD[0].setAll(2*x/mum, -2*y/mum, 2*x/mum, -2*y/mum);
				GRAD[1].setAll(2*x/mup, -2*y/mup, 2*x/mup, -2*y/mup);
			}
			double div			(FVector_double& p) {
				double x = p[0], y=p[1];
				double divergence;
				double r = sqrt(x*x + y*y);
				if(Interface(p) <= 0 )	divergence = (2*x-2*y)/mum;
				else					divergence = (2*x-2*y)/mup;	
				return divergence;
			}
			void div			(FVector_double& p, FVector_double& div) {
				double x = p[0], y=p[1];
				double r = sqrt(x*x + y*y);
				div.setAll((2*x-2*y)/mum,(2*x-2*y)/mup);
			}
			void	VF			(FVector_double& p, FVector_double& vF) {
				double x=p[0], y=p[1];
				double r = sqrt(x*x + y*y);
				if(Interface(p) <= 0 ) {
					vF[0] = (-1-1*lambdam/mum)*2;
					vF[1] = (+1+1*lambdam/mum)*2;
				}
				else 
				{
					vF[0] = (-1-1*lambdap/mup)*2;
					vF[1] = (+1+1*lambdap/mup)*2;
				}
			}
			void	VF			(FVector_double& p, FMatrix_double& vF) {
				double x=p[0], y=p[1];
				double r = sqrt(x*x + y*y);
				vF.setAll((-1-1*lambdam/mum)*2, (+1+1*lambdam/mum)*2,
						(-1-1*lambdap/mup)*2, (+1+1*lambdap/mup)*2);
			}
		};
		class P_HOMOGENEOUS_KWAK_Epsilon_Hansbo_Condition_CurveInterface_HyperbolicEquation: public FEM_PROBLEM {	
		public:
			double nu,r0;
			int numb;
			void	initialize	(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll( -1., -1., 1.,1.);
				//nu = 0.25;
				Input("Poisson ratio", nu);
				Input("Interior mum, lambdam", mum);
				Input("Exterior mup, lambdap", mup);
				Input("r0",r0);
				alpha = (1/mup-1/mum)*r0/4.;
				beta = alpha;
				nBasis = 10;
				lambdam = 2*nu/(1-2*nu)*mum; lambdap = 2*nu/(1-2*nu)*mup; 
				cout << "alpha : " << alpha << endl;
				cout << "beta : " << beta << endl;
				cout << " r0 : " << r0 << " mum :" << mum << " mup : " << mup << " lambdap : " << lambdap  << " lambdam : " << lambdam <<endl;
			}
			
			double	coef_mu		(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}

			double	coef_mu		(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if(Interface(p) <= 0) {
					return mus[0];
				} else { 
					return mus[1];
				}
			}
			double coef_lambda  (FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(lambdam, lambdap);              // (Interior, Exterior)
				return 0;
			}
			double coef_lambda (FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_lambda(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.

				if(io == CV.IN) return mus[0];
				return mus[1];
			}
			double coef_lambda  (FVector_double& p) {
				static FVector_double mus(2);
				coef_lambda(p, mus);               // 두 값을 호출해서 알맞게 돌려준다.

				if(Interface(p) < 0) {
					return mus[0];
				} 
				else { 
					return mus[1];
				}
				return 0.;
			}
			double	Interface	(FVector_double& p) {
				double x=p[0], y=p[1];
				double r = sqrt(x*x+y*y);
				return r-r0;
			}
			
			void	V			(FVector_double& p, FVector_double& v) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				if(Interface(p) <= 0)	v.setAll((x*x-y*y)/mum, (x*x-y*y)/mum);
				else					v.setAll((x*x-y*y)/mup+(1/mup-1/mum)*r0*r0/2., (x*x-y*y)/mup-(1/mup-1/mum)*r0*r0/2.);
			}
			void  V				(FVector_double& p, FMatrix_double& v)
			{
				double x = p[0], y = p[1];
				double r = sqrt(x*x+y*y);
				v.setAll((x*x-y*y)/mum, (x*x-y*y)/mum,
						(x*x-y*y)/mup+(1/mup-1/mum)*r0*r0/2., (x*x-y*y)/mup-(1/mup-1/mum)*r0*r0/2.);
			}
			void GRADV			(FVector_double& p, FMatrix_double& GRAD) {
				double x= p[0], y= p[1];
				double r=sqrt(x*x + y*y);
				if(Interface(p) <= 0)	GRAD.setAll(2*x/mum, -2*y/mum, 2*x/mum, -2*y/mum);
				else					GRAD.setAll(2*x/mup, -2*y/mup, 2*x/mup, -2*y/mup);		
			}
			void GRADV			(FVector_double& p, FCube_double& cGRAD) {
				double x= p[0], y= p[1];
				double r=sqrt(x*x + y*y);
				cGRAD[0].setAll(2*x/mum, -2*y/mum, 2*x/mum, -2*y/mum);
				cGRAD[1].setAll(2*x/mup, -2*y/mup, 2*x/mup, -2*y/mup);		
			}
			double div			(FVector_double& p) {
				double x = p[0], y=p[1];
				double divergence;
				double r = sqrt(x*x + y*y);
				if(Interface(p) <= 0 )	divergence = (2*x-2*y)/mum;
				else					divergence = (2*x-2*y)/mup;	
				return divergence;
			}
			void div			(FVector_double& p, FVector_double& div) {
				double x = p[0], y=p[1];
				double r = sqrt(x*x + y*y);
				div.setAll((2*x-2*y)/mum,(2*x-2*y)/mup);
			}
			void	VF			(FVector_double& p, FVector_double& vF) {
				double x=p[0], y=p[1];
				double r = sqrt(x*x + y*y);
				if(Interface(p) <= 0 ) {
					vF[0] = -2-2*lambdam/mum;
					vF[1] = +2+2*lambdam/mum;
				}
				else 
				{
					vF[0] = -2-2*lambdap/mup;
					vF[1] = +2+2*lambdap/mup;
				}
			}
			void	VF			(FVector_double& p, FMatrix_double& vF) {
				double x=p[0], y=p[1];
				double r = sqrt(x*x + y*y);
				vF.setAll(-2-2*lambdam/mum, +2+2*lambdam/mum,
						-2-2*lambdap/mup, +2+2*lambdap/mup);
			}
		};
		class IIM_Eigen : public FEM_PROBLEM {
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);
				//RX = __.RX.make(__.dim, __.dim).setAll(-CV.PI/2.,-CV.PI/2., CV.PI/2.,CV.PI/2.);
				//RX = __.RX.make(__.dim, __.dim).setAll(-CV.PI,-CV.PI/2., CV.PI,CV.PI/2.);
				//RX = __.RX.make(__.dim, __.dim).setAll(0,0, CV.PI,CV.PI);

				printf("\n[0] Circle");
				printf("\n[1] Sharp edge");
				printf("\n[2] Star shape");
				printf("\n[3] Line");
				printf("\n[4] Sharp edge inside");
				printf("\n[5] Ellipse");
				printf("\n[6] Double Circle");
				printf("\n[7] Multi Circle - four circle");
				printf("\n[8] Multi Circle - five circle");
				printf("\n[9] Multi Circle - five circle-diagonal");

				Input("\nChoose a Interface", nInterface);

				Input("\nInterior mum", mum);
				Input("Exterior mup", mup);
				Input("Interior lambdam", lambdam);
				Input("Exterior lambdap", lambdap);

				switch (nInterface){
				case 0:
					Input("r", r0);
					break;
				case 1:
					Input("theta", k);
					k = k / 180.*CV.PI;
					break;
				case 3:
					vDirection.make(__.dim);													// 방향벡터의 왼쪽이 Omega^- 가 되도록 한다.
					vCenter.make(__.dim);														// 직선의 중심이 어디인지를 나타낸다.

					Input("center-x", vCenter[0]);
					Input("center-y", vCenter[1]);
					Input("x-direction", vDirection[0]);
					Input("y-direction", vDirection[1]);

					vDirection.normalize();
					MATH::rotate2D(vDirection, 0., 1., false);									// -90도 회전시킨다.
					break;
				case 5:
					Input("a", a);
					Input("b", b);
					break;
				case 6:
					Input("r0", r0);
					Input("r1", r1);
					break;
				case 7: // (0.5,0)을 0번째 원으로 시계반대로 한바퀴 돈다
					Input("r0", r0);
					Input("r1", r1);
					Input("r2", r2);
					Input("r3", r3);
					break;
				case 8:// (0,0)을 0번째 원, (0.6,0)을 1번째원으로 시계반대로 한바퀴 돈다
					Input("r0", r0);
					Input("r1", r1);
					Input("r2", r2);
					Input("r3", r3);
					Input("r4", r4);
					break;
				case 9:// (0,0)을 0번째 원, (0.5,0.5)을 1번째원으로 시계반대로 한바퀴 돈다 사분면 마다 원 하나
					Input("r0", r0);
					Input("r1", r1);
					Input("r2", r2);
					Input("r3", r3);
					Input("r4", r4);
					break;
				}
			}
			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				double theta = MATH::slope_to_radian(x, y);

				switch (nInterface) {
				case 0:	// kink(left)

					return r - r0;
				case 1:
					return y*y - (x - 1)*(x - 1)*tan(k)*tan(k)*x;
				case 2: // star shape
					return (r - 0.2*sin(5 * theta - CV.PI / 5) - 0.5);
				case 3:
					return (vDirection, p - vCenter);
				case 4:
					if (x <= 1 + x_intercept) 	return y*y - ((x - 1. - x_intercept)*tan(k))*((x - 1. - x_intercept)*tan(k))*(x - x_intercept);
					else			return 1.;
				case 5:
					r = sqrt(x*x / a / a + y*y / b / b);
					return (r - 1.);
				case 6:
					return ((x - 0.5)*(x - 0.5) + (y - 0.5)*(y - 0.5) - r0*r0)*((x + 0.3)*(x + 0.3) + (y + 0.3)*(y + 0.3) - r1*r1);
				case 7:
					return ((x - 0.5)*(x - 0.5) + y*y - r0*r0)*((x + 0.5)*(x + 0.5) + y*y - r2*r2)*((y - 0.5)*(y - 0.5) + x*x - r1*r1)*((y + 0.5)*(y + 0.5) + x*x - r3*r3);
				case 8:
					return ((x - 0.6)*(x - 0.6) + y*y - r1*r1)*((x + 0.6)*(x + 0.6) + y*y - r3*r3)*((y - 0.6)*(y - 0.6) + x*x - r2*r2)*((y + 0.6)*(y + 0.6) + x*x - r4*r4)*(x*x + y*y - r0*r0);
				case 9:
					return ((x - 0.5)*(x - 0.5) + (y - 0.5)*(y - 0.5) - r1*r1)*((x + 0.5)*(x + 0.5) + (y + 0.5)*(y + 0.5) - r3*r3)*((y - 0.5)*(y - 0.5) + (x + 0.5)*(x + 0.5) - r2*r2)*((y + 0.5)*(y + 0.5) + (x - 0.5)*(x - 0.5) - r4*r4)*(x*x + y*y - r0*r0);
				}
				return 0;
			}
			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}
			double	coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) < 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}
			double	coef_lambda(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(lambdam, lambdap);														// (Interior, Exterior)
				return 0;
			}
			double	coef_lambda(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_lambda(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double	coef_lambda(FVector_double& p) {
				static FVector_double mus(2);
				coef_lambda(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) < 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}
		};
	};
	class BIHARMONIC {
	public:
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		//============================================================================
		//                                ID
		//============================================================================
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		class ID {
		public:
			enum {P_BRAESS, P_SINCOS};
		};
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		//============================================================================
		//                            BIHARMONIC_BRAESS
		//============================================================================
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		class P_BRAESS: public FEM_PROBLEM {	// △△u = f
		public:
			void	initialize	(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(0.,0., 1.,1.);
			}

			double	P	(FVector_double& p) {
				double x=p[0], y=p[1];
				return 256*x*x*(1-x)*(1-x)*y*y*(1-y)*(1-y);	
			}

			void	DP	(FVector_double &p, FVector_double &dp) {
				double x=p[0], y=p[1];
				dp.setAll((1-2*x)*(1-y)*y, x*(1-x)*(1-2*y)) *= (512*x*(1-x)*y*(1-y));
			}
			
			double	F	(FVector_double& p) {
				double x=p[0], y=p[1];
				return 6144*(x*x*(1-x)*(1-x) + y*y*(1-y)*(1-y)) + 2048*(1-6*x+6*x*x)*(1-6*y+6*y*y);	
			}
		};
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		//============================================================================
		//                            BIHARMONIC_SINCOS
		//============================================================================
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		class P_SINCOS: public FEM_PROBLEM {	// △△u = f
		public:
			void	initialize	(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1.,-1., 1.,1.);
			}

			double	P	(FVector_double& p) {
				double x=p[0], y=p[1];
				return sin(2*CV.PI*x)*cos(CV.PI*y);	
			}

			void	DP	(FVector_double &p, FVector_double &dp) {
				double x=p[0], y=p[1];
				dp.setAll(2*CV.PI*cos(2*CV.PI*x)*cos(CV.PI*y), -CV.PI*sin(2*CV.PI*x)*sin(CV.PI*y));
			}
			
			double	F	(FVector_double& p) {
				double x=p[0], y=p[1];
				return 25*$(CV.PI,4)*sin(2*CV.PI*x)*cos(CV.PI*y);	
			}
		};
	};
	class PARABOLIC{
	public:
		class ID{
		public:
			enum{ Li_sample, Boundary_zero, Elementary, test_problem1, test_problem2 };
		};
		class Li_sample : public FEM_PROBLEM{
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				Input("r0", r0);
				Input("Initial time", ini_time);
				Input("Terminal time", ter_time);
				Input("maximum time step", time_step);
				Input("mum", mum);
				Input("mup", mup);

				__.time_step = time_step;
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);
			}

			double	Interface(double r, double t) {												// 내부에서 음수의 값을 가지도록 한다.
				return (r - r0);
			}

			double	Interface(FVector_double& p, double t) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				return (r - r0);
			}

			double	coef_mu(FVector_double& p, FVector_double& mus, double t) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0.;

			}
			double	coef_mu(FVector_double& p, double t) {
				static FVector_double mus(2);
				coef_mu(p, mus, t);															// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p, t) <= 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}

			double	P(FVector_double& p, FVector_double& ps, double t) {
				double x = p[0], y = p[1];
				ps.setAll(1 / t * exp(-(x*x + y*y) / (4 * mum*t)), 1 / t * exp(-(x*x + y*y) / (4 * mup*t)));															// (Interior, Exterior)
				return 0;
			}

			double	P(FVector_double& p, double t) {
				static FVector_double ps(2);
				P(p, ps, t);																	// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p, t) <= 0) {
					return ps[0];
				}
				else {
					return ps[1];
				}
			}

			void	DP(FVector_double& p, FMatrix_double& dps, double t) {
				double x = p[0], y = p[1];
				dps.setAll(
					-x / (2 * mum*t*t) *(exp((-x*x - y*y) / (4 * mum*t))), -y / (2 * mum*t*t) *(exp((-x*x - y*y) / (4 * mum*t))),
					-x / (2 * mup*t*t) *(exp((-x*x - y*y) / (4 * mup*t))), -y / (2 * mup*t*t) *(exp((-x*x - y*y) / (4 * mup*t)))
					);
			}

			void	DP(FVector_double& p, FVector_double& dp, double t) {
				static FMatrix_double dps(2, 2);
				DP(p, dps, t);

				if (Interface(p, t) <= 0) {
					dp = dps[0];
				}
				else {
					dp = dps[1];
				}
			}

			void iniP(FVector_double& p, FVector_double& ps) {
				double x = p[0], y = p[1];
				ps.setAll(exp(-(x*x + y*y) / 4.*mum), exp(-(x*x + y*y) / 4.*mup));
			}

			void endP(FVector_double& p, FVector_double& ps) {
				double x = p[0], y = p[1];
				ps.setAll(1. / 2. * exp(-(x*x + y*y) / (8.*mum)), 1. / 2. * exp(-(x*x + y*y) / (8.*mup)));
			}

			double  F(FVector_double& p, FVector_double& fs, double t)
			{
				double x = p[0], y = p[1];
				fs.setAll(0., 0.);
				return 0;
			}

			double	F(FVector_double& p, double t) {
				static FVector_double fs(2);
				F(p, fs, t);
				if (Interface(p, t) <= 0) {
					return fs[0];
				}
				else {
					return fs[1];
				}
			}
		};
		class Boundary_zero : public FEM_PROBLEM{
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				//r0 = 0.48;
				Input("r0", r0);
				Input("maximum time step", time_step);
				Input("mum", mum);
				Input("mup", mup);
				//mum = mup = 1;

				__.time_step = time_step;
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);
			}

			double	Interface(double r, double t) {												// 내부에서 음수의 값을 가지도록 한다.
				return (r - r0);
			}

			double	Interface(FVector_double& p, double t) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				return (r - r0);
			}

			double	coef_mu(FVector_double& p, FVector_double& mus, double t) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;

			}
			double	coef_mu(FVector_double& p, double t = 0) {
				static FVector_double mus(2);
				coef_mu(p, mus, t);															// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p, t) <= 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}

			double	P(FVector_double& p, FVector_double& ps, double t) {
				double x = p[0], y = p[1];
				ps.setAll((x*x - 1.)*(y*y - 1.)*1. / t * exp(-(x*x + y*y) / 4.*mum*t), (x*x - 1)*(y*y - 1)*1. / t * exp(-(x*x + y*y) / 4.*mup*t));															// (Interior, Exterior)
				return 0;
			}

			double	P(FVector_double& p, double t = 0) {
				static FVector_double ps(2);
				P(p, ps, t);																	// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p, t) <= 0) {
					return ps[0];
				}
				else {
					return ps[1];
				}
			}
			void	DP(FVector_double& p, FMatrix_double& dps, double t) {
				double x = p[0], y = p[1];
				dps.setAll(
					-x*(y*y - 1.)*(-x*x + 4.*mum*t + 1.) / (2.*t*t) *(exp(-x*x - y*y) / 4.*mum*t), -x*(y*y - 1.)*(-x*x + 4.*mum*t + 1.) / (2.*t*t) *(exp(-x*x - y*y) / 4.*mup*t),
					-y*(x*x - 1.)*(-x*x + 4.*mum*t + 1.) / (2.*t*t) *(exp(-x*x - y*y) / 4.*mum*t), -y*(x*x - 1.)*(-x*x + 4.*mum*t + 1.) / (2.*t*t) *(exp(-x*x - y*y) / 4.*mum*t)
					);
			}

			void	DP(FVector_double& p, FVector_double& dp, double t) {
				static FMatrix_double dps(2, 2);
				DP(p, dps, t);

				if (Interface(p, t) <= 0) {
					dp = dps[0];
				}
				else {
					dp = dps[1];
				}
			}

			void iniP(FVector_double& p, FVector_double& ps) {
				double x = p[0], y = p[1];
				ps.setAll((x*x - 1.)*(y*y - 1.)*exp(-(x*x + y*y) / 4.*mum), (x*x - 1.)*(y*y - 1.)*exp(-(x*x + y*y) / 4.*mup));
			}

			void endP(FVector_double& p, FVector_double& ps) {
				double x = p[0], y = p[1];
				Pause(mup);
				ps.setAll(1. / 2.*(x*x - 1.)*(y*y - 1.)* exp(-(x*x + y*y) / 8.*mum), 1. / 2.*(x*x - 1.)*(y*y - 1.) * exp(-(x*x + y*y) / 8.*mup));
			}

			double  F(FVector_double& p, FVector_double& fs, double t)
			{
				double x = p[0], y = p[1];
				fs.setAll(((mum*(4.*t - 2.*x*x*y*y + x*x*y*y*y*y + x*x*x*x*y*y - 12.*t*x*x - 12.*t*y*y + x*x - x*x*x*x + y*y - y*y*y*y + 20.*t*x*x*y*y)) / (4.*exp((x*x + y*y) / (4.*mum*t))) - ((x*x + y*y)*(x*x - 1.)*(y*y - 1.)) / (4.*exp((x*x + y*y) / (4.*mum*t)))) / (mum*mum*t*t*t) - (x*x*y*y - 4.*t + 2.*t*x*x + 2.*t*y*y - x*x - y*y + 1.) / (t*t*exp((x*x + y*y) / (4.*mum*t))), ((mup*(4.*t - 2.*x*x*y*y + x*x*y*y*y*y + x*x*x*x*y*y - 12.*t*x*x - 12.*t*y*y + x*x - x*x*x*x + y*y - y*y*y*y + 20.*t*x*x*y*y)) / (4.*exp((x*x + y*y) / (4.*mup*t))) - ((x*x + y*y)*(x*x - 1.)*(y*y - 1.)) / (4.*exp((x*x + y*y) / (4.*mup*t)))) / (mup*mup*t*t*t) - (x*x*y*y - 4.*t + 2.*t*x*x + 2.*t*y*y - x*x - y*y + 1.) / (t*t*exp((x*x + y*y) / (4.*mup*t))));
				return 0;
			}

			double	F(FVector_double& p, double t) {
				static FVector_double fs(2);
				F(p, fs, t);
				if (Interface(p, t) <= 0) {
					return fs[0];
				}
				else {
					return fs[1];
				}
			}
		};
		class Elementary : public FEM_PROBLEM{ // not iim problem
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __)
			{
				Input("Initial time", ini_time);
				Input("Terminal time", ter_time);
				Input("maximum time step", time_step);
				__.time_step = time_step;
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);
			}
			void	coef_mMu(FVector_double& p, FMatrix_double& mMu) {
				double x = p[0], y = p[1];
				mMu.setAll(1., 0., 0., 1.);
			}

			void	coef_cDMu(FVector_double& p, FCube_double& cDMu) {
				double x = p[0], y = p[1];
				cDMu.setAll(0., 0., 0., 0., 0., 0., 0., 0.);
			}
			double	P(FVector_double& p, double t) {
				double x = p[0], y = p[1];
				return (1. / t * exp(-(x*x + y*y) / (4 * t)));
			}

			void	DP(FVector_double& p, FVector_double& dp, double t) {
				double x = p[0], y = p[1];
				dp.setAll(-x / (2.*t*t)*exp(-(x*x + y*y) / (4.*t)), -y / (2.*t*t)*exp(-(x*x + y*y) / (4.*t)));
			}

			double iniP(FVector_double& p) {
				//double x = p[0], y= p[1];
				return P(p, ini_time);
				//return exp(-(x*x+y*y)/4.);		
			}

			double endP(FVector_double& p) {
				//double x = p[0], y= p[1];
				return P(p, ter_time);
				//return 1./2. * exp(-(x*x + y*y)/(8.));
			}

			double	F(FVector_double& p, double t) {
				return 0.;
			}
		};
		class Elementary2 : public FEM_PROBLEM{ //not iim problem
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __)
			{
				Input("r0", r0);
				Input("Initial time", ini_time);
				Input("Terminal time", ter_time);
				Input("maximum time step", time_step);
				__.time_step = time_step;
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);
			}
			void	coef_mMu(FVector_double& p, FMatrix_double& mMu) {
				double x = p[0], y = p[1];
				mMu.setAll(1., 0., 0., 1.);
			}

			void	coef_cDMu(FVector_double& p, FCube_double& cDMu) {
				double x = p[0], y = p[1];
				cDMu.setAll(0., 0., 0., 0., 0., 0., 0., 0.);
			}
			double	P(FVector_double& p, double t) {
				double x = p[0], y = p[1];
				return (1. / t * exp(-(x*x + y*y - r0*r0) / (4 * t)));
			}

			void	DP(FVector_double& p, FVector_double& dp, double t) {
				double x = p[0], y = p[1];
				dp.setAll(-x / (2.*t*t)*exp(-(x*x + y*y - r0*r0) / (4.*t)), -y / (2.*t*t)*exp(-(x*x + y*y - r0*r0) / (4.*t)));
			}

			double iniP(FVector_double& p) {
				//double x = p[0], y= p[1];
				return P(p, ini_time);
				//return exp(-(x*x+y*y)/4.);		
			}

			double endP(FVector_double& p) {
				//double x = p[0], y= p[1];
				return P(p, ter_time);
				//return 1./2. * exp(-(x*x + y*y)/(8.));
			}

			double	F(FVector_double& p, double t) {
				double x = p[0], y = p[1];
				return -r0*r0 / (4.*t*t*t)*exp(-(x*x + y*y - r0*r0) / (4.*t));
			}
		};
		class Elementary3 : public FEM_PROBLEM{ // not iim problem
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __)
			{
				Input("r0", r0);
				Input("Initial time", ini_time);
				Input("Terminal time", ter_time);
				Input("maximum time step", time_step);
				Input("mum", mum);
				__.time_step = time_step;
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);
			}
			void	coef_mMu(FVector_double& p, FMatrix_double& mMu) {
				double x = p[0], y = p[1];
				mMu.setAll(1., 0., 0., 1.);
			}

			void	coef_cDMu(FVector_double& p, FCube_double& cDMu) {
				double x = p[0], y = p[1];
				cDMu.setAll(0., 0., 0., 0., 0., 0., 0., 0.);
			}
			double	P(FVector_double& p, double t) {
				double x = p[0], y = p[1];
				return 1. / t * exp(-(x*x + y*y - r0*r0) / (4 * mum*t));
			}

			void	DP(FVector_double& p, FVector_double& dp, double t) {
				double x = p[0], y = p[1];
				dp.setAll(-x / (2.*mum*t*t)*exp(-(x*x + y*y - r0*r0) / (4.*mum*t)), -y / (2.*mum*t*t)*exp(-(x*x + y*y - r0*r0) / (4.*mum*t)));
			}

			double iniP(FVector_double& p) {
				return P(p, ini_time);
			}

			double endP(FVector_double& p) {
				return P(p, ter_time);
			}

			double  F(FVector_double& p, double t)
			{
				double x = p[0], y = p[1];
				return -r0*r0 / (4.*mum*t*t*t)*exp(-(x*x + y*y - r0*r0) / (4.*mum*t));
			}
		};
		class Elementary_IIM : public FEM_PROBLEM{
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __)
			{
				Input("r0", r0);
				Input("Initial time", ini_time);
				Input("Terminal time", ter_time);
				Input("maximum time step", time_step);
				Input("mum", mum);
				Input("mup", mup);
				__.time_step = time_step;
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);
			}
			double	Interface(double r, double t) {												// 내부에서 음수의 값을 가지도록 한다.
				return (r - r0);
			}
			double	Interface(FVector_double& p, double t) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				return (r - r0);
			}
			double	coef_mu(FVector_double& p, FVector_double& mus, double t) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}
			double	coef_mu(FVector_double& p, double t) {
				static FVector_double mus(2);
				coef_mu(p, mus, t);															// 두 값을 호출해서 알맞게 돌려준다.
				if (Interface(p, t) <= 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}

			double	P(FVector_double& p, FVector_double& ps, double t) {
				double x = p[0], y = p[1];
				ps.setAll(1. / t * exp(-(x*x + y*y - r0*r0) / (4 * mum*t)), 1. / t * exp(-(x*x + y*y - r0*r0) / (4 * mup*t)));															// (Interior, Exterior)
				return 0;
			}

			double	P(FVector_double& p, double t) {
				static FVector_double ps(2);
				P(p, ps, t);																	// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p, t) <= 0) {
					return ps[0];
				}
				else {
					return ps[1];
				}
			}

			void	DP(FVector_double& p, FMatrix_double& dps, double t) {
				double x = p[0], y = p[1];
				dps.setAll(
					-x / (2.*mum*t*t)*exp(-(x*x + y*y - r0*r0) / (4.*mum*t)), -y / (2.*mum*t*t)*exp(-(x*x + y*y - r0*r0) / (4.*mum*t)),
					-x / (2.*mup*t*t)*exp(-(x*x + y*y - r0*r0) / (4.*mup*t)), -y / (2.*mup*t*t)*exp(-(x*x + y*y - r0*r0) / (4.*mup*t))
					);
			}

			void	DP(FVector_double& p, FVector_double& dp, double t) {
				static FMatrix_double dps(2, 2);
				DP(p, dps, t);
				double x = p[0], y = p[1];
				if (Interface(p, t) <= 0) {
					dp = dps[0];
				}
				else {
					dp = dps[1];
				}
			}
			double iniP(FVector_double& p) {
				return P(p, ini_time);
			}

			double endP(FVector_double& p) {
				return P(p, ter_time);
			}

			double  F(FVector_double& p, FVector_double& fs, double t)
			{
				double x = p[0], y = p[1];
				fs.setAll(-r0*r0 / (4.*mum*t*t*t)*exp(-(x*x + y*y - r0*r0) / (4.*mum*t)), -r0*r0 / (4.*mup*t*t*t)*exp(-(x*x + y*y - r0*r0) / (4.*mup*t)));
				return 0;
			}

			double	F(FVector_double& p, double t) {
				static FVector_double fs(2);
				F(p, fs, t);
				if (Interface(p, t) <= 0) {
					return fs[0];
				}
				else {
					return fs[1];
				}
			}
		};
		class IIM_SECTOR : public FEM_PROBLEM {
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				Input("r0", r0);
				Input("Initial time", ini_time);
				Input("Terminal time", ter_time);
				Input("maximum time step for lowest level", time_step);
				Input("mum", mum);
				Input("mup", mup);
				__.time_step = time_step;
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);
			}
			double	Interface(FVector_double& p, double t) {
				double x = p[0], y = p[1];
				double r = sqrt((x - 1)*(x - 1) + (y + 1)*(y + 1));
				return (r - r0);
			}
			double	coef_mu(FVector_double& p, FVector_double& mus, double t) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}
			double	coef_mu(FVector_double& p, double t) {
				static FVector_double mus(2);
				coef_mu(p, mus, t);															// 두 값을 호출해서 알맞게 돌려준다.
				if (Interface(p, t) <= 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}
			double	P(FVector_double& p, FVector_double& ps, double t) {
				double x = p[0], y = p[1];
				ps.setAll(t*((x - 1)*(x - 1) + (y + 1)*(y + 1) - r0*r0)*sin(CV.PI*x)*sin(CV.PI*y) / mum, t*((x - 1)*(x - 1) + (y + 1)*(y + 1) - r0*r0)*sin(CV.PI*x)*sin(CV.PI*y) / mup);
				return 0;
			}
			double	P(FVector_double& p, double t) {
				static FVector_double ps(2);
				P(p, ps, t);																	// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p, t) <= 0) {
					return ps[0];
				}
				else {
					return ps[1];
				}
			}
			void	DP(FVector_double& p, FMatrix_double& dps, double t) {
				double x = p[0], y = p[1];
				dps.setAll(
					t*(2 * (x - 1)*sin(CV.PI*x)*sin(CV.PI*y) + CV.PI*((x - 1)*(x - 1) + (y + 1)*(y + 1) - r0*r0)*cos(CV.PI*x)*sin(CV.PI*y)) / mum, t*(2 * (y + 1)*sin(CV.PI*x)*sin(CV.PI*y) + CV.PI*((x - 1)*(x - 1) + (y + 1)*(y + 1) - r0*r0)*sin(CV.PI*x)*cos(CV.PI*y)) / mum,
					t*(2 * (x - 1)*sin(CV.PI*x)*sin(CV.PI*y) + CV.PI*((x - 1)*(x - 1) + (y + 1)*(y + 1) - r0*r0)*cos(CV.PI*x)*sin(CV.PI*y)) / mup, t*(2 * (y + 1)*sin(CV.PI*x)*sin(CV.PI*y) + CV.PI*((x - 1)*(x - 1) + (y + 1)*(y + 1) - r0*r0)*sin(CV.PI*x)*cos(CV.PI*y)) / mup
					);
			}
			void	DP(FVector_double& p, FVector_double& dp, double t) {
				static FMatrix_double dps(2, 2);
				DP(p, dps, t);
				double x = p[0], y = p[1];
				if (Interface(p, t) <= 0) {
					dp = dps[0];
				}
				else {
					dp = dps[1];
				}
			}
			double  F(FVector_double& p, FVector_double& fs, double t)
			{
				double x = p[0], y = p[1];
				fs.setAll(
					((x - 1)*(x - 1) + (y + 1)*(y + 1) - r0*r0)*sin(CV.PI*x)*sin(CV.PI*y) / mum - t*(2 * sin(CV.PI*x)*sin(CV.PI*y) + 2 * (x - 1)*CV.PI*cos(CV.PI*x)*sin(CV.PI*y) + 2 * (x - 1)*CV.PI*cos(CV.PI*x)*sin(CV.PI*y) - CV.PI*CV.PI*((x - 1)*(x - 1) + (y + 1)*(y + 1) - r0*r0)*sin(CV.PI*x)*sin(CV.PI*y) + 2 * sin(CV.PI*x)*sin(CV.PI*y) + 2 * (y + 1)*CV.PI*sin(CV.PI*x)*cos(CV.PI*y) + 2 * (y + 1)*CV.PI*sin(CV.PI*x)*cos(CV.PI*y) - CV.PI*CV.PI*((x - 1)*(x - 1) + (y + 1)*(y + 1) - r0*r0)*sin(CV.PI*x)*sin(CV.PI*y)),
					((x - 1)*(x - 1) + (y + 1)*(y + 1) - r0*r0)*sin(CV.PI*x)*sin(CV.PI*y) / mup - t*(2 * sin(CV.PI*x)*sin(CV.PI*y) + 2 * (x - 1)*CV.PI*cos(CV.PI*x)*sin(CV.PI*y) + 2 * (x - 1)*CV.PI*cos(CV.PI*x)*sin(CV.PI*y) - CV.PI*CV.PI*((x - 1)*(x - 1) + (y + 1)*(y + 1) - r0*r0)*sin(CV.PI*x)*sin(CV.PI*y) + 2 * sin(CV.PI*x)*sin(CV.PI*y) + 2 * (y + 1)*CV.PI*sin(CV.PI*x)*cos(CV.PI*y) + 2 * (y + 1)*CV.PI*sin(CV.PI*x)*cos(CV.PI*y) - CV.PI*CV.PI*((x - 1)*(x - 1) + (y + 1)*(y + 1) - r0*r0)*sin(CV.PI*x)*sin(CV.PI*y)));
				return 0;
			}
			double	F(FVector_double& p, double t) {
				static FVector_double fs(2);
				F(p, fs, t);
				if (Interface(p, t) <= 0) {
					return fs[0];
				}
				else {
					return fs[1];
				}
			}
		};
		class IIM_TIME_JUMP : public FEM_PROBLEM {
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				Input("r0", r0);
				Input("Initial time", ini_time);
				Input("Terminal time", ter_time);
				Input("maximum time step for first ", time_step);
				Input("mum", mum);
				Input("mup", mup);
				__.time_step = time_step;
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);
			}
			double	Interface(FVector_double& p, double t) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				return (r - r0);
			}
			double	coef_mu(FVector_double& p, FVector_double& mus, double t) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}
			double	coef_mu(FVector_double& p, double t) {
				static FVector_double mus(2);
				coef_mu(p, mus, t);															// 두 값을 호출해서 알맞게 돌려준다.
				if (Interface(p, t) <= 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}
			double	P(FVector_double& p, FVector_double& ps, double t) {
				double x = p[0], y = p[1];
				ps.setAll(t*(x*x + y*y - r0*r0)*cos(CV.PI*x)*cos(CV.PI*y) / mum, t*(x*x + y*y - r0*r0)*sin(CV.PI*x)*sin(CV.PI*y) / mup);
				return 0;
			}
			double	P(FVector_double& p, double t) {
				static FVector_double ps(2);
				P(p, ps, t);																	// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p, t) <= 0) {
					return ps[0];
				}
				else {
					return ps[1];
				}
			}
			double  Flux_Jump(FVector_double& p, FVector_double& vN, double t)
			{
				static FMatrix_double dps(2, 2);
				static FVector_double mus(2);
				double x = p[0], y = p[1];
				DP(p, dps, t);
				coef_mu(p, mus, t);
				return (mus[0] * dps[0] - mus[1] * dps[1], vN);
			}
			void	DP(FVector_double& p, FMatrix_double& dps, double t) {
				double x = p[0], y = p[1];
				dps.setAll(
					t*(2 * x*cos(CV.PI*x)*cos(CV.PI*y) - CV.PI*(x*x + y*y - r0*r0)*sin(CV.PI*x)*cos(CV.PI*y)) / mum, t*(2 * y*cos(CV.PI*x)*cos(CV.PI*y) - CV.PI*(x*x + y*y - r0*r0)*cos(CV.PI*x)*sin(CV.PI*y)) / mum,
					t*(2 * x*sin(CV.PI*x)*sin(CV.PI*y) + CV.PI*(x*x + y*y - r0*r0)*cos(CV.PI*x)*sin(CV.PI*y)) / mup, t*(2 * y*sin(CV.PI*x)*sin(CV.PI*y) + CV.PI*(x*x + y*y - r0*r0)*sin(CV.PI*x)*cos(CV.PI*y)) / mup
					);
			}
			void	DP(FVector_double& p, FVector_double& dp, double t) {
				static FMatrix_double dps(2, 2);
				DP(p, dps, t);
				double x = p[0], y = p[1];
				if (Interface(p, t) <= 0) {
					dp = dps[0];
				}
				else {
					dp = dps[1];
				}
			}
			double  F(FVector_double& p, FVector_double& fs, double t)
			{
				double x = p[0], y = p[1];
				fs.setAll(
					(x*x + y*y - r0*r0)*cos(CV.PI*x)*cos(CV.PI*y) / mum - t*(2 * cos(CV.PI*x)*cos(CV.PI*y) - 2 * x*CV.PI*sin(CV.PI*x)*cos(CV.PI*y) - 2 * x*CV.PI*sin(CV.PI*x)*cos(CV.PI*y) - CV.PI*CV.PI*(x*x + y*y - r0*r0)*cos(CV.PI*x)*cos(CV.PI*y) + 2 * cos(CV.PI*x)*cos(CV.PI*y) - 2 * y*CV.PI*cos(CV.PI*x)*sin(CV.PI*y) - 2 * y*CV.PI*cos(CV.PI*x)*sin(CV.PI*y) - CV.PI*CV.PI*(x*x + y*y - r0*r0)*cos(CV.PI*x)*cos(CV.PI*y)),
					(x*x + y*y - r0*r0)*sin(CV.PI*x)*sin(CV.PI*y) / mup - t*(2 * sin(CV.PI*x)*sin(CV.PI*y) + 2 * x*CV.PI*cos(CV.PI*x)*sin(CV.PI*y) + 2 * x*CV.PI*cos(CV.PI*x)*sin(CV.PI*y) - CV.PI*CV.PI*(x*x + y*y - r0*r0)*sin(CV.PI*x)*sin(CV.PI*y) + 2 * sin(CV.PI*x)*sin(CV.PI*y) + 2 * y*CV.PI*sin(CV.PI*x)*cos(CV.PI*y) + 2 * y*CV.PI*sin(CV.PI*x)*cos(CV.PI*y) - CV.PI*CV.PI*(x*x + y*y - r0*r0)*sin(CV.PI*x)*sin(CV.PI*y)));
				return 0;
			}
			double	F(FVector_double& p, double t) {
				static FVector_double fs(2);
				F(p, fs, t);
				if (Interface(p, t) <= 0) {
					return fs[0];
				}
				else {
					return fs[1];
				}
			}
		};
		class IIM_COEFFICIENT_JUMP : public FEM_PROBLEM{
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __)
			{
				Input("r0", r0);
				Input("Initial time", ini_time);
				Input("Terminal time", ter_time);
				Input("mum", mum);
				Input("mup", mup);
				Input("maximum time step", time_step);
				__.time_step = time_step;
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);
			}
			double	Interface(double r, double t) {												// 내부에서 음수의 값을 가지도록 한다.
				return (r - r0);
			}
			double	Interface(FVector_double& p, double t) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				return (r - r0);
			}
			double	coef_mu(FVector_double& p, FVector_double& mus, double t) {
				double x = p[0], y = p[1];
				mus.setAll(mum*exp(-t), mup*exp(-t));														// (Interior, Exterior)
				return 0;
			}
			double	coef_mu(FVector_double& p, double t) {
				static FVector_double mus(2);
				coef_mu(p, mus, t);															// 두 값을 호출해서 알맞게 돌려준다.
				if (Interface(p, t) <= 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}
			double	P(FVector_double& p, FVector_double& ps, double t) {
				double x = p[0], y = p[1];
				static FVector_double mus(2);
				coef_mu(p, mus, t);
				ps.setAll(t*(x*x + y*y - r0*r0)*(x*x + y*y - r0*r0) / mus[0], t*(x*x + y*y - r0*r0)*(x*x + y*y - r0*r0) / mus[1]);
				return 0;
			}
			double	P(FVector_double& p, double t) {
				static FVector_double ps(2);
				P(p, ps, t);																	// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p, t) <= 0) {
					return ps[0];
				}
				else {
					return ps[1];
				}
			}
			void	DP(FVector_double& p, FMatrix_double& dps, double t) {
				double x = p[0], y = p[1];
				static FVector_double mus(2);
				coef_mu(p, mus, t);
				dps.setAll(
					4 * t*(x*x + y*y - r0*r0)*x / mus[0], 4 * t*(x*x + y*y - r0*r0)*y / mus[0],
					4 * t*(x*x + y*y - r0*r0)*x / mus[1], 4 * t*(x*x + y*y - r0*r0)*y / mus[1]
					);
			}
			void	DP(FVector_double& p, FVector_double& dp, double t) {
				static FMatrix_double dps(2, 2);
				DP(p, dps, t);
				double x = p[0], y = p[1];
				if (Interface(p, t) <= 0) {
					dp = dps[0];
				}
				else {
					dp = dps[1];
				}
			}
			double  F(FVector_double& p, FVector_double& fs, double t)
			{
				double x = p[0], y = p[1];
				static FVector_double mus(2);
				coef_mu(p, mus, t);
				fs.setAll(
					(x*x + y*y - r0*r0)*(x*x + y*y - r0*r0)*(1 + t) / mus[0] - 8 * (x*x + y*y - r0*r0)*t - 8 * x*x*t - 8 * y*y*t,
					(x*x + y*y - r0*r0)*(x*x + y*y - r0*r0)*(1 + t) / mus[1] - 8 * (x*x + y*y - r0*r0)*t - 8 * x*x*t - 8 * y*y*t
					);
				return 0;
			}
			double	F(FVector_double& p, double t) {
				static FVector_double fs(2);
				F(p, fs, t);
				if (Interface(p, t) <= 0) {
					return fs[0];
				}
				else {
					return fs[1];
				}
			}
		};
		class IIM_COEFFICIENT_JUMP_WITH_MOVING : public FEM_PROBLEM{
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __)
			{
				Input("r0", r0);
				Input("Initial time", ini_time);
				Input("Terminal time", ter_time);
				Input("mum", mum);
				Input("mup", mup);
				Input("maximum time step", time_step);
				__.time_step = time_step;
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);
			}
			double	Interface(FVector_double& p, double t) {
				double x = p[0], y = p[1];
				double r = sqrt((x + 1.5 - t)*(x + 1.5 - t) + y*y);
				return (r - r0);
			}
			double	coef_mu(FVector_double& p, FVector_double& mus, double t) {
				double x = p[0], y = p[1];
				mus.setAll(mum*exp(-t), mup*exp(-t));														// (Interior, Exterior)
				return 0;
			}
			double	coef_mu(FVector_double& p, double t) {
				static FVector_double mus(2);
				coef_mu(p, mus, t);															// 두 값을 호출해서 알맞게 돌려준다.
				if (Interface(p, t) <= 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}
			double	P(FVector_double& p, FVector_double& ps, double t) {
				double x = p[0], y = p[1];
				static FVector_double mus(2);
				coef_mu(p, mus, t);
				ps.setAll(t*((x + 1.5 - t)*(x + 1.5 - t) + y*y - r0*r0)*((x + 1.5 - t)*(x + 1.5 - t) + y*y - r0*r0) / mus[0], t*((x + 1.5 - t)*(x + 1.5 - t) + y*y - r0*r0)*((x + 1.5 - t)*(x + 1.5 - t) + y*y - r0*r0) / mus[1]);
				return 0;
			}
			double	P(FVector_double& p, double t) {
				static FVector_double ps(2);
				P(p, ps, t);																	// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p, t) <= 0) {
					return ps[0];
				}
				else {
					return ps[1];
				}
			}
			void	DP(FVector_double& p, FMatrix_double& dps, double t) {
				double x = p[0], y = p[1];
				static FVector_double mus(2);
				coef_mu(p, mus, t);
				dps.setAll(
					4 * t*((x + 1.5 - t)*(x + 1.5 - t) + y*y - r0*r0)*(x + 1.5 - t) / mus[0], 4 * t*((x + 1.5 - t)*(x + 1.5 - t) + y*y - r0*r0)*y / mus[0],
					4 * t*((x + 1.5 - t)*(x + 1.5 - t) + y*y - r0*r0)*(x + 1.5 - t) / mus[1], 4 * t*((x + 1.5 - t)*(x + 1.5 - t) + y*y - r0*r0)*y / mus[1]
					);
			}
			void	DP(FVector_double& p, FVector_double& dp, double t) {
				static FMatrix_double dps(2, 2);
				DP(p, dps, t);
				double x = p[0], y = p[1];
				if (Interface(p, t) <= 0) {
					dp = dps[0];
				}
				else {
					dp = dps[1];
				}
			}
			double  F(FVector_double& p, FVector_double& fs, double t)
			{
				double x = p[0], y = p[1];
				static FVector_double mus(2);
				coef_mu(p, mus, t);
				fs.setAll(
					((x + 1.5 - t)*(x + 1.5 - t) + y*y - r0*r0)*((x + 1.5 - t)*(x + 1.5 - t) + y*y - r0*r0)*(1 + t) / mus[0] - 4 * ((x + 1.5 - t)*(x + 1.5 - t) + y*y - r0*r0)*t / mus[0] - 8 * ((x + 1.5 - t)*(x + 1.5 - t) + y*y - r0*r0)*t - 8 * (x + 1.5 - t)*(x + 1.5 - t)*t - 8 * y*y*t,
					((x + 1.5 - t)*(x + 1.5 - t) + y*y - r0*r0)*((x + 1.5 - t)*(x + 1.5 - t) + y*y - r0*r0)*(1 + t) / mus[1] - 4 * ((x + 1.5 - t)*(x + 1.5 - t) + y*y - r0*r0)*t / mus[1] - 8 * ((x + 1.5 - t)*(x + 1.5 - t) + y*y - r0*r0)*t - 8 * (x + 1.5 - t)*(x + 1.5 - t)*t - 8 * y*y*t
					);
				return 0;
			}
			double	F(FVector_double& p, double t) {
				static FVector_double fs(2);
				F(p, fs, t);
				if (Interface(p, t) <= 0) {
					return fs[0];
				}
				else {
					return fs[1];
				}
			}
		};
		class test_problem_time1 : public FEM_PROBLEM{ // not iim problem
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __)
			{
				Input("mum", mum);
				Input("Initial time", ini_time);
				Input("Terminal time", ter_time);
				Input("maximum time step", time_step);
				__.time_step = time_step;
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(0., 0., 1., 1.);
			}
			double	P(FVector_double& p, double t) {
				double x = p[0], y = p[1];
				return (t*(1 - x)*x*(1 - y)*y);
			}
			void	DP(FVector_double& p, FVector_double& dp, double t) {
				double x = p[0], y = p[1];
				dp.setAll((1 - 2 * x)*(y - y*y)*t, (1 - 2 * y)*(x - x*x)*t);
			}
			double iniP(FVector_double& p) {
				//double x = p[0], y= p[1];
				return P(p, ini_time);
				//return exp(-(x*x+y*y)/4.);		
			}
			double endP(FVector_double& p) {
				//double x = p[0], y= p[1];
				return P(p, ter_time);
				//return 1./2. * exp(-(x*x + y*y)/(8.));
			}
			double	coef_mu(FVector_double& p, double t) {
				return mum*t;
			}
			double	F(FVector_double& p, double t)
			{
				double x = p[0], y = p[1];
				return (1 - x)*(1 - y)*x*y + mum*(2 * (x - x*x) + 2 * (y - y*y))*t*t;
			}
		};
		class test_problem1 : public FEM_PROBLEM{ // not iim problem
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __)
			{
				Input("mum", mum);
				Input("Initial time", ini_time);
				Input("Terminal time", ter_time);
				Input("maximum time step", time_step);
				__.time_step = time_step;
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(0., 0., 1., 1.);
			}

			double	P(FVector_double& p, double t) {
				double x = p[0], y = p[1];
				return (t*(1 - x)*x*(1 - y)*y);
			}

			void	DP(FVector_double& p, FVector_double& dp, double t) {
				double x = p[0], y = p[1];
				dp.setAll((1 - 2 * x)*(y - y*y)*t, (1 - 2 * y)*(x - x*x)*t);
			}
			double iniP(FVector_double& p) {
				//double x = p[0], y= p[1];
				return P(p, ini_time);
				//return exp(-(x*x+y*y)/4.);		
			}
			double endP(FVector_double& p) {
				//double x = p[0], y= p[1];
				return P(p, ter_time);
				//return 1./2. * exp(-(x*x + y*y)/(8.));
			}
			double coef_mu(FVector_double& p, double t)
			{
				return 1.;
			}
			double	F(FVector_double& p, double t)
			{
				double x = p[0], y = p[1];
				return (1 - x)*(1 - y)*x*y + mum*(2 * (x - x*x) + 2 * (y - y*y))*t;
			}
		};
		class test_problem2 : public FEM_PROBLEM{ // not iim problem
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __)
			{
				Input("Initial time", ini_time);
				Input("Terminal time", ter_time);
				Input("maximum time step", time_step);
				__.time_step = time_step;
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(0., 0., 1., 1.);
			}
			void	coef_mMu(FVector_double& p, FMatrix_double& mMu) {
				double x = p[0], y = p[1];
				mMu.setAll(1., 0., 0., 1.);
			}

			void	coef_cDMu(FVector_double& p, FCube_double& cDMu) {
				double x = p[0], y = p[1];
				cDMu.setAll(0., 0., 0., 0., 0., 0., 0., 0.);
			}
			double	P(FVector_double& p, double t) {
				double x = p[0], y = p[1];
				return ((1 - x)*x*(1 - y)*y);
			}

			void	DP(FVector_double& p, FVector_double& dp, double t) {
				double x = p[0], y = p[1];
				dp.setAll((1 - 2 * x)*(y - y*y), (1 - 2 * y)*(x - x*x));
			}

			double iniP(FVector_double& p) {
				double x = p[0], y = p[1];
				return (1 - x)*x*(1 - y)*y;
			}

			double endP(FVector_double& p) {
				double x = p[0], y = p[1];
				return (1 - x)*x*(1 - y)*y;
			}

			double	F(FVector_double& p, double t)
			{
				double x = p[0], y = p[1];
				return 2.*(x - x*x + y - y*y);
			}
		};
		class test_problem3 : public FEM_PROBLEM{ // not iim problem
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __)
			{
				Input("Initial time", ini_time);
				Input("Terminal time", ter_time);
				Input("maximum time step", time_step);
				__.time_step = time_step;
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(0., 0., 1., 1.);
			}

			double	P(FVector_double& p, double t) {
				double x = p[0], y = p[1];
				return exp(-2 * CV.PI*CV.PI*t)*(sin(CV.PI*x)*sin(CV.PI*y));
			}

			void	DP(FVector_double& p, FVector_double& dp, double t) {
				double x = p[0], y = p[1];
				dp.setAll((1 - 2 * x)*(y - y*y), (1 - 2 * y)*(x - x*x));
			}

			double iniP(FVector_double& p) {
				return P(p, ini_time);
			}

			double endP(FVector_double& p) {
				return P(p, ter_time);
			}

			double	F(FVector_double& p, double t)
			{
				double x = p[0], y = p[1];
				return 0.;
			}
		};
		class test_problem4 : public FEM_PROBLEM{ // not iim problem
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __)
			{
				Input("Initial time", ini_time);
				Input("Terminal time", ter_time);
				Input("maximum time step", time_step);
				__.time_step = time_step;
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(0., 0., 1., 1.);
			}

			double	P(FVector_double& p, double t) {
				double x = p[0], y = p[1];
				return exp(-CV.PI*CV.PI*t)*sin(CV.PI*x)*sin(CV.PI*y) + x*y;
			}

			void	DP(FVector_double& p, FVector_double& dp, double t) {
				double x = p[0], y = p[1];
				dp.setAll((1 - 2 * x)*(y - y*y), (1 - 2 * y)*(x - x*x));
			}

			double iniP(FVector_double& p) {
				return P(p, ini_time);
			}

			double endP(FVector_double& p) {
				return P(p, ter_time);
			}

			double	F(FVector_double& p, double t)
			{
				double x = p[0], y = p[1];
				return CV.PI*CV.PI*exp(-CV.PI*CV.PI*t)*sin(CV.PI*x)*sin(CV.PI*y);
			}
		};
		class Imm : public FEM_PROBLEM{
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				//r0 = 0.48;
				Input("r0", r0);
				Input("maximum time step", time_step);
				Input("mum", mum);
				Input("mup", mup);
				//mum = mup = 1;

				__.time_step = time_step;
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);
			}

			double	Interface(double r, double t) {												// 내부에서 음수의 값을 가지도록 한다.
				return (r - r0);
			}

			double	Interface(FVector_double& p, double t) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				return (r - r0);
			}

			double	coef_mu(FVector_double& p, FVector_double& mus, double t) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;

			}
			double	coef_mu(FVector_double& p, double t = 0) {
				static FVector_double mus(2);
				coef_mu(p, mus, t);															// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p, t) <= 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}

			double	P(FVector_double& p, FVector_double& ps, double t) {
				double x = p[0], y = p[1];
				ps.setAll((x*x - 1.)*(y*y - 1.)*1. / t*(x*x + y*y - r0)*mum, (x*x - 1)*(y*y - 1)*1. / t * (x*x + y*y - r0));															// (Interior, Exterior)
				return 0;
			}

			double	P(FVector_double& p, double t = 0) {
				static FVector_double ps(2);
				P(p, ps, t);																	// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p, t) <= 0) {
					return ps[0];
				}
				else {
					return ps[1];
				}
			}

			void	DP(FVector_double& p, FMatrix_double& dps, double t) {
				double x = p[0], y = p[1];
				dps.setAll(-(2.*x*(y*y - 1.)*(r0*r0 - 2.*x*x - y*y + 1.)) / t,
					-(2.*y*(x*x - 1.)*(r0*r0 - x*x - 2.*y*y + 1.)) / t
					);
			}

			void	DP(FVector_double& p, FVector_double& dp, double t) {
				static FMatrix_double dps(2, 2);
				DP(p, dps, t);

				if (Interface(p, t) <= 0) {
					dp = dps[0];
				}
				else {
					dp = dps[1];
				}
			}

			void iniP(FVector_double& p, FVector_double& ps) {
				double x = p[0], y = p[1];
				ps.setAll((x*x - 1.)*(y*y - 1.)*(x*x + y*y - r0*r0) / mum, (x*x - 1.)*(y*y - 1.)*(x*x + y*y - r0*r0) / mup);
			}

			void endP(FVector_double& p, FVector_double& ps) {
				double x = p[0], y = p[1];
				ps.setAll(1. / 2.*(x*x - 1.)*(y*y - 1.)* (x*x + y*y - r0*r0) / mum, 1. / 2.*(x*x - 1.)*(y*y - 1.) * (x*x + y*y - r0*r0) / mup);
			}

			double  F(FVector_double& p, FVector_double& fs, double t)
			{
				double x = p[0], y = p[1];
				fs.setAll((-(-2.*r0*r0*x*x - 2.*r0*r0*y*y + 4.*r0*r0 + 2.*x*x*x*x + 24.*x*x*y*y - 16.*x*x + 2.*y*y*y*y - 16.*y*y + 4.) / t - ((x - 1.)*(x + 1.)*(y - 1.)*(y + 1.)*(-r0*r0 + x*x + y*y)) / (t*t), -(-2.*r0*r0*x*x - 2.*r0*r0*y*y + 4.*r0*r0 + 2.*x*x*x*x + 24.*x*x*y*y - 16.*x*x + 2.*y*y*y*y - 16.*y*y + 4.) / t - ((x - 1.)*(x + 1.)*(y - 1.)*(y + 1.)*(-r0*r0 + x*x + y*y)) / (t*t)) / mum, (-(-2.*r0*r0*x*x - 2.*r0*r0*y*y + 4.*r0*r0 + 2.*x*x*x*x + 24.*x*x*y*y - 16.*x*x + 2.*y*y*y*y - 16.*y*y + 4.) / t - ((x - 1.)*(x + 1.)*(y - 1.)*(y + 1.)*(-r0*r0 + x*x + y*y)) / (t*t), -(-2.*r0*r0*x*x - 2.*r0*r0*y*y + 4.*r0*r0 + 2.*x*x*x*x + 24.*x*x*y*y - 16.*x*x + 2.*y*y*y*y - 16.*y*y + 4.) / t - ((x - 1.)*(x + 1.)*(y - 1.)*(y + 1.)*(-r0*r0 + x*x + y*y)) / (t*t)) / mup);
				return 0;
			}

			double	F(FVector_double& p, double t) {
				static FVector_double fs(2);
				F(p, fs, t);
				if (Interface(p, t) <= 0) {
					return fs[0];
				}
				else {
					return fs[1];
				}
			}
		};
		class Test_Parabolic : public FEM_PROBLEM{
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __)
			{
				Input("r0", r0);
				Input("mum", mum);
				Input("mup", mup);

				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);
			}
			double	Interface(double r) {												// 내부에서 음수의 값을 가지도록 한다.
				return (r - r0);
			}
			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				return (r - r0);
			}
			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}
			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.
				if (Interface(p) <= 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}

			double	P(FVector_double& p, FVector_double& ps) {
				double x = p[0], y = p[1];
				ps.setAll(1. / 2 * exp(-(x*x + y*y - r0*r0) / (4 * mum * 2)), 1. / 2 * exp(-(x*x + y*y - r0*r0) / (4 * mup * 2)));															// (Interior, Exterior)
				return 0;
			}

			double	P(FVector_double& p) {
				static FVector_double ps(2);
				P(p, ps);																	// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) <= 0) {
					return ps[0];
				}
				else {
					return ps[1];
				}
			}

			void	DP(FVector_double& p, FMatrix_double& dps) {
				double x = p[0], y = p[1];
				dps.setAll(
					-x / (2.*mum * 2 * 2)*exp(-(x*x + y*y - r0*r0) / (4.*mum * 2)), -y / (2.*mum * 2 * 2)*exp(-(x*x + y*y - r0*r0) / (4.*mum * 2)),
					-x / (2.*mup * 2 * 2)*exp(-(x*x + y*y - r0*r0) / (4.*mup * 2)), -y / (2.*mup * 2 * 2)*exp(-(x*x + y*y - r0*r0) / (4.*mup * 2))
					);
			}

			void	DP(FVector_double& p, FVector_double& dp) {
				static FMatrix_double dps(2, 2);
				DP(p, dps);
				double x = p[0], y = p[1];
				if (Interface(p) <= 0) {
					dp = dps[0];
				}
				else {
					dp = dps[1];
				}
			}

			double  F(FVector_double& p, FVector_double& fs)
			{
				double x = p[0], y = p[1];
				fs.setAll(-r0*r0 / (4.*mum * 2 * 2 * 2)*exp(-(x*x + y*y - r0*r0) / (4.*mum * 2)), -r0*r0 / (4.*mup * 2 * 2 * 2)*exp(-(x*x + y*y - r0*r0) / (4.*mup * 2)));
				return 0;
			}

			double	F(FVector_double& p) {
				static FVector_double fs(2);
				F(p, fs);
				if (Interface(p) <= 0) {
					return fs[0];
				}
				else {
					return fs[1];
				}
			}
		};
	};
	class ADVECTION_DIFFUSION { //steady state
	public:
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		//============================================================================
		//							CONCENTRATION EQUATION
		//============================================================================
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		
		class SMOOTH_SOL_1: public FEM_PROBLEM {
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		//============================================================================
		//					div (  -mu grad u +  R u)=f
		//============================================================================
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		public:
			void		initialize	(FEM_VARIABLES::ENTIRE& __) {
				mu = 1;
				__.dim = 2;
				__.RX.make(__.dim, __.dim).setAll(0.,0., 1.,1.);
			}

			double	P	(FVector_double& p) {
				double x=p[0], y=p[1];
				return 100. *x*x* (1-x)*(1-x)*y*(1-2*y)*(1-y);
			}

			void	DP	(FVector_double& p, FVector_double& dp) {	 
				double x=p[0], y=p[1];
				dp.setAll(200.*x*y*(2*x - 1)*(2*y - 1)*(x - 1)*(y - 1), 100*x*x*(x - 1)*(x-1)*(6*y*y - 6*y + 1));
			}
			void DDP (FVector_double & p, FMatrix_double & ddp){
				double x=p[0], y=p[1];
				ddp[0].setAll(200*y*(2*y - 1)*(y - 1)*(6.*x*x - 6.*x + 1.),200*x*(2*x - 1)*(x - 1)*(6*y*y - 6*y + 1));
				ddp[1].setAll(200*x*(2*x - 1)*(x - 1)*(6*y*y - 6*y + 1),600.*x*x*(2*y - 1)*(x - 1)*(x-1) );
			}
			void	R	(FVector_double& p,	FVector_double& vR)	{
				double x=p[0], y=p[1];
				vR.setAll(-2.,3.);

			}
			double	F	(FVector_double& p) {
				double x=p[0], y=p[1];
				FMatrix_double ddp(2,2);	FVector_double dp(2);	FVector_double vR(2);
				double ret_;
				DDP (p, ddp);	DP(p,dp);	R(p,vR);
				ret_=-mu*ddp[0][0]-mu*ddp[1][1]+(vR,dp);
				ddp.release();	dp.release();	vR.release();
				return ret_;
			//	return 1800*x*x*x*x*y*y-1812*x*x*x*x*y + 306*x*x*x*x + 1600*x*x*x*y*y*y - 6000*x*x*x*y*y + 4424*x*x*x*y - 612*x*x*x - 2424*x*x*y*y*y + 5436*x*x*y*y - 3024*x*x*y + 306*x*x + 824*x*y*y*y - 1236*x*y*y + 412*x*y - 4*y*y*y + 6*y*y - 2*y;

			}
			
			void	coef_mMu	(FVector_double& p, FMatrix_double& mMu) {
				mMu[0][0]=0.01;		mMu[0][1]=0;
				mMu[1][0]=0;		mMu[1][1]=0.01;
			}
		};

		class SMOOTH_SOL_2: public FEM_PROBLEM {
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		//============================================================================
		//					div (  -mu grad u +  R u)=f
		//============================================================================
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		public:
			void		initialize	(FEM_VARIABLES::ENTIRE& __) {
				mu = 0.001;
				__.dim = 2;
				__.RX.make(__.dim, __.dim).setAll(0.,0., 1.,1.);
			}

			double	P	(FVector_double& p) {
				double x=p[0], y=p[1];
				return (x+1.)*(x+1.)*(y+1.)*(y+1.);
			}

			void	DP	(FVector_double& p, FVector_double& dp) {	 
				double x=p[0], y=p[1];
				dp.setAll(2.*(x+1.)*(y+1.)*(y+1.), 2.*(x+1.)*(x+1.)*(y+1.) );
			}
			void DDP (FVector_double & p, FMatrix_double & ddp){
				double x=p[0], y=p[1];
				ddp[0].setAll(2.*(y+1)*(y+1),4*(x+1)*(y+1));
				ddp[1].setAll(4*(x+1)*(y+1),2.*(x+1)*(x+1));
			}

			void	R	(FVector_double& p,	FVector_double& vR)	{
				double x=p[0], y=p[1];
				vR.setAll(-2.,3.);
			}
			double	F	(FVector_double& p) {
				double x=p[0], y=p[1];
				FMatrix_double ddp(2,2);	FVector_double dp(2);	FVector_double vR(2);
				double ret_;
				DDP (p, ddp);	DP(p,dp);	R(p,vR);
				ret_=-mu*ddp[0][0]-mu*ddp[1][1]+(vR,dp);
			//	ddp.release();	dp.release();	vR.release();
				return ret_;

			}
			
			void	coef_mMu	(FVector_double& p, FMatrix_double& mMu) {
				mMu[0][0]=0.01;		mMu[0][1]=0;
				mMu[1][0]=0;		mMu[1][1]=0.01;
			}
			
		};



		class LAYER_1: public FEM_PROBLEM {
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		//============================================================================
		//					div (  -mu grad u +  R u)=f
		//============================================================================
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		public:
			// %
			void		initialize	(FEM_VARIABLES::ENTIRE& __) {
				mu = 0.01;
				__.dim = 2;
				__.RX.make(__.dim, __.dim).setAll(0.,0., 1.,1.);
			}

			double	P	(FVector_double& p) {
				double x=p[0], y=p[1];
				return (x-exp(2.*(x-1)/0.01))*(y*y-exp(3*(y-1)/0.01));
			}

			void	DP	(FVector_double& p, FVector_double& dp) {	 
				double x=p[0], y=p[1];
				dp.setAll( (1.-2./0.01* exp(2.*(x-1)/0.01))*(y*y-exp(3*(y-1)/0.01)),(x-exp(2.*(x-1)/0.01))*(2*y-3./0.01*exp(3*(y-1)/0.01)));
			}

			double	F	(FVector_double& p) {
				double x=p[0], y=p[1];
				return exp(200.*x - 200.)/50. - x/50. - 2.*exp(300*y - 300.) + 6.*x*y - 6*y*exp(200.*x - 200.) + 2.*y*y;

			}
			void	R	(FVector_double& p,	FVector_double& vR)	{
				double x=p[0], y=p[1];
				vR.setAll(2.,3.);

			}
			void	coef_mMu	(FVector_double& p, FMatrix_double& mMu) {
				mMu[0][0]=0.01;		mMu[0][1]=0;
				mMu[1][0]=0;		mMu[1][1]=0.01;
			}
		};
		class P_CONVEC_DIFF1 : public FEM_PROBLEM {	//-div(mu▽p) + kp + beta·▽p = f
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				Input("mu", mu);
				Input("k", k);
				Input("beta_x", beta_x);
				Input("beta_y", beta_y);
				RX = __.RX.make(__.dim, __.dim).setAll(0., 0., 1., 1.);
			}

			double	coef_mu(FVector_double& p) {
				return mu;
			}

			double	coef_k(FVector_double& p) {
				return k;
			}

			void	coef_beta(FVector_double& p, FVector_double& mus) {
				mus.setAll(beta_x, beta_y);
			}

			double	P(FVector_double& p) {
				double x = p[0], y = p[1];
				return exp(-5.*(x - 0.5)*(x - 0.5) - 15.*(y - 0.5)*(y - 0.5));
			}

			void	DP(FVector_double &p, FVector_double &dp) {
				double x = p[0], y = p[1];
				dp.setAll(-10.*(x - 0.5)*P(p), -30.*(y - 0.5)*P(p));
			}


			double	F(FVector_double& p) {
				double x = p[0], y = p[1];
				FVector_double dp(2);
				FVector_double vBeta(2);
				vBeta.setAll(beta_x, beta_y);

				DP(p, dp);
				return (vBeta, dp) + k*P(p) - mu*((100.*(x - 0.5)*(x - 0.5) + 900 * (y - 0.5)*(y - 0.5))*P(p) - 40 * P(p));
			}
		};

		class P_CONVEC_DIFF2 : public FEM_PROBLEM {	//-div(mu▽p) + kp + beta·▽p = f
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				Input("mu", mu);
				Input("k", k);
				Input("beta_x", beta_x);
				Input("beta_y", beta_y);
				RX = __.RX.make(__.dim, __.dim).setAll(0., 0., 1., 1.);
			}

			double	coef_mu(FVector_double& p) {
				return mu;
			}

			double	coef_k(FVector_double& p) {
				return k;
			}

			void	coef_beta(FVector_double& p, FVector_double& mus) {
				mus.setAll(beta_x, beta_y);
			}

			double	P(FVector_double& p) {
				double x = p[0], y = p[1];
				return (x - exp(2.*(x - 1) / mu)) * (y*y - exp(3.*(y - 1) / mu));
			}

			void	DP(FVector_double &p, FVector_double &dp) {
				double x = p[0], y = p[1];
				dp.setAll((1 - 2. / mu * exp(2.*(x - 1) / mu))*(y*y - exp(3.*(y - 1) / mu)), (x - exp(2.*(x - 1) / mu))*(2.*y - 3. / mu*exp(3.*(y - 1) / mu)));
			}


			double	F(FVector_double& p) {
				double x = p[0], y = p[1];
				FVector_double dp(2);
				FVector_double vBeta(2);
				vBeta.setAll(beta_x, beta_y);

				DP(p, dp);
				return (vBeta, dp) + k*P(p) - mu*(-4 / (mu*mu) *exp(2.*(x - 1) / mu)*(y*y - exp(3.*(y - 1) / mu)) + (x - exp(2.*(x - 1) / mu))*(2 - 9 / (mu*mu)*exp(3.*(y - 1) / mu)));
			}
		};

		class P_CONVEC_DIFF3 : public FEM_PROBLEM {	//-div(mu▽p) + kp + beta·▽p = f
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				Input("mu", mu);
				Input("k", k);
				Input("beta_x", beta_x);
				Input("beta_y", beta_y);
				RX = __.RX.make(__.dim, __.dim).setAll(0., 0., 1., 1.);
			}

			double	coef_mu(FVector_double& p) {
				return mu;
			}

			double	coef_k(FVector_double& p) {
				return k;
			}

			void	coef_beta(FVector_double& p, FVector_double& mus) {
				mus.setAll(beta_x, beta_y);
			}

			double	P(FVector_double& p) {
				double x = p[0], y = p[1];
				return (x - exp(2.*(x - 1) / mu)) * (y - exp(2.*(y - 1) / mu));
			}

			void	DP(FVector_double &p, FVector_double &dp) {
				double x = p[0], y = p[1];
				dp.setAll((1 - 2. / mu * exp(2.*(x - 1) / mu))*(y - exp(2.*(y - 1) / mu)), (x - exp(2.*(x - 1) / mu))*(1 - 2. / mu*exp(2.*(y - 1) / mu)));
			}


			double	F(FVector_double& p) {
				double x = p[0], y = p[1];
				FVector_double dp(2);
				FVector_double vBeta(2);
				vBeta.setAll(beta_x, beta_y);

				DP(p, dp);
				return (vBeta, dp) + k*P(p) - mu*(-4 / (mu*mu) *exp(2.*(x - 1) / mu)*(y - exp(2.*(y - 1) / mu)) + (x - exp(2.*(x - 1) / mu))*(-4 / (mu*mu)*exp(2.*(y - 1) / mu)));
			}
		};

	};
	class Miscible_Displacement{
	public:
	//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
	//============================================================================
	//							Miscible Displacement
	//		-div ( K/mu(c) \grad  p ) = \grad u = 0
	//		phi c_t + div (uc- D(u) \grad c) =0
	//============================================================================
	//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		class Riviere_Wheeler_case1 : public FEM_PROBLEM {
		public:
			// (sw, pn) couple
			void		initialize(FEM_VARIABLES::ENTIRE& __) {
				K_p = pow(10., -11.);	phi = 1.;
				__.dim = 2;
				__.RX.make(__.dim, __.dim).setAll(0., 0., 1600., 1600.);
				mu0 = pow(10., -3.);
				M = 1.;		c_in = 1.;
				alpha_t=0.01;	alpha_l=0.1;	D_m=1.16*pow(10.,-9.);
			}
			double	K_p_(FVector_double & p) {
				double x = p[0], y = p[1];
				return K_p;
			}
			double		mu_(double c) {
				double rt=mu0*pow((1.-c_in*c)+pow(M,-0.25)*c_in*c,-4.);
				return rt;
			}
			int boundary_indicator_p(FVector_double& p) {
				double x = p[0];	double y = p[1];
				int rt=0;

				if (y == 0) rt = 1;
				if (y == 1600) rt = 1;
				if (x == 0)	rt = 0;
				if (x == 1600) rt = 0;

				return rt; 
			
			}
			int	boundary_indicator_c(FVector_double& p) {
				double x = p[0];	double y = p[1];
				int rt = 0;

				if (x == 0)	rt = 1;

				return rt; 
				
			}

			double	flux_p(FVector_double& p){
				double x = p[0], y = p[1];
				double rt;
				if (y == 0)		rt = 0.;
				if (y == 1600)	rt = 0.;

				return rt;
			}
			double	dirichlet_p(FVector_double& p) {
				double x = p[0], y = p[1];
				double rt;
				if (x==0)		rt = pow(10., 8.);
				if (x == 1600)	rt = 0.;

				return rt;
			}

			double	Initial_Val(FVector_double & p) {
				double x = p[0], y = p[1];
				double rt = 0.;
				return rt;
			}

		};

	};
	class HELE_SHAW {
	public: 
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		//============================================================================
		//                           HELE SHAW
		//============================================================================
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		class NON_INTERFACE_FIRST: public FEM_PROBLEM {
		public:
			void	initialize	(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(0.,0., 1., 1.);
			}
			double		Initial_PHI		(FVector_double& p) { 
				double x=p[0], y=p[1];
				double r_;
				double r0=0.1;
				//r_=sqrt((x-0.5)*(x-0.5)+(y-0.5)*(y-0.5));
		        //if (r_>=r0)
				//	return r_-r0;
		        //if (r_<0.1)
		          //  return r0-r_;

				return r0-sqrt((x-0.5)*(x-0.5)+(y-0.5)*(y-0.5));
			}
			double	P			(FVector_double& p) {
				double x=p[0], y=p[1];
				return x*y*(1-x)*(1-y);	
			}

			void	DP			(FVector_double& p, FVector_double& vDP) {
				double x=p[0], y=p[1];
				vDP.clear();
				vDP.setAll(y*(1-y)*(1-2*x), x*(1-x)*(1-2*y));
			}
			
			void	DDP			(FVector_double& p, FMatrix_double& mDDP) {
				double x=p[0], y=p[1];
				mDDP.setAll(2*y*(y-1), (-1+2*x)*(-1+2*y), (-1+2*x)*(-1+2*y), 2*x*(x-1));
			}

			void	coef_mMu	(FVector_double& p, FMatrix_double& mMu) {
				double x=p[0], y=p[1];
			//	mMu.setAll(1., 0., 0., 1.);
			}

			void	coef_cDMu	(FVector_double& p, FCube_double& cDMu) {
				double x=p[0], y=p[1];
			//	cDMu.setAll(0., 0., 0., 0., 0., 0., 0., 0.);
			}

			double	F			(FVector_double& p) {
				double x=p[0], y=p[1];
				return 10./((x-0.5)*(x-0.5)+(y-0.5)*(y-0.5)+1);	
			}
			
			// 자동결정 함수들
			void	V			(FVector_double& p, FVector_double& vV) {
				// vV = -μ▽p
				double x=p[0]; 
				double y=p[1];

				vV[0]=(x-0.5);
				vV[1]=(y-0.5);
			}

			void	DV			(FVector_double& p, FMatrix_double& mDV) {
				// mDV = ▽(-μ▽p) = -(▽μ▽p + μ▽▽p)   μ:matrix  p:vector
				// 참고: div(mDV) = div(-μ▽p) = tr(-▽(μ▽p)) = (tr(-▽μ▽p) - tr(μ▽▽p)) = (tr(-▽μ▽p) - μ:▽▽p)
				static FVector_double	vDP(dim);
				static FMatrix_double	mMu(dim,dim), mDDP(dim,dim), mIm1(dim,dim), mIm2(dim,dim);
				static FCube_double		cDMu(dim,dim,dim);

				coef_mMu(p, mMu);
				coef_cDMu(p, cDMu);
				DP(p, vDP);
				DDP(p, mDDP);

				// 첫번째 식을 기반으로 계산한다.
				mIm1.op("=", "kfcfv", 1., cDMu, vDP);
				mIm2.op("=", mMu, mDDP);
				mDV.op("=", "kfm+kfm", -1., mIm1, -1., mIm2); 
			}
		

		};
		class INTERFACE_CIRCLE_JUMP : public FEM_PROBLEM {
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(0., 0., 1., 1.);
				r0 = 0.14;
				mum = 1.;	// 밖
				mup = 10.;	// 안
			}
			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);

				return 0;
			}
			double	coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) < 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}
			double		Initial_PHI(FVector_double& p) {
				double x = p[0], y = p[1];
				double r_;
				double r0 = 0.3;

				double ret=r0 - sqrt((x - 0.5)*(x - 0.5) + (y - 0.5)*(y - 0.5));

				if (ret>0){
					ret= ret;
				}
				else{
					ret= ret;
				}
				// (r - 0.2*sin(5 * theta - CV.PI / 5) - 0.5);
				//r_=sqrt((x-0.5)*(x-0.5)+(y-0.5)*(y-0.5));
				//if (r_>=r0)
				//	return r_-r0;
				//if (r_<0.1)
				//  return r0-r_;

				return ret*2;
			}
			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				double r = sqrt((x - 0.5)*(x - 0.5) + (y - 0.5)*(y - 0.5));
				return (r - r0);
			}
			double	P(FVector_double& p) {
				double x = p[0], y = p[1];
				return x*y*(1 - x)*(1 - y);
			}
			double	P(FVector_double& p, FVector_double& ps) {
				double x = p[0], y = p[1];
				ps.setAll(x*y*(1 - x)*(1 - y), x*y*(1 - x)*(1 - y));

				return 0.;
			}
			void	DP(FVector_double& p, FVector_double& vDP) {
				double x = p[0], y = p[1];
				vDP.clear();
				vDP.setAll(y*(1 - y)*(1 - 2 * x), x*(1 - x)*(1 - 2 * y));
			}

			void	DDP(FVector_double& p, FMatrix_double& mDDP) {
				double x = p[0], y = p[1];
				mDDP.setAll(2 * y*(y - 1), (-1 + 2 * x)*(-1 + 2 * y), (-1 + 2 * x)*(-1 + 2 * y), 2 * x*(x - 1));
			}
			double	P_Jump(FVector_double& p) {
				//static FVector_double ps(2);
				//P(p, ps);
				//return (ps[0] - ps[1]);
				
				return 0.01;
			}
			double	Flux_Jump(FVector_double& p, FVector_double& vN) {
				

				return 0.;
			}
			void	coef_mMu(FVector_double& p, FMatrix_double& mMu) {
				double x = p[0], y = p[1];
				//	mMu.setAll(1., 0., 0., 1.);
			}

			void	coef_cDMu(FVector_double& p, FCube_double& cDMu) {
				double x = p[0], y = p[1];
				//	cDMu.setAll(0., 0., 0., 0., 0., 0., 0., 0.);
			}

			double	F(FVector_double& p) {
				double x = p[0], y = p[1];
				return 2. / ((x - 0.5)*(x - 0.5) + (y - 0.5)*(y - 0.5) + 1);
			}
			double	F(FVector_double& p, FVector_double& fs) {
				double x = p[0], y = p[1];
				fs.setAll(2. / ((x - 0.5)*(x - 0.5) + (y - 0.5)*(y - 0.5) + 1), 2. / ((x - 0.5)*(x - 0.5) + (y - 0.5)*(y - 0.5) + 1));
				return 0.;
			}


			// 자동결정 함수들
			void	V(FVector_double& p, FVector_double& vV) {
				// vV = -μ▽p
				double x = p[0];
				double y = p[1];

				vV[0] = (x - 0.5);
				vV[1] = (y - 0.5);
			}

			void	DV(FVector_double& p, FMatrix_double& mDV) {
				// mDV = ▽(-μ▽p) = -(▽μ▽p + μ▽▽p)   μ:matrix  p:vector
				// 참고: div(mDV) = div(-μ▽p) = tr(-▽(μ▽p)) = (tr(-▽μ▽p) - tr(μ▽▽p)) = (tr(-▽μ▽p) - μ:▽▽p)
				static FVector_double	vDP(dim);
				static FMatrix_double	mMu(dim, dim), mDDP(dim, dim), mIm1(dim, dim), mIm2(dim, dim);
				static FCube_double		cDMu(dim, dim, dim);

				coef_mMu(p, mMu);
				coef_cDMu(p, cDMu);
				DP(p, vDP);
				DDP(p, mDDP);

				// 첫번째 식을 기반으로 계산한다.
				mIm1.op("=", "kfcfv", 1., cDMu, vDP);
				mIm2.op("=", mMu, mDDP);
				mDV.op("=", "kfm+kfm", -1., mIm1, -1., mIm2);
			}


		};
		class NON_INTERFACE_STAR : public FEM_PROBLEM {
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(0., 0., 1., 1.);
				r0 = 0.64;
			}
			double		Initial_PHI(FVector_double& p) {
				double x = p[0], y = p[1];
				double r = sqrt((x-0.5)*(x-0.5) + (y-0.5)*(y-0.5));
			//	double r_;
				double r0 = 0.1;
				double theta = MATH::slope_to_radian(x-0.5, y-0.5);
				
				double rt;
				rt= 0.2 - (0.02 + r ) * (1 + 0.25*sin(3 * theta));
				
				mum = 1.;
				mup = 1.;
				//r_=sqrt((x-0.5)*(x-0.5)+(y-0.5)*(y-0.5));
				//if (r_>=r0)
				//	return r_-r0;
				//if (r_<0.1)
				//  return r0-r_;

				return rt;
			}
			double	P(FVector_double& p) {
				double x = p[0], y = p[1];
				return x*y*(1 - x)*(1 - y);
			}

			void	DP(FVector_double& p, FVector_double& vDP) {
				double x = p[0], y = p[1];
				vDP.clear();
				vDP.setAll(y*(1 - y)*(1 - 2 * x), x*(1 - x)*(1 - 2 * y));
			}

			void	DDP(FVector_double& p, FMatrix_double& mDDP) {
				double x = p[0], y = p[1];
				mDDP.setAll(2 * y*(y - 1), (-1 + 2 * x)*(-1 + 2 * y), (-1 + 2 * x)*(-1 + 2 * y), 2 * x*(x - 1));
			}
			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);

				return 0;
			}
			double	coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) < 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}
			void	coef_mMu(FVector_double& p, FMatrix_double& mMu) {
				double x = p[0], y = p[1];
				mMu.setAll(1., 0., 0., 1.);
			}

			void	coef_cDMu(FVector_double& p, FCube_double& cDMu) {
				double x = p[0], y = p[1];
				//	cDMu.setAll(0., 0., 0., 0., 0., 0., 0., 0.);
			}

			double	F(FVector_double& p) {
				double x = p[0], y = p[1];
				return 2. / ((x - 0.5)*(x - 0.5) + (y - 0.5)*(y - 0.5) + 1);
			}
			double	F(FVector_double& p, FVector_double& vf) {
				double x = p[0], y = p[1];
				vf.setAll(2. / ((x - 0.5)*(x - 0.5) + (y - 0.5)*(y - 0.5) + 1), 2. / ((x - 0.5)*(x - 0.5) + (y - 0.5)*(y - 0.5) + 1));
				return 0.;
			}
			// 자동결정 함수들
			void	V(FVector_double& p, FVector_double& vV) {
				// vV = -μ▽p
				double x = p[0];
				double y = p[1];

				vV[0] = (x - 0.5);
				vV[1] = (y - 0.5);
			}

			void	DV(FVector_double& p, FMatrix_double& mDV) {
				// mDV = ▽(-μ▽p) = -(▽μ▽p + μ▽▽p)   μ:matrix  p:vector
				// 참고: div(mDV) = div(-μ▽p) = tr(-▽(μ▽p)) = (tr(-▽μ▽p) - tr(μ▽▽p)) = (tr(-▽μ▽p) - μ:▽▽p)
				static FVector_double	vDP(dim);
				static FMatrix_double	mMu(dim, dim), mDDP(dim, dim), mIm1(dim, dim), mIm2(dim, dim);
				static FCube_double		cDMu(dim, dim, dim);

				coef_mMu(p, mMu);
				coef_cDMu(p, cDMu);
				DP(p, vDP);
				DDP(p, mDDP);

				// 첫번째 식을 기반으로 계산한다.
				mIm1.op("=", "kfcfv", 1., cDMu, vDP);
				mIm2.op("=", mMu, mDDP);
				mDV.op("=", "kfm+kfm", -1., mIm1, -1., mIm2);
			}


		};
		class INTERFACE_STAR_JUMP : public FEM_PROBLEM {
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(0., 0., 1., 1.);
				r0 = 0.64;
			}
			double		Initial_PHI(FVector_double& p) {
				double x = p[0], y = p[1];
				double r = sqrt((x-0.5)*(x-0.5) + (y-0.5)*(y-0.5));
			//	double r_;
				double r0 = 0.1;
				double theta = MATH::slope_to_radian(x-0.5, y-0.5);
				
				double rt;
				rt= 0.2 - (0.02 + r ) * (1 + 0.25*sin(3 * theta));
				
				mum = 1.;
				mup = 10.;
				//r_=sqrt((x-0.5)*(x-0.5)+(y-0.5)*(y-0.5));
				//if (r_>=r0)
				//	return r_-r0;
				//if (r_<0.1)
				//  return r0-r_;

				return rt;
			}
			double	P(FVector_double& p) {
				double x = p[0], y = p[1];
				return x*y*(1 - x)*(1 - y);
			}

			void	DP(FVector_double& p, FVector_double& vDP) {
				double x = p[0], y = p[1];
				vDP.clear();
				vDP.setAll(y*(1 - y)*(1 - 2 * x), x*(1 - x)*(1 - 2 * y));
			}

			void	DDP(FVector_double& p, FMatrix_double& mDDP) {
				double x = p[0], y = p[1];
				mDDP.setAll(2 * y*(y - 1), (-1 + 2 * x)*(-1 + 2 * y), (-1 + 2 * x)*(-1 + 2 * y), 2 * x*(x - 1));
			}
			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);

				return 0;
			}
			double	coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) < 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}
			void	coef_mMu(FVector_double& p, FMatrix_double& mMu) {
				double x = p[0], y = p[1];
				mMu.setAll(1., 0., 0., 1.);
			}

			void	coef_cDMu(FVector_double& p, FCube_double& cDMu) {
				double x = p[0], y = p[1];
				//	cDMu.setAll(0., 0., 0., 0., 0., 0., 0., 0.);
			}

			double	F(FVector_double& p) {
				double x = p[0], y = p[1];
				return 2. / ((x - 0.5)*(x - 0.5) + (y - 0.5)*(y - 0.5) + 1);
			}
			double	F(FVector_double& p, FVector_double& vf) {
				double x = p[0], y = p[1];
				vf.setAll(2. / ((x - 0.5)*(x - 0.5) + (y - 0.5)*(y - 0.5) + 1), 2. / ((x - 0.5)*(x - 0.5) + (y - 0.5)*(y - 0.5) + 1));
				return 0.;
			}
			// 자동결정 함수들
			void	V(FVector_double& p, FVector_double& vV) {
				// vV = -μ▽p
				double x = p[0];
				double y = p[1];

				vV[0] = (x - 0.5);
				vV[1] = (y - 0.5);
			}

			void	DV(FVector_double& p, FMatrix_double& mDV) {
				// mDV = ▽(-μ▽p) = -(▽μ▽p + μ▽▽p)   μ:matrix  p:vector
				// 참고: div(mDV) = div(-μ▽p) = tr(-▽(μ▽p)) = (tr(-▽μ▽p) - tr(μ▽▽p)) = (tr(-▽μ▽p) - μ:▽▽p)
				static FVector_double	vDP(dim);
				static FMatrix_double	mMu(dim, dim), mDDP(dim, dim), mIm1(dim, dim), mIm2(dim, dim);
				static FCube_double		cDMu(dim, dim, dim);

				coef_mMu(p, mMu);
				coef_cDMu(p, cDMu);
				DP(p, vDP);
				DDP(p, mDDP);

				// 첫번째 식을 기반으로 계산한다.
				mIm1.op("=", "kfcfv", 1., cDMu, vDP);
				mIm2.op("=", mMu, mDDP);
				mDV.op("=", "kfm+kfm", -1., mIm1, -1., mIm2);
			}

			double	P_Jump(FVector_double& p) {
				//static FVector_double ps(2);
				//P(p, ps);
				//return (ps[0] - ps[1]);
				
				return 0.1;
			}
		};
		
		class EXAMPLE2 : public FEM_PROBLEM {
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-2., -2., 2., 2.);
				r0 = 0.7;
				mum = 100.;
				mup = 1.;
				alpha= 0.3;
				V0 = 0.25;
				d0 = 2.3*0.001;
				//d0 = 1.2*0.01;
				double total_injection_rate=2*V0*CV.PI*alpha;
				tau = total_injection_rate *d0/2/CV.PI/mup;

			}
			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);

				return 0;
			}
			double	coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) < 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}
			double		Initial_PHI(FVector_double& p) {
				double x = p[0], y = p[1];
				
				double ret;
				double r_ = sqrt(x*x + y*y);
				//	double r_;
				double r0 = 0.9;
				double theta = MATH::slope_to_radian(x, y);

				double rt;
				rt = r0 + 0.1*sin(5 * theta);

				ret = rt - r_;
				return ret;

			}
			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1];

				double ret;
				double r_ = sqrt(x*x + y*y);
				//	double r_;
				double r0 = 0.9;
				double theta = MATH::slope_to_radian(x, y);

				double rt;
				rt = r0 + 0.1*sin(3 * theta);

				ret = r_ - rt;
				return ret;
			}
			double	P(FVector_double& p, double t) {
				double x = p[0], y = p[1];
				double r=sqrt(x*x+y*y);
				double r_Gamma=sqrt(2*alpha*V0*t + r0*r0);
				double ret_=0.;
				double C1=0.;
				double C0=0.;

				C0= tau/r_Gamma + V0*alpha*log(r_Gamma)*(1/mum-1/mup);
				C1= C0 - V0*alpha*log(alpha)/mum + 5*V0*alpha/6/mum;

				if (r< alpha){
					ret_=V0/mum*(2*r*r*r/3/alpha/alpha - 3*r*r/2/alpha) + C1;
				}
				else if ( r < r_Gamma){
					ret_= -V0*alpha/mum*log(r) + C0;
				}
				else {
					ret_= -V0*alpha/mup*log(r);
				}

				return ret_;
			}
			double	P(FVector_double& p, FVector_double& ps, double t) {
				double x = p[0], y = p[1];
				double r=sqrt(x*x+y*y);
				double r_Gamma=sqrt(2*alpha*V0*t + r0*r0);
				double ret_in;
				double ret_out;
				double C1=0.;
				double C0=0.;

				C0= tau/r_Gamma + V0*alpha*log(r_Gamma)*(1/mum-1/mup);
				C1= C0 - V0*alpha*log(alpha)/mum + 5*V0*alpha/6/mum;

				if (r< alpha){
					ret_in=V0/mum*(2*r*r*r/3/alpha/alpha - 3*r*r/2/alpha) + C1;
				}
				else {
					ret_in= -V0*alpha/mum*log(r) + C0;
				}
				ret_out= -V0*alpha/mup*log(r);

				ps.setAll(ret_in,ret_out);

				return 0.;
			}
			void	DP(FVector_double& p, FVector_double& vDP) {
				double x = p[0], y = p[1];
				vDP.clear();
				vDP.setAll(y*(1 - y)*(1 - 2 * x), x*(1 - x)*(1 - 2 * y));
			}

			void	DDP(FVector_double& p, FMatrix_double& mDDP) {
				double x = p[0], y = p[1];
				mDDP.setAll(2 * y*(y - 1), (-1 + 2 * x)*(-1 + 2 * y), (-1 + 2 * x)*(-1 + 2 * y), 2 * x*(x - 1));
			}
			double	P_Jump(FVector_double& p) {
				//static FVector_double ps(2);
				//P(p, ps);
				//return (ps[0] - ps[1]);
				
				return 0.01;
			}
			double	Flux_Jump(FVector_double& p, FVector_double& vN) {
				

				return 0.;
			}
			void	coef_mMu(FVector_double& p, FMatrix_double& mMu) {
				double x = p[0], y = p[1];
				//	mMu.setAll(1., 0., 0., 1.);
			}

			void	coef_cDMu(FVector_double& p, FCube_double& cDMu) {
				double x = p[0], y = p[1];
				//	cDMu.setAll(0., 0., 0., 0., 0., 0., 0., 0.);
			}

			double	F(FVector_double& p) {
				double x = p[0], y = p[1];
				double r=sqrt(x*x+y*y);
				double ret=0.;

				if (r<alpha){
					ret = V0*6*(1./alpha-r/alpha/alpha);
				}
				else{
					ret=0.;
				}
				
				return ret;;
			}
			double	F(FVector_double& p, FVector_double& fs) {
				double x = p[0], y = p[1];
				double r=sqrt(x*x+y*y);
				double ret=0.;

				if (r<alpha){
					ret = V0*6*(1./alpha-r/alpha/alpha);
				}
				else{
					ret=0.;
				}
				
				fs.setAll(ret,ret);
				return ret;
			}

			// 자동결정 함수들
			void	V(FVector_double& p, FVector_double& vV) {
				// vV = -μ▽p
				double x = p[0];
				double y = p[1];

				vV[0] = (x - 0.5);
				vV[1] = (y - 0.5);
			}

			void	DV(FVector_double& p, FMatrix_double& mDV) {
				// mDV = ▽(-μ▽p) = -(▽μ▽p + μ▽▽p)   μ:matrix  p:vector
				// 참고: div(mDV) = div(-μ▽p) = tr(-▽(μ▽p)) = (tr(-▽μ▽p) - tr(μ▽▽p)) = (tr(-▽μ▽p) - μ:▽▽p)
				static FVector_double	vDP(dim);
				static FMatrix_double	mMu(dim, dim), mDDP(dim, dim), mIm1(dim, dim), mIm2(dim, dim);
				static FCube_double		cDMu(dim, dim, dim);

				coef_mMu(p, mMu);
				coef_cDMu(p, cDMu);
				DP(p, vDP);
				DDP(p, mDDP);

				// 첫번째 식을 기반으로 계산한다.
				mIm1.op("=", "kfcfv", 1., cDMu, vDP);
				mIm2.op("=", mMu, mDDP);
				mDV.op("=", "kfm+kfm", -1., mIm1, -1., mIm2);
			}


		};

		class EXAMPLE1 : public FEM_PROBLEM {
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-2., -2., 2., 2.);
				r0 = 0.41;
				mum = 100.;
				mup = 1.;
				alpha = 0.1;
				V0 = 0.25;
				d0 = 2.5*0.001;

				double total_injection_rate = 2 * V0*CV.PI*alpha;
				tau = total_injection_rate *d0 / 2 / CV.PI / mup;

			}
			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);

				return 0;
			}
			double	coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) < 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}
			double		Initial_PHI(FVector_double& p) {
				double x = p[0], y = p[1];
				double ret = r0 - sqrt(x*x + y*y);

				return ret;
			}
			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				double ret = sqrt(x*x + y*y) - r0;

				return ret;
			}
			double	P(FVector_double& p, double t) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				double r_Gamma = sqrt(2 * alpha*V0*t + r0*r0);
				double ret_ = 0.;
				double C1 = 0.;
				double C0 = 0.;

				C0 = tau / r_Gamma + V0*alpha*log(r_Gamma)*(1 / mum - 1 / mup);
				C1 = C0 - V0*alpha*log(alpha) / mum + 5 * V0*alpha / 6 / mum;

				if (r< alpha) {
					ret_ = V0 / mum*(2 * r*r*r / 3 / alpha / alpha - 3 * r*r / 2 / alpha) + C1;
				}
				else if (r < r_Gamma) {
					ret_ = -V0*alpha / mum*log(r) + C0;
				}
				else {
					ret_ = -V0*alpha / mup*log(r);
				}

				return ret_;
			}
			double	P(FVector_double& p, FVector_double& ps, double t) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				double r_Gamma = sqrt(2 * alpha*V0*t + r0*r0);
				double ret_in;
				double ret_out;
				double C1 = 0.;
				double C0 = 0.;

				C0 = tau / r_Gamma + V0*alpha*log(r_Gamma)*(1 / mum - 1 / mup);
				C1 = C0 - V0*alpha*log(alpha) / mum + 5 * V0*alpha / 6 / mum;

				if (r< alpha) {
					ret_in = V0 / mum*(2 * r*r*r / 3 / alpha / alpha - 3 * r*r / 2 / alpha) + C1;
				}
				else {
					ret_in = -V0*alpha / mum*log(r) + C0;
				}
				ret_out = -V0*alpha / mup*log(r);

				ps.setAll(ret_in, ret_out);

				return 0.;
			}
			void	DP(FVector_double& p, FVector_double& vDP) {
				double x = p[0], y = p[1];
				vDP.clear();
				vDP.setAll(y*(1 - y)*(1 - 2 * x), x*(1 - x)*(1 - 2 * y));
			}

			void	DDP(FVector_double& p, FMatrix_double& mDDP) {
				double x = p[0], y = p[1];
				mDDP.setAll(2 * y*(y - 1), (-1 + 2 * x)*(-1 + 2 * y), (-1 + 2 * x)*(-1 + 2 * y), 2 * x*(x - 1));
			}
			double	P_Jump(FVector_double& p) {
				//static FVector_double ps(2);
				//P(p, ps);
				//return (ps[0] - ps[1]);

				return 0.01;
			}
			double	Flux_Jump(FVector_double& p, FVector_double& vN) {


				return 0.;
			}
			void	coef_mMu(FVector_double& p, FMatrix_double& mMu) {
				double x = p[0], y = p[1];
				//	mMu.setAll(1., 0., 0., 1.);
			}

			void	coef_cDMu(FVector_double& p, FCube_double& cDMu) {
				double x = p[0], y = p[1];
				//	cDMu.setAll(0., 0., 0., 0., 0., 0., 0., 0.);
			}

			double	F(FVector_double& p) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				double ret = 0.;

				if (r<alpha) {
					ret = V0 * 6 * (1. / alpha - r / alpha / alpha);
				}
				else {
					ret = 0.;
				}

				return ret;;
			}
			double	F(FVector_double& p, FVector_double& fs) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				double ret = 0.;

				if (r<alpha) {
					ret = V0 * 6 * (1. / alpha - r / alpha / alpha);
				}
				else {
					ret = 0.;
				}

				fs.setAll(ret, ret);
				return ret;
			}

			// 자동결정 함수들
			void	V(FVector_double& p, FVector_double& vV) {
				// vV = -μ▽p
				double x = p[0];
				double y = p[1];

				vV[0] = (x - 0.5);
				vV[1] = (y - 0.5);
			}

			void	DV(FVector_double& p, FMatrix_double& mDV) {
				// mDV = ▽(-μ▽p) = -(▽μ▽p + μ▽▽p)   μ:matrix  p:vector
				// 참고: div(mDV) = div(-μ▽p) = tr(-▽(μ▽p)) = (tr(-▽μ▽p) - tr(μ▽▽p)) = (tr(-▽μ▽p) - μ:▽▽p)
				static FVector_double	vDP(dim);
				static FMatrix_double	mMu(dim, dim), mDDP(dim, dim), mIm1(dim, dim), mIm2(dim, dim);
				static FCube_double		cDMu(dim, dim, dim);

				coef_mMu(p, mMu);
				coef_cDMu(p, cDMu);
				DP(p, vDP);
				DDP(p, mDDP);

				// 첫번째 식을 기반으로 계산한다.
				mIm1.op("=", "kfcfv", 1., cDMu, vDP);
				mIm2.op("=", mMu, mDDP);
				mDV.op("=", "kfm+kfm", -1., mIm1, -1., mIm2);
			}


		};

		class EXAMPLE3 : public FEM_PROBLEM {
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-2., -2., 2., 2.);
				//r0 = 0.311;
				
				r0 = 0.551;
				mum = 100.;
				mup = 1.;
				alpha = 0.3;
				V0 = 0.25;
				d0 = 2.1*0.001;

				double total_injection_rate = 2 * V0*CV.PI*alpha;
				tau = total_injection_rate *d0 / 2 / CV.PI / mup;

			}
			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);

				return 0;
			}
			double	coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p) < 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}
			double	Initial_PHI(FVector_double& p) {
				double x = p[0], y = p[1];

				double ret;
				double r_ = sqrt(x*x + y*y);
				//	double r_;
				//double r0 = 0.4;
				double theta = MATH::slope_to_radian(x, y);

				double rt;
				rt = r0 + 0.05*(sin(2 * theta) + cos(3 * theta));

				ret = rt - r_;
				return ret;

			}
			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1];

				double ret;
				double r_ = sqrt(x*x + y*y);
				//	double r_;
				//double r0 = 0.9;
				double theta = MATH::slope_to_radian(x, y);

				double rt;
				rt = r0 + 0.05*(sin(2 * theta) + cos(3 * theta));

				ret = r_ - rt;
				return ret;
			}
			double	P(FVector_double& p, double t) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				double r_Gamma = sqrt(2 * alpha*V0*t + r0*r0);
				double ret_ = 0.;
				double C1 = 0.;
				double C0 = 0.;

				C0 = tau / r_Gamma + V0*alpha*log(r_Gamma)*(1 / mum - 1 / mup);
				C1 = C0 - V0*alpha*log(alpha) / mum + 5 * V0*alpha / 6 / mum;

				if (r< alpha) {
					ret_ = V0 / mum*(2 * r*r*r / 3 / alpha / alpha - 3 * r*r / 2 / alpha) + C1;
				}
				else if (r < r_Gamma) {
					ret_ = -V0*alpha / mum*log(r) + C0;
				}
				else {
					ret_ = -V0*alpha / mup*log(r);
				}

				ret_ = ret_ + 0.1;
				return ret_;
			}
			double	P(FVector_double& p, FVector_double& ps, double t) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				double r_Gamma = sqrt(2 * alpha*V0*t + r0*r0);
				double ret_in;
				double ret_out;
				double C1 = 0.;
				double C0 = 0.;

				C0 = tau / r_Gamma + V0*alpha*log(r_Gamma)*(1 / mum - 1 / mup);
				C1 = C0 - V0*alpha*log(alpha) / mum + 5 * V0*alpha / 6 / mum;

				if (r< alpha) {
					ret_in = V0 / mum*(2 * r*r*r / 3 / alpha / alpha - 3 * r*r / 2 / alpha) + C1;
				}
				else {
					ret_in = -V0*alpha / mum*log(r) + C0;
				}

				ret_out = -V0*alpha / mup*log(r);
				
				ret_in += 0.1;
				ret_out += 0.1;

				ps.setAll(ret_in, ret_out);

				return 0.;
			}
			void	DP(FVector_double& p, FVector_double& vDP) {
				double x = p[0], y = p[1];
				vDP.clear();
				vDP.setAll(y*(1 - y)*(1 - 2 * x), x*(1 - x)*(1 - 2 * y));
			}

			void	DDP(FVector_double& p, FMatrix_double& mDDP) {
				double x = p[0], y = p[1];
				mDDP.setAll(2 * y*(y - 1), (-1 + 2 * x)*(-1 + 2 * y), (-1 + 2 * x)*(-1 + 2 * y), 2 * x*(x - 1));
			}
			double	P_Jump(FVector_double& p) {
				//static FVector_double ps(2);
				//P(p, ps);
				//return (ps[0] - ps[1]);

				return 0.01;
			}
			double	Flux_Jump(FVector_double& p, FVector_double& vN) {


				return 0.;
			}
			void	coef_mMu(FVector_double& p, FMatrix_double& mMu) {
				double x = p[0], y = p[1];
				//	mMu.setAll(1., 0., 0., 1.);
			}

			void	coef_cDMu(FVector_double& p, FCube_double& cDMu) {
				double x = p[0], y = p[1];
				//	cDMu.setAll(0., 0., 0., 0., 0., 0., 0., 0.);
			}

			double	F(FVector_double& p) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				double ret = 0.;

				if (r<alpha) {
					ret = V0 * 6 * (1. / alpha - r / alpha / alpha);
				}
				else {
					ret = 0.;
				}

				return ret;;
			}
			double	F(FVector_double& p, FVector_double& fs) {
				double x = p[0], y = p[1];
				double r = sqrt(x*x + y*y);
				double ret = 0.;

				if (r<alpha) {
					ret = V0 * 6 * (1. / alpha - r / alpha / alpha);
				}
				else {
					ret = 0.;
				}

				fs.setAll(ret, ret);
				return ret;
			}

			// 자동결정 함수들
			void	V(FVector_double& p, FVector_double& vV) {
				// vV = -μ▽p
				double x = p[0];
				double y = p[1];

				vV[0] = (x - 0.5);
				vV[1] = (y - 0.5);
			}

			void	DV(FVector_double& p, FMatrix_double& mDV) {
				// mDV = ▽(-μ▽p) = -(▽μ▽p + μ▽▽p)   μ:matrix  p:vector
				// 참고: div(mDV) = div(-μ▽p) = tr(-▽(μ▽p)) = (tr(-▽μ▽p) - tr(μ▽▽p)) = (tr(-▽μ▽p) - μ:▽▽p)
				static FVector_double	vDP(dim);
				static FMatrix_double	mMu(dim, dim), mDDP(dim, dim), mIm1(dim, dim), mIm2(dim, dim);
				static FCube_double		cDMu(dim, dim, dim);

				coef_mMu(p, mMu);
				coef_cDMu(p, cDMu);
				DP(p, vDP);
				DDP(p, mDDP);

				// 첫번째 식을 기반으로 계산한다.
				mIm1.op("=", "kfcfv", 1., cDMu, vDP);
				mIm2.op("=", mMu, mDDP);
				mDV.op("=", "kfm+kfm", -1., mIm1, -1., mIm2);
			}


		};
	};
	class PPS {  
	public:
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		//============================================================================
		//			Porous media phase pressure saturation formulation
		//============================================================================
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		class HYPERBOLIC_EX1: public FEM_PROBLEM {
		public:
			// (sw, pn) couple
			void		initialize	(FEM_VARIABLES::ENTIRE& __) {
				K_p=pow(10.,-7.);	mu=pow(10.,-3.);	phi=0.2;
				__.dim = 2;
				__.RX.make(__.dim, __.dim).setAll(0., 0., 300., 75.);
				boundary_inf_n.make(4);
				boundary_inf_w.make(4);
				boundary_inf_n.setAll(1, 1, 1, 0);
				boundary_inf_w.setAll(1, 0, 1, 0);
			}
			double		K_p_		(FVector_double & x){
				return K_p;
			}
			
			double	k_n	(double s)	{
				return (1.-s)*(1.-s)*(1.-s*s);
			}

			double	k_w	(double s){
				return s*s*s*s;
			}
			double	Lamda_n	(double s){
				double k=k_n(s);
				return k/mu;
			}
			double	Lamda_w	(double s){
				double k=k_w(s);
				return k/mu;
			}
			double Lamdad_n (double s){
				return (2.*(s-1.)*(1.-s*s)+(s-1.)*(s-1.)*(-2.*s))/mu;
			}
			double Lamdad_w (double s){
				return 4.*s*s*s/mu;
			}
			double	Lamda	(double s){
				double t1;	double t2;
				t1=Lamda_n(s);
				t2=Lamda_w(s);
				return t1+t2;

			}
			double	Lamdad	(double s){
				double t1;	double t2;
				t1=Lamdad_n(s);
				t2=Lamdad_w(s);
				return t1+t2;

			}
			double	flux_n(FVector_double& p){
				// u dot n or -K grad p
				double x=p[0], y=p[1];
				double rt;
				if (y==0.){
					rt=0.;
				}
				if (y==75.){
					rt=0.;
				}
				if (x==0){
					rt=0.;
				}
				if (x==300.){
					rt=3.*pow(10.,-7.);
				}
				return rt;
			}
			double	flux_w(FVector_double& p){
				double x=p[0], y=p[1];
				double rt;
				if (y==0.){
					rt=0.;
				}
				if (x==300.){
					rt=0;
				}
				if (y==75.){
					rt=0.;
				}
				if (x==0){
					rt=0.;
				}

				return rt;
			}

			double	saturation		(FVector_double& p) {
				double x=p[0], y=p[1];
				double rt;
				if (y==0.){
					rt=0.;
				}
				if (x==300.){
					rt=0;
				}
				if (y==75.){
					rt=0.;
				}
				if (x==0){
					rt=1.;
				}
				return rt;
			}
			double	pressure		(FVector_double& p) {
				double x=p[0], y=p[1];
				double rt;
				if (y==0.){
					rt=0.;
				}
				if (x==300.){
					rt=0;
				}
				if (y==75.){
					rt=0.;
				}
				if (x==0){
					rt=0;
				}
				return rt;
			}
		
		};
		class HYPERBOLIC_EX2: public FEM_PROBLEM {
		public:
			// (sn, pw) couple
			void		initialize	(FEM_VARIABLES::ENTIRE& __) {
				K_p=pow(10.,-7.);	mu=pow(10.,-3.);	phi=0.2;
				__.dim = 2;
				RX=__.RX.make(__.dim, __.dim).setAll(0., 0., 300., 75.);
				boundary_inf_n.make(4);
				boundary_inf_w.make(4);
				boundary_inf_n.setAll(1, 1, 1, 0);
				boundary_inf_w.setAll(1, 0, 1, 0);
				
			}
			double	k_n	(double sn)	{
				return sn*sn*(1.-(1.-sn)*(1.-sn));
			}
			double	k_w	(double sn){
				return (1.-sn)*(1.-sn)*(1.-sn)*(1.-sn);
			}
			double	Lamda_n	(double s){
				double k=k_n(s);
				return k/mu;
			}
			double	Lamda_w	(double s){
				double k=k_w(s);
				return k/mu;
			}
			double Lamdad_n (double sn){
				return (2*sn*(1.-(1.-sn)*(1.-sn)) + sn*sn*(-2.*(sn-1.))  )/mu;
			}
			double Lamdad_w (double sn){
				return 4.*(sn-1.)*(sn-1.)*(sn-1.)/mu;
			}
			double	Lamda	(double s){
				double t1;	double t2;
				t1=Lamda_n(s);
				t2=Lamda_w(s);
				return t1+t2;

			}
			double	Lamdad	(double s){
				double t1;	double t2;
				t1=Lamdad_n(s);
				t2=Lamdad_w(s);
				return t1+t2;

			}
			double	flux_n(FVector_double& p){
				// u dot n or -K grad p
				double x=p[0], y=p[1];
				double rt;
				if (y==RX[0][1]){
					rt=0.;
				}
				if (y==RX[1][1]){
					rt=0.;
				}
				if (x==RX[1][0]){
					rt=3.*pow(10.,-7.);
				}
				return rt;
			}
			double	flux_w(FVector_double& p){
				double x=p[0], y=p[1];
				double rt;
				if (y==RX[0][1]){
					rt=0.;
				}
				if (y==RX[1][1]){
					rt=0.;
				}
				return rt;
			}
			double	sn		(FVector_double& p) {
				double x=p[0], y=p[1];
				double rt;
				if (x==RX[0][0]){
					rt=0.;
				}
				if (x==RX[1][0]){
					rt=1.;
				}
				return rt;
			}
			double	pw		(FVector_double& p) {
				double x=p[0], y=p[1];
				double rt;
				if (x==RX[0][0]){
					rt=0.;
				}
				return rt;
			}
		
		};
		class PARABOLIC_EX1: public FEM_PROBLEM {
		public:
			// (sw, pn) couple
			void		initialize	(FEM_VARIABLES::ENTIRE& __) {
				K_p=pow(10.,-10.);	mu=pow(10.,-3.);	phi=0.3;
				__.dim = 2;
				RX=__.RX.make(__.dim, __.dim).setAll(0., 0., 1.6, 1.6);
				boundary_inf_n.make(4);
				boundary_inf_w.make(4);
				boundary_inf_n.setAll(1, 1, 1, 0);
				boundary_inf_w.setAll(1, 0, 1, 0);
				eps=0.01;
			}
			double	k_n	(double s)	{
				return (1.-s)*(1.-s)*(1.-s*s);
			}

			double	k_w	(double s){
				return s*s*s*s;
			}
			double	Lamda_n	(double s){
				double k=k_n(s);
				return k/mu;
			}
			double	Lamda_w	(double s){
				double k=k_w(s);
				return k/mu;
			}
			double Lamdad_n (double s){
				return (2.*(s-1.)*(1.-s*s)+(s-1.)*(s-1.)*(-2.*s))/mu;
			}
			double Lamdad_w (double s){
				return 4.*s*s*s/mu;
			}
			double	Lamda	(double s){
				double t1;	double t2;
				t1=Lamda_n(s);
				t2=Lamda_w(s);
				return t1+t2;

			}
			double	Lamdad	(double s){
				double t1;	double t2;
				t1=Lamdad_n(s);
				t2=Lamdad_w(s);
				return t1+t2;

			}
			int	boundary_indicator_w	(FVector_double& p)	{
				int ret=1;
				// ret=1. normal. ret=0. dirichlet.
				double x=p[0];	double y=p[1];
				if ( (y==0.) || (y==1.6) )
					ret=1;
				if ( (x==0.) || (x==1.6) )
					ret=0;
				return ret;
			}
			int	boundary_indicator_n	(FVector_double& p)	{
				int ret=1;
				// ret=1. normal. ret=0. dirichlet.
				double x=p[0];	double y=p[1];
				if ( (y==0.) || (x==1.6) || (y==1.6) )
					ret=1;
				if ( x==0 )
					ret=0;
				return ret;
			}
			double	flux_n(FVector_double& p){
				// u dot n or -K grad p
				double x=p[0], y=p[1];
				double rt;
				if (y==RX[0][1]){
					rt=0.;
				}
				if (y==RX[1][1]){
					rt=0.;
				}
				if (x==RX[1][0]){
					rt=0.;
				}
				return rt;
			}
			double	flux_w(FVector_double& p){
				double x=p[0], y=p[1];
				double rt;
				if (y==RX[0][1]){
					rt=0.;
				}
				if (y==RX[1][1]){
					rt=0.;
				}
				return rt;
			}
			double	dirichlet_w	(FVector_double& p) {
				double x=p[0], y=p[1];
				double rt=0;
				if	( (x==RX[0][0])  )
					rt=1.;
				return rt;
			}
			double	dirichlet_n	(FVector_double& p) {
				double x=p[0], y=p[1];
				double rt=2.*pow(10.,5.);
				return rt;
			}
			double	sw		(FVector_double& p) {
				double x=p[0], y=p[1];
				double rt;
				if (x==RX[0][0]){
					rt=1.;
				}
				if (x==RX[1][0]){
					rt=0.;
				}
				return rt;
			}
			double	pn		(FVector_double& p) {
				double x=p[0], y=p[1];
				double rt;
				if (x==RX[0][0]){
					rt=2.*pow(10.,5.);
				}
				return rt;
			}
			double pc (double sw){
				double pd=5000.;
				double crt=5.*pow(10.,-3.);
				double rt;
				if (sw>crt){
					rt=pd*pow(sw,-0.5);
				}
				else {
					rt=pd*(-0.5*pow(crt,-1.5)*(sw-crt)+pow(crt,-0.5));
				}
				return pd*pow(sw+eps,-0.5);
			}
			double dpc (double sw){
				double pd=5000.;
				double crt=5.*pow(10.,-3.);
				double rt=0;
				if (sw>crt){
					rt=-0.5*pd*pow(sw,-1.5);
				}
				else{
					rt=pd*(-0.5*pow(crt,-1.5));
				}
				return -0.5*pd*pow(sw+eps,-1.5);;
			}
			double ddpc (double sw){
				double pd=5000.;
				double crt=5.*pow(10.,-3.);
				double rt=0;
			//	if (sw>crt){
					rt=0.5*1.5*pd*pow(sw+eps,-2.5);
			//	}
			//	else{
			//		rt=0;
			//	}
				return rt;
			}
		};
		class Permeable_Lens: public FEM_PROBLEM {
		public:
			// Parabolic Example. Example in Peter Bastian book 167p
			// pw, sn coupling.
			void		initialize	(FEM_VARIABLES::ENTIRE& __) {
				mu_w=pow(10.,-3.);	mu_n=0.9*pow(10.,-3.);	phi=0.4;
				phi_w=0.4;			phi_n=0.39;
				rho_w=1000.;		rho_n=1460.;
				__.dim = 2;
				eps=0.01;
				RX=__.RX.make(__.dim, __.dim).setAll(0., 0., 0.9, 0.65);
			//	cout << "INIT " << endl;
			}
			double	k_w	(FVector_double &p,double sn){
				double sw_;
				double lamda;
				double x=p[0];	double y=p[1];
				double denom;
				if ((x>0.1875)&&(x<0.7125)&&(y>0.32)&&(y<0.4625)){
					denom=0.88;
					sw_=(1-sn-0.12)/denom;
					lamda=2.;
				}
				else{
					denom=0.9;
					sw_=(1-sn-0.1)/denom;
					lamda=2.7;
				}
				return pow(sw_,(2.+3.*lamda)/lamda);
			}
			double	k_n	(FVector_double &p,double sn)	{
				double sn_;
				double lamda;
				double x=p[0];	double y=p[1];
				double denom;
				if ((x>0.1875)&&(x<0.7125)&&(y>0.32)&&(y<0.4625)){
					denom=0.88;
					sn_=sn/denom;
					lamda=2.;
				}
				else{
					denom=0.9;
					sn_=sn/denom;
					lamda=2.7;
				}
				return sn_*sn_*(1-pow((1-sn_),(2+lamda)/lamda) );
			}
			double	dk_w	(FVector_double &p,double s){
				double sw_;
				double lamda;
				double x=p[0];	double y=p[1];
				double denom;
				if ((x>0.1875)&&(x<0.7125)&&(y>0.32)&&(y<0.4625)){
					denom=0.88;
					sw_=(1-s-0.12)/denom;
					lamda=2.;
				}
				else{
					denom=0.9;
					sw_=(1-s-0.1)/denom;
					lamda=2.7;
				}
				return -(2.+3.*lamda)/lamda/denom*pow(sw_,(2.+3.*lamda)/lamda-1.);
			}
			double	dk_n	(FVector_double &p,double s)	{
				double sn_;
				double lamda;
				double x=p[0];	double y=p[1];
				double denom;
				if ((x>0.1875)&&(x<0.7125)&&(y>0.32)&&(y<0.4625)){
					denom=0.88;
					sn_=(s)/denom;
					lamda=2.;
				}
				else{
					denom=0.9;
					sn_=(s)/denom;
					lamda=2.7;
				}
				return 2.*sn_/denom*(1-pow((1-sn_),(2+lamda)/lamda)) + sn_*sn_*( (2+lamda)/lamda)/denom*2*pow(1.-sn_,2/lamda);
			}
			double	Lamda_n	(FVector_double &p,double s){
				double k=k_n(p,s);
				return k/mu_n;
			}
			double	Lamda_w	(FVector_double &p,double s){
				double k=k_w(p,s);
				return k/mu_w;
			}
			double	Lamda	(FVector_double &p,double s){
				double t1;	double t2;
				t1=Lamda_n(p,s);
				t2=Lamda_w(p,s);
				return t1+t2;
			}
			double Lamdad_n (FVector_double &p,double s){
				double k=dk_n(p,s);
				return k/mu_n;
			}
			double Lamdad_w (FVector_double &p,double s){
				double k=dk_w(p,s);
				return k/mu_w;
			}
			double	Lamdad	(FVector_double &p,double s){
				double t1;	double t2;
				t1=Lamdad_n(p,s);
				t2=Lamdad_w(p,s);
				return t1+t2;
			}
			double	fn		(FVector_double& p, double s) {
				double t1; double t2;
				t1=Lamda(p,s);
				t2=Lamda_n(p,s);
				return t2/t1;
			}
			double	fw		(FVector_double& p, double s) {
				double t1; double t2;
				t1=Lamda(p,s);
				t2=Lamda_w(p,s);
				return t2/t1;
			}
			int	boundary_indicator_t	(FVector_double& p)	{
				int ret=1;
				// ret=1. normal. ret=0. dirichlet.
				double x=p[0];	double y=p[1];
				if ( (x==RX[0][0]) || (x==RX[1][0]) )
					ret=0;
				else
					ret=1;
				return ret;
			}
			int	boundary_indicator_w	(FVector_double& p)	{
				int ret=1;
				// ret=1. normal. ret=0. dirichlet.
				double x=p[0];	double y=p[1];
				if ( (x==RX[0][0]) || (x==RX[1][0]) )
					ret=0;
				else
					ret=1;
				return ret;
			}
			int	boundary_indicator_n	(FVector_double& p)	{
				int ret=1;
				// ret=1. normal. ret=0. dirichlet.
				double x=p[0];	double y=p[1];
				if ( (x==RX[0][0]) || (x==RX[1][0]) || (y==RX[0][1]) )
					ret=0;
				else
					ret=1;
				return ret;
			}
			
			double	flux_w(FVector_double& p){
				double x=p[0], y=p[1];
				double rt;
				if ((y==RX[1][1]) || (y==RX[0][1]) )
					rt=0.;
				return rt;
			}
			double	flux_n(FVector_double& p){
				double x=p[0], y=p[1];
				double rt;
				if ( (y==RX[0][1]) || (y==RX[1][1]) )
					rt=0.;
				if ((y==RX[1][1]) && (x>=0.384375) && (x<=0.51625) )
					rt=-0.075/rho_n;
				return rt;
			}
			double	flux_t(FVector_double& p){
				double rt;
				double f1;	double f2;
				f1=_problem->flux_w(p);
				f2=_problem->flux_n(p);
				rt=f1+f2;
				return rt;
			}
			double	K_p_(FVector_double & p) {
				double x=p[0], y=p[1];		
				double rt=0;
				if ((x>0.1875)&&(x<0.7125)&&(y>0.32)&&(y<0.4625))
					rt=3.32*pow(10.,-11.);
				else
					rt=6.64*pow(10.,-11.);
				return rt;
			}
			double	Phi_(FVector_double & p) {
				double x=p[0], y=p[1];		
				double rt=0;
				if ((x>=0.1875)&&(x<=0.7125)&&(y>=0.32)&&(y<=0.4625))
					rt=0.39;
				else
					rt=0.4;
				return rt;
			}
			double	Initial_Val(FVector_double & p) {
				double x=p[0], y=p[1];
				double rt=0;
				return rt;
			}
			
			double	dirichlet_t	(FVector_double& p) {
				double x=p[0], y=p[1];
				double rt=0;
				if	( (x==RX[0][0]) || (x==RX[1][0]) )
					rt=(0.65-y)*9810.;
				return rt;
			}
			double	dirichlet_w	(FVector_double& p) {
				double x=p[0], y=p[1];
				double rt=0;
				if	( (x==RX[0][0]) || (x==RX[1][0]) )
					rt=(0.65-y)*9810.;
				return rt;
			}
			double	dirichlet_n	(FVector_double& p) {
				double x=p[0], y=p[1];
				double rt=0;
				if	( (x==RX[0][0]) || (x==RX[1][0]) || (y==RX[0][1]) )
					rt=0.;
				return rt;
			}
			double pc (FVector_double& p, double sn){
				double x=p[0], y=p[1];
				double pd;
				double lamda;
				double sw_;
				double denom;
				if (sn<0)
					sn=0;
				if ((x>=0.1875)&&(x<=0.7125)&&(y>=0.32)&&(y<=0.4625)){
					pd = 1466;
					lamda=2.;
					denom=0.88;
					sw_=(1-sn-0.12)/denom;
				}
				else{
					pd=775.;
					lamda=2.7;
					denom=0.9;
					sw_=(1-sn-0.1)/denom;
				}
				return pd*pow(sw_,-1/lamda);
			}
			double dpc (FVector_double& p, double sn){
				double x=p[0], y=p[1];
				double pd;
				double lamda;
				double sw_;
				double denom;
				if (sn<0)
					sn=0;
				if ((x>=0.1875)&&(x<=0.7125)&&(y>=0.32)&&(y<=0.4625)){
					pd = 1466;
					lamda=2.;
					denom=0.88;
					sw_=(1-sn-0.12)/denom;
				}
				else{
					pd=775.;
					lamda=2.7;
					denom=0.9;
					sw_=(1-sn-0.1)/denom;
				}
				return -(-1/lamda)/denom*pd*pow(sw_,-1/lamda-1);
			}
			double ddpc (FVector_double& p, double sn){
				double x=p[0], y=p[1];
				double pd;
				double lamda;
				double denom;
				double sw_;
				if (sn<0)
					sn=0;
				if ((x>=0.1875)&&(x<=0.7125)&&(y>=0.32)&&(y<=0.4625)){
					pd=1466;
					lamda=2.;
					denom=0.88;
					sw_=(1-sn-0.12)/denom;
				}
				else{
					pd=775.;
					lamda=2.7;
					denom=0.9;
					sw_=(1-sn-0.1)/denom;
				}
				return (-1/lamda)*(-1/lamda-1)/denom/denom*pd*pow(sw_,-1/lamda-2);
			}
		};
		class Permeable_Lens2: public FEM_PROBLEM {
		public:
			// Parabolic Example. Example in Peter Bastian book 167p
			// pw, sn coupling.
			void		initialize	(FEM_VARIABLES::ENTIRE& __) {
				mu_w=pow(10.,-3.);	mu_n=0.9*pow(10.,-3.);	phi=0.4;
				phi_w=0.4;			phi_n=0.39;
				rho_w=1000.;		rho_n=1460.;
				__.dim = 2;
				eps=0.01;
				RX=__.RX.make(__.dim, __.dim).setAll(0., 0., 0.9, 0.65);
			//	cout << "INIT " << endl;
			}
			double	k_w	(FVector_double &p,double sn){
				double sw_;
				double lamda;
				double x=p[0];	double y=p[1];
				double denom;
				denom=0.9;
				sw_=(1-sn-0.1)/denom;
				lamda=2.7;
				return pow(sw_,(2.+3.*lamda)/lamda);
			}
			double	k_n	(FVector_double &p,double sn)	{
				double sn_;
				double lamda;
				double x=p[0];	double y=p[1];
				double denom;
				denom=0.9;
				sn_=sn/denom;
				lamda=2.7;
				return sn_*sn_*(1-pow((1-sn_),(2+lamda)/lamda) );
			}
			double	dk_w	(FVector_double &p,double s){
				double sw_;
				double lamda;
				double x=p[0];	double y=p[1];
				double denom;
				denom=0.9;
				sw_=(1-s-0.1)/denom;
				lamda=2.7;
				return -(2.+3.*lamda)/lamda/denom*pow(sw_,(2.+3.*lamda)/lamda-1.);
			}
			double	dk_n	(FVector_double &p,double s)	{
				double sn_;
				double lamda;
				double x=p[0];	double y=p[1];
				double denom;
				denom=0.9;
				sn_=(s)/denom;
				lamda=2.7;
				return 2.*sn_/denom*(1-pow((1-sn_),(2+lamda)/lamda)) + sn_*sn_*( (2+lamda)/lamda)/denom*pow(1.-sn_,2/lamda);
			}
			double	Lamda_n	(FVector_double &p,double s){
				double k=k_n(p,s);
				return k/mu_n;
			}
			double	Lamda_w	(FVector_double &p,double s){
				double k=k_w(p,s);
				return k/mu_w;
			}
			double	Lamda	(FVector_double &p,double s){
				double t1;	double t2;
				t1=Lamda_n(p,s);
				t2=Lamda_w(p,s);
				return t1+t2;
			}
			double Lamdad_n (FVector_double &p,double s){
				double k=dk_n(p,s);
				return k/mu_n;
			}
			double Lamdad_w (FVector_double &p,double s){
				double k=dk_w(p,s);
				return k/mu_w;
			}
			double	Lamdad	(FVector_double &p,double s){
				double t1;	double t2;
				t1=Lamdad_n(p,s);
				t2=Lamdad_w(p,s);
				return t1+t2;
			}
			double	fn		(FVector_double& p, double s) {
				double t1; double t2;
				t1=Lamda(p,s);
				t2=Lamda_n(p,s);
				return t2/t1;
			}
			double	fw		(FVector_double& p, double s) {
				double t1; double t2;
				t1=Lamda(p,s);
				t2=Lamda_w(p,s);
				return t2/t1;
			}
			int	boundary_indicator_t	(FVector_double& p)	{
				int ret=1;
				// ret=1. normal. ret=0. dirichlet.
				double x=p[0];	double y=p[1];
				if ( (x==RX[0][0]) || (x==RX[1][0]) )
					ret=0;
				else
					ret=1;
				return ret;
			}
			int	boundary_indicator_w	(FVector_double& p)	{
				int ret=1;
				// ret=1. normal. ret=0. dirichlet.
				double x=p[0];	double y=p[1];
				if ( (x==RX[0][0]) || (x==RX[1][0]) )
					ret=0;
				else
					ret=1;
				return ret;
			}
			int	boundary_indicator_n	(FVector_double& p)	{
				int ret=1;
				// ret=1. normal. ret=0. dirichlet.
				double x=p[0];	double y=p[1];
				if ( (x==RX[0][0]) || (x==RX[1][0]) || (y==RX[0][1]) )
					ret=0;
				else
					ret=1;
				return ret;
			}
			
			double	flux_w(FVector_double& p){
				double x=p[0], y=p[1];
				double rt;
				if ((y==RX[1][1]) || (y==RX[0][1]) )
					rt=0.;
				return rt;
			}
			double	flux_n(FVector_double& p){
				double x=p[0], y=p[1];
				double rt;
				if ( (y==RX[0][1]) || (y==RX[1][1]) )
					rt=0.;
				if ((y==RX[1][1]) && (x>=0.384375) && (x<=0.51625) )
					rt=-0.075/rho_n;
				return rt;
			}
			double	flux_t(FVector_double& p){
				double rt;
				double f1;	double f2;
				f1=_problem->flux_w(p);
				f2=_problem->flux_n(p);
				rt=f1+f2;
				return rt;
			}
			double	K_p_(FVector_double & p) {
				double x=p[0], y=p[1];		
				double rt=0;
				if ((x>0.1875)&&(x<0.7125)&&(y>0.32)&&(y<0.4625))
					rt=3.32*pow(10.,-11.);
				else
					rt=6.64*pow(10.,-11.);
				return rt;
			}
			double	Phi_(FVector_double & p) {
				double x=p[0], y=p[1];		
				double rt=0;
				rt=0.4;
				return rt;
			}
			double	Initial_Val(FVector_double & p) {
				double x=p[0], y=p[1];
				double rt=0;
				return rt;
			}
			
			double	dirichlet_t	(FVector_double& p) {
				double x=p[0], y=p[1];
				double rt=0;
				if	( (x==RX[0][0]) || (x==RX[1][0]) )
					rt=(0.65-y)*9810.;
				return rt;
			}
			double	dirichlet_w	(FVector_double& p) {
				double x=p[0], y=p[1];
				double rt=0;
				if	( (x==RX[0][0]) || (x==RX[1][0]) )
					rt=(0.65-y)*9810.;
				return rt;
			}
			double	dirichlet_n	(FVector_double& p) {
				double x=p[0], y=p[1];
				double rt=0;
				if	( (x==RX[0][0]) || (x==RX[1][0]) || (y==RX[0][1]) )
					rt=0.;
				return rt;
			}
			double pc (FVector_double& p, double sn){
				double x=p[0], y=p[1];
				double pd;
				double lamda;
				double sw_;
				double denom;
				if (sn<0)
					sn=0;
				pd=775.;
				lamda=2.7;
				denom=0.9;
				sw_=(1-sn-0.1)/denom;
				return pd*pow(sw_,-1/lamda);
			}
			double dpc (FVector_double& p, double sn){
				double x=p[0], y=p[1];
				double pd;
				double lamda;
				double sw_;
				double denom;
				if (sn<0)
					sn=0;
				pd=775.;
				lamda=2.7;
				denom=0.9;
				sw_=(1-sn-0.1)/denom;
				return -(-1/lamda)/denom*pd*pow(sw_,-1/lamda-1);
			}
			double ddpc (FVector_double& p, double sn){
				double x=p[0], y=p[1];
				double pd;
				double lamda;
				double denom;
				double sw_;
				if (sn<0)
					sn=0;
				pd=775.;
				lamda=2.7;
				denom=0.9;
				sw_=(1-sn-0.1)/denom;
				return (-1/lamda)*(-1/lamda-1)/denom/denom*pd*pow(sw_,-1/lamda-2);
			}
		};
		class Both_Fluids_At_Maximum_Saturation: public FEM_PROBLEM {
		public:
			// Parabolic, homogeneous capillary pressure. Example in Peter Bastian book 174pg
			// pw, sn coupling.
			void		initialize	(FEM_VARIABLES::ENTIRE& __) {
				mu_w=pow(10.,-3.);	mu_n=0.9*pow(10.,-3.);	phi=0.4;
				rho_w=1000.;		rho_n=1460.;
				__.dim = 2;
				eps=0.01;
				RX=__.RX.make(__.dim, __.dim).setAll(0., 0., 0.9, 0.65);
			//	cout << "INIT " << endl;
			}
			double	k_w	(double sn){
				double sw_=1-sn;
				double lamda=2;
				return pow(sw_,(2.+3.*lamda)/lamda);
			}
			double	k_n	(double sn)	{
				double sn_=sn;
				double lamda=2;
				return sn_*sn_*(1-pow((1-sn_),(2+lamda)/lamda) );
			}
			double	dk_w	(double s){
				double sw_=1-s;
				double lamda=2;
				return -(2.+3.*lamda)/lamda*pow(sw_,(2.+3.*lamda)/lamda-1.);
			}
			double	dk_n	(double s)	{
				double sn_=s;
				double lamda=2;
				return 2.*sn_*(1-pow((1-sn_),(2+lamda)/lamda)) + sn_*sn_*( (2+lamda)/lamda)*pow(1.-sn_,2/lamda);
			}
			double	Lamda_n	(double s){
				double k=k_n(s);
				return k/mu_n;
			}
			double	Lamda_w	(double s){
				double k=k_w(s);
				return k/mu_w;
			}
			double Lamdad_n (double s){
				double k=dk_n(s);
				return k/mu_n;
			}
			double Lamdad_w (double s){
				double k=dk_w(s);
				return k/mu_w;
			}
			int	boundary_indicator_w	(FVector_double& p)	{
				int ret=1;
				// ret=1. normal. ret=0. dirichlet.
				double x=p[0];	double y=p[1];
				if ( y==RX[1][1] )
					ret=0;
				else
					ret=1;
				return ret;
			}
			int	boundary_indicator_n	(FVector_double& p)	{
				int ret=1;
				// ret=1. normal. ret=0. dirichlet.
				double x=p[0];	double y=p[1];
				if (y==RX[0][1])
					ret=0;
				else
					ret=1;
				return ret;
			}
			double	flux_w(FVector_double& p){
				double x=p[0], y=p[1];
				double rt=0;
				return rt;
			}
			double	flux_n(FVector_double& p){
				double x=p[0], y=p[1];
				double rt=0;
				return rt;
			}

			double	Initial_Val(FVector_double & p) {
				double x=p[0], y=p[1];
				double rt=0;
				return rt;
			}
			double	dirichlet_w	(FVector_double& p) {
				double x=p[0], y=p[1];
				double rt=0;
				if	( y==RX[1][1])
					rt=pow(10.,5.);
				return rt;
			}
			double	dirichlet_n	(FVector_double& p) {
				double x=p[0], y=p[1];
				double rt=0;
				if	( y==RX[0][1] )
					rt=0.;
				return rt;
			}
			double pc (double sn){
				if (sn<0)
					sn=0;
				double pd=775;;
				double lamda=2;
				double sw_=1-sn;
				if (sw_<0)
					sw_=0;
				return pd*pow(sw_+eps,-1/lamda);
			}
			double dpc (double sn){
				if (sn<0)
					sn=0;
				double pd=775;;
				double lamda=2;
				double sw_=1-sn;
				if (sw_<0)
					sw_=0;
				return -(-1/lamda)*pd*pow(sw_+eps,-1/lamda-1);
			}
			double ddpc (FVector_double& p, double sn){
				if (sn<0)
					sn=0;
				double pd=775;;
				double lamda=2;
				double sw_=1-sn;
				if (sw_<0)
					sw_=0;
				return (-1/lamda)*(-1/lamda-1)*pd*pow(sw_+eps,-1/lamda-2);
			}
		};
		class HYPERBOLIC_EX_Interface: public FEM_PROBLEM {
		public:
			void		initialize	(FEM_VARIABLES::ENTIRE& __) {
				K_p=pow(10.,-7.);	mu=pow(10.,-3.);	phi=0.2;
				__.dim = 2;
				__.RX.make(__.dim, __.dim).setAll(0., 0., 300., 75.);
				boundary_inf_n.make(4);
				boundary_inf_w.make(4);
				boundary_inf_n.setAll(1, 1, 1, 0);
				boundary_inf_w.setAll(1, 0, 1, 0);
				nInterface=1;
				nFunction=101;
				r0=22.;
				mum=pow(10.,-3.);
				mup=pow(10.,0.);
			}

			double	Interface	(FVector_double& p) {
				double x=p[0], y=p[1];
				double r = sqrt((x-120)*(x-120) + (y-37.5)*(y-37.5));
				return (r - r0);
			}

			double	coef_mu		(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum,mup);
				return 0;
			}
			double	coef_mu		(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if(io == CV.IN) return mus[0];
				return mus[1];
			}
			double	coef_mu		(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if(Interface(p) < 0) {
					return mus[0];
				} else { 
					return mus[1];
				}
			}
			double	K_p_(FVector_double & p) {
				double x=p[0], y=p[1];		
				double rt=0;
				if(Interface(p) < 0) {
					rt=pow(10.,-10.);
				}
				if (Interface(p) > 0){ 
					rt=pow(10.,-7.);
				}
				return rt;
			}
			double	K_p_(FVector_double & p, FVector_double & vp) {
				double x = p[0], y = p[1];
				double rt = 0;
				vp[0] = pow(10., -10.);
				vp[1] = pow(10., -7.);
				return 0.;
			}

			double	k_n	(double s)	{
				return (1.-s)*(1.-s)*(1.-s*s);
			}

			double	k_w	(double s){
				return s*s*s*s;
			}
			double	Lamda_n	(double s){
				double k=k_n(s);
				return k/mu;
			}
			double	Lamda_w	(double s){
				double k=k_w(s);
				return k/mu;
			}
			double	Lamda	(double s){
				double t1;	double t2;
				t1=Lamda_n(s);
				t2=Lamda_w(s);
				return t1+t2;

			}
			double	Lamdad	(double s){
				double t1;	double t2;
				t1=Lamdad_n(s);
				t2=Lamdad_w(s);
				return t1+t2;

			}
			double Lamdad_n (double s){
				return (2.*(s-1.)*(1.-s*s)+(s-1.)*(s-1.)*(-2.*s))/mu;
			}
			double Lamdad_w (double s){
				return 4.*s*s*s/mu;
			}
			double	flux_n(FVector_double& p){
				double x=p[0], y=p[1];
				double rt;
				if (y==0.){
					rt=0.;
				}
				if (y==75.){
					rt=0.;
				}
				if (x==0){
					rt=0.;
				}
				if (x==300.){
					rt=3.*pow(10.,-7.);
				}
				return rt;
			}
			double	flux_w(FVector_double& p){
				double x=p[0], y=p[1];
				double rt;
				if (y==0.){
					rt=0.;
				}
				if (x==300.){
					rt=0;
				}
				if (y==75.){
					rt=0.;
				}
				if (x==0){
					rt=0.;
				}

				return rt;
			}

			double	saturation		(FVector_double& p) {
				double x=p[0], y=p[1];
				double rt;
				if (y==0.){
					rt=0.;
				}
				if (x==300.){
					rt=0;
				}
				if (y==75.){
					rt=0.;
				}
				if (x==0){
					rt=1.;
				}
				return rt;
			}
			double	pressure		(FVector_double& p) {
				double x=p[0], y=p[1];
				double rt;
				if (y==0.){
					rt=0.;
				}
				if (x==300.){
					rt=0;
				}
				if (y==75.){
					rt=0.;
				}
				if (x==0){
					rt=0;
				}
				return rt;
			}

		};
	};
	class IMPES {
	public:
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		//============================================================================
		//			Porous media phase Global Pressure Jaffre/Chavent
		//============================================================================
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		class BL_GH : public FEM_PROBLEM {
		public:
			void		initialize(FEM_VARIABLES::ENTIRE& __) {
				K_p = pow(10., 0.);	mu = pow(10., 0.);	phi = 1.;
				__.dim = 2;
				__.RX.make(__.dim, __.dim).setAll(0., 0., 1., 1.);
				boundary_inf_n.make(4);
				boundary_inf_w.make(4);
				boundary_inf_n.setAll(1, 1, 1, 0);
				boundary_inf_w.setAll(1, 0, 1, 0);
			}

			double	K_p_(FVector_double & p) {
				double x = p[0], y = p[1];
				return K_p;
			}

			double	k_n(double s)	{
				return (1. - s)*(1. - s)*(1. - s*s);
			}

			double	k_w(double s){
				return s*s*s*s;
			}
			double	Lamda_n(double s){
				double k = k_n(s);
				return k / mu;
			}
			double	Lamda_w(double s){
				double k = k_w(s);
				return k / mu;
			}
			double	Lamda(double s){
				double t1;	double t2;
				t1 = Lamda_n(s);
				t2 = Lamda_w(s);
				return t1 + t2;

			}
			double	Lamdad(double s){
				double t1;	double t2;
				t1 = Lamdad_n(s);
				t2 = Lamdad_w(s);
				return t1 + t2;

			}
			double Lamdad_n(double s){
				return (2.*(s - 1.)*(1. - s*s) + (s - 1.)*(s - 1.)*(-2.*s)) / mu;
			}
			double Lamdad_w(double s){
				return 4.*s*s*s / mu;
			}
			int	boundary_indicator_t(FVector_double& p)	{
				int ret = 1;
				// ret=1. normal. ret=0. dirichlet.
				double x = p[0];	double y = p[1];

				if (x == 0){
					ret = 0;
				}
				return ret;
			}
			int	boundary_indicator_w(FVector_double& p)	{
				int ret = 1;
				// ret=1. normal. ret=0. dirichlet.
				double x = p[0];	double y = p[1];
				if (((x >= 0) && (x <= 15) && (y == 0)) || ((y >= 0) && (y <= 15) && (x == 0))){
					ret = 1;
				}
				if (((x >= 285) && (x <= 300) && (y == 300)) || ((y >= 285) && (y <= 300) && (x == 300))){
					ret = 0;
				}
				return ret;
			}
			int	boundary_indicator_n(FVector_double& p)	{
				int ret = 1;
				// ret=1. normal. ret=0. dirichlet.
				double x = p[0];	double y = p[1];
				if (((x >= 0) && (x <= 15) && (y == 0)) || ((y >= 0) && (y <= 15) && (x == 0))){
					ret = 1;
				}
				if (((x >= 285) && (x <= 300) && (y == 300)) || ((y >= 285) && (y <= 300) && (x == 300))){
					ret = 0;
				}
				return ret;
			}
			double	flux_n(FVector_double& p){
				double x = p[0], y = p[1];
				double rt;
				if (y == 0.){
					rt = 0.;
				}
				if (y == 1.){
					rt = 0.;
				}
				if (x == 0){
					rt = 0.;
				}
				if (x == 1.){
					rt = 6.*pow(10., -1.);
				}
				return rt;
			}
			double	flux_w(FVector_double& p){
				double x = p[0], y = p[1];
				double rt;
				if (y == 0.){
					rt = 0.;
				}
				if (x == 1.){
					rt = 0;
				}
				if (y == 1.){
					rt = 0.;
				}
				if (x == 0){
					rt = 0.;
				}

				return rt;
			}

			double	saturation(FVector_double& p) {
				double x = p[0], y = p[1];
				double rt;
				if (y == 0.){
					rt = 0.;
				}
				if (x == 1.){
					rt = 0;
				}
				if (y == 1.){
					rt = 0.;
				}
				if (x == 0){
					rt = 1.;
				}
				return rt;
			}
			double	pressure(FVector_double& p) {
				double x = p[0], y = p[1];
				double rt;
				if (y == 0.){
					rt = 0.;
				}
				if (x == 1.){
					rt = 0;
				}
				if (y == 1.){
					rt = 0.;
				}
				if (x == 0){
					rt = 0;
				}
				return rt;
			}


		};
		class Five_Spot_Waterflooding_Multi_Interface : public FEM_PROBLEM {
		public:
			// Hyperbolic Example. Example in Peter Bastian book 167p
			void		initialize(FEM_VARIABLES::ENTIRE& __) {
				K_p = pow(10., -10.);	mu_w = pow(10., -3.);	mu_n = 4.*pow(10., -2.);	phi = 0.25;
				__.dim = 2;
				RX=__.RX.make(__.dim, __.dim).setAll(0., 0., 200., 200.);
				 vMum.make(3);

				mup = pow(10., -9.);
				mum = pow(10., -12.);
				vMum[0] = pow(10., -12.);
				vMum[1] = pow(10., -12.);
				vMum[2] = pow(10., -12.); 
			} 
			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				double rt = 0.00001*Interface0(p)*Interface1(p)*Interface2(p);
				//	cout << rt << endl;
				return rt;
			}
			double	Interface0(FVector_double& p) {
				double x = p[0], y = p[1];
				double rt = (x - 41)*(x - 41) + (y - 67)*(y - 67) - 20 * 20;
				return rt;
			}
			double	Interface1(FVector_double& p) {
				double x = p[0], y = p[1];
				double rt = (x - 119)*(x - 119) + (y - 57)*(y - 57) - 20 * 20;
				return rt;
			}
			double	Interface2(FVector_double& p) {
				double x = p[0], y = p[1];
				double rt = (x - 69)*(x - 69) + (y - 138)*(y - 138) - 18 * 18;

				return rt;
			}
			double	coef_mu(FVector_double& p) {

				if (Interface(p) > 0){
					return mup;
				}
				else{
					if (Interface0(p) <= 0){
						return vMum[0];
					}
					if (Interface1(p) <= 0){
						return vMum[1];
					}
					if (Interface2(p) <= 0){
						return vMum[2];
					}
				}
			}
			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			} 
			double	coef_mu(FVector_double& p, int io) {

				if (io == CV.OUT)
					return mup;
				if (io == CV.IN){
					if (Interface0(p) <= 4){
						return vMum[0];
					}
					if (Interface1(p) <= 4){
						return vMum[1];
					}
					if (Interface2(p) <= 4){
						return vMum[2];
					}
				}
			}
			double	k_n(double s)	{
				return (1. - s)*(1. - s)*(1. - s*s);
			}

			double	k_w(double s){
				return s*s*s*s;
			}
			double	Lamda_n(double s){
				double k = k_n(s);
				return k / mu_n;
			}
			double	Lamda_w(double s){
				double k = k_w(s);
				return k / mu_w;
			}
			double	Lamda(double s){
				double t1;	double t2;
				t1 = Lamda_n(s);
				t2 = Lamda_w(s);
				return t1 + t2;

			}
			double	Lamdad(double s){
				double t1;	double t2;
				t1 = Lamdad_n(s);
				t2 = Lamdad_w(s);
				return t1 + t2;

			}
			double Lamdad_n(double s){
				return (2.*(s - 1.)*(1. - s*s) + (s - 1.)*(s - 1.)*(-2.*s)) / mu_n;
			}
			double Lamdad_w(double s){
				return 4.*s*s*s / mu_w;
			}
			int	boundary_indicator_t(FVector_double& p)	{
				int ret = 1;
				// ret=1. normal. ret=0. dirichlet.
				double x = p[0];	double y = p[1];
				if (((x >= 187.5) && (x <= 200) && (y == 200)) || ((y >= 187.5) && (y <= 200) && (x == 200))){
					ret = 0;
				}
				return ret;
			}
			int	boundary_indicator_w(FVector_double& p)	{
				int ret = 1;
				// ret=1. normal. ret=0. dirichlet.
				double x = p[0];	double y = p[1];
				if (((x >= 187.5) && (x <= 200) && (y == 200)) || ((y >= 187.5) && (y <= 200) && (x == 200))){
					ret = 0;
				}	
				return ret;
			}
			double	flux_t(FVector_double& p){
				double x = p[0], y = p[1];
				double rt = 0;
				if (((x >= 0) && (x <= 12.5) && (y == 0)) || ((y >= 0) && (y <= 12.5) && (x == 0))){
					rt = -0.002 / 1000.;
				}
				return rt;
			}
			double	flux_w(FVector_double& p){
				double x = p[0], y = p[1];
				double rt = 0;
				if (((x >= 0) && (x <= 12.5) && (y == 0)) || ((y >= 0) && (y <= 12.5) && (x == 0))){
					rt = -0.002 / 1000.;
				}
				return rt;
			}
			double	K_p_(FVector_double & p) {
				if (Interface(p) > 0){
					return mup;
				}
				else{
					if (Interface0(p) <= 0){
						return vMum[0];
					}
					if (Interface1(p) <= 0){
						return vMum[1];
					}
					if (Interface2(p) <= 0){
						return vMum[2];
					}
				}
			}
			double	K_p_(FVector_double & p, FVector_double & vp) {
				double x = p[0], y = p[1];
				vp[0] = mum;
				vp[1] = mup;
				return 0.;
			}

			double	Initial_Val(FVector_double & p) {
				double x = p[0], y = p[1];
				double rt = 0; 
				rt = 0.;
				return rt;
			} 
			double	dirichlet_t(FVector_double& p) {
				return pow(10., 5.);
			}
			double	dirichlet_w(FVector_double& p) { 
				return 0.;
			}  
			double pc(double s){
				double pd = pow(10., 3.);
				if (s <0){
					s = 0;
				}
				return pd*pow(s + 10E-10, -0.5);
			}
			double	dpc(double s) { 
				double pd = pow(10., 3.);
				if (s <0){
					s = 0;
				}
				else{
					return  -0.5 * pd * pow(s + 10E-10, -1.5);

				}
			}
		};
		class Multi_Interfaces_Wells : public FEM_PROBLEM {
		public:
			// Hyperbolic Example. Example in Peter Bastian book 167p
			void		initialize(FEM_VARIABLES::ENTIRE& __) {
				K_p = pow(10., -10.);	mu_w = pow(10., -3.);	mu_n = 4.*pow(10., -2.);	phi = 0.25;
				__.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(0., 0., 400., 400.);
				vMum.make(3);

				mup = pow(10., -9.);
				mum = pow(10., -12.);
				vMum[0] = pow(10., -12.);
				vMum[1] = pow(10., -12.);
				vMum[2] = pow(10., -12.);
			}
			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				double rt = 0.00001*Interface0(p)*Interface1(p)*Interface2(p);
				rt = 1.;
				//	cout << rt << endl;
				return rt;
			}
			double	Interface0(FVector_double& p) {
				double x = p[0], y = p[1];
				double rt = (x - 41)*(x - 41) + (y - 67)*(y - 67) - 24 * 24;
				return rt;
			}
			double	Interface1(FVector_double& p) {
				double x = p[0], y = p[1];
				double rt = (x - 119)*(x - 119) + (y - 57)*(y - 57) - 20 * 20;
				return rt;
			}
			double	Interface2(FVector_double& p) {
				double x = p[0], y = p[1];
				double rt = (x - 68)*(x - 68) + (y - 134)*(y - 134) - 20 * 20;

				return rt;
			}
			double	coef_mu(FVector_double& p) {

				if (Interface(p) > 0){
					return mup;
				}
				else{
					if (Interface0(p) <= 0){
						return vMum[0];
					}
					if (Interface1(p) <= 0){
						return vMum[1];
					}
					if (Interface2(p) <= 0){
						return vMum[2];
					}
				}
			}
			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, Exterior)
				return 0;
			}
			double	coef_mu(FVector_double& p, int io) {

				if (io == CV.OUT)
					return mup;
				if (io == CV.IN){
					if (Interface0(p) <= 4){
						return vMum[0];
					}
					if (Interface1(p) <= 4){
						return vMum[1];
					}
					if (Interface2(p) <= 4){
						return vMum[2];
					}
				}
			}
			double	k_n(double s)	{
				return (1. - s)*(1. - s)*(1. - s*s);
			}

			double	k_w(double s){
				return s*s*s*s;
			}
			double	Lamda_n(double s){
				double k = k_n(s);
				return k / mu_n;
			}
			double	Lamda_w(double s){
				double k = k_w(s);
				return k / mu_w;
			}
			double	Lamda(double s){
				double t1;	double t2;
				t1 = Lamda_n(s);
				t2 = Lamda_w(s);
				return t1 + t2;

			}
			double	Lamdad(double s){
				double t1;	double t2;
				t1 = Lamdad_n(s);
				t2 = Lamdad_w(s);
				return t1 + t2;

			}
			double Lamdad_n(double s){
				return (2.*(s - 1.)*(1. - s*s) + (s - 1.)*(s - 1.)*(-2.*s)) / mu_n;
			}
			double Lamdad_w(double s){
				return 4.*s*s*s / mu_w;
			}
			int	boundary_indicator_t(FVector_double& p)	{
				int ret = 1;
				// ret=1. normal. ret=0. dirichlet.
				double x = p[0];	double y = p[1];
				if (((x >= 0) && (x <= 25) && (y == 0)) || ((y >= 0) && (y <= 25) && (x == 0))){
					ret = 0;
				}
				if (((x >= 175) && (x <= 200) && (y == 200)) || ((y >= 175) && (y <= 200) && (x == 200))){
					ret = 0;
				}
				return ret;
			}
			int	boundary_indicator_w(FVector_double& p)	{
				int ret = 1;
				// ret=1. normal. ret=0. dirichlet.
				double x = p[0];	double y = p[1];
				if (((x >= 0) && (x <= 25) && (y == 0)) || ((y >= 0) && (y <= 25) && (x == 0))){
					ret = 0;
				}
				if (((x >= 175) && (x <= 200) && (y == 200)) || ((y >= 175) && (y <= 200) && (x == 200))){
					ret = 0;
				}
				return ret;
			}
			double	flux_t(FVector_double& p){
				double x = p[0], y = p[1];
				double rt = 0; 
				return rt;
			}
			double	flux_w(FVector_double& p){
				double x = p[0], y = p[1];
				double rt = 0; 
				return rt;
			}
			double	K_p_(FVector_double & p) {
				if (Interface(p) > 0){
					return mup;
				}
				else{
					if (Interface0(p) <= 0){
						return vMum[0];
					}
					if (Interface1(p) <= 0){
						return vMum[1];
					}
					if (Interface2(p) <= 0){
						return vMum[2];
					}
				}
			}
			double	K_p_(FVector_double & p, FVector_double & vp) {
				double x = p[0], y = p[1];
				vp[0] = mum;
				vp[1] = mup;
				return 0.;
			}

			double	Initial_Val(FVector_double & p) {
				double x = p[0], y = p[1];
				double rt = 0;
				rt = 0.;
				return rt;
			}
			double	dirichlet_t(FVector_double& p) {
				return pow(10., 5.);
			}
			double	dirichlet_w(FVector_double& p) {
				return 0.;
			}
			double pc(double s){
				double pd = 5 * pow(10., 3.);
				if (s <0){
					s = 0;
				}
				return pd*pow(s + 10E-10, -0.5);
			}
			double	dpc(double s) {
				double pd = 5 * pow(10., 3.);
				if (s <0){
					s = 0;
				}
				else{
					return  -0.5 * pd * pow(s + 10E-10, -1.5);

				}
			}
		};
		class HYPERBOLIC_EX1: public FEM_PROBLEM {
		public:
			void		initialize	(FEM_VARIABLES::ENTIRE& __) {
				K_p=pow(10.,-7.);	mu=pow(10.,-3.);	phi=0.2;
				__.dim = 2;
				__.RX.make(__.dim, __.dim).setAll(0., 0., 300., 75.);
				boundary_inf_n.make(4);
				boundary_inf_w.make(4);
				boundary_inf_n.setAll(1, 1, 1, 0);
				boundary_inf_w.setAll(1, 0, 1, 0);
			}
			
			double	K_p_(FVector_double & p) {
				double x=p[0], y=p[1];		
				
				return K_p;
			}

			double	k_n	(double s)	{
				return (1.-s)*(1.-s)*(1.-s*s);
			}

			double	k_w	(double s){
				return s*s*s*s;
			}
			double	Lamda_n	(double s){
				double k=k_n(s);
				return k/mu;
			}
			double	Lamda_w	(double s){
				double k=k_w(s);
				return k/mu;
			}
			double	Lamda	(double s){
				double t1;	double t2;
				t1=Lamda_n(s);
				t2=Lamda_w(s);
				return t1+t2;

			}
			double	Lamdad	(double s){
				double t1;	double t2;
				t1=Lamdad_n(s);
				t2=Lamdad_w(s);
				return t1+t2;

			}
			double Lamdad_n (double s){
				return (2.*(s-1.)*(1.-s*s)+(s-1.)*(s-1.)*(-2.*s))/mu;
			}
			double Lamdad_w (double s){
				return 4.*s*s*s/mu;
			}
			int	boundary_indicator_t	(FVector_double& p)	{
				int ret=1;
				// ret=1. normal. ret=0. dirichlet.
				double x=p[0];	double y=p[1];
				
				if	( x==0 ){
					ret=0;
				}
				return ret;
			}
			int	boundary_indicator_w	(FVector_double& p)	{
				int ret=1;
				// ret=1. normal. ret=0. dirichlet.
				double x=p[0];	double y=p[1];
				if	( ((x>=0)&&(x<=15)&&(y==0)) || ((y>=0)&&(y<=15)&&(x==0)) ){
					ret=1;
				}
				if	( ((x>=285)&&(x<=300)&&(y==300)) || ((y>=285)&&(y<=300)&&(x==300)) ){
					ret=0;
				}
				return ret;
			}
			int	boundary_indicator_n	(FVector_double& p)	{
				int ret=1;
				// ret=1. normal. ret=0. dirichlet.
				double x=p[0];	double y=p[1];
				if	( ((x>=0)&&(x<=15)&&(y==0)) || ((y>=0)&&(y<=15)&&(x==0)) ){
					ret=1;
				}
				if	( ((x>=285)&&(x<=300)&&(y==300)) || ((y>=285)&&(y<=300)&&(x==300)) ){
					ret=0;
				}
				return ret;
			}
			double	flux_n(FVector_double& p){
				double x=p[0], y=p[1];
				double rt;
				if (y==0.){
					rt=0.;
				}
				if (y==75.){
					rt=0.;
				}
				if (x==0){
					rt=0.;
				}
				if (x==300.){
					rt=3.*pow(10.,-7.);
				}
				return rt;
			}
			double	flux_w(FVector_double& p){
				double x=p[0], y=p[1];
				double rt;
				if (y==0.){
					rt=0.;
				}
				if (x==300.){
					rt=0;
				}
				if (y==75.){
					rt=0.;
				}
				if (x==0){
					rt=0.;
				}

				return rt;
			}

			double	saturation		(FVector_double& p) {
				double x=p[0], y=p[1];
				double rt;
				if (y==0.){
					rt=0.;
				}
				if (x==300.){
					rt=0;
				}
				if (y==75.){
					rt=0.;
				}
				if (x==0){
					rt=1.;
				}
				return rt;
			}
			double	pressure		(FVector_double& p) {
				double x=p[0], y=p[1];
				double rt;
				if (y==0.){
					rt=0.;
				}
				if (x==300.){
					rt=0;
				}
				if (y==75.){
					rt=0.;
				}
				if (x==0){
					rt=0;
				}
				return rt;
			}


		};
		class FOKAS_ : public FEM_PROBLEM {
		public:
			void		initialize(FEM_VARIABLES::ENTIRE& __) {
				K_p = pow(10., 0.);	mu = pow(10., 0.);	phi = 1.;
				mu_w = 1.5;
				mu_n = 1.;
				__.dim = 2;
				__.RX.make(__.dim, __.dim).setAll(0., 0., 1., 1.);
				RX = __.RX;
				boundary_inf_n.make(4);
				boundary_inf_w.make(4);
				boundary_inf_n.setAll(1, 0, 1, 1);
				boundary_inf_w.setAll(1, 0, 1, 1);
				
				//	beta = 10;
				//	gamma = 20;
				//	alpha = -beta*beta*(gamma / beta)*(gamma / beta + 1); -600
				//		delta = beta - alpha*(beta + gamma) ^ (-1);       30

			}

			double	K_p_(FVector_double & p) {
				double x = p[0], y = p[1];
				return K_p;
			}

			double	k_n(double s)	{
				return (1. - s);
			}

			double	k_w(double s){
				return s;
			}
			double	Lamda_n(double s){
				double k = k_n(s);
				return k / mu_n;
			}
			double	Lamda_w(double s){
				double k = k_w(s);
				return k / mu_w;
			}
			double	Lamda(double s){
				double t1;	double t2;
				t1 = Lamda_n(s);
				t2 = Lamda_w(s);
				return t1 + t2;

			}
			double	Lamdad(double s){
				double t1;	double t2;
				t1 = Lamdad_n(s);
				t2 = Lamdad_w(s);
				return t1 + t2;

			}
			double Lamdad_n(double s){
				return -1. / mu_n;
			}
			double Lamdad_w(double s){
				return 1. / mu_w;
			}
			int	boundary_indicator_t(FVector_double& p)	{
				int ret = 1;
				// ret=1. normal. ret=0. dirichlet.
				double x = p[0];	double y = p[1];

				if (x == 1){
					ret = 0;
				}
				return ret;
			}
			double	dpc(double s) {

				if ( (s == 0) || (s==1) ){

					return 0.;
				}
				else{
					return -0.005 / (s * (1 - s) * (3 - s)  +10E-10 );

				}
			}
			double	flux_n(FVector_double& p){
				double x = p[0], y = p[1];
				double rt;
				if (y == 0.){
					rt = 0.;
				}
				if (y == 1.){
					rt = 0.;
				}
				if (x == 0){
					rt = -1.;
				}
				if (x == RX[1][0]){
					rt = 0.;
				}
				return rt;
			}
			double	flux_w(FVector_double& p){
				double x = p[0], y = p[1];
				double rt;
				if (y == 0.){
					rt = 0.;
				}
				if (x == RX[1][0]){
					rt = 0;
				}
				if (y == 1.){
					rt = 0.;
				}
				if (x == 0){
					rt = -1.;
				}

				return rt;
			}

			double	saturation(FVector_double& p) {
				double x = p[0], y = p[1];
				double rt;
				if (y == 0.){
					rt = 0.;
				}
				if (x == RX[1][0]){
					rt = 0;
				}
				if (y == 1.){
					rt = 0.;
				}
				if (x == 0){
					rt = 1.;
				}
				return rt;
			}
			double	pressure(FVector_double& p) {
				double x = p[0], y = p[1];
				double rt;
				if (y == 0.){
					rt = 0.;
				}
				if (x == RX[1][0]){
					rt = 0;
				}
				if (y == 1.){
					rt = 0.;
				}
				if (x == 0){
					rt = 0;
				}
				return rt;
			}


		};
		class HYPERBOLIC_EX_Interface: public FEM_PROBLEM {
		public:
			void		initialize	(FEM_VARIABLES::ENTIRE& __) {
				K_p=pow(10.,-7.);	mu=pow(10.,-3.);	phi=0.2;
				__.dim = 2;
				__.RX.make(__.dim, __.dim).setAll(0., 0., 300., 75.);
				boundary_inf_n.make(4);
				boundary_inf_w.make(4);
				boundary_inf_n.setAll(1, 1, 1, 0);
				boundary_inf_w.setAll(1, 0, 1, 0);
				nInterface=1;
				nFunction=101;
				r0=35.;
				mum=pow(10.,-2.);
				mup=pow(10.,0.);
			}

			double	Interface	(FVector_double& p) {
				double x=p[0], y=p[1];
				double r = sqrt((x-110)*(x-110) + (y-37.5)*(y-37.5));
				return (r - r0);
			}

			double	coef_mu		(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum,mup);
				return 0;
			}
			double	coef_mu		(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if(io == CV.IN) return mus[0];
				return mus[1];
			}
			double	coef_mu		(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if(Interface(p) < 0) {
					return mus[0];
				} else { 
					return mus[1];
				}
			}
			double	K_p_(FVector_double & p) {
				double x=p[0], y=p[1];		
				double rt=0;
				if(Interface(p) < 0) {
					rt=pow(10.,-9.);
				}
				if (Interface(p) > 0){ 
					rt=pow(10.,-7.);
				}
				return rt;
			}
			double	K_p_(FVector_double & p, FVector_double & vp) {
				double x = p[0], y = p[1];
				vp[0] = pow(10., -9.);
				vp[1] = pow(10., -7.);
				return 0.;
			}
			
			double	k_n	(double s)	{
				return (1.-s)*(1.-s)*(1.-s*s);
			}

			double	k_w	(double s){
				return s*s*s*s;
			}
			double	Lamda_n	(double s){
				double k=k_n(s);
				return k/mu;
			}
			double	Lamda_w	(double s){
				double k=k_w(s);
				return k/mu;
			}
			double	Lamda	(double s){
				double t1;	double t2;
				t1=Lamda_n(s);
				t2=Lamda_w(s);
				return t1+t2;

			}
			double	Lamdad	(double s){
				double t1;	double t2;
				t1=Lamdad_n(s);
				t2=Lamdad_w(s);
				return t1+t2;

			}
			double Lamdad_n (double s){
				return (2.*(s-1.)*(1.-s*s)+(s-1.)*(s-1.)*(-2.*s))/mu;
			}
			double Lamdad_w (double s){
				return 4.*s*s*s/mu;
			}
			double	flux_n(FVector_double& p){
				double x=p[0], y=p[1];
				double rt;
				if (y==0.){
					rt=0.;
				}
				if (y==75.){
					rt=0.;
				}
				if (x==0){
					rt=0.;
				}
				if (x==300.){
					rt=3.*pow(10.,-7.);
				}
				return rt;
			}
			double	flux_w(FVector_double& p){
				double x=p[0], y=p[1];
				double rt;
				if (y==0.){
					rt=0.;
				}
				if (x==300.){
					rt=0;
				}
				if (y==75.){
					rt=0.;
				}
				if (x==0){
					rt=0.;
				}

				return rt;
			}

			double	saturation		(FVector_double& p) {
				double x=p[0], y=p[1];
				double rt;
				if (y==0.){
					rt=0.;
				}
				if (x==300.){
					rt=0;
				}
				if (y==75.){
					rt=0.;
				}
				if (x==0){
					rt=1.;
				}
				return rt;
			}
			double	pressure		(FVector_double& p) {
				double x=p[0], y=p[1];
				double rt;
				if (y==0.){
					rt=0.;
				}
				if (x==300.){
					rt=0;
				}
				if (y==75.){
					rt=0.;
				}
				if (x==0){
					rt=0;
				}
				return rt;
			}

		};
		class PARABOLIC_EX1: public FEM_PROBLEM {
		public:
			// (sw, pn) couple
			void		initialize	(FEM_VARIABLES::ENTIRE& __) {
				K_p=pow(10.,-10.);	mu=pow(10.,-3.);	phi=0.3;
				__.dim = 2;
				RX=__.RX.make(__.dim, __.dim).setAll(0., 0., 1.6, 1.6);
				boundary_inf_n.make(4);
				boundary_inf_w.make(4);
				boundary_inf_n.setAll(1, 1, 1, 0);
				boundary_inf_w.setAll(1, 0, 1, 0);
				eps=0.1;
			}
			double	k_n	(double s)	{
				return (1.-s)*(1.-s)*(1.-s*s);
			}

			double	k_w	(double s){
				return s*s*s*s;
			}
			double	Lamda_n	(double s){
				double k=k_n(s);
				return k/mu;
			}
			double	Lamda_w	(double s){
				double k=k_w(s);
				return k/mu;
			}
			double Lamdad_n (double s){
				return (2.*(s-1.)*(1.-s*s)+(s-1.)*(s-1.)*(-2.*s))/mu;
			}
			double Lamdad_w (double s){
				return 4.*s*s*s/mu;
			}
			double	Lamda	(double s){
				double t1;	double t2;
				t1=Lamda_n(s);
				t2=Lamda_w(s);
				return t1+t2;
			}
			double	Lamdad	(double s){
				double t1;	double t2;
				t1=Lamdad_n(s);
				t2=Lamdad_w(s);
				return t1+t2;
			}
			double	fw		(double s){
				double t1; double t2;
				t1=Lamda(s);
				t2=Lamda_w(s);
				return t2/t1;
			}
			double	fn		(double s){
				double t1; double t2;
				t1=Lamda(s);
				t2=Lamda_n(s);
				return t2/t1;
			}
			double	flux_n(FVector_double& p){
				// u dot n or -K grad p
				double x=p[0], y=p[1];
				double rt;
				if (y==RX[0][1]){
					rt=0.;
				}
				if (y==RX[1][1]){
					rt=0.;
				}
				if (x==RX[1][0]){
					rt=0.;
				}
				return rt;
			}
			double	flux_w(FVector_double& p){
				double x=p[0], y=p[1];
				double rt;
				if (y==RX[0][1]){
					rt=0.;
				}
				if (y==RX[1][1]){
					rt=0.;
				}
				return rt;
			}
			double	saturation		(FVector_double& p) {
				double x=p[0], y=p[1];
				double rt;
				if (x==RX[0][0]){
					rt=1.;
				}
				if (x==RX[1][0]){
					rt=0.;
				}
				return rt;
			}
			double	pressure		(FVector_double& p) {
				double x=p[0], y=p[1];
				double rt;
				if (x==RX[0][0]){
					rt=2.*pow(10.,5.);
				}
				return rt;
			}
			double pc (double sw){
				double pd=5000.;
				if (sw <0){
					sw=0;
				}
				return pd*pow(sw+eps,-0.5);
			}
			double dpc (double sw){
				double pd=5000.;
				return -0.5*pd*pow(sw+eps,-1.5);
			}
			double ddpc (double sw){
				double pd=5000.;
				return 0.5*1.5*pd*pow(sw+eps,-2.5);
			}
		};
		class Five_Spot_Waterflooding_1: public FEM_PROBLEM {
		public:
			// Hyperbolic Example. Example in Peter Bastian book 167p
			void		initialize	(FEM_VARIABLES::ENTIRE& __) {
				K_p=pow(10.,-10.);	mu_w=pow(10.,-3.);	mu_n=20. * pow(10.,-3.);	phi=0.2;
				__.dim = 2;
				__.RX.make(__.dim, __.dim).setAll(0., 0., 300., 300.);
			}
			double	k_n	(double s)	{
				return (1.-s)*(1.-s)*(1.-s*s);
			}

			double	k_w	(double s){
				return s*s*s*s;
			}
			double	Lamda_n	(double s){
				double k=k_n(s);
				return k/mu_n;
			}
			double	Lamda_w	(double s){
				double k=k_w(s);
				return k/mu_w;
			}
			double	Lamda	(double s){
				double t1;	double t2;
				t1=Lamda_n(s);
				t2=Lamda_w(s);
				return t1+t2;

			}
			double	Lamdad	(double s){
				double t1;	double t2;
				t1=Lamdad_n(s);
				t2=Lamdad_w(s);
				return t1+t2;

			}
			double Lamdad_n (double s){
				return (2.*(s-1.)*(1.-s*s)+(s-1.)*(s-1.)*(-2.*s))/mu_n;
			}
			double Lamdad_w (double s){
				return 4.*s*s*s/mu_w;
			}
			int	boundary_indicator_t	(FVector_double& p)	{
				int ret=1;
				// ret=1. normal. ret=0. dirichlet.
				double x=p[0];	double y=p[1];
				if	( ((x>=0)&&(x<=15)&&(y==0)) || ((y>=0)&&(y<=15)&&(x==0)) ){
					ret=1;
				}
				if	( ((x>=285)&&(x<=300)&&(y==300)) || ((y>=285)&&(y<=300)&&(x==300)) ){
					ret=0;
				}
				return ret;
			}
			int	boundary_indicator_w	(FVector_double& p)	{
				int ret=1;
				// ret=1. normal. ret=0. dirichlet.
				double x=p[0];	double y=p[1];
				if	( ((x>=0)&&(x<=15)&&(y==0)) || ((y>=0)&&(y<=15)&&(x==0)) ){
					ret=1;
				}
				if	( ((x>=285)&&(x<=300)&&(y==300)) || ((y>=285)&&(y<=300)&&(x==300)) ){
					ret=0;
				}
				return ret;
			}
			int	boundary_indicator_n	(FVector_double& p)	{
				int ret=1;
				// ret=1. normal. ret=0. dirichlet.
				double x=p[0];	double y=p[1];
				if	( ((x>=0)&&(x<=15)&&(y==0)) || ((y>=0)&&(y<=15)&&(x==0)) ){
					ret=1;
				}
				if	( ((x>=285)&&(x<=300)&&(y==300)) || ((y>=285)&&(y<=300)&&(x==300)) ){
					ret=0;
				}
				return ret;
			}
			double	flux_t(FVector_double& p){
				double x=p[0], y=p[1];
				double rt=0;
				if	( ((x>=0)&&(x<=15)&&(y==0)) || ((y>=0)&&(y<=15)&&(x==0)) ){
					rt=-0.0032/1000.;
				}
				return rt;
			}
			double	flux_w(FVector_double& p){
				double x=p[0], y=p[1];
				double rt=0;
				if	( ((x>=0)&&(x<=15)&&(y==0)) || ((y>=0)&&(y<=15)&&(x==0)) ){
					rt=-0.0032/1000.;
				}
				return rt;
			}
			double	flux_n(FVector_double& p){
				double x=p[0], y=p[1];
				double rt=0;
				
				return rt;
			}
			double	K_p_(FVector_double & p) {
				double x=p[0], y=p[1];		
				return K_p;
			}
			double	Initial_Val(FVector_double & p) {
				double x=p[0], y=p[1];		
				return 0;
			}
			
			double	dirichlet_t	(FVector_double& p) {
				double x=p[0], y=p[1];
				double rt=0;
				if	( ((x>=285)&&(x<=300)&&(y==300)) || ((y>=285)&&(y<=300)&&(x==300)) ){
					rt=pow(10.,5.);
				}
				return rt;
			}
			double	dirichlet_w	(FVector_double& p) {
				double x=p[0], y=p[1];
				double rt=0;
				if	( ((x>=285)&&(x<=300)&&(y==300)) || ((y>=285)&&(y<=300)&&(x==300)) ){
					rt=0.;
				}
				return rt;
			}
			double	dirichlet_n	(FVector_double& p) {
				double x=p[0], y=p[1];
				double rt=0;
				if	( ((x>=285)&&(x<=300)&&(y==300)) || ((y>=285)&&(y<=300)&&(x==300)) ){
					rt=pow(10.,5.);
				}
				return rt;
			}

		};
		class Five_Spot_Waterflooding_2: public FEM_PROBLEM {
		public:
			// Hyperbolic Example. Example in Peter Bastian book 167p
			void		initialize	(FEM_VARIABLES::ENTIRE& __) {
				K_p=pow(10.,-10.);	mu_w=pow(10.,-3.);	mu_n=20.*pow(10.,-3.);	phi=0.2;
				__.dim = 2;
				__.RX.make(__.dim, __.dim).setAll(0., 0., 300., 300.);
			}
			double	k_n	(double s)	{
				return (1.-s)*(1.-s)*(1.-s*s);
			}

			double	k_w	(double s){
				return s*s*s*s;
			}
			double	Lamda_n	(double s){
				double k=k_n(s);
				return k/mu_n;
			}
			double	Lamda_w	(double s){
				double k=k_w(s);
				return k/mu_w;
			}
			double	Lamda	(double s){
				double t1;	double t2;
				t1=Lamda_n(s);
				t2=Lamda_w(s);
				return t1+t2;

			}
			double	Lamdad	(double s){
				double t1;	double t2;
				t1=Lamdad_n(s);
				t2=Lamdad_w(s);
				return t1+t2;

			}
			double Lamdad_n (double s){
				return (2.*(s-1.)*(1.-s*s)+(s-1.)*(s-1.)*(-2.*s))/mu_n;
			}
			double Lamdad_w (double s){
				return 4.*s*s*s/mu_w;
			}
			int	boundary_indicator_t	(FVector_double& p)	{
				int ret=1;
				// ret=1. normal. ret=0. dirichlet.
				double x=p[0];	double y=p[1];
				if	( ((x>=0)&&(x<=15)&&(y==0)) || ((y>=0)&&(y<=15)&&(x==0)) ){
					ret=1;
				}
				if	( ((x>=285)&&(x<=300)&&(y==300)) || ((y>=285)&&(y<=300)&&(x==300)) ){
					ret=0;
				}
				return ret;
			}
			int	boundary_indicator_w	(FVector_double& p)	{
				int ret=1;
				// ret=1. normal. ret=0. dirichlet.
				double x=p[0];	double y=p[1];
				if	( ((x>=0)&&(x<=15)&&(y==0)) || ((y>=0)&&(y<=15)&&(x==0)) ){
					ret=1;
				}
				if	( ((x>=285)&&(x<=300)&&(y==300)) || ((y>=285)&&(y<=300)&&(x==300)) ){
					ret=0;
				}
				return ret;
			}
			int	boundary_indicator_n	(FVector_double& p)	{
				int ret=1;
				// ret=1. normal. ret=0. dirichlet.
				double x=p[0];	double y=p[1];
				if	( ((x>=0)&&(x<=15)&&(y==0)) || ((y>=0)&&(y<=15)&&(x==0)) ){
					ret=1;
				}
				if	( ((x>=285)&&(x<=300)&&(y==300)) || ((y>=285)&&(y<=300)&&(x==300)) ){
					ret=0;
				}
				return ret;
			}
			double	flux_t(FVector_double& p){
				double x=p[0], y=p[1];
				double rt=0;
				if	( ((x>=0)&&(x<=15)&&(y==0)) || ((y>=0)&&(y<=15)&&(x==0)) ){
					rt=-0.0032/1000.;
				}
				return rt;
			}
			double	flux_w(FVector_double& p){
				double x=p[0], y=p[1];
				double rt=0;
				if	( ((x>=0)&&(x<=15)&&(y==0)) || ((y>=0)&&(y<=15)&&(x==0)) ){
					rt=-0.0032/1000.;
				}
				return rt;
			}
			double	K_p_(FVector_double & p) {
				double x=p[0], y=p[1];		
				double rt=0;
				if ( (x>33.3)&&(x<133.3)&&(y>88.8)&&(y<233.3) )
					rt=pow(10.,-16.);
				else
					rt=pow(10.,-10.);
				return rt;
			}
			double	Initial_Val(FVector_double & p) {
				double x=p[0], y=p[1];
				double rt=0;
				if ( (x>30.)&&(x<140.)&&(y>170.7)&&(y<243.3) )
					rt=0.8;
				else
					rt=0.;
				return rt;
			}
			
			double	dirichlet_t	(FVector_double& p) {
				double x=p[0], y=p[1];
				double rt=0;
				if	( ((x>=285)&&(x<=300)&&(y==300)) || ((y>=285)&&(y<=300)&&(x==300)) ){
					rt=pow(10.,5.);
				}
				return rt;
			}
			double	dirichlet_w	(FVector_double& p) {
				double x=p[0], y=p[1];
				double rt=0;
				if	( ((x>=285)&&(x<=300)&&(y==300)) || ((y>=285)&&(y<=300)&&(x==300)) ){
					rt=0.;
				}
				return rt;
			}
			double	dirichlet_n	(FVector_double& p) {
				double x=p[0], y=p[1];
				double rt=0;
				if	( ((x>=285)&&(x<=300)&&(y==300)) || ((y>=285)&&(y<=300)&&(x==300)) ){
					rt=pow(10.,5.);
				}
				return rt;
			}

		};
		class Five_Spot_Waterflooding_Interface: public FEM_PROBLEM {
		public:
			// Hyperbolic Example. Example in Peter Bastian book 167p
			void		initialize	(FEM_VARIABLES::ENTIRE& __) {
				K_p=pow(10.,-10.);	mu_w=pow(10.,-3.);	mu_n=20.*pow(10.,-3.);	phi=0.2;
				__.dim = 2;
				__.RX.make(__.dim, __.dim).setAll(0., 0., 300., 300.);
				nInterface=1;
				nFunction=101;
				r0=50.;
				mum=pow(10.,-4.);
				mup=pow(10.,0.);
			//	mum=1.;
			//	mup=1.;
			}
 
			double	Interface	(FVector_double& p) {
				double x=p[0], y=p[1];
				double r = sqrt((x-85)*(x-85) + (y-185)*(y-185));
				return (r - r0);
			}

			double	coef_mu		(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum,mup);
				return 0;
			}
			double	coef_mu		(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if(io == CV.IN) return mus[0];
				return mus[1];
			}
			double	coef_mu		(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if(Interface(p) < 0) {
					return mus[0];
				} else { 
					return mus[1];
				}
			}
			double	k_n	(double s)	{
				return (1.-s)*(1.-s)*(1.-s*s);
			}

			double	k_w	(double s){
				return s*s*s*s;
			}
			double	Lamda_n	(double s){
				double k=k_n(s);
				return k/mu_n;
			}
			double	Lamda_w	(double s){
				double k=k_w(s);
				return k/mu_w;
			}
			double	Lamda	(double s){
				double t1;	double t2;
				t1=Lamda_n(s);
				t2=Lamda_w(s);
				return t1+t2;

			}
			double	Lamdad	(double s){
				double t1;	double t2;
				t1=Lamdad_n(s);
				t2=Lamdad_w(s);
				return t1+t2;

			}
			double Lamdad_n (double s){
				return (2.*(s-1.)*(1.-s*s)+(s-1.)*(s-1.)*(-2.*s))/mu_n;
			}
			double Lamdad_w (double s){
				return 4.*s*s*s/mu_w;
			}
			int	boundary_indicator_t	(FVector_double& p)	{
				int ret=1;
				// ret=1. normal. ret=0. dirichlet.
				double x=p[0];	double y=p[1];
				if	( ((x>=0)&&(x<=15)&&(y==0)) || ((y>=0)&&(y<=15)&&(x==0)) ){
					ret=1;
				}
				if	( ((x>=285)&&(x<=300)&&(y==300)) || ((y>=285)&&(y<=300)&&(x==300)) ){
					ret=0;
				}
				return ret;
			}
			int	boundary_indicator_w	(FVector_double& p)	{
				int ret=1;
				// ret=1. normal. ret=0. dirichlet.
				double x=p[0];	double y=p[1];
				if	( ((x>=0)&&(x<=15)&&(y==0)) || ((y>=0)&&(y<=15)&&(x==0)) ){
					ret=1;
				}
				if	( ((x>=285)&&(x<=300)&&(y==300)) || ((y>=285)&&(y<=300)&&(x==300)) ){
					ret=0;
				}
				return ret;
			}
			int	boundary_indicator_n	(FVector_double& p)	{
				int ret=1;
				// ret=1. normal. ret=0. dirichlet.
				double x=p[0];	double y=p[1];
				if	( ((x>=0)&&(x<=15)&&(y==0)) || ((y>=0)&&(y<=15)&&(x==0)) ){
					ret=1;
				}
				if	( ((x>=285)&&(x<=300)&&(y==300)) || ((y>=285)&&(y<=300)&&(x==300)) ){
					ret=0;
				}
				return ret;
			}
			double	flux_t(FVector_double& p){
				double x=p[0], y=p[1];
				double rt=0;
				if	( ((x>=0)&&(x<=15)&&(y==0)) || ((y>=0)&&(y<=15)&&(x==0)) ){
					rt=-0.0032/1000.;
				}
				return rt;
			}
			double	flux_w(FVector_double& p){
				double x=p[0], y=p[1];
				double rt=0;
				if	( ((x>=0)&&(x<=15)&&(y==0)) || ((y>=0)&&(y<=15)&&(x==0)) ){
					rt=-0.0032/1000.;
				}
				return rt;
			}
			double	K_p_(FVector_double & p) {
				double x=p[0], y=p[1];		
				double rt=0;
				if(Interface(p) < 0) {
					rt=pow(10.,-14.);
				}
				if (Interface(p) > 0){ 
					rt=pow(10.,-10.);
				}
				return rt;
			}
			double	K_p_(FVector_double & p, FVector_double & vp) {
				double x = p[0], y = p[1];
				vp[0] = pow(10., -14.);
				vp[1] = pow(10., -10.);
				return 0.;
			}

			double	Initial_Val(FVector_double & p) {
				double x=p[0], y=p[1];
				double rt=0;
				if ( (x>30.)&&(x<140.)&&(y>170.7)&&(y<243.3) )
					rt=0.8;
				else
					rt=0.;
				return rt;
			}
			
			double	dirichlet_t	(FVector_double& p) {
				double x=p[0], y=p[1];
				double rt=0;
				if	( ((x>=285)&&(x<=300)&&(y==300)) || ((y>=285)&&(y<=300)&&(x==300)) ){
					rt=pow(10.,5.);
				}
				return rt;
			}
			double	dirichlet_w	(FVector_double& p) {
				double x=p[0], y=p[1];
				double rt=0;
				if	( ((x>=285)&&(x<=300)&&(y==300)) || ((y>=285)&&(y<=300)&&(x==300)) ){
					rt=0.;
				}
				return rt;
			}
			double	dirichlet_n	(FVector_double& p) {
				double x=p[0], y=p[1];
				double rt=0;
				if	( ((x>=285)&&(x<=300)&&(y==300)) || ((y>=285)&&(y<=300)&&(x==300)) ){
					rt=pow(10.,5.);
				}
				return rt;
			}

		};
		class Permeable_Lens : public FEM_PROBLEM {
		public:
			// Parabolic Example. Example in Peter Bastian book 167p
			// pw, sn coupling.
			void		initialize(FEM_VARIABLES::ENTIRE& __) {
				mu_w = pow(10., -3.);	mu_n = 0.9*pow(10., -3.);	phi = 0.4;
				phi_w = 0.4;			phi_n = 0.39;
				rho_w = 1000.;		rho_n = 1460.;
				__.dim = 2;
				eps = 0.01;
				RX = __.RX.make(__.dim, __.dim).setAll(0., 0., 0.9, 0.65);
				//	cout << "INIT " << endl;
			}
			double	k_w(FVector_double &p, double sn){
				double sw_;
				double lamda;
				double x = p[0];	double y = p[1];
				double denom;
				if ((x>0.1875) && (x<0.7125) && (y>0.32) && (y<0.4625)){
					denom = 0.88;
					sw_ = (1 - sn - 0.12) / denom;
					lamda = 2.;
				}
				else{
					denom = 0.9;
					sw_ = (1 - sn - 0.1) / denom;
					lamda = 2.7;
				}
				return pow(sw_, (2. + 3.*lamda) / lamda);
			}
			double	k_n(FVector_double &p, double sn)	{
				double sn_;
				double lamda;
				double x = p[0];	double y = p[1];
				double denom;
				if ((x>0.1875) && (x<0.7125) && (y>0.32) && (y<0.4625)){
					denom = 0.88;
					sn_ = sn / denom;
					lamda = 2.;
				}
				else{
					denom = 0.9;
					sn_ = sn / denom;
					lamda = 2.7;
				}
				return sn_*sn_*(1 - pow((1 - sn_), (2 + lamda) / lamda));
			}
			double	dk_w(FVector_double &p, double s){
				double sw_;
				double lamda;
				double x = p[0];	double y = p[1];
				double denom;
				if ((x>0.1875) && (x<0.7125) && (y>0.32) && (y<0.4625)){
					denom = 0.88;
					sw_ = (1 - s - 0.12) / denom;
					lamda = 2.;
				}
				else{
					denom = 0.9;
					sw_ = (1 - s - 0.1) / denom;
					lamda = 2.7;
				}
				return -(2. + 3.*lamda) / lamda / denom*pow(sw_, (2. + 3.*lamda) / lamda - 1.);
			}
			double	dk_n(FVector_double &p, double s)	{
				double sn_;
				double lamda;
				double x = p[0];	double y = p[1];
				double denom;
				if ((x>0.1875) && (x<0.7125) && (y>0.32) && (y<0.4625)){
					denom = 0.88;
					sn_ = (s) / denom;
					lamda = 2.;
				}
				else{
					denom = 0.9;
					sn_ = (s) / denom;
					lamda = 2.7;
				}
				return 2.*sn_ / denom*(1 - pow((1 - sn_), (2 + lamda) / lamda)) + sn_*sn_*((2 + lamda) / lamda) / denom * 2 * pow(1. - sn_, 2 / lamda);
			}
			double	Lamda_n(FVector_double &p, double s){
				double k = k_n(p, s);
				return k / mu_n;
			}
			double	Lamda_w(FVector_double &p, double s){
				double k = k_w(p, s);
				return k / mu_w;
			}
			double	Lamda(FVector_double &p, double s){
				double t1;	double t2;
				t1 = Lamda_n(p, s);
				t2 = Lamda_w(p, s);
				return t1 + t2;
			}
			double Lamdad_n(FVector_double &p, double s){
				double k = dk_n(p, s);
				return k / mu_n;
			}
			double Lamdad_w(FVector_double &p, double s){
				double k = dk_w(p, s);
				return k / mu_w;
			}
			double	Lamdad(FVector_double &p, double s){
				double t1;	double t2;
				t1 = Lamdad_n(p, s);
				t2 = Lamdad_w(p, s);
				return t1 + t2;
			}
			double	fn(FVector_double& p, double s) {
				double t1; double t2;
				t1 = Lamda(p, s);
				t2 = Lamda_n(p, s);
				return t2 / t1;
			}
			double	fw(FVector_double& p, double s) {
				double t1; double t2;
				t1 = Lamda(p, s);
				t2 = Lamda_w(p, s);
				return t2 / t1;
			}
			int	boundary_indicator_t(FVector_double& p)	{
				int ret = 1;
				// ret=1. normal. ret=0. dirichlet.
				double x = p[0];	double y = p[1];
				if ((x == RX[0][0]) || (x == RX[1][0]))
					ret = 0;
				else
					ret = 1;
				return ret;
			}
			int	boundary_indicator_w(FVector_double& p)	{
				int ret = 1;
				// ret=1. normal. ret=0. dirichlet.
				double x = p[0];	double y = p[1];
				if ((x == RX[0][0]) || (x == RX[1][0]))
					ret = 0;
				else
					ret = 1;
				return ret;
			}
			int	boundary_indicator_n(FVector_double& p)	{
				int ret = 1;
				// ret=1. normal. ret=0. dirichlet.
				double x = p[0];	double y = p[1];
				if ((x == RX[0][0]) || (x == RX[1][0]) || (y == RX[0][1]))
					ret = 0;
				else
					ret = 1;
				return ret;
			}

			double	flux_w(FVector_double& p){
				double x = p[0], y = p[1];
				double rt;
				if ((y == RX[1][1]) || (y == RX[0][1]))
					rt = 0.;
				return rt;
			}
			double	flux_n(FVector_double& p){
				double x = p[0], y = p[1];
				double rt;
				if ((y == RX[0][1]) || (y == RX[1][1]))
					rt = 0.;
				if ((y == RX[1][1]) && (x >= 0.384375) && (x <= 0.51625))
					rt = -0.075 / rho_n;
				return rt;
			}
			double	flux_t(FVector_double& p){
				double rt;
				double f1;	double f2;
				f1 = _problem->flux_w(p);
				f2 = _problem->flux_n(p);
				rt = f1 + f2;
				return rt;
			}
			double	K_p_(FVector_double & p) {
				double x = p[0], y = p[1];
				double rt = 0;
				if ((x>0.1875) && (x<0.7125) && (y>0.32) && (y<0.4625))
					rt = 3.32*pow(10., -11.);
				else
					rt = 6.64*pow(10., -11.);
				return rt;
			}
			double	Phi_(FVector_double & p) {
				double x = p[0], y = p[1];
				double rt = 0;
				if ((x >= 0.1875) && (x <= 0.7125) && (y >= 0.32) && (y <= 0.4625))
					rt = 0.39;
				else
					rt = 0.4;
				return rt;
			}
			double	Initial_Val(FVector_double & p) {
				double x = p[0], y = p[1];
				double rt = 0;
				return rt;
			}

			double	dirichlet_t(FVector_double& p) {
				double x = p[0], y = p[1];
				double rt = 0;
				if ((x == RX[0][0]) || (x == RX[1][0]))
					rt = (0.65 - y)*9810.;
				return rt;
			}
			double	dirichlet_w(FVector_double& p) {
				double x = p[0], y = p[1];
				double rt = 0;
				if ((x == RX[0][0]) || (x == RX[1][0]))
					rt = (0.65 - y)*9810.;
				return rt;
			}
			double	dirichlet_n(FVector_double& p) {
				double x = p[0], y = p[1];
				double rt = 0;
				if ((x == RX[0][0]) || (x == RX[1][0]) || (y == RX[0][1]))
					rt = 0.;
				return rt;
			}
			double pc(FVector_double& p, double sn){
				double x = p[0], y = p[1];
				double pd;
				double lamda;
				double sw_;
				double denom;
				if (sn<0)
					sn = 0;
				if ((x >= 0.1875) && (x <= 0.7125) && (y >= 0.32) && (y <= 0.4625)){
					pd = 1466;
					lamda = 2.;
					denom = 0.88;
					sw_ = (1 - sn - 0.12) / denom;
				}
				else{
					pd = 775.;
					lamda = 2.7;
					denom = 0.9;
					sw_ = (1 - sn - 0.1) / denom;
				}
				return pd*pow(sw_, -1 / lamda);
			}
			double dpc(FVector_double& p, double sn){
				double x = p[0], y = p[1];
				double pd;
				double lamda;
				double sw_;
				double denom;
				if (sn<0)
					sn = 0;
				if ((x >= 0.1875) && (x <= 0.7125) && (y >= 0.32) && (y <= 0.4625)){
					pd = 1466;
					lamda = 2.;
					denom = 0.88;
					sw_ = (1 - sn - 0.12) / denom;
				}
				else{
					pd = 775.;
					lamda = 2.7;
					denom = 0.9;
					sw_ = (1 - sn - 0.1) / denom;
				}
				return -(-1 / lamda) / denom*pd*pow(sw_, -1 / lamda - 1);
			}
			double ddpc(FVector_double& p, double sn){
				double x = p[0], y = p[1];
				double pd;
				double lamda;
				double denom;
				double sw_;
				if (sn<0)
					sn = 0;
				if ((x >= 0.1875) && (x <= 0.7125) && (y >= 0.32) && (y <= 0.4625)){
					pd = 1466;
					lamda = 2.;
					denom = 0.88;
					sw_ = (1 - sn - 0.12) / denom;
				}
				else{
					pd = 775.;
					lamda = 2.7;
					denom = 0.9;
					sw_ = (1 - sn - 0.1) / denom;
				}
				return (-1 / lamda)*(-1 / lamda - 1) / denom / denom*pd*pow(sw_, -1 / lamda - 2);
			}
		}; 
		class Interface_Smooth_Sol_Line_Interface : public FEM_PROBLEM {
		public:
			// Exact Solution.
			// Line Interface
			void		initialize(FEM_VARIABLES::ENTIRE& __) {
				cout << " Line Interface Line Interface sdifojsdifj " << endl;
				K_p = pow(10., 0.);	mu_w = 1.;	mu_n = 1.;	phi = 1.;
				__.dim = 2;
				__.RX.make(__.dim, __.dim).setAll(0., 0., CV.PI / 2., CV.PI/2.);
				nInterface = 1;
				nFunction = 101;
				r0 = 0.2911;
				mum = pow(10., -3.);
			//	mum = pow(10., 0.);
				mup = pow(10., 0.);
				cl = 1.;
				cr = 3.;
			}
			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				double t = x + y;
				double r = (t - 1.)*(t - 3.);
				return r;
			}

			void	DInterface(FVector_double& p, FVector_double& vDI) {
				double x = p[0], y = p[1];
				double t = x + y;
				vDI[0] = 2.*(t - 2.);
				vDI[1] = 2.*(t - 2.);

			}
			void	DDInterface(FVector_double& p, FMatrix_double& mDDI)	{
				double x = p[0], y = p[1];
				mDDI[0][0] = 2.;
				mDDI[1][1] = 2.;
			}

			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);
				return 0;
			}
			double	coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.
				if (Interface(p) < 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}
			double	sw(double t, FVector_double& p) {
				double x = p[0], y = p[1];
				double s = x + y;
				double rt;
				double t_ = 0.7*t+0.1;
				
				if (Interface(p) > 0){
					if (s < 1.){
						rt = (1 - 5. / 4. * t_)*(s - 1.)*(s - 1.) - t_ / 4. * (s - 1.) + t_;
					}
					if (s>3.){
						rt = -t_ / 4. * (s - 3.)*(s - 3.) - t_ / 4. * (s - 3.) + t_ / 2;
					}
				}
				if (Interface(p) <= 0){
					rt = -t_ / 4. * (s - 1.) + t_;
				}
				return rt;

			}
			double 	Dtsw(double t, FVector_double& p) {
				double x = p[0], y = p[1];
				double s = x + y;
				double rt;
				double t_ = 0.7*t + 0.1;
		
				if (Interface(p) > 0){
					if (s < 1.)
						rt = -5. / 4. *  0.7 *(s - 1.)*(s - 1.) - 0.7 / 4. * (s - 1.) + 0.7;
					if (s >3.)
						rt = -0.7 / 4. * (s - 3.)*(s - 3.) - 0.7 / 4. * (s - 3.) + 0.7 / 2.;
				}
				if (Interface(p) <= 0){
					rt = -0.7 / 4. * (s - 1.) + 0.7;
				}
				return rt;
			}
			void	Dsw(double t, FVector_double& p, FVector_double & vDS) {
				double x = p[0], y = p[1];
				double s = x + y;
				double t_ = 0.7*t + 0.1;

				if (Interface(p) > 0){
					if (s < 1.){
						vDS[0] = (1 - 5. / 4. * t_)*2.*(s - 1.) - t_ / 4;
						vDS[1] = (1 - 5. / 4. * t_)*2.*(s - 1.) - t_ / 4;
					}
					if (s > 3.){
						vDS[0] = -t_ / 4. * 2. * (s - 3.) - t_ / 4;
						vDS[1] = -t_ / 4. * 2. * (s - 3.) - t_ / 4;
					} 
				}
				if (Interface(p) <= 0){
					vDS[0] = -t_ / 4.;
					vDS[1] = -t_ / 4.;
				}
			}
			double	gp(double t, FVector_double& p) {
				double x = p[0], y = p[1];
				double s = x + y;
				double rt;
				double red_;
				if (Interface(p) > 0){
					if (s < 1.)
						rt = (-(s - 1.) + (s - 1.)*(s - 1.))*(2. - t)*mum + 100.;
					if (s > 3.){
						red_ = -(2./3.)*(2 - t);
						rt = (-(s - 3.) - (s - 3.)*(s - 3.))*(2. - t)*mum + 100. + red_;
					}
				}
				if (Interface(p) <= 0) 
					rt = (-1. / 3. * (s - 1.)*(s - 1.)*(s - 1.) + (s - 1.)*(s - 1.) - (s - 1.))  * (2. - t) + 100;
				rt = rt*10;
			//	rt = rt/100;
				return rt;
			}
			void	Dgp(double t, FVector_double& p, FVector_double& vDP)	{

				double x = p[0], y = p[1];
				double s = x + y;

				if (Interface(p) > 0){
					if (s < 1){
						vDP[0] = (-1. + 2.*(s - 1.))*(2. - t) *mum;
						vDP[1] = (-1. + 2.*(s - 1.))*(2. - t) *mum;
					}
					if (s > 3){
						vDP[0] = (-1. - 2.*(s - 3.))*(2. - t) *mum;
						vDP[1] = (-1. - 2.*(s - 3.))*(2. - t) *mum;
					}
				}
				if (Interface(p) <= 0){
					vDP[0] = (-(s - 1.)*(s - 1.) + 2.* (s - 1.) - 1.) *(2. - t);
					vDP[1] = (-(s - 1.)*(s - 1.) + 2.* (s - 1.) - 1.)  *(2. - t);
				}
				vDP[0] = vDP[0] * 10;
				vDP[1] = vDP[1] * 10;
			}
			void	DDgp(double t, FVector_double& p, FMatrix_double& mDP)	{
				double x = p[0], y = p[1];
				double s = x + y;

				if (Interface(p) > 0){
					if (s < 1){
						mDP[0][0] =  2.*(2. - t)*mum;
						mDP[1][1] = 2.*(2. - t)*mum;
					}
					if (s > 3){
						mDP[0][0] =  -2.*(2. - t)*mum;
						mDP[1][1] = -2.*(2. - t)*mum;
					}
				}
				if (Interface(p) <= 0){
					mDP[0][0] = (-2. * (s - 1.) + 2.) *(2. - t);
					mDP[1][1] = (-2. * (s - 1.) + 2.) *(2. - t);;
				}
				mDP[0][0] =  mDP[0][0]*10;
				mDP[1][1] =  mDP[1][1]*10;
			//	cout << mum << endl;
			}
			void	tv(double t, FVector_double& p, FVector_double& vDV) {
				double x = p[0], y = p[1];

				double sw_ = sw(t, p);
				
				double L = Interface(p);
				double K_ = K_p_(p);;
				double gp_ = gp(t, p);
				double lambda = Lamda(sw_);

				static FVector_double stv_vDP(2);
				Dgp(t, p, stv_vDP);

				vDV[0] = -lambda*stv_vDP[0] * K_;
				vDV[1] = -lambda*stv_vDP[1] * K_;
			}
			void	Dtv(double t, FVector_double& p, FMatrix_double& mDV) {

			}
			double	qt(double t, FVector_double& p) {

				double x = p[0], y = p[1];
				double e = 2.7182818284590452353602874;
				double rt;
				double L = Interface(p);
				double sw_ = sw(t, p);
				double lamda_ = Lamda(sw_);
				double lamdad_ = Lamdad(sw_);
				double K_;
				double lap_p;

				static FVector_double sqt_DL(2);
				static FMatrix_double sqt_DDP(2, 2);
				static FVector_double sqt_DP(2);
				static FVector_double sqt_DS(2);

				DInterface(p, sqt_DL);
				Dgp(t, p, sqt_DP);
				DDgp(t, p, sqt_DDP);
				Dsw(t, p, sqt_DS);

				K_ = K_p_(p);
				lap_p = sqt_DDP[0][0] + sqt_DDP[1][1];
				rt = -lap_p*K_*lamda_ - lamdad_*K_*(sqt_DS, sqt_DP);

				return rt;

			}
			double	qw(double t, FVector_double& p) {

				double x = p[0], y = p[1];
				double rt;
				double sw_ = sw(t, p);
				double f = fw(sw_);
				double df = Dfw(sw_);
				double divu = qt(t, p);
				double st;

				static FVector_double sqw_DS(2);
				static FVector_double sqw_U(2);

				Dsw(t, p, sqw_DS);
				tv(t, p, sqw_U);

				st = Dtsw(t, p);
				rt = st + df*(sqw_DS, sqw_U) + f*divu;

				return rt;

			}
			double	k_n(double s)	{
				return (1. - s)*(1. - s)*(1. - s*s);
			}

			double	k_w(double s){
				return s*s*s*s;
			}
			double	Lamda_n(double s){
				double k = k_n(s);
				return k / mu_n;
			}
			double	Lamda_w(double s){
				double k = k_w(s);
				return k / mu_w;
			}
			double	Lamda(double s){
				double t1;	double t2;
				t1 = Lamda_n(s);
				t2 = Lamda_w(s);
				return t1 + t2;

			}
			double	Lamdad(double s){
				double t1;	double t2;
				t1 = Lamdad_n(s);
				t2 = Lamdad_w(s);
				return t1 + t2;

			}
			double fw(double s){

				double lamda;
				double lamdaw;
				lamdaw = Lamda_w(s);
				lamda = Lamda(s);

				return lamdaw / lamda;
			}
			double	Dfw(double s) {

				double denom = (s*s*s*s + (1 - s)*(1 - s)*(1 - s*s))*(s*s*s*s + (1 - s)*(1 - s)*(1 - s*s));
				double numer = 4 * s*s*s*(s*s*s*s + (1 - s)*(1 - s)*(1 - s*s)) - s*s*s*s*(4 * s*s*s - 2 * (1 - s)*(1 - s*s) + (1 - s)*(1 - s)*(-2 * s));
				
				return numer / denom;

			}

			double Lamdad_n(double s){
				return (2.*(s - 1.)*(1. - s*s) + (s - 1.)*(s - 1.)*(-2.*s)) / mu_n;
			}
			double Lamdad_w(double s){
				return 4.*s*s*s / mu_w;
			}
			int	boundary_indicator_t(FVector_double& p)	{
				int ret = 1;
				// ret=1. normal. ret=0. dirichlet.
				double x = p[0];	double y = p[1];
				return ret;
			}
			int	boundary_indicator_w(FVector_double& p)	{
				int ret = 1;
				// ret=1. normal. ret=0. dirichlet.
				double x = p[0];	double y = p[1];
				return ret;
			}
			int	boundary_indicator_n(FVector_double& p)	{
				int ret = 1;
				// ret=1. normal. ret=0. dirichlet.
				double x = p[0];	double y = p[1];
				return ret;
			}
			double	flux_t(FVector_double& p){
				double x = p[0], y = p[1];
				double rt = 0;
				return rt;
			}
			double	flux_w(FVector_double& p){
				double x = p[0], y = p[1];
				double rt = 0;
				return rt;
			}
			double	K_p_(FVector_double & p) {
				double x = p[0], y = p[1];
				double rt = 0;

				if (Interface(p) < 0) {
					rt = mum;
				}
				if (Interface(p) > 0){
					rt = mup;
				}
				return rt;

			}
			double	Initial_Val(FVector_double & p) {
				double rt = sw(0, p);
				return rt;
			}

			double	dirichlet_t(FVector_double& p) {
				double x = p[0], y = p[1];
				double rt = 0;
				return rt;
			}
			double	dirichlet_w(FVector_double& p) {
				double x = p[0], y = p[1];
				double rt = 0;
				return rt;
			}
			double	dirichlet_n(FVector_double& p) {
				double x = p[0], y = p[1];
				double rt = 0;
				return rt;
			}

		};
		class Interface_Smooth_Sol_Line_Interface_Sw_Regular : public FEM_PROBLEM {
		public:
			// Exact Solution.
			// Line Interface
			void		initialize(FEM_VARIABLES::ENTIRE& __) {
				cout << " Line Interface Line Interface sdifojsdifj " << endl;
				K_p = pow(10., 0.);	mu_w = 1.;	mu_n = 1.;	phi = 1.;
				__.dim = 2;
				__.RX.make(__.dim, __.dim).setAll(0., 0., CV.PI / 2., CV.PI / 2.);
				RX = __.RX;
				nInterface = 1;
				nFunction = 101;
				r0 = 0.2911;
				mum = pow(10., -3.);
				//	mum = pow(10., 0.);
				mup = pow(10., 0.);
				cl = 1.;
				cr = 3.;
			}
			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				double t = x + y;
				double r = (t - 1.)*(t - 3.);
				return r;
			}

			void	DInterface(FVector_double& p, FVector_double& vDI) {
				double x = p[0], y = p[1];
				double t = x + y;
				vDI[0] = 2.*(t - 2.);
				vDI[1] = 2.*(t - 2.);

			}
			void	DDInterface(FVector_double& p, FMatrix_double& mDDI)	{
				double x = p[0], y = p[1];
				mDDI[0][0] = 2.;
				mDDI[1][1] = 2.;
			}

			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);
				return 0;
			}
			double	coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.
				if (Interface(p) < 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}
			double	sw(double t, FVector_double& p) {
				double x = p[0], y = p[1];
				double s = x + y;
				double rt;
				rt = (1. / 8. * (8. - s) - 1. / 20. *s*s)*(0.5 + 0.5*t);
				return rt;

			}
			double 	Dtsw(double t, FVector_double& p) {
				double x = p[0], y = p[1];
				double s = x + y;
				double rt;
				rt = (1. / 8. * (8. - s) - 1. / 20. *s*s)*0.5;

				return rt;
			}
			void	Dsw(double t, FVector_double& p, FVector_double & vDS) {
				double x = p[0], y = p[1];
				double s = x + y;
				vDS[0] = (-1. / 8. - 1. / 10. *s)*(0.5 + 0.5*t);
				vDS[1] = (-1. / 8. - 1. / 10. *s)*(0.5 + 0.5*t);
			}
			double	gp(double t, FVector_double& p) {
				double x = p[0], y = p[1];
				double s = x + y;
				double rt;
				double red_;
				if (Interface(p) > 0){
					if (s < 1.)
						rt = (-(s - 1.) + (s - 1.)*(s - 1.))*(2. - t)*mum + 1.;
					if (s > 3.){
						red_ = -(2. / 3.)*(2 - t);
						rt = (-(s - 3.) - (s - 3.)*(s - 3.))*(2. - t)*mum + 1. + red_;
					}
				}
				if (Interface(p) <= 0)
					rt = (-1. / 3. * (s - 1.)*(s - 1.)*(s - 1.) + (s - 1.)*(s - 1.) - (s - 1.))  * (2. - t) + 1.;
			//	rt = rt ;
				//	rt = rt/100;
				return rt;
			}
			void	Dgp(double t, FVector_double& p, FVector_double& vDP)	{

				double x = p[0], y = p[1];
				double s = x + y;

				if (Interface(p) > 0){
					if (s < 1){
						vDP[0] = (-1. + 2.*(s - 1.))*(2. - t) *mum;
						vDP[1] = (-1. + 2.*(s - 1.))*(2. - t) *mum;
					}
					if (s > 3){
						vDP[0] = (-1. - 2.*(s - 3.))*(2. - t) *mum;
						vDP[1] = (-1. - 2.*(s - 3.))*(2. - t) *mum;
					}
				}
				if (Interface(p) <= 0){
					vDP[0] = (-(s - 1.)*(s - 1.) + 2.* (s - 1.) - 1.) *(2. - t);
					vDP[1] = (-(s - 1.)*(s - 1.) + 2.* (s - 1.) - 1.)  *(2. - t);
				}
			//	vDP[0] = vDP[0] * 100;
			//	vDP[1] = vDP[1] * 100;
			}
			void	DDgp(double t, FVector_double& p, FMatrix_double& mDP)	{
				double x = p[0], y = p[1];
				double s = x + y;

				if (Interface(p) > 0){
					if (s < 1){
						mDP[0][0] = 2.*(2. - t)*mum;
						mDP[1][1] = 2.*(2. - t)*mum;
					}
					if (s > 3){
						mDP[0][0] = -2.*(2. - t)*mum;
						mDP[1][1] = -2.*(2. - t)*mum;
					}
				}
				if (Interface(p) <= 0){
					mDP[0][0] = (-2. * (s - 1.) + 2.) *(2. - t);
					mDP[1][1] = (-2. * (s - 1.) + 2.) *(2. - t);;
				}
			//	mDP[0][0] = mDP[0][0] * 100;
			//	mDP[1][1] = mDP[1][1] * 100;
				//	cout << mum << endl;
			}
			void	tv(double t, FVector_double& p, FVector_double& vDV) {
				double x = p[0], y = p[1];

				double sw_ = sw(t, p);

				double L = Interface(p);
				double K_ = K_p_(p);;
				double gp_ = gp(t, p);
				double lambda = Lamda(sw_);

				static FVector_double stv_vDP(2);
				Dgp(t, p, stv_vDP);

				vDV[0] = -lambda*stv_vDP[0] * K_;
				vDV[1] = -lambda*stv_vDP[1] * K_;
			}
			void	Dtv(double t, FVector_double& p, FMatrix_double& mDV) {

			}
			double	qt(double t, FVector_double& p) {

				double x = p[0], y = p[1];
				double e = 2.7182818284590452353602874;
				double rt;
				double L = Interface(p);
				double sw_ = sw(t, p);
				double lamda_ = Lamda(sw_);
				double lamdad_ = Lamdad(sw_);
				double K_;
				double lap_p;

				static FVector_double sqt_DL(2);
				static FMatrix_double sqt_DDP(2, 2);
				static FVector_double sqt_DP(2);
				static FVector_double sqt_DS(2);

				DInterface(p, sqt_DL);
				Dgp(t, p, sqt_DP);
				DDgp(t, p, sqt_DDP);
				Dsw(t, p, sqt_DS);

				K_ = K_p_(p);
				lap_p = sqt_DDP[0][0] + sqt_DDP[1][1];
				rt = -lap_p*K_*lamda_ - lamdad_*K_*(sqt_DS, sqt_DP);

				return rt;

			}
			double	qw(double t, FVector_double& p) {

				double x = p[0], y = p[1];
				double rt;
				double sw_ = sw(t, p);
				double f = fw(sw_);
				double df = Dfw(sw_);
				double divu = qt(t, p);
				double st;

				static FVector_double sqw_DS(2);
				static FVector_double sqw_U(2);

				Dsw(t, p, sqw_DS);
				tv(t, p, sqw_U);

				st = Dtsw(t, p);
				rt = st + df*(sqw_DS, sqw_U) + f*divu;

				return rt;

			}
			double	k_n(double s)	{
				return (1. - s)*(1. - s)*(1. - s*s);
			}

			double	k_w(double s){
				return s*s*s*s;
			}
			double	Lamda_n(double s){
				double k = k_n(s);
				return k / mu_n;
			}
			double	Lamda_w(double s){
				double k = k_w(s);
				return k / mu_w;
			}
			double	Lamda(double s){
				double t1;	double t2;
				t1 = Lamda_n(s);
				t2 = Lamda_w(s);
				return t1 + t2;

			}
			double	Lamdad(double s){
				double t1;	double t2;
				t1 = Lamdad_n(s);
				t2 = Lamdad_w(s);
				return t1 + t2;

			}
			double fw(double s){

				double lamda;
				double lamdaw;
				lamdaw = Lamda_w(s);
				lamda = Lamda(s);

				return lamdaw / lamda;
			}
			double	Dfw(double s) {

				double denom = (s*s*s*s + (1 - s)*(1 - s)*(1 - s*s))*(s*s*s*s + (1 - s)*(1 - s)*(1 - s*s));
				double numer = 4 * s*s*s*(s*s*s*s + (1 - s)*(1 - s)*(1 - s*s)) - s*s*s*s*(4 * s*s*s - 2 * (1 - s)*(1 - s*s) + (1 - s)*(1 - s)*(-2 * s));

				return numer / denom;

			}

			double Lamdad_n(double s){
				return (2.*(s - 1.)*(1. - s*s) + (s - 1.)*(s - 1.)*(-2.*s)) / mu_n;
			}
			double Lamdad_w(double s){
				return 4.*s*s*s / mu_w;
			}
			int	boundary_indicator_t(FVector_double& p)	{
				int ret = 1;
				// ret=1. normal. ret=0. dirichlet.
				double x = p[0];	double y = p[1];
				return ret;
			}
			int	boundary_indicator_w(FVector_double& p)	{
				int ret = 1;
				// ret=1. normal. ret=0. dirichlet.
				double x = p[0];	double y = p[1];
				return ret;
			}
			int	boundary_indicator_n(FVector_double& p)	{
				int ret = 1;
				// ret=1. normal. ret=0. dirichlet.
				double x = p[0];	double y = p[1];
				return ret;
			}
			double	flux_t(FVector_double& p){
				double x = p[0], y = p[1];
				double rt = 0;
				return rt;
			}
			double	flux_w(FVector_double& p){
				double x = p[0], y = p[1];
				double rt = 0;
				return rt;
			}
			double	K_p_(FVector_double & p) {
				double x = p[0], y = p[1];
				double rt = 0;

				if (Interface(p) < 0) {
					rt = mum;
				}
				if (Interface(p) > 0){
					rt = mup;
				}
				return rt;

			}
			double	Initial_Val(FVector_double & p) {
				double rt = sw(0, p);
				return rt;
			}

			double	dirichlet_t(FVector_double& p) {
				double x = p[0], y = p[1];
				double rt = 0;
				return rt;
			}
			double	dirichlet_w(FVector_double& p) {
				double x = p[0], y = p[1];
				double rt = 0;
				return rt;
			}
			double	dirichlet_n(FVector_double& p) {
				double x = p[0], y = p[1];
				double rt = 0;
				return rt;
			}
		};
		class Interface_Smooth_Sol_Line_Interface_Sw_Regular_new : public FEM_PROBLEM {
		public:
			// Exact Solution.
			// Line Interface
			void		initialize(FEM_VARIABLES::ENTIRE& __) {
				cout << " Line Interface Line Interface sdifojsdifj " << endl;
				K_p = pow(10., 0.);	mu_w = 1.;	mu_n = 1.;	phi = 1.;
				__.dim = 2;
				__.RX.make(__.dim, __.dim).setAll(0., 0., CV.PI / 2., CV.PI / 2.);
				RX = __.RX;
				nInterface = 1;
				nFunction = 101;
				r0 = 0.2911;
				mum = pow(10., -3.);
				//	mum = pow(10., 0.);
				mup = pow(10., 0.);
				cl = 1.;
				cr = 3.;
			}
			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				double t = x + y;
				double r = (t - 1.)*(t - 2.);
				return r;
			}

			void	DInterface(FVector_double& p, FVector_double& vDI) {
				double x = p[0], y = p[1];
				double t = x + y;
				vDI[0] = 2.*(t - 1.5);
				vDI[1] = 2.*(t - 1.5);

			}
			void	DDInterface(FVector_double& p, FMatrix_double& mDDI)	{
				double x = p[0], y = p[1];
				mDDI[0][0] = 2.;
				mDDI[1][1] = 2.;
			}

			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);
				return 0;
			}
			double	coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.
				if (Interface(p) < 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}
			double	sw(double t, FVector_double& p) {
				double x = p[0], y = p[1];
				double s = x + y;
				double rt;
				rt = (1. / 8. * (8. - s) - 1. / 20. *s*s)*(0.5 + 0.5*t);
				return rt;

			}
			double 	Dtsw(double t, FVector_double& p) {
				double x = p[0], y = p[1];
				double s = x + y;
				double rt;
				rt = (1. / 8. * (8. - s) - 1. / 20. *s*s)*0.5;

				return rt;
			}
			void	Dsw(double t, FVector_double& p, FVector_double & vDS) {
				double x = p[0], y = p[1];
				double s = x + y;
				vDS[0] = (-1. / 8. - 1. / 10. *s)*(0.5 + 0.5*t);
				vDS[1] = (-1. / 8. - 1. / 10. *s)*(0.5 + 0.5*t);
			}
			double	gp(double t, FVector_double& p) {
				double x = p[0], y = p[1];
				double s = x + y;
				double rt;
				double red_;
				if (Interface(p) > 0){
					if (s < 1.)
						rt = (-(s - 1.) + (s - 1.)*(s - 1.))*(2. - t)*mum + 1.;
					if (s > 2.){
						red_ = -(5. / 6.)*(2 - t);
						rt = (-(s - 2.) - (s - 2.)*(s - 2.))*(2. - t)*mum + 1. + red_;
					}
				}
				if (Interface(p) <= 0)
					rt = (-1. / 3. * (s - 1.)*(s - 1.)*(s - 1.) + 0.5*(s - 1.)*(s - 1.) - (s - 1.))  * (2. - t) + 1.;
				//	rt = rt ;
				//	rt = rt/100;
				return rt;
			}
			void	Dgp(double t, FVector_double& p, FVector_double& vDP)	{

				double x = p[0], y = p[1];
				double s = x + y;

				if (Interface(p) > 0){
					if (s < 1){
						vDP[0] = (-1. + 2.*(s - 1.))*(2. - t) *mum;
						vDP[1] = (-1. + 2.*(s - 1.))*(2. - t) *mum;
					}
					if (s > 2){
						vDP[0] = (-1. - 2.*(s - 2.))*(2. - t) *mum;
						vDP[1] = (-1. - 2.*(s - 2.))*(2. - t) *mum;
					}
				}
				if (Interface(p) <= 0){
					vDP[0] = (-(s - 1.)*(s - 1.) + (s - 1.) - 1.) *(2. - t);
					vDP[1] = (-(s - 1.)*(s - 1.) + (s - 1.) - 1.)  *(2. - t);
				}
				//	vDP[0] = vDP[0] * 100;
				//	vDP[1] = vDP[1] * 100;
			}
			void	DDgp(double t, FVector_double& p, FMatrix_double& mDP)	{
				double x = p[0], y = p[1];
				double s = x + y;

				if (Interface(p) > 0){
					if (s < 1){
						mDP[0][0] = 2.*(2. - t)*mum;
						mDP[1][1] = 2.*(2. - t)*mum;
					}
					if (s > 2){
						mDP[0][0] = -2.*(2. - t)*mum;
						mDP[1][1] = -2.*(2. - t)*mum;
					}
				}
				if (Interface(p) <= 0){
					mDP[0][0] = (-2. * (s - 1.) + 1.) *(2. - t);
					mDP[1][1] = (-2. * (s - 1.) + 1.) *(2. - t);;
				}
				//	mDP[0][0] = mDP[0][0] * 100;
				//	mDP[1][1] = mDP[1][1] * 100;
				//	cout << mum << endl;
			}
			void	tv(double t, FVector_double& p, FVector_double& vDV) {
				double x = p[0], y = p[1];

				double sw_ = sw(t, p);

				double L = Interface(p);
				double K_ = K_p_(p);;
				double gp_ = gp(t, p);
				double lambda = Lamda(sw_);

				static FVector_double stv_vDP(2);
				Dgp(t, p, stv_vDP);

				vDV[0] = -lambda*stv_vDP[0] * K_;
				vDV[1] = -lambda*stv_vDP[1] * K_;
			}
			void	Dtv(double t, FVector_double& p, FMatrix_double& mDV) {

			}
			double	qt(double t, FVector_double& p) {

				double x = p[0], y = p[1];
				double e = 2.7182818284590452353602874;
				double rt;
				double L = Interface(p);
				double sw_ = sw(t, p);
				double lamda_ = Lamda(sw_);
				double lamdad_ = Lamdad(sw_);
				double K_;
				double lap_p;

				static FVector_double sqt_DL(2);
				static FMatrix_double sqt_DDP(2, 2);
				static FVector_double sqt_DP(2);
				static FVector_double sqt_DS(2);

				DInterface(p, sqt_DL);
				Dgp(t, p, sqt_DP);
				DDgp(t, p, sqt_DDP);
				Dsw(t, p, sqt_DS);

				K_ = K_p_(p);
				lap_p = sqt_DDP[0][0] + sqt_DDP[1][1];
				rt = -lap_p*K_*lamda_ - lamdad_*K_*(sqt_DS, sqt_DP);

				return rt;

			}
			double	qw(double t, FVector_double& p) {

				double x = p[0], y = p[1];
				double rt;
				double sw_ = sw(t, p);
				double f = fw(sw_);
				double df = Dfw(sw_);
				double divu = qt(t, p);
				double st;

				static FVector_double sqw_DS(2);
				static FVector_double sqw_U(2);

				Dsw(t, p, sqw_DS);
				tv(t, p, sqw_U);

				st = Dtsw(t, p);
				rt = st + df*(sqw_DS, sqw_U) + f*divu;

				return rt;

			}
			double	k_n(double s)	{
				return (1. - s)*(1. - s)*(1. - s*s);
			}

			double	k_w(double s){
				return s*s*s*s;
			}
			double	Lamda_n(double s){
				double k = k_n(s);
				return k / mu_n;
			}
			double	Lamda_w(double s){
				double k = k_w(s);
				return k / mu_w;
			}
			double	Lamda(double s){
				double t1;	double t2;
				t1 = Lamda_n(s);
				t2 = Lamda_w(s);
				return t1 + t2;

			}
			double	Lamdad(double s){
				double t1;	double t2;
				t1 = Lamdad_n(s);
				t2 = Lamdad_w(s);
				return t1 + t2;

			}
			double fw(double s){

				double lamda;
				double lamdaw;
				lamdaw = Lamda_w(s);
				lamda = Lamda(s);

				return lamdaw / lamda;
			}
			double	Dfw(double s) {

				double denom = (s*s*s*s + (1 - s)*(1 - s)*(1 - s*s))*(s*s*s*s + (1 - s)*(1 - s)*(1 - s*s));
				double numer = 4 * s*s*s*(s*s*s*s + (1 - s)*(1 - s)*(1 - s*s)) - s*s*s*s*(4 * s*s*s - 2 * (1 - s)*(1 - s*s) + (1 - s)*(1 - s)*(-2 * s));

				return numer / denom;

			}

			double Lamdad_n(double s){
				return (2.*(s - 1.)*(1. - s*s) + (s - 1.)*(s - 1.)*(-2.*s)) / mu_n;
			}
			double Lamdad_w(double s){
				return 4.*s*s*s / mu_w;
			}
			int	boundary_indicator_t(FVector_double& p)	{
				int ret = 1;
				// ret=1. normal. ret=0. dirichlet.
				double x = p[0];	double y = p[1];
				return ret;
			}
			int	boundary_indicator_w(FVector_double& p)	{
				int ret = 1;
				// ret=1. normal. ret=0. dirichlet.
				double x = p[0];	double y = p[1];
				return ret;
			}
			int	boundary_indicator_n(FVector_double& p)	{
				int ret = 1;
				// ret=1. normal. ret=0. dirichlet.
				double x = p[0];	double y = p[1];
				return ret;
			}
			double	flux_t(FVector_double& p){
				double x = p[0], y = p[1];
				double rt = 0;
				return rt;
			}
			double	flux_w(FVector_double& p){
				double x = p[0], y = p[1];
				double rt = 0;
				return rt;
			}
			double	K_p_(FVector_double & p) {
				double x = p[0], y = p[1];
				double rt = 0;

				if (Interface(p) < 0) {
					rt = mum;
				}
				if (Interface(p) > 0){
					rt = mup;
				}
				return rt;

			}
			double	Initial_Val(FVector_double & p) {
				double rt = sw(0, p);
				return rt;
			}

			double	dirichlet_t(FVector_double& p) {
				double x = p[0], y = p[1];
				double rt = 0;
				return rt;
			}
			double	dirichlet_w(FVector_double& p) {
				double x = p[0], y = p[1];
				double rt = 0;
				return rt;
			}
			double	dirichlet_n(FVector_double& p) {
				double x = p[0], y = p[1];
				double rt = 0;
				return rt;
			}
		};
		class Interface_Smooth_Sol_Line_Interface_Cap_Press_Example5_3 : public FEM_PROBLEM {
		public:
			// Exact Solution.
			// Line Interface
			void		initialize(FEM_VARIABLES::ENTIRE& __) {
				cout << " Line Interface Line Interface sdifojsdifj " << endl;
				K_p;	mu_w = 1.;	mu_n = 1.;	phi = 1.;
				__.dim = 2;
				__.RX.make(__.dim, __.dim).setAll(0., 0., CV.PI / 2., CV.PI / 2.);
				mum = pow(10., -3.);
				mup = pow(10., -1.);
				pd = 0.1;
			}
			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				double t = x + y;
				double r = (2. - t);
				return r;
			}

			void	DInterface(FVector_double& p, FVector_double& vDI) {
				double x = p[0], y = p[1];
				double t = x + y;
				vDI[0] =-1.;
				vDI[1] =-1.;

			}
			void	DDInterface(FVector_double& p, FMatrix_double& mDDI)	{
				double x = p[0], y = p[1];
				mDDI[0][0] = 0.;
				mDDI[1][1] = 0.;
			}

			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);
				return 0;
			}
			double	coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.
				if (Interface(p) < 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}
			
			double	sw(double t, FVector_double& p) {
				double x = p[0], y = p[1];
				double s = x + y;
				double L = Interface(p);
				double rt;
				if (L > 0){
					rt = (1 - 2*s*mum)*(0.9 - 0.2*t);
				}
				if (L <= 0){
					rt = (1 - 4 * mum - 2*(s - 2)*mup) * (0.9 - 0.2*t);
				}
			
				return rt;
			}
			double 	Dtsw(double t, FVector_double& p) {
				double x = p[0], y = p[1];
				double s = x + y;
				double L = Interface(p);
				double rt;
				if (L > 0){
					rt = -0.2*(1 - 2*s*mum);
				}
				if (L <= 0){
					rt = -0.2*(1 - 4 * mum - 2*(s - 2)*mup);
				}
				return rt;
			}
			void	Dsw(double t, FVector_double& p, FVector_double & vDS) {
				double x = p[0], y = p[1];
				double s = x + y;
				double L = Interface(p);
				if (L > 0){
					vDS[0] = -2*mum*(0.9 - 0.2*t);
					vDS[1] = -2 * mum*(0.9 - 0.2*t);
				}
				if (L <= 0){
					vDS[0] = -2 * mup*(0.9 - 0.2*t);
					vDS[1] = -2 * mup*(0.9 - 0.2*t);
				}
			//	vDS.clear();
			}
			void	DDsw(double t, FVector_double& p, FMatrix_double & DDS) {
				double x = p[0], y = p[1];
				double s = x + y;
				double L = Interface(p);
				DDS.clear();
			}

			double	gp(double t, FVector_double& p) {
				double x = p[0], y = p[1];
				double s = x + y;
				double rt;
				double L = Interface(p);
				double e = 2.7182818284590452353602874;
				double K__ = K_p_(p);
				
				if (L > 0){
					rt = -L*cos(s) *(2 - t)*mum + 10;
				}
				if (L <= 0){
					rt = -L*cos(s) *(2 - t)*mup + 10;
				}
				return 10*rt;
			}
			void	Dgp(double t, FVector_double& p, FVector_double& vDP)	{

				double x = p[0], y = p[1];
				double s = x + y;
				double L = Interface(p);

				if (L > 0){
					vDP[0] = cos(s)*(2 - t)*mum + L*sin(s)*(2 - t)*mum;
					vDP[1] = cos(s)*(2 - t)*mum + L*sin(s)*(2 - t)*mum;
				}
				if (L <= 0){
					vDP[0] = cos(s)*(2 - t)*mup + L*sin(s)*(2 - t)*mup;
					vDP[1] = cos(s)*(2 - t)*mup + L*sin(s)*(2 - t)*mup;
				}
				vDP[0] = vDP[0] * 10;
				vDP[1] = vDP[1] * 10;
			}
			void	DDgp(double t, FVector_double& p, FMatrix_double& mDP)	{
				double x = p[0], y = p[1];
				double s = x + y;
				double L = Interface(p);
				mDP.clear();
				if (L > 0){
					mDP[0][0] = -sin(s)*(2 - t)*mum - sin(s)*(2 - t)*mum + L*cos(s)*(2-t)*mum;
					mDP[1][1] = -sin(s)*(2 - t)*mum - sin(s)*(2 - t)*mum + L*cos(s)*(2 - t)*mum;
				}
				if (L <= 0){
					mDP[0][0] = -sin(s)*(2 - t)*mup - sin(s)*(2 - t)*mup + L*cos(s)*(2 - t)*mup;
					mDP[1][1] = -sin(s)*(2 - t)*mup - sin(s)*(2 - t)*mup + L*cos(s)*(2 - t)*mup;
				}
				mDP[0][0] = mDP[0][0] * 10;
				mDP[1][1] = mDP[1][1] * 10;
			}
			void	tv(double t, FVector_double& p, FVector_double& vDV) {
				double x = p[0], y = p[1];

				double sw_ = sw(t, p);

				double L = Interface(p);
				double K_ = K_p_(p);;
				double gp_ = gp(t, p);
				double lambda = Lamda(sw_);

				static FVector_double stv_vDP(2);
				Dgp(t, p, stv_vDP);

				vDV[0] = -lambda*stv_vDP[0] * K_;
				vDV[1] = -lambda*stv_vDP[1] * K_;
			}
			void	Dtv(double t, FVector_double& p, FMatrix_double& mDV) {

			}
			double	qt(double t, FVector_double& p) {

				double x = p[0], y = p[1];
				double e = 2.7182818284590452353602874;
				double rt;
				double L = Interface(p);
				double sw_ = sw(t, p);
				double lamda_ = Lamda(sw_);
				double lamdad_ = Lamdad(sw_);
				double K_;
				double lap_p;

				static FVector_double sqt_DL(2);
				static FMatrix_double sqt_DDP(2, 2);
				static FVector_double sqt_DP(2);
				static FVector_double sqt_DS(2);

				DInterface(p, sqt_DL);
				Dgp(t, p, sqt_DP);
				DDgp(t, p, sqt_DDP);
				Dsw(t, p, sqt_DS);

				K_ = K_p_(p);
				lap_p = sqt_DDP[0][0] + sqt_DDP[1][1];
				rt = -lap_p*K_*lamda_ - lamdad_*K_*(sqt_DS, sqt_DP);

				return rt;

			}
			double	qw(double t, FVector_double& p) {

				double x = p[0], y = p[1];
				double rt;
				double sw_ = sw(t, p);
				double f = fw(sw_);
				double df = Dfw(sw_);
				double divu = qt(t, p);
				double st;
				double gamma = _problem->gamma(sw_);
				double dgamma = _problem->dgamma(sw_);
				double K_ = K_p_(p);

				static FVector_double sqw_DS(2);
				static FVector_double sqw_U(2);
				static FMatrix_double sqw_DDS(2, 2);

				Dsw(t, p, sqw_DS);
				tv(t, p, sqw_U);
				DDsw(t, p, sqw_DDS);

				double divs = sqw_DDS[0][0] + sqw_DDS[1][1];
				//	cout << gamma << endl;
				st = Dtsw(t, p);
				rt = st + df*(sqw_DS, sqw_U) + f*divu + dgamma*(sqw_DS, sqw_DS)*K_ + gamma*divs*K_;

				return rt;
				
			}

			double	k_n(double s)	{
				return (1. - s)*(1. - s)*(1. - s*s);
			}

			double	k_w(double s){
				return s*s*s*s;
			}
			double	Lamda_n(double s){
				double k = k_n(s);
				return k / mu_n;
			}
			double	Lamda_w(double s){
				double k = k_w(s);
				return k / mu_w;
			}
			double	Lamda(double s){
				double t1;	double t2;
				t1 = Lamda_n(s);
				t2 = Lamda_w(s);
				return t1 + t2;

			}
			double	Lamdad(double s){
				double t1;	double t2;
				t1 = Lamdad_n(s);
				t2 = Lamdad_w(s);
				return t1 + t2;

			}
			double fw(double s){

				double lamda;
				double lamdaw;
				lamdaw = Lamda_w(s);
				lamda = Lamda(s);

				return lamdaw / lamda;
			}
			double fn(double s){

				double lamda;
				double lamdan;
				lamdan = Lamda_n(s);
				lamda = Lamda(s);

				return lamdan / lamda;
			}
			double	Dfw(double s) {

				double denom = (s*s*s*s + (1 - s)*(1 - s)*(1 - s*s))*(s*s*s*s + (1 - s)*(1 - s)*(1 - s*s));
				double numer = 4 * s*s*s*(s*s*s*s + (1 - s)*(1 - s)*(1 - s*s)) - s*s*s*s*(4 * s*s*s - 2 * (1 - s)*(1 - s*s) + (1 - s)*(1 - s)*(-2 * s));

				return numer / denom;

			}

			double	gamma(double s) {
				if (s > 0){
					double kw = s*s*s*s;
					double kn = (1. - s)*(1. - s)*(1. - s*s);
					double dpc_ = -0.5*pow(s, -1.5);
					double rt = kw*kn / (kw + kn)*dpc_;
					
				//	rt = 0.;
					return pd*rt;
				//	return 0.;
				}
				else{
					return 0.;
				}

			}
			double	dpc(double s) {
				if (s > 0){
					return -pd*0.5*pow(s, -1.5);
				//	return 0.;
				}
				else{
					cout << "S = zero " << endl;
					return -10000000.;
				}

			}
			double	dgamma(double s) {
				if (s > 0){
					double kw = s*s*s*s;
					double kn = (1. - s)*(1. - s)*(1. - s*s);
					double dpc_ = -0.5*pow(s, -1.5);

					double dkw = 4 * s*s*s;
					double dkn = 2 * (s - 1)*(1. - s*s) + (1. - s)*(1. - s)*(-2 * s);
					double ddpc_ = 1.5*0.5*pow(s, -2.5);

					double rt = ((dkw*kn + kw*dkn)*(kw + kn) - kw*kn*(dkw + dkn)) / (kw + kn) / (kw + kn)*dpc_ + kw*kn / (kw + kn)*ddpc_;
					
				//	rt = 0.;
					return pd*rt;
				//	return 0;
				}
				else {
					return 0.;
				}
			}

			double Lamdad_n(double s){
				return (2.*(s - 1.)*(1. - s*s) + (s - 1.)*(s - 1.)*(-2.*s)) / mu_n;
			}
			double Lamdad_w(double s){
				return 4.*s*s*s / mu_w;
			}
			int	boundary_indicator_t(FVector_double& p)	{
				int ret = 1;
				// ret=1. normal. ret=0. dirichlet.
				double x = p[0];	double y = p[1];
				return ret;
			}
			int	boundary_indicator_w(FVector_double& p)	{
				int ret = 1;
				// ret=1. normal. ret=0. dirichlet.
				double x = p[0];	double y = p[1];
				return ret;
			}
			int	boundary_indicator_n(FVector_double& p)	{
				int ret = 1;
				// ret=1. normal. ret=0. dirichlet.
				double x = p[0];	double y = p[1];
				return ret;
			}
			double	flux_t(FVector_double& p){
				double x = p[0], y = p[1];
				double rt = 0;
				return rt;
			}
			double	flux_w(FVector_double& p){
				double x = p[0], y = p[1];
				double rt = 0;
				return rt;
			}
			double	K_p_(FVector_double & p) {
				double x = p[0], y = p[1];
				double rt = 0;

				if (Interface(p) < 0) {
					rt = mum;
				}
				if (Interface(p) > 0){
					rt = mup;
				}
				return rt;

			}
			double	Initial_Val(FVector_double & p) {
				double rt = sw(0, p);
				return rt;
			}

			double	dirichlet_t(FVector_double& p) {
				double x = p[0], y = p[1];
				double rt = 0;
				return rt;
			}
			double	dirichlet_w(FVector_double& p) {
				double x = p[0], y = p[1];
				double rt = 0;
				return rt;
			}
			double	dirichlet_n(FVector_double& p) {
				double x = p[0], y = p[1];
				double rt = 0;
				return rt;
			}

		};
		class Interface_Smooth_Sol_Line_Interface_Cap_Press_Example5_3_S_w_Polynomial_Second_Order : public FEM_PROBLEM {
		public:
			// Exact Solution.
			// Line Interface
			void		initialize(FEM_VARIABLES::ENTIRE& __) {
				cout << "Nonzero Cap Pressure. S second order in polynomial " << endl;
				K_p;	mu_w = 1.;	mu_n = 1.;	phi = 1.;
				__.dim = 2;
				__.RX.make(__.dim, __.dim).setAll(0., 0., CV.PI / 2., CV.PI / 2.);
				RX = __.RX;
				mum = pow(10., -3.);
				mup = pow(10., -1.); 

				mum = 0.008;
				mup = 0.02;

				pd = 1.;
			}
			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				double t = x + y;
				double r = (2. - t);
				return r;
			}

			void	DInterface(FVector_double& p, FVector_double& vDI) {
				double x = p[0], y = p[1];
				double t = x + y;
				vDI[0] = -1.;
				vDI[1] = -1.;

			}
			void	DDInterface(FVector_double& p, FMatrix_double& mDDI)	{
				double x = p[0], y = p[1];
				mDDI[0][0] = 0.;
				mDDI[1][1] = 0.;
			}

			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);
				return 0;
			}
			double	coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.
				if (Interface(p) < 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}

			double	sw(double t, FVector_double& p) {
				double x = p[0], y = p[1];
				double s = x + y;
				double L = Interface(p);
				double rt;
				if (L > 0){
					rt = (1 - 4 * (s + 0.25*(s - 2)*(s - 2))*mum)*(1 - 0.5*t);
				}
				if (L <= 0){
					rt = (1 - 8 * mum - 4 * ((s - 2) + 0.25*(s - 2)*(s - 2))*mup) * (1 - 0.5*t);
				}
				//	rt = 0;

				return rt;
			}
			double 	Dtsw(double t, FVector_double& p) {
				double x = p[0], y = p[1];
				double s = x + y;
				double L = Interface(p);
				double rt;
				if (L > 0){
					rt = -0.5*(1 - 4 * (s + 0.25*(s - 2)*(s - 2))*mum);
				}
				if (L <= 0){
					rt = -0.5*(1 - 8 * mum - 4 * ((s - 2) + 0.25*(s - 2)*(s - 2))*mup);
				}
				//	rt = 0.;
				return rt;
			}
			void	Dsw(double t, FVector_double& p, FVector_double & vDS) {
				double x = p[0], y = p[1];
				double s = x + y;
				double L = Interface(p);
				if (L > 0){
					vDS[0] = -4 * (1. + 0.5*(s - 2))*mum*(1 - 0.5*t);
					vDS[1] = -4 * (1. + 0.5*(s - 2))*mum*(1 - 0.5*t);
				}
				if (L <= 0){
					vDS[0] = -4 * (1. + 0.5*(s - 2))*mup*(1 - 0.5*t);
					vDS[1] = -4 * (1. + 0.5*(s - 2))*mup*(1 - 0.5*t);
				}
				//	vDS.clear();
			}
			void	DDsw(double t, FVector_double& p, FMatrix_double & DDS) {
				double x = p[0], y = p[1];
				double s = x + y;
				double L = Interface(p);
				if (L > 0){
					DDS[0][0] = -4 * (0.5)*mum*(1 - 0.5*t);;
					DDS[1][1] = -4 * (0.5)*mum*(1 - 0.5*t);;
				}
				if (L <= 0){
					DDS[0][0] = -4 * (0.5)*mup*(1 - 0.5*t);;
					DDS[1][1] = -4 * (0.5)*mup*(1 - 0.5*t);;
				}
			}
			/*
			double	gp(double t, FVector_double& p) {
				double x = p[0], y = p[1];
				double s = x + y;
				double rt;
				double L = Interface(p);
				double e = 2.7182818284590452353602874;
				double K__ = K_p_(p);

				if (L > 0){
					rt =  (-3 * s + (s - 2)*(s - 2))*(2 - t)*mum + 100;
				}
				if (L <= 0){
					rt = -6* mum*(2 - t) + (-3 * (s - 2) + (s - 2)*(s - 2))*(2 - t)*mup + 100;
				}
				rt = 10 * rt;
				return rt;
			}
			void	Dgp(double t, FVector_double& p, FVector_double& vDP)	{

				double x = p[0], y = p[1];
				double s = x + y;
				double L = Interface(p);

				if (L > 0){
					vDP[0] = (-3 + 2 * (s - 2))*(2 - t)*mum;
					vDP[1] = (-3 + 2 * (s - 2))*(2 - t)*mum;
				}
				if (L <= 0){
					vDP[0] = (-3 + 2 * (s - 2))*(2 - t)*mup;
					vDP[1] = (-3 + 2 * (s - 2))*(2 - t)*mup;
				}
					vDP[0] = 10 * vDP[0];
					vDP[1] = 10 * vDP[1];
			}
			void	DDgp(double t, FVector_double& p, FMatrix_double& mDP)	{
				double x = p[0], y = p[1];
				double s = x + y;
				double L = Interface(p);

				if (L > 0){
					mDP[0][0] = 2 * (2 - t)*mum;
					mDP[1][1] = 2 * (2 - t)*mum;
				}
				if (L <= 0){
					mDP[0][0] = 2 * (2 - t)*mup;
					mDP[1][1] = 2 * (2 - t)*mup;
				}
					mDP[0][0] = mDP[0][0] * 10;
					mDP[1][1] = mDP[1][1] * 10;

			}
			*/
			
			double	gp(double t, FVector_double& p) {
				double x = p[0], y = p[1];
				double s = x + y;
				double rt;
				double L = Interface(p);
				double e = 2.7182818284590452353602874;
				double K__ = K_p_(p);

				if (L > 0){
					rt = -L*cos(s) *(2 - t)*mum + 0.1;
				}
				if (L <= 0){
					rt = -L*cos(s) *(2 - t)*mup + 0.1;
				}
				rt = 10 * rt;
				return rt;
			}
			void	Dgp(double t, FVector_double& p, FVector_double& vDP)	{

				double x = p[0], y = p[1];
				double s = x + y;
				double L = Interface(p);

				if (L > 0){
					vDP[0] = cos(s)*(2 - t)*mum + L*sin(s)*(2 - t)*mum;
					vDP[1] = cos(s)*(2 - t)*mum + L*sin(s)*(2 - t)*mum;
				}
				if (L <= 0){
					vDP[0] = cos(s)*(2 - t)*mup + L*sin(s)*(2 - t)*mup;
					vDP[1] = cos(s)*(2 - t)*mup + L*sin(s)*(2 - t)*mup;
				}
				vDP[0] = 10 * vDP[0];
				vDP[1] = 10 * vDP[1];
			}
			void	DDgp(double t, FVector_double& p, FMatrix_double& mDP)	{
				double x = p[0], y = p[1];
				double s = x + y;
				double L = Interface(p);

				if (L > 0){
					mDP[0][0] = -sin(s)*(2 - t)*mum - sin(s)*(2 - t)*mum + L*cos(s)*(2 - t)*mum;
					mDP[1][1] = -sin(s)*(2 - t)*mum - sin(s)*(2 - t)*mum + L*cos(s)*(2 - t)*mum;
				}
				if (L <= 0){
					mDP[0][0] = -sin(s)*(2 - t)*mup - sin(s)*(2 - t)*mup + L*cos(s)*(2 - t)*mup;
					mDP[1][1] = -sin(s)*(2 - t)*mup - sin(s)*(2 - t)*mup + L*cos(s)*(2 - t)*mup;
				}
				mDP[0][0] = mDP[0][0] * 10;
				mDP[1][1] = mDP[1][1] * 10;

			}
			
			void	tv(double t, FVector_double& p, FVector_double& vDV) {
				double x = p[0], y = p[1];

				double sw_ = sw(t, p);

				double L = Interface(p);
				double K_ = K_p_(p);;
				double gp_ = gp(t, p);
				double lambda = Lamda(sw_);

				static FVector_double stv_vDP(2);
				Dgp(t, p, stv_vDP);

				vDV[0] = -lambda*stv_vDP[0] * K_;
				vDV[1] = -lambda*stv_vDP[1] * K_;
			}
			void	Dtv(double t, FVector_double& p, FMatrix_double& mDV) {

			}
			double	qt(double t, FVector_double& p) {

				double x = p[0], y = p[1];
				double e = 2.7182818284590452353602874;
				double rt;
				double L = Interface(p);
				double sw_ = sw(t, p);
				double lamda_ = Lamda(sw_);
				double lamdad_ = Lamdad(sw_);
				double K_;
				double lap_p;

				static FVector_double sqt_DL(2);
				static FMatrix_double sqt_DDP(2, 2);
				static FVector_double sqt_DP(2);
				static FVector_double sqt_DS(2);

				DInterface(p, sqt_DL);
				Dgp(t, p, sqt_DP);
				DDgp(t, p, sqt_DDP);
				Dsw(t, p, sqt_DS);

				K_ = K_p_(p);
				lap_p = sqt_DDP[0][0] + sqt_DDP[1][1];
				rt = -lap_p*K_*lamda_ - lamdad_*K_*(sqt_DS, sqt_DP);

				return rt;

			}
			double	qw(double t, FVector_double& p) {

				double x = p[0], y = p[1];
				double rt;
				double sw_ = sw(t, p);
				double f = fw(sw_);
				double df = Dfw(sw_);
				double divu = qt(t, p);
				double st;
				double gamma = _problem->gamma(sw_);
				double dgamma = _problem->dgamma(sw_);
				double K_ = K_p_(p);

				static FVector_double sqw_DS(2);
				static FVector_double sqw_U(2);
				static FMatrix_double sqw_DDS(2, 2);

				Dsw(t, p, sqw_DS);
				tv(t, p, sqw_U);
				DDsw(t, p, sqw_DDS);

				double divs = sqw_DDS[0][0] + sqw_DDS[1][1];
				//	cout << gamma << endl;
				st = Dtsw(t, p);
				rt = st + df*(sqw_DS, sqw_U) + f*divu + dgamma*(sqw_DS, sqw_DS)*K_ + gamma*divs*K_;

				return rt;

			}

			double	k_n(double s)	{
				return (1. - s)*(1. - s)*(1. - s*s);
			}

			double	k_w(double s){
				return s*s*s*s;
			}
			double	Lamda_n(double s){
				double k = k_n(s);
				return k / mu_n;
			}
			double	Lamda_w(double s){
				double k = k_w(s);
				return k / mu_w;
			}
			double	Lamda(double s){
				double t1;	double t2;
				t1 = Lamda_n(s);
				t2 = Lamda_w(s);
				return t1 + t2;

			}
			double	Lamdad(double s){
				double t1;	double t2;
				t1 = Lamdad_n(s);
				t2 = Lamdad_w(s);
				return t1 + t2;

			}
			double fw(double s){

				double lamda;
				double lamdaw;
				lamdaw = Lamda_w(s);
				lamda = Lamda(s);

				return lamdaw / lamda;
			}
			double fn(double s){

				double lamda;
				double lamdan;
				lamdan = Lamda_n(s);
				lamda = Lamda(s);

				return lamdan / lamda;
			}
			double	Dfw(double s) {

				double denom = (s*s*s*s + (1 - s)*(1 - s)*(1 - s*s))*(s*s*s*s + (1 - s)*(1 - s)*(1 - s*s));
				double numer = 4 * s*s*s*(s*s*s*s + (1 - s)*(1 - s)*(1 - s*s)) - s*s*s*s*(4 * s*s*s - 2 * (1 - s)*(1 - s*s) + (1 - s)*(1 - s)*(-2 * s));

				return numer / denom;

			}

			double	gamma(double s) {
				if (s > 0){
					double kw = s*s*s*s;
					double kn = (1. - s)*(1. - s)*(1. - s*s);
					double dpc_ = -0.5*pow(s, -1.5);
					double rt = kw*kn / (kw + kn)*dpc_;

					//	rt = 0.;
					return pd*rt;
					//	return 0.;
				}
				else{
					return 0.;
				}

			}
			double	dpc(double s) {
				if (s > 0){
					return -pd*0.5*pow(s, -1.5);
					//	return 0.;
				}
				else{
					cout << "S = zero " << endl;
					return -10000000.;
				}

			}
			double	dgamma(double s) {
				if (s > 0){
					double kw = s*s*s*s;
					double kn = (1. - s)*(1. - s)*(1. - s*s);
					double dpc_ = -0.5*pow(s, -1.5);

					double dkw = 4 * s*s*s;
					double dkn = 2 * (s - 1)*(1. - s*s) + (1. - s)*(1. - s)*(-2 * s);
					double ddpc_ = 1.5*0.5*pow(s, -2.5);

					double rt = ((dkw*kn + kw*dkn)*(kw + kn) - kw*kn*(dkw + dkn)) / (kw + kn) / (kw + kn)*dpc_ + kw*kn / (kw + kn)*ddpc_;

					//	rt = 0.;
					return pd*rt;
					//	return 0;
				}
				else {
					return 0.;
				}
			}

			double Lamdad_n(double s){
				return (2.*(s - 1.)*(1. - s*s) + (s - 1.)*(s - 1.)*(-2.*s)) / mu_n;
			}
			double Lamdad_w(double s){
				return 4.*s*s*s / mu_w;
			}
			int	boundary_indicator_t(FVector_double& p)	{
				int ret = 1;
				// ret=1. normal. ret=0. dirichlet.
				double x = p[0];	double y = p[1];
				return ret;
			}
			int	boundary_indicator_w(FVector_double& p)	{
				int ret = 1;
				// ret=1. normal. ret=0. dirichlet.
				double x = p[0];	double y = p[1];
				return ret;
			}
			int	boundary_indicator_n(FVector_double& p)	{
				int ret = 1;
				// ret=1. normal. ret=0. dirichlet.
				double x = p[0];	double y = p[1];
				return ret;
			}
			double	flux_t(FVector_double& p){
				double x = p[0], y = p[1];
				double rt = 0;
				return rt;
			}
			double	flux_w(FVector_double& p){
				double x = p[0], y = p[1];
				double rt = 0;
				return rt;
			}
			double	K_p_(FVector_double & p) {
				double x = p[0], y = p[1];
				double rt = 0;

				if (Interface(p) < 0) {
					rt = mum;
				}
				if (Interface(p) > 0){
					rt = mup;
				}
				return rt;

			}
			double	Initial_Val(FVector_double & p) {
				double rt = sw(0, p);
				return rt;
			}

			double	dirichlet_t(FVector_double& p) {
				double x = p[0], y = p[1];
				double rt = 0;
				return rt;
			}
			double	dirichlet_w(FVector_double& p) {
				double x = p[0], y = p[1];
				double rt = 0;
				return rt;
			}
			double	dirichlet_n(FVector_double& p) {
				double x = p[0], y = p[1];
				double rt = 0;
				return rt;
			}

		};
		class Interface_Smooth_Sol_Line_Interface_Cap_Pre: public FEM_PROBLEM {
		public:
			// Exact Solution.
			// Line Interface
			void		initialize(FEM_VARIABLES::ENTIRE& __) {
				K_p = pow(10., 0.);	mu_w = 1.;	mu_n = 1.;	phi = 1.;
				__.dim = 2;
				__.RX.make(__.dim, __.dim).setAll(0., 0., CV.PI / 2., CV.PI / 2.);
				nInterface = 1;
				nFunction = 101;
				r0 = 0.2911;
				mum = pow(10., -3.);
				mup = pow(10., 0.);
				cl = 1.;
				cr = 3.;
			}
			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				double t = x + y;
				double r = (t - 1.)*(t - 3.);
				return r;
			}

			void	DInterface(FVector_double& p, FVector_double& vDI) {
				double x = p[0], y = p[1];
				double t = x + y;
				vDI[0] = 2.*(t - 2.);
				vDI[1] = 2.*(t - 2.);

			}
			void	DDInterface(FVector_double& p, FMatrix_double& mDDI)	{
				double x = p[0], y = p[1];
				mDDI[0][0] = 2.;
				mDDI[1][1] = 2.;
			}

			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);
				return 0;
			}
			double	coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.
				if (Interface(p) < 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}
			double	sw(double t, FVector_double& p) {
				double x = p[0], y = p[1];
				double s = x + y;
				double rt;
				double red_;
				if (Interface(p) > 0){
					if (s < 1.)
						rt = (-(s - 1.) + (s - 1.)*(s - 1.))*(2. - t) + 100.;
					if (s > 3.){
						red_ = -(2. / 3.) / mum*(2 - t);
						rt = (-(s - 3.) - (s - 3.)*(s - 3.))*(2. - t) + 100. + red_;
					}
				}
				if (Interface(p) <= 0)
					rt = (-1. / 3. * (s - 1.)*(s - 1.)*(s - 1.) + (s - 1.)*(s - 1.) - (s - 1.)) / mum * (2. - t) + 100;
				rt = rt / 2000.+0.8;

				return rt;

			}
			double 	Dtsw(double t, FVector_double& p) {
				double x = p[0], y = p[1];
				double s = x + y;
				double rt;
				double red_;
				if (Interface(p) > 0){
					if (s < 1.)
						rt = (-(s - 1.) + (s - 1.)*(s - 1.))*(-1);
					if (s > 3.){
						red_ = -(2. / 3.) / mum*( - 1);
						rt = (-(s - 3.) - (s - 3.)*(s - 3.))*(-1) + red_;
					}
				}
				if (Interface(p) <= 0)
					rt = (-1. / 3. * (s - 1.)*(s - 1.)*(s - 1.) + (s - 1.)*(s - 1.) - (s - 1.)) / mum * (-1);// +100;
				rt = rt / 2000.;

				return rt;
			}
			void	Dsw(double t, FVector_double& p, FVector_double & vDS) {
				double x = p[0], y = p[1];
				double s = x + y;

				if (Interface(p) > 0){
					if (s < cl){
						vDS[0] = (-1. + 2.*(s - 1.))*(2. - t);
						vDS[1] = (-1. + 2.*(s - 1.))*(2. - t);
					}
					if (s > cr){
						vDS[0] = (-1. - 2.*(s - 3.))*(2. - t);
						vDS[1] = (-1. - 2.*(s - 3.))*(2. - t);
					}
				}
				if (Interface(p) <= 0){
					vDS[0] = (-(s - 1.)*(s - 1.) + 2.* (s - 1.) - 1.) / mum *(2. - t);
					vDS[1] = (-(s - 1.)*(s - 1.) + 2.* (s - 1.) - 1.) / mum *(2. - t);
				}
				vDS[0] = vDS[0] / 2000.;
				vDS[1] = vDS[1] / 2000.;

			}
			void	DDsw(double t, FVector_double& p, FMatrix_double& mDS)	{
				double x = p[0], y = p[1];
				double s = x + y;

				if (Interface(p) > 0){
					if (s < cl){
						mDS[0][0] = 2.*(2. - t);
						mDS[1][1] = 2.*(2. - t);
					}
					if (s > cr){
						mDS[0][0] = -2.*(2. - t);
						mDS[1][1] = -2.*(2. - t);
					}
				}
				if (Interface(p) <= 0){
					mDS[0][0] = (-2. * (s - 1.) + 2.) / mum *(2. - t);
					mDS[1][1] = (-2. * (s - 1.) + 2.) / mum *(2. - t);;
				}
				mDS[0][0] = mDS[0][0] / 2000.;
				mDS[1][1] = mDS[1][1] / 2000.;
			}
			double	gp(double t, FVector_double& p) {
				double x = p[0], y = p[1];
				double s = x + y;
				double rt;
				double red_;
				if (Interface(p) > 0){
					if (s < 1.)
						rt = (-(s - 1.) + (s - 1.)*(s - 1.))*(2. - t) + 100.;
					if (s > 3.){
						red_ = -(2. / 3.) / mum*(2 - t);
						rt = (-(s - 3.) - (s - 3.)*(s - 3.))*(2. - t) + 100. + red_;
					}
				}
				if (Interface(p) <= 0)
					rt = (-1. / 3. * (s - 1.)*(s - 1.)*(s - 1.) + (s - 1.)*(s - 1.) - (s - 1.)) / mum * (2. - t) + 100;
				rt = rt / 100.;
				return rt;
			}
			void	Dgp(double t, FVector_double& p, FVector_double& vDP)	{

				double x = p[0], y = p[1];
				double s = x + y;

				if (Interface(p) > 0){
					if (s < cl){
						vDP[0] = (-1. + 2.*(s - 1.))*(2. - t);
						vDP[1] = (-1. + 2.*(s - 1.))*(2. - t);
					}
					if (s > cr){
						vDP[0] = (-1. - 2.*(s - 3.))*(2. - t);
						vDP[1] = (-1. - 2.*(s - 3.))*(2. - t);
					}
				}
				if (Interface(p) <= 0){
					vDP[0] = (-(s - 1.)*(s - 1.) + 2.* (s - 1.) - 1.) / mum *(2. - t);
					vDP[1] = (-(s - 1.)*(s - 1.) + 2.* (s - 1.) - 1.) / mum *(2. - t);
				}
				vDP[0] = vDP[0] / 100.;
				vDP[1] = vDP[1] / 100.;
			}
			void	DDgp(double t, FVector_double& p, FMatrix_double& mDP)	{
				double x = p[0], y = p[1];
				double s = x + y;

				if (Interface(p) > 0){
					if (s < cl){
						mDP[0][0] = 2.*(2. - t);
						mDP[1][1] = 2.*(2. - t);
					}
					if (s > cr){
						mDP[0][0] = -2.*(2. - t);
						mDP[1][1] = -2.*(2. - t);
					}
				}
				if (Interface(p) <= 0){
					mDP[0][0] = (-2. * (s - 1.) + 2.) / mum *(2. - t);
					mDP[1][1] = (-2. * (s - 1.) + 2.) / mum *(2. - t);;
				}
				mDP[0][0] = mDP[0][0] / 100.;
				mDP[1][1] = mDP[1][1] / 100.;

			}
			void	tv(double t, FVector_double& p, FVector_double& vDV) {
				double x = p[0], y = p[1];

				double sw_ = sw(t, p);
				double L = Interface(p);
				double K_ = K_p_(p);;
				double gp_ = gp(t, p);
				double lambda = Lamda(sw_);

				static FVector_double stv_vDP(2);
				Dgp(t, p, stv_vDP);

				vDV[0] = -lambda*stv_vDP[0] * K_;
				vDV[1] = -lambda*stv_vDP[1] * K_;

			}
			void	Dtv(double t, FVector_double& p, FMatrix_double& mDV) {

			}
			double	qt(double t, FVector_double& p) {

				double x = p[0], y = p[1];
				double e = 2.7182818284590452353602874;
				double rt;
				double L = Interface(p);
				double sw_ = sw(t, p);
				double lamda_ = Lamda(sw_);
				double lamdad_ = Lamdad(sw_);
				double K_;
				double lap_p;

				static FVector_double sqt_DL(2);
				static FMatrix_double sqt_DDP(2, 2);
				static FVector_double sqt_DP(2);
				static FVector_double sqt_DS(2);

				DInterface(p, sqt_DL);
				Dgp(t, p, sqt_DP);
				DDgp(t, p, sqt_DDP);
				Dsw(t, p, sqt_DS);

				K_ = K_p_(p);

				lap_p = sqt_DDP[0][0] + sqt_DDP[1][1];
				rt = -lap_p*K_*lamda_ - lamdad_*K_*(sqt_DS, sqt_DP);

				return rt;

			}
			double	qw(double t, FVector_double& p) {

				double x = p[0], y = p[1];
				double rt;
				double sw_ = sw(t, p);
				double f = fw(sw_);
				double df = Dfw(sw_);
				double divu = qt(t, p);
				double st;
				double gamma = _problem->gamma(sw_);
				double dgamma = _problem->dgamma(sw_);
				double K_ = K_p_(p);
		
				static FVector_double sqw_DS(2);
				static FVector_double sqw_U(2);
				static FMatrix_double sqw_DDS(2, 2);

				Dsw(t, p, sqw_DS);
				tv(t, p, sqw_U);
				DDsw(t, p, sqw_DDS);

				double divs = sqw_DDS[0][0] + sqw_DDS[1][1];
			//	cout << gamma << endl;
				st = Dtsw(t, p);
				rt = st + df*(sqw_DS, sqw_U) + f*divu -dgamma*(sqw_DS, sqw_DS)*K_ - gamma*divs*K_;

				return rt;

			}
			double	k_n(double s)	{
				return (1. - s)*(1. - s)*(1. - s*s);
			}

			double	k_w(double s){
				return s*s*s*s;
			}
			double	Lamda_n(double s){
				double k = k_n(s);
				return k / mu_n;
			}
			double	Lamda_w(double s){
				double k = k_w(s);
				return k / mu_w;
			}
			double	Lamda(double s){
				double t1;	double t2;
				t1 = Lamda_n(s);
				t2 = Lamda_w(s);
				return t1 + t2;

			}
			double	Lamdad(double s){
				double t1;	double t2;
				t1 = Lamdad_n(s);
				t2 = Lamdad_w(s);
				return t1 + t2;

			}
			double fw(double s){

				double lamda;
				double lamdaw;
				lamdaw = Lamda_w(s);
				lamda = Lamda(s);

				return lamdaw / lamda;
			}
			double	Dfw(double s) {

				double denom = (s*s*s*s + (1 - s)*(1 - s)*(1 - s*s))*(s*s*s*s + (1 - s)*(1 - s)*(1 - s*s));
				double numer = 4 * s*s*s*(s*s*s*s + (1 - s)*(1 - s)*(1 - s*s)) - s*s*s*s*(4 * s*s*s - 2 * (1 - s)*(1 - s*s) + (1 - s)*(1 - s)*(-2 * s));

				return numer / denom;

			}
			double	gamma(double s) {
				if (s > 0){
					double kw = s*s*s*s;
					double kn = (1. - s)*(1. - s)*(1. - s*s);
					double dpc_ = -0.5*pow(s, -1.5);
					double rt = kw*kn / (kw + kn)*dpc_;
					rt = -rt;

					return rt;
				}
				else{
					return 0.;
				}
			
			}
			double	dgamma(double s) {
				if (s > 0){
					double kw = s*s*s*s;
					double kn = (1. - s)*(1. - s)*(1. - s*s);
					double dpc_ = -0.5*pow(s, -1.5);

					double dkw = 4 * s*s*s;
					double dkn = 2 * (s - 1)*(1. - s*s) + (1. - s)*(1. - s)*(-2 * s);
					double ddpc_ = 1.5*0.5*pow(s, -2.5);

					double rt = ((dkw*kn + kw*dkn)*(kw + kn) - kw*kn*(dkw + dkn)) / (kw + kn) / (kw + kn)*dpc_ + kw*kn / (kw + kn)*ddpc_;
					rt = -rt;

					return rt;
				}
				else {
					return 0.;
				}
			}
			double Lamdad_n(double s){
				return (2.*(s - 1.)*(1. - s*s) + (s - 1.)*(s - 1.)*(-2.*s)) / mu_n;
			}
			double Lamdad_w(double s){
				return 4.*s*s*s / mu_w;
			}
			int	boundary_indicator_t(FVector_double& p)	{
				int ret = 1;
				// ret=1. normal. ret=0. dirichlet.
				double x = p[0];	double y = p[1];
				return ret;
			}
			int	boundary_indicator_w(FVector_double& p)	{
				int ret = 1;
				// ret=1. normal. ret=0. dirichlet.
				double x = p[0];	double y = p[1];
				return ret;
			}
			int	boundary_indicator_n(FVector_double& p)	{
				int ret = 1;
				// ret=1. normal. ret=0. dirichlet.
				double x = p[0];	double y = p[1];
				return ret;
			}
			double	flux_t(FVector_double& p){
				double x = p[0], y = p[1];
				double rt = 0;
				return rt;
			}
			double	flux_w(FVector_double& p){
				double x = p[0], y = p[1];
				double rt = 0;
				return rt;
			}
			double	K_p_(FVector_double & p) {
				double x = p[0], y = p[1];
				double rt = 0;
				if (Interface(p) <= 0) {
					rt = mum;
				}
				if (Interface(p) > 0){
					rt = mup;
				}
				return rt;
			}
			double	Initial_Val(FVector_double & p) {
				double rt = sw(0, p);
				return rt;
			}
			double	dirichlet_t(FVector_double& p) {
				double x = p[0], y = p[1];
				double rt = 0;
				return rt;
			}
			double	dirichlet_w(FVector_double& p) {
				double x = p[0], y = p[1];
				double rt = 0;
				return rt;
			}
			double	dirichlet_n(FVector_double& p) {
				double x = p[0], y = p[1];
				double rt = 0;
				return rt;
			}
		};
		class Interface_Smooth_Sol_Curve_Interface : public FEM_PROBLEM {
		public:
			// Exact Solution.
			// Line Interface
			void		initialize(FEM_VARIABLES::ENTIRE& __) {
				cout << "Curve Interface" << endl;
				mu_w = 1.;	mu_n = 1.;	phi = 1.;
				__.dim = 2;
				__.RX.make(__.dim, __.dim).setAll(0., 0., CV.PI / 2., CV.PI / 2.);
				nInterface = 1;
				nFunction = 101;
				r0 = 1./4.;
				mum = pow(10., -3.);
				mup = pow(10., 0.);

				mum = 0.001;
				mup = 1.;
			}
			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				double rt = (x - 0.5)*(x - 0.5) + (y - 0.5)*(y - 0.5) - r0*r0;
				return rt;
			}

			void	DInterface(FVector_double& p, FVector_double& vDI) {
				double x = p[0], y = p[1];
				vDI[0] = 2.*(x - 0.5);
				vDI[1] = 2.*(y - 0.5);
			}
			void	DDInterface(FVector_double& p, FMatrix_double& mDDI)	{
				double x = p[0], y = p[1];
				mDDI[0][0] = 2.;
				mDDI[1][1] = 2.;
			}

			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);
				return 0;
			}
			double	coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.
				if (Interface(p) < 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}
			double	sw(double t, FVector_double& p) {
				double x = p[0], y = p[1];
				double L = Interface(p);
				double rt;
				rt = cos(x)*(0.2 + 0.5*t);
		//		rt = 0.5;
				return rt;

			}
			double 	Dtsw(double t, FVector_double& p) {
				double x = p[0], y = p[1];
				double L = Interface(p);
				double rt;
				rt = cos(x)*0.5;
		//		rt = 0;
				return rt;
			}
			void	Dsw(double t, FVector_double& p, FVector_double & vDS) {
				double x = p[0], y = p[1];
				double L = Interface(p);
				double DLx = 2.*(x - 0.5);
				double DLy = 2.*(y - 0.5);

				vDS[0] = -sin(x)*(0.2 + 0.5*t);
				vDS[1] = 0;
		//		vDS.clear();
			}
			double	gp(double t, FVector_double& p) {
				double x = p[0], y = p[1];
				double rt;
				double L = Interface(p);
				double e = 2.7182818284590452353602874;
				double K__ = K_p_(p);

				if (L > 0){
					rt = -L*(x - 1) *(2 - t)*mum + 1;
				}
				if (L <= 0){
					rt = -L*(x - 1) *(2 - t) + 1;
				}
				rt = 10*rt;
				return rt;
			}
			void	Dgp(double t, FVector_double& p, FVector_double& vDP)	{

				double x = p[0], y = p[1];
				double L = Interface(p);
				double DLx = 2.*(x - 0.5);
				double DLy = 2.*(y - 0.5);
				double K__ = K_p_(p);
				
				if (L > 0){
					vDP[0] = ((x - 1)*DLx + L)*mum;
					vDP[1] = DLy*(x - 1)*mum;
				}
				if (L <= 0){
					vDP[0] = (x - 1)*DLx + L;
					vDP[1] = DLy*(x - 1);
				}
				vDP[0] = -vDP[0] * (2. - t) *10;
				vDP[1] = -vDP[1] * (2. - t) * 10;
			}
			void	DDgp(double t, FVector_double& p, FMatrix_double& mDP)	{
				double x = p[0], y = p[1];
				double L = Interface(p);
				double DLx = 2.*(x - 0.5);
				double DLy = 2.*(y - 0.5);
				double DDL = 2.;
				double K__ = K_p_(p);
			
				if (L > 0){
					mDP[0][0] = (2 * DLx + (x - 1)*DDL)*mum;
					mDP[1][1] = DDL * (x - 1)*mum;
				}
				if (L <= 0){
					mDP[0][0] = 2 * DLx + (x - 1)*DDL;
					mDP[1][1] = DDL * (x - 1);
				}
				mDP[0][0] = -mDP[0][0] * (2 - t) * 10;
				mDP[1][1] = -mDP[1][1] * (2 - t) * 10;
			}
			void	tv(double t, FVector_double& p, FVector_double& vDV) {
				double x = p[0], y = p[1];

				double sw_ = sw(t, p);
				double L = Interface(p);
				double K_ = K_p_(p);;
				double gp_ = gp(t, p);
				double lambda = Lamda(sw_);

				static FVector_double stv_vDP(2);
				Dgp(t, p, stv_vDP);

				vDV[0] = -lambda*stv_vDP[0] * K_;
				vDV[1] = -lambda*stv_vDP[1] * K_;

			}
			void	Dtv(double t, FVector_double& p, FMatrix_double& mDV) {

			}
			double	qt(double t, FVector_double& p) {

				double x = p[0], y = p[1];
				double e = 2.7182818284590452353602874;
				double rt;
				double L = Interface(p);
				double sw_ = sw(t, p);
				double lamda_ = Lamda(sw_);
				double lamdad_ = Lamdad(sw_);
				double K_;
				double lap_p;

				static FVector_double sqt_DL(2);
				static FMatrix_double sqt_DDP(2, 2);
				static FVector_double sqt_DP(2);
				static FVector_double sqt_DS(2);

				DInterface(p, sqt_DL);
				Dgp(t, p, sqt_DP);
				DDgp(t, p, sqt_DDP);
				Dsw(t, p, sqt_DS);

				K_ = K_p_(p);

				lap_p = sqt_DDP[0][0] + sqt_DDP[1][1];
				rt = -lap_p*K_*lamda_ - lamdad_*K_*(sqt_DS, sqt_DP);

				return rt;

			}
			double	qw(double t, FVector_double& p) {

				double x = p[0], y = p[1];
				double rt;
				double sw_ = sw(t, p);
				double f = fw(sw_);
				double df = Dfw(sw_);
				double divu = qt(t, p);
				double st;

				static FVector_double sqw_DS(2);
				static FVector_double sqw_U(2);

				Dsw(t, p, sqw_DS);
				tv(t, p, sqw_U);

				st = Dtsw(t, p);
				rt = st + df*(sqw_DS, sqw_U) + f*divu;

				return rt;

			}
			double	k_n(double s)	{
				return (1. - s)*(1. - s)*(1. - s*s);
			}

			double	k_w(double s){
				return s*s*s*s;
			}
			double	Lamda_n(double s){
				double k = k_n(s);
				return k / mu_n;
			}
			double	Lamda_w(double s){
				double k = k_w(s);
				return k / mu_w;
			}
			double	Lamda(double s){
				double t1;	double t2;
				t1 = Lamda_n(s);
				t2 = Lamda_w(s);
				return t1 + t2;

			}
			double	Lamdad(double s){
				double t1;	double t2;
				t1 = Lamdad_n(s);
				t2 = Lamdad_w(s);
				return t1 + t2;

			}
			double fw(double s){

				double lamda;
				double lamdaw;
				lamdaw = Lamda_w(s);
				lamda = Lamda(s);

				return lamdaw / lamda;
			}
			double	Dfw(double s) {

				double denom = (s*s*s*s + (1 - s)*(1 - s)*(1 - s*s))*(s*s*s*s + (1 - s)*(1 - s)*(1 - s*s));
				double numer = 4 * s*s*s*(s*s*s*s + (1 - s)*(1 - s)*(1 - s*s)) - s*s*s*s*(4 * s*s*s - 2 * (1 - s)*(1 - s*s) + (1 - s)*(1 - s)*(-2 * s));

				return numer / denom;

			}

			double Lamdad_n(double s){
				return (2.*(s - 1.)*(1. - s*s) + (s - 1.)*(s - 1.)*(-2.*s)) / mu_n;
			}
			double Lamdad_w(double s){
				return 4.*s*s*s / mu_w;
			}
			int	boundary_indicator_t(FVector_double& p)	{
				int ret = 1;
				// ret=1. normal. ret=0. dirichlet.
				double x = p[0];	double y = p[1];
				return ret;
			}
			int	boundary_indicator_w(FVector_double& p)	{
				int ret = 1;
				// ret=1. normal. ret=0. dirichlet.
				double x = p[0];	double y = p[1];
				return ret;
			}
			int	boundary_indicator_n(FVector_double& p)	{
				int ret = 1;
				// ret=1. normal. ret=0. dirichlet.
				double x = p[0];	double y = p[1];
				return ret;
			}
			double	flux_t(FVector_double& p){
				double x = p[0], y = p[1];
				double rt = 0;
				return rt;
			}
			double	flux_w(FVector_double& p){
				double x = p[0], y = p[1];
				double rt = 0;
				return rt;
			}
			double	K_p_(FVector_double & p) {
				double x = p[0], y = p[1];
				double rt = 0;
				if (Interface(p) <= 0) {
					rt = mum;
				}
				if (Interface(p) > 0){
					rt = mup;
				}
				return rt;
			}
			double	Initial_Val(FVector_double & p) {
				double rt = sw(0, p);
				return rt;
			}

			double	dirichlet_t(FVector_double& p) {
				double x = p[0], y = p[1];
				double rt = 0;
				return rt;
			}
			double	dirichlet_w(FVector_double& p) {
				double x = p[0], y = p[1];
				double rt = 0;
				return rt;
			}
			double	dirichlet_n(FVector_double& p) {
				double x = p[0], y = p[1];
				double rt = 0;
				return rt;
			}

		};
		class Interface_Smooth_Sol_Curve_Interface_DISCON_DIVU : public FEM_PROBLEM {
		public:
			// Exact Solution.
			// Line Interface
			void		initialize(FEM_VARIABLES::ENTIRE& __) {
				 
			//	cout << "Curve Interface DISC DIVU SIOSDJFOSDJFIOSDJFIOJO" << endl;
				K_p = pow(10., 0.);	mu_w = 1.;	mu_n = 1.;	phi = 1.;
				__.dim = 2;
				
				__.RX.make(__.dim, __.dim).setAll(0., 0., CV.PI / 2., CV.PI / 2.);
				RX = __.RX;
				nInterface = 1;
				nFunction = 101;
				r0 = 1./4.;
				mum = pow(10., -3.);
				mup = pow(10., 0.);
			}
			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				double rt = (x - 0.5)*(x - 0.5) + (y - 0.5)*(y - 0.5) - r0*r0;
				return rt;
			}

			void	DInterface(FVector_double& p, FVector_double& vDI) {
				double x = p[0], y = p[1];
				vDI[0] = 2.*(x - 0.5);
				vDI[1] = 2.*(y - 0.5);
			}
			void	DDInterface(FVector_double& p, FMatrix_double& mDDI)	{
				double x = p[0], y = p[1];
				mDDI[0][0] = 2.;
				mDDI[1][1] = 2.;
			}

			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);
				return 0;
			}
			double	coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.
				if (Interface(p) < 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}
			double	sw(double t, FVector_double& p) {
				double x = p[0], y = p[1];
				double L = Interface(p);
				double rt;
				rt=	cos(x)*(0.2 + 0.5*t);
			//	rt = 0.5;
				return rt;

			}
			double 	Dtsw(double t, FVector_double& p) {
				double x = p[0], y = p[1];
				double L = Interface(p);
				double rt;
				rt = cos(x)*0.5;
			//	rt = 0.;
				return rt;
			}
			void	Dsw(double t, FVector_double& p, FVector_double & vDS) {
				double x = p[0], y = p[1];
				double L = Interface(p);
				double DLx = 2.*(x - 0.5);
				double DLy = 2.*(y - 0.5);

				vDS[0] = -sin(x)*(0.2+0.5*t);
				vDS[1] = 0;
			//	vDS.clear();
			}
			double	gp(double t, FVector_double& p) {
				double x = p[0], y = p[1];
				double rt;
				double L = Interface(p);
				double e = 2.7182818284590452353602874;
				if (L > 0){
					rt = -L*(x - 1);
					rt = rt*mum*(2 - t) + 0.1;
				}
				if (L <= 0){
					rt = -pow(e, L*(x - 1)) + 1;
					rt = rt*(2 - t) + 0.1;
				}
				rt = 10 * rt;
				return rt;
			}
			void	Dgp(double t, FVector_double& p, FVector_double& vDP)	{

				double x = p[0], y = p[1];
				double L = Interface(p);
				double DLx = 2.*(x - 0.5);
				double DLy = 2.*(y - 0.5);
				double e = 2.7182818284590452353602874;
				if (L > 0){
					vDP[0] = (x-1)*DLx + L;
					vDP[1] = DLy*(x-1);
					vDP[0] = -vDP[0] * mum * (2. - t);
					vDP[1] = -vDP[1] * mum * (2. - t);
				}
				if (L <= 0){
					vDP[0] = (x - 1)*DLx*pow(e, L*(x - 1)) + L*pow(e, L* (x - 1));
					vDP[1] = DLy*(x-1)*pow(e,L*(x-1));
					vDP[0] = -vDP[0] * (2 - t);
					vDP[1] = -vDP[1] * (2 - t);
				}
				vDP[0] = vDP[0] * 10;
				vDP[1] = vDP[1] * 10;
			}
			void	DDgp(double t, FVector_double& p, FMatrix_double& mDP)	{
				double x = p[0], y = p[1];
				double L = Interface(p);
				double DLx = 2.*(x - 0.5);
				double DLy = 2.*(y - 0.5);
				double DDL = 2.;
				double e = 2.7182818284590452353602874;

				if (Interface(p) > 0){
					mDP[0][0] = 2 * DLx + (x - 1)*DDL;
					mDP[1][1] = DDL * (x - 1);
					mDP[0][0] = -mDP[0][0] * mum*(2 - t);
					mDP[1][1] = -mDP[1][1] * mum*(2 - t);
				}
				if (Interface(p) <= 0){
					mDP[0][0] = DLx*pow(e, L*(x - 1)) + (x - 1)*DDL*pow(e, L*(x - 1)) + (x - 1)*DLx*((x - 1)*DLx*pow(e, L*(x - 1)) + L*pow(e, L* (x - 1))) + DLx*pow(e, L*(x - 1)) + L*((x - 1)*DLx*pow(e, L*(x - 1)) + L*pow(e, L* (x - 1)));

					// -DLx*pow(e, L*(x - 1)) - (x - 1)*DDL*pow(e, L*(x - 1)) - (x - 1)*DLx*((x - 1)*DLx*pow(e, L*(x - 1)) + L*pow(e, L* (x - 1)))-DLx*pow(e,L*(x-1))-L*(DLx*(x-1)+L)*pow(e,L*(x-1));
					mDP[1][1] = DDL*(x-1)*pow(e,L*(x-1)) + DLy*DLy*(x-1)*(x-1)*pow(e,L*(x-1));
					mDP[0][0] = -mDP[0][0] * (2 - t);
					mDP[1][1] = -mDP[1][1] * (2 - t);
				}
				mDP[0][0] = mDP[0][0] * 10;
				mDP[1][1] = mDP[1][1] * 10;
			}
			void	tv(double t, FVector_double& p, FVector_double& vDV) {
				double x = p[0], y = p[1];

				double sw_ = sw(t, p);
				double L = Interface(p);
				double K_ = K_p_(p);;
				double gp_ = gp(t, p);
				double lambda = Lamda(sw_);

				static FVector_double stv_vDP(2);
				Dgp(t, p, stv_vDP);

				vDV[0] = -lambda*stv_vDP[0] * K_;
				vDV[1] = -lambda*stv_vDP[1] * K_;


			}
			void	Dtv(double t, FVector_double& p, FMatrix_double& mDV) {

			}
			double	qt(double t, FVector_double& p) {

				double x = p[0], y = p[1];
				double e = 2.7182818284590452353602874;
				double rt;
				double L = Interface(p);
				double sw_ = sw(t, p);
				double lamda_ = Lamda(sw_);
				double lamdad_ = Lamdad(sw_);
				double K_;
				double lap_p;

				static FVector_double sqt_DL(2);
				static FMatrix_double sqt_DDP(2, 2);
				static FVector_double sqt_DP(2);
				static FVector_double sqt_DS(2);

				DInterface(p, sqt_DL);
				Dgp(t, p, sqt_DP);
				DDgp(t, p, sqt_DDP);
				Dsw(t, p, sqt_DS);

				K_ = K_p_(p);

				lap_p = sqt_DDP[0][0] + sqt_DDP[1][1];
				rt = -lap_p*K_*lamda_ - lamdad_*K_*(sqt_DS, sqt_DP);

				return rt;

			}
			double	qw(double t, FVector_double& p) {

				double x = p[0], y = p[1];
				double rt;
				double sw_ = sw(t, p);
				double f = fw(sw_);
				double df = Dfw(sw_);
				double divu = qt(t, p);
				double st;

				static FVector_double sqw_DS(2);
				static FVector_double sqw_U(2);

				Dsw(t, p, sqw_DS);
				tv(t, p, sqw_U);

				st = Dtsw(t, p);
				rt = st + df*(sqw_DS, sqw_U) + f*divu;

				return rt;
			}
			double	k_n(double s)	{
				return (1. - s)*(1. - s)*(1. - s*s);
			}

			double	k_w(double s){
				return s*s*s*s;
			}
			double	Lamda_n(double s){
				double k = k_n(s);
				return k / mu_n;
			}
			double	Lamda_w(double s){
				double k = k_w(s);
				return k / mu_w;
			}
			double	Lamda(double s){
				double t1;	double t2;
				t1 = Lamda_n(s);
				t2 = Lamda_w(s);
				return t1 + t2;

			}
			double	Lamdad(double s){
				double t1;	double t2;
				t1 = Lamdad_n(s);
				t2 = Lamdad_w(s);
				return t1 + t2;

			}
			double fw(double s){

				double lamda;
				double lamdaw;
				lamdaw = Lamda_w(s);
				lamda = Lamda(s);

				return lamdaw / lamda;
			}
			double	Dfw(double s) {

				double denom = (s*s*s*s + (1 - s)*(1 - s)*(1 - s*s))*(s*s*s*s + (1 - s)*(1 - s)*(1 - s*s));
				double numer = 4 * s*s*s*(s*s*s*s + (1 - s)*(1 - s)*(1 - s*s)) - s*s*s*s*(4 * s*s*s - 2 * (1 - s)*(1 - s*s) + (1 - s)*(1 - s)*(-2 * s));

				return numer / denom;

			}

			double Lamdad_n(double s){
				return (2.*(s - 1.)*(1. - s*s) + (s - 1.)*(s - 1.)*(-2.*s)) / mu_n;
			}
			double Lamdad_w(double s){
				return 4.*s*s*s / mu_w;
			}
			int	boundary_indicator_t(FVector_double& p)	{
				int ret = 1;
				// ret=1. normal. ret=0. dirichlet.
				double x = p[0];	double y = p[1];
				return ret;
			}
			int	boundary_indicator_w(FVector_double& p)	{
				int ret = 1;
				// ret=1. normal. ret=0. dirichlet.
				double x = p[0];	double y = p[1];
				return ret;
			}
			int	boundary_indicator_n(FVector_double& p)	{
				int ret = 1;
				// ret=1. normal. ret=0. dirichlet.
				double x = p[0];	double y = p[1];
				return ret;
			}
			double	flux_t(FVector_double& p){
				double x = p[0], y = p[1];
				double rt = 0;
				return rt;
			}
			double	flux_w(FVector_double& p){
				double x = p[0], y = p[1];
				double rt = 0;
				return rt;
			}
			double	K_p_(FVector_double & p) {
				double x = p[0], y = p[1];
				double rt = 0;
				if (Interface(p) <= 0) {
					rt = mum;
				}
				if (Interface(p) > 0){
					rt = mup;
				}
				return rt;
			}
			double	Initial_Val(FVector_double & p) {
				double rt = sw(0, p);
				return rt;
			}

			double	dirichlet_t(FVector_double& p) {
				double x = p[0], y = p[1];
				double rt = 0;
				return rt;
			}
			double	dirichlet_w(FVector_double& p) {
				double x = p[0], y = p[1];
				double rt = 0;
				return rt;
			}
			double	dirichlet_n(FVector_double& p) {
				double x = p[0], y = p[1];
				double rt = 0;
				return rt;
			}

		}; 
		class Permeable_Lens_IFEM: public FEM_PROBLEM {
		public:
			// Parabolic Example. Example in Peter Bastian book 167p
			
			void		initialize	(FEM_VARIABLES::ENTIRE& __) {
				mu_w = pow(10., -3.);	mu_n = 0.9*pow(10., -3.);	phi = 0.4;
				phi_w = 0.4;			phi_n = 0.39;
				rho_w = 1000.;			rho_n = 1460.;
				__.dim = 2;
				eps = 0.01;
				RX = __.RX.make(__.dim, __.dim).setAll(0., 0., 0.9, 0.65); 
				mup = 6.64*pow(10., -11.);
				mum = 3.32*pow(10., -11.);
				snr = 0.;
				s_critical = 0.62;
			//	cout << "INIT " << endl;
			}
			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				return (x-0.45)*(x-0.45)/8.+(y-0.4)*(y-0.4)-0.1*0.1;
			} 
			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);
				return 0;
			}
			double	coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.
				if (Interface(p) < 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}
			double	k_w(int io, double sn){
				double sw_;
				double lamda; 
				double denom;
				if (io == CV.IN){
					denom = 0.88;
					sw_ = (1 - sn - 0.12) / denom;
					lamda = 2.;
				}
				else{
					denom = 0.9;
					sw_ = (1 - sn - 0.1) / denom;
					lamda = 2.7;
				}
				return pow(sw_, (2. + 3.*lamda) / lamda);
			}
			double	k_n(int io, double sn)	{
				double sn_;
				double lamda;
				double denom;
				if (io == CV.IN){
					denom = 0.88;
					sn_ = sn / denom;
					lamda = 2.;
				}
				else{
					denom = 0.9;
					sn_ = sn / denom;
					lamda = 2.7;
				}
				return sn_*sn_*(1 - pow((1 - sn_), (2 + lamda) / lamda));
			}
			double	dk_w(int io, double s){
				double sw_;
				double lamda;
				double denom;
				if (io == CV.IN){
					denom = 0.88;
					sw_ = (1 - s - 0.12) / denom;
					lamda = 2.;
				}
				else{
					denom = 0.9;
					sw_ = (1 - s - 0.1) / denom;
					lamda = 2.7;
				}
				return -(2. + 3.*lamda) / lamda / denom*pow(sw_, (2. + 3.*lamda) / lamda - 1.);
			}
			double	dk_n(int io, double s)	{
				double sn_;
				double lamda;
				double denom;
				if (io == CV.IN){
					denom = 0.88;
					sn_ = (s) / denom;
					lamda = 2.;
				}
				else{
					denom = 0.9;
					sn_ = (s) / denom;
					lamda = 2.7;
				}
				return 2.*sn_ / denom*(1 - pow((1 - sn_), (2 + lamda) / lamda)) + sn_*sn_*((2 + lamda) / lamda) / denom * 2 * pow(1. - sn_, 2 / lamda);
			}
			double	Lamda_n(int io, double s){
				double k = k_n(io, s);
				return k / mu_n;
			}
			double	Lamda_w(int io, double s){
				double k = k_w(io, s);
				return k / mu_w;
			}
			double	Lamda(int io, double s){
				double t1;	double t2;
				t1 = Lamda_n(io, s);
				t2 = Lamda_w(io, s);
				return t1 + t2;
			}
			double Lamdad_n(int io, double s){
				double k = dk_n(io, s);
				return k / mu_n;
			}
			double Lamdad_w(int io, double s){
				double k = dk_w(io, s);
				return k / mu_w;
			}
			double	Lamdad(int io, double s){
				double t1;	double t2;
				t1 = Lamdad_n(io, s);
				t2 = Lamdad_w(io, s);
				return t1 + t2;
			}
			double	fn(int io, double s) {
				double t1; double t2;
				t1 = Lamda(io, s);
				t2 = Lamda_n(io, s);
				return t2 / t1;
			}
			double	fw(int io, double s) {
				double t1; double t2;
				t1 = Lamda(io, s);
				t2 = Lamda_w(io, s);
				return t2 / t1;
			}
			int	boundary_indicator_t	(FVector_double& p)	{
				int ret=1;
				// ret=1. normal. ret=0. dirichlet.
				double x=p[0];	double y=p[1];
				if ( (x==RX[0][0]) || (x==RX[1][0]) )
					ret=0;
				else
					ret=1;
				return ret;
			}
			int	boundary_indicator_w	(FVector_double& p)	{
				int ret=1;
				// ret=1. normal. ret=0. dirichlet.
				double x=p[0];	double y=p[1];
				if ( (x==RX[0][0]) || (x==RX[1][0]) )
					ret=0;
				else
					ret=1;
				return ret;
			}
			int	boundary_indicator_n	(FVector_double& p)	{
				int ret=1;
				// ret=1. normal. ret=0. dirichlet.
				double x=p[0];	double y=p[1];
				if ( (x==RX[0][0]) || (x==RX[1][0]) || (y==RX[0][1]) )
					ret=0;
				else
					ret=1;
				return ret;
			}
			double	flux_w(FVector_double& p){
				double x=p[0], y=p[1];
				double rt=0.;
				if ((y==RX[1][1]) || (y==RX[0][1]) )
					rt=0.;
				return rt;
			}
			double	flux_n(FVector_double& p){
				double x=p[0], y=p[1];
				double rt=0.;
				if ( (y==RX[0][1]) || (y==RX[1][1]) )
					rt=0.;
				if ((y==RX[1][1]) && (x>=0.225) && (x<=0.675) )
					rt=-0.075/rho_n;
				return rt;
			}
			double	flux_t(FVector_double& p){
				double rt;
				double f1;	double f2;
				f1=_problem->flux_w(p);
				f2=_problem->flux_n(p);
				rt=f1+f2;
				return rt;
			}
			double	K_p_(int io) {
				double rt=0;
				if (io == CV.IN)
					rt=3.32*pow(10.,-11.);
				else
					rt=6.64*pow(10.,-11.);
				return rt;
			}
			double	Phi_(int io) {
				double rt=0;
				if (io == CV.IN)
					rt=0.39;
				else
					rt=0.4;
				return rt;
			}
			double	Initial_Val(FVector_double & p) {
				double x=p[0], y=p[1];
				double rt=0;
				return rt;
			}
			
			double	dirichlet_t	(FVector_double& p) {
				double x=p[0], y=p[1];
				double rt=0;
				if	( (x==RX[0][0]) || (x==RX[1][0]) )
					rt=(0.65-y)*9810.;
				return rt;
			}
			double	dirichlet_w	(FVector_double& p) {
				double x=p[0], y=p[1];
				double rt=0;
				if	( (x==RX[0][0]) || (x==RX[1][0]) )
					rt=(0.65-y)*9810.;
				return rt;
			}
			double	dirichlet_n	(FVector_double& p) {
				double x=p[0], y=p[1];
				double rt=0;
				if	( (x==RX[0][0]) || (x==RX[1][0]) || (y==RX[0][1]) )
					rt=0.;
				return rt;
			}
			double pc (int io, double sn){
				double pd;
				double lamda;
				double sw_;
				double denom;
				if (sn<0)
					sn=0;
				if (io == CV.IN){
					pd = 1163.5;
					lamda = 2.;
					denom = 0.88;
					sw_ = (1 - sn - 0.12) / denom;
				}
				else{
					pd = 775.;
					lamda = 2.7;
					denom = 0.9;
					sw_ = (1 - sn - 0.1) / denom;
				}
				return pd*pow(sw_, -1 / lamda);
			}
			double pc_in_inv (double s) {
				 
				int io = CV.IN;
				double left_ = 0.;
				double right_ = 0.85;
				double mid_ = 0.;
				
				double f_left_ = pc(io, left_) - s;
				double f_right_ = pc(io, right_) - s; 
				double tol = pow(10., -10.);
				double res = 1.;
				while (abs(res) > tol){
					mid_ = (left_ + right_) / 2.;
					res = pc(io, mid_) - s;

					if (res <= 0){
						left_ = mid_;
					}
					else{
						right_ = mid_;
					}

				} 
				return mid_;
			
			}
			double dpc (int io, double sn){ 
				double pd;
				double lamda;
				double sw_;
				double denom;
				if (sn<0)
					sn = 0;
				if (io == CV.IN){
					pd = 1163.5;
					lamda = 2.;
					denom = 0.88;
					sw_ = (1 - sn - 0.12) / denom;
				}
				else{
					pd = 775.;
					lamda = 2.7;
					denom = 0.9;
					sw_ = (1 - sn - 0.1) / denom;
				}
				return -(-1 / lamda) / denom*pd*pow(sw_, -1 / lamda - 1);
			}
			double ddpc (int io, double sn){ 
				double pd;
				double lamda;
				double denom;
				double sw_;
				if (sn<0)
					sn = 0;
				if (io == CV.IN){
					pd = 1163.5;
					lamda = 2.;
					denom = 0.88;
					sw_ = (1 - sn - 0.12) / denom;
				}
				else{
					pd = 775.;
					lamda = 2.7;
					denom = 0.9;
					sw_ = (1 - sn - 0.1) / denom;
				}
				return (-1 / lamda)*(-1 / lamda - 1) / denom / denom*pd*pow(sw_, -1 / lamda - 2);
			}
			double P_Jump(FVector_double & p){
				// Jump of Sw at t=0
				return 0.;
			}
			double Flux_Jump(FVector_double & p, FVector_double & vN){
				// Jump of Sw at t=0
				return 0.;
			}
		};
		class Permeable_Lens_IFEM_GH_ZERO_GRAVITY : public FEM_PROBLEM {
		public:
			// Parabolic Example. Example in Peter Bastian book 167p

			void		initialize(FEM_VARIABLES::ENTIRE& __) {
				mu_w = pow(10., -3.);	mu_n = 0.9*pow(10., -3.);	phi = 0.4;
				phi_w = 0.4;			phi_n = 0.39;
				rho_w = 1000.;			rho_n = 1460.;
				__.dim = 2;
				eps = 0.01;
				RX = __.RX.make(__.dim, __.dim).setAll(0., 0., 0.9, 0.65);
				mup = 6.64*pow(10., -11.);
				mum = 3.32*pow(10., -11.);
				snr = 0.;
				s_critical = 0.447772;
				pd_in = 1163.5;
				// 1163.5 or 1466.1
				//	cout << "INIT " << endl;
			}
			double	Jump_Saturation_In	(double s_out) {
				double s_in = 0.;
				double pc_out_;
				if (s_out <= s_critical){
					s_in = 0.;
				}
				else{
					pc_out_ = _problem->pc(CV.OUT, s_out);
					s_in=pc_in_inv(pc_out_);
				}

				return s_in;
			}
			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				return (x - 0.45)*(x - 0.45) / 5. + (y - 0.38)*(y - 0.38) - 0.122*0.122;
			}
			void	DInterface(FVector_double& p, FVector_double& vDI)	{
				double x = p[0], y = p[1];
				vDI.setAll(2.*(x-0.45)/5., 2.*(y-0.45));
			}
			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);
				return 0;
			}
			double	coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.
				if (Interface(p) < 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}
			double	k_w(int io, double sn){
				double sw_;
				double lamda;
				double denom;
				if (io == CV.IN){
					denom = 0.88;
					sw_ = (1 - sn - 0.12) / denom;
					lamda = 2.;
				}
				else{
					denom = 0.9;
					sw_ = (1 - sn - 0.1) / denom;
					lamda = 2.7;
				}
				return pow(sw_, (2. + 3.*lamda) / lamda);
			}
			double	k_n(int io, double sn)	{
				double sn_;
				double lamda;
				double denom;
				if (io == CV.IN){
					denom = 0.88;
					sn_ = sn / denom;
					lamda = 2.;
				}
				else{
					denom = 0.9;
					sn_ = sn / denom;
					lamda = 2.7;
				}
				return sn_*sn_*(1 - pow((1 - sn_), (2 + lamda) / lamda));
			}
			double	dk_w(int io, double s){
				double sw_;
				double lamda;
				double denom;
				if (io == CV.IN){
					denom = 0.88;
					sw_ = (1 - s - 0.12) / denom;
					lamda = 2.;
				}
				else{
					denom = 0.9;
					sw_ = (1 - s - 0.1) / denom;
					lamda = 2.7;
				}
				return -(2. + 3.*lamda) / lamda / denom*pow(sw_, (2. + 3.*lamda) / lamda - 1.);
			}
			double	dk_n(int io, double s)	{
				double sn_;
				double lamda;
				double denom;
				if (io == CV.IN){
					denom = 0.88;
					sn_ = (s) / denom;
					lamda = 2.;
				}
				else{
					denom = 0.9;
					sn_ = (s) / denom;
					lamda = 2.7;
				}
				return 2.*sn_ / denom*(1 - pow((1 - sn_), (2 + lamda) / lamda)) + sn_*sn_*((2 + lamda) / lamda) / denom * 2 * pow(1. - sn_, 2 / lamda);
			}
			double	Lamda_n(int io, double s){
				double k = k_n(io, s);
				return k / mu_n;
			}
			double	Lamda_w(int io, double s){
				double k = k_w(io, s);
				return k / mu_w;
			}
			double	Lamda(int io, double s){
				double t1;	double t2;
				t1 = Lamda_n(io, s);
				t2 = Lamda_w(io, s);
				return t1 + t2;
			}
			double Lamdad_n(int io, double s){
				double k = dk_n(io, s);
				return k / mu_n;
			}
			double Lamdad_w(int io, double s){
				double k = dk_w(io, s);
				return k / mu_w;
			}
			double	Lamdad(int io, double s){
				double t1;	double t2;
				t1 = Lamdad_n(io, s);
				t2 = Lamdad_w(io, s);
				return t1 + t2;
			}
			double	fn(int io, double s) {
				double t1; double t2;
				t1 = Lamda(io, s);
				t2 = Lamda_n(io, s);
				return t2 / t1;
			}
			double	dfn(int io, double s) {
				double lamda_ = Lamda(io, s);
				double lamdad_ = Lamdad(io, s);
				double lamda_n = Lamda_n(io, s);
				double lamdad_n = Lamdad_n(io, s);

				return lamdad_n / lamda_ - lamda_n *lamdad_ / lamda_ / lamda_;
			}
			double	reduced_fn(int io, double s) {  
				double lambda_t = Lamda(io, s);
				double reduced_k_n;
				double Lamda_n;
				double sn_;
				double lamda;
				double denom;
				if (io == CV.IN){
					denom = 0.88;
					sn_ = (s+pow(10.,-9.)) / denom;
					lamda = 2.;
				}
				else{
					denom = 0.9;
					sn_ = (s + pow(10., -9.)) / denom;
					lamda = 2.7;
				}
				reduced_k_n =(1 - pow((1 - sn_), (2 + lamda) / lamda));				
				Lamda_n = reduced_k_n / mu_n; 
				return Lamda_n / lambda_t;
			}
			double	fw(int io, double s) {
				double t1; double t2;
				t1 = Lamda(io, s);
				t2 = Lamda_w(io, s);
				return t2 / t1;
			}
			int	boundary_indicator_t(FVector_double& p)	{
				int ret = 1;
				// ret=1. normal. ret=0. dirichlet.
				double x = p[0];	double y = p[1];
			//	if ((x == RX[0][0]) || (x == RX[1][0]))
				if (y==0)
					ret = 0;
				else
					ret = 1;
				return ret;
			}
			int	boundary_indicator_w(FVector_double& p)	{
				int ret = 1;
				// ret=1. normal. ret=0. dirichlet.
				double x = p[0];	double y = p[1];
			//	if ((x == RX[0][0]) || (x == RX[1][0]))
				if (y==0)
					ret = 0;
				else
					ret = 1;
				return ret;
			}
			int	boundary_indicator_n(FVector_double& p)	{
				int ret = 1;
				// ret=1. normal. ret=0. dirichlet.
				double x = p[0];	double y = p[1];
				//	if ((x == RX[0][0]) || (x == RX[1][0]))
				if (y == 0)
					ret = 0;
				else
					ret = 1;
				return ret;
			}
			double	flux_w(FVector_double& p){
				double x = p[0], y = p[1];
				double rt=0.;
				if ((y == RX[1][1]) || (y == RX[0][1]))
					rt = 0.;
				return rt;
			}
			double	flux_n(FVector_double& p){
				double x = p[0], y = p[1];
				double rt=0.;
				if ((y == RX[0][1]) || (y == RX[1][1]))
					rt = 0.;
				if ((y == RX[1][1]) && (x >= 0.45 - 0.2250 / 2) && (x <= 0.45 + 0.2250 / 2))
					rt = -0.075 / rho_n;
				return rt;
			}
			double	flux_t(FVector_double& p){
				double rt;
				double f1;	double f2;
				f1 = _problem->flux_w(p);
				f2 = _problem->flux_n(p);
				rt = f1 + f2;
				return rt;
			}
			double	K_p_(int io) {
				double rt = 0;
				if (io == CV.IN)
					rt = 3.32*pow(10., -11.);
				else
					rt = 6.64*pow(10., -11.);
				return rt;
			}
			double	K_p_(FVector_double & p) {
				double x = p[0], y = p[1];
				double rt = 0;
				if (Interface(p) <= 0) 
					rt = 3.32*pow(10., -11.);
				else
					rt = 6.64*pow(10., -11.);
				return rt;
			} 
			double	Phi_(int io) {
				double rt = 0;
				if (io == CV.IN)
					rt = 0.39;
				else
					rt = 0.4;
				return rt;
			}
			double	Phi_(FVector_double & p) {
				double x = p[0], y = p[1];
				double rt = 0;
				if (Interface(p) <= 0)
					rt = 0.39;
				else
					rt = 0.4;
				return rt;
			}
			double	Initial_Val(FVector_double & p) {
				double x = p[0], y = p[1];
				double rt = 0;
				return rt;
			} 
			double	dirichlet_t(FVector_double& p) {
				double x = p[0], y = p[1];
				double rt = 0;
			//	if ((x == RX[0][0]) || (x == RX[1][0]))
			//		rt = (0.65 - y)*9810.;
				return 0.;
			}
			double	dirichlet_w(FVector_double& p) {
				double x = p[0], y = p[1];
				double rt = 0;
			//	if ((x == RX[0][0]) || (x == RX[1][0]))
			//		rt = (0.65 - y)*9810.;
				return 0.;
			}
			double	dirichlet_n(FVector_double& p) {
				double x = p[0], y = p[1];
				double rt = 0;
				if ((x == RX[0][0]) || (x == RX[1][0]) || (y == RX[0][1]))
					rt = 0.;
				return rt;
			}
			double pc(int io, double sn){
				double pd;
				double lamda;
				double sw_;
				double denom;
				if (sn < 0){
					if (abs(sn) < pow(10., -16.))
						sn = 0;
					else
						cout << "FEM Problem dpc: sn<0: " << sn << endl;
				}
				if (io == CV.IN){
					pd = pd_in;
				//	pd = 1466.1;
				// 	pd = 775.;
					lamda = 2.;
					denom = 0.88;
					sw_ = (1 - sn - 0.12) / denom;
				}
				else{
					pd = 775.;
					lamda = 2.7;
					denom = 0.9;
					sw_ = (1 - sn - 0.1) / denom;
				}
				return pd*pow(sw_, -1 / lamda);
			}
			double pc(FVector_double& p, double sn){
				double pd;
				double lamda;
				double sw_;
				double denom;
				if (sn < 0){
					if (abs(sn) < pow(10., -16.))
						sn = 0;
					else
						cout << "FEM Problem dpc: sn<0: " << sn << endl;
				}
				if (Interface(p) <= 0) {
					pd = pd_in;
			//		pd = 1466.1;
			// 		pd = 775.;
					lamda = 2.;
					denom = 0.88;
					sw_ = (1 - sn - 0.12) / denom;
				}
				else{
					pd = 775.;
					lamda = 2.7;
					denom = 0.9;
					sw_ = (1 - sn - 0.1) / denom;
				}
				return pd*pow(sw_, -1 / lamda);
			}
			double pc_in_inv(double s) {
				double left_ = 0.;
				double right_ = 0.85;
				double mid_ = 0.;
				double f_left_ = pc(CV.IN, left_) - s;
				double f_right_ = pc(CV.IN, right_) - s;
				double tol = pow(10., -10.);
				double res = 1.;

				while (abs(res) > tol){
					mid_ = (left_ + right_) / 2.;
					res = pc(CV.IN, mid_) - s;

					if (res <= 0){
						left_ = mid_;
					}
					else{
						right_ = mid_;
					}
				}
				return mid_;
			}
			double dpc(int io, double sn){
				double pd;
				double lamda;
				double sw_;
				double denom;
				if (sn < 0){
				 	if (abs(sn) < pow(10., -16.))
						sn = 0.;
					else
						cout << "FEM Problem dpc: sn<0: " << sn << endl;
				}
				if (io == CV.IN){
					pd = pd_in;
			//		pd = 1466.1;
					lamda = 2.;
					denom = 0.88;
					sw_ = (1 - sn - 0.12) / denom;
				}
				else{
					pd = 775.;
					lamda = 2.7;
					denom = 0.9;
					sw_ = (1 - sn - 0.1) / denom;
				} 
				return -(-1 / lamda) / denom*pd*pow(sw_, -1 / lamda - 1);
			}
			double dpc(FVector_double& p, double sn){
				double pd;
				double lamda;
				double sw_;
				double denom;
				if (sn < 0){
					if (abs(sn) < pow(10., -16.))
						sn = 0.;
					else
						cout << "FEM Problem dpc: sn<0: " << sn << endl;
				}
				if (Interface(p) <= 0) {
					pd = pd_in;
			//		pd = 1466.1;
					lamda = 2.;
					denom = 0.88;
					sw_ = (1 - sn - 0.12) / denom;
				}
				else{
					pd = 775.;
					lamda = 2.7;
					denom = 0.9;
					sw_ = (1 - sn - 0.1) / denom;
				}
				return -(-1 / lamda) / denom*pd*pow(sw_, -1 / lamda - 1);
			}
			double		gamma(int io, double s) 
			{ 
				double rt=0.;
				double fn;
				double lamba_w;
				double dpc;
				if (s < 0){ 
					if (abs(s) < pow(10., -16.))
						s = 0.;
					else
						cout << "FEM Problem gamma: sn<0: " << s << endl;
				}
				else{
					fn = _problem->fn(io, s);
					lamba_w = _problem->Lamda_w(io, s);
					dpc = _problem->dpc(io, s);
					rt = fn*lamba_w*dpc;
				}
				return rt;
			}
			double		dgamma(int io, double s) 
			{ 
				return 0; 
			}

			double ddpc(int io, double sn){
				double pd;
				double lamda;
				double denom;
				double sw_;
				if (sn<0)
					sn = 0;
				if (io == CV.IN){
					pd = 1163.5;
					lamda = 2.;
					denom = 0.88;
					sw_ = (1 - sn - 0.12) / denom;
				}
				else{
					pd = 775.;
					lamda = 2.7;
					denom = 0.9;
					sw_ = (1 - sn - 0.1) / denom;
				}
				return (-1 / lamda)*(-1 / lamda - 1) / denom / denom*pd*pow(sw_, -1 / lamda - 2);
			}
			double P_Jump(FVector_double & p){
				// Jump of Sw at t=0
				return 0.;
			}
			double Flux_Jump(FVector_double & p, FVector_double & vN){
				// Jump of Sw at t=0
				return 0.;
			}
		};
		class Permeable_Lens_GH_ZERO_GRAVITY : public FEM_PROBLEM {
		public:
			// Parabolic Example. Example in Peter Bastian book 167p

			void		initialize(FEM_VARIABLES::ENTIRE& __) {
				mu_w = pow(10., -3.);	mu_n = 0.9*pow(10., -3.);	phi = 0.4;
				phi_w = 0.4;			phi_n = 0.39;
				rho_w = 1000.;			rho_n = 1460.;
				__.dim = 2;
				eps = 0.01;
				RX = __.RX.make(__.dim, __.dim).setAll(0., 0., 0.9, 0.65);
				mu = 3.32*pow(10., -11.);
				snr = 0.;
				s_critical = 0.62;
				//	cout << "INIT " << endl;
			} 
			double	k_w(double sn){
				double sw_;
				double lamda;
				double denom;
				
				denom = 0.88;
				sw_ = (1 - sn - 0.12) / denom;
				lamda = 2.;

				return pow(sw_, (2. + 3.*lamda) / lamda);
			}
			double	k_n(double sn)	{
				double sn_;
				double lamda;
				double denom;
				denom = 0.88;
				sn_ = sn / denom;
				lamda = 2.;

				return sn_*sn_*(1 - pow((1 - sn_), (2 + lamda) / lamda));
			}
			double	dk_w(double s){
				double sw_;
				double lamda;
				double denom;
				denom = 0.88;
				sw_ = (1 - s - 0.12) / denom;
				lamda = 2.;

				return -(2. + 3.*lamda) / lamda / denom*pow(sw_, (2. + 3.*lamda) / lamda - 1.);
			}
			double	dk_n(double s)	{
				double sn_;
				double lamda;
				double denom;

				denom = 0.88;
				sn_ = (s) / denom;
				lamda = 2.;
				
				return 2.*sn_ / denom*(1 - pow((1 - sn_), (2 + lamda) / lamda)) + sn_*sn_*((2 + lamda) / lamda) / denom * 2 * pow(1. - sn_, 2 / lamda);
			}
			double	Lamda_n(double s){
				double k = k_n(s);
				return k / mu_n;
			}
			double	Lamda_w(double s){
				double k = k_w(s);
				return k / mu_w;
			}
			double	Lamda(double s){
				double t1;	double t2;
				t1 = Lamda_n(s);
				t2 = Lamda_w(s);
				return t1 + t2;
			}
			double Lamdad_n(double s){
				double k = dk_n(s);
				return k / mu_n;
			}
			double Lamdad_w(double s){
				double k = dk_w(s);
				return k / mu_w;
			}
			double	Lamdad(double s){
				double t1;	double t2;
				t1 = Lamdad_n(s);
				t2 = Lamdad_w(s);
				return t1 + t2;
			}
			double	fn(double s) {
				double t1; double t2;
				t1 = Lamda(s);
				t2 = Lamda_n(s);
				return t2 / t1;
			} 
			double	fw(double s) {
				double t1; double t2;
				t1 = Lamda(s);
				t2 = Lamda_w(s);
				return t2 / t1;
			}
			int	boundary_indicator_t(FVector_double& p)	{
				int ret = 1;
				// ret=1. normal. ret=0. dirichlet.
				double x = p[0];	double y = p[1];
				if ((x == RX[0][0]) || (x == RX[1][0]))
					ret = 0;
				else
					ret = 1;
				return ret;
			}
			int	boundary_indicator_w(FVector_double& p)	{
				int ret = 1;
				// ret=1. normal. ret=0. dirichlet.
				double x = p[0];	double y = p[1];
				if ((x == RX[0][0]) || (x == RX[1][0]))
					ret = 0;
				else
					ret = 1;
				return ret;
			}
			int	boundary_indicator_n(FVector_double& p)	{
				int ret = 1;
				// ret=1. normal. ret=0. dirichlet.
				double x = p[0];	double y = p[1];
				if ((x == RX[0][0]) || (x == RX[1][0]) || (y == RX[0][1]))
					ret = 0;
				else
					ret = 1;
				return ret;
			}
			double	flux_w(FVector_double& p){
				double x = p[0], y = p[1];
				double rt;
				if ((y == RX[1][1]) || (y == RX[0][1]))
					rt = 0.;
				return rt;
			}
			double	flux_n(FVector_double& p){
				double x = p[0], y = p[1];
				double rt;
				if ((y == RX[0][1]) || (y == RX[1][1]))
					rt = 0.;
				if ((y == RX[1][1]) && (x >= 0.45 - 0.2250) && (x <= 0.45 + 0.2250))
					rt = -0.075 / rho_n;
				return rt;
			}
			double	flux_t(FVector_double& p){
				double rt;
				double f1;	double f2;
				f1 = _problem->flux_w(p);
				f2 = _problem->flux_n(p);
				rt = f1 + f2;
				return rt;
			}
			double	K_p_(FVector_double & p) {
				double rt = 0;
				rt = 3.32*pow(10., -11.);
				return rt;
			}
			double	Phi_(FVector_double & p) {
				double rt = 0;
				rt = 0.39;
				return rt;
			}
			double	Initial_Val(FVector_double & p) {
				double x = p[0], y = p[1];
				double rt = 0;
				return rt;
			}

			double	dirichlet_t(FVector_double& p) {
				double x = p[0], y = p[1];
				double rt = 0;
				//	if ((x == RX[0][0]) || (x == RX[1][0]))
				//		rt = (0.65 - y)*9810.;
				return 0.;
			}
			double	dirichlet_w(FVector_double& p) {
				double x = p[0], y = p[1];
				double rt = 0;
				//	if ((x == RX[0][0]) || (x == RX[1][0]))
				//		rt = (0.65 - y)*9810.;
				return 0.;
			}
			double	dirichlet_n(FVector_double& p) {
				double x = p[0], y = p[1];
				double rt = 0;
				if ((x == RX[0][0]) || (x == RX[1][0]) || (y == RX[0][1]))
					rt = 0.;
				return rt;
			}
			double pc(double sn){
				double pd;
				double lamda;
				double sw_;
				double denom;
				if (sn<0)
					sn = 0;
				pd = 1163.5;
				lamda = 2.;
				denom = 0.88;
				sw_ = (1 - sn - 0.12) / denom;

				return pd*pow(sw_, -1 / lamda);
			}
			double dpc(double sn){
				double pd;
				double lamda;
				double sw_;
				double denom;
				if (sn<0)
					sn = 0;
				pd = 1163.5;
				lamda = 2.;
				denom = 0.88;
				sw_ = (1 - sn - 0.12) / denom;
				return -(-1 / lamda) / denom*pd*pow(sw_, -1 / lamda - 1);
			}
			double		gamma(double s)
			{
				double rt = 0.;
				double fn;
				double lamba_w;
				double dpc;
				if (s == 0){
					rt = 0.;
				}
				else{
					fn = _problem->fn(s);
					lamba_w = _problem->Lamda_w(s);
					dpc = _problem->dpc(s);
					rt = fn*lamba_w*dpc;
				}
				return rt;
			}
			double		dgamma(int io, double s)
			{
				return 0;
			}
			double P_Jump(FVector_double & p){
				// Jump of Sw at t=0
				return 0.;
			}
			double Flux_Jump(FVector_double & p, FVector_double & vN){
				// Jump of Sw at t=0
				return 0.;
			}
		};
		class Duijin_1D_Discontinuous_CapillaryPressure: public FEM_PROBLEM {
		public:
			// Parabolic Example. Example in Peter Bastian book 167p
			void		initialize(FEM_VARIABLES::ENTIRE& __) {
				mu_w = 1.;	mu_n = 1.;	phi = 1.;
				phi_w = 1.;			phi_n = 1.;
				rho_w = 1.;			rho_n = 1.;
				__.dim = 2;
				snr = 0.;
				eps = 0.01;
				RX = __.RX.make(__.dim, __.dim).setAll(-0.6, 0., 0.6, 1.);
				mup = 1.;
				mum = 0.64; 

				s_critical = 1 - mum;
				// 1163.5 or 1466.1
				//	cout << "INIT " << endl;
			}
			double	Jump_Saturation_In(double s_out) {
				double s_in = 0.;
				double pc_out_;
				if (s_out <= s_critical){
					s_in = 0.;
				}
				else{
					pc_out_ = _problem->pc(CV.OUT, s_out);
					s_in = pc_in_inv(pc_out_);
				}

				return s_in;
			}
			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				return -x;
			}
			void	DInterface(FVector_double& p, FVector_double& vDI)	{
				double x = p[0], y = p[1];
				vDI.setAll(-1., 0.);
			}
			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);
				return 0;
			}
			double	coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.
				if (Interface(p) < 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}
			double	k_w(int io, double sn){
				double sw_;
				double lamda=2;
				sw_ = (1 - sn);
				return pow(sw_, (2. + 3.*lamda) / lamda);
			}
			double	k_n(int io, double sn)	{
				double sn_;
				double lamda=2;
				sn_ = sn;
				return sn_*sn_*(1 - pow((1 - sn_), (2 + lamda) / lamda));
			}
			double	dk_w(int io, double s){
				double sw_;
				double lamda=2.;
				double denom;
				sw_ = (1 - s) ;
				return -(2. + 3.*lamda) / lamda * pow(sw_, (2. + 3.*lamda) / lamda - 1.);
			}
			double	dk_n(int io, double s)	{
				double sn_=s;
				double lamda=2.;
				return 2.*sn_ * (1 - pow((1 - sn_), (2 + lamda) / lamda)) + sn_*sn_*((2 + lamda) / lamda) * 2 * pow(1. - sn_, 2 / lamda);
			}
			double	Lamda_n(int io, double s){
				double k = k_n(io, s);
				return k / mu_n;
			}
			double	Lamda_w(int io, double s){
				double k = k_w(io, s);
				return k / mu_w;
			}
			double	Lamda(int io, double s){
				double t1;	double t2;
				t1 = Lamda_n(io, s);
				t2 = Lamda_w(io, s);
				return t1 + t2;
			}
			double Lamdad_n(int io, double s){
				double k = dk_n(io, s);
				return k / mu_n;
			}
			double Lamdad_w(int io, double s){
				double k = dk_w(io, s);
				return k / mu_w;
			}
			double	Lamdad(int io, double s){
				double t1;	double t2;
				t1 = Lamdad_n(io, s);
				t2 = Lamdad_w(io, s);
				return t1 + t2;
			}
			double	fn(int io, double s) {
				double t1; double t2;
				t1 = Lamda(io, s);
				t2 = Lamda_n(io, s);
				return t2 / t1;
			}
			double	dfn(int io, double s) {
				double lamda_ = Lamda(io, s);
				double lamdad_ = Lamdad(io, s);
				double lamda_n = Lamda_n(io, s);
				double lamdad_n = Lamdad_n(io, s);

				return lamdad_n / lamda_ - lamda_n *lamdad_ / lamda_ / lamda_;
			}
			double	fw(int io, double s) {
				double t1; double t2;
				t1 = Lamda(io, s);
				t2 = Lamda_w(io, s);
				return t2 / t1;
			}
			int	boundary_indicator_t(FVector_double& p)	{
				int ret = 1;
				// ret=1. normal. ret=0. dirichlet.
				double x = p[0];	double y = p[1];
				if (x == RX[1][0])
					ret = 0;
			
				return ret;
			}
			int	boundary_indicator_w(FVector_double& p)	{
				int ret = 1;
			
				return ret;
			}
			int	boundary_indicator_n(FVector_double& p)	{
				int ret = 1;
				// ret=1. normal. ret=0. dirichlet.
				double x = p[0];	double y = p[1];
				if ((x == RX[0][0]) || (x == RX[1][0]))
					ret = 0;
	
				return ret;
			}
			double	flux_w(FVector_double& p){
				double x = p[0], y = p[1];
				double rt = 0.;
			
				return rt;
			}
			double	flux_n(FVector_double& p){
				double x = p[0], y = p[1];
				double rt = 0.;
			
				return rt;
			}
			double	flux_t(FVector_double& p){
				double rt=0.;
			
				return rt;
			}
			double	K_p_(int io) {
				double rt = 0;
				if (io == CV.IN)
					rt = mum;
				else
					rt = mup;
				return rt;
			}
			double	K_p_(FVector_double & p) {
				double x = p[0], y = p[1];
				double rt = 0;
				if (Interface(p) <= 0)
					rt = mum;
				else
					rt = mup;
				return rt;
			}
			double	Phi_(int io) {
				double rt = 0;
				if (io == CV.IN)
					rt = 1.;
				else
					rt = 1.;
				return rt;
			}
			double	Phi_(FVector_double & p) {
				double x = p[0], y = p[1];
				double rt = 0;
				if (Interface(p) <= 0)
					rt = 1.;
				else
					rt = 1.;
				return rt;
			}
			double	Initial_Val(FVector_double & p) {
				double x = p[0], y = p[1];

				if (Interface(p) <= 0) {
					return 1.;
				}
				else {
					return 0.;
				}

			}
			double	dirichlet_t(FVector_double& p) {
				double x = p[0], y = p[1];
				double rt = 0; 
				return 0.;
			}
			double	dirichlet_w(FVector_double& p) {
				double x = p[0], y = p[1];
				double rt = 0; 
				return 0.;
			}
			double	dirichlet_n(FVector_double& p) {
				double x = p[0], y = p[1];
				double rt = 0;
				if (x == RX[0][1]) 
					rt = 1.;
				return rt;
			}
			double pc(int io, double sn){
				double pd;
				double lamda=2;
				double sw_;
				if (sn < 0){
					if (abs(sn) < pow(10., -16.))
						sn = 0;
					else
						cout << "FEM Problem dpc: sn<0: " << sn << endl;
				}
				if (io == CV.IN){
					pd = 1/sqrt(mum);
					lamda = 2.;
					sw_ = (1 - sn);
				}
				else{
					pd = 1 / sqrt(mup);
					lamda = 2.;
					sw_ = (1 - sn);
				}
				return pd*pow(sw_+0.0001, -1 / lamda);
			}
			double pc(FVector_double& p, double sn){
				double pd;
				double lamda;
				double sw_; 
				if (sn < 0){
					if (abs(sn) < pow(10., -16.))
						sn = 0;
					else
						cout << "FEM Problem dpc: sn<0: " << sn << endl;
				}
				if (Interface(p) <= 0) {
					pd = 1 / sqrt(mum);
					lamda = 2.;
					sw_ = (1 - sn);
				}
				else{
					pd = 1 / sqrt(mup);
					lamda = 2.;
					sw_ = (1 - sn);
				}
				return pd*pow(sw_, -1 / lamda);
			}
			double pc_in_inv(double s) {
				double left_ = 0.;
				double right_ = 0.99;
				double mid_ = 0.;
				double f_left_ = pc(CV.IN, left_) - s;
				double f_right_ = pc(CV.IN, right_) - s;
				double tol = pow(10., -10.);
				double res = 1.;

				while (abs(res) > tol){
					mid_ = (left_ + right_) / 2.;
					res = pc(CV.IN, mid_) - s;

					if (res <= 0){
						left_ = mid_;
					}
					else{
						right_ = mid_;
					}
				}
				return mid_;
			}
			double dpc(int io, double sn){
				double pd;
				double lamda;
				double sw_; 
				if (sn < 0){
					if (abs(sn) < pow(10., -16.))
						sn = 0.;
					else
						cout << "FEM Problem dpc: sn<0: " << sn << endl;
				}
				if (io == CV.IN){ 
					pd = 1 / sqrt(mum);
					lamda = 2.;
					sw_ = (1 - sn);
				}
				else{
					pd = 1 / sqrt(mup);
					lamda = 2.;
					sw_ = (1 - sn);
				}
				return -(-1 / lamda) * pd*pow(sw_ + 0.0001, -1 / lamda - 1);
			}
			double dpc(FVector_double& p, double sn){
				double pd;
				double lamda;
				double sw_; 
				if (sn < 0){
					if (abs(sn) < pow(10., -16.))
						sn = 0.;
					else
						cout << "FEM Problem dpc: sn<0: " << sn << endl;
				}
				if (Interface(p) <= 0) {
					pd = 1 / sqrt(mum);
					lamda = 2.;
					sw_ = (1 - sn);
				}
				else{
					pd = 1 / sqrt(mup);
					lamda = 2.;
					sw_ = (1 - sn);
				}
				return -(-1 / lamda) * pd*pow(sw_ + 0.0001, -1 / lamda - 1);
			}
			double		gamma(int io, double s)
			{
				double rt = 0.;
				double fn;
				double lamba_w;
				double dpc;
				if (s < 0){
					if (abs(s) < pow(10., -16.))
						s = 0.;
					else
						cout << "FEM Problem gamma: sn<0: " << s << endl;
				}
				else{
					fn = _problem->fn(io, s);
					lamba_w = _problem->Lamda_w(io, s);
					dpc = _problem->dpc(io, s);
					rt = fn*lamba_w*dpc;
				}
				return rt;
			}
			double		dgamma(int io, double s)
			{
				return 0;
			}

			double ddpc(int io, double sn){
				double pd;
				double lamda; 
				double sw_;
				if (sn<0)
					sn = 0;
				if (io == CV.IN){
					pd = 1 / sqrt(mum);
					lamda = 2.;
					sw_ = (1 - sn);
				}
				else{
					pd = 1 / sqrt(mup);
					lamda = 2.;
					sw_ = (1 - sn);
				}
				return (-1 / lamda)*(-1 / lamda - 1) *pd*pow(sw_, -1 / lamda - 2);
			}
			double P_Jump(FVector_double & p){
				// Jump of Sw at t=0
				return 0.;
			}
			double Flux_Jump(FVector_double & p, FVector_double & vN){
				// Jump of Sw at t=0
				return 0.;
			}
		};
	};
	class HYPERBOLIC {
	public:
		 
		class LINEAR_ADVECTION_1D : public FEM_PROBLEM {
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 1;
				RX = __.RX.make(__.dim, 2).setAll(0., 1.);
				ini_time = 0.;
				ter_time = 3.;
				a = 1.;
			}

			double	P(FVector_double & p) {
				double x = p[0];
				return sin(2.*CV.PI*x);
			}
			   
		};

		class LINEAR_ADVECTION_2D : public FEM_PROBLEM {
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);
				ini_time = 0.;
				ter_time = 1.;
			}

			double Interface0(FVector_double & p)
			{
				double x = p[0];
				double y = p[1];
				double r = 0.4;
				double value = pow(r, 2) - pow(x, 2.) - pow(y, 2.);

				if (value >= 0)
				{
					return sqrt(value);
				}
				else
				{
					return (-1)*sqrt(-value);
				}
			}

			void V(FVector_double& p, FVector_double& vV)
			{
				vV[0] = p[0]; vV[1] = p[1];
			}


		};
	};
	class IMPERFECT_CONTACT {
	public:
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		//============================================================================
		//								IMPERFECT_CONTACT
		//============================================================================
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		class STEADY_STATE_GH : public FEM_PROBLEM {
		public:
			void		initialize(FEM_VARIABLES::ENTIRE& __) {
				__.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);
				mup = 2.;
				mum = 1; 
			}
			
			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1];
			//	return 0.11-x; 
			//	return y-3*x*(x-0.3)*(x-0.5)-0.38;
			//	return 0.12222-x-0.1*y;
				return (x-5)*(x-5)+y*y-5.1*5.1;
			}
			
			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);
				return 0;
			}
			double	coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.
				if (Interface(p) < 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}
			int	boundary_indicator_t(FVector_double& p)	{
				int ret = 1;
				// ret=1. normal. ret=0. dirichlet.
				double x = p[0];	double y = p[1];
				if (x == RX[1][0])
					ret = 0;
			
				return ret;
			}
		};
		class UNSTEADY_STATE_GH_HEAT_FLOW_FROM_LEFT : public FEM_PROBLEM {
		public:
			void		initialize(FEM_VARIABLES::ENTIRE& __) {
				__.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);
				mup = 1.;
				mum = 1; 
				alpha=1.;
			}
			
			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1];
			//	return 0.11-x; 
			//	return y-3*x*(x-0.3)*(x-0.5)-0.38;
			//	return 0.12222-x-0.1*y;
				return (x)*(x)+y*y-0.4*0.4;
			}
			
			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);
				return 0;
			}
			double	coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.
				if (Interface(p) < 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}
			int	boundary_indicator_t(FVector_double& p)	{
				int ret = 1;
				// ret=1. normal. ret=0. dirichlet.
				double x = p[0];	double y = p[1];
				if (x == RX[1][0])
					ret = 0;
			
				return ret;
			}
		};
		class STEADY_STATE_GH_ANALYTIC_CIRCLE : public FEM_PROBLEM {
		public:
			void		initialize(FEM_VARIABLES::ENTIRE& __) {
				__.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);
				mup = 1.;
				mum = 1; 
				alpha=1.;
				r0=0.4;
			}
			
			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1];
			//	return 0.11-x; 
			//	return y-3*x*(x-0.3)*(x-0.5)-0.38;
			//	return 0.12222-x-0.1*y;
				return (x)*(x)+y*y-r0*r0;
			//	return -10;
			}
			int		IO(FVector_double& p) {
				if (Interface(p) < 0.0)	return CV.IN;
				else return CV.OUT;
				return 0;
			}
			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);
				return 0;
			}
			double	coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.
				if (Interface(p) < 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}
			double	P(FVector_double& p, FVector_double& ps) {
				double x = p[0], y = p[1], d;
				double q; 
				static FVector_double mus(2) ; 
				coef_mu(p, mus);// 두 값을 호출해서 알맞게 돌려준다.
			
				q = (x*x + y*y) / 2.0;
				ps.setAll(q / mum - r0*alpha + (1. / mup - 1. / mum)*r0*r0 / 2., q / mup); 
				
				return 0.;
			}
			double	P(FVector_double& p) {
				static FVector_double ps(2);
				P(p, ps);																	// 두 값을 호출해서 알맞게 돌려준다.
				if (Interface(p) >= 0.0)	return ps[1];
				return ps[0];
			}
			void	DP(FVector_double& p, FMatrix_double& dps) {
				double x = p[0], y = p[1];
				double d, dxP, dyP, L1, L2, L3, L4;
				static FVector_double mus(2), dq(dim);
				d = gap;
				coef_mu(p, mus);
				dps.setAll(x / mum, y / mum, x / mup, y / mup);
			}
			void	DP(FVector_double& p, FVector_double& dp) {
				static FMatrix_double dps(2, 2);
				DP(p, dps);

				if (Interface(p)<0.0)	 dp = dps[0];
				else	dp = dps[1];
			}
			void	V(FVector_double& p, FVector_double& U_real) {
				double x=p[0];
				double y=p[1]; 
				U_real.setAll(-x,-y);
			}
			double	Flux_Jump(FVector_double& p, FVector_double& vN) {
				return 0.;
			}			
			double	P_Jump(FVector_double& p) { 
				double x, y;
				x = p[0];
				y = p[1];
				static FVector_double ps(2);
				P(p, ps);

				return  0.;
			}
			double	F(FVector_double& p, FVector_double& fs) {
				double x = p[0], y = p[1], d; 
				static FVector_double mus(2) ;
				d = gap;
				coef_mu(p, mus);
				fs.setAll(-2.0, -2.0);
				return 0;
			}
			double	F(FVector_double& p) {
				static FVector_double fs(2);
				F(p, fs);
				if (Interface(p)<0.0)	 return fs[0];
				else	return fs[1];
			}
		};
		class STEADY_STATE_GH_ANALYTIC_ELLIPSE: public FEM_PROBLEM {
		public:
			void	initialize(FEM_VARIABLES::ENTIRE& __) {
				double A, B;
				dim = __.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);
 
				VAR.nData[0] = 30; VAR.nData[1] = 60;
			//	cout << "r0=" << r0 << endl; 
				r0=0.78;

				A2=1.1;
				B2=1.1; 
				//cout << "r0=" << r0 << endl; 
			//	Input("mu_inside", mum); 
				
				// case 1.
				a=1.;
				mum=2;
				mup=1.; 

			} 
			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1];
				double r;
				double L1, L2, L3, L4, L5, L6, L7, L8, L9;
				double theta = MATH::slope_to_radian(x, y);
				 
				// peanut-shaped
				r = sqrt(x*x / A2 + y*y / B2) - r0;
				return r;
			}  
			int		IO(FVector_double& p) {
				if (Interface(p) < 0.0)	return CV.IN;
				else return CV.OUT;
				return 0;
			}

			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);														// (Interior, middle, Exterior)

				return 0;
			}

			double	coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}

			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (Interface(p)<0.0)	return mus[0];
				return mus[1];
			}

			double	value_varAlpha(FVector_double& p) {
				double x = p[0], y = p[1];
				double value, d, tempx, tempy;
				static FVector_double vMus(2);
				
				value =  sqrt(x*x / (A2*A2) + y*y / (B2*B2));
				value = a / value;
				return value;
			} 

			double	P(FVector_double& p, FVector_double& ps) {
				double x = p[0], y = p[1], d;
				double q;
				double L1, L2, L3, L4;
				static FVector_double mus(2), dq(dim);
				d = gap;
				coef_mu(p, mus);// 두 값을 호출해서 알맞게 돌려준다.

				//the solutions with "Peanut" shape interface with variable alpha				
				q = (x*x / A2 + y*y / B2) / 2.0;
				ps.setAll(q / mum  - a + (1. / mup - 1. / mum)*r0*r0 / 2. ,  q / mup);

				return 0;
			}
			double	P_Jump(FVector_double& p) { 
				double x, y;
				x = p[0];
				y = p[1];
				return 0.;
			}
			double	Flux_Jump(FVector_double& p, FVector_double& vN) {
				double x=p[0];
				double y=p[1];
				return 0.;
			}
			double	P(FVector_double& p) {
				static FVector_double ps(2);
				P(p, ps);																	// 두 값을 호출해서 알맞게 돌려준다.
				if (Interface(p) >= 0.0)	return ps[1];
				return ps[0];
			}

			void	DP(FVector_double& p, FMatrix_double& dps) {
				double x = p[0], y = p[1];
				double d, dxP, dyP, L1, L2, L3, L4;
				static FVector_double mus(2), dq(dim);
				d = gap;
				coef_mu(p, mus);
				 
				// case1.
				dps.setAll(x / A2 / mum, y / B2 / mum, x / A2 / mup, y / B2 / mup);
			}

			void	DP(FVector_double& p, FVector_double& dp) {
				static FMatrix_double dps(2, 2);
				DP(p, dps);

				if (Interface(p)<0.0)	 dp = dps[0];
				else	dp = dps[1];
			}
			void	V(FVector_double& p, FVector_double& dV) {
				double x = p[0], y = p[1];
				double d, dxP, dyP, L1, L2, L3, L4;
				static FVector_double mus(2), dq(dim);
				d = gap;
				coef_mu(p, mus); 
				dV.setAll(-x / A2 , -y / B2);
			}
			double	F(FVector_double& p, FVector_double& fs) {
				double x = p[0], y = p[1];
				double fx, fy, d, L1, L2, L3, L4, dxL1, dyL1, dxL2, dyL2, dxL3, dyL3, dxL4, dyL4;
				static FVector_double mus(2), dq(dim);
				d = gap;
				coef_mu(p, mus);

				//case 1
				fx = 1.0 / A2 + 1.0 / B2;
				fy = fx;
				fs.setAll(-1.0* fx, -1.0* fy);
				
				return 0;
			}
			double	F(FVector_double& p) {
				static FVector_double fs(2);
				F(p, fs);
				if (Interface(p)<0.0)	 return fs[0];
				else	return fs[1];
			}
		};
		class UNSTEADY_STATE_GH_HEAT_FLOW_FROM_ABOVE : public FEM_PROBLEM {
		public:
			void		initialize(FEM_VARIABLES::ENTIRE& __) {
				__.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(-1., -1., 1., 1.);
				mup = 1.;
				mum = 1; 
				alpha=1.;
			}
			
			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1];
			//	return 0.11-x; 
			//	return y-3*x*(x-0.3)*(x-0.5)-0.38;
			//	return 0.12222-x-0.1*y;
				return (x)*(x)+y*y-0.6*0.6;
			}
			
			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);
				return 0;
			}
			double	coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.
				if (Interface(p) < 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}
			int	boundary_indicator_t(FVector_double& p)	{
				int ret = 1;
				// ret=1. normal. ret=0. dirichlet.
				double x = p[0];	double y = p[1];
				if (x == RX[1][0])
					ret = 0;
			
				return ret;
			}
			double	F(FVector_double& p, FVector_double& fs) {
				static FVector_double mus(2);
				double x = p[0], y = p[1];
				double r2 = x*x + y*y;
				double r = sqrt(r2);
				
				fs.setAll(1./(r+0.1),1./(r+0.1));
				return 1./(r+0.1);
			}
			double	F(FVector_double& p) {
				static FVector_double fs(2);
				F(p, fs);
				if (Interface(p) < 0) {
					return fs[0];
				}
				else {
					return fs[1];
				}
			}
		};
	};
	class SEMI_CONDUCTOR {
	public:
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		//============================================================================
		//								IMPERFECT_CONTACT
		//============================================================================
		//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
		class DIODE : public FEM_PROBLEM {
		public:
			void		initialize(FEM_VARIABLES::ENTIRE& __) {
				__.dim = 2;
				RX = __.RX.make(__.dim, __.dim).setAll(0., 0., 0.0001, 0.0001);

				eps_=11.8;
				q=1.602*pow(10., -19.);
				ni=1.5*pow(10., 10.);
				ni_hat=2.4030*pow(10., -9.);	// ni_hat = q*ni;
				Vth=0.02585; 

				Vp=0.;
				Vm=8.;
				Cp=-3.5*pow(10., 15.);
				Cm=pow(10., 18.);

				Cp_hat=-5.6070*pow(10., -4.);
				Cm_hat=0.1602;

				mu_n=800.;
				mu_p=400.;
				Dn=mu_n*Vth;
				Dp=mu_p*Vth;

				Tau_n=4.0*pow(10., -4.);
				Tau_p=4.0*pow(10., -4.);

				Cn_over_q_square = 1.0910*pow(10., 7.);
				Cp_over_q_square = 3.8575*pow(10., 6.);

				En_crit=1.231*pow(10., 6.);
				Ep_crit=2.036*pow(10., 6.);
				alpha_n=7.03*pow(10., 5.);
				alpha_p=1.582 *pow(10., 6.);
			}
			double	Interface(FVector_double& p) {
				double x = p[0], y = p[1];
			//	return 0.11-x;
				return (x-5)*(x-5)+y*y-5.1*5.1;
			}
			double		DOPING(FVector_double& p) {
				double x = p[0], y = p[1];

				if ( sqrt(x*x+y*y) < 0.4*0.0001 ){
					return Cm;
				}
				else{
					return Cp;
				}
			
			}
			double		DOPING_HAT(FVector_double& p) {
				double x = p[0], y = p[1];

				if ( sqrt(x*x+y*y)<0.4*0.0001 ){
					return Cm_hat;
				}
				else{
					return Cp_hat;
				}
			
			}			
			int	boundary_indicator (FVector_double& p)	{
				int ret = 1;
				// ret=1. normal. ret=0. dirichlet.
				double x = p[0];	double y = p[1];
				if ( (y == 0) && (x>=0) && (x<=0.25*0.0001)   ){
					ret = 0;
				}
				if ( (y == 0.0001) ){
					ret = 0;
				}
				return ret;
			}
			double		EP				(FVector_double& p) {
				double x=p[0], y=p[1];
				if (y==0){
					return Vm/Vth;
				}
				if (y==0.0001){
					return Vp/Vth;
				}
				return 0;
			}
			double		PN				(FVector_double& p) {
				double x=p[0], y=p[1];
				double n;
				double V=EP(p);
				double psi_hat=V;

				if (y==0){
					n = (sqrt(Cm*Cm+4*ni*ni)+Cm)/2.;
					return psi_hat-log(n/ni);
				}
				if (y==0.0001){
					n = (sqrt(Cp*Cp+4*ni*ni)+Cp)/2.;
					return psi_hat-log(n/ni);
				}
					
				return 0; 
			}
			double		PP				(FVector_double& p) {
				double x=p[0], y=p[1];
				double p_;
				double V=EP(p);
				double psi_hat=V;

				if (y==0){
					p_ = (sqrt(Cm*Cm+4*ni*ni)-Cm)/2.;
					return psi_hat+log(p_/ni);
				}
				if (y==0.0001){
					p_ = (sqrt(Cp*Cp+4*ni*ni)-Cp)/2.;
					return psi_hat+log(p_/ni);
				}
				return 0; 
			}
			double		N_HAT			(FVector_double& p) {
				double x=p[0], y=p[1];
				double vEP_;
				double vPN_;
				double vPP_;
			//	n_hat = ni_hat * exp(vEP[pj]-vPN[pj]);
			//	p_hat = ni_hat * exp(vPP[pj]-vEP[pj]);
				if (y==0){
					vEP_=EP(p);
					vPN_=PN(p);
					vPP_=PP(p);
					return ni_hat * exp(vEP_-vPN_);
				//	return 0.160200000000000;	//n*q
				}
				if (y==0.0001){
					vEP_=EP(p);
					vPN_=PN(p);
					vPP_=PP(p);
					return ni_hat * exp(vEP_-vPN_);
				//	return  1.029857715000000*pow(10., -14.);	//n*q
				}
				return 0; 
			}
			double		P_HAT			(FVector_double& p) {
				double x=p[0], y=p[1];
				double vEP_;
				double vPN_;
				double vPP_;
				if (y==0){
					vEP_=EP(p);
					vPN_=PN(p);
					vPP_=PP(p);
					return ni_hat * exp(vPP_-vEP_);
				//	return 4.10112*pow(10., -17.);	//p*q
				}
				if (y==0.0001){
					vEP_=EP(p);
					vPN_=PN(p);
					vPP_=PP(p);
					return ni_hat * exp(vPP_-vEP_);
				//	return  5.607000000102986*pow(10., -4.);	//p*q
				}
				return 0;
			}
			double	coef_mu(FVector_double& p, FVector_double& mus) {
				double x = p[0], y = p[1];
				mus.setAll(mum, mup);
				return 0;
			}
			double	coef_mu(FVector_double& p, int io) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.

				if (io == CV.IN) return mus[0];
				return mus[1];
			}
			double	coef_mu(FVector_double& p) {
				static FVector_double mus(2);
				coef_mu(p, mus);															// 두 값을 호출해서 알맞게 돌려준다.
				if (Interface(p) < 0) {
					return mus[0];
				}
				else {
					return mus[1];
				}
			}
			int	boundary_indicator_t(FVector_double& p)	{
				int ret = 1;
				// ret=1. normal. ret=0. dirichlet.
				double x = p[0];	double y = p[1];
				if (x == RX[1][0])
					ret = 0;
			
				return ret;
			}
		};
	};
	/*//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
	//============================================================================
	//                            IIM_ELLIPTIC_CONST
	//============================================================================
	//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
	class IIM_ELLIPTIC_CONST {
	public:
		static double	INTERFACE_ELT(FVector_double& p) {	// 내부에서 음수의 값을 가지도록 한다.
			double r = p.norm2();

			switch(PV.interfaceType) {
				case D_CIRCLE;
					return (r - PV.r0);
				default:
					Pause("Default Interface");
					exit(1);
			}
		}

		double MY_BETAS(FVector_double& p) {
			double x=p[0], y=p[1];
			//double r2 = x*x + y*y;
			//double r = sqrt(r2);
			
			if(MY_INTERFACE(p)<=0) return _betam;
			return _betap;
		}

		void MY_BETAS(FVector_double& p, FVector_double& b) {
			double x=p[0], y=p[1];
			//double r2 = x*x + y*y;
			//double r = sqrt(r2);
			
			b[0] = _betam;
			b[1] = _betap;
		}

		double	MY_P(FVector_double& p) {
			double x=p[0], y=p[1];
			double r = sqrt(x*x + y*y);

			if(r <= _r0) {
				return x*x + y*y*y;		// Omega-
			} else {
				return y*y*y;		// Omega+
			} 
		}

		double	MY_P_JUMP(FVector_double& p) {
			double x = p[0], y = p[1];
			//return x - _r0;
			//return 100.;
			return x*x;
		}

		double	MY_F(FVector_double& p) {
			double x=p[0], y=p[1];
			double r = sqrt(x*x + y*y);
			static FVector_double betas(2);

			MY_BETAS(p, betas);
			if(r <= _r0) {
				return (-2 - 6*y)*betas[0];
			} else {
				return (-6*y)*betas[1];
			}
		}

		void	MY_P_GRAD(FVector_double& p, FVector_double& u1, FVector_double& u2) {	// u1: Omega-, u2: Omega+, 
			double x=p[0], y=p[1];
			double r = sqrt(x*x + y*y);

			u1.setAll(2*x, 3*y*y);
			u2.setAll(0., 3*y*y);
		}

		void	MY_P_FLUX_JUMP(FVector_double& p, FVector_double& vJump) {	// 모든 점에서 flux 점을 값을 준다. 하지만 실제로는 interface에서만 정확한 값을 가지므로 cp에서 구해서 근사해야 한다.
			double x=p[0], y=p[1];
			static FVector_double betas(2);
			static FVector_double vGradm(_dim);
			static FVector_double vGradp(_dim);

			MY_BETAS(p, betas);
			MY_P_GRAD(p, vGradm, vGradp);
			vJump.sum(betas[0], vGradm, -betas[1], vGradp);		// jump는 항상 Omega- - Omega+으로 취한다. 
		}
	};
	*/
};
#endif