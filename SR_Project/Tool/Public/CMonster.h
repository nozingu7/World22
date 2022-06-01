#pragma once
#include "Tool_Defines.h"
#include "CCharacter.h"

BEGIN(Engine)
// AStar AI Comp
class CAStar_AI;
class CTexture;
class CVIVertex_Rect;
class CTransform;
END

BEGIN(Tool)
// 몬스터들의 부모가 되는 클래스
class CMonster : public CCharacter
{
protected:
	explicit CMonster(const LPDIRECT3DDEVICE9& _pDevice);
	explicit CMonster(const CMonster& _rhs);
	virtual ~CMonster() = default;

public:
	virtual HRESULT NativeConstruct_ProtoType();
	virtual HRESULT NativeConstruct_Clone(void*& pArg);
	virtual void Tick(const _float& _fDeltaTime);
	virtual void Late_Tick(const _float& _fDeltaTime);
	virtual HRESULT Render();
protected:

	// Readay Component
	virtual HRESULT Ready_Comp();
private:
	// 트랜스폼
	CTransform*				m_pTransformComp;
	// Rect
	CVIVertex_Rect*		m_pVertexRectComp;
	// Texture
	CTexture*					m_pTextureComp;
	// AStar Component
	CAStar_AI*				m_pAStar_AIComp;
public:
	static CMonster* Create(const LPDIRECT3DDEVICE9& _pDevice);
	virtual CGameObject* Clone(void*& _pArg) override;
	virtual void Free() override;
};

END