#include "..\Public\CSword.h"
#include "CGameInstance.h"

CSword::CSword(const LPDIRECT3DDEVICE9 & _pDevice)
	:CWeapon(_pDevice)
{
}

CSword::CSword(const CSword & _rhs)
	:CWeapon(_rhs)
{
}

HRESULT CSword::NativeConstruct_ProtoType()
{
	if (FAILED(__super::NativeConstruct_ProtoType()))
		return E_FAIL;

	return S_OK;
}

HRESULT CSword::NativeConstruct_Clone(void *& pArg)
{
	if (FAILED(__super::NativeConstruct_Clone(pArg)))
		return E_FAIL;

	if (FAILED(Add_Component()))
		return E_FAIL;

	m_pTransformComp->Set_Position(_VECTOR3(0.f, 1.f, 0.f));

	return S_OK;
}

void CSword::Tick(const _float & _fDeltaTime)
{
	__super::Tick(_fDeltaTime);

	//Fly(_fDeltaTime);
}

void CSword::Late_Tick(const _float & _fDeltaTime)
{
	__super::Late_Tick(_fDeltaTime);

	CGameInstance*			pGameInstance = CGameInstance::Get_Instance();

	Safe_AddRef(pGameInstance);

	pGameInstance->Add_RenderObj(CRenderer_Manager::RENDER_NONALPHABLEND, this);

	Safe_Release(pGameInstance);
}

HRESULT CSword::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(m_pTransformComp->Bind_WorldMatrix()))
		return E_FAIL;

	if (FAILED(m_pTextureComp->Bind_Texture(0)))
		return E_FAIL;

	if (FAILED(SetUp_RenderState()))
		return E_FAIL;

	if (FAILED(m_pVIBufferComp->Render()))
		return E_FAIL;

	if (FAILED(Release_RenderState()))
		return E_FAIL;

	return S_OK;
}

HRESULT CSword::Add_Component()
{
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	if (FAILED(CGameObject::Add_Component((CComponent**)&m_pVIBufferComp, L"Com_Sword", LEVEL_STATIC, L"PROTO_COMP_VIBUFFER_SWORD")))
		return E_FAIL;

	if (FAILED(CGameObject::Add_Component((CComponent**)&m_pTransformComp, L"Com_Transform", LEVEL_STATIC, L"PROTO_COMP_TRANSFORM")))
		return E_FAIL;

	if (FAILED(CGameObject::Add_Component((CComponent**)&m_pTextureComp, L"Com_Texture", LEVEL_STATIC, L"PROTO_COMP_TEXTURE_TEST")))
		return E_FAIL;

	Safe_Release(pGameInstance);
	return S_OK;
}

HRESULT CSword::Show_ToolTip()
{
	if (nullptr == m_pToolTip)
		return E_FAIL;

	return S_OK;
}

HRESULT CSword::SetUp_RenderState()
{
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;

	m_pGraphic_Device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHAREF, 254);
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	return S_OK;
}

HRESULT CSword::Release_RenderState()
{
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;

	m_pGraphic_Device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	return S_OK;
}

void CSword::Fly(_float fDeltaTime)
{
	// 220530 ��ǥ ���� �ӽ÷� �ۼ��� �ڵ� ������ �ʿ���.
	_VECTOR3 vPos = m_pTransformComp->Get_Position();
	_VECTOR3 vLimit = _VECTOR3(0.f, 0.5f, 0.f);

	//// ����Ʈ���� �۾����� Up = true;
	if (1.f < vPos.y)
		m_bIsDown = true;
	else if (vLimit.y > vPos.y)
		m_bIsDown = false;

	m_fAccel = -vPos.y;
}

void CSword::Move_Up(_float fDeltaTime)
{
}

void CSword::Move_Down(_float fDeltaTime)
{
}

CSword * CSword::Create(LPDIRECT3DDEVICE9 & _pDevice)
{
	CSword* pInstance = new CSword(_pDevice);
	if (FAILED(pInstance->NativeConstruct_ProtoType()))
	{
		MSG_BOX("Failed To Create : CSword");
		Safe_Release(pInstance);
	}	
	return pInstance;
}

CGameObject * CSword::Clone(void*& pArg)
{
	CSword* pInstance = new CSword(*this);
	if (FAILED(pInstance->NativeConstruct_Clone(pArg)))
	{
		MSG_BOX("Failed To Create : CSword Clone");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CSword::Free()
{
	__super::Free();

	Safe_Release(m_pTextureComp);
	Safe_Release(m_pTransformComp);
	Safe_Release(m_pVIBufferComp);
}
