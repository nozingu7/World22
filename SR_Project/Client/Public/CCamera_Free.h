#pragma once
#include "CCamera.h"
#include "Client_Defines.h"


class CCamera_Free : public CCamera
{
protected:
	explicit CCamera_Free(const LPDIRECT3DDEVICE9& _pDevice, void*& _pInitDesc);
	explicit CCamera_Free(const CCamera_Free& _rhs);
	virtual  ~CCamera_Free() = default;
public:
	// Initialize Methods 
	virtual HRESULT NativeConstruct_ProtoType();
	virtual HRESULT NativeConstruct_Clone(void*& pArg);
	virtual void Tick(const _float& _fDeltaTime);
	virtual void Late_Tick(const _float& _fDeltaTime);
	virtual HRESULT Render();
private:
	// Cam Move
	void Camera_Move(const _float& _fDeltaTime);
public:
	static CCamera_Free* Create(const LPDIRECT3DDEVICE9& _pDevice, void* _pInitDesc);
	virtual CGameObject* Clone(void*& _pArg) override;
	virtual void Free() override;
};

