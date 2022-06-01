#include "stdafx.h"
#include "..\Public\CLoader.h"
#include "CGameInstance.h"
#include "CBackGround.h"
#include "CTerrian_Stage1.h"
#include"CEffect.h"
#include "CVIVertex_Cube.h"
#include "CSky.h"

CLoader::CLoader() :
	m_pGraphic_Device(nullptr), m_eNextLevel(LEVEL_END),
	m_hThread(0), m_isLoadingEnd(false)
{}

CLoader::CLoader(LPDIRECT3DDEVICE9 & _pDevice, const LEVEL & _eNextLevel) :
	m_pGraphic_Device(_pDevice),
	m_eNextLevel(_eNextLevel),
	m_hThread(0),
	m_isLoadingEnd(false)
{
	Safe_AddRef(m_pGraphic_Device);
}

HRESULT CLoader::NativeConstruct()
{
	InitializeCriticalSection(&m_CriticalSection);

	m_hThread = (HANDLE)(_beginthreadex(nullptr, 0, Resource_Loading_MainThread, this, 0, nullptr));
	if (nullptr == m_hThread)
		return E_FAIL;

	return S_OK;
}

_uint CLoader::Resource_Loading_MainThread(void* _pArg)
{
	CLoader* pLoader = static_cast<CLoader*>(_pArg);
	pLoader->Resources_Loader();
	return 0;
}

void CLoader::Resources_Loader()
{
	EnterCriticalSection(&m_CriticalSection);

	switch (m_eNextLevel)
	{
	case LEVEL_LOGO:
		Loading_Logo_Resource();
		break;
	case LEVEL_GS1:
		Loading_GS1_Resource();
		break;
	}
	LeaveCriticalSection(&m_CriticalSection);
}

void CLoader::Loading_Logo_Resource()
{
#ifdef _DEBUG
	cout << "Loading_Logo_Resource" << endl;
#endif

	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);
	if (FAILED(pGameInstance->Add_ProtoType(TEXT("Prototype_GameObject_BackGround"),CBackGround::Create(m_pGraphic_Device))))
		return;

#ifdef _DEBUG
	cout << "로딩 완료" << endl;
#endif

	Safe_Release(pGameInstance);
	m_isLoadingEnd = true;
}

void CLoader::Loading_GS1_Resource()
{
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

 	if (FAILED(pGameInstance->Add_ProtoType(LEVEL_GS1, TEXT("PROTO_COMP_TERRIAN_TEXTRUEE"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT,
		TEXT("..\\Bin\\Resources\\Textures\\Terrain\\Grass_%d.tga"), 2))))
		return;

	/* For.Prototype_Component_Texture_Explosion */
	if (FAILED(pGameInstance->Add_ProtoType(LEVEL_GS1, TEXT("Prototype_Component_Texture_Explosion"),
		CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Bin/Resources/Textures/Explosion/Explosion%d.png"), 90))))
		return;

	/* For.Prototype_Component_Texture_Sky */
	if (FAILED(pGameInstance->Add_ProtoType(LEVEL_GS1, TEXT("Prototype_Component_Texture_Sky"),
		CTexture::Create(m_pGraphic_Device, CTexture::TYPE_CUBEMAP, TEXT("../Bin/Resources/Textures/SkyBox/Sky_%d.dds"), 4))))
		return;

	// ====================================================================

	if (FAILED(pGameInstance->Add_ProtoType(LEVEL_GS1, TEXT("PROTO_COMP_VERTEX_TERRIAN"), CVIVertex_Terrian::Create(m_pGraphic_Device,
		TEXT("../Bin/Resources/Textures/Terrain/Height.bmp")))))
		return;

	if (FAILED(pGameInstance->Add_ProtoType(TEXT("Prototype_GameObject_Terrian"), CTerrian_Stage1::Create(m_pGraphic_Device))))
		return;

	/* For.Prototype_GameObject_Effect */
	if (FAILED(pGameInstance->Add_ProtoType(TEXT("Prototype_GameObject_Effect"),
		CEffect::Create(m_pGraphic_Device))))
		return;

	/* For.Prototype_Component_VIBuffer_Cube */
	if (FAILED(pGameInstance->Add_ProtoType(LEVEL_GS1, TEXT("Prototype_Component_VIBuffer_Cube"),
		CVIVertex_Cube::Create(m_pGraphic_Device))))
		return;

	/* For.Prototype_GameObject_Sky */
	if (FAILED(pGameInstance->Add_ProtoType(TEXT("Prototype_GameObject_Sky"),
		CSky::Create(m_pGraphic_Device))))
		return;

#ifdef _DEBUG
	cout << "Loading_GS1_Resource" << endl;
#endif

	Safe_Release(pGameInstance);
	m_isLoadingEnd = true;
}

CLoader * CLoader::Create(LPDIRECT3DDEVICE9 & _pDevice, const LEVEL & _eNextLevel)
{
	CLoader* pLoader = new CLoader(_pDevice, _eNextLevel);
	if (FAILED(pLoader->NativeConstruct()))
	{
		MSG_BOX("CLoader::Create NaticeConstruct Error");
		Safe_Release(pLoader);
	}
	return pLoader;
}

void CLoader::Free()
{
	Safe_Release(m_pGraphic_Device);
	WaitForSingleObject(m_hThread, INFINITE);
	DeleteCriticalSection(&m_CriticalSection);
	CloseHandle(m_hThread);
}

