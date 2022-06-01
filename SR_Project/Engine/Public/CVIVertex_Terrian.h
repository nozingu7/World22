#pragma once
#include"CVIVertex.h"


BEGIN(Engine)

class ENGINE_DLL CVIVertex_Terrian final : public CVIVertex
{
public:
	typedef struct tagTerrianDesc
	{
		_uint			m_iNumVerticesX, m_iNumVerticesZ;
	}TERRIANDESC;
public:
	// Get Terrian  Desc
	const TERRIANDESC& Get_TerrianDesc() const { return m_tTerrianDesc; }
	// Start Pos
	const _VECTOR3& Get_TileSize() const { return m_v3TileSize; }
private:
	explicit CVIVertex_Terrian(const LPDIRECT3DDEVICE9& _pGraphic_Device);
	explicit CVIVertex_Terrian(const LPDIRECT3DDEVICE9& _pGraphic_Device, void*& _pTerrianIDesc);
	explicit CVIVertex_Terrian(const CVIVertex_Terrian& _Prototype);
	virtual ~CVIVertex_Terrian() = default;
public:
	virtual HRESULT NativeConstruct_ProtoType() override;
	HRESULT NativeConstruct_ProtoType(const _tchar * pHeightMapPath);
	virtual HRESULT NativeConstruct_Clone(void*& _pArg) override;
	// Render Method
	virtual HRESULT Render();
public:
	_float Get_TerrianFloorYPos(const _VECTOR3& _v3TargetPos, const _float4x4& _TerrianWorldMatrixInv);
private:
	TERRIANDESC			m_tTerrianDesc;
	_VECTOR3				m_v3TileSize;
public:
	static CVIVertex_Terrian* Create(const LPDIRECT3DDEVICE9& pGraphic_Device, void* _pTerrianIDesc);
	static CVIVertex_Terrian* Create(const LPDIRECT3DDEVICE9& pGraphic_Device, const _tchar* pHeightMapPath);
	virtual CComponent* Clone(void*& _pArg) override;
	virtual void Free();
};

END