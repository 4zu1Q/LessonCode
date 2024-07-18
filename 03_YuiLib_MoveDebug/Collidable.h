// 2024 Takeru Yui All Rights Reserved.
#pragma once

namespace YuiLib {

	class Rigidbody;
	class Physics;

	/// <summary>
	/// 衝突できるもの。物理・衝突判定をする場合はこれを継承させる
	/// </summary>
	class Collidable abstract
	{
	public:
		enum class Tag
		{
			kPlayer,
			kEnemy
		};

		virtual void OnCollide(Tag tag) abstract;	// 衝突したとき
		virtual void DrawCol();

	protected:
		Rigidbody m_rigidbody;

		float m_radius;


		Tag m_tag;
	private:

		// PhysicsがCollidableを自由に管理するためにフレンド化
		friend Physics;


	};

}

