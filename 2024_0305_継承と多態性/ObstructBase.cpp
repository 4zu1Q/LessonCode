#include "ObstructBase.h"

ObstructBase::ObstructBase(const char* path):
	pos_(VGet(0, 0, 0)),
	modelHandle_(-1)
{
	// ‚R‚cƒ‚ƒfƒ‹‚Ì“Ç‚İ‚İ
	modelHandle_ = MV1LoadModel(path);
	if (modelHandle_ < 0)
	{
		printfDx("ObstructStatic:ƒf[ƒ^“Ç‚İ‚İ‚É¸”s");
	}

}

ObstructBase::~ObstructBase()
{
	// ƒ‚ƒfƒ‹‚ÌƒAƒ“ƒ[ƒh.
	MV1DeleteModel(GetModelHandle());
}

void ObstructBase::Draw()
{
	// ‚R‚cƒ‚ƒfƒ‹‚Ì•`‰æ
	MV1DrawModel(modelHandle_);
}
