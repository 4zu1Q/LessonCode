// 2024 Takeru Yui All Rights Reserved.
#include "DxLib.h"
#include <list>
#include <vector>
#include "DebugDraw.h"
using namespace YuiLib;

// 実体定義
std::list<DebugDraw::LineInfo> DebugDraw::lineInfo;
std::vector<DebugDraw::CircleInfo> DebugDraw::circleInfo;

/// <summary>
/// クリア
/// </summary>
void DebugDraw::Clear()
{
	lineInfo.clear();
}

/// <summary>
/// 描画
/// </summary>
void DebugDraw::Draw()
{
	for (const auto& item : lineInfo)
	{
		DxLib::DrawLine(static_cast<int>(item.start.x),
			static_cast<int>(item.start.y),
			static_cast<int>(item.end.x),
			static_cast<int>(item.end.y),
			item.color);
	}
}

/// <summary>
/// ライン描画
/// </summary>
void DebugDraw::DrawLine(const VECTOR& start, const VECTOR& end, int color)
{
	LineInfo newInfo;
	newInfo.start = start;
	newInfo.end = end;
	newInfo.color = color;
	lineInfo.push_back(newInfo);
}

/// <summary>
/// 円描画
/// </summary>
void YuiLib::DebugDraw::DrawCircle(const VECTOR& center, float radius, int color)
{
	CircleInfo newInfo;
	newInfo.center = center;
	newInfo.radius = radius;
	newInfo.color = color;
	circleInfo.emplace_back(newInfo);
}
