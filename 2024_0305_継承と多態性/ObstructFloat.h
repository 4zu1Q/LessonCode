//-----------------------------------------------------------------------------
// @brief  障害物：浮遊する.
// 2016 Takeru Yui All Rights Reserved.
//-----------------------------------------------------------------------------
#ifndef _OBSTRUCT_FLOAT_H_
#define _OBSTRUCT_FLOAT_H_

#include "DxLib.h"
#include "ObstructBase.h"

class ObstructFloat : public ObstructBase
{
public:
	ObstructFloat();				// コンストラクタ.
	virtual ~ObstructFloat();		// デストラクタ.

    void Update();					// 更新.
    void Draw();					// 描画.

private:

	float rad_;						// sin移動用のラジアン関数.
};

#endif // _OBSTRUCT_FLOAT_H_

