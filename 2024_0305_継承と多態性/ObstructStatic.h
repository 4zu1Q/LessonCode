//-----------------------------------------------------------------------------
// @brief  障害物：動かない.
// 2016 Takeru Yui All Rights Reserved.
//-----------------------------------------------------------------------------
#ifndef _OBSTRUCT_STATIC_H_
#define _OBSTRUCT_STATIC_H_

#include "DxLib.h"
#include "ObstructBase.h"

class ObstructStatic : public ObstructBase
{
public:
	ObstructStatic();				// コンストラクタ.
	virtual ~ObstructStatic();		// デストラクタ.

	void Update();					// 更新.
    void Draw();					// 描画.

};

#endif // _OBSTACLE_BASE_H_

