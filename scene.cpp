////==================================================
////シーン処理(.cpp)
////
////制作日2022/10/25			製作者:太田 飛鳥
////最終更新日2022/10/25
////==================================================
//
////include処理
//#include "scene.h"
//#include "title.h"
////#include "game.h"
////#include "result.h"
//
////グローバル関数
//static int g_Scene;		//シーン制御
//static int g_SceneNext;	//遷移先のシーン
//
////初期化処理
//void InitScene(void)
//{
//	//初期シーンとしてタイトル画面をセット
//	g_Scene = g_SceneNext = SCENE_NONE;
//	SetScene(SCENE_TITLE);
//
//	//return S_OK;
//}
//
////終了処理
//void UninitScene(void)
//{
//	//多分必要なし
//}
//
////更新処理
//void UpdateScene(void)
//{
//	//現在動作しているシーンを更新する
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
////描画処理
//void DrawScene(void)
//{
//	//現在動作しているシーンを描画する
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
//	//現在動作しているシーンを終了させる
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
//	//現在のシーンを更新する
//	g_Scene = g_SceneNext;
//
//	//更新されたシーンを初期化する
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
////メイン関数内に内蔵
////if (g_Scene != g_SceneNext)
////{
////	//シーンの切り替えを行う
////	ChangeScene();
////}
////scene.cpp
////2 KB