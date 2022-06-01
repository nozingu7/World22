#pragma once
#include "Tool_Defines.h"
#include"Engine_Defines.h"
#include"CBase.h"

class CEngineApp final : public CBase
{
public:
	explicit CEngineApp();
	virtual ~CEngineApp() = default;
public:
	HRESULT NativeConstruct();


private:
	void Tick(const _float& _fDeltaSeconds);
	HRESULT Render();

private:


};

