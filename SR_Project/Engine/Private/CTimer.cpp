#include "..\Public\CTimer.h"



CTimer::CTimer() : m_fDeltaTime(0.f)
{
	ZeroMemory(&m_CpuClock, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_CtlTime, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_CurTime, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_OldTime, sizeof(LARGE_INTEGER));
}

HRESULT CTimer::NativeConstruct()
{
	QueryPerformanceCounter(&m_CurTime);
	QueryPerformanceCounter(&m_OldTime);
	QueryPerformanceCounter(&m_CtlTime);
	QueryPerformanceFrequency(&m_CpuClock);

	return S_OK;
}

void CTimer::Tick()
{
	QueryPerformanceCounter(&m_CurTime);
	if (m_CurTime.QuadPart - m_CtlTime.QuadPart > m_CpuClock.QuadPart)
	{
		QueryPerformanceFrequency(&m_CpuClock);
		m_CtlTime = m_CurTime;
	}
	m_fDeltaTime = static_cast<float>(m_CurTime.QuadPart - m_OldTime.QuadPart) / m_CpuClock.QuadPart;
	m_OldTime = m_CurTime;
}

CTimer * CTimer::Create()
{
	CTimer* pTimer = new CTimer();
	ERR_CHECK_INIT(pTimer, "CTimer::Create Error")
	return pTimer;
}

void CTimer::Free()
{
	
}
