// HelpDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestTetris.h"
#include "HelpDlg.h"


// CHelpDlg �Ի���

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


// CHelpDlg ��Ϣ�������

BOOL CHelpDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetDlgItemText(IDC_EDIT_HELP,
		"���Ʒ�����\r\n"
		"���Ҽ�ͷ�ƶ���ǰ���飻\r\n"
		"�ϼ�ͷ��ת(����)��ǰ���飻\r\n"
		"�¼�ͷ���ٵ�ǰ�������䡣\r\n"
		"\r\n"
		"���ֹ���\r\n"
		"������1��10�֣�\r\n"
		"������2��40�֣�\r\n"
		"������3��80�֣�\r\n"
		"������4��160�֡�"
		);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
