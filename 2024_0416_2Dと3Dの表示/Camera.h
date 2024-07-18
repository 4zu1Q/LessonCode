#pragma once
#include "DxLib.h"

class Obj3D;

class Camera
{
public:
	Camera();							// コンストラクタ.
	~Camera();							// デストラクタ.

	void Update(const Obj3D& obj);	// 更新.

	// ポジションのgetter/setter.
	const VECTOR& GetPos() const { return m_pos; }

private:
	VECTOR	m_pos;			// ポジション.
	float m_frame;
	bool m_isFlag;
};

