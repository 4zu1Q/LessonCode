// 2024 Takeru Yui All Rights Reserved.
#include <cassert>
#include "DxLib.h"
#include "YuiLib.h"
#include <cmath>

using namespace YuiLib;

/// <summary>
/// 衝突物の登録
/// </summary>
void Physics::Entry(Collidable* collidable)
{
	// 登録
	bool found = (std::find(collidables.begin(), collidables.end(), collidable) != collidables.end());
	if (!found)
	{
		collidables.emplace_back(collidable);
		//collidables.push_back(collidable);
	}
	// 既に登録されてたらエラー
	else
	{
		assert(0 && "指定のcollidableは登録済です。");
	}
}

/// <summary>
/// 衝突物の登録解除
/// </summary>
void Physics::Exit(Collidable* collidable)
{
	//// 登録解除(erace)
	//for (std::list<Collidable*>::const_iterator iterator = collidables.begin();
	//	iterator != collidables.end();
	//	++iterator)
	//{
	//	if ((*iterator) == collidable)
	//	{
	//		collidables.erase(iterator);
	//		break;
	//	}
	//}
	// 登録解除(remove)
	bool found = (std::find(collidables.begin(), collidables.end(), collidable) != collidables.end());
	if (found)
	{
		collidables.remove(collidable);
	}
	// 登録されてなかったらエラー
	else
	{
		assert(0 && "指定のcollidableが登録されていません。");
	}
}

/// <summary>
/// 更新（登録オブジェクトの物理移動、衝突通知）
/// </summary>
void Physics::Update()
{
	//移動
	for (auto item : collidables)
	{
		// 移動
		// ポジションに移動力を足す
		auto pos = item->m_rigidbody.GetPos();
		auto nextPos = VAdd(pos, item->m_rigidbody.GetVelocity());

		// デバッグ表示
#if _DEBUG
		DebugDraw::DrawLine(pos, nextPos, 0xff00ff);
		DebugDraw::DrawCircle(pos, item->m_radius, 0xff00ff);
#endif


		item->m_rigidbody.SetPos(nextPos);
	}

	bool isDoCheck = true;
	int checkCount = 0;

	while (isDoCheck)
	{
		isDoCheck = false;
		checkCount++;
		//衝突情報の更新と通知
//2重ループで全オブジェクトに当たり判定
//重いので近いオブジェクトのみに当たり判定を行う
		for (auto obj1 : collidables)
		{
			for (auto obj2 : collidables)
			{
				//obj1とobj2が同じではない場合
				if (obj1 != obj2)
				{
					//obj2のタグがkEnemyでobj1のタグがkPlayerだった場合
					if (obj2->m_tag == Collidable::Tag::kEnemy && obj1->m_tag == Collidable::Tag::kPlayer)
					{
						//円の当たり判定
						bool isHit = false;

						//始点と終点のベクトル
						VECTOR toEnemy = VSub(obj2->m_rigidbody.GetPos(), obj1->m_rigidbody.GetPos());

						//ベクトルのサイズをfloatで取得
						float length = VSize(toEnemy);

						//プレイヤーとエネミーの半径の合計
						float Rlength = obj1->m_radius + obj2->m_radius;

						//始点と終点の長さよりプレイヤーとエネミーの合計の長さの方が大きかった場合
						if (Rlength >= length)
						{
							isHit = true;
						}
						else isHit = false;

						DrawFormatString(100, 100, GetColor(255, 255, 255), "Rlen:%f:::len:%f", Rlength, length);



						//当たった場合
						if (isHit)
						{

							//移動変数
							VECTOR moveVec;

							//プレイヤーとエネミーの座標を引く
							moveVec = VSub(obj1->m_rigidbody.GetPos(), obj2->m_rigidbody.GetPos());

							//始点と終点の長さが0.0fより大きかった場合
							if (length > 0.0f)
							{
								//斜めも同じ距離になるよう正規化する
								moveVec = VNorm(moveVec);
							}

							//始点と終点の長さとプレイヤーとエネミーの合計の差を移動ベクトルで掛ける
							moveVec = VScale(moveVec, length - Rlength);

							//エネミーの座標に移動ベクトルを足してやる
							obj2->m_rigidbody.SetPos(VAdd(obj2->m_rigidbody.GetPos(), moveVec));

							//当たった場合にプレイヤーとエネミーのOnCollideの関数を呼ぶ
							obj1->OnCollide(Collidable::Tag::kEnemy);
							obj2->OnCollide(Collidable::Tag::kPlayer);
						}
						break;


					}
				}

			}
			if (isDoCheck)
			{
				break;
			}


		}

		if (checkCount > 1000 && isDoCheck)
		{
			printfDx("当たり判定の繰り返しチェックが規定数を超えた\n");
			break;
		}

	}

}
