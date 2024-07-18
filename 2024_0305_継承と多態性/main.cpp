//-----------------------------------------------------------------------------
// @brief  メイン処理.
// 2016 Takeru Yui All Rights Reserved.
//-----------------------------------------------------------------------------
#include "DxLib.h"
#include "Player.h"
#include "Camera.h"
#include "ObstructStatic.h"
#include "ObstructFloat.h"
#include "ObstructManager.h"



//-----------------------------------------------------------------------------
// @brief  メイン関数.
//-----------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) 
{
	// 画面モードのセット
	SetGraphMode(640, 480, 16);
	ChangeWindowMode(TRUE);

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)		
	{
		return -1;	// エラーが起きたら直ちに終了
	}

	// カメラを生成.
	Camera* camera = new Camera();

	// プレイヤーを生成.
	Player* player = new Player();

	ObstructManager* obstructs = new ObstructManager();

	obstructs->CreateObject();


	// 障害物を生成.
	//ObstructBase* obstructs[3];
	//obstructs[0] = new ObstructStatic();
	//obstructs[1] = new ObstructFloat();
	//obstructs[2] = new ObstructStatic();

	// 障害物の位置を初期化.
	//float band = 10.0f;
	//obstructs[0]->SetPos(VGet(-band + (band * 0), 0, -1.0f));
	//obstructs[1]->SetPos(VGet(-band + (band * 1), 0, -1.0f));
	//obstructs[2]->SetPos(VGet(-band + (band * 2), 0, -1.0f));

	// エスケープキーが押されるかウインドウが閉じられるまでループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// プレイヤー制御.
		player->Update();

		// カメラ制御.
		camera->Update(*player);

		// 障害物制御.
		//obstructs[0]->Update();
		//obstructs[1]->Update();
		//obstructs[2]->Update();
		obstructs->Update();

		// 画面を初期化する
		ClearDrawScreen();

		// プレイヤー描画.
		player->Draw();

		// 障害物描画.
		//obstructs[0]->Draw();
		//obstructs[1]->Draw();
		//obstructs[2]->Draw();
		obstructs->Draw();

		// 裏画面の内容を表画面に反映させる
		ScreenFlip();
	}

	// プレイヤーを削除.
	delete(player);

	// カメラを削除.
	delete(camera);

	// 障害物を削除.
    //delete(obstructs[0]);
    //delete(obstructs[1]);
    //delete(obstructs[2]);
	obstructs->DestroyObject();

	// ＤＸライブラリの後始末
	DxLib_End();

	// ソフトの終了
	return 0;
}