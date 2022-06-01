#include "..\Public\CObject_Layers.h"
#include "CGameObject.h"

CObject_Layers::CObject_Layers()
{
}

HRESULT CObject_Layers::Add_GameObject(CGameObject *& _pObject)
{
	if (nullptr == _pObject)
		return E_FAIL;

	m_lsGameObjects.emplace_back(_pObject);

	return S_OK;
}

CGameObject * CObject_Layers::Find_GameObject(const _uint & _iIndex)
{
	if (_iIndex >= m_lsGameObjects.size())
		return nullptr;

	CGameObject* pGameObject = nullptr;
	_uint iIndex = 0;
	for (auto& iter : m_lsGameObjects)
	{
		if (iIndex++ == _iIndex)
		{
			pGameObject = iter;
			break;
		}
	}
	return pGameObject;
}

HRESULT CObject_Layers::NativeConstruct()
{
	return S_OK;
}

void CObject_Layers::Tick(const _float & _fDeltaSeconds)
{
	for (auto& iter : m_lsGameObjects)
		iter->Tick(_fDeltaSeconds);
}

void CObject_Layers::Late_Tick(const _float & _fDeltaSeconds)
{
	for (auto& iter : m_lsGameObjects)
		iter->Late_Tick(_fDeltaSeconds);
}

CObject_Layers * CObject_Layers::Create()
{
	CObject_Layers* pInstance = new CObject_Layers;
	if (FAILED(pInstance->NativeConstruct()))
	{
		MSG_BOX("CObject_Layers::Create Error");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CObject_Layers::Free()
{
	// list ªË¡¶
	for_each(m_lsGameObjects.begin(), m_lsGameObjects.end(), [&](auto& iter)
	{
		Safe_Release(iter);}
	);
	m_lsGameObjects.clear();
}
