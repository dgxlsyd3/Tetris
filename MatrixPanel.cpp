#include "stdafx.h"
#include "MatrixPanel.h"

using namespace Tetris;

IMPLEMENT_DYNAMIC(CMatrixPanel, CStatic)

CMatrixPanel::CMatrixPanel()
{
	m_pMatrix=NULL;
	m_nFlashRow=-1;

	clrBack=RGB(220,220,220);

	clrBlock3Dtop=RGB(250,250,250);
	clrBlock3Dbottom=RGB(100,100,100);

	clrBack3Dtop=RGB(230,230,230);
	clrBack3Dbottom=RGB(210,210,210);
}

CMatrixPanel::~CMatrixPanel()
{

}

BEGIN_MESSAGE_MAP(CMatrixPanel, CStatic)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

void CMatrixPanel::RedrawMatrix( CMatrix *pMatrix,int nFlashRow/*=-1*/)
{
	m_nFlashRow=nFlashRow;
	m_pMatrix=pMatrix;
	RedrawWindow();
}

void CMatrixPanel::OnPaint()
{
	CPaintDC dc(this);

	if (m_pMatrix==NULL)
		return;

	CRect rcWnd;
	GetClientRect(rcWnd);
	int nBlockWidth=rcWnd.Width()/m_pMatrix->GetColCount();
	int nBlockHeight=rcWnd.Height()/m_pMatrix->GetRowCount();

	CRect rcMatrix(
		rcWnd.left,
		rcWnd.top,
		rcWnd.left+nBlockWidth*m_pMatrix->GetColCount(),
		rcWnd.top+nBlockHeight*m_pMatrix->GetRowCount());

	CDC dcMemory;
	dcMemory.CreateCompatibleDC(&dc);
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(&dc,rcWnd.Width(),rcWnd.Height());
	dcMemory.SelectObject(&bmp);
	dcMemory.FillRect(rcWnd,&CBrush(GetSysColor(COLOR_3DFACE)));

	for (int row=0;row<m_pMatrix->GetRowCount();row++)
	{
		for (int col=0;col<m_pMatrix->GetColCount();col++)
		{
			dcMemory.FillRect(
				CRect(
				col*nBlockWidth+1,
				row*nBlockHeight+1,
				col*nBlockWidth+nBlockWidth-1,
				row*nBlockHeight+nBlockHeight-1),
				&CBrush(clrBack));

			dcMemory.Draw3dRect(
				col*nBlockWidth,
				row*nBlockHeight,
				nBlockWidth,
				nBlockHeight,
				clrBack3Dtop,
				clrBack3Dbottom);
			
			if (m_pMatrix->GetData(row,col)>0)
			{
				if(m_nFlashRow==row)
				{
					dcMemory.FillRect(
						CRect(
						col*nBlockWidth,
						row*nBlockHeight,
						col*nBlockWidth+nBlockWidth,
						row*nBlockHeight+nBlockHeight),
						&CBrush(RGB(255,255,255)));
				}
				else
				{
					dcMemory.FillRect(
						CRect(
						col*nBlockWidth,
						row*nBlockHeight,
						col*nBlockWidth+nBlockWidth,
						row*nBlockHeight+nBlockHeight),
						&CBrush(CMatrixBlock::s_Color[m_pMatrix->GetData(row,col)-1]));
				}

				dcMemory.Draw3dRect(
					col*nBlockWidth,
					row*nBlockHeight,
					nBlockWidth,
					nBlockHeight,
					clrBlock3Dtop,
					clrBlock3Dbottom);
			}	


		}
	}

	dc.BitBlt(0,0,rcWnd.Width(),rcWnd.Height(),&dcMemory,0,0,SRCCOPY);

	dcMemory.DeleteDC();
	bmp.DeleteObject();
}

BOOL CMatrixPanel::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}
