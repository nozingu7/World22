#include "..\Public\CBase.h"

CBase::CBase() : m_dwRefCount(0)
{
}

unsigned long CBase::AddRef()
{
	return ++m_dwRefCount;
}

unsigned long CBase::Release()
{
	if (0 >= m_dwRefCount)
	{
		Free();
		delete this;
		return 0;
	}
	return m_dwRefCount--;
}

void CBase::Free()
{

}