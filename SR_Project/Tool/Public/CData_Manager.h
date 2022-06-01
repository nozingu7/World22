#pragma once
#include"Tool_Defines.h"
#include "CBase.h"

class CData_Manager final : public CBase
{
	DECLARE_SINGLETON(CData_Manager)
private:
	explicit CData_Manager();
	virtual ~CData_Manager() = default;

	
public: /* Save */

public:  /* Load */

public:
	/* Data_Manager  */
	// Player, Item, Monster, 

private:

public:
	virtual void Free() override;

};
