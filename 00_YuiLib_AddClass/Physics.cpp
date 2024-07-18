// 2024 Takeru Yui All Rights Reserved.
#include "DxLib.h"
#include "Physics.h"
#include "Collidable.h"
#include "Rigidbody.h"
#include <cassert>

using namespace YuiLib;

/// <summary>
/// 衝突物の登録
/// </summary>
void Physics::Entry( Collidable* collidable)
{

	bool isFound = (std::find(m_pCollidables.begin(), m_pCollidables.end(), collidable) != m_pCollidables.end());
	
	//登録
	if (!isFound)
	{
		m_pCollidables.emplace_back(collidable);
	}
	else	//登録されてたらエラー
	{
		assert(0);
	}
	
}

/// <summary>
/// 衝突物の登録解除
/// </summary>
void Physics::Exit( Collidable* collidable)
{
	//登録解除(remove)
	bool isFound = (std::find(m_pCollidables.begin(), m_pCollidables.end(), collidable) != m_pCollidables.end());

		if (isFound)
		{
			m_pCollidables.remove(collidable);
		}
		else	//登録されてなかったらエラー
		{
			assert(0);
		}

}

/// <summary>
/// 更新
/// </summary>
void Physics::Update()
{
	// TODO:衝突情報の更新と通知
	for (auto item : m_pCollidables)
	{
		//auto nextPos = VAdd(item->rigidbody.GetPos(), item->rigidbody.Getpos, );
		//item->rigidbody.SetPos(nextPos);

			// 余計な数値が入るので、純粋に長さ１の向きとして正規化する
		if (VSquareSize(item->rigidbody->GetDir() > 1)
		{
			rigid->GetDir() = VNorm(obj.dir);
		}

		// 向きにスピードをかけて、移動力に変更する
		VECTOR velocity = VScale(obj.dir, speed);

			// ポジションに移動力を足す.
			obj.pos = VAdd(obj.pos, velocity);


			// プレイヤーが画面端からはみ出そうになっていたら画面内の座標に戻してあげる
			if ( < 0)
			{
				obj.pos.x = 0;
			}
		if (obj.pos.x > SCREEN_WIDTH - obj.w)
		{
			obj.pos.x = SCREEN_WIDTH - obj.w;
		}
		if (obj.pos.y < 0)
		{
			obj.pos.y = 0;
		}
		if (obj.pos.y > SCREEN_HEIGHT - obj.h)
		{
			obj.pos.y = SCREEN_HEIGHT - obj.h;
		}


		item->OnCollide();
	}



}