#pragma once
#include "Tool_Defines.h"
#include "CCharacter.h"

BEGIN(Engine)
class CVIVertex_Rect;
class CTexture;
class CTransform;
END

BEGIN(Tool)

// �÷��̾� ĳ���� Ŭ����
class CPlayer : public CCharacter
{
protected:
	explicit CPlayer(const LPDIRECT3DDEVICE9& _pDevice);
	explicit CPlayer(const CPlayer& _rhs);
	virtual ~CPlayer() = default;

public:
	virtual HRESULT NativeConstruct_ProtoType();
	virtual HRESULT NativeConstruct_Clone(void*& pArg);
	virtual void Tick(const _float& _fDeltaTime);
	virtual void Late_Tick(const _float& _fDeltaTime);
	virtual HRESULT Render();
private:
	HRESULT Add_Component();
	HRESULT SetUp_RenderState();
	HRESULT Release_RenderState();
	HRESULT SetUp_Height();
	HRESULT Player_Move(const _float & _fDeltaSeconds);
private:
	CVIVertex_Rect*			m_pVertexRectComp;
	CTexture*						m_pTextureComp;
	CTransform*				m_pTransformComp;
public:
	static CPlayer* Create(const LPDIRECT3DDEVICE9& _pDevice);
	virtual CGameObject* Clone(void*& _pArg) override;
	virtual void Free() override;
};

END