
// MFCDraw.h : MFCDraw Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMFCDrawApp:
// �йش����ʵ�֣������ MFCDraw.cpp
//

class CMFCDrawApp : public CWinApp
{
public:
	CMFCDrawApp();
public:
	ULONG_PTR m_gdiplusToken;

// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCDrawApp theApp;
