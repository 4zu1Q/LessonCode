#pragma once
#include "DxLib.h"

class BackGround2D
{
public:
	BackGround2D();
	virtual ~BackGround2D();

	void Init();
	void Update();
	void Draw();

	// �|�W�V������getter/setter.
	const VECTOR& GetPos() const { return m_pos; }
	void SetPos(const VECTOR set) { m_pos = set; }

private:

	int m_handle;
	VECTOR m_pos;
};

