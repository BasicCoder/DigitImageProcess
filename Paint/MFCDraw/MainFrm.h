
// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once
enum SBID{prompt, xName, xVal, yName, yVal, dxName, dxVal, dyName, dyVal};
class CMainFrame : public CFrameWnd
{
	
protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:  // �ؼ���Ƕ���Ա
	CToolBar          m_wndToolBar;
	

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
public:
	CToolBar		m_ToolBar;
	CStatusBar        m_wndStatusBar;
};


