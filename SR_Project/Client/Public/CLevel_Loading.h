#pragma once
#include "Client_Defines.h"
#include "CLevel.h"
#include "CLoader.h"

BEGIN(Client)

class CLevel_Loading final: public CLevel
{
private:
	explicit CLevel_Loading(const LPDIRECT3DDEVICE9& _pDevice, const LEVEL& _eLevel);
	virtual ~CLevel_Loading() = default;

public:
	virtual HRESULT NativeConstruct() override;
	virtual void Tick(const _float& _fDeltaSeconds)override;
	virtual void Late_Tick(const _float& _fDeletaSeconds)override;
	virtual HRESULT Render()override;

	HRESULT Open_Level(LPDIRECT3DDEVICE9& _pDevice);
private:
	CLoader*	m_pLoader;
	LEVEL		m_eNextLevel;
public:
	static CLevel* Create(LPDIRECT3DDEVICE9& _pDevice, const LEVEL& _eLevel);
	virtual void Free() override;
};

END