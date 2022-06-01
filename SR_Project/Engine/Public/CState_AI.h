#pragma once
#include "CAIComponent.h"

BEGIN(Engine)

class CGameObject;

class CState_AI final : public CAIComponent
{
public:
	enum STATE{
		STATE_IDLE, STATE_MOVE, STATE_ATTACK, STATE_DIE, STATE_END
	};
private:
	explicit CState_AI(const LPDIRECT3DDEVICE9& _pGraphic_Device);
	explicit CState_AI(const CState_AI& _rhs);
	virtual ~CState_AI() = default;
public:
	virtual HRESULT NativeConstruct_ProtoType() override;
	virtual HRESULT NativeConstruct_Clone(void*& _pArg) override;
public:
	// Setting State
	HRESULT Set_State(const STATE& _eState);
private:
	// Owner
	CGameObject*	m_pOwner;
private:
	// Cur State
	STATE					m_eCurState;
public:
	virtual CComponent* Clone(void*& _pArg) override;
	virtual void Free() override;
};

END