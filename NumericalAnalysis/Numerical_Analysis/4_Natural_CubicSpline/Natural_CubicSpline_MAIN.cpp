#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


class Assignment4 {
private:
	static double Runge(double x) {
		return 1. / (1 + pow(x, 2));
	}
	static double dRunge(double x) {
		return -2.*x / pow(pow(x, 2) + 1, 2);
	}
	static double Exponential(double x) {
		return exp(0.8*x);
	}
	static double dExponential(double x) {
		return 0.8*exp(0.8*x);
	}
private:
	// L-infinite error function
	static double L_infinite_error(const vector<double>& realValue, const vector<double>& estimate) {

		int num_pt = realValue.size();

		if (num_pt != estimate.size()) {
			cout << "size of realValue != size of estimate" << endl;
			exit(-1);
		}

		vector<double> errors(num_pt);

		for (int i = 0; i < num_pt; i++)
			errors[i] = abs(realValue[i] - estimate[i]);

		//Find the maximum element
		vector<double>::iterator max_itr;
		max_itr = max_element(errors.begin(), errors.end());

		double max_error = *max_itr;

		return max_error;
	}

	// Draw graph
	static void draw_graph(const vector<double>& points, const vector<double>& data, const vector<double>& axes, char* filename, int order, int option, bool showDerivative = false) {
		int num_pt = points.size();

		if (num_pt != data.size()) {
			cout << "size of points != size of data" << endl;
			exit(-1);
		}

		FILE *fp = fopen(filename, "w");

		fprintf(fp, "clear all\nclose all\nclc\n");

		if (option == 1) {
			// Plot Runge
			if (showDerivative) {
				fprintf(fp, "syms x;\n");
				fprintf(fp, "F=inline(char(-2*x/(1+x^2)^2),'x');\n");
				fprintf(fp, "ezplot(char(F(x)),[%f,%f,%f,%f])\n", axes[0], axes[1], axes[2], axes[3]);
				fprintf(fp, "grid\n");
				fprintf(fp, "hold all\n");
			}
			else {
				fprintf(fp, "syms x;\n");
				fprintf(fp, "F=inline(char(1/(1+x^2)),'x');\n");
				fprintf(fp, "ezplot(char(F(x)),[%f,%f,%f,%f])\n", axes[0], axes[1], axes[2], axes[3]);
				fprintf(fp, "grid\n");
				fprintf(fp, "hold all\n");
			}
		}
		else if (option == 2) {
			// Plot exp(0.8x);
			if (showDerivative) {
				fprintf(fp, "syms x;\n");
				fprintf(fp, "F=inline(char(0.8*exp(0.8*x)),'x');\n");
				fprintf(fp, "ezplot(char(F(x)),[%f,%f,%f,%f])\n", axes[0], axes[1], axes[2], axes[3]);
				fprintf(fp, "grid\n");
				fprintf(fp, "hold all\n");
			}
			else {
				fprintf(fp, "syms x;\n");
				fprintf(fp, "F=inline(char(exp(0.8*x)),'x');\n");
				fprintf(fp, "ezplot(char(F(x)),[%f,%f,%f,%f])\n", axes[0], axes[1], axes[2], axes[3]);
				fprintf(fp, "grid\n");
				fprintf(fp, "hold all\n");
			}
		}
		else {
			
		}
		// Plot interpolation
		fprintf(fp, "X = [");

		for (int i = 0; i < num_pt; i++)
			fprintf(fp, "%f,", points[i]);
		fprintf(fp, "];\n");

		fprintf(fp, "Y = [");
		for (int i = 0; i < num_pt; i++)
			fprintf(fp, "%f,", data[i]);
		fprintf(fp, "];\n");

		fprintf(fp, "plot(X, Y, 'r--');\n");

		
		// Set the title
		if (option == 1) {
			// Plot Runge
			if (showDerivative) {
				fprintf(fp, "title('dRunge with order %d');\n", order);
			}
			else {
				fprintf(fp, "title('Runge with order %d');\n", order);
			}
		}
		else if (option == 2) {
			// Plot exp(0.8x);
			if (showDerivative) {
				fprintf(fp, "title('dExponential with order %d');\n", order);
			}
			else {
				//fprintf(fp, "title('Exponential with order ');\n");
				fprintf(fp, "title('Exponential with order %d');\n", order);
			}
		}
		else {

		}

		fclose(fp);

	}

	// Print vector
	template<typename T>
	static void showInfo(T v) {
		T::iterator itr;
		for (itr = v.begin(); itr != v.end(); itr++)
			cout << *itr << " ";
		cout << endl;
	}

private:
	static void makeLinearSystem(double(*f)(double x), const vector<double>& interval, int order, vector<vector<double>>& mA, vector<double>&vF, vector<double>& points, vector<double>& y, double& mesh_size) {
		double start = interval[0];
		double end = interval[1];
		double interval_size = end - start;
		mesh_size = interval_size / order;

		int i, j, k;

		//delete[]mA;
		vF.clear();


		mA.resize(order + 1);
		for (i = 0; i < mA.size(); i++)
			mA[i].resize(order + 1, 0);

		vF.resize(order + 1, 0);


		y.resize(order + 1);
		points.resize(order + 1);
		for (i = 0; i < order + 1; i++) {
			points[i] = start + mesh_size*i;
			y[i] = f(points[i]);
		}

		//make A 
		double common_term = mesh_size*mesh_size / 6.;
		
		mA[0][0] = common_term;
		mA[order][order] = common_term;

		
		for (i = 1; i < order; i++) {
			mA[i][i - 1] = common_term;
			mA[i][i + 1] = common_term;
			mA[i][i] = 4 * common_term;
		}

		//make K
		for (i =1; i < order; i++) {
			vF[i] = y[i + 1] - 2 * y[i] + y[i-1];
		}

	}

	static void TridigonalLU(vector<vector<double>>& mA) {
		/*
		mA = LU
		1. diagonal and lower part of mA : L
		mA[i][i-1] = l[i]==mA[i][i-1]
		mA[i][i] = d[i]
		2. upper part of mA : U
		mA[i][i+1] = u[i]
		*/
		
		int size = mA.size();
		
		mA[0][1] = mA[0][1] / mA[0][0];
		for (int i = 1; i < size-1; i++){
			// update L
			mA[i][i] -= mA[i][i - 1] * mA[i - 1][i];
			// update U
			mA[i][i + 1] = mA[i][i + 1] / mA[i][i];
		}
		mA[size - 1][size - 1] -= mA[size - 1][size - 2] * mA[size - 2][size - 1];
	}

	static void TriBackwardSubs(vector<vector<double>>& mA, vector<double>&b, vector<double>&x) {

		int size = b.size();
		x[size - 1] = b[size - 1];

		for (int i = size - 2; i >= 0; i--) {
			x[i] = (b[i] - x[i + 1] * mA[i][i + 1]);
		}

	}

	static void TriForwardSubs(vector<vector<double>>& mA, vector<double>&b, vector<double>&x) {
		
		int size = b.size();
		x[0] = b[0]/mA[0][0];

		for (int i = 1; i < size; i++) {
			x[i] = (b[i] - x[i - 1] * mA[i][i - 1]) / mA[i][i];
		}
		
	}

	static void TriSolver(vector<vector<double>>& mA, vector<double>&b, vector<double>&x) {
		x.resize(b.size());
		TridigonalLU(mA);
		TriForwardSubs(mA, b, x);
		
		for (int i = 0; i < b.size(); i++)
			b[i] = x[i];

		TriBackwardSubs(mA, b, x);
	}

	static double CubicSpline(vector<double>& d, vector<double>& y,vector<double>& points, double mesh_size, double x) {
		int x_idx;
		double c2, c3;
		int i, j;
		int order = d.size();
		double res;
		// Find the subinterval which containing x
		if (x<points[0] || x>points[order - 1]) {
			cout << "CubicSpline : x is out of the interval" << endl;
			exit(1);
		}

		
		for (i = 0; i < order-1; i++) {
			if (points[i] <= x&&x <= points[i + 1]) {
				x_idx = i+1;
				break;
			}
		}
		

		c2 = y[x_idx] / mesh_size - d[x_idx] * mesh_size / 6.;
		c3 = y[x_idx - 1] / mesh_size - d[x_idx - 1] * mesh_size / 6.;
		res = d[x_idx - 1] * pow(points[x_idx] - x, 3) / 6. / mesh_size + d[x_idx] * pow(x - points[x_idx - 1], 3) / 6. / mesh_size + c2*(x - points[x_idx - 1]) + c3*(points[x_idx] - x);
		
		return res;
	}

	static double CubicSpline_derivative(vector<double>& d, vector<double>& y, vector<double>& points, double mesh_size, double x) {
		int x_idx;
		double c1,c2, c3;
		int i, j;
		int order = d.size();
		double res;
		// Find the subinterval which containing x
		if (x<points[0] || x>points[order - 1]) {
			cout << "CubicSpline : x is out of the interval" << endl;
			exit(1);
		}

		x_idx = 0;
		for (i = 0; i < order - 1; i++) {
			if (points[i] <= x&&x <= points[i + 1]) {
				x_idx = i + 1;
				break;
			}
		}
		
		

		c2 = y[x_idx] / mesh_size - d[x_idx] * mesh_size / 6.;
		c3 = y[x_idx - 1] / mesh_size - d[x_idx - 1] * mesh_size / 6.;
		c1 = c2 - c3;
		res = -d[x_idx - 1] * pow(points[x_idx] - x, 2) / (2. * mesh_size) + 
			d[x_idx] * pow(x - points[x_idx - 1], 2) / (2. * mesh_size) + c1;
	
		return res;
	}

public:
	static void Exercise2_5_4_Runge() {
		cout << " =============================================================" << endl;
		cout << " ========================Exercise2_5_4(Runge)=================" << endl;
		int i, j;

		double start = -5.;
		double end = 5.;
		double interval_size = end - start;

		double mesh_size;
		int order;

		vector<int> orders = { 10,20,40,80,160,320,640,1280 };
		vector<char*> filenames = { "Runge_Cubic_10.m", "Runge_Cubic_20.m", "Runge_Cubic_40.m","Runge_Cubic_80.m" };
		vector<char*> dfilenames = { "dRunge_Cubic_10.m", "dRunge_Cubic_20.m", "dRunge_Cubic_40.m","dRunge_Cubic_80.m" };
		vector<double> errors(orders.size()), derivative_errors(orders.size());


		vector<vector<double>> mA;
		vector<double> vF, points, y, spline_coef;

		int test_size = 2001;
		vector<double> test_points(test_size), test_values(test_size), test_derivative(test_size);
		vector<double> estimate_value(test_size), estimate_derivative(test_size);
		
		for (i = 0; i < test_size; i++) {
			test_points[i] = start + (interval_size / (test_size - 1))*i;
			test_values[i] = Runge(test_points[i]);
			test_derivative[i] = dRunge(test_points[i]);
		}

		for (i = 0; i < orders.size(); i++) {

			order = orders[i];
			makeLinearSystem(Runge, { start, end }, order, mA, vF, points, y, mesh_size);
			TriSolver(mA, vF, spline_coef);

		
			//Approximate test points
			for (j = 0; j < test_size; j++) {
				estimate_value[j] = CubicSpline(spline_coef, y, points, mesh_size, test_points[j]);
			}

			for (j = 0; j<test_size; j++)
				estimate_derivative[j] = CubicSpline_derivative(spline_coef, y, points, mesh_size, test_points[j]);

			errors[i] = L_infinite_error(test_values, estimate_value);
			derivative_errors[i] = L_infinite_error(test_derivative, estimate_derivative);

			cout << " Order : " << orders[i] << endl;
			cout << " Error of approximation : " << errors[i] << endl;
			cout << " Error of derivatives : " << derivative_errors[i] << endl << endl;

			//Draw the graph
			if (i < 4) {
				draw_graph(test_points, estimate_value, { -5,5,0,1.1 }, filenames[i],order, 1, false);
				draw_graph(test_points, estimate_derivative, { -5,5,-0.8,0.8 }, dfilenames[i],order, 1, true);
			}
		}

		vector<double> error_order(orders.size() - 2);
		vector<double> ratio(orders.size() - 1);
		for (i = 0; i < orders.size() - 1; i++) {
			ratio[i] = errors[i + 1] / errors[i];
			ratio[i] = -log(ratio[i]) / log(2);
		}
		for (i = 0; i < orders.size() - 2; i++) {
			error_order[i] = log(errors[i + 2] / errors[i + 1]) / log(errors[i + 1] / errors[i]);
		}
		cout << " Orders : "; showInfo(error_order);
		cout << " Ratio : "; showInfo(ratio);
		cout << endl;

		for (i = 0; i < orders.size() - 1; i++) {
			ratio[i] = derivative_errors[i + 1] / derivative_errors[i];
			ratio[i] = -log(ratio[i]) / log(2);
		}
		for (i = 0; i < orders.size() - 2; i++) {
			error_order[i] = log(derivative_errors[i + 2] / derivative_errors[i + 1]) / log(derivative_errors[i + 1] / derivative_errors[i]);
		}
		cout << " Orders(derivative) : "; showInfo(error_order);
		cout << " Ratio(derivative) : "; showInfo(ratio);
		cout << " =============================================================" << endl;
	}

	static void Exercise2_5_4_Exponential() {
		cout << " =============================================================" << endl;
		cout << " ========================Exercise2_5_4(Exponential)===========" << endl;
		int i, j;

		double start = -3.;
		double end = 3.;
		double interval_size = end - start;

		double mesh_size;
		int order;

		vector<int> orders = { 10,20,40,80,160,320,640 };
		vector<char*> filenames = { "Exponential_Cubic_10.m", "Exponential_Cubic_20.m", "Exponential_Cubic_40.m","Exponential_Cubic_80.m" };
		vector<char*> dfilenames = { "dExponential_Cubic_10.m", "dExponential_Cubic_20.m", "dExponential_Cubic_40.m","dExponential_Cubic_80.m" };
		vector<double> errors(orders.size()), derivative_errors(orders.size());


		vector<vector<double>> mA;
		vector<double> vF, points, y, spline_coef;

		int test_size = 2001;
		vector<double> test_points(test_size), test_values(test_size), test_derivative(test_size);
		vector<double> estimate_value(test_size), estimate_derivative(test_size);

		for (i = 0; i < test_size; i++) {
			test_points[i] = start + (interval_size / (test_size - 1))*i;
			test_values[i] = Exponential(test_points[i]);
			test_derivative[i] = dExponential(test_points[i]);
		}


		for (i = 0; i < orders.size(); i++) {

			order = orders[i];

			makeLinearSystem(Exponential, { start, end }, order, mA, vF, points, y, mesh_size);

			TriSolver(mA, vF, spline_coef);
			

			//Approximate test points
			for (j = 0; j < test_size; j++) {
				estimate_value[j] = CubicSpline(spline_coef, y, points, mesh_size, test_points[j]);
			}

			for (j = 0; j<test_size; j++)
				estimate_derivative[j] = CubicSpline_derivative(spline_coef, y, points, mesh_size, test_points[j]);

			errors[i] = L_infinite_error(test_values, estimate_value);
			derivative_errors[i] = L_infinite_error(test_derivative, estimate_derivative);

			cout << " Order : " << orders[i] << endl;
			cout << " Error of approximation : " << errors[i] << endl;
			cout << " Error of derivatives : " << derivative_errors[i] << endl << endl;

			//Draw the graph
			if (i < 4) {
				draw_graph(test_points, estimate_value, { -3,3,0,12 }, filenames[i], order, 2, false);
				draw_graph(test_points, estimate_derivative, { -3,3,0,10 }, dfilenames[i], order, 2, true);
			}
		}

		vector<double> error_order(orders.size() - 2);
		vector<double> ratio(orders.size() - 1);
		for (i = 0; i < orders.size() - 1; i++) {
			ratio[i] = errors[i + 1] / errors[i];
			ratio[i] = -log(ratio[i]) / log(2);
		}
		for (i = 0; i < orders.size() - 2; i++) {
			error_order[i] = log(errors[i + 2] / errors[i + 1]) / log(errors[i + 1] / errors[i]);
		}
		cout << " Orders : "; showInfo(error_order);
		cout << " Ratio : "; showInfo(ratio);
		cout << endl;

		for (i = 0; i < orders.size() - 1; i++) {
			ratio[i] = derivative_errors[i + 1] / derivative_errors[i];
			ratio[i] = -log(ratio[i]) / log(2);
		}
		for (i = 0; i < orders.size() - 2; i++) {
			error_order[i] = log(derivative_errors[i + 2] / derivative_errors[i + 1]) / log(derivative_errors[i + 1] / derivative_errors[i]);
		}
		cout << " Orders(derivative) : "; showInfo(error_order);
		cout << " Ratio(derivative) : "; showInfo(ratio);
		cout << " =============================================================" << endl;
	}

	static void MAIN() {
		Exercise2_5_4_Runge();
		Exercise2_5_4_Exponential();
	}

	
};


int main() {
	Assignment4::MAIN();
	

	return 0;
}
