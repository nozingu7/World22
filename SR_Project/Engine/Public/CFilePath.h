#pragma once
#include "CBase.h"

BEGIN(Engine)

class CFilePath final : public CBase
{
private:
	explicit CFilePath();
	virtual ~CFilePath() = default;

private:
	vector<FILEDESC> m_FilePaths;
	typedef vector<FILEDESC> PATHS;
public:
	static CFilePath* Create();
	virtual void Free() override;
};

END