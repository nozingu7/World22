#pragma once
#include "Tool_Defines.h"
#include "CGameObject.h"

BEGIN(Engine)
class CVIVertex_Terrian;
class CTexture;
class CTransform;
END

BEGIN(Tool)

class CTerrian final : public CGameObject
{
private:
	explicit CTerrian(const LPDIRECT3DDEVICE9& _pGraphic_Device);
	explicit CTerrian(const CTerrian& _Prototype);
	virtual ~CTerrian() = default;
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
	// Readay Terrian
	HRESULT Ready_Terrian();
private:
	CVIVertex_Terrian*	m_pVertexTerrian;
	CTransform*				m_pTransformComp;
	CTexture*				m_pTextureComp;
public:
	static CTerrian* Create(const LPDIRECT3DDEVICE9& pGraphic_Device); /* ������ü�� �����. */
	virtual CGameObject* Clone(void*& _pArg) override;
	virtual void Free() override;
};

END