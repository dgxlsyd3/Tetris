#include "StdAfx.h"
#include "Matrix.h"
#include "MatrixBoard.h"

using namespace Tetris;

CMatrixBoard::CMatrixBoard(void)
{
	Init(20,10);
}

CMatrixBoard::~CMatrixBoard(void)
{
}

void CMatrixBoard::Clear()
{
	memset(_pdata,0,_row*_column);
}