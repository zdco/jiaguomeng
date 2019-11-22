// SuperLinkCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "SuperLinkCtrl.h"


// CSuperLinkCtrl

IMPLEMENT_DYNAMIC(CSuperLinkCtrl, CStatic)

// CSuperLinkCtrl 消息处理程序

CSuperLinkCtrl::CSuperLinkCtrl()
{
	m_bClicked=FALSE;     
	m_bcaptured=FALSE;
	m_clickedtextcor=RGB(0,0,255);
	m_moveontextcor=RGB(255,0,0);
	m_ordinarytextcor=RGB(0,0,255);
	m_crText=m_ordinarytextcor;    
	// 设置初始化字体颜色
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
	// 设置初始化字体颜色
	::GetObject((HFONT)GetStockObject(DEFAULT_GUI_FONT),sizeof(m_lf),&m_lf); 
	m_hCursor=NULL;
}

//在类的析构函数中删除在类的构造函数中创建的字体
CSuperLinkCtrl::~CSuperLinkCtrl()
{
	m_font.DeleteObject();   
	//删除在类的构造函数中创建的字体
}

//用classwizard为类加入如下消息映射并编写消息映射函数
BEGIN_MESSAGE_MAP(CSuperLinkCtrl, CStatic)
	//{{AFX_MSG_MAP(CSuperLinkCtrl)
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_LBUTTONDOWN()
	ON_WM_SETCURSOR()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//编写消息映射函数CtlColor()用于实现超联接文本颜色的变化
HBRUSH CSuperLinkCtrl::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	// TODO: Change any attributes of the DC here
	if (CTLCOLOR_STATIC == nCtlColor)
	{
		pDC->SelectObject(&m_font);
		pDC->SetTextColor(m_crText);
		pDC->SetBkMode(TRANSPARENT);
	}
	HBRUSH hBrush = ::CreateSolidBrush(GetSysColor(COLOR_3DFACE));  //创建一个刷子句柄
	return hBrush;  // 返回一个用来画控件背景的刷子句柄
}

//实现鼠标按下左键消息
void CSuperLinkCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_bClicked=TRUE;         
	m_crText=m_clickedtextcor;  //设置超联接文本的颜色
	RedrawWindow();    // 重画控件实现超联接文本颜色的变化
	if(m_linktext!=_T(""))  
		//如果设置了超联接的地址则调用ShellExecute函数实现超联接
		ShellExecute(NULL, _T("open"), m_linktext, NULL, NULL, SW_SHOWNORMAL);  
	CStatic::OnLButtonDown(nFlags, point);
	// 调用基类响应函数
}

//设置超联接文本上的鼠标形状的消息映射函数
BOOL CSuperLinkCtrl::OnSetCursor(CWnd* pWnd, 
								 UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_hCursor)   // 如果已取得光标句柄则设置新的鼠标形状
	{
		::SetCursor(m_hCursor);
		return TRUE;
	}
	return CStatic::OnSetCursor(pWnd, nHitTest, message);
}

//设置超联接文本上的光标句柄
void CSuperLinkCtrl::SetLinkCursor(HCURSOR hCursor)
{
	m_hCursor = hCursor;
}

//响应鼠标移动消息
void CSuperLinkCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	SetCapture();     // 捕捉鼠标
	POINT mpoint;   
	GetCursorPos(&mpoint);  // 取得当前鼠标位置
	CRect rect;
	GetWindowRect(&rect);  // 取得控件的窗口大小
	if(!rect.PtInRect(mpoint)) // 判断鼠标是否在控件的窗口内
	{             // 鼠标不在控件的窗口内
		m_bcaptured=FALSE;
		ReleaseCapture();    // 释放鼠标捕捉
		MouseLeave(); //  调用mouseleave()函数
		return;
	} 
	// 鼠标在控件的窗口内
	if(m_bcaptured)  // 如果鼠标在窗口内且已经被捕捉则返回
		return;
	m_bcaptured=TRUE;
	MouseEnter();   //调用MouseEnter()函数
	ReleaseCapture(); // 释放鼠标捕捉
	CStatic::OnMouseMove(nFlags, point); // 调用基类响应函数
}

//在MouseEnter()和MouseLeave()
//函数中设置鼠标进入和离开时的超联接文本的颜色
void CSuperLinkCtrl::MouseEnter()
{
	m_crText=m_bClicked? m_clickedtextcor : m_moveontextcor;
	RedrawWindow();    // 重画控件实现超联接文本颜色的变化
}

void CSuperLinkCtrl::MouseLeave()
{
	m_crText=m_bClicked? m_clickedtextcor : m_ordinarytextcor;
	RedrawWindow();   // 重画控件实现超联接文本颜色的变化
}

//在SetLinkAddress()函数中设置超联接到地址
BOOL CSuperLinkCtrl::SetLinkAddress(CString linkaddress)
{   // 验证地址的合法性
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
//---- 由于static控件并不响应鼠标消息，所以还需在派生的子类中作些修改。下面函数是使static控件能响应鼠标消息的关键（因为通常static控件只能响应很少一部分消息）

void CSuperLinkCtrl::SetSuperLink(BOOL setlink)
{
	if (setlink)   // 此处必须加入ModifyStyle()，
		//使static控件能响应鼠标消息
		ModifyStyle(0,SS_NOTIFY);
	else
		ModifyStyle(SS_NOTIFY,0);
}

void CSuperLinkCtrl::SetUnderLine(BOOL bUnderLine = TRUE)
{	
	//取得当前的缺省字体
	m_lf.lfUnderline = bUnderLine;  
	//为当前缺省字体加入下划线
	BOOL bCreated = m_font.CreateFontIndirect(&m_lf); 
	// 创建超联接字体
	ASSERT(bCreated);
}