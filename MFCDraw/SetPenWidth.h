#pragma once


// CSetPenWidth dialog

class CSetPenWidth : public CDialogEx
{
	DECLARE_DYNAMIC(CSetPenWidth)

public:
	CSetPenWidth(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSetPenWidth();

// Dialog Data
	enum { IDD = IDD_DIALOG_SET_PEN_WIDTH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int m_PenWidth;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
