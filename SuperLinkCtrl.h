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
	COLORREF m_crText;   //�������ı�����ɫ
	// Operations
public:
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSuperLinkCtrl)
	//}}AFX_VIRTUAL

	// Implementation
public:
	BOOL SetLinkAddress(CString linkaddress); 
	//�������ó����ӵĵ�ַ
	void MouseLeave(void);
	void MouseEnter(void);
	void SetLinkCursor(HCURSOR hCursor); 
	//�������ó����ӵ������״
	void SetSuperLink(BOOL setlink);
	virtual ~CSuperLinkCtrl();

	void SetUnderLine(BOOL bUnderline /*=TRUE*/);

	// Generated message map functions
protected:
	CString m_linktext;  // shell ���õ����Ӳ���
	BOOL m_bClicked;    // ����Ƿ񵥻�������
	HCURSOR m_hCursor;  // ����ƶ�����������ʱ�������״
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
	BOOL m_bcaptured;             //��׽����ƶ�
	COLORREF m_clickedtextcor;    //���������Ӻ��ı�����ɫ
	COLORREF m_moveontextcor;    //����ƶ���������ʱ���ı�����ɫ
	COLORREF m_ordinarytextcor;   //δ�������ʱ�ı�����ɫ
	LOGFONT		m_lf;          
	CFont		m_font;      //�������ϵ��ı�������
};