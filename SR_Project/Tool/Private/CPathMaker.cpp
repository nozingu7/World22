#include "CPathMaker.h"
#include "..\Public\CPathMaker.h"
#include "CGameInstance.h"

CPathMaker::CPathMaker(const LPDIRECT3DDEVICE9 & _pDevice)
	: CIMGUI(_pDevice), m_pPathPosList(nullptr)
{
}

HRESULT CPathMaker::NativeConstruct()
{
	if (FAILED(__super::NativeConstruct()))
		return E_FAIL;

	m_strWindowName = "PathMaker";
	m_pPathPosList = new PATHLIST[1];

	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);
	{
		for (_uint i = 0; i < 1; ++i)
		{
			
		}
	}
	Safe_Release(pGameInstance);
	return S_OK;
}

HRESULT CPathMaker::Tick(const _float & _fDeltaSeconds)
{
	if (FAILED(__super::Tick(_fDeltaSeconds)))
		return E_FAIL;

	return S_OK;
}

HRESULT CPathMaker::Late_Tick(const _float & _fDeltaSeconds)
{
	if (FAILED(__super::Late_Tick(_fDeltaSeconds)))
		return E_FAIL;

	return S_OK;
}

HRESULT CPathMaker::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	return S_OK;
}

void CPathMaker::Show_Window()
{
	__super::Show_Window();
	ImVec2 InitPos = ImVec2{ static_cast<_float>(g_iWinSizeX + 50),  50.f };
	ImGui::SetNextWindowPos(InitPos, ImGuiCond_Appearing);
	ImGui::SetNextWindowSize(ImVec2(500.f, 500.f), ImGuiCond_Appearing);
	ImGui::Begin(m_strWindowName.c_str(), &m_bOpenWindow);
	{

	}
	ImGui::End();
}

CPathMaker * CPathMaker::Create(const LPDIRECT3DDEVICE9 & _pDevice)
{
	CPathMaker* pInstance = new CPathMaker(_pDevice);
	if (FAILED(pInstance->NativeConstruct()))
	{
		MSG_BOX("Tool -> CPathMaker::Create");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CPathMaker::Free()
{
	Safe_Delete_Array(m_pPathPosList);
	__super::Free();
}
