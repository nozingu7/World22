#pragma once
#include "CGameObject.h"
#include "Client_Defines.h"

BEGIN(Engine)
class CVIVertex_Rect;
class CTexture;
class CTransform;
END

BEGIN(Client)

class CBackGround final : public CGameObject
{
private:
	explicit CBackGround(LPDIRECT3DDEVICE9& _pDevice);
	explicit CBackGround(CBackGround& _pProtoType);
	virtual ~CBackGround() = default;
public:
	// Initialize Methods 
	virtual HRESULT NativeConstruct_ProtoType() override;
	virtual HRESULT NativeConstruct_Clone(void*& _pArg) override;
	virtual void Tick(const _float& _fDeltaTime) override;
	virtual void Late_Tick(const _float& _fDeltaTime) override;
	virtual HRESULT Render() override;
private:
	HRESULT Add_Component();
private:
	CVIVertex_Rect*	m_pVertexRectComp;
	CTexture*		m_pTextureComp;
	CTransform*		m_pTransformComp;
public:
	static CBackGround* Create(LPDIRECT3DDEVICE9 pGraphic_Device); /* 원형객체를 만든다. */
	virtual CGameObject* Clone(void*& _pArg) override;
	virtual void Free() override;
};

END