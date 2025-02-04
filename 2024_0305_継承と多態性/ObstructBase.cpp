#include "ObstructBase.h"

ObstructBase::ObstructBase(const char* path):
	pos_(VGet(0, 0, 0)),
	modelHandle_(-1)
{
	// ３Ｄモデルの読み込み
	modelHandle_ = MV1LoadModel(path);
	if (modelHandle_ < 0)
	{
		printfDx("ObstructStatic:データ読み込みに失敗");
	}

}

ObstructBase::~ObstructBase()
{
	// モデルのアンロード.
	MV1DeleteModel(GetModelHandle());
}

void ObstructBase::Draw()
{
	// ３Ｄモデルの描画
	MV1DrawModel(modelHandle_);
}
