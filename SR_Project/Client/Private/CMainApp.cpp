#include "stdafx.h"
#include "..\Public\CMainApp.h"
#include "CGameInstance.h"
#include "CLevel_Loading.h"
#include "CLevel_Logo.h"
#include "CBackGround.h"
#include "CCamera_Free.h"

CMainApp::CMainApp() : m_pGameInstance(CGameInstance::Get_Instance())
{
	Safe_AddRef(m_pGameInstance);
}

HRESULT CMainApp::NativeConstructor()
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

	if (FAILED(m_pGameInstance->Ready_RenderManager()))
		return E_FAIL;

	if (FAILED(Ready_RenderState()))
		return E_FAIL;

	if (FAILED(Ready_SamplerState()))
		return E_FAIL;

	if (FAILED(Ready_Static_Component()))
		return E_FAIL;

	if (FAILED(Ready_Static_GameObj()))
		return E_FAIL;

	if (FAILED(Open_Level()))
		return E_FAIL;

	return S_OK;
}

void CMainApp::Tick(const _float& _fDeltaSeconds)
{
	if (nullptr == m_pGameInstance)
		return;

	m_pGameInstance->Tick_Engine(_fDeltaSeconds);
	m_pGameInstance->LateTick_Engine(_fDeltaSeconds);
}

HRESULT CMainApp::Render()
{
	m_pGameInstance->Render_Begin();

	m_pGameInstance->Render_Engine();

	m_pGameInstance->Render_End();
	return S_OK;
}

HRESULT CMainApp::Open_Level()
{
	if (nullptr == m_pGameInstance)
	{
		MSG_BOX("CMainApp::Open_Level() : GameInstacne is nullptr");
		return E_FAIL;
	}

	CLevel* pLevel = CLevel_Logo::Create(m_pDevice, LEVEL_LOADING);
	if (nullptr == pLevel)
	{
		MSG_BOX("CMainApp::Open_Level() : Level is Not Created");
		return E_FAIL;
	}

	m_pGameInstance->Open_Level(LEVEL_LOADING, pLevel);
	return S_OK;
}

HRESULT CMainApp::Ready_Static_Component()
{
	if (nullptr == m_pGameInstance)
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_ProtoType(LEVEL_STATIC, TEXT("PROTO_COMP_VIBUF_RECT"), CVIVertex_Rect::Create(m_pDevice))))
		return E_FAIL;
	if (FAILED(m_pGameInstance->Add_ProtoType(LEVEL_STATIC, TEXT("PROTO_COMP_TEXTURE"), CTexture::Create(m_pDevice, CTexture::TYPE_DEFAULT,
		TEXT("..\\Bin\\Resources\\Textures\\Default%d.jpg"), 2))))
		return E_FAIL;
	if(FAILED(m_pGameInstance->Add_ProtoType(LEVEL_STATIC, TEXT("PROTO_COMP_TRANSFORM"), CTransform::Create(m_pDevice))))
		return E_FAIL;

	return S_OK;
}

HRESULT CMainApp::Ready_Static_GameObj()
{
	if (nullptr == m_pGameInstance)
		return E_FAIL;


	CCamera::CAMERAINITDESC tInitData = { LEVEL_STATIC, TEXT("PROTO_COMP_TRANSFORM" });
	if(FAILED(m_pGameInstance->Add_ProtoType(TEXT("Prototype_GameObject_Camera_Free"), 
		CCamera_Free::Create(m_pDevice, &tInitData))))
		return E_FAIL;
	
	return S_OK;
}

HRESULT CMainApp::Ready_RenderState()
{
	m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	//m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	return S_OK;
}

HRESULT CMainApp::Ready_SamplerState()
{
	m_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	return S_OK;
}

CMainApp* CMainApp::Create()
{
	CMainApp* pInstance = new CMainApp();
	if (FAILED(pInstance->NativeConstructor()))
	{
		MSG_BOX("CMainApp NactiveContructor Error");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CMainApp::Free()
{
	__super::Free();
	Safe_Release(m_pDevice);
	m_pGameInstance->Release_Engine();
	Safe_Release(m_pGameInstance);
}
