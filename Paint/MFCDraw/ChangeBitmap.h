#pragma once


// CChangeBitmap dialog

class CChangeBitmap : public CDialogEx
{
	DECLARE_DYNAMIC(CChangeBitmap)

public:
	CChangeBitmap(CWnd* pParent = NULL);   // standard constructor
	virtual ~CChangeBitmap();

// Dialog Data
	enum { IDD = IDD_DIALOG_CHANGE_BITMAP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CBitmap m_Bitmap;
	CString m_StrBitmapPath;


public:
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButtonOpen();
};
