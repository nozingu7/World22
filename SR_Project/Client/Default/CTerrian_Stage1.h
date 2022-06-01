#pragma once
#include "CGameObject.h"
#include "Client_Defines.h"

BEGIN(Engine)
class CVIVertex_Terrian;
class CTexture;
class CTransform;
END

BEGIN(Client)

class CTerrian_Stage1 final : public CGameObject
{
private:
	explicit CTerrian_Stage1(const LPDIRECT3DDEVICE9& _pGraphic_Device);
	explicit CTerrian_Stage1(const CTerrian_Stage1& _Prototype);
	virtual ~CTerrian_Stage1() = default;
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
	CVIVertex_Terrian*	m_pVertexTerrian;
	CTexture*					m_pTextureComp;
	CTransform*				m_pTransformComp;
public:
	static CTerrian_Stage1* Create(LPDIRECT3DDEVICE9 pGraphic_Device); /* 원형객체를 만든다. */
	virtual CGameObject* Clone(void*& _pArg) override;
	virtual void Free() override;
};

END