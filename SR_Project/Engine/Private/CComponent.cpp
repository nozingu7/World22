#include "..\Public\CComponent.h"


CComponent::CComponent(const LPDIRECT3DDEVICE9 & _pGraphic_Device)
	: m_pGraphic_Device(_pGraphic_Device)
{
	Safe_AddRef(_pGraphic_Device);
}

CComponent::CComponent(const CComponent & _rhs)
	: CComponent(_rhs.m_pGraphic_Device)
{
	
}

HRESULT CComponent::NativeConstruct_ProtoType()
{
	return S_OK;
}

HRESULT CComponent::NativeConstruct_Clone(void *& _pArg)
{
	return S_OK;
}

void CComponent::Free()
{
	Safe_Release(m_pGraphic_Device);
}
