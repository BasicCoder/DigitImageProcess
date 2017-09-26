// SetFontString.cpp : implementation file
//

#include "stdafx.h"
#include "MFCDraw.h"
#include "SetFontString.h"
#include "afxdialogex.h"


// CSetFontString dialog

IMPLEMENT_DYNAMIC(CSetFontString, CDialogEx)

CSetFontString::CSetFontString(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetFontString::IDD, pParent)
{

}

CSetFontString::~CSetFontString()
{
}

void CSetFontString::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSetFontString, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSetFontString::OnBnClickedOk)
END_MESSAGE_MAP()


// CSetFontString message handlers


BOOL CSetFontString::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	SetDlgItemTextW(IDC_EDIT_INPUT_TEXT, m_textString);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CSetFontString::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	GetDlgItemTextW(IDC_EDIT_INPUT_TEXT, m_textString);
	CDialogEx::OnOK();
}
