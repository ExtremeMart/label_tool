
// ImageMark.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CImageMarkApp: 
// �йش����ʵ�֣������ ImageMark.cpp
//

class CImageMarkApp : public CWinApp
{
public:
	CImageMarkApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CImageMarkApp theApp;