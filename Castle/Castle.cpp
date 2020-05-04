
#include "Castle.h"






void Castle::SetHealth(double h)
{
	if (h > 0)
		Health = h;
	else
		Health = 0; // killed
	current_health = Health;
}
Castle::Castle()
{
	firstshot = true;
}
void Castle::startFreeze()
{
	if (Health <= 100)
	{
		Freeze = 5;
	}
	else if (Health <= 200)
	{
		Freeze = 10;
	}
	else if (Health <= 400)
	{
		Freeze = 15;
	}
	else
		Freeze = 20;
}

double Castle::GetCurrentHealth()
{
	return current_health;
}

double Castle::GetHealth() const
{
	return Health;
}
void Castle::decHealth(double D)
{
	current_health = current_health - D;
}
CASTLE_STAT Castle::getCStat()
{
	return CS;
}
void Castle::setCStat(CASTLE_STAT C)
{
	CS = C;
}
void Castle::incrementChealth()
{
	if (1.3*current_health >= Health)
	{
		return;
	}
	else
	{
		current_health = current_health * 1.3;
	}

}
void Castle::setFD(int FFDD)
{
	FD = FFDD;
}
int Castle::getFd()
{
	return FD;
}
void  Castle::Act_C(PriorityQueue<Enemy*>&aPqueue, Stack<Enemy*>&aStack, Queue<Enemy*>&aQueue,int timestep)
{


	if (CS == FROZEN)
	{
		return;
	}
	double random;
	int Count = 0;
	Enemy * tempFighter;
	Enemy  *tempheal;
	Enemy *tempfreeze;
	Queue<Enemy*>tempPqueue;
	Stack<Enemy*>tempStack;
	Queue<Enemy*>tempQueue;
	double n = 0;


	while (!aPqueue.isEmpty() && Count != MaxHits)
	{
		random = ((double)rand() / (RAND_MAX));
		aPqueue.remove(tempFighter);

		if (random < 0.2)
		{
			if (tempFighter->GetStatus() == ACTV)
			{
				tempFighter->freezeme((1.0 / tempFighter->GetDistance())*CastlePower,timestep);
				if (firstshot)
				{
					FD= timestep- tempFighter->GetArrvTime();
					firstshot = false;
				}
				Count++;
			}
		}

		else
		{ 
			if (tempFighter->GetStatus() != KILD)
			{
				n = (1.0 / tempFighter->GetDistance())*CastlePower;
				tempFighter->decHealth(n,timestep);
				if (firstshot)
				{
					FD = timestep - tempFighter->GetArrvTime();
					firstshot = false;
				}
				Count++;
			}
		}

		tempPqueue.enqueue(tempFighter);

	}

	while (!aStack.isEmpty() && Count != MaxHits)
	{
		tempheal = aStack.peek();
		random = ((double)rand() / (RAND_MAX));
		if (random < 0.2)
		{
			if (tempheal->GetStatus() == ACTV)
			{
				
				tempheal->freezeme((1.0 / tempheal->GetDistance())*CastlePower, timestep);
				if (firstshot)
				{
					FD = timestep - tempheal->GetArrvTime();
					firstshot = false;
				}
				Count++;
			}
		}
		else
		{
			if (tempheal->GetStatus() != KILD)
			{
				n = (1.0 / tempheal->GetDistance())*CastlePower;
				tempheal->decHealth(n, timestep);
				if (firstshot)
				{
					FD = timestep - tempheal->GetArrvTime();
					firstshot = false;
				}
				Count++;
			}
		}


		if (tempheal->isKilled() && tempheal->GetDistance() <= 5)
		{
			current_health = 1.03*current_health;
		}


		aStack.pop();
		tempStack.push(tempheal);

	}

	while (!aQueue.isEmpty() && Count != MaxHits)
	{
		aQueue.dequeue(tempfreeze);
		random = ((double)rand() / (RAND_MAX));
		if (random < 0.2)
		{
			if (tempfreeze->GetStatus() == ACTV)
			{
				
				tempfreeze->freezeme((1.0 / tempfreeze->GetDistance())*CastlePower, timestep);
				if (firstshot)
				{
					FD = timestep - tempfreeze->GetArrvTime();
					firstshot = false;
				}
				Count++;
			}
		}
		else
		{
			if (tempfreeze->GetStatus() != KILD)
			{
				n = (1.0 / tempfreeze->GetDistance())*CastlePower;
				
				tempfreeze->decHealth(n, timestep);
				if (firstshot)
				{
					FD = timestep - tempfreeze->GetArrvTime();
					firstshot = false;
				}
				Count++;
			}
		}

		tempQueue.enqueue(tempfreeze);
		
	}
	while (tempPqueue.isEmpty()!=true )
	{
		tempPqueue.dequeue(tempFighter);
		int priority=tempFighter->calculatePriority();
		aPqueue.add(tempFighter, priority);	
	}
	while (tempStack.isEmpty() != true)
	{
		tempheal = tempStack.peek();
		tempStack.pop();
		aStack.push(tempheal);	
	}
	while (tempQueue.isEmpty()!=true)
	{
		tempQueue.dequeue(tempfreeze);
		aQueue.enqueue(tempfreeze);
	}
	
}
void Castle::decFreeze(int f)
{
	// Freeze = 0;
	Freeze -= f;
	checkFreeze();
}
int Castle::getfreeze()
{
	return Freeze;
}


void Castle::unfreeze()
{
	if (CS == FROZEN)
	{
		CS = ACTIVE;
		if (Health<=100)
		{
			Freeze = 5;
		}
		else if (Health <= 200)
		{
			Freeze = 10;
		}
		else if (Health <= 400)
		{
			Freeze = 15;
		}
		else
			Freeze = 20;
	}
	
}





void Castle::checkFreeze()
{
	if (Freeze<=0)
		setCStat(FROZEN);
}
void Castle::incFreeze(int F)// this function will be used to increment threshhold of the castle untill it reaches a certain point call it in the act of the freezer
{
	Freeze += F;
}
void Castle::setMaxHits(int N)
{
	MaxHits = N;
}
int Castle::getMaxHits()
{
	return MaxHits;
}
void Castle::setPower(int P)
{
	CastlePower = P;
}