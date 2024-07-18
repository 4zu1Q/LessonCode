// 2024 Takeru Yui All Rights Reserved.
#include "DxLib.h"
#include "Screen.h"
#include "Rigidbody.h"
#include "YuiLib.h"
//#include "GameObject.h"
#include "Player.h"

/// <summary>
/// 初期化
/// </summary>
void Player::Initialize(YuiLib::Physics* physics)
{
	physics->Entry(this);	// 物理情報に自身を登録

	m_handle = LoadGraph("data/texture/player.png");
	m_speed = 10;


	//// プレイヤーのグラフィックをメモリにロード＆表示座標を初期化
	//obj.graph = LoadGraph("data/texture/player.png");
	//obj.pos.x = 288;
	//obj.pos.y = 400;
	//speed = 10;

	//// プレイヤーの画像のサイズを得る
	//int w, h;
	//GetGraphSize(obj.graph, &w, &h);
	//obj.w = (float)w;
	//obj.h = (float)h;

	//obj.dir.x = 0;
	//obj.dir.y = 0;

}

/// <summary>
/// 終了
/// </summary>
void Player::Finalize(YuiLib::Physics* physics)
{
	physics->Exit(this);	// 物理情報登録解除
}

/// <summary>
/// 更新
/// </summary>
void Player::Update(YuiLib::Rigidbody* rigid)
{
	// 矢印キーを押していたらプレイヤーを移動させる
	// 向きを決定する.

	
	rigid->GetDir(VGet(0, 0, 0));

	if (CheckHitKey(KEY_INPUT_UP) == 1)
	{
		rigid->GetDir(VGet(0,-1,0));
	}
	if (CheckHitKey(KEY_INPUT_DOWN) == 1)
	{
		rigid->GetDir(VGet(0, 1, 0));

	}
	if (CheckHitKey(KEY_INPUT_LEFT) == 1)
	{
		rigid->GetDir(VGet(-1, 0, 0));

	}
	if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
	{
		rigid->GetDir(VGet(1, 0, 0));

	}



	
}

/// <summary>
/// 描画
/// </summary>
void Player::Draw()
{
	//DrawGraph((int)obj.pos.x, (int)obj.pos.y, m_handle, TRUE);



}

/// <summary>
/// 衝突したとき
/// </summary>
void Player::OnCollide()
{
}

