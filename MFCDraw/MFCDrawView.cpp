
// MFCDrawView.cpp : CMFCDrawView 类的实现
//

#include "stdafx.h"
#include "MainFrm.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCDraw.h"
#endif

#include <math.h>
#include <gdiplus.h>


#include "MFCDrawDoc.h"
#include "MFCDrawView.h"
#include "Resource.h"
#include "DrawSetDlg.h"
#include "ChangeBitmap.h"
#include "SetFontColor.h"
#include "SetFontString.h"
#include "SetPenWidth.h"
/*#ifdef _DEBUG
#define new DEBUG_NEW
#endif*/

using namespace Gdiplus;
// CMFCDrawView

IMPLEMENT_DYNCREATE(CMFCDrawView, CView)

BEGIN_MESSAGE_MAP(CMFCDrawView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_VIEW_MYTOOLBAR, &CMFCDrawView::OnViewMytoolbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_MYTOOLBAR, &CMFCDrawView::OnUpdateViewMytoolbar)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_DRAW_GRAPH_LINE, &CMFCDrawView::OnDrawGraphLine)
	ON_UPDATE_COMMAND_UI(ID_DRAW_GRAPH_LINE, &CMFCDrawView::OnUpdateDrawGraphLine)
	ON_COMMAND(ID_DRAW_GRAPH_RECT, &CMFCDrawView::OnDrawGraphRect)
	ON_UPDATE_COMMAND_UI(ID_DRAW_GRAPH_RECT, &CMFCDrawView::OnUpdateDrawGraphRect)
	ON_COMMAND(ID_DRAW_GRAPH_RORECT, &CMFCDrawView::OnDrawGraphRorect)
	ON_UPDATE_COMMAND_UI(ID_DRAW_GRAPH_RORECT, &CMFCDrawView::OnUpdateDrawGraphRorect)
	ON_COMMAND(ID_DRAW_GRAPH_CIRCLE, &CMFCDrawView::OnDrawGraphCircle)
	ON_UPDATE_COMMAND_UI(ID_DRAW_GRAPH_CIRCLE, &CMFCDrawView::OnUpdateDrawGraphCircle)
	ON_COMMAND(ID_DRAW_GRAPH_EllIPSE, &CMFCDrawView::OnDrawGraphEllipse)
	ON_UPDATE_COMMAND_UI(ID_DRAW_GRAPH_EllIPSE, &CMFCDrawView::OnUpdateDrawGraphEllipse)
	ON_COMMAND(ID_DRAW_GRAPH_POLYLINE, &CMFCDrawView::OnDrawGraphPolyline)
	ON_UPDATE_COMMAND_UI(ID_DRAW_GRAPH_POLYLINE, &CMFCDrawView::OnUpdateDrawGraphPolyline)
	ON_COMMAND(ID_DRAW_GRAPH_POLYGON, &CMFCDrawView::OnDrawGraphPolygon)
	ON_UPDATE_COMMAND_UI(ID_DRAW_GRAPH_POLYGON, &CMFCDrawView::OnUpdateDrawGraphPolygon)
	ON_COMMAND(ID_DRAW_GRAPH_FONT, &CMFCDrawView::OnDrawGraphFont)
	ON_UPDATE_COMMAND_UI(ID_DRAW_GRAPH_FONT, &CMFCDrawView::OnUpdateDrawGraphFont)
	ON_COMMAND(ID_DRAW_PEN_WIDTH_1, &CMFCDrawView::OnDrawPenWidth1)
	ON_COMMAND(ID_DRAW_PEN_WIDTH_2, &CMFCDrawView::OnDrawPenWidth2)
	ON_COMMAND(ID_DRAW_PEN_WIDTH_4, &CMFCDrawView::OnDrawPenWidth4)
	ON_COMMAND(ID_DRAW_PEN_WIDTH_8, &CMFCDrawView::OnDrawPenWidth8)
	ON_COMMAND(ID_DRAW_PEN_WIDTH_10, &CMFCDrawView::OnDrawPenWidth10)
	ON_COMMAND(ID_DRAW_PEN_WIDTH_15, &CMFCDrawView::OnDrawPenWidth15)
	ON_COMMAND(ID_DRAW_PEN_WIDTH_20, &CMFCDrawView::OnDrawPenWidth20)
	ON_COMMAND(ID_DRAW_PEN_WIDTH_30, &CMFCDrawView::OnDrawPenWidth30)
	ON_COMMAND(ID_DRAW_PEN_WIDTH_50, &CMFCDrawView::OnDrawPenWidth50)
	ON_COMMAND(ID_DRAW_PEN_WIDTH_100, &CMFCDrawView::OnDrawPenWidth100)
	ON_COMMAND(ID_DRAW_PEN_WIDTH_200, &CMFCDrawView::OnDrawPenWidth200)
	ON_COMMAND(ID_DRAW_PEN_SOLIDLINE, &CMFCDrawView::OnDrawPenSolidline)
	ON_UPDATE_COMMAND_UI(ID_DRAW_PEN_SOLIDLINE, &CMFCDrawView::OnUpdateDrawPenSolidline)
	ON_COMMAND(ID_DRAW_PEN_DASH, &CMFCDrawView::OnDrawPenDash)
	ON_UPDATE_COMMAND_UI(ID_DRAW_PEN_DASH, &CMFCDrawView::OnUpdateDrawPenDash)
	ON_COMMAND(ID_DRAW_PEN_DOT, &CMFCDrawView::OnDrawPenDot)
	ON_UPDATE_COMMAND_UI(ID_DRAW_PEN_DOT, &CMFCDrawView::OnUpdateDrawPenDot)
	ON_COMMAND(ID_DRAW_PEN_DASHDOT, &CMFCDrawView::OnDrawPenDashdot)
	ON_UPDATE_COMMAND_UI(ID_DRAW_PEN_DASHDOT, &CMFCDrawView::OnUpdateDrawPenDashdot)
	ON_COMMAND(ID_DRAW_PEN_DASHDOTDOT, &CMFCDrawView::OnDrawPenDashdotdot)
	ON_UPDATE_COMMAND_UI(ID_DRAW_PEN_DASHDOTDOT, &CMFCDrawView::OnUpdateDrawPenDashdotdot)
	ON_COMMAND(ID_DRAW_BRUSH_NULL, &CMFCDrawView::OnDrawBrushNull)
	ON_UPDATE_COMMAND_UI(ID_DRAW_BRUSH_NULL, &CMFCDrawView::OnUpdateDrawBrushNull)
	ON_COMMAND(ID_DRAW_BRUSH_SOLID, &CMFCDrawView::OnDrawBrushSolid)
	ON_UPDATE_COMMAND_UI(ID_DRAW_BRUSH_SOLID, &CMFCDrawView::OnUpdateDrawBrushSolid)
	ON_COMMAND(ID_DRAW_BRUSH_HORIZON, &CMFCDrawView::OnDrawBrushHorizon)
	ON_UPDATE_COMMAND_UI(ID_DRAW_BRUSH_HORIZON, &CMFCDrawView::OnUpdateDrawBrushHorizon)
	ON_COMMAND(ID_DRAW_BRUSH_VERTICAL, &CMFCDrawView::OnDrawBrushVertical)
	ON_UPDATE_COMMAND_UI(ID_DRAW_BRUSH_VERTICAL, &CMFCDrawView::OnUpdateDrawBrushVertical)
	ON_COMMAND(ID_DRAW_BRUSH_FDIAGONAL, &CMFCDrawView::OnDrawBrushFdiagonal)
	ON_UPDATE_COMMAND_UI(ID_DRAW_BRUSH_FDIAGONAL, &CMFCDrawView::OnUpdateDrawBrushFdiagonal)
	ON_COMMAND(ID_DRAW_BRUSH_BDIAGONAL, &CMFCDrawView::OnDrawBrushBdiagonal)
	ON_UPDATE_COMMAND_UI(ID_DRAW_BRUSH_BDIAGONAL, &CMFCDrawView::OnUpdateDrawBrushBdiagonal)
	ON_COMMAND(ID_DRAW_BRUSH_CROSS, &CMFCDrawView::OnDrawBrushCross)
	ON_UPDATE_COMMAND_UI(ID_DRAW_BRUSH_CROSS, &CMFCDrawView::OnUpdateDrawBrushCross)
	ON_COMMAND(ID_DRAW_BRUSH_DIAGCROSS, &CMFCDrawView::OnDrawBrushDiagcross)
	ON_UPDATE_COMMAND_UI(ID_DRAW_BRUSH_DIAGCROSS, &CMFCDrawView::OnUpdateDrawBrushDiagcross)
	ON_COMMAND(ID_DRAW_BRUSH_GRAPH, &CMFCDrawView::OnDrawBrushGraph)
	ON_UPDATE_COMMAND_UI(ID_DRAW_BRUSH_GRAPH, &CMFCDrawView::OnUpdateDrawBrushGraph)
	ON_COMMAND(ID_DRAW_FILL, &CMFCDrawView::OnDrawFill)
	ON_UPDATE_COMMAND_UI(ID_DRAW_FILL, &CMFCDrawView::OnUpdateDrawFill)
	ON_COMMAND(ID_DRAW_CLEAR, &CMFCDrawView::OnDrawClear)
	ON_COMMAND(ID_DRAW_PEN_COLOR, &CMFCDrawView::OnDrawPenColor)
	ON_COMMAND(ID_DRAW_BRUSH_COLOR, &CMFCDrawView::OnDrawBrushColor)
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_DRAW_SET, &CMFCDrawView::OnDrawSet)
	ON_COMMAND(ID_DRAW_BRUSH_CHANGE, &CMFCDrawView::OnDrawBrushChange)
	ON_COMMAND(ID_FONT_CHOOSE, &CMFCDrawView::OnFontChoose)
	ON_COMMAND(ID_FONT_COLOR, &CMFCDrawView::OnFontColor)
	ON_COMMAND(ID_FONT_INTPUTSTR, &CMFCDrawView::OnFontIntputstr)
	ON_COMMAND(ID_FONT_OUTPUTSTR, &CMFCDrawView::OnFontOutputstr)
	ON_COMMAND(ID_FONT_SIZE, &CMFCDrawView::OnFontSize)
	ON_COMMAND(ID_FONT_ROTATE, &CMFCDrawView::OnFontRotate)
	ON_COMMAND(ID_DRAW_PEN_WIDTH_N, &CMFCDrawView::OnDrawPenWidthN)
	ON_COMMAND(ID_BMP_ROTATION, &CMFCDrawView::OnBmpRotation)
	ON_COMMAND(ID_BITMAP_GRAY, &CMFCDrawView::OnBitmapGray)
	ON_COMMAND(ID_BITMAP_NEGATIVE, &CMFCDrawView::OnBitmapNegative)
	ON_COMMAND(ID_BITMAP_Woodcut, &CMFCDrawView::OnBitmapWoodcut)
	ON_COMMAND(ID_BITMAP_Carve, &CMFCDrawView::OnBitmapCarve)
	ON_COMMAND(ID_BITMAP_Relievo, &CMFCDrawView::OnBitmapRelievo)
END_MESSAGE_MAP()

// CMFCDrawView 构造/析构

CMFCDrawView::CMFCDrawView()
	: m_bTBar(true)
	, m_bLButtonDown(false)
	, m_bErase(false)
	, m_nDrawGraph(DrawGraphLine)
	, m_nDrawPenWidth(0)
	, m_nDrawPenStyle(DrawPenSolidLine)
	, m_DrawPenColor(RGB(0, 0, 0))
	, m_bStart(false)
	, m_nDrawBrushStyle(DrawBrushImg)
	, m_bDrawFill(true)
{
	// TODO:  在此处添加构造代码
	pGrayPen = new CPen(PS_SOLID, 0, RGB(128, 128, 128));
	pLinePen = new CPen(PS_SOLID, 0, RGB(0, 0, 0));
	pPen = new CPen(PS_SOLID, 0, RGB(128, 128, 128));
	m_Brush.CreateStockObject(NULL_BRUSH);
	m_Bitmap.LoadBitmapW(IDB_JTX);
	m_StrBitmapPath = "..\\res\\LoLi1.bmp";

	//字体初始化
	wcscpy_s(m_fontName, LF_FACESIZE, L"宋体");
	m_iFontSize = 120;
	m_font.CreatePointFont(m_iFontSize, m_fontName);
	m_font.GetLogFont(&m_logFont);
	m_textColor = RGB(0, 0, 0);
	m_textBackColor = RGB(255, 255, 255);
	m_bItalic = false;
	m_bBold = false;
	m_bUnderline = false;
	m_bStrikeOut = false;
	m_textString = _T("This is a test text");
}

CMFCDrawView::~CMFCDrawView()
{
}

BOOL CMFCDrawView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMFCDrawView 绘制

void CMFCDrawView::OnDraw(CDC* pDC)
{
	CMFCDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码
	//if (!pDoc->img.IsNull())pDoc->img.Draw(pDC->m_hDC, 0, 0);

	Graphics graph(pDC->m_hDC);
	if (!pDoc->ImagePath.IsEmpty()){
		Image Rotation_img(pDoc->ImagePath);

		int width = Rotation_img.GetWidth();
		int height = Rotation_img.GetHeight();
		graph.DrawImage(&Rotation_img, 0, 0, width, height);
	}
	
	//MessageBox(L"Test", L"Test");

	
}


// CMFCDrawView 打印

BOOL CMFCDrawView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMFCDrawView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void CMFCDrawView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}


// CMFCDrawView 诊断

#ifdef _DEBUG
void CMFCDrawView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCDrawView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCDrawDoc* CMFCDrawView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCDrawDoc)));
	return (CMFCDrawDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCDrawView 消息处理程序


void CMFCDrawView::OnViewMytoolbar()
{
	// TODO: Add your command handler code here
	CMainFrame *pFrmWnd = (CMainFrame*)GetTopLevelFrame();
	if (m_bTBar){
		pFrmWnd->ShowControlBar(&pFrmWnd->m_ToolBar, false, false);
		m_bTBar = false;
	}
	else{
		pFrmWnd->ShowControlBar(&pFrmWnd->m_ToolBar, true, false);
		m_bTBar = true;
	}
}


void CMFCDrawView::OnUpdateViewMytoolbar(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_bTBar);
}

int CMFCDrawView::mGetPenStyle()
{
	switch (m_nDrawPenStyle)
	{
		case DrawPenSolidLine:
			return PS_SOLID;
		case DrawPenDash:
			return PS_DASH;
		case DrawPenDot:
			return PS_DOT;
		case DrawPenDashDot:
			return PS_DASHDOT;
		case DrawPenDashDotDot:
			return PS_DASHDOTDOT;
		default:
			return PS_NULL;
	}
}
int CMFCDrawView::mGetPenWidth()
{
	switch (m_nDrawPenWidth)
	{
	case DrawPenWidth_1:
		return 1;
	case DrawPenWidth_2:
		return 2;
	case DrawPenWidth_4:
		return 4;
	case DrawPenWidth_8:
		return 8;
	case DrawPenWidth_10:
		return 10;
	case DrawPenWidth_15:
		return 15;
	case DrawPenWidth_20:
		return 20;
	case DrawPenWidth_30:
		return 30;
	case DrawPenWidth_50:
		return 50;
	case DrawPenWidth_100:
		return 100;
	case DrawPenWidth_200:
		return 200;
	default:
		return 0;
	}
}
COLORREF CMFCDrawView::mGetPenColor()
{
	return m_DrawPenColor;
}
void CMFCDrawView::mCreateBrush()
{
	m_Brush.DeleteObject();
	switch (m_nDrawBrushStyle)
	{
	case DrawBrushNull:

		break;
	case DrawBrushSolid:
		m_Brush.CreateSolidBrush(m_DrawBrushColor);
		break;
	case DrawBrushHorizon:
		m_Brush.CreateHatchBrush(HS_HORIZONTAL, m_DrawBrushColor);
		break;
	case DrawBrushVertical:
		m_Brush.CreateHatchBrush(HS_VERTICAL, m_DrawBrushColor);
		break;
	case DrawBrushFdiagonal:
		m_Brush.CreateHatchBrush(HS_FDIAGONAL, m_DrawBrushColor);
		break;
	case DrawBrushBdiagonal:
		m_Brush.CreateHatchBrush(HS_BDIAGONAL, m_DrawBrushColor);
		break;
	case DrawBrushCross:
		m_Brush.CreateHatchBrush(HS_CROSS, m_DrawBrushColor);
		break;
	case DrawBrushDiagcross:
		m_Brush.CreateHatchBrush(HS_DIAGCROSS, m_DrawBrushColor);
		break;
	case DrawBrushImg:
		m_Brush.CreatePatternBrush(&m_Bitmap);
		break;
	}
}

void CMFCDrawView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	SetCursor(LoadCursor(NULL, IDC_CROSS));  //// 设置鼠标为十字
	wchar_t buf[20];
	CMainFrame *pFrmWnd = (CMainFrame*)GetTopLevelFrame();
	_itow_s(point.x, buf, 20, 10);
	pFrmWnd->m_wndStatusBar.SetPaneText(xVal, buf);
	_itow_s(point.y, buf, 20, 10);
	pFrmWnd->m_wndStatusBar.SetPaneText(yVal, buf);

	CDC* pDC = GetDC(); // 获取设备上下文
	pDC->SetROP2(R2_XORPEN); // 设置为异或绘图方式
	pDC->SetBkMode(TRANSPARENT); // 设置透明背景模式

	if (m_bLButtonDown){  //左鼠标键按下为真（拖动画图）
		//设置dx,dy值
		_itow_s(abs(point.x - p0.x), buf, 20, 10);
		pFrmWnd->m_wndStatusBar.SetPaneText(dxVal, buf);
		_itow_s(abs(point.y - p0.y), buf, 20, 10);
		pFrmWnd->m_wndStatusBar.SetPaneText(dyVal, buf);

		CPen* pOldPen;
		CBrush* pOldBrush;
		CRect rect;
		int d;
		int r;
		switch (m_nDrawGraph)
		{
		case DrawGraphLine:
			pOldPen = pDC->SelectObject(pGrayPen); // 选取灰色点线笔
			//pDC->SelectStockObject(NULL_BRUSH); // 选入空刷
			// 用于动态画封闭图形（如矩形、椭圆等）
			if (m_bErase) { // 需要擦除为真
				pDC->MoveTo(p0); pDC->LineTo(pm); // 擦除原直线
			}
			else // 需要擦除为假
				m_bErase = TRUE; // 设需要擦除为真

			pDC->MoveTo(p0); pDC->LineTo(point); // 绘制新直线
			pm = point; // 更新老终点

			pDC->SetROP2(R2_COPYPEN); // 设置覆盖绘图模式（还原默认的）
			pDC->SelectObject(pOldPen); // 选入旧笔

			break;
		case DrawGraphRect:
			pOldPen = pDC->SelectObject(pGrayPen); // 选取灰色点线笔

			pDC->SelectStockObject(NULL_BRUSH); // 选入空刷
			// 用于动态画封闭图形（如矩形、椭圆等）
			if (m_bErase){// 需要擦除为真
				pDC->Rectangle(min(p0.x, pm.x), min(p0.y, pm.y), max(p0.x, pm.x), max(p0.y, pm.y));
			}
			else
				m_bErase = TRUE;
			pDC->Rectangle(min(p0.x, point.x), min(p0.y, point.y), max(p0.x,point.x), max(p0.y, point.y));
			pm = point;// 更新老终点

			pDC->SetROP2(R2_COPYPEN);// 设置覆盖绘图模式（还原默认的）
			pDC->SelectObject(pOldPen); // 选入旧笔

			break;
		case DrawGraphRorect:
			pOldPen = pDC->SelectObject(pGrayPen);// 选取灰色点线笔
			pDC->SelectStockObject(NULL_BRUSH);
			if (m_bErase){// 需要擦除为真
				rect = CRect(min(p0.x, pm.x), min(p0.y, pm.y), max(p0.x, pm.x), max(p0.y, pm.y));
				d = min(rect.Width(), rect.Height()) / 4;
				pDC->RoundRect(&rect, CPoint(d, d));
			}
			else
				m_bErase = TRUE;
			rect = CRect(min(p0.x, point.x), min(p0.y, point.y), max(p0.x, point.x), max(p0.y, point.y));
			d = min(rect.Width(), rect.Height()) / 4;
			pDC->RoundRect(&rect, CPoint(d, d));
			pm = point;// 更新老终点

			pDC->SetROP2(R2_COPYPEN);// 设置覆盖绘图模式（还原默认的）
			pDC->SelectObject(pOldPen); // 选入旧笔
			break;
		case DrawGraphCircle:
			pOldPen = pDC->SelectObject(pGrayPen);// 选取灰色点线笔
			pDC->SelectStockObject(NULL_BRUSH);
			if (m_bErase){// 需要擦除为真
				r = max(pm.x - p0.x, pm.y - p0.y);
				pDC->Ellipse(p0.x, p0.y, p0.x + r, p0.y + r);
			}
			else
				m_bErase = TRUE;
			r = max(point.x - p0.x, point.y - p0.y);
			pDC->Ellipse(p0.x, p0.y, p0.x + r, p0.y + r);
			pm = point; // 更新老终点

			pDC->SetROP2(R2_COPYPEN);// 设置覆盖绘图模式（还原默认的）
			pDC->SelectObject(pOldPen); // 选入旧笔
			break;
		case DrawGraphEllipse:
			pOldPen = pDC->SelectObject(pGrayPen);// 选取灰色点线笔
			pDC->SelectStockObject(NULL_BRUSH);

			if (m_bErase){
				pDC->Ellipse(min(p0.x, pm.x), min(p0.y, pm.y), max(p0.x, pm.x), max(p0.y, pm.y));
			}
			else
				m_bErase = TRUE;
			pDC->Ellipse(min(p0.x, point.x), min(p0.y, point.y), max(p0.x, point.x), max(p0.y, point.y));
			pm = point;

			pDC->SetROP2(R2_COPYPEN);// 设置覆盖绘图模式（还原默认的）
			pDC->SelectObject(pOldPen); // 选入旧笔
			break;
		
		case DrawGraphFont:
			break;
		}	
	}
	else
	{
		CPen* pOldPen;
		switch (m_nDrawGraph)
		{
		case DrawGraphPolyline:
			if (m_bStart)
			{
				pOldPen = pDC->SelectObject(pGrayPen); // 选取灰色点线笔
				//pDC->SelectStockObject(NULL_BRUSH); // 选入空刷
				// 用于动态画封闭图形（如矩形、椭圆等）
				if (m_bErase) { // 需要擦除为真
					pDC->MoveTo(pPoly); pDC->LineTo(pm); // 擦除原直线
				}
				else // 需要擦除为假
					m_bErase = TRUE; // 设需要擦除为真

				pDC->MoveTo(pPoly); pDC->LineTo(point); // 绘制新直线
				pm = point; // 更新老终点

				pDC->SetROP2(R2_COPYPEN); // 设置覆盖绘图模式（还原默认的）
				pDC->SelectObject(pOldPen); // 选入旧笔
			}
			break;
		case DrawGraphPolygon:
			break;
		}
	}
	ReleaseDC(pDC); // 释放设备上下文
	CView::OnMouseMove(nFlags, point);
}


void CMFCDrawView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	SetCapture();		// 设置鼠标捕获
	m_bLButtonDown = true;	// 设左鼠标键按下为真
	if (m_bStart) pPoly = pm;
	p0 = point;				// 保存直线的起点
	pm = p0;				// 让直线的终点等于起点
	if (m_nDrawGraph == DrawGraphPolyline) m_bStart = true; // 设置折线开始		
	//pPoly = point;			//保存多边形节点
	CView::OnLButtonDown(nFlags, point);
}


void CMFCDrawView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	ReleaseCapture(); // 释放鼠标捕获
	CDC* pDC = GetDC(); // 获取设备上下文
	pDC->SelectObject(pGrayPen); // 选入灰色点线笔
	pDC->SetROP2(R2_XORPEN); // 设置为异或绘图方式
	pDC->SetBkMode(TRANSPARENT); // 设置透明背景模式

	if (m_bLButtonDown) { // 左鼠标键按下为真
		CRect rect;
		int d;
		int r;
		switch (m_nDrawGraph)
		{
		case DrawGraphLine:
			// pDC->SelectStockObject(NULL_BRUSH); // 选入空刷
			// 用于动态画封闭图形（如矩形、椭圆等）
			pDC->MoveTo(p0); pDC->LineTo(pm); // 擦除原直线

			pPen->DeleteObject();
			pPen = new CPen(mGetPenStyle(), mGetPenWidth(), m_DrawPenColor);
			pDC->SelectObject(pPen); // 选择直线笔
			pDC->SetROP2(R2_COPYPEN); // 设置为覆盖绘图方式

			pDC->MoveTo(p0); pDC->LineTo(point); // 绘制最终的直线

			m_bLButtonDown = FALSE; // 重设左鼠标键按下为假
			m_bErase = FALSE; // 重需要擦除为假
			break;
		case DrawGraphRect:
			pDC->SelectStockObject(NULL_BRUSH);// 选入空刷
			pDC->Rectangle(min(p0.x, pm.x), min(p0.y, pm.y), max(p0.x, pm.x), max(p0.y, pm.y));
			
			//选入笔，设置绘图模式
			pPen->DeleteObject();
			pPen = new CPen(mGetPenStyle(), mGetPenWidth(), m_DrawPenColor);
			pDC->SelectObject(pPen); // 选择直线笔

			//选入刷
			if (m_bDrawFill)
			{
				mCreateBrush();
				if (m_nDrawBrushStyle == DrawBrushImg)
				{
					pDC->SetBrushOrg(p0);
				}
				pDC->SelectObject(&m_Brush);
			}
			pDC->SetROP2(R2_COPYPEN); // 设置为覆盖绘图方式

			//绘制最终图案：
			pDC->Rectangle(min(p0.x, point.x), min(p0.y, point.y), max(p0.x, point.x), max(p0.y, point.y));
			
			m_bLButtonDown = FALSE; // 重设左鼠标键按下为假
			m_bErase = FALSE; // 重需要擦除为假
			break;
		case DrawGraphRorect:
			pDC->SelectStockObject(NULL_BRUSH);// 选入空刷
			rect = CRect(min(p0.x, pm.x), min(p0.y, pm.y), max(p0.x, pm.x), max(p0.y, pm.y));
			d = min(rect.Width(), rect.Height()) / 4;
			pDC->RoundRect(&rect, CPoint(d, d));

			//选入笔，设置绘图模式
			pPen->DeleteObject();
			pPen = new CPen(mGetPenStyle(), mGetPenWidth(), m_DrawPenColor);
			pDC->SelectObject(pPen); // 选择直线笔
			//选入刷
			if (m_bDrawFill)
			{
				mCreateBrush();
				if (m_nDrawBrushStyle == DrawBrushImg)
				{
					pDC->SetBrushOrg(p0);
				}
				pDC->SelectObject(&m_Brush);
			}
			pDC->SetROP2(R2_COPYPEN); // 设置为覆盖绘图方式

			rect = CRect(min(p0.x, point.x), min(p0.y, point.y), max(p0.x, point.x), max(p0.y, point.y));
			d = min(rect.Width(), rect.Height()) / 4;
			pDC->RoundRect(&rect, CPoint(d, d));

			m_bLButtonDown = FALSE; // 重设左鼠标键按下为假
			m_bErase = FALSE; // 重需要擦除为假
			break;
		case DrawGraphCircle:
			pDC->SelectStockObject(NULL_BRUSH);// 选入空刷
			r = max(pm.x - p0.x, pm.y - p0.y);
			pDC->Ellipse(p0.x, p0.y, p0.x + r, p0.y + r);

			pPen->DeleteObject();
			pPen = new CPen(mGetPenStyle(), mGetPenWidth(), m_DrawPenColor);
			pDC->SelectObject(pPen); // 选择直线笔
			//选入刷
			if (m_bDrawFill)
			{
				mCreateBrush();
				if (m_nDrawBrushStyle == DrawBrushImg)
				{
					pDC->SetBrushOrg(p0);
				}
				pDC->SelectObject(&m_Brush);
			}
			pDC->SetROP2(R2_COPYPEN); // 设置为覆盖绘图方式

			r = max(point.x - p0.x, point.y - p0.y);
			pDC->Ellipse(p0.x, p0.y, p0.x + r, p0.y + r);

			m_bLButtonDown = FALSE; // 重设左鼠标键按下为假
			m_bErase = FALSE; // 重需要擦除为假
			break;
		case DrawGraphEllipse:
			pDC->SelectStockObject(NULL_BRUSH);// 选入空刷
			pDC->Ellipse(min(p0.x, pm.x), min(p0.y, pm.y), max(p0.x, pm.x), max(p0.y, pm.y));

			pPen->DeleteObject();
			pPen = new CPen(mGetPenStyle(), mGetPenWidth(), m_DrawPenColor);
			pDC->SelectObject(pPen); // 选择直线笔
			//选入刷
			if (m_bDrawFill)
			{
				mCreateBrush();
				if (m_nDrawBrushStyle == DrawBrushImg)
				{
					pDC->SetBrushOrg(p0);
				}
				pDC->SelectObject(&m_Brush);
			}
			pDC->SetROP2(R2_COPYPEN); // 设置为覆盖绘图方式

			pDC->Ellipse(min(p0.x, point.x), min(p0.y, point.y), max(p0.x, point.x), max(p0.y, point.y));

			m_bLButtonDown = FALSE; // 重设左鼠标键按下为假
			m_bErase = FALSE; // 重需要擦除为假
			break;
		case DrawGraphPolyline:
			// pDC->SelectStockObject(NULL_BRUSH); // 选入空刷
			// 用于动态画封闭图形（如矩形、椭圆等）
			pDC->SelectObject(pGrayPen); // 选取灰色点线笔
			pDC->MoveTo(pPoly); pDC->LineTo(pm); // 擦除原直线

			pPen->DeleteObject();
			pPen = new CPen(mGetPenStyle(), mGetPenWidth(), m_DrawPenColor);
			pDC->SelectObject(pPen); // 选择直线笔
			pDC->SetROP2(R2_COPYPEN); // 设置为覆盖绘图方式

			pDC->MoveTo(pPoly); pDC->LineTo(point); // 绘制最终的直线

			m_bLButtonDown = FALSE; // 重设左鼠标键按下为假
			m_bErase = FALSE; // 重需要擦除为假
			break;
		case DrawGraphPolygon:
			break;
		case DrawGraphFont:
			pDC->SetTextColor(m_textColor);
			pDC->SetBkColor(m_textBackColor);
			pDC->TextOutW(point.x, point.y, m_textString);
			break;
		}	
	}
	ReleaseDC(pDC); // 释放设备上下文
	CView::OnLButtonUp(nFlags, point);
}

void CMFCDrawView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	ReleaseCapture(); // 释放鼠标捕获
	CDC* pDC = GetDC(); // 获取设备上下文
	pDC->SelectObject(pGrayPen); // 选入灰色点线笔
	pDC->SetROP2(R2_XORPEN); // 设置为异或绘图方式
	pDC->SetBkMode(TRANSPARENT); // 设置透明背景模式

		switch (m_nDrawGraph)
		{
		case DrawGraphPolyline:
			pDC->MoveTo(pPoly); pDC->LineTo(pm); // 擦除原直线

			pPen->DeleteObject();
			pPen = new CPen(mGetPenStyle(), mGetPenWidth(), m_DrawPenColor);
			pDC->SelectObject(pPen); // 选择直线笔
			pDC->SetROP2(R2_COPYPEN); // 设置为覆盖绘图方式

			pDC->MoveTo(pPoly); pDC->LineTo(point); // 绘制最终的直线

			m_bLButtonDown = FALSE; // 重设左鼠标键按下为假
			m_bErase = FALSE; // 重需要擦除为假
			m_bStart = FALSE; //设置折线结束
			break;
		case DrawGraphPolygon:
			break;
		}

	ReleaseDC(pDC); // 释放设备上下文
	CView::OnRButtonUp(nFlags, point);
}

void CMFCDrawView::OnDrawGraphLine()
{
	// TODO: Add your command handler code here
	if (m_nDrawGraph != DrawGraphLine)
	{
		m_nDrawGraph = DrawGraphLine;
	}
}


void CMFCDrawView::OnUpdateDrawGraphLine(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if (m_nDrawGraph == DrawGraphLine)
	{
		pCmdUI->SetCheck(true);
	}
	else
		pCmdUI->SetCheck(false);
}


void CMFCDrawView::OnDrawGraphRect()
{
	// TODO: Add your command handler code here
	if (m_nDrawGraph != DrawGraphRect)
	{
		m_nDrawGraph = DrawGraphRect;
	}
}


void CMFCDrawView::OnUpdateDrawGraphRect(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if (m_nDrawGraph == DrawGraphRect)
	{
		pCmdUI->SetCheck(true);
	}
	else
		pCmdUI->SetCheck(false);
}


void CMFCDrawView::OnDrawGraphRorect()
{
	// TODO: Add your command handler code here
	if (m_nDrawGraph != DrawGraphRorect)
	{
		m_nDrawGraph = DrawGraphRorect;
	}
}


void CMFCDrawView::OnUpdateDrawGraphRorect(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if (m_nDrawGraph == DrawGraphRorect)
	{
		pCmdUI->SetCheck(true);
	}
	else
		pCmdUI->SetCheck(false);
}


void CMFCDrawView::OnDrawGraphCircle()
{
	// TODO: Add your command handler code here
	if (m_nDrawGraph != DrawGraphCircle)
	{
		m_nDrawGraph = DrawGraphCircle;
	}
}


void CMFCDrawView::OnUpdateDrawGraphCircle(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if (m_nDrawGraph == DrawGraphCircle)
	{
		pCmdUI->SetCheck(true);
	}
	else
		pCmdUI->SetCheck(false);
}



void CMFCDrawView::OnDrawGraphEllipse()
{
	// TODO: Add your command handler code here
	if (m_nDrawGraph != DrawGraphEllipse)
	{
		m_nDrawGraph = DrawGraphEllipse;
	}
}



void CMFCDrawView::OnUpdateDrawGraphEllipse(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if (m_nDrawGraph == DrawGraphEllipse)
	{
		pCmdUI->SetCheck(true);
	}
	else
		pCmdUI->SetCheck(false);
}


void CMFCDrawView::OnDrawGraphPolyline()
{
	// TODO: Add your command handler code here
	if (m_nDrawGraph != DrawGraphPolyline)
	{
		m_nDrawGraph = DrawGraphPolyline;
	}
}


void CMFCDrawView::OnUpdateDrawGraphPolyline(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if (m_nDrawGraph == DrawGraphPolyline)
	{
		pCmdUI->SetCheck(true);
	}
	else
		pCmdUI->SetCheck(false);
}


void CMFCDrawView::OnDrawGraphPolygon()
{
	// TODO: Add your command handler code here
	if (m_nDrawGraph != DrawGraphPolygon)
	{
		m_nDrawGraph = DrawGraphPolygon;
	}
}


void CMFCDrawView::OnUpdateDrawGraphPolygon(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if (m_nDrawGraph == DrawGraphPolygon)
	{
		pCmdUI->SetCheck(true);
	}
	else
		pCmdUI->SetCheck(false);
}


void CMFCDrawView::OnDrawGraphFont()
{
	// TODO: Add your command handler code here
	if (m_nDrawGraph != DrawGraphFont)
	{
		m_nDrawGraph = DrawGraphFont;
	}
}


void CMFCDrawView::OnUpdateDrawGraphFont(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if (m_nDrawGraph == DrawGraphFont)
	{
		pCmdUI->SetCheck(true);
	}
	else
		pCmdUI->SetCheck(false);
}


void CMFCDrawView::OnDrawPenWidth1()
{
	// TODO: Add your command handler code here
	m_nDrawPenWidth = DrawPenWidth_1;
}




void CMFCDrawView::OnDrawPenWidth2()
{
	// TODO: Add your command handler code here
	m_nDrawPenWidth = DrawPenWidth_2;
}

void CMFCDrawView::OnDrawPenWidth4()
{
	// TODO: Add your command handler code here
	m_nDrawPenWidth = DrawPenWidth_4;
}

void CMFCDrawView::OnDrawPenWidth8()
{
	// TODO: Add your command handler code here
	m_nDrawPenWidth = DrawPenWidth_8;
}


void CMFCDrawView::OnDrawPenWidth10()
{
	// TODO: Add your command handler code here
	m_nDrawPenWidth = DrawPenWidth_10;
}

void CMFCDrawView::OnDrawPenWidth15()
{
	// TODO: Add your command handler code here
	m_nDrawPenWidth = DrawPenWidth_15;
}

void CMFCDrawView::OnDrawPenWidth20()
{
	// TODO: Add your command handler code here
	m_nDrawPenWidth = DrawPenWidth_20;
}


void CMFCDrawView::OnDrawPenWidth30()
{
	// TODO: Add your command handler code here
	m_nDrawPenWidth = DrawPenWidth_30;
}

void CMFCDrawView::OnDrawPenWidth50()
{
	// TODO: Add your command handler code here
	m_nDrawPenWidth = DrawPenWidth_50;
}

void CMFCDrawView::OnDrawPenWidth100()
{
	// TODO: Add your command handler code here
	m_nDrawPenWidth = DrawPenWidth_100;
}

void CMFCDrawView::OnDrawPenWidth200()
{
	// TODO: Add your command handler code here
	m_nDrawPenWidth = DrawPenWidth_200;
}

void CMFCDrawView::OnDrawPenSolidline()
{
	// TODO: Add your command handler code here
	if (m_nDrawPenStyle != DrawPenSolidLine)
	{
		m_nDrawPenStyle = DrawPenSolidLine;
	}
}



void CMFCDrawView::OnUpdateDrawPenSolidline(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if (m_nDrawPenStyle == DrawPenSolidLine)
	{
		pCmdUI->SetCheck(true);
	}
	else
		pCmdUI->SetCheck(false);
}




void CMFCDrawView::OnDrawPenDash()
{
	// TODO: Add your command handler code here
	if (m_nDrawPenStyle != DrawPenDash)
	{
		m_nDrawPenStyle = DrawPenDash;
	}

}


void CMFCDrawView::OnUpdateDrawPenDash(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if (m_nDrawPenStyle == DrawPenDash)
	{
		pCmdUI->SetCheck(true);
	}
	else
		pCmdUI->SetCheck(false);
}


void CMFCDrawView::OnDrawPenDot()
{
	// TODO: Add your command handler code here
	if (m_nDrawPenStyle != DrawPenDot)
	{
		m_nDrawPenStyle = DrawPenDot;
	}
}


void CMFCDrawView::OnUpdateDrawPenDot(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if (m_nDrawPenStyle == DrawPenDot)
	{
		pCmdUI->SetCheck(true);
	}
	else
		pCmdUI->SetCheck(false);
}


void CMFCDrawView::OnDrawPenDashdot()
{
	// TODO: Add your command handler code here
	if (m_nDrawPenStyle != DrawPenDashDot)
	{
		m_nDrawPenStyle = DrawPenDashDot;
	}
}


void CMFCDrawView::OnUpdateDrawPenDashdot(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if (m_nDrawPenStyle == DrawPenDashDot)
	{
		pCmdUI->SetCheck(true);
	}
	else
		pCmdUI->SetCheck(false);
}


void CMFCDrawView::OnDrawPenDashdotdot()
{
	// TODO: Add your command handler code here
	if (m_nDrawPenStyle != DrawPenDashDotDot)
	{
		m_nDrawPenStyle = DrawPenDashDotDot;
	}
}


void CMFCDrawView::OnUpdateDrawPenDashdotdot(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if (m_nDrawPenStyle == DrawPenDashDotDot)
	{
		pCmdUI->SetCheck(true);
	}
	else
		pCmdUI->SetCheck(false);
}


void CMFCDrawView::OnDrawBrushNull()
{
	// TODO: Add your command handler code here
	if (m_nDrawBrushStyle != DrawBrushNull)
	{
		m_nDrawBrushStyle = DrawBrushNull;
	}
}


void CMFCDrawView::OnUpdateDrawBrushNull(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if (m_nDrawBrushStyle == DrawBrushNull)
	{
		pCmdUI->SetCheck(true);
	}
	else
		pCmdUI->SetCheck(false);
}


void CMFCDrawView::OnDrawBrushSolid()
{
	// TODO: Add your command handler code here
	if (m_nDrawBrushStyle != DrawBrushSolid)
	{
		m_nDrawBrushStyle = DrawBrushSolid;
	}
}


void CMFCDrawView::OnUpdateDrawBrushSolid(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if (m_nDrawBrushStyle == DrawBrushSolid)
	{
		pCmdUI->SetCheck(true);
	}
	else
		pCmdUI->SetCheck(false);
}


void CMFCDrawView::OnDrawBrushHorizon()
{
	// TODO: Add your command handler code here
	if (m_nDrawBrushStyle != DrawBrushHorizon)
	{
		m_nDrawBrushStyle = DrawBrushHorizon;
	}
}


void CMFCDrawView::OnUpdateDrawBrushHorizon(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if (m_nDrawBrushStyle == DrawBrushHorizon)
	{
		pCmdUI->SetCheck(true);
	}
	else
		pCmdUI->SetCheck(false);
}



void CMFCDrawView::OnDrawBrushVertical()
{
	// TODO: Add your command handler code here
	if (m_nDrawBrushStyle != DrawBrushVertical)
	{
		m_nDrawBrushStyle = DrawBrushVertical;
	}
}


void CMFCDrawView::OnUpdateDrawBrushVertical(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if (m_nDrawBrushStyle == DrawBrushVertical)
	{
		pCmdUI->SetCheck(true);
	}
	else
		pCmdUI->SetCheck(false);
}


void CMFCDrawView::OnDrawBrushFdiagonal()
{
	// TODO: Add your command handler code here
	if (m_nDrawBrushStyle != DrawBrushFdiagonal)
	{
		m_nDrawBrushStyle = DrawBrushFdiagonal;
	}
}


void CMFCDrawView::OnUpdateDrawBrushFdiagonal(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if (m_nDrawBrushStyle == DrawBrushFdiagonal)
	{
		pCmdUI->SetCheck(true);
	}
	else
		pCmdUI->SetCheck(false);
}


void CMFCDrawView::OnDrawBrushBdiagonal()
{
	// TODO: Add your command handler code here
	if (m_nDrawBrushStyle != DrawBrushBdiagonal)
	{
		m_nDrawBrushStyle = DrawBrushBdiagonal;
	}
}


void CMFCDrawView::OnUpdateDrawBrushBdiagonal(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if (m_nDrawBrushStyle == DrawBrushBdiagonal)
	{
		pCmdUI->SetCheck(true);
	}
	else
		pCmdUI->SetCheck(false);
}


void CMFCDrawView::OnDrawBrushCross()
{
	// TODO: Add your command handler code here
	if (m_nDrawBrushStyle != DrawBrushCross)
	{
		m_nDrawBrushStyle = DrawBrushCross;
	}
}


void CMFCDrawView::OnUpdateDrawBrushCross(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if (m_nDrawBrushStyle == DrawBrushCross)
	{
		pCmdUI->SetCheck(true);
	}
	else
		pCmdUI->SetCheck(false);
}


void CMFCDrawView::OnDrawBrushDiagcross()
{
	// TODO: Add your command handler code here
	if (m_nDrawBrushStyle != DrawBrushDiagcross)
	{
		m_nDrawBrushStyle = DrawBrushDiagcross;
	}
}


void CMFCDrawView::OnUpdateDrawBrushDiagcross(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if (m_nDrawBrushStyle == DrawBrushDiagcross)
	{
		pCmdUI->SetCheck(true);
	}
	else
		pCmdUI->SetCheck(false);
}


void CMFCDrawView::OnDrawBrushGraph()
{
	// TODO: Add your command handler code here
	if (m_nDrawBrushStyle != DrawBrushImg)
	{
		m_nDrawBrushStyle = DrawBrushImg;
	}
}


void CMFCDrawView::OnUpdateDrawBrushGraph(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if (m_nDrawBrushStyle == DrawBrushImg)
	{
		pCmdUI->SetCheck(true);
	}
	else
		pCmdUI->SetCheck(false);
}


void CMFCDrawView::OnDrawFill()
{
	// TODO: Add your command handler code here
	if (m_bDrawFill == true)
	{
		m_bDrawFill = false;
	}
	else
		m_bDrawFill = true;
}


void CMFCDrawView::OnUpdateDrawFill(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_bDrawFill);
}


void CMFCDrawView::OnDrawClear()
{
	// TODO: Add your command handler code here
	RedrawWindow();
}


void CMFCDrawView::OnDrawPenColor()
{
	// TODO: Add your command handler code here
	CColorDialog colDlg(m_DrawPenColor, CC_FULLOPEN);
	if (colDlg.DoModal() == IDOK)
		m_DrawPenColor = colDlg.GetColor();

}


void CMFCDrawView::OnDrawBrushColor()
{
	// TODO: Add your command handler code here
	CColorDialog colDlg(m_DrawBrushColor, CC_FULLOPEN);
	if (colDlg.DoModal() == IDOK)
		m_DrawBrushColor = colDlg.GetColor();
}
HBITMAP CMFCDrawView::CopyBitmap(HBITMAP hSourceHbitmap)
{
	CDC sourceDC;
	CDC destDC;
	sourceDC.CreateCompatibleDC(NULL);
	destDC.CreateCompatibleDC(NULL);
	//The bitmap information.
	BITMAP bm = { 0 };
	//Get the bitmap information.
	::GetObject(hSourceHbitmap, sizeof(bm), &bm); 
	//Create a bitmap to hold the result
	CBitmap destbitmap;
	HBITMAP hbmResult;
	destbitmap.CreateCompatibleBitmap(&sourceDC, bm.bmWidth, bm.bmHeight);
	hbmResult = (HBITMAP)destbitmap.GetSafeHandle();
	//HBITMAP hbmOldSource = (HBITMAP)::SelectObject(sourceDC.m_hDC, hSourceHbitmap);
	HBITMAP hbmOldDest = (HBITMAP)::SelectObject(destDC.m_hDC, hbmResult);
	destDC.BitBlt(0, 0, bm.bmWidth, bm.bmHeight, &sourceDC, 0, 0, SRCCOPY);
	// Restore DCs
	//::SelectObject(sourceDC.m_hDC, hbmOldSource);
	::SelectObject(destDC.m_hDC, hbmOldDest);
	//::DeleteObject(sourceDC.m_hDC);
	::DeleteObject(destDC.m_hDC);

	return hbmResult;
}

void CMFCDrawView::OnDrawSet()
{
	// TODO: Add your command handler code here
	CDrawSetDlg m_DrawSetDlg;
	m_DrawSetDlg.m_Graph = m_nDrawGraph;
	//笔的数值进行传回
	m_DrawSetDlg.m_iPenWidth = m_nDrawPenWidth;
	m_DrawSetDlg.m_sPenStyle = m_nDrawPenStyle;
	m_DrawSetDlg.m_cPenColor = m_DrawPenColor;
	//刷的数值进行传回
	m_DrawSetDlg.m_BrushStyle = m_nDrawBrushStyle;
	m_DrawSetDlg.m_BrushColor = m_DrawBrushColor;
	m_DrawSetDlg.m_bCheckFill = m_bDrawFill;
	//图案路径数据传回
	m_DrawSetDlg.m_StrBitmapPath = m_StrBitmapPath;

	INT_PTR nRes;
	nRes = m_DrawSetDlg.DoModal();
	if (nRes == IDOK)
	{
		//m_DrawSetDlg.UpdateData(TRUE);
		m_nDrawGraph = m_DrawSetDlg.m_Graph;
		m_nDrawPenWidth = m_DrawSetDlg.m_iPenWidth;
		m_nDrawPenStyle = m_DrawSetDlg.m_sPenStyle;
		m_DrawPenColor = m_DrawSetDlg.m_cPenColor;

		m_DrawBrushColor = m_DrawSetDlg.m_BrushColor;
		m_nDrawBrushStyle = m_DrawSetDlg.m_BrushStyle;
		m_bDrawFill = m_DrawSetDlg.m_bCheckFill;

		m_StrBitmapPath = m_DrawSetDlg.m_StrBitmapPath;
		HBITMAP hBmp = (HBITMAP)LoadImageW(NULL, m_StrBitmapPath,
			IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_DEFAULTCOLOR |
			LR_DEFAULTSIZE); // 装入位图文件，获取位图句柄
		if (hBmp != NULL){
			m_Bitmap.DeleteObject();
			m_Bitmap.Attach(hBmp);
		}
	}
}


void CMFCDrawView::OnDrawBrushChange()
{
	// TODO: Add your command handler code here
	CChangeBitmap ChangeBitmap;
	ChangeBitmap.m_StrBitmapPath = m_StrBitmapPath;
	INT_PTR nRes;
	nRes = ChangeBitmap.DoModal();

	if (nRes == IDOK)
	{
		m_StrBitmapPath = ChangeBitmap.m_StrBitmapPath;
		HBITMAP hBmp = (HBITMAP)LoadImageW(NULL, m_StrBitmapPath,
			IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_DEFAULTCOLOR |
			LR_DEFAULTSIZE); // 装入位图文件，获取位图句柄
		if (hBmp != NULL){
			m_Bitmap.DeleteObject();
			m_Bitmap.Attach(hBmp);
		}
	}
}


void CMFCDrawView::OnFontChoose()
{
	// TODO: Add your command handler code here
	CFontDialog fontDlg(&m_logFont);
	fontDlg.m_cf.rgbColors = m_textColor;
	if (fontDlg.DoModal() == IDOK) {
		wcscpy_s(m_fontName, LF_FACESIZE, fontDlg.GetFaceName());
		m_iFontSize = fontDlg.GetSize();
		m_textColor = fontDlg.GetColor();
		m_bItalic = fontDlg.IsItalic();
		m_bBold = fontDlg.IsBold();
		m_bStrikeOut = fontDlg.IsStrikeOut();
		m_bUnderline = fontDlg.IsUnderline();
	}
	RedrawWindow(); // 重绘窗口（请求调用OnDraw）

}


void CMFCDrawView::OnFontColor()
{
	// TODO: Add your command handler code here
	CSetFontColor SetFontColor;
	SetFontColor.m_textColor = m_textColor;
	SetFontColor.m_textBackColor = m_textBackColor;
	INT_PTR nRes;
	nRes = SetFontColor.DoModal();

	if (nRes == IDOK)
	{
		m_textColor = SetFontColor.m_textColor;
		m_textBackColor = SetFontColor.m_textBackColor;
	}
}


void CMFCDrawView::OnFontIntputstr()
{
	// TODO: Add your command handler code here
	CSetFontString SetFontString;
	SetFontString.m_textString = m_textString;
	INT_PTR nRes;
	nRes = SetFontString.DoModal();

	if (nRes == IDOK)
	{
		m_textString = SetFontString.m_textString;
	}
}


void CMFCDrawView::OnFontOutputstr()
{
	// TODO: Add your command handler code here
	m_nDrawGraph = DrawGraphFont;
}

CString CMFCDrawView::GetFontNumber(int size)
{
	switch (size) {
	case 420: return L"初号";
	case 360: return L"小初";
	case 260: return L"一号";
	case 240: return L"小一";
	case 220: return L"二号";
	case 180: return L"小二";
	case 160: return L"三号";
	case 150: return L"小三";
	case 140: return L"四号";
	case 120: return L"小四";
	case 105: return L"五号";
	case  90: return L"小五";
	case  75: return L"六号";
	case  65: return L"小六";
	case  55: return L"七号";
	case  50: return L"八号";
	}
	return L"未知";

}

void CMFCDrawView::OnFontSize()
{
	// TODO: Add your command handler code here
	CFont font;
	CDC* pDC = GetDC();
	int iSize, y = 0; // 定义字体大小变量和垂直坐标变量
	// 定义对应于汉字字号的nPointSize值数组
	int fs[16] = { 420, 360, 260, 240, 220, 180, 160, 150, 140, 120,
		105, 90, 75, 65, 55, 50 };
	wchar_t buf[40]; // 定义字符串缓冲区
	// 定义字号与字体名称的字符串对象
	CString sFontNum;
	for (int i = 0; i < 16; i++) { // 字号循环
		iSize = fs[i]; // 获取当前字号的nPointSize值
		font.CreatePointFont(iSize, m_fontName); // 创建字体对象
		pOldFont = pDC->SelectObject(&font); // 选入字体对象
		sFontNum = GetFontNumber(iSize); // 获取当前字号
		swprintf_s(buf, 40, L"这是%s%s字(%g磅)", m_fontName,
			sFontNum, iSize / 10.0); // 生成输出的字符串
		pDC->TextOut(0, y, buf); // 输出字符串
		pDC->SelectObject(pOldFont); // 选出字体
		font.DeleteObject(); // 删除字体对象
		y += fs[i] / 6; // 更新y值
	}
	ReleaseDC(pDC);
}

BOOL CMFCDrawView::SetMyFont(CDC *pDC, LPCTSTR name, int size,
	COLORREF col, int angle, BOOL italic, BOOL bold,
	BOOL underline, BOOL strikeOut)
{
	int height = -MulDiv(size, pDC->GetDeviceCaps(LOGPIXELSY), 720);
	CFont font; // m_font.DeleteObject(); 并用m_font代替font：
	BOOL bOk = font.CreateFont(height, 0, angle, angle,
		bold ? 700 : 400, italic, underline, strikeOut,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_PITCH | FF_DONTCARE, name);
	if (bOk) {
		//font.GetLogFont(&m_logFont);
		pDC->SelectObject(font);
		pDC->SetTextColor(col);
	}
	return bOk;

}

void CMFCDrawView::OnFontRotate()
{
	// TODO: Add your command handler code here
	CDC *pDC = GetDC();
	RECT rect;
	GetClientRect(&rect);
	wchar_t buf[40]; // 定义字符串缓冲区
	// 定义字号与字体名称的字符串对象
	CString sFontNum;
	for (int angle = 0; angle <= 360; angle += 10) {
		sFontNum = GetFontNumber(m_iFontSize); // 获取当前字号
		SetMyFont(pDC, m_fontName, m_iFontSize, m_textColor, angle * 10, m_bItalic, m_bBold, m_bUnderline, m_bStrikeOut);
		swprintf_s(buf, 40, L"字体:名称=%s,字号=%s,大小=%g磅", m_fontName,
			sFontNum, m_iFontSize / 10.0); // 生成输出的字符串
		pDC->TextOutW(rect.right / 2, rect.bottom / 2, buf); // 输出字符串
	}
	ReleaseDC(pDC);

}


void CMFCDrawView::OnDrawPenWidthN()
{
	// TODO: Add your command handler code here
	CSetPenWidth SetPenWidth;
	SetPenWidth.m_PenWidth = m_nDrawPenWidth;
	INT_PTR nRes;
	nRes = SetPenWidth.DoModal();

	if (nRes == IDOK)
	{
		m_nDrawPenWidth = SetPenWidth.m_PenWidth;
	}
}


void CMFCDrawView::OnBmpRotation()
{
	// TODO: Add your command handler code here
	
	CDC *pDC = GetDC();
	Graphics graph(pDC->m_hDC);
	graph.RotateTransform(30.0f);
	
	CMFCDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (!pDoc->ImagePath.IsEmpty()){
		Image Rotation_img(pDoc->ImagePath);

		int width = Rotation_img.GetWidth();
		int height = Rotation_img.GetHeight();
		graph.DrawImage(&Rotation_img, 400, 0, width, height);
	}




	ReleaseDC(pDC);
}


void CMFCDrawView::OnBitmapGray()
{
	// TODO: Add your command handler code here
	Color col;
	BYTE val;
	CDC *pDC = GetDC();
	Graphics graph(pDC->m_hDC);
	
	CMFCDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (!pDoc->ImagePath.IsEmpty()){
		Gdiplus::Bitmap img(pDoc->ImagePath);
		int w = img.GetWidth();
		int h = img.GetHeight();

		Gdiplus::Bitmap *pImg = new Gdiplus::Bitmap(w, h, PixelFormat32bppARGB);
		for (int i = 0; i < w; i++){
			for (int j = 0; j < h; j++){
				img.GetPixel(i, j, &col);
				val = BYTE(0.299f * col.GetR() + 0.587f * col.GetG() + 0.114 * col.GetB());
				col.SetValue(col.MakeARGB(255, val, val, val));
				pImg->SetPixel(i, j, col);
			}
		}
		graph.DrawImage(pImg, PointF(w + 10, 0));
	}
}


void CMFCDrawView::OnBitmapNegative()
{
	// TODO: Add your command handler code here
	Color col;
	BYTE r, g, b;
	CDC *pDC = GetDC();
	Graphics graph(pDC->m_hDC);

	CMFCDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (!pDoc->ImagePath.IsEmpty()){
		Gdiplus::Bitmap img(pDoc->ImagePath);
		int w = img.GetWidth();
		int h = img.GetHeight();

		Gdiplus::Bitmap *pImg = new Gdiplus::Bitmap(w, h, PixelFormat32bppARGB);
		for (int i = 0; i < w; i++) {
			for (int j = 0; j < h; j++) {
				img.GetPixel(i, j, &col);
				r = 255 - col.GetR();
				g = 255 - col.GetG();
				b = 255 - col.GetB();
				col.SetValue(col.MakeARGB(255, r, g, b));
				pImg->SetPixel(i, j, col);
			}
		}

		graph.DrawImage(pImg, PointF(2 * w + 10, 0));
	}
}


void CMFCDrawView::OnBitmapWoodcut()
{
	// TODO: Add your command handler code here
	Color col;
	BYTE r, g, b;
	BYTE val;
	int avg;
	CDC *pDC = GetDC();
	Graphics graph(pDC->m_hDC);

	CMFCDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (!pDoc->ImagePath.IsEmpty()){
		Gdiplus::Bitmap img(pDoc->ImagePath);
		int w = img.GetWidth();
		int h = img.GetHeight();

		Gdiplus::Bitmap *pImg = new Gdiplus::Bitmap(w, h, PixelFormat32bppARGB);
		for (int i = 0; i < w; i++) {
			for (int j = 0; j < h; j++) {
				img.GetPixel(i, j, &col);
				avg = int(0.299f * col.GetR() + 0.587f * col.GetG() +
					0.114 * col.GetB());
				//avg = int((col.GetR() + col.GetG() + col.GetB()) / 3);
				if (avg >= 128) val = 255; else val = 0;
				col.SetValue(col.MakeARGB(255, val, val, val));
				pImg->SetPixel(i, j, col);
			}
		}


		graph.DrawImage(pImg, PointF(2 * w + 10, 0));
	}
}


void CMFCDrawView::OnBitmapCarve()
{
	// TODO: Add your command handler code here
	Color col, collt;
	BYTE r, g, b;
	BYTE val;
	int avg;
	CDC *pDC = GetDC();
	Graphics graph(pDC->m_hDC);

	CMFCDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (!pDoc->ImagePath.IsEmpty()){
		Gdiplus::Bitmap img(pDoc->ImagePath);
		int w = img.GetWidth();
		int h = img.GetHeight();

		Gdiplus::Bitmap *pImg = new Gdiplus::Bitmap(w-1, h-1, PixelFormat32bppARGB);
		for (int i = 1; i < w; i++) {
			for (int j = 1; j < h; j++) {
				img.GetPixel(i, j, &col);
				img.GetPixel(i - 1, j - 1, &collt);
				r = BYTE(max(67, min(255, abs(col.GetR() - collt.GetR()
					+ 128))));
				g = BYTE(max(67, min(255, abs(col.GetG() - collt.GetG()
					+ 128))));
				b = BYTE(max(67, min(255, abs(col.GetB() - collt.GetB()
					+ 128))));
				col.SetValue(col.MakeARGB(255, r, g, b));
				pImg->SetPixel(i - 1, j - 1, col);
			}
		}



		graph.DrawImage(pImg, PointF(w + 10, 0));
	}
}


void CMFCDrawView::OnBitmapRelievo()
{
	// TODO: Add your command handler code here
	Color col, collt;
	BYTE r, g, b;
	BYTE val;
	int avg;
	CDC *pDC = GetDC();
	Graphics graph(pDC->m_hDC);

	CMFCDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (!pDoc->ImagePath.IsEmpty()){
		Gdiplus::Bitmap img(pDoc->ImagePath);
		int w = img.GetWidth();
		int h = img.GetHeight();

		Gdiplus::Bitmap *pImg = new Gdiplus::Bitmap(w - 1, h - 1, PixelFormat32bppARGB);
		for (int i = 1; i < w; i++) {
			for (int j = 1; j < h; j++) {
				img.GetPixel(i, j, &col);
				img.GetPixel(i - 1, j - 1, &collt);
				r = BYTE(max(67, min(255, abs(collt.GetR() - col.GetR()
					+ 128))));
				g = BYTE(max(67, min(255, abs(collt.GetG() - col.GetG()
					+ 128))));
				b = BYTE(max(67, min(255, abs(collt.GetB() - col.GetB()
					+ 128))));
				col.SetValue(col.MakeARGB(255, r, g, b));
				pImg->SetPixel(i - 1, j - 1, col);
			}
		}




		graph.DrawImage(pImg, PointF(2 *w + 10, 0));
	}
}
