#pragma once
#include "Client_Defines.h"
#include "CGameObject.h"

BEGIN(Engine)
class CTexture;
class CTransform;
class CVIVertex_Cube;
END

BEGIN(Client)

class CSky final : public CGameObject
{
private:
	explicit CSky(const LPDIRECT3DDEVICE9& pGraphic_Device);
	explicit CSky(const CSky& Prototype);
	virtual ~CSky() = default;
public:
	// Initialize Methods 
	virtual HRESULT NativeConstruct_ProtoType() override;
	virtual HRESULT NativeConstruct_Clone(void*& pArg) override;
	virtual void Tick(const _float& _fDeltaTime) override;
	virtual void Late_Tick(const _float& _fDeltaTime) override;
	virtual HRESULT Render() override;
private:
	CTransform*				m_pTransformCom = nullptr;
	CVIVertex_Cube*			m_pVIBufferCom = nullptr;
	CTexture*				m_pTextureCom = nullptr;
private:
	HRESULT SetUp_Components();
	HRESULT SetUp_RenderState();
	HRESULT Release_RenderState();

public:
	static CSky* Create(LPDIRECT3DDEVICE9 pGraphic_Device); /* 원형객체를 만든다. */
	virtual CGameObject* Clone(void*&  _pArg) override; /* 사본객체를 만들어 리턴한다. */
	virtual void Free() override;
};

END