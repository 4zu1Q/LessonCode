#pragma once
#include "DxLib.h"
#include "ObstructManager.h"

class ObstructBase 
{
public:
    ObstructBase(const char* path);				// �R���X�g���N�^.
    virtual ~ObstructBase();		// �f�X�g���N�^.

    //virtual void Update() = 0;
    virtual void Update() abstract;
    void Draw();

    // ���f���n���h���̎擾.
    int GetModelHandle() { return modelHandle_; }

    // �|�W�V������getter/setter.
    const VECTOR& GetPos() const { return pos_; }
    void SetPos(const VECTOR set) { pos_ = set; }

protected:
	int		modelHandle_;	// ���f���n���h��.
	VECTOR	pos_;			// �|�W�V����.
};

