#pragma once
#include "Tool_Defines.h"
#include"Engine_Defines.h"
#include"CBase.h"

BEGIN(Engine)
class CGameInstance;
END

BEGIN(Tool)

class CIMGUI_Manager;
class CCopyView;

class CMainTool : public CBase
{
private: 
	explicit CMainTool();
	virtual ~CMainTool() = default;
public:
	HRESULT NativeConstructor(_bool& _bIsRun);
	void Tick(const _float& _fDeltaSeconds);
	HRESULT Render();
public:

private:
	// Open Level
	HRESULT Open_Level();
	// Ready Load Texture
	HRESULT Ready_LoadTexture();
	// Ready Static Component 
	HRESULT Ready_Static_Component();
	// Ready Static GameObject
	HRESULT Ready_Static_GameObject();
private:
	CGameInstance*		m_pGameInstance;
	CIMGUI_Manager*	m_pIMGUIManager;
	LPDIRECT3DDEVICE9	m_pDevice;
private:
	CCopyView*				m_pCopyView;
public:
	static CMainTool* Create(_bool& _bIsRun);
	virtual void Free() override;
};

END