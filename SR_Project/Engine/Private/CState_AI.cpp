#include"CAStar_AI.h"
#include "..\Public\CState_AI.h"

CState_AI::CState_AI(const LPDIRECT3DDEVICE9 & _pGraphic_Device)
	: CAIComponent(_pGraphic_Device), m_pOwner(nullptr)
{
}

CState_AI::CState_AI(const CState_AI & _rhs)
	: CAIComponent(_rhs), m_pOwner(_rhs.m_pOwner)
{
}

HRESULT CState_AI::NativeConstruct_ProtoType()
{
	if (FAILED(__super::NativeConstruct_ProtoType()))
		return E_FAIL;
	return S_OK;
}

HRESULT CState_AI::NativeConstruct_Clone(void *& _pArg)
{
	if (FAILED(__super::NativeConstruct_Clone(_pArg)))
		return E_FAIL;
	return S_OK;
}

CComponent * CState_AI::Clone(void *& _pArg)
{
	return nullptr;
}

void CState_AI::Free()
{
	__super::Free();
}
