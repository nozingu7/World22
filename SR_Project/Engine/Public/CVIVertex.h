#pragma once
#include "CComponent.h"

BEGIN(Engine)

class ENGINE_DLL CVIVertex abstract : public CComponent
{
protected:
	explicit CVIVertex(const LPDIRECT3DDEVICE9& _pGraphic_Device);
	explicit CVIVertex(const CVIVertex& _rhs);
	virtual ~CVIVertex() = default;
public:
	_VECTOR3* Get_VerticesPos() { return m_pVerticesPos; }
public:
	virtual HRESULT NativeConstruct_ProtoType() override;
	virtual HRESULT NativeConstruct_Clone(void*& _pArg) override;
	// Render Method
	virtual HRESULT Render();
protected:
	LPDIRECT3DVERTEXBUFFER9		m_pVB;
	_uint												m_iStride;
	_uint												m_iVertexCount;
	DWORD											m_dwVF;
	D3DPRIMITIVETYPE						m_d3dPrimitiveType;
	_uint												m_iPrimitiveCount;
protected:
	LPDIRECT3DINDEXBUFFER9			m_pIB;
	_uint												m_iPrimitiveByteSize;
	D3DFORMAT									m_eFormat;

protected:
	_VECTOR3*		m_pVerticesPos;
	_bool					m_bIsClone;
protected:
	HRESULT Create_VertexBuf(const _uint& _iAssignSize, const _uint& _iVertexCount, const DWORD& _dwVF, 
		const D3DPRIMITIVETYPE& _d3dPrimitiveType, const _uint& _iPrimitiveCount);
	HRESULT Create_IndexBuffer(const _uint& _iPrimitiveByteSize, const D3DFORMAT& _eFormat);
public:
	virtual CComponent* Clone(void*& _pArg) override;
	virtual void Free() override;
};

END