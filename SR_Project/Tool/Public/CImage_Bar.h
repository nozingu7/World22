#pragma once
#include "Tool_Defines.h"
#include "CUI_Default.h"


BEGIN(Tool)

class CImage_Bar final : public CUI_Default
{
private:
	explicit CImage_Bar(const LPDIRECT3DDEVICE9& _pDevice);
	explicit CImage_Bar(const CImage_Bar& _pProtoType);
	virtual ~CImage_Bar() = default;
public:
	virtual HRESULT NativeConstruct_ProtoType() override;
	virtual HRESULT NativeConstruct_Clone(void*& pArg)override;
	virtual void	Tick(const _float& _fDeltaTime) override;
	virtual void	Late_Tick(const _float& _fDeltaTime) override;
	virtual HRESULT Render() override;
public:
	virtual HRESULT Add_Component() override;
public:
	static CImage_Bar* Create(const LPDIRECT3DDEVICE9& _pDevice);
	virtual CGameObject* Clone(void*& _pArg) override;
	virtual void Free() override;
};
END

