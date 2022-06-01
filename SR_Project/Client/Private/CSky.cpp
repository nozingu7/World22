#include "stdafx.h"
#include "CSky.h"
#include "CGameInstance.h"

CSky::CSky(const LPDIRECT3DDEVICE9 & pGraphic_Device)
	: CGameObject(pGraphic_Device)
{
}

CSky::CSky(const CSky & Prototype)
	: CGameObject(Prototype)
{
}

HRESULT CSky::NativeConstruct_ProtoType()
{
	if (FAILED(__super::NativeConstruct_ProtoType()))
		return E_FAIL;

	/* 서버나 파일을 통해서 데이터 초기화를 거친다. */

	return S_OK;
}

HRESULT CSky::NativeConstruct_Clone(void *& pArg)
{
	if (FAILED(__super::NativeConstruct_Clone(pArg)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	return S_OK;
}

void CSky::Tick(const _float & _fDeltaTime)
{
	__super::Tick(_fDeltaTime);
}

void CSky::Late_Tick(const _float & _fDeltaTime)
{
	__super::Late_Tick(_fDeltaTime);
	CGameInstance*			pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);
	_float4x4			ViewMatrix;

	m_pGraphic_Device->GetTransform(D3DTS_VIEW, &ViewMatrix);
	D3DXMatrixInverse(&ViewMatrix, nullptr, &ViewMatrix);

	m_pTransformCom->Set_Position(*(_VECTOR3*)&ViewMatrix.m[3][0]);

	pGameInstance->Add_RenderObj(CRenderer_Manager::RENDER_PRIORITY, this);
	Safe_Release(pGameInstance);
}

HRESULT CSky::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(m_pTransformCom->Bind_WorldMatrix()))
		return E_FAIL;

	m_pTextureCom->Bind_Texture(3);

	if (FAILED(SetUp_RenderState()))
		return E_FAIL;

	m_pVIBufferCom->Render();

	if (FAILED(Release_RenderState()))
		return E_FAIL;

	return S_OK;
}

HRESULT CSky::SetUp_Components()
{
	/* For.Com_Transform */
	if (FAILED(__super::Add_Component((CComponent**)&m_pTransformCom, TEXT("Com_Transform"), 
		LEVEL_STATIC, TEXT("PROTO_COMP_TRANSFORM"))))
		return E_FAIL;

	/* For.Com_VIBuffer */
	if (FAILED(__super::Add_Component((CComponent**)&m_pVIBufferCom, TEXT("Com_VIBuffer"), 
		LEVEL_GS1, TEXT("Prototype_Component_VIBuffer_Cube"))))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::Add_Component((CComponent**)&m_pTextureCom, TEXT("Com_Texture"), 
		LEVEL_GS1, TEXT("Prototype_Component_Texture_Sky"))))
		return E_FAIL;

	return S_OK;
}

HRESULT CSky::SetUp_RenderState()
{
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;

	m_pGraphic_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	m_pGraphic_Device->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	return S_OK;
}

HRESULT CSky::Release_RenderState()
{
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;

	m_pGraphic_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pGraphic_Device->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	return S_OK;
}

CSky * CSky::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CSky*		pInstance = new CSky(pGraphic_Device);

	if (FAILED(pInstance->NativeConstruct_ProtoType()))
	{
		MSG_BOX("Failed to Created : CSky");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CSky::Clone(void *& _pArg)
{
	CSky*		pInstance = new CSky(*this);

	if (FAILED(pInstance->NativeConstruct_Clone(_pArg)))
	{
		MSG_BOX("Failed to Created : CSky");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CSky::Free()
{
	__super::Free();
}
