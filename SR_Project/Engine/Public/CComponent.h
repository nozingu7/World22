#pragma once
#include "CBase.h"

BEGIN(Engine)

class ENGINE_DLL CComponent abstract : public CBase
{
protected:
	explicit CComponent(const LPDIRECT3DDEVICE9& _pGraphic_Device);
	explicit CComponent(const CComponent& _rhs);
	virtual ~CComponent() = default;

public:
	virtual HRESULT NativeConstruct_ProtoType();
	virtual HRESULT NativeConstruct_Clone(void*& _pArg);

protected:
	LPDIRECT3DDEVICE9 m_pGraphic_Device;
public:
	virtual CComponent* Clone(void*& _pArg) = 0;     
	virtual void Free() override;
};

END