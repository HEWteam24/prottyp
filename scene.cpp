////==================================================
////�V�[������(.cpp)
////
////�����2022/10/25			�����:���c ��
////�ŏI�X�V��2022/10/25
////==================================================
//
////include����
//#include "scene.h"
//#include "title.h"
////#include "game.h"
////#include "result.h"
//
////�O���[�o���֐�
//static int g_Scene;		//�V�[������
//static int g_SceneNext;	//�J�ڐ�̃V�[��
//
////����������
//void InitScene(void)
//{
//	//�����V�[���Ƃ��ă^�C�g����ʂ��Z�b�g
//	g_Scene = g_SceneNext = SCENE_NONE;
//	SetScene(SCENE_TITLE);
//
//	//return S_OK;
//}
//
////�I������
//void UninitScene(void)
//{
//	//�����K�v�Ȃ�
//}
//
////�X�V����
//void UpdateScene(void)
//{
//	//���ݓ��삵�Ă���V�[�����X�V����
//	switch (g_Scene)
//	{
//	case SCENE_NONE:
//		break;
//	case SCENE_TITLE:
//		UpdateTitle();
//		break;
//	case SCENE_GAME:
//		//UpdateGame();
//		break;
//	case SCENE_RESULT:
//		//UpdateResult();
//		break;
//	}
//}
//
////�`�揈��
//void DrawScene(void)
//{
//	//���ݓ��삵�Ă���V�[����`�悷��
//	switch (g_Scene)
//	{
//	case SCENE_NONE:
//		break;
//	case SCENE_TITLE:
//		DrawTitle();
//		break;
//	case SCENE_GAME:
//		//DrawGame();
//		break;
//	case SCENE_RESULT:
//		//DrawResult();
//		break;
//	}
//}
//
//void SetScene(SCENE nextScene)
//{
//	g_SceneNext = nextScene;
//}
//
//void ChangeScene(void)
//{
//	//���ݓ��삵�Ă���V�[�����I��������
//	switch (g_Scene)
//	{
//	case SCENE_NONE:
//		break;
//	case SCENE_TITLE:
//		UninitTitle();
//		break;
//	case SCENE_GAME:
//		//UninitGame();
//		break;
//	case SCENE_RESULT:
//		//UninitResult();
//		break;
//	}
//
//	//���݂̃V�[�����X�V����
//	g_Scene = g_SceneNext;
//
//	//�X�V���ꂽ�V�[��������������
//	switch (g_Scene)
//	{
//	case SCENE_NONE:
//		break;
//	case SCENE_TITLE:
//		InitTitle();
//		break;
//	case SCENE_GAME:
//		//InitGame();
//		break;
//	case SCENE_RESULT:
//		//InitResult();
//		break;
//	}
//}
//
////���C���֐����ɓ���
////if (g_Scene != g_SceneNext)
////{
////	//�V�[���̐؂�ւ����s��
////	ChangeScene();
////}
////scene.cpp
////2 KB