#include "CCharacter.h"
#include "..\Public\CCharacter.h"

CCharacter::CCharacter(const LPDIRECT3DDEVICE9 & _pDevice)
	: CGameObject(_pDevice)
{
	ZeroMemory(&m_tCharInfoDesc, sizeof(CHARINFO));
}

CCharacter::CCharacter(const CCharacter & _rhs)
	: CGameObject(_rhs), m_tCharInfoDesc(_rhs.m_tCharInfoDesc)
{
}

HRESULT CCharacter::NativeConstruct_ProtoType()
{
	if (FAILED(__super::NativeConstruct_ProtoType()))
		return E_FAIL;

	return S_OK;
}

HRESULT CCharacter::NativeConstruct_Clone(void *& pArg)
{
	if (FAILED(__super::NativeConstruct_Clone(pArg)))
		return E_FAIL;

	return S_OK;
}

void CCharacter::Tick(const _float & _fDeltaTime)
{
	__super::Tick(_fDeltaTime);
}

void CCharacter::Late_Tick(const _float & _fDeltaTime)
{
	__super::Late_Tick(_fDeltaTime);
}

HRESULT CCharacter::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;
	return S_OK;
}


void CCharacter::Free()
{
	__super::Free();
}
