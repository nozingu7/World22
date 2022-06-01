#include "..\Public\CComponent_Manager.h"
#include"CComponent.h"

IMPLEMENT_SINGLETON(CComponent_Manager)

CComponent_Manager::CComponent_Manager() : 
	m_mProtoTypes(nullptr), 
	m_iLevelCount(0)
{
}

HRESULT CComponent_Manager::Reserve_Componets(const _uint & _iLevelCount)
{
	if (_iLevelCount <= 0)
		return E_FAIL;

	if (nullptr != m_mProtoTypes)
		return E_FAIL;

	m_mProtoTypes = new PROTOTYPES[_iLevelCount];
	m_iLevelCount = _iLevelCount;
	return S_OK;
}

HRESULT CComponent_Manager::Add_ProtoType(const _uint& _iLevelIndex, const _tchar * _pProtoTypeTag, CComponent * _pComponent)
{
	if (0 > _iLevelIndex || m_iLevelCount <= _iLevelIndex || nullptr == _pComponent)
		return E_FAIL;

	if (nullptr != Find_Component(_iLevelIndex, _pProtoTypeTag))
		return E_FAIL;
	// ProtoTypes 
	m_mProtoTypes[_iLevelIndex].emplace(_pProtoTypeTag, _pComponent);
	return S_OK;
}

CComponent* CComponent_Manager::Clone_Component(const _uint & _iLevelIndex, const _tchar *& _pProtoTypeTag, void *& _pArg)
{
	if (0 > _iLevelIndex  || m_iLevelCount <= _iLevelIndex)
		return nullptr;

	CComponent* pComponent = Find_Component(_iLevelIndex, _pProtoTypeTag);
	if (nullptr == pComponent)
		return nullptr;

	pComponent = pComponent->Clone(_pArg);
	return pComponent;
}

HRESULT CComponent_Manager::Release_Components(const _uint & _iLevelIndex)
{
	if (0 >= _iLevelIndex || _iLevelIndex >= m_iLevelCount)
		return E_FAIL;

	for_each(m_mProtoTypes[_iLevelIndex].begin(), m_mProtoTypes[_iLevelIndex].end(), [&](auto& pair) { Safe_Release(pair.second); });
	m_mProtoTypes[_iLevelIndex].clear();
	return S_OK;
}

CComponent * CComponent_Manager::Find_Component(const _uint & _iLevelIndex, const _tchar *& _pFindTag)
{
	auto& iter = find_if(m_mProtoTypes[_iLevelIndex].begin(), m_mProtoTypes[_iLevelIndex].end(), [&](auto& Pair)->bool
	{
		if (!lstrcmp(Pair.first, _pFindTag))
			return true;

		return false;
	});

	if (m_mProtoTypes[_iLevelIndex].end() == iter)
		return nullptr;

	return iter->second;
}

void CComponent_Manager::Free()
{
	for (_uint i = 0; i < m_iLevelCount; ++i)
	{
		for_each(m_mProtoTypes[i].begin(), m_mProtoTypes[i].end(), [&](auto& Pair){ Safe_Release(Pair.second); });
		m_mProtoTypes[i].clear();
	}
	Safe_Delete_Array(m_mProtoTypes);
	__super::Free();
}