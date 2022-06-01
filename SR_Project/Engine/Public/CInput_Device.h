#pragma once

#include "CBase.h"

BEGIN(Engine)

class CInput_Device final : public CBase
{
	DECLARE_SINGLETON(CInput_Device)
public:
	enum DIMOUSEMOVE { DIMM_X, DIMM_Y, DIMM_WHEEL, DIMM_END };
	enum DIMOUSEBUTTON { DIMB_L, DIMB_R, DIMB_WHEEL, DIMB_END };

private:
	explicit CInput_Device();
	virtual ~CInput_Device() = default;

public:
	_byte Get_DIKeyState(const _ubyte& _eKeyID) {return m_byKeyState[_eKeyID];}

	_long Get_DIMMoveState(const DIMOUSEMOVE& _eMouseMove){	return *((_long*)&m_MouseState + _eMouseMove); }
	_byte Get_DIMButtonState(const DIMOUSEBUTTON& _eMouseButton){ return m_MouseState.rgbButtons[_eMouseButton]; }

public:
	HRESULT Initialize_Input_Device(const HINSTANCE& _hInst, const HWND& _hwnd);
	HRESULT Update();

private:
	LPDIRECTINPUT8					m_pInput = nullptr;
	LPDIRECTINPUTDEVICE8		m_pKeyboard = nullptr;
	LPDIRECTINPUTDEVICE8		m_pMouse = nullptr;

private:
	_byte						m_byKeyState[256] = { 0 };
	DIMOUSESTATE				m_MouseState;

public:
	virtual void Free() override;
};

END