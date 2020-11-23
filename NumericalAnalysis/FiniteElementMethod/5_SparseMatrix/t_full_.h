#ifndef ____t_full_
#define ____t_full_

#include "standard_.h"

enum T_FVECTOR_SIGN {D_NOTHING, D_PLUS, D_MINUS, D_MULTIPLICATION, D_DIVISION};

template <class T>												//이 헤더파일에서 template class들의 생성자와 멤버함수를 선언하고 class17_ 에서 구체적으로 정의
class T_FVECTOR{
public:	
	int _size;
	T * _vec;

public:
						T_FVECTOR(int size);
						T_FVECTOR();
						~T_FVECTOR();
	T&					operator()(int);
	T&					operator[](int);
	T_FVECTOR&			operator+(T_FVECTOR&);
	T_FVECTOR&			operator-(T_FVECTOR&);
	T_FVECTOR&			operator=(T_FVECTOR&);
	T_FVECTOR&			operator*(T&); 
	T_FVECTOR&			operator/(T&);
	T					operator*(T_FVECTOR&); 
	T_FVECTOR&			make(int);
	void				clear();
	void				release();
	T_FVECTOR&			op(char* sb, char* se, ...);
	T_FVECTOR&			op(char* sb, double k1,	T_FVECTOR& fv1, double k2,	T_FVECTOR& fv2);
	T_FVECTOR&			op(char* sb, double k1,	T_FMATRIX<T>& fm1, T_FVECTOR& fv1);
	T_FVECTOR&			op(char* sb,			T_FMATRIX<T>& fm1, T_FVECTOR& fv1);

	T					operator,(T_FVECTOR&);
	T_FVECTOR&			normalize();
	T					norm2();
	T					norm2_2();
	T_FVECTOR&			print();
	T_FVECTOR&			setAll(T first, ...) ;

	T_FVECTOR&			operator^=(double k);	
	T_FVECTOR&			operator+=(T k);
	T_FVECTOR&			operator-=(T k);
	T_FVECTOR&			operator*=(T k);
	T_FVECTOR&			operator/=(T k);
	T_FVECTOR&			operator+=(T_FVECTOR& V);
	T_FVECTOR&			operator-=(T_FVECTOR& V);
	T_FVECTOR&			operator*=(T_FVECTOR& V);
	T_FVECTOR&			operator/=(T_FVECTOR& V);

};

template <class T>
class T_FMATRIX{
public:	
	int _row;
	int _col;
	T_FVECTOR<T> * _mat;

public:
						T_FMATRIX(int n, int m);
						T_FMATRIX();
						~T_FMATRIX();
	T_FVECTOR<T>&		operator()(int);
	T_FVECTOR<T>&		operator[](int);
	T&					operator()(int, int);
	T_FMATRIX&			operator=(T_FVECTOR<T>&);
	T_FMATRIX&			make(int, int);
	T_FMATRIX&			setAll(T first, ...);
	void				clear();
	void				release();
	T_FMATRIX&			print();
	T_FMATRIX&			op(char* sb, char* se, ...);
	T_FMATRIX&			op(char* sb, double k, T_FMATRIX& A, T_FMATRIX& B);
	T_FMATRIX&			op(char* sb, T_FMATRIX& A, T_FMATRIX& B);
	void				transpose();

};

template<class T>	inline	T_FMATRIX<T>&	T_FMATRIX<T>::op(char* sb, char* se, ...) {
	va_list list;
	va_start(list, se);
	
	int i, j, k;
	int attri;
	double k1, k2, im;
	T_FVECTOR<T>	*fvp1, *fvp2;
	T_FMATRIX<T>	*fmp1, *fmp2;
//	T_FCUBE<T>		*fcp1;

	// substitution part
	if(strcmp(sb, "=")  == 0) attri = D_NOTHING;
	if(strcmp(sb, "+=") == 0) attri = D_PLUS;
	if(strcmp(sb, "-=") == 0) attri = D_MINUS;
	if(strcmp(sb, "*=") == 0) attri = D_MULTIPLICATION;
	if(strcmp(sb, "/=") == 0) attri = D_DIVISION;

	// operation sentence
//	if(strcmp(se, "kfcfv") == 0) {			
//		k1  = va_arg(list, double);		fcp1 = &va_arg(list, T_FCUBE<T>);		fvp1 = &va_arg(list, T_FVECTOR<T>);
//		for(i=0; i<_row; i++) {		// cube의 미분방향 x, y, z
//			for(j=0; j<_col; j++) {
//				im = k1 * ((*fcp1)[j][i], (*fvp1));
//				FMATRIX_OP;
//			}
//		}
//	}

	//if(strcmp(se, "(kfcfv)^t") == 0) {			
	//	k1  = va_arg(list, double);		fcp1 = &va_arg(list, T_FCUBE<T>);		fvp1 = &va_arg(list, T_FVECTOR<T>);
	//	for(i=0; i<_row; i++) {
	//		(*this)[i].op(sb, "kfmfv", k1, (*fcp1)[i], (*fvp1));
	//	}
	//}

	if(strcmp(se, "kfm+kfm") == 0) {
		k1  = va_arg(list, double);		fmp1 = &va_arg(list, T_FMATRIX<T>);
		k2  = va_arg(list, double);		fmp2 = &va_arg(list, T_FMATRIX<T>);
		for(i=0; i<_row; i++) {
			(*this)[i].op(sb, "kfv+kfv", k1, (*fmp1)[i], k2, (*fmp2)[i]);
		}
	}

	if(strcmp(se, "kfm*kfm") == 0) {
		k1  = va_arg(list, double);		fmp1 = &va_arg(list, T_FMATRIX<T>);
		k2  = va_arg(list, double);		fmp2 = &va_arg(list, T_FMATRIX<T>);
		double kk = k1*k2;

		for(i=0; i<_row; i++) {
			for(j=0; j<_col; j++) {
				im = 0;
				for(k=0; k<(*fmp1)._col; k++) {
					im += (*fmp1)[i][k]*(*fmp2)[k][j];
				}
				im *= kk;
				FMATRIX_OP;
			}
		}
	}

//	if(strcmp(se, "kfm+k") == 0) {
//		k1  = va_arg(list, double);		fmp1 = &va_arg(list, T_FMATRIX<T>);
//		k2  = va_arg(list, double);
//		for(i=0; i<_row; i++) {
//			(*this)[i].op(sb, "kfv+k", k1, (*fmp1)[i], k2);
//		}
//	}

//	if(strcmp(se, "kfm") == 0) {
//		k1  = va_arg(list, double);		fmp1 = &va_arg(list, T_FMATRIX<T>);
//		for(i=0; i<_row; i++) {
//			(*this)[i].op(sb, "kfv", k1, (*fmp1)[i]);
//		}
//	}

//	if(strcmp(se, "k") == 0) {
//		k1  = va_arg(list, double);
//		for(i=0; i<_row; i++) {
//			(*this)[i].op(sb, "k", k1);
//		}
//	}

	if(strcmp(se, "fv(×)fv") == 0) {
		fvp1 = &va_arg(list, T_FVECTOR<T>);		fvp2 = &va_arg(list, T_FVECTOR<T>);
		for(i=0; i<_row; i++) {
			for(j=0; j<_col; j++) {
				im = (*fvp1)[i] * (*fvp2)[j];
				FMATRIX_OP;
			}
		}
	}

	if(strcmp(se, "list") == 0) {
		int stRow = va_arg(list, int);
		int stCol = va_arg(list, int);
		int nRow  = va_arg(list, int);
		int nCol  = va_arg(list, int);
		int edRow = STANDARD::cksMin(stRow+nRow, _row);		// upper row bound
		int edCol = STANDARD::cksMin(stCol+nCol, _col);		// upper col bound

		for(i=stRow; i<edRow; i++) {
			for(j=stCol; j<edCol; j++) {
				im = va_arg(list, T);
				FMATRIX_OP;
			}
		}
	}

	va_end(list);

	return (*this);
}
template<class T>	inline  T_FMATRIX<T>&	T_FMATRIX<T>::op(char* sb, double k, T_FMATRIX<T> &A, T_FMATRIX<T> &B) {
	return op(sb, "kfm*kfm", k, A, 1., B);
}
template<class T>	inline  T_FMATRIX<T>&	T_FMATRIX<T>::op(char* sb, T_FMATRIX<T> &A, T_FMATRIX<T> &B) {
	return op(sb, "kfm*kfm", 1., A, 1., B);
}
T_FVECTOR<double> *fvi_ptr;
#endif