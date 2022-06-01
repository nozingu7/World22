#pragma once
#include "Tool_Defines.h"
#include"imgui.h"
#include"imgui_impl_win32.h"
#include"imgui_impl_dx9.h"
#include"Engine_Defines.h"
#include"CBase.h"

BEGIN(Engine)
class CGameInstance;
END

BEGIN(Tool)

class CIMGUI;
class CMainView;
class CEngineApp;

class CIMGUI_Manager : public CBase
{
	DECLARE_SINGLETON(CIMGUI_Manager)
private:
	explicit CIMGUI_Manager();
	virtual ~CIMGUI_Manager() = default;
public:
	class CMainView* Get_MainView() { return m_pMainView; }
public:
	// Native  Construct
	HRESULT NativeConstruct(const LPDIRECT3DDEVICE9& _pDevice);
	// Tick
	void Tick(const _float& _fDeltaSeconds);
	// Late Tick
	void Late_Tick(const _float& _fDeltaSeconds);
	// Render
	HRESULT Render();
private:
	// Add IMGUI
	HRESULT Make_AmGui();
private:
	CGameInstance*		m_pGameInstance;
private:
	LPDIRECT3DDEVICE9 m_pGraphic_Device;
private:
	CMainView*	m_pMainView;
public:
	static CIMGUI_Manager* Create();
	virtual void Free() override;
};

END