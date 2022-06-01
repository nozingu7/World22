#include "..\Public\CMonster.h"
#include "CGameInstance.h"

CMonster::CMonster(const LPDIRECT3DDEVICE9 & _pDevice)
	:CCharacter(_pDevice),
	m_pTransformComp(nullptr), m_pVertexRectComp(nullptr), m_pTextureComp(nullptr), m_pAStar_AIComp(nullptr)
{
}

CMonster::CMonster(const CMonster & _rhs)
	: CCharacter(_rhs), 
	m_pTransformComp(nullptr), m_pVertexRectComp(nullptr), m_pTextureComp(nullptr), m_pAStar_AIComp(nullptr)
{
}

HRESULT CMonster::NativeConstruct_ProtoType()
{
	if (FAILED(__super::NativeConstruct_ProtoType()))
		return E_FAIL;

	return S_OK;
}

HRESULT CMonster::NativeConstruct_Clone(void *& pArg)
{
	if (FAILED(__super::NativeConstruct_Clone(pArg)))
		return E_FAIL;

	if (FAILED(Ready_Comp()))
		return E_FAIL;

	return S_OK;
}
bool bFind = true;
void CMonster::Tick(const _float & _fDeltaTime)
{
	__super::Tick(_fDeltaTime);
	if (nullptr != m_pAStar_AIComp)
	{
		if (true == m_pAStar_AIComp->Is_Find_Target())
		{
			if (!FAILED(m_pAStar_AIComp->Move_Target(m_pTransformComp)))
			{
				m_pTransformComp->Move_Forward(5.f, _fDeltaTime);
			}
		}
	}
}

void CMonster::Late_Tick(const _float & _fDeltaTime)
{
	__super::Late_Tick(_fDeltaTime);
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);
	pGameInstance->Add_RenderObj(CRenderer_Manager::RENDER_NONALPHABLEND, this);
	Safe_Release(pGameInstance);
}

HRESULT CMonster::Render()
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

HRESULT CMonster::Ready_Comp()
{
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
	m_pTransformComp->Set_Position(_VECTOR3(1.0f, 0.f, 1.0f));
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);
	if (true == g_bGameRun)
	{
		/* For.Com_Transform */
		if (FAILED(__super::Add_Component((CComponent**)&m_pAStar_AIComp, TEXT("Com_AStar"), LEVEL_STATIC,
			TEXT("PROTO_COMP_AI_ASTAR"))))
			return E_FAIL;

		CTransform* pTerrianTransform = static_cast<CTransform*>(pGameInstance->Find_GameObject(LEVEL_ENGINE,
			L"Layer_Background", 0)->Get_Component(L"Com_Transform"));
		if (nullptr != pTerrianTransform)
		{
			m_pAStar_AIComp->Start_AStar(m_pTransformComp->Get_Position(), _VECTOR3(75.f, 0.f, 90.f),
				pTerrianTransform->Get_WorldMatrixInverse());
			pGameInstance->Register_AStar(m_pAStar_AIComp);
		}
	}
	Safe_Release(pGameInstance);
	return S_OK;
}

CMonster * CMonster::Create(const LPDIRECT3DDEVICE9 & _pDevice)
{
	CMonster* pMonster = new CMonster(_pDevice);
	if (FAILED(pMonster->NativeConstruct_ProtoType()))
	{
		MSG_BOX("Tool -> CMonster::Create Is Failed");
		Safe_Release(pMonster);
	}
	return pMonster;
}

CGameObject * CMonster::Clone(void *& _pArg)
{
	CMonster* pMonster = new CMonster(*this);
	if (FAILED(pMonster->NativeConstruct_Clone(_pArg)))
	{
		MSG_BOX("Tool -> CMonster::Clone Is Failed");
		Safe_Release(pMonster);
	}
	return pMonster;
}

void CMonster::Free()
{
	__super::Free();
}
