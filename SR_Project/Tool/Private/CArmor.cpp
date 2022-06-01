#include "..\Public\CArmor.h"

CArmor::CArmor(const LPDIRECT3DDEVICE9 & _pDevice)
	:CItem(_pDevice)
{
}

CArmor::CArmor(const CArmor & _rhs)
	:CItem(_rhs)
{
}

HRESULT CArmor::NativeConstruct_ProtoType()
{
	if (FAILED(__super::NativeConstruct_ProtoType()))
		return E_FAIL;


	return S_OK;
}

HRESULT CArmor::NativeConstruct_Clone(void *& pArg)
{
	if (FAILED(__super::NativeConstruct_Clone(pArg)))
		return E_FAIL;

	return S_OK;
}

void CArmor::Tick(const _float & _fDeltaTime)
{
	__super::Tick(_fDeltaTime);
}

void CArmor::Late_Tick(const _float & _fDeltaTime)
{
	__super::Late_Tick(_fDeltaTime);
}

HRESULT CArmor::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	return S_OK;
}

void CArmor::Free()
{
	__super::Free();
}
