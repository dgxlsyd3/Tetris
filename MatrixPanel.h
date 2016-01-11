#pragma once
#include "Matrix.h"
#include "MatrixBlock.h"
#include "MatrixPanel.h"

using namespace Tetris;

class CMatrixPanel : public CStatic
{
	DECLARE_DYNAMIC(CMatrixPanel)

protected:
	DECLARE_MESSAGE_MAP()
protected:
	CMatrix *m_pMatrix;

	COLORREF clrBack;
	//COLORREF clrBlock;

	COLORREF clrBlock3Dtop;
	COLORREF clrBlock3Dbottom;

	COLORREF clrBack3Dtop;
	COLORREF clrBack3Dbottom;

	int m_nFlashRow;
public:
	CMatrixPanel();
	virtual ~CMatrixPanel();
	void RedrawMatrix(CMatrix  *pMatrix,int nFlashRow=-1);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};



