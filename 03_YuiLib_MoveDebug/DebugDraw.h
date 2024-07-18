// 2024 Takeru Yui All Rights Reserved.
#pragma once
#include <vector>

namespace YuiLib {

/// <summary>
/// �f�o�b�O�p�̕`������܂Ƃ߁A��ŕ\�����邽�߂̃N���X
/// </summary>
class DebugDraw
{
public:
	static void Clear();
	static void Draw();

	// ���C���`��
	static void DrawLine(const VECTOR& start, const VECTOR& end, int color);

	//�T�[�N���`��
	static void DrawCircle(const VECTOR& center, float radius, int color);

private:
	// ���C�����
	struct LineInfo
	{
		VECTOR start;
		VECTOR end;
		int color;
	};

	// �T�[�N�����
	struct CircleInfo
	{
		VECTOR	center;
		float	radius;
		int		color;
	};

	static std::list<LineInfo> lineInfo;
	static std::vector<CircleInfo>	circleInfo;
};

}