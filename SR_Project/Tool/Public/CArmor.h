#pragma once
#include "CItem.h"

BEGIN(Tool)

class CArmor abstract : public CItem
{
protected:
	explicit CArmor(const LPDIRECT3DDEVICE9& _pDevice);
	explicit CArmor(const CArmor& _rhs);
	virtual ~CArmor() = default;

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
	virtual CGameObject* Clone(void* pArg) = 0;
	virtual void Free();
};

END