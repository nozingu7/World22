#include "..\Public\CTimer_Manager.h"
#include"CTimer.h"

IMPLEMENT_SINGLETON(CTimer_Manager)

CTimer_Manager::CTimer_Manager()
{
}

_float CTimer_Manager::Get_TimeDelta(const _tchar*& _pTag)
{
	CTimer* pTimer = Compare_TimerTag(_pTag);
	if (nullptr == pTimer)
		return 0.f;

	return pTimer->Get_DeltaTime();
}

HRESULT CTimer_Manager::Add_Timer(const _tchar*& _pTag)
{
	if (nullptr != Compare_TimerTag(_pTag))
		return E_FAIL;

	m_Timers.emplace(_pTag, CTimer::Create());
	return S_OK;
}

void CTimer_Manager::Tick(const _tchar*& _pTag)
{
	CTimer* pTimer = Compare_TimerTag(_pTag);
	if (nullptr == pTimer)
		return;

	pTimer->Tick();
}

CTimer * CTimer_Manager::Compare_TimerTag(const _tchar*& _pTag)
{
	auto& iter = find_if(m_Timers.begin(), m_Timers.end(), [&](auto& pair)->bool
	{
		if (!lstrcmp(_pTag, pair.first))
			return true;

		return false;
	});

	if (m_Timers.end() == iter)
		return nullptr;

	return iter->second;
}

CTimer_Manager* CTimer_Manager::Create()
{
	CTimer_Manager* pTimerManager = new CTimer_Manager;
	return pTimerManager;
}

void CTimer_Manager::Free()
{
	for_each(m_Timers.begin(), m_Timers.end(), [&](auto& iter) 
	{Safe_Release(iter.second);});
}
