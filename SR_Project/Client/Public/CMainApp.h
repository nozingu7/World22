#pragma once
#include "CBase.h"
#include "Client_Defines.h"

BEGIN(Engine)
class CGameInstance;
END

BEGIN(Client)

class CMainApp final : public CBase
{ 
private:
	explicit CMainApp();
	virtual ~CMainApp() = default;
public:
	HRESULT NativeConstructor();
	void Tick(const _float& _fDeltaSeconds);
	HRESULT Render();
public:
	static CMainApp* Create();
	virtual void Free() override;
private:
	HRESULT Open_Level();
	// stat
	HRESULT Ready_Static_Component();
	// Ready Static GameObject
	HRESULT Ready_Static_GameObj();
	// Ready Render State
	HRESULT Ready_RenderState();
	// Rady Render State
	HRESULT Ready_SamplerState();
private:
	CGameInstance*		m_pGameInstance;
	LPDIRECT3DDEVICE9	m_pDevice;
#ifdef _DEBUG
	_tchar				m_szFrame[64];
	_uint				m_iCount = 0;
#endif
};

END