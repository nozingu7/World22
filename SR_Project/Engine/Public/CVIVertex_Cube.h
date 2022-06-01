#pragma once
#include "CVIVertex.h"

BEGIN(Engine)

class ENGINE_DLL CVIVertex_Cube final : public CVIVertex
{
private:
	explicit CVIVertex_Cube(const LPDIRECT3DDEVICE9& _pGraphic_Device);
	explicit CVIVertex_Cube(const CVIVertex_Cube& _rhs);
	virtual ~CVIVertex_Cube() = default;

public:
	virtual HRESULT NativeConstruct_ProtoType() override;
	virtual HRESULT NativeConstruct_Clone(void*& _pArg) override;

public:
	static CVIVertex_Cube* Create(LPDIRECT3DDEVICE9& _pGraphic_Device);
	virtual CComponent* Clone(void*& _pArg) override;
	virtual void Free() override;
};

END