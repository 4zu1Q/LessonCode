// 2024 Takeru Yui All Rights Reserved.
#include "DxLib.h"
#include "Rigidbody.h"

void YuiLib::Rigidbody::Init()
{
	m_pos = VGet(0.0f, 0.0f, 0.0f);
	m_dir = VGet(0.0f, 0.0f, 0.0f);
	m_velocity = VGet(0.0f, 0.0f, 0.0f);
}
