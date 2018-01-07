// SetPenWidth.cpp : implementation file
//

#include "stdafx.h"
#include "MFCDraw.h"
#include "SetPenWidth.h"
#include "afxdialogex.h"


// CSetPenWidth dialog

IMPLEMENT_DYNAMIC(CSetPenWidth, CDialogEx)

CSetPenWidth::CSetPenWidth(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetPenWidth::IDD, pParent)
{

}

CSetPenWidth::~CSetPenWidth()
{
}

void CSetPenWidth::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSetPenWidth, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSetPenWidth::OnBnClickedOk)
END_MESSAGE_MAP()


// CSetPenWidth message handlers


BOOL CSetPenWidth::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	CSpinButtonCtrl *pSpin =
		(CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_PEN_WIDTH);
	pSpin->SetRange(0, 500);
	SetDlgItemInt(IDC_EDIT_INTPUT_PEN_WIDTH, m_PenWidth);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CSetPenWidth::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	m_PenWidth = GetDlgItemInt(IDC_SPIN_PEN_WIDTH);
	CDialogEx::OnOK();
}
