#pragma once
#include "CIMGUI.h"

BEGIN(Tool)

class CPathMaker final : public CIMGUI
{
private:
	explicit CPathMaker(const LPDIRECT3DDEVICE9& _pDevice);
	virtual ~CPathMaker() = default;
private:
	typedef struct tagPathMakerDesc
	{
		_VECTOR3 v3CenterPos, v3MinPos, v3MaxPos;
		_bool bIsClikced;
	}PATHMAKERDESC;
public:
	virtual HRESULT NativeConstruct();
	virtual HRESULT Tick(const _float& _fDeltaSeconds);
	virtual HRESULT Late_Tick(const _float& _fDeltaSeconds);
	virtual HRESULT Render();
protected:
	// IMGUI  UI
	virtual void Show_Window();
private:
	// PathPosList 
	typedef list<PATHMAKERDESC>	PATHLIST;
	PATHLIST*									m_pPathPosList;
	map<_uint, list<_VECTOR3>>	m_mapPathGroup;
private:
	
public:
	static CPathMaker* Create(const LPDIRECT3DDEVICE9& _pDevice);
	virtual void Free() override;
};

END