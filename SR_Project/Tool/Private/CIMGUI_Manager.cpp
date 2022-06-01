#include "CIMGUI_Manager.h"
#include "..\Public\CIMGUI_Manager.h"
#include "CIMGUI.h"
#include "CMainView.h"
#include"CGameInstance.h"

IMPLEMENT_SINGLETON(CIMGUI_Manager)

CIMGUI_Manager::CIMGUI_Manager() : 
	m_pGraphic_Device(nullptr), m_pMainView(nullptr), 
	m_pGameInstance(CGameInstance::Get_Instance())
{
	Safe_AddRef(m_pGameInstance);
}

HRESULT CIMGUI_Manager::NativeConstruct(const LPDIRECT3DDEVICE9 & _pDevice)
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

	io.BackendFlags |= ImGuiBackendFlags_PlatformHasViewports;
	io.BackendFlags |= ImGuiBackendFlags_RendererHasViewports;
	io.BackendFlags |= ImGuiBackendFlags_RendererHasVtxOffset;
	io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

	RECT rc;
	GetClientRect(g_hWnd, &rc);

	ImVec2 vec;
	vec.x = (float)rc.right;
	vec.y = (float)rc.bottom;
	io.DisplaySize = vec;

	vec.x = (float)g_iWinSizeX;
	vec.y = (float)g_iWinSizeY;
	io.DisplayFramebufferScale = vec;

//	io.Fonts->AddFontFromFileTTF("C\\Windows\\Fonts\\malgun.ttf", 18.f, NULL, io.Fonts->GetGlyphRangesKorean());
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}
	// Setup Platform/Renderer backends
	ImGui_ImplWin32_Init(g_hWnd);
	ImGui_ImplDX9_Init(_pDevice);
	Safe_AddRef(_pDevice);
	m_pGraphic_Device = _pDevice;

	if (FAILED(Make_AmGui()))
		return E_FAIL;

	return S_OK;
}

void CIMGUI_Manager::Tick(const _float & _fDeltaSeconds)
{
	m_pMainView->Tick(_fDeltaSeconds);
}

void CIMGUI_Manager::Late_Tick(const _float & _fDeltaSeconds)
{
	m_pMainView->Late_Tick(_fDeltaSeconds);
}

HRESULT CIMGUI_Manager::Render()
{
	// Start the Dear ImGui frame
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	m_pMainView->Render();
	// Rendering
	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	// Update and Render additional Platform Windows
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
	}
	return S_OK;
}

/*  Tool Editor Create */
HRESULT CIMGUI_Manager::Make_AmGui()
{
	// CAnimEditor Plus'
	CMainView* pImGuiEditor = nullptr;
	
	pImGuiEditor = CMainView::Create(m_pGraphic_Device);
	if (nullptr == pImGuiEditor)
		return E_FAIL;
	// Emplace Back
	m_pMainView = pImGuiEditor;

	return S_OK;
}

CIMGUI_Manager * CIMGUI_Manager::Create(){ return new CIMGUI_Manager();  }

void CIMGUI_Manager::Free()
{
	Safe_Release(m_pGameInstance);
	Safe_Release(m_pMainView);
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
	Safe_Release(m_pGraphic_Device);
}
