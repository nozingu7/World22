#include "CLevel_Tool.h"
#include "CGameInstance.h"
#include"CCamera.h"
#include "CMonster.h"
#include "Tool_Macro.h"

CLevel_Tool::CLevel_Tool(const LPDIRECT3DDEVICE9 & _pDevice, const _uint& _iCurrentLevel)
	: CLevel(_pDevice), m_iCurrentLevel(_iCurrentLevel)
{

}

HRESULT CLevel_Tool::NativeConstruct()
{
	if (FAILED(__super::NativeConstruct()))
		return E_FAIL;

	if (FAILED(Ready_Player(L"Layer_Player")))
		return E_FAIL;

	if (FAILED(Ready_Background(L"Layer_Background")))
		return E_FAIL;

	if (FAILED(Ready_Camera(L"Layer_Camera")))
		return E_FAIL;

	if (FAILED(Ready_Monster(L"Layer_Monster")))
		return E_FAIL;

	if (FAILED(Ready_GameObject(LAYER_UI)))
		return E_FAIL;
	
	return S_OK;
}

void CLevel_Tool::Tick(const _float & _fDeltaSeconds)
{
	__super::Tick(_fDeltaSeconds);
}

void CLevel_Tool::Late_Tick(const _float & _fDeletaSeconds)
{
	__super::Late_Tick(_fDeletaSeconds);
}

HRESULT CLevel_Tool::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	return S_OK;
}
HRESULT CLevel_Tool::Ready_Background(const _tchar * _pLayerTag)
{
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	if (FAILED(pGameInstance->Clone_GameObject(m_iCurrentLevel, _pLayerTag, TEXT("Prototype_GameObject_Terrian"))))
		return E_FAIL;

	if (FAILED(pGameInstance->Clone_GameObject(m_iCurrentLevel, _pLayerTag, TEXT("Prototype_GameObject_Sword"))))
		return E_FAIL;

	Safe_Release(pGameInstance);
	return S_OK;
}

HRESULT CLevel_Tool::Ready_Player(const _tchar * _pLayerTag)
{
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	//CCharacter::CHARINFO tCharacterInfo = { 100.f,100.f,50.f,50.f,20.f,0.f,5.f,10.f,0.f };
	CCharacter::CHARINFO tCharacterInfo;
	tCharacterInfo.fMaxHp = 100.f;
	tCharacterInfo.fCurHp = 100.f;
	tCharacterInfo.fMaxMp = 50.f;
	tCharacterInfo.fCurMp = 50.f;
	tCharacterInfo.fAtkPower = 20.f;
	tCharacterInfo.fArmor = 0.f;
	tCharacterInfo.fCurSpeed = 5.f;
	tCharacterInfo.fMaxSpeed = 10.f;
	tCharacterInfo.fExp = 0.f;

	if (FAILED(pGameInstance->Clone_GameObject(m_iCurrentLevel, _pLayerTag, TEXT("Prototype_GameObject_Player"), &tCharacterInfo)))
		return E_FAIL;

	Safe_Release(pGameInstance);
	return S_OK;
}

HRESULT CLevel_Tool::Ready_Camera(const _tchar * _pLayerTag)
{
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	if (FAILED(pGameInstance->Clone_GameObject(m_iCurrentLevel, _pLayerTag, TEXT("Prototype_GameObject_CameraTool"))))
		return E_FAIL;

	CCamera::CAMERACLONEDESC tCameraCloneDesc = { static_cast<_float>(g_iWinSizeX) / g_iWinSizeY, 0.2f, 500.f, D3DXToRadian(60.0f),
		_VECTOR3(0.f, -1.f, 1.f), _VECTOR3(0.f, 20.f, -20.f) };

	if (FAILED(pGameInstance->Clone_GameObject(m_iCurrentLevel, _pLayerTag, TEXT("Prototype_GameObject_CameraEngine"), &tCameraCloneDesc)))
		return E_FAIL;

	Safe_Release(pGameInstance);
	return S_OK;
}
HRESULT CLevel_Tool::Ready_Monster(const _tchar * _pLayerTag)
{
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);
	{
		if (FAILED(pGameInstance->Clone_GameObject(m_iCurrentLevel, _pLayerTag, L"Prototype_GameObject_Monster")))
			return E_FAIL;
	}
	Safe_Release(pGameInstance);
	return S_OK;
}

HRESULT CLevel_Tool::Ready_GameObject(const _tchar* _pLayerTag)
{
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	if (FAILED(pGameInstance->Clone_GameObject(m_iCurrentLevel, _pLayerTag, PROTO_LAYER_UI)))
		return E_FAIL;

	Safe_Release(pGameInstance);
	return S_OK;
}

CLevel * CLevel_Tool::Create(LPDIRECT3DDEVICE9 & _pDevice, const _uint& _iLevel)
{
	CLevel_Tool* pLevel = new CLevel_Tool(_pDevice, _iLevel);
	if (FAILED(pLevel->NativeConstruct()))
	{
		MSG_BOX("CLevel_Tool::Create Failed");
		Safe_Release(pLevel);
	}
	return pLevel;
}

void CLevel_Tool::Free()
{
	__super::Free();
}
