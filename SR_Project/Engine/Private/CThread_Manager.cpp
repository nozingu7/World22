#include "..\Public\CThread_Manager.h"
#include "CMyThread.h"

IMPLEMENT_SINGLETON(CThread_Manager)

CThread_Manager::CThread_Manager() : m_iGiveIDIndex(0)
{

}
// �����带 �����ϰ�  JOIN �ϴ� �Լ�
HRESULT CThread_Manager::Add_Thread(_uint & _iThreadID, function<void(void*, mutex*, _bool*)> _pData, void * _pArg)
{
	CMyThread* pMyThread = CMyThread::Create(m_iGiveIDIndex, _pData, _pArg, &m_Mutex);
	_iThreadID = m_iGiveIDIndex++;
	m_Threads.emplace_back(pMyThread);
	pMyThread->Join();
	return S_OK;
}
// ���� ���� ���� �����带 ����
HRESULT CThread_Manager::Delete_Thread(const _uint & _iThreadID)
{
	// ������ ���̵� ���� �����尡 ������ �ִ� �ߺ��� ũ�� ����
	if (m_Threads.size() < _iThreadID)
		return E_FAIL;
	// ���� �����带 ��ã�Ҵٸ� ����
	list<CMyThread*>::iterator iter = Find_Thread(_iThreadID);
	if (m_Threads.end() == iter)
		return E_FAIL;
	// ���� ���� ������ ����
	Safe_Release((*iter));
	m_Threads.erase(iter);
	// ������ ����
	m_Threads.sort([&](CMyThread* p1, CMyThread* p2)->bool{
		return p1->Get_ThreadID() < p2->Get_ThreadID();
	});

	return S_OK;
}

HRESULT CThread_Manager::End_Threads()
{
	// ������ ��� ���� 
	for_each(m_Threads.begin(), m_Threads.end(), [&](auto& iter) { Safe_Release(iter); });
	return S_OK;
}

list<CMyThread*>::iterator CThread_Manager::Find_Thread(const _uint & _iThreadID)
{
	if (m_Threads.size() < _iThreadID)
		return m_Threads.end() ;

	auto& iter = find_if(m_Threads.begin(), m_Threads.end(), [&](auto& iter)->bool
	{
		if (iter->Get_ThreadID() == _iThreadID)
			return true;

		return false;
	});

	if (m_Threads.end() == iter)
		return m_Threads.end();

	return iter;
}

void CThread_Manager::Free()
{
	End_Threads();
}

