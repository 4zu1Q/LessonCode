#include "DxLib.h"
#include "Screen.h"
#include "YuiLib.h"
#include "Enemy.h"

#include <string>

Enemy::Enemy():
	m_handle(-1),
	m_speed(0)
{
	m_radius = 20;
}

void Enemy::Initialize(YuiLib::Physics* physics)
{
	physics->Entry(this);	// 物理情報に自身を登録

	// プレイヤーのグラフィックをメモリにロード＆表示座標を初期化
	m_handle = LoadGraph("data/texture/enemy.png");

	// 物理挙動の初期化
	m_rigidbody.Initialize();
	m_rigidbody.SetPos(VGet(300, 200, 0));

	m_tag = Tag::kEnemy;
}

void Enemy::Finalize(YuiLib::Physics* physics)
{
	physics->Exit(this);	// 物理情報登録解除
}

void Enemy::Update()
{
}

void Enemy::Draw()
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

void Enemy::OnCollide(Tag tag)
{
	std::string message = "敵が";
	if (tag == Collidable::Tag::kEnemy)
	{
		message += "敵";
	}
	else if (tag == Collidable::Tag::kPlayer)
	{
		message += "プレイヤー";
	}
	message += "と当たった\n";

	printfDx(message.c_str());

}


