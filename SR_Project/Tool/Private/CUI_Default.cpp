#include "CUI_Default.h"
#include "CGameInstance.h"

CUI_Default::CUI_Default(const LPDIRECT3DDEVICE9 & _pDevice)
	: CUserInterFace(_pDevice), 
	m_eUIRender(MODE_END), m_eUIType(UI_END), m_iSortOrder(0),
	m_pTransformComp(nullptr), m_pVIBufferComp(nullptr), m_pTextrueComp(nullptr)
{
	ZeroMemory(&m_tUiRect, sizeof(UIRECT));
	ZeroMemory(&m_vCenter, sizeof(_VECTOR2));
	D3DXMatrixIdentity(&m_fProjMatrix);
}

CUI_Default::CUI_Default(const CUI_Default & _pProtoType)
	: CUserInterFace(_pProtoType),
	m_eUIRender(MODE_END), m_eUIType(UI_END), m_iSortOrder(0),
	m_tUiRect(_pProtoType.m_tUiRect), m_vCenter(_pProtoType.m_vCenter), m_fProjMatrix(_pProtoType.m_fProjMatrix),
	m_pTransformComp(nullptr), m_pVIBufferComp(nullptr), m_pTextrueComp(nullptr)
{
}

HRESULT CUI_Default::NativeConstruct_ProtoType()
{
	if (FAILED(__super::NativeConstruct_ProtoType()))
		return E_FAIL;

	return S_OK;
}

HRESULT CUI_Default::NativeConstruct_Clone(void *& pArg)
{
	if (FAILED(__super::NativeConstruct_Clone(pArg)))
		return E_FAIL;

	return S_OK;
}

void CUI_Default::Tick(const _float & _fDeltaTime)
{
	__super::Tick(_fDeltaTime);

	Update_Mouse();
}

void CUI_Default::Late_Tick(const _float & _fDeltaTime)
{
	__super::Late_Tick(_fDeltaTime);


}

HRESULT CUI_Default::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	return S_OK;
}

HRESULT CUI_Default::Add_Component()
{
	if (FAILED(CGameObject::Add_Component((CComponent**)&m_pTransformComp, COMP_TRANSFORM, LEVEL_STATIC, PROTO_COMP_TRANSFORM)))
		return E_FAIL;

	if (FAILED(CGameObject::Add_Component((CComponent**)&m_pVIBufferComp, COMP_VB_RECT, LEVEL_STATIC, PROTO_COMP_VB_RECT)))
		return E_FAIL;

	if (FAILED(CGameObject::Add_Component((CComponent**)&m_pTextrueComp, COMP_TEXTRUE_TEST, LEVEL_STATIC, PROTO_COMP_TEXTURE_TEST)))
		return E_FAIL;

	return S_OK;
}


HRESULT CUI_Default::Bind_OrthoMatrix()
{
	if (!m_pGraphic_Device)
		return E_FAIL;

	_float4x4	fViewMatrix;	// orthographic

	m_pGraphic_Device->SetTransform(D3DTS_VIEW, D3DXMatrixIdentity(&fViewMatrix));
	m_pGraphic_Device->SetTransform(D3DTS_PROJECTION, &m_fProjMatrix);

	return S_OK;
}

HRESULT CUI_Default::BillBoard()
{
	if (!m_pGraphic_Device)
		return E_FAIL;

	_float4x4	fViewMatrix;	// perspective

	m_pGraphic_Device->GetTransform(D3DTS_VIEW, &fViewMatrix);
	D3DXMatrixInverse(&fViewMatrix, nullptr, &fViewMatrix);

	// 카메라 world 회전 -> 객체 적용
	m_pTransformComp->Set_Right(*(_VECTOR3*)&fViewMatrix.m[0][0]);
	m_pTransformComp->Set_Look(*(_VECTOR3*)&fViewMatrix.m[2][0]);

	return S_OK;
}

void CUI_Default::Update_Mouse()
{
	POINT	tMouse;
	GetCursorPos(&tMouse);
	ScreenToClient(g_hWnd, &tMouse);	// screen view

	RECT	tUiRect;
	SetRect(&tUiRect, 0, 0, (int)m_tUiRect.m_fWidth, (int)m_tUiRect.m_fHeight);

	if (PtInRect(&tUiRect, tMouse))
	{
		//MSG_BOX("충돌");
		return;
	}
}


HRESULT CUI_Default::SetUp_RenderState()
{
	if (FAILED(__super::SetUp_RenderState()))
		return E_FAIL;

	m_pGraphic_Device->SetRenderState(D3DRS_ZENABLE, FALSE);

	return S_OK;
}

HRESULT CUI_Default::Release_RenderState()
{
	if (FAILED(__super::Release_RenderState()))
		return E_FAIL;

	m_pGraphic_Device->SetRenderState(D3DRS_ZENABLE, FALSE);

	return S_OK;
}


void CUI_Default::Free()
{
	__super::Free();

	Safe_Release(m_pTransformComp);
	Safe_Release(m_pVIBufferComp);
	Safe_Release(m_pTextrueComp);
}
