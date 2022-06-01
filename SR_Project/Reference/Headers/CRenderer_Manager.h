#pragma once
#include"CBase.h"

BEGIN(Engine)

class CCamera;

class CRenderer_Manager final : public CBase
{
	DECLARE_SINGLETON(CRenderer_Manager)
private:
	explicit CRenderer_Manager();
	virtual ~CRenderer_Manager() = default;
public:
	typedef enum ERenderType
	{
		RENDER_PRIORITY, RENDER_NONALPHABLEND, RENDER_ALPHABLEND, RENDER_DEBUG, RENDER_UI, RENDER_END
	}RENDERTYPE;
public:
	// Ready RenderManager
	HRESULT Ready_RenderManager(const _uint& _iRenderMaxCount = 1);
	// Add Object
	HRESULT Add_RenderObj(const ERenderType& _eRenderType, class CGameObject*& _pObject, const _uint& _iRenderID = 0);
	// Render 
	void Render(const _uint& _iRenderID);
private:
	typedef list<class CGameObject*> RENDERS;
	RENDERS**			m_pRenderObj;
	_uint				m_iRenderMaxCount;
public:
	virtual void Free() override;
};

END