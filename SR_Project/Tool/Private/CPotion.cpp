#include "..\Public\CPotion.h"

CPotion::CPotion(const LPDIRECT3DDEVICE9 & _pDevice)
	:CItem(_pDevice)
{
}

CPotion::CPotion(const CPotion & _rhs)
	: CItem(_rhs)
{
}

HRESULT CPotion::NativeConstruct_ProtoType()
{
	if (FAILED(__super::NativeConstruct_ProtoType()))
		return E_FAIL;


	return S_OK;
}

HRESULT CPotion::NativeConstruct_Clone(void *& pArg)
{
	if (FAILED(__super::NativeConstruct_Clone(pArg)))
		return E_FAIL;

	return S_OK;
}

void CPotion::Tick(const _float & _fDeltaTime)
{
	__super::Tick(_fDeltaTime);
}

void CPotion::Late_Tick(const _float & _fDeltaTime)
{ 
	__super::Late_Tick(_fDeltaTime);
}

HRESULT CPotion::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	return S_OK;
}

void CPotion::Free()
{
	__super::Free();
}
