#include "..\Public\CObject_Manager.h"
#include"CGameObject.h"
#include "CObject_Layers.h"

IMPLEMENT_SINGLETON(CObject_Manager)

CObject_Manager::CObject_Manager() :
	m_pLayers(nullptr),
	m_iLevelCount(0)
{
}

HRESULT CObject_Manager::Reserve_Objects(const _uint & _iLevelCount)
{
	if (nullptr != m_pLayers)
		return E_FAIL;
	if (0 >= _iLevelCount)
#ifndef _AFX
		return S_OK;
#elif
		return E_FAIL;
#endif

	m_pLayers = new LAYERS[_iLevelCount];
	this->m_iLevelCount = _iLevelCount;

	return S_OK;
}
HRESULT CObject_Manager::Add_ProtoType(const _tchar*& _pProtoTypeTag, CGameObject *& _pGameObject)
{
	if (nullptr != Find_ProtoType(_pProtoTypeTag))
		return E_FAIL;

	m_mProtoTypes.emplace(_pProtoTypeTag, _pGameObject);
	return S_OK;
}
HRESULT CObject_Manager::Clone_GameObject(const _uint & _iLevelIndex, const _tchar*& _pLayerTypeTag, const _tchar*& _pProtoTypeTag, void*& _pArg)
{
	if (nullptr == m_pLayers || m_iLevelCount <= _iLevelIndex)
		return E_FAIL;

	CGameObject* pGameObject = Find_ProtoType(_pProtoTypeTag);
	if (nullptr == pGameObject)
		return E_FAIL;

	CGameObject* pCloneObject = pGameObject->Clone(_pArg);
	if (nullptr == pCloneObject)
		return E_FAIL;

	CObject_Layers* pLayers = Find_Layer(_iLevelIndex, _pLayerTypeTag);
	if (nullptr == pLayers)
	{
		pLayers = CObject_Layers::Create();
		if (nullptr == pLayers)
			return E_FAIL;

		pLayers->Add_GameObject(pCloneObject);
		m_pLayers[_iLevelIndex].emplace(_pLayerTypeTag, pLayers);
	}
	else
		pLayers->Add_GameObject(pCloneObject);

	return S_OK;
}

CGameObject * CObject_Manager::Find_GameObject(const _uint & _iLevelIndex, const _tchar *& _pLayerTypeTag, const _uint & _iIndex)
{
	if (0 > _iIndex)
		return nullptr;

	CObject_Layers* pLayers = Find_Layer(_iLevelIndex, _pLayerTypeTag);
	if (nullptr == pLayers)
		return nullptr;

	CGameObject* pGameObject = pLayers->Find_GameObject(_iIndex);
	return pGameObject;
}

HRESULT CObject_Manager::Release_Layer(const _uint & _iLevelIndex)
{
	if (nullptr == m_pLayers)
		return E_FAIL;

	if (0 >= _iLevelIndex || _iLevelIndex >= m_iLevelCount)
		return E_FAIL;

	// Level Reset
	for_each(m_pLayers[_iLevelIndex].begin(), m_pLayers[_iLevelIndex].end(), [&](auto& pair) { 
		Safe_Release(pair.second);
	});
	m_pLayers[_iLevelIndex].clear();
	return S_OK;
}
void CObject_Manager::Tick(const _float & _fDeltaSeconds)
{
	for (_uint i = 0; i < m_iLevelCount; ++i)
	{
		for (auto& iter : m_pLayers[i])
			iter.second->Tick(_fDeltaSeconds);
	}
}
void CObject_Manager::Late_Tick(const _float & _fDeltaSeconds)
{
	for (_uint i = 0; i < m_iLevelCount; ++i)
	{
		for (auto& iter : m_pLayers[i])
			iter.second->Late_Tick(_fDeltaSeconds);
	}
}
CObject_Layers * CObject_Manager::Find_Layer(const _uint & _iLevel,const _tchar*& _pLayerTag)
{
	if (nullptr == m_pLayers || m_iLevelCount <= _iLevel)
		return nullptr;

	LAYERS pLayer = m_pLayers[_iLevel];

	auto& iter = find_if(m_pLayers[_iLevel].begin(), m_pLayers[_iLevel].end(), [&](auto& Pair)->bool
	{
		if (!lstrcmp(_pLayerTag, Pair.first))
			return true;

		return false;
	});

	if (m_pLayers[_iLevel].end() != iter)
		return iter->second;

	return nullptr;
}
CGameObject * CObject_Manager::Find_ProtoType(const _tchar*& _pProtoTypeTag)
{
	if (m_mProtoTypes.size() <= 0)
		return nullptr;

	auto& iter = find_if(m_mProtoTypes.begin(), m_mProtoTypes.end(), [&](auto& Pair)->bool
	{
		if (!lstrcmp(_pProtoTypeTag, Pair.first))
			return true;

		return false;
	});

	if (m_mProtoTypes.end() != iter)
		return iter->second;

	return nullptr;
}

void CObject_Manager::Free()
{
	if (nullptr != m_pLayers)
	{
		for (_uint i = 0; i < m_iLevelCount; ++i)
			for_each(m_pLayers[i].begin(), m_pLayers[i].end(), [&](auto& Pair) {
			Safe_Release(Pair.second);
		});

		Safe_Delete_Array(m_pLayers);
	}

	for (auto& iter : m_mProtoTypes)
		Safe_Release(iter.second);

	m_mProtoTypes.clear();
}
