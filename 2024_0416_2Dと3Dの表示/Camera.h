#pragma once
#include "DxLib.h"

class Obj3D;

class Camera
{
public:
	Camera();							// �R���X�g���N�^.
	~Camera();							// �f�X�g���N�^.

	void Update(const Obj3D& obj);	// �X�V.

	// �|�W�V������getter/setter.
	const VECTOR& GetPos() const { return m_pos; }

private:
	VECTOR	m_pos;			// �|�W�V����.
	float m_frame;
	bool m_isFlag;
};

