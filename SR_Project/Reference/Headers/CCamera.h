#pragma once
#include "CGameObject.h"

BEGIN(Engine)
class CTransform;

class ENGINE_DLL CCamera abstract : public CGameObject
{
public:
	typedef struct tagCameraInitDesc
	{
		_uint				m_iLevel;
		const _tchar*	pTransformProtoTypeTag;
	}CAMERAINITDESC;
public:
	typedef struct tagCameraCloneDesc
	{
		_float fAspect,  fMinDis,  fMaxDis, fForv;
		_VECTOR3		v3Look, v3Pos;
	}CAMERACLONEDESC;
protected:
	explicit CCamera(const LPDIRECT3DDEVICE9& _pDevice, void*& _pCameraInitData);
	explicit CCamera(const CCamera& _rhs);
	virtual ~CCamera() = default;
public:
	// Initialize Methods 
	virtual HRESULT NativeConstruct_ProtoType();
	virtual HRESULT NativeConstruct_Clone(void*& pArg);
	virtual void Tick(const _float& _fDeltaTime);
	virtual void Late_Tick(const _float& _fDeltaTime);
	virtual HRESULT Render();

public:
	/* DEFINE METHOD */
// Bine ViewMatrix
	HRESULT Bind_Matrixes();
protected:
	// Add Transform Comp
	HRESULT Add_Transform();
public:
protected:
	CTransform*					m_pTransformComp;
protected:
	// Camera Clone Data 
	CAMERACLONEDESC		m_tCameraCloneDesc;
	// Camera Init Data
	CAMERAINITDESC			m_tCameraInitDesc;
public:
	virtual CGameObject* Clone(void*& _pArg) = 0;
	virtual void Free() override;
};
END