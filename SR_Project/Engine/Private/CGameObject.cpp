#include "..\Public\CGameObject.h"
#include "CGameInstance.h"
#include "CTransform.h"


CGameObject::CGameObject(const LPDIRECT3DDEVICE9& _pDevice) :
	m_pGraphic_Device(_pDevice)
{
	Safe_AddRef(m_pGraphic_Device);
}

CGameObject::CGameObject(const CGameObject & _pProtoType)
	: m_pGraphic_Device(_pProtoType.m_pGraphic_Device)
{
	Safe_AddRef(m_pGraphic_Device);
}

HRESULT CGameObject::NativeConstruct_ProtoType()
{
	return S_OK;
}

HRESULT CGameObject::NativeConstruct_Clone(void*& pArg)
{
	return S_OK;
}

void CGameObject::Tick(const _float& _fDeltaTime)
{
}

void CGameObject::Late_Tick(const _float& _fDeltaTime)
{
}

HRESULT CGameObject::Render()
{
	return S_OK;
}

HRESULT CGameObject::Add_Component(CComponent** _ppOut, const _tchar* _pTag, const _uint& _iLevelIndex, const _tchar* _pProtoTypeTag, void* _pArg)
{
	if (nullptr == _pTag)
		return E_FAIL;

	CComponent* pComponent = Find_Component(_pTag);
	if (nullptr != pComponent)
		return E_FAIL;

	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	pComponent = pGameInstance->Clone_Component(_iLevelIndex, _pProtoTypeTag, _pArg);
	if (nullptr == pComponent)
	{
		MSG_BOX("CGameObject::AddComponent Clone Assignment Error");
		return E_FAIL;
	}

	m_mComponets.emplace(_pTag, pComponent);

	*_ppOut = pComponent;
	Safe_Release(pGameInstance);
	return S_OK;
}

CComponent * CGameObject::Find_Component(const _tchar *& _pTag)
{
	auto& iter = find_if(m_mComponets.begin(), m_mComponets.end(), [&](auto& Pair)->bool
	{
		if (!lstrcmp(_pTag, Pair.first))
			return true;
		return false;
	});

	if (iter == m_mComponets.end())
		return nullptr;

	return iter->second;
}

void CGameObject::Free()
{
	for_each(m_mComponets.begin(), m_mComponets.end(), [&](auto& Pair) { Safe_Release(Pair.second); });
	Safe_Release(m_pGraphic_Device);
}
