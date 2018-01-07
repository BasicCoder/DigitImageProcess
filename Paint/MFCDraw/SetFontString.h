#pragma once


// CSetFontString dialog

class CSetFontString : public CDialogEx
{
	DECLARE_DYNAMIC(CSetFontString)

public:
	CSetFontString(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSetFontString();

// Dialog Data
	enum { IDD = IDD_DIALOG_INTPUT_STRING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_textString;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
