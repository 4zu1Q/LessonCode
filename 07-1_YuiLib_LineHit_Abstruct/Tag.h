﻿#pragma once

// 当たったものの判別を行うためのタグ
enum class GameObjectTag
{
	Player,		// プレイヤー
	Enemy,		// 敵
	SystemWall	// 画面端の壁
};