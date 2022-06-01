#include"CIMGUI_Manager.h"
#include "CMainView.h"
#include"CMainTool.h"
#include "CGameInstance.h"
#include "CCopyView.h"
#include "CBackground.h"
#include "CLevel_Tool.h"
#include "CCamera_Tool.h"
#include "CCamera_Engine.h"
#include "CTerrian.h"
#include "CMonster.h"
#include "CSword.h"
#include "CPlayer.h"
#include "CImage_Bar.h"

CMainTool::CMainTool() : m_pGameInstance(CGameInstance::Get_Instance()), 
m_pIMGUIManager(CIMGUI_Manager::Get_Instance()), m_pCopyView(nullptr)
{
	Safe_AddRef(m_pGameInstance);
	Safe_AddRef(m_pIMGUIManager);
}
HRESULT CMainTool::NativeConstructor(_bool& _bIsRun)
{
	if (nullptr == m_pGameInstance)
		return E_FAIL;

	GRAPHICDESC tGraphicDesc;
	tGraphicDesc.hWnd = g_hWnd;
	tGraphicDesc.iWinCX = g_iWinSizeX;
	tGraphicDesc.iWinCY = g_iWinSizeY;
	tGraphicDesc.isWindowed = true;

	if (FAILED(m_pGameInstance->Initialize_Device(LEVEL_END, g_hInstance, tGraphicDesc, m_pDevice)))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Ready_RenderManager(2)))
		return E_FAIL;

	if (FAILED(Ready_LoadTexture()))
		return E_FAIL;

	if (FAILED(Ready_Static_Component()))
		return E_FAIL;

	if (FAILED(Ready_Static_GameObject()))
		return E_FAIL;

	if (FAILED(Open_Level()))
		return E_FAIL;

	if (FAILED(m_pIMGUIManager->NativeConstruct(m_pDevice)))
		return E_FAIL;


	// Test Code, Need to Remove
	m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	m_pCopyView = CCopyView::Create(m_pDevice);
	if (nullptr == m_pCopyView)
		return E_FAIL;

	return S_OK;
}

void CMainTool::Tick(const _float & _fDeltaSeconds)
{
	if (nullptr == m_pGameInstance)
		return;

	m_pGameInstance->Tick_Engine(_fDeltaSeconds);

	m_pIMGUIManager->Tick(_fDeltaSeconds);

	m_pGameInstance->LateTick_Engine(_fDeltaSeconds);

	m_pIMGUIManager->Late_Tick(_fDeltaSeconds);
}

HRESULT CMainTool::Render()
{
	// ================================
	if (false == m_pIMGUIManager->Get_MainView()->Is_GameStart())
	{
		m_pGameInstance->Render_Begin();
		m_pGameInstance->Render_Engine();
		m_pGameInstance->Render_End();
	}
	else
	{
		m_pCopyView->CreateScreenShot();
		m_pIMGUIManager->Get_MainView()->Set_SceneViewTexture(m_pCopyView->Get_CopyTex());
	}
	m_pIMGUIManager->Render();
	return S_OK;
}

HRESULT CMainTool::Open_Level()
{
	if (nullptr == m_pGameInstance)
		return E_FAIL;

	CLevel* pLevel = CLevel_Tool::Create(m_pDevice);
	if (nullptr == pLevel)
	{
		MSG_BOX("CMainApp::Open_Level() : Level is Not Created");
		return E_FAIL;
	}

	m_pGameInstance->Open_Level(LEVEL_TOOL, pLevel);
	return S_OK;
}

HRESULT CMainTool::Ready_LoadTexture()
{
	vector<_wstring> pathList;
	// ���� �ӽ÷� �ؽ��� �ο�
	pathList.emplace_back(
		_wstring(L"..\\..\\Resources\\Game_Resource\\Character\\BlueBlob\\BlueBlob_Idle\\blueBlob_idle 1_4.png"));

	if (FAILED(m_pGameInstance->Add_ProtoType(LEVEL_STATIC, TEXT("PROTO_COMP_TEXTURE"), CTexture::Create(m_pDevice,
		CTexture::TYPE_DEFAULT, &pathList))))
		return E_FAIL;

	// texture load
	//if (FAILED(m_pGameInstance->Load_Data(TEXT("SR_Project"), TEXT("Resources"))))
	//	return E_FAIL;

	//if (FAILED(m_pGameInstance->Load_Data(TEXT("SR_Project"), TEXT("Client\\Bin\\Resources"))))
	//	return E_FAIL;

	if (FAILED(m_pGameInstance->Load_Data(TEXT("SR_Project"), TEXT("Resources\\Game_Resource"))))
		return E_FAIL;

	// ���� �޾ƿ��°��� �� �޾ƿ�. ���� ImGui�� �� �������� Ȯ�� �ʿ�
	// Character ���ҽ� �ε�
	if (FAILED(m_pGameInstance->Load(TEXT("SR_Project"), TEXT("Resources\\Game_Resource"), TEXT("Character"))))
		return E_FAIL;

	// �������� ���� �ؽ��� �ε�
	if (FAILED(m_pGameInstance->Load(TEXT("SR_Project"), TEXT("Resources\\Game_Resource"), TEXT("Structure"))))
		return E_FAIL;

	return S_OK;
}

HRESULT CMainTool::Ready_Static_Component()
{
	if (nullptr == m_pGameInstance)
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_ProtoType(LEVEL_STATIC, TEXT("PROTO_COMP_VIBUF_RECT"), CVIVertex_Rect::Create(m_pDevice))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_ProtoType(LEVEL_STATIC, TEXT("PROTO_COMP_TRANSFORM"), CTransform::Create(m_pDevice))))
		return E_FAIL;

	CVIVertex_Terrian::TERRIANDESC tTerrianDesc = { 100, 100 };
	if (FAILED(m_pGameInstance->Add_ProtoType(LEVEL_STATIC, TEXT("PROTO_COMP_VIBUFFER_TERRIAN"), CVIVertex_Terrian::Create(m_pDevice, &tTerrianDesc))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_ProtoType(LEVEL_STATIC, L"PROTO_COMP_AI_ASTAR", CAStar_AI::Create(m_pDevice))))
		return E_FAIL;


	vector<FILEDESC>* pFileDesc = m_pGameInstance->Get_FilePaths();
	if (FAILED(m_pGameInstance->Add_ProtoType(LEVEL_STATIC, TEXT("PROTO_COMP_TEXTURE_TEST"),
		CTexture::Create(m_pDevice, CTexture::TYPE_DEFAULT, pFileDesc))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_ProtoType(LEVEL_STATIC, TEXT("PROTO_COMP_VIBUFFER_SWORD"), CVIVertex_Rect::Create(m_pDevice))))
		return E_FAIL;


	return S_OK;
}

HRESULT CMainTool::Ready_Static_GameObject()
{
	if (nullptr == m_pGameInstance)
		return E_FAIL;

	// Background �Ҵ�
	//if (FAILED(m_pGameInstance->Add_ProtoType(TEXT("Prototype_GameObject_BackGround"), CBackground::Create(m_pDevice))))
	//	return E_FAIL;
	if (FAILED(m_pGameInstance->Add_ProtoType(TEXT("Prototype_GameObject_Player"), CPlayer::Create(m_pDevice))))
		return E_FAIL;
	// Tool Camera �Ҵ�
	CCamera::CAMERAINITDESC tInitDesc = {LEVEL_STATIC, L"PROTO_COMP_TRANSFORM"};
	if (FAILED(m_pGameInstance->Add_ProtoType(TEXT("Prototype_GameObject_CameraTool"), CCamera_Tool::Create(m_pDevice, &tInitDesc))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_ProtoType(L"Prototype_GameObject_CameraEngine", CCamera_Engine::Create(m_pDevice, &tInitDesc))))
		return E_FAIL;

	// Terrian �Ҵ�
	if (FAILED(m_pGameInstance->Add_ProtoType(TEXT("Prototype_GameObject_Terrian"), CTerrian::Create(m_pDevice))))
		return E_FAIL;

	// Monster
	if (FAILED(m_pGameInstance->Add_ProtoType(L"Prototype_GameObject_Monster", CMonster::Create(m_pDevice))))
		return E_FAIL;

	// test
	if (FAILED(m_pGameInstance->Add_ProtoType(PROTO_LAYER_UI, CImage_Bar::Create(m_pDevice))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_ProtoType(TEXT("Prototype_GameObject_Sword"), CSword::Create(m_pDevice))))
		return E_FAIL;

	return S_OK;
}

CMainTool * CMainTool::Create(_bool& _bIsRun)
{
	CMainTool* pInstance = new CMainTool();
	if (FAILED(pInstance->NativeConstructor(_bIsRun)))
	{
		MSG_BOX("CMainTool NactiveContructor Error");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CMainTool::Free()
{
	__super::Free();
	Safe_Release(m_pCopyView);
	Safe_Release(m_pDevice);
	// release
	CIMGUI_Manager::Destroy_Instance();
	Safe_Release(m_pIMGUIManager);
	// Destory
	m_pGameInstance->Release_Engine();
	Safe_Release(m_pGameInstance);
}
