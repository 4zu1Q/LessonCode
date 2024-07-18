#pragma once
#include "Collidable.h"
#include <list>

class Collidable;
class Rigidbody;
class Physics
{
public:
	Physics();
	virtual ~Physics();

	void Update();
	void Draw();

	void Entry(Collidable* collidable);
	void Exit(Collidable* collidable);

private:
	std::list<Collidable*> pCollidable;



};

