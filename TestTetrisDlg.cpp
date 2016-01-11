
// TestTetrisDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TestTetris.h"
#include "TestTetrisDlg.h"

#include "Matrix.h"
#include "MatrixBlock.h"
#include "MatrixBoard.h"
using namespace Tetris;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


CTestTetrisDlg::CTestTetrisDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestTetrisDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestTetrisDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_MATRIX_BLOCK, m_StaticMatrixBlock);
	DDX_Control(pDX, IDC_STATIC_MATRIX_BOARD, m_StaticMatrixBoard);
	DDX_Control(pDX, IDC_COMBO_SPEED, m_ComboSpeed);
}

BEGIN_MESSAGE_MAP(CTestTetrisDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_MENU_NEW, &CTestTetrisDlg::OnMenuNew)
	ON_COMMAND(ID_MENU_PAUSE, &CTestTetrisDlg::OnMenuPause)
	ON_COMMAND(ID_MENU_RUN, &CTestTetrisDlg::OnMenuRun)
	ON_COMMAND(ID_MENU_EXIT, &CTestTetrisDlg::OnMenuExit)
	ON_COMMAND(ID_MENU_HELP, &CTestTetrisDlg::OnMenuHelp)
	ON_COMMAND(ID_MENU_ABOUT, &CTestTetrisDlg::OnMenuAbout)
	ON_CBN_SELCHANGE(IDC_COMBO_SPEED, &CTestTetrisDlg::OnCbnSelchangeComboSpeed)
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_GETMINMAXINFO()
END_MESSAGE_MAP()


// CTestTetrisDlg 消息处理程序


BOOL CTestTetrisDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	m_ComboSpeed.ResetContent();
	m_ComboSpeed.AddString("1");
	m_ComboSpeed.AddString("10");
	m_ComboSpeed.AddString("50");
	m_ComboSpeed.AddString("100");
	m_ComboSpeed.AddString("200");
	m_ComboSpeed.AddString("300");
	m_ComboSpeed.AddString("400");
	m_ComboSpeed.AddString("500");
	m_ComboSpeed.AddString("800");
	m_ComboSpeed.SelectString(-1, "400");
	OnCbnSelchangeComboSpeed();

	NewGame();

	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	SetTimer(987,200,NULL);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTestTetrisDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTestTetrisDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTestTetrisDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CTestTetrisDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case 37://左
			MoveBlock(CTetris::LEFT);
			break;
		case 38://上
			MoveBlock(CTetris::ROTATE);
			break;
		case 39://右
			MoveBlock(CTetris::RIGHT);
			break;
		case 40://下
			MoveBlockFastDown(TRUE);
			break;
		case VK_ESCAPE:
			return TRUE;
		default:
			break;
		}
	}
	else if (pMsg->message == WM_KEYUP)
	{
		if (pMsg->wParam==40)
		{
			MoveBlockFastDown(FALSE);
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CTestTetrisDlg::OnMenuNew()
{
	NewGame();
}

void CTestTetrisDlg::OnMenuPause()
{
	Pause();
}

void CTestTetrisDlg::OnMenuRun()
{
	Run();
}

void CTestTetrisDlg::OnMenuExit()
{
	DestroyWindow();
}

void CTestTetrisDlg::OnMenuHelp()
{
	CHelpDlg HelpDlg;
	HelpDlg.DoModal();
}

void CTestTetrisDlg::OnMenuAbout()
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}

void CTestTetrisDlg::OnCbnSelchangeComboSpeed()
{
	CString csSpeed;
	m_ComboSpeed.GetLBText(m_ComboSpeed.GetCurSel(), csSpeed);
	SetSpeed(atoi(csSpeed));
	GetDlgItem(IDC_EDIT_FOCUS)->SetFocus();
}

void CTestTetrisDlg::OnDrawMatrixNext( CMatrix* pMatrix )
{
	m_StaticMatrixBlock.RedrawMatrix(pMatrix);
}

void CTestTetrisDlg::OnDrawMatrixBoard( CMatrix* pMatrix,int nFullRow/*=-1*/ )
{
	m_StaticMatrixBoard.RedrawMatrix(pMatrix,nFullRow);
}

void CTestTetrisDlg::OnGameOver()
{
	AfxMessageBox("Game Over!");
	NewGame();
}

void CTestTetrisDlg::OnUpdateScore( int nScore )
{
	SetDlgItemInt(IDC_EDIT_SCORE,nScore);
}

void CTestTetrisDlg::OnUpdateBlockCount( int nBlockCount )
{
	SetDlgItemInt(IDC_EDIT_BLOCKCOUNT,nBlockCount);
}

void CTestTetrisDlg::OnOK()
{

}

void CTestTetrisDlg::OnCancel()
{
	__super::OnCancel();
}

void CTestTetrisDlg::OnSize(UINT nType, int cx, int cy)
{
	__super::OnSize(nType, cx, cy);
	
	if (m_StaticMatrixBlock.GetSafeHwnd() == NULL)
		return;

	
	CRect rcBlock;
	m_StaticMatrixBlock.GetWindowRect(&rcBlock);
	ScreenToClient(&rcBlock);
	int LEFT = cx - rcBlock.Width() - 10;
	m_StaticMatrixBlock.MoveWindow(
		LEFT,
		10,
		rcBlock.Width(),
		rcBlock.Height());
	m_StaticMatrixBlock.Invalidate(TRUE);

	//--
	CRect rcVelocity;
	GetDlgItem(IDC_STATIC_VELOCITY)->GetWindowRect(&rcVelocity);
	ScreenToClient(&rcVelocity);
	GetDlgItem(IDC_STATIC_VELOCITY)->MoveWindow(
		LEFT,
		rcBlock.bottom + 10,
		rcVelocity.Width(),
		rcVelocity.Height());
	GetDlgItem(IDC_STATIC_VELOCITY)->Invalidate(TRUE);

	CRect rcSpeed;
	GetDlgItem(IDC_COMBO_SPEED)->GetWindowRect(&rcSpeed);
	ScreenToClient(&rcSpeed);
	GetDlgItem(IDC_COMBO_SPEED)->MoveWindow(
		rcVelocity.right + 4,
		rcVelocity.top - 4,
		rcSpeed.Width(),
		rcSpeed.Height());
	GetDlgItem(IDC_COMBO_SPEED)->Invalidate(TRUE);

	//---
	CRect rcCount;
	GetDlgItem(IDC_STATIC_COUNT)->GetWindowRect(&rcCount);
	ScreenToClient(&rcCount);
	GetDlgItem(IDC_STATIC_COUNT)->MoveWindow(
		LEFT,
		rcSpeed.bottom + 10,
		rcCount.Width(),
		rcCount.Height());
	GetDlgItem(IDC_STATIC_COUNT)->Invalidate(TRUE);

	CRect rcBlockCount;
	GetDlgItem(IDC_EDIT_BLOCKCOUNT)->GetWindowRect(&rcBlockCount);
	ScreenToClient(&rcBlockCount);
	GetDlgItem(IDC_EDIT_BLOCKCOUNT)->MoveWindow(
		rcCount.right + 4,
		rcCount.top - 4,
		rcBlockCount.Width(),
		rcBlockCount.Height());
	GetDlgItem(IDC_EDIT_BLOCKCOUNT)->Invalidate(TRUE);

	//--
	CRect rcScore;
	GetDlgItem(IDC_STATIC_SCORE)->GetWindowRect(&rcScore);
	ScreenToClient(&rcScore);
	GetDlgItem(IDC_STATIC_SCORE)->MoveWindow(
		LEFT,
		rcCount.bottom + 10,
		rcScore.Width(),
		rcScore.Height());
	GetDlgItem(IDC_STATIC_SCORE)->Invalidate(TRUE);

	CRect rcEditScore;
	GetDlgItem(IDC_EDIT_SCORE)->GetWindowRect(&rcEditScore);
	ScreenToClient(&rcEditScore);
	GetDlgItem(IDC_EDIT_SCORE)->MoveWindow(
		rcScore.right + 4,
		rcScore.top - 2,
		rcEditScore.Width(),
		rcEditScore.Height());
	GetDlgItem(IDC_EDIT_SCORE)->Invalidate(TRUE);
	
	// ---
	CRect rcBoard;
	m_StaticMatrixBoard.GetWindowRect(&rcBoard);
	ScreenToClient(&rcBoard);
	m_StaticMatrixBoard.MoveWindow(
		10,
		10,
		cx - rcBlock.Width() - 30,
		cy - 20);
	m_StaticMatrixBoard.Invalidate(TRUE);

}

void CTestTetrisDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 987)
	{
		KillTimer(nIDEvent);

		//CRect rc;
		//GetWindowRect(&rc);
		//MoveWindow(rc.left, rc.top, 433, 642);
	}
	__super::OnTimer(nIDEvent);
}

void CTestTetrisDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	if (lpMMI->ptMinTrackSize.x <= 312)
	{
		lpMMI->ptMinTrackSize.x = 312;
	}

	  if (lpMMI->ptMinTrackSize.y <= 456)
	  {
		  lpMMI->ptMinTrackSize.y = 456;
	  }

	  CDialog::OnGetMinMaxInfo(lpMMI);
}