#include "..\Public\CLevel_Manager.h"
#include "CLevel.h"
#include "CGameInstance.h"

IMPLEMENT_SINGLETON(CLevel_Manager)

CLevel_Manager::CLevel_Manager() : m_pCurrentLevel(nullptr), m_iCurrentLevelIndex(0)
{
}

HRESULT CLevel_Manager::Open_Level(const _uint& _iLevel, CLevel*& _pLevel)
{
	if (nullptr == _pLevel)
		return E_FAIL;

	if (nullptr != m_pCurrentLevel)
	{
		CGameInstance* pGameInstance = CGameInstance::Get_Instance();
		Safe_AddRef(pGameInstance);
		pGameInstance->Release_Container(m_iCurrentLevelIndex);
		Safe_Release(pGameInstance);
	}
	Safe_Release(m_pCurrentLevel);
	m_pCurrentLevel = _pLevel;
	m_iCurrentLevelIndex = _iLevel;
	return S_OK;
}

HRESULT CLevel_Manager::Tick(const _float & _fDeltaSeconds)
{
	if (nullptr == m_pCurrentLevel)
		return E_FAIL;

	m_pCurrentLevel->Tick(_fDeltaSeconds);

	return S_OK;
}

HRESULT CLevel_Manager::LateTick(const _float & _fDeltaSeconds)
{
	if (nullptr == m_pCurrentLevel)
		return E_FAIL;

	m_pCurrentLevel->Late_Tick(_fDeltaSeconds);

	return S_OK;
}

void CLevel_Manager::Free()
{
	Safe_Release(m_pCurrentLevel);
	__super::Free();
}

