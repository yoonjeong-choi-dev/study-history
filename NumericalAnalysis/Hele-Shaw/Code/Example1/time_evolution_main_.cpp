#include "package_2015.h"
#include <fstream>
#include "FEM_CLASS_.h"
#include "time.h"
//�ƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢ�
//============================================================================
//                                  Main                                  
//============================================================================
//�ƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢ�
void MAIN() {
	FEM_CLASS fem;

	fem.__.nLayer = 6;
	double Target_Time = 10;
	int draw_count = 16;
	int it;
	int nnT = fem._.nnT;	int i;	int j;	double res = 1.;
	int npT = fem._.npT;
	int nvT = fem._.nvT;
	int neT = fem._.neT;


	//double dt=(fem._.dx)*(fem._.dx);
	double t;
	int nT = 4*pow(4., fem.__.nLayer - 3); //draw_count = nT;
	double dt = Target_Time / double(nT);

	cout << "Number of Time Iteration: " << nT << endl;
	cout << " dt : " << dt << endl;

	FVector_double pressure(npT);
	FVector_double vel(nvT);
	FVector_double level_set_(neT);


	fem.SETALL();
	fem.MAKE_PRIMITIVE_MASS_MATRIX(0.);
	SOLVER::PCG(fem._.mA, fem._.vCP, fem._.vF);
	fem.VEL_RECOV(0.);

	for (it = 1; it <= nT; it++) {
		cout << "it: " << it << endl;
		t = dt*it;

		fem.LEVEL_SET_UPDATE(dt); //fem.draw_levelset("Level_set",it);

		fem.find_Control_Points(it, 1);
		fem.FIND_INTERFACE_POINTS(it, 1);
		fem.INTERFACE_ELEMENT_EDGE_UPDATE_YJ(it, 1);

		fem.INTERFACE_ELEMENT_VLEVELSET_ALL();
		fem.INTERFACE_BASIS_UPDATE();

		fem.MAKE_PRIMITIVE_MASS_MATRIX(t);
		SOLVER::PCG(fem._.mA, fem._.vCP, fem._.vF, pow(10., -9.));
		fem.VEL_RECOV(t);

		if (it%draw_count == 0) {
			fem.draw_PHI("PHI", it /draw_count);
			//fem.draw_levelset("Level_set", it /draw_count);
			fem.pressure_standard_IIM("IIM_PRESSURE", it/draw_count);
			fem.draw_VEL("VEL", it /draw_count);	

		}


		//fem.draw_PHI("PHI", it);

	}
}