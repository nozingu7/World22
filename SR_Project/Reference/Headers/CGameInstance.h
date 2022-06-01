#pragma once
#include "CBase.h"
#include "CGraphic_Device.h"
#include "CInput_Device.h"
#include "CLevel_Manager.h"
#include "CTimer_Manager.h"
#include "CObject_Manager.h"
#include "CComponent_Manager.h"
#include "CRenderer_Manager.h"
#include "CFile_Manager.h"
#include "CThread_Manager.h"
#include "CAStar_Manager.h"

BEGIN(Engine)

class ENGINE_DLL CGameInstance final : public CBase
{
	DECLARE_SINGLETON(CGameInstance)
private:
	explicit CGameInstance();
	virtual ~CGameInstance() = default;
public: /* ALL */
	// ������ ����� ����ϱ� ���� ��ġ �ʱ�ȭ
	HRESULT Initialize_Device(const _uint& _iLevelNum, const HINSTANCE& _hInst, const GRAPHICDESC& _tGraphicDesc, LPDIRECT3DDEVICE9& _pOut);
	// �� �����Ӹ��� ������ �ʿ��� �Ŵ����� ����
	void Tick_Engine(const _float& _deltaSeconds);
	void LateTick_Engine(const _float& _delataSeconds);
	// Render Engine
	void Render_Engine(const _uint& _iRenderID = 0);
	// Release Containers
	HRESULT Release_Container(const _uint& _iLevelIndex);
public: /* DEVICE */
	// �׸��� �Լ�
	void Render_Begin();
	void Render_End();
public: /* LEVEL Manager */
	HRESULT Open_Level(const _uint& _iLevelIndex, CLevel*& _pLevel);
	const _uint Get_CurrentLevelIndex() const;
public: /* Timer Manager */
	_float Get_TimeDelta(const _tchar* _pTag);
	HRESULT Add_Timer(const _tchar* _pTag);
	void Tick_Timer(const _tchar* _pTag);
public: /* Object Manager */
	// ��ü���� ���� �߰�
	HRESULT Add_ProtoType(const _tchar* _pProtoTypeTag, CGameObject* _pGameObject);
	// ��ü���� �纻�� �߰�
	HRESULT Clone_GameObject(const _uint & _iLevelCount, const _tchar* _pLayerTypeTag, const _tchar* _pProtoTypeTag, void* _pArg = nullptr);
	// Find GameObject
	CGameObject* Find_GameObject(const _uint& _iLevelIndex, const _tchar* _pLayerTypeTag, const _uint& _iIndex = 0);
	// Destroy Layers 
	HRESULT Release_Layer(const _uint& _iLevelIndex);
public: /* Component Manager */
	// ��ü���� ���� �߰�
	HRESULT Add_ProtoType(const _uint& _iLevelIndex, const _tchar* _pProtoTypeTag, CComponent* _pComponent);
	// ��ü���� �纻�� �߰�
	CComponent* Clone_Component(const _uint & _iLevelIndex, const _tchar* _pProtoTypeTag, void* _pArg = nullptr);
public: /* Render Manager */
	// Ready RenderManager
	HRESULT Ready_RenderManager(const _uint& _iRenderMaxCount = 1);
	// Add Object
	HRESULT Add_RenderObj(const CRenderer_Manager::ERenderType& _eRenderType, class CGameObject* _pObject, const _uint& _iRenderID = 0);
public: /* For  Input Device  */
	_byte Get_DIKeyState(const _ubyte& _eKeyID);
	_long Get_DIMMoveState(const CInput_Device::DIMOUSEMOVE& _eMouseMove);
	_byte Get_DIMButtonState(const CInput_Device::DIMOUSEBUTTON& _eMouseButton);
public: /* CFileLoader */
	// ������ �ε��Ѵ�.
	HRESULT Load(const _tchar* pProjectName, const _tchar* pDirectoryName, const _tchar* pSeekTag, const _tchar* pFilePath = TEXT(""));
	// ��� �Լ��� ��������
	HRESULT Load_Data(const _tchar* pProjectName, const _tchar* pDirectoryName, const _tchar* pFilePath = TEXT(""));

	// ��� �޾ƿ�
	vector<tagFileInfo>* Get_FilePaths();

public: /* Thread Manager */
	// Add Thread 
	// ������ ���̵� ������ ������ ������
	HRESULT Add_Thread(_uint& _iThreadID, function<void(void*, mutex*, _bool*)> _pData, void* _pArg);
	// Delete Thread
	HRESULT Delete_Thread(const _uint& _iThreadID);
	// End All Thread
	HRESULT End_Threads();
public: /* AStar Manager */
	// Ready AStar
	HRESULT Ready_AStar(byte* _pTileInfo, const _float4x4& _matTerrianWorld, const _VECTOR3& _v3TileStartPos,
		const _uint& _iTileWidth, const _uint& _iTileHeight);
	// Register
	HRESULT Register_AStar(CAStar_AI* _pAStar);
	// Get AStar Desc
	CAStar_AI::ASTARDESC* Get_AstarDesc();
	// Release_Data
	void			Release_AStar_Data();
private:
	CGraphic_Device*				m_pGraphicDevice;
	CInput_Device*					m_pInputDevice;
	CLevel_Manager*				m_pLevelMgr;
	CTimer_Manager*				m_pTimerMgr;
	CObject_Manager*			m_pObjectMgr;
	CComponent_Manager*	m_pComponentMgr;
	CRenderer_Manager*		m_pRendererMgr;
	CFile_Manager*					m_pFileMgr;
	CThread_Manager*			m_pThreadMgr;
	CAStar_Manager*				m_pAStarMgr;
public:
	// �������� ���� �Ŵ����� �޸� ����
	void Release_Engine();
public:
	virtual void Free() override;
};

END
