#include "stdafx.h"
#include "..\Public\CCamera_Free.h"
#include "CComponent_Manager.h"
#include "CGameInstance.h"

CCamera_Free::CCamera_Free(const LPDIRECT3DDEVICE9 & _pDevice, void*& _pInitDesc)
	: CCamera(_pDevice, _pInitDesc)
{
}

CCamera_Free::CCamera_Free(const CCamera_Free & _rhs)
	: CCamera(_rhs)
{
}

HRESULT CCamera_Free::NativeConstruct_ProtoType()
{
	if (FAILED(__super::NativeConstruct_ProtoType()))
		return E_FAIL;

	return S_OK;
}

HRESULT CCamera_Free::NativeConstruct_Clone(void *& pArg)
{
	if (FAILED(__super::NativeConstruct_Clone(pArg)))
		return E_FAIL;

	return S_OK;
}

void CCamera_Free::Tick(const _float & _fDeltaTime)
{
	Camera_Move(_fDeltaTime);
	__super::Tick(_fDeltaTime);
}

void CCamera_Free::Late_Tick(const _float & _fDeltaTime)
{
	__super::Late_Tick(_fDeltaTime);
}

HRESULT CCamera_Free::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	return S_OK;
}

void CCamera_Free::Camera_Move(const _float& _fDeltaTime)
{
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);
	if (pGameInstance->Get_DIKeyState(DIK_W) < 0)
		m_pTransformComp->Move_Forward(10.f, _fDeltaTime);
	if (pGameInstance->Get_DIKeyState(DIK_A) < 0)
		m_pTransformComp->Move_Left(10.f, _fDeltaTime);
	if (pGameInstance->Get_DIKeyState(DIK_D) < 0)
		m_pTransformComp->Move_Right(10.f, _fDeltaTime);
	if (pGameInstance->Get_DIKeyState(DIK_S) < 0)
		m_pTransformComp->Move_Back(10.f, _fDeltaTime);

	_long		MouseMove = 0;
	if (MouseMove = pGameInstance->Get_DIMMoveState(CInput_Device::DIMM_X))
		m_pTransformComp->RotationAxisToTurn(_VECTOR3(0.f, 1.f, 0.f), D3DXToRadian(90.f),_fDeltaTime * MouseMove * 0.1f);

	if (MouseMove = pGameInstance->Get_DIMMoveState(CInput_Device::DIMM_Y))
		m_pTransformComp->RotationAxisToTurn(m_pTransformComp->Get_Right(), D3DXToRadian(90.f), _fDeltaTime * MouseMove * 0.1f);

	Safe_Release(pGameInstance);
}

CCamera_Free * CCamera_Free::Create(const LPDIRECT3DDEVICE9 & _pDevice, void* _pInitDesc)
{
	CCamera_Free* pInstance = new CCamera_Free(_pDevice, _pInitDesc);
	if (FAILED(pInstance->NativeConstruct_ProtoType()))
	{
		MSG_BOX("CCamera_Free::Create is Faield");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CCamera_Free::Clone(void *& _pArg)
{
	CCamera_Free* pInstance = new CCamera_Free(*this);
	if (FAILED(pInstance->NativeConstruct_Clone(_pArg)))
	{
		MSG_BOX("Camera_Free::Clone Error");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CCamera_Free::Free()
{
	__super::Free();
}
