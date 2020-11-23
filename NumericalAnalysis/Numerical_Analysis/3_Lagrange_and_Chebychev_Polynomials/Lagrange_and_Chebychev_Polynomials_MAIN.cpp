#include <iostream>
#include <cstring>
#include <vector>
#include <deque>
#include <algorithm>
#include <typeinfo>



#define PI 3.141592



using namespace std;

class Assignment3 {
	/*
	(Runge) f(x) = 1/(1+x*x) in [-5, 5]

	Exercise 2.3.7
	: Use Laplace interpolation with n=5, 10, 20, 40
	Find 1. error and 2. Draw the graph (f and p_n)

	Exercise 2.4.5
	: Use Chebyshev points for n = 10, 20, 40
	Find 1. error and 2. Draw the graph (f and p_n)

	Here error : L-infinite error
	*/

	// Runge function and interval
private:
	static double Runge(double x) {
		return 1. / (1 + pow(x, 2));
	}
	static double dRunge(double x) {
		return -2.*x / pow(pow(x, 2) + 1, 2);
	}

	// Interpolation function
	static double LagrangeInterpolation(double(*f)(double x), const vector<double>& points, double input) {

		int order = points.size();

		double res = 0;
		double sum;

		int i, j;

		for (i = 0; i < order; i++) {
			sum = 1.;

			for (j = 0; j < order; j++) {
				if (j != i)
					sum *= (input - points[j]) / (points[i] - points[j]);
			}

			res += f(points[i])*sum;
		}


		return res;
	}

	// Chebyshev points
	static void ChebyshevPoint(int num_pt, const vector<double>& interval, vector<double>& cheby_pt) {
		double start = interval[0];
		double end = interval[1];

		cheby_pt.clear();
		cheby_pt.resize(num_pt);

		for (int i = 0; i < num_pt; i++) {
			cheby_pt[i] = cos((double)(2. * i + 1.)*PI / (2.*num_pt));
			cheby_pt[i] = 0.5 *((end - start)*cheby_pt[i] + (end + start));
		}


	}

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
	static void draw_graph(const vector<double>& points, const vector<double>& data, const vector<double>& axes, char* filename) {
		int num_pt = points.size();

		if (num_pt != data.size()) {
			cout << "size of points != size of data" << endl;
			exit(-1);
		}

		FILE *fp = fopen(filename, "w");

		fprintf(fp, "clear all\nclose all\nclc\n");


		// Plot Runge
		fprintf(fp, "syms x;\n");
		fprintf(fp, "F=inline(char(1/(1+x^2)),'x');\n");
		fprintf(fp, "ezplot(char(F(x)),[%f,%f,%f,%f])\n", axes[0], axes[1], axes[2], axes[3]);
		fprintf(fp, "grid\n");
		fprintf(fp, "hold all\n");

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

public:
	static void Exercise2_3_7(double(*f)(double x) = Runge) {
		cout << " =============================================================" << endl;
		cout << " ========================Exercise2_3_7(Lagrange)==============" << endl;
		double start = -5.;
		double end = 5.;
		double interval_size = end - start;
		int i, j;

		vector<int> orders = { 5, 10, 20, 40 };
		vector<char*> filenames = { "Lagrange_5.m", "Lagrange_10.m", "Lagrange_20.m", "Lagrange_40.m" };
		vector<double> errors(4);

		vector<double> train_points;
		double point;
		int order;


		int test_size = 1001;
		vector<double> test_points(test_size);
		vector<double> test_values(test_size);
		vector<double> estimate_value(test_size);
		for (i = 0; i < test_size; i++) {
			test_points[i] = start + (interval_size / (test_size - 1))*i;
			test_values[i] = f(test_points[i]);
		}

		for (i = 0; i < orders.size(); i++) {
			order = orders[i]+1;

			train_points.clear();
			// Make points which make a Lagrange interpolation
			for (j = 0; j < order; j++) {
				point = start + (interval_size / (order - 1))*j;
				train_points.push_back(point);
			}

			// Approximate test data
			for (j = 0; j < test_size; j++) {
				estimate_value[j] = LagrangeInterpolation(f, train_points, test_points[j]);
			}

			errors[i] = L_infinite_error(test_values, estimate_value);
			//showInfo(train_points);
			cout << " Order : " << orders[i] << ", errors : " << errors[i] << endl;
			draw_graph(test_points, estimate_value, { -5,5,-5,5 }, filenames[i]);

		}

		cout << " =============================================================" << endl;
	}
	static void Exercise2_4_5(double(*f)(double x) = Runge) {
		cout << " =============================================================" << endl;
		cout << " ========================Exercise2_4_5(Chebyshev)=============" << endl;

		double start = -5.;
		double end = 5.;

		double interval_size = end - start;
		int i, j;

		vector<int> orders = { 5, 10, 20, 40 };
		vector<char*> filenames = { "Chebyshev_5.m", "Chebyshev_10.m", "Chebyshev_20.m", "Chebyshev_40.m" };
		vector<double> errors(4);


		vector<double> cheby_points;
		int order;


		int test_size = 1001;
		vector<double> test_points(test_size);
		vector<double> test_values(test_size);
		vector<double> estimate_value(test_size);
		for (i = 0; i < test_size; i++) {
			test_points[i] = start + (interval_size / (test_size - 1))*i;
			test_values[i] = f(test_points[i]);
		}

		for (i = 0; i < orders.size(); i++) {
			order = orders[i] + 1;


			// Find Chebyshev points
			ChebyshevPoint(order, { start, end }, cheby_points);

			// Approximate test data
			for (j = 0; j < test_size; j++) {
				estimate_value[j] = LagrangeInterpolation(f, cheby_points, test_points[j]);
			}

			errors[i] = L_infinite_error(test_values, estimate_value);
			//showInfo(train_points);
			cout << " Order : " << orders[i] << ", errors : " << errors[i] << endl;
			draw_graph(test_points, estimate_value, { -5,5,-0.5,1.5 }, filenames[i]);

		}

		cout << " =============================================================" << endl;

	}
	static void MAIN() {
		Exercise2_3_7();
		cout << endl;
		Exercise2_4_5();
	}
};



int main() {

	Assignment3::MAIN();
	
	return 0;
}
