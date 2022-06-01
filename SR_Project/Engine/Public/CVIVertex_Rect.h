#pragma once
#include "CVIVertex.h"

BEGIN(Engine)

class ENGINE_DLL CVIVertex_Rect final : public CVIVertex
{
private:
	explicit CVIVertex_Rect(const LPDIRECT3DDEVICE9& _pGraphic_Device);
	explicit CVIVertex_Rect(const CVIVertex_Rect& _rhs);
	virtual ~CVIVertex_Rect() = default;

public:
	virtual HRESULT NativeConstruct_ProtoType() override;
	virtual HRESULT NativeConstruct_Clone(void*& _pArg) override;
public:
	static CVIVertex_Rect* Create(LPDIRECT3DDEVICE9& _pGraphic_Device);
	virtual CComponent* Clone(void*& _pArg) override;
	virtual void Free() override;
};

END