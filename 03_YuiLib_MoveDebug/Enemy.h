#pragma once
class Physics;
class Collidable;

class Enemy : public YuiLib::Collidable
{
public:
	Enemy();
	void Initialize(YuiLib::Physics* physics);
	void Finalize(YuiLib::Physics* physics);
	void Update();
	void Draw();

	// �Փ˂����Ƃ�
	void OnCollide(Tag tag) override;

private:
	int		m_handle;	// �摜�O���t�B�b�N�n���h��
	float	m_speed;			// �ړ��X�s�[�h
};

