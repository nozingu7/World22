#pragma once
#include "CBase.h"

BEGIN(Engine)

class ENGINE_DLL CMyThread final : public CBase
{
private:
	explicit CMyThread(const _uint& _iThreadID);
	virtual ~CMyThread() = default;
public:
	void Set_Run(const _bool& _bIsRun) { this->m_bRun = _bIsRun; }

	void Set_ThreadID(const _uint& _iID) { this->m_iThreadID = _iID; }
	const _uint& Get_ThreadID() const { return m_iThreadID; }
public:
	// NativeConstruct
	// function<void(void*, mutex*, _bool*)> = void Method(void* _pArg, mutex* _Mutex, _bool* _bControl)�� ���� �Լ��� ��� ��
	HRESULT NativeConstruct(function<void(void*, mutex*, _bool*)> _pData, void*& _pArg, mutex* _mutex );
	// Join
	void Join(){ m_Thread.join(); }
private:
	// ������ 
	thread		m_Thread;
	// ������ ID
	_uint		m_iThreadID;
	// �����带 ������ �� �ִ� bool ����
	_bool		m_bRun;
public:
	static CMyThread* Create(const _uint& _iThread, function<void(void*, mutex*, _bool*)> _pData, void*& _pArg, mutex* _mutex);
	virtual void Free() override;
};

END