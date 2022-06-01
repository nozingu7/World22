#include "stdafx.h"
#include "..\Public\CLevel_Logo.h"
#include "CLevel_Loading.h"
#include "CLevel_GameStage1.h"
#include "CGameInstance.h"
#include "CBackGround.h"
#include "CCamera_Free.h"


CLevel_Logo::CLevel_Logo(const LPDIRECT3DDEVICE9 & _pDevice)
	: CLevel(_pDevice)
{

}

HRESULT CLevel_Logo::NativeConstruct()
{
	if (FAILED(__super::NativeConstruct()))
		return E_FAIL;

	if (FAILED(Ready_Layer_Background(TEXT("Layer_BackGround"))))
		return E_FAIL;

	if (FAILED(Ready_Layer_CameraFree(TEXT("Layer_CameraFree"))))
		return E_FAIL;

	return S_OK;
}

void CLevel_Logo::Tick(const _float & _fDeltaSeconds)
{
#ifdef _DEBUG
	cout << "Logo _ TICK" << endl;
#endif
}

void CLevel_Logo::Late_Tick(const _float & _fDeletaSeconds)
{
#ifdef _DEBUG
	cout << "Logo _ Late_Tick" << endl;
#endif
	if (GetAsyncKeyState(VK_RETURN))
	{
		CGameInstance* pGameInstance = CGameInstance::Get_Instance();
		Safe_AddRef(pGameInstance);
		CLevel* pLevel = CLevel_GameStage1::Create(m_pGraphic_Device, LEVEL_LOADING);
		if (nullptr == pLevel)
		{
			MSG_BOX("CMainApp::Open_Level() : Level is Not Created");
			Safe_Release(pGameInstance);
			return;
		}
		pGameInstance->Open_Level(LEVEL_LOGO, pLevel);
		Safe_Release(pGameInstance);
	}
}

HRESULT CLevel_Logo::Render()
{
	return S_OK;
}

HRESULT CLevel_Logo::Ready_Layer_Background(const _tchar * _pLayerTag)
{
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();

	Safe_AddRef(pGameInstance);

	if (FAILED(pGameInstance->Clone_GameObject(LEVEL_LOGO, _pLayerTag, TEXT("Prototype_GameObject_BackGround"))))
		return E_FAIL;

	Safe_Release(pGameInstance);
	return S_OK;
}

HRESULT CLevel_Logo::Ready_Layer_CameraFree(const _tchar * _pLayerTag)
{
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	CCamera::CAMERACLONEDESC tCameraCloneDesc = { static_cast<_float>(g_iWinSizeX) / g_iWinSizeY ,0.2f, 300.f, D3DXToRadian(60.0f),
		_VECTOR3(0.f, 0.f, -1.f), _VECTOR3(0.f, 0.f, 100.f) };
	if (FAILED(pGameInstance->Clone_GameObject(LEVEL_LOGO, _pLayerTag, TEXT("Prototype_GameObject_Camera_Free"), &tCameraCloneDesc)))
		return E_FAIL;

	Safe_Release(pGameInstance);
	return S_OK;
}

CLevel * CLevel_Logo::Create(LPDIRECT3DDEVICE9& _pDevice, const LEVEL& _eLevel)
{
	CLevel* pLevel = nullptr;
	if (LEVEL_LOADING == _eLevel)
		pLevel = CLevel_Loading::Create(_pDevice, LEVEL_LOGO);
	else
		pLevel = new CLevel_Logo(_pDevice);

	if (nullptr == pLevel)
	{
		MSG_BOX("LevelLoading Create Failed");
		Safe_Release(pLevel);
	}

	return pLevel;
}

void CLevel_Logo::Free()
{
	CLevel::Free();
}
