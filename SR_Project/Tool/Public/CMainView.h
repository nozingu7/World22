#pragma once
#include"CIMGUI.h"

BEGIN(Tool)

class CMainView final : public CIMGUI
{
public:
	typedef struct tagDockSpaceDesc 
	{
		tagDockSpaceDesc() : 
			iID(0), bControl(true), pName(nullptr), imWindowFlag(0)
		{}
		tagDockSpaceDesc(const char* _pName, const ImGuiWindowFlags& _imWindowFlag) : 
			pName(_pName), bControl(true), iID(0), imWindowFlag(_imWindowFlag){}
		// ID
		ImGuiID		iID;
		// Control 
		_bool			bControl;
		// Name
		const char*	pName;
		// WindowFlags
		ImGuiWindowFlags imWindowFlag;
	}DOCKDESC;
private:
	explicit CMainView(const LPDIRECT3DDEVICE9& _pDevice);
	virtual ~CMainView() = default;
public:
	const _bool& Is_GameStart() const { return m_tGameView.bControl; }
	void Set_SceneViewTexture(const LPDIRECT3DBASETEXTURE9& _pSceneViewTexture) { this->m_pSceneViewTexture = _pSceneViewTexture; }
public:
	DOCKDESC Get_MainView() { return m_tMainView; }
public:
	virtual HRESULT NativeConstruct();
	virtual HRESULT Tick(const _float& _fDeltaSeconds);
	virtual HRESULT Late_Tick(const _float& _fDeltaSeconds);
	virtual HRESULT Render();
private:
	// Add ImGuiAdd
	HRESULT Add_ImGuiClass();
private:
	virtual void	Show_Window() override;
	void				Main_Window();
private:
	// Save ImGui Class
	vector<CIMGUI*>			m_vecImGuiClass;
private:
	// 텍스쳐에 그린 이미지를 받아서 저장
	LPDIRECT3DBASETEXTURE9	m_pSceneViewTexture;
private:
	// ImGui OwnerViewPort
	ImGuiViewport		m_imGViewPort;
	// Owner BackGround Window
	DOCKDESC				m_tOwner;
	// else.... 
	DOCKDESC				m_tMainView;
	DOCKDESC				m_tPerspective;
	DOCKDESC				m_tHierarchy;
	DOCKDESC				m_tGameView;
private:

private:
#ifdef _DEBUG
	_tchar				m_szFrame[64];
	_uint				m_iCount = 0;
#endif
public:
	static CMainView* Create(const LPDIRECT3DDEVICE9& _pDevice);
	// Create
	virtual void Free() override;
};

END

/*
	ImGuiWindowFlags flags = ImGuiWindowFlags_MenuBar;
	flags |= ImGuiWindowFlags_NoDocking;
	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowSize(ImVec2(static_cast<float>(g_iWinSizeX), static_cast<float>(g_iWinSizeY)));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize;
	flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("DockSpace Demo", 0, flags);
	ImGui::PopStyleVar();

	ImGuiIO& io = ImGui::GetIO();
	ImGuiID dockspace_id = ImGui::GetID("MyDockspace");

	ImGuiContext* ctx = ImGui::GetCurrentContext();
	ImGui::DockBuilderRemoveNode(dockspace_id); // Clear out existing layout
	ImGui::DockBuilderAddNode(dockspace_id, 0); // Add empty node

	ImGuiID dock_main_id = dockspace_id; // This variable will track the document node, however we are not using it here as we aren't docking anything into it.
	ImGuiID dock_id_prop = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 0.20f, NULL, &dock_main_id);
	ImGuiID dock_id_bottom = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Down, 0.20f, NULL, &dock_main_id);

	ImGui::DockBuilderDockWindow("Log", dock_id_bottom);
	ImGui::DockBuilderDockWindow("Properties", dock_id_prop);
	ImGui::DockBuilderFinish(dockspace_id);

	ImGui::DockSpace(dockspace_id);

	{
		// Properties
		ImGui::Begin("Properties");
		ImGui::End();
	}

	{
		// Log
		ImGui::Begin("Log");
		ImGui::End();
	}


	ImGui::End();
	ImGui::PopStyleVar();
*/

/*

// Submit top-level dockspace
ImGuiWindowClass top_level_class;
top_level_class.ClassId = ImHashStr("MyTopLevelClass");
top_level_class.DockingAllowUnclassed = false;
ImGui::DockSpaceOverViewport(NULL, ImGuiDockNodeFlags_None, &top_level_class);

// Submit top-level documents
ImGui::SetNextWindowClass(&top_level_class);
ImGui::Begin("ThirdPersonExampleMap", ....);

ImGuiWindowClass inside_document_class;
// Choice 1: shared class for all documents (all tools can be docked into all documents)
inside_document_class.ClassId = ImHashStr("InsideDocumentClass");
// Choice 2: each document has its class
inside_document_class.ClassId = my_document->ID; or ImHashStr(my_document->Name);
ImGui::Dockspace(...., ..., ...., &inside_document_class);

ImGui::End();

// Submit tools
ImGui::SetNextWindowClass(&inside_document_class);
ImGui::Begin("Components");
...
ImGui::End();

	ImGuiID dockspaceID = 0;
	ImGui::DockSpaceOverViewport(NULL, ImGuiDockNodeFlags_None, pPerspectiveWindowClass);
	ImGui::SetNextWindowClass(pPerspectiveWindowClass);
	ImGui::SetNextWindowPos(ImVec2(m_tImGuiDataDesc.v2Pos.x,m_tImGuiDataDesc.v2Pos.y),ImGuiCond_Appearing);
	ImGui::SetNextWindowSize(ImVec2(m_tImGuiDataDesc.v2Size.x, m_tImGuiDataDesc.v2Size.y), ImGuiCond_Appearing);
	if (ImGui::Begin("View", &m_bOpenWindow, ImGuiWindowFlags_NoTitleBar))
	{
		dockspaceID = ImGui::GetID("HUB_DockSpace");
		ImGui::DockSpace(0, ImVec2(0.f, 0.0f),  ImGuiDockNodeFlags_PassthruCentralNode , pPerspectiveWindowClass);
		ImGui::End();
	}

	// ImGui  Perspective Window
	{
		ImGui::SetNextWindowDockID(dockspaceID, ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowSize(ImVec2(m_tImGuiDataDesc.v2Size.x, m_tImGuiDataDesc.v2Size.y), ImGuiCond_Appearing);
		ImGui::Begin("Window", &m_bOpen_SelectWindow, ImGuiWindowFlags_UnsavedDocument | ImGuiWindowFlags_NoTitleBar);
		dockspaceID = ImGui::GetID("HUB_DockSpace");
		ImGui::DockSpace(dockspaceID, ImVec2(0.f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode, pPerspectiveWindowClass);

		ImGui::End();
	}

	{
		ImGui::SetNextWindowDockID(dockspaceID, ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowPos(ImVec2(500.f, 0.f), ImGuiCond_Appearing);
		ImGui::SetNextWindowSize(ImVec2(300.f, m_tImGuiDataDesc.v2Size.y), ImGuiCond_Appearing);
		ImGui::Begin("Perspective", &m_bOpen_SelectWindow, ImGuiWindowFlags_UnsavedDocument);

		ImGui::End();
	}
*/

/*
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
	window_flags |= ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize;
	window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(viewport->Size);
	ImGui::SetNextWindowViewport(viewport->ID);
	window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	ImGui::Begin("Test", &m_bOpenWindow, window_flags);

	if (ImGui::BeginTabBar("Main", ImGuiTabBarFlags_AutoSelectNewTabs | ImGuiTabBarFlags_Reorderable))
	{
		if (ImGui::BeginTabItem("Layout", NULL, ImGuiTabBarFlags_TabListPopupButton))
		{

			// Dockspace
			ImGuiIO& io = ImGui::GetIO();
			if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
			{
				ImGuiID dockspace_id = ImGui::GetID("Test");
				ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f));
			}

			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Animation", NULL, ImGuiTabBarFlags_TabListPopupButton))
		{

			// Dockspace
			ImGuiIO& io = ImGui::GetIO();
			if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
			{
				ImGuiID dockspace_id = ImGui::GetID("Test1");
				ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f));
			}

			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Shader", NULL, ImGuiTabBarFlags_TabListPopupButton))
		{

			// Dockspace
			ImGuiIO& io = ImGui::GetIO();
			if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
			{
				ImGuiID dockspace_id = ImGui::GetID("Test2");
				ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f));
			}

			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Node Editor", NULL, ImGuiTabBarFlags_TabListPopupButton))
		{

			// Dockspace
			ImGuiIO& io = ImGui::GetIO();
			if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
			{
				ImGuiID dockspace_id = ImGui::GetID("Test3");
				ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f));
			}

			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}
	ImGui::End();
*/

/*
	static int initialized = 0;
	static int new_window = 0;
	ImGuiWindowFlags flags = ImGuiWindowFlags_MenuBar;
	flags |= ImGuiWindowFlags_NoDocking;
	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(viewport->Size);
	ImGui::SetNextWindowViewport(viewport->ID);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
	flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("DockSpace Demo", 0, flags);
	ImGui::PopStyleVar();

	if (ImGui::BeginMenuBar())
	{
		if (initialized == 0)
		{
			if (ImGui::Button("1. Initialize"))
				initialized = 1;
		}
		if (initialized > 0 && new_window == 0)
		{
			if (ImGui::Button("2. New Window"))
				new_window = 1;
		}
		ImGui::EndMenuBar();
	}

	ImGuiIO& io = ImGui::GetIO();
	ImGuiID dockspace_id = ImGui::GetID("MyDockspace");

	if (initialized == 1)
	{
		initialized = 2;
		ImGuiContext* ctx = ImGui::GetCurrentContext();
		ImGui::DockBuilderRemoveNode( dockspace_id); // Clear out existing layout
		ImGui::DockBuilderAddNode(dockspace_id); // Add empty node

		ImGuiID dock_main_id = dockspace_id; // This variable will track the document node, however we are not using it here as we aren't docking anything into it.
		ImGuiID dock_id_prop = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 0.20f, NULL, &dock_main_id);
		ImGuiID dock_id_bottom = ImGui::DockBuilderSplitNode( dock_main_id, ImGuiDir_Down, 0.20f, NULL, &dock_main_id);

		ImGui::DockBuilderDockWindow("Log", dock_id_bottom);
		ImGui::DockBuilderDockWindow("Properties", dock_id_prop);
		ImGui::DockBuilderFinish(dockspace_id);
	}

	ImGui::DockSpace(dockspace_id);
	if (initialized == 2)
	{
		ImGui::Begin("Properties");
		ImGui::End();

		ImGui::Begin("Log");
		ImGui::End();
	}

	if (new_window == 1)
	{
		// Should dock window to empty space, instead window is not docked anywhere.
		ImGui::SetNextWindowDockID(dockspace_id, ImGuiCond_Once);
		ImGui::Begin("New Window");
		ImGui::End();
	}

	ImGui::End();
	ImGui::PopStyleVar();
*/

/*

#include "Engine.h"

using namespace Engine;
using namespace graphics;

int main()
{
	Window window("Advent3D", 800,600, false);
	Shader shader("Res/Shaders/Unlit.shader");

	//TRIANGLE CREATION//
	float Tvertices[] = {-0.5f, -0.5f, 0.0f,0.5f, -0.5f, 0.0f,0.0f,  0.5f, 0.0f};

	unsigned int Tvbo, Tvao;
	glGenVertexArrays(1, &Tvao);
	glGenBuffers(1, &Tvbo);
	glBindVertexArray(Tvao);
	glBindBuffer(GL_ARRAY_BUFFER, Tvbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Tvertices), Tvertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);


	while (!window.Closed())
	{
		//we need to clear the window,
		window.Clear(0.5f, 0.5f, 0.5f,true,true);

		//switch to the custom fbo
		window.bindFBO();

		window.Clear(1.0f, 1.0f, 1.0f, true, false);

		shader.Use();
		glBindVertexArray(Tvao);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//switch to the default fbo
		window.unbindFBO();

		ImGui::Begin("Scene Window");

		ImVec2 pos = ImGui::GetCursorScreenPos();

		ImGui::GetWindowDrawList()->AddImage(
			(void *)window.getRenderTexture(), ImVec2(ImGui::GetCursorScreenPos()),
			ImVec2(ImGui::GetCursorScreenPos().x + window.getWidth()/2, ImGui::GetCursorScreenPos().y +
			window.getHeight()/2), ImVec2(0, 1), ImVec2(1, 0));

		ImGui::End();

		window.Update();
	}
}

	// Use object uid as identifier. Most commonly you could also use the object pointer as a base ID.
	ImGui::PushID(_iID);

	// Text and Tree nodes are less high than framed widgets, using AlignTextToFramePadding() we add vertical spacing to make the tree lines equal high.
	ImGui::TableNextRow();
	ImGui::TableSetColumnIndex(0);
	ImGui::AlignTextToFramePadding();
	bool node_open = ImGui::TreeNode("Object", "%s_%u", prefix, _iID);
	ImGui::TableSetColumnIndex(1);
	ImGui::Text("my sailor is rich");

	if (node_open)
	{
		static float placeholder_members[8] = { 0.0f, 0.0f, 1.0f, 3.1416f, 100.0f, 999.0f };
		for (int i = 0; i < 8; i++)
		{
			ImGui::PushID(i); // Use field index as identifier.
			// Show Item
			ImGui::PopID();
		}
		ImGui::TreePop();
	}
	ImGui::PopID();

*/