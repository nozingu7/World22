#pragma once
#include "Tool_Defines.h"
#include "CBase.h"

class CData_Loader final : public CBase
{
private:
	explicit CData_Loader();
	virtual ~CData_Loader() = default;



public:
	virtual void Free() override;
};

