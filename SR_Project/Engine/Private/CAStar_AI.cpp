#include "..\Public\CAStar_AI.h"
#include "CGameInstance.h"
#include "CTransform.h"

CAStar_AI::CAStar_AI(const LPDIRECT3DDEVICE9 & _pGraphic_Device)
	: CAIComponent(_pGraphic_Device),
	m_pCurTile(nullptr), m_pGoalTile(nullptr), m_pCenterTile(nullptr),
	m_bFindTarget(false)
{

}

CAStar_AI::CAStar_AI(const CAStar_AI & _rhs) 
	: CAIComponent(_rhs), 
	m_pCurTile(nullptr), m_pGoalTile(nullptr), m_pCenterTile(nullptr),
	m_bFindTarget(false)
{

}

HRESULT CAStar_AI::NativeConstruct_ProtoType()
{
	if (FAILED(__super::NativeConstruct_ProtoType()))
		return E_FAIL;

	return S_OK;
}

HRESULT CAStar_AI::NativeConstruct_Clone(void *& _pArg)
{
	if (FAILED(__super::NativeConstruct_Clone(_pArg)))
		return E_FAIL;
	CAStar_Manager* pAStarManager = CAStar_Manager::Get_Instance();
	Safe_AddRef(pAStarManager);
	{
		pAStarManager->Send_Data(m_tAStarDesc);
		_uint SIZE = m_tAStarDesc.iNumVerticesX * m_tAStarDesc.iNumVerticesZ;
		m_vecCheckOpen.resize(SIZE);
		m_vecCheckClose.resize(SIZE);
		m_vecDistance.resize(SIZE);
	}
	Safe_Release(pAStarManager);
	return S_OK;
}

HRESULT CAStar_AI::Move_Target(CTransform * _pTransform)
{
	if (nullptr == _pTransform)
		return E_FAIL;
	if (m_lsBestList.size() > 0)
	{
		_VECTOR3 dir = m_lsBestList.back()->v3Position - _pTransform->Get_Position();
		_float len = D3DXVec3Length(&dir);

		if (len <= 0.5f) 
			m_lsBestList.pop_back();
		else
			_pTransform->LookAt(m_lsBestList.back()->v3Position);
		return S_OK;
	}
	return E_FAIL;
}

void CAStar_AI::Running()
{
	// 찾지 못했을 때, 다시 검사
	if (false == m_bFindTarget && nullptr != m_pCenterTile)
		Make_Route(m_pCenterTile, m_pGoalTile);
}

HRESULT CAStar_AI::Start_AStar(const _VECTOR3 & _v3CurPos, const _VECTOR3 & _v3TargetPos, const _float4x4& _matWorldInve)
{
	Release_Data();
	_uint iSize = (_uint)m_tAStarDesc.vecTileList.size();
	_uint iCurPosIndex = Get_Index(_v3CurPos, _matWorldInve);
	_uint iTargetPosIndex = Get_Index(_v3TargetPos, _matWorldInve);
	// 인덱스가 범위 넘어 갔을 때
	if (iCurPosIndex >= iSize || iTargetPosIndex >= iSize)
		return E_FAIL;
	// 찾았으면 바로 리턴
	if (iCurPosIndex == iTargetPosIndex)
		return S_OK;

	m_pCurTile = (m_tAStarDesc.vecTileList)[iCurPosIndex];
	m_pGoalTile = (m_tAStarDesc.vecTileList)[iTargetPosIndex];

	m_pCenterTile = m_pCurTile;
	m_bFindTarget = false;
	return S_OK;
}

HRESULT CAStar_AI::Make_Route(TILE *& _pStart, TILE *& _pEnd)
{
	TILE* pTile = _pStart;
	// Find Size만큼 찾음
	for (_uint i = 0; i < FIND_SIZE; ++i)
	{
		// Open List가 비어있지 않으면, 방문한 노드 보지 못하게 제거
		if (false == m_lsOpenList.empty())
			m_lsOpenList.pop_front();
		// 타일을 방문했다면, 다시 방문 하지 않게 추가
		m_vecCheckClose[pTile->iIndex] = true;
		// 각 Tile을 검사
		for (auto& CheckTile : m_tAStarDesc.vecAdjTileList[pTile->iIndex])
		{
			if (true == m_vecCheckOpen[CheckTile->iIndex])
				continue;
			// End == Check Tile
			if (_pEnd == CheckTile)
			{
				CheckTile->pParents = pTile;
				// Make Best List 
				Make_BestList(m_pCurTile, m_pGoalTile);
				return S_OK;
			}
			_VECTOR3 _v3Dir = CheckTile->v3Position - pTile->v3Position;
			_float fCost = Calculate_DistCost(_pStart->v3Position, _pEnd->v3Position, CheckTile->v3Position, pTile->v3Position);
			m_lsOpenList.emplace_front(CheckTile);
			m_vecCheckOpen[CheckTile->iIndex] = true;
			CheckTile->pParents = pTile;
			m_vecDistance[CheckTile->iIndex] = fCost;
		}
		// Distance 검사
		vector<_float>& vecDistance = m_vecDistance;
		m_lsOpenList.sort([&vecDistance](TILE*& t1, TILE*& t2)->bool {
			return vecDistance[t1->iIndex] < vecDistance[t2->iIndex];
		});
		pTile = m_lsOpenList.front();
		m_pCenterTile = pTile;
	}
	return S_OK;
}

HRESULT CAStar_AI::Make_BestList(TILE *& _pStart, TILE *& _pEnd)
{
	m_bFindTarget = true;
	m_pCenterTile = nullptr;
	m_lsBestList.emplace_back(_pEnd);
	TILE* pTile = _pEnd;
	while (true)
	{
		pTile = pTile->pParents;
		if (pTile == _pStart)
			break;
		m_lsBestList.emplace_back(pTile);
	}
	return S_OK;
}

HRESULT CAStar_AI::Release_Data()
{
	// 방문 노드
	for (auto& iter : m_vecCheckOpen)
		iter = false;
	for (auto& iter : m_vecCheckClose)
		iter = false;

	// 방문할 리스트
	m_lsOpenList.clear();
	// 최상의 길 리스트
	m_lsBestList.clear();
	// 프레임 단위로 찾기 위한 변
	return S_OK;
}

_uint CAStar_AI::Get_Index(const _VECTOR3 & _v3Pos, const _float4x4& _matWorldInve)
{
	_VECTOR3 v3StartPos;
	D3DXVec3TransformCoord(&v3StartPos, &_v3Pos, &_matWorldInve);
	_uint		iIndex = (_uint)v3StartPos.z * m_tAStarDesc.iNumVerticesX + (_uint)v3StartPos.x;
	return iIndex;
}

_float CAStar_AI::Calculate_DistCost(const _VECTOR3 & _v3Start, const _VECTOR3 & _v3End, const _VECTOR3 & _v3Visited, const _VECTOR3 & _v3Cur)
{
	// 시작지에서 방문지까지 거리
	_VECTOR3 vCostF = _v3Visited - _v3Start;
	// 방문지에서 목표까지 거리
	_VECTOR3 vCostG = _v3Visited - _v3End;
	// 방문지에서 현재 있는 타일까지 거리
	_VECTOR3 vCostT = _v3Visited - _v3Cur;
	return D3DXVec3LengthSq(&vCostF) + D3DXVec3LengthSq(&vCostG) + D3DXVec3LengthSq(&vCostT);
}

CAStar_AI * CAStar_AI::Create(const LPDIRECT3DDEVICE9 & _pGraphic_Device)
{
	CAStar_AI* pInstance = new CAStar_AI(_pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_ProtoType()))
	{
		MSG_BOX("CAStar_AI::Clone Error");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CComponent * CAStar_AI::Clone(void *& _pArg)
{
	CAStar_AI* pInstance = new CAStar_AI(*this);
	if (FAILED(pInstance->NativeConstruct_Clone(_pArg)))
	{
		MSG_BOX("CAStar_AI::Clone Error");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CAStar_AI::Free()
{
	__super::Free();
}
