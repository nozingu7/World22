#pragma once
#include "Tool_Defines.h"
#include "CBase.h"

class CData_Saver final : public CBase
{
private:
	explicit CData_Saver();
	virtual ~CData_Saver() = default;

public:
	virtual HRESULT File_Saver();


public:
	virtual void Free() override;
};

