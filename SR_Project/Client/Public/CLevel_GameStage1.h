#pragma once
#include "Client_Defines.h"
#include "CLevel.h"

BEGIN(Client)

class CLevel_GameStage1 final : public CLevel
{
private:
	explicit CLevel_GameStage1(const LPDIRECT3DDEVICE9& _pDevice);
	virtual ~CLevel_GameStage1() = default;

public:
	virtual HRESULT NativeConstruct() override;
	virtual void Tick(const _float& _fDeltaSeconds)override;
	virtual void Late_Tick(const _float& _fDeletaSeconds)override;
	virtual HRESULT Render()override;
protected:
	HRESULT Ready_Layer_Terrian(const _tchar* _pLayerTag);
	HRESULT Ready_Layer_CameraFree(const _tchar* _pLayerTag);
	HRESULT Ready_Layer_Effect(const _tchar* _pLayerTag);
public:
	static CLevel* Create(LPDIRECT3DDEVICE9& _pDevice, const LEVEL& _eLevel);
	virtual void Free() override;
};

END