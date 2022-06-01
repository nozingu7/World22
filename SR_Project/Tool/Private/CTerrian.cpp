#include "CTerrian.h"
#include "CGameInstance.h"

CTerrian::CTerrian(const LPDIRECT3DDEVICE9 & _pGraphic_Device)
	: CGameObject(_pGraphic_Device)
{
}

CTerrian::CTerrian(const CTerrian & _Prototype)
	: CGameObject(_Prototype)
{
}

HRESULT CTerrian::NativeConstruct_ProtoType()
{
	if (FAILED(__super::NativeConstruct_ProtoType()))
		return E_FAIL;

	return S_OK;
}

HRESULT CTerrian::NativeConstruct_Clone(void *& _pArg)
{
	if (FAILED(__super::NativeConstruct_Clone(_pArg)))
		return E_FAIL;

	if (FAILED(Add_Component()))
		return E_FAIL;

	return S_OK;
}

void CTerrian::Tick(const _float & _fDeltaTime)
{
	__super::Tick(_fDeltaTime);
}

void CTerrian::Late_Tick(const _float & _fDeltaTime)
{
	__super::Late_Tick(_fDeltaTime);
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);
	pGameInstance->Add_RenderObj(CRenderer_Manager::RENDER_NONALPHABLEND, this);
	Safe_Release(pGameInstance);
}

HRESULT CTerrian::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(m_pTransformComp->Bind_WorldMatrix()))
		return E_FAIL;

	if (FAILED(m_pTextureComp->Bind_Texture(1)))
		return E_FAIL;

	m_pGraphic_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	if (FAILED(m_pVertexTerrian->Render()))
		return E_FAIL;

	m_pGraphic_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	return S_OK;
}

HRESULT CTerrian::Add_Component()
{
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);
	{
		if (FAILED(__super::Add_Component((CComponent**)&m_pVertexTerrian, L"Com_Terrian", LEVEL_STATIC, L"PROTO_COMP_VIBUFFER_TERRIAN")))
			return E_FAIL;

		if (FAILED(__super::Add_Component((CComponent**)&m_pTransformComp, L"Com_Transform", LEVEL_STATIC, L"PROTO_COMP_TRANSFORM")))
			return E_FAIL;

		if (FAILED(__super::Add_Component((CComponent**)&m_pTextureComp, L"Com_Texture", LEVEL_STATIC, L"PROTO_COMP_TEXTURE_TEST")))
			return E_FAIL;

		CVIVertex_Terrian::TERRIANDESC tTerrianDesc = m_pVertexTerrian->Get_TerrianDesc();
		_VECTOR3 _v3TileSize = m_pVertexTerrian->Get_TileSize();
		_VECTOR3 _v3StartPos = _v3TileSize;
		BYTE* m_bByte = new BYTE[(tTerrianDesc.m_iNumVerticesX - 1) * (tTerrianDesc.m_iNumVerticesZ - 1)];
		memset(m_bByte, 0, sizeof(BYTE) * (tTerrianDesc.m_iNumVerticesX - 1) * (tTerrianDesc.m_iNumVerticesZ - 1));

		pGameInstance->Ready_AStar(m_bByte, m_pTransformComp->Get_WorldMatrixInverse(), _v3StartPos, tTerrianDesc.m_iNumVerticesX - 1, tTerrianDesc.m_iNumVerticesZ - 1);
		Safe_Delete_Array(m_bByte);
	}
	Safe_Release(pGameInstance);
	return S_OK;
}

HRESULT CTerrian::Ready_Terrian()
{
	return S_OK;
}

CTerrian * CTerrian::Create(const LPDIRECT3DDEVICE9& pGraphic_Device)
{
	CTerrian* pInstance = new CTerrian(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_ProtoType()))
	{
		MSG_BOX("Tool -> CTerrian::Create Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CTerrian::Clone(void *& _pArg)
{
	CTerrian* pInstance = new CTerrian(*this);
	if (FAILED(pInstance->NativeConstruct_Clone(_pArg)))
	{
		MSG_BOX("Tool -> CTerrian::Clone Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CTerrian::Free()
{
	__super::Free();
}
