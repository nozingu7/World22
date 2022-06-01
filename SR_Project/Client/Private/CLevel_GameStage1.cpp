#include "stdafx.h"
#include "..\Public\CLevel_GameStage1.h"
#include "CGameInstance.h"
#include "CLevel_Loading.h"
#include "CTerrian_Stage1.h"
#include "CCamera_Free.h"
#include"CEffect.h"


CLevel_GameStage1::CLevel_GameStage1(const LPDIRECT3DDEVICE9 & _pDevice)
	: CLevel(_pDevice)
{

}

HRESULT CLevel_GameStage1::NativeConstruct()
{
	if (FAILED(__super::NativeConstruct()))
		return E_FAIL;

	if (FAILED(Ready_Layer_Terrian(TEXT("Layer_Terrian"))))
		return E_FAIL;

	if (FAILED(Ready_Layer_CameraFree(TEXT("Layer_CameraFree"))))
		return E_FAIL;

	if (FAILED(Ready_Layer_Effect(TEXT("Layer_Effect"))))
		return E_FAIL;

	return S_OK;
}

void CLevel_GameStage1::Tick(const _float & _fDeltaSeconds)
{
#ifdef _DEBUG
	cout << "GS1 _ TICK" << endl;
#endif
}

void CLevel_GameStage1::Late_Tick(const _float & _fDeletaSeconds)
{
#ifdef _DEBUG
	cout << "GS1 _ Late_Tick" << endl;
#endif
}

HRESULT CLevel_GameStage1::Render()
{
	return S_OK;
}

HRESULT CLevel_GameStage1::Ready_Layer_Terrian(const _tchar * _pLayerTag)
{
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();

	Safe_AddRef(pGameInstance);

	if (FAILED(pGameInstance->Clone_GameObject(LEVEL_GS1, _pLayerTag, TEXT("Prototype_GameObject_Terrian"))))
		return E_FAIL; 

	if (FAILED(pGameInstance->Clone_GameObject(LEVEL_GS1, _pLayerTag, TEXT("Prototype_GameObject_Sky"))))
		return E_FAIL;

	Safe_Release(pGameInstance);
	return S_OK;
}

HRESULT CLevel_GameStage1::Ready_Layer_CameraFree(const _tchar * _pLayerTag)
{
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);
	CCamera::CAMERACLONEDESC tCameraCloneDesc = 
	{ static_cast<_float>(g_iWinSizeX) / g_iWinSizeY ,0.2f, 500.f, D3DXToRadian(60.0f),
		_VECTOR3(0.f, -1.f, 1.f), _VECTOR3(0.f, 20.f, -20.f) };
	if (FAILED(pGameInstance->Clone_GameObject(LEVEL_GS1, _pLayerTag, 
		TEXT("Prototype_GameObject_Camera_Free"), &tCameraCloneDesc)))
		return E_FAIL;
	Safe_Release(pGameInstance);
	return S_OK;
}

HRESULT CLevel_GameStage1::Ready_Layer_Effect(const _tchar * _pLayerTag)
{
	CGameInstance*			pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	for (_uint i = 0; i < 30; ++i)
	{
		if (FAILED(pGameInstance->Clone_GameObject(LEVEL_GS1, _pLayerTag, TEXT("Prototype_GameObject_Effect"))))
			return E_FAIL;
	}

	Safe_Release(pGameInstance);

	return S_OK;
}

CLevel * CLevel_GameStage1::Create(LPDIRECT3DDEVICE9 & _pDevice, const LEVEL& _eLevel)
{
	CLevel* pLevel = nullptr;
	if (LEVEL_LOADING == _eLevel)
		pLevel = CLevel_Loading::Create(_pDevice, LEVEL_GS1);
	else
		pLevel = new CLevel_GameStage1(_pDevice);

	if (nullptr == pLevel)
	{
		MSG_BOX("LevelLoading Create Failed");
		Safe_Release(pLevel);
	}

	return pLevel;
}

void CLevel_GameStage1::Free()
{
	CLevel::Free();
}
