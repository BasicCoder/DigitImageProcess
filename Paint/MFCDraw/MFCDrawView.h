
// MFCDrawView.h : CMFCDrawView 类的接口
//
#pragma once
//绘图类型
#define DrawGraphLine			1
#define DrawGraphRect			2
#define DrawGraphRorect			3
#define DrawGraphCircle			4
#define DrawGraphEllipse		5
#define DrawGraphPolyline		6
#define DrawGraphPolygon		7
#define DrawGraphFont			8
//笔的宽度
#define DrawPenWidth_1			1
#define DrawPenWidth_2			2
#define DrawPenWidth_4			4
#define DrawPenWidth_8			8
#define DrawPenWidth_10			10
#define DrawPenWidth_15			15
#define DrawPenWidth_20			20
#define DrawPenWidth_30			30
#define DrawPenWidth_50			50
#define DrawPenWidth_100		100
#define DrawPenWidth_200		200
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

class CMFCDrawView : public CView
{
protected: // 仅从序列化创建
	CMFCDrawView();
	DECLARE_DYNCREATE(CMFCDrawView)

// 特性
public:
	CMFCDrawDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMFCDrawView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnViewMytoolbar();
private:
	bool m_bTBar;
	int mGetPenStyle();
	int mGetPenWidth();
	COLORREF mGetPenColor();

	void mCreateBrush();
	HBITMAP CopyBitmap(HBITMAP hSourceHbitmap);
	CString GetFontNumber(int size);
	BOOL SetMyFont(CDC *pDC, LPCTSTR name, int size,
		COLORREF col, int angle, BOOL italic, BOOL bold,
		BOOL underline, BOOL strikeOut);

public:
	afx_msg void OnUpdateViewMytoolbar(CCmdUI *pCmdUI);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
public:
	bool m_bLButtonDown, m_bErase;			//判断是否按下左鼠标键,是否需要擦除图形
	CPoint p0, pm, pPoly, pStart;							//记录直线起点和动态终点	
	bool m_bStart;
	CPen *pGrayPen, *pLinePen;				//定义灰色和直线笔的对象指针
	CPen *pPen;								//笔的指针
	CBrush m_Brush;							//定义笔
	CBitmap m_Bitmap;						//位图
	CString m_StrBitmapPath;			//位图路径
	int  m_nDrawGraph;						//绘制图形类型
	//笔的参数
	int  m_nDrawPenWidth;
	int  m_nDrawPenStyle;
	COLORREF m_DrawPenColor;
	//刷的参数
	int  m_nDrawBrushStyle;
	bool m_bDrawFill;
	COLORREF m_DrawBrushColor;

	//字体定义
	CFont m_font, *pOldFont;
	LOGFONT m_logFont;
	wchar_t m_fontName[LF_FACESIZE];
	int m_iFontSize;
	COLORREF m_textColor;
	COLORREF m_textBackColor;
	BOOL m_bItalic, m_bBold, m_bUnderline, m_bStrikeOut;
	CString m_textString;

	//设置绘图图形消息映射函数
	afx_msg void OnDrawGraphLine();
	afx_msg void OnUpdateDrawGraphLine(CCmdUI *pCmdUI);
	afx_msg void OnDrawGraphRect();
	afx_msg void OnUpdateDrawGraphRect(CCmdUI *pCmdUI);
	afx_msg void OnDrawGraphRorect();
	afx_msg void OnUpdateDrawGraphRorect(CCmdUI *pCmdUI);
	afx_msg void OnDrawGraphCircle();
	afx_msg void OnUpdateDrawGraphCircle(CCmdUI *pCmdUI);
	afx_msg void OnDrawGraphEllipse();
	afx_msg void OnUpdateDrawGraphEllipse(CCmdUI *pCmdUI);
	afx_msg void OnDrawGraphPolyline();
	afx_msg void OnUpdateDrawGraphPolyline(CCmdUI *pCmdUI);
	afx_msg void OnDrawGraphPolygon();
	afx_msg void OnUpdateDrawGraphPolygon(CCmdUI *pCmdUI);
	afx_msg void OnDrawGraphFont();
	afx_msg void OnUpdateDrawGraphFont(CCmdUI *pCmdUI);

	//设置线宽消息映射函数
	afx_msg void OnDrawPenWidth1();
	afx_msg void OnDrawPenWidth2();
	afx_msg void OnDrawPenWidth4();
	afx_msg void OnDrawPenWidth8();
	afx_msg void OnDrawPenWidth10();
	afx_msg void OnDrawPenWidth15();
	afx_msg void OnDrawPenWidth20();
	afx_msg void OnDrawPenWidth30();
	afx_msg void OnDrawPenWidth50();
	afx_msg void OnDrawPenWidth100();
	afx_msg void OnDrawPenWidth200();

	//设置画笔的线型消息映射函数
	afx_msg void OnDrawPenSolidline();
	afx_msg void OnUpdateDrawPenSolidline(CCmdUI *pCmdUI);
	afx_msg void OnDrawPenDash();
	afx_msg void OnUpdateDrawPenDash(CCmdUI *pCmdUI);
	afx_msg void OnDrawPenDot();
	afx_msg void OnUpdateDrawPenDot(CCmdUI *pCmdUI);
	afx_msg void OnDrawPenDashdot();
	afx_msg void OnUpdateDrawPenDashdot(CCmdUI *pCmdUI);
	afx_msg void OnDrawPenDashdotdot();
	afx_msg void OnUpdateDrawPenDashdotdot(CCmdUI *pCmdUI);
	afx_msg void OnDrawBrushNull();
	afx_msg void OnUpdateDrawBrushNull(CCmdUI *pCmdUI);
	afx_msg void OnDrawBrushSolid();
	afx_msg void OnUpdateDrawBrushSolid(CCmdUI *pCmdUI);
	afx_msg void OnDrawBrushHorizon();
	afx_msg void OnUpdateDrawBrushHorizon(CCmdUI *pCmdUI);
	afx_msg void OnDrawBrushVertical();
	afx_msg void OnUpdateDrawBrushVertical(CCmdUI *pCmdUI);
	afx_msg void OnDrawBrushFdiagonal();
	afx_msg void OnUpdateDrawBrushFdiagonal(CCmdUI *pCmdUI);
	afx_msg void OnDrawBrushBdiagonal();
	afx_msg void OnUpdateDrawBrushBdiagonal(CCmdUI *pCmdUI);
	afx_msg void OnDrawBrushCross();
	afx_msg void OnUpdateDrawBrushCross(CCmdUI *pCmdUI);
	afx_msg void OnDrawBrushDiagcross();
	afx_msg void OnUpdateDrawBrushDiagcross(CCmdUI *pCmdUI);
	afx_msg void OnDrawBrushGraph();
	afx_msg void OnUpdateDrawBrushGraph(CCmdUI *pCmdUI);
	afx_msg void OnDrawFill();
	afx_msg void OnUpdateDrawFill(CCmdUI *pCmdUI);
	afx_msg void OnDrawClear();
	afx_msg void OnDrawPenColor();
	afx_msg void OnDrawBrushColor();	
	afx_msg void OnDrawSet();
	afx_msg void OnDrawBrushChange();

	//设置字体的消息映射函数
	afx_msg void OnFontChoose();
	afx_msg void OnFontColor();
	afx_msg void OnFontIntputstr();
	afx_msg void OnFontOutputstr();
	afx_msg void OnFontSize();
	afx_msg void OnFontRotate();
	afx_msg void OnDrawPenWidthN();
	afx_msg void OnBmpRotation();
	afx_msg void OnBitmapGray();
	afx_msg void OnBitmapNegative();
	afx_msg void OnBitmapWoodcut();
	afx_msg void OnBitmapCarve();
	afx_msg void OnBitmapRelievo();
};

#ifndef _DEBUG  // MFCDrawView.cpp 中的调试版本
inline CMFCDrawDoc* CMFCDrawView::GetDocument() const
   { return reinterpret_cast<CMFCDrawDoc*>(m_pDocument); }
#endif

