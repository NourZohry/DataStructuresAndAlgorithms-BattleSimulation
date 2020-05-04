#include"Fighter.h"
#include"Castle/Castle.h"
Fighter::Fighter(int id, int arrTime,int p, int S, int rP,double h):Enemy(id,arrTime)
{
	setPower(p);
	setspeed(S);
	setreloadPeriod(rP);
	setType(FIGHTER);// maloosh lazma nazwd function hya ama ya construct hay7oot el type el sa7 (function fe Enemy base class bs)
	SetStatus(INAC);//3ashan am ay enemy ya construct yat7t fe el inactive w na8yro ba3daan ama el time step btaa3o ygy
	//arr[actual_count++] = new Fighter(id,arrTime,d,p,S,rP);
	setCurrent_Health(h);
	Health = h;

	
}
void Fighter::setCastlePtr(Castle* ptr)
{
	c_ptr = ptr;
}
Castle* Fighter::getCastlePtr()
{
	return c_ptr;
}
void Fighter::Move()
{
	int s=Speed;
	if (GetStatus() == ACTV && current_health==0.5*Health)
	{
		s = Speed/2;

	}
	if(GetStatus() == ACTV && Distance <= MaxDistance)
	{ 
		if(s==Speed/2)
		{
			for (int i = 0; i < Speed; i++) //loop would most likely be removed
			{
				//Sleep(200);
				DecrementDist();
			}
		}
		else
		{
			for (int i = 0; i < s; i++)
			{
				//Sleep(100);
				DecrementDist();
			}
		}
	}
}
void Fighter::Act()
{
	
	if (R != RELOADING && GetStatus()== ACTV)
	{
		int k;
		if (current_health < 0.5*Health)
			k = 0.5;
		else
			k = 1;
		double DFC = ( ( (k*power) / Distance) *3);
		//int DFC = ((k*power)); //for testing
		c_ptr->decHealth(DFC);

		
		//fighters should decrement the castle`s health according to the formula given in the PDF.
		//How to get the castle health?
		//castle has a default constructor 
		//cant complete fighter act or freezer untill castle has some funciton and memebrs defined for it
	}
}
void Fighter::Activate(int t)
{
	if (ArrvTime == t )
		SetStatus(ACTV);
}
//ENMY_TYPE Fighter::getType()
//{
//	return fighter;
//}
int Fighter::calculatePriority()
{
	double statconst = 1;
	if (GetStatus() == FROZEN)
	{
		statconst = 0.5;

	}
	return ((getPower() / GetDistance())* getCurrnet_Health())*statconst;
}
