#include "stdafx.h"
#include "CEffect.h"
#include "CGameInstance.h"

CEffect::CEffect(const LPDIRECT3DDEVICE9 & _pDevice)
	: CSortObject(_pDevice), m_fFrame(0.f)
{
}

CEffect::CEffect(const CEffect & _rhs)
	: CSortObject(_rhs), m_fFrame(0.f)
{
}

HRESULT CEffect::NativeConstruct_ProtoType()
{
	if (FAILED(__super::NativeConstruct_ProtoType()))
		return E_FAIL;

	return S_OK;
}

HRESULT CEffect::NativeConstruct_Clone(void *& pArg)
{
	if (FAILED(__super::NativeConstruct_Clone(pArg)))
		return E_FAIL;

	if (FAILED(SetUp_Component()))
		return E_FAIL;

	m_pTransformCom->Set_Position(_VECTOR3((_float)(rand() % 10), 2.f, (_float)(rand() % 10)));

	m_fFrame = _float(rand() % 90);

	return S_OK;
}

void CEffect::Tick(const _float & _fDeltaTime)
{
	__super::Tick(_fDeltaTime);
	CGameInstance*		pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	m_fFrame += 90.0f * _fDeltaTime;

	if (m_fFrame >= 90.f)
		m_fFrame = 0.f;

	__super::Compute_CamDistance(m_pTransformCom);
	Safe_Release(pGameInstance);
}

void CEffect::Late_Tick(const _float & _fDeltaTime)
{
	__super::Late_Tick(_fDeltaTime);
	CGameInstance*			pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	CGameObject* pTerrian = pGameInstance->Find_GameObject(LEVEL_GS1, L"Layer_Terrian", 0);

	CVIVertex_Terrian* pComp = static_cast<CVIVertex_Terrian*>(pTerrian->Get_Component(L"Com_VIBuffer"));
	if (nullptr != pComp)
	{
		CTransform* pTransform = static_cast<CTransform*>(pTerrian->Get_Component(L"Com_Transform"));

		_VECTOR3 v3Pos = m_pTransformCom->Get_Position();
		v3Pos.y = pComp->Get_TerrianFloorYPos(m_pTransformCom->Get_Position(), pTransform->Get_WorldMatrixInverse()) + 0.5f;
		m_pTransformCom->Set_Position(v3Pos);
	}

	pGameInstance->Add_RenderObj(CRenderer_Manager::RENDER_ALPHABLEND, this);

	Safe_Release(pGameInstance);
}

HRESULT CEffect::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(m_pTransformCom->Bind_WorldMatrix()))
		return E_FAIL;

	m_pTextureCom->Bind_Texture((_uint)m_fFrame);

	if (FAILED(Render_State()))
		return E_FAIL;

	m_pVIBufferCom->Render();

	if (FAILED(Release_RenderState()))
		return E_FAIL;

	return S_OK;
}

HRESULT CEffect::SetUp_Component()
{
	CGameInstance*		pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	if (FAILED(__super::Add_Component((CComponent**)&m_pTextureCom, L"Com_Texture",
		LEVEL_GS1, TEXT("Prototype_Component_Texture_Explosion"))))
		return E_FAIL;

	if (FAILED(__super::Add_Component((CComponent**)&m_pVIBufferCom, TEXT("Com_VIBuffer"), 
		LEVEL_STATIC, TEXT("PROTO_COMP_VIBUF_RECT"))))
		return E_FAIL;

	if (FAILED(__super::Add_Component((CComponent**)&m_pTransformCom, L"LEVEL_STATIC",
		LEVEL_STATIC, TEXT("PROTO_COMP_TRANSFORM"))))
		return E_FAIL;

	Safe_Release(pGameInstance);
	return S_OK;
}

HRESULT CEffect::Render_State()
{
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;

	m_pGraphic_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	m_pGraphic_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pGraphic_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pGraphic_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	return S_OK;
}

HRESULT CEffect::Release_RenderState()
{
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;

	m_pGraphic_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

	return S_OK;
}

CEffect * CEffect::Create(const LPDIRECT3DDEVICE9 & pGraphic_Device)
{
	CEffect*		pInstance = new CEffect(pGraphic_Device);

	if (FAILED(pInstance->NativeConstruct_ProtoType()))
	{
		MSG_BOX("Failed to Created : CEffect");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CEffect::Clone(void *& pArg)
{
	CEffect*		pInstance = new CEffect(*this);
	if (FAILED(pInstance->NativeConstruct_Clone(pArg)))
	{
		MSG_BOX("Failed to Created : CEffect");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CEffect::Free()
{
	__super::Free();
}
