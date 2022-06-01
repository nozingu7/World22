#include "..\Public\CLevel.h"
#include"CGraphic_Device.h"
#include "CGameObject.h"

CLevel::CLevel(const LPDIRECT3DDEVICE9& _pDevice) : m_pGraphic_Device(_pDevice)
{
	Safe_AddRef(m_pGraphic_Device);
}

HRESULT CLevel::NativeConstruct()
{
	return S_OK;
}

void CLevel::Tick(const _float & _fDeltaSeconds)
{

}

void CLevel::Late_Tick(const _float & _fDeletaSeconds)
{

}

HRESULT CLevel::Render()
{
	return S_OK;
}

void CLevel::Free()
{
	Safe_Release(m_pGraphic_Device);
}
