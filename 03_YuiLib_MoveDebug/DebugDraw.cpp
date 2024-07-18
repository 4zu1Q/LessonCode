// 2024 Takeru Yui All Rights Reserved.
#include "DxLib.h"
#include <list>
#include <vector>
#include "DebugDraw.h"
using namespace YuiLib;

// ŽÀ‘Ì’è‹`
std::list<DebugDraw::LineInfo> DebugDraw::lineInfo;
std::vector<DebugDraw::CircleInfo> DebugDraw::circleInfo;

/// <summary>
/// ƒNƒŠƒA
/// </summary>
void DebugDraw::Clear()
{
	lineInfo.clear();
}

/// <summary>
/// •`‰æ
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
/// ƒ‰ƒCƒ“•`‰æ
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
/// ‰~•`‰æ
/// </summary>
void YuiLib::DebugDraw::DrawCircle(const VECTOR& center, float radius, int color)
{
	CircleInfo newInfo;
	newInfo.center = center;
	newInfo.radius = radius;
	newInfo.color = color;
	circleInfo.emplace_back(newInfo);
}
