#pragma once
#include "CBase.h"
#include "CTimer.h"

BEGIN(Engine)

class CTimer_Manager final : public CBase
{
	DECLARE_SINGLETON(CTimer_Manager)
private:
	explicit CTimer_Manager();
	virtual ~CTimer_Manager() = default;
public:
	_float Get_TimeDelta(const _tchar*& _pTag);
	HRESULT Add_Timer(const _tchar*& _pTag);
	void Tick(const _tchar*& _pTag);
private:
	CTimer* Compare_TimerTag(const _tchar*& _pTag);
private:
	map<const _tchar*, CTimer*> m_Timers;
	typedef map<const _tchar*, CTimer*> TIMER;
public:
	static CTimer_Manager* Create();
	virtual void Free() override;
};

END