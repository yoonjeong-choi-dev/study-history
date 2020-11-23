#include "standard_.h"
#include "t_full_.h"

//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
//============================================================================
//                                 T_FVECTOR
//============================================================================
//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
template <class T>							T_FVECTOR<T>::T_FVECTOR(int n){				//t_full 에서 선언된 template class들의 생성자와 멤버함수들을 구체적으로 정의
	_size=n;
	_vec = new T [_size];
	int i;
	for (i=0; i< _size; i++)	_vec[i]=0;
}
template <class T>							T_FVECTOR<T>::T_FVECTOR(){
	_size=0;
	_vec=NULL;
}
template <class T>							T_FVECTOR<T>::~T_FVECTOR(){
	if (_vec!=NULL)
	{
		free(_vec);
		_vec=NULL;
	}
}
template <class T> void						T_FVECTOR<T>::release(){
	if (_vec!=NULL)
	{
		free(_vec);
		_vec=NULL;
	}
}
template <class T>	T&						T_FVECTOR<T>::operator()(int n){
	return _vec[n];
}
template <class T>	T&						T_FVECTOR<T>::operator[](int n){
	return _vec[n];
}
template <class T>	T_FVECTOR<T> &			T_FVECTOR<T>::operator=(T_FVECTOR<T>& v){

	_size=v._size;
	_vec = new T [_size];
	for (int i=0; i<v._size; i++)	_vec[i]= v[i];
	return *this;
	
}
template<class T>	T						T_FVECTOR<T>::operator,(T_FVECTOR& V){
	int n=_size;
	int i;
	T sum=0;
	for (i=0; i<n; i++)	sum+=_vec[i]*V[i];
	return sum;
}
template <class T>	T_FVECTOR<T> &			T_FVECTOR<T>::operator/=(T k){
	int i;
	for (i=0; i<_size; i++) _vec[i]/=k;
	return (*this);
}
template <class T>	T_FVECTOR<T> &			T_FVECTOR<T>::operator*=(T k){
	int i;
	for (i=0; i<_size; i++) _vec[i]*=k;
	return (*this);
}
template <class T>	T_FVECTOR<T> &			T_FVECTOR<T>::make(int n){
	int i;
	_size=n;
	(*this).~T_FVECTOR();
	_vec = new T [_size];
	for (i=0; i< _size; i++)	_vec[i]=0;
	return (*this);
}
template <class T>	void					T_FVECTOR<T>::clear(){
	int i;
	for (i=0; i<_size; i++)	_vec[i]=0;
}

template<class T>	inline T_FVECTOR<T>&	T_FVECTOR<T>::op(char* sb, char* se, ...) {

	int attri;

	va_list list;
	va_start(list, se);

	T data;
	double k1, k2, k3, k4, im;
	int i;
	T_FVECTOR<T> *fvp1, *fvp2;
	T_FMATRIX<T> *fmp1, *fmp2;
//	T_IVECTOR<T> *ivp1;
//	T_IMATRIX<T> *imp1, *imp2;


	if(strcmp(sb, "=")  == 0) attri = D_NOTHING;
	if(strcmp(sb, "+=") == 0) attri = D_PLUS;
	if(strcmp(sb, "-=") == 0) attri = D_MINUS;
	if(strcmp(sb, "*=") == 0) attri = D_MULTIPLICATION;
	if(strcmp(sb, "/=") == 0) attri = D_DIVISION;

	if(strcmp(se, "kfv*kfv") == 0) {
		k1  = va_arg(list, double);		fvp1 = &va_arg(list, T_FVECTOR<T>);
		k2  = va_arg(list, double);		fvp2 = &va_arg(list, T_FVECTOR<T>);
		for(i=0; i<_size; i++) {
			im = k1*(*fvp1)[i] * k2*(*fvp2)[i];
			FVECTOR_OP(i);
		}
	}

	if(strcmp(se, "kfv+kfv") == 0) {
		k1  = va_arg(list, double);		fvp1 = &va_arg(list, T_FVECTOR<T>);
		k2  = va_arg(list, double);		fvp2 = &va_arg(list, T_FVECTOR<T>);
		for(i=0; i<_size; i++) {
			im = k1*(*fvp1)[i] + k2*(*fvp2)[i];
			FVECTOR_OP(i);
		}
	}
	if(strcmp(se, "kfmfv") == 0) {
		k1  = va_arg(list, double);		fmp1 = &va_arg(list, T_FMATRIX<T>);		fvp1 = &va_arg(list, T_FVECTOR<T>);
		for(i=0; i<_size; i++) {
			im = k1*((*fmp1)[i], (*fvp1));
			FVECTOR_OP(i);
		}
	}
	
	va_end(list);
	return (*this);
	
}


template<class T>	inline T_FVECTOR<T>&	T_FVECTOR<T>::op(char* sb, double k1,	T_FVECTOR<T>& fv1, double k2, T_FVECTOR<T>& fv2) {
	return op(sb, "kfv+kfv", k1, fv1, k2, fv2);
}
template<class T>	inline T_FVECTOR<T>&	T_FVECTOR<T>::op(char* sb, double k1,	T_FMATRIX<T>& fm, T_FVECTOR<T>& fv) {
	return op(sb, "kfmfv", k1., fm, fv);
}
template<class T>	inline T_FVECTOR<T>&	T_FVECTOR<T>::op(char* sb,				T_FMATRIX<T>& fm, T_FVECTOR<T>& fv) {
	return op(sb, "kfmfv", 1., fm, fv);
}

template<class T>	T_FVECTOR<T>&	T_FVECTOR<T>::print() {
	printf("\n<FVector_> \n");
	for(int i=0; i<_size; i++) 	cout << i << ": " << _vec[i] << endl;
	return (*this);
}

template<class T>	T_FVECTOR<T>&			T_FVECTOR<T>::normalize(){
	return (*this)/=norm2();
}
template<class T>	T						T_FVECTOR<T>::norm2(){
	return sqrt(norm2_2());
}
template<class T>	T						T_FVECTOR<T>::norm2_2(){
	return ((*this),(*this));
}
template<class T>	T_FVECTOR<T>&			T_FVECTOR<T>::setAll(T first, ...) {
	va_list list;
	va_start(list, first);	_vec[0]= first;

	for(int i=1; i<_size; i++) {
		if(i>=_size) break;
		_vec[i]= va_arg(list, T);
	}
	va_end(list);
	return (*this);
}


//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
//============================================================================
//                                 T_FMATRIX
//============================================================================
//▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
template <class T>							T_FMATRIX<T>::T_FMATRIX(int n, int m){
	make(n,m);
}
template <class T>							T_FMATRIX<T>::T_FMATRIX(){
	_row=0;	_col=0;
	_mat = NULL;
}
template <class T>							T_FMATRIX<T>::~T_FMATRIX(){
	if (_mat!=NULL)
	{
		for (int i=0; i<_row; i++)	_mat[i].release();
		_mat=NULL;
	}
}
template <class T>	T_FVECTOR<T>&			T_FMATRIX<T>::operator()(int n){
	return _mat[n];
}
template <class T>	T_FVECTOR<T>&			T_FMATRIX<T>::operator[](int n){
	return _mat[n];
}
template <class T>	T&						T_FMATRIX<T>::operator()(int n, int m){
	return _mat[n][m];
}
template <class T>	T_FMATRIX<T>&			T_FMATRIX<T>::operator=(T_FVECTOR<T>& A){
	make(A._row,A._col);
	return (*this);
}
template <class T> T_FMATRIX<T>&			T_FMATRIX<T>::make(int n, int m){
	release();
	_row=n;	_col=m;
	_mat = new T_FVECTOR<T>[_row];
	for (int i=0; i<_row; i++)	_mat[i].make(_col);
	return (*this);
}
template <class T> T_FMATRIX<T>&			T_FMATRIX<T>::setAll(T first, ...){
	va_list list;
	va_start(list, first);	_mat[0][1]= first;
	int i, row;
	for(i=1; i<_row*_col; i++) {
		row = i/_col;
		_mat[i/_col][i%_col] = va_arg(list, T);
	}
	va_end(list);
	return (*this);
}
template <class T> void						T_FMATRIX<T>::clear(){
	for (int i=0; i<_row; i++)	_mat[i].clear();
}
template <class T>	void					T_FMATRIX<T>::release(){
	if (_mat!=NULL)
	{
		for (int i=0; i<_row; i++)	_mat[i].release();
		_mat=NULL;
	}
}
template <class T>	T_FMATRIX<T>&			T_FMATRIX<T>::print(){
	printf("\n<FMatrix_> \n");
	int i, j;
	for (i=0; i<_row; i++){
		for (j=0; j<_col; j++){
			cout << " " << _mat[i][j];
		}
		cout << endl;
	}
	return (*this);
}

