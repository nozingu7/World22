#include "..\Public\CFile_Manager.h"
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi" )

// ���ϸ��� �ε��� ��ȣ ����
static int iFileCnt = 0;

IMPLEMENT_SINGLETON(CFile_Manager)

CFile_Manager::CFile_Manager()
{
}

HRESULT CFile_Manager::Load(const _tchar * pProjectName, const _tchar * pDirectoryName, const _tchar * pSeekTag, const _tchar * pFilePath)
{
	if (FAILED(Load_Resources(pProjectName, pDirectoryName, pSeekTag, pFilePath)))
		return E_FAIL;

	// Ű���� �ߺ����� �ʴ´ٸ� Map �����̳ʿ� path �ֱ�
	if (nullptr == Find_FileMap(pSeekTag))
		m_FileMap.emplace(pSeekTag, m_vecPath);

	// ���� ���� ���鼭 ���� �ٽ� �־���ϴ� path ����
	m_vecPath.clear();

	// �� �������� �ִ� ������ �� �����Դٸ� FileCnt�� 0���� �ʱ�ȭ. ( �ٸ� ���� �ҷ��� �� �ε��� �ѹ� �� ����ϴϱ� )
	iFileCnt = 0;

	return S_OK;
}

HRESULT CFile_Manager::Load_Data(const _tchar* pProjectName, const _tchar* pDirectoryName, const _tchar* pFilePath)
{
	WIN32_FIND_DATA findData = {};
	WIN32_FIND_DATA parentData = {};

	_tchar szDirectoryPath[MAX_PATH] = L"";
	// ���� ���丮�� ��θ� �޾ƿ�.
	GetCurrentDirectory(MAX_PATH, szDirectoryPath);

	// szProjectPath = L"C:\\Users\\Kang\\Desktop\\SR_TeamPortfolio\\SR_TeamPortfolio-main\\SR_TeamPortfolio-main\\SR_Project\\Client\\Default"
	_wstring szProjectPath = _wstring(szDirectoryPath);

	_uint iNum = (_uint)szProjectPath.find(pProjectName, lstrlenW(pProjectName));

	// szFilePath = L"C:\\Users\\Kang\\Desktop\\SR_TeamPortfolio\\SR_TeamPortfolio-main\\SR_TeamPortfolio-main\\"
	_wstring szFilePath = szProjectPath.substr(0, iNum);

	szFilePath.append(pProjectName);
	szFilePath.append(TEXT("\\"));
	szFilePath.append(pDirectoryName);
	szFilePath.append(TEXT("\\"));
	// ���� �������ٸ� ������ ��ο� �߰��ϱ� ( ��ͷ� ���� )
	szFilePath.append(pFilePath);

	// *.* ���̱� �������� ��θ� ����
	_wstring szFullPath;
	szFullPath.append(szFilePath);

	szFilePath.append(TEXT("*.*"));

	BOOL bResult = TRUE;

	HANDLE hFile = FindFirstFile(szFilePath.c_str(), &findData);

	if (hFile == INVALID_HANDLE_VALUE)
		return E_FAIL;

	// �θ��� �̸��� �޾ƿ��� ���ؼ� ���� ��θ� �޾ƿ�.
	_tchar* parentName = (_tchar*)szFilePath.c_str();

	// ���� ��ο��� �� �޺κ��� ���� �����Ǿ��ִ� ������ �̸��� ���.
	PathRemoveFileSpec(parentName);

	// FindFirstFile �Լ��� ���� �˻����� ������ �θ� �̸��� �޾ƿ�.
	HANDLE hParent = FindFirstFile(parentName, &parentData);
	if (hParent == INVALID_HANDLE_VALUE)
		return E_FAIL;

	// ������ ��� ����Լ��� ����, ������ �ƴ� ������ ��쿡�� while���� ���鼭 ��� ������ �˻��Ѵ�.
	while (bResult)
	{
		// ���� �������
		if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if (lstrcmp(findData.cFileName, TEXT(".")) && lstrcmp(findData.cFileName, TEXT("..")))
			{
				FILEDESC FileDesc;

				// ���� �̸�
				FileDesc.szFileName.append(findData.cFileName);
				// ���� ����
				string fileType;
				FileDesc.szFileType.append(TEXT("Directory"));
				// ���� ���
				_wstring filePath = wstring(szFilePath).substr(0, szFilePath.length() - 3);
				filePath.append(findData.cFileName);
				FileDesc.szFilePath.append(filePath);
				// ���� ����(�θ�) �̸�
				FileDesc.szParentName.append(parentData.cFileName);
				// ���� ����
				FileDesc.bIsFolder = true;
				// �ε��� ��ȣ ä���ֱ�
				FileDesc.iIndex = (_int)m_FilePaths.size();
				FileDesc.iFileCnt = -1;

				// vector�� �ֱ�
				m_FilePaths.push_back(FileDesc);

				_tchar* pFileName = findData.cFileName;
				_tchar pPath[MAX_PATH] = TEXT("");
				lstrcat(pPath, pFilePath);
				lstrcat(pPath, pFileName);
				lstrcat(pPath, TEXT("\\"));
				Load_Data(pProjectName, pDirectoryName, pPath);
			}
		}
		// ������ �ƴ϶�� ( �����̶�� )
		else
		{
			FILEDESC FileDesc;

			// ���� �̸�
			FileDesc.szFileName.append(findData.cFileName);
			// ���� ����
			string fileType;
			FileDesc.szFileType.append(findData.cFileName);
			fileType.assign(FileDesc.szFileType.begin(), FileDesc.szFileType.end());
			FileDesc.szFileType = FileDesc.szFileType.substr(fileType.find_last_of(".") + 1);
			// ���� ���
			FileDesc.szFilePath.append(szFullPath);
			FileDesc.szFilePath.append(findData.cFileName);
			// ���� ����(�θ�) �̸�
			FileDesc.szParentName.append(parentData.cFileName);
			// ���� ����
			FileDesc.bIsFolder = false;
			// �ε��� ��ȣ ä���ֱ�
			FileDesc.iIndex = (_int)m_FilePaths.size();
			FileDesc.iFileCnt = iFileCnt++;

			// ���� �����̳ʿ� �������
			m_FilePaths.push_back(FileDesc);
		}
		bResult = (FindNextFile(hFile, &findData));
	}

	FindClose(hFile);

	// �� �������� �ִ� ������ �� �����Դٸ� FileCnt�� 0���� �ʱ�ȭ. ( �ٸ� ���� �ҷ��� �� �ε��� �ѹ� �� ����ϴϱ� )
	iFileCnt = 0;

	return S_OK;
}


HRESULT CFile_Manager::Load_Resources(const _tchar * pProjectName, const _tchar * pDirectoryName, const _tchar * pSeekTag, const _tchar * pFilePath)
{
	WIN32_FIND_DATA findData = {};
	WIN32_FIND_DATA parentData = {};

	_tchar szDirectoryPath[MAX_PATH] = L"";
	// ���� ���丮�� ��θ� �޾ƿ�.
	GetCurrentDirectory(MAX_PATH, szDirectoryPath);

	// szProjectPath = L"C:\\Users\\Kang\\Desktop\\SR_TeamPortfolio\\SR_TeamPortfolio-main\\SR_TeamPortfolio-main\\SR_Project\\Client\\Default"
	_wstring szProjectPath = _wstring(szDirectoryPath);

	_uint iNum = (_uint)szProjectPath.find(pProjectName, lstrlenW(pProjectName));

	// szFilePath = L"C:\\Users\\Kang\\Desktop\\SR_TeamPortfolio\\SR_TeamPortfolio-main\\SR_TeamPortfolio-main\\"
	_wstring szFilePath = szProjectPath.substr(0, iNum);

	// ������Ʈ���� ��ο� ����
	szFilePath.append(pProjectName);
	szFilePath.append(TEXT("\\"));
	// ������Ʈ ������ Ž���� �������� ��ο� ����
	szFilePath.append(pDirectoryName);
	szFilePath.append(TEXT("\\"));
	// Ž���ϴ� ���� ������ ���ҽ��� ������������ �������� ��ο� ����
	szFilePath.append(pSeekTag);
	szFilePath.append(TEXT("\\"));
	// ���� �������ٸ� ������ ��ο� �߰��ϱ� ( ��ͷ� ���� )
	szFilePath.append(pFilePath);

	// *.* ���̱� �������� ��θ� ����
	_wstring szFullPath;
	szFullPath.append(szFilePath);

	szFilePath.append(TEXT("*.*"));

	BOOL bResult = TRUE;

	HANDLE hFile = FindFirstFile(szFilePath.c_str(), &findData);

	if (hFile == INVALID_HANDLE_VALUE)
		return E_FAIL;

	// �θ��� �̸��� �޾ƿ��� ���ؼ� ���� ��θ� �޾ƿ�.
	_tchar* parentName = (_tchar*)szFilePath.c_str();

	// ���� ��ο��� �� �޺κ��� ���� �����Ǿ��ִ� ������ �̸��� ���.
	PathRemoveFileSpec(parentName);

	// FindFirstFile �Լ��� ���� �˻����� ������ �θ� �̸��� �޾ƿ�.
	HANDLE hParent = FindFirstFile(parentName, &parentData);
	if (hParent == INVALID_HANDLE_VALUE)
		return E_FAIL;

	// ������ ��� ����Լ��� ����, ������ �ƴ� ������ ��쿡�� while���� ���鼭 ��� ������ �˻��Ѵ�.
	while (bResult)
	{
		// ���� �������
		if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if (lstrcmp(findData.cFileName, TEXT(".")) && lstrcmp(findData.cFileName, TEXT("..")))
			{
				FILEDESC FileDesc;

				// ���� �̸�
				FileDesc.szFileName.append(findData.cFileName);
				// ���� ����
				string fileType;
				FileDesc.szFileType.append(TEXT("Directory"));
				// ���� ���
				_wstring filePath = wstring(szFilePath).substr(0, szFilePath.length() - 3);
				filePath.append(findData.cFileName);
				FileDesc.szFilePath.append(filePath);
				// ���� ����(�θ�) �̸�
				FileDesc.szParentName.append(parentData.cFileName);
				// ���� ����
				FileDesc.bIsFolder = true;
				// �ε��� ��ȣ ä���ֱ�
				FileDesc.iIndex = (_int)m_FilePaths.size();
				FileDesc.iFileCnt = -1;

				// map�� �ֱ�
				m_vecPath.push_back(FileDesc);

				_tchar* pFileName = findData.cFileName;
				_tchar pPath[MAX_PATH] = TEXT("");
				lstrcat(pPath, pFilePath);
				lstrcat(pPath, pFileName);
				lstrcat(pPath, TEXT("\\"));
				Load_Resources(pProjectName, pDirectoryName, pSeekTag, pPath);
			}
		}
		// ������ �ƴ϶�� ( �����̶�� )
		else
		{
			FILEDESC FileDesc;

			// ���� �̸�
			FileDesc.szFileName.append(findData.cFileName);
			// ���� ����
			string fileType;
			FileDesc.szFileType.append(findData.cFileName);
			fileType.assign(FileDesc.szFileType.begin(), FileDesc.szFileType.end());
			FileDesc.szFileType = FileDesc.szFileType.substr(fileType.find_last_of(".") + 1);
			// ���� ���
			FileDesc.szFilePath.append(szFullPath);
			FileDesc.szFilePath.append(findData.cFileName);
			// ���� ����(�θ�) �̸�
			FileDesc.szParentName.append(parentData.cFileName);
			// ���� ����
			FileDesc.bIsFolder = false;
			// �ε��� ��ȣ ä���ֱ�
			FileDesc.iIndex = (_int)m_FilePaths.size();
			FileDesc.iFileCnt = iFileCnt++;

			// ���� �����̳ʿ� �������
			m_vecPath.push_back(FileDesc);
		}
		bResult = (FindNextFile(hFile, &findData));
	}

	FindClose(hFile);

	return S_OK;
}

vector<FILEDESC> * CFile_Manager::Find_FileMap(const _tchar * pSeekPath)
{
	auto iter = find_if(m_FileMap.begin(), m_FileMap.end(), CTag_Finder(pSeekPath));

	if (iter == m_FileMap.end())
		return nullptr;

	return &(iter->second);
}

void CFile_Manager::Free()
{
	for (auto& Pair : m_FileMap)
	{
		Pair.second.clear();
	}

	m_FilePaths.clear();
	m_FileMap.clear();
}