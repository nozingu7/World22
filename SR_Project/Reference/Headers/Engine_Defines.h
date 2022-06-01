#pragma once

#pragma warning (disable : 4251)

#include<d3d9.h>
#include<d3dx9.h>

// Windows ��� ����:
#include <windows.h>
#include<iostream>
#include<map>
#include<unordered_map>
#include<list>
#include<vector>
#include<algorithm>
#include<thread>
#include<mutex>
#include<shared_mutex>

// ���̷�Ʈ X �Է�
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

using namespace std;

#include"Engine_Macro.h"
#include"Engine_Function.h"
#include"Engine_Struct.h"
#include"Engine_Typedef.h"

#ifndef _AFX

#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifndef DBG_NEW 

#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW                                                                                                        
#endif

#endif
#endif

#ifndef ENGINE_EXPORTS
#ifdef _DEBUG
#ifdef UNICODE                                                                                      
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console") 
#else                                                                                                    
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")   
#endif 
#endif
#endif

//#pragma warning

using namespace Engine;

