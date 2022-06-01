#include "CCamera_Engine.h"
#include "..\Public\CCamera_Engine.h"
#include "CGameInstance.h"

CCamera_Engine::CCamera_Engine(const LPDIRECT3DDEVICE9 & _pDevice, void *& _pCameraInitData)
	: CCamera(_pDevice, _pCameraInitData), m_pTargetTransform(nullptr)
{
}

CCamera_Engine::CCamera_Engine(const CCamera_Engine & _rhs)
	: CCamera(_rhs), m_pTargetTransform(nullptr)
{

}

HRESULT CCamera_Engine::NativeConstruct_ProtoType()
{
	if (FAILED(__super::NativeConstruct_ProtoType()))
		return E_FAIL;

	return S_OK;
}

HRESULT CCamera_Engine::NativeConstruct_Clone(void *& _pArg)
{
	if (FAILED(__super::NativeConstruct_Clone(_pArg)))
		return E_FAIL;

	Set_Target();

	return S_OK;
}

void CCamera_Engine::Tick(const _float & _fDeltaTime)
{
	if (false == g_bGameRun)
		return;

	Cam_Move(_fDeltaTime);
	__super::Tick(_fDeltaTime);
}

void CCamera_Engine::Late_Tick(const _float & _fDeltaTime)
{
	if (false == g_bGameRun)
		return;

	__super::Late_Tick(_fDeltaTime);
}

HRESULT CCamera_Engine::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	return S_OK;
}

HRESULT CCamera_Engine::Cam_Move(const _float & _fDeltaSeconds)
{
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	_long		MouseMove = 0;

	if (pGameInstance->Get_DIMButtonState(CInput_Device::DIMB_R) & 0x80)
	{
		if (MouseMove = pGameInstance->Get_DIMMoveState(CInput_Device::DIMM_X))
			m_pTransformComp->RotationAxisToTurn(_VECTOR3(0.f, 1.f, 0.f), D3DXToRadian(90.f), _fDeltaSeconds * MouseMove * 0.1f);

		if (MouseMove = pGameInstance->Get_DIMMoveState(CInput_Device::DIMM_Y))
			m_pTransformComp->RotationAxisToTurn(m_pTransformComp->Get_Right(), D3DXToRadian(90.f), _fDeltaSeconds * MouseMove * 0.1f);
	}

	m_pTransformComp->Set_WorldMatrix(m_pTargetTransform->Get_WorldMatrix());

	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CCamera_Engine::Set_Target()
{
	if (true == g_bGameRun)
	{
		CGameInstance* pGameInstance = CGameInstance::Get_Instance();
		Safe_AddRef(pGameInstance);

		CGameObject* pTarget = pGameInstance->Find_GameObject(LEVEL::LEVEL_ENGINE, TEXT("Layer_Player"));
		m_pTargetTransform = static_cast<CTransform*>(pTarget->Get_Component(TEXT("Com_Transform")));
		Safe_AddRef(m_pTargetTransform);

		Safe_Release(pGameInstance);

		if (nullptr == m_pTargetTransform)
			return E_FAIL;
	}
	return S_OK;
}

CCamera_Engine * CCamera_Engine::Create(const LPDIRECT3DDEVICE9 & _pDevice, void * _pInitData)
{
	CCamera_Engine* pInstance = new CCamera_Engine(_pDevice, _pInitData);
	if (FAILED(pInstance->NativeConstruct_ProtoType()))
	{
		MSG_BOX("CCamera_Free::Create is Faield");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CCamera_Engine::Clone(void *& _pArg)
{
	CCamera_Engine* pInstance = new CCamera_Engine(*this);
	if (FAILED(pInstance->NativeConstruct_Clone(_pArg)))
	{
		MSG_BOX("Camera_Free::Clone Error");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CCamera_Engine::Free()
{
	Safe_Release(m_pTargetTransform);
	__super::Free();
}
