#pragma once

// 当たったものの判別を行うためのタグ
// FIXME: ゲームによって変わる定数群をライブラリ側に持たせるのは良くない。string等にしてゲーム側で定数を。
enum class Tag
{
	Player,		// プレイヤー
	Enemy		// 敵
};