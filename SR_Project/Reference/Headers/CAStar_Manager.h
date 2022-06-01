#pragma once
#include "CBase.h"
#include "CAStar_AI.h"

BEGIN(Engine)

class CAStar_AI;
class CMyThread;

class CAStar_Manager final : public CBase
{
	DECLARE_SINGLETON(CAStar_Manager)
private:
	explicit CAStar_Manager();
	virtual ~CAStar_Manager() = default;
public:
	// Ready AStar
	HRESULT Ready_AStar(byte* _pTileInfo, const _float4x4& _matTerrianWorldInv, const _VECTOR3& _v3TileSize,
		const _uint& _iTileWidth, const _uint& _iTileHeight);
	// Register
	HRESULT Register_AStar(CAStar_AI*& _pAStar);
	// Get AStar Desc
	CAStar_AI::ASTARDESC* Get_AstarDesc() { return m_pAStarDesc; }
	// Running
	void Running();
	// Release_Data
	void Release_Data();
private:
	// Run AStar
	static _uint _stdcall Run_AStar(void* _pArg);
	// End Running
	HRESULT End_Running();
private: 
	// Check DirectionTile
	TILE* Check_DirectionTile(vector<TILE*>& _pTileList, const int& _iDirIndex);
private: /* Define Tile List */
	CAStar_AI::ASTARDESC	m_tAStarDesc;
private:
	list<CAStar_AI*>					m_lsAStarList;
	_uint										m_iSaveThreadID;
private:
	HANDLE									m_hThread;
	CRITICAL_SECTION				m_CriticalSection;
public:
	// Free
	virtual void Free() override;
};

END