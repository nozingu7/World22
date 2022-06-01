#include "..\Public\CCamera.h"
#include "CComponent_Manager.h"
#include "CGameInstance.h"

CCamera::CCamera(const LPDIRECT3DDEVICE9 & _pDevice, void*& _pCameraInitData)
	: CGameObject(_pDevice), m_pTransformComp(nullptr)
{
	memcpy(&m_tCameraInitDesc, _pCameraInitData, sizeof(CAMERAINITDESC));
}

CCamera::CCamera(const CCamera & _rhs) 
	: CGameObject(_rhs), m_tCameraInitDesc(_rhs.m_tCameraInitDesc)
	, m_pTransformComp(nullptr)
{
}

HRESULT CCamera::NativeConstruct_ProtoType()
{
	if (__super::NativeConstruct_ProtoType())
		return E_FAIL;

	return S_OK;
}

HRESULT CCamera::NativeConstruct_Clone(void *& pArg)
{
	if (nullptr == pArg)
		return E_FAIL;

	if (__super::NativeConstruct_Clone(pArg))
		return E_FAIL;

	if (FAILED(Add_Transform()))
		return E_FAIL;

	memcpy(&m_tCameraCloneDesc, pArg, sizeof(CAMERACLONEDESC));

	m_pTransformComp->LookAt(m_tCameraCloneDesc.v3Look);
	m_pTransformComp->Set_Position(m_tCameraCloneDesc.v3Pos);
	return S_OK;
}

void CCamera::Tick(const _float & _fDeltaTime)
{
	__super::Tick(_fDeltaTime);

	Bind_Matrixes();
}

void CCamera::Late_Tick(const _float & _fDeltaTime)
{
	__super::Late_Tick(_fDeltaTime);
}

HRESULT CCamera::Render()
{
	if (__super::Render())
		return E_FAIL;

	return S_OK;
}

HRESULT CCamera::Bind_Matrixes()
{
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;

	m_pGraphic_Device->SetTransform(D3DTS_VIEW, &m_pTransformComp->Get_WorldMatrixInverse());

	_float4x4		matPerspective;
	D3DXMatrixPerspectiveFovLH(&matPerspective, m_tCameraCloneDesc.fForv, m_tCameraCloneDesc.fAspect,
		m_tCameraCloneDesc.fMinDis, m_tCameraCloneDesc.fMaxDis);
	m_pGraphic_Device->SetTransform(D3DTS_PROJECTION, &matPerspective);
	return S_OK;
}

HRESULT CCamera::Add_Transform()
{
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	// Set Transform
	m_pTransformComp = static_cast<CTransform*>(pGameInstance->Clone_Component(m_tCameraInitDesc.m_iLevel, 
																						m_tCameraInitDesc.pTransformProtoTypeTag));

	Safe_Release(pGameInstance);
	return S_OK;
}

void CCamera::Free()
{
	Safe_Release(m_pTransformComp);
	__super::Free();
}
