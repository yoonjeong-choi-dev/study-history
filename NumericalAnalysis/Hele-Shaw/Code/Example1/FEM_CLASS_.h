 
//�ƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢ�
//============================================================================
//                               CLASS�� ����
//============================================================================
//�ƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢ�
//�� �̰��� ���Ӱ� ����� CLASS�� �����Ѵ�. 
//�� �ڽ��� ���Ӱ� ���� CLASS�� ���� CLASS���� ȥ���� ���ϱ� ���� "_CLASS"�� �ٿ��� ����Ѵ�.

class FEM_CLASS {
public://�� �������� �����Ѵ�.
	C_TIME _time;				//�� �ð��� check �ϱ� ���� �����Ѵ�. ( "c_time_2008.h"�� ��� �ִ�. )
	FEM_VARIABLES::LEVEL _;		//�� ���� LEVEL���� ����� ���� ( "fem_variables_2008.h"�� ��� �ִ�. )
	FEM_VARIABLES::ENTIRE __;	//�� ��ü LEVEL���� ����� ���� ( "fem_variables_2008.h"�� ��� �ִ�. )

	FEM_VARIABLES::IIM iim;		//�� immersed ���� ( "fem_variables_2008.h"�� ��� �ִ�. )
	FEM_VARIABLES::IIM iim_N;
	FMatrix_int drtV;
	double eps;
	double kappa;
	double source_;				// value for the Dirac-delta function

	FVector_double vPHI;
	FVector_double voldPHI;
	FCube_double cInterfaceLocation;
	FMatrix_double vEAt;
	FMatrix_int CI; // index
	FMatrix_double CP; // coordinate
	FMatrix_double IP; // interface point[node][x,y]

	FVector_double Interfact_Element_Curvature; // Curvature on interface element

	double nIP;
	FCube_double CEIP;

public://�� �Լ����� �����Ѵ�.
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	//�̢�                        ������ �����Ѵ�.                        �̢� ( ������ "fem_problems_2008.h"���Ͽ� ��� �ִ�. )
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	void	SET_PROBLEM() {
		_problem = new FEM_PROBLEMS::HELE_SHAW::EXAMPLE1;				//�� _problem�̶�� ������ ������ ����Ѵ�.( �ٸ������� ó���� ��� _problem�� �����ϸ� �ȴ�. )
	//	_problem = new FEM_PROBLEMS::ELLIPTIC::P_ELEMENTARY;				//�� _problem�̶�� ������ ������ ����Ѵ�.( �ٸ������� ó���� ��� _problem�� �����ϸ� �ȴ�. )
		_problem->initialize(__);											//�� _problem������ �������� �ʱ�ȭ ��Ų��.
		eps = 1.;
		kappa = 2.;
		source_ = 0.25;
	}

	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	//�̢�      domain mapping�� �� �� �ʿ��� domain basis�� ����Ѵ�.    �̢�
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	void	SET_DOMAIN_BASIS() {
		__.domain_poly_type[0] = 4;										//�� ��������� ����
		__.nnshape = 4;										//�� domain basis ������ ����
		__.shape.domain = FEM_SHAPES::STANDARD::Q1_CONFORMING;		//�� domain basis�� domain �����Ϳ� ����Ѵ�. ( basis�� "fem_shapes_2008.h"�� ��� �ִ�. )


		// [ Interface Part ] : inteface�� �κп��� noninterface�� �ٸ� space�� ����� ��츦 ����ؼ� ���� ������ �־�� �Ѵ�.
		__.domain_poly_type[1] = 3;										//�� second grid: rectangle
		__.nnshapes[3] = 3;										//�� interface���� triangle�� �ش��ϴ� domain basis ������ ����
		__.nnshapes[4] = 4;										//�� interface���� rectangle�� �ش��ϴ� domain basis ������ ����
		__.shape.domains[3] = FEM_SHAPES::STANDARD::P1_CONFORMING;		//�� interface triangle domain basis�� domain �����Ϳ� ����Ѵ�. ( basis�� "fem_shapes_2008.h"�� ��� �ִ�. )
		__.shape.domains[4] = FEM_SHAPES::STANDARD::Q1_CONFORMING;		//�� interface triangle domain basis�� domain �����Ϳ� ����Ѵ�. ( basis�� "fem_shapes_2008.h"�� ��� �ִ�. )
	}

	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	//�̢�          ������ Ǯ �� ����� solution basis�� ����Ѵ�.        �̢�
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	void	SET_SOLUTION_BASIS() {
		// [ Noninterface Part ]
		__.npshape = 5;										//�� pressure basis ������ ����
		__.shape.pressure = FEM_SHAPES::STANDARD::Q1_CONFORMING_EG;		//�� pressure basis�� pressure �����Ϳ� ����Ѵ�. ( basis�� "fem_shapes_2008.h"�� ��� �ִ�. )
		
		// [ Interface Part ]
		__.npiimshape = 4;
		__.shape.iim_pressure = FEM_SHAPES::STANDARD::Q1_CON_IIM;				//�� interface�� subgrid���� pressure ������ ����
		__.shape.iim_pressure_component = FEM_SHAPES::STANDARD::Q1_CON_COMPONENT;		//�� interface�� subgrid���� pressure component ������ ����

		// [Vecocity Recovery Part]
		__.nvshape = 4;
		__.shape.vector = FEM_SHAPES::MIXED::D2C2_RTB0_SIZE1;
	}

	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	//�̢�  ���н� ����� ����� �� ���鿡���� basis������ �̸� �����Ѵ�. �̢� 
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	void	SET_PREVALUES() {
		// [ ���� �ִ� ��������� �Է¹޴´�. ] ( ���� 3���� �Է��ϸ� ����ϸ� 1���� �Է��ص� Linear�� ��� ��������. )
		//Input("Input the number of Integration order", __.intOrd);
		//Input("Input the number of Integration order of error", __.intErrOrd);
		__.intOrd = __.intErrOrd = 3;	// �Է¹ް� ������ ���� ������ ���� �� �ΰ��� ������ �����Ų��.

		// [ Noninterface Part ]
		__.nGauss = Integration::get_XI_W_2D(__.domain_poly_type[0], __.intOrd, __.XI, __.W, 0, 1);						//�� GaussPoints(XI) �� Weight(W)�� �ҷ����� ������ nGauss�� ���� ( ���а��� class�� "c_integration_2008.h"�� ��� �ִ�. )
		FEM::GET_SHAPE_VALUES::Pre_Values(__.dim, __.XI, __.nnshape, __.shape.domain, __.pre_npsi, __.pre_ndpsi);		//�� domain prevalue�� ���´�.
		FEM::GET_SHAPE_VALUES::Pre_Values(__.dim, __.XI, __.npshape, __.shape.pressure, __.pre_ppsi, __.pre_pdpsi);		//�� pressure prevalue�� ���´�.
		FEM::GET_SHAPE_VALUES::Pre_Values(__.dim, __.XI, __.nvshape, __.shape.vector, __.pre_Vpsi, __.pre_Vdpsi);

		__.nGauss1D = Integration::get_XI_W_1D(__.intOrd, __.XIL, __.WL);
		__.nGauss1D_round = Integration::get_XI_W_2D_ROUND(__.domain_poly_type[0], __.intOrd, __.XILs, __.WL);
		FEM::GET_SHAPE_VALUES::Pre_Values(__.dim, __.XILs, __.nnshape, __.shape.domain, __.pre_nepsi, __.pre_nedpsi);		//�� domain prevalue�� ���´�.
		FEM::GET_SHAPE_VALUES::Pre_Values(__.dim, __.XILs, __.npshape, __.shape.pressure, __.pre_pepsi, __.pre_pedpsi);		//�� velocity prevalue�� ���´�.

		// [ Interface Part ]
		int nD;
		for (int i = 0; i <= 1; i++) {
			nD = __.domain_poly_type[i];
			__.vGauss[nD] = Integration::get_XI_W_2D(__.domain_poly_type[i], __.intOrd, __.XIs[nD], __.Ws[nD], 0, 1);								//�� GaussPoints(XI) �� Weight(W)�� �ҷ����� ������ nGauss�� ���� ( ���а��� class�� "c_integration_2008.h"�� ��� �ִ�. )
			FEM::GET_SHAPE_VALUES::Pre_Values(__.dim, __.XIs[nD], __.nnshapes[nD], __.shape.domains[nD], __.pre_npsis[nD], __.pre_ndpsis[nD]);		//�� interface domain prevalue�� ���´�.
		}
	}

	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	//�̢�	           ������ �ʱ�ȭ ��Ű�� ��ƾ�� ȣ���Ѵ�.              �̢�
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	void	INITIALIZE() {
		SET_PROBLEM();
		SET_DOMAIN_BASIS();
		SET_SOLUTION_BASIS();
		SET_PREVALUES();

		// [ � level(layer)���� �۾��� ������ ���� ]
		Input("Starting Layer", __.stLayer);
		Input("End Layer", __.edLayer);

		// [ ������ ERROR�� ������ �����Ѵ�. ]
		__.errorNames[0] = "L2_ERROR";
		__.errorNames[1] = "H1_ERROR";
		__.errorNames[2] = "Hdiv_ERROR";
	}

	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	//�̢�             ����� element���� �ڷḦ setting�Ѵ�.             �̢�
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	void	ELEMENT_SETTING() {
		printf("\n[[ ELEMENT SETTING..  ]]");

		// [ Domain ������ setting ]
		FEM::CALCULATE_DOMAIN_VARIABLES::Q1_RECTANGLE(_, __);					//�� �ﰢ���ڿ� ���� ������ �����Ѵ�.
	//	_.nsR = 30 * __.nLayer;	// the number of side rectangles
		_.nsE = _.nsR;								// the number of rectangle elements
		_.nsN = _.nsR + 1;
		_.dx = (__.RX(1,0) - __.RX(0,0)) / _.nsR;
		_.dy = (__.RX(1,1) - __.RX(0,1)) / _.nsR;
		_.neT = _.nsR * _.nsR;
		_.nnT = _.nsN * _.nsN;

		FEM::INDEXING::NEIGHBORHOOD_RECT(_,__);
		FEM::INDEXING::Q1_CONFORMING(_, _.indexN, __.nnshape);				//�� domain basis indexing
		FEM::INDEXING::BOUNDARY_Q1_NODAL_RECT(_, __);							//�� boundary�� ��������� ����
		FEM::COORDINATING::STANDARD(_, __);									//�� ������ ��ǥ�� ����Ѵ�.

		FEM::INDEXING::NEIGHBORHOOD_RECT(_, __);								//�� ���� elt�� ������ �����Ѵ�.
		FEM::INDEXING::EDGE_Q1_NONCONFORMING_NODE(_, _.indexL, __.nnshape);

		// [ Pressure ������ setting ]
		FEM::INDEXING::Q1_CONFORMING_BUBBLE(_, _.indexP, __.npshape);		//�� conforming basis���� ������ ���´�. ( ���� ���ص� �����ϴ�. )
		_.npT = _.nnT + _.neT;

		// [ Velocity ������ setting ]
		// [ Velocity ���� ]
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

	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	//�̢�                         memory�� �Ҵ��Ѵ�.                     �̢�
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	void	MEMORY_ALLOCATION() {
		printf("\n[[ VARIABLE SETTING.. ]]");

		_.mA.make(_.npT, 7);
		_.vCP.make(_.npT);
		_.vF.make(_.npT);
		_.vCV.make(_.nvT);
		vPHI.make(_.neT);
		voldPHI.make(_.neT);
		cInterfaceLocation.make(_.neT,3,__.dim);
		vEAt.make(_.neT,2);

		CI.make(_.neT,2); // index
		CP.make(_.neT,2); // coordinate
		IP.make(_.neT, 2);// interface point
		CEIP.make(_.neT, 6, 2);// coordinate of edge CEIP[e][0,1][x,y]
		Interfact_Element_Curvature.make(_.neT);

		CEIP.clear(-1);
		Interfact_Element_Curvature.clear(-10000000.);
		
		for (int e=0; e<_.neT; e++){
			vEAt[e][0] = -1.; // Non Interface
		}

		iim.initialize(__.dim, 3, __.domain_poly_type[0], 4);				//�� dim, subgrid����, main grid node����, subgrid maximun node����
		iim_N.initialize(__.dim, 3, __.domain_poly_type[0], 4);

		__.drtP.make(__.npshape).setValues(__.domain_poly_type[0], -1, -1, _.mEltN);
		__.drtV.make(__.nvshape).setValues(__.domain_poly_type[0], 0, __.nvshape, _.mEltN);

		_.vLevelSet.make(_.nnT);
		_.vEltA.make(_.neT);
	}
	 
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	//�̢�       Simple swap function with 2 variables                 �̢�
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
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

	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	//�̢�                                             �̢�
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	void RECURSIVE_ADJACENT_EDGE_UPDATE(FVector_double& vRealP_1, FVector_double& vRealP_2, FVector_int& interface_count_) {
		
		int e1_x, e1_y, e2_x, e2_y;
		double  inter_edge_x, inter_edge_y;

		e1_x = int((vRealP_1[0] - __.RX[0][0]) / _.dx);
		e1_y = int((vRealP_1[1] - __.RX[0][1]) / _.dy);

		e2_x = int((vRealP_2[0] - __.RX[0][0]) / _.dx);
		e2_y = int((vRealP_2[1] - __.RX[0][1]) / _.dy);

		//Stopping Criteria1 : same element
		if ((abs(e1_x - e2_x) + abs(e1_y - e2_y) == 0)) {
			return;
		}

		//e1<=e2
		int e1, e2, e3;
		e1 = e1_x + e1_y*_.nsR;
		e2 = e2_x + e2_y*_.nsR;

		double x1, x2, y1, y2;
		x1 = vRealP_1[0]; y1 = vRealP_1[1];
		x2 = vRealP_2[0]; y2 = vRealP_2[1];

		if (e1 > e2)
		{
			swap_(e1, e2);
			swap_(e1_x, e2_x);
			swap_(e1_y, e2_y);

			swap_(x1, x2);
			swap_(y1, y2);

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
		vRealP_mid[0] = (x1 + x2) / 2;
		vRealP_mid[1] = (y1 + y2) / 2;

		RECURSIVE_ADJACENT_EDGE_UPDATE(vRealP_1, vRealP_mid, interface_count_);
		RECURSIVE_ADJACENT_EDGE_UPDATE(vRealP_mid, vRealP_2, interface_count_);


	}
	void INTERFACE_ELEMENT_EDGE_UPDATE_YJ(int it, int draw_count=1) {

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

		for (k = 0; k < nIP; k++) {
			vRealP_1 = IP[k];
			if (k+1==nIP)
				vRealP_2 = IP[0];
			else
				vRealP_2 = IP[k+1];

			RECURSIVE_ADJACENT_EDGE_UPDATE(vRealP_1, vRealP_2, interface_count_);
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
	/*
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

		for (k = 0; k < nIP; k++) {
			vRealP_1 = IP[k];
			if (k+1==nIP)
				vRealP_2 = IP[0];
			else
				vRealP_2 = IP[k+1];

			// 
			e1_x = int((vRealP_1[0] - __.RX[0][0] )/ _.dx);
			e1_y = int((vRealP_1[1] - __.RX[0][1] )/ _.dy);
		
			e2_x = int((vRealP_2[0] - __.RX[0][0] )/ _.dx);
			e2_y = int((vRealP_2[1] - __.RX[0][1] )/ _.dy); 
			
			//e1<=e2
			e1 = e1_x + e1_y*_.nsR;
			e2 = e2_x + e2_y*_.nsR;

			x1 = vRealP_1[0]; y1 = vRealP_1[1];
			x2 = vRealP_2[0]; y2 = vRealP_2[1];

			if (e1 > e2)
			{
				swap_(e1, e2);
				swap_(e1_x, e2_x);
				swap_(e1_y, e2_y);

				swap_(x1, x2);
				swap_(y1, y2);
				
			}
 
			if ((abs(e1_x - e2_x) + abs(e1_y - e2_y) == 0)) {
				 
				// pass
			}//case1
			else if ((abs(e1_x - e2_x) + abs(e1_y - e2_y) == 1)) {
				
				MATH::addAtt(_.vEltA[e1], CV.INTERFACE_ELT);	
				MATH::addAtt(_.vEltA[e2], CV.INTERFACE_ELT);
				 

				if (e1_x == e2_x)
				{
					inter_edge_y = _.coordN[_.indexP[e1][2]][1];
					inter_edge_x = (x2 - x1) / (y2 - y1)*(inter_edge_y - y1) + x1;					
				}//case2-1
				else
				{
					inter_edge_x = _.coordN[_.indexP[e1][1]][0];
					inter_edge_y = (y2 - y1) / (x2 - x1)*(inter_edge_x - x1) + y1;
				}//case2-2

				// update CEIP[e1]
				count_Interface = interface_count_[e1];
				CEIP[e1][count_Interface][0] = inter_edge_x;
				CEIP[e1][count_Interface][1] = inter_edge_y;
				interface_count_[e1] = count_Interface + 1;

		//		if (CEIP[e1][0][0] == -1)//new data
		//		{
		//			CEIP[e1][0][0] = inter_edge_x;
		//			CEIP[e1][0][1] = inter_edge_y;
		//		}
		//		else
		//		{
		//			CEIP[e1][1][0] = inter_edge_x;
		//			CEIP[e1][1][1] = inter_edge_y;
		//		}
		
				// update CEIP[e2]
				count_Interface = interface_count_[e2];
				CEIP[e2][count_Interface][0] = inter_edge_x;
				CEIP[e2][count_Interface][1] = inter_edge_y;
				interface_count_[e2] = count_Interface + 1;
		
		//		if (CEIP[e2][0][0] == -1)//new data
		//		{
		//			CEIP[e2][0][0] = inter_edge_x;
		//			CEIP[e2][0][1] = inter_edge_y;
		//		}
		//		else
		//		{
		//			CEIP[e2][1][0] = inter_edge_x;
		//			CEIP[e2][1][1] = inter_edge_y;
		//		} 
		
			}//case2
			else if ( abs (e1_x-e2_x) + abs(e1_y-e2_y) ==2 ) 
			{  
			 	MATH::addAtt(_.vEltA[e1], CV.INTERFACE_ELT);
				MATH::addAtt(_.vEltA[e2], CV.INTERFACE_ELT);

				if (e1_x == e2_x)
				{
					e3 = e1_x + (e1_y + 1)*_.nsR;
					MATH::addAtt(_.vEltA[e3], CV.INTERFACE_ELT);

					//CEIP[e3][0]
					inter_edge_y = _.coordN[_.indexP[e3][0]][1];
					inter_edge_x = (x2 - x1) / (y2 - y1)*(inter_edge_y - y1) + x1;

				
					count_Interface = interface_count_[e3];
					CEIP[e3][count_Interface][0] = inter_edge_x;
					CEIP[e3][count_Interface][1] = inter_edge_y;
					interface_count_[e3] = count_Interface + 1;

				
				//	CEIP[e3][0][0] = inter_edge_x;
				//	CEIP[e3][0][1] = inter_edge_y;
				
					//CEIP[e3][1]
					inter_edge_y = _.coordN[_.indexP[e3][2]][1];
					inter_edge_x = (x2 - x1) / (y2 - y1)*(inter_edge_y - y1) + x1;

					count_Interface = interface_count_[e3];
					CEIP[e3][count_Interface][0] = inter_edge_x;
					CEIP[e3][count_Interface][1] = inter_edge_y;
					interface_count_[e3] = count_Interface + 1;

				
				//	CEIP[e3][1][0] = inter_edge_x;
				//	CEIP[e3][1][1] = inter_edge_y;
				

				}//case3-1
				else if (e1_y == e2_y)
				{
					e3 = (e1_x+1) + e1_y *_.nsR;
					MATH::addAtt(_.vEltA[e3], CV.INTERFACE_ELT);

					//CEIP[e3][0]
					inter_edge_x = _.coordN[_.indexP[e3][0]][0];
					inter_edge_y = (y2 - y1) / (x2 - x1)*(inter_edge_x - x1) + y1;

					count_Interface = interface_count_[e3];
					CEIP[e3][count_Interface][0] = inter_edge_x;
					CEIP[e3][count_Interface][1] = inter_edge_y;
					interface_count_[e3] = count_Interface + 1;
				
				//	CEIP[e3][0][0] = inter_edge_x;
				//	CEIP[e3][0][1] = inter_edge_y;
				
					//CEIP[e3][1]
					inter_edge_x = _.coordN[_.indexP[e3][1]][0];
					inter_edge_y = (y2 - y1) / (x2 - x1)*(inter_edge_x - x1) + y1;

					count_Interface = interface_count_[e3];
					CEIP[e3][count_Interface][0] = inter_edge_x;
					CEIP[e3][count_Interface][1] = inter_edge_y;
					interface_count_[e3] = count_Interface + 1;

				//	CEIP[e3][1][0] = inter_edge_x;
				//	CEIP[e3][1][1] = inter_edge_y;
				

				}//case3-2
				else
				{
					if (e1_x < e2_x)
					{
						cent_x = _.coordN[_.indexP[e1][2]][0];
						cent_y = _.coordN[_.indexP[e1][2]][1];

						if (cent_y < (y2 - y1) / (x2 - x1)*(cent_x - x1) + y1)
						{
							e3 = e1_x + (e1_y + 1)*_.nsR;

							MATH::addAtt(_.vEltA[e3], CV.INTERFACE_ELT);

							//CEIP[e3][0]
							inter_edge_y = _.coordN[_.indexP[e3][0]][1];
							inter_edge_x = (x2 - x1) / (y2 - y1)*(inter_edge_y - y1) + x1;

							count_Interface = interface_count_[e3];
							CEIP[e3][count_Interface][0] = inter_edge_x;
							CEIP[e3][count_Interface][1] = inter_edge_y;
							interface_count_[e3] = count_Interface + 1;

							
						//	CEIP[e3][0][0] = inter_edge_x;
						//	CEIP[e3][0][1] = inter_edge_y;
							

							//CEIP[e3][1]
							inter_edge_x = _.coordN[_.indexP[e3][1]][0];
							inter_edge_y = (y2 - y1) / (x2 - x1)*(inter_edge_x - x1) + y1;

							count_Interface = interface_count_[e3];
							CEIP[e3][count_Interface][0] = inter_edge_x;
							CEIP[e3][count_Interface][1] = inter_edge_y;
							interface_count_[e3] = count_Interface + 1;
							
						//	CEIP[e3][1][0] = inter_edge_x;
						//	CEIP[e3][1][1] = inter_edge_y;
							
						}//case3-3-1 
						else
						{
							e3 = (e1_x + 1) + e1_y *_.nsR;
							MATH::addAtt(_.vEltA[e3], CV.INTERFACE_ELT);

							//CEIP[e3][0]
							inter_edge_x = _.coordN[_.indexP[e3][0]][0];
							inter_edge_y = (y2 - y1) / (x2 - x1)*(inter_edge_x - x1) + y1;


							count_Interface = interface_count_[e3];
							CEIP[e3][count_Interface][0] = inter_edge_x;
							CEIP[e3][count_Interface][1] = inter_edge_y;
							interface_count_[e3] = count_Interface + 1;
							
						//	CEIP[e3][0][0] = inter_edge_x;
						//	CEIP[e3][0][1] = inter_edge_y;
							

							//CEIP[e3][1]
							inter_edge_y = _.coordN[_.indexP[e3][2]][1];
							inter_edge_x = (x2 - x1) / (y2 - y1)*(inter_edge_y - y1) + x1;
							
							count_Interface = interface_count_[e3];
							CEIP[e3][count_Interface][0] = inter_edge_x;
							CEIP[e3][count_Interface][1] = inter_edge_y;
							interface_count_[e3] = count_Interface + 1;
							
						//	CEIP[e3][1][0] = inter_edge_x;
						//	CEIP[e3][1][1] = inter_edge_y;
							

						}//case3-3-2
					}//case3_a
					else
					{
						cent_x = _.coordN[_.indexP[e1][3]][0];
						cent_y = _.coordN[_.indexP[e1][3]][1];

						if (cent_y < (y2 - y1) / (x2 - x1)*(cent_x - x1) + y1)
						{
							e3 = e1_x + (e1_y + 1)*_.nsR;

							MATH::addAtt(_.vEltA[e3], CV.INTERFACE_ELT);

							//CEIP[e3][0]
							inter_edge_y = _.coordN[_.indexP[e3][0]][1];
							inter_edge_x = (x2 - x1) / (y2 - y1)*(inter_edge_y - y1) + x1;

							count_Interface = interface_count_[e3];
							CEIP[e3][count_Interface][0] = inter_edge_x;
							CEIP[e3][count_Interface][1] = inter_edge_y;
							interface_count_[e3] = count_Interface + 1;
							
						//	CEIP[e3][0][0] = inter_edge_x;
						//	CEIP[e3][0][1] = inter_edge_y;
							

							//CEIP[e3][1]
							inter_edge_x = _.coordN[_.indexP[e3][0]][0];
							inter_edge_y = (y2 - y1) / (x2 - x1)*(inter_edge_x - x1) + y1;

							count_Interface = interface_count_[e3];
							CEIP[e3][count_Interface][0] = inter_edge_x;
							CEIP[e3][count_Interface][1] = inter_edge_y;
							interface_count_[e3] = count_Interface + 1;
							
						//	CEIP[e3][1][0] = inter_edge_x;
						//	CEIP[e3][1][1] = inter_edge_y;
							
						}//case3-3-1 
						else
						{
							e3 = (e1_x - 1) + e1_y *_.nsR;
							MATH::addAtt(_.vEltA[e3], CV.INTERFACE_ELT);

							//CEIP[e3][0]
							inter_edge_x = _.coordN[_.indexP[e3][1]][0];
							inter_edge_y = (y2 - y1) / (x2 - x1)*(inter_edge_x - x1) + y1;

							count_Interface = interface_count_[e3];
							CEIP[e3][count_Interface][0] = inter_edge_x;
							CEIP[e3][count_Interface][1] = inter_edge_y;
							interface_count_[e3] = count_Interface + 1;
							
						//	CEIP[e3][0][0] = inter_edge_x;
						//	CEIP[e3][0][1] = inter_edge_y;
							

							//CEIP[e3][1]
							inter_edge_y = _.coordN[_.indexP[e3][2]][1];
							inter_edge_x = (x2 - x1) / (y2 - y1)*(inter_edge_y - y1) + x1;

							count_Interface = interface_count_[e3];
							CEIP[e3][count_Interface][0] = inter_edge_x;
							CEIP[e3][count_Interface][1] = inter_edge_y;
							interface_count_[e3] = count_Interface + 1;
							
						//	CEIP[e3][1][0] = inter_edge_x;
						//	CEIP[e3][1][1] = inter_edge_y;
							
						}//case3-3-2
					}//case3_b
					
				}//case3-3

				 // update CEIP[e1]
				CEIP[e1][interface_count_[e1]] = CEIP[e3][interface_count_[e3]-2];
				interface_count_[e1]++;
				
				CEIP[e2][interface_count_[e2]] = CEIP[e3][interface_count_[e3]-1];
				interface_count_[e2]++;

			
			}//case3
			else  {
				IP.print();
				cout << "Warning: " << endl;
			}//other case


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

		char buffer[128];
		

		if (it%draw_count==0){
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
	*/
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	//�̢�                                             �̢�
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
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
	
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	//�̢�                                             �̢�
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	void INTERFACE_ELEMENT_VLEVELSET_ALL() {
		int e,k,i,j;
		FVector_double vLevelSet(4);
		int nNode = __.domain_poly_type[0];

		static FEM_VARIABLES::IIM	iim(__.dim, 3, nNode, 4);	//subgrid ���� maximum�� 3���̴�
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
				Interfact_Element_Curvature[e]=curvature_;
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
						//
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

	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	//�̢� �̢�
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	void POST_PROCESSING() {

		int e;
		int nNode = __.domain_poly_type[0]; 
		int i = 0;
		static FEM_VARIABLES::IIM	iim(__.dim, 3, nNode, 4);	//subgrid ���� maximum�� 3���̴�
		
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
	
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	//�̢�    find_IIM_Shape_Pressure_Q1_Conforming ����κ�     �̢�
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	void INTERFACE_BASIS_UPDATE() {
		int nOption = FEM::IIFEM::D_IIM + FEM::IIFEM::D_BUBBLE;
		find_IIM_Shape_Pressure_Q1_Conforming(nOption);
	}
	
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	//�̢�  1. �� elmenet ���� get_Cross_Points_Bisection ����   �̢�
	//�̢�  2. �� element ���� FEM::IIFEM::make_SubGrids  ����   �̢�
	//�̢�  3. �� element ���� iim.levelSet update              �̢�
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	void get_iElt_Datas(int e, FEM_VARIABLES::IIM & iim) {
		int nNode = __.domain_poly_type[0];
		int i;
		for (i = 0; i<nNode; i++) 
			iim.vLevelSet[i] = _.vLevelSet[_.indexN[e][i]];										// levelSet value�� �ҷ��´�.
																			//Try(IIFEM::get_Cross_Points(_, __, e, iim););		
		get_Cross_Points_Bisection(e, iim);													// Cross Point���� ã�´�.
		FEM::IIFEM::make_SubGrids(_, __, e, iim);
	}
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	//�̢�                                             �̢�
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	void find_IIM_Shape_Pressure_Q1_Conforming( int nOption = FEM::IIFEM::D_IIM)
	{
		int i, j, e, eA;
		int eN;

		int nNode = __.domain_poly_type[0];
		int nCoef = __.npiimshape;
		double x, y;
		eA = 1;

		// IIM Domain Variable
		static FEM_VARIABLES::IIM	iim(__.dim, 3, nNode, 4);	//subgrid ���� maximum�� 3���̴�
		static FEM_VARIABLES::IIM	iim_N(__.dim, 3, nNode, 4);	//subgrid ���� maximum�� 3���̴�
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
		static FMatrix_double	mIIM(nCoef * 2, nCoef * 2);																				// GE�� ������ �ؾ� �ϹǷ� �����ؼ� ����Ѵ�.
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
			_.cShapeCoef.make(_.neT);																									// petrov galerkin�� ���� �Ϲ��Լ��� ����� ���
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
					vCpr[i] = iim.vCpr.getData_ge(i+1);
					mCurvature_Three_Points[i].op("=",1., mCps[i]);
				}
				mIIM.clear();																									// Initialize
																																//	mIIM.print("", 5);
				for (i = 0; i<nNode; i++) mNodes[i] = _.coordN[_.indexN(e, i)];

				// �� Condition(0~3): +4 Edge average delta functions ��
				for (i = 0; i<4; i++) {																							// 3 delta conditions
					x = mNodes[i][0];
					y = mNodes[i][1];

					if (iim.vLevelSet[i] <= 0) {																				// ���� basis component���� �Է�: 0�� ���η� �ν��Ѵ�.
						mIIM[i].setAll(1., x, y, x*y, 0., 0., 0., 0.);
					}
					else {																										// ���� basis component���� �Է�
						mIIM[i].setAll(0., 0., 0., 0., 1., x, y, x*y);
					}
				}
				// �� Point Continuity(4~5): +2 point continuity ��
				for (i = 0; i<2; i++) {
					__.shape.iim_pressure_component(mCps[i], vComponent);
					mIIM[i + 4].copy(vComponent);
					vComponent *= -1;
					mIIM[i + 4].copy(vComponent, nCoef);
				}

				// �� Second derivative Continuity(6): +1 ��

				mIIM[6].setAll(0., 0., 0., 1., 0., 0., 0., -1.);

				// �� Flux Continuity(7): +1 ��
				// [ Make Normal ]
				if (iim.vIO[1] == CV.IN) vIm.op("=", mCps[1], -1., mCps[0]);
				else vIm.op("=", mCps[0], -1., mCps[1]);
				vN.setAll(-vIm[1], vIm[0]).normalize();																				// 90�� ȸ�� �� normalize
				vMp1.op("=", 0.5, mCps[0], 0.5, mCps[1]);
				// [ Make the Average of coefficients ]
				vMus.clear();
				for (i = 0; i<2; i++) {
					_problem->coef_mu(mCps[i], vIm);
					vMus += vIm;
				}
				vMus *= 0.5; 
				mIIM[7].setAll(0., vN[0] * vMus[0], vN[1] * vMus[0], vMus[0] * (vMp1[0] * vN[1] + vMp1[1] * vN[0]), 0., -vN[0] * vMus[1], -vN[1] * vMus[1], -vMus[1] * (vMp1[0] * vN[1] + vMp1[1] * vN[0]));
				// �� Find IIM Basis Coefficients ��
				if (nOption & FEM::IIFEM::D_IIM) {																					// find IIM coef;
					_.cIIMCoef[e].make(nCoef, nCoef * 2);																				// (basis����, coef����)
					for (i = 0; i<nCoef; i++) {
						mIIM_clone = mIIM;
						vLoad.clear();
						vLoad[i] = 1.;
						SOLVER::GE(mIIM_clone, _.cIIMCoef[e][i], vLoad);
					}
				}

				// �� Find Bubble Coefficients ��
				if (nOption & FEM::IIFEM::D_BUBBLE) {																					// find IIM Bubble coef
					_.cIIMCoefBubble[e].make(1, nCoef * 2);																				// (basis����, coef����) : ������ bubble ����� �޾Ҵٸ� �޸𸮸� �������� ���ƾ� �Ѵ�.
					mIIM_clone = mIIM;
					
					// �� Nonhomogeneous Fulx Conditions: �������� ����Ǵ� �κ� ��
					vLoad.clear();
				//	vCpr.print();
				//	nLocal = (int)iim.vCpr.getData_ge(2);
					for (i = 0; i<2; i++) {
						edge_number = (int)vCpr[i];
						eN = _.mEltN[e][edge_number];
						get_iElt_Datas(eN, iim_N);

						match_index=-100;
						for (j = 0; j<2; j++) {
							mCps_N[j] = iim_N.mCps.getData(j + 1);
							if ( (mCps[i][0]-mCps_N[j][0])*(mCps[i][0]-mCps_N[j][0])  +  (mCps[i][1]-mCps_N[j][1])*(mCps[i][1]-mCps_N[j][1])    < 0.000000000001 ){
								match_index=j;
							}
						}
						mCurvature_Three_Points[2].op("=", 1., mCps_N[(match_index+1)%2]);
						three_point_curvature_ = curvature_(mCurvature_Three_Points);
					//	cout << three_point_curvature_ << endl;
					//	cout << three_point_curvature_ << endl;
					//	vLoad[i + 4] =  three_point_curvature_ * _problem->tau;
					//	vLoad[i + 4] =  (_problem->tau)/(_problem->r0);
						vLoad[i + 4] =  (Interfact_Element_Curvature[e] + Interfact_Element_Curvature[eN])/2  * _problem->tau; // _problem->P_Jump(mCps[i]);
					//	cout << (Interfact_Element_Curvature[e] + Interfact_Element_Curvature[eN])/2 << endl;
					//	vLoad[i + 4] =  0.01;// get point jump
					} 
					//vLoad[5] *= 0.5;																									// flux jump average�� ���Ѵ�.
					vIm.op("=", 0.5, mCps[0], 0.5, mCps[1]);
					vLoad[7] =0.;// _problem->Flux_Jump((mCps[0] + mCps[1]) / 2, vN);
					//if(fabs(vLoad[5]) < 1.0E-15) vLoad[5] = 0;
					//if(vLoad[3] != 0) Pause("vLoad[3] Jump Exists: " << vLoad[3]);
					//if(vLoad[4] != 0) Pause("vLoad[4] Jump Exists: " << vLoad[4]);
					//if(vLoad[5] != 0) Pause("Flux Jump Exists: " << vLoad[5]);
					SOLVER::GE(mIIM_clone, _.cIIMCoefBubble[e][0], vLoad);

					 
				}// end if(nOption & D_BUBBLE)	


				 //	mIIM.print("",5);
				 // �� Find Normal Basis Coefficients ��
				vMus[0] = 1.;
				vMus[1] = 1.;
				mIIM[7].setAll(0., vN[0] * vMus[0], vN[1] * vMus[0], vMus[0] * (vMp1[0] * vN[1] + vMp1[1] * vN[0]), 0., -vN[0] * vMus[1], -vN[1] * vMus[1], -vMus[1] * (vMp1[0] * vN[1] + vMp1[1] * vN[0]));
				//	mIIM[7].setAll(0., vN[0], vN[1], 2.*(vMp1[0] * vN[0] - vMp1[1] * vN[1]), 0., -vN[0], -vN[1], -2.*(vMp1[0] * vN[0] - vMp1[1] * vN[1]));
				if (nOption & FEM::IIFEM::D_IIM) {																					// find IIM coef;
					_.cShapeCoef[e].make(nCoef, nCoef * 2);																				// (basis����, coef����)
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
	double curvature_(FMatrix_double & three_points){
		double x0=three_points[0][0];
		double y0=three_points[0][1];

		double x1=three_points[1][0];
		double y1=three_points[1][1];

		double x2=three_points[2][0];
		double y2=three_points[2][1];

		double area_= x0*(y1-y2) + x1*(y2-y0) + x2*(y0-y1);
		area_ = abs(area_/2);

		double length_1 = sqrt( (x0-x1)*(x0-x1) + (y0-y1)*(y0-y1)  );
		double length_2 = sqrt( (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2)  );
		double length_3 = sqrt( (x2-x0)*(x2-x0) + (y2-y0)*(y2-y0)  );

		double curvature_= 4*area_/length_1/length_2/length_3;
		return curvature_;
	}
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	//�̢�WENO35 Schemes(+ & -) : Update u_** with fivePoint    �̢�
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
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
	

	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	//�̢�Get the Godunov flux with one_dircetion WENO35 scheme �̢�
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	void ONE_DIMENSION_GODUNOV_FLUX(double & u_m, double & u_p, double & vel, double & godunov_flux_){
		if (vel<=0)
			godunov_flux_=vel*u_p;
		if (vel>0)
			godunov_flux_=vel*u_m;
	}
	

	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	//�̢�  WENO scheme for Hamilto-Jacobi equation      �̢�
	//�̢�   - by Guang Shan and Danping Peng             �̢�
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
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


	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	//�̢� Linear Advection of the level set function		   �̢�
	//�̢� Use WENO35 sheme with Godonuv flux				   �̢�
	//�̢�  - update  "vPHI" which is a class variable		   �̢�
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	void LEVEL_SET_UPDATE(double dt){
		int i, j, e, i_x, i_y;
		double vel_u_left=1.; // vel=(u,v)
		double vel_v_top=1.; // vel=(u,v)
		double vel_u_right=1.; // vel=(u,v)
		double vel_v_bottom=1.; // vel=(u,v)

		double vel_u_avg, vel_v_avg;

		int nsE=_.nsE;
		int index_temp=0;
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
		FMatrix_double DF(2,2);
		FMatrix_double DFI(2,2);
		FMatrix_double DFIT(2,2);

		FVector_double U_h(2);
		FMatrix_double VPSI(4, 2);

		FVector_double pre_npsi(4);
		FMatrix_double pre_ndpsi(4,2);

		FMatrix_double pre_Vpsi(4,2);
		FCube_double pre_Vdpsi(4,2,2);
		 
		voldPHI=vPHI;


		for (i_x = 0; i_x<nsE; i_x++){
			for (i_y = 0; i_y<nsE; i_y++) {
				//cout << "Start : " << i_x << ", " << i_y << endl;
				e = i_x + i_y*_.nsR;
				// 1. Setting. Find vel_u_avg
				XI.setAll(0., 0.5);

				// 2. pre_npsi, pre_ndpsi, pre_Vpsi, pre_Vdpsi
				__.shape.domain(XI, pre_npsi, pre_ndpsi);
				__.shape.vector(XI, pre_Vpsi, pre_Vdpsi);


				// 3. DF ��Ȯ�� ã��
				FEM::MAPPING::make_realP_and_DF(vRealP, DF, pre_npsi, pre_ndpsi, _.coordN, _.indexN[e]);					// DF ���Ѵ�. // Real Point�� �˾ƾ� �Ѵ�?
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


				// 3. DF ��Ȯ�� ã��
				FEM::MAPPING::make_realP_and_DF(vRealP, DF, pre_npsi, pre_ndpsi, _.coordN, _.indexN[e]);					// DF ���Ѵ�. // Real Point�� �˾ƾ� �Ѵ�?
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

				// 3. DF ��Ȯ�� ã��
				FEM::MAPPING::make_realP_and_DF(vRealP, DF, pre_npsi, pre_ndpsi, _.coordN, _.indexN[e]);					// DF ���Ѵ�. // Real Point�� �˾ƾ� �Ѵ�?
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

				// 3. DF ��Ȯ�� ã��
				FEM::MAPPING::make_realP_and_DF(vRealP, DF, pre_npsi, pre_ndpsi, _.coordN, _.indexN[e]);					// DF ���Ѵ�. // Real Point�� �˾ƾ� �Ѵ�?
				det = MATH::inverse(DF, DFI);	DFIT.transposeFrom(DFI);	jaco = fabs(det);	deti = 1 / jaco;

				U_h.clear();
				for (i = 0; i < __.nvshape; i++) {
					pi = _.indexV(e, i);
					VPSI[i].op("=", deti*drtV[e][i], DF, pre_Vpsi[i]);
					U_h.op("+=", _.vCV[pi], VPSI[i]);
				}
				vel_v_top = U_h[1]; // vel=(u,v) 

				vel_v_avg = (vel_v_bottom + vel_v_top) / 2.; // Done : find the velocity 

				// Find diff_x_m
				// diff_val = {dphi_{-3}, dphi_{-2}, d_phi_{-1}, d_phi_{0}, d_phi_{1}
				// dphi_{i} = phi(i+1) - phi(i) 
				for (i = 0; i < 5; i++) {
					index_temp = i_x + i - 3;
					if (index_temp < 0) {
						//diff_val[i] = -1000.;
						//diff_val[i] = index_temp*1000.;
						diff_val[i] = 0;
					}
					else if (index_temp + 1 >= nsE) {
						//diff_val[i] = -1000.;
						//diff_val[i] = -(index_temp+1-nsE)*1000.;
						diff_val[i] = 0;
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
						//diff_val[i] = -1000.;
						//diff_val[i] = index_temp*1000.;
						diff_val[i] = 0;
					}
					else if (index_temp + 1 >= nsE) {
						//diff_val[i] = -1000.;
						//diff_val[i] = -(index_temp + 1 - nsE)*1000.;
						diff_val[i] = 0;
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
						//diff_val[i] = -1000.;
						//diff_val[i] = index_temp*1000.;
						diff_val[i] = 0;
					}
					else if (index_temp + 1 >= nsE) {
						//diff_val[i] = -1000.;
						//diff_val[i] = -(index_temp + 1 - nsE)*1000.;
						diff_val[i] = 0;
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
						//diff_val[i] = -1000.;
						//diff_val[i] = index_temp*1000.;
						diff_val[i] = 0;
					}
					else if (index_temp + 1 >= nsE) {
						//diff_val[i] = -1000.;
						//diff_val[i] = -(index_temp + 1 - nsE)*1000.;
						diff_val[i] = 0;
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

		
		voldPHI=vPHI;
		//draw_PHI("test_PHI", 0);
	}
	
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	//�̢� ��(?) ���� : projection for interface points (���� �ʿ�) �̢�
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	void FIND_INTERFACE_POINTS(int it, int draw_count=1) {
		//cout << "FIND_INTERFACE_POINTS  : Start" << endl;
		int i, j, k, e, e0, e1, e2, e3; 
		double a, b, c, x, y;
		double phi, phi_x, phi_y, phi_xx, phi_yy, phi_xy, alpha;
		FMatrix_double He(2, 2);
		FVector_double vHeP(2);
		FVector_double P(2);
		Interfact_Element_Curvature.clear();
		double curvature_=0.;
		for (k = 0; k < nIP; k++) {

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

			alpha = (-b + sqrt(b*b - 4 * a*c)) / 2 / a;

			IP(k, 0) = x + alpha*P(0);
			IP(k, 1) = y + alpha*P(1);

		//	Interfact_Element_Curvature[i + j*_.nsR]=curvature_;
			// Modify IP


			// Save CP
			char buffer[128];
			

			if (it%draw_count==0){
				sprintf(buffer, "%s%d_%d.txt", "IP",__.nLayer,it/draw_count);
				FILE *fp = fopen(buffer, "w");

				for (j = 0; j<nIP; j++) {
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
	
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	//�̢�                                             �̢�
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	void find_Control_Points(int it, int draw_count=1) {

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
							CP(count).setAll(__.RX[0][0]  + (i + 0.5)*_.dx,__.RX[0][1]  + (j + 0.5)*_.dy);
							count = count + 1;
						}
						else
						{
							vRealP.setAll(__.RX[0][0]  + (i + 0.5)*_.dx, __.RX[0][1]  + (j + 0.5)*_.dy);
							repeat_ = false;
							for (k = 0; k<count; k++) {
								if ((CP[k][0] - vRealP[0])*(CP[k][0] - vRealP[0]) + (CP[k][1] - vRealP[1])*(CP[k][1] - vRealP[1]) < 0.000001) {
									repeat_ = true;
								}
							}
							if (repeat_ == false) {
								CI(count).setAll(i, j);
								CP(count).setAll(__.RX[0][0]  + (i + 0.5)*_.dx, __.RX[0][1]  + (j + 0.5)*_.dy);
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
							CP(count).setAll(__.RX[0][0]  + (i + 1.5)*_.dx, __.RX[0][1]  + (j + 0.5)*_.dy);
							count = count + 1;
						}
						else {
							vRealP.setAll(__.RX[0][0]  + (i + 1.5)*_.dx, __.RX[0][1]  +  (j + 0.5)*_.dy);
							repeat_ = false;
							for (k = 0; k<count; k++) {
								if ((CP[k][0] - vRealP[0])*(CP[k][0] - vRealP[0]) + (CP[k][1] - vRealP[1])*(CP[k][1] - vRealP[1]) < 0.000001) {
									repeat_ = true;
								}
							}
							if (repeat_ == false) {
								CI(count).setAll(i + 1, j);
								CP(count).setAll(__.RX[0][0]  + (i + 1.5)*_.dx, __.RX[0][1]  +  (j + 0.5)*_.dy);
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
							CP(count).setAll(__.RX[0][0]  + (i + 1.5)*_.dx, __.RX[0][1]  + (j + 1.5)*_.dy);
							count = count + 1;
						}
						else {
							vRealP.setAll(__.RX[0][0]  + (i + 1.5)*_.dx, __.RX[0][1]  + (j + 1.5)*_.dy);
							repeat_ = false;
							for (k = 0; k<count; k++) {
								if ((CP[k][0] - vRealP[0])*(CP[k][0] - vRealP[0]) + (CP[k][1] - vRealP[1])*(CP[k][1] - vRealP[1]) < 0.000001) {
									repeat_ = true;
								}
							}
							if (repeat_ == false) {
								CI(count).setAll(i + 1, j + 1);
								CP(count).setAll(__.RX[0][0]  + (i + 1.5)*_.dx, __.RX[0][1]  +  (j + 1.5)*_.dy);
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
							CP(count).setAll(__.RX[0][0]  +  (i + 0.5)*_.dx, __.RX[0][1]  + (j + 1.5)*_.dy);
							count = count + 1;
						}
						else {
							vRealP.setAll(__.RX[0][0]  + (i + 0.5)*_.dx,__.RX[0][1]  +  (j + 1.5)*_.dy);
							repeat_ = false;
							for (k = 0; k<count; k++) {
								if ((CP[k][0] - vRealP[0])*(CP[k][0] - vRealP[0]) + (CP[k][1] - vRealP[1])*(CP[k][1] - vRealP[1]) < 0.000001) {
									repeat_ = true;
								}
							}
							if (repeat_ == false) {
								CI(count).setAll(i, j + 1);
								CP(count).setAll(__.RX[0][0]  + (i + 0.5)*_.dx, __.RX[0][1]  + (j + 1.5)*_.dy);
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
			//		CI._row=count;
			//		CP._row=count;
		nIP = count;


		// Curve Algorithm
		FVector_int vHandle_idx(count);
		FMatrix_int copy_CI(count, 2);
		//		vHandle_idx.print();

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
			//		cout <<"idx_c[0]: "  << endl;
			//		copy_CI[idx_ci[0]].print();
			//		cout <<"idx_c[1]: "  << endl;
			//		copy_CI[idx_ci[1]].print();

			if (adj_ct != 2) {
				cout << "adj_ct not 2" << endl;

				char buffer[128];
				sprintf(buffer, "%s.txt", "ERROR_CI");

				FILE *fp = fopen(buffer, "w");

				for (j = 0; j<count; j++) {
					for (i = 0; i<2; i++) {
						fprintf(fp, "%d \t", copy_CI[j][i]);
					}
					fprintf(fp, "\n");
				}

				fclose(fp);
				draw_PHI("PHI_ERROR", 0);

				//exit(-1);
				CI.print();
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
			CP[i][1] = __.RX[0][0] + _.dy*(CI[i][1] + 0.5);
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
		char buffer2[128];
		//	sprintf(buffer2, "%s.txt", "CP");
		

		if (it%draw_count==0){
			sprintf(buffer2, "%s%d_%d.txt", "CP", __.nLayer, it/draw_count);
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

	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	//�̢�    boundary ó�� ������ matrix�� primitive matrix�� �����Ѵ�.  �̢�
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	void	MAKE_PRIMITIVE_MASS_MATRIX(double t) {
		_.mA.clear();
		_.vF.clear();
		// [ Variables ]
		int i, j, l, nl, iN, mi;
		int e, eN;
		int edge;
		int pi, pj;															//�� global pressure number
		int k;																//�� Gauss points
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

		// �� IIM Variables     ��
		int nsbMax, nsbMax_N;												//�� subgrid ���� (Noninterface�� ���� 1���� �ȴ�.)
		int nsb, nsbN;														//�� ������ ����Ű�� subgrid�� ��ȣ
		int nPoly;															//�� subgrid �� polygon type
		FVector_double mus(2);

		double fluxJump;													//�� flux jump���� �����Ѵ�.
		double jaco_l, jacoWeight_l;

		FVector_double vN(__.dim);											//�� interface���� normal vector
		FVector_double vStartP(__.dim);										//�� Line integral�� Line ������
		FVector_double vEndP(__.dim);										//�� Line integral�� Line ����
		// �� Clone Variables   ��
		double mu = 1.;															//�� ���� ����ϰ��� �ϴ� subgrid�� mu���� �����Ѵ�.
		FVector_double vMus(2);												//�� ���� ����ϰ��� �ϴ� subgrid�� cp���� �����Ѵ�.
		FMatrix_double mCps(2, __.dim);										//�� 2���� cp��ǥ�� �����Ѵ�.
		FMatrix_double mNodes(4, __.dim);									//�� subgrid maximum node����, dim
		FMatrix_double mLNodes(2, __.dim);									//�� line ������ ���� ������ ����

		FVector_double PSI(__.npshape);										//�� interface�� noninterface�� psi���� ����
		FMatrix_double DPSI(__.npshape, __.dim);							//�� interface�� noninterface�� dpsi���� ����

		FVector_double PSI_N(__.npshape);									//�� interface�� noninterface�� psi���� ����
		FMatrix_double DPSI_N(__.npshape, __.dim);							//�� interface�� noninterface�� dpsi���� ����

		FVector_double PSI_JUMP(8);											//�� interface�� noninterface�� psi���� ����
		FMatrix_double DPSI_JUMP(8, __.dim);								//�� interface�� noninterface�� dpsi���� ����
		FMatrix_double DPSI_AVE(8, __.dim);

		FVector_double SPSI(__.npshape);									//�� interface�� noninterface�� psi���� ����
		FMatrix_double SDPSI(__.npshape, __.dim);							//�� interface�� noninterface�� dpsi���� ����

		FVector_double BPSI(1);												//�� bubble function�� psi���� ����
		FMatrix_double BDPSI(1, __.dim);

		FVector_double BPSI_N(1);												//�� bubble function�� psi���� ����
		FMatrix_double BDPSI_N(1, __.dim);

		FVector_double BPSI_JUMP(1);											//�� interface�� noninterface�� psi���� ����
		FMatrix_double BDPSI_JUMP(1, __.dim);								//�� interface�� noninterface�� dpsi���� ����
		FMatrix_double BDPSI_AVE(1, __.dim);

		
		printf("\n[[ MAKE MASS MATRIX.. ]] : ");
		printf("    ");

	//	cout << _.vEltA[117] << endl;
	//	if (_.vEltA[117] & CV.INTERFACE_ELT){
	//		get_iElt_Datas(117, iim);
	//		iim.vIO.print();
	//		iim.cSubGrids.print();
	//	}
		

		

		int percentSave = 0, percent;
		for (e = 0; e<_.neT; e++) {
			percent = ((e + 1) * 50) / _.neT;

			if (percentSave != percent) {
				percentSave = percent;
				printf("\b\b\b\b%3d%%", percent);
			}

			//�� �� Noninterface Part ��
			if (!(_.vEltA[e] & CV.INTERFACE_ELT)) {																						
				iim.vIO[0] = (_.vEltA[e] & CV.IN) ? CV.IN : CV.OUT;		//�� noninterface�� ��� in, out ������ vEltA�� ��� �����Ƿ� �װ����� ���´�.
				nsbMax = 1;												//�� subgrid ������ �����Ѵ�.

			}
			//�� �� Interface Part    ��
			else {																												
				get_iElt_Datas(e, iim);									//�� interface elt ������ ���´�.
			//	FEM::IIFEM::get_iElt_Datas(_, __, e, iim);			    
				nsbMax = iim.cSubGrids._height;							//�� subgrid ������ �����Ѵ�.
			}
			//Pause(0);
			for (nsb = 0; nsb < nsbMax; nsb++) {
				if (nsbMax != 1 && iim.cSubGrids[nsb]._row == 2) continue;		//�� ��: ������ ��� �۾��� ���� �ʴ´�. (��, Interface Element���� �����ؾ� �Ѵ�.)
				mNodes._row = __.nnshape;
				//�� �� Noninterface Part  ��
				if (nsbMax == 1) {																										
					for (i = 0; i < __.nnshape; i++)
					{
						mNodes[i].getClone(_.coordN[_.indexN(e, i)]);
					}										//�� mNodes�� ������ ���´�.
															//�� ������ ũ�Ⱑ 3�� �ǰ� �Ѵ�. �ﰢ�� elt���� ����ϹǷ�
				}
				//�� �� Interface Part     ��
				else {																											
					mNodes.getClone(iim.cSubGrids[nsb]);	//�� subgird�� ������ ���´�.
				}
				nPoly = mNodes._row;
				//�� subgird�� polygon ������ �޴´�.
				//mu = (iim.vIO[nsb]==CV.IN)? _problem->mum: _problem->mup;													
				//�� subgird�� �´� mu���� ���´�.
				for (k = 0; k < __.vGauss[nPoly]; k++) {
					// �� Mapping         
				    //�� : Mapping�� ���õ� vRealP, DF, det, DFIT, jacoWeight �� �����ش�.
					FEM::MAPPING::make_realP_and_DF(vRealP, DF, __.pre_npsis(nPoly, k), __.pre_ndpsis(nPoly, k), mNodes);
					det = MATH::inverse(DF, DFIT);	DFIT.transpose();	jaco = fabs(det);	jacoWeight = jaco * __.Ws(nPoly, k);

					//�� �� Noninterface Basis ��
					// non-interface element => original Q1 conforming
					if (nsbMax == 1) {																								
						PSI.getClone(__.pre_ppsi(k));
						for (i = 0; i < __.npshape; i++) {
							DPSI[i].op("=", DFIT, __.pre_pdpsi(k, i));
							BPSI.clear();
							BDPSI.clear();
						}
					}
					//�� �� Interface Basis ��
					// interface element => IFEM scheme
					else {
						__.shape.iim_pressure(vRealP, iim.vIO[nsb], _.cIIMCoef[e], PSI, DPSI);
						__.shape.iim_pressure(vRealP, iim.vIO[nsb], _.cIIMCoefBubble[e], BPSI, BDPSI);

						PSI[4] = 1.;
						DPSI[4].clear();
					}
					// �� Get Real Values ��
					_problem->coef_mu(vRealP, mus);																			// �� ���� ȣ���ؼ� �˸°� �����ش�.
					mu = (iim.vIO[nsb] == CV.IN) ? mus[0] : mus[1];

					//���� �� �κ� :
					_problem->F(vRealP, vF);
					f = (iim.vIO[nsb] == CV.IN) ? vF[0] : vF[1]; 
					
					// �� Weak Equation   ��
					for (j = 0; j < __.npshape; j++) {																					//�� test index "j"
						pj = _.indexP(e, j);

						// [[ _.mA�� ��� ]] : A += ����p^0����q
						for (i = 0; i < __.npshape; i++) {																				//�� trial index "i"
							pi = _.indexP(e, i);
							_.mA[pj][pi] += mu * (DPSI[i], DPSI[j]) * jacoWeight;
						}
						// [[ _.vF�� ��� ]] : F +=��fq  
						_.vF[pj] -= mu * (BDPSI[0], DPSI[j]) * jacoWeight;
						_.vF[pj] += f*PSI[j] * jacoWeight;
					}
				}// end for (k=0; k<__.vGauss[nPoly]; k++) 
			}
		}
		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		//						�� Line Integral ��
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
			// e�� ���� interface element üũ
			if (!(_.vEltA[e] & CV.INTERFACE_ELT)) {																					//�� �� Noninterface Part ��
				iim.vIO[0] = (_.vEltA[e] & CV.IN) ? CV.IN : CV.OUT;																	//�� noninterface�� ��� in, out ������ vEltA�� ��� �����Ƿ� �װ����� ���´�.
				nsbMax = 1;																											//�� subgrid ������ �����Ѵ�.
																																	//splitted = false;
			}
			else {																													//�� �� Interface Part    ��
				get_iElt_Datas(e, iim); 
			//	FEM::IIFEM::get_iElt_Datas(_, __, e, iim);																			//�� interface elt ������ ���´�.
				nsbMax = iim.cSubGrids._height;
			}

			// eN�� ���� interface element üũ
			if (eN < 0) {
				iim_N.vIO[0] = CV.OUT;
				nsbMax_N = 1;
			}
			else if (!(_.vEltA[eN] & CV.INTERFACE_ELT)) {																			//�� �� Noninterface Part ��
				iim_N.vIO[0] = (_.vEltA[eN] & CV.IN) ? CV.IN : CV.OUT;																//�� noninterface�� ��� in, out ������ vEltA�� ��� �����Ƿ� �װ����� ���´�.
				nsbMax_N = 1;																										//�� subgrid ������ �����Ѵ�.
			}
			else {																													//�� �� Interface Part    ��
				get_iElt_Datas(eN, iim_N);
			//	FEM::IIFEM::get_iElt_Datas(_, __, eN, iim_N);																		//�� interface elt ������ ���´�.
				nsbMax_N = iim_N.cSubGrids._height;																					//�� subgrid ������ �����Ѵ�.
			}

			for (k = 0; k<__.nGauss1D; k++) {	// Line Integral point
				for (nsb = 0; nsb<nsbMax; nsb++) {
					bCalculate = false;		//bCalculate = true �� ���� ���

					if (nsbMax == 1) {																								//�� �� Noninterface Basis ��
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
						for (i = 1; i<nPoly; i++) {// 0 �� ���� ���� edge�̹Ƿ� ������� �ƴ���
							if ((((int)((iim.mSbr_temp[nsb][i] + iim.mSbr_temp[nsb][i + 1]) / 2)) % 4 == l) && iim.mSbr_temp[nsb][i + 1] - iim.mSbr_temp[nsb][i] <= 1) { // l�� ��ġ�ϴ� subgrid line�� ã�´�.
								jaco_l = iim.mSbr_temp[nsb][i + 1] - iim.mSbr_temp[nsb][i];
								weight = __.WL[k];
								vRealP.op("=", 1 - __.XIL[k], iim.cSubGrids[nsb][i], __.XIL[k], iim.cSubGrids[nsb][(i + 1) % nPoly]);
								__.shape.iim_pressure(vRealP, iim.vIO[nsb], _.cIIMCoef[e], PSI, DPSI);
								__.shape.iim_pressure(vRealP, iim.vIO[nsb], _.cIIMCoefBubble[e], BPSI, BDPSI);

								PSI[4] = 1.;
								DPSI[4].clear();
								bCalculate = true;
								break;	// Subgrid nsb���� edge l�� ��ġ�ϴ� ���� ���ƾ� �ϳ� ���̴�.
							}
						}
					}

					if (bCalculate == false) continue;
					for (nsbN = 0; nsbN < nsbMax_N; nsbN++) {	// nsb, nsb_N loop
						bCalculate = false;		// bCalculate = true �� ���� �����
												// iim.vIO[nsb] �� iim_N.vIO[nsb_N] �� ���� ���� ���� ���� nsb_N ����
						if (eN >= 0 && iim_N.vIO[nsbN] != iim.vIO[nsb]) continue;
						// element eN ������ PSI, DPSI ���ϴ� ����
						// Noninterface element�� ��� �׻� bCalculate = true
						if (eN < 0) {
							PSI_N.clear();
							DPSI_N.clear();
							BPSI_N.clear();
							BDPSI_N.clear();

							bCalculate = true;
							vRealP_N = vRealP;
						}
						else if (nsbMax_N == 1) {																								//�� �� Noninterface Basis ��
							FEM::MAPPING::make_realP_and_DF(vRealP_N, DF_N, __.pre_nepsi[nl][__.nGauss1D - 1 - k], __.pre_nedpsi[nl][__.nGauss1D - 1 - k], _.coordN, _.indexN[eN]);
							det = MATH::inverse(DF_N, DFIT);	DFIT.transpose();//vRealP.print();
							jaco_l = 1.;//(mNodes((l+1)%__.nvshape) - mNodes(l)).norm2();
							weight = __.WL[__.nGauss1D - 1 - k];
							PSI_N.getClone(__.pre_pepsi(nl, __.nGauss1D - 1 - k));
							for (j = 0; j < __.npshape; j++) DPSI_N[j].op("=", DFIT, __.pre_pedpsi(nl, __.nGauss1D - 1 - k, j));

							BPSI_N.clear();
							BDPSI_N.clear();
							// Interface element�� ��� iim.mSbr[nsb][i] �� iim.mSbr[nsb][i+1] �� ��� l ���� ���� ���� bCalculate = true;
							bCalculate = true;
							
						}
						else {
							nPoly = iim_N.mSbr[nsbN]._size;
							for (i = 1; i < nPoly; i++) {// 0 �� ���� ���� edge�̹Ƿ� ������� �ƴ���
														 //if (((int)((iim_N.mSbr_temp[nsb_N][i]+iim_N.mSbr_temp[nsb_N][i+1])/2))%3 ==l) { // l�� ��ġ�ϴ� subgrid line�� ã�´�.
								if (((int)iim_N.mSbr[nsbN][i] == nl || iim_N.mSbr[nsbN][i] == (nl + 1) % 4) && ((int)iim_N.mSbr[nsbN][(i + 1) % nPoly] == nl || iim_N.mSbr[nsbN][(i + 1) % nPoly] == (nl + 1) % 4) && iim_N.mSbr_temp[nsbN][i + 1] - iim_N.mSbr_temp[nsbN][i] <= 1) {
									jaco_l = iim_N.mSbr_temp[nsbN][i + 1] - iim_N.mSbr_temp[nsbN][i];
									weight = __.WL[__.nGauss1D - 1 - k];
									vRealP_N.op("=", 1 - __.XIL[__.nGauss1D - 1 - k], iim_N.cSubGrids[nsbN][i], __.XIL[__.nGauss1D - 1 - k], iim_N.cSubGrids[nsbN][(i + 1) % nPoly]);

									__.shape.iim_pressure(vRealP_N, iim_N.vIO[nsbN], _.cIIMCoef[eN], PSI_N, DPSI_N);
									__.shape.iim_pressure(vRealP_N, iim_N.vIO[nsbN], _.cIIMCoefBubble[eN], BPSI_N, BDPSI_N);

									PSI_N[4] = 1.;
									DPSI_N[4].clear();
									bCalculate = true;
									break;	// Subgrid nsb_N���� edge l�� ��ġ�ϴ� ���� ���ƾ� �ϳ� ���̴�.
								}
							}
						}


						//  Element e �� nsb ���� l�� ��ġ�ϴ� ���� ������ ���� nsb��
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
						_problem->coef_mu(vRealP, mus);																			// �� ���� ȣ���ؼ� �˸°� �����ش�.
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
		_.mA.trim();															//�� mA���� 0�� �ڷ���� �޸𸮸� ����ش�.
	}
	void	VEL_RECOV(double t=0.) {
		printf("\n[[ VECTOR RECOVERY.. ]] : ");
		printf("    ");
		// [ Variables ]
		int i, j;
		int pi, pj;															//�� global pressure number
		int k;																//�� Gauss points
		int e, eN;															//�� element number
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
		// �� IIM Variables     ��
		int nsbMax, nsbMax_N;												//�� subgrid ���� (Noninterface�� ���� 1���� �ȴ�.)
		int nsb, nsbN;														//�� ������ ����Ű�� subgrid�� ��ȣ
		int nPoly;															//�� subgrid �� polygon type

																			// �� Line Integral Val ��
		double fluxJump;													//�� flux jump���� �����Ѵ�.
		double jaco_l, jacoWeight_l;

		FVector_double vN(__.dim);											//�� interface���� normal vector
		FVector_double vStartP(__.dim);										//�� Line integral�� Line ������
		FVector_double vEndP(__.dim);										//�� Line integral�� Line ����
																			// �� Clone Variables   ��
		FVector_double vMus(2);												//�� ���� ����ϰ��� �ϴ� subgrid�� cp���� �����Ѵ�.
		FMatrix_double mCps(2, __.dim);										//�� 2���� cp��ǥ�� �����Ѵ�.
		FMatrix_double mNodes(4, __.dim);									//�� subgrid maximum node����, dim
		FMatrix_double mLNodes(2, __.dim);									//�� line ������ ���� ������ ����

		FVector_double PSI(__.npshape);										//�� interface�� noninterface�� psi���� ����
		FMatrix_double DPSI(__.npshape, __.dim);							//�� interface�� noninterface�� dpsi���� ����

		FVector_double PSI_N(__.npshape);									//�� interface�� noninterface�� psi���� ����
		FMatrix_double DPSI_N(__.npshape, __.dim);							//�� interface�� noninterface�� dpsi���� ����

		FVector_double PSI_JUMP(8);											//�� interface�� noninterface�� psi���� ����
		FMatrix_double DPSI_JUMP(8, __.dim);								//�� interface�� noninterface�� dpsi���� ����
		FMatrix_double DPSI_AVE(8, __.dim);


		FVector_double BPSI(1);												//�� bubble function�� psi���� ����
		FMatrix_double BDPSI(1, __.dim);

		FVector_double BPSI_N(1);												//�� bubble function�� psi���� ����
		FMatrix_double BDPSI_N(1, __.dim);

		FVector_double BPSI_JUMP(1);											//�� interface�� noninterface�� psi���� ����
		FMatrix_double BDPSI_JUMP(1, __.dim);								//�� interface�� noninterface�� dpsi���� ����
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

			// e�� ���� interface element üũ
			if (!(_.vEltA[e] & CV.INTERFACE_ELT)) {																					//�� �� Noninterface Part ��
				iim.vIO[0] = (_.vEltA[e] & CV.IN) ? CV.IN : CV.OUT;																	//�� noninterface�� ��� in, out ������ vEltA�� ��� �����Ƿ� �װ����� ���´�.
				nsbMax = 1;																											//�� subgrid ������ �����Ѵ�.
																																	//splitted = false;
			}
			else {																													//�� �� Interface Part    ��
				get_iElt_Datas(e, iim);
			//	FEM::IIFEM::get_iElt_Datas(_, __, e, iim);																			//�� interface elt ������ ���´�.
				nsbMax = iim.cSubGrids._height;
			}

			// eN�� ���� interface element üũ
			if (eN < 0) {
				iim_N.vIO[0] = CV.OUT;
				nsbMax_N = 1;
			}
			else if (!(_.vEltA[eN] & CV.INTERFACE_ELT)) {																			//�� �� Noninterface Part ��
				iim_N.vIO[0] = (_.vEltA[eN] & CV.IN) ? CV.IN : CV.OUT;																//�� noninterface�� ��� in, out ������ vEltA�� ��� �����Ƿ� �װ����� ���´�.
				nsbMax_N = 1;																										//�� subgrid ������ �����Ѵ�.
			}
			else {																													//�� �� Interface Part    ��
			//	FEM::IIFEM::get_iElt_Datas(_, __, eN, iim_N);																		//�� interface elt ������ ���´�.
				get_iElt_Datas(eN, iim_N);
				nsbMax_N = iim_N.cSubGrids._height;																					//�� subgrid ������ �����Ѵ�.
			}

			flow_average_ = 0;
			psi_jump = 0;
			vel_dof = 0;

			for (k = 0; k < __.nGauss1D; k++) {	// Line Integral point
				for (nsb = 0; nsb < nsbMax; nsb++) {
					bCalculate = false;		//bCalculate = true �� ���� ���

					if (nsbMax == 1) {																								//�� �� Noninterface Basis ��
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
						for (i = 1; i < nPoly; i++) {// 0 �� ���� ���� edge�̹Ƿ� ������� �ƴ���
							if ((((int)((iim.mSbr_temp[nsb][i] + iim.mSbr_temp[nsb][i + 1]) / 2)) % 4 == l) && iim.mSbr_temp[nsb][i + 1] - iim.mSbr_temp[nsb][i] <= 1) { // l�� ��ġ�ϴ� subgrid line�� ã�´�.
								jaco_l = iim.mSbr_temp[nsb][i + 1] - iim.mSbr_temp[nsb][i];
								weight = __.WL[k];
								vRealP.op("=", 1 - __.XIL[k], iim.cSubGrids[nsb][i], __.XIL[k], iim.cSubGrids[nsb][(i + 1) % nPoly]);
								__.shape.iim_pressure(vRealP, iim.vIO[nsb], _.cIIMCoef[e], PSI, DPSI);
								__.shape.iim_pressure(vRealP, iim.vIO[nsb], _.cIIMCoefBubble[e], BPSI, BDPSI);

								PSI[4] = 1.;
								DPSI[4].clear();
								bCalculate = true;
								break;	// Subgrid nsb���� edge l�� ��ġ�ϴ� ���� ���ƾ� �ϳ� ���̴�.
							}
						}
					}

					if (bCalculate == false) continue;
					for (nsbN = 0; nsbN < nsbMax_N; nsbN++) {	// nsb, nsb_N loop
						bCalculate = false;		// bCalculate = true �� ���� �����

						// iim.vIO[nsb] �� iim_N.vIO[nsb_N] �� ���� ���� ���� ���� nsb_N ����
						if (eN >= 0 && iim_N.vIO[nsbN] != iim.vIO[nsb]) continue;

						// element eN ������ PSI, DPSI ���ϴ� ����
						// Noninterface element�� ��� �׻� bCalculate = true
						if (eN < 0) {
							PSI_N.clear();
							DPSI_N.clear();
							BPSI_N.clear();
							BDPSI_N.clear();
							bCalculate = true;
							vRealP_N = vRealP;
						}
						else if (nsbMax_N == 1) {																								//�� �� Noninterface Basis ��
							FEM::MAPPING::make_realP_and_DF(vRealP_N, DF_N, __.pre_nepsi[nl][__.nGauss1D - 1 - k], __.pre_nedpsi[nl][__.nGauss1D - 1 - k], _.coordN, _.indexN[eN]);
							det = MATH::inverse(DF_N, DFIT);	DFIT.transpose();//vRealP.print();
							jaco_l = 1.;//(mNodes((l+1)%__.nvshape) - mNodes(l)).norm2();
							weight = __.WL[__.nGauss1D - 1 - k];
							PSI_N.getClone(__.pre_pepsi(nl, __.nGauss1D - 1 - k));
							for (j = 0; j < __.npshape; j++) DPSI_N[j].op("=", DFIT, __.pre_pedpsi(nl, __.nGauss1D - 1 - k, j));

							BPSI_N.clear();
							BDPSI_N.clear();
							bCalculate = true;
							// Interface element�� ��� iim.mSbr[nsb][i] �� iim.mSbr[nsb][i+1] �� ��� l ���� ���� ���� bCalculate = true;
						}
						else {
							nPoly = iim_N.mSbr[nsbN]._size;
							for (i = 1; i < nPoly; i++) {
								// 0 �� ���� ���� edge�̹Ƿ� ������� �ƴ���
								//if (((int)((iim_N.mSbr_temp[nsb_N][i]+iim_N.mSbr_temp[nsb_N][i+1])/2))%3 ==l) { // l�� ��ġ�ϴ� subgrid line�� ã�´�.
								if (((int)iim_N.mSbr[nsbN][i] == nl || iim_N.mSbr[nsbN][i] == (nl + 1) % 4) && ((int)iim_N.mSbr[nsbN][(i + 1) % nPoly] == nl || iim_N.mSbr[nsbN][(i + 1) % nPoly] == (nl + 1) % 4) && iim_N.mSbr_temp[nsbN][i + 1] - iim_N.mSbr_temp[nsbN][i] <= 1) {
									jaco_l = iim_N.mSbr_temp[nsbN][i + 1] - iim_N.mSbr_temp[nsbN][i];
									weight = __.WL[__.nGauss1D - 1 - k];
									vRealP_N.op("=", 1 - __.XIL[__.nGauss1D - 1 - k], iim_N.cSubGrids[nsbN][i], __.XIL[__.nGauss1D - 1 - k], iim_N.cSubGrids[nsbN][(i + 1) % nPoly]);

									__.shape.iim_pressure(vRealP_N, iim_N.vIO[nsbN], _.cIIMCoef[eN], PSI_N, DPSI_N);
									__.shape.iim_pressure(vRealP_N, iim_N.vIO[nsbN], _.cIIMCoefBubble[eN], BPSI_N, BDPSI_N);

									PSI_N[4] = 1.;
									DPSI_N[4].clear();
									bCalculate = true;
									break;	// Subgrid nsb_N���� edge l�� ��ġ�ϴ� ���� ���ƾ� �ϳ� ���̴�.
								}
							}
						}


						//  Element e �� nsb ���� l�� ��ġ�ϴ� ���� ������ ���� nsb��
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
						_problem->coef_mu(vRealP, mus);																			// �� ���� ȣ���ؼ� �˸°� �����ش�.
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
	
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	//�̢�                   �� level������ �۾��� �����Ѵ�.              �̢�
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	void LAYER_ROUTINE() {
		PrintInBox("�¢� LEVEL(LAYER) : %d �¢�", __.nLayer);
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
	
	//	FEM::PRINT_ERROR_ORDER::uniform_mesh_2pow_n(__, "P");				//�� x,y������ �����ϰ� �ڸ� uniform mesh������ error�� order�� ����Ѵ�.
	//	FEM::PRINT_ERROR_ORDER::uniform_mesh_2pow_n(__, "V");

		//	if(__.nLayer <= 5) FEM::DRAW_FIGURE::pressure_standard(_,__,"ELLIPTIC_2008_");
	//	if (__.nLayer <=3 ) FEM::DRAW_FIGURE::velocity(_,__,"VELOCITY");
	}

	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	//�̢�                                             �̢�
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	void pressure_standard_IIM(char *filename = "DRAW_PRESSURE_", int k=-1, int nOption = FEM::IIFEM::D_IIM) {

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
		FEM_VARIABLES::IIM	iim(__.dim, 3, __.domain_poly_type[0], 4);		//�� iim variables

		FVector_double PSI(__.npshape);										//�� interface�� noninterface�� psi���� ����
		FMatrix_double DPSI(__.npshape, __.dim);							//�� interface�� noninterface�� dpsi���� ����

		FVector_double BPSI(1);												//�� bubble function�� psi���� ����
		FMatrix_double BDPSI(1, __.dim);									//�� bubble function�� dpsi���� ����


		cNodes[0].make(vPoly[0], __.dim);
		cNodes[1].make(vPoly[1], __.dim);

		cNodes[1].setAll(0., 0., 1., 0., 0., 1.);
		cNodes[0].setAll(0., 0., 1., 0., 1., 1., 0., 1.);
		 
		FCube_double	pre_ppsis(5);					// domain psis on Gauss points
		FCube4_double	pre_pdpsis(5);					// domain dpsis on Gauss points

		for (i = 0; i<2; i++) {
			nPoly = vPoly[i];
			for (n = 0; n<nPoly; n++) {
			//	FEM::GET_SHAPE_VALUES::Pre_Values(__.dim, cNodes[i], nPoly, __.shape.pressure, pre_ppsis[nPoly], pre_pdpsis[nPoly]);		//�� interface domain prevalue�� ���´�.
				FEM::GET_SHAPE_VALUES::Pre_Values(__.dim, cNodes[i], nPoly, __.shape.domain, pre_ppsis[nPoly], pre_pdpsis[nPoly]);		//�� interface domain prevalue�� ���´�.
																																			//__.shape.pressure(cNodes[i][n], pre_ppsis[nPoly][n], pre_pdpsis[nPoly][n]);
			}
		}   

	//	pre_ppsis[4][0].setAll(1., 0., 0., 0.);
		// ========================================================
		printf("\n[[    DRAW SCALAR FIGURE..   ]]");
		printf("   "); 
		for (e = 0; e<_.neT; e++) {
			if (!(_.vEltA[e] & CV.INTERFACE_ELT)) {																						//�� �� Noninterface Part ��
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
			else {																												//�� �� Interface Part    ��
				get_iElt_Datas(e,iim);
		//		FEM::IIFEM::get_iElt_Datas(_, __, e, iim);																			//�� interface elt ������ ���´�.
				nsbMax = iim.cSubGrids._height;																						//�� subgrid ������ �����Ѵ�.

				for (nsb = 0; nsb<nsbMax; nsb++) {
					//if(iim.cSubGrids[nsb]._row == 2) continue;														//�� ������ ��� �۾��� ���� �ʴ´�.
					nPoly = iim.cSubGrids[nsb]._row;

					for (n = 0; n<nPoly; n++) {
						BPSI.clear();

						vRealP = iim.cSubGrids[nsb][n];

						__.shape.iim_pressure(vRealP, iim.vIO[nsb], _.cIIMCoef[e], PSI, DPSI);								//�� vRalp������ basis�� ���� �����.
						__.shape.iim_pressure(vRealP, iim.vIO[nsb], _.cIIMCoefBubble[e], BPSI, BDPSI);						//�� vRalp������ basis�� ���� �����.
			
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

		// ȭ�鿡 ���� polygon�� ����
		bView._nOfBit = polygons.size();
		bView.set(0, polygons.getSize() - 1);
		MATLAB::viewPolygons(bView, fileName, __.nLayer, 50, 30, 1);
	}
	
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	//�̢�  Level set function(PHI) �� �ʱ�ȭ��Ų��				�̢�
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
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


	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	//�̢�                                             �̢�
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
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

	//	INTERFACE_ELEMENT_EDGE_UPDATE(0);
		INTERFACE_ELEMENT_EDGE_UPDATE_YJ(0);
		INTERFACE_ELEMENT_VLEVELSET_ALL();
		INTERFACE_BASIS_UPDATE(); 

	} 

	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	//�̢�                                             �̢�
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
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
			FEM::MAPPING::make_realP_and_DF(vRealP, DF, pre_psi,pre_pdpsi, _.coordN, _.indexN(e)); // F : reference -> element. k�� ° gaussian point�� ������ ���� point�� vRealP.
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
	
	void		IIM_EG_pressure(FEM_VARIABLES::LEVEL &_, FEM_VARIABLES::ENTIRE &__, double& L2, double& H1, int nOption, double t) {
		//�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�
		L2 = H1 = 0;
		double p_real, p_h;
		double error_k;														//�� Gauss point������ error
		FVector_double dp_real(__.dim), dp_h(__.dim), vH1(__.dim);
		//�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�

		// �� General Variables ��
		int i;
		int pi;																//�� global pressure number
		int k;																//�� Gauss points
		int e;																//�� element number
		double det, jaco, jacoWeight;

		FVector_double vRealP(__.dim), vIm(__.dim), vP_real(__.dim);
		FMatrix_double DF(__.dim, __.dim), DFIT(__.dim, __.dim), mDP(__.dim, __.dim);
		FMatrix_double mP_real(2,__.dim);

		// �� IIM Variables     ��
		int nsbMax;															//�� subgrid ���� (Noninterface�� ���� 1���� �ȴ�.)
		int nsb;															//�� ������ ����Ű�� subgrid�� ��ȣ
		int nPoly;															//�� subgrid �� polygon type
		FEM_VARIABLES::IIM	iim;		//�� iim variables
		if (__.domain_poly_type[0] == 3){
			iim.initialize(__.dim, 2, __.domain_poly_type[0], 4);			//�� iim variables
		}
		else {
			iim.initialize(__.dim, 3, __.domain_poly_type[0], 4);			//�� iim variables
		}
		// �� Clone Variables   ��
		double mu;															//�� ���� ����ϰ��� �ϴ� subgrid�� mu���� �����Ѵ�.
		FVector_double vMus(2);												//�� ���� ����ϰ��� �ϴ� subgrid�� cp���� �����Ѵ�.
		FMatrix_double mCps(2, __.dim);										//�� 2���� cp��ǥ�� �����Ѵ�.
		FMatrix_double mNodes(4, __.dim);									//�� subgrid maximum node����, dim

		FVector_double PSI(__.npshape);										//�� interface�� noninterface�� psi���� ����
		FMatrix_double DPSI(__.npshape, __.dim);							//�� interface�� noninterface�� dpsi���� ����

		FVector_double BPSI(1);												//�� bubble function�� psi���� ����
		FMatrix_double BDPSI(1, __.dim);									//�� bubble function�� dpsi���� ����

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
			if (!(_.vEltA[e] & CV.INTERFACE_ELT)) {																					//�� �� Noninterface Part ��
				iim.vIO[0] = (_.vEltA[e] & CV.IN) ? CV.IN : CV.OUT;																	//�� noninterface�� ��� in, out ������ vEltA�� ��� �����Ƿ� �װ����� ���´�.
				nsbMax = 1;																											//�� subgrid ������ �����Ѵ�.
				//Pause(e);
			}
			else {																												//�� �� Interface Part    ��
				get_iElt_Datas(e, iim);	
			//	FEM::IIFEM::get_iElt_Datas(_, __, e, iim);																			//�� interface elt ������ ���´�.
				nsbMax = iim.cSubGrids._height;																						//�� subgrid ������ �����Ѵ�.
			}

			for (nsb = 0; nsb<nsbMax; nsb++) {
				//Pause(iim.cSubGrids[nsb]._row);
				if (nsbMax != 1 && iim.cSubGrids[nsb]._row == 2) continue;														//�� ������ ��� �۾��� ���� �ʴ´�.
				mNodes._row = __.nnshape;																						//�� ������ ũ�Ⱑ 3�� �ǰ� �Ѵ�. �ﰢ�� elt���� ����ϹǷ�
				if (nsbMax == 1) {																										//�� �� Noninterface Part  ��
					for (i = 0; i<__.nnshape; i++) mNodes[i].getClone(_.coordN[_.indexN(e, i)]);										//�� mNodes�� ������ ���´�.
					
				}
				else {																											//�� �� Interface Part     ��
					mNodes.getClone(iim.cSubGrids[nsb]);																	//�� subgird�� ������ ���´�.
				}
				nPoly = mNodes._row;																								//�� subgird�� polygon ������ �޴´�.
				mu = (iim.vIO[nsb] == CV.IN) ? _problem->mum : _problem->mup;													//�� subgird�� �´� mu���� ���´�.

				for (k = 0; k<__.vGauss[nPoly]; k++) {
					// �� Mapping         �� : Mapping�� ���õ� vRealP, DF, det, DFIT, jacoWeight �� �����ش�.
					FEM::MAPPING::make_realP_and_DF(vRealP, DF, __.pre_npsis(nPoly, k), __.pre_ndpsis(nPoly, k), mNodes);
					det = MATH::inverse(DF, DFIT);	DFIT.transpose();	jaco = fabs(det);	jacoWeight = jaco * __.Ws(nPoly, k);

					if (nsbMax == 1) {																								//�� �� Noninterface Basis ��
						PSI.getClone(__.pre_ppsi(k));
						for (i = 0; i<__.npshape; i++) DPSI[i].op("=", DFIT, __.pre_pdpsi(k, i));
					}
					else {																										//�� �� Interface basis    ��
						__.shape.iim_pressure(vRealP, iim.vIO[nsb], _.cIIMCoef[e], PSI, DPSI);								//�� vRalp������ basis�� ���� �����.
						PSI[__.npiimshape] = 1.;	DPSI[__.npiimshape].clear();
						if (nOption & FEM::IIFEM::D_BUBBLE)
							__.shape.iim_pressure(vRealP, iim.vIO[nsb], _.cIIMCoefBubble[e], BPSI, BDPSI);						//�� vRalp������ basis�� ���� �����.
					}
					// �� Get Real Values ��
					_problem->P(vRealP, vP_real,  t);
					p_real = vP_real[iim.vIO[nsb] - 1];

					dp_real.clear();
				//	_problem->P(vRealP, vP_real,  t);
				//	p_real = _problem->P(vRealP, t);
					
					
				//	_problem->DP(vRealP, dp_real,  t); 
					_problem->DP(vRealP, mDP,t);
					dp_real = mDP[iim.vIO[nsb] - 1];  
					 
					// �� Get p_h, dp_h   ��
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
						if (nsbMax != 1) {																									//�� ��: Interface�� NonInterface�� �¹��� �����Ƿ� Interface�� ó���ؾ� �ϴ� ���� �� ������ ��
							p_h += BPSI[0];
							dp_h += BDPSI[0];
						}
					}
					// �� Error Calculate ��
					error_k = fabs(p_real - p_h);
					L2 += pow(error_k, 2.) * jacoWeight; //Pause(pow(errorM,2.)<<" "<<W[k]<<" "<<jacoWeight<<" "<<L2);
					vH1.op("+=", "k(kfv+kfv)^k", jacoWeight, 1., dp_real, -1., dp_h, 2.);	// += (dp-dp_h)^2 * jacoWeight
				}// for (k=0; k<__.vGauss[nPoly]; k++)
			}// end for (nsb=0; nsb<nsbMax; nsb++)
		}// end for (e=0; e<_.neT; e++)
		L2 = sqrt(L2);
		H1 = sqrt(vH1.totalSum());
	}
	
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

	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	//�̢�                 �� �Լ��� ��ü���� �۾��� �Ѱ��Ѵ�.            �̢�
	//�̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢̢�
	void	MAIN() {
		INITIALIZE();

		_time.check();														//�� �ð��� ����ϴ� ������ ������ check() �Լ��� �θ��� ��ϵȴ�.
		for (__.nLayer = __.stLayer; __.nLayer <= __.edLayer; __.nLayer++) {
			LAYER_ROUTINE();
			_time.check();
		}
		FEM::PRINT_ERROR_ORDER::All_Levels(__, "P");
		FEM::PRINT_ERROR_ORDER::All_Levels(__, "V");
		_time.print();														//�� ���ݱ��� ����ؿ� �ð��� ������ش�.
	}
}; 