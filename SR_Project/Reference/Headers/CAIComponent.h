#pragma once
#include "CComponent.h"

BEGIN(Engine)

class CGameObject;

class ENGINE_DLL CAIComponent abstract : public CComponent
{
protected:
	explicit CAIComponent(const LPDIRECT3DDEVICE9& _pGraphic_Device);
	explicit CAIComponent(const CAIComponent& _rhs);
	virtual ~CAIComponent() = default;

public:
	virtual HRESULT NativeConstruct_ProtoType();
	virtual HRESULT NativeConstruct_Clone(void*& _pArg);

public:
	virtual CComponent* Clone(void*& _pArg) = 0;
	virtual void Free() override;
};

END