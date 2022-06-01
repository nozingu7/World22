#include"stdafx.h"
#include "..\Public\CBackGround.h"
#include"CGameInstance.h"

CBackGround::CBackGround(LPDIRECT3DDEVICE9 & _pDevice)
	: CGameObject(_pDevice), m_pVertexRectComp(nullptr), m_pTextureComp(nullptr), m_pTransformComp(nullptr)
{
}

CBackGround::CBackGround(CBackGround & _pProtoType)
	: CGameObject(_pProtoType), m_pVertexRectComp(nullptr), m_pTextureComp(nullptr), m_pTransformComp(nullptr)
{

}

HRESULT CBackGround::NativeConstruct_ProtoType()
{
	if (FAILED(__super::NativeConstruct_ProtoType()))
		return E_FAIL;

	return S_OK;
}

HRESULT CBackGround::NativeConstruct_Clone(void*& _pArg)
{
	if (FAILED(__super::NativeConstruct_Clone(_pArg)))
		return E_FAIL;

	if (FAILED(Add_Component()))
		return E_FAIL;
	
	return S_OK;
}

void CBackGround::Tick(const _float & _fDeltaTime)
{
	__super::Tick(_fDeltaTime);
}

void CBackGround::Late_Tick(const _float & _fDeltaTime)
{
	__super::Late_Tick(_fDeltaTime);
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);
	pGameInstance->Add_RenderObj(CRenderer_Manager::RENDER_PRIORITY, this);
	Safe_Release(pGameInstance);
}

HRESULT CBackGround::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(m_pTransformComp->Bind_WorldMatrix()))
		return E_FAIL;
	if (FAILED(m_pTextureComp->Bind_Texture(0)))
		return E_FAIL;

	m_pGraphic_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	if (FAILED(m_pVertexRectComp->Render()))
		return E_FAIL;

	m_pGraphic_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	return S_OK;
}

HRESULT CBackGround::Add_Component()
{
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	if (nullptr == pGameInstance)
		return E_FAIL;

	/* For.Com_VIBuffer */
	if (FAILED(__super::Add_Component((CComponent**)&m_pVertexRectComp, TEXT("Com_VIBuffer"), LEVEL_STATIC, 
		TEXT("PROTO_COMP_VIBUF_RECT"))))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::Add_Component((CComponent**)&m_pTextureComp, TEXT("Com_Texture"), LEVEL_STATIC, 
		TEXT("PROTO_COMP_TEXTURE"))))
		return E_FAIL;

	/* For.Com_Transform */
	if (FAILED(__super::Add_Component((CComponent**)&m_pTransformComp, TEXT("Com_Transform"), LEVEL_STATIC, 
		TEXT("PROTO_COMP_TRANSFORM"))))
		return E_FAIL;

	m_pTransformComp->Set_Position(_VECTOR3(0.f, 0.f, 0.f));
	Safe_Release(pGameInstance);
	return S_OK;
}

CBackGround * CBackGround::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CBackGround*		pInstance = new CBackGround(pGraphic_Device);

	if (FAILED(pInstance->NativeConstruct_ProtoType()))
	{
		MSG_BOX("Failed to Created : CBackGround");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CBackGround::Clone(void *& _pArg)
{
	CBackGround*		pInstance = new CBackGround(*this);

	if (FAILED(pInstance->NativeConstruct_Clone(_pArg)))
	{
		MSG_BOX("Failed to Created : CBackGround");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CBackGround::Free()
{
	__super::Free();
}
