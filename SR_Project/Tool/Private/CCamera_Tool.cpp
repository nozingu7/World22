#include "CCamera_Tool.h"
#include "..\Public\CCamera_Tool.h"
#include "CGameInstance.h"

CCamera_Tool::CCamera_Tool(const LPDIRECT3DDEVICE9 & _pDevice, void *& _pCameraInitData)
	: CCamera(_pDevice, _pCameraInitData)
{
}

CCamera_Tool::CCamera_Tool(const CCamera_Tool & _rhs)
	: CCamera(_rhs)
{
	m_pTransformComp = _rhs.m_pTransformComp;
	m_tCameraCloneDesc = _rhs.m_tCameraCloneDesc;
	Safe_AddRef(m_pTransformComp);
}

HRESULT CCamera_Tool::NativeConstruct_ProtoType()
{
	if (FAILED(__super::NativeConstruct_ProtoType()))
		return E_FAIL;

	if (FAILED(Add_Transform()))
		return E_FAIL;

	m_tCameraCloneDesc = { static_cast<_float>(g_iWinSizeX) / g_iWinSizeY ,0.2f, 500.f, D3DXToRadian(60.0f),
		_VECTOR3(0.f, -1.f, 1.f), _VECTOR3(0.f, 20.f, -20.f) };

	m_pTransformComp->LookAt(m_tCameraCloneDesc.v3Look);
	m_pTransformComp->Set_Position(m_tCameraCloneDesc.v3Pos);

	return S_OK;
}

HRESULT CCamera_Tool::NativeConstruct_Clone(void *& _pArg)
{
	return S_OK;
}

void CCamera_Tool::Tick(const _float & _fDeltaTime)
{
	if (true == g_bGameRun)
		return;

		Cam_Move(_fDeltaTime);
	__super::Tick(_fDeltaTime);
}

void CCamera_Tool::Late_Tick(const _float & _fDeltaTime)
{
	if (true == g_bGameRun)
		return;

	__super::Late_Tick(_fDeltaTime);
}

HRESULT CCamera_Tool::Render()
{
	return S_OK;
}

HRESULT CCamera_Tool::Cam_Move(const _float& _fDeltaSeconds)
{
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);
	if (pGameInstance->Get_DIKeyState(DIK_W) < 0)
		m_pTransformComp->Move_Forward(10.f, _fDeltaSeconds);
	if (pGameInstance->Get_DIKeyState(DIK_A) < 0)
		m_pTransformComp->Move_Left(10.f, _fDeltaSeconds);
	if (pGameInstance->Get_DIKeyState(DIK_D) < 0)
		m_pTransformComp->Move_Right(10.f, _fDeltaSeconds);
	if (pGameInstance->Get_DIKeyState(DIK_S) < 0)
		m_pTransformComp->Move_Back(10.f, _fDeltaSeconds);

	_long		MouseMove = 0;
	if (pGameInstance->Get_DIMButtonState(CInput_Device::DIMB_R) & 0x80)
	{
		if (MouseMove = pGameInstance->Get_DIMMoveState(CInput_Device::DIMM_X))
			m_pTransformComp->RotationAxisToTurn(_VECTOR3(0.f, 1.f, 0.f), D3DXToRadian(90.f), _fDeltaSeconds * MouseMove * 0.1f);

		if (MouseMove = pGameInstance->Get_DIMMoveState(CInput_Device::DIMM_Y))
			m_pTransformComp->RotationAxisToTurn(m_pTransformComp->Get_Right(), D3DXToRadian(90.f), _fDeltaSeconds * MouseMove * 0.1f);
	}

	Safe_Release(pGameInstance);
	return S_OK;
}

HRESULT CCamera_Tool::Find_Prototype_Transform()
{
	return E_NOTIMPL;
}

CCamera_Tool * CCamera_Tool::Create(const LPDIRECT3DDEVICE9 & _pDevice, void * _pInitData)
{
	CCamera_Tool* pInstance = new CCamera_Tool(_pDevice, _pInitData);
	if (FAILED(pInstance->NativeConstruct_ProtoType()))
	{
		MSG_BOX("CCamera_Free::Create is Faield");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CCamera_Tool::Clone(void *& _pArg)
{
	CCamera_Tool* pInstance = new CCamera_Tool(*this);
	if (FAILED(pInstance->NativeConstruct_Clone(_pArg)))
	{
		MSG_BOX("Camera_Free::Clone Error");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CCamera_Tool::Free()
{
	__super::Free();
}
