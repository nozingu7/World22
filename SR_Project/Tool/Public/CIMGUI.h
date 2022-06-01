#pragma once
#include "Tool_Macro.h"
#include"CIMGUI_Manager.h"

BEGIN(Tool)

class CIMGUI abstract : public CBase
{
protected:
	explicit CIMGUI(const LPDIRECT3DDEVICE9& _pDevice);
	virtual ~CIMGUI() = default;
public:
	const string& Get_Name() const { return m_strWindowName; }

	const _bool& Is_OpenWindow() const { return m_bOpenWindow; }
	// Set Open This Window
	void Set_Open(const _bool& _bOpen) { this->m_bOpenWindow = _bOpen; }
public:
	virtual HRESULT NativeConstruct();
	virtual HRESULT Tick(const _float& _fDeltaSeconds);
	virtual HRESULT Late_Tick(const _float& _fDeltaSeconds);
	virtual HRESULT Render();
protected:
	// IMGUI  UI
	virtual void Show_Window();
protected:
	
protected:
	// Graphic Device
	LPDIRECT3DDEVICE9		m_pGraphic_Device;
	// Open Window
	_bool								m_bOpenWindow;
	//Window Name
	string								m_strWindowName;
public:
	// Create
	virtual void Free() override;
};

END