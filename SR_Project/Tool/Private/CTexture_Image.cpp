#include "..\Public\CTexture_Image.h"


CTexture_Image::CTexture_Image(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CIMGUI(pGraphic_Device)
{
}

HRESULT CTexture_Image::NativeConstruct()
{
	if (FAILED(__super::NativeConstruct()))
		return E_FAIL;

	

	return S_OK;
}

HRESULT CTexture_Image::Tick(const _float & _fDeltaSeconds)
{
	if (FAILED(__super::Tick(_fDeltaSeconds)))
		return E_FAIL;

	return S_OK;
}

HRESULT CTexture_Image::Late_Tick(const _float & _fDeltaSeconds)
{
	if (FAILED(__super::Late_Tick(_fDeltaSeconds)))
		return E_FAIL;

	return S_OK;
}

HRESULT CTexture_Image::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	return S_OK;
}

CTexture_Image * CTexture_Image::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CTexture_Image* pInstance = new CTexture_Image(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct()))
	{
		MSG_BOX("Failed To Create : CTexture_Image");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CTexture_Image::Free()
{
	__super::Free();
}
