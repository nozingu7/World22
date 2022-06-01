#pragma once

#define BEGIN(NAMESPACE) namespace NAMESPACE{
#define END }

#ifdef ENGINE_EXPORTS
#define ENGINE_DLL _declspec(dllexport)
#else
#define ENGINE_DLL _declspec(dllimport)
#endif

#define MSG_BOX(message) \
::MessageBox(0, TEXT(message), TEXT("ERROR"), MB_OK)

#define ERR_MSG_MT(message, title) \
::MessageBox(0, TEXT(message), title, MB_OK)

#define ERR_CHECK_INIT(CLASS, MESSAGE) \
if(FAILED(CLASS->NativeConstruct())) \
{	\
	ERR_MSG_SRELEASE(CLASS, MESSAGE)\
}

#define ERR_MSG_SRELEASE(CLASS, MESSAGE) \
MSG_BOX(MESSAGE); \
Safe_Release(CLASS); 

#define SAFE_RELEASE(CLASS_NAME)		\
if(nullptr != CLASS_NAME) {				\
 if(0 == CLASS_NAME->Release()){		\
	CLASS_NAME = nullptr;		}		\
 else									\
 {										\
	CLASS_NAME = CLASS_NAME->Destroy();	\
 }										\
}


#define NO_COPY(ClassName)								\
ClassName(const ClassName&) = delete;					\
ClassName& operator=(const ClassName&) = delete;

#define DECLARE_SINGLETON(ClassName)					\
		NO_COPY(ClassName)								\
public :												\
	static ClassName* Get_Instance();					\
	static unsigned long Destroy_Instance();			\
private:												\
	static ClassName* m_pInstance;

#define IMPLEMENT_SINGLETON(ClassName)					\
ClassName* ClassName::m_pInstance = nullptr;			\
ClassName* ClassName::Get_Instance()					\
{														\
	if (nullptr == m_pInstance)							\
		m_pInstance = new ClassName;					\
	return m_pInstance;									\
}														\
unsigned long ClassName::Destroy_Instance()				\
{														\
	unsigned long dwRefCnt = 0;							\
	if(nullptr != m_pInstance)							\
	{													\
		dwRefCnt  = m_pInstance->Release();				\
		if(0 == dwRefCnt)								\
			m_pInstance = nullptr;						\
	}													\
	return dwRefCnt;									\
}


#define COM_INSTANCE_IS_LEAK_ERROR(x, message) \
if(0 > Safe_Release(x)) \
 MSG_BOX(message);
