#pragma once
#include"CVIVertex_Rect.h"
#include "CTransform.h"
#include "CTexture.h"
#include "CVIVertex_Terrian.h"
#include "CVIVertex_Cube.h"
#include "CAStar_AI.h"

BEGIN(Engine)

class CComponent;

class CComponent_Manager final : public CBase
{
	DECLARE_SINGLETON(CComponent_Manager)
private:
	explicit CComponent_Manager();
	virtual ~CComponent_Manager() = default;

public:
	// Reserve Components
	HRESULT Reserve_Componets(const _uint& _iLevelCount);
	// 객체들의 원형 추가
	HRESULT Add_ProtoType(const _uint& _iLevelIndex, const _tchar* _pProtoTypeTag, CComponent* _pComponent);
	// 객체들의 사본을 추가
	CComponent* Clone_Component(const _uint & _iLevelIndex, const _tchar*& _pProtoTypeTag, void*& _pArg);
	// Level Index
	HRESULT Release_Components(const _uint& _iLevelIndex);
private:
	// Find Component
	CComponent* Find_Component(const _uint& _iLevelIndex, const _tchar*& _pFindTag);
private:
	map<const _tchar*, CComponent*>* m_mProtoTypes;
	typedef map<const _tchar*, CComponent*> PROTOTYPES;

	_uint m_iLevelCount;
public:
	virtual void Free() override;
};

END