﻿
// ENCODER.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CENCODERApp:
// Сведения о реализации этого класса: ENCODER.cpp
//

class CENCODERApp : public CWinApp
{
public:
	CENCODERApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CENCODERApp theApp;
