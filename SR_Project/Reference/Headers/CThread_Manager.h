#pragma once
#include "CBase.h"

BEGIN(Engine)
class CMyThread;

class CThread_Manager final : public CBase
{
	DECLARE_SINGLETON(CThread_Manager)
private:
	explicit CThread_Manager();
	virtual ~CThread_Manager() = default;
public:
	// Add Thread 
	// ������ ���̵� ������ ������ ������
	HRESULT Add_Thread(_uint& _iThreadID, function<void(void*, mutex*, _bool*)> _pData, void* _pArg);
	// Delete Thread
	HRESULT Delete_Thread(const _uint& _iThreadID);
	// End All Thread
	HRESULT End_Threads();
protected:
	// �ش��ϴ� �����带 ã��
	list<CMyThread*>::iterator Find_Thread(const _uint& _iThreadID);
protected:
	typedef list<CMyThread*> THREADS;
	list<CMyThread*>  m_Threads;
protected:
	// mutex
	mutex	m_Mutex;
	// Index�� �Ҵ����ִ� ����
	_uint		m_iGiveIDIndex;
public:
	// Free
	virtual void Free() override;

};

END