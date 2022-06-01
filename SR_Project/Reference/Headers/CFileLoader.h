#pragma once
#include"CBase.h"

class CFileLoader final : public CBase
{
public:
	typedef struct tagFildFolderDesc
	{
		_wstring strName;
		_wstring strPath;
	}FILEFOLDERDESC;
	typedef struct tagFileDataDesc
	{
		_wstring				strName;
		list<CFileLoader::FILEFOLDERDESC>	strPathList;
	}FILEDATADESC;
private:
	explicit CFileLoader();
	virtual ~CFileLoader() = default;
public:
	// Find Path
	static list<FILEDATADESC>	FindDataName(const _tchar* _pFindFolderName, const _tchar* _strPath);
private:
	// Find Folder Name
	static list<FILEFOLDERDESC> FindFolderName(const _tchar* _pFindFolderName, const _tchar* _strPath);
public:
	virtual void Free() override;
};

