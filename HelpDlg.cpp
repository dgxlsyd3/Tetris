// HelpDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TestTetris.h"
#include "HelpDlg.h"


// CHelpDlg 对话框

IMPLEMENT_DYNAMIC(CHelpDlg, CDialog)

CHelpDlg::CHelpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHelpDlg::IDD, pParent)
{

}

CHelpDlg::~CHelpDlg()
{
}

void CHelpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHelpDlg, CDialog)
END_MESSAGE_MAP()


// CHelpDlg 消息处理程序

BOOL CHelpDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetDlgItemText(IDC_EDIT_HELP,
		"控制方法：\r\n"
		"左右箭头移动当前方块；\r\n"
		"上箭头旋转(变形)当前方块；\r\n"
		"下箭头加速当前方块下落。\r\n"
		"\r\n"
		"积分规则：\r\n"
		"单独消1行10分；\r\n"
		"连续消2行40分；\r\n"
		"连续消3行80分；\r\n"
		"连续消4行160分。"
		);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
