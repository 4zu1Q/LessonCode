#pragma once

class Physics;
class Collidable;

/// <summary>
/// プレイヤークラス。物理・衝突判定をするため、Collidableを継承
/// </summary>
class Player : public YuiLib::Collidable
{
public:
	Player();
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