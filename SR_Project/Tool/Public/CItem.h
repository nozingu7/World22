#pragma once
#include "Tool_Defines.h"
#include "CGameObject.h"

BEGIN(Tool)

class CItem abstract : public CGameObject
{
protected:
	explicit CItem(const LPDIRECT3DDEVICE9& _pDevice);
	explicit CItem(const CItem& _rhs);
	virtual ~CItem() = default;
public:
	typedef struct tagItemInfoDesc
	{
		_float fHp;
		_float fAtkPower;
		_float fArmor;
		_float fSpeed;
	}ITEMINFO;
public:
	virtual HRESULT NativeConstruct_ProtoType();
	virtual HRESULT NativeConstruct_Clone(void*& pArg);
	virtual void Tick(const _float& _fDeltaTime);
	virtual void Late_Tick(const _float& _fDeltaTime);
	virtual HRESULT Render();

protected:
	// �������� �÷��̾ ������ ������ ���ȵ��� �����ִ� ������ ���;� �ϴ� ���� ���� Ŭ������ �߰��ؾ��Ѵ�.
	class CItem_ToolTip* m_pToolTip = nullptr;
protected:
	// ������ Info
	ITEMINFO					m_tItemInfo;
public:
	// ������ ������ �Ѵ�.
	virtual HRESULT Show_ToolTip() PURE;	

private:
	virtual HRESULT SetUp_RenderState() PURE;
	virtual HRESULT Release_RenderState() PURE;

public:
	virtual CGameObject* Clone(void*& _pArg) = 0;
	virtual void Free() override;
};

END