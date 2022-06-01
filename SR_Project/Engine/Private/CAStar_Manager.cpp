#include "CAStar_Manager.h"
#include "CMyThread.h"
#include "CGameInstance.h"
#include <process.h>

IMPLEMENT_SINGLETON(CAStar_Manager)

CAStar_Manager::CAStar_Manager() 
	: m_iSaveThreadID(0)
{

}


HRESULT CAStar_Manager::Ready_AStar(byte* _pTileInfo, const _float4x4& _matTerrianWorldInv, const _VECTOR3& _v3TileSize,
	const _uint& _iTileWidth, const _uint& _iTileHeight)
{
	if (nullptr == _pTileInfo)
	{
		MSG_BOX("Engine -> CAStar_Manager::Ready_AStar -> Tile Info Is Nullptr ");
		return E_FAIL;
	}

	_VECTOR3 v3StartPos, v3Size, v3Pos;
	D3DXVec3TransformCoord(&v3StartPos, &_v3TileSize, &_matTerrianWorldInv);
	v3Size = v3StartPos;
	v3Pos = v3StartPos / 2.f;
	m_tAStarDesc.iNumVerticesX =		_iTileWidth - 1;
	m_tAStarDesc.iNumVerticesZ =		_iTileHeight - 1;
	// Reserve
	m_tAStarDesc.vecTileList.reserve(m_tAStarDesc.iNumVerticesX  * m_tAStarDesc.iNumVerticesZ + 1);
	m_tAStarDesc.vecAdjTileList.reserve(m_tAStarDesc.iNumVerticesX  * m_tAStarDesc.iNumVerticesZ + 1);

	// Ready Tile
	for (_uint i = 0; i < m_tAStarDesc.iNumVerticesZ; ++i)
	{
		_VECTOR3 pos = v3Pos;
		for (_uint j = 0; j < m_tAStarDesc.iNumVerticesX; ++j)
		{
			_uint iIndex = m_tAStarDesc.iNumVerticesX * i + j;
			TILE* pTile = new TILE();
			pTile->v3Position = pos;
			pTile->iIndex = iIndex;
			pTile->bType = _pTileInfo[iIndex];
			m_tAStarDesc.vecTileList.emplace_back(pTile);
			pos.x += v3Size.x;
		}
		v3Pos.z+= v3Size.z;
	}
	// Ready Adj
	for (_uint i = 0; i < m_tAStarDesc.iNumVerticesZ; ++i)
	{
		for (_uint j = 0; j < m_tAStarDesc.iNumVerticesX; ++j)
		{
			int iIndex = i * m_tAStarDesc.iNumVerticesX + j;
			m_tAStarDesc.vecAdjTileList.emplace_back(vector<TILE*>());
			m_tAStarDesc.vecAdjTileList[iIndex].reserve(8);
			// Ÿ�� ������ ���� �� ����
			if (0 == (iIndex % (m_tAStarDesc.iNumVerticesX)))
				continue;
			// Ÿ�� ���� �� ���� ������
			// �ε��� / (Ÿ�� X ���� * 2)
			if ((m_tAStarDesc.iNumVerticesX - 1) == (iIndex % (m_tAStarDesc.iNumVerticesX)))
				continue;

			// Tile�� ����
			// �ε��� / Ÿ�� X ����
			// Up, pLeft, pRight, pDown �˻�
			TILE* pUp = Check_DirectionTile(m_tAStarDesc.vecTileList, iIndex + (m_tAStarDesc.iNumVerticesX + 1));
			TILE* pLeft = Check_DirectionTile(m_tAStarDesc.vecTileList, iIndex - 1);
			TILE* pRight = Check_DirectionTile(m_tAStarDesc.vecTileList, iIndex + 1);
			TILE* pDown = Check_DirectionTile(m_tAStarDesc.vecTileList, iIndex - (m_tAStarDesc.iNumVerticesX));
			// Left Up, Right Up, Left Down, Right Down �˻�
			TILE* pLeftUp = Check_DirectionTile(m_tAStarDesc.vecTileList, iIndex + (m_tAStarDesc.iNumVerticesX - 1));
			TILE* pRightUp = Check_DirectionTile(m_tAStarDesc.vecTileList, iIndex + (m_tAStarDesc.iNumVerticesX * 2));
			TILE* pLeftDown = Check_DirectionTile(m_tAStarDesc.vecTileList, iIndex - (m_tAStarDesc.iNumVerticesX - 1));
			TILE* pRightDown = Check_DirectionTile(m_tAStarDesc.vecTileList, iIndex - (m_tAStarDesc.iNumVerticesX + 1));

			// TileList
			TILE* pTileList[8] = { pUp, pLeft, pRight, pDown, pLeftUp, pRightUp, pLeftDown, pRightDown };
			for (_uint k = 0; k < 8; ++k)
				if (nullptr != pTileList[k])
				{
					_bool bSame = false;
					for (auto & iter : m_tAStarDesc.vecAdjTileList[iIndex])
						if (iter->iIndex == pTileList[k]->iIndex)
							bSame = true;
					if(false == bSame)
						m_tAStarDesc.vecAdjTileList[iIndex].emplace_back(pTileList[k]);
				}
		}
	}
	return S_OK;
}


HRESULT CAStar_Manager::Register_AStar(CAStar_AI *& _pAStar)
{
	if (nullptr == _pAStar)
		return E_FAIL;

	// �׸��� ������ ����
	Safe_AddRef(_pAStar);
	m_lsAStarList.emplace_back(_pAStar);
	//  ���� AStar �ȿ� �˻��ϴ� �͵��� ���ٸ�, �����带 �����Ų��.
	if (1 >= m_lsAStarList.size())
	{
		InitializeCriticalSection(&m_CriticalSection);

		m_hThread = (HANDLE)(_beginthreadex(nullptr, 0, Run_AStar, this, 0, nullptr));
		if (nullptr == m_hThread)
			return E_FAIL;
	}
	return S_OK;
}
// Running 
HRESULT CAStar_Manager::Running()
{
	EnterCriticalSection(&m_CriticalSection);
	// Lock
	while (true)
	{
		auto& iter = m_lsAStarList.begin();
		for (; iter != m_lsAStarList.end();)
		{
			(*iter)->Running();
			if (true == (*iter)->Is_Find_Target())
			{
				Safe_Release((*iter));
				iter = m_lsAStarList.erase(iter);
			}
			else
				++iter;
		}

		if (0 >= m_lsAStarList.size())
			break;
	}
	LeaveCriticalSection(&m_CriticalSection);
	End_Running();
	return S_OK;
}
// Run AStar
_uint CAStar_Manager::Run_AStar(void * _pArg)
{
	CAStar_Manager* pMgr = static_cast<CAStar_Manager*>(_pArg);
	if (nullptr == pMgr)
		return 0;

	pMgr->Running();
	return 0;
}

HRESULT CAStar_Manager::End_Running()
{
	if (0 < m_lsAStarList.size())
		return E_FAIL;

	WaitForSingleObject(m_hThread, INFINITE);
	DeleteCriticalSection(&m_CriticalSection);
	CloseHandle(m_hThread);
	return S_OK;
}

TILE * CAStar_Manager::Check_DirectionTile(vector<TILE*>& _pTileList, const int& _iDirIndex)
{
	if (0 > _iDirIndex || (int)(m_tAStarDesc.iNumVerticesX * m_tAStarDesc.iNumVerticesZ) <= _iDirIndex)
		return nullptr;

	if (0 != _pTileList[_iDirIndex]->bType)
		return nullptr;

	return _pTileList[_iDirIndex];
}

void CAStar_Manager::Free()
{
	for_each(m_lsAStarList.begin(), m_lsAStarList.end(), [&](auto& iter) { Safe_Release(iter); });
	for_each(m_tAStarDesc.vecTileList.begin(), m_tAStarDesc.vecTileList.end(), [&](auto& iter) { Safe_Delete(iter); });
	m_tAStarDesc.vecAdjTileList.clear();
}
