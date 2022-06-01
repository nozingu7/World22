#pragma once
#include "Client_Defines.h"
#include "CSortObject.h"

BEGIN(Engine)
class CTexture;
class CTransform;
class CVIVertex_Rect;
END

BEGIN(Client)
class CEffect : public CSortObject
{
protected:
	explicit CEffect(const LPDIRECT3DDEVICE9& _pDevice);
	explicit CEffect(const CEffect& _rhs);
	virtual ~CEffect() = default;
public:
	// Initialize Methods 
	virtual HRESULT NativeConstruct_ProtoType() override;
	virtual HRESULT NativeConstruct_Clone(void*& pArg) override;
	virtual void Tick(const _float& _fDeltaTime) override;
	virtual void Late_Tick(const _float& _fDeltaTime) override;
	virtual HRESULT Render() override;
protected:
	// SetUp Component
	virtual HRESULT SetUp_Component();
	// Render state
	virtual HRESULT Render_State();
	// Release Render State
	virtual HRESULT Release_RenderState();
private:
	CTransform*		m_pTransformCom = nullptr;
	CVIVertex_Rect*	m_pVIBufferCom = nullptr;
	CTexture*			m_pTextureCom = nullptr;
private:
	_float					m_fFrame;
public:
	static CEffect* Create(const LPDIRECT3DDEVICE9& pGraphic_Device); /* 원형객체를 만든다. */
	virtual CGameObject* Clone(void*& pArg) override; /* 사본객체를 만들어 리턴한다. */
	virtual void Free() override;
};

END