#include "..\Public\CRenderer_Manager.h"
#include "CGameObject.h"
#include "CObject_Layers.h"
#include"CSortObject.h"
#include "CCamera.h"

IMPLEMENT_SINGLETON(CRenderer_Manager)

CRenderer_Manager::CRenderer_Manager() : 
	m_pRenderObj(nullptr),
	m_iRenderMaxCount(0)
{
}

HRESULT CRenderer_Manager::Ready_RenderManager(const _uint & _iRenderMaxCount)
{
	if (0 > _iRenderMaxCount)
		return E_FAIL;

	this->m_iRenderMaxCount = _iRenderMaxCount;

	m_pRenderObj = new RENDERS*[_iRenderMaxCount];
	for (_uint i = 0; i < _iRenderMaxCount; ++i)
		m_pRenderObj[i] = new RENDERS[RENDER_END];

	return S_OK;
}

HRESULT CRenderer_Manager::Add_RenderObj(const ERenderType& _eRenderType, CGameObject *& _pObject, const _uint& _iRenderID)
{
	if (nullptr == m_pRenderObj)
		return E_FAIL;

	if (nullptr == _pObject)
		return E_FAIL;

	if (_eRenderType < 0 || _eRenderType >= RENDER_END)
		return E_FAIL;

	m_pRenderObj[_iRenderID][_eRenderType].emplace_back(_pObject);
	Safe_AddRef(_pObject);
	return S_OK;
}

void CRenderer_Manager::Render(const _uint& _iRenderID)
{
	for (int i = 0; i < RENDER_END; ++i)
	{
		if (RENDER_ALPHABLEND == i)
		{
			m_pRenderObj[_iRenderID][i].sort([&](CGameObject*& _pG1, CGameObject*& _pG2)
			{
				return static_cast<CSortObject*>(_pG1)->Get_CamToDistance() > static_cast<CSortObject*>(_pG2)->Get_CamToDistance();
			});
		}
		for_each(m_pRenderObj[_iRenderID][i].begin(), m_pRenderObj[_iRenderID][i].end(), [&](auto& Pair) { Pair->Render(); Safe_Release(Pair); });
		m_pRenderObj[_iRenderID][i].clear();
	}
}

void CRenderer_Manager::Free()
{
	if (nullptr != m_pRenderObj) {
		for (_uint k = 0; k < m_iRenderMaxCount; ++k)
		{
			for (int i = 0; i < RENDER_END; ++i)
			{
				for_each(m_pRenderObj[k][i].begin(), m_pRenderObj[k][i].end(), [&](auto& Pair) { Safe_Release(Pair); });
				m_pRenderObj[k][i].clear();
			}
			Safe_Delete_Array(m_pRenderObj[k]);
		}
		Safe_Delete_Array(m_pRenderObj);
	}
}
