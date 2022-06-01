#pragma once
#include"framework.h"

extern HWND					g_hWnd;
extern HINSTANCE			g_hInstance;
extern bool						g_bGameRun;

#include<process.h>

#include "Tool_Macro.h"

namespace Tool
{
	const unsigned int g_iWinSizeX = 1280;
	const unsigned int g_iWinSizeY = 720;


	enum LEVEL { LEVEL_STATIC, LEVEL_TOOL, LEVEL_ENGINE , LEVEL_END };
}

using namespace Tool;