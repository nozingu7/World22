#include "CIMGUI.h"
#include "..\Public\CIMGUI.h"

CIMGUI::CIMGUI(const LPDIRECT3DDEVICE9& _pDevice) :
	m_pGraphic_Device(_pDevice), m_bOpenWindow(false)
{
	Safe_AddRef(m_pGraphic_Device);
}

HRESULT CIMGUI::NativeConstruct()
{

	return S_OK;
}

HRESULT CIMGUI::Tick(const _float & _fDeltaSeconds)
{
	if (false == m_bOpenWindow)
		return E_FAIL;
	return S_OK;
}

HRESULT CIMGUI::Late_Tick(const _float & _fDeltaSeconds)
{
	if (false == m_bOpenWindow)
		return E_FAIL;
	return S_OK;
}

HRESULT CIMGUI::Render()
{
	if (false == m_bOpenWindow)
		return E_FAIL;

	Show_Window();

	return S_OK;
}

void CIMGUI::Show_Window()
{
}

void CIMGUI::Free()
{
	m_bOpenWindow = false;
	Safe_Release(m_pGraphic_Device);
}
