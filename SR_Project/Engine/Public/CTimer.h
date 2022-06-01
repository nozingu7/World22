#pragma once
#include "CBase.h"

BEGIN(Engine)

class CTimer final : public CBase
{
private:
	explicit CTimer();
	virtual ~CTimer() = default;
public:
	const float& Get_DeltaTime() const { return m_fDeltaTime; }
public:
	HRESULT NativeConstruct();
	void Tick();

private:
	LARGE_INTEGER m_CurTime;
	LARGE_INTEGER m_OldTime;
	LARGE_INTEGER m_CtlTime;
	LARGE_INTEGER m_CpuClock;

	float m_fDeltaTime;
public:
	static CTimer* Create();
	virtual void Free() override;
};

END
