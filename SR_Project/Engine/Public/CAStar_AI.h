#pragma once
#include "CAIComponent.h"

BEGIN(Engine)

class ENGINE_DLL CAStar_AI final : public CAIComponent
{
public:
	typedef struct tagAStarDesc
	{
		vector<TILE*>					vecTileList;
		vector<vector<TILE*>>	vecAdjTileList;
		_uint iNumVerticesX;
		_uint iNumVerticesZ;
	}ASTARDESC;
public:
	
private:
	explicit CAStar_AI(const LPDIRECT3DDEVICE9& _pGraphic_Device);
	explicit CAStar_AI(const CAStar_AI& _rhs);
	virtual ~CAStar_AI() = default;
public:
	// Find Target
	const _bool& Is_Find_Target() const { return m_bFindTarget; }
	// Get BestList
	const list<TILE*>& Get_BestList() const { return m_lsBestList; }
public:
	// NativeConstruct ProtoType, Clone
	virtual HRESULT NativeConstruct_ProtoType() override;
	virtual HRESULT NativeConstruct_Clone(void*& _pArg) override;

public:
	// Move Target
	HRESULT Move_Target(class CTransform* _pTransform);
	// Find Target
	void Running();
	// Start A_Star
	HRESULT Start_AStar(const _VECTOR3& _v3CurPos, const _VECTOR3& _v3TargetPos, const _float4x4& _matWorldInve);
private:
	// Make Route 
	HRESULT Make_Route(TILE*& _pStart, TILE*& _pEnd);
	// Make Best List
	HRESULT Make_BestList(TILE*& _pStart, TILE*& _pEnd);
	// Release Data 
	HRESULT Release_Data();
private:
	// Get Index
	_uint			Get_Index(const _VECTOR3& _v3Pos, const _float4x4& _matWorldInve);
	_float			Calculate_DistCost(const _VECTOR3& _v3Start, const _VECTOR3& _v3End,  const _VECTOR3& _v3Visited, const _VECTOR3& _v3Cur);
private:
	ASTARDESC		m_tAStarDesc;
private:
	// 현재 있는 타일
	TILE* m_pCurTile;
	// 목표 타일
	TILE* m_pGoalTile;
	// 중간 타일
	TILE* m_pCenterTile;
	// Open List
	vector<_bool> m_vecCheckOpen;
	// Close List
	vector <_bool> m_vecCheckClose;
	// Distance List
	vector<_float> m_vecDistance;
	//	OpenList
	list<TILE*> m_lsOpenList;
	// 최종 길
	list<TILE*> m_lsBestList;
private:
	// X번 검사( 너무 적으면 목표를 찾을 때, 이상한 곳으로 왔다갔다 거림) 
	const _uint  FIND_SIZE = 50;
	// 현재 목표를 찾았는지 확인
	_bool			m_bFindTarget;
public:
	static CAStar_AI* Create(const LPDIRECT3DDEVICE9& _pGraphic_Device);
	virtual CComponent* Clone(void*& _pArg) override;
	virtual void Free() override;
};

END