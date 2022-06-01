#include"imgui.h"
#include"imgui_impl_win32.h"
#include"imgui_impl_dx9.h"
#include "..\Public\CFileDialog.h"

CFileDialog::CFileDialog(const LPDIRECT3DDEVICE9& _pDevice)
	:CIMGUI(_pDevice)
{
}

HRESULT CFileDialog::NativeConstruct()
{
	if (FAILED(__super::NativeConstruct()))
		return E_FAIL;

	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	/*if (FAILED(pGameInstance->Load_Data(TEXT("SR_Project"), TEXT("Client\\Bin\\Resources"))))
		return E_FAIL;*/
	m_pTextureComp = (CTexture*)pGameInstance->Clone_Component(LEVEL_STATIC, PROTO_COMP_TEXTURE_TEST);
	if (!m_pTextureComp)
		return E_FAIL;

	Safe_Release(pGameInstance);

	m_strWindowName = "FileDialog";

	return S_OK;
}

HRESULT CFileDialog::Tick(const _float & _fDeltaSeconds)
{
	if (FAILED(__super::Tick(_fDeltaSeconds)))
		return E_FAIL;

	return S_OK;
}

HRESULT CFileDialog::Late_Tick(const _float & _fDeltaSeconds)
{
	if (FAILED(__super::Late_Tick(_fDeltaSeconds)))
		return E_FAIL;

	return S_OK;
}

//HRESULT CFileDialog::Render()
//{
//	if (FAILED(__super::Render()))
//		return E_FAIL;
//
//	// ImGuiCond_Appearing
//	// ImGuiCond_FirstUseEver
//
//	ImVec2 InitPos = ImVec2{ static_cast<_float>(g_iWinSizeX),  50.f };
//	ImGui::SetNextWindowPos(InitPos, ImGuiCond_Appearing);
//	ImGui::SetNextWindowSize(ImVec2(300.f, 300.f), ImGuiCond_Appearing);
//	ImGui::Begin("Path Finder");
//
//	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
//	Safe_AddRef(pGameInstance);
//
//	// �̹� ������ �������ִ� ���� �����̳�
//	vector<FILEDESC> pPaths = *pGameInstance->Get_FilePaths();
//
//	const float TEXT_BASE_WIDTH = ImGui::CalcTextSize("A").x;
//	const float TEXT_BASE_HEIGHT = ImGui::GetTextLineHeightWithSpacing();
//
//	if (ImGui::TreeNode("Test view"))
//	{
//		static ImGuiTableFlags flags = ImGuiTableFlags_BordersV | ImGuiTableFlags_BordersOuterH | ImGuiTableFlags_Resizable | ImGuiTableFlags_RowBg | ImGuiTableFlags_NoBordersInBody;
//
//		if (ImGui::BeginTable("3ways", 3, flags))
//		{
//			// The first column will use the default _WidthStretch when ScrollX is Off and _WidthFixed when ScrollX is On
//			ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_NoHide);
//			ImGui::TableSetupColumn("Index", ImGuiTableColumnFlags_WidthFixed, TEXT_BASE_WIDTH * 12.0f);
//			ImGui::TableSetupColumn("Type", ImGuiTableColumnFlags_WidthFixed, TEXT_BASE_WIDTH * 18.0f);
//			ImGui::TableHeadersRow();
//
//			// Tree View ������ �����.
//			DisplayNode(&pPaths[0], pPaths);
//
//			ImGui::EndTable();
//		}
//		ImGui::TreePop();
//	}
//
//	Safe_Release(pGameInstance);
//
//	ImGui::End();
//
//	return S_OK;
//}

HRESULT CFileDialog::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	// ImGuiCond_Appearing
	// ImGuiCond_FirstUseEver

	ImVec2 InitPos = ImVec2{ static_cast<_float>(g_iWinSizeX),  50.f };
	ImGui::SetNextWindowPos(InitPos, ImGuiCond_Appearing);
	ImGui::SetNextWindowSize(ImVec2(300.f, 300.f), ImGuiCond_Appearing);
	ImGui::Begin("Path Finder");

	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	// �̹� ������ �������ִ� ���� �����̳�
	vector<FILEDESC> pPaths = *pGameInstance->Get_FilePaths();

	const float TEXT_BASE_WIDTH = ImGui::CalcTextSize("A").x;
	const float TEXT_BASE_HEIGHT = ImGui::GetTextLineHeightWithSpacing();

	if (ImGui::TreeNode("Test view"))
	{
		static ImGuiTableFlags flags = ImGuiTableFlags_BordersV | ImGuiTableFlags_BordersOuterH | ImGuiTableFlags_Resizable | ImGuiTableFlags_RowBg | ImGuiTableFlags_NoBordersInBody;

		if (ImGui::BeginTable("3ways", 3, flags))
		{
			// The first column will use the default _WidthStretch when ScrollX is Off and _WidthFixed when ScrollX is On
			ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_NoHide);
			ImGui::TableSetupColumn("Index", ImGuiTableColumnFlags_WidthFixed, TEXT_BASE_WIDTH * 12.0f);
			ImGui::TableSetupColumn("Type", ImGuiTableColumnFlags_WidthFixed, TEXT_BASE_WIDTH * 18.0f);
			ImGui::TableHeadersRow();

			// Tree View ������ �����.
			DisplayNode(&pPaths[0], pPaths);

			ImGui::EndTable();
		}
		ImGui::TreePop();
	}

	Safe_Release(pGameInstance);

	ImGui::End();

	return S_OK;
}

void CFileDialog::DisplayNode(const FILEDESC* node, const vector<FILEDESC>& allNode)
{
	ImGui::TableNextRow();
	ImGui::TableNextColumn();

	// �������� �ƴ��� �����Ѵ�
	const bool is_folder = node->bIsFolder;

	// ���� ����� �̸��� ������ ������ ������ �ű��.
	string strName;
	strName.assign(node->szFileName.begin(), node->szFileName.end());
	const char* pFileName = strName.c_str();

	string strType;
	strType.assign(node->szFileType.begin(), node->szFileType.end());
	const char* pFileType = strType.c_str();


	_uint iSelected = -1;

	// ���� ���� Ž������ ������ �������
	if (is_folder)
	{
		bool open = ImGui::TreeNodeEx(pFileName, ImGuiTreeNodeFlags_SpanFullWidth);
		ImGui::TableNextColumn();
		ImGui::Text("%d", node->iIndex);
		ImGui::TableNextColumn();
		ImGui::TextUnformatted(pFileType);

		// �ش� ������ �����ִ��� üũ
		if (open)
		{
			for (int i = 0; i < allNode.size(); ++i)
			{
				// ���� ���� ����� �̸��� �θ��� �̸��� ���ٸ� ( ���� ��Ȳ�� ������ ������ �� ��Ȳ��. => ���� ���� ������. )
				if (node->szFileName == allNode[i].szParentName)
				{
					// DisplayNode�� �ش� ��ü�� ��忡 ����.
					DisplayNode(&allNode[i], allNode);
				}
			}
			ImGui::TreePop();
		}
	}
	// ���� Ž������ ������ �����̶��
	else
	{
		// s : �׸� ���� üũ
		_bool bOpen = ImGui::TreeNodeEx(pFileName, ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_Bullet | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_SpanFullWidth);
		if (bOpen && ImGui::IsItemHovered() && !ImGui::IsItemToggledOpen())
		{
			//iSelected = node->iIndex;
			iSelected = node->iFileCnt;
			PreView(iSelected);
			ImGui::NewLine();

			string strPath;
			strPath.assign(node->szFilePath.begin(), node->szFilePath.end());
			const char* pFilePath = strPath.c_str();
			ImGui::Text(pFilePath);

			if (ImGui::IsItemClicked(1)/* && (iSelected != -1)*/)
			{
				MSG_BOX("pause");
			}
		}

		ImGui::TableNextColumn();
		ImGui::Text("%d", node->iIndex);
		//ImGui::Text("file : %d", node->iFileCnt);
		ImGui::TableNextColumn();
		ImGui::TextUnformatted(pFileType);
		ImGui::TableNextColumn();
	}
}

// ���콺 �����ÿ� �̸������ ������ �̹����� �����ݴϴ�.
void CFileDialog::PreView(_uint iTexIndex)
{
	if (!m_pTextureComp)
		return;

	LPDIRECT3DBASETEXTURE9 pTexture = m_pTextureComp->Get_Texture(iTexIndex);
	if (!pTexture)
		return;

	ImGui::TextWrapped("...");
	_float fTexWidth = 100.f;
	_float fTexHeight = 100.f;
	{
		ImGui::Text("%.0fx%.0f", fTexWidth, fTexHeight);		// texture size
		ImVec2 pos = ImGui::GetCursorScreenPos();
		ImVec2 uv_min = ImVec2(0.0f, 0.0f);                 // Top-left
		ImVec2 uv_max = ImVec2(1.0f, 1.0f);                 // Lower-right
		ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);   // No tint
		ImVec4 border_col = ImVec4(1.0f, 1.0f, 1.0f, 0.5f); // 50% opaque white
		ImGui::Image((void*)pTexture, ImVec2(fTexWidth, fTexHeight), uv_min, uv_max, tint_col, border_col);
	}

}

CFileDialog * CFileDialog::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CFileDialog* pInstance = new CFileDialog(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct()))
	{
		MSG_BOX("Failed To Create : CFileDialog");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CFileDialog::Free()
{
	// ������ �� �սô�.
	Safe_Release(m_pTextureComp);
	__super::Free();
}
