#include "stdafx.h"
#include "Matrix.h"

using namespace Tetris;

CMatrix::CMatrix( void )
{
	_pdata=NULL;
	_row=0;
	_column=0;
}

CMatrix::CMatrix( CMatrix& objMatrix )
{
	_pdata=NULL;
	_row=0;
	_column=0;
	*this=objMatrix;
}

CMatrix& CMatrix::operator=( CMatrix& objMatrix )
{
	if (this!=&objMatrix)
	{
		BYTE* p=new BYTE[objMatrix._row*objMatrix._column];
		memcpy(p,objMatrix._pdata,objMatrix._row*objMatrix._column);

		if (_pdata!=NULL)
		{
			delete []_pdata;
			_pdata=NULL;
		}

		_row=objMatrix._row;
		_column=objMatrix._column;
		_pdata=p;
	}

	return *this;
}

CMatrix::~CMatrix( void )
{
	if (_pdata!=NULL)
	{
		delete []_pdata;
		_pdata=NULL;
	}
}

void CMatrix::SetData(IN BYTE *data)
{
	memcpy(_pdata,data,_row*_column);
}

void CMatrix::Init( int row,int column )
{
	if (_pdata!=NULL)
	{
		delete []_pdata;
		_pdata=NULL;
	}

	_row=row;
	_column=column;
	_pdata=new BYTE[_row*_column];
	memset(_pdata,0,_row*_column);
}

void CMatrix::RotateRight()
{
	BYTE *_p_new_data=new BYTE[_row*_column];
	Tetris::RotateRight(_row,_column,_pdata,_p_new_data);
	delete []_pdata;
	_pdata=_p_new_data;

	int _new_row=_column;
	int _new_column=_row;

	_row=_new_row;
	_column=_new_column;
}

void CMatrix::RotateLeft()
{
	BYTE *_p_new_data=new BYTE[_row*_column];
	Tetris::RotateLeft(_row,_column,_pdata,_p_new_data);
	delete []_pdata;
	_pdata=_p_new_data;

	int _new_row=_column;
	int _new_column=_row;

	_row=_new_row;
	_column=_new_column;
}

void CMatrix::DebugTrace()
{
	TRACE("_row=%d,_column=%d\n",_row,_column);
	for (int i=0;i<_row;i++)
	{
		for (int j=0;j<_column;j++)
		{
			TRACE("%d ",GetData(i,j));
		}
		TRACE("\n");
	}
}

void CMatrix::SetData(IN int row, IN int column, IN BYTE data)
{		
	ASSERT(row>=0 && row<_row);
	ASSERT(column>=0 && column<_column);
	_pdata[row*_column+column] = data;
}

BYTE CMatrix::GetData(IN int row, IN int column)
{		
	ASSERT(row>=0 && row<_row);
	ASSERT(column>=0 && column<_column);
	return _pdata[row*_column+column];
}

int CMatrix::GetRowCount()
{
	return _row;
}

int CMatrix::GetColCount()
{
	return _column;
}