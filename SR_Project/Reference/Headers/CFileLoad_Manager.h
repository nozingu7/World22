#pragma once
#include"CBase.h"

class CFileLoad_Manager final : public CBase
{
private:
	explicit CFileLoad_Manager();
	virtual ~CFileLoad_Manager() = default;
public:
	// Find Folder Name
	list<const _tchar*> FindFolderName(const _tchar* _pFindFolderName, const _tchar* _strPath);
	// Find Path
	list<const _tchar*> FindDataName(const _tchar* _pFindFolderName, const _tchar* _strPath);
public:
	virtual void Free() override;
};

