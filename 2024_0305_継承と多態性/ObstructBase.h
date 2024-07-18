#pragma once
#include "DxLib.h"
#include "ObstructManager.h"

class ObstructBase 
{
public:
    ObstructBase(const char* path);				// コンストラクタ.
    virtual ~ObstructBase();		// デストラクタ.

    //virtual void Update() = 0;
    virtual void Update() abstract;
    void Draw();

    // モデルハンドルの取得.
    int GetModelHandle() { return modelHandle_; }

    // ポジションのgetter/setter.
    const VECTOR& GetPos() const { return pos_; }
    void SetPos(const VECTOR set) { pos_ = set; }

protected:
	int		modelHandle_;	// モデルハンドル.
	VECTOR	pos_;			// ポジション.
};

