#pragma once
#include "Tool_Defines.h"
#include "CUserInterFace.h"

BEGIN(Engine)
class CTransform;
class CVIVertex_Rect;
class CTexture;
END

BEGIN(Tool)

class CUI_Default abstract : public CUserInterFace
{
public:
	enum RENDERMODE { MODE_OVERLAY, MODE_WORLD, MODE_END };
	// canvas / visual / interaction
	enum UITYPE { UI_CANVAS, UI_IMAGE, UI_BUTTON, UI_TEXT, UI_END };
	typedef struct tagRectTfDesc
	{
		_float			m_fWidth, m_fHeight;	// 크기
		_VECTOR2		m_vPivot;				// local 원점
		_VECTOR2		m_vAnchors;				// world 원점

	}UIRECT;
protected:
	explicit CUI_Default(const LPDIRECT3DDEVICE9& _pDevice);
	explicit CUI_Default(const CUI_Default& _pProtoType);
	virtual ~CUI_Default() = default;
public:
	// Initialize Methods 
	virtual HRESULT NativeConstruct_ProtoType() override;
	virtual HRESULT NativeConstruct_Clone(void*& pArg)override;
	virtual void Tick(const _float& _fDeltaTime) override;
	virtual void Late_Tick(const _float& _fDeltaTime) override;
	virtual HRESULT Render() override;
protected:
	// Add Component
	virtual HRESULT Add_Component() = 0;
	// Set Up Comp
	virtual HRESULT SetUp_RenderState() override;
	// Release Comp
	virtual HRESULT Release_RenderState() override;
protected:
	HRESULT	Bind_OrthoMatrix();
	HRESULT BillBoard();
	void	Update_Mouse();
protected:
	RENDERMODE			m_eUIRender;
	UITYPE							m_eUIType;
	_uint							m_iSortOrder;

	UIRECT						m_tUiRect;
	_float4x4						m_fProjMatrix;
	_VECTOR2					m_vCenter;
protected:
	CTransform*				m_pTransformComp;
	CVIVertex_Rect*			m_pVIBufferComp;
	CTexture*					m_pTextrueComp ;
public:
	virtual CGameObject* Clone(void*& _pArg) = 0;
	virtual void Free() override;
};

END