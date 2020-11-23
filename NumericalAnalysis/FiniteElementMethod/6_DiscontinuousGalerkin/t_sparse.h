#ifndef __T_SPARSE_H__
#define __T_SPARSE_H__



#include "class17_.h"
//�ƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢ�
//============================================================================
//                                 IVECTOR_double
//============================================================================
//�ƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢ�
class IVector_double
{
public :
	int *_index;			//index set :full vector���� nonzero���� ��ġ�� �����Ѵ�.
	double *_data;			//full vector���� nonzero�� ���� �����Ѵ�.
	int _memory_size;		//full vector���� �ִ�� ���� nonzero���� ����
	int _occupied_size;		//���� full vector�� ����� nonzero���� ����

public :
								IVector_double();
	int							find_index(int k);			//k�� _index�� ������ �� ��ġ�� ��ȯ, ������ -1��ȯ
	IVector_double&				make(int memorysize);
	IVector_double&				clear();					//full vector�� �����ͷ� �����.
	void						print();
	void						release();					//�Ҵ�� memory ����

public :
	double&						operator[](int idx);
	double						operator()(int idx);
	void						set_data(int idx, double data);
	double						operator,  (FVector_double& v);
};



//�ƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢ�
//============================================================================
//                                 IVECTOR_double
//============================================================================
//�ƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢ�

class IMatrix_double
{
public :
	int _row;				//full matrix�� row ���� i.e column vector�� ����
	int _col;				//full matrix�� col ���� i.e full row vector�� ����
	int _col_max_index;		//�� row=IMatrix_double�� _memory_size
	IVector_double *_mat;	//�� row = IMatrix 

public :
								IMatrix_double();
	IMatrix_double&				make(int row, int col, int col_max_index);
	void						print();

public :
	IVector_double&				operator[](int idx);
	double						operator()(int row, int col);
};


//�ƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢ�
//============================================================================
//                                 IVECTOR_double : �����Լ� ����
//============================================================================
//�ƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢ�
								IVector_double::IVector_double()
{
	_memory_size = 0;
	_occupied_size = 0;
	_index = NULL;
	_data = NULL;
}


int								IVector_double::find_index(int k)
{
	if (_index == NULL)
	{
		cout << "find_index : _index is NULL" << endl;
		exit(-1);
	}


	for (int i = 0; i < _occupied_size; i++)
		if (k == _index[i])
			return i;

	return -1;		//k�� _index�� ����
}


IVector_double&					IVector_double::make(int memorysize)
{
	//�޸𸮰� ���°��
	if (_index == NULL)
	{

		_memory_size = memorysize;
		_occupied_size = 0;
		_index = new int[memorysize];
		_data = new double[memorysize];
	}
	//�޸𸮰� �ִ� ��� =>�����޸� ����
	else
	{
		int *prev_index = _index;
		double *prev_data = _data;
		
		_memory_size = memorysize;
		_occupied_size = 0;
		_index = new int[memorysize];
		_data = new double[memorysize];

		delete prev_index;
		delete prev_data;
	}
	return (*this);
}

IVector_double&					IVector_double::clear()
{
	for (int i = 0; i < _occupied_size; i++)
	{
		_index[i] = 0;
		_data[i] = 0;
	}
	_occupied_size = 0;
	return (*this);
}

void							IVector_double::print()
{
	cout << "IMatrix : " << endl;
	if (_index == NULL)
	{
		cout << "print() : _index is NULL" << endl;
		return;
	}
	for (int i = 0; i < _occupied_size; i++)
		cout << "Position " << _index[i] << " : " << _data[i] << endl;
}

void							IVector_double::release()
{
	if (_index != NULL) 
	{
		delete _index;
		delete _data;
	}
}

double&							IVector_double::operator[](int idx)
{
	int pos = find_index(idx);
	if (pos == -1)		//_index�� idx�� ����
	{
		pos = _occupied_size;
		if (_occupied_size == _memory_size)
		{
			cout << "operator[] : memory is full" << endl;
			exit(-1);
		}

		_occupied_size++;
		_index[pos] = idx;
		_data[pos] = 0;			//�ӽ�
	}
	
	return _data[pos];
}

double							IVector_double::operator()(int idx)
{
	int pos = find_index(idx);
	if (pos == -1)
		return 0;
	
	return _data[pos];
}


double							IVector_double::operator,  (FVector_double& v)
{
	
	double sum = 0;
	int pos;

	for (int i = 0; i < _occupied_size; i++)
	{
		pos = _index[i];
		if(_data[i]!=0)
			sum += _data[i] * v[pos];
	}
	return sum;
}


void							IVector_double::set_data(int idx, double data)
{
	if (data == 0)
		return;
	int pos = find_index(idx);
	if (pos == -1)
	{
		pos = _occupied_size;
		if (_occupied_size == _memory_size)
		{
			cout << "set_data : memory is full" << endl;
			exit(-1);
		}

		_occupied_size++;
		_index[pos] = idx;
		_data[pos] = data;
	}
	else
	{
		_data[pos] = data;
	}
}

//�ƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢ�
//============================================================================
//                                 IMatrix_double : �����Լ� ����
//============================================================================
//�ƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢƢ�
									IMatrix_double::IMatrix_double()
{
	_col = 0;
	_row = 0;
	_col_max_index = 0;
	_mat = NULL;
}

IMatrix_double&						IMatrix_double::make(int row, int col, int col_max_index)
{	
	if (col < col_max_index)
	{
		cout << "IMatrix_double::make : col < col_max_index" << endl;
		exit(-1);
	}

	//�޸𸮰� �̹� �ִ� ��� =>�޸� ���� �� ���Ҵ�
	if (_mat != NULL)
	{
		IVector_double* pre_mat = _mat;

		for (int i = 0; i < _row; i++)
			pre_mat[i].release();

	}
	_col = col;
	_row = row;
	_col_max_index = col_max_index;
	_mat = new IVector_double[_row];

	for (int i = 0; i < _row; i++)
		_mat[i].make(_col_max_index);
	
	return (*this);
}

void								IMatrix_double::print()
{
	for (int i = 0; i < _row; i++)
	{
		cout << "----------[ " << i << "th row ]----------" << endl;
		_mat[i].print();
	}
}

IVector_double&						IMatrix_double::operator[](int idx)
{
	if (idx < 0 || idx >= _row)
	{
		cout << "IMatrix_double::operator[] : wrong index!" << endl;
		exit(-1);
	}
	return _mat[idx];
}

double								IMatrix_double::operator()(int row, int col)
{
	if (row < 0 || row >= _row)
	{
		cout << "IMatrix_double::operator() : wrong row index!" << endl;
		exit(-1);
	}
	else if (col < 0 || col >= _col)
	{
		cout << "IMatrix_double::operator() : wrong column index!" << endl;
		exit(-1);
	}

	return _mat[row](col);
}
#endif