#include "..\Public\CItem_ToolTip.h"


CItem_ToolTip::CItem_ToolTip(const LPDIRECT3DDEVICE9 & _pDevice)
	: CUI_Default(_pDevice)
{
}

CItem_ToolTip::CItem_ToolTip(const CItem_ToolTip & _rhs)
	: CUI_Default(_rhs)
{
}

HRESULT CItem_ToolTip::NativeConstruct_ProtoType()
{
	if (FAILED(__super::NativeConstruct_ProtoType()))
		return E_FAIL;

	return S_OK;
}

HRESULT CItem_ToolTip::NativeConstruct_Clone(void *& pArg)
{
	if (FAILED(__super::NativeConstruct_Clone(pArg)))
		return E_FAIL;

	return S_OK;
}

void CItem_ToolTip::Tick(const _float & _fDeltaTime)
{
	__super::Tick(_fDeltaTime);
}

void CItem_ToolTip::Late_Tick(const _float & _fDeltaTime)
{
	__super::Late_Tick(_fDeltaTime);
}

HRESULT CItem_ToolTip::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	return S_OK;
}

HRESULT CItem_ToolTip::SetUp_RenderState()
{
	if (FAILED(__super::SetUp_RenderState()))
		return E_FAIL;
	return S_OK;
}

HRESULT CItem_ToolTip::Release_RenderState()
{
	if (FAILED(__super::Release_RenderState()))
		return E_FAIL;
	return S_OK;
}

CGameObject * CItem_ToolTip::Clone(void *& _pArg)
{
	return nullptr;
}

void CItem_ToolTip::Free()
{
	__super::Free();
}
