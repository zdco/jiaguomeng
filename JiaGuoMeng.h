
// JiaGuoMeng.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CJiaGuoMengApp: 
// �йش����ʵ�֣������ JiaGuoMeng.cpp
//

class CJiaGuoMengApp : public CWinApp
{
public:
	CJiaGuoMengApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CJiaGuoMengApp theApp;