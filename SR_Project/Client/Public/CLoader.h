#pragma once
#include"CBase.h"
#include "Client_Defines.h"   

BEGIN(Client)

class CLoader final : public CBase
{
private:
	explicit CLoader();
	explicit CLoader(LPDIRECT3DDEVICE9& _pDevice, const LEVEL& _eNextLevel);
	virtual ~CLoader() = default;
public:
	const _bool& Is_LoadingEnd() const { return m_isLoadingEnd; }
public:
	HRESULT NativeConstruct();
	// Loading Thread
	static _uint _stdcall Resource_Loading_MainThread(void* _pArg);
	// Resource Loader
	void Resources_Loader();
	// Logo Resource Load
	void Loading_Logo_Resource();
	// Gs1 Resource Load
	void Loading_GS1_Resource();
private:
	LPDIRECT3DDEVICE9	m_pGraphic_Device;
	LEVEL							m_eNextLevel;
	HANDLE						m_hThread;
	CRITICAL_SECTION		m_CriticalSection;
	_bool							m_isLoadingEnd;
public:
	static CLoader* Create(LPDIRECT3DDEVICE9& _pDevice, const LEVEL& _eNextLevel);
	virtual void Free() override;
};

END