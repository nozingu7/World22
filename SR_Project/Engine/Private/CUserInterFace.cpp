#include "CUserInterFace.h"
#include "..\Public\CUserInterFace.h"

CUserInterFace::CUserInterFace(const LPDIRECT3DDEVICE9 & _pDevice)
	: CGameObject(_pDevice), m_iDepth(0)
{
}

CUserInterFace::CUserInterFace(const CUserInterFace & _pProtoType)
	: CGameObject(_pProtoType), m_iDepth(0)
{
}

HRESULT CUserInterFace::NativeConstruct_ProtoType()
{
	if (FAILED(__super::NativeConstruct_ProtoType()))
		return E_FAIL;
	return S_OK;
}

HRESULT CUserInterFace::NativeConstruct_Clone(void *& pArg)
{
	if (FAILED(__super::NativeConstruct_Clone(pArg)))
		return E_FAIL;
	return S_OK;
}

void CUserInterFace::Tick(const _float & _fDeltaTime)
{
	__super::Tick(_fDeltaTime);
}

void CUserInterFace::Late_Tick(const _float & _fDeltaTime)
{
	__super::Late_Tick(_fDeltaTime);
}

HRESULT CUserInterFace::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;
	return S_OK;
}

HRESULT CUserInterFace::SetUp_RenderState()
{
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;

	m_pGraphic_Device->SetRenderState(D3DRS_ZENABLE, FALSE);
	return S_OK;
}

HRESULT CUserInterFace::Release_RenderState()
{
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;

	m_pGraphic_Device->SetRenderState(D3DRS_ZENABLE, TRUE);
	return S_OK;
}

void CUserInterFace::Free()
{
	__super::Free();
}
