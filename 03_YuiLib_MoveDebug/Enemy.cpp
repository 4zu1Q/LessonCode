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
	physics->Entry(this);	// �������Ɏ��g��o�^

	// �v���C���[�̃O���t�B�b�N���������Ƀ��[�h���\�����W��������
	m_handle = LoadGraph("data/texture/enemy.png");

	// ���������̏�����
	m_rigidbody.Initialize();
	m_rigidbody.SetPos(VGet(300, 200, 0));

	m_tag = Tag::kEnemy;
}

void Enemy::Finalize(YuiLib::Physics* physics)
{
	physics->Exit(this);	// �������o�^����
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
	std::string message = "�G��";
	if (tag == Collidable::Tag::kEnemy)
	{
		message += "�G";
	}
	else if (tag == Collidable::Tag::kPlayer)
	{
		message += "�v���C���[";
	}
	message += "�Ɠ�������\n";

	printfDx(message.c_str());

}


