#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <typeinfo>
using namespace std;



class Assignment2 {
	/*
	Problem :
	(1) f1(x)=(x-1)(x^7+6x^6+3x^2-3)
	Find the zero near 0.757627 and -0.779945
	(2) f2(x)=2x^7-x^6-3.5x^4+2
	Find the zero between -1 and 0.5

	(a)Newton's method for f1 and f2
	(b)Secant Method for f2
	(c) Steffensen's method for f2

	*/
private:
	static double epsilon;
	static double f1(double x)
	{
		return (x - 1)*(pow(x, 7) + 6 * pow(x, 6) + 3 * pow(x, 2) - 3);
	}
	static double df1(double x)
	{
		return (pow(x, 7) + 6 * pow(x, 6) + 3 * pow(x, 2) - 3) + (x - 1)*(7 * pow(x, 6) + 36 * pow(x, 5) + 6 * x);
	}
	static double f2(double x)
	{
		return 2 * pow(x, 7) - pow(x, 6) - 3.5*pow(x, 4) + 2;
	}
	static double df2(double x)
	{
		return 14 * pow(x, 6) - 6 * pow(x, 5) - 14 * pow(x, 3);
	}
	template<typename T>
	static void showInfo(T v) {
		T::iterator itr;
		for (itr = v.begin(); itr != v.end(); itr++)
			cout << *itr << " ";
		cout << endl;
	}

public:
	static double SecantMethod(double(*f)(double x), double x0, double x1, int maxloop, vector<double>& error, deque<double>& z_seq) {
		double z0 = x0;
		double z1 = x1;
		double z;
		int i;

		error.clear();
		z_seq.clear();

		z_seq.push_back(z0);
		z_seq.push_back(z1);
		
		double order;

		for (i = 0; i < maxloop; i++) {
			if (abs(f(z0) - f(z1)) <epsilon) {
				cout << "Take another initial points" << endl;
				exit(-1);
			}

			z = (z0*f(z1) - z1*f(z0)) / (f(z1) - f(z0));
			
			

			if (abs(z - z1) < epsilon || abs(f(z) - f(z1)) < epsilon) {
				break;
			}

			if (z_seq.size() <= 10) {
				z_seq.push_back(z);
			}
			else {
				z_seq.pop_front();
				z_seq.push_back(z);
			}

			z0 = z1;
			z1 = z;
		}
		
		cout << " iteration : " << i << endl;

		

		for (i = 0; i < z_seq.size(); i++)
			z_seq[i] = abs(z_seq[i] - z);
		
		z_seq.pop_back();
		
		
		for (i = 0; i < z_seq.size() - 2; i++) {
			order = log(z_seq[i + 2] / z_seq[i + 1]) / log(z_seq[i + 1] / z_seq[i]);
			error.push_back(order);
		}
			
		
		return z;
	}

	static double NewtonMethod(double(*f)(double x), double(*df)(double x), double x0, int maxloop, vector<double>& error, deque<double>& z_seq) {
		double z0 = x0;
		double z;
		int i;


		
		error.clear();
		z_seq.clear();
		z_seq.push_back(z0);

		double order;

		for (i = 0; i < maxloop; i++) {
			if (abs(df(z0)) < epsilon) {
				cout << "the derivative has zero" << endl;
				exit(-1);
			}

			z = z0 - f(z0) / df(z0);

			

			if (abs(z - z0) < epsilon || abs(f(z)) < epsilon) {
				break;
			}
			
			if (z_seq.size() <= 10) {
				z_seq.push_back(z);
			}
			else {
				z_seq.pop_front();
				z_seq.push_back(z);
			}

			z0 = z;
		}
		cout << " iteration : " << i << endl;

		//showInfo(z_seq);
		for (i = 0; i < z_seq.size(); i++)
			z_seq[i] = abs(z_seq[i] - z);
		
		z_seq.pop_back(); 

		for (i = 0; i < z_seq.size() - 2; i++) {
			order = log(z_seq[i + 2] / z_seq[i + 1]) / log(z_seq[i + 1] / z_seq[i]);
			error.push_back(order);
		}

		
		return z;
	}

	static double SteffensenMethod(double(*f)(double x), double x0, int maxloop, vector<double>& error, deque<double>& z_seq) {
		double z0 = x0;
		double z;
		double denominator, numerator;
		int i;

		error.clear();
		z_seq.clear();
		z_seq.push_back(z0);

		double order;

		for (i = 0; i < maxloop; i++) {
			numerator = pow(f(z0), 2);
			denominator = f(f(z0)+z0) - f(z0);

			if (abs(denominator) < epsilon) {
				cout << " Iteration : " << i << endl;
				cout << " The denominator is zero" << endl;
				exit(-1);
			}

			z = z0 - numerator / denominator;

			

			if (abs(z - z0) < epsilon || abs(f(z)) < epsilon) {
				break;
			}

			if (z_seq.size() <= 10) {
				z_seq.push_back(z);
			}
			else {
				z_seq.pop_front();
				z_seq.push_back(z);
			}

			z0 = z;
		}
		cout << " iteration : " << i << endl;

		for (i = 0; i < z_seq.size(); i++)
			z_seq[i] = abs(z_seq[i] - z);

		z_seq.pop_back();

		for (i = 0; i < z_seq.size() - 2; i++) {
			order = log(z_seq[i + 2] / z_seq[i + 1]) / log(z_seq[i + 1] / z_seq[i]);
			error.push_back(order);
		}

		
		return z;
	}

	static void MAIN() {
		int maxLoop = 100000;
		double root;
		vector<double> error(0);
		deque<double> z_seq(0);
		double startpoint, endpoint;

		cout << " =============================================================" << endl;
		cout << " f1(x) = (x - 1)*(x^7 + 6x^6 + 3x^2 - 3)" << endl;
		cout << " f(x) = 2x^7 - x^6 - 3.5x^4 + 2" << endl;
		cout << " =============================================================" << endl << endl;


		cout << " ======================1. Newton Method=======================" << endl;
		cout << " root of f1 around x=0.1" << endl;
		startpoint = 0.1;
		root = NewtonMethod(f1, df1, startpoint, maxLoop, error ,z_seq);
		cout << " zero of f1 : " << root << "  ,f(root) = " << f1(root) << endl;
		cout << " Error for last 10 term : "; showInfo(z_seq);
		cout << " Order of convergence : "; showInfo(error);
		cout << endl;

		cout << " root of f1 around x=-1.0" << endl;
		startpoint = -1.0;
		root = NewtonMethod(f1, df1, startpoint, maxLoop, error, z_seq);
		cout << " zero of f1 : " << root << "  ,f(root) = " << f1(root) << endl;
		cout << " Error for last 10 term : "; showInfo(z_seq);
		cout << " Order of convergence : "; showInfo(error);
		cout << endl;

		cout << " root of f2 around x=-0.9" << endl;
		startpoint = -0.9;
		root = NewtonMethod(f2, df2, startpoint, maxLoop, error, z_seq);
		cout << " zero of f2 : " << root << "  ,f(root) = " << f2(root) << endl;
		cout << " Error for last 10 term : "; showInfo(z_seq);
		cout << " Order of convergence : "; showInfo(error);
		cout << endl;
		cout << " =============================================================" << endl << endl;


		
		cout << " ======================2. Secant Method=======================" << endl;

		cout << " root of f2 between -1 and 0.5" << endl;
		startpoint = -1.; endpoint = 0.;
		root = SecantMethod(f2, startpoint, endpoint, maxLoop, error, z_seq);
		cout << " zero of f2 : " << root << "  ,f(root) = " << f2(root) << endl;
		cout << " Error for last 10 term : "; showInfo(z_seq);
		cout << " Order of convergence : "; showInfo(error);
		cout << " =============================================================" << endl << endl;


		
		cout << " ======================3. Steffensen Method===================" << endl;
		cout << " root of f1 around x=0.8" << endl;
		startpoint = 0.8;
		root = SteffensenMethod(f1, startpoint, maxLoop, error, z_seq);
		cout << " zero of f1 : " << root << "  ,f(root) = " << f1(root) << endl;
		cout << " Error for last 10 term : "; showInfo(z_seq);
		cout << " Order of convergence : "; showInfo(error);
		cout << endl;

		cout << " root of f1 around x=-0.9" << endl;
		startpoint = -0.9;
		root = SteffensenMethod(f1, startpoint, maxLoop, error, z_seq);
		cout << " zero of f1 : " << root << "  ,f(root) = " << f1(root) << endl;
		cout << " Error for last 10 term : "; showInfo(z_seq);
		cout << " Order of convergence : "; showInfo(error);
		cout << endl;

		cout << " root of f2 around x=-1." << endl;
		startpoint = -1.;
		root = SteffensenMethod(f2, startpoint, maxLoop, error, z_seq);
		cout << " zero of f2 : " << root << "  ,f(root) = " << f2(root) << endl;
		cout << " Error for last 10 term : "; showInfo(z_seq);
		cout << " Order of convergence : "; showInfo(error);
		cout << " =============================================================" << endl<<endl;
	}
};


double Assignment2::epsilon = 2e-16;

int main() {

	Assignment2::MAIN();

	return 0;
}
