/*==============================================================================

   �����_�����O�Ǘ�[renderer.h]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once

#include "main.h"


//*********************************************************
// �}�N����`
//*********************************************************
enum BLEND_MODE
{
	BLEND_MODE_NONE,		//�u�����h����
	BLEND_MODE_ALPHABLEND,	//���u�����h
	BLEND_MODE_ADD,			//���Z�u�����h
	BLEND_MODE_SUBTRACT,	//���Z�u�����h

	BLEDD_MODE_NUM
};

enum CULL_MODE
{
	CULL_MODE_NONE,			//�J�����O����
	CULL_MODE_FRONT,		//�\�̃|���S����`�悵�Ȃ�(CW)
	CULL_MODE_BACK,			//���̃|���S����`�悵�Ȃ�(CCW)

	CULL_MODE_NUM
};

enum ADDRESS_MODE
{
	ADDRESS_MODE_WRAP,
	ADDRESS_MODE_MIRROR,
	ADDRESS_MODE_CLAMP,
	ADDRESS_MODE_BORDER,

	ADDRESS_MODE_NUM
};

enum FILTER_MODE
{
	FILTER_MODE_POINT,
	FILTER_MODE_LINEAR,
	FILTER_MODE_ANISOTROPIC,

	FILTER_MODE_NUM
};

//*********************************************************
// �\����
//*********************************************************

// ���_�\����
struct VERTEX_3D
{
    D3DXVECTOR3 Position;
    D3DXVECTOR3 Normal;
    D3DXCOLOR   Diffuse;
    D3DXVECTOR2 TexCoord;
};


// �}�e���A���\����
struct MATERIAL
{
	D3DXCOLOR	Ambient;
	D3DXCOLOR	Diffuse;
	D3DXCOLOR	Specular;
	D3DXCOLOR	Emission;
	float		Shininess;
	float		Dummy[3];//16byte���E�p
};


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitRenderer(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void UninitRenderer(void);

void Clear(void);
void Present(void);

ID3D11Device *GetDevice( void );
ID3D11DeviceContext *GetDeviceContext( void );

void SetDepthEnable( bool Enable );
void SetBlendState(BLEND_MODE bm);
void SetCullingMode(CULL_MODE cm);
void SetSamplerState(FILTER_MODE fm, ADDRESS_MODE am);
void SetSamplerBorderColor(D3DXCOLOR col);

void SetWorldViewProjection2D( void );
void SetWorldMatrix( D3DXMATRIX *WorldMatrix );
void SetViewMatrix( D3DXMATRIX *ViewMatrix );
void SetProjectionMatrix( D3DXMATRIX *ProjectionMatrix );
