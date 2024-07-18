#pragma once
#include "Collidable.h"

struct GameObject;
class Rigidbody;
/// <summary>
/// プレイヤークラス
/// </summary>
class Player : public YuiLib::Collidable
{
public:
	void Init();
	void Update();
	void Draw();

	void OnHit();

private:

	GameObject	obj;

	int m_handle;
	float	speed;
};