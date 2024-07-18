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

	// 衝突したとき
	void OnCollide(Tag tag) override;

private:
	int		m_handle;	// 画像グラフィックハンドル
	float	m_speed;			// 移動スピード
};

