#pragma once

#include "CBase.h"

BEGIN(Engine)

class CGraphic_Device final : public CBase
{
	DECLARE_SINGLETON(CGraphic_Device)
private:
	CGraphic_Device();
	virtual ~CGraphic_Device() = default;
	// com 객체 : 언어와의 통신 규약을 갖고 하드웨어를 통제하여 각종 기능을 제공하는 객체

public:
	LPDIRECT3DDEVICE9			Get_Device(void) { return m_pDevice; }
	LPD3DXFONT					Get_Font(void) { return m_pFont; }
public:
	HRESULT		InitDevice(const GRAPHICDESC& GraphicDesc, LPDIRECT3DDEVICE9& _pOut);
	void		SetParameters(D3DPRESENT_PARAMETERS& d3dpp);

	void		Render_Begin(void);
	void		Render_End(HWND hWnd = NULL);
	// Render Line
	void		Render_Line(const _VECTOR3& _Start, const _VECTOR3& _End, const _float& _fLineWidth, const D3DXCOLOR& _Color);
	void		Render_Lines(void* _pPosList, const _float& _fLineWidth, const D3DXCOLOR& _Color);
private:
	LPDIRECT3D9					m_p3D;
	LPDIRECT3DDEVICE9		m_pDevice;
	GRAPHICDESC				m_GraphicDesc;

	// dx 상에서 2d 이미지를 출력해주는 com객체
	LPD3DXFONT				m_pFont;
	LPD3DXSPRITE			m_pSprite;
	LPD3DXLINE				m_pLine;
public:
	virtual void Free() override;
};

END