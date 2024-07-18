#include "ObstructBase.h"

ObstructBase::ObstructBase(const char* path):
	pos_(VGet(0, 0, 0)),
	modelHandle_(-1)
{
	// �R�c���f���̓ǂݍ���
	modelHandle_ = MV1LoadModel(path);
	if (modelHandle_ < 0)
	{
		printfDx("ObstructStatic:�f�[�^�ǂݍ��݂Ɏ��s");
	}

}

ObstructBase::~ObstructBase()
{
	// ���f���̃A�����[�h.
	MV1DeleteModel(GetModelHandle());
}

void ObstructBase::Draw()
{
	// �R�c���f���̕`��
	MV1DrawModel(modelHandle_);
}
