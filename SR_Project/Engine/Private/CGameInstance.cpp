#include "..\Public\CGameInstance.h"

IMPLEMENT_SINGLETON(CGameInstance)

CGameInstance::CGameInstance() :
	m_pGraphicDevice(CGraphic_Device::Get_Instance()),
	m_pInputDevice(CInput_Device::Get_Instance()),
	m_pLevelMgr(CLevel_Manager::Get_Instance()),
	m_pTimerMgr(CTimer_Manager::Get_Instance()),
	m_pObjectMgr(CObject_Manager::Get_Instance()),
	m_pComponentMgr(CComponent_Manager::Get_Instance()),
	m_pRendererMgr(CRenderer_Manager::Get_Instance()),
	m_pFileMgr(CFile_Manager::Get_Instance()),
	m_pThreadMgr(CThread_Manager::Get_Instance()),
	m_pAStarMgr(CAStar_Manager::Get_Instance())
{
	Safe_AddRef(m_pGraphicDevice);
	Safe_AddRef(m_pInputDevice);
	Safe_AddRef(m_pLevelMgr);
	Safe_AddRef(m_pTimerMgr);
	Safe_AddRef(m_pObjectMgr);
	Safe_AddRef(m_pComponentMgr);
	Safe_AddRef(m_pRendererMgr);
	Safe_AddRef(m_pFileMgr);
	Safe_AddRef(m_pThreadMgr);
	Safe_AddRef(m_pAStarMgr);
}

HRESULT CGameInstance::Initialize_Device(const _uint& _iLevelNum, const HINSTANCE& _hInst, const GRAPHICDESC & _tGraphicDesc, LPDIRECT3DDEVICE9& _pOut)
{
	if (nullptr == m_pGraphicDevice)
		return E_FAIL;

	if (FAILED(m_pGraphicDevice->InitDevice(_tGraphicDesc, _pOut)))
		return E_FAIL;

	if (FAILED(m_pInputDevice->Initialize_Input_Device(_hInst, _tGraphicDesc.hWnd)))
		return E_FAIL;

	if (FAILED(m_pObjectMgr->Reserve_Objects(_iLevelNum)))
		return E_FAIL;

	if (FAILED(m_pComponentMgr->Reserve_Componets(_iLevelNum)))
		return E_FAIL;

	return S_OK;
}

void CGameInstance::Tick_Engine(const _float & _deltaSeconds)
{
	if (nullptr == m_pLevelMgr)
		return;

	m_pInputDevice->Update();

	m_pObjectMgr->Tick(_deltaSeconds);
	m_pLevelMgr->Tick(_deltaSeconds);
}

void CGameInstance::LateTick_Engine(const _float & _delataSeconds)
{
	if (nullptr == m_pLevelMgr)
		return;

	m_pObjectMgr->Late_Tick(_delataSeconds);
	m_pLevelMgr->LateTick(_delataSeconds);
}

void CGameInstance::Render_Engine(const _uint& _iRenderID)
{
	if (nullptr == m_pRendererMgr)
		return;

	m_pRendererMgr->Render(_iRenderID);
}

HRESULT CGameInstance::Release_Container(const _uint & _iLevelIndex)
{
	if (nullptr == m_pObjectMgr || nullptr == m_pComponentMgr)
		return E_FAIL;

	if (FAILED(m_pObjectMgr->Release_Layer(_iLevelIndex)))
		return E_FAIL;

	if (FAILED(m_pComponentMgr->Release_Components(_iLevelIndex)))
		return E_FAIL;

	return S_OK;
}

void CGameInstance::Render_Begin()
{
	if (nullptr == m_pGraphicDevice)
		return;
	m_pGraphicDevice->Render_Begin();
}

void CGameInstance::Render_End()
{
	if (nullptr == m_pGraphicDevice)
		return;
	m_pGraphicDevice->Render_End();
}

HRESULT CGameInstance::Open_Level(const _uint& _iLevelIndex, CLevel *& _pLevel)
{
	if (nullptr == m_pLevelMgr)
		return E_FAIL;
	return m_pLevelMgr->Open_Level(_iLevelIndex, _pLevel);
}

const _uint CGameInstance::Get_CurrentLevelIndex() const
{
	if (nullptr == m_pLevelMgr)
		return 0;

	return m_pLevelMgr->Get_CurrentLevelIndex();
}

_float CGameInstance::Get_TimeDelta(const _tchar* _pTag)
{
	if (nullptr == m_pTimerMgr)
		return 0.f;

	m_pTimerMgr->Tick(_pTag);

	return m_pTimerMgr->Get_TimeDelta(_pTag);
}

HRESULT CGameInstance::Add_Timer(const _tchar* _pTag)
{
	if (nullptr == m_pTimerMgr)
		return E_FAIL;

	return m_pTimerMgr->Add_Timer(_pTag);
}

void CGameInstance::Tick_Timer(const _tchar* _pTag)
{
	if (nullptr == m_pTimerMgr)
		return;

	m_pTimerMgr->Tick(_pTag);
}

HRESULT CGameInstance::Add_ProtoType(const _tchar * _pProtoTypeTag, CGameObject * _pGameObject)
{
	if (nullptr == m_pObjectMgr)
		return E_FAIL;

	m_pObjectMgr->Add_ProtoType(_pProtoTypeTag, _pGameObject);
	return S_OK;
}

HRESULT CGameInstance::Clone_GameObject(const _uint & _iLevelCount, const _tchar * _pLayerTypeTag, const _tchar * _pProtoTypeTag, void * _pArg)
{
	if (nullptr == m_pObjectMgr)
		return E_FAIL;

	m_pObjectMgr->Clone_GameObject(_iLevelCount, _pLayerTypeTag, _pProtoTypeTag, _pArg);
	return S_OK;
}

CGameObject * CGameInstance::Find_GameObject(const _uint & _iLevelIndex, const _tchar * _pLayerTypeTag, const _uint & _iIndex)
{
	if (nullptr == m_pObjectMgr)
		return nullptr;

	return m_pObjectMgr->Find_GameObject(_iLevelIndex, _pLayerTypeTag, _iIndex);
}

HRESULT CGameInstance::Release_Layer(const _uint & _iLevelIndex)
{
	if (nullptr == m_pObjectMgr)
		return E_FAIL;
	return m_pObjectMgr->Release_Layer(_iLevelIndex);
}

HRESULT CGameInstance::Add_ProtoType(const _uint & _iLevelIndex, const _tchar * _pProtoTypeTag, CComponent * _pComponent)
{
	if (nullptr == m_pComponentMgr)
		return E_FAIL;

	m_pComponentMgr->Add_ProtoType(_iLevelIndex, _pProtoTypeTag, _pComponent);
	return S_OK;
}

CComponent * CGameInstance::Clone_Component(const _uint & _iLevelIndex, const _tchar* _pProtoTypeTag, void* _pArg)
{
	if (nullptr == m_pComponentMgr)
		return nullptr;
	return m_pComponentMgr->Clone_Component(_iLevelIndex, _pProtoTypeTag, _pArg);
}

HRESULT CGameInstance::Ready_RenderManager(const _uint & _iRenderMaxCount)
{
	if (nullptr == m_pRendererMgr)
		return E_FAIL;
	return m_pRendererMgr->Ready_RenderManager(_iRenderMaxCount);
}

HRESULT CGameInstance::Add_RenderObj(const CRenderer_Manager::ERenderType & _eRenderType, CGameObject * _pObject, const _uint& _iRenderID)
{
	if (nullptr == m_pRendererMgr)
		return E_FAIL;
	return m_pRendererMgr->Add_RenderObj(_eRenderType, _pObject, _iRenderID);
}

_byte CGameInstance::Get_DIKeyState(const _ubyte & _eKeyID)
{
	if (nullptr == m_pInputDevice)
		return 0;

	return m_pInputDevice->Get_DIKeyState(_eKeyID);
}

_long CGameInstance::Get_DIMMoveState(const CInput_Device::DIMOUSEMOVE & _eMouseMove)
{
	if (nullptr == m_pInputDevice)
		return 0;

	return m_pInputDevice->Get_DIMMoveState(_eMouseMove);
}

_byte CGameInstance::Get_DIMButtonState(const CInput_Device::DIMOUSEBUTTON & _eMouseButton)
{
	if (nullptr == m_pInputDevice)
		return 0;

	return m_pInputDevice->Get_DIMButtonState(_eMouseButton);
}

HRESULT CGameInstance::Load(const _tchar * pProjectName, const _tchar * pDirectoryName, const _tchar * pSeekTag, const _tchar * pFilePath)
{
	if (nullptr == m_pFileMgr)
		return E_FAIL;

	return m_pFileMgr->Load(pProjectName, pDirectoryName, pSeekTag, pFilePath);
}

HRESULT CGameInstance::Load_Data(const _tchar * pProjectName, const _tchar * pDirectoryName, const _tchar * pFilePath)
{
	if (nullptr == m_pFileMgr)
		return E_FAIL;

	return m_pFileMgr->Load_Data(pProjectName, pDirectoryName, pFilePath);
}

vector<tagFileInfo>* CGameInstance::Get_FilePaths()
{
	if (nullptr == m_pFileMgr)
		return nullptr;

	return m_pFileMgr->Get_FilePaths();
}

HRESULT CGameInstance::Add_Thread(_uint & _iThreadID, function<void(void*, mutex*, _bool*)> _pData, void * _pArg)
{
	if (nullptr == m_pThreadMgr)
		return E_FAIL;
	// Add Thread 
	return m_pThreadMgr->Add_Thread(_iThreadID, _pData, _pArg);
}

HRESULT CGameInstance::Delete_Thread(const _uint & _iThreadID)
{
	if (nullptr == m_pThreadMgr)
		return E_FAIL;
	// Add Thread 
	return m_pThreadMgr->Delete_Thread(_iThreadID);
}

HRESULT CGameInstance::End_Threads()
{
	if (nullptr == m_pThreadMgr)
		return E_FAIL;
	// Add Thread 
	return m_pThreadMgr->End_Threads();
}

HRESULT CGameInstance::Ready_AStar(byte * _pTileInfo, const _float4x4 & _matTerrianWorld, const _VECTOR3 & _v3TileStartPos, const _uint & _iTileWidth, const _uint & _iTileHeight)
{
	if (nullptr == m_pAStarMgr)
		return E_FAIL;
	return m_pAStarMgr->Ready_AStar(_pTileInfo, _matTerrianWorld, _v3TileStartPos, _iTileWidth, _iTileHeight);
}

HRESULT CGameInstance::Register_AStar(CAStar_AI * _pAStar)
{
	if (nullptr == m_pAStarMgr)
		return E_FAIL;

	return m_pAStarMgr->Register_AStar(_pAStar);
}

CAStar_AI::ASTARDESC * CGameInstance::Get_AstarDesc()
{
	if (nullptr == m_pAStarMgr)
		return nullptr;

	return m_pAStarMgr->Get_AstarDesc();
}

void CGameInstance::Release_AStar_Data()
{
	if (nullptr == m_pAStarMgr)
		return;

	m_pAStarMgr->Release_Data();
}

void CGameInstance::Release_Engine()
{
	CTimer_Manager::Destroy_Instance();
	CLevel_Manager::Destroy_Instance();
	CRenderer_Manager::Destroy_Instance();
	CAStar_Manager::Destroy_Instance();
	CThread_Manager::Destroy_Instance();
	CObject_Manager::Destroy_Instance();
	CComponent_Manager::Destroy_Instance();
	CInput_Device::Destroy_Instance();
	CFile_Manager::Destroy_Instance();
	CGraphic_Device::Destroy_Instance();

	Destroy_Instance();
}

void CGameInstance::Free()
{
	Safe_Release(m_pTimerMgr);
	Safe_Release(m_pLevelMgr);
	Safe_Release(m_pRendererMgr);
	Safe_Release(m_pAStarMgr);
	Safe_Release(m_pThreadMgr);
	Safe_Release(m_pObjectMgr);
	Safe_Release(m_pComponentMgr);
	Safe_Release(m_pInputDevice);
	Safe_Release(m_pFileMgr);
	Safe_Release(m_pGraphicDevice);
}
