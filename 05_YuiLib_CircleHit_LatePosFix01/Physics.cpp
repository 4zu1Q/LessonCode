// 2024 Takeru Yui All Rights Reserved.
#include <cassert>
#include "DxLib.h"
#include "YuiLib.h"

using namespace YuiLib;

/// <summary>
/// 衝突物の登録
/// </summary>
void Physics::Entry(Collidable* collidable)
{
	// 登録
	bool found = (std::find(m_pCollidables.begin(), m_pCollidables.end(), collidable) != m_pCollidables.end());
	if(!found)
	{
		m_pCollidables.emplace_back(collidable);
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
	bool found = (std::find(m_pCollidables.begin(), m_pCollidables.end(), collidable) != m_pCollidables.end());
	if (found)
	{
		m_pCollidables.remove(collidable);
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
	// 移動
	FixPosition();

	std::list<OnCollideInfo> OnColInfo;

		CheckCollide(OnColInfo);

	// 位置確定
	for (auto& item : m_pCollidables)
	{
#if _DEBUG
		// 補正後の位置をデバッグ表示
		DebugDraw::DrawLine(item->rigidbody.GetPos(), item->nextPos, 0xff00ff);
		DebugDraw::DrawCircle(item->nextPos, item->radius, 0xff00ff);
#endif
		item->rigidbody.SetPos(item->nextPos);

	}

	for (auto& item : OnColInfo)
	{
		item.m_owner->OnCollide(*item.m_colider);
	}
}

void YuiLib::Physics::CheckCollide(std::list<OnCollideInfo>& OnColInfo)
{
	// 衝突チェック、通知、ポジション補正
	bool	doCheck = true;
	int		checkCount = 0;	// チェック回数
	while (doCheck)
	{
		doCheck = false;
		++checkCount;

		// 2重ループで全オブジェクト当たり判定
		// FIXME: 重いので近いオブジェクト同士のみ当たり判定するなど工夫がいる
		for (auto& objA : m_pCollidables)
		{
			for (auto& objB : m_pCollidables)
			{
				if (objA != objB)
				{
					// collidable同士、円と円の当たり判定を行う
					auto atob = VSub(objB->nextPos, objA->nextPos);
					auto atobLength = VSize(atob);

					// お互いの距離が、それぞれの半径を足したものより小さければ当たる
					if (atobLength < objA->radius + objB->radius)
					{
						// 衝突によるポジション補正
						auto tagA = objA->GetTag();
						auto tagB = objB->GetTag();

						// 片方がプレイヤーならエネミーのほうを移動
						Collidable* player = nullptr;
						Collidable* enemy = nullptr;
						if (tagA == Collidable::Tag::kPlayer
							&& tagB == Collidable::Tag::kEnemy)
						{
							player = objA;
							enemy = objB;
						}
						else if (tagB == Collidable::Tag::kPlayer
							&& tagA == Collidable::Tag::kEnemy)
						{
							player = objB;
							enemy = objA;
						}



						if (player && enemy)
						{

							FixNextPosition(player,enemy);


							// HACK: playerもenemyも何回も呼ばれる可能性はある
							// 衝突通知
							OnColInfo.push_back({ player, enemy });
							OnColInfo.push_back({ enemy, player });



							//player->OnCollide(*enemy);
							//enemy->OnCollide(*player);


							// 一度でもヒット+補正したら衝突判定と補正やりなおし
							doCheck = true;
						}
						break;
					}
				}
			}
			if (doCheck)
			{
				break;
			}
		}

		// 無限ループ避け
		// FIXME: 定数化
		if (checkCount > 1000 && doCheck)
		{
#if _DEBUG
			printfDx("当たり判定の繰り返しチェックが規定数を超えた\n");
#endif
			break;
		}
	}
}

void YuiLib::Physics::FixNextPosition(Collidable* player, Collidable* enemy)
{
	VECTOR playerToEnemy = VSub(enemy->nextPos, player->nextPos);
	VECTOR playerToEnemyN = VNorm(playerToEnemy);

	// HACK: 先に位置を補正してしまうと、過去が参照できない
	VECTOR oldEnemyPos = enemy->nextPos;
	float  awayDist = player->radius + enemy->radius + 0.0001f;	// そのままだとちょうど当たる位置になるので少し余分に離す
	VECTOR playerToNewEnemyPos = VScale(playerToEnemyN, awayDist);
	VECTOR fixedPos = VAdd(player->nextPos, playerToNewEnemyPos);

	enemy->nextPos = fixedPos;

	// nextPosを更新したので、velocityもそこに移動するvelocityに修正
	VECTOR toFixedPos = VSub(enemy->nextPos, enemy->rigidbody.GetPos());
	enemy->rigidbody.SetVelocity(toFixedPos);

}

void YuiLib::Physics::FixPosition()
{
	for (auto& item : m_pCollidables)
	{
		// ポジションに移動力を足す
		auto pos = item->rigidbody.GetPos();
		auto nextPos = VAdd(pos, item->rigidbody.GetVelocity());

		// もともとの情報をデバッグ表示
#if _DEBUG
		DebugDraw::DrawLine(pos, nextPos, 0x0000ff);
		DebugDraw::DrawCircle(pos, item->radius, 0x0000aa);
		DebugDraw::DrawCircle(nextPos, item->radius, 0x0000ff);
#endif

		// 予定ポジション設定
		item->nextPos = nextPos;
	}
}
