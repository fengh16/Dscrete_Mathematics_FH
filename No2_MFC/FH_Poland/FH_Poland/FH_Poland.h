
// FH_Poland.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CFH_PolandApp: 
// �йش����ʵ�֣������ FH_Poland.cpp
//

class CFH_PolandApp : public CWinApp
{
public:
	CFH_PolandApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CFH_PolandApp theApp;
