#pragma once

#include"CBase.h"

BEGIN(Engine)

class CLevel;

class CLevel_Manager final : public CBase
{
	DECLARE_SINGLETON(CLevel_Manager)
public:
	explicit CLevel_Manager();
	virtual ~CLevel_Manager() = default;
public:
	const _uint& Get_CurrentLevelIndex() const { return m_iCurrentLevelIndex; }
public:
	HRESULT Open_Level(const _uint& _iLevel, CLevel*& _pLevel);
public:
	HRESULT Tick(const _float& _fDeltaSeconds);
	HRESULT LateTick(const _float& _fDeltaSeconds);
private:
	CLevel* m_pCurrentLevel;
	_uint	m_iCurrentLevelIndex;
public:
	virtual void Free() override;
};

END