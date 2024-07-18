#include "Physics.h"
#include "Collidable.h"
#include "DxLib.h"

Physics::Physics()
{

}

Physics::~Physics()
{
}

void Physics::Update()
{
	for (auto& col : pCollidable)
	{
		col->OnHit();
	}
}

void Physics::Draw()
{
}

void Physics::Entry(Collidable* collidable)
{
	pCollidable.push_back(collidable);
	printfDx("“o˜^");

}

void Physics::Exit(Collidable* collidable)
{
	printfDx("‰ğœ");
}

