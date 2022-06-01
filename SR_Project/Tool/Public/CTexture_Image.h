#pragma once
#include "CIMGUI.h"

BEGIN(Tool)

class CTexture_Image final : public CIMGUI
{
private:
	explicit CTexture_Image(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual ~CTexture_Image() = default;

public:
	virtual HRESULT NativeConstruct() override;
	virtual HRESULT Tick(const _float& _fDeltaSeconds) override;
	virtual HRESULT Late_Tick(const _float& _fDeltaSeconds) override;
	virtual HRESULT Render() override;

public:
	static CTexture_Image* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual void Free() override;
};

END