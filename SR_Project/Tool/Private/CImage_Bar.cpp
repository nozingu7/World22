#include "..\Public\CImage_Bar.h"
#include "CGameInstance.h"

CImage_Bar::CImage_Bar(const LPDIRECT3DDEVICE9 & _pDevice)
	: CUI_Default(_pDevice)
{
}

CImage_Bar::CImage_Bar(const CImage_Bar & _pProtoType)
	: CUI_Default(_pProtoType)
{
}

HRESULT CImage_Bar::NativeConstruct_ProtoType()
{
	if (FAILED(__super::NativeConstruct_ProtoType()))
		return E_FAIL;

	return S_OK;
}

HRESULT CImage_Bar::NativeConstruct_Clone(void *& pArg)
{
	if (FAILED(__super::NativeConstruct_Clone(pArg)))
		return E_FAIL;

	if (FAILED(Add_Component()))
		return E_FAIL;

	m_eUIRender = RENDERMODE::MODE_OVERLAY;
	m_eUIType = UITYPE::UI_IMAGE;

	ZeroMemory(&m_tUiRect, sizeof(UIRECT));
	m_tUiRect.m_fWidth = 100.f;
	m_tUiRect.m_fHeight = 200.f;
	m_tUiRect.m_vPivot = _VECTOR2(0.5f, 0.5f);
	m_tUiRect.m_vAnchors = _VECTOR2(0.5f, 0.5f);

	m_vCenter = _VECTOR2(m_tUiRect.m_fWidth * m_tUiRect.m_vPivot.x, m_tUiRect.m_fHeight * m_tUiRect.m_vPivot.y);

	// 원점(0, 0, 0) 기준, 직교 투영 (wincx, wincy)
	D3DXMatrixOrthoLH(&m_fProjMatrix, (_float)g_iWinSizeX, (_float)g_iWinSizeY, 0.f, 1.f);

	return S_OK;
}

void CImage_Bar::Tick(const _float & _fDeltaTime)
{
	__super::Tick(_fDeltaTime);
}

void CImage_Bar::Late_Tick(const _float & _fDeltaTime)
{
	__super::Late_Tick(_fDeltaTime);

	// win 좌표 기준 중점
	_VECTOR3	vWorldPos = {
		m_vCenter.x - (g_iWinSizeX * m_tUiRect.m_vAnchors.x),
		-m_vCenter.y + (g_iWinSizeY * m_tUiRect.m_vAnchors.y),
		1.f
	};

	m_pTransformComp->Set_Scale(_VECTOR3(m_tUiRect.m_fWidth, m_tUiRect.m_fHeight, 1.f));
	m_pTransformComp->Set_Position(vWorldPos);

	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	pGameInstance->Add_RenderObj(CRenderer_Manager::RENDER_UI, this);

	Safe_Release(pGameInstance);
}

HRESULT CImage_Bar::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(m_pTextrueComp->Bind_Texture(10)))
		return E_FAIL;

	// update에서 구한 matrix 장치 bind
	if (FAILED(m_pTransformComp->Bind_WorldMatrix()))
		return E_FAIL;

	if (FAILED(__super::Bind_OrthoMatrix()))
		return E_FAIL;

	if (FAILED(__super::SetUp_RenderState()))
		return E_FAIL;

	if (FAILED(m_pVIBufferComp->Render()))
		return E_FAIL;

	if (FAILED(__super::Release_RenderState()))
		return E_FAIL;

	return S_OK;
}

HRESULT CImage_Bar::Add_Component()
{
	if (FAILED(__super::Add_Component()))
		return E_FAIL;

	return S_OK;
}


CImage_Bar * CImage_Bar::Create(const LPDIRECT3DDEVICE9 & _pDevice)
{
	CImage_Bar* pInstance = new CImage_Bar(_pDevice);
	if (FAILED(pInstance->NativeConstruct_ProtoType()))
	{
		MSG_BOX("Create Failed : Prototype CImage_Bar");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CImage_Bar::Clone(void *& _pArg)
{
	CImage_Bar* pInstance = new CImage_Bar(*this);
	if (FAILED(pInstance->NativeConstruct_Clone(_pArg)))
	{
		MSG_BOX("Create Failed : Clone CImage_Bar");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CImage_Bar::Free()
{
	__super::Free();
}
