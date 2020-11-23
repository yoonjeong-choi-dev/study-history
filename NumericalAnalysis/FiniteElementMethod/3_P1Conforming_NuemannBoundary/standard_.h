#ifndef ____standard_
#define ____standard_
#include <stdarg.h>
#include <time.h>
#include <math.h>
#include<iostream>
using namespace std;


template<class T> class T_FVECTOR;
template<class T> class T_FMATRIX;

typedef T_FVECTOR<char>				FVector_char;					//template class들을 typedef를 이용하여 새로운 이름으로 정의
typedef T_FVECTOR<int>				FVector_int;
typedef T_FVECTOR<double>			FVector_double;
typedef T_FMATRIX<char>				FMatrix_char;
typedef T_FMATRIX<int>				FMatrix_int;
typedef T_FMATRIX<double>			FMatrix_double;



#define FVECTOR_OP(x) {\
switch(attri) {\
	case D_NOTHING:			_vec[x]  = (T)im;	break;\
	case D_PLUS:			_vec[x] += (T)im;	break;\
	case D_MINUS:			_vec[x] -= (T)im;	break;\
	case D_MULTIPLICATION:	_vec[x] *= (T)im;	break;\
	case D_DIVISION:		if(im!=0) _vec[x] /= (T)im;	break;\
}\
}
#define FMATRIX_OP {\
switch(attri) {\
	case D_NOTHING:			_mat[i][j]  = (T)im;	break;\
	case D_PLUS:			_mat[i][j] += (T)im;	break;\
	case D_MINUS:			_mat[i][j] -= (T)im;	break;\
	case D_MULTIPLICATION:	_mat[i][j] *= (T)im;	break;\
	case D_DIVISION:		if(im!=0) _mat[i][j] /= (T)im;	break;\
}\
}

#endif