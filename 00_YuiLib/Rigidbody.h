#pragma once
#include"DxLib.h"

class Rigidbody
{
public:

	void Init();

	
	//GetterÅESetter
	void GetPos(VECTOR pos) { pos = m_pos; }
	void GetPos(VECTOR dir) { dir = m_dir; }
	void GetPos(VECTOR velocity) { velocity = m_velocity; }

	VECTOR SetPos(VECTOR set) { set = m_pos; }
	VECTOR SetVelo(VECTOR set) { set = m_velocity; }

private:
	VECTOR m_pos;
	VECTOR m_dir;
	VECTOR m_velocity;
};

