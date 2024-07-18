//-----------------------------------------------------------------------------
// @brief  メイン処理.
// 2016 Takeru Yui All Rights Reserved.
//-----------------------------------------------------------------------------
#include "Common.h"
#include "Player.h"
#include "Enemy.h"
#include "Obj3D.h"
#include "Camera.h"
#include "BackGround2D.h"
#include "FrontGround2D.h"

#include <vector>

// WinMain関数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	// 画面モードの設定
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 16);		// 解像度を640*480、colorを16bitに設定.
	ChangeWindowMode(TRUE);			// ウインドウモードに.
	
	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		return -1;
	}

	// グラフィックの描画先を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);

	// ZBufferとは
	SetUseZBufferFlag(TRUE);		// Ｚバッファを使用する
	SetUseBackCulling(TRUE);		// バックカリングを行う
	SetWriteZBufferFlag(TRUE);		// Ｚバッファへの書き込みを行う

	// プレイヤー初期化
	Player player;
	InitPlayer(player);

	// エネミー初期化.
	Enemy enemy;
	InitEnemy(enemy);

	Obj3D* obj = new Obj3D();
	obj->Load();

	Camera* camera = new Camera();

	BackGround2D* bg01 = new BackGround2D();
	FrontGround2D* bg02 = new FrontGround2D();



	//////////////////////
	// ベクトル計算のテスト.
	Vector v1, v2, v3;
	v1.x = 0;
	v1.y = 1;
	v2.x = 2;
	v2.y = 3;
	v3 = AddVector(v1, v2);
	printfDx("x:%f y:%f\n", v3.x, v3.y);
	v3 = SubVector(v1, v2);
	printfDx("x:%f y:%f\n", v3.x, v3.y);
	printfDx("len:%f\n", GetVectorLength(v3));
	v3 = NormalizeVector(v3);
	printfDx("x:%f y:%f\n", v3.x, v3.y);
	//////////////////////




	// ゲームループ.
	while (1)
	{
		// 画面を初期化(真っ黒にする)
		ClearDrawScreen();

		bg01->Update();
		bg02->Update();
		camera->Update(*obj);
		obj->Update();
		UpdatePlayer(player);
		UpdateEnemy(enemy, player);

		SetWriteZBufferFlag(FALSE);		// Ｚバッファへの書き込みをしない
		bg01->Draw();
		SetWriteZBufferFlag(TRUE);		// Ｚバッファへの書き込みをしない
		obj->Draw();
		SetWriteZBufferFlag(FALSE);		// Ｚバッファへの書き込みをしない
		DrawPlayer(player);
		DrawEnemy(enemy);
		bg02->Draw();


		// 裏画面の内容を表画面にコピーする（描画の確定）.
		ScreenFlip();

		// Windows 特有の面倒な処理をＤＸライブラリにやらせる
		// マイナスの値（エラー値）が返ってきたらループを抜ける
		if (ProcessMessage() < 0)
		{
			break;
		}
		// もしＥＳＣキーが押されていたらループから抜ける
		else if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}
	}

	delete(bg01);
	delete(bg02);
	delete(obj);
	delete(camera);

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;					// ソフトの終了
}