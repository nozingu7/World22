#pragma once
#include"CBase.h"

BEGIN(Engine)

class CGameObject;
class CObject_Layers;

class CObject_Manager final : public CBase
{
	DECLARE_SINGLETON(CObject_Manager)
private:
	explicit CObject_Manager();
	virtual ~CObject_Manager() = default;   
public:
	HRESULT Reserve_Objects(const _uint& _iLevelCount);
	// 객체들의 원형 추가
	HRESULT Add_ProtoType(const _tchar*& _pProtoTypeTag, CGameObject*& _pGameObject);
	// 객체들의 사본을 추가
	HRESULT Clone_GameObject(const _uint & _iLevelIndex, const _tchar*& _pLayerTypeTag, const _tchar*& _pProtoTypeTag, void*& _pArg);
	// Find GameObject
	CGameObject* Find_GameObject(const _uint& _iLevelIndex, const _tchar*& _pLayerTypeTag, const _uint& _iIndex);
	// Destroy Layers 
	HRESULT Release_Layer(const _uint& _iLevelIndex);
	// Tick
	void Tick(const _float& _fDeltaSeconds);
	void Late_Tick(const _float& _fDeltaSeconds);
private:
	CObject_Layers* Find_Layer(const _uint& _iLevel,const _tchar*& _pLayerTag);
	CGameObject* Find_ProtoType(const _tchar*& _pProtoTypeTag);
private:
	map<const _tchar*, CGameObject*> m_mProtoTypes;
	typedef map<const _tchar*, CGameObject*> PROTOTYPES;
private:
	typedef map<const _tchar*, CObject_Layers*> LAYERS;
	LAYERS* m_pLayers;
private:
	_uint m_iLevelCount;
public:
	virtual void Free() override;
};

END