#include "imgui_internal.h"
#include "..\Public\CMainView.h"
#include"CGameInstance.h"
#include "CLevel_Tool.h"
#include "CFileDialog.h"
#include "CMyThread.h"

CMainView::CMainView(const LPDIRECT3DDEVICE9& _pDevice) :
	CIMGUI(_pDevice)
{
	m_bOpenWindow = true;
}

HRESULT CMainView::NativeConstruct()
{
	if (FAILED(__super::NativeConstruct()))
		return E_FAIL;
	
	m_imGViewPort.Size = ImVec2(static_cast<_float>(300), static_cast<_float>(720));

	m_tOwner = DOCKDESC("Parents", ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_MenuBar |  ImGuiWindowFlags_NoDecoration );
	m_tMainView = DOCKDESC("Main", ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoTitleBar| ImGuiWindowFlags_NoCollapse | 
		ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoDocking);
	m_tPerspective = DOCKDESC("Perspective", ImGuiWindowFlags_NoFocusOnAppearing);
	m_tHierarchy = DOCKDESC("Hierarchy", ImGuiWindowFlags_NoFocusOnAppearing);
	m_tGameView = DOCKDESC("GameView",  ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoFocusOnAppearing);
	m_tGameView.bControl = false;
	// AdImGui Class 
	if (FAILED(Add_ImGuiClass()))
		return E_FAIL;

	return S_OK;
}

HRESULT CMainView::Tick(const _float & _fDeltaSeconds)
{
	if (FAILED(__super::Tick(_fDeltaSeconds)))
		return E_FAIL;

	for_each(m_vecImGuiClass.begin(), m_vecImGuiClass.end(), [&](auto& iter) {	iter->Tick(_fDeltaSeconds); });
	return S_OK;
}

HRESULT CMainView::Late_Tick(const _float & _fDeltaSeconds)
{
	if(FAILED(__super::Late_Tick(_fDeltaSeconds)))
		return E_FAIL;

	for_each(m_vecImGuiClass.begin(), m_vecImGuiClass.end(), [&](auto& iter){	iter->Late_Tick(_fDeltaSeconds);});
	return S_OK;
}

HRESULT CMainView::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	for (auto& iter : m_vecImGuiClass)
	{
		if (nullptr != iter)
			iter->Render();
	}

	return S_OK;
}

HRESULT CMainView::Add_ImGuiClass()
{
	CIMGUI* pInstance = CFileDialog::Create(m_pGraphic_Device);
	/* Declare ImGui Class */
	if (nullptr == pInstance)
		return E_FAIL;
	m_vecImGuiClass.emplace_back(pInstance);
	return S_OK;
}

void CMainView::Show_Window()
{
//	ImGui::ShowDemoWindow();
	Main_Window();
}

void CMainView::Main_Window()
{
	if (true == m_tGameView.bControl)
	{
		{
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			ImVec2 size = ImGui::GetMainViewport()->WorkSize;
			size.x += 25.f;
			size.y += 25.f;
			ImGuiViewport* pViewPort = ImGui::GetMainViewport();
			ImGui::SetNextWindowSize(size, ImGuiCond_Appearing);
			ImGui::SetNextWindowPos(ImGui::GetMainViewport()->Pos, ImGuiCond_Appearing);
			ImGui::Begin(m_tGameView.pName, &m_tGameView.bControl, m_tGameView.imWindowFlag);
			ImGui::PopStyleVar(2);
			{
				ImGui::Image((void*)m_pSceneViewTexture, ImGui::GetMainViewport()->WorkSize);
			}

			// 레벨을 다시 로드 함..
			if (false == m_tGameView.bControl)
			{
				g_bGameRun = m_tGameView.bControl;
				CGameInstance* pInstance = CGameInstance::Get_Instance();
				Safe_AddRef(pInstance);
				CLevel* pLevel = CLevel_Tool::Create(m_pGraphic_Device, LEVEL_TOOL);
				pInstance->Open_Level(LEVEL_TOOL, pLevel);
				Safe_Release(pInstance);
			}
			ImGui::End();
		}
	}

	{
		// Main View
		ImGui::SetNextWindowSize(ImGui::GetMainViewport()->WorkSize, ImGuiCond_Appearing);
		ImGui::SetNextWindowPos(ImGui::GetMainViewport()->WorkPos, ImGuiCond_Appearing);
		ImGui::Begin(m_tMainView.pName, &m_tMainView.bControl, m_tMainView.imWindowFlag);
		ImGui::End();
	}

	ImGuiViewport* pViewPort = &m_imGViewPort;
	ImGui::SetNextWindowSize(pViewPort->Size, ImGuiCond_Appearing);
	ImGui::SetNextWindowPos(ImVec2(static_cast<_float>(g_iWinSizeX), 0.f), ImGuiCond_Appearing);
	ImGui::Begin(m_tOwner.pName, &m_bOpenWindow, m_tOwner.imWindowFlag);
	{
		// Menu Bar 
		ImGui::BeginMenuBar();
		{
			if (ImGui::BeginMenu("Open_ImGuiClass"))
			{
				for (auto& iter : m_vecImGuiClass)
				{
					if (nullptr != iter)
					{
						bool bIsOpen = iter->Is_OpenWindow();
						ImGui::MenuItem(iter->Get_Name().c_str(), NULL, &bIsOpen);
						iter->Set_Open(bIsOpen);
					}
				}
				ImGui::EndMenu();
			}
		}
		ImGui::EndMenuBar();

		// Start Button
		if (true == ImGui::Button(u8"Play"))
		{
			if (false == m_tGameView.bControl)
			{
				m_tGameView.bControl = true;
				g_bGameRun = m_tGameView.bControl;
				CGameInstance* pInstance = CGameInstance::Get_Instance();
				Safe_AddRef(pInstance);
				CLevel* pLevel = CLevel_Tool::Create(m_pGraphic_Device, LEVEL_ENGINE);
				pInstance->Open_Level(LEVEL_ENGINE, pLevel);
				Safe_Release(pInstance);
			}
		}
		// Window Setting
		m_tOwner.iID = ImGui::GetID(m_tOwner.pName);
		if (m_tOwner.bControl)
		{
			ImGui::DockBuilderRemoveNode(m_tOwner.iID); // Clear out existing layout
			ImGui::DockBuilderAddNode(m_tOwner.iID, 0); // Add empty node

			ImGuiID dock_main_id = m_tOwner.iID; // This variable will track the document node, however we are not using it here as we aren't docking anything into it.
			ImGuiID dock_id_prop = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Right, 0.5f, NULL, &dock_main_id);
			ImGuiID dock_id_Hier = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Right, 0.5f, NULL, &dock_main_id);

			m_tPerspective.iID = dock_id_prop;
			m_tHierarchy.iID = dock_id_Hier;
			// Perspective , Heirecky
			ImGui::DockBuilderDockWindow(m_tPerspective.pName, dock_id_prop);
			ImGui::DockBuilderDockWindow(m_tHierarchy.pName, dock_id_Hier);
			ImGui::DockBuilderFinish(m_tOwner.iID);

			m_tOwner.bControl = false;
		}
		ImGui::DockSpace(m_tOwner.iID);
		{
			// Properties
			ImGui::Begin(m_tPerspective.pName, &m_tPerspective.bControl, m_tPerspective.imWindowFlag);
			{

			}
			ImGui::End();
		}
		{
			// Hierachy
			ImGui::Begin(m_tHierarchy.pName, &m_tHierarchy.bControl, m_tHierarchy.imWindowFlag);
			{

			}
			ImGui::End();
		}
	}
	ImGui::End();
}

CMainView * CMainView::Create(const LPDIRECT3DDEVICE9& _pDevice)
{
	CMainView* pInstance = new CMainView(_pDevice);
	if (FAILED(pInstance->NativeConstruct()))
	{
		MSG_BOX("Tool -> CAnimEditor::Create Method Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CMainView::Free()
{
	for_each(m_vecImGuiClass.begin(), m_vecImGuiClass.end(), [&](auto& iter) { Safe_Release(iter); });
	__super::Free();
}
