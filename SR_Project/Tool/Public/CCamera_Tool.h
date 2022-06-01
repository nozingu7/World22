#pragma once
#include "CCamera.h"
#include "Tool_Defines.h"

BEGIN(Tool)

class CIMGUI_Manager;

class CCamera_Tool final : public CCamera
{
protected:
	explicit CCamera_Tool(const LPDIRECT3DDEVICE9& _pDevice, void*& _pCameraInitData);
	explicit CCamera_Tool(const CCamera_Tool& _rhs);
	virtual ~CCamera_Tool() = default;
public:
	// Initialize Methods 
	virtual HRESULT NativeConstruct_ProtoType() override;
	virtual HRESULT NativeConstruct_Clone(void*& _pArg)override;
	virtual void Tick(const _float& _fDeltaTime)override;
	virtual void Late_Tick(const _float& _fDeltaTime)override;
	virtual HRESULT Render()override;
protected:
	// Cam Move
	HRESULT Cam_Move(const _float& _fDeltaSeconds);
	// Find ProtoType Transform
	HRESULT Find_Prototype_Transform();
public:
	static CCamera_Tool* Create(const LPDIRECT3DDEVICE9& _pDevice, void* _pInitData);
	virtual CGameObject* Clone(void*& _pArg) override;
	virtual void Free() override;
};

END