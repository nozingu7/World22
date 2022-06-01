#include "..\Public\CWeapon.h"

CWeapon::CWeapon(const LPDIRECT3DDEVICE9 & _pDevice)
	:CItem(_pDevice)
{
}

CWeapon::CWeapon(const CWeapon & _rhs)
	:CItem(_rhs)
{
}

HRESULT CWeapon::NativeConstruct_ProtoType()
{
	if (FAILED(__super::NativeConstruct_ProtoType()))
		return E_FAIL;

	return S_OK;
}

HRESULT CWeapon::NativeConstruct_Clone(void *& pArg)
{
	if (FAILED(__super::NativeConstruct_Clone(pArg)))
		return E_FAIL;

	return S_OK;
}

void CWeapon::Tick(const _float & _fDeltaTime)
{
	__super::Tick(_fDeltaTime);
}

void CWeapon::Late_Tick(const _float & _fDeltaTime)
{
	__super::Late_Tick(_fDeltaTime);
}

HRESULT CWeapon::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	return S_OK;
}

void CWeapon::Free()
{
	__super::Free();
}
