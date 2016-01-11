
// TestTetrisDlg.h : 头文件
//

#pragma once
#include "afxwin.h"

#include "Tetris.h"
#include "MatrixPanel.h"

#include "HelpDlg.h"

using namespace Tetris;

// CTestTetrisDlg 对话框
class CTestTetrisDlg : public CDialog,CTetris
{
public:
	virtual void OnDrawMatrixNext(CMatrix* pMatrix);
	virtual void OnDrawMatrixBoard(CMatrix* pMatrix,int nFullRow=-1);
	virtual void OnGameOver();
	virtual void OnUpdateScore(int nScore);
	virtual void OnUpdateBlockCount(int nBlockCount);
// 构造
public:
	CTestTetrisDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TESTTETRIS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CMatrixPanel m_StaticMatrixBlock;
	CMatrixPanel m_StaticMatrixBoard;
	CComboBox m_ComboSpeed;

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnMenuNew();
	afx_msg void OnMenuPause();
	afx_msg void OnMenuRun();
	afx_msg void OnMenuExit();
	afx_msg void OnMenuHelp();
	afx_msg void OnMenuAbout();
	afx_msg void OnCbnSelchangeComboSpeed();
protected:
	virtual void OnOK();
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual void OnCancel();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void OnGetMinMaxInfo(MINMAXINFO * lpMMI);
};
