#pragma once
#include "CIMGUI.h"
// CFile_Manager::FILEDESC �� ����ؼ� ��¿ �� ���� ������Ͽ� �߰�
#include "CGameInstance.h"

BEGIN(Tool)

class CFileDialog final : public CIMGUI
{
private:
	explicit CFileDialog(const LPDIRECT3DDEVICE9& _pDevice);
	virtual ~CFileDialog() = default;

public:
	virtual HRESULT NativeConstruct() override;
	virtual HRESULT Tick(const _float& _fDeltaSeconds) override;
	virtual HRESULT Late_Tick(const _float& _fDeltaSeconds) override;
	virtual HRESULT Render() override;

private:
	void DisplayNode(const FILEDESC* node, const vector<FILEDESC>& allNode);
	void PreView(_uint iTexIndex);

private:
	CTexture*	m_pTextureComp = nullptr;

public:
	static CFileDialog* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual void Free() override;
};

END