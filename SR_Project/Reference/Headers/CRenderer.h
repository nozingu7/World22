#pragma once
#include "CComponent.h"

class CRenderer final : public CComponent
{
private:
	explicit CRenderer(const LPDIRECT3DDEVICE9& _pGraphic_Device);
	explicit CRenderer(CRenderer& _rhs);
	virtual ~CRenderer() = default;


private:
public:
	static CRenderer* Create();
	virtual CComponent* Clone(void*& _pArg) override;
	virtual void Free() override;
};

