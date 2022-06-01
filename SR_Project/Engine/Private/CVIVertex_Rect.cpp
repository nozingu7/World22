#include "..\Public\CVIVertex_Rect.h"

CVIVertex_Rect::CVIVertex_Rect(const LPDIRECT3DDEVICE9 & _pGraphic_Device)
	: CVIVertex(_pGraphic_Device)
{
}

CVIVertex_Rect::CVIVertex_Rect(const CVIVertex_Rect & _rhs)
	: CVIVertex(_rhs)
{
	
}

HRESULT CVIVertex_Rect::NativeConstruct_ProtoType()
{
	if (FAILED(__super::NativeConstruct_ProtoType()))
		E_FAIL;

	if (FAILED(Create_VertexBuf(sizeof(VTXTEX), 4, D3DFVF_XYZ | D3DFVF_TEX1, D3DPT_TRIANGLELIST, 2)))
		return E_FAIL;

	if (FAILED(Create_IndexBuffer(sizeof(FACEINDICES16), D3DFMT_INDEX16)))
		return E_FAIL;

	// Lock
	VTXTEX* pVertices = nullptr;
	m_pVB->Lock(0, 0, (void**)(&pVertices), 0);

	pVertices[0].v3Position = _VECTOR3(-0.5f, 0.5f, 0.f);
	pVertices[0].v2UVPosition = _VECTOR2(0.0f, 0.f);

	pVertices[1].v3Position = _VECTOR3(0.5f, 0.5f, 0.f);
	pVertices[1].v2UVPosition = _VECTOR2(1.f, 0.f);

	pVertices[2].v3Position = _VECTOR3(0.5f, -0.5f, 0.f);
	pVertices[2].v2UVPosition = _VECTOR2(1.f, 1.f);

	pVertices[3].v3Position = _VECTOR3(-0.5f, -0.5f, 0.f);
	pVertices[3].v2UVPosition = _VECTOR2(0.f, 1.f);

	// UnLock
	m_pVB->Unlock();

	FACEINDICES16*		pIndices = nullptr;

	m_pIB->Lock(0, 0, (void**)&pIndices, 0);

	pIndices[0]._1 = 0;
	pIndices[0]._2 = 1;
	pIndices[0]._3 = 2;

	pIndices[1]._1 = 0;
	pIndices[1]._2 = 2;
	pIndices[1]._3 = 3;

	m_pIB->Unlock();

	return S_OK;
}

HRESULT CVIVertex_Rect::NativeConstruct_Clone(void *& _pArg)
{
	if (FAILED(__super::NativeConstruct_Clone(_pArg)))
		E_FAIL;

	return S_OK;
}

CVIVertex_Rect * CVIVertex_Rect::Create(LPDIRECT3DDEVICE9 & _pGraphic_Device)
{
	CVIVertex_Rect* pInstance = new CVIVertex_Rect(_pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_ProtoType()))
	{
		MSG_BOX("CVIVertex_Rect::Create Error");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CComponent * CVIVertex_Rect::Clone(void *& _pArg)
{
	CVIVertex_Rect* pInstance = new CVIVertex_Rect(*this);
	if (FAILED(pInstance->NativeConstruct_Clone(_pArg)))
	{
		MSG_BOX("CVIVertex_Rect::Create Error");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CVIVertex_Rect::Free()
{
	__super::Free();
}
