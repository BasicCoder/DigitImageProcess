#pragma once
#include "Resource.h"

// CDrawSetDlg dialog
//绘图类型
#define DrawGraphLine			1
#define DrawGraphRect			2
#define DrawGraphRorect			3
#define DrawGraphCircle			4
#define DrawGraphEllipse		5
#define DrawGraphPolyline		6
#define DrawGraphPolygon		7
#define DrawGraphFont			8
//笔的线型
#define DrawPenSolidLine		1
#define DrawPenDash				2
#define DrawPenDot				3
#define DrawPenDashDot			4
#define DrawPenDashDotDot		5
//刷的类型
#define DrawBrushNull			1
#define DrawBrushSolid			2
#define DrawBrushHorizon		3
#define DrawBrushVertical		4
#define DrawBrushFdiagonal		5
#define DrawBrushBdiagonal		6
#define DrawBrushCross			7
#define DrawBrushDiagcross		8
#define DrawBrushImg			9

class CDrawSetDlg : public CDialog
{
	DECLARE_DYNAMIC(CDrawSetDlg)

public:
	CDrawSetDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDrawSetDlg();

// Dialog Data
	enum { IDD = IDD_DRAW_SET_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int m_iPenWidth;
	int m_sPenStyle;
	COLORREF m_cPenColor;
	virtual BOOL OnInitDialog();
	int m_Graph;
	int m_BrushStyle;
	int m_BrushHatch;
	COLORREF m_BrushColor;
	BOOL m_bCheckFill;
	CBitmap m_Bitmap;
	CString m_StrBitmapPath;
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButtonPenColor();
	afx_msg void OnBnClickedButtonBrushColor();
	afx_msg void OnStnClickedBitmapImg();
};
