#include "CVIVertex_Terrian.h"



CVIVertex_Terrian::CVIVertex_Terrian(const LPDIRECT3DDEVICE9 & _pGraphic_Device)
	: CVIVertex(_pGraphic_Device)
{
	ZeroMemory(&m_v3TileSize, sizeof(_VECTOR3));
}

CVIVertex_Terrian::CVIVertex_Terrian(const LPDIRECT3DDEVICE9 & _pGraphic_Device, void*& _pTerrianIDesc)
	: CVIVertex(_pGraphic_Device)
{
	// Terrian Info
	memcpy(&m_tTerrianDesc, _pTerrianIDesc, sizeof(TERRIANDESC));
}

CVIVertex_Terrian::CVIVertex_Terrian(const CVIVertex_Terrian & _Prototype)
	: CVIVertex(_Prototype), 
	m_tTerrianDesc(_Prototype.m_tTerrianDesc),
	m_v3TileSize(_Prototype.m_v3TileSize)
{
}

HRESULT CVIVertex_Terrian::NativeConstruct_ProtoType()
{
	if (FAILED(__super::NativeConstruct_ProtoType()))
		return E_FAIL;

	_uint iNumVertices = m_tTerrianDesc.m_iNumVerticesX * m_tTerrianDesc.m_iNumVerticesZ;
	_uint iNumPrimitive = (m_tTerrianDesc.m_iNumVerticesX - 1)* (m_tTerrianDesc.m_iNumVerticesZ - 1) * 2;

	if (FAILED(Create_VertexBuf(sizeof(VTXTEX), iNumVertices, D3DFVF_XYZ | D3DFVF_TEX1, D3DPT_TRIANGLELIST, iNumPrimitive)))
		return E_FAIL;

	if (FAILED(Create_IndexBuffer(sizeof(FACEINDICES32), D3DFMT_INDEX32)))
		return E_FAIL;

	VTXTEX*			pVertices = nullptr;
	m_pVB->Lock(0, 0, (void**)&pVertices, 0);
	for (_uint i = 0; i < m_tTerrianDesc.m_iNumVerticesZ; ++i)
	{
		for (_uint j = 0; j < m_tTerrianDesc.m_iNumVerticesX; ++j)
		{
			_uint iIndex = m_tTerrianDesc.m_iNumVerticesX * i + j;
			pVertices[iIndex].v3Position = m_pVerticesPos[iIndex] = _VECTOR3(static_cast<_float>(j), 0.0f, static_cast<_float>(i));
			pVertices[iIndex].v2UVPosition = _VECTOR2(j / _float(m_tTerrianDesc.m_iNumVerticesX - 1), i / _float(m_tTerrianDesc.m_iNumVerticesZ - 1));
		}
	}
	m_pVB->Unlock();


	FACEINDICES32* pIndices = nullptr;

	m_pIB->Lock(0, 0, (void**)&pIndices, 0);
	_uint iNumFaces = 0;
	for (_uint i = 0; i < m_tTerrianDesc.m_iNumVerticesZ - 1; ++i)
	{
		for (_uint j = 0; j < m_tTerrianDesc.m_iNumVerticesX - 1; ++j)
		{
			_uint iIndex = i * m_tTerrianDesc.m_iNumVerticesX + j;

			_uint iIndices[] = {
				iIndex + m_tTerrianDesc.m_iNumVerticesX,
				iIndex + m_tTerrianDesc.m_iNumVerticesX + 1,
				iIndex + 1,
				iIndex
			};

			pIndices[iNumFaces]._1 = iIndices[0];
			pIndices[iNumFaces]._2 = iIndices[1];
			pIndices[iNumFaces]._3 = iIndices[2];
			++iNumFaces;

			pIndices[iNumFaces]._1 = iIndices[0];
			pIndices[iNumFaces]._2 = iIndices[2];
			pIndices[iNumFaces]._3 = iIndices[3];
			++iNumFaces;
		}
	}

	// Current Tile Size
	if(2 <= m_tTerrianDesc.m_iNumVerticesX * m_tTerrianDesc.m_iNumVerticesZ)
		m_v3TileSize = m_pVerticesPos[pIndices[0]._2] - m_pVerticesPos[pIndices[1]._3];
 	m_pIB->Unlock();

	return S_OK;
}

HRESULT CVIVertex_Terrian::NativeConstruct_ProtoType(const _tchar * pHeightMapPath)
{
	if (FAILED(__super::NativeConstruct_ProtoType()))
		return E_FAIL;

	HANDLE		hFile = CreateFile(pHeightMapPath, GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (0 == hFile)
		return FALSE;

	_ulong		dwByte = 0;
	BITMAPFILEHEADER			fh;
	BITMAPINFOHEADER			ih;

	ReadFile(hFile, &fh, sizeof(BITMAPFILEHEADER), &dwByte, nullptr);
	ReadFile(hFile, &ih, sizeof(BITMAPINFOHEADER), &dwByte, nullptr);

	m_tTerrianDesc.m_iNumVerticesX = ih.biWidth;
	m_tTerrianDesc.m_iNumVerticesZ = ih.biHeight;

	_ulong*			pPixel = new _ulong[m_tTerrianDesc.m_iNumVerticesX * m_tTerrianDesc.m_iNumVerticesZ];
	ReadFile(hFile, pPixel, sizeof(_ulong) * m_tTerrianDesc.m_iNumVerticesX * m_tTerrianDesc.m_iNumVerticesZ, &dwByte, nullptr);
	CloseHandle(hFile);

	if (FAILED(__super::Create_VertexBuf(sizeof(VTXTEX), m_tTerrianDesc.m_iNumVerticesX * m_tTerrianDesc.m_iNumVerticesZ,
		D3DFVF_XYZ | D3DFVF_TEX1, D3DPT_TRIANGLELIST, (m_tTerrianDesc.m_iNumVerticesX - 1) * (m_tTerrianDesc.m_iNumVerticesZ - 1) * 2)))
		return E_FAIL;
	VTXTEX*			pVertices = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVertices, 0);

	for (_uint i = 0; i < m_tTerrianDesc.m_iNumVerticesZ; ++i)
	{
		for (_uint j = 0; j < m_tTerrianDesc.m_iNumVerticesX; ++j)
		{
			_uint iIndex = i * m_tTerrianDesc.m_iNumVerticesX + j;

			pVertices[iIndex].v3Position = m_pVerticesPos[iIndex] = _VECTOR3((_float)j,  0, (_float)i);
			pVertices[iIndex].v2UVPosition = _VECTOR2(j / _float(m_tTerrianDesc.m_iNumVerticesX - 1) * 20.f, i / _float(m_tTerrianDesc.m_iNumVerticesZ - 1) * 20.f);
		}
	}
	m_pVB->Unlock();


	if (FAILED(__super::Create_IndexBuffer(sizeof(FACEINDICES32), D3DFMT_INDEX32)))
		return E_FAIL;

	FACEINDICES32*			pIndices = nullptr;

	m_pIB->Lock(0, 0, (void**)&pIndices, 0);

	_uint		iNumFaces = 0;

	for (_uint i = 0; i < m_tTerrianDesc.m_iNumVerticesZ - 1; ++i)
	{
		for (_uint j = 0; j < m_tTerrianDesc.m_iNumVerticesX - 1; ++j)
		{
			_uint iIndex = i * m_tTerrianDesc.m_iNumVerticesX + j;

			_uint iIndices[] = {
				iIndex + m_tTerrianDesc.m_iNumVerticesX,
				iIndex + m_tTerrianDesc.m_iNumVerticesX + 1,
				iIndex + 1,
				iIndex
			};

			pIndices[iNumFaces]._1 = iIndices[0];
			pIndices[iNumFaces]._2 = iIndices[1];
			pIndices[iNumFaces]._3 = iIndices[2];
			++iNumFaces;

			pIndices[iNumFaces]._1 = iIndices[0];
			pIndices[iNumFaces]._2 = iIndices[2];
			pIndices[iNumFaces]._3 = iIndices[3];
			++iNumFaces;
		}
	}
	if (2 <= m_tTerrianDesc.m_iNumVerticesX * m_tTerrianDesc.m_iNumVerticesZ)
		m_v3TileSize = m_pVerticesPos[pIndices[0]._2] - m_pVerticesPos[pIndices[1]._3];

	m_pIB->Unlock();

	Safe_Delete_Array(pPixel);

	return S_OK;
}

HRESULT CVIVertex_Terrian::NativeConstruct_Clone(void *& _pArg)
{
	if (FAILED(__super::NativeConstruct_Clone(_pArg)))
		return E_FAIL;

	return S_OK;
}

HRESULT CVIVertex_Terrian::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	return S_OK;
}

_float CVIVertex_Terrian::Get_TerrianFloorYPos(const _VECTOR3 & _v3TargetPos, const _float4x4 & _TerrianWorldMatrixInv)
{
	_VECTOR3 v3Out;
	D3DXVec3TransformCoord(&v3Out, &_v3TargetPos, &_TerrianWorldMatrixInv);

	//  인덱스를 구함
	_uint iIndex = (_uint)v3Out.z/ m_tTerrianDesc.m_iNumVerticesX +  (_uint)v3Out.x;

	_uint iIndices[4] =
	{
		iIndex + m_tTerrianDesc.m_iNumVerticesX,
		iIndex + m_tTerrianDesc.m_iNumVerticesX + 1,
		iIndex + 1,
		iIndex
	};

	_VECTOR3 v3SqaurePosList[4] = {};
	for (_uint i = 0; i < 4; ++i)
		v3SqaurePosList[i] = m_pVerticesPos[iIndices[i]];
	
	// 플레이어로부터 가로 거리
	_float fWidth = v3Out.x - v3SqaurePosList[0].x;
	_float fHeight = v3SqaurePosList[0].z - v3Out.z;
	//  현재 삼각형 안에 있는지 구함
	D3DXPLANE			Plane;
	if (fWidth > fHeight)
		D3DXPlaneFromPoints(&Plane, &v3SqaurePosList[0], &v3SqaurePosList[1], &v3SqaurePosList[2]);
	else
		D3DXPlaneFromPoints(&Plane, &v3SqaurePosList[0], &v3SqaurePosList[2], &v3SqaurePosList[3]);

	// 플레인에 따른 실제 평면의 높이를 구함
	v3Out.y = (-(Plane.a * v3Out.x) - (Plane.c * v3Out.z) - Plane.d) / Plane.b;
	_float4x4 WorldMatrix;
	D3DXMatrixInverse(&WorldMatrix, 0, &_TerrianWorldMatrixInv);
	D3DXVec3TransformCoord(&v3Out, &v3Out, &WorldMatrix);
	return v3Out.y + 0.5f;
}

CVIVertex_Terrian * CVIVertex_Terrian::Create(const LPDIRECT3DDEVICE9& pGraphic_Device, void* _pTerrianIDesc)
{
	CVIVertex_Terrian*		pInstance = new CVIVertex_Terrian(pGraphic_Device, _pTerrianIDesc);

	if (FAILED(pInstance->NativeConstruct_ProtoType()))
	{
		MSG_BOX("Failed to Created : CVIBuffer_Terrain");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CVIVertex_Terrian * CVIVertex_Terrian::Create(const LPDIRECT3DDEVICE9& pGraphic_Device, const _tchar* pHeightMapPath)
{
	CVIVertex_Terrian*		pInstance = new CVIVertex_Terrian(pGraphic_Device);

	if (FAILED(pInstance->NativeConstruct_ProtoType(pHeightMapPath)))
	{
		MSG_BOX("Failed to Created : CVIBuffer_Terrain");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CComponent * CVIVertex_Terrian::Clone(void *& _pArg)
{
	CVIVertex_Terrian*		pInstance = new CVIVertex_Terrian(*this);

	if (FAILED(pInstance->NativeConstruct_Clone(_pArg)))
	{
		MSG_BOX("Failed to Created : CVIBuffer_Terrain");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CVIVertex_Terrian::Free()
{
	__super::Free();
}
