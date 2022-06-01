#include "..\Public\CPlayer.h"
#include "CGameInstance.h"

CPlayer::CPlayer(const LPDIRECT3DDEVICE9 & _pDevice)
	: CCharacter(_pDevice), 
	m_pVertexRectComp(nullptr), m_pTextureComp(nullptr), m_pTransformComp(nullptr)
{
}

CPlayer::CPlayer(const CPlayer & _rhs)
	: CCharacter(_rhs),
	m_pVertexRectComp(nullptr), m_pTextureComp(nullptr), m_pTransformComp(nullptr)
{
}

HRESULT CPlayer::NativeConstruct_ProtoType()
{
	if (FAILED(__super::NativeConstruct_ProtoType()))
		return E_FAIL;

	return S_OK;
}

HRESULT CPlayer::NativeConstruct_Clone(void *& pArg)
{
	if (FAILED(__super::NativeConstruct_Clone(pArg)))
		return E_FAIL;

	if (FAILED(Add_Component()))
		return E_FAIL;

	m_pTransformComp->Set_Position(_VECTOR3(0.f, 10.f, 0.f));

	return S_OK;
}

void CPlayer::Tick(const _float & _fDeltaTime)
{
	__super::Tick(_fDeltaTime);
	if (true == g_bGameRun)
	{
		Player_Move(_fDeltaTime);
	}
}

void CPlayer::Late_Tick(const _float & _fDeltaTime)
{
	__super::Late_Tick(_fDeltaTime);
	if (true == g_bGameRun)
	{
		SetUp_Height();
	}
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);
	{
		pGameInstance->Add_RenderObj(CRenderer_Manager::RENDER_NONALPHABLEND, this);
	}
	Safe_Release(pGameInstance);
}

HRESULT CPlayer::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(m_pTransformComp->Bind_WorldMatrix()))
		return E_FAIL;

	m_pTextureComp->Bind_Texture(93);

	SetUp_RenderState();

	if (FAILED(m_pVertexRectComp->Render()))
		return E_FAIL;

	Release_RenderState();
	return S_OK;
}

HRESULT CPlayer::Add_Component()
{
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);
	pGameInstance->Add_RenderObj(CRenderer_Manager::RENDER_PRIORITY, this);

	if (FAILED(CGameObject::Add_Component((CComponent**)&m_pTransformComp, TEXT("Com_Transform"), LEVEL_STATIC,
		TEXT("PROTO_COMP_TRANSFORM"))))
		return E_FAIL;

	if (FAILED(CGameObject::Add_Component((CComponent**)&m_pVertexRectComp, TEXT("Com_VIBuffer"), LEVEL_STATIC,
		TEXT("PROTO_COMP_VIBUF_RECT"))))
		return E_FAIL;

	if (FAILED(CGameObject::Add_Component((CComponent**)&m_pTextureComp, TEXT("Com_Texture"), LEVEL_STATIC,
		TEXT("PROTO_COMP_TEXTURE_TEST"))))
		return E_FAIL;

	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CPlayer::SetUp_RenderState()
{
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;

	m_pGraphic_Device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHAREF, 254);
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	return S_OK;
}

HRESULT CPlayer::Release_RenderState()
{
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	return S_OK;
}

HRESULT CPlayer::SetUp_Height()
{
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);
	{
		// ¤©¾ð·¡¤Á‰C¸® Š¤©Àú¤Ó¶û´·´©¤Ñ
		CGameObject* pTerrian = pGameInstance->Find_GameObject(LEVEL_ENGINE, TEXT("Layer_Background"), 0);
		CVIVertex_Terrian* pTerrianBuffer = static_cast<CVIVertex_Terrian*>(pTerrian->Get_Component(TEXT("Com_Terrian")));
		CTransform* pTerrianTransform = static_cast<CTransform*>(pTerrian->Get_Component(TEXT("Com_Transform")));

		_VECTOR3 vWorldPos = m_pTransformComp->Get_Position();
		vWorldPos.y = pTerrianBuffer->Get_TerrianFloorYPos(vWorldPos, pTerrianTransform->Get_WorldMatrixInverse()) + 0.5f;
		m_pTransformComp->Set_Position(vWorldPos);
	}
	Safe_Release(pGameInstance);
	return S_OK;
}

HRESULT CPlayer::Player_Move(const _float & _fDeltaSeconds)
{
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);
	{
		if (pGameInstance->Get_DIKeyState(DIK_W) < 0)
		m_pTransformComp->Move_Forward(10.f, _fDeltaSeconds);
	if (pGameInstance->Get_DIKeyState(DIK_A) < 0)
		m_pTransformComp->Move_Left(10.f, _fDeltaSeconds);
	if (pGameInstance->Get_DIKeyState(DIK_D) < 0)
		m_pTransformComp->Move_Right(10.f, _fDeltaSeconds);
	if (pGameInstance->Get_DIKeyState(DIK_S) < 0)
		m_pTransformComp->Move_Back(10.f, _fDeltaSeconds);

	_long		MouseMove = 0;
	if (MouseMove = pGameInstance->Get_DIMMoveState(CInput_Device::DIMM_X))
		m_pTransformComp->RotationAxisToTurn(_VECTOR3(0.f, 1.f, 0.f), D3DXToRadian(90.f), _fDeltaSeconds * MouseMove * 0.1f);

	if (MouseMove = pGameInstance->Get_DIMMoveState(CInput_Device::DIMM_Y))
		m_pTransformComp->RotationAxisToTurn(m_pTransformComp->Get_Right(), D3DXToRadian(90.f), _fDeltaSeconds * MouseMove * 0.1f);

	}
	Safe_Release(pGameInstance);

	return S_OK;
}

CPlayer * CPlayer::Create(const LPDIRECT3DDEVICE9 & _pDevice)
{
	CPlayer* pInstance = new CPlayer(_pDevice);
	if (FAILED(pInstance->NativeConstruct_ProtoType()))
	{
		MSG_BOX("Camera_Free::Clone Error");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CPlayer::Clone(void *& _pArg)
{
	CPlayer* pInstance = new CPlayer(*this);
	if (FAILED(pInstance->NativeConstruct_Clone(_pArg)))
	{
		MSG_BOX("Camera_Free::Clone Error");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CPlayer::Free()
{
	__super::Free();
}