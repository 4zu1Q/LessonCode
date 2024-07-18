#pragma once
#include "DxLib.h"
#include <vector>


class WorldSprite;
class Obj3D
{
public:
	Obj3D();
	virtual ~Obj3D();

	void Load();
	void Init();
	void Update();
	void Draw();

	// �|�W�V������getter/setter.
	const VECTOR& GetPos() const { return m_pos; }
	void SetPos(const VECTOR set) { m_pos = set; }


	// �}�b�v�`�b�v�̃T�C�Y
	static const float	ChipSize;
	static const int	ChipPixelSize;

private:
	int m_chipGraph;
	int m_modelHandle;
	VECTOR m_pos;

	WorldSprite* sprite;
};

