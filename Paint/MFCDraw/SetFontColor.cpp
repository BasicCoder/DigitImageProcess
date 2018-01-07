// SetFontColor.cpp : implementation file
//

#include "stdafx.h"
#include "MFCDraw.h"
#include "SetFontColor.h"
#include "afxdialogex.h"


// CSetFontColor dialog

IMPLEMENT_DYNAMIC(CSetFontColor, CDialogEx)

CSetFontColor::CSetFontColor(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetFontColor::IDD, pParent)
{

}

CSetFontColor::~CSetFontColor()
{
}

void CSetFontColor::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSetFontColor, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_FRONT_COLOR_FONT, &CSetFontColor::OnBnClickedButtonFrontColorFont)
	ON_BN_CLICKED(IDC_BUTTON_BACK_COLOR_FONT, &CSetFontColor::OnBnClickedButtonBackColorFont)
END_MESSAGE_MAP()


// CSetFontColor message handlers


void CSetFontColor::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialogEx::OnPaint() for painting messages
	CWnd* pWnd = GetDlgItem(IDC_BUTTON_FRONT_COLOR_FONT);
	CDC* pDC = pWnd->GetDC();
	CRect rect;
	pWnd->GetClientRect(&rect);
	//CBrush brush(m_cPenColor);
	pWnd->Invalidate();
	pWnd->UpdateWindow();
	pDC->FillSolidRect(&rect, m_textColor);
	ReleaseDC(pDC);

	pWnd = GetDlgItem(IDC_BUTTON_BACK_COLOR_FONT);
	pDC = pWnd->GetDC();
	pWnd->GetClientRect(&rect);
	pWnd->Invalidate();
	pWnd->UpdateWindow();
	pDC->FillSolidRect(&rect, m_textBackColor);
	ReleaseDC(pDC);
}


void CSetFontColor::OnBnClickedButtonFrontColorFont()
{
	// TODO: Add your control notification handler code here
	CColorDialog colDlg(m_textColor, CC_FULLOPEN);
	if (colDlg.DoModal() == IDOK)
	{
		m_textColor = colDlg.GetColor();
		CWnd* pWnd = GetDlgItem(IDC_BUTTON_FRONT_COLOR_FONT);
		CDC* pDC = pWnd->GetDC();
		CRect rect;
		pWnd->GetClientRect(&rect);
		pWnd->Invalidate();
		pWnd->UpdateWindow();
		pDC->FillSolidRect(&rect, m_textColor);
	}
}


void CSetFontColor::OnBnClickedButtonBackColorFont()
{
	// TODO: Add your control notification handler code here
	CColorDialog colDlg(m_textBackColor, CC_FULLOPEN);
	if (colDlg.DoModal() == IDOK)
	{
		m_textBackColor = colDlg.GetColor();
		CWnd* pWnd = GetDlgItem(IDC_BUTTON_BACK_COLOR_FONT);
		CDC* pDC = pWnd->GetDC();
		CRect rect;
		pWnd->GetClientRect(&rect);
		pWnd->Invalidate();
		pWnd->UpdateWindow();
		pDC->FillSolidRect(&rect, m_textBackColor);
	}
}
