#pragma once
#include "CItem.h"

BEGIN(Tool)

class CPotion abstract : public CItem
{
public:
	typedef struct tagPotionInfo
	{
		// ���� ���ǵ��� �ɼǰ� (ü�� ȸ��, ���� ȸ��, ���ݷ� ���� ��� �󸶸�ŭ�� ��ġ�� �þ���� �����ָ� ��.)
		_uint iOption;
	}POTIONINFO;
protected:
	explicit CPotion(const LPDIRECT3DDEVICE9& _pDevice);
	explicit CPotion(const CPotion& _rhs);
	virtual ~CPotion() = default;

public:
	virtual HRESULT NativeConstruct_ProtoType();
	virtual HRESULT NativeConstruct_Clone(void*& pArg);
	virtual void Tick(const _float& _fDeltaTime);
	virtual void Late_Tick(const _float& _fDeltaTime);
	virtual HRESULT Render();

public:
	// ������ ������ �Ѵ�.
	virtual HRESULT Show_ToolTip() PURE;

private:
	virtual HRESULT SetUp_RenderState() PURE;
	virtual HRESULT Release_RenderState() PURE;

public:
	virtual CGameObject* Clone(void* pArg) = 0;
	virtual void Free();
};

END