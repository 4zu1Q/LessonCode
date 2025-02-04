﻿// 2024 Takeru Yui All Rights Reserved.
#include <cassert>
#include "DxLib.h"
#include "YuiLib.h"
#include "Tag.h"

using namespace YuiLib;

/// <summary>
/// 衝突物の登録
/// </summary>
void Physics::Entry(Collidable* collidable)
{
	// 登録
	bool found = (std::find(collidables.begin(), collidables.end(), collidable) != collidables.end());
	if(!found)
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
	// 移動
	for (auto item : collidables)
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

	// 当たり判定チェック（nextPos指定）
	std::vector<OnCollideInfo> onCollideInfo;
	CheckColide(onCollideInfo);

	// velocity、位置補正
	for (auto item : collidables)
	{
#if _DEBUG
		// 補正後の位置をデバッグ表示
		DebugDraw::DrawLine(item->rigidbody.GetPos(), item->nextPos, 0xff00ff);
		DebugDraw::DrawCircle(item->nextPos, item->radius, 0xff00ff);
#endif
		// nextPosを更新したので、velocityもそこに移動するvelocityに修正
		VECTOR toFixedPos = VSub(item->nextPos, item->rigidbody.GetPos());
		item->rigidbody.SetVelocity(toFixedPos);

		// 位置確定
		item->rigidbody.SetPos(item->nextPos);
	}

	// 当たり通知
	for (auto item : onCollideInfo)
	{
		item.owner->OnCollide(*item.colider);
	}
}

/// <summary>
/// 当たり判定チェック
/// </summary>
void Physics::CheckColide(std::vector<OnCollideInfo>& onCollideInfo)
{
	// 衝突通知、ポジション補正
	bool	doCheck = true;
	int		checkCount = 0;	// チェック回数
	while (doCheck)
	{
		doCheck = false;
		++checkCount;

		// 2重ループで全オブジェクト当たり判定
		// FIXME: 重いので近いオブジェクト同士のみ当たり判定するなど工夫がいる
		for (auto objA : collidables)
		{
			for (auto objB : collidables)
			{
				if (objA != objB)
				{
					// collidable同士、円と円の当たり判定を行う
					auto atob = VSub(objB->nextPos, objA->nextPos);
					auto atobLength = VSize(atob);

					// お互いの距離が、それぞれの半径を足したものより小さければ当たる
					if (atobLength < objA->radius + objB->radius)
					{
						// 次目標位置修正
						// HACK: onCollideInfoを渡すの気持ちわるい…あくまでFixNextPositionなのに
						FixNextPosition(objA, objB);


						// 衝突通知
						// HACK: playerもenemyも何回も呼ばれる可能性はあるので、排他遅延処理
						bool hasPlayerInfo = false;
						bool hasEnemyInfo = false;
						for (const auto& item : onCollideInfo)
						{
							// 既に通知リストに含まれていたら呼ばない
							if (item.owner == objA)
							{
								hasPlayerInfo = true;
							}
							if (item.owner == objB)
							{
								hasEnemyInfo = true;
							}
						}

						if (!hasPlayerInfo)
						{
							onCollideInfo.push_back({ objA, objB });
						}
						if (!hasEnemyInfo)
						{
							onCollideInfo.push_back({ objB, objA });
						}

						// 一度でもヒット+補正したら衝突判定と補正やりなおし
						doCheck = true;
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

/// <summary>
/// 次位置補正
/// </summary>
void Physics::FixNextPosition( Collidable* primary, Collidable* secondary)
{
	// 衝突によるポジション補正
	auto tagA = primary->GetTag();
	auto tagB = secondary->GetTag();

	// 片方がプレイヤーならエネミーのほうを移動
	Collidable* pPrimary = nullptr;
	Collidable* pSecondary = nullptr;
	if (tagA == Collidable::Tag::Player
		&& tagB == Collidable::Tag::Enemy)
	{
		pPrimary = primary;
		pSecondary = secondary;
	}
	else if (tagB == Collidable::Tag::Player
		&& tagA == Collidable::Tag::Enemy)
	{
		pPrimary = secondary;
		pSecondary = primary;
	}


	if (pPrimary && pSecondary)
	{
		VECTOR primaryToSecondary = VSub(pSecondary->nextPos, pPrimary->nextPos);
		VECTOR primaryToSecondaryN = VNorm(primaryToSecondary);

		// HACK: 先に位置を補正してしまうと、過去が参照できない
		VECTOR oldSecondaryPos = pSecondary->nextPos;
		float  awayDist = pPrimary->radius + pSecondary->radius + 0.0001f;	// そのままだとちょうど当たる位置になるので少し余分に離す
		VECTOR primaryToNewSecondaryPos = VScale(primaryToSecondaryN, awayDist);
		VECTOR fixedPos = VAdd(pPrimary->nextPos, primaryToNewSecondaryPos);
		pSecondary->nextPos = fixedPos;




	}
}