// ChangeBitmap.cpp : implementation file
//

#include "stdafx.h"
#include "Resource.h"
#include "MFCDraw.h"
#include "ChangeBitmap.h"
#include "afxdialogex.h"


// CChangeBitmap dialog

IMPLEMENT_DYNAMIC(CChangeBitmap, CDialogEx)

CChangeBitmap::CChangeBitmap(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChangeBitmap::IDD, pParent)
{
	m_Bitmap.LoadBitmapW(IDB_JTX);
}

CChangeBitmap::~CChangeBitmap()
{
}

void CChangeBitmap::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CChangeBitmap, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CChangeBitmap::OnBnClickedButtonOpen)
END_MESSAGE_MAP()


// CChangeBitmap message handlers


void CChangeBitmap::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialogEx::OnPaint() for painting messages
	CWnd* pWnd = GetDlgItem(IDC_STATIC_BITMAP);
	CDC* pDC = pWnd->GetDC();
	CRect rect;
	pWnd->GetClientRect(&rect);
	CDC dcbm;
	BITMAP bms;
	HBITMAP hBmp = (HBITMAP)LoadImageW(NULL, m_StrBitmapPath,
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_DEFAULTCOLOR |
		LR_DEFAULTSIZE); // 装入位图文件，获取位图句柄
	if (hBmp != NULL){
		m_Bitmap.DeleteObject();
		m_Bitmap.Attach(hBmp);
	}
	m_Bitmap.GetBitmap(&bms);
	dcbm.CreateCompatibleDC(pDC);
	dcbm.SelectObject(&m_Bitmap);
	pDC->SetStretchBltMode(HALFTONE);
	pDC->StretchBlt(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, &dcbm, 0, 0, bms.bmWidth, bms.bmHeight, SRCCOPY);
	ReleaseDC(pDC);

	CString Width, Height;
	Width.Format(_T("%d"), bms.bmWidth);
	Height.Format(_T("%d"), bms.bmHeight);
	pWnd = GetDlgItem(IDC_STATIC_WEIGHT);
	pWnd->SetWindowTextW(Width);
	pWnd = GetDlgItem(IDC_STATIC_HEIGHT);
	pWnd->SetWindowTextW(Height);
}


void CChangeBitmap::OnBnClickedButtonOpen()
{
	// TODO: Add your control notification handler code here
	m_StrBitmapPath = L"..\\res\\Loli1.bmp";
	CFileDialog FileDlg(TRUE, _T("Bitmap File(*.bmp)|*.bmp"), NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("Bitmap File(*.bmp)|*.bmp| All Files (*.*)|*.*||"), this);
	if (FileDlg.DoModal() == IDOK)
	{
		m_StrBitmapPath = FileDlg.GetPathName();
	}

	HBITMAP hBmp = (HBITMAP)LoadImageW(NULL, m_StrBitmapPath,
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_DEFAULTCOLOR |
		LR_DEFAULTSIZE); // 装入位图文件，获取位图句柄
	if (hBmp != NULL) { // 句柄有效（装入位图文件成功）
		// 由位图句柄创建位图对象：
		CBitmap *pBmp = CBitmap::FromHandle(hBmp);
		m_Bitmap.DeleteObject();
		m_Bitmap.Attach(hBmp);
		// 显示位图（方法同上2）
		CRect rect;
		BITMAP bs;
		CWnd* pWnd = GetDlgItem(IDC_STATIC_BITMAP);
		CDC* pDC = pWnd->GetDC();
		pBmp->GetBitmap(&bs);
		pWnd->GetClientRect(&rect);
		CDC dc;
		dc.CreateCompatibleDC(pDC);
		dc.SelectObject(pBmp);
		pDC->SetStretchBltMode(HALFTONE);
		pDC->StretchBlt(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, &dc, 0, 0, bs.bmWidth, bs.bmHeight, SRCCOPY);
		ReleaseDC(pDC);

		CString Width, Height;
		Width.Format(_T("%d"), bs.bmWidth);
		Height.Format(_T("%d"), bs.bmHeight);
		pWnd = GetDlgItem(IDC_STATIC_WEIGHT);
		pWnd->SetWindowTextW(Width);
		pWnd = GetDlgItem(IDC_STATIC_HEIGHT);
		pWnd->SetWindowTextW(Height);
	}
}
