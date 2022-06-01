#pragma once
#include "CComponent.h"
#include "CFile_Manager.h"

BEGIN(Engine)

class ENGINE_DLL CTexture final : public CComponent
{
public:
	enum TYPE { TYPE_DEFAULT, TYPE_CUBEMAP, TYPE_END };
private:
	explicit CTexture(const LPDIRECT3DDEVICE9& _pDevice);
	explicit CTexture(const CTexture& _rhs);
	virtual ~CTexture() override = default;

public:
	virtual HRESULT NativeConstruct_ProtoType(const TYPE& _eType, const _tchar*& _pPath, const _uint& _iTextureNum);
	virtual HRESULT NativeConstruct_ProtoType(const TYPE& _eType, void*& _pList);
	virtual HRESULT NativeConstruct_ProtoType(const TYPE& _eType, vector<FILEDESC>*& rFileDesc);
	virtual HRESULT NativeConstruct_Clone(void*& _pArg) override;

public:
	HRESULT Bind_Texture(const _uint& iIndex);
	LPDIRECT3DBASETEXTURE9	Get_Texture(const _uint& iIndex) {
		if (iIndex < m_vecTextureList.size())
			return m_vecTextureList[iIndex];
		return nullptr;
	}
public:
	_uint	Get_TextureNum() { return m_iTextureNum; }
	void	Set_TextureNum(_uint iTextureNum) { m_iTextureNum = iTextureNum; }

private:
	vector<LPDIRECT3DBASETEXTURE9>	m_vecTextureList;
	_uint	m_iTextureNum = 0;

public:
	static CTexture* Create(const LPDIRECT3DDEVICE9& _pDevice, const TYPE & _eType, vector<FILEDESC>*& rFileDesc);
	static CTexture* Create(const LPDIRECT3DDEVICE9& _pDevice, const TYPE& _eType, const _tchar* _pPath, const _uint& _iTextureNum);
	static CTexture* Create(const LPDIRECT3DDEVICE9& _pDevice, const TYPE& _eType, void* _pList);
	virtual CComponent* Clone(void*& _pArg) override;
	virtual void Free() override;
};

END