
// twenty-four-cal.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CtwentyfourcalApp: 
// �йش����ʵ�֣������ twenty-four-cal.cpp
//

class CtwentyfourcalApp : public CWinApp
{
public:
	CtwentyfourcalApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CtwentyfourcalApp theApp;