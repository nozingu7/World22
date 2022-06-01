#pragma once

extern HWND			g_hWnd;
extern HINSTANCE g_hInstance;

#include<process.h>

namespace Client
{
	const unsigned int g_iWinSizeX = 1280;
	const unsigned int g_iWinSizeY = 720;

	enum LEVEL { LEVEL_STATIC, LEVEL_LOADING, LEVEL_LOGO, LEVEL_GS1, LEVEL_END };
}

using namespace Client;