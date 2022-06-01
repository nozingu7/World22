#pragma once
#include "Tool_Defines.h"
#include "CUI_Default.h"

BEGIN(Tool)
// ������ ������ ��쿡�� �������� ��������� �����ִ� Ŭ�����̸�, �÷��̾ �����ۿ� ������ ���� ��� �ش� �������� ������ �����ְ� �ȴ�.
// ��� �ÿ��� ������ ������ �ش� �������� ���� ������ ��������� �����ִ� ������ ������ �Ѱ��ִ� ������ ����ϸ� �ȴ�.
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
	// ������ Ȱ��ȭ ����
	_bool	m_bIsOn = false;

public:
	virtual CGameObject* Clone(void*& _pArg) override;
	virtual void Free() override;
};

END