#include "..\Public\CMyThread.h"



CMyThread::CMyThread(const _uint & _iThreadID) :
	m_iThreadID(_iThreadID), m_bRun(true)
{
}

HRESULT CMyThread::NativeConstruct(function<void(void*, mutex*, _bool*)> _pData, void*& _pArg, mutex* _mutex)
{
	m_Thread = thread(_pData, _pArg, _mutex, &m_bRun);
	return S_OK;
}

CMyThread * CMyThread::Create(const _uint & _iThread, function<void(void*, mutex*, _bool*)> _pData, void *& _pArg, mutex * _mutex)
{
	CMyThread* pInstance = new CMyThread(_iThread);
	if (FAILED(pInstance->NativeConstruct(_pData, _pArg, _mutex)))
	{
		MSG_BOX("CMyThread::Create Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CMyThread::Free()
{
	m_Thread.detach();
	m_bRun = false;
}

