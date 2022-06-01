#pragma once
#include "CBase.h"

BEGIN(Engine)

class CComponent;

class ENGINE_DLL CGameObject abstract : public CBase
{
protected:
	explicit CGameObject(const LPDIRECT3DDEVICE9& _pDevice);
	explicit CGameObject(const CGameObject& _pProtoType);
	virtual ~CGameObject() = default;
public:
	CComponent* Get_Component(const _tchar* _pName) { return m_mComponets[_pName]; }
public:
	// Initialize Methods 
	virtual HRESULT NativeConstruct_ProtoType();
	virtual HRESULT NativeConstruct_Clone(void*& pArg);
	virtual void Tick(const _float& _fDeltaTime);
	virtual void Late_Tick(const _float& _fDeltaTime);
	virtual HRESULT Render();
public:
	// Actor AddComponent
	HRESULT Add_Component(CComponent** _ppOut, const _tchar* _pTag, const _uint& _iLevelIndex, const _tchar* _pProtoTypeTag, void* _pArg = nullptr);
private:
	CComponent* Find_Component(const _tchar*& _pTag);
protected:
	LPDIRECT3DDEVICE9		m_pGraphic_Device;
protected:
	typedef map<const _tchar*, CComponent*> COMPONENTS;
	COMPONENTS m_mComponets;
public:
	virtual CGameObject* Clone(void*& _pArg) = 0;
	virtual void Free() override;
};

END