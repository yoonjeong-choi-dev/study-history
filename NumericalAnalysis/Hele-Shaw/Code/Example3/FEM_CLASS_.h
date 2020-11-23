 
//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
//============================================================================
//                               CLASS의 선언
//============================================================================
//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
//☞ 이곳에 새롭게 사용할 CLASS를 선언한다. 
//☞ 자신이 새롭게 만든 CLASS는 기존 CLASS와의 혼동을 피하기 위해 "_CLASS"를 붙여서 사용한다.

class FEM_CLASS {
public://☞ 변수들을 선언한다.
	C_TIME _time;				//▷ 시간을 check 하기 위해 선언한다. ( "c_time_2008.h"에 들어 있다. )
	FEM_VARIABLES::LEVEL _;		//▷ 각각 LEVEL에서 사용할 변수 ( "fem_variables_2008.h"에 들어 있다. )
	FEM_VARIABLES::ENTIRE __;	//▷ 전체 LEVEL에서 사용할 변수 ( "fem_variables_2008.h"에 들어 있다. )

	FEM_VARIABLES::IIM iim;		//▷ immersed 변수 ( "fem_variables_2008.h"에 들어 있다. )
	FEM_VARIABLES::IIM iim_N;
	FMatrix_int drtV;
	double eps;
	double kappa;


	FVector_double vPHI;
	FVector_double voldPHI;
	//FMatrix_double vEAt;

	// For interface update
	FMatrix_int CI; // index
	FMatrix_double CP; // coordinate
	FMatrix_double IP; // interface point[node][x,y]
	FCube_double CEIP;
	FVector_double Interface_Element_Curvature; // Curvature on interface element
	int nIP;			// number of interpolation point(obtained from Projection)
	int nCI;			// number of control point(obtained from vPHI
	

public://☞ 함수들을 선언한다.
	//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
	//▩▩                        문제를 선택한다.                        ▩▩ ( 문제는 "fem_problems_2008.h"파일에 들어 있다. )
	//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
	void	SET_PROBLEM() {
		_problem = new FEM_PROBLEMS::HELE_SHAW::EXAMPLE3;				//▷ _problem이라는 변수에 문제를 등록한다.( 다른문제를 처리할 경우 _problem만 변경하면 된다. )
	//	_problem = new FEM_PROBLEMS::ELLIPTIC::P_ELEMENTARY;				//▷ _problem이라는 변수에 문제를 등록한다.( 다른문제를 처리할 경우 _problem만 변경하면 된다. )
		_problem->initialize(__);											//▷ _problem내부의 변수들을 초기화 시킨다.
		eps = 1.;
		kappa = 10.;
		
	}

	//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
	//▩▩      domain mapping을 할 때 필요한 domain basis를 등록한다.    ▩▩
	//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
	void	SET_DOMAIN_BASIS() {
		__.domain_poly_type[0] = 4;										//▷ 몇각형인지를 설정
		__.nnshape = 4;										//▷ domain basis 개수를 지정
		__.shape.domain = FEM_SHAPES::STANDARD::Q1_CONFORMING;		//▷ domain basis를 domain 포인터에 등록한다. ( basis는 "fem_shapes_2008.h"에 들어 있다. )


		// [ Interface Part ] : inteface의 부분에서 noninterface와 다른 space를 사용할 경우를 대비해서 각각 지정해 주어야 한다.
		__.domain_poly_type[1] = 3;										//▷ second grid: rectangle
		__.nnshapes[3] = 3;										//▷ interface에서 triangle에 해당하는 domain basis 개수를 지정
		__.nnshapes[4] = 4;										//▷ interface에서 rectangle에 해당하는 domain basis 개수를 지정
		__.shape.domains[3] = FEM_SHAPES::STANDARD::P1_CONFORMING;		//▷ interface triangle domain basis를 domain 포인터에 등록한다. ( basis는 "fem_shapes_2008.h"에 들어 있다. )
		__.shape.domains[4] = FEM_SHAPES::STANDARD::Q1_CONFORMING;		//▷ interface triangle domain basis를 domain 포인터에 등록한다. ( basis는 "fem_shapes_2008.h"에 들어 있다. )
	}

	//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
	//▩▩          문제를 풀 때 사용할 solution basis를 등록한다.        ▩▩
	//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
	void	SET_SOLUTION_BASIS(){
		// [ Noninterface Part ]
		__.npshape = 5;										//▷ pressure basis 개수를 지정
		__.shape.pressure = FEM_SHAPES::STANDARD::Q1_CONFORMING_EG;		//▷ pressure basis를 pressure 포인터에 등록한다. ( basis는 "fem_shapes_2008.h"에 들어 있다. )
		
		// [ Interface Part ]
		__.npiimshape = 4;
		__.shape.iim_pressure = FEM_SHAPES::STANDARD::Q1_CON_IIM;				//▷ interface의 subgrid에서 pressure 포인터 설정
		__.shape.iim_pressure_component = FEM_SHAPES::STANDARD::Q1_CON_COMPONENT;		//▷ interface의 subgrid에서 pressure component 포인터 설정

		// [Vecocity Recovery Part]
		__.nvshape = 4;
		__.shape.vector = FEM_SHAPES::MIXED::D2C2_RTB0_SIZE1;
	}

	//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
	//▩▩  적분시 사용할 점들과 그 점들에서의 basis값들을 미리 저장한다. ▩▩ 
	//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
	void	SET_PREVALUES() {
		// [ 적분 최대 허용차수를 입력받는다. ] ( 보통 3차를 입력하면 충분하며 1차를 입력해도 Linear인 경우 문제없다. )
		//Input("Input the number of Integration order", __.intOrd);
		//Input("Input the number of Integration order of error", __.intErrOrd);
		__.intOrd = __.intErrOrd = 3;	// 입력받고 싶으면 현재 구문을 막고 위 두개의 구문을 실행시킨다.

		// [ Noninterface Part ]
		__.nGauss = Integration::get_XI_W_2D(__.domain_poly_type[0], __.intOrd, __.XI, __.W, 0, 1);						//▷ GaussPoints(XI) 와 Weight(W)을 불러온후 개수를 nGauss에 저장 ( 적분관련 class는 "c_integration_2008.h"에 들어 있다. )
		FEM::GET_SHAPE_VALUES::Pre_Values(__.dim, __.XI, __.nnshape, __.shape.domain, __.pre_npsi, __.pre_ndpsi);		//▷ domain prevalue를 얻어온다.
		FEM::GET_SHAPE_VALUES::Pre_Values(__.dim, __.XI, __.npshape, __.shape.pressure, __.pre_ppsi, __.pre_pdpsi);		//▷ pressure prevalue를 얻어온다.
		FEM::GET_SHAPE_VALUES::Pre_Values(__.dim, __.XI, __.nvshape, __.shape.vector, __.pre_Vpsi, __.pre_Vdpsi);

		__.nGauss1D = Integration::get_XI_W_1D(__.intOrd, __.XIL, __.WL);
		__.nGauss1D_round = Integration::get_XI_W_2D_ROUND(__.domain_poly_type[0], __.intOrd, __.XILs, __.WL);
		FEM::GET_SHAPE_VALUES::Pre_Values(__.dim, __.XILs, __.nnshape, __.shape.domain, __.pre_nepsi, __.pre_nedpsi);		//▷ domain prevalue를 얻어온다.
		FEM::GET_SHAPE_VALUES::Pre_Values(__.dim, __.XILs, __.npshape, __.shape.pressure, __.pre_pepsi, __.pre_pedpsi);		//▷ velocity prevalue를 얻어온다.

		// [ Interface Part ]
		int nD;
		for (int i = 0; i <= 1; i++) {
			nD = __.domain_poly_type[i];
			__.vGauss[nD] = Integration::get_XI_W_2D(__.domain_poly_type[i], __.intOrd, __.XIs[nD], __.Ws[nD], 0, 1);								//▷ GaussPoints(XI) 와 Weight(W)을 불러온후 개수를 nGauss에 저장 ( 적분관련 class는 "c_integration_2008.h"에 들어 있다. )
			FEM::GET_SHAPE_VALUES::Pre_Values(__.dim, __.XIs[nD], __.nnshapes[nD], __.shape.domains[nD], __.pre_npsis[nD], __.pre_ndpsis[nD]);		//▷ interface domain prevalue를 얻어온다.
		}
	}

	//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
	//▩▩	           문제를 초기화 시키는 루틴을 호출한다.              ▩▩
	//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
	void	INITIALIZE() {
		SET_PROBLEM();
		SET_DOMAIN_BASIS();
		SET_SOLUTION_BASIS();
		SET_PREVALUES();

		// [ 어떤 level(layer)에서 작업할 것인지 설정 ]
		Input("Starting Layer", __.stLayer);
		Input("End Layer", __.edLayer);

		// [ 저장할 ERROR의 종류를 선언한다. ]
		__.errorNames[0] = "L2_ERROR";
		__.errorNames[1] = "H1_ERROR";
		__.errorNames[2] = "Hdiv_ERROR";
	}

	//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
	//▩▩             사용할 element들의 자료를 setting한다.             ▩▩
	//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
	void	ELEMENT_SETTING() {
		printf("\n[[ ELEMENT SETTING..  ]]");

		// [ Domain 정보를 setting ]
		FEM::CALCULATE_DOMAIN_VARIABLES::Q1_RECTANGLE(_, __);					//▷ 삼각격자에 대한 정보를 생성한다.
		FEM::INDEXING::Q1_CONFORMING(_, _.indexN, __.nnshape);				//▷ domain basis indexing
		FEM::INDEXING::BOUNDARY_Q1_NODAL_RECT(_, __);							//▷ boundary가 어디인지를 설정
		FEM::COORDINATING::STANDARD(_, __);									//▷ 점들의 좌표를 기억한다.

		FEM::INDEXING::NEIGHBORHOOD_RECT(_, __);								//▷ 인접 elt의 정보를 생성한다.
		FEM::INDEXING::EDGE_Q1_NONCONFORMING_NODE(_, _.indexL, __.nnshape);

		// [ Pressure 정보를 setting ]
		FEM::INDEXING::Q1_CONFORMING_BUBBLE(_, _.indexP, __.npshape);		//▷ conforming basis들의 개수를 얻어온다. ( 직접 구해도 무방하다. )
		_.npT = _.nnT + _.neT;

		// [ Velocity 정보를 setting ]
		// [ Velocity 정보 ]
		_.nvT = FEM::CALCULATE_VARIABLES::getBasisN(FEM_SHAPES::MIXED::ID::D_SHAPES_RTB0_SIZE1, _);
		FEM::INDEXING::RTB0(_, _.indexV, __.nvshape);

		drtV.make(_.neT, 4);
		int i, l, nl;
		int e, eN;
		int edge;

		for (edge = 0; edge < _.nlt; edge++){
			e = _.indexL(edge, 0);
			eN = _.indexL(edge, 1);
			l = _.indexL(edge, 2);
			if (e < 0) {
				_.indexL(edge, 0) = eN;
				_.indexL(edge, 1) = e;
				_.indexL(edge, 2) = (l+2)%4;
			}
			e = _.indexL(edge, 0);
			eN = _.indexL(edge, 1);
			l = _.indexL(edge, 2);
			nl = (l + 2) % 4;
			if (e > eN){
				drtV[e][l] = -1;
				if (eN >= 0){
					drtV[eN][nl] = 1;
				}
			}
			if (e < eN){
				drtV[e][l] = 1;
				if (eN >= 0){
					drtV[eN][nl] = -1;
				}
			}

		}

	}

	//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
	//▩▩                         memory를 할당한다.                     ▩▩
	//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
	void	MEMORY_ALLOCATION() {
		printf("\n[[ VARIABLE SETTING.. ]]");

		_.mA.make(_.npT, 7);
		_.vCP.make(_.npT);
		_.vF.make(_.npT);
		_.vCV.make(_.nvT);
		vPHI.make(_.neT);
		voldPHI.make(_.neT);
		//vEAt.make(_.neT,2);

		CI.make(_.neT,2); // index
		CP.make(_.neT,2); // coordinate
		IP.make(_.neT, 2);// interface point
		CEIP.make(_.neT, 6, 2);// coordinate of edge CEIP[e][0,1][x,y]
		Interface_Element_Curvature.make(_.neT);

		CEIP.clear(-1);
		Interface_Element_Curvature.clear(-10000000.);
		
		//for (int e=0; e<_.neT; e++){
			//vEAt[e][0] = -1.; // Non Interface
		//}

		iim.initialize(__.dim, 3, __.domain_poly_type[0], 4);				//▷ dim, subgrid개수, main grid node개수, subgrid maximun node개수
		iim_N.initialize(__.dim, 3, __.domain_poly_type[0], 4);

		__.drtP.make(__.npshape).setValues(__.domain_poly_type[0], -1, -1, _.mEltN);
		__.drtV.make(__.nvshape).setValues(__.domain_poly_type[0], 0, __.nvshape, _.mEltN);

		_.vLevelSet.make(_.nnT);
		_.vEltA.make(_.neT);
	}
	 
	//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
	//▩▩       Simple swap function with 2 variables                 ▩▩
	//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
	void swap_(double & a, double & b) {
		double temp;
		temp = a;
		a = b;
		b = temp;
	}
	void swap_(int & a, int & b) {
		double temp;
		temp = a;
		a = b;
		b = temp;
	}

	//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
	//▩▩         문제생김 case 오류                   ▩▩
	//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
	void RECURSIVE_ADJACENT_EDGE_UPDATE(FVector_double& vRealP_1, FVector_double& vRealP_2, FVector_int& interface_count_, int& max_count) {
		max_count++;
		if (max_count > 200) {
			cout << "max count : "<<max_count << endl;
			cout << "Point 1 :" << endl; vRealP_1.print();
			cout << "Point 2 :" << endl; vRealP_2.print();


			
			int e1_x, e1_y, e2_x, e2_y;

			e1_x = int((vRealP_1[0] - __.RX[0][0]) / _.dx);
			e1_y = int((vRealP_1[1] - __.RX[0][1]) / _.dy);

			e2_x = int((vRealP_2[0] - __.RX[0][0]) / _.dx);
			e2_y = int((vRealP_2[1] - __.RX[0][1]) / _.dy);

			//e1<=e2
			int e1, e2;
			e1 = e1_x + e1_y*_.nsR;
			e2 = e2_x + e2_y*_.nsR;

			cout << "e1 : " << e1 << ",  e2 : " << e2 << endl;
		
			cout << "CEIP[e1]" << endl;
			CEIP[e1].print();

			cout << "CEIP[e2]" << endl;
			CEIP[e2].print();

			system("pause");
		}


		double x1, x2, y1, y2;
		x1 = vRealP_1[0]; y1 = vRealP_1[1];
		x2 = vRealP_2[0]; y2 = vRealP_2[1];

		int e1_x, e1_y, e2_x, e2_y;
		double  inter_edge_x, inter_edge_y;

		e1_x = int((vRealP_1[0] - __.RX[0][0]) / _.dx);
		e1_y = int((vRealP_1[1] - __.RX[0][1]) / _.dy);

		e2_x = int((vRealP_2[0] - __.RX[0][0]) / _.dx);
		e2_y = int((vRealP_2[1] - __.RX[0][1]) / _.dy);

		//e1<=e2
		int e1, e2;
		e1 = e1_x + e1_y*_.nsR;
		e2 = e2_x + e2_y*_.nsR;

		
		if (e1 > e2)
		{
			swap_(e1, e2);
			swap_(e1_x, e2_x);
			swap_(e1_y, e2_y);

			swap_(x1, x2);
			swap_(y1, y2);
		}


		//Stopping Criteria1 : same element
		if ((abs(e1_x - e2_x) + abs(e1_y - e2_y) == 0)) {
			return;
		}

		//Stopping Criteria2 : adjacent element
		if (abs(e1_x - e2_x) + abs(e1_y - e2_y) == 1) {
			int count_Interface;
			MATH::addAtt(_.vEltA[e1], CV.INTERFACE_ELT);
			MATH::addAtt(_.vEltA[e2], CV.INTERFACE_ELT);


			if (e1_x == e2_x)
			{
				inter_edge_y = _.coordN[_.indexP[e1][2]][1];
				inter_edge_x = (x2 - x1) / (y2 - y1)*(inter_edge_y - y1) + x1;
			}//case1-1
			else
			{
				inter_edge_x = _.coordN[_.indexP[e1][1]][0];
				inter_edge_y = (y2 - y1) / (x2 - x1)*(inter_edge_x - x1) + y1;
			}//case1-2

			 // update CEIP[e1]
			count_Interface = interface_count_[e1];
			CEIP[e1][count_Interface][0] = inter_edge_x;
			CEIP[e1][count_Interface][1] = inter_edge_y;
			interface_count_[e1] = count_Interface + 1;


			// update CEIP[e2]
			count_Interface = interface_count_[e2];
			CEIP[e2][count_Interface][0] = inter_edge_x;
			CEIP[e2][count_Interface][1] = inter_edge_y;
			interface_count_[e2] = count_Interface + 1;

			return;
		}


		// abs(e1_x - e2_x) + abs(e1_y - e2_y) >1
		FVector_double vRealP_mid(__.dim);
		vRealP_mid[0] = (x1 + x2) *0.5;
		vRealP_mid[1] = (y1 + y2) *0.5;

		RECURSIVE_ADJACENT_EDGE_UPDATE(vRealP_1, vRealP_mid, interface_count_, max_count);
		RECURSIVE_ADJACENT_EDGE_UPDATE(vRealP_mid, vRealP_2, interface_count_, max_count);


	}

	void INTERFACE_ELEMENT_EDGE_UPDATE(int it, int draw_count=1) {

		int nOption = FEM::IIFEM::D_IIM;

		int e, i, j, k;
		int count_Interface;
		FVector_double vRealP_1(__.dim);
		FVector_double vRealP_2(__.dim);

		FVector_int interface_count_(_.neT);


		int e1, e2, e3;
		int e1_x, e1_y, e2_x, e2_y;
		double x1, x2, y1, y2;
		double cent_x,cent_y;
		double  inter_edge_x, inter_edge_y;

		int temp;
		int count;
		int NDNode;

		_.vEltA.clear();
		CEIP.clear(-1.);
		interface_count_.clear();

		int max_count = 0;
		for (k = 0; k < nCI; k++) {
			vRealP_1 = IP[k];
			if (k+1==nCI)
				vRealP_2 = IP[0];
			else
				vRealP_2 = IP[k+1];

			max_count = 0;
			RECURSIVE_ADJACENT_EDGE_UPDATE(vRealP_1, vRealP_2, interface_count_, max_count);
		}   

		double x, y,xleft,xright,ytop,ybottom;
		FVector_int edgeNumber(6);
		edgeNumber.clear(-1);
		int xMark1, xMark2;
		int target_count;
		FVector_double target1(2), target2(2);
		bool repeat_;
		for (e = 0; e < _.neT; e++) {
			if (interface_count_[e] > 2) {
				//CEIP[e].print();

				xleft = _.coordN[_.indexN[e][0]][0];
				xright = _.coordN[_.indexN[e][2]][0];
				ybottom = _.coordN[_.indexN[e][0]][1];
				ytop = _.coordN[_.indexN[e][2]][1];

				for (i = 0; i < interface_count_[e]; i++) {
					x = CEIP[e][i][0];
					y = CEIP[e][i][1];

					if (x == xleft) {
						edgeNumber[i] = 3;
					}
					if (x == xright) {
						edgeNumber[i] = 1;
					}
					if (y == ybottom) {
						edgeNumber[i] = 0;					
					}
					if (y == ytop) {
						edgeNumber[i] = 2;					
					}
				}
				//edgeNumber.print();
				for (i = 0; i < interface_count_[e]-1; i++)
				{
					repeat_ = false;
					xMark1 = i;
					for (j = i + 1; j < interface_count_[e]; j++)
					{
						xMark2 = j;
						if (edgeNumber[xMark1] == edgeNumber[xMark2])
						{
							repeat_ = true;
							break;
						}
					}
					if (repeat_ == true)
						break;
				}
				target_count = 0;
				for (i = 0; i < interface_count_[e]; i++)
				{
					if (i != xMark1 && i != xMark2 && i != -1)
					{
						if (target_count == 0)
						{
							target1 = CEIP[e][i];
							target_count++;
						}
						else
						{
							target2 = CEIP[e][i];
						}
					}
				}		
				CEIP[e][0] = target1;
				CEIP[e][1] = target2;
			}

		}

		POST_PROCESSING();

		if (it%draw_count==0 && draw_count!=-1){
			char buffer[128];
			sprintf(buffer, "%s%d_%d.txt", "CEIP", __.nLayer, it/draw_count);
			FILE *fp = fopen(buffer, "w"); 
			for (e = 0; e < _.neT; e++) { 
				if (_.vEltA[e] & CV.INTERFACE_ELT) { 
					for (i = 0; i < 2; i++) { 
						for (k = 0; k < 2; k++) {
							fprintf(fp, "%.8f \t", CEIP[e][i][k]);
						}
						fprintf(fp, "\n");
					} 
				}
			}
			fclose(fp);   
		}
		// [ Find IIM Variables ]
	//	FEM::LEVEL_SET::initialize(_, __);
	//	FEM::IIFEM::check_Interface_Element(_, __); 
	//	FEM::IIFEM::find_IIM_Shape_Pressure_Q1_Conforming(_, __, nOption);

	}

	//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
	//▩▩      인터페이스가 겹치는 edge point의 비율을 찾는다       ▩▩
	//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
	void get_Cross_Points_Bisection(int e, FEM_VARIABLES::IIM & iim) {
		
		int nNode = __.domain_poly_type[0];
		int i, k;
		int edgeNumber;
		double x, y;
		int i0, i1;

		double xleft=_.coordN[_.indexN[e][0]][0];
		double xright=_.coordN[_.indexN[e][2]][0];
		double ybottom = _.coordN[_.indexN[e][0]][1];
		double ytop=_.coordN[_.indexN[e][2]][1];
		double ratio; 

		ratio = -1;
		iim.vCpr.clear(-1);
		iim.mCps.setSize(nNode, __.dim);
		for (k = 0; k < 4; k++) {
			iim.mCps[k]._size = 0;
		}
		  
		for (i = 0; i < 2; i++) {
			x = CEIP[e][i][0];
			y = CEIP[e][i][1];

			if (x == xleft) {
				edgeNumber = 3;
				ratio = (y-ytop) / (ybottom-ytop);
			}
			if (x == xright) {
				edgeNumber = 1;
				ratio = (y - ybottom) / (ytop - ybottom);
			}
			if (y == ybottom) {
				edgeNumber = 0;
				ratio = (x - xleft) / (xright - xleft);
			}
			if (y == ytop) {
				edgeNumber = 2;
				ratio = (x - xright) / (xleft - xright);
			}
		//	iim.mCps[edgeNumber].setAll(x, y);
		
			if (ratio < 0) {
				cout << ratio << endl;
			}
			if (ratio > 1) {
				cout << ratio << endl;
			}
			iim.vCpr[edgeNumber] = edgeNumber + ratio;

			i0 = _.indexN[e][edgeNumber];
			i1 = _.indexN[e][(edgeNumber+1)%4];
			iim.mCps[edgeNumber]._size = 2;
			iim.mCps[edgeNumber].op("=", 1 - ratio, _.coordN[i0], ratio, _.coordN[i1]);

		}
	}
	
	//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
	//▩▩                                             ▩▩
	//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
	void INTERFACE_ELEMENT_VLEVELSET_ALL() {
		int e,k,i,j;
		FVector_double vLevelSet(4);
		int nNode = __.domain_poly_type[0];

		static FEM_VARIABLES::IIM	iim(__.dim, 3, nNode, 4);	//subgrid 개수 maximum이 3개이다
		int nInterfaceEdge1, nInterfaceEdge2;
		int count;
		FVector_int set1(3), set2(3);
		int idx_set;
		int temp_cond;
		double phi_x, phi_y, phi_xx, phi_yy, phi_xy, curvature_;

		_.vLevelSet.clear(-10.);
		for (e = 0; e < _.neT; e++) {
			if (!(_.vEltA[e] & CV.INTERFACE_ELT)) {
				// IN
				if (vPHI[e] > 0)
				{
					MATH::addAtt(_.vEltA[e], CV.IN);
					_.vLevelSet[_.indexN[e][0]] = -1;
					_.vLevelSet[_.indexN[e][1]] = -1;
					_.vLevelSet[_.indexN[e][2]] = -1;
					_.vLevelSet[_.indexN[e][3]] = -1;
				}
				else
				{
					MATH::addAtt(_.vEltA[e], CV.OUT);
					_.vLevelSet[_.indexN[e][0]] = 1;
					_.vLevelSet[_.indexN[e][1]] = 1;
					_.vLevelSet[_.indexN[e][2]] = 1;
					_.vLevelSet[_.indexN[e][3]] = 1;
				}
			}
		}
		for (e = 0; e < _.neT; e++) {
			
			if ((_.vEltA[e] & CV.INTERFACE_ELT)) {

				// Find Curvature
				i=e%_.nsR;	j=e/_.nsR;
			
				phi_x = (vPHI(i + 1 + j*_.nsR) - vPHI(i - 1 + j*_.nsR))/2/_.dx;
				phi_y = (vPHI(i + (j+1)*_.nsR) - vPHI(i + (j-1)*_.nsR)) / 2 / _.dy;

				phi_xx = (vPHI(i + 1 + j*_.nsR) + vPHI(i - 1 + j*_.nsR) - 2 * vPHI(i + j*_.nsR)) / _.dx / _.dx;
				phi_yy = (vPHI(i + (j+1)*_.nsR) + vPHI(i + (j-1)*_.nsR) - 2 * vPHI(i + j*_.nsR)) / _.dy / _.dy;
				phi_xy = (vPHI(i + 1 + j*_.nsR) - vPHI(i - 1 + j*_.nsR) - vPHI(i + 1 + (j - 1)*_.nsR) + vPHI(i - 1 +( j - 1)*_.nsR) ) / _.dx / _.dx / 4;

				curvature_ = -(phi_xx * phi_y * phi_y - 2* phi_xy *phi_x * phi_y + phi_yy *phi_x*phi_x )/ pow(phi_x*phi_x +phi_y* phi_y  , 1.5);
				Interface_Element_Curvature[e]=curvature_;
				// Find Curvature

				get_Cross_Points_Bisection(e, iim); 
				count = 0;
				for (k = 0; k < 4; k++) {
					vLevelSet[k] = _.vLevelSet[_.indexN[e][k]];

					
					if (iim.vCpr[k] > 0 && count==0) {
						nInterfaceEdge1 = int(iim.vCpr[k]);
						count++;
					}
					if (iim.vCpr[k] > 0 && count == 1) {
						nInterfaceEdge2 = int(iim.vCpr[k]); 
					}   
				} 
				
				if ((nInterfaceEdge2 - nInterfaceEdge1) % 2 == 0)
				{
					set1._size = 2;
					set2._size = 2;
					set1.setAll((nInterfaceEdge1 + 1)%4, (nInterfaceEdge1 + 2)%4);
					set2.setAll((nInterfaceEdge2 + 1)%4, (nInterfaceEdge2 + 2)%4);

					
					for (k = 0; k < 2; k++)
					{
						if (vLevelSet[set1[k]] != -10)
						{
							idx_set = 1;
							temp_cond = vLevelSet[set1[k]];
							break;
						}
						
						if (vLevelSet[set2[k]] != -10)
						{
							idx_set = 2;
							temp_cond = vLevelSet[set2[k]];
							break;
						}
					}

					if (idx_set == 1)
					{
						vLevelSet[set1[0]] = temp_cond;
						vLevelSet[set1[1]] = temp_cond;
						vLevelSet[set2[0]] = -1*temp_cond;
						vLevelSet[set2[1]] = -1*temp_cond;
					}
					else
					{
						vLevelSet[set1[0]] = -1*temp_cond;
						vLevelSet[set1[1]] = -1*temp_cond;
						vLevelSet[set2[0]] =   temp_cond;
						vLevelSet[set2[1]] =  temp_cond;

					}
				}

				if ((nInterfaceEdge2 - nInterfaceEdge1) % 2 == 1)
				{
					set1._size = 1;
					set2._size = 3;
					
					if (nInterfaceEdge2 == 3 && nInterfaceEdge1==0)
					{
						swap(nInterfaceEdge1, nInterfaceEdge2);
					}

					set1.setAll((nInterfaceEdge1 + 1)%4);
					
					for (i = 0; i < 3; i++)
					{
						set2[i] = (set1[0] + 1 + i) % 4;
					}

					if (vLevelSet[set1[0]] != -10)
					{
						for (i = 0; i < 3; i++)
						{
							vLevelSet[set2[i]] = -1 * vLevelSet[set1[0]];
						}
					}
					else 
					{
						for (k = 0; k < 3; k++)
						{
							if (vLevelSet[set2[k]] != -10)
							{
								temp_cond = vLevelSet[set2[k]];
								break;
							}
						}
						vLevelSet[set1[0]] = -1 * temp_cond;
						vLevelSet[set2[0]] = temp_cond;
						vLevelSet[set2[1]] = temp_cond;
						vLevelSet[set2[2]] = temp_cond;
						
					}
				}

				for (k = 0; k < 4; k++) {
					_.vLevelSet[_.indexN[e][k]] = vLevelSet[k];
				}
			
			}	// if Interface element
		}	// for e 
	//	cout << "element e: 117. Level Set" << endl;
	//	for (k = 0; k < 4; k++) {
	//		cout << _.vLevelSet[_.indexN[117][k]] << endl;
	//	}
 
	//	_.vLevelSet.print();
	}

	//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
	//▩▩ ▩▩
	//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
	void POST_PROCESSING() {

		int e;
		int nNode = __.domain_poly_type[0]; 
		int i = 0;
		static FEM_VARIABLES::IIM	iim(__.dim, 3, nNode, 4);	//subgrid 개수 maximum이 3개이다
		
		int count_ = 0;
		for (e = 0; e < _.neT; e++) {
			if (_.vEltA[e] & CV.INTERFACE_ELT)
			{
				get_Cross_Points_Bisection(e, iim); 
				count_ = 0;
				for (i = 0; i < nNode; i++) {
					if (iim.vCpr[i] >= 0) {
					
						count_++;
					}

				}
				if (count_==1) {
					_.vEltA[e] = CV.OUT;
					
					for (i = 0; i < nNode; i++) {
						_.vLevelSet[_.indexN[e][i]] = 1;
					}
				}
			}	
		}
	}
	
	//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
	//▩▩    find_IIM_Shape_Pressure_Q1_Conforming 실행부분     ▩▩
	//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
	void INTERFACE_BASIS_UPDATE() {
		int nOption = FEM::IIFEM::D_IIM + FEM::IIFEM::D_BUBBLE;
		find_IIM_Shape_Pressure_Q1_Conforming(nOption);
	}
	
	//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
	//▩▩  1. 각 elmenet 마다 get_Cross_Points_Bisection 실행   ▩▩
	//▩▩  2. 각 element 마다 FEM::IIFEM::make_SubGrids  실행   ▩▩
	//▩▩  3. 각 element 마다 iim.levelSet update              ▩▩
	//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
	void get_iElt_Datas(int e, FEM_VARIABLES::IIM & iim) {
		int nNode = __.domain_poly_type[0];
		int i;
		for (i = 0; i<nNode; i++) 
			iim.vLevelSet[i] = _.vLevelSet[_.indexN[e][i]];										// levelSet value를 불러온다.
																			//Try(IIFEM::get_Cross_Points(_, __, e, iim););		
		get_Cross_Points_Bisection(e, iim);													// Cross Point들을 찾는다.
		FEM::IIFEM::make_SubGrids(_, __, e, iim);
	}

	//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
	//▩▩  IFEM basis의 coefficient 구한다                      ▩▩
	//▩▩  이때 jump condition을 위한 3-pt curvature를 계산      ▩▩
	//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
	void find_IIM_Shape_Pressure_Q1_Conforming(int nOption = FEM::IIFEM::D_IIM)
	{
		int i, j, e, eA;
		int eN;

		int nNode = __.domain_poly_type[0];
		int nCoef = __.npiimshape;
		double x, y;
		eA = 1;

		// IIM Domain Variable
		static FEM_VARIABLES::IIM	iim(__.dim, 3, nNode, 4);	//subgrid 개수 maximum이 3개이다
		static FEM_VARIABLES::IIM	iim_N(__.dim, 3, nNode, 4);	//subgrid 개수 maximum이 3개이다
																// IIM Coefficient Variables
		static FVector_double	vN(__.dim), vIm(__.dim);
		static FVector_double	vRealP(__.dim);
		static FVector_double	vComponent(nCoef);
		static FVector_double	vComponent1(nCoef);
		static FVector_double	vComponent2(nCoef);
		static FVector_double	vLoad(2 * nCoef);
		static FVector_double	vMus(2);
		static FVector_double	vMp1(__.dim), vMp2(__.dim);
		static FVector_double	vTemp(nCoef * 2);

		static FMatrix_double	mNodes(nNode, __.dim);
		static FMatrix_double	mIIM(nCoef * 2, nCoef * 2);																				// GE를 여러번 해야 하므로 복사해서 사용한다.
		static FMatrix_double	mIIM_clone(nCoef * 2, nCoef * 2);
		static FMatrix_double	mCps(2, __.dim);
		static FMatrix_double	mCps_N(2, __.dim);
		static FVector_double	vCpr(2);

		static FMatrix_double	mCurvature_Three_Points(3, __.dim);

		int edge_number;
		int edge_number_N;
		int match_index;
		double three_point_curvature_;
		// Memory Allocation
		if (nOption & FEM::IIFEM::D_IIM) {
			_.cIIMCoef.make(_.neT);
			_.cShapeCoef.make(_.neT);
		}

		if (nOption & FEM::IIFEM::D_BUBBLE) {
			_.cShapeCoef.make(_.neT);																									// petrov galerkin을 위해 일반함수를 만들어 사용
			_.cIIMCoefBubble.make(_.neT);
			_.vCP_ext.make(_.npT);
			_.mCPB.make(_.neT, 3);
		}
		if (nOption & FEM::IIFEM::D_EXTRACTION)	_.cIIMCoefExtraction.make(_.neT);
		//_.mA.getLowerTriangle(_.mA);
		// Find Coefficient
		for (e = 0; e<_.neT; e++) {
			if (_.vEltA[e] & CV.INTERFACE_EXTENSION) continue;

			if (_.vEltA[e] & CV.INTERFACE_ELT) {
				get_iElt_Datas(e, iim);
				for (i = 0; i<2; i++) {
					mCps[i] = iim.mCps.getData(i + 1);
					vCpr[i] = iim.vCpr.getData_ge(i + 1);
					mCurvature_Three_Points[i].op("=", 1., mCps[i]);
				}
				mIIM.clear();																									// Initialize
																																//	mIIM.print("", 5);
				for (i = 0; i<nNode; i++) mNodes[i] = _.coordN[_.indexN(e, i)];

				// ◈ Condition(0~3): +4 Edge average delta functions ◈
				for (i = 0; i<4; i++) {																							// 3 delta conditions
					x = mNodes[i][0];
					y = mNodes[i][1];

					if (iim.vLevelSet[i] <= 0) {																				// 내부 basis component값을 입력: 0도 내부로 인식한다.
						mIIM[i].setAll(1., x, y, x*y, 0., 0., 0., 0.);
					}
					else {																										// 내부 basis component값을 입력
						mIIM[i].setAll(0., 0., 0., 0., 1., x, y, x*y);
					}
				}
				// ◈ Point Continuity(4~5): +2 point continuity ◈
				for (i = 0; i<2; i++) {
					__.shape.iim_pressure_component(mCps[i], vComponent);
					mIIM[i + 4].copy(vComponent);
					vComponent *= -1;
					mIIM[i + 4].copy(vComponent, nCoef);
				}

				// ◈ Second derivative Continuity(6): +1 ◈

				mIIM[6].setAll(0., 0., 0., 1., 0., 0., 0., -1.);

				// ◈ Flux Continuity(7): +1 ◈
				// [ Make Normal ]
				if (iim.vIO[1] == CV.IN) vIm.op("=", mCps[1], -1., mCps[0]);
				else vIm.op("=", mCps[0], -1., mCps[1]);
				vN.setAll(-vIm[1], vIm[0]).normalize();																				// 90도 회전 및 normalize
				vMp1.op("=", 0.5, mCps[0], 0.5, mCps[1]);
				// [ Make the Average of coefficients ]
				vMus.clear();
				for (i = 0; i<2; i++) {
					_problem->coef_mu(mCps[i], vIm);
					vMus += vIm;
				}
				vMus *= 0.5;
				mIIM[7].setAll(0., vN[0] * vMus[0], vN[1] * vMus[0], vMus[0] * (vMp1[0] * vN[1] + vMp1[1] * vN[0]), 0., -vN[0] * vMus[1], -vN[1] * vMus[1], -vMus[1] * (vMp1[0] * vN[1] + vMp1[1] * vN[0]));
				// ◈ Find IIM Basis Coefficients ◈
				if (nOption & FEM::IIFEM::D_IIM) {																					// find IIM coef;
					_.cIIMCoef[e].make(nCoef, nCoef * 2);																				// (basis개수, coef개수)
					for (i = 0; i<nCoef; i++) {
						mIIM_clone = mIIM;
						vLoad.clear();
						vLoad[i] = 1.;
						SOLVER::GE(mIIM_clone, _.cIIMCoef[e][i], vLoad);
					}
				}

				// ◈ Find Bubble Coefficients ◈
				if (nOption & FEM::IIFEM::D_BUBBLE) {																					// find IIM Bubble coef
					_.cIIMCoefBubble[e].make(1, nCoef * 2);																				// (basis개수, coef개수) : 기존에 bubble 계수를 받았다면 메모리를 생성하지 말아야 한다.
					mIIM_clone = mIIM;

					// ▣ Nonhomogeneous Fulx Conditions: 공통으로 적용되는 부분 ▣
					vLoad.clear();
					//	vCpr.print();
					//	nLocal = (int)iim.vCpr.getData_ge(2);
					for (i = 0; i<2; i++) {
						edge_number = (int)vCpr[i];
						eN = _.mEltN[e][edge_number];
						get_iElt_Datas(eN, iim_N);

						match_index = -100;
						for (j = 0; j<2; j++) {
							mCps_N[j] = iim_N.mCps.getData(j + 1);
							if ((mCps[i][0] - mCps_N[j][0])*(mCps[i][0] - mCps_N[j][0]) + (mCps[i][1] - mCps_N[j][1])*(mCps[i][1] - mCps_N[j][1])    < 0.000000000001) {
								match_index = j;
							}
						}
						mCurvature_Three_Points[2].op("=", 1., mCps_N[(match_index + 1) % 2]);
						three_point_curvature_ = curvature_(mCurvature_Three_Points);
						//	cout << three_point_curvature_ << endl;
						//	cout << three_point_curvature_ << endl;
						//	vLoad[i + 4] =  three_point_curvature_ * _problem->tau;
						//	vLoad[i + 4] =  (_problem->tau)/(_problem->r0);
						vLoad[i + 4] = (Interface_Element_Curvature[e] + Interface_Element_Curvature[eN]) / 2 * _problem->tau; // _problem->P_Jump(mCps[i]);
																															   //	cout << (Interfact_Element_Curvature[e] + Interfact_Element_Curvature[eN])/2 << endl;
																															   //	vLoad[i + 4] =  0.01;// get point jump
					}
					//vLoad[5] *= 0.5;																									// flux jump average를 취한다.
					vIm.op("=", 0.5, mCps[0], 0.5, mCps[1]);
					vLoad[7] = 0.;// _problem->Flux_Jump((mCps[0] + mCps[1]) / 2, vN);
								  //if(fabs(vLoad[5]) < 1.0E-15) vLoad[5] = 0;
								  //if(vLoad[3] != 0) Pause("vLoad[3] Jump Exists: " << vLoad[3]);
								  //if(vLoad[4] != 0) Pause("vLoad[4] Jump Exists: " << vLoad[4]);
								  //if(vLoad[5] != 0) Pause("Flux Jump Exists: " << vLoad[5]);
					SOLVER::GE(mIIM_clone, _.cIIMCoefBubble[e][0], vLoad);


				}// end if(nOption & D_BUBBLE)	


				 //	mIIM.print("",5);
				 // ◈ Find Normal Basis Coefficients ◈
				vMus[0] = 1.;
				vMus[1] = 1.;
				mIIM[7].setAll(0., vN[0] * vMus[0], vN[1] * vMus[0], vMus[0] * (vMp1[0] * vN[1] + vMp1[1] * vN[0]), 0., -vN[0] * vMus[1], -vN[1] * vMus[1], -vMus[1] * (vMp1[0] * vN[1] + vMp1[1] * vN[0]));
				//	mIIM[7].setAll(0., vN[0], vN[1], 2.*(vMp1[0] * vN[0] - vMp1[1] * vN[1]), 0., -vN[0], -vN[1], -2.*(vMp1[0] * vN[0] - vMp1[1] * vN[1]));
				if (nOption & FEM::IIFEM::D_IIM) {																					// find IIM coef;
					_.cShapeCoef[e].make(nCoef, nCoef * 2);																				// (basis개수, coef개수)
					for (i = 0; i<nCoef; i++) {
						mIIM_clone = mIIM;
						vLoad.clear();
						vLoad[i] = 1.;
						SOLVER::GE(mIIM_clone, _.cShapeCoef[e][i], vLoad);
					}
				}

			}// end if(_.vEltA[e] & CV.INTERFACE_ELT)
			 //Pause(e);
			 //_.cIIMCoef[e].print("IIM Basis");
			 //_.cIIMCoefBubble[e].print("Bubble");
			 //_.cShapeCoef[e].print("Standard Basis");
			 //_.vCP_ext.print("vCP_ext");
		}// end for(e )
		 //_.cIIMCoef.print("IIM");
		 //_.cIIMCoefBubble.print("Bubble");
		 //_.vCP_ext.print("vCP_ext");  
	}
	double curvature_(FMatrix_double & three_points) {
		double x0 = three_points[0][0];
		double y0 = three_points[0][1];

		double x1 = three_points[1][0];
		double y1 = three_points[1][1];

		double x2 = three_points[2][0];
		double y2 = three_points[2][1];

		double area_ = x0*(y1 - y2) + x1*(y2 - y0) + x2*(y0 - y1);
		area_ = abs(area_ / 2);

		double length_1 = sqrt((x0 - x1)*(x0 - x1) + (y0 - y1)*(y0 - y1));
		double length_2 = sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
		double length_3 = sqrt((x2 - x0)*(x2 - x0) + (y2 - y0)*(y2 - y0));

		double curvature_ = 4 * area_ / length_1 / length_2 / length_3;
		return curvature_;
	}


	void find_IIM_Shape_Pressure_Q1_Conforming_origin( int nOption = FEM::IIFEM::D_IIM)
	{
		int i, e, eA;
		int nNode = __.domain_poly_type[0];
		int nCoef = __.npiimshape;
		double x, y;
		eA = 1;

		// IIM Domain Variable
		static FEM_VARIABLES::IIM	iim(__.dim, 3, nNode, 4);	//subgrid 개수 maximum이 3개이다

																// IIM Coefficient Variables
		static FVector_double	vN(__.dim), vIm(__.dim);
		static FVector_double	vRealP(__.dim);
		static FVector_double	vComponent(nCoef);
		static FVector_double	vComponent1(nCoef);
		static FVector_double	vComponent2(nCoef);
		static FVector_double	vLoad(2 * nCoef);
		static FVector_double	vMus(2);
		static FVector_double	vMp1(__.dim), vMp2(__.dim);
		static FVector_double	vTemp(nCoef * 2);

		static FMatrix_double	mNodes(nNode, __.dim);
		static FMatrix_double	mIIM(nCoef * 2, nCoef * 2);																				// GE를 여러번 해야 하므로 복사해서 사용한다.
		static FMatrix_double	mIIM_clone(nCoef * 2, nCoef * 2);
		static FMatrix_double	mCps(2, __.dim);


		// Memory Allocation
		if (nOption & FEM::IIFEM::D_IIM) {
			_.cIIMCoef.make(_.neT);
			_.cShapeCoef.make(_.neT);
		}

		if (nOption & FEM::IIFEM::D_BUBBLE) {
			_.cShapeCoef.make(_.neT);																									// petrov galerkin을 위해 일반함수를 만들어 사용
			_.cIIMCoefBubble.make(_.neT);
			_.vCP_ext.make(_.npT);
			_.mCPB.make(_.neT, 3);
		}
		if (nOption & FEM::IIFEM::D_EXTRACTION)	_.cIIMCoefExtraction.make(_.neT);
		//_.mA.getLowerTriangle(_.mA);
		// Find Coefficient
		for (e = 0; e<_.neT; e++) {
			if (_.vEltA[e] & CV.INTERFACE_EXTENSION) continue;

			if (_.vEltA[e] & CV.INTERFACE_ELT) {
				get_iElt_Datas(e, iim);
				for (i = 0; i<2; i++) mCps[i] = iim.mCps.getData(i + 1);

				mIIM.clear();																									// Initialize
																																//	mIIM.print("", 5);
				for (i = 0; i<nNode; i++) mNodes[i] = _.coordN[_.indexN(e, i)];

				// ◈ Condition(0~3): +4 Edge average delta functions ◈
				for (i = 0; i<4; i++) {																							// 3 delta conditions
					x = mNodes[i][0];
					y = mNodes[i][1];

					if (iim.vLevelSet[i] <= 0) {																				// 내부 basis component값을 입력: 0도 내부로 인식한다.
						mIIM[i].setAll(1., x, y, x*y, 0., 0., 0., 0.);
					}
					else {																										// 내부 basis component값을 입력
						mIIM[i].setAll(0., 0., 0., 0., 1., x, y, x*y);
					}
				}
				// ◈ Point Continuity(4~5): +2 point continuity ◈
				for (i = 0; i<2; i++) {
					__.shape.iim_pressure_component(mCps[i], vComponent);
					mIIM[i + 4].copy(vComponent);
					vComponent *= -1;
					mIIM[i + 4].copy(vComponent, nCoef);
				}

				// ◈ Second derivative Continuity(6): +1 ◈

				mIIM[6].setAll(0., 0., 0., 1., 0., 0., 0., -1.);

				// ◈ Flux Continuity(7): +1 ◈
				// [ Make Normal ]
				if (iim.vIO[1] == CV.IN) vIm.op("=", mCps[1], -1., mCps[0]);
				else vIm.op("=", mCps[0], -1., mCps[1]);
				vN.setAll(-vIm[1], vIm[0]).normalize();																				// 90도 회전 및 normalize
				vMp1.op("=", 0.5, mCps[0], 0.5, mCps[1]);
				// [ Make the Average of coefficients ]
				vMus.clear();
				for (i = 0; i<2; i++) {
					_problem->coef_mu(mCps[i], vIm);
					vMus += vIm;
				}
				vMus *= 0.5; 
				mIIM[7].setAll(0., vN[0] * vMus[0], vN[1] * vMus[0], vMus[0] * (vMp1[0] * vN[1] + vMp1[1] * vN[0]), 0., -vN[0] * vMus[1], -vN[1] * vMus[1], -vMus[1] * (vMp1[0] * vN[1] + vMp1[1] * vN[0]));
				// ◈ Find IIM Basis Coefficients ◈
				if (nOption & FEM::IIFEM::D_IIM) {																					// find IIM coef;
					_.cIIMCoef[e].make(nCoef, nCoef * 2);																				// (basis개수, coef개수)
					for (i = 0; i<nCoef; i++) {
						mIIM_clone = mIIM;
						vLoad.clear();
						vLoad[i] = 1.;
						SOLVER::GE(mIIM_clone, _.cIIMCoef[e][i], vLoad);
					}
				}

				// ◈ Find Bubble Coefficients ◈
				if (nOption & FEM::IIFEM::D_BUBBLE) {																					// find IIM Bubble coef
					_.cIIMCoefBubble[e].make(1, nCoef * 2);																				// (basis개수, coef개수) : 기존에 bubble 계수를 받았다면 메모리를 생성하지 말아야 한다.
					mIIM_clone = mIIM;
					
					// ▣ Nonhomogeneous Fulx Conditions: 공통으로 적용되는 부분 ▣
					vLoad.clear();
					for (i = 0; i<2; i++) {
						vLoad[i + 4] =  Interface_Element_Curvature[e] * _problem->tau; // _problem->P_Jump(mCps[i]);
					//	vLoad[i + 4] =  0.01;// get point jump
					} 
					//vLoad[5] *= 0.5;																									// flux jump average를 취한다.
					vIm.op("=", 0.5, mCps[0], 0.5, mCps[1]);
					vLoad[7] =0.;// _problem->Flux_Jump((mCps[0] + mCps[1]) / 2, vN);
					//if(fabs(vLoad[5]) < 1.0E-15) vLoad[5] = 0;
					//if(vLoad[3] != 0) Pause("vLoad[3] Jump Exists: " << vLoad[3]);
					//if(vLoad[4] != 0) Pause("vLoad[4] Jump Exists: " << vLoad[4]);
					//if(vLoad[5] != 0) Pause("Flux Jump Exists: " << vLoad[5]);
					SOLVER::GE(mIIM_clone, _.cIIMCoefBubble[e][0], vLoad);

					 
				}// end if(nOption & D_BUBBLE)	


				 //	mIIM.print("",5);
				 // ◈ Find Normal Basis Coefficients ◈
				vMus[0] = 1.;
				vMus[1] = 1.;
				mIIM[7].setAll(0., vN[0] * vMus[0], vN[1] * vMus[0], vMus[0] * (vMp1[0] * vN[1] + vMp1[1] * vN[0]), 0., -vN[0] * vMus[1], -vN[1] * vMus[1], -vMus[1] * (vMp1[0] * vN[1] + vMp1[1] * vN[0]));
				//	mIIM[7].setAll(0., vN[0], vN[1], 2.*(vMp1[0] * vN[0] - vMp1[1] * vN[1]), 0., -vN[0], -vN[1], -2.*(vMp1[0] * vN[0] - vMp1[1] * vN[1]));
				if (nOption & FEM::IIFEM::D_IIM) {																					// find IIM coef;
					_.cShapeCoef[e].make(nCoef, nCoef * 2);																				// (basis개수, coef개수)
					for (i = 0; i<nCoef; i++) {
						mIIM_clone = mIIM;
						vLoad.clear();
						vLoad[i] = 1.;
						SOLVER::GE(mIIM_clone, _.cShapeCoef[e][i], vLoad);
					}
				}

			}// end if(_.vEltA[e] & CV.INTERFACE_ELT)
			 //Pause(e);
			 //_.cIIMCoef[e].print("IIM Basis");
			 //_.cIIMCoefBubble[e].print("Bubble");
			 //_.cShapeCoef[e].print("Standard Basis");
			 //_.vCP_ext.print("vCP_ext");
		}// end for(e )
		 //_.cIIMCoef.print("IIM");
		 //_.cIIMCoefBubble.print("Bubble");
		 //_.vCP_ext.print("vCP_ext");  
	}

	//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
	//▩▩WENO35 Schemes(+ & -) : Update u_** with fivePoint    ▩▩
	//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
	void WENO35_minus(FVector_double & fivePoint, double & u_minus){
		double c_00=1. / 3.;
		double c_01=-7. / 6.;
		double c_02=11. / 6;

		double c_10=-1. / 6.;
		double c_11=5. / 6.;
		double c_12=1. / 3.; 

		double c_20=1. / 3.;
		double c_21=5. / 6.;
		double c_22= -1. / 6.;

		double d0=1. / 10.;
		double d1=3. / 5.;
		double d2=1. / 10.;

		double eps=pow(10., -6.);
		double f_2, f_1, f0, f1, f2;
		f_2=fivePoint[0];
		f_1=fivePoint[1];
		f0=fivePoint[2];
		f1=fivePoint[3];
		f2=fivePoint[4];

		double vBeta0 = 13. / 12 * pow(f_2 - 2 * f_1 + f0, 2) + pow(-2 * f_1 + 0.5*f_2 + 1.5*f0, 2);
		double vBeta1 = 13. / 12 * pow(f_1 - 2 * f0 + f1, 2) + pow(-0.5*f_1 + 0.5*f1, 2);
		double vBeta2 = 13. / 12 * pow(f0 - 2 * f1 + f2, 2) + pow(-1.5*f0 - 0.5*f2 + 2 * f1, 2);

		double p0=f_2*c_00+f_1*c_01+f0*c_02;
		double p1=f_1*c_10+f0*c_11+f1*c_12;
		double p2=f0*c_20+f1*c_21+f2*c_22;

		double w0=d0/(vBeta0+eps)/(vBeta0+eps);
		double w1=d1/(vBeta1+eps)/(vBeta1+eps);
		double w2=d2/(vBeta2+eps)/(vBeta2+eps);

		double sum_=w0+w1+w2;
		w0=w0/sum_;
		w1=w1/sum_;
		w2=w2/sum_;

		u_minus=p0*w0+p1*w1+p2*w2;

	}
	void WENO35_plus(FVector_double & fivePoint, double & u_plus){
		double c_00=1. / 3.;
		double c_01=-7. / 6.;
		double c_02=11. / 6;

		double c_10=-1. / 6.;
		double c_11=5. / 6.;
		double c_12=1. / 3.; 

		double c_20=1. / 3.;
		double c_21=5. / 6.;
		double c_22= -1. / 6.;

		double d0=1. / 10.;
		double d1=3. / 5.;
		double d2=1. / 10.;

		double eps=pow(10., -6.);
		double f_2, f_1, f0, f1, f2;
		f_2=fivePoint[4];
		f_1=fivePoint[3];
		f0=fivePoint[2];
		f1=fivePoint[1];
		f2=fivePoint[0];

		double vBeta0 = 13. / 12 * pow(f_2 - 2 * f_1 + f0, 2) + pow(-2 * f_1 + 0.5*f_2 + 1.5*f0, 2);
		double vBeta1 = 13. / 12 * pow(f_1 - 2 * f0 + f1, 2) + pow(-0.5*f_1 + 0.5*f1, 2);
		double vBeta2 = 13. / 12 * pow(f0 - 2 * f1 + f2, 2) + pow(-1.5*f0 - 0.5*f2 + 2 * f1, 2);

		double p0=f_2*c_00+f_1*c_01+f0*c_02;
		double p1=f_1*c_10+f0*c_11+f1*c_12;
		double p2=f0*c_20+f1*c_21+f2*c_22;

		double w0=d0/(vBeta0+eps)/(vBeta0+eps);
		double w1=d1/(vBeta1+eps)/(vBeta1+eps);
		double w2=d2/(vBeta2+eps)/(vBeta2+eps);

		double sum_=w0+w1+w2;
		w0=w0/sum_;
		w1=w1/sum_;
		w2=w2/sum_;

		u_plus=p0*w0+p1*w1+p2*w2;

	}
	

	//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
	//▩▩Get the Godunov flux with one_dircetion WENO35 scheme ▩▩
	//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
	void ONE_DIMENSION_GODUNOV_FLUX(double & u_m, double & u_p, double & vel, double & godunov_flux_){
		if (vel<=0)
			godunov_flux_=vel*u_p;
		if (vel>0)
			godunov_flux_=vel*u_m;
	}
	

	//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
	//▩▩  WENO scheme for Hamilto-Jacobi equation      ▩▩
	//▩▩   - by Guang Shan and Danping Peng             ▩▩
	//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
	void WENO35_PHI(FVector_double& divided_diff, double& weno) {

		double eps = pow(10., -6.);

		double a = divided_diff[0];
		double b = divided_diff[1];
		double c = divided_diff[2];
		double d = divided_diff[3];

		// beta : smoothness indicator
		double beta0 = 13 * pow(a - b, 2) + 3 * pow(a - 3 * b, 2);
		double beta1 = 13 * pow(b - c, 2) + 3 * pow(b + c, 2);
		double beta2 = 13 * pow(c - d, 2) + 3 * pow(3 * c - d, 2);


		double alpha0 = 1. / pow(beta0 + eps, 2);
		double alpha1 = 6. / pow(beta1 + eps, 2);
		double alpha2 = 3. / pow(beta2 + eps, 2);

		double sum_ = alpha0 + alpha1 + alpha2;

		double weight0 = alpha0 / sum_;
		double weight1 = alpha1 / sum_;

		weno = weight0*(a - 2 * b + c) / 3 + (weight1 - 0.5)*(b - 2 * c + d) / 6;
	}

	void WENO35_diff_minus(FVector_double& diff_val, double& diff_minus) {
		// diff_val = {dphi_{-3}, dphi_{-2}, d_phi_{-1}, d_phi_{0}, d_phi_{1}}

		diff_minus = (-diff_val[1] + 7 * diff_val[2] + 7 * diff_val[3] - diff_val[4]) / _.dx / 12;

		FVector_double divided_diff(4);
		double weno;
		int i;

		for (i = 0; i < 4; i++) {
			divided_diff[i] = (diff_val[i + 1] - diff_val[i]) / _.dx;
		}

		WENO35_PHI(divided_diff, weno);

		diff_minus -= weno;
	}

	void WENO35_diff_plus(FVector_double& diff_val, double& diff_plus) {
		// diff_val = {dphi_{-2}, d_phi_{-1}, d_phi_{0}, d_phi_{1}, d_phi_{2}}

		diff_plus = (-diff_val[0] + 7 * diff_val[1] + 7 * diff_val[2] - diff_val[3]) / _.dx / 12;
		
		FVector_double divided_diff(4);
		double weno;
		int i;

		for (i = 0; i < 4; i++) {
			divided_diff[i] = (diff_val[4 - i] - diff_val[4 - i - 1]) / _.dx;
		}

		WENO35_PHI(divided_diff, weno);

		diff_plus += weno;
	}

	void LLF_flux(double& diff_x_p, double& diff_x_m, double& diff_y_p, double& diff_y_m, double& vel_x, double& vel_y, double& llf_flux) {
		// Local Lax-Friedrichs flux
		// since the partial derivatives H_1(w.r.t phi_x) and H_2(w.r.t phi_y) are constant,
		// the flux is same to Godonuv flux
		double x_sum = (diff_x_p + diff_x_m) / 2;
		double x_diff = (diff_x_p - diff_x_m) / 2;
		double y_sum = (diff_y_p + diff_y_m) / 2;
		double y_diff = (diff_y_p - diff_y_m) / 2;

		double alpha, beta;

	
		alpha = abs(vel_x);
		beta = abs(vel_y);

		llf_flux = vel_x*x_sum + vel_y*y_sum - alpha*x_diff - beta*y_diff;
	
	}


	//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
	//▩▩ Linear Advection of the level set function		   ▩▩
	//▩▩ Use WENO35 sheme with Godonuv flux				   ▩▩
	//▩▩  - update  "vPHI" which is a class variable		   ▩▩
	//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
	void LEVEL_SET_UPDATE(double dt) {
		int i, j, e, i_x, i_y;
		double vel_u_left = 1.; // vel=(u,v)
		double vel_v_top = 1.; // vel=(u,v)
		double vel_u_right = 1.; // vel=(u,v)
		double vel_v_bottom = 1.; // vel=(u,v)

		double vel_u_avg, vel_v_avg;

		int nsE = _.nsE;
		int index_temp = 0;
		double dx, dy;

		double diff_x_m, diff_x_p;
		double diff_y_m, diff_y_p;

		double lax_friedrichs_flux;

		dx = _.dx;
		dy = _.dy;

		int index_cur, index_next;

		FVector_int index(5);
		FVector_double diff_val(5);


		// Variables for velocity 
		double det, jaco, deti;
		int pi;

		FVector_double XI(2);
		FVector_double vRealP(2);
		FMatrix_double DF(2, 2);
		FMatrix_double DFI(2, 2);
		FMatrix_double DFIT(2, 2);

		FVector_double U_h(2);
		FMatrix_double VPSI(4, 2);

		FVector_double pre_npsi(4);
		FMatrix_double pre_ndpsi(4, 2);

		FMatrix_double pre_Vpsi(4, 2);
		FCube_double pre_Vdpsi(4, 2, 2);

		voldPHI = vPHI;


		for (i_x = 0; i_x<nsE; i_x++) {
			for (i_y = 0; i_y<nsE; i_y++) {
				//cout << "Start : " << i_x << ", " << i_y << endl;
				e = i_x + i_y*_.nsR;

				//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
				//▩▩ Find velocity in each element   ▩▩
				//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
				// 1. Setting. Find vel_u_avg
				XI.setAll(0., 0.5);

				// 2. pre_npsi, pre_ndpsi, pre_Vpsi, pre_Vdpsi
				__.shape.domain(XI, pre_npsi, pre_ndpsi);
				__.shape.vector(XI, pre_Vpsi, pre_Vdpsi);


				// 3. DF 정확히 찾음
				FEM::MAPPING::make_realP_and_DF(vRealP, DF, pre_npsi, pre_ndpsi, _.coordN, _.indexN[e]);					// DF 구한다. // Real Point를 알아야 한다?
				det = MATH::inverse(DF, DFI);	DFIT.transposeFrom(DFI);	jaco = fabs(det);	deti = 1 / jaco;

				U_h.clear();
				for (i = 0; i < __.nvshape; i++) {
					pi = _.indexV(e, i);
					VPSI[i].op("=", deti*drtV[e][i], DF, pre_Vpsi[i]);
					U_h.op("+=", _.vCV[pi], VPSI[i]);
				}

				vel_u_left = U_h[0]; // vel=(u,v)

				XI.setAll(1., 0.5);
				// 2. pre_npsi, pre_ndpsi, pre_Vpsi, pre_Vdpsi
				__.shape.domain(XI, pre_npsi, pre_ndpsi);
				__.shape.vector(XI, pre_Vpsi, pre_Vdpsi);


				// 3. DF 정확히 찾음
				FEM::MAPPING::make_realP_and_DF(vRealP, DF, pre_npsi, pre_ndpsi, _.coordN, _.indexN[e]);					// DF 구한다. // Real Point를 알아야 한다?
				det = MATH::inverse(DF, DFI);
				DFIT.transposeFrom(DFI);	jaco = fabs(det);
				deti = 1 / jaco;

				U_h.clear();
				for (i = 0; i < __.nvshape; i++) {
					pi = _.indexV(e, i);
					VPSI[i].op("=", deti*drtV[e][i], DF, pre_Vpsi[i]);
					U_h.op("+=", _.vCV[pi], VPSI[i]);
				}
				//_problem->V(vRealP, U_h);
				vel_u_right = U_h[0]; // vel=(u,v)


				vel_u_avg = (vel_u_left + vel_u_right) / 2;


				// 1. Setting. Find vel_v_avg
				XI.setAll(0.5, 0.);

				// 2. pre_npsi, pre_ndpsi, pre_Vpsi, pre_Vdpsi
				__.shape.domain(XI, pre_npsi, pre_ndpsi);
				__.shape.vector(XI, pre_Vpsi, pre_Vdpsi);

				// 3. DF 정확히 찾음
				FEM::MAPPING::make_realP_and_DF(vRealP, DF, pre_npsi, pre_ndpsi, _.coordN, _.indexN[e]);					// DF 구한다. // Real Point를 알아야 한다?
				det = MATH::inverse(DF, DFI);	DFIT.transposeFrom(DFI);	jaco = fabs(det);	deti = 1 / jaco;

				U_h.clear();
				for (i = 0; i < __.nvshape; i++) {
					pi = _.indexV(e, i);
					VPSI[i].op("=", deti*drtV[e][i], DF, pre_Vpsi[i]);
					U_h.op("+=", _.vCV[pi], VPSI[i]);
				}
				//	_problem->V(vRealP, U_h);
				vel_v_bottom = U_h[1]; // vel=(u,v) 

				XI.setAll(0.5, 1.);

				// 2. pre_npsi, pre_ndpsi, pre_Vpsi, pre_Vdpsi
				__.shape.domain(XI, pre_npsi, pre_ndpsi);
				__.shape.vector(XI, pre_Vpsi, pre_Vdpsi);

				// 3. DF 정확히 찾음
				FEM::MAPPING::make_realP_and_DF(vRealP, DF, pre_npsi, pre_ndpsi, _.coordN, _.indexN[e]);					// DF 구한다. // Real Point를 알아야 한다?
				det = MATH::inverse(DF, DFI);	DFIT.transposeFrom(DFI);	jaco = fabs(det);	deti = 1 / jaco;

				U_h.clear();
				for (i = 0; i < __.nvshape; i++) {
					pi = _.indexV(e, i);
					VPSI[i].op("=", deti*drtV[e][i], DF, pre_Vpsi[i]);
					U_h.op("+=", _.vCV[pi], VPSI[i]);
				}
				vel_v_top = U_h[1]; // vel=(u,v) 

				vel_v_avg = (vel_v_bottom + vel_v_top) / 2.; // Done : find the velocity 



				/*▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
				  ▩▩ restruction of derivatives             ▩▩
				  ▩▩ - out of boudnary = diff at boundary   ▩▩
				  ▩▩ =>similar value of back/forward diff   ▩▩
				  ▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩*/

				// Find diff_x_m
				// diff_val = {dphi_{-3}, dphi_{-2}, d_phi_{-1}, d_phi_{0}, d_phi_{1}
				// dphi_{i} = phi(i+1) - phi(i) 
				for (i = 0; i < 5; i++) {
					index_temp = i_x + i - 3;
					if (index_temp < 0) {
						index_cur = 0 + i_y*_.nsR;
						index_next = 1 + i_y*_.nsR;
						diff_val[i] = voldPHI[index_next] - voldPHI[index_cur];
					}
					else if (index_temp + 1 >= nsE) {
						index_cur = (_.nsR - 2) + i_y*_.nsR;
						index_next = (_.nsR - 1) + i_y*_.nsR;
						diff_val[i] = voldPHI[index_next] - voldPHI[index_cur];
					}
					else {
						index_cur = index_temp + i_y*_.nsR;
						index_next = index_cur + 1;
						diff_val[i] = voldPHI[index_next] - voldPHI[index_cur];
					}
				}
				WENO35_diff_minus(diff_val, diff_x_m);

				// Find diff_x_p
				// diff_val = {dphi_{-2}, dphi_{-1}, d_phi_{0}, d_phi_{1}, d_phi_{2}
				// dphi_{i} = phi(i+1) - phi(i) 
				for (i = 0; i < 5; i++) {
					index_temp = i_x + i - 2;
					if (index_temp < 0) {
						index_cur = 0 + i_y*_.nsR;
						index_next = 1 + i_y*_.nsR;
						diff_val[i] = voldPHI[index_next] - voldPHI[index_cur];
					}
					else if (index_temp + 1 >= nsE) {
						index_cur = (_.nsR - 2) + i_y*_.nsR;
						index_next = (_.nsR - 1) + i_y*_.nsR;
						diff_val[i] = voldPHI[index_next] - voldPHI[index_cur];
					}
					else {
						index_cur = index_temp + i_y*_.nsR;
						index_next = index_cur + 1;
						diff_val[i] = voldPHI[index_next] - voldPHI[index_cur];
					}
				}
				WENO35_diff_plus(diff_val, diff_x_p);

				// Find diff_y_m
				// diff_val = {dphi_{-3}, dphi_{-2}, d_phi_{-1}, d_phi_{0}, d_phi_{1}
				// dphi_{i} = phi(i+1) - phi(i) 
				for (i = 0; i < 5; i++) {
					index_temp = i_y + i - 3;

					if (index_temp < 0) {
						index_cur = i_x + 0 * _.nsR;
						index_next = i_x + 1 * _.nsR;
						diff_val[i] = voldPHI[index_next] - voldPHI[index_cur];
					}
					else if (index_temp + 1 >= nsE) {
						index_cur = i_x + (_.nsR - 2) * _.nsR;
						index_next = i_x + (_.nsR - 1) * _.nsR;
						diff_val[i] = voldPHI[index_next] - voldPHI[index_cur];
					}
					else {
						index_cur = i_x + index_temp*_.nsR;
						index_next = index_cur + _.nsR;

						diff_val[i] = voldPHI[index_next] - voldPHI[index_cur];
					}
				}
				WENO35_diff_minus(diff_val, diff_y_m);

				// Find diff_y_p
				// diff_val = {dphi_{-2}, dphi_{-1}, d_phi_{0}, d_phi_{1}, d_phi_{2}
				// dphi_{i} = phi(i+1) - phi(i) 
				for (i = 0; i < 5; i++) {
					index_temp = i_y + i - 2;
					if (index_temp < 0) {
						index_cur = i_x + 0 * _.nsR;
						index_next = i_x + 1 * _.nsR;
						diff_val[i] = voldPHI[index_next] - voldPHI[index_cur];
					}
					else if (index_temp + 1 >= nsE) {
						index_cur = i_x + (_.nsR - 2) * _.nsR;
						index_next = i_x + (_.nsR - 1) * _.nsR;
						diff_val[i] = voldPHI[index_next] - voldPHI[index_cur];
					}
					else {
						index_cur = i_x + index_temp*_.nsR;
						index_next = index_cur + _.nsR;
						//cout << i_x << "," << i_y << ": " << "index cur : " << index_cur << ",   index next : " << index_next << endl;
						diff_val[i] = voldPHI[index_next] - voldPHI[index_cur];
					}
				}
				WENO35_diff_plus(diff_val, diff_y_p);



				LLF_flux(diff_x_p, diff_x_m, diff_y_p, diff_y_m, vel_u_avg, vel_v_avg, lax_friedrichs_flux);


				// Update vPHI(e)
				vPHI[e] = voldPHI[e] - dt*lax_friedrichs_flux;

			} //i_y


		}//i_x


		voldPHI = vPHI;
		//draw_PHI("test_PHI", 0);
	}
	
	//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
	//▩▩  projection for interface points					  ▩▩
	//▩▩ - A Hybrid Method for Moving Interface Problems ~   ▩▩
	//▩▩   Section3.1         by Zhinlin Li				      ▩▩
	//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
	void FIND_INTERFACE_POINTS(int it, int draw_count=1) {
		//cout << "FIND_INTERFACE_POINTS  : Start" << endl;
		int i, j, k, e, e0, e1, e2, e3; 
		double a, b, c, x, y;
		double phi, phi_x, phi_y, phi_xx, phi_yy, phi_xy, alpha, phi_yx;
		FMatrix_double He(2, 2);
		FVector_double vHeP(2);
		FVector_double P(2);
		Interface_Element_Curvature.clear();
		double curvature_=0.;
		for (k = 0; k < nCI; k++) {

			i = CI(k, 0);
			j = CI(k, 1);

			x = CP(k, 0);
			y = CP(k, 1);

			phi=vPHI(i+ j*_.nsR);

			phi_x = (vPHI(i + 1 + j*_.nsR) - vPHI(i - 1 + j*_.nsR))/2/_.dx;
			phi_y = (vPHI(i + (j+1)*_.nsR) - vPHI(i + (j-1)*_.nsR)) / 2 / _.dy;

			phi_xx = (vPHI(i + 1 + j*_.nsR) + vPHI(i - 1 + j*_.nsR) - 2 * vPHI(i + j*_.nsR)) / _.dx / _.dx;
			phi_yy = (vPHI(i + (j+1)*_.nsR) + vPHI(i + (j-1)*_.nsR) - 2 * vPHI(i + j*_.nsR)) / _.dy / _.dy;
			phi_xy = (vPHI(i + 1 + j*_.nsR) - vPHI(i - 1 + j*_.nsR) - vPHI(i + 1 + (j - 1)*_.nsR) + vPHI(i - 1 +( j - 1)*_.nsR) ) / _.dx / _.dx / 4;
			//phi_yx = (vPHI(i+ (j+1)*_.nsR) - vPHI(i + (j-1)*_.nsR) - vPHI(i -1 + (j + 1)*_.nsR) + vPHI(i - 1 + (j - 1)*_.nsR)) / _.dx / _.dx / 4;
		//	curvature_ = -(phi_xx * phi_y * phi_y - 2* phi_xy *phi_x * phi_y + phi_yy *phi_x*phi_x )/ pow(phi_x*phi_x +phi_y* phi_y  , 1.5);
			 

			He(0, 0) = phi_xx;
			He(0, 1) = phi_xy;
			He(1, 0) = phi_xy;
			He(1, 1) = phi_yy;

			P.setAll(phi_x, phi_y);
			P.normalize();


			c = phi;
			b = sqrt(phi_x*phi_x + phi_y*phi_y);
			vHeP.op("=", He, P);
			a = (vHeP, P) / 2.;

			if (b*b - 4 * a*c < 0) {
				
				cout << "sqrt is not defined" << endl;
				cout << "e_x : " << i << ",  e_y : " << j << endl;
				cout << "value : " << b*b - 4 * a*c << endl;
				draw_levelset("ERROR_IP_Level_set", it);
				draw_CP("ERROR_CP");
				system("pause");
			}

			alpha = (-b + sqrt(b*b - 4 * a*c)) / 2 / a;

			IP(k, 0) = x + alpha*P(0);
			IP(k, 1) = y + alpha*P(1);

		//	Interfact_Element_Curvature[i + j*_.nsR]=curvature_;
			// Modify IP


			// Save IP
			if (it%draw_count==0 && draw_count!=-1){
				char buffer[128];
				sprintf(buffer, "%s%d_%d.txt", "IP",__.nLayer,it/draw_count);
				FILE *fp = fopen(buffer, "w");

				for (j = 0; j<nCI; j++) {
					for (i = 0; i<2; i++) {
						fprintf(fp, "%.8f \t", IP[j][i]);
					}
					fprintf(fp, "\n");
				}

				fclose(fp);
			}	
		}

		//cout << "FIND_INTERFACE_POINTS  : END" << endl;
	}   
	
	//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
	//▩▩         문제생김     : num_adj !=2			          ▩▩
	//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
	void is_Connected(int e1, int e2, bool& isConnected) {
		/* e1과 e2가 연결되어 있는지 확인한다.
			- e1과 e2를 포함하는 2*2 square를 생각한다.
		   1.  e1, e2가 대각선
			- 이 square에서  phi부호가 +인 element가 있으면 e1과 e2는 연결되어있다.
		   2. e1, e2가 인접해 있는 경우
		    - 이 square에서 e1/e2가 아닌 원소들의 phi 부호가 모두 +여야 연결되어있다.

		*/
		isConnected = false;

		int i, j, k, e;
		int e1_x, e1_y, e2_x, e2_y;
		int neighbor_e1, neighbor_e2;
		int distance,d_x,d_y;
		bool is_there_pos;

		double phi_val[2];


		e1_x = e1%_.nsR;
		e1_y = e1 / _.nsR;
		e2_x = e2%_.nsR;
		e2_y = e2 / _.nsR;

		distance = abs(e1_x - e2_x) + abs(e1_y - e2_y);

		// ERROR !!
		if (distance > 2||distance<=0) {
			cout << "find_Control_Points => is_Connected : wrong e1,e2 " << endl;
			cout << "e1 : " << e1 << ",  e2 : " << e2 << endl;
			cout << "e1 : e1_x=" << e1%_.nsR << "   e1_y=" << e1 / _.nsR << endl;
			cout << "e2 : e2_x=" << e2%_.nsR << "   e2_y=" << e2 / _.nsR << endl;
			cout << "distance(l1-norm) : " << distance << endl;

			draw_levelset("Error_level_set_is_Connected",0);

			// Sace CP
			char buffer2[128];
			sprintf(buffer2, "%s.txt", "ERROR_CP");
			FILE *fp2 = fopen(buffer2, "w");
			for (j = 0; j<nCI; j++) {
				CP[j][0] = __.RX[0][0] + _.dx*(CI[j][0] + 0.5);
				CP[j][1] = __.RX[0][1] + _.dy*(CI[j][1] + 0.5);
				for (i = 0; i<2; i++) {
					fprintf(fp2, "%f \t", CP[j][i]);
				}
				fprintf(fp2, "\n");
			}

			fclose(fp2);	

			system("pause");
		}

		if (distance == 1) {
			d_x = abs(e2_x - e1_x);
			d_y = abs(e2_y - e1_y);

			//int direction[2] = { -1, 1 };
			FVector_int direction(2);
			direction.setAll(1, -1);

			if (d_x == 1) {
				for (i = 0; i < 2; i++) {
					neighbor_e1 = e1 + direction[i] * _.nsR;
					neighbor_e2 = e2 + direction[i] * _.nsR;

					phi_val[0] = vPHI[neighbor_e1];
					phi_val[1] = vPHI[neighbor_e2];


					//phi_val[0,1]모두 positive여야 연결된것
					if (phi_val[0] > 0 && phi_val[1] > 0) {
						isConnected = true;
						return;
					}
						
				}
				isConnected = false;
				return;
			}
			if (d_y == 1) {
				for (i = 0; i < 2; i++) {
					neighbor_e1 = e1 + direction[i];
					neighbor_e2 = e2 + direction[i];

					phi_val[0] = vPHI[neighbor_e1];
					phi_val[1] = vPHI[neighbor_e2];

					//// sss
					//if (e1 == 208 && e2 == 176) {
					//	cout << "direction : " << direction[i] << endl;
					//	cout << phi_val[0] << endl;
					//	cout << phi_val[1] << endl;
					//}

					//phi_val[0,1]모두 positive여야 연결된것
					if (phi_val[0] > 0 && phi_val[1] > 0) {
						isConnected = true;
						return;
					}
				}

				isConnected = false;
				return;
			}
		}

		if (distance == 2) {
			d_x = e2_x - e1_x;
			d_y = e2_y - e1_y;

			neighbor_e1 = e1 + d_x;
			neighbor_e2 = e1 + d_y*_.nsR;

			phi_val[0] = vPHI[neighbor_e1];
			phi_val[1] = vPHI[neighbor_e2];

			is_there_pos = false;
			for (i = 0; i < 2; i++) {
				if (phi_val[i] > 0) {
					is_there_pos = true;
				}
			}

			if (is_there_pos)
				isConnected = true;
			else
				isConnected = false;
			return;
		}
	}

	void find_all_CIs() {
		/*
		우선 CI(control index)만 생각한다.
		함수의 맨마지막에 CP(control point)를 계산하여 저장한다.
		i.e CP[i][0] = __.RX[0][0] + _.dx*(CI[i][0] + 0.5)
		CP[i][1] = __.RX[0][1] + _.dy*(CI[i][1] + 0.5)
		*/
		// CI, CP 초기화
		CI.clear(-1.);
		CP.clear(-1.);

		// common variables
		int e, eM, i, j, k, l;
		int count, num_neighbor_neg;
		int cur_e;
		double cur_phi;
		// 0: left 1:right 2:up 3:down
		int neighbor_e[4];
		int neighbor_e_i[4], neighbor_e_j[4];
		double neighbor_phi[4];

		bool repeat_;

		/*
		Step 1 : CI 구하기
		- phi>0인 element 주변(4방향)의 element의 phi값이 음수인 경우 CI/CP로 생각한다.
		- 우선 순서는 생각하지 않고 값을 저장한다
		*/

		count = 0;
		for (i = 1; i < _.nsR - 1; i++) {
			for (j = 1; j < _.nsR - 1; j++) {

				cur_e = i + j*_.nsR;
				cur_phi = vPHI(cur_e);

				//현재 노드의 phi값이 - 가 아니면 무시
				if (cur_phi < 0) {
					continue;
				}

				neighbor_e[0] = cur_e - 1;
				neighbor_e[1] = cur_e + 1;
				neighbor_e[2] = cur_e + _.nsR;
				neighbor_e[3] = cur_e - _.nsR;

				neighbor_e_i[0] = i - 1; neighbor_e_j[0] = j;
				neighbor_e_i[1] = i + 1; neighbor_e_j[1] = j;
				neighbor_e_i[2] = i; neighbor_e_j[2] = j + 1;
				neighbor_e_i[3] = i; neighbor_e_j[3] = j - 1;

				for (k = 0; k < 4; k++) {
					neighbor_phi[k] = vPHI(neighbor_e[k]);
				}

				num_neighbor_neg = 0;
				for (k = 0; k < 4; k++) {
					if (neighbor_phi[k] < 0)
						num_neighbor_neg++;
				}

				// num_neighbor_neg==4 : vPHI값의 오류(NOT simply connected)
				if (num_neighbor_neg == 4) {
					cout << "find_Control_Points=>find_all_CIs : vPHI is NOT simply connected" << endl;
					cout << "cur_e : e_x=" << i << ",   e_y=" << j << endl;
					for (k = 0; k < 4; k++) {
						cout << neighbor_phi[k] << endl;
					}
					draw_levelset("ERROR_FCP_LEVELSET_", 0);
					system("pause");
				}

				// vPHI값이 음수인 주변 노드의 갯수가 1,2,3인경우만 control point이다.
				if (num_neighbor_neg != 0 && num_neighbor_neg != 4) {
					// vPHI값이 음수인 주변 노드를 저장한다.
					for (k = 0; k < 4; k++) {

						if (neighbor_phi[k] < 0) {

							// 처음 노드인 경우
							if (count == 0) {
								CI[count].setAll(neighbor_e_i[k], neighbor_e_j[k]);
								count = count + 1;
							}
							// 처음 노드가 아닌 경우 => 중복 검사
							else {
								//vRealP.setAll(__.RX[0][0] + (i + 0.5)*_.dx, __.RX[0][1] + (j + 0.5)*_.dy);

								//중복 검사
								repeat_ = false;
								for (l = 0; l < count; l++) {
									if ((CI[l][0] - neighbor_e_i[k])*(CI[l][0] - neighbor_e_i[k]) + (CI[l][1] - neighbor_e_j[k])*(CI[l][1] - neighbor_e_j[k]) == 0) {
										repeat_ = true;
										break;
									}
								}

								// 중복이 아닌경우 (repeat_==false) => CI update
								if (repeat_ == false) {
									CI[count].setAll(neighbor_e_i[k], neighbor_e_j[k]);
									count = count + 1;
								}
							}
						}//if (neighbor_phi[k] < 0)
					}//k : neighbor node


				}//if (num_neighbor_neg != 0 || num_neighbor_neg != 4)
			}
		}

		nCI = count;
	}

	void ordering_CIs() {
		/*
		Step 2 : CI 연결하기 (CI-Ordering)
		1)e1과 e2가 연결되어 있는지 확인한다.
		우선 e1에 인접한(8방향) prev_CI가 아닌 CI들의 갯수(n_possibles)를 구한다.
		- n_possibles== 1 =>  CI를 next_CI에 저장
		- n_possibles > 2 
		=> is_Connected 함수를 이용하여 실제 연결된 CI찾는다
		*/
		int i, j, k, e;
		int prev_element, cur_e,next_e;
		int n_possibles, n_neighbors;
		int e_x, e_y;
		bool isConnected;
		FVector_int vNeighbor_idx(8), neighbor_e(8);

		FMatrix_int copy_CI(nCI, 2);
		FMatrix_int direction(8, 2);
		direction.setAll(-1, 0, -1, -1, 0, -1, 1, -1, 1, 0, 1, 1, 0, 1, -1, 1);

		// n_neighbors == 2 일때 사용할 변수들
		FVector_int xy_direction(2);
		xy_direction.setAll(1, _.nsR);
		bool isIgnored[2];
		int e1, e2;
		double phi1, phi2;

		//copy_CI = CI;
		for (i = 0; i < nCI; i++) {
			copy_CI[i][0] = CI[i][0];
			copy_CI[i][1] = CI[i][1];
		}
		
		CI.clear(-1);

		//i=0
		CI[0] = copy_CI[0];
		e_x = CI[0][0];
		e_y = CI[0][1];
		//Search with 8 direction
		vNeighbor_idx.clear(-1);
		for (i = 0; i < 8; i++) {
			cur_e = (e_x + direction[i][0]) + (e_y + direction[i][1])*_.nsR;
			for (j = 0; j < nCI; j++) {
				if (cur_e == (copy_CI[j][0] + copy_CI[j][1] * _.nsR)) {
					vNeighbor_idx[0] = cur_e;
					break;
				}
			}
			if (vNeighbor_idx[0] != -1)
				break;
		}

		CI[1][0] = vNeighbor_idx[0] % _.nsR;
		CI[1][1] = vNeighbor_idx[0] / _.nsR;
		
		// i>0
		for (e = 1; e < nCI - 1; e++) {
			vNeighbor_idx.clear(-1);
			n_possibles = 0;
			prev_element = CI[e - 1][0] + CI[e - 1][1] * _.nsR;
			e_x = CI[e][0];
			e_y = CI[e][1];

			if (e_x == CI[0][0] && e_y == CI[0][1]) {
				break;
			}

			for (i = 0; i < 8; i++) {
				cur_e = (e_x + direction[i][0]) + (e_y + direction[i][1])*_.nsR;
				if (cur_e == prev_element) {
					continue;
				}

				for (j = 0; j < nCI; j++) {
					if (cur_e == (copy_CI[j][0] + copy_CI[j][1] * _.nsR)) {
						vNeighbor_idx[n_possibles] = cur_e;
						n_possibles++;
					}
				}
			}

			/*
			//우선은 예외로 처리한다.
			if (n_possibles == 0) {
				cout << "find_Control_Points=>ordering_CIs : 예외" << endl;
				draw_levelset("ERROR_FCP_LEVELSET_", 0);
				// Sace CP

				char buffer2[128];
				sprintf(buffer2, "%s%d.txt", "ERROR_CP", __.nLayer);
				FILE *fp2 = fopen(buffer2, "w");
				for (j = 0; j<nCI; j++) {
					CP[j][0] = __.RX[0][0] + _.dx*(copy_CI[j][0] + 0.5);
					CP[j][1] = __.RX[0][1] + _.dy*(copy_CI[j][1] + 0.5);
					for (i = 0; i<2; i++) {
						fprintf(fp2, "%f \t", CP[j][i]);
					}
					fprintf(fp2, "\n");
				}

				fclose(fp2);

				system("pause");
			}
			*/

			//n_possibles == 1 : CI update
			if (n_possibles == 1) {
				CI[e + 1][0] = vNeighbor_idx[0] % _.nsR;
				CI[e + 1][1] = vNeighbor_idx[0] / _.nsR;
				continue;
			}

			//n_possibles > 1 : 연결된 점 찾기
			neighbor_e.clear(-1);
			n_neighbors = 0;
			cur_e = CI[e][0] + CI[e][1] * _.nsR;
			for (i = 0; i < n_possibles; i++) {
				next_e = vNeighbor_idx[i];

				is_Connected(cur_e, next_e, isConnected);
				if (isConnected) {
					neighbor_e[n_neighbors] = next_e;
					n_neighbors++;
				}
			}

			if (n_neighbors == 1) {
				CI[e + 1][0] = neighbor_e[0] % _.nsR;
				CI[e + 1][1] = neighbor_e[0] / _.nsR;
			}
			else if (n_neighbors == 2) {
				isIgnored[0] = false;
				isIgnored[1] = false;
				for (i = 0; i < n_neighbors; i++) {
					
					for (j = 0; j < 2; j++) {
						e1 = neighbor_e[i] + xy_direction[j];
						e2 = neighbor_e[i] - xy_direction[j];
						phi1 = vPHI[e1];
						phi2 = vPHI[e2];

						if (phi1 > 0 && phi2 > 0) {
							isIgnored[i] = true;
							break;
						}
					}
				}
				////temp
				//cout << "current e : e_x=" << CI[e][0] << ",  e_y=" << CI[e][1] << endl;
				//cout << "n_neighbors == 2 -  isIngored : " << endl;
				//cout << isIgnored[0] << "   , " << isIgnored[1] << endl;

				for (i = 0; i < n_neighbors; i++) {
					if (isIgnored[i]==false) {
						CI[e + 1][0] = neighbor_e[i] % _.nsR;
						CI[e + 1][1] = neighbor_e[i] / _.nsR;
						cout << "A node is ignored ....." << endl;
					}
				}

			}


			// ERROR : n_neighbors >2
			else {
				cout << "find_Control_Points=>ordering_CIs : n_neighbors is wrong" << endl;
				cout << "current e : e_x=" << CI[e][0] << ",  e_y=" << CI[e][1] << endl;
				cout << "n_neighbors : " << n_neighbors << "  n_possibles : " << n_possibles << endl;
				
				draw_levelset("ERROR_FCP_LEVELSET_", 0);
				
				// Sace CP
				char buffer2[128];
				sprintf(buffer2, "%s.txt", "ERROR_CP");
				FILE *fp2 = fopen(buffer2, "w");
				for (j = 0; j<nCI; j++) {
					CP[j][0] = __.RX[0][0] + _.dx*(copy_CI[j][0] + 0.5);
					CP[j][1] = __.RX[0][1] + _.dy*(copy_CI[j][1] + 0.5);
					for (i = 0; i<2; i++) {
						fprintf(fp2, "%f \t", CP[j][i]);
					}
					fprintf(fp2, "\n");
				}

				fclose(fp2);

				cout << "neigbhor e :" ;
				neighbor_e.print();
				cout << "vNeighbor_idx : ";
				vNeighbor_idx.print();
				system("pause");
			}

			

		}

		nCI = e;//????

	}

	void find_Control_Points(int it, int draw_count=1) {
		
		int i, j;
		//Find all CIs
		find_all_CIs(); 
		
		//Order all CIs
		ordering_CIs();
	
		// Update CP
		for (i = 0; i<nCI; i++) {
			CP[i][0] = __.RX[0][0] + _.dx*(CI[i][0] + 0.5);
			CP[i][1] = __.RX[0][1] + _.dy*(CI[i][1] + 0.5);
		}
		
		// Sace CP
		if (it%draw_count==0 && draw_count!=-1){
			char buffer2[128];
			sprintf(buffer2, "%s%d_%d.txt", "CP", __.nLayer, it/draw_count);
			FILE *fp2 = fopen(buffer2, "w");
			for (j = 0; j<nCI; j++) {
				for (i = 0; i<2; i++) {
					fprintf(fp2, "%f \t", CP[j][i]);
				}
				fprintf(fp2, "\n");
			}

			fclose(fp2);
		}
	}


	void find_Control_Points_origin(int it, int draw_count = 1) {

		int e, eM, i, j, k;
		int e0, e1, e2, e3;
		FVector_double vRealP(__.dim);
		FVector_double vRealP2(__.dim);
		double phi0, phi1, phi2, phi3;
		bool repeat_;

		// CE[element][0] :# of adjacent element 
		// CE[element][1~2]: index of adjacent element 
		FMatrix_int CE(_.neT, 3);


		CI.clear(-1.);
		CP.clear(-1.);
		CE.clear(0);

		int count = 0;
		int num_neg;
		for (i = 0; i<_.nsR - 1; i++) {
			for (j = 0; j<_.nsR - 1; j++) {

				// element index = i+j*_.nsR
				// e0~e3 : element 
				e0 = i + j*_.nsR;
				e1 = i + 1 + j*_.nsR;
				e2 = i + 1 + (j + 1)*_.nsR;
				e3 = i + (j + 1)*_.nsR;

				phi0 = vPHI(e0);
				phi1 = vPHI(e1);
				phi2 = vPHI(e2);
				phi3 = vPHI(e3);

				num_neg = 0;

				if (phi0 < 0) num_neg++;
				if (phi1 < 0) num_neg++;
				if (phi2 < 0) num_neg++;
				if (phi3 < 0) num_neg++;

				//cout << "e0 : "<<e0<< " num_neg : "<<num_neg << endl;

				if (num_neg == 2 || num_neg == 3)
				{
					if (phi0<0)
					{
						if (count == 0)
						{
							CI(count).setAll(i, j);
							CP(count).setAll(__.RX[0][0] + (i + 0.5)*_.dx, __.RX[0][1] + (j + 0.5)*_.dy);
							count = count + 1;
						}
						else
						{
							vRealP.setAll(__.RX[0][0] + (i + 0.5)*_.dx, __.RX[0][1] + (j + 0.5)*_.dy);
							repeat_ = false;
							for (k = 0; k<count; k++) {
								if ((CP[k][0] - vRealP[0])*(CP[k][0] - vRealP[0]) + (CP[k][1] - vRealP[1])*(CP[k][1] - vRealP[1]) < 0.000001) {
									repeat_ = true;
									break;
								}
							}
							if (repeat_ == false) {
								CI(count).setAll(i, j);
								CP(count).setAll(__.RX[0][0] + (i + 0.5)*_.dx, __.RX[0][1] + (j + 0.5)*_.dy);
								count = count + 1;
							}
						}
						//CE update
						if (phi1 < 0)
						{
							if (CE[e0][0] == 0)
							{
								CE[e0][1] = e1;
								CE[e0][0] = CE[e0][0] + 1;
							}
							if (CE[e0][0] == 1 && CE[e0][1] != e1)
							{
								CE[e0][2] = e1;
								CE[e0][0] = CE[e0][0] + 1;
							}

						}
						if (phi3 < 0)
						{
							if (CE[e0][0] == 0)
							{
								CE[e0][1] = e3;
								CE[e0][0] = CE[e0][0] + 1;
							}
							if (CE[e0][0] == 1 && CE[e0][1] != e3)
							{
								CE[e0][2] = e3;
								CE[e0][0] = CE[e0][0] + 1;
							}
						}
					} // if phi_0 <0
					if (phi1<0) {
						if (count == 0) {
							CI(count).setAll(i + 1, j);
							CP(count).setAll(__.RX[0][0] + (i + 1.5)*_.dx, __.RX[0][1] + (j + 0.5)*_.dy);
							count = count + 1;
						}
						else {
							vRealP.setAll(__.RX[0][0] + (i + 1.5)*_.dx, __.RX[0][1] + (j + 0.5)*_.dy);
							repeat_ = false;
							for (k = 0; k<count; k++) {
								if ((CP[k][0] - vRealP[0])*(CP[k][0] - vRealP[0]) + (CP[k][1] - vRealP[1])*(CP[k][1] - vRealP[1]) < 0.000001) {
									repeat_ = true;
									break;
								}
							}
							if (repeat_ == false) {
								CI(count).setAll(i + 1, j);
								CP(count).setAll(__.RX[0][0] + (i + 1.5)*_.dx, __.RX[0][1] + (j + 0.5)*_.dy);
								count = count + 1;
							}
						}
						//CE update
						if (phi0 < 0)
						{
							if (CE[e1][0] == 0)
							{
								CE[e1][1] = e0;
								CE[e1][0] = CE[e1][0] + 1;
							}
							if (CE[e1][0] == 1 && CE[e1][1] != e0)
							{
								CE[e1][2] = e0;
								CE[e1][0] = CE[e1][0] + 1;
							}

						}
						if (phi2 < 0)
						{
							if (CE[e1][0] == 0)
							{
								CE[e1][1] = e2;
								CE[e1][0] = CE[e1][0] + 1;
							}
							if (CE[e1][0] == 1 && CE[e1][1] != e2)
							{
								CE[e1][2] = e2;
								CE[e1][0] = CE[e1][0] + 1;
							}
						}
					} // if phi_1 <0
					if (phi2<0) {
						if (count == 0) {
							CI(count).setAll(i + 1, j + 1);
							CP(count).setAll(__.RX[0][0] + (i + 1.5)*_.dx, __.RX[0][1] + (j + 1.5)*_.dy);
							count = count + 1;
						}
						else {
							vRealP.setAll(__.RX[0][0] + (i + 1.5)*_.dx, __.RX[0][1] + (j + 1.5)*_.dy);
							repeat_ = false;
							for (k = 0; k<count; k++) {
								if ((CP[k][0] - vRealP[0])*(CP[k][0] - vRealP[0]) + (CP[k][1] - vRealP[1])*(CP[k][1] - vRealP[1]) < 0.000001) {
									repeat_ = true;
									break;
								}
							}
							if (repeat_ == false) {
								CI(count).setAll(i + 1, j + 1);
								CP(count).setAll(__.RX[0][0] + (i + 1.5)*_.dx, __.RX[0][1] + (j + 1.5)*_.dy);
								count = count + 1;
							}
						}
						//CE update
						if (phi1 < 0)
						{
							if (CE[e2][0] == 0)
							{
								CE[e2][1] = e1;
								CE[e2][0] = CE[e2][0] + 1;
							}
							if (CE[e2][0] == 1 && CE[e2][1] != e1)
							{
								CE[e2][2] = e1;
								CE[e2][0] = CE[e2][0] + 1;
							}

						}
						if (phi3 < 0)
						{
							if (CE[e2][0] == 0)
							{
								CE[e2][1] = e3;
								CE[e2][0] = CE[e2][0] + 1;
							}
							if (CE[e2][0] == 1 && CE[e2][1] != e3)
							{
								CE[e2][2] = e3;
								CE[e2][0] = CE[e2][0] + 1;
							}
						}
					}	// if phi_2 <0
					if (phi3<0) {
						if (count == 0) {
							CI(count).setAll(i, j + 1);
							CP(count).setAll(__.RX[0][0] + (i + 0.5)*_.dx, __.RX[0][1] + (j + 1.5)*_.dy);
							count = count + 1;
						}
						else {
							vRealP.setAll(__.RX[0][0] + (i + 0.5)*_.dx, __.RX[0][1] + (j + 1.5)*_.dy);
							repeat_ = false;
							for (k = 0; k<count; k++) {
								if ((CP[k][0] - vRealP[0])*(CP[k][0] - vRealP[0]) + (CP[k][1] - vRealP[1])*(CP[k][1] - vRealP[1]) < 0.000001) {
									repeat_ = true;
									break;
								}
							}
							if (repeat_ == false) {
								CI(count).setAll(i, j + 1);
								CP(count).setAll(__.RX[0][0] + (i + 0.5)*_.dx, __.RX[0][1] + (j + 1.5)*_.dy);
								count = count + 1;
							}
						}
						//CE update
						if (phi0 < 0)
						{
							if (CE[e3][0] == 0)
							{
								CE[e3][1] = e0;
								CE[e3][0] = CE[e3][0] + 1;
							}
							if (CE[e3][0] == 1 && CE[e3][1] != e0)
							{
								CE[e3][2] = e0;
								CE[e3][0] = CE[e3][0] + 1;
							}

						}
						if (phi2 < 0)
						{
							if (CE[e3][0] == 0)
							{
								CE[e3][1] = e2;
								CE[e3][0] = CE[e3][0] + 1;
							}
							if (CE[e3][0] == 1 && CE[e3][1] != e2)
							{
								CE[e3][2] = e2;
								CE[e3][0] = CE[e3][0] + 1;
							}
						}
					}	// if phi_3 <0
				} // Interface
			}	// j
		}	// i

			// 수정부분 :count
			//count = count - 1;

		nCI = count;


		// Curve Algorithm
		FVector_int vHandle_idx(count);
		FMatrix_int copy_CI(count, 2);

		FMatrix_int adj(2, 2);
		int idx_ci[2];
		int adj_ct;
		copy_CI = CI;
		CI.clear(-1);

		CI[0] = copy_CI[0];
		int idx1, idx2;

		int i_x, i_y;


		//i==0
		vHandle_idx[0] = 0;
		i_x = CI[0][0];
		i_y = CI[0][1];


		//Search
		for (j = 0; j<count; j++)
		{
			if (copy_CI[j][0] == i_x + 1 && copy_CI[j][1] == i_y)
			{
				idx_ci[0] = j;
				break;
			}
			if (copy_CI[j][0] == i_x && copy_CI[j][1] == i_y + 1)
			{
				idx_ci[0] = j;
				break;
			}
			if (copy_CI[j][0] == i_x - 1 && copy_CI[j][1] == i_y)
			{
				idx_ci[0] = j;
				break;
			}
			if (copy_CI[j][0] == i_x && copy_CI[j][1] == i_y - 1)
			{
				idx_ci[0] = j;
				break;
			}
		}

		CI[1][0] = copy_CI[idx_ci[0]][0];
		CI[1][1] = copy_CI[idx_ci[0]][1];
		vHandle_idx[1] = idx_ci[0];


		for (i = 1; i<count - 1; i++)
		{
			//	CI.print();
			adj_ct = 0;

			idx_ci[0] = -1;
			idx_ci[1] = -1;

			i_x = CI[i][0];
			i_y = CI[i][1];

			// element index = i_x+i_y*_.nsR
			e = i_x + i_y*_.nsR;

			//	cout << "i_x: " << i_x << endl;
			//	cout << "i_y: " << i_y << endl;

			//Search
			for (j = 0; j<count; j++)
			{
				if (copy_CI[j][0] + 1 == i_x && copy_CI[j][1] == i_y)
				{
					if (CE[e][1] == (i_x - 1) + i_y*_.nsR || CE[e][2] == (i_x - 1) + i_y*_.nsR)
					{
						idx_ci[adj_ct] = j;
						adj_ct++;
					}
				}
				if (copy_CI[j][0] == i_x && copy_CI[j][1] + 1 == i_y)
				{
					if (CE[e][1] == i_x + (i_y - 1)*_.nsR || CE[e][2] == i_x + (i_y - 1)*_.nsR)
					{
						idx_ci[adj_ct] = j;
						adj_ct++;
					}
				}
				if (copy_CI[j][0] - 1 == i_x && copy_CI[j][1] == i_y)
				{
					if (CE[e][1] == (i_x + 1) + i_y*_.nsR || CE[e][2] == (i_x + 1) + i_y*_.nsR)
					{
						idx_ci[adj_ct] = j;
						adj_ct++;
					}
				}
				if (copy_CI[j][0] == i_x && copy_CI[j][1] - 1 == i_y)
				{
					if (CE[e][1] == i_x + (i_y + 1)*_.nsR || CE[e][2] == i_x + (i_y + 1)*_.nsR)
					{
						idx_ci[adj_ct] = j;
						adj_ct++;
					}
				}
			}


			if (adj_ct != 2) {
				cout << "Warning: find_Control_Points " << endl;
				cout << "adj_ct not 2   adj_ct = " << adj_ct << endl;
				cout << "ix : " << i_x << "  iy : " << i_y << endl;




				// Sace CP
				for (i = 0; i<count; i++) {
					CP[i][0] = __.RX[0][0] + _.dx*(copy_CI[i][0] + 0.5);
					CP[i][1] = __.RX[0][1] + _.dy*(copy_CI[i][1] + 0.5);
				}

				char buffer2[128];
				sprintf(buffer2, "%s.txt", "ERROR_CP");
				FILE *fp2 = fopen(buffer2, "w");
				for (j = 0; j<count; j++) {
					for (i = 0; i<2; i++) {
						fprintf(fp2, "%f \t", CP[j][i]);
					}
					fprintf(fp2, "\n");
				}

				fclose(fp2);
				draw_levelset("Error_FCP_LevelSet", 0);

				CE[e].print();
				system("pause");
			}

			repeat_ = false;
			//
			for (k = 0; k<i; k++)
			{
				if (vHandle_idx[k] == idx_ci[0])
				{
					repeat_ = true;
					break;
				}
			}
			if (repeat_ == true)
			{
				CI[i + 1][0] = copy_CI[idx_ci[1]][0];
				CI[i + 1][1] = copy_CI[idx_ci[1]][1];
				vHandle_idx[i + 1] = idx_ci[1];
			}
			else
			{
				CI[i + 1][0] = copy_CI[idx_ci[0]][0];
				CI[i + 1][1] = copy_CI[idx_ci[0]][1];
				vHandle_idx[i + 1] = idx_ci[0];
			}

		}	// search i

		for (i = 0; i<count; i++) {
			CP[i][0] = __.RX[0][0] + _.dx*(CI[i][0] + 0.5);
			CP[i][1] = __.RX[0][1] + _.dy*(CI[i][1] + 0.5);
		}
		// Save CP
		/*
		char buffer[128];
		sprintf(buffer, "%s.txt", "CI");

		FILE *fp = fopen(buffer, "w");

		for (j = 0; j<count; j++) {
		for (i = 0; i<2; i++) {
		fprintf(fp, "%d \t", CI[j][i]);
		}
		fprintf(fp, "\n");
		}

		fclose(fp);
		*/

		//	sprintf(buffer2, "%s.txt", "CP");

		// Sace CP
		if (it%draw_count == 0 && draw_count != -1) {
			char buffer2[128];
			sprintf(buffer2, "%s%d_%d.txt", "CP", __.nLayer, it / draw_count);
			FILE *fp2 = fopen(buffer2, "w");



			for (j = 0; j<count; j++) {
				for (i = 0; i<2; i++) {
					fprintf(fp2, "%f \t", CP[j][i]);
				}
				fprintf(fp2, "\n");
			}

			fclose(fp2);
		}
	}
	//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
	//▩▩    boundary 처리 이전의 matrix인 primitive matrix를 생성한다.  ▩▩
	//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
	void MAKE_PRIMITIVE_MASS_MATRIX(double t) {
		_.mA.clear();
		_.vF.clear();
		// [ Variables ]
		int i, j, l, nl, iN, mi;
		int e, eN;
		int edge;
		int pi, pj;															//▷ global pressure number
		int k;																//▷ Gauss points
		double det, jaco, jacoWeight;
		double f;
		double gamma = 10.;
		double size_h = 1.;
		bool bCalculate;
		double weight;
		double eps = 1.;
		double pb;
		double gp;
		FVector_double vRealP(__.dim), vRealP_N(__.dim), vF(__.dim), vIm(__.dim), vDOF(8);
		FMatrix_double DF(__.dim, __.dim), DF_N(__.dim, __.dim), DFIT(__.dim, __.dim);

		// ◈ IIM Variables     ◈
		int nsbMax, nsbMax_N;												//▷ subgrid 개수 (Noninterface의 경우는 1개가 된다.)
		int nsb, nsbN;														//▷ 현재의 가리키는 subgrid의 번호
		int nPoly;															//▷ subgrid 의 polygon type
		FVector_double mus(2);

		double fluxJump;													//▷ flux jump값을 저장한다.
		double jaco_l, jacoWeight_l;

		FVector_double vN(__.dim);											//▷ interface에서 normal vector
		FVector_double vStartP(__.dim);										//▷ Line integral의 Line 시작점
		FVector_double vEndP(__.dim);										//▷ Line integral의 Line 끝점
		// ◈ Clone Variables   ◈
		double mu = 1.;															//▷ 현재 계산하고자 하는 subgrid의 mu값을 저장한다.
		FVector_double vMus(2);												//▷ 현재 계산하고자 하는 subgrid의 cp값을 저장한다.
		FMatrix_double mCps(2, __.dim);										//▷ 2개의 cp좌표를 대입한다.
		FMatrix_double mNodes(4, __.dim);									//▷ subgrid maximum node개수, dim
		FMatrix_double mLNodes(2, __.dim);									//▷ line 적분을 위해 두점을 저장

		FVector_double PSI(__.npshape);										//▷ interface와 noninterface의 psi값을 저장
		FMatrix_double DPSI(__.npshape, __.dim);							//▷ interface와 noninterface의 dpsi값을 저장

		FVector_double PSI_N(__.npshape);									//▷ interface와 noninterface의 psi값을 저장
		FMatrix_double DPSI_N(__.npshape, __.dim);							//▷ interface와 noninterface의 dpsi값을 저장

		FVector_double PSI_JUMP(8);											//▷ interface와 noninterface의 psi값을 저장
		FMatrix_double DPSI_JUMP(8, __.dim);								//▷ interface와 noninterface의 dpsi값을 저장
		FMatrix_double DPSI_AVE(8, __.dim);

		FVector_double SPSI(__.npshape);									//▷ interface와 noninterface의 psi값을 저장
		FMatrix_double SDPSI(__.npshape, __.dim);							//▷ interface와 noninterface의 dpsi값을 저장

		FVector_double BPSI(1);												//▷ bubble function의 psi값을 저장
		FMatrix_double BDPSI(1, __.dim);

		FVector_double BPSI_N(1);												//▷ bubble function의 psi값을 저장
		FMatrix_double BDPSI_N(1, __.dim);

		FVector_double BPSI_JUMP(1);											//▷ interface와 noninterface의 psi값을 저장
		FMatrix_double BDPSI_JUMP(1, __.dim);								//▷ interface와 noninterface의 dpsi값을 저장
		FMatrix_double BDPSI_AVE(1, __.dim);

		
		printf("\n[[ MAKE MASS MATRIX.. ]] : ");
		printf("    ");

		int percentSave = 0, percent;
		for (e = 0; e<_.neT; e++) {
			percent = ((e + 1) * 50) / _.neT;

			if (percentSave != percent) {
				percentSave = percent;
				printf("\b\b\b\b%3d%%", percent);
			}

			//▷ ◈ Noninterface Part ◈
			if (!(_.vEltA[e] & CV.INTERFACE_ELT)) {																						
				iim.vIO[0] = (_.vEltA[e] & CV.IN) ? CV.IN : CV.OUT;		//▷ noninterface의 경우 in, out 정보가 vEltA에 들어 있으므로 그곳에서 얻어온다.
				nsbMax = 1;												//▷ subgrid 개수를 저장한다.

			}
			//▷ ◈ Interface Part    ◈
			else {																												
				get_iElt_Datas(e, iim);									//▷ interface elt 정보를 얻어온다.
			//	FEM::IIFEM::get_iElt_Datas(_, __, e, iim);			    
				nsbMax = iim.cSubGrids._height;							//▷ subgrid 개수를 저장한다.
			}
			//Pause(0);
			for (nsb = 0; nsb < nsbMax; nsb++) {
				if (nsbMax != 1 && iim.cSubGrids[nsb]._row == 2) continue;		//▷ ☞: 직선일 경우 작업을 하지 않는다. (단, Interface Element에만 적용해야 한다.)
				mNodes._row = __.nnshape;
				//▷ ◈ Noninterface Part  ◈
				if (nsbMax == 1) {																										
					for (i = 0; i < __.nnshape; i++)
					{
						mNodes[i].getClone(_.coordN[_.indexN(e, i)]);
					}										//▷ mNodes로 세점을 얻어온다.
															//▷ 강제로 크기가 3이 되게 한다. 삼각형 elt에서 사용하므로
				}
				//▷ ◈ Interface Part     ◈
				else {																											
					mNodes.getClone(iim.cSubGrids[nsb]);	//▷ subgird의 점들을 얻어온다.
				}
				nPoly = mNodes._row;
				//▷ subgird의 polygon 종류를 받는다.
				//mu = (iim.vIO[nsb]==CV.IN)? _problem->mum: _problem->mup;													
				//▷ subgird의 맞는 mu값을 얻어온다.
				for (k = 0; k < __.vGauss[nPoly]; k++) {
					// ◈ Mapping         
				    //◈ : Mapping에 관련된 vRealP, DF, det, DFIT, jacoWeight 를 구해준다.
					FEM::MAPPING::make_realP_and_DF(vRealP, DF, __.pre_npsis(nPoly, k), __.pre_ndpsis(nPoly, k), mNodes);
					det = MATH::inverse(DF, DFIT);	DFIT.transpose();	jaco = fabs(det);	jacoWeight = jaco * __.Ws(nPoly, k);

					//▷ ◈ Noninterface Basis ◈
					// non-interface element => original Q1 conforming
					if (nsbMax == 1) {																								
						PSI.getClone(__.pre_ppsi(k));
						for (i = 0; i < __.npshape; i++) {
							DPSI[i].op("=", DFIT, __.pre_pdpsi(k, i));
							BPSI.clear();
							BDPSI.clear();
						}
					}
					//▷ ◈ Interface Basis ◈
					// interface element => IFEM scheme
					else {
						__.shape.iim_pressure(vRealP, iim.vIO[nsb], _.cIIMCoef[e], PSI, DPSI);
						__.shape.iim_pressure(vRealP, iim.vIO[nsb], _.cIIMCoefBubble[e], BPSI, BDPSI);

						PSI[4] = 1.;
						DPSI[4].clear();
					}
					// ◈ Get Real Values ◈
					_problem->coef_mu(vRealP, mus);																			// 두 값을 호출해서 알맞게 돌려준다.
					mu = (iim.vIO[nsb] == CV.IN) ? mus[0] : mus[1];

					//수정 전 부분 :
					_problem->F(vRealP, vF);
					f = (iim.vIO[nsb] == CV.IN) ? vF[0] : vF[1]; 
					
					// ◈ Weak Equation   ◈
					for (j = 0; j < __.npshape; j++) {																					//▷ test index "j"
						pj = _.indexP(e, j);

						// [[ _.mA의 계산 ]] : A += ∫β∇p^0·∇q
						for (i = 0; i < __.npshape; i++) {																				//▷ trial index "i"
							pi = _.indexP(e, i);
							_.mA[pj][pi] += mu * (DPSI[i], DPSI[j]) * jacoWeight;
						}
						// [[ _.vF의 계산 ]] : F +=∫fq  
						_.vF[pj] -= mu * (BDPSI[0], DPSI[j]) * jacoWeight;
						_.vF[pj] += f*PSI[j] * jacoWeight;
					}
				}// end for (k=0; k<__.vGauss[nPoly]; k++) 
			}
		}
		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		//						◈ Line Integral ◈
		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		for (edge = 0; edge<_.nlt; edge++) {
			e = _.indexL(edge, 0);
			eN = _.indexL(edge, 1);
			l = _.indexL(edge, 2);
			if (e<0) {
				e = _.indexL(edge, 1);
				eN = _.indexL(edge, 0);
				l = (l + 2) % 4;
			}
			nl = (l + 2) % 4;
			percent = ((edge + 1) * 100) / _.nlt;

			if (percentSave != percent) {
				percentSave = percent;
				printf("\b\b\b\b%3d%%", percent);
			}

			//if (e<0 || eN<0) continue;
			size_h = _.dx;
			vIm.op("=", _.coordN[_.indexN[e][(l + 1) % __.nnshape]], -1., _.coordN[_.indexN[e][(l + 0) % __.nnshape]]);
			vN.setAll(vIm[1], -vIm[0]).normalize();


			//if (eN<0) vN.setAll(-vIm[1], +vIm[0]).normalize();	
			// e에 대한 interface element 체크
			if (!(_.vEltA[e] & CV.INTERFACE_ELT)) {																					//▷ ◈ Noninterface Part ◈
				iim.vIO[0] = (_.vEltA[e] & CV.IN) ? CV.IN : CV.OUT;																	//▷ noninterface의 경우 in, out 정보가 vEltA에 들어 있으므로 그곳에서 얻어온다.
				nsbMax = 1;																											//▷ subgrid 개수를 저장한다.
																																	//splitted = false;
			}
			else {																													//▷ ◈ Interface Part    ◈
				get_iElt_Datas(e, iim); 
			//	FEM::IIFEM::get_iElt_Datas(_, __, e, iim);																			//▷ interface elt 정보를 얻어온다.
				nsbMax = iim.cSubGrids._height;
			}

			// eN에 대한 interface element 체크
			if (eN < 0) {
				iim_N.vIO[0] = CV.OUT;
				nsbMax_N = 1;
			}
			else if (!(_.vEltA[eN] & CV.INTERFACE_ELT)) {																			//▷ ◈ Noninterface Part ◈
				iim_N.vIO[0] = (_.vEltA[eN] & CV.IN) ? CV.IN : CV.OUT;																//▷ noninterface의 경우 in, out 정보가 vEltA에 들어 있으므로 그곳에서 얻어온다.
				nsbMax_N = 1;																										//▷ subgrid 개수를 저장한다.
			}
			else {																													//▷ ◈ Interface Part    ◈
				get_iElt_Datas(eN, iim_N);
			//	FEM::IIFEM::get_iElt_Datas(_, __, eN, iim_N);																		//▷ interface elt 정보를 얻어온다.
				nsbMax_N = iim_N.cSubGrids._height;																					//▷ subgrid 개수를 저장한다.
			}

			for (k = 0; k<__.nGauss1D; k++) {	// Line Integral point
				for (nsb = 0; nsb<nsbMax; nsb++) {
					bCalculate = false;		//bCalculate = true 일 때만 계산

					if (nsbMax == 1) {																								//▷ ◈ Noninterface Basis ◈
						FEM::MAPPING::make_realP_and_DF(vRealP, DF, __.pre_nepsi[l][k], __.pre_nedpsi[l][k], _.coordN, _.indexN[e]);
						det = MATH::inverse(DF, DFIT);	DFIT.transpose();
						jaco_l = 1.;//(mNodes((l+1)%__.nvshape) - mNodes(l)).norm2();
						weight = __.WL[k];
						PSI.getClone(__.pre_pepsi(l, k));
						for (j = 0; j<__.npshape; j++) DPSI[j].op("=", DFIT, __.pre_pedpsi(l, k, j));

						BPSI.clear();
						BDPSI.clear();
						bCalculate = true;
					}
					else {
						nPoly = iim.mSbr[nsb]._size;
						for (i = 1; i<nPoly; i++) {// 0 인 경우는 내부 edge이므로 계산하지 아니함
							if ((((int)((iim.mSbr_temp[nsb][i] + iim.mSbr_temp[nsb][i + 1]) / 2)) % 4 == l) && iim.mSbr_temp[nsb][i + 1] - iim.mSbr_temp[nsb][i] <= 1) { // l과 일치하는 subgrid line을 찾는다.
								jaco_l = iim.mSbr_temp[nsb][i + 1] - iim.mSbr_temp[nsb][i];
								weight = __.WL[k];
								vRealP.op("=", 1 - __.XIL[k], iim.cSubGrids[nsb][i], __.XIL[k], iim.cSubGrids[nsb][(i + 1) % nPoly]);
								__.shape.iim_pressure(vRealP, iim.vIO[nsb], _.cIIMCoef[e], PSI, DPSI);
								__.shape.iim_pressure(vRealP, iim.vIO[nsb], _.cIIMCoefBubble[e], BPSI, BDPSI);

								PSI[4] = 1.;
								DPSI[4].clear();
								bCalculate = true;
								break;	// Subgrid nsb에서 edge l과 일치하는 변은 많아야 하나 뿐이다.
							}
						}
					}

					if (bCalculate == false) continue;
					for (nsbN = 0; nsbN < nsbMax_N; nsbN++) {	// nsb, nsb_N loop
						bCalculate = false;		// bCalculate = true 일 때만 계산함
												// iim.vIO[nsb] 와 iim_N.vIO[nsb_N] 가 같지 않은 경우는 다음 nsb_N 으로
						if (eN >= 0 && iim_N.vIO[nsbN] != iim.vIO[nsb]) continue;
						// element eN 에서의 PSI, DPSI 구하는 과정
						// Noninterface element의 경우 항상 bCalculate = true
						if (eN < 0) {
							PSI_N.clear();
							DPSI_N.clear();
							BPSI_N.clear();
							BDPSI_N.clear();

							bCalculate = true;
							vRealP_N = vRealP;
						}
						else if (nsbMax_N == 1) {																								//▷ ◈ Noninterface Basis ◈
							FEM::MAPPING::make_realP_and_DF(vRealP_N, DF_N, __.pre_nepsi[nl][__.nGauss1D - 1 - k], __.pre_nedpsi[nl][__.nGauss1D - 1 - k], _.coordN, _.indexN[eN]);
							det = MATH::inverse(DF_N, DFIT);	DFIT.transpose();//vRealP.print();
							jaco_l = 1.;//(mNodes((l+1)%__.nvshape) - mNodes(l)).norm2();
							weight = __.WL[__.nGauss1D - 1 - k];
							PSI_N.getClone(__.pre_pepsi(nl, __.nGauss1D - 1 - k));
							for (j = 0; j < __.npshape; j++) DPSI_N[j].op("=", DFIT, __.pre_pedpsi(nl, __.nGauss1D - 1 - k, j));

							BPSI_N.clear();
							BDPSI_N.clear();
							// Interface element의 경우 iim.mSbr[nsb][i] 과 iim.mSbr[nsb][i+1] 이 모두 l 위에 있을 때만 bCalculate = true;
							bCalculate = true;
							
						}
						else {
							nPoly = iim_N.mSbr[nsbN]._size;
							for (i = 1; i < nPoly; i++) {// 0 인 경우는 내부 edge이므로 계산하지 아니함
														 //if (((int)((iim_N.mSbr_temp[nsb_N][i]+iim_N.mSbr_temp[nsb_N][i+1])/2))%3 ==l) { // l과 일치하는 subgrid line을 찾는다.
								if (((int)iim_N.mSbr[nsbN][i] == nl || iim_N.mSbr[nsbN][i] == (nl + 1) % 4) && ((int)iim_N.mSbr[nsbN][(i + 1) % nPoly] == nl || iim_N.mSbr[nsbN][(i + 1) % nPoly] == (nl + 1) % 4) && iim_N.mSbr_temp[nsbN][i + 1] - iim_N.mSbr_temp[nsbN][i] <= 1) {
									jaco_l = iim_N.mSbr_temp[nsbN][i + 1] - iim_N.mSbr_temp[nsbN][i];
									weight = __.WL[__.nGauss1D - 1 - k];
									vRealP_N.op("=", 1 - __.XIL[__.nGauss1D - 1 - k], iim_N.cSubGrids[nsbN][i], __.XIL[__.nGauss1D - 1 - k], iim_N.cSubGrids[nsbN][(i + 1) % nPoly]);

									__.shape.iim_pressure(vRealP_N, iim_N.vIO[nsbN], _.cIIMCoef[eN], PSI_N, DPSI_N);
									__.shape.iim_pressure(vRealP_N, iim_N.vIO[nsbN], _.cIIMCoefBubble[eN], BPSI_N, BDPSI_N);

									PSI_N[4] = 1.;
									DPSI_N[4].clear();
									bCalculate = true;
									break;	// Subgrid nsb_N에서 edge l과 일치하는 변은 많아야 하나 뿐이다.
								}
							}
						}


						//  Element e 의 nsb 에서 l과 일치하는 변이 없으면 다음 nsb로
						if (bCalculate == false) continue;

						if ((vRealP - vRealP_N).norm2() >pow(10., -13.)) {
							cout << "edge: " << edge << "e: " << e << "eN: " << eN << "l: " << l << "nl: " << nl << endl;
							//	cout << (vRealP - vRealP_N).norm2() << endl;
							vRealP.print();
							vRealP_N.print();
						}

						vDOF.clear(-1);
						PSI_JUMP.clear();
						DPSI_AVE.clear();
						if (eN >= 0)
						{
							vDOF[0] = _.indexP[e][l];
							vDOF[1] = _.indexP[e][(l + 1) % 4];
							vDOF[2] = _.indexP[e][(l + 2) % 4];
							vDOF[3] = _.indexP[e][(l + 3) % 4];
							vDOF[4] = _.indexP[eN][(nl + 2) % 4];
							vDOF[5] = _.indexP[eN][(nl + 3) % 4];
							vDOF[6] = _.indexP[e][4];
							vDOF[7] = _.indexP[eN][4];

							PSI_JUMP[0] = PSI[l] - PSI_N[(nl + 1) % 4];
							PSI_JUMP[1] = PSI[(l + 1) % 4] - PSI_N[nl];
							PSI_JUMP[2] = PSI[(l + 2) % 4];
							PSI_JUMP[3] = PSI[(l + 3) % 4];
							PSI_JUMP[4] = -PSI_N[(nl + 2) % 4];
							PSI_JUMP[5] = -PSI_N[(nl + 3) % 4];
							PSI_JUMP[6] = PSI[4];
							PSI_JUMP[7] = -PSI_N[4];

							BPSI_JUMP[0] = BPSI[0] - BPSI_N[0];

							DPSI_AVE[0].op("=", 0.5, DPSI[l], 0.5, DPSI_N[(nl + 1) % 4]);
							DPSI_AVE[1].op("=", 0.5, DPSI[(l + 1) % 4], 0.5, DPSI_N[nl]);
							DPSI_AVE[2].op("=", 0.5, DPSI[(l + 2) % 4]);
							DPSI_AVE[3].op("=", 0.5, DPSI[(l + 3) % 4]);
							DPSI_AVE[4].op("=", 0.5, DPSI_N[(nl + 2) % 4]);
							DPSI_AVE[5].op("=", 0.5, DPSI_N[(nl + 3) % 4]);
							DPSI_AVE[6].op("=", 0.5, DPSI[4]);
							DPSI_AVE[7].op("=", 0.5, DPSI_N[4]);

							BDPSI_AVE[0].op("=", 0.5, BDPSI[0], 0.5, BDPSI_N[0]);

						}
						else
						{
							vDOF[0] = _.indexP[e][l];
							vDOF[1] = _.indexP[e][(l + 1) % 4];
							vDOF[2] = _.indexP[e][(l + 2) % 4];
							vDOF[3] = _.indexP[e][(l + 3) % 4];
							vDOF[6] = _.indexP[e][4];

							PSI_JUMP[0] = PSI[l];
							PSI_JUMP[1] = PSI[(l + 1) % 4];
							PSI_JUMP[2] = PSI[(l + 2) % 4];
							PSI_JUMP[3] = PSI[(l + 3) % 4];
							PSI_JUMP[6] = PSI[4];

							DPSI_AVE[0].op("=", 1., DPSI[l]);
							DPSI_AVE[1].op("=", 1., DPSI[(l + 1) % 4]);
							DPSI_AVE[2].op("=", 1., DPSI[(l + 2) % 4]);
							DPSI_AVE[3].op("=", 1., DPSI[(l + 3) % 4]);
							DPSI_AVE[6].op("=", 1., DPSI[4]);

							BPSI_JUMP[0] = BPSI[0];
							BDPSI_AVE[0].op("=", 1., BDPSI[0]);
						} 
						_problem->coef_mu(vRealP, mus);																			// 두 값을 호출해서 알맞게 돌려준다.
						mu = (iim.vIO[nsb] == CV.IN) ? mus[0] : mus[1];
						gamma = kappa*mu;
						for (j = 0; j < 8; j++) {
							if (vDOF[j] >= 0) {
								for (i = 0; i < 8; i++) {
									if (vDOF[i] >= 0) {

										_.mA[vDOF[j]][vDOF[i]] += gamma * (PSI_JUMP[i] * PSI_JUMP[j]) * weight * jaco_l;

										_.mA[vDOF[j]][vDOF[i]] -= mu* (DPSI_AVE[i], vN) * PSI_JUMP[j] * weight * jaco_l * size_h;
										_.mA[vDOF[j]][vDOF[i]] -= mu* eps * (DPSI_AVE[j], vN) * PSI_JUMP[i] * weight * jaco_l * size_h;
									}
								}
								_.vF[vDOF[j]]  -= gamma * (BPSI_JUMP[0] * PSI_JUMP[j]) * weight * jaco_l;

								_.vF[vDOF[j]] += mu* (BDPSI_AVE[0], vN) * PSI_JUMP[j] * weight * jaco_l * size_h;
								_.vF[vDOF[j]] += mu* eps* (DPSI_AVE[j], vN) * BPSI_JUMP[0] * weight * jaco_l * size_h;
							}
						}
						// Boundary Process : Assumption(?)
						if (eN < 0) {
							gp = _problem->P(vRealP,t); 
							for (j = 0; j < 8; j++) {
								if (vDOF[j] >= 0) {
									_.vF[vDOF[j]] += gamma * (gp * PSI_JUMP[j]) * weight * jaco_l;
									_.vF[vDOF[j]] -= mu* eps * (DPSI_AVE[j], vN) * gp * weight * jaco_l * size_h;
								}
							}

						}

					} // for (nsb_N=0; nsb_N<nsbMax_N; nsb_N++) 
				}	// for (nsb = 0; nsb<nsbMax; nsb++)
			}	//for(k=0; k<__.nGauss1D; k++) {
		}//for(edge=0; edge<__.nvshape; edge++) {	// Edge for line integral*/
		_.mA.trim();															//▷ mA에서 0인 자료들의 메모리를 비워준다.
	}
	void VEL_RECOV(double t=0.) {
		printf("\n[[ VECTOR RECOVERY.. ]] : ");
		printf("    ");
		// [ Variables ]
		int i, j;
		int pi, pj;															//▷ global pressure number
		int k;																//▷ Gauss points
		int e, eN;															//▷ element number
		int l, nl;
		double det, jaco, jacoWeight;
		int nPoly_e, nPoly_eN;
		int old_e;
		int edge;
		double size_h;
		double gamma = 10.;
		int vi;

		double f, f_av, area_;
		double swv;
		double K_p = _problem->K_p;
		double lamda;
		double sw_ = 0;
		double mu;
		double weight;

		double flow_average_;
		double psi_jump;
		double w_1;
		double w_2;
		double deti;
		double vel_dof;
		bool bCalculate;

		double temp;
		double bv_p;

		FVector_double mus(2);
		FVector_double vDOF(8);
		FVector_double loc_res(__.npshape);
		FVector_double loc_f(__.npshape);
		FVector_double loc_pre(__.npshape);

		FVector_double vRealP(__.dim), vF(__.dim), vRealP_N(__.dim), vIm(__.dim);
		FMatrix_double DF(__.dim, __.dim), DF_N(__.dim, __.dim), DFIT(__.dim, __.dim);
		// ◈ IIM Variables     ◈
		int nsbMax, nsbMax_N;												//▷ subgrid 개수 (Noninterface의 경우는 1개가 된다.)
		int nsb, nsbN;														//▷ 현재의 가리키는 subgrid의 번호
		int nPoly;															//▷ subgrid 의 polygon type

																			// ◈ Line Integral Val ◈
		double fluxJump;													//▷ flux jump값을 저장한다.
		double jaco_l, jacoWeight_l;

		FVector_double vN(__.dim);											//▷ interface에서 normal vector
		FVector_double vStartP(__.dim);										//▷ Line integral의 Line 시작점
		FVector_double vEndP(__.dim);										//▷ Line integral의 Line 끝점
																			// ◈ Clone Variables   ◈
		FVector_double vMus(2);												//▷ 현재 계산하고자 하는 subgrid의 cp값을 저장한다.
		FMatrix_double mCps(2, __.dim);										//▷ 2개의 cp좌표를 대입한다.
		FMatrix_double mNodes(4, __.dim);									//▷ subgrid maximum node개수, dim
		FMatrix_double mLNodes(2, __.dim);									//▷ line 적분을 위해 두점을 저장

		FVector_double PSI(__.npshape);										//▷ interface와 noninterface의 psi값을 저장
		FMatrix_double DPSI(__.npshape, __.dim);							//▷ interface와 noninterface의 dpsi값을 저장

		FVector_double PSI_N(__.npshape);									//▷ interface와 noninterface의 psi값을 저장
		FMatrix_double DPSI_N(__.npshape, __.dim);							//▷ interface와 noninterface의 dpsi값을 저장

		FVector_double PSI_JUMP(8);											//▷ interface와 noninterface의 psi값을 저장
		FMatrix_double DPSI_JUMP(8, __.dim);								//▷ interface와 noninterface의 dpsi값을 저장
		FMatrix_double DPSI_AVE(8, __.dim);


		FVector_double BPSI(1);												//▷ bubble function의 psi값을 저장
		FMatrix_double BDPSI(1, __.dim);

		FVector_double BPSI_N(1);												//▷ bubble function의 psi값을 저장
		FMatrix_double BDPSI_N(1, __.dim);

		FVector_double BPSI_JUMP(1);											//▷ interface와 noninterface의 psi값을 저장
		FMatrix_double BDPSI_JUMP(1, __.dim);								//▷ interface와 noninterface의 dpsi값을 저장
		FMatrix_double BDPSI_AVE(1, __.dim);

		int percentSave = 0, percent;
		for (edge = 0; edge<_.nlt; edge++) {
			e = _.indexL(edge, 0);
			eN = _.indexL(edge, 1);
			l = _.indexL(edge, 2);
			if (e<0) {
				e = _.indexL(edge, 1);
				eN = _.indexL(edge, 0);
				l = (l + 2) % 4;
			}
			nl = (l + 2) % 4;

			percent = 50 + ((edge + 1) * 50) / _.nlt;
			if (percentSave != percent) {
				percentSave = percent;
				printf("\b\b\b\b%3d%%", percent);
			}

			size_h = _.dx;
			vIm.op("=", _.coordN[_.indexN[e][(l + 1) % __.nnshape]], -1., _.coordN[_.indexN[e][(l + 0) % __.nnshape]]);
			vN.setAll(vIm[1], -vIm[0]).normalize();

			// e에 대한 interface element 체크
			if (!(_.vEltA[e] & CV.INTERFACE_ELT)) {																					//▷ ◈ Noninterface Part ◈
				iim.vIO[0] = (_.vEltA[e] & CV.IN) ? CV.IN : CV.OUT;																	//▷ noninterface의 경우 in, out 정보가 vEltA에 들어 있으므로 그곳에서 얻어온다.
				nsbMax = 1;																											//▷ subgrid 개수를 저장한다.
																																	//splitted = false;
			}
			else {																													//▷ ◈ Interface Part    ◈
				get_iElt_Datas(e, iim);
			//	FEM::IIFEM::get_iElt_Datas(_, __, e, iim);																			//▷ interface elt 정보를 얻어온다.
				nsbMax = iim.cSubGrids._height;
			}

			// eN에 대한 interface element 체크
			if (eN < 0) {
				iim_N.vIO[0] = CV.OUT;
				nsbMax_N = 1;
			}
			else if (!(_.vEltA[eN] & CV.INTERFACE_ELT)) {																			//▷ ◈ Noninterface Part ◈
				iim_N.vIO[0] = (_.vEltA[eN] & CV.IN) ? CV.IN : CV.OUT;																//▷ noninterface의 경우 in, out 정보가 vEltA에 들어 있으므로 그곳에서 얻어온다.
				nsbMax_N = 1;																										//▷ subgrid 개수를 저장한다.
			}
			else {																													//▷ ◈ Interface Part    ◈
			//	FEM::IIFEM::get_iElt_Datas(_, __, eN, iim_N);																		//▷ interface elt 정보를 얻어온다.
				get_iElt_Datas(eN, iim_N);
				nsbMax_N = iim_N.cSubGrids._height;																					//▷ subgrid 개수를 저장한다.
			}

			flow_average_ = 0;
			psi_jump = 0;
			vel_dof = 0;

			for (k = 0; k < __.nGauss1D; k++) {	// Line Integral point
				for (nsb = 0; nsb < nsbMax; nsb++) {
					bCalculate = false;		//bCalculate = true 일 때만 계산

					if (nsbMax == 1) {																								//▷ ◈ Noninterface Basis ◈
						FEM::MAPPING::make_realP_and_DF(vRealP, DF, __.pre_nepsi[l][k], __.pre_nedpsi[l][k], _.coordN, _.indexN[e]);
						det = MATH::inverse(DF, DFIT);	DFIT.transpose();
						jaco_l = 1.;//(mNodes((l+1)%__.nvshape) - mNodes(l)).norm2();
						weight = __.WL[k];
						PSI.getClone(__.pre_pepsi(l, k));
						for (j = 0; j < __.npshape; j++) DPSI[j].op("=", DFIT, __.pre_pedpsi(l, k, j));

						BPSI.clear();
						BDPSI.clear();
						bCalculate = true;
					}
					else {
						nPoly = iim.mSbr[nsb]._size;
						for (i = 1; i < nPoly; i++) {// 0 인 경우는 내부 edge이므로 계산하지 아니함
							if ((((int)((iim.mSbr_temp[nsb][i] + iim.mSbr_temp[nsb][i + 1]) / 2)) % 4 == l) && iim.mSbr_temp[nsb][i + 1] - iim.mSbr_temp[nsb][i] <= 1) { // l과 일치하는 subgrid line을 찾는다.
								jaco_l = iim.mSbr_temp[nsb][i + 1] - iim.mSbr_temp[nsb][i];
								weight = __.WL[k];
								vRealP.op("=", 1 - __.XIL[k], iim.cSubGrids[nsb][i], __.XIL[k], iim.cSubGrids[nsb][(i + 1) % nPoly]);
								__.shape.iim_pressure(vRealP, iim.vIO[nsb], _.cIIMCoef[e], PSI, DPSI);
								__.shape.iim_pressure(vRealP, iim.vIO[nsb], _.cIIMCoefBubble[e], BPSI, BDPSI);

								PSI[4] = 1.;
								DPSI[4].clear();
								bCalculate = true;
								break;	// Subgrid nsb에서 edge l과 일치하는 변은 많아야 하나 뿐이다.
							}
						}
					}

					if (bCalculate == false) continue;
					for (nsbN = 0; nsbN < nsbMax_N; nsbN++) {	// nsb, nsb_N loop
						bCalculate = false;		// bCalculate = true 일 때만 계산함

						// iim.vIO[nsb] 와 iim_N.vIO[nsb_N] 가 같지 않은 경우는 다음 nsb_N 으로
						if (eN >= 0 && iim_N.vIO[nsbN] != iim.vIO[nsb]) continue;

						// element eN 에서의 PSI, DPSI 구하는 과정
						// Noninterface element의 경우 항상 bCalculate = true
						if (eN < 0) {
							PSI_N.clear();
							DPSI_N.clear();
							BPSI_N.clear();
							BDPSI_N.clear();
							bCalculate = true;
							vRealP_N = vRealP;
						}
						else if (nsbMax_N == 1) {																								//▷ ◈ Noninterface Basis ◈
							FEM::MAPPING::make_realP_and_DF(vRealP_N, DF_N, __.pre_nepsi[nl][__.nGauss1D - 1 - k], __.pre_nedpsi[nl][__.nGauss1D - 1 - k], _.coordN, _.indexN[eN]);
							det = MATH::inverse(DF_N, DFIT);	DFIT.transpose();//vRealP.print();
							jaco_l = 1.;//(mNodes((l+1)%__.nvshape) - mNodes(l)).norm2();
							weight = __.WL[__.nGauss1D - 1 - k];
							PSI_N.getClone(__.pre_pepsi(nl, __.nGauss1D - 1 - k));
							for (j = 0; j < __.npshape; j++) DPSI_N[j].op("=", DFIT, __.pre_pedpsi(nl, __.nGauss1D - 1 - k, j));

							BPSI_N.clear();
							BDPSI_N.clear();
							bCalculate = true;
							// Interface element의 경우 iim.mSbr[nsb][i] 과 iim.mSbr[nsb][i+1] 이 모두 l 위에 있을 때만 bCalculate = true;
						}
						else {
							nPoly = iim_N.mSbr[nsbN]._size;
							for (i = 1; i < nPoly; i++) {
								// 0 인 경우는 내부 edge이므로 계산하지 아니함
								//if (((int)((iim_N.mSbr_temp[nsb_N][i]+iim_N.mSbr_temp[nsb_N][i+1])/2))%3 ==l) { // l과 일치하는 subgrid line을 찾는다.
								if (((int)iim_N.mSbr[nsbN][i] == nl || iim_N.mSbr[nsbN][i] == (nl + 1) % 4) && ((int)iim_N.mSbr[nsbN][(i + 1) % nPoly] == nl || iim_N.mSbr[nsbN][(i + 1) % nPoly] == (nl + 1) % 4) && iim_N.mSbr_temp[nsbN][i + 1] - iim_N.mSbr_temp[nsbN][i] <= 1) {
									jaco_l = iim_N.mSbr_temp[nsbN][i + 1] - iim_N.mSbr_temp[nsbN][i];
									weight = __.WL[__.nGauss1D - 1 - k];
									vRealP_N.op("=", 1 - __.XIL[__.nGauss1D - 1 - k], iim_N.cSubGrids[nsbN][i], __.XIL[__.nGauss1D - 1 - k], iim_N.cSubGrids[nsbN][(i + 1) % nPoly]);

									__.shape.iim_pressure(vRealP_N, iim_N.vIO[nsbN], _.cIIMCoef[eN], PSI_N, DPSI_N);
									__.shape.iim_pressure(vRealP_N, iim_N.vIO[nsbN], _.cIIMCoefBubble[eN], BPSI_N, BDPSI_N);

									PSI_N[4] = 1.;
									DPSI_N[4].clear();
									bCalculate = true;
									break;	// Subgrid nsb_N에서 edge l과 일치하는 변은 많아야 하나 뿐이다.
								}
							}
						}


						//  Element e 의 nsb 에서 l과 일치하는 변이 없으면 다음 nsb로
						if (bCalculate == false) continue;

						if ((vRealP - vRealP_N).norm2() > pow(10., -13.)) {
							cout << "edge: " << edge << "e: " << e << "eN: " << eN << "l: " << l << "nl: " << nl << endl;
							//	cout << (vRealP - vRealP_N).norm2() << endl;
							vRealP.print();
							vRealP_N.print();
						}

						vDOF.clear(-1);
						PSI_JUMP.clear();
						DPSI_AVE.clear();

						vDOF.clear(-1);
						PSI_JUMP.clear();
						DPSI_AVE.clear();
						if (eN >= 0)
						{
							vDOF[0] = _.indexP[e][l];
							vDOF[1] = _.indexP[e][(l + 1) % 4];
							vDOF[2] = _.indexP[e][(l + 2) % 4];
							vDOF[3] = _.indexP[e][(l + 3) % 4];
							vDOF[4] = _.indexP[eN][(nl + 2) % 4];
							vDOF[5] = _.indexP[eN][(nl + 3) % 4];
							vDOF[6] = _.indexP[e][4];
							vDOF[7] = _.indexP[eN][4];

							PSI_JUMP[0] = PSI[l] - PSI_N[(nl + 1) % 4];
							PSI_JUMP[1] = PSI[(l + 1) % 4] - PSI_N[nl];
							PSI_JUMP[2] = PSI[(l + 2) % 4];
							PSI_JUMP[3] = PSI[(l + 3) % 4];
							PSI_JUMP[4] = -PSI_N[(nl + 2) % 4];
							PSI_JUMP[5] = -PSI_N[(nl + 3) % 4];
							PSI_JUMP[6] = PSI[4];
							PSI_JUMP[7] = -PSI_N[4];

							DPSI_AVE[0].op("=", 0.5, DPSI[l], 0.5, DPSI_N[(nl + 1) % 4]);
							DPSI_AVE[1].op("=", 0.5, DPSI[(l + 1) % 4], 0.5, DPSI_N[nl]);
							DPSI_AVE[2].op("=", 0.5, DPSI[(l + 2) % 4]);
							DPSI_AVE[3].op("=", 0.5, DPSI[(l + 3) % 4]);
							DPSI_AVE[4].op("=", 0.5, DPSI_N[(nl + 2) % 4]);
							DPSI_AVE[5].op("=", 0.5, DPSI_N[(nl + 3) % 4]);
							DPSI_AVE[6].op("=", 0.5, DPSI[4]);
							DPSI_AVE[7].op("=", 0.5, DPSI_N[4]);

							BPSI_JUMP[0] = BPSI[0] - BPSI_N[0];
							BDPSI_AVE[0].op("=", 0.5, BDPSI[0], 0.5, BDPSI_N[0]);


						}
						else
						{
							vDOF[0] = _.indexP[e][l];
							vDOF[1] = _.indexP[e][(l + 1) % 4];
							vDOF[2] = _.indexP[e][(l + 2) % 4];
							vDOF[3] = _.indexP[e][(l + 3) % 4];
							vDOF[6] = _.indexP[e][4];

							PSI_JUMP[0] = PSI[l];
							PSI_JUMP[1] = PSI[(l + 1) % 4];
							PSI_JUMP[2] = PSI[(l + 2) % 4];
							PSI_JUMP[3] = PSI[(l + 3) % 4];
							PSI_JUMP[6] = PSI[4];

							DPSI_AVE[0].op("=", 1., DPSI[l]);
							DPSI_AVE[1].op("=", 1., DPSI[(l + 1) % 4]);
							DPSI_AVE[2].op("=", 1., DPSI[(l + 2) % 4]);
							DPSI_AVE[3].op("=", 1., DPSI[(l + 3) % 4]);
							DPSI_AVE[6].op("=", 1., DPSI[4]);

							BPSI_JUMP[0] = BPSI[0];
							BDPSI_AVE[0].op("=", 1., BDPSI[0]);
						}
						_problem->coef_mu(vRealP, mus);																			// 두 값을 호출해서 알맞게 돌려준다.
						mu = (iim.vIO[nsb] == CV.IN) ? mus[0] : mus[1];
						gamma = kappa*mu;
						if (eN >= 0) {
							for (j = 0; j < 8; j++) {
								if (vDOF[j] >= 0) {
									flow_average_ += _.vCP[vDOF[j]] * mu * (DPSI_AVE[j], vN)* size_h  * jaco_l * weight;
									psi_jump += gamma * _.vCP[vDOF[j]] * PSI_JUMP[j] * weight * jaco_l;
								}
							}
							psi_jump += gamma * BPSI_JUMP[0] * weight * jaco_l;
							flow_average_ += mu * (BDPSI_AVE[0], vN)* size_h  * jaco_l * weight;
						}
						// edge on the boundary
						else {
							temp = 0;

							_problem->P(vRealP, vF, t);
							bv_p = (iim.vIO[nsb] == CV.IN) ? vF[0] : vF[1];


							for (j = 0; j < 8; j++) {
								if (vDOF[j] >= 0) {
									flow_average_ += _.vCP[vDOF[j]] * mu * (DPSI_AVE[j], vN) * size_h  * jaco_l * weight;
									temp += _.vCP[vDOF[j]] * PSI_JUMP[j];

								}
							}
							psi_jump += gamma * (temp - bv_p) * weight * jaco_l;
						}
					} // 
				}
			}
			vi = _.indexV[e][l];
			_.vCV[vi] = (-flow_average_ + psi_jump) * drtV[e][l]; // *drtV[e][l];
		}

	}

	
	//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
	//▩▩                   각 level에서의 작업을 수행한다.              ▩▩
	//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
	void LAYER_ROUTINE() {
		PrintInBox("◈◈ LEVEL(LAYER) : %d ◈◈", __.nLayer);
		ELEMENT_SETTING();
		MEMORY_ALLOCATION();

		MAKE_PRIMITIVE_MASS_MATRIX(0.);
		if (__.nLayer <= 3) _.mA.save("pre_mA");
		if (__.nLayer <= 3) _.vF.save("pre_vF");
		FEM::BOUNDARY_PROCESS::Elliptic_Dirichelt_P1_Conforming(_,__);
		//	FEM::BOUNDARY_PROCESS::Elliptic_Dirichelt_P1_Conforming(_,__);
		//	if(__.nLayer<=3) _.mA.save("post_mA");
		//	if(__.nLayer<=3) _.vF.save("post_vF");

		SOLVER::PCG(_.mA, _.vCP, _.vF, 1.0E-11);
		VEL_RECOV();
	//	_.vCV.print();
		//	if(__.nLayer<=3) _.vCP.save("post_vCP");

	//	FEM::CALCULATE_ERROR::pressure(_, __, __.intErrOrd, __.errorP[0][__.nLayer], __.errorP[1][__.nLayer]);
	//	Error_Vector(_, __, __.intErrOrd, __.errorV[0][__.nLayer], __.errorV[1][__.nLayer]);
	
	//	FEM::PRINT_ERROR_ORDER::uniform_mesh_2pow_n(__, "P");				//▷ x,y축으로 동일하게 자른 uniform mesh에서의 error와 order를 계산한다.
	//	FEM::PRINT_ERROR_ORDER::uniform_mesh_2pow_n(__, "V");

		//	if(__.nLayer <= 5) FEM::DRAW_FIGURE::pressure_standard(_,__,"ELLIPTIC_2008_");
	//	if (__.nLayer <=3 ) FEM::DRAW_FIGURE::velocity(_,__,"VELOCITY");
	}


	//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
	//▩▩  Level set function(PHI) 을 초기화시킨다				▩▩
	//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
	void PHI_INITIALIZE(){

		int i, j, e;
		
		FVector_double vRealP(2);
		FVector_double vRealP0(2); 

		for (i=0; i<_.nsR; i++){
			for (j=0; j<_.nsR; j++){
				e=i+j*_.nsR;
				vRealP0=_.coordN[_.indexN[e][0]];

				vRealP[0]=vRealP0[0]+0.5*_.dx;
				vRealP[1]=vRealP0[1]+0.5*_.dy;

				vPHI[e]=_problem->Initial_PHI(vRealP);

			}
		} 
		draw_PHI("PHI",0);
		//Initial_PHI
	}


	//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
	//▩▩   IFEM을 풀기 이전 작업들을 수행                     ▩▩
	//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
	void SETALL(){
		SET_PROBLEM(); 
		SET_DOMAIN_BASIS(); 
		SET_SOLUTION_BASIS();
		SET_PREVALUES(); 
		ELEMENT_SETTING(); 
		MEMORY_ALLOCATION();  
		PHI_INITIALIZE(); 

		find_Control_Points(0); 
		FIND_INTERFACE_POINTS(0);

		INTERFACE_ELEMENT_EDGE_UPDATE(0); 
		INTERFACE_ELEMENT_VLEVELSET_ALL(); 
		INTERFACE_BASIS_UPDATE(); 

	} 

	//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
	//▩▩       Draw Pressure / PHI/ Velocity            ▩▩
	//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
	void pressure_standard_IIM(char *filename = "DRAW_PRESSURE_", int k = -1, int nOption = FEM::IIFEM::D_IIM) {

		char fileName[128];

		if (k == -1) sprintf(fileName, "%s_", filename);
		else sprintf(fileName, "%s%d_", filename, k);


		int e, n, i, s = 0, pi = 0;
		int nPoly;
		int nsb, nsbMax;
		double p_h;

		FVector_double	vRealP(__.dim), V1(__.dim), V2(__.dim);
		SHCube_double	polygons;
		C_BIT bView(5);						// the number of polygon groups

		FVector_int vPoly(2);

		vPoly = __.domain_poly_type;							// the number of vertex

		FCube_double	cNodes(2);
		FEM_VARIABLES::IIM	iim(__.dim, 3, __.domain_poly_type[0], 4);		//▷ iim variables

		FVector_double PSI(__.npshape);										//▷ interface와 noninterface의 psi값을 저장
		FMatrix_double DPSI(__.npshape, __.dim);							//▷ interface와 noninterface의 dpsi값을 저장

		FVector_double BPSI(1);												//▷ bubble function의 psi값을 저장
		FMatrix_double BDPSI(1, __.dim);									//▷ bubble function의 dpsi값을 저장


		cNodes[0].make(vPoly[0], __.dim);
		cNodes[1].make(vPoly[1], __.dim);

		cNodes[1].setAll(0., 0., 1., 0., 0., 1.);
		cNodes[0].setAll(0., 0., 1., 0., 1., 1., 0., 1.);

		FCube_double	pre_ppsis(5);					// domain psis on Gauss points
		FCube4_double	pre_pdpsis(5);					// domain dpsis on Gauss points

		for (i = 0; i<2; i++) {
			nPoly = vPoly[i];
			for (n = 0; n<nPoly; n++) {
				//	FEM::GET_SHAPE_VALUES::Pre_Values(__.dim, cNodes[i], nPoly, __.shape.pressure, pre_ppsis[nPoly], pre_pdpsis[nPoly]);		//▷ interface domain prevalue를 얻어온다.
				FEM::GET_SHAPE_VALUES::Pre_Values(__.dim, cNodes[i], nPoly, __.shape.domain, pre_ppsis[nPoly], pre_pdpsis[nPoly]);		//▷ interface domain prevalue를 얻어온다.
																																		//__.shape.pressure(cNodes[i][n], pre_ppsis[nPoly][n], pre_pdpsis[nPoly][n]);
			}
		}

		//	pre_ppsis[4][0].setAll(1., 0., 0., 0.);
		// ========================================================
		printf("\n[[    DRAW SCALAR FIGURE..   ]]");
		printf("   ");
		for (e = 0; e<_.neT; e++) {
			if (!(_.vEltA[e] & CV.INTERFACE_ELT)) {																						//▷ ◈ Noninterface Part ◈
				nPoly = __.nnshape;

				for (n = 0; n<nPoly; n++) {
					vRealP = _.coordN[_.indexN[e][n]];

					// get approximation solution
					p_h = 0;

					for (i = 0; i<4; i++) {
						pi = _.indexP[e][i];
						p_h += _.vCP[pi] * pre_ppsis[nPoly][n][i];
						if (!(_.vEltA[e] & CV.INTERFACE_ELT) && (_.vEltA[e] & CV.IN) && (nOption & FEM::IIFEM::D_EXTRACTION)) p_h += _.vCP_ext[pi] * pre_ppsis[nPoly][n][i];
					}
					//	p_h = 0.;
					polygons[0][e][n][0] = vRealP[0];
					polygons[0][e][n][1] = vRealP[1];
					polygons[0][e][n][2] = p_h;
				}
			}
			else {																												//▷ ◈ Interface Part    ◈
				get_iElt_Datas(e, iim);
				//		FEM::IIFEM::get_iElt_Datas(_, __, e, iim);																			//▷ interface elt 정보를 얻어온다.
				nsbMax = iim.cSubGrids._height;																						//▷ subgrid 개수를 저장한다.

				for (nsb = 0; nsb<nsbMax; nsb++) {
					//if(iim.cSubGrids[nsb]._row == 2) continue;														//▷ 직선일 경우 작업을 하지 않는다.
					nPoly = iim.cSubGrids[nsb]._row;

					for (n = 0; n<nPoly; n++) {
						BPSI.clear();

						vRealP = iim.cSubGrids[nsb][n];

						__.shape.iim_pressure(vRealP, iim.vIO[nsb], _.cIIMCoef[e], PSI, DPSI);								//▷ vRalp에서의 basis의 값을 만든다.
						__.shape.iim_pressure(vRealP, iim.vIO[nsb], _.cIIMCoefBubble[e], BPSI, BDPSI);						//▷ vRalp에서의 basis의 값을 만든다.

						p_h = 0;
						for (i = 0; i<4; i++) {
							pi = _.indexP[e][i];
							p_h += _.vCP[pi] * PSI[i];
						}
						p_h += BPSI[0];

						polygons[nsb * 10 + nPoly][e][n][0] = vRealP[0];
						polygons[nsb * 10 + nPoly][e][n][1] = vRealP[1];
						polygons[nsb * 10 + nPoly][e][n][2] = p_h;
					}
				}
			}
		}
		MATLAB::savePolygons(polygons, fileName, __.nLayer);

		// 화면에 찍을 polygon을 선택
		bView._nOfBit = polygons.size();
		bView.set(0, polygons.getSize() - 1);
		MATLAB::viewPolygons(bView, fileName, __.nLayer, 50, 30, 1);
	}

	void draw_PHI(char *filename, int k = -1) {
		int e, n, s = 0, pi = 0,i, j;
		double p_h;

		char fileName[128];

		if (k == -1) sprintf(fileName, "%s_", filename);
		else sprintf(fileName, "%s%d_", filename, k);

		int number = __.nLayer;
			
		char buffer[128];
		if (number<0) sprintf(buffer, "%s.m", fileName);
		else sprintf(buffer, "%s%d.m", fileName, number);

		FILE *fp = fopen(buffer, "w");

			 
		fprintf(fp, "\n clear all ");
		fprintf(fp, "\n dx=%.14f; ", _.dx);
		fprintf(fp, "\n x=%.14f + 1/2*dx:dx: %.14f -1/2*dx; ", __.RX[0][0], __.RX[1][0]);

		fprintf(fp, "\n dy=%.14f; ", _.dy);
		fprintf(fp, "\n y=%.14f + 1/2*dy:dy:%.14f -1/2*dy; ", __.RX[0][1], __.RX[1][1]);

		fprintf(fp, "\n phi=[ ");
		for (j = 0; j<_.nsE; j++) {
			for (i = 0; i<_.nsE; i++) {
				e=i+j*_.nsE;
				fprintf(fp, "%.14f \t", vPHI[e]);
			}
			fprintf(fp, "\n");
		}
		fprintf(fp, "]; ");

		fprintf(fp, "\n figure('position',[100 100 800 700])");
		fprintf(fp, "\n contour(x,y,phi')");

		fprintf(fp, "\n xlabel \'X\';\n");
		fprintf(fp, "ylabel \'Y\';\n");
		fprintf(fp, "colormap jet;\n");
		fprintf(fp, "colorbar;\n");

		fprintf(fp, "\n figure('position',[100 100 800 700])");
		fprintf(fp, "\n surf(x,y,phi')");

		fprintf(fp, "\n xlabel \'X\';\n");
		fprintf(fp, "ylabel \'Y\';\n");
		fprintf(fp, "colormap jet;\n");
		fprintf(fp, "colorbar;\n");
		 
		fclose(fp);
	}
	void draw_VEL(char *filename, int k = -1) {
	//	FEM::DRAW_FIGURE::velocity_center();
		int n, pi = 0,i, j;
		double p_h;

		char fileName[128];

		if (k == -1) sprintf(fileName, "%s_", filename);
		else sprintf(fileName, "%s%d_", filename, k);
		
		int number = __.nLayer;
			
		char buffer[128];
		if (number<0) sprintf(buffer, "%s.m", fileName);
		else sprintf(buffer, "%s%d.m", fileName, number);

		int e, dim, s=0, vi=0;
		double v_h;

		FVector_double	vRealP(__.dim), V1(__.dim), V2(__.dim), V_h(__.dim);
		SCube_double	vector;	
		C_BIT bView(1);						// the number of polygon groups
			
		int nV = __.domain_poly_type[0];
		FVector_double	node(__.dim);
		if(nV == 3) node.setAll(1./3., 1./3.);
		if(nV == 4) node.setAll(1./2., 1./2.);

		static FVector_double	pre_vpsi (__.nvshape);	
		static FMatrix_double	pre_vdpsi(__.nvshape, __.dim), pre_Vpsi(__.nvshape, __.dim);
		static FCube_double		pre_Vdpsi(__.nvshape, __.dim, __.dim);
		static FVector_double   pre_psi (__.nnshape);
		static FMatrix_double	pre_pdpsi(__.nnshape, __.dim);	
		static FMatrix_double	DF(__.dim,__.dim), DFIT(__.dim,__.dim);
		static FVector_double	uhat(__.dim);
			
		double det, deti;
		FMatrix_double PSI(__.nvshape,__.dim);
		__.shape.domain(node,pre_psi,pre_pdpsi);
		__.shape.vector(node, pre_Vpsi, pre_Vdpsi);				
		// ========================================================
	//	printf("\n[[    DRAW VECTOR FIGURE..   ]]");
	//	printf("   "); 
		for(e=0; e<_.neT; e++) {
			vRealP.clear();
			FEM::MAPPING::make_realP_and_DF(vRealP, DF, pre_psi,pre_pdpsi, _.coordN, _.indexN(e)); // F : reference -> element. k번 째 gaussian point가 실제로 가는 point가 vRealP.
			det = MATH::inverse(DF, DFIT);	DFIT.transpose();
			deti = 1./det;
				
			for (i = 0; i<__.nvshape; i++) {
				PSI[i].op("=", deti * drtV[e][i], DF, pre_Vpsi[i]);
			//	mTemp.op("=", deti  * drtV[e][i], DF, pre_Vdpsi[i]);
			//	DPSI[i].op("=", mTemp, DFI);
			}

			V_h.clear();
			for (i = 0; i<__.nvshape; i++) {							// summation
				vi = _.indexV[e][i];
				V_h.op("+=", _.vCV[vi], PSI[i]);
			}

			vector[e][0] = vRealP;
			vector[e][1] = V_h;
		}
		MATLAB::saveVector(vector, fileName, __.nLayer); 
	}
	

	void draw_levelset(char *filename="DRAW_LEVELSET_", int k = -1) {
		int e, n, s = 0, pi = 0, i, j;
		double p_h;
		double sign;
		char fileName[128];

		if (k == -1) sprintf(fileName, "%s_", filename);
		else sprintf(fileName, "%s%d_", filename, k);

		int number = __.nLayer;

		char buffer[128];
		if (number<0) sprintf(buffer, "%s.m", fileName);
		else sprintf(buffer, "%s%d.m", fileName, number);

		FILE *fp = fopen(buffer, "w");


		fprintf(fp, "\n clear all ");
		fprintf(fp, "\n dx=%.14f; ", _.dx);
		fprintf(fp, "\n x=%.14f + 1/2*dx:dx: %.14f -1/2*dx; ", __.RX[0][0], __.RX[1][0]);

		fprintf(fp, "\n dy=%.14f; ", _.dy);
		fprintf(fp, "\n y=%.14f + 1/2*dy:dy:%.14f -1/2*dy; ", __.RX[0][1], __.RX[1][1]);

		fprintf(fp, "\n phi=[ ");
		for (j = 0; j<_.nsE; j++) {
			for (i = 0; i<_.nsE; i++) {
				e = i + j*_.nsE;
				if (vPHI[e] > 0)
					sign = 1.0;
				else if (vPHI[e] < 0)
					sign = -1.0;
				else
					sign = 0;

				fprintf(fp, "%.14f \t", sign);
			}
			fprintf(fp, "\n");
		}
		fprintf(fp, "]; ");

		/*fprintf(fp, "\n figure('position',[100 100 800 700])");
		fprintf(fp, "\n contour(x,y,phi')");

		fprintf(fp, "\n xlabel \'X\';\n");
		fprintf(fp, "ylabel \'Y\';\n");
		fprintf(fp, "colormap jet;\n");
		fprintf(fp, "colorbar;\n");*/

		fprintf(fp, "\n figure('position',[100 100 800 700])");
		fprintf(fp, "\n surf(x,y,phi')");

		fprintf(fp, "\n xlabel \'X\';\n");
		fprintf(fp, "ylabel \'Y\';\n");
		fprintf(fp, "colormap jet;\n");
		fprintf(fp, "colorbar;\n");

		fclose(fp);
	}

	void draw_CP(char *filename = "CP") {
		int i, j;
		char buffer2[128];
		sprintf(buffer2, "%s.txt", filename);
		FILE *fp2 = fopen(buffer2, "w");
		for (j = 0; j<nCI; j++) {
			for (i = 0; i<2; i++) {
				fprintf(fp2, "%f \t", CP[j][i]);
			}
			fprintf(fp2, "\n");
		}
		fclose(fp2);
	}
	//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
	//▩▩	    Error Functions(Pressure/Vecocity)             ▩▩
	//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
	void	IIM_EG_pressure(FEM_VARIABLES::LEVEL &_, FEM_VARIABLES::ENTIRE &__, double& L2, double& H1, int nOption, double t) {
		//▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤
		L2 = H1 = 0;
		double p_real, p_h;
		double error_k;														//▷ Gauss point에서의 error
		FVector_double dp_real(__.dim), dp_h(__.dim), vH1(__.dim);
		//▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤

		// ◈ General Variables ◈
		int i;
		int pi;																//▷ global pressure number
		int k;																//▷ Gauss points
		int e;																//▷ element number
		double det, jaco, jacoWeight;

		FVector_double vRealP(__.dim), vIm(__.dim), vP_real(__.dim);
		FMatrix_double DF(__.dim, __.dim), DFIT(__.dim, __.dim), mDP(__.dim, __.dim);
		FMatrix_double mP_real(2, __.dim);

		// ◈ IIM Variables     ◈
		int nsbMax;															//▷ subgrid 개수 (Noninterface의 경우는 1개가 된다.)
		int nsb;															//▷ 현재의 가리키는 subgrid의 번호
		int nPoly;															//▷ subgrid 의 polygon type
		FEM_VARIABLES::IIM	iim;		//▷ iim variables
		if (__.domain_poly_type[0] == 3) {
			iim.initialize(__.dim, 2, __.domain_poly_type[0], 4);			//▷ iim variables
		}
		else {
			iim.initialize(__.dim, 3, __.domain_poly_type[0], 4);			//▷ iim variables
		}
		// ◈ Clone Variables   ◈
		double mu;															//▷ 현재 계산하고자 하는 subgrid의 mu값을 저장한다.
		FVector_double vMus(2);												//▷ 현재 계산하고자 하는 subgrid의 cp값을 저장한다.
		FMatrix_double mCps(2, __.dim);										//▷ 2개의 cp좌표를 대입한다.
		FMatrix_double mNodes(4, __.dim);									//▷ subgrid maximum node개수, dim

		FVector_double PSI(__.npshape);										//▷ interface와 noninterface의 psi값을 저장
		FMatrix_double DPSI(__.npshape, __.dim);							//▷ interface와 noninterface의 dpsi값을 저장

		FVector_double BPSI(1);												//▷ bubble function의 psi값을 저장
		FMatrix_double BDPSI(1, __.dim);									//▷ bubble function의 dpsi값을 저장

																			// =======================================================================
		printf("\n[[ CALCULATE PRESSURE ERROR ]] : ");
		printf("    ");

		int percentSave = 0, percent;
		for (e = 0; e<_.neT; e++) {
			percent = ((e + 1) * 100) / _.neT;

			if (percentSave != percent) {
				percentSave = percent;
				printf("\b\b\b\b%3d%%", percent);
			}
			if (!(_.vEltA[e] & CV.INTERFACE_ELT)) {																					//▷ ◈ Noninterface Part ◈
				iim.vIO[0] = (_.vEltA[e] & CV.IN) ? CV.IN : CV.OUT;																	//▷ noninterface의 경우 in, out 정보가 vEltA에 들어 있으므로 그곳에서 얻어온다.
				nsbMax = 1;																											//▷ subgrid 개수를 저장한다.
																																	//Pause(e);
			}
			else {																												//▷ ◈ Interface Part    ◈
				get_iElt_Datas(e, iim);
				//	FEM::IIFEM::get_iElt_Datas(_, __, e, iim);																			//▷ interface elt 정보를 얻어온다.
				nsbMax = iim.cSubGrids._height;																						//▷ subgrid 개수를 저장한다.
			}

			for (nsb = 0; nsb<nsbMax; nsb++) {
				//Pause(iim.cSubGrids[nsb]._row);
				if (nsbMax != 1 && iim.cSubGrids[nsb]._row == 2) continue;														//▷ 직선일 경우 작업을 하지 않는다.
				mNodes._row = __.nnshape;																						//▷ 강제로 크기가 3이 되게 한다. 삼각형 elt에서 사용하므로
				if (nsbMax == 1) {																										//▷ ◈ Noninterface Part  ◈
					for (i = 0; i<__.nnshape; i++) mNodes[i].getClone(_.coordN[_.indexN(e, i)]);										//▷ mNodes로 세점을 얻어온다.

				}
				else {																											//▷ ◈ Interface Part     ◈
					mNodes.getClone(iim.cSubGrids[nsb]);																	//▷ subgird의 점들을 얻어온다.
				}
				nPoly = mNodes._row;																								//▷ subgird의 polygon 종류를 받는다.
				mu = (iim.vIO[nsb] == CV.IN) ? _problem->mum : _problem->mup;													//▷ subgird의 맞는 mu값을 얻어온다.

				for (k = 0; k<__.vGauss[nPoly]; k++) {
					// ◈ Mapping         ◈ : Mapping에 관련된 vRealP, DF, det, DFIT, jacoWeight 를 구해준다.
					FEM::MAPPING::make_realP_and_DF(vRealP, DF, __.pre_npsis(nPoly, k), __.pre_ndpsis(nPoly, k), mNodes);
					det = MATH::inverse(DF, DFIT);	DFIT.transpose();	jaco = fabs(det);	jacoWeight = jaco * __.Ws(nPoly, k);

					if (nsbMax == 1) {																								//▷ ◈ Noninterface Basis ◈
						PSI.getClone(__.pre_ppsi(k));
						for (i = 0; i<__.npshape; i++) DPSI[i].op("=", DFIT, __.pre_pdpsi(k, i));
					}
					else {																										//▷ ◈ Interface basis    ◈
						__.shape.iim_pressure(vRealP, iim.vIO[nsb], _.cIIMCoef[e], PSI, DPSI);								//▷ vRalp에서의 basis의 값을 만든다.
						PSI[__.npiimshape] = 1.;	DPSI[__.npiimshape].clear();
						if (nOption & FEM::IIFEM::D_BUBBLE)
							__.shape.iim_pressure(vRealP, iim.vIO[nsb], _.cIIMCoefBubble[e], BPSI, BDPSI);						//▷ vRalp에서의 basis의 값을 만든다.
					}
					// ◈ Get Real Values ◈
					_problem->P(vRealP, vP_real, t);
					p_real = vP_real[iim.vIO[nsb] - 1];

					dp_real.clear();
					//	_problem->P(vRealP, vP_real,  t);
					//	p_real = _problem->P(vRealP, t);


					//	_problem->DP(vRealP, dp_real,  t); 
					_problem->DP(vRealP, mDP, t);
					dp_real = mDP[iim.vIO[nsb] - 1];

					// ◈ Get p_h, dp_h   ◈
					p_h = 0;
					dp_h.clear();
					for (i = 0; i<__.npshape; i++) {
						pi = _.indexP[e][i];
						p_h += _.vCP[pi] * PSI[i];
						dp_h.op("+=", _.vCP[pi], DPSI[i]);
					}
					double pre_p_h = p_h;
					if (nOption & FEM::IIFEM::D_BUBBLE)
					{
						if (nsbMax != 1) {																									//▷ ★: Interface와 NonInterface가 맞물려 있으므로 Interface만 처리해야 하는 곳을 잘 막아줄 것
							p_h += BPSI[0];
							dp_h += BDPSI[0];
						}
					}
					// ◈ Error Calculate ◈
					error_k = fabs(p_real - p_h);
					L2 += pow(error_k, 2.) * jacoWeight; //Pause(pow(errorM,2.)<<" "<<W[k]<<" "<<jacoWeight<<" "<<L2);
					vH1.op("+=", "k(kfv+kfv)^k", jacoWeight, 1., dp_real, -1., dp_h, 2.);	// += (dp-dp_h)^2 * jacoWeight
				}// for (k=0; k<__.vGauss[nPoly]; k++)
			}// end for (nsb=0; nsb<nsbMax; nsb++)
		}// end for (e=0; e<_.neT; e++)
		L2 = sqrt(L2);
		H1 = sqrt(vH1.totalSum());
	}
	//Later
	/*
	void	Error_Vector(FEM_VARIABLES::LEVEL &_, FEM_VARIABLES::ENTIRE &__, int order, double& L2, double& Div, double t) {
		int type = FEM::CALCULATE_ERROR::VECTOR_ID::DIV_MAP;
		L2 = Div = 0;	// 0: L2   1: Div

						//▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤
						//	## Pre Values ##
						//▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤
		int k;
		int nGauss = C_INTEGRATION::change_Ord_nGauss(__.dim, __.domain_poly_type[0], order);

		FMatrix_double XI;
		FVector_double W;

		C_INTEGRATION::get_XI_W_2D(__.domain_poly_type[0], order, XI, W);

		FMatrix_double	pre_npsi(nGauss, __.nnshape);
		FCube_double	pre_ndpsi(nGauss, __.nnshape, __.dim), pre_Vpsi(nGauss, __.nvshape, __.dim);
		FCube4_double	pre_Vdpsi(nGauss, __.nvshape, __.dim, __.dim);

		for (k = 0; k<nGauss; k++) {
			__.shape.domain(XI[k], pre_npsi[k], pre_ndpsi[k]);
			__.shape.vector(XI[k], pre_Vpsi[k], pre_Vdpsi[k]);
		}


		//▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤
		//	## Precedure ##
		//▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤
		int e, i;
		int vi;
		double det, deti, jaco, jacoWeight;

		// [ Transformed Variables ]
		FMatrix_double PSI(__.nvshape, __.dim);
		FCube_double DPSI(__.nvshape, __.dim, __.dim);

		FVector_double vIm(__.dim), vRealP(__.dim);
		FMatrix_double DF(__.dim, __.dim), DFI(__.dim, __.dim), DFIT(__.dim, __.dim), mTemp(__.dim, __.dim);

		// [ L2 Error Variable ]
		FVector_double U_real(__.dim), U_h(__.dim), vErrorL2(__.dim);	vErrorL2.clear();

		// [ Div Error ]
		double div_real, div_h;
		FMatrix_double mDV(__.dim, __.dim);

		// ========================================================
		printf("\n[[ CALCULATE VECTOR ERROR ]] : ");
		printf("   ");

		int percentSave = 0, percent;
		for (e = 0; e<_.neT; e++) {
			percent = ((e + 1) * 100) / _.neT;

			if (percentSave != percent) {
				percentSave = percent;
				printf("\b\b\b\b%3d%%", percent);
			}

			for (k = 0; k<nGauss; k++) {
				FEM::MAPPING::make_realP_and_DF(vRealP, DF, pre_npsi[k], pre_ndpsi[k], _.coordN, _.indexN[e]);
				det = MATH::inverse(DF, DFI);	DFIT.transposeFrom(DFI);	jaco = fabs(det);	jacoWeight = jaco * W[k];
				deti = 1 / det;

				switch (type) {
				case FEM::CALCULATE_ERROR::VECTOR_ID::DIV_MAP:	// PIOLA
					for (i = 0; i<__.nvshape; i++) {
						PSI[i].op("=", deti* drtV[e][i], DF, pre_Vpsi[k][i]);
						mTemp.op("=", deti*drtV[e][i], DF, pre_Vdpsi[k][i]);
						DPSI[i].op("=", mTemp, DFI);
					}
					//	__.drtV.vDrt.print();
					break;
				case FEM::CALCULATE_ERROR::VECTOR_ID::CURL_MAP:
					for (i = 0; i<__.nvshape; i++) PSI[i].op("=", DFIT, pre_Vpsi[k][i]);
					break;
				}

				// [ get real & approximation solution ]
				_problem->V(vRealP, U_real, t);
				div_real = _problem->F(vRealP);
				//	_problem->fDV(vRealP, mDV);
				//	div_real = mDV.trace();

				// [ make U_h, div_h ]
				U_h.clear();
				div_h = 0;

				for (i = 0; i<__.nvshape; i++) {							// summation
					vi = _.indexV[e][i];
					U_h.op("+=", _.vCV[vi], PSI[i]);
					div_h += _.vCV[vi] * DPSI[i].trace();
				}

				// [ U error ]
				(vIm.op("=", U_h, -1., U_real) ^= 2) *= jacoWeight;
				vErrorL2 += vIm;

				//Pause(div_real<<" "<<div_h);
				// [ div error ]
				Div += pow(div_real - div_h, 2.) * jacoWeight;
			}
		}
		L2 = sqrt(vErrorL2.totalSum());
		Div = sqrt(Div);
	}*/

	
	//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
	//▩▩      Matlab의 Solver를 사용하기 위한 함수               ▩▩
	//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
	void solve_in_matlab(IMatrix_double mA, FVector_double & vF, char *filename, int k = -1, char *fileType = "w", char *printType = "", char *indexType = "[%5d]"){

		char fileName[128];

		mA.save_matlab("mA", k, -1);
		vF.save_matlab("vF", k);

		if (k == -1) sprintf(fileName, "%s.m", filename);
		else sprintf(fileName, "%s%d.m", filename, k);

		if (strcmp(printType, "") == 0) {
			printType = "%6.16f";
		}
		FILE* fp = fopen(fileName, fileType);
		int i, j;

		fprintf(fp, "load mA%d.dat; \n", k);
		fprintf(fp, "load vF%d.dat; \n", k);

		//	A_5 = sparse(mA_5(1, :), mA_5(2, :), mA_5(3, :));
		fprintf(fp, "mA=sparse(mA%d(1, :), mA%d(2, :), mA%d(3, :)); \n", k, k, k);
		fprintf(fp, "vCP=mA \\ vF%d; \n", k);

		fprintf(fp, "save vCP%d.txt vCP -ascii -double; \n", k);
		fprintf(fp, "clear mA%d; \n", k);
		fprintf(fp, "clear vF%d; \n", k);


		/*	fprintf(fp, "i = [ ");
		for(i=0; i<mA._row; i++) {
		for(j=0; j<mA[i]._occupiedSize; j++) {
		fprintf(fp, "%d", i+1);
		fprintf(fp, " ");
		}
		}

		fprintf(fp, "];\n");
		fprintf(fp, "j = [ ");
		for(i=0; i<mA._row; i++) {
		for(j=0; j<mA[i]._occupiedSize; j++) {
		fprintf(fp, "%d", mA[i]._index[j]+1);
		fprintf(fp, " ");
		}
		}

		fprintf(fp, "];\n");
		fprintf(fp, "var = [ ");
		for(i=0; i<mA._row; i++) {
		for(j=0; j<mA[i]._occupiedSize; j++) {
		fprintf(fp, "%6.16f", mA[i]._data[j]);
		fprintf(fp, " ");
		}
		}
		fprintf(fp, "];\n");
		fprintf(fp, "mA"); // fprintf(fp, "%d", k);
		fprintf(fp, " = sparse(i,j,var,");
		fprintf(fp, "%d,%d);", mA._row, mA._row);
		fprintf(fp,"\n");

		fprintf(fp, "vF= [");

		for(i=0; i<vF._size; i++) {
		fprintf(fp, "%6.16f", vF(i));
		fprintf(fp, " ");

		}

		filename ="%";

		fprintf(fp, "];\n");

		fprintf(fp, "vCP=mA \\ vF'; \n");

		fprintf(fp, "save vCP%d.txt vCP -ascii ", k);
		*/
		// sol = mldivide(A,b'); \n 
		/*	fprintf(fp, "fid = fopen('vcp%d.txt ', 'w'); \n",k);

		fprintf(fp, "for i=1:size(vF',1) \n");
		fprintf(fp, "fprintf(fid, ' %s",filename); fprintf(fp,".16f ', vCP(i)); \n");
		fprintf(fp, "fprintf(fid,'\\n'); \n");
		fprintf(fp, "end \n");


		fprintf(fp, "fclose(fid); \n");

		*/


		fclose(fp);


	}

	void readSolution(FEM_VARIABLES::LEVEL &_, int k=-1) {
		int i;
		char fileName[128];
		sprintf(fileName, "%s%d.txt", "vCP", k);
		ifstream input(fileName,ios::in); 
	//	if(input == NULL){
	//	cout << "File not found" << endl;
	//	}
		int n=_.vCP._size;
		for (i=0; i<n; i++) {
			input>>_.vCP[i];
		}

	}

	
	//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
	//▩▩                 주 함수로 전체적인 작업을 총괄한다.            ▩▩
	//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
	void	MAIN() {
		INITIALIZE();

		_time.check();														//▷ 시각을 기록하는 것으로 간단히 check() 함수만 부르면 기록된다.
		for (__.nLayer = __.stLayer; __.nLayer <= __.edLayer; __.nLayer++) {
			LAYER_ROUTINE();
			_time.check();
		}
		FEM::PRINT_ERROR_ORDER::All_Levels(__, "P");
		FEM::PRINT_ERROR_ORDER::All_Levels(__, "V");
		_time.print();														//▷ 지금까지 기록해온 시각을 출력해준다.
	}
}; 