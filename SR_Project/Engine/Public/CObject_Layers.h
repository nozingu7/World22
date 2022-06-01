#pragma once
#include "CBase.h"

BEGIN(Engine)

class CObject_Layers final : public CBase
{
private:
	explicit CObject_Layers();
	virtual ~CObject_Layers() = default;
public:
	const list<class CGameObject*>& Get_GameObjects() { return m_lsGameObjects; }
public:

public:
	HRESULT Add_GameObject(class CGameObject*& _pObject);
	CGameObject* Find_GameObject(const _uint& _iIndex);
public:
	HRESULT NativeConstruct();
	void Tick(const _float& _fDeltaSeconds);
	void Late_Tick(const _float& _fDeltaSeconds);
private:
	list<class CGameObject*> m_lsGameObjects;
	typedef list<class CGameObject*> OBJECTS;
public:
	static CObject_Layers* Create();
	virtual void Free() override;
};

END