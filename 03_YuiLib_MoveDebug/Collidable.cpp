// 2024 Takeru Yui All Rights Reserved.
#include "DxLib.h"
#include "Rigidbody.h"
#include "Collidable.h"

void YuiLib::Collidable::DrawCol()
{
	DrawCircle(m_rigidbody.GetPos().x, m_rigidbody.GetPos().y, m_radius, 0xffffff, false);
}
