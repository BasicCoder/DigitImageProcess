// DrawSetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCDrawDoc.h"
#include "DrawSetDlg.h"
#include "afxdialogex.h"
#include "Resource.h"
// CDrawSetDlg dialog

IMPLEMENT_DYNAMIC(CDrawSetDlg, CDialog)

CDrawSetDlg::CDrawSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDrawSetDlg::IDD, pParent)
	, m_iPenWidth(0)
	, m_sPenStyle(DrawPenSolidLine)
	, m_cPenColor(RGB(128,128,128))
	, m_Graph(DrawGraphLine)
	, m_BrushStyle(DrawBrushImg)
	, m_BrushHatch(DrawBrushHorizon)
	, m_BrushColor(RGB(128,128,128))
	, m_bCheckFill(TRUE)

{
	m_Bitmap.LoadBitmapW(IDB_JTX);
	//m_StrBitmapPath = "..\\res\\LoLi1.bmp";
}

CDrawSetDlg::~CDrawSetDlg()
{
}

void CDrawSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PEN_WIDTH, m_iPenWidth);
	DDV_MinMaxInt(pDX, m_iPenWidth, 0, 500);
	//DDX_CBIndex(pDX, IDC_COMBO_PEN_STYLE, m_sPenStyle);
	//DDX_CBString(pDX, IDC_COMBO_PEN_STYLE, m_sPenStyle);
	//DDV_MaxChars(pDX, m_sPenStyle, 10);
	//DDX_Radio(pDX, IDC_GRAPH_LINE, m_Graph);
	//DDX_Radio(pDX, IDC_BRUSH_NULL, m_BrushStyle);
	//DDX_CBIndex(pDX, IDC_COMBO_BRUSH_HATCH, m_BrushHatch);
	DDX_Check(pDX, IDC_CHECK_FILL, m_bCheckFill);
}


BEGIN_MESSAGE_MAP(CDrawSetDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CDrawSetDlg::OnBnClickedOk)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_PEN_COLOR, &CDrawSetDlg::OnBnClickedButtonPenColor)
	ON_BN_CLICKED(IDC_BUTTON_BRUSH_COLOR, &CDrawSetDlg::OnBnClickedButtonBrushColor)
	ON_STN_CLICKED(IDC_BITMAP_IMG, &CDrawSetDlg::OnStnClickedBitmapImg)
END_MESSAGE_MAP()


// CDrawSetDlg message handlers


BOOL CDrawSetDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	SetDlgItemInt(IDC_EDIT_PEN_WIDTH, 1);
	CSpinButtonCtrl * pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_PEN_WIDTH);
	pSpin->SetRange(0, 500);
	CComboBox* pSLB = (CComboBox*)GetDlgItem(IDC_COMBO_PEN_STYLE);
	pSLB->AddString(L"实心");
	pSLB->AddString(L"虚线");
	pSLB->AddString(L"点线");
	pSLB->AddString(L"虚点线");
	pSLB->AddString(L"虚点点线");
	pSLB->AddString(L"空笔");
	pSLB->AddString(L"框内");
	CComboBox* pSBB = (CComboBox*)GetDlgItem(IDC_COMBO_BRUSH_HATCH);
	pSBB->AddString(L"水平线");
	pSBB->AddString(L"垂直线");
	pSBB->AddString(L"正斜线");
	pSBB->AddString(L"反斜线");
	pSBB->AddString(L"十字线");
	pSBB->AddString(L"斜十字线");
	pSBB->SetCurSel(0);
	
	CheckDlgButton(IDC_CHECK_FILL, m_bCheckFill);
	//CheckDlgButton(IDC_BRUSH_IMG, 1);
	SetDlgItemInt(IDC_EDIT_PEN_WIDTH, m_iPenWidth);
	int index = 0;
	switch (m_sPenStyle)
	{
	case DrawPenSolidLine:
		index = 0;
		break;
	case DrawPenDash:
		index = 1;
		break;
	case DrawPenDot:
		index = 2;
		break;
	case DrawPenDashDot:
		index = 3;
		break;
	case DrawPenDashDotDot:
		index = 4;
		break;
	}
	pSLB->SetCurSel(index);
	switch (m_Graph)
	{
	case DrawGraphLine:
		CheckDlgButton(IDC_GRAPH_LINE, 1);
		break;
	case DrawGraphRect:
		CheckDlgButton(IDC_GRAPH_RECT, 1);
		break;
	case DrawGraphRorect:
		CheckDlgButton(IDC_GRAPH_ROUNDRECT, 1);
		break;
	case DrawGraphCircle:
		CheckDlgButton(IDC_GRAPH_CIRCLE, 1);
		break;
	case DrawGraphEllipse:
		CheckDlgButton(IDC_GRAPH_ELLIPSE, 1);
		break;
	case DrawGraphPolyline:
		CheckDlgButton(IDC_GRAPH_POLYLINE, 1);
		break;
	case DrawGraphPolygon:
		CheckDlgButton(IDC_GRAPH_POLYGON, 1);
		break;
	case DrawGraphFont:
		CheckDlgButton(IDC_GRAPH_FONT, 1);
		break;
		break;
	}

	index = 0;
	switch (m_BrushStyle)
	{
	case DrawBrushNull:
		CheckDlgButton(IDC_BRUSH_NULL, 1);
		break;
	case DrawBrushSolid:
		CheckDlgButton(IDC_BRUSH_SOLID, 1);
		break;
	case DrawBrushHorizon:
	case DrawBrushVertical:
	case DrawBrushFdiagonal:
	case DrawBrushBdiagonal:
	case DrawBrushCross:
	case DrawBrushDiagcross:
		CheckDlgButton(IDC_BRUSH_HATCH, 1);
		switch (m_BrushStyle)
		{
		case DrawBrushHorizon:
			index = 0;
			break;
		case DrawBrushVertical:
			index = 1;
			break;
		case DrawBrushFdiagonal:
			index = 2;
			break;
		case DrawBrushBdiagonal:
			index = 3;
			break;
		case DrawBrushCross:
			index = 4;
			break;
		case DrawBrushDiagcross:
			index = 5;
			break;
		}
		pSBB->SetCurSel(index);
		break;
	case DrawBrushImg:
		CheckDlgButton(IDC_BRUSH_IMG, 1);
		break;
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CDrawSetDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	int index = 0;
	m_iPenWidth = GetDlgItemInt(IDC_EDIT_PEN_WIDTH);
	CComboBox* pSLB = (CComboBox*)GetDlgItem(IDC_COMBO_PEN_STYLE);
	index = pSLB->GetCurSel();
	switch (index)
	{
	case 0:
		m_sPenStyle = DrawPenSolidLine;
		break;
	case 1:
		m_sPenStyle = DrawPenDash;
		break;
	case 2:
		m_sPenStyle = DrawPenDot;
		break;
	case 3:
		m_sPenStyle = DrawPenDashDot;
		break;
	case 4:
		m_sPenStyle = DrawPenDashDotDot;
		break;
	}
	//绘图类型
	if (IsDlgButtonChecked(IDC_GRAPH_LINE))m_Graph = DrawGraphLine;
	if (IsDlgButtonChecked(IDC_GRAPH_RECT))m_Graph = DrawGraphRect;
	if (IsDlgButtonChecked(IDC_GRAPH_ROUNDRECT))m_Graph = DrawGraphRorect;
	if (IsDlgButtonChecked(IDC_GRAPH_CIRCLE))m_Graph = DrawGraphCircle;
	if (IsDlgButtonChecked(IDC_GRAPH_ELLIPSE))m_Graph = DrawGraphEllipse;
	if (IsDlgButtonChecked(IDC_GRAPH_POLYLINE))m_Graph = DrawGraphPolyline;
	if (IsDlgButtonChecked(IDC_GRAPH_POLYGON))m_Graph = DrawGraphPolygon;
	if (IsDlgButtonChecked(IDC_GRAPH_FONT))m_Graph = DrawGraphFont;

	//刷类型
	if (IsDlgButtonChecked(IDC_BRUSH_NULL))m_BrushStyle = DrawBrushNull;
	if (IsDlgButtonChecked(IDC_BRUSH_SOLID))m_BrushStyle = DrawBrushSolid;
	if (IsDlgButtonChecked(IDC_BRUSH_HATCH))
	{
		CComboBox* pSBB = (CComboBox*)GetDlgItem(IDC_COMBO_BRUSH_HATCH);
		index = pSBB->GetCurSel();
		switch (index)
		{
		case 0:
			m_BrushStyle = DrawBrushHorizon;
				break;
		case 1:
			m_BrushStyle = DrawBrushVertical;
			break;
		case 2:
			m_BrushStyle = DrawBrushFdiagonal;
			break;
		case 3:
			m_BrushStyle = DrawBrushBdiagonal;
			break;
		case 4:
			m_BrushStyle = DrawBrushCross;
			break;
		case 5:
			m_BrushStyle = DrawBrushDiagcross;
			break;
		}
	}
	if (IsDlgButtonChecked(IDC_BRUSH_IMG))m_BrushStyle = DrawBrushImg;
	
	CDialog::OnOK();
}


void CDrawSetDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialog::OnPaint() for painting messages
	CWnd* pWnd = GetDlgItem(IDC_BUTTON_PEN_COLOR);
	CDC* pDC = pWnd->GetDC();
	CRect rect;
	pWnd->GetClientRect(&rect);
	//CBrush brush(m_cPenColor);
	pWnd->Invalidate();
	pWnd->UpdateWindow();
	pDC->FillSolidRect(&rect, m_cPenColor);
	ReleaseDC(pDC);

	pWnd = GetDlgItem(IDC_BUTTON_BRUSH_COLOR);
	pDC = pWnd->GetDC();
	pWnd->GetClientRect(&rect);
	pWnd->Invalidate();
	pWnd->UpdateWindow();
	pDC->FillSolidRect(&rect, m_BrushColor);
	ReleaseDC(pDC);

	pWnd = GetDlgItem(IDC_BITMAP_IMG);
	pDC = pWnd->GetDC();
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
	pDC->StretchBlt(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, &dcbm, 0, 0, bms.bmWidth, bms.bmHeight,SRCCOPY);
	ReleaseDC(pDC);

	CString Width, Height;
	Width.Format(_T("%d"), bms.bmWidth);
	Height.Format(_T("%d"), bms.bmHeight);
	pWnd = GetDlgItem(IDC_BITMAP_WIDTH);
	pWnd->SetWindowTextW(Width);
	pWnd = GetDlgItem(IDC_BITMAP_HEIGHT);
	pWnd->SetWindowTextW(Height);
}


void CDrawSetDlg::OnBnClickedButtonPenColor()
{
	// TODO: Add your control notification handler code here
	CColorDialog colDlg(m_cPenColor, CC_FULLOPEN);
	if (colDlg.DoModal() == IDOK)
	{
		m_cPenColor = colDlg.GetColor();
		CWnd* pWnd = GetDlgItem(IDC_BUTTON_PEN_COLOR);
		CDC* pDC = pWnd->GetDC();
		CRect rect;
		pWnd->GetClientRect(&rect);
		pWnd->Invalidate();
		pWnd->UpdateWindow();
		pDC->FillSolidRect(&rect, m_cPenColor);
	}
		
}


void CDrawSetDlg::OnBnClickedButtonBrushColor()
{
	// TODO: Add your control notification handler code here
	CColorDialog colDlg(m_BrushColor, CC_FULLOPEN);
	if (colDlg.DoModal() == IDOK)
	{
		m_BrushColor = colDlg.GetColor();
		CWnd* pWnd = GetDlgItem(IDC_BUTTON_BRUSH_COLOR);
		CDC* pDC = pWnd->GetDC();
		CRect rect;
		pWnd->GetClientRect(&rect);
		pWnd->Invalidate();
		pWnd->UpdateWindow();
		pDC->FillSolidRect(&rect, m_BrushColor);
	}	
}


void CDrawSetDlg::OnStnClickedBitmapImg()
{
	// TODO: Add your control notification handler code here
	m_StrBitmapPath = L"..\\res\\Loli1.bmp";
	CFileDialog FileDlg(TRUE, _T("Bitmap File(*.bmp)|*.bmp"), NULL, 
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("Bitmap File(*.bmp)|*.bmp| All Files (*.*)|*.*||"),this);
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
		CWnd* pWnd = GetDlgItem(IDC_BITMAP_IMG);
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
		pWnd = GetDlgItem(IDC_BITMAP_WIDTH);
		pWnd->SetWindowTextW(Width);
		pWnd = GetDlgItem(IDC_BITMAP_HEIGHT);
		pWnd->SetWindowTextW(Height);
	}
}
