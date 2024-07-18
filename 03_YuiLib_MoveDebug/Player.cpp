// 2024 Takeru Yui All Rights Reserved.
#include "DxLib.h"
#include "Screen.h"
#include "YuiLib.h"
#include "Player.h"

#include <string>

/// <summary>
/// コンストラクタ
/// </summary>
Player::Player() :
	m_handle(-1),
	m_speed(0)
{
	m_radius = 20;
	// 処理なし
}

/// <summary>
/// 初期化
/// </summary>
void Player::Initialize(YuiLib::Physics* physics)
{
	physics->Entry(this);	// 物理情報に自身を登録

	// プレイヤーのグラフィックをメモリにロード＆表示座標を初期化
	m_handle = LoadGraph("data/texture/player.png");

	// 物理挙動の初期化
	m_rigidbody.Initialize();
	m_rigidbody.SetPos(VGet(288, 400, 0));
	m_speed = 3;
	m_tag = Tag::kPlayer;
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
void Player::Update()
{
	// 矢印キーを押していたらプレイヤーを移動させる
	// 向きを決定する.
	VECTOR dir = VGet(0, 0, 0);
	dir.x = 0;
	dir.y = 0;
	if (CheckHitKey(KEY_INPUT_UP) == 1)
	{
		dir.y = -1;
	}
	if (CheckHitKey(KEY_INPUT_DOWN) == 1)
	{
		dir.y = 1;
	}
	if (CheckHitKey(KEY_INPUT_LEFT) == 1)
	{
		dir.x = -1;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
	{
		dir.x = 1;
	}

	// 余計な数値が入るので、純粋に長さ１の向きとして正規化する
	if (VSquareSize(dir) > 0)
	{
		dir = VNorm(dir);
	}

	// 向きにスピードをかけて、移動力に変更する
	m_rigidbody.SetVelocity(VScale(dir, m_speed));

	////////////////////////////////////
	// ここはPhysicsの範囲！
	////////////////////////////////////
	//// ポジションに移動力を足す.
	//rigidbody.GetPos() = VAdd(rigidbody.GetPos(), rigidbody.velocity);

	//// プレイヤーが画面端からはみ出そうになっていたら画面内の座標に戻してあげる
	//if (rigidbody.GetPos().x < 0)
	//{
	//	rigidbody.GetPos().x = 0;
	//}
	//if (rigidbody.GetPos().x > SCREEN_WIDTH - w)
	//{
	//	rigidbody.GetPos().x = static_cast<float>(SCREEN_WIDTH - w);
	//}
	//if (rigidbody.GetPos().y < 0)
	//{
	//	rigidbody.GetPos().y = 0;
	//}
	//if (rigidbody.GetPos().y > static_cast<float>(SCREEN_HEIGHT - h))
	//{
	//	rigidbody.GetPos().y = static_cast<float>(SCREEN_HEIGHT - h);
	//}
	////////////////////////////////////
}

/// <summary>
/// 描画
/// </summary>
void Player::Draw()
{

	DrawRotaGraph(
		static_cast<int>(m_rigidbody.GetPos().x),
		static_cast<int>(m_rigidbody.GetPos().y),
		1.0f,
		0,
		m_handle,
		TRUE);

	//YuiLib::Collidable::DrawCol();

}

/// <summary>
/// 衝突したとき
/// </summary>
void Player::OnCollide(Tag tag)
{
	std::string message = "プレイヤーが";
	if (tag == Collidable::Tag::kPlayer)
	{
		message += "プレイヤー";
	}
	else if (tag == Collidable::Tag::kEnemy)
	{
		message += "敵";
	}
	message += "と当たった\n";

	printfDx(message.c_str());
}


