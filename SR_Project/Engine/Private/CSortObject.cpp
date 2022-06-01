#include "CSortObject.h"
#include "..\Public\CSortObject.h"
#include "CTransform.h"

CSortObject::CSortObject(const LPDIRECT3DDEVICE9 & _pDevice)
	: CGameObject(_pDevice), m_fCamToDistance(0.f)
{
}

CSortObject::CSortObject(const CSortObject & _pProtoType)
	: CGameObject(_pProtoType), m_fCamToDistance(0.f)
{
}

HRESULT CSortObject::NativeConstruct_ProtoType()
{
	if (FAILED(__super::NativeConstruct_ProtoType()))
		return E_FAIL;

	return S_OK;
}

HRESULT CSortObject::NativeConstruct_Clone(void *& pArg)
{
	if (FAILED(__super::NativeConstruct_Clone(pArg)))
		return E_FAIL;

	return S_OK;
}

void CSortObject::Tick(const _float & _fDeltaTime)
{
	__super::Tick(_fDeltaTime);
}

void CSortObject::Late_Tick(const _float & _fDeltaTime)
{
	__super::Late_Tick(_fDeltaTime);
}

HRESULT CSortObject::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;
	return S_OK;
}

void CSortObject::Compute_CamDistance(CTransform * _pTransform)
{
	if (nullptr == _pTransform)
		return;

	_float4x4 ViewMatrix;
	m_pGraphic_Device->GetTransform(D3DTS_VIEW, &ViewMatrix);
	D3DXMatrixInverse(&ViewMatrix, 0, &ViewMatrix);

	_VECTOR3 v3CamPos = *(_VECTOR3*)&ViewMatrix.m[3][0];
	v3CamPos -= _pTransform->Get_Position();
	m_fCamToDistance = D3DXVec3LengthSq(&v3CamPos);
}
void CSortObject::Free()
{
	__super::Free();
}
