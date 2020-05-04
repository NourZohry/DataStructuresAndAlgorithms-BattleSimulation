#pragma once
#include"Enemies/Enemy.h"
#include"Castle/Castle.h"


class Freezer:public Enemy
{
private:
	Castle *c_ptr;
public:
	Freezer(int id, int arrTime, int p, int S, int rP,double h);
	 void Move();
	 void Act();
	 void Activate(int t);

	 void setCastlePtr(Castle* ptr);
	 Castle* getCastlePtr();



};
