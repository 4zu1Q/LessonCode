//-----------------------------------------------------------------------------
// @brief  プレイヤークラス.
// 2016 Takeru Yui All Rights Reserved.
//-----------------------------------------------------------------------------
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "DxLib.h"

class Player final
{
public:
	Player();				// コンストラクタ.
	~Player();				// デストラクタ.

	void Update();			// 更新.
	void Draw();			// 描画.

	// モデルハンドルの取得.
	int GetModelHandle(){ return modelHandle_; }

	// ポジションのgetter/setter.
	const VECTOR& GetPos() const { return pos_; }
	void SetPos(const VECTOR set) { pos_ = set; }

private:
	int		modelHandle_;	// モデルハンドル.
	VECTOR	pos_;			// ポジション.

};

#endif // _PLAYER_H_