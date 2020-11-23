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
	//==========================================================
	//         Main  : Without MATLAB solver                                  
	//==========================================================
	FEM_CLASS fem;

	fem.__.nLayer = 6;
	double Target_Time = 8;
	int draw_count = 16;
	int it;
	int nnT = fem._.nnT;	int i;	int j;	double res = 1.;
	int npT = fem._.npT;
	int nvT = fem._.nvT;
	int neT = fem._.neT;


	//double dt=(fem._.dx)*(fem._.dx);
	double t;
	int nT = 2 * pow(4., fem.__.nLayer - 3); //draw_count = nT;
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
		fem.INTERFACE_ELEMENT_EDGE_UPDATE(it, 1);

		fem.INTERFACE_ELEMENT_VLEVELSET_ALL();
		fem.INTERFACE_BASIS_UPDATE();

		fem.MAKE_PRIMITIVE_MASS_MATRIX(t);
		SOLVER::PCG(fem._.mA, fem._.vCP, fem._.vF, pow(10., -9.));
		fem.VEL_RECOV(t);

		if (it%draw_count == 0) {
			fem.draw_PHI("PHI", it / draw_count);
			//fem.draw_levelset("Level_set", it /draw_count);
			fem.pressure_standard_IIM("IIM_PRESSURE", it / draw_count);
			fem.draw_VEL("VEL", it / draw_count);

		}


		//fem.draw_PHI("PHI", it);

	}


	//==========================================================
	//         Main  : With MATLAB solver                                  
	//==========================================================
	
	//FEM_CLASS fem;
	////cout << "LeveL: ";
	////cin >> fem.__.nLayer;
	//fem.__.nLayer=7;
	//fem.SETALL();

	//int it;
	//int nnT = fem._.nnT;	int i;	int j;	double res = 1.;
	//int npT = fem._.npT;
	//int nvT = fem._.nvT;
	//int neT = fem._.neT;

	//double Target_Time = 0;
	////double dt=(fem._.dx)*(fem._.dx);
	//double t;
	//int nT = 2 * (fem.__.nLayer)*(fem.__.nLayer);
	//double dt = Target_Time / double(nT);

	//cout << "Number of Time Iteration: " << nT << endl;

	//FVector_double pressure(npT);
	//FVector_double vel(nvT);
	//FVector_double level_set_(neT);


	//char fileName[128];
	//FILE* fp;

	//int sys_count = 0;
	//int status_;

	//int draw_count = 10000;

	//sys_count++;
	//status_ = -1;
	//_sleep(500);
	//sprintf(fileName, "%s.txt", "status_vis");
	//fp = fopen(fileName, "w");
	//fprintf(fp, "%d", status_);
	//fclose(fp);

	//STANDARD::repeat('\b', 80);
	//printf("Making Matrix: ");


	//fem.MAKE_PRIMITIVE_MASS_MATRIX(0.);
	//STANDARD::repeat('\b', 80);
	//printf("Mat file gen:      ");

	//fem.solve_in_matlab(fem._.mA, fem._.vF, "sys", sys_count);
	//_sleep(500);
	//status_ = 1;
	//sprintf(fileName, "%s.txt", "status_vis");
	//fp = fopen(fileName, "w");
	//fprintf(fp, "%d", status_);
	//fclose(fp);

	//STANDARD::repeat('\b', 80);
	//printf("Input solution:          ");

	//status_ = -1;
	////	while (status_ < 10){
	////		_sleep(500);
	////		sprintf(fileName, "%s.txt", "status_mat");
	////		ifstream input(fileName, ios::in);
	////		for (i = 0; i < 1; i++) {
	////			input >> status_;
	////		}
	////		if (status_ == 2 || status_ == 3) status_ = 100;
	////	}
	//status_ = 2;
	//sprintf(fileName, "%s.txt", "status_vis");
	//fp = fopen(fileName, "w");
	//fprintf(fp, "%d", status_);
	//fclose(fp);

	////	fem.readSolution(fem._, sys_count);

	//SOLVER::PCG(fem._.mA, fem._.vCP, fem._.vF, pow(10., -9.));
	//fem.VEL_RECOV(0.);


	//
	//for (it = 1; it <= nT; it++) {
	//	cout << "it: " << it << endl;
	//	t = dt*it;

	//	fem.LEVEL_SET_UPDATE(dt);

	//	fem.find_Control_Points(it, draw_count);
	//	fem.FIND_INTERFACE_POINTS(it, draw_count);
	//	fem.INTERFACE_ELEMENT_EDGE_UPDATE(it, draw_count);
	//	fem.INTERFACE_ELEMENT_VLEVELSET_ALL();
	//	fem.INTERFACE_BASIS_UPDATE();

	//	sys_count++;
	//	status_ = -1;
	//	_sleep(500);
	//	sprintf(fileName, "%s.txt", "status_vis");
	//	fp = fopen(fileName, "w");
	//	fprintf(fp, "%d", status_);
	//	fclose(fp);

	//	STANDARD::repeat('\b', 80);
	//	printf("Making Matrix: ");

	//	fem.MAKE_PRIMITIVE_MASS_MATRIX(t);

	//	STANDARD::repeat('\b', 80);
	//	printf("Mat file gen:      ");

	//	fem.solve_in_matlab(fem._.mA, fem._.vF, "sys", sys_count);
	//	_sleep(500);
	//	status_ = 1;
	//	sprintf(fileName, "%s.txt", "status_vis");
	//	fp = fopen(fileName, "w");
	//	fprintf(fp, "%d", status_);
	//	fclose(fp);

	//	STANDARD::repeat('\b', 80);
	//	printf("Input solution:          ");

	//	status_ = -1;
	//	while (status_ < 10) {
	//		_sleep(500);
	//		sprintf(fileName, "%s.txt", "status_mat");
	//		ifstream input(fileName, ios::in);
	//		for (i = 0; i < 1; i++) {
	//			input >> status_;
	//		}
	//		if (status_ == 2 || status_ == 3) status_ = 100;
	//	}
	//	status_ = 2;
	//	sprintf(fileName, "%s.txt", "status_vis");
	//	fp = fopen(fileName, "w");
	//	fprintf(fp, "%d", status_);
	//	fclose(fp);

	//	fem.readSolution(fem._, sys_count);
	//	//	fem.MAKE_PRIMITIVE_MASS_MATRIX(t);
	//	SOLVER::PCG(fem._.mA, fem._.vCP, fem._.vF, pow(10., -9.));
	//	fem.VEL_RECOV(t);

	//	if (it%draw_count == 0) {
	//		fem.draw_PHI("PHI", it / draw_count);
	//		fem.pressure_standard_IIM("IIM_PRESSURE", it / draw_count);
	//		//	fem.draw_VEL("VEL", it /draw_count);
	//		//	cout << "T: " << it*dt << endl;
	//	}

	//}
	//
	//double pressure_L2;
	//double pressure_H1;
	//double Vel_L2;
	//double Vel_Hdiv;

	//int nOption = FEM::IIFEM::D_IIM + FEM::IIFEM::D_BUBBLE;
	//fem.IIM_EG_pressure(fem._, fem.__, pressure_L2, pressure_H1, nOption, Target_Time);
	////fem.Error_Vector(fem._, fem.__, fem.__.intOrd, Vel_L2, Vel_Hdiv, Target_Time);

	//cout << "Pressure L2 " << pressure_L2 << "Pressure H1: " << pressure_H1 << endl;
	////cout << "Velocity L2 " << Vel_L2 << "Velocity Hdiv: " << Vel_Hdiv << endl;










	cout << "END OF LINE " << endl;
	system("pause");
}