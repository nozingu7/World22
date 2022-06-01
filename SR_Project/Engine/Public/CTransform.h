#pragma once
#include "CComponent.h"

BEGIN(Engine)

class ENGINE_DLL CTransform final : public CComponent
{
private:
	explicit CTransform(const LPDIRECT3DDEVICE9& _pDevice);
	explicit CTransform(CTransform& _rhs);
	virtual ~CTransform() = default;
public:
	_VECTOR3 Get_Reset_Right() { return _VECTOR3(1.f, 0.f, 0.f); }
	_VECTOR3 Get_Reset_Up() { return _VECTOR3(0.f, 1.f, 0.f); }
	_VECTOR3 Get_Reset_Look() { return _VECTOR3(0.f, 0.f, 1.f); }

	_VECTOR3 Get_Right() const { return (_VECTOR3)&m_matWorld.m[0][0]; }
	_VECTOR3 Get_Up() { return (_VECTOR3)&m_matWorld.m[1][0]; }
	_VECTOR3 Get_Look() { return (_VECTOR3)&m_matWorld.m[2][0]; }
	_VECTOR3 Get_Position() { return (_VECTOR3)&m_matWorld.m[3][0]; }
	// get, set
	const _float4x4& Get_WorldMatrix() const { return m_matWorld; }
	void Set_WorldMatrix(const _float4x4& _WorldMatrix) { this->m_matWorld = _WorldMatrix; }

	_VECTOR3 Get_Scale() { return _VECTOR3(D3DXVec3Length(&Get_Right()), D3DXVec3Length(&Get_Up()), D3DXVec3Length(&Get_Look())); }
	void Set_Scale(const _VECTOR3& _v3Scale);

	void Set_Right(const _VECTOR3& _v3Value) { memcpy(&m_matWorld.m[0][0], &_v3Value, sizeof(_VECTOR3)); }
	void Set_Up(const _VECTOR3& _v3Value) { memcpy(&m_matWorld.m[1][0], &_v3Value, sizeof(_VECTOR3)); }
	void Set_Look(const _VECTOR3& _v3Value) { memcpy(&m_matWorld.m[2][0], &_v3Value, sizeof(_VECTOR3)); }
	void Set_Position(const _VECTOR3& _v3Value) { memcpy(&m_matWorld.m[3][0], &_v3Value, sizeof(_VECTOR3)); }
public:
	virtual HRESULT NativeConstruct_ProtoType() override;
	virtual HRESULT NativeConstruct_Clone(void*& _pArg) override;
public:
	HRESULT Bind_WorldMatrix();
public:
	HRESULT Move_Forward(const   _float& _fSpeed, const _float& _fDeltaSeconds);
	HRESULT Move_Back(const _float& _fSpeed, const _float& _fDeltaSeconds);
	HRESULT Move_Right(const _float& _fSpeed, const _float& _fDeltaSeconds);
	HRESULT Move_Left(const _float& _fSpeed, const _float& _fDeltaSeconds);
	// Translate
	HRESULT Translate(const _VECTOR3& _v3Pos, const _float& _fSpeed, const _float& _fDeltaSeconds, const _float& fLimitTime = 0.1f);
	HRESULT Translate(CTransform* _pLookTransform, const _float& _fSpeed, const _float& _fDeltaSeconds, const _float& fLimitTime = 0.1f);
	// Look Just Look
	HRESULT LookAt(CTransform* _pLookTransform);
	HRESULT LookAt(const _VECTOR3& _v3Pos);
	// Look At And Need Dir
	HRESULT LookAt(const _VECTOR3& _v3Pos, _VECTOR3& _v3Dir);
	// Rotate
	HRESULT RotationAxisToFix(const _VECTOR3& _v3Axis, const _float& _fAngle);
	HRESULT RotationAxisToTurn(const _VECTOR3& _v3Axis, const _float& fDotPerSeconds, const _float& _fDeltaSeconds);
	// ¿ªÇà·Ä
	_float4x4 Get_WorldMatrixInverse();
private:
	// World Transform
	_float4x4 m_matWorld;
public:
	static CTransform* Create(const LPDIRECT3DDEVICE9& _pDevice);
	virtual CComponent* Clone(void*& _pArg) override;
	virtual void Free() override;
};

END