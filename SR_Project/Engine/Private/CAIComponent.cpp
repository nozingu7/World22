#include "CAIComponent.h"
#include "CGameObject.h"

CAIComponent::CAIComponent(const LPDIRECT3DDEVICE9 & _pGraphic_Device)
	: CComponent(_pGraphic_Device)
{

}

CAIComponent::CAIComponent(const CAIComponent & _rhs)
	: CComponent(_rhs)
{

}

HRESULT CAIComponent::NativeConstruct_ProtoType()
{
	if (FAILED(__super::NativeConstruct_ProtoType()))
		return E_FAIL;

	return S_OK;
}

HRESULT CAIComponent::NativeConstruct_Clone(void *& _pArg)
{
	if (FAILED(__super::NativeConstruct_Clone(_pArg)))
		return E_FAIL;

	return S_OK;
}

void CAIComponent::Free()
{
	__super::Free();
}
