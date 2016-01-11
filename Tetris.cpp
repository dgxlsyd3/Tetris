#include "StdAfx.h"
#include "Tetris.h"

using namespace Tetris;

CTetris* CTetris::s_Tetris=NULL;
VOID CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	CTetris::s_Tetris->OnTimerProc(idEvent);
}

CTetris::CTetris(void)
{
	s_Tetris=this;
	_nTimer=0;
	_nSpeed=500;

	_nScore=0;
	_nBlockCount=0;
}

CTetris::~CTetris(void)
{
	KillTimer(NULL, _nTimer);
}

void CTetris::SetSpeed( UINT nSpeed )
{
	_nSpeed=nSpeed;

	KillTimer(NULL, _nTimer);
	_nTimer=SetTimer(NULL,NULL,_nSpeed,TimerProc);
}

void CTetris::NewGame()
{
	_MatrixBoard.Clear();
	_TempMatrixBoard.Clear();
	GetMatrixBlock();
	_nScore=0;
	_nBlockCount=0;

	OnUpdateBlockCount(_nBlockCount);
	OnUpdateScore(_nScore);

	OnDrawMatrixNext(&_MatrixBlockNext);
	OnDrawMatrixBoard(&_TempMatrixBoard);

	KillTimer(NULL, _nTimer);
	_nTimer=SetTimer(NULL,NULL,_nSpeed,TimerProc);
}

void CTetris::GetMatrixBlock()
{
	_MatrixBlock=_MatrixBlockNext;
	_MatrixBlock.col=3;
	_MatrixBlock.row=-4;

	CMatrixBlock newMatrixBlock;
	_MatrixBlockNext=newMatrixBlock;
	OnDrawMatrixNext(&_MatrixBlockNext);

	_nBlockCount++;
	OnUpdateBlockCount(_nBlockCount);
}

void CTetris::OnTimerProc(UINT_PTR idEvent)
{
	MoveBlock(DOWN);
}

void CTetris::Pause()
{
	KillTimer(NULL, _nTimer);
}

void CTetris::Run()
{
	_nTimer=SetTimer(NULL,NULL,_nSpeed,TimerProc);
}

void CTetris::MoveBlockFastDown(BOOL bFast)
{
	KillTimer(NULL, _nTimer);
	if (bFast)
	{
		_nTimer=SetTimer(NULL,NULL,1,TimerProc);
	}
	else
	{
		_nTimer=SetTimer(NULL,NULL,_nSpeed,TimerProc);
	}
}

BOOL CTetris::CanMove()
{
	for (int i=_MatrixBlock.GetRowCount()-1;i>=0;i--)
	{
		for (int j=0;j<_MatrixBlock.GetColCount();j++)
		{
			BYTE dataBlock=_MatrixBlock.GetData(i,j);
			if (dataBlock>0)
			{
				if (_MatrixBlock.row+i==_TempMatrixBoard.GetRowCount())
				{
					return FALSE;
				}

				if (_MatrixBlock.col+j<0 || 
					_MatrixBlock.col+j>=_TempMatrixBoard.GetColCount())
				{
					return FALSE;
				}

				if( _MatrixBlock.row+i>=0 &&
					_MatrixBlock.row+i<_TempMatrixBoard.GetRowCount())
				{
					BYTE dataBoard=_MatrixBoard.GetData(_MatrixBlock.row+i,_MatrixBlock.col+j);
					if (dataBoard>0)
					{
						return FALSE;
					}
				}
			}
		}
	}

	return TRUE;
}

int CTetris::FindFullRow()
{
	int iRow=_TempMatrixBoard.GetRowCount()-1;
	for (;iRow>=0;iRow--)
	{
		BOOL isFullRow=TRUE;
		for (int j=0;j<_TempMatrixBoard.GetColCount();j++)
		{
			if (_TempMatrixBoard.GetData(iRow,j)<=0)
			{
				isFullRow=FALSE;
				break;
			}
		}

		if (isFullRow)
		{
			return iRow;
		}
	}

	return -1;
}

void CTetris::DeleteFullRow(int nFullRow)
{
	if (nFullRow!=-1)
	{
		for (int i=nFullRow;i>0;i--)
		{
			for (int j=0;j<_TempMatrixBoard.GetColCount();j++)
			{
				BYTE data=_TempMatrixBoard.GetData(i-1,j);
				_TempMatrixBoard.SetData(i,j,data);
			}
		}
	}
}

void CTetris::OnPutDown()
{
	int nDeleteRow=0;
	for(int i=0;i<4;i++)
	{
		int nFullRow=FindFullRow();
		if (nFullRow!=-1)
		{
			OnDrawMatrixBoard(&_TempMatrixBoard,nFullRow);
			Sleep(30);
			OnDrawMatrixBoard(&_TempMatrixBoard);
			Sleep(30);
			OnDrawMatrixBoard(&_TempMatrixBoard,nFullRow);
			Sleep(30);
			OnDrawMatrixBoard(&_TempMatrixBoard);
			Sleep(30);
			OnDrawMatrixBoard(&_TempMatrixBoard,nFullRow);

			DeleteFullRow(nFullRow);
			nDeleteRow++;
		}
	}

	switch(nDeleteRow)
	{
	case 1:
		_nScore+=10;
		break;
	case 2:
		_nScore+=40;
		break;
	case 3:
		_nScore+=80;
		break;
	case 4:
		_nScore+=160;
		break;
	default:
		break;
	}

	OnUpdateScore(_nScore);

	if (IsGameOver())
	{
		KillTimer(NULL,_nTimer);
		OnGameOver();
	}

	_MatrixBoard=_TempMatrixBoard;
	GetMatrixBlock();
}

BOOL CTetris::IsGameOver()
{
	for (int i=_MatrixBlock.GetRowCount()-1;i>=0;i--)
	{
		for (int j=0;j<_MatrixBlock.GetColCount();j++)
		{
			if( _MatrixBlock.col+j>=0 &&
				_MatrixBlock.col+j<_TempMatrixBoard.GetColCount())
			{
				BYTE dataBlock=_MatrixBlock.GetData(i,j);
				BYTE dataBoard=_TempMatrixBoard.GetData(0,_MatrixBlock.col+j);

				if(dataBlock>0)
				{
					if (dataBoard>0)
					{
						return TRUE;
					}
				}
			}
		}
	}

	return FALSE;
}

void CTetris::MoveBlock(Direction dir)
{
	switch (dir)
	{
	case LEFT:
		{
			_MatrixBlock.col-=1;
			if (!CanMove())
			{
				_MatrixBlock.col+=1;
			}
			break;
		}
	case RIGHT:
		{
			_MatrixBlock.col+=1;
			if (!CanMove())
			{
				_MatrixBlock.col-=1;
			}
			break;
		}
	case DOWN:
		{
			_MatrixBlock.row+=1;
			break;
		}
	case ROTATE:
		{
			_MatrixBlock.RotateRight();
			if (!CanMove())
			{
				_MatrixBlock.RotateLeft();
			}
			break;
		}
	default:
		break;
	}

	if (!CanMove())
	{
		OnPutDown();
	}

	_TempMatrixBoard=_MatrixBoard;
	for (int i=_MatrixBlock.GetRowCount()-1;i>=0;i--)
	{
		for (int j=0;j<_MatrixBlock.GetColCount();j++)
		{
			if( _MatrixBlock.row+i>=0 &&
				_MatrixBlock.row+i<_TempMatrixBoard.GetRowCount() &&
				_MatrixBlock.col+j>=0 &&
				_MatrixBlock.col+j<_TempMatrixBoard.GetColCount())
			{
				BYTE dataBlock=_MatrixBlock.GetData(i,j);
				BYTE dataBoard=_TempMatrixBoard.GetData(_MatrixBlock.row+i,_MatrixBlock.col+j);

				if(dataBlock>0)
				{
					if (dataBoard<=0)
					{
						_TempMatrixBoard.SetData(_MatrixBlock.row+i,_MatrixBlock.col+j,dataBlock);
					}
				}
			}
		}
	}

	OnDrawMatrixBoard(&_TempMatrixBoard);
}
