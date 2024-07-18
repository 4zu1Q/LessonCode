// 2024 Takeru Yui All Rights Reserved.
#pragma once

namespace YuiLib {

/// <summary>
/// 物理、衝突判定に必要なデータの塊
/// </summary>
	class Rigidbody
	{
	public:
	
		void Init();

		//Getter
		void GetPos(VECTOR& pos) { pos = m_pos; }
		void GetDir(VECTOR& dir) { dir = m_dir; }
		void GetVelocity(VECTOR& velocity) { velocity = m_velocity; }


		//Setter
		VECTOR SetPos(VECTOR& pos) { m_pos = pos; }
		VECTOR SetVelocity(VECTOR& velocity) { m_velocity = velocity; }

	private:
		VECTOR	m_pos;
		VECTOR	m_dir;
		VECTOR	m_velocity;
	};

}
