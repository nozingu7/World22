#pragma once
#include "CBase.h"

BEGIN(Engine)

class CFile_Manager final : public CBase
{
	DECLARE_SINGLETON(CFile_Manager)

public:

private:
	explicit CFile_Manager();
	virtual ~CFile_Manager() = default;

public:
	// ��θ� �������� �Լ�
	vector<tagFileInfo>* Get_FilePaths() {
		return &m_FilePaths;
	}

public:
	// ������ �ε� �Լ�
	HRESULT Load(const _tchar* pProjectName, const _tchar* pDirectoryName, const _tchar* pSeekTag, const _tchar* pFilePath = TEXT(""));

	// ��� �Լ��� ��������
	HRESULT Load_Data(const _tchar* pProjectName, const _tchar* pDirectoryName, const _tchar* pFilePath = TEXT(""));

	// vector* ������ �ٲٱ� ���� �Լ���, ���� Load_Data�� ���ڿ� ���� ������ ���� �ٸ���.
	// 1���� - ���� ������Ʈ �� / 2���� - ������Ʈ ������ Ž���� ���� / 3���� - 2���� ������ ���ҽ��� �������� ���� ���� �� Map�� ����� Tag��
	HRESULT Load_Resources(const _tchar* pProjectName, const _tchar* pDirectoryName, const _tchar* pSeekTag,  const _tchar* pFilePath = TEXT(""));

private:
	vector<tagFileInfo> m_FilePaths;
	typedef vector<tagFileInfo> FILEPATHS;

	// �������� map�� �����ϱ����� ����
	map<const _tchar* , vector<FILEDESC>> m_FileMap;
	typedef map<const _tchar*, vector<FILEDESC>> FILEMAP;

	vector<FILEDESC> m_vecPath; // �ʿ� ���� Path

public:
	// ���� �� ã�� �Լ�
	vector<FILEDESC>* Find_FileMap(const _tchar* pSeekPath);


public:
	virtual void Free() override;
};

END