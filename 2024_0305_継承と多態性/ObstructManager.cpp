#include "ObstructManager.h"
#include "ObstructFloat.h"
#include "ObstructStatic.h"
#include "DxLib.h"


ObstructManager::ObstructManager():
	staticModelHandle_(-1),
	floatModelHandle_(-1)
{
	for (int i = 0; i < 3; i++)
	{
		obstructs[i] = NULL;
	}
}

ObstructManager::~ObstructManager()
{
}

void ObstructManager::CreateObject()
{
	staticModelHandle_ = MV1LoadModel("data/model/obstructStatic/obstructStatic.pmd");
	if (staticModelHandle_ < 0)
	{
		printfDx("ObstructStatic:データ読み込みに失敗");
	}

	floatModelHandle_ = MV1LoadModel("data/model/obstructFloat/obstructFloat.pmx");
	if (floatModelHandle_ < 0)
	{
		printfDx("ObstructStatic:データ読み込みに失敗");
	}

	obstructs[0] = new ObstructStatic();
	obstructs[1] = new ObstructFloat();
	obstructs[2] = new ObstructStatic();

	for (int i = 3; i < OBSTRUCT_NUM; ++i)
	{
		obstructs[i] = new ObstructStatic();
	}

	float band = 10.0f;
	for (int i = 0; i < OBSTRUCT_NUM; i++)
	{
		obstructs[i]->SetPos(VGet(band * (i - OBSTRUCT_NUM * 0.5f), 0, -1.0f));
	}
}

void ObstructManager::DestroyObject()
{
	for (int i = 0; i < OBSTRUCT_NUM; i++)
	{
		delete obstructs[i];
		obstructs[i] = nullptr;
	}
}

void ObstructManager::Update()
{
	for (int i = 0; i < OBSTRUCT_NUM; i++)
	{
		obstructs[i]->Update();
	}
}

void ObstructManager::Draw()
{
	for (int i = 0; i < OBSTRUCT_NUM; i++)
	{
		obstructs[i]->Draw();
	}
}
