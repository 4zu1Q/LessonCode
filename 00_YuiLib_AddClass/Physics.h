// 2024 Takeru Yui All Rights Reserved.
#pragma once
#include <list>


namespace YuiLib{

class Collidable;
class Rigidbody;

/// <summary>
/// 物理をつかさどる
/// </summary>
	class Physics final
	{
	public:
		// 衝突物の登録・登録解除
		void Entry( Collidable* collidable);
		void Exit( Collidable* collidable);

		void Update();	// 更新
	
	private:
		std::list<Collidable*> m_pCollidables;	//登録された


	};

}
