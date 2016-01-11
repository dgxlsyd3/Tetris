#include "StdAfx.h"
#include "MatrixBlock.h"

using namespace Tetris;

CMatrixBlock::CMatrixBlock(void)
{
	Init(4,4);

	srand(GetTickCount());
	int block = rand() % 7;
	memcpy(_pdata, s_MatrixBlockData[block], 4*4);

	srand(GetTickCount());
	int rotate = rand() % 4;
	for (int i = 0;i < rotate;i++)
	{
		RotateRight();
	}

	int color= GetTickCount() % 7;
	for (int i=0;i<GetRowCount();i++)
	{
		for (int j=0;j<GetColCount();j++)
		{
			if (GetData(i,j)>0)
			{
				//color的值可能为0，所以要+1
				SetData(i,j,color+1);
			}
		}
	}

	row=0;
	col=0;
}

CMatrixBlock::~CMatrixBlock(void)
{
}

COLORREF CMatrixBlock::s_Color[7]=
{
	RGB(255,0,128),
	RGB(128,0,255),
	RGB(0,128,255),
	RGB(0,255,64),
	RGB(128,128,0),
	RGB(255,64,0),
	RGB(255,0,255),
};

BYTE CMatrixBlock::s_MatrixBlockData[7][16] =
{
	{   
		0, 0, 0, 0,
		1, 1, 1, 1,
		0, 0, 0, 0,
		0, 0, 0, 0,
	},

	{
		0, 0, 0, 0,
		0, 1, 0, 0,
		1, 1, 1, 0,
		0, 0, 0, 0,
	},

	{
		0, 0, 0, 0,
		1, 1, 0, 0,
		0, 1, 1, 0,
		0, 0, 0, 0,
	},

	{
		0, 0, 0, 0,
		0, 1, 1, 0,
		1, 1, 0, 0,
		0, 0, 0, 0,
	},

	{
		0, 0, 0, 0,
		0, 1, 1, 0,
		0, 1, 1, 0,
		0, 0, 0, 0,
	},

	{
		0, 0, 0, 0,
		0, 1, 1, 1,
		0, 1, 0, 0,
		0, 0, 0, 0,
	},

	{
		0, 0, 0, 0,
		1, 1, 1, 0,
		0, 0, 1, 0,
		0, 0, 0, 0,
	}
};

