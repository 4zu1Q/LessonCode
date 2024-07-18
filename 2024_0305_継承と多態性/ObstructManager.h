#pragma once

class ObstructBase;
//class ObstructStatic;
//class ObstructFloat;

// è·äQï®ÇÃêî.
#define OBSTRUCT_NUM 30

class ObstructManager
{
public:
	ObstructManager();
	~ObstructManager();

	void CreateObject();
	void DestroyObject();

	void Update();
	void Draw();



protected:

	ObstructBase* obstructs[OBSTRUCT_NUM];

	int staticModelHandle_;
	int floatModelHandle_;

};

