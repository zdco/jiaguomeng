// SuperLinkCtrl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SuperLinkCtrl.h"


// CSuperLinkCtrl

IMPLEMENT_DYNAMIC(CSuperLinkCtrl, CStatic)

// CSuperLinkCtrl ��Ϣ�������

CSuperLinkCtrl::CSuperLinkCtrl()
{
	m_bClicked=FALSE;     
	m_bcaptured=FALSE;
	m_clickedtextcor=RGB(0,0,255);
	m_moveontextcor=RGB(255,0,0);
	m_ordinarytextcor=RGB(0,0,255);
	m_crText=m_ordinarytextcor;    
	// ���ó�ʼ��������ɫ
	::GetObject((HFONT)GetStockObject(DEFAULT_GUI_FONT),sizeof(m_lf),&m_lf); 
	m_hCursor=NULL;       
}

CSuperLinkCtrl::CSuperLinkCtrl(COLORREF clickedtextcor,COLORREF moveontextcor,COLORREF ordinarytextcor)
{
	m_bClicked=FALSE;
	m_bcaptured=FALSE;
	m_clickedtextcor=clickedtextcor;
	m_moveontextcor=moveontextcor;
	m_ordinarytextcor=ordinarytextcor;
	m_crText=m_ordinarytextcor;       
	// ���ó�ʼ��������ɫ
	::GetObject((HFONT)GetStockObject(DEFAULT_GUI_FONT),sizeof(m_lf),&m_lf); 
	m_hCursor=NULL;
}

//���������������ɾ������Ĺ��캯���д���������
CSuperLinkCtrl::~CSuperLinkCtrl()
{
	m_font.DeleteObject();   
	//ɾ������Ĺ��캯���д���������
}

//��classwizardΪ�����������Ϣӳ�䲢��д��Ϣӳ�亯��
BEGIN_MESSAGE_MAP(CSuperLinkCtrl, CStatic)
	//{{AFX_MSG_MAP(CSuperLinkCtrl)
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_LBUTTONDOWN()
	ON_WM_SETCURSOR()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//��д��Ϣӳ�亯��CtlColor()����ʵ�ֳ������ı���ɫ�ı仯
HBRUSH CSuperLinkCtrl::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	// TODO: Change any attributes of the DC here
	if (CTLCOLOR_STATIC == nCtlColor)
	{
		pDC->SelectObject(&m_font);
		pDC->SetTextColor(m_crText);
		pDC->SetBkMode(TRANSPARENT);
	}
	HBRUSH hBrush = ::CreateSolidBrush(GetSysColor(COLOR_3DFACE));  //����һ��ˢ�Ӿ��
	return hBrush;  // ����һ���������ؼ�������ˢ�Ӿ��
}

//ʵ����갴�������Ϣ
void CSuperLinkCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_bClicked=TRUE;         
	m_crText=m_clickedtextcor;  //���ó������ı�����ɫ
	RedrawWindow();    // �ػ��ؼ�ʵ�ֳ������ı���ɫ�ı仯
	if(m_linktext!=_T(""))  
		//��������˳����ӵĵ�ַ�����ShellExecute����ʵ�ֳ�����
		ShellExecute(NULL, _T("open"), m_linktext, NULL, NULL, SW_SHOWNORMAL);  
	CStatic::OnLButtonDown(nFlags, point);
	// ���û�����Ӧ����
}

//���ó������ı��ϵ������״����Ϣӳ�亯��
BOOL CSuperLinkCtrl::OnSetCursor(CWnd* pWnd, 
								 UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_hCursor)   // �����ȡ�ù�����������µ������״
	{
		::SetCursor(m_hCursor);
		return TRUE;
	}
	return CStatic::OnSetCursor(pWnd, nHitTest, message);
}

//���ó������ı��ϵĹ����
void CSuperLinkCtrl::SetLinkCursor(HCURSOR hCursor)
{
	m_hCursor = hCursor;
}

//��Ӧ����ƶ���Ϣ
void CSuperLinkCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	SetCapture();     // ��׽���
	POINT mpoint;   
	GetCursorPos(&mpoint);  // ȡ�õ�ǰ���λ��
	CRect rect;
	GetWindowRect(&rect);  // ȡ�ÿؼ��Ĵ��ڴ�С
	if(!rect.PtInRect(mpoint)) // �ж�����Ƿ��ڿؼ��Ĵ�����
	{             // ��겻�ڿؼ��Ĵ�����
		m_bcaptured=FALSE;
		ReleaseCapture();    // �ͷ���겶׽
		MouseLeave(); //  ����mouseleave()����
		return;
	} 
	// ����ڿؼ��Ĵ�����
	if(m_bcaptured)  // �������ڴ��������Ѿ�����׽�򷵻�
		return;
	m_bcaptured=TRUE;
	MouseEnter();   //����MouseEnter()����
	ReleaseCapture(); // �ͷ���겶׽
	CStatic::OnMouseMove(nFlags, point); // ���û�����Ӧ����
}

//��MouseEnter()��MouseLeave()
//������������������뿪ʱ�ĳ������ı�����ɫ
void CSuperLinkCtrl::MouseEnter()
{
	m_crText=m_bClicked? m_clickedtextcor : m_moveontextcor;
	RedrawWindow();    // �ػ��ؼ�ʵ�ֳ������ı���ɫ�ı仯
}

void CSuperLinkCtrl::MouseLeave()
{
	m_crText=m_bClicked? m_clickedtextcor : m_ordinarytextcor;
	RedrawWindow();   // �ػ��ؼ�ʵ�ֳ������ı���ɫ�ı仯
}

//��SetLinkAddress()���������ó����ӵ���ַ
BOOL CSuperLinkCtrl::SetLinkAddress(CString linkaddress)
{   // ��֤��ַ�ĺϷ���
	if(linkaddress.Find(_T("http"))!=-1)
		m_linktext=linkaddress;
	else if(linkaddress.Find(_T("@"))!=-1)
		m_linktext=_T("mailto:")+linkaddress;
	else
	{
		MessageBox(_T("Error: wrong superlink format"));
		m_linktext=_T("");
		return FALSE;
	}
	return TRUE;
}
//---- ����static�ؼ�������Ӧ�����Ϣ�����Ի�������������������Щ�޸ġ����溯����ʹstatic�ؼ�����Ӧ�����Ϣ�Ĺؼ�����Ϊͨ��static�ؼ�ֻ����Ӧ����һ������Ϣ��

void CSuperLinkCtrl::SetSuperLink(BOOL setlink)
{
	if (setlink)   // �˴��������ModifyStyle()��
		//ʹstatic�ؼ�����Ӧ�����Ϣ
		ModifyStyle(0,SS_NOTIFY);
	else
		ModifyStyle(SS_NOTIFY,0);
}

void CSuperLinkCtrl::SetUnderLine(BOOL bUnderLine = TRUE)
{	
	//ȡ�õ�ǰ��ȱʡ����
	m_lf.lfUnderline = bUnderLine;  
	//Ϊ��ǰȱʡ��������»���
	BOOL bCreated = m_font.CreateFontIndirect(&m_lf); 
	// ��������������
	ASSERT(bCreated);
}