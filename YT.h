// YT.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// CYTApp:
// �йش����ʵ�֣������ YT.cpp
//

class CYTApp : public CWinApp
{
public:
	CYTApp();

// ��д
	public:
	virtual BOOL InitInstance();


// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CYTApp theApp;
