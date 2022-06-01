#include "..\Public\CTransform.h"


CTransform::CTransform(const LPDIRECT3DDEVICE9 & _pDevice)
	: CComponent(_pDevice)
{
	// 항등 행렬로 초기화
	D3DXMatrixIdentity(&m_matWorld);
}

CTransform::CTransform(CTransform & _rhs)
	: CComponent(_rhs), m_matWorld(_rhs.m_matWorld)
{
}

void CTransform::Set_Scale(const _VECTOR3 & _v3Scale)
{
	_VECTOR3    vRight = Get_Right();
	_VECTOR3    vUp = Get_Up();
	_VECTOR3    vLook = Get_Look();

	Set_Right(*D3DXVec3Normalize(&vRight, &vRight) * _v3Scale.x);
	Set_Up(*D3DXVec3Normalize(&vUp, &vUp) *_v3Scale.y);
	Set_Look(*D3DXVec3Normalize(&vLook, &vLook) * _v3Scale.z);
}

HRESULT CTransform::NativeConstruct_ProtoType()
{
	if (__super::NativeConstruct_ProtoType())
		return E_FAIL;

	return S_OK;
}

HRESULT CTransform::NativeConstruct_Clone(void *& _pArg)
{
	if (__super::NativeConstruct_Clone(_pArg))
		return E_FAIL;


	return S_OK;
}

HRESULT CTransform::Bind_WorldMatrix()
{
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;

	m_pGraphic_Device->SetTransform(D3DTS_WORLD, &m_matWorld);
	return S_OK;
}

HRESULT CTransform::Move_Forward(const _float & _fSpeed, const _float & _fDeltaSeconds)
{
	_VECTOR3 v3Look = Get_Look();
	Set_Position(Get_Position() + *D3DXVec3Normalize(&v3Look, &v3Look) * _fSpeed * _fDeltaSeconds);
	return S_OK;
}

HRESULT CTransform::Move_Back(const _float & _fSpeed, const _float & _fDeltaSeconds)
{
	_VECTOR3 v3Look = Get_Look();
	Set_Position(Get_Position() - *D3DXVec3Normalize(&v3Look, &v3Look) * _fSpeed * _fDeltaSeconds);
	return S_OK;
}

HRESULT CTransform::Move_Right(const _float & _fSpeed, const _float & _fDeltaSeconds)
{
	_VECTOR3 v3Look = Get_Right();
	Set_Position(Get_Position() + *D3DXVec3Normalize(&v3Look, &v3Look) * _fSpeed * _fDeltaSeconds);
	return S_OK;
}

HRESULT CTransform::Move_Left(const _float & _fSpeed, const _float & _fDeltaSeconds)
{
	_VECTOR3 v3Look = Get_Right();
	Set_Position(Get_Position() - *D3DXVec3Normalize(&v3Look, &v3Look) * _fSpeed * _fDeltaSeconds);
	return S_OK;
}

// 방향을 바꿈
HRESULT CTransform::Translate(const _VECTOR3 & _v3Pos, const _float & _fSpeed, const _float & _fDeltaSeconds, const _float& fLimitTime)
{
	_VECTOR3 _v3Dir = _VECTOR3(0.f ,0.f, 0.f);
	LookAt(_v3Pos, _v3Dir);
	_v3Dir = _v3Dir * _fSpeed * _fDeltaSeconds;
	if(fLimitTime < D3DXVec3Length(&(_v3Dir)))
		Set_Position(Get_Position() + _v3Dir);
	return S_OK;
}

HRESULT CTransform::Translate(CTransform * _pLookTransform, const _float & _fSpeed, const _float & _fDeltaSeconds, const _float & fLimitTime)
{
	if (nullptr == _pLookTransform)
		return E_FAIL;

	Translate(_pLookTransform->Get_Position(), _fSpeed, _fDeltaSeconds, fLimitTime);
	return S_OK;
}

HRESULT CTransform::LookAt(CTransform * _pLookTransform)
{
	if (nullptr == _pLookTransform)
		return E_FAIL;

	LookAt(_pLookTransform->Get_Position(), _VECTOR3(0.f, 0.f, 0.f));
	return S_OK;
}

HRESULT CTransform::LookAt(const _VECTOR3 & _v3Pos)
{
	LookAt(_v3Pos, _VECTOR3(0.f, 0.f, 0.f));
	return S_OK;
}

HRESULT CTransform::LookAt(const _VECTOR3 & _v3Pos, _VECTOR3 & _v3Dir)
{
	_VECTOR3		vPosition = Get_Position();
	_VECTOR3		vTargetPosition = _v3Pos;
	_VECTOR3		vLook = vTargetPosition - vPosition;
	_VECTOR3		vRight;
	D3DXVec3Cross(&vRight, &_VECTOR3(0.f, 1.f, 0.f), &vLook);
	_VECTOR3		vUp;
	D3DXVec3Cross(&vUp, &vLook, &vRight);
	_VECTOR3		vScale = Get_Scale();
	vRight = *D3DXVec3Normalize(&vRight, &vRight) * vScale.x;
	vUp = *D3DXVec3Normalize(&vUp, &vUp) * vScale.y;
	vLook = *D3DXVec3Normalize(&vLook, &vLook) * vScale.z;

	Set_Right(vRight);
	Set_Up( vUp);
	Set_Look(vLook);
	return E_NOTIMPL;
}

HRESULT CTransform::RotationAxisToFix(const _VECTOR3 & _v3Axis, const float & _fAngle)
{
	_VECTOR3 v3Scale;
	_float4x4 matRotation;
	D3DXMatrixRotationAxis(&matRotation, &_v3Axis, _fAngle);

	_VECTOR3 v3Right = Get_Reset_Right() * v3Scale.x;
	_VECTOR3 v3Up = Get_Reset_Up()* v3Scale.y;
	_VECTOR3 v3Look = Get_Reset_Look()* v3Scale.z;

	D3DXVec3TransformNormal(&v3Right, &v3Right, &matRotation);
	D3DXVec3TransformNormal(&v3Up, &v3Up, &matRotation);
	D3DXVec3TransformNormal(&v3Look, &v3Look, &matRotation);
	Set_Right(v3Right);
	Set_Up(v3Up);
	Set_Look(v3Look);
	return S_OK;
}

HRESULT CTransform::RotationAxisToTurn(const _VECTOR3 & _v3Axis, const _float& fDotPerSeconds, const _float & _fDeltaSeconds)
{
	_float4x4 matRotation;
	D3DXMatrixRotationAxis(&matRotation, &_v3Axis, fDotPerSeconds * _fDeltaSeconds);

	_VECTOR3 v3Right = Get_Right();
	_VECTOR3 v3Up = Get_Up();
	_VECTOR3 v3Look = Get_Look();
	D3DXVec3TransformNormal(&v3Right, &v3Right, &matRotation);
	D3DXVec3TransformNormal(&v3Up, &v3Up, &matRotation);
	D3DXVec3TransformNormal(&v3Look, &v3Look, &matRotation);
	Set_Right(v3Right);
	Set_Up(v3Up);
	Set_Look(v3Look);
	return S_OK;
}

_float4x4 CTransform::Get_WorldMatrixInverse()
{
	_float4x4 matViewMatrix;
	D3DXMatrixInverse(&matViewMatrix, 0, &m_matWorld);
	return matViewMatrix;
}

CTransform * CTransform::Create(const LPDIRECT3DDEVICE9 & _pDevice)
{
	CTransform* pInstance = new CTransform(_pDevice);
	if (FAILED(pInstance->NativeConstruct_ProtoType()))
	{
		MSG_BOX("CTransform::Create Failed");
		Safe_Release(pInstance);
	}
	return 	pInstance;
}

CComponent * CTransform::Clone(void *& _pArg)
{
	CTransform* pInstance = new CTransform(*this);
	if (FAILED(pInstance->NativeConstruct_Clone(_pArg)))
	{
		MSG_BOX("CTransform::Clone Failed");
		Safe_Release(pInstance);
	}
	return 	pInstance;
}

void CTransform::Free()
{
	__super::Free();
}
