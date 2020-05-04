#include"Healer.h"
Healer::Healer(int id, int arrTime, int p, int S, int rP,double h) :Enemy(id, arrTime)
{
	setPower(p);
	setspeed(S);
	setreloadPeriod(rP);
	setType(HEALER);
	SetStatus(INAC);
	//arr[actual_count++] = new Healer(id, arrTime, d, p, S, rP);
	setCurrent_Health(h);
	Health = h;
}
void Healer::sethealead(Enemy * ptr)
{
	healed = ptr;
}
Enemy* Healer::gethealed()
{
	return healed;
}
void Healer::Move()
{
	
	int s = Speed;
	if (GetStatus() == ACTV && current_health <= 0.5*Health)
	{
		s = Speed / 2;

	}
	
	if (GetStatus() == ACTV && MoveDirection == false)
	{
		if (s == Speed / 2)
		{
			for (int i = 0; i < s; i++)//loop would most likely be removed
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
		if (Distance <= MinDistance)
			MoveDirection = true;
		

	}
	else if (GetStatus() == ACTV && MoveDirection == true)
	{
		if (s == Speed / 2)
		{


			for (int i = 0; i < s; i++)
			{
				//Sleep(250);
				increment_Dist();

			}
		}
		else
		{
			for (int i = 0; i < s; i++)
			{
				//Sleep(100);
				increment_Dist();
			}
		}
		if (Distance >= MaxDistance)
			MoveDirection = false;
	}
	////for healers only:to move backward 
	//if (GetStatus() == ACTV &&(Distance<=MaxDistance && Distance!=MinDistance))
	//{
	//	if (s = Speed / 2)
	//	{
	//		for (int i = 0; i < s; i++)//loop would most likely be removed
	//		{
	//			//Sleep(250);
	//			DecrementDist();
	//		}
	//	}
	//	else
	//	{
	//		for (int i = 0; i < s; i++)
	//		{
	//			//Sleep(100);
	//			DecrementDist();
	//		}
	//	}
	//}
	//else if (GetStatus() == ACTV && (Distance >= MinDistance && Distance!=MaxDistance))
	//{
	//	if (s = Speed / 2)
	//	{

	//	
	//		for (int i = 0; i < s; i++)
	//		{
	//			Sleep(250);
	//			increment_Dist();
	//	
	//		}	
	//	}
	//	else
	//	{
	//		for (int i = 0; i < s; i++)
	//		{
	//			Sleep(100);
	//			increment_Dist();
	//		}
	//	}
	//}
}
void Healer::Act()
{
	if (R != RELOADING && GetStatus() == ACTV)
	{
		this->increment_health(healed);
	}
}
void Healer::Activate(int t)
{
	if (ArrvTime == t)
		SetStatus(ACTV);
}
// a function to move forward for the healers only
void Healer::increment_Dist()
{
//	if (Distance >=MinDistance)
//	{
//		Distance++;
//	}
	if (Distance < MaxDistance)
		Distance++;
}
bool Healer::getMoveDirection()
{
	return MoveDirection;
}