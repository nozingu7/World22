#pragma once
#include"CBase.h"

BEGIN(Engine)

class CGameObject;

class ENGINE_DLL CLevel abstract : public CBase
{
protected:
	explicit CLevel(const LPDIRECT3DDEVICE9& _pDevice);
	virtual ~CLevel() = default;
public:
	virtual HRESULT NativeConstruct();
	virtual void Tick(const _float& _fDeltaSeconds);
	virtual void Late_Tick(const _float& _fDeletaSeconds);
	virtual HRESULT Render();

protected:
	LPDIRECT3DDEVICE9 m_pGraphic_Device;
public:
	virtual void Free() override;
};

END