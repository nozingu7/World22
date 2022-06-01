#pragma once
#include "Tool_Defines.h"
#include "CGameObject.h"

BEGIN(Tool)
// Character 클래스
class CCharacter abstract : public CGameObject
{
public:
	typedef struct tagCharInfoDesc
	{
		_float fCurHp;
		_float fMaxHp;
		_float fCurMp;
		_float fMaxMp;
		_float fAtkPower;
		_float fArmor;
		_float fCurSpeed;
		_float fMaxSpeed;
		_float fExp;
	}CHARINFO;
protected:
	explicit CCharacter(const LPDIRECT3DDEVICE9& _pDevice);
	explicit CCharacter(const CCharacter& _rhs);
	virtual ~CCharacter() = default;
public:
	virtual HRESULT NativeConstruct_ProtoType() override;
	virtual HRESULT NativeConstruct_Clone(void*& pArg) override;
	virtual void Tick(const _float& _fDeltaTime) override;
	virtual void Late_Tick(const _float& _fDeltaTime) override;
	virtual HRESULT Render() override;

protected:
	// 몸통을 제외한 신체 부위들
	vector<CGameObject*> m_vecBodies;
	// 플레이어의 경우, 장착하고 있는 아이템들 / 몬스터 경우 장착하고 있는 아이템
	vector<CGameObject*>	m_vecItemList;
	// Character Info Desc
	CHARINFO						m_tCharInfoDesc;
public:
	virtual CGameObject* Clone(void*& _pArg) = 0;
	virtual void Free() override;
};

END