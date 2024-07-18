#pragma once
#include "YuiLib.h"

namespace YuiLib 
{
	class ColliderDataBase
	{
	public:
		enum class Kind : int
		{
			Circle2D,		//円
			Line2D,		//ライン

		};

		//コンストラクタ
		ColliderDataBase(Kind kind) { this->kind = kind; }

		//当たり判定種別取得
		Kind GetKind() const { return kind; }		

	private:
		Kind kind;


	};

}


