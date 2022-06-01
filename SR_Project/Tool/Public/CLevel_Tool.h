#pragma once
#include "Tool_Defines.h"
#include "CLevel.h"

BEGIN(Tool)

class CLevel_Tool final : public CLevel
{
private:
	explicit CLevel_Tool(const LPDIRECT3DDEVICE9& _pDevice, const _uint& _iCurrentLevel);
	virtual ~CLevel_Tool() = default;
public:
	virtual HRESULT NativeConstruct() override;
	virtual void Tick(const _float& _fDeltaSeconds)override;
	virtual void Late_Tick(const _float& _fDeletaSeconds)override;
	virtual HRESULT Render()override;
private:
	HRESULT Ready_Background(const _tchar* _pLayerTag);
	HRESULT Ready_Player(const _tchar* _pLayerTag);
	HRESULT Ready_Camera(const _tchar* _pCamera);
	HRESULT Ready_Monster(const _tchar* _pLayerTag);
	HRESULT Ready_GameObject(const _tchar* _pLayerTag);
private:
	_uint		m_iCurrentLevel;
public:
	static CLevel* Create(LPDIRECT3DDEVICE9& _pDevice, const _uint& _iLevel = LEVEL_TOOL);
	virtual void Free() override;
};

END