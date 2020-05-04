#pragma once
#include"Enemies/Enemy.h"


class Healer:public Enemy
{
private:
	bool MoveDirection = 0;
	Enemy*healed;
public:
	Healer(int id, int arrTime, int p, int S, int rP,double h);
	void Move();
	void Act();
	void Activate(int t);
	void increment_Dist(); //only for healers as they move backward and forward untill their status is changed
	void sethealead(Enemy * ptr);
	Enemy* gethealed();
	bool getMoveDirection();


};
