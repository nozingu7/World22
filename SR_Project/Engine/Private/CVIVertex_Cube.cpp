#include "CVIVertex_Cube.h"
#include "..\Public\CVIVertex_Cube.h"

CVIVertex_Cube::CVIVertex_Cube(const LPDIRECT3DDEVICE9 & _pGraphic_Device)
	: CVIVertex(_pGraphic_Device)
{
}

CVIVertex_Cube::CVIVertex_Cube(const CVIVertex_Cube & _rhs)
	: CVIVertex(_rhs)
{
}

HRESULT CVIVertex_Cube::NativeConstruct_ProtoType()
{
	if (FAILED(__super::NativeConstruct_ProtoType()))
		E_FAIL;

	if (FAILED(Create_VertexBuf(sizeof(VTXCUBETEX), 8, D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE3(0), D3DPT_TRIANGLELIST, 12)))
		return E_FAIL;

	if (FAILED(Create_IndexBuffer(sizeof(FACEINDICES16), D3DFMT_INDEX16)))
		return E_FAIL;

	VTXCUBETEX*			pVertices = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVertices, 0);

	pVertices[0].v3Position = _VECTOR3(-0.5f, 0.5f, -0.5f);
	pVertices[0].v3UvPosition = pVertices[0].v3Position;

	pVertices[1].v3Position = _VECTOR3(0.5f, 0.5f, -0.5f);
	pVertices[1].v3UvPosition = pVertices[1].v3Position;

	pVertices[2].v3Position = _VECTOR3(0.5f, -0.5f, -0.5f);
	pVertices[2].v3UvPosition = pVertices[2].v3Position;

	pVertices[3].v3Position = _VECTOR3(-0.5f, -0.5f, -0.5f);
	pVertices[3].v3UvPosition = pVertices[3].v3Position;

	pVertices[4].v3Position = _VECTOR3(-0.5f, 0.5f, 0.5f);
	pVertices[4].v3UvPosition = pVertices[4].v3Position;

	pVertices[5].v3Position = _VECTOR3(0.5f, 0.5f, 0.5f);
	pVertices[5].v3UvPosition = pVertices[5].v3Position;

	pVertices[6].v3Position = _VECTOR3(0.5f, -0.5f, 0.5f);
	pVertices[6].v3UvPosition = pVertices[6].v3Position;

	pVertices[7].v3Position = _VECTOR3(-0.5f, -0.5f, 0.5f);
	pVertices[7].v3UvPosition = pVertices[7].v3Position;

	m_pVB->Unlock();

	FACEINDICES16*			pIndices = nullptr;

	m_pIB->Lock(0, 0, (void**)&pIndices, 0);

	/* +X */
	pIndices[0]._1 = 1; pIndices[0]._2 = 5; pIndices[0]._3 = 6;
	pIndices[1]._1 = 1; pIndices[1]._2 = 6; pIndices[1]._3 = 2;

	/* -X */
	pIndices[2]._1 = 4; pIndices[2]._2 = 0; pIndices[2]._3 = 3;
	pIndices[3]._1 = 4; pIndices[3]._2 = 3; pIndices[3]._3 = 7;

	/* +Y */
	pIndices[4]._1 = 4; pIndices[4]._2 = 5; pIndices[4]._3 = 1;
	pIndices[5]._1 = 4; pIndices[5]._2 = 1; pIndices[5]._3 = 0;

	/* -Y */
	pIndices[6]._1 = 3; pIndices[6]._2 = 2; pIndices[6]._3 = 6;
	pIndices[7]._1 = 3; pIndices[7]._2 = 6; pIndices[7]._3 = 7;

	/* +Z */
	pIndices[8]._1 = 5; pIndices[8]._2 = 4; pIndices[8]._3 = 7;
	pIndices[9]._1 = 5; pIndices[9]._2 = 7; pIndices[9]._3 = 6;

	/* -Z */
	pIndices[10]._1 = 0; pIndices[10]._2 = 1; pIndices[10]._3 = 2;
	pIndices[11]._1 = 0; pIndices[11]._2 = 2; pIndices[11]._3 = 3;

	m_pIB->Unlock();
	return S_OK;
}

HRESULT CVIVertex_Cube::NativeConstruct_Clone(void *& _pArg)
{
	if (FAILED(__super::NativeConstruct_Clone(_pArg)))
		E_FAIL;

	return S_OK;
}

CVIVertex_Cube * CVIVertex_Cube::Create(LPDIRECT3DDEVICE9 & _pGraphic_Device)
{
	CVIVertex_Cube* pInstance = new CVIVertex_Cube(_pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_ProtoType()))
	{
		MSG_BOX("CVIVertex_Rect::Create Error");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CComponent * CVIVertex_Cube::Clone(void *& _pArg)
{
	CVIVertex_Cube* pInstance = new CVIVertex_Cube(*this);
	if (FAILED(pInstance->NativeConstruct_Clone(_pArg)))
	{
		MSG_BOX("CVIVertex_Rect::Create Error");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CVIVertex_Cube::Free()
{
	__super::Free();
}
