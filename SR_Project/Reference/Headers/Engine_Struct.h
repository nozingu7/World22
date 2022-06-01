#pragma once


namespace Engine
{
	typedef struct tagGraphicDesc
	{
		HWND hWnd;
		unsigned long iWinCX;
		unsigned long iWinCY;
		bool isWindowed;
	}GRAPHICDESC;

	typedef struct tagVertex_TextureDesc
	{
		D3DXVECTOR3 v3Position;
		D3DXVECTOR2 v2UVPosition;
	}VTXTEX;

	typedef struct tagVertex_CubeTextureDesc
	{
		D3DXVECTOR3 v3Position;
		D3DXVECTOR3 v3UvPosition;
	}VTXCUBETEX;

	typedef struct tagTileDesc
	{
		tagTileDesc()
		{		
			pParents = nullptr;
			// Value
			v3Position = D3DXVECTOR3(0.f, 0.f, 0.f);
			iIndex = 0;
			bType = 0;
		}
		tagTileDesc* pParents;
		D3DXVECTOR3 v3Position;
		unsigned int iIndex;
		byte				bType;
	}TILE;

	typedef struct tagFaceIndices16
	{
		unsigned short _1, _2, _3;
	}FACEINDICES16;

	typedef struct FaceIndices32
	{
		unsigned long _1, _2, _3;
	}FACEINDICES32;

	typedef struct FaceLineIndices16
	{
		unsigned short _1, _2;
	}FACELINEINDICES16;

	typedef struct FaceLineIndices32
	{
		unsigned long _1, _2;
	}FACELINEINDICES32;

	// ������ �������� ��� ����ü
	typedef struct tagFileInfo
	{
		// ���� �̸�
		wstring szFileName;
		// ���� ����
		wstring szFileType;
		// ���� ���
		wstring szFilePath;
		// ���� ���� �̸�
		wstring szParentName;
		// �������� �ƴ���
		bool	 bIsFolder;
		// Vector �����̳� ����� �� ����� �ε���
		unsigned  int  iIndex;
		// FileCnt�� ������ �����ϰ� ���ϸ��� �ε����� ��´�.
		unsigned int	iFileCnt;

	}FILEDESC;
}