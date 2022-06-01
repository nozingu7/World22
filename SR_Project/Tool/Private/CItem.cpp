#include "..\Public\CItem.h"
#include "CItem_ToolTip.h"

CItem::CItem(const LPDIRECT3DDEVICE9 & _pDevice)
	:CGameObject(_pDevice)
{
	ZeroMemory(&m_tItemInfo, sizeof(ITEMINFO));
}

CItem::CItem(const CItem & _rhs)
	:CGameObject(_rhs)
	,m_pToolTip(_rhs.m_pToolTip), m_tItemInfo(_rhs.m_tItemInfo)
{
	Safe_AddRef(m_pToolTip);
}

HRESULT CItem::NativeConstruct_ProtoType()
{
	if (FAILED(__super::NativeConstruct_ProtoType()))
		return E_FAIL;

	return S_OK;
}

HRESULT CItem::NativeConstruct_Clone(void *& pArg)
{
	if (FAILED(__super::NativeConstruct_Clone(pArg)))
		return E_FAIL;

	return S_OK;
}

void CItem::Tick(const _float & _fDeltaTime)
{
	__super::Tick(_fDeltaTime);
}

void CItem::Late_Tick(const _float & _fDeltaTime)
{
	__super::Late_Tick(_fDeltaTime);
}

HRESULT CItem::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	return S_OK;
}

void CItem::Free()
{
	Safe_Release(m_pToolTip);
	__super::Free();
}
