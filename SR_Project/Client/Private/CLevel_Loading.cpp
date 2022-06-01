#include "stdafx.h"
#include "..\Public\CLevel_Loading.h"
#include"CLevel_Logo.h"
#include"CLevel_GameStage1.h"
#include "CGameInstance.h"

CLevel_Loading::CLevel_Loading(const LPDIRECT3DDEVICE9 & _pDevice, const LEVEL& _eLevel)
	: CLevel(_pDevice), m_eNextLevel(_eLevel), m_pLoader(nullptr)
{

}

HRESULT CLevel_Loading::NativeConstruct()
{
	if (FAILED(CLevel::NativeConstruct()))
		return E_FAIL;

	if (nullptr != m_pLoader)
		return E_FAIL;

	m_pLoader = CLoader::Create(m_pGraphic_Device, m_eNextLevel);
	if (nullptr == m_pLoader)
		return E_FAIL;

	return S_OK;
}

void CLevel_Loading::Tick(const _float & _fDeltaSeconds)
{
}

void CLevel_Loading::Late_Tick(const _float & _fDeletaSeconds)
{
	if (nullptr == m_pLoader)
		return;
	if (m_pLoader->Is_LoadingEnd())
	{
		if (GetAsyncKeyState(VK_SPACE))
			Open_Level(m_pGraphic_Device);
	}
}

HRESULT CLevel_Loading::Render()
{
	return S_OK;
}

HRESULT CLevel_Loading::Open_Level(LPDIRECT3DDEVICE9& _pDevice)
{
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	if (nullptr == pGameInstance)
		return E_FAIL;

	Safe_AddRef(pGameInstance);

	CLevel* pLevel = nullptr;
	switch (m_eNextLevel)
	{
	case LEVEL_LOGO:
		pLevel = CLevel_Logo::Create(_pDevice, m_eNextLevel);
		break;
	case LEVEL_GS1:
		pLevel = CLevel_GameStage1::Create(_pDevice, m_eNextLevel);
		break;
	}

	if (nullptr == pLevel)
	{
		MSG_BOX("HRESULT CLevel_Loading::Open_Level(LPDIRECT3DDEVICE9& _pDevice)\n Method Create Faield");
		Safe_Release(pGameInstance);
		return E_FAIL;
	}

	if (FAILED(pLevel->NativeConstruct()))
	{
		MSG_BOX("HRESULT CLevel_Loading::Open_Level(LPDIRECT3DDEVICE9& _pDevice)\n Method NativeConstruct Run Faield");
		Safe_Release(pGameInstance);
		return E_FAIL;
	}

	//pGameInstance
	pGameInstance->Open_Level(m_eNextLevel, pLevel);
	Safe_Release(pGameInstance);
	return S_OK;
}

CLevel * CLevel_Loading::Create(LPDIRECT3DDEVICE9 & _pDevice, const LEVEL & _eLevel)
{
	CLevel* pLevel = new CLevel_Loading(_pDevice, _eLevel);
	if (FAILED(pLevel->NativeConstruct()))
	{
		MSG_BOX("LevelLoading Create Failed");
		Safe_Release(pLevel);
	}

	return pLevel;
}

void CLevel_Loading::Free()
{
	CLevel::Free();
	Safe_Release(m_pLoader);
}
