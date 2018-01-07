#pragma once


// CSetFontColor dialog

class CSetFontColor : public CDialogEx
{
	DECLARE_DYNAMIC(CSetFontColor)

public:
	CSetFontColor(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSetFontColor();

// Dialog Data
	enum { IDD = IDD_DIALOG_SET_TEXT_COLOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	COLORREF m_textColor;
	COLORREF m_textBackColor;
public:
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButtonFrontColorFont();
	afx_msg void OnBnClickedButtonBackColorFont();
};
