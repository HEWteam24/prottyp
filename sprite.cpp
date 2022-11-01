//=============================================================================
//
// �X�v���C�g���� [sprite.cpp]
// Author : 
//
//=============================================================================
#include "sprite.h"
#include "renderer.h"
#include "texture.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define NUM_VERTEX 4	//�K�v�Ȓ��_�̐�


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11Buffer				*g_VertexBuffer = NULL;	// ���_���
static ID3D11Buffer				*g_VertexBufferTriangle = NULL;		// �O�p���_���



//=============================================================================
// ����������
//=============================================================================
void InitSprite(void)
{
	ID3D11Device *pDevice = GetDevice();

	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * NUM_VERTEX;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	pDevice->CreateBuffer(&bd, NULL, &g_VertexBuffer);
}

//=============================================================================
// �I������
//=============================================================================
void UninitSprite(void)
{
	// ���_�o�b�t�@�̉��
	if (g_VertexBuffer)
	{
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}
}

//=============================================================================
// �X�v���C�g�f�[�^�ݒ�
// ���W�E�T�C�Y�EUV�w��
//=============================================================================
// texNo		:�e�N�X�`���̎��ʎq�itexture.cpp��LoadTexture�֐��̖߂�l�j
// X			:X���W�i��`�̒��S��j
// Y			:Y���W�i��`�̒��S��j
// Width		:����
// Height		:����
// U			:UV�l�̎n�_
// V			:UV�l�̎n�_
// UW			:UV�l�̉���
// VH			:UV�l�̍���
void DrawSprite(int texNo, float X, float Y, float Width, float Height, float U, float V, float UW, float VH)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;

	float hw, hh;
	hw = Width * 0.5f;
	hh = Height * 0.5f;

	// ���_�O�ԁi����̒��_�j
	vertex[0].Position = D3DXVECTOR3(X - hw, Y - hh, 0.0f);
	vertex[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(U, V);

	// ���_�P�ԁi�E��̒��_�j
	vertex[1].Position = D3DXVECTOR3(X + hw, Y - hh, 0.0f);
	vertex[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(U + UW, V);

	// ���_�Q�ԁi�����̒��_�j
	vertex[2].Position = D3DXVECTOR3(X - hw, Y + hh, 0.0f);
	vertex[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(U, V + VH);

	// ���_�R�ԁi�E���̒��_�j
	vertex[3].Position = D3DXVECTOR3(X + hw, Y + hh, 0.0f);
	vertex[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(U + UW, V + VH);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(texNo));

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_VERTEX, 0);
}

//=============================================================================
// �X�v���C�g�f�[�^�ݒ�i����w��j
// ���W�E�T�C�Y�EUV�w��
//=============================================================================
// texNo		:�e�N�X�`���̎��ʎq�itexture.cpp��LoadTexture�֐��̖߂�l�j
// X			:X���W�i��`�̍����j
// Y			:Y���W�i��`�̍����j
// Width		:����
// Height		:����
// U			:UV�l�̎n�_
// V			:UV�l�̎n�_
// UW			:UV�l�̉���
// VH			:UV�l�̍���
void DrawSpriteLeftTop(int texNo, float X, float Y, float Width, float Height, float U, float V, float UW, float VH)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;

	// ��������_�Ƃ��Đݒ肷��v���O����
	vertex[0].Position = D3DXVECTOR3(X, Y, 0.0f);
	vertex[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(U, V);

	vertex[1].Position = D3DXVECTOR3(X + Width, Y, 0.0f);
	vertex[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(U + UW, V);

	vertex[2].Position = D3DXVECTOR3(X, Y + Height, 0.0f);
	vertex[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(U, V + VH);

	vertex[3].Position = D3DXVECTOR3(X + Width, Y + Height, 0.0f);
	vertex[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(U + UW, V + VH);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(texNo));

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_VERTEX, 0);
}


//=============================================================================
// �X�v���C�g�f�[�^�ݒ�
// ���W�E�T�C�Y�EUV�w��E���_�F
//=============================================================================
// texNo		:�e�N�X�`���̎��ʎq�itexture.cpp��LoadTexture�֐��̖߂�l�j
// X			:X���W�i��`�̒��S��j
// Y			:Y���W�i��`�̒��S��j
// Width		:����
// Height		:����
// U			:UV�l�̎n�_
// V			:UV�l�̎n�_
// UW			:UV�l�̉���
// VH			:UV�l�̍���
// color		:�e���_�̐F�iRGBA�j
void DrawSpriteColor(int texNo, float X, float Y, float Width, float Height,
		float U, float V, float UW, float VH,
		D3DXCOLOR color)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;

	float hw, hh;
	hw = Width * 0.5f;
	hh = Height * 0.5f;

	// ���_�O�ԁi����̒��_�j
	vertex[0].Position = D3DXVECTOR3(X - hw, Y - hh, 0.0f);
	vertex[0].Diffuse = color;
	vertex[0].TexCoord = D3DXVECTOR2(U, V);

	// ���_�P�ԁi�E��̒��_�j
	vertex[1].Position = D3DXVECTOR3(X + hw, Y - hh, 0.0f);
	vertex[1].Diffuse = color;
	vertex[1].TexCoord = D3DXVECTOR2(U + UW, V);

	// ���_�Q�ԁi�����̒��_�j
	vertex[2].Position = D3DXVECTOR3(X - hw, Y + hh, 0.0f);
	vertex[2].Diffuse = color;
	vertex[2].TexCoord = D3DXVECTOR2(U, V + VH);

	// ���_�R�ԁi�E���̒��_�j
	vertex[3].Position = D3DXVECTOR3(X + hw, Y + hh, 0.0f);
	vertex[3].Diffuse = color;
	vertex[3].TexCoord = D3DXVECTOR2(U + UW, V + VH);

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(texNo));

	// �|���S���`��
	GetDeviceContext()->Draw(NUM_VERTEX, 0);
}


//=============================================================================
// �X�v���C�g�f�[�^�ݒ�
// ���W�E�T�C�Y�EUV�w��E���_�F�E��]�p�x
//=============================================================================
// texNo		:�e�N�X�`���̎��ʎq�itexture.cpp��LoadTexture�֐��̖߂�l�j
// X			:X���W�i��`�̒��S��j
// Y			:Y���W�i��`�̒��S��j
// Width		:����
// Height		:����
// U			:UV�l�̎n�_
// V			:UV�l�̎n�_
// UW			:UV�l�̉���
// VH			:UV�l�̍���
// color		:�e���_�̐F�iRGBA�j
// Rot			:��]�p�x�i���W�A���Ŏw��j
void DrawSpriteColorRotation(float PosX, float PosY, int Size_W, int Size_H,
	float Kakudo, D3DXCOLOR col,
	float PaternNo, float uv_w, float uv_h, int NumPatern)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	//���_�o�b�t�@�ւ̏������݋������炤
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
	//���_�\���̂̌^�Ƀ|�C���^�[�^��ϊ�������
	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;

	static	float offset = 0.0f;
	//���_ V0���Z�b�g
	vertex[0].Position = D3DXVECTOR3(-Size_W / 2, -Size_H / 2, 0.0f);
	vertex[0].Diffuse = col;
	vertex[0].TexCoord = D3DXVECTOR2(0.0f + offset, 0.0f);
	//���_ V1���Z�b�g
	vertex[1].Position = D3DXVECTOR3(+Size_W / 2, -Size_H / 2, 0.0f);
	vertex[1].Diffuse = col;
	vertex[1].TexCoord = D3DXVECTOR2(1.0f + offset, 0.0f);
	//���_ V2���Z�b�g
	vertex[2].Position = D3DXVECTOR3(-Size_W / 2, +Size_H / 2, 0.0f);
	vertex[2].Diffuse = col;
	vertex[2].TexCoord = D3DXVECTOR2(0.0f + offset, 1.0);
	//���_ V3���Z�b�g
	vertex[3].Position = D3DXVECTOR3(+Size_W / 2, +Size_H / 2, 0.0f);
	vertex[3].Diffuse = col;
	vertex[3].TexCoord = D3DXVECTOR2(1.0f + offset, 1.0f);
	//	offset += 1.0f / 60.0f;

	//UV�A�j���[�V����
	//�{���͈����Ŏw�肷��p�����[�^�[
	//static	float	PaternNo = 0;	//�p�^�[���ԍ�
	//float	uv_w = 0.5f;			//���T�C�Y
	//float	uv_h = 0.5f;			//�c�T�C�Y
	//int		NumPatern = 2;			//������

	//UV���W�̌v�Z
	int no = PaternNo;	//�p�^�[���ԍ��𐮐��l�ɂ��� �����_�ȉ����̂Ă�
	float	u = (no % NumPatern) * uv_w;
	float	v = (no / NumPatern) * uv_h;

	//UV���W�̏�������
	vertex[0].TexCoord = D3DXVECTOR2(u, v);				//LEFT-TOP
	vertex[1].TexCoord = D3DXVECTOR2(u + uv_w, v);		//RIGHT-TOP
	vertex[2].TexCoord = D3DXVECTOR2(u, v + uv_h);		//LEFT-BOTTOM
	vertex[3].TexCoord = D3DXVECTOR2(u + uv_w, v + uv_h);	//RIGHT-BOTTOM

	//PaternNo += 0.005f;
	//if (PaternNo >= 4.0f) { PaternNo -= 4.0f; }

	//�x�����W�A���֕ϊ�����
	float	rad = D3DXToRadian(Kakudo);
	float	x, y;

	for (int i = 0; i < 4; i++)
	{

		//���@�藝		
		x = vertex[i].Position.x * cosf(rad) - vertex[i].Position.y * sinf(rad);
		y = vertex[i].Position.y * cosf(rad) + vertex[i].Position.x * sinf(rad);

		vertex[i].Position.x = x + PosX;	//���s�ړ��i���S�����炷�j
		vertex[i].Position.y = y + PosY;
	}

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);//�������ݏI��



	//�`��ݒ�
	{
		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);
		// �v���~�e�B�u�g�|���W�ݒ�
		GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	}
	//�e�N�X�`���̐ݒ�


	// �|���S���`��
	GetDeviceContext()->Draw(NUM_VERTEX, 0);

}
