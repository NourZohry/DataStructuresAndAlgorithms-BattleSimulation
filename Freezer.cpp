#include"Freezer.h"
Freezer::Freezer(int id, int arrTime, int p, int S, int rP,double h) :Enemy(id, arrTime)
{
	setPower(p);
	setspeed(S);
	setreloadPeriod(rP);
	setType(FREEZER);
	SetStatus(INAC);
	//arr[actual_count++] = new Freezer(id, arrTime, d, p, S, rP);
	setCurrent_Health(h);
	Health = h;

}
void Freezer::Move()
{
	int s = Speed;
	if (GetStatus() == ACTV && current_health <= 0.5*Health)
	{
		s = Speed / 2;

	}
	if (GetStatus() == ACTV && Distance <= MaxDistance)
	{
		if(s==Speed/2)
		{
			for (int i = 0; i < s; i++) //loop would most likely be removed
			{
				//Sleep(250);
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
void Freezer::Act()
{
	if (c_ptr->getCStat() == FROZEN)
	{
		return;
	}
	if (R != RELOADING && GetStatus() == ACTV)
	{

		if (power<=2)
		{
			c_ptr->decFreeze(1);
		}
		else if (power<=4)
		{ 
			c_ptr->decFreeze(2);
		}
		else
			c_ptr->decFreeze(3);
		
	}
}
void Freezer::Activate(int t)
{
	if (ArrvTime == t)
		SetStatus(ACTV);
}

void Freezer::setCastlePtr(Castle* ptr)
{
	c_ptr = ptr;
}
Castle* Freezer::getCastlePtr()
{
	return c_ptr;
}