#include "..\Public\CTexture.h"

CTexture::CTexture(const LPDIRECT3DDEVICE9 & _pDevice)
	: CComponent(_pDevice)
{
}

CTexture::CTexture(const CTexture & _rhs)
	: CComponent(_rhs), m_vecTextureList(_rhs.m_vecTextureList)
{
	for_each(m_vecTextureList.begin(), m_vecTextureList.end(), [&](auto& Textures) { Safe_AddRef(Textures); });
}

HRESULT CTexture::NativeConstruct_ProtoType(const TYPE & _eType, const _tchar *& _pPath, const _uint & _iTextureNum)
{
	if (FAILED(__super::NativeConstruct_ProtoType()))
		return E_FAIL;

	_tchar szPath[MAX_PATH] = TEXT("");
	m_vecTextureList.reserve(_iTextureNum + 1);

	for (_uint i = 0; i < _iTextureNum; ++i)
	{
		wsprintf(szPath, _pPath, i);

		LPDIRECT3DBASETEXTURE9 _pBaseTexture = nullptr;
		if (TYPE_DEFAULT == _eType)
		{
			if (FAILED(D3DXCreateTextureFromFile(m_pGraphic_Device, szPath, (LPDIRECT3DTEXTURE9*)&_pBaseTexture)))
			{
				MSG_BOX("CTexture::NatviceConstruct_ProtoType Failed To Load Default Texture");
				return E_FAIL;
			}
		}
		else if (TYPE_CUBEMAP == _eType)
		{
			if (FAILED(D3DXCreateCubeTextureFromFile(m_pGraphic_Device, szPath, (LPDIRECT3DCUBETEXTURE9*)&_pBaseTexture)))
			{
				MSG_BOX("CTexture::NatviceConstruct_ProtoType Failed To Load Cube Texture");
				return E_FAIL;
			}
		}

		m_vecTextureList.emplace_back(_pBaseTexture);
	}
	return S_OK;
}

HRESULT CTexture::NativeConstruct_ProtoType(const TYPE & _eType, void *& _pList)
{
	if (FAILED(__super::NativeConstruct_ProtoType()))
		return E_FAIL;

	vector<_wstring> m_strPathList = *static_cast<vector<_wstring>*>(_pList);

	_tchar szPath[MAX_PATH] = TEXT("");
	m_vecTextureList.reserve(m_strPathList.size() + 1);

	for (_uint i = 0; i < m_strPathList.size(); ++i)
	{
		wsprintf(szPath, m_strPathList[i].c_str(), i);

		LPDIRECT3DBASETEXTURE9 _pBaseTexture = nullptr;
		if (TYPE_DEFAULT == _eType)
		{
			if (FAILED(D3DXCreateTextureFromFile(m_pGraphic_Device, szPath, (LPDIRECT3DTEXTURE9*)&_pBaseTexture)))
			{
				MSG_BOX("CTexture::NatviceConstruct_ProtoType Failed To Load Default Texture");
				return E_FAIL;
			}
		}
		else if (TYPE_CUBEMAP == _eType)
		{
			if (FAILED(D3DXCreateCubeTextureFromFile(m_pGraphic_Device, szPath, (LPDIRECT3DCUBETEXTURE9*)&_pBaseTexture)))
			{
				MSG_BOX("CTexture::NatviceConstruct_ProtoType Failed To Load Cube Texture");
				return E_FAIL;
			}
		}

		m_vecTextureList.emplace_back(_pBaseTexture);
	}
	return S_OK;
}

HRESULT CTexture::NativeConstruct_ProtoType(const TYPE& _eType, vector<FILEDESC>*& rFileDesc)
{
	if (FAILED(__super::NativeConstruct_ProtoType()))
		return E_FAIL;

	// c : 리스트 전체 순회 ?
	//m_pTextureVec = new TEXTURES[rFileDesc->size()];

	_tchar szFullPath[MAX_PATH] = TEXT("");
	m_vecTextureList.reserve(rFileDesc->size() + 1);

	for (_uint i = 0; i < rFileDesc->size(); ++i)
	{
		auto	iter = (*rFileDesc)[i];

		//if (iter.bIsFolder)
		//	continue;

		lstrcpy(szFullPath, iter.szFilePath.c_str());

		//if (iter.szFileName == TEXT("front.png"))
		//{
		//	int a = 10;
		//}

		//wsprintf(szFullPath, iter.szFilePath.c_str(), i);
		LPDIRECT3DBASETEXTURE9 _pBaseTexture = nullptr;

		if (TYPE_DEFAULT == _eType)
		{
			if (FAILED(D3DXCreateTextureFromFile(m_pGraphic_Device, szFullPath, (LPDIRECT3DTEXTURE9*)&_pBaseTexture)))
			{
				//MSG_BOX("CTexture::NatviceConstruct_ProtoType Failed To Load Default Texture");
				//return E_FAIL;
				continue;
			}
		}
		else if (TYPE_CUBEMAP == _eType)
		{
			if (FAILED(D3DXCreateCubeTextureFromFile(m_pGraphic_Device, szFullPath, (LPDIRECT3DCUBETEXTURE9*)&_pBaseTexture)))
			{
				MSG_BOX("CTexture::NatviceConstruct_ProtoType Failed To Load Cube Texture");
				return E_FAIL;

				continue;
			}
		}

		m_vecTextureList.emplace_back(_pBaseTexture);
	}

	return S_OK;
}

HRESULT CTexture::NativeConstruct_Clone(void *& _pArg)
{
	if (__super::NativeConstruct_Clone(_pArg))
		return E_FAIL;

	return S_OK;
}

HRESULT CTexture::Bind_Texture(const _uint & _iIndex)
{
	if (_iIndex < 0 || _iIndex >= m_vecTextureList.size())
		return E_FAIL;

	m_pGraphic_Device->SetTexture(0, m_vecTextureList[_iIndex]);
	return S_OK;
}


CTexture* CTexture::Create(const LPDIRECT3DDEVICE9& _pDevice, const TYPE & _eType, vector<FILEDESC>*& rFileDesc)
{
	CTexture* pInstance = new CTexture(_pDevice);
	if (FAILED(pInstance->NativeConstruct_ProtoType(_eType, rFileDesc)))
		Safe_Release(pInstance);

	return pInstance;
}


CTexture * CTexture::Create(const LPDIRECT3DDEVICE9 & _pDevice, const TYPE & _eType, const _tchar * _pPath, const _uint & _iTextureNum)
{
	CTexture* pInstance = new CTexture(_pDevice);
	if (FAILED(pInstance->NativeConstruct_ProtoType(_eType, _pPath, _iTextureNum)))
		Safe_Release(pInstance);

	return pInstance;
}

CTexture * CTexture::Create(const LPDIRECT3DDEVICE9 & _pDevice, const TYPE & _eType, void * _pList)
{
	CTexture* pInstance = new CTexture(_pDevice);
	if (FAILED(pInstance->NativeConstruct_ProtoType(_eType, _pList)))
		Safe_Release(pInstance);

	return pInstance;
}

CComponent * CTexture::Clone(void *& _pArg)
{
	CTexture* pTexture = new CTexture(*this);
	if (FAILED(pTexture->NativeConstruct_Clone(_pArg)))
	{
		MSG_BOX("CTexture::Clone Failed");
		Safe_Release(pTexture);
	}
	return pTexture;
}

void CTexture::Free()
{
	__super::Free();
	for_each(m_vecTextureList.begin(), m_vecTextureList.end(), [&](auto& Textures) { Safe_Release(Textures); });


}
