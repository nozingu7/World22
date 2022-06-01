#pragma once
#include "Tool_Defines.h"
#include "CBase.h"

BEGIN(Tool)

class CCamera_Engine;

class CCopyView final : public CBase
{
protected:
	typedef struct tagCustomVertex
	{ 
		_VECTOR4 v4Pos;
		DWORD color;
		_VECTOR2 v2Uv;
	}CUSTOMVERTEX;
private:
	explicit CCopyView(const LPDIRECT3DDEVICE9& _pDevice);
	virtual ~CCopyView() = default;
public:
	LPDIRECT3DTEXTURE9 Get_CopyTex() { return m_pMainTexture; }
public:
	// Intialize
	HRESULT NativeConstructor();
public:
	// Create Screen Shot
	HRESULT CreateScreenShot();
private:
	// Main Texture
	LPDIRECT3DTEXTURE9 	m_pMainTexture;
	// Surface 
	LPDIRECT3DSURFACE9 m_pSurface;
	LPDIRECT3DSURFACE9 m_pBackSurface;
private:
	// Graphic Device
	LPDIRECT3DDEVICE9 m_pGraphic_Device;
public:
	// Create 
	static CCopyView* Create(const LPDIRECT3DDEVICE9& _pDevice);
	virtual void Free() override;
};

END

/*

	//if (nullptr == m_pGraphic_Device)
	//	return E_FAIL;
	//LPDIRECT3DSURFACE9 dest = NULL;

	//LPDIRECT3DSURFACE9 pSurface = NULL;

	//LPD3DXBUFFER buffer = NULL;

	//m_pGraphic_Device->CreateOffscreenPlainSurface(g_iWinSizeX, g_iWinSizeY,
	//	D3DFMT_A8R8G8B8, D3DPOOL_SCRATCH, &pSurface, NULL);

	//m_pGraphic_Device->GetFrontBufferData(0, pSurface);

	//D3DXSaveSurfaceToFileInMemory(&buffer, D3DXIFF_JPG, pSurface, NULL, NULL);

	//D3DXCreateTextureFromFileInMemoryEx(m_pGraphic_Device, buffer->GetBufferPointer(), buffer->GetBufferSize(),
	//	D3DX_DEFAULT_NONPOW2, D3DFMT_A8R8G8B8, D3DPOOL_SCRATCH, 0,
	//	D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT, 0, NULL, 0, &m_pMainTexture);

	//if (dest) dest->Release();

	//if (pSurface) pSurface->Release();

*/