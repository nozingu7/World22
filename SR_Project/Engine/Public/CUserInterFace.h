#pragma once
#include "CGameObject.h"

class ENGINE_DLL CUserInterFace abstract : public CGameObject
{

protected:
	explicit CUserInterFace(const LPDIRECT3DDEVICE9& _pDevice);
	explicit CUserInterFace(const CUserInterFace& _pProtoType);
	virtual ~CUserInterFace() = default;
public:
	// Initialize Methods 
	virtual HRESULT NativeConstruct_ProtoType() override;
	virtual HRESULT NativeConstruct_Clone(void*& pArg) override;
	virtual void Tick(const _float& _fDeltaTime) override;
	virtual void Late_Tick(const _float& _fDeltaTime) override;
	virtual HRESULT Render() override;
protected:
	// Add Component
	virtual HRESULT Add_Component() = 0;
	// Set Up Comp
	virtual HRESULT SetUp_RenderState();
	// Release Comp
	virtual HRESULT Release_RenderState();
private:
	_uint	m_iDepth;
public:
	virtual CGameObject* Clone(void*& _pArg) = 0;
	virtual void Free() override;
};

