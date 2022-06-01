#include "..\Public\CBackground.h"
#include"CGameInstance.h"

CBackground::CBackground(LPDIRECT3DDEVICE9 & _pDevice)
	: CGameObject(_pDevice), m_pVertexRectComp(nullptr), m_pTextureComp(nullptr), m_pTransformComp(nullptr)
{
}

CBackground::CBackground(CBackground & _pProtoType)
	: CGameObject(_pProtoType), m_pVertexRectComp(nullptr), m_pTextureComp(nullptr), m_pTransformComp(nullptr)
{

}

HRESULT CBackground::NativeConstruct_ProtoType()
{
	if (FAILED(__super::NativeConstruct_ProtoType()))
		return E_FAIL;

	return S_OK;
}

HRESULT CBackground::NativeConstruct_Clone(void*& _pArg)
{
	if (FAILED(__super::NativeConstruct_Clone(_pArg)))
		return E_FAIL;

	if (FAILED(Add_Component()))
		return E_FAIL;

	return S_OK;
}

void CBackground::Tick(const _float & _fDeltaTime)
{
	__super::Tick(_fDeltaTime);
}

void CBackground::Late_Tick(const _float & _fDeltaTime)
{
	__super::Late_Tick(_fDeltaTime);
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);
	pGameInstance->Add_RenderObj(CRenderer_Manager::RENDER_PRIORITY, this);
	Safe_Release(pGameInstance);
}

HRESULT CBackground::Render()
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

HRESULT CBackground::Add_Component()
{
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);
	if (nullptr == pGameInstance)
		return E_FAIL;

	m_pTransformComp->Set_Position(_VECTOR3(0.f, 0.f, 0.f));
	Safe_Release(pGameInstance);
	return S_OK;
}

CBackground * CBackground::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CBackground*		pInstance = new CBackground(pGraphic_Device);

	if (FAILED(pInstance->NativeConstruct_ProtoType()))
	{
		MSG_BOX("Failed to Created : CBackGround");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CBackground::Clone(void *& _pArg)
{
	CBackground*		pInstance = new CBackground(*this);

	if (FAILED(pInstance->NativeConstruct_Clone(_pArg)))
	{
		MSG_BOX("Failed to Created : CBackGround");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CBackground::Free()
{
	__super::Free();
}
