#include <iostream>
#include <algorithm>
#include <typeinfo>
using namespace std;

class Assignment1 {
	// Exercise 1.1.2
private:

	static bool doubleEqual(double a, double b) {
		const double epsil = 1.0e-15;
		double diff = fabs(a - b);

		// 절대 오차가 매우작으면 같다고 처리
		if (diff <= epsil)
			return true;

		//ralative Error i.e |a-b|/max(|a|, |b|)
		return diff <= epsil*max(fabs(a), fabs(b));
	}

	static double func(double x) {
		return exp(-x) - (1 - x + pow(x, 2) / 2);
	}

	static double taylor(double x, int order) {
		double factorial = 1./2;
		double sum = 0.;

		for (int i = 3; i <= order; i++) {
			factorial /= (double)i;
			if (i % 2 == 0)
				sum += pow(x, i)*(factorial);
			else
				sum -= pow(x, i)*(factorial);
		}

		return sum;
	}

	static double nested(double x, int order) {
		double sum = 1.;
		for (int i = order; i >= 4; i--) {
			sum = 1 - x*sum / (double)i;
		}
		sum = -1. / 6 * pow(x, 3)*sum;
		return sum;
	}

public:
	static void Exercise1() {
		const double epsil = 1.0e-15;
		
		const int max_itr =2000;
		double test_point = 4.5;
		cout.precision(16);

		double real_val = func(test_point);
		cout << " Real value at x="<< test_point<<" : " << real_val << endl;
		
		int i;

		double taylor_val, nested_val;
		
		cout << " ======================Taylor expansion====================== " << endl;
		for (i = 3; i < max_itr; i++) {
			taylor_val = taylor(test_point, i);

			if (doubleEqual(taylor_val, real_val)) {
				cout << " Order : " << i << endl;
				cout << " Taylor : " << taylor_val << endl;
				cout << " Differ : " << abs(taylor_val - real_val) << endl;
				break;
			}
		}
		cout << endl;
		cout << " ======================Nested expression===================== " << endl;
		for (i = 3; i < max_itr; i++) {
			nested_val = nested(test_point, i);
			if (doubleEqual(nested_val, real_val)) {
				cout << " Order : " << i << endl;
				cout << " Nested : " << nested_val << endl;
				cout << " Differ : " << abs(nested_val - real_val) << endl;
				break;
			}
		}

		cout << endl;
		cout << " ===========Comparison Taylor and Nested expression==========" << endl;
		for (i = 3; i < max_itr; i++) {
			taylor_val = taylor(test_point, i);
			nested_val = nested(test_point, i);

			if (abs(nested_val-taylor_val)>epsil) {
				cout.precision(16);
				cout << " Order : " << i << endl;
				cout << " Taylor : " << taylor_val << endl;
				cout << " Nested : " << nested_val << endl;
				cout << " Differ : " << abs(taylor_val - nested_val) << endl;
				/*double err1 = abs(real_val - taylor_val);
				double err2 = abs(real_val - nested_val);
				cout << "Diff(real, taylor) : " << err1 << endl;
				cout << "Diff(real, nested) : " << err2 << endl;*/
				break;
			}
		}
		cout << endl;
		return;
	}
	static void Exercise2() {
		cout.precision(16);

		float fs = 1.0f;
		float ft;
		for (int i = 0; i < 2000; i++) {
			fs = fs *0.5;
			ft = fs + 1.0;
			if (ft <= 1.0) {
				cout << " ==========flaot============" << endl;
				cout << " iteration : " << i - 1 << endl;
				cout << " Machine eplison : " << fs*2.0 << endl;
				cout << " ===========================" << endl;
				break;
			}
		}

		double ds = 1.0;
		double dt;
		for (int i = 0; i < 2000; i++) {
			ds = ds *0.5;
			dt = ds + 1.0;
			if (dt <= 1.0) {
				cout << " ==========double============" << endl;
				cout << " iteration : " << i - 1 << endl;
				cout << " Machine eplison : " << ds*2.0 << endl;
				cout << " ===========================" << endl;
				break;
			}
		}
		
		
		return;
	}
	static void Exercise3() {
		cout.precision(16);


		float fs = 1.0f;
		for (int i = 0; i < 2000; i++) {
			fs = fs * 0.5f;
			if (fs + 1.0 <= 1.0) {
				cout << " ==========flaot============" << endl;
				cout << " fs type : " << typeid(fs).name() << endl;
				cout << " iteration : " << i - 1 << endl;
				cout << " Machine eplison : " << fs*2.0 << endl;
				cout << " ===========================" << endl;
				break;
			}
		}

		double ds = 1.0;
		
		for (int i = 0; i < 2000; i++) {
			ds = (double)ds *0.5;
			if (ds + 1.0 <= 1.0) {
				cout << " ==========double============" << endl;
				cout << " iteration : " << i - 1 << endl;
				cout << " Machine eplison : " << ds*2.0 << endl;
				cout << " ===========================" << endl;
				break;
			}
		}

		return;
	}

	static void Exercise3_modified() {
		cout.precision(16);


		float fs = 1.0f;
		for (int i = 0; i < 2000; i++) {
			fs = fs * 0.5f;

			if (fs + 1.0f <= 1.0f) {
				cout << " ==========flaot============" << endl;
				cout << " fs type : " << typeid(fs).name() << endl;
				cout << " iteration : " << i - 1 << endl;
				cout << " Machine eplison : " << fs*2.0 << endl;
				cout << " ===========================" << endl;
				break;
			}
		}

		double ds = 1.0;

		for (int i = 0; i < 2000; i++) {
			ds = (double)ds / 2;
			if (ds + 1.0 <= 1.0) {
				cout << " ==========double============" << endl;
				cout << " iteration : " << i - 1 << endl;
				cout << " Machine eplison : " << ds*2.0 << endl;
				cout << " ===========================" << endl;
				break;
			}
		}

		

		return;
	}

	static void MAIN() {

		cout << endl;

		cout << " ==========================Exericse 1==========================" << endl;
		Assignment1::Exercise1();
		cout << " ==============================================================" << endl;

		cout << endl;

		cout << " ==========================Exericse 2==========================" << endl;
		Assignment1::Exercise2();
		cout << " ==============================================================" << endl;

		cout << endl;

		cout << " ==========================Exericse 3==========================" << endl;
		Assignment1::Exercise3();
		cout << " ==============================================================" << endl;

		cout << endl;

		cout << " =====================Exericse 3(Modified)=====================" << endl;
		Assignment1::Exercise3_modified();
		cout << " ==============================================================" << endl;
		cout << endl;
	}

	
};




int main() {
	
	
	Assignment1::MAIN();
	//cout << typeid(1.0).name() << endl;

	return 0;
}