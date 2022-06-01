#include "CCopyView.h"
#include "CGameInstance.h"

CCopyView::CCopyView(const LPDIRECT3DDEVICE9& _pDevice)
	: m_pGraphic_Device(_pDevice), m_pMainTexture(nullptr),
	m_pSurface(nullptr), m_pBackSurface(nullptr)
{
	Safe_AddRef(m_pGraphic_Device);
}

HRESULT CCopyView::NativeConstructor()
{
	// Is Not Graphic Device Assignment
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;

	//if (FAILED(0))
	//	return E_FAIL;
	m_pGraphic_Device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_NONE);

	m_pGraphic_Device->CreateTexture(g_iWinSizeX, g_iWinSizeY, 0,
		D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT,
		&m_pMainTexture, nullptr);

	return S_OK;
}

HRESULT CCopyView::CreateScreenShot()
{
	CGameInstance* pInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pInstance);
	m_pMainTexture->GetSurfaceLevel(0, &m_pSurface);
	_uint i = Safe_Release(m_pMainTexture);
	m_pGraphic_Device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &m_pBackSurface);
	m_pGraphic_Device->SetRenderTarget(0, m_pSurface);

	pInstance->Render_Begin();
	pInstance->Render_Engine(0);
	pInstance->Render_End();

	// Draw Texti
	m_pGraphic_Device->SetRenderTarget(0, m_pBackSurface);
	Safe_Release(pInstance);
	return S_OK;
}

CCopyView * CCopyView::Create(const LPDIRECT3DDEVICE9 & _pDevice)
{
	CCopyView* pInstance = new CCopyView(_pDevice);
	if (FAILED(pInstance->NativeConstructor()))
	{
		MSG_BOX("CCopyView::Create Is Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CCopyView::Free()
{
	Safe_Release(m_pMainTexture);
	Safe_Release(m_pGraphic_Device);
}
