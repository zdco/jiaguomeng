#pragma once


// CSuperLinkCtrl

class CSuperLinkCtrl : public CStatic
{
	DECLARE_DYNAMIC(CSuperLinkCtrl)
	// Construction
public:
	CSuperLinkCtrl();
	CSuperLinkCtrl(COLORREF clickedtextcor,COLORREF moveontextcor,COLORREF ordinarytextcor);
	// Attributes
public:
	COLORREF m_crText;   //超联接文本的颜色
	// Operations
public:
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSuperLinkCtrl)
	//}}AFX_VIRTUAL

	// Implementation
public:
	BOOL SetLinkAddress(CString linkaddress); 
	//用于设置超联接的地址
	void MouseLeave(void);
	void MouseEnter(void);
	void SetLinkCursor(HCURSOR hCursor); 
	//用于设置超联接的鼠标形状
	void SetSuperLink(BOOL setlink);
	virtual ~CSuperLinkCtrl();

	void SetUnderLine(BOOL bUnderline /*=TRUE*/);

	// Generated message map functions
protected:
	CString m_linktext;  // shell 调用的联接参数
	BOOL m_bClicked;    // 鼠标是否单击超联接
	HCURSOR m_hCursor;  // 鼠标移动到超联接上时的鼠标形状
	//{{AFX_MSG(CSuperLinkCtrl)
	afx_msg HBRUSH CtlColor(CDC* pDC, 
		UINT nCtlColor);
	afx_msg void OnLButtonDown(UINT
		nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, 
		UINT nHitTest, UINT message);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bcaptured;             //捕捉鼠标移动
	COLORREF m_clickedtextcor;    //单击超联接后文本的颜色
	COLORREF m_moveontextcor;    //鼠标移动到超联接时的文本的颜色
	COLORREF m_ordinarytextcor;   //未激活超联接时文本的颜色
	LOGFONT		m_lf;          
	CFont		m_font;      //超联接上的文本的字体
};