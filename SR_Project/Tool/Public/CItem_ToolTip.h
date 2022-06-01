#pragma once
#include "Tool_Defines.h"
#include "CUI_Default.h"

BEGIN(Tool)
// 아이템 툴팁의 경우에는 아이템이 멤버변수로 갖고있는 클래스이며, 플레이어가 아이템에 가까이 갔을 경우 해당 아이템의 정보를 보여주게 된다.
// 사용 시에는 아이템 생성시 해당 아이템이 가진 정보를 멤버변수로 갖고있는 아이템 툴팁에 넘겨주는 식으로 사용하면 된다.
class CItem_ToolTip final : public CUI_Default
{
private:
	explicit CItem_ToolTip(const LPDIRECT3DDEVICE9& _pDevice);
	explicit CItem_ToolTip(const CItem_ToolTip& _rhs);
	virtual ~CItem_ToolTip() = default;

public:
	// Initialize Methods 
	virtual HRESULT NativeConstruct_ProtoType();
	virtual HRESULT NativeConstruct_Clone(void*& pArg);
	virtual void Tick(const _float& _fDeltaTime);
	virtual void Late_Tick(const _float& _fDeltaTime);
	virtual HRESULT Render();
protected:
	// Add Component
	virtual HRESULT Add_Component() = 0;
	// Set Up Comp
	virtual HRESULT SetUp_RenderState() override;
	// Release Comp
	virtual HRESULT Release_RenderState() override;
protected:
	// 툴팁의 활성화 여부
	_bool	m_bIsOn = false;

public:
	virtual CGameObject* Clone(void*& _pArg) override;
	virtual void Free() override;
};

END