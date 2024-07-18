#pragma once
#include <memory>

//struct GameObject;
class Physics;
class Collidable;
class Rigidbody;

/// <summary>
/// プレイヤークラス
/// </summary>
class Player : public YuiLib::Collidable
{
public:


	void Initialize(YuiLib::Physics* physics);
	void Finalize(YuiLib::Physics* physics);
	void Update(YuiLib::Rigidbody* rigid);
	void Draw();

	// 衝突したとき
	void OnCollide() override;

private:

	int m_handle;
	float m_speed;

	
};