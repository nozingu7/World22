#pragma once
#include "CGameObject.h"

BEGIN(Engine)

class CComponent;

class ENGINE_DLL CSortObject abstract : public CGameObject
{
public:
protected:
	explicit CSortObject(const LPDIRECT3DDEVICE9& _pDevice);
	explicit CSortObject(const CSortObject& _pProtoType);
	virtual ~CSortObject() = default;
public:
	const _float& Get_CamToDistance() const { return m_fCamToDistance; }
public:
	// Initialize Methods 
	virtual HRESULT NativeConstruct_ProtoType() override;
	virtual HRESULT NativeConstruct_Clone(void*& pArg) override;
	virtual void Tick(const _float& _fDeltaTime) override;
	virtual void Late_Tick(const _float& _fDeltaTime) override;
	virtual HRESULT Render() override;

protected:
	// Compute Cam Distance
	void Compute_CamDistance(class CTransform* _pTransform);
protected:
	_float m_fCamToDistance;

public:
	virtual CGameObject* Clone(void*& _pArg) = 0;
	virtual void Free() override;
};

END