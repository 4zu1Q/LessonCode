﻿#pragma once

namespace YuiLib {

/// <summary>
/// 当たり判定のデータ基底
/// </summary>
class ColliderData
{
public:
	// 当たり判定種別
	enum class Kind
	{
		Circle2D,
		Line2D
	};

	// コンストラクタ
	ColliderData(Kind kind) { this->kind = kind; }

	// 当たり判定種別取得
	Kind GetKind() const { return kind; }

private:
	Kind kind;
};

}