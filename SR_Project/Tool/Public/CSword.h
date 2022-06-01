#pragma once
#include "CWeapon.h"

BEGIN(Engine)
class CTexture;
class CVIVertex_Rect;
class CTransform;
END

BEGIN(Tool)

class CSword final : public CWeapon
{
private:
	explicit CSword(const LPDIRECT3DDEVICE9& _pDevice);
	explicit CSword(const CSword& _rhs);
	virtual ~CSword() = default;

public:
	virtual HRESULT NativeConstruct_ProtoType() override;
	virtual HRESULT NativeConstruct_Clone(void*& pArg) override;
	virtual void Tick(const _float& _fDeltaTime) override;
	virtual void Late_Tick(const _float& _fDeltaTime) override;
	virtual HRESULT Render() override;

private:
	HRESULT Add_Component();

public:
	// ������ ������ �Ѵ�.
	virtual HRESULT Show_ToolTip() override;

private:
	virtual HRESULT SetUp_RenderState() override;
	virtual HRESULT Release_RenderState() override;

private:
	// �̸� ������ �������ô� �� ��õ��~
	// ������ ��������� �� �Ʒ��� �Դٰ��� �ϴ°���~
	void Fly(_float fDeltaTime);

	void Move_Up(_float fDeltaTime);
	void Move_Down(_float fDeltaTime);

private:
	CTexture*				m_pTextureComp = nullptr;
	CVIVertex_Rect*			m_pVIBufferComp = nullptr;
	CTransform*				m_pTransformComp = nullptr;

private:
	// ������ �����̴°� �׽�Ʈ��
	list<_VECTOR3>  m_vNodeList;
	// ������ �����̴°� �� �� ����� �ӵ� ��
	_float			m_fAccel = 0.f;
	_bool			m_bIsDown = false;
public:
	static CSword* Create(LPDIRECT3DDEVICE9& _pDevice);
	virtual CGameObject* Clone(void*& _pArg) override;
	virtual void Free() override;
};

END