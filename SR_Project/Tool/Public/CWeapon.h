#pragma once
#include "CItem.h"

BEGIN(Tool)

class CWeapon abstract : public CItem
{
protected:
	explicit CWeapon(const LPDIRECT3DDEVICE9& _pDevice);
	explicit CWeapon(const CWeapon& _rhs);
	virtual ~CWeapon() = default;

public:
	virtual HRESULT NativeConstruct_ProtoType();
	virtual HRESULT NativeConstruct_Clone(void*& pArg);
	virtual void Tick(const _float& _fDeltaTime);
	virtual void Late_Tick(const _float& _fDeltaTime);
	virtual HRESULT Render();

public:
	// ������ ������ �Ѵ�.
	virtual HRESULT Show_ToolTip() PURE;

private:
	virtual HRESULT SetUp_RenderState() PURE;
	virtual HRESULT Release_RenderState() PURE;

public:
	virtual CGameObject* Clone(void*& _pArg) = 0;
	virtual void Free();
};

END