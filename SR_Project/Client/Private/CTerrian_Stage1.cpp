#include"stdafx.h"
#include "..\Default\CTerrian_Stage1.h"
#include "CGameInstance.h"

CTerrian_Stage1::CTerrian_Stage1(const LPDIRECT3DDEVICE9 & _pGraphic_Device)
	: CGameObject(_pGraphic_Device), 
	m_pVertexTerrian(nullptr), m_pTextureComp(nullptr), m_pTransformComp(nullptr)
{
}

CTerrian_Stage1::CTerrian_Stage1(const CTerrian_Stage1 & _Prototype) 
	: CGameObject(_Prototype),
	m_pVertexTerrian(nullptr), m_pTextureComp(nullptr), m_pTransformComp(nullptr)
{
}

HRESULT CTerrian_Stage1::NativeConstruct_ProtoType()
{
	if (FAILED(__super::NativeConstruct_ProtoType()))
		return E_FAIL;

	return S_OK;
}

HRESULT CTerrian_Stage1::NativeConstruct_Clone(void *& _pArg)
{
	if (FAILED(__super::NativeConstruct_Clone(_pArg)))
		return E_FAIL;

	if (FAILED(Add_Component()))
		return E_FAIL;

	return S_OK;
}

void CTerrian_Stage1::Tick(const _float & _fDeltaTime)
{
	__super::Tick(_fDeltaTime);
}

void CTerrian_Stage1::Late_Tick(const _float & _fDeltaTime)
{
	__super::Late_Tick(_fDeltaTime);
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);
	pGameInstance->Add_RenderObj(CRenderer_Manager::RENDER_NONALPHABLEND, this);
	Safe_Release(pGameInstance);
}

HRESULT CTerrian_Stage1::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(m_pTransformComp->Bind_WorldMatrix()))
		return E_FAIL;
	if (FAILED(m_pTextureComp->Bind_Texture(0)))
		return E_FAIL;

	m_pGraphic_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	if (FAILED(m_pVertexTerrian->Render()))
		return E_FAIL;

	m_pGraphic_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	return S_OK;
}

HRESULT CTerrian_Stage1::Add_Component()
{
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	if (nullptr == pGameInstance)
		return E_FAIL;

	Safe_AddRef(pGameInstance);

	/* For.Com_VIBuffer */
	if (FAILED(__super::Add_Component((CComponent**)&m_pVertexTerrian, TEXT("Com_VIBuffer"), LEVEL_GS1, TEXT("PROTO_COMP_VERTEX_TERRIAN"))))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::Add_Component((CComponent**)&m_pTextureComp, TEXT("Com_Texture"), LEVEL_STATIC, TEXT("PROTO_COMP_TEXTURE"))))
		return E_FAIL;

	/* For.Com_Transform */
	if (FAILED(__super::Add_Component((CComponent**)&m_pTransformComp, TEXT("Com_Transform"), LEVEL_STATIC, TEXT("PROTO_COMP_TRANSFORM"))))
		return E_FAIL;

	//m_pTransformComp->Set_Position(_VECTOR3(0.f, -100.f, 0.f));
	Safe_Release(pGameInstance);
	return S_OK;
}

CTerrian_Stage1 * CTerrian_Stage1::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CTerrian_Stage1*		pInstance = new CTerrian_Stage1(pGraphic_Device);

	if (FAILED(pInstance->NativeConstruct_ProtoType()))
	{
		MSG_BOX("Failed to Created : CTerrian_Stage1");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CTerrian_Stage1::Clone(void *& _pArg)
{
	CTerrian_Stage1*		pInstance = new CTerrian_Stage1(*this);

	if (FAILED(pInstance->NativeConstruct_Clone(_pArg)))
	{
		MSG_BOX("Failed to Created : CTerrian_Stage1");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CTerrian_Stage1::Free()
{
	__super::Free();
}
