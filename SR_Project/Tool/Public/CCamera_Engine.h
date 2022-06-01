#pragma once
#include "Tool_Defines.h"
#include "CCamera.h"

BEGIN(Tool)
class CIMGUI_Manager;

class CCamera_Engine final : public CCamera
{
protected:
	explicit CCamera_Engine(const LPDIRECT3DDEVICE9& _pDevice, void*& _pCameraInitData);
	explicit CCamera_Engine(const CCamera_Engine& _rhs);
	virtual ~CCamera_Engine() = default;
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
	HRESULT Set_Target();
private:
	CTransform* m_pTargetTransform;
public:
	static CCamera_Engine* Create(const LPDIRECT3DDEVICE9& _pDevice, void* _pInitData);
	virtual CGameObject* Clone(void*& _pArg) override;
	virtual void Free() override;
};

END