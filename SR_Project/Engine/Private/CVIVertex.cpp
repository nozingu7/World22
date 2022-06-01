#include "..\Public\CVIVertex.h"


CVIVertex::CVIVertex(const LPDIRECT3DDEVICE9 & _pGraphic_Device)
	: CComponent(_pGraphic_Device), 
	m_pVB(nullptr),
	m_iStride(0), m_iVertexCount(0),
	m_dwVF(0),
	m_iPrimitiveCount(0),
	m_pIB(nullptr),
	m_iPrimitiveByteSize(0),
	m_eFormat(D3DFMT_UNKNOWN), 
	m_pVerticesPos(nullptr), m_bIsClone(false)
{
}

CVIVertex::CVIVertex(const CVIVertex & _rhs)
	: CComponent(_rhs)
	, m_pVB(_rhs.m_pVB)
	, m_iStride(_rhs.m_iStride), m_iVertexCount(_rhs.m_iVertexCount)
	, m_dwVF(_rhs.m_dwVF)
	, m_d3dPrimitiveType(_rhs.m_d3dPrimitiveType),m_iPrimitiveCount(_rhs.m_iPrimitiveCount)
	, m_pIB(_rhs.m_pIB), m_iPrimitiveByteSize(_rhs.m_iPrimitiveByteSize), m_eFormat(_rhs.m_eFormat)
	, m_pVerticesPos(_rhs.m_pVerticesPos), m_bIsClone(true)
{
	Safe_AddRef(m_pVB);
	Safe_AddRef(m_pIB);
}

HRESULT CVIVertex::NativeConstruct_ProtoType()
{
	if (FAILED(__super::NativeConstruct_ProtoType()))
		E_FAIL;

	return S_OK;
}

HRESULT CVIVertex::NativeConstruct_Clone(void *& _pArg)
{
	if (FAILED(__super::NativeConstruct_Clone(_pArg)))
		E_FAIL;

	return S_OK;
}

HRESULT CVIVertex::Render()
{
	if (nullptr == m_pGraphic_Device || nullptr == m_pVB)
		return E_FAIL;

	m_pGraphic_Device->SetStreamSource(0, m_pVB, 0, m_iStride);
	m_pGraphic_Device->SetFVF(m_dwVF);
	m_pGraphic_Device->SetIndices(m_pIB);
	m_pGraphic_Device->DrawIndexedPrimitive(m_d3dPrimitiveType, 0, 0, m_iVertexCount, 0, m_iPrimitiveCount);

	return S_OK;
}

HRESULT CVIVertex::Create_VertexBuf(const _uint & _iAssignSize, const _uint & _iVertexCount, const DWORD & _dwVF,
									const D3DPRIMITIVETYPE& _d3dPrimitiveType, const _uint& _iPrimitiveCount)
{
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;

	if (FAILED(m_pGraphic_Device->CreateVertexBuffer(_iAssignSize * _iVertexCount, 0,
		_dwVF, D3DPOOL_MANAGED, &m_pVB, nullptr)))
		return E_FAIL;

	this->m_iStride = _iAssignSize;
	this->m_iVertexCount = _iVertexCount;
	this->m_dwVF = _dwVF;
	this->m_d3dPrimitiveType = _d3dPrimitiveType;
	this->m_iPrimitiveCount = _iPrimitiveCount;

	m_pVerticesPos = new _VECTOR3[m_iVertexCount];

	return S_OK;
}

HRESULT CVIVertex::Create_IndexBuffer(const _uint& _iPrimitiveByteSize, const D3DFORMAT& _eFormat)
{
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;

	if (FAILED(m_pGraphic_Device->CreateIndexBuffer(m_iPrimitiveCount * _iPrimitiveByteSize, 0,
		_eFormat, D3DPOOL_MANAGED, &m_pIB, nullptr)))
		return E_FAIL;

	this->m_iPrimitiveByteSize = _iPrimitiveByteSize;
	this->m_eFormat = _eFormat;

	return S_OK;
}

CComponent * CVIVertex::Clone(void *& _pArg)
{

	return nullptr;
}

void CVIVertex::Free()
{
	if (!m_bIsClone)
		Safe_Delete_Array(m_pVerticesPos);
	Safe_Release(m_pVB);
	Safe_Release(m_pIB);
	__super::Free();
}
