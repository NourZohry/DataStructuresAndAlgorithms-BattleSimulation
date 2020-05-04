#pragma once
#include<iostream>
#include"Enemies/Enemy.h"
class Castle; /*Circular dependency issue will occur if this line is removed check(https://stackoverflow.com/questions/23283080/compiler-error-c4430-missing-type-specifier-int-assumed)
for more info*/ //when using a castle pointer do not include the castle instead write class Castl;

class Fighter:public Enemy
{
private:
	ENMY_TYPE fighter;
	Castle *c_ptr;
	
public:
	Fighter(int id, int arrTime, int p, int S, int rP,double h);
	 void Move();
	 void Act();
	 void Activate(int t);
	 int calculatePriority();
	 void setCastlePtr(Castle* ptr);
	 Castle* getCastlePtr();
	
	 
	




};