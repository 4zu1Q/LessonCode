#pragma once
#include "YuiLib.h"

namespace YuiLib 
{
	class ColliderDataBase
	{
	public:
		enum class Kind : int
		{
			Circle2D,		//�~
			Line2D,		//���C��

		};

		//�R���X�g���N�^
		ColliderDataBase(Kind kind) { this->kind = kind; }

		//�����蔻���ʎ擾
		Kind GetKind() const { return kind; }		

	private:
		Kind kind;


	};

}


