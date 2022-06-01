#pragma once

#include "Engine_Defines.h"

BEGIN(Engine)

class ENGINE_DLL CBase abstract
{
protected:
	explicit CBase();
	virtual ~CBase() = default;
public:
	unsigned long AddRef();
	unsigned long Release();
private:
	unsigned long m_dwRefCount = 0;

public:
	virtual void Free();
};

END