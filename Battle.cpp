#include "Battle.h"
#include"Fighter.h"
#include <time.h>

Battle::Battle()
{
	EnemyCount = 0;
	KilledCount = 0;
	ActiveCount = 0;
	FrostedCount = 0;
	CurrentTimeStep = 0;

	ActiveFighters = 0;
	ActiveHealers = 0;
	ActiveFreezers = 0;
	FrozenFighters = 0;
	FrozenHealers = 0;
	FrozenFreezers = 0;
	KilledFighters = 0;
	KilledFreezers = 0;
	KilledHealers = 0;

	pGUI = NULL;

	SilentModeIsOn = 0;
}


Castle * Battle::GetCastle()
{
	return &BCastle;
}


void Battle::RunSimulation()
{
	pGUI = new GUI;
	PROG_MODE	mode = pGUI->getGUIMode();

	switch (mode)	
	{
	case MODE_INTR:
	{
		InteractiveMode();
		break;
	}
	case MODE_STEP:
	{
		StepMode();
		break;
	}
	case MODE_SLNT:
	{
		SilentModeIsOn = 1;
		SilentMode();
		break;
	}
	case MODE_DEMO:
		//Just_A_Demo();
		simulation();

	}

	delete pGUI;

}

void Battle::CheckStatus(Enemy *ptr)
{
	if (ptr->getType() == FREEZER)
	{
		if (ptr->GetStatus() == FRST)
		{
			FrozenFreezers++;
			FrostedCount++;
		}
		else if (ptr->GetStatus() == ACTV)
		{
			ActiveFreezers++;
			ActiveCount++;
		}
		else if (ptr->GetStatus() == KILD)
		{
			KilledFreezers++;
			KilledCount++;
		}

	}
	else if (ptr->getType() == HEALER)
	{
		if (ptr->GetStatus() == FRST)
		{
			FrozenHealers++;
			FrostedCount++;
		}
		else if (ptr->GetStatus() == ACTV)
		{
			ActiveHealers++;
			ActiveCount++;
		}
		else if (ptr->GetStatus() == KILD)
		{
			KilledHealers++;
			KilledCount++;
		}

	}
	else if (ptr->getType() == FIGHTER)
	{
		if (ptr->GetStatus() == FRST)
		{
			FrozenFighters++;
			FrostedCount++;
		}
		else if (ptr->GetStatus() == ACTV)
		{
			ActiveFighters++;
			ActiveCount++;
		}


	}
}

void Battle::CalculateCounts()
{
	ActiveCount = 0;
	FrostedCount = 0;
	KilledCount = 0;

	ActiveFighters = 0;
	ActiveHealers = 0;
	ActiveFreezers = 0;

	FrozenFighters = 0;
	FrozenHealers = 0;
	FrozenFreezers = 0;

	KilledFighters = 0;
	KilledFreezers = 0;
	KilledHealers = 0;

	Queue<Enemy*> tempQ;
	Enemy *F;
	while (!freezersqueue.isEmpty())
	{
		freezersqueue.dequeue(F);
		tempQ.enqueue(F);
		CheckStatus(F);
	}
	while (!tempQ.isEmpty())
	{
		tempQ.dequeue(F);
		freezersqueue.enqueue(F);
	}


	Stack<Enemy*> tempS;
	Enemy*S;
	while (!healersstack.isEmpty())
	{
		S = healersstack.peek();
		healersstack.pop();
		tempS.push(S);
		CheckStatus(S);
	}
	while (!tempS.isEmpty())
	{
		S = tempS.peek();
		tempS.pop();
		healersstack.push(S);
	}

	PriorityQueue<Enemy*> tempPQ;
	Enemy *Fight;
	while (!fighterspq.isEmpty())
	{
		fighterspq.remove(Fight);
		int d = Fight->calculatePriority();
		tempPQ.add(Fight, d);
		CheckStatus(Fight);
	}
	while (!tempPQ.isEmpty())
	{
		tempPQ.remove(Fight);
		int d = Fight->calculatePriority();
		fighterspq.add(Fight, d);
	}



	Queue<Enemy*> tempK;
	Enemy *K;
	while (!KilledQueue.isEmpty())
	{
		KilledQueue.dequeue(K);
		tempK.enqueue(K);
		//KilledCount++;
		if (K->getType() == HEALER)
		{
			KilledHealers++;
			KilledCount++;
		}
		else if (K->getType() == FIGHTER)
		{
			KilledFighters++;
			KilledCount++;
		}
		else if (K->getType() == FREEZER)
		{
			KilledFreezers++;
			KilledCount++;
		}
	}
	while (!tempK.isEmpty())
	{
		tempK.dequeue(K);
		KilledQueue.enqueue(K);
	}

}


//Add enemy lists (inactive, active,.....) to drawing list to be displayed on user interface
void Battle::AddAllListsToDrawingList()
{
	//Add inactive queue to drawing list
	int InactiveCount;
	Enemy* const * EnemyList = Q_Inactive.toArray(InactiveCount);
	for (int i = 0; i < InactiveCount; i++)
		pGUI->AddToDrawingList(EnemyList[i]);

	

	Queue<Enemy*> tempQ;
	Enemy *F;
	while (!freezersqueue.isEmpty())
	{
		freezersqueue.dequeue(F);
		tempQ.enqueue(F);
		pGUI->AddToDrawingList(F);
	}
	while (!tempQ.isEmpty())
	{
		tempQ.dequeue(F);
		freezersqueue.enqueue(F);
	}

	Stack<Enemy*> tempS;
	Enemy*S;
	while (!healersstack.isEmpty())
	{
		S = healersstack.peek();
		healersstack.pop(); 
		tempS.push(S);
		pGUI->AddToDrawingList(S);
	}
	while (!tempS.isEmpty())
	{
		S = tempS.peek();
		tempS.pop();
		healersstack.push(S);
	}

	PriorityQueue<Enemy*> tempPQ;
	Enemy *Fight;
	while (!fighterspq.isEmpty())
	{
		fighterspq.remove(Fight);
		int d = Fight->calculatePriority();
		tempPQ.add(Fight, d);
		pGUI->AddToDrawingList(Fight);
	}
	while (!tempPQ.isEmpty())
	{
		tempPQ.remove(Fight);
		int d = Fight->calculatePriority();
		fighterspq.add(Fight, d);
	}

	Queue<Enemy*> tempK;
	Enemy *K;
	while (!KilledQueue.isEmpty())
	{
		KilledQueue.dequeue(K);
		tempK.enqueue(K);
		pGUI->AddToDrawingList(K);
	}
	while (!tempK.isEmpty())
	{
		tempK.dequeue(K);
		KilledQueue.enqueue(K);
	}
}

void Battle::CheckKTSAll()
{
	Queue<Enemy*> tempQ;
	Enemy *F;
	while (!freezersqueue.isEmpty())
	{
		freezersqueue.dequeue(F);
		tempQ.enqueue(F);
		F->CheckKTS(CurrentTimeStep);
	}
	while (!tempQ.isEmpty())
	{
		tempQ.dequeue(F);
		freezersqueue.enqueue(F);
	}

	Stack<Enemy*> tempS;
	Enemy*S;
	while (!healersstack.isEmpty())
	{
		S = healersstack.peek();
		healersstack.pop();
		tempS.push(S);
		S->CheckKTS(CurrentTimeStep);
	}
	while (!tempS.isEmpty())
	{
		S = tempS.peek();
		tempS.pop();
		healersstack.push(S);
	}

	PriorityQueue<Enemy*> tempPQ;
	Enemy *Fight;
	while (!fighterspq.isEmpty())
	{
		fighterspq.remove(Fight);
		int d = Fight->calculatePriority();
		tempPQ.add(Fight, d);
		Fight->CheckKTS(CurrentTimeStep);
	}
	while (!tempPQ.isEmpty())
	{
		tempPQ.remove(Fight);
		int d = Fight->calculatePriority();
		fighterspq.add(Fight, d);
	}

}

void Battle::Addenemy(Enemy *ptr)
{
	Q_Inactive.enqueue(ptr);
}
void Battle::readparameters()
{
	string filename;
	ifstream file;
	pGUI->PrintMessage("Enter file name (without .txt):");
	do {
		filename = pGUI->GetString();
		filename = filename + ".txt";
		file.open(filename);
		if (!file.is_open())
			pGUI->PrintMessage("Invalid file name. File does not exist.");
	} while (!file.is_open());
	int ch, mh, cp;
	int ID, type, arrvtime, enemyhealth, enemypower, reload_period, speed;
	if (file.is_open())
	{
		file >> ch >> mh >> cp;
		BCastle.SetHealth(ch);
		BCastle.setMaxHits(mh);
		BCastle.setPower(cp);
		BCastle.startFreeze();
		file >> EnemyCount;
		for (int i = 0; i < EnemyCount; i++)
		{

			file >> ID;
			file >> type;
			file >> arrvtime >> enemyhealth >> enemypower >> reload_period >> speed;
			if (type == 0)
			{
				Enemy*ptr = new Fighter(ID, arrvtime, enemypower, speed, reload_period, enemyhealth);
				Addenemy(ptr);
				ptr->setCastlePtr(&BCastle);
			}
			else if (type == 1)
			{
				Enemy*ptr = new Healer(ID, arrvtime, enemypower, speed, reload_period, enemyhealth);
				Addenemy(ptr);
				ptr->setCastlePtr(&BCastle);
			}
			else
			{
				Enemy*ptr = new Freezer(ID, arrvtime, enemypower, speed, reload_period, enemyhealth);
				Addenemy(ptr);
				ptr->setCastlePtr(&BCastle);
			}

		}
	}
}

void Battle::SaveAll()
{
	string filename = "output.txt";
	ofstream file;
	file.open(filename);
	Queue<Enemy*>tempq;
	Enemy*F;

	double AvgFD = 0.0;
	double AvgKD = 0.0;



	file << WhoWon;
	file << "\n" << "KTS\tID\tFD\tKD\tLT\n";
	while (!KilledQueue.isEmpty())
	{
		KilledQueue.dequeue(F);
		file << F->getKTS() << "\t" << F->GetID() << "\t" << F->getFD() << "\t" << F->getKD() << "\t" << F->getLifeTime() << "\n";
		tempq.enqueue(F);

		AvgFD += F->getFD();
		AvgKD += F->getKD();
	}
	while (!tempq.isEmpty())
	{
		tempq.dequeue(F);
		KilledQueue.enqueue(F);
	}


	if (WhoWon == "Game is WIN") //means castle won
	{
		double CastleTotalDamage = BCastle.GetHealth() - BCastle.GetCurrentHealth();
		if (CastleTotalDamage < 0)
			CastleTotalDamage = 0;
		file << "Castle Total Damage = " << CastleTotalDamage << "\n";
		//Damage dealt to castle is the damage the castle lost... original health minus current health

		//Then print total enemies
		file << "Total Enemies = " << EnemyCount << "\n";
	}

	if (WhoWon == "Game is LOSS") //means castle lost, enemies won
	{
		//Should print alive enemies = any enemy that isn't dead
		file << "Alive enemies = " << EnemyCount - KilledCount << "\n";
	}


	if (AvgFD != 0)
	{
	AvgFD = AvgFD / KilledCount;
	file << "Average First-Shot Delay = " << AvgFD << "\n";
	}

	

	if (AvgKD != 0)
	{
	AvgKD = AvgKD / KilledCount;
	file << "Average Kill Delay = " << AvgKD << "\n";
	}



	file.close();
}

void Battle::InteractiveMode()
{
	StartSimulation();
	while (KilledCount != EnemyCount && BCastle.GetCurrentHealth() > 0)
	{
		simulationloop();
		pGUI->waitForClick();
	}
	GameOver();

}


void Battle::StepMode()
{
	StartSimulation();
	while (KilledCount != EnemyCount && BCastle.GetCurrentHealth() > 0)
	{
		simulationloop();
		Sleep(1000);
	}
	GameOver();

}

void Battle::SilentMode()
{
	StartSimulation();
	while (KilledCount != EnemyCount && BCastle.GetCurrentHealth() > 0)
	{
		simulationloop();
	}
	
	//GameOver();

	if (BCastle.GetCurrentHealth() <= 0 && KilledCount == EnemyCount)
	{
		WhoWon = "Game is DRAW";
	}
	else if (BCastle.GetCurrentHealth() <= 0)
	{
		WhoWon = "Game is LOSS";
	}
	else if (KilledCount == EnemyCount)
	{
		WhoWon = "Game is WIN";
	}

	SaveAll();

	return;

}


void Battle::StartSimulation()
{
	readparameters(); //Load

	CurrentTimeStep = 0;
	int ArrivalTime = 1;

	//pGUI->PrintMessage("Input accepted. Attempting to draw. Please click.");
	//pGUI->waitForClick();

	if (!SilentModeIsOn)
	{
		AddAllListsToDrawingList();
	}
}

void Battle::simulationloop()
{

	CurrentTimeStep++;
	activate();
	MoveAll();

	BCastle.unfreeze();

	ActAll(); //Means to act for all enemies

	UnfreezeAll();

	BCastle.Act_C(fighterspq, healersstack, freezersqueue,CurrentTimeStep);

    AddToKilledQueue();

	//CheckKTSAll();
	if (!SilentModeIsOn)
	{
		pGUI->ResetDrawingList();
		AddAllListsToDrawingList();
	}


	CalculateCounts();

	if (!SilentModeIsOn)
	{
		pGUI->UpdateInterface(CurrentTimeStep, BCastle.GetCurrentHealth(), BCastle.getCStat(), //Fighter -> Healer -> Freezer -> Count, Active -> Frosted -> Killed
			ActiveFighters, ActiveHealers, ActiveFreezers, ActiveCount,
			FrozenFighters, FrozenHealers, FrozenFreezers, FrostedCount,
			KilledFighters, KilledFreezers, KilledHealers, KilledCount);
	}

	//pGUI->waitForClick();

}

void Battle::simulation()
{
	readparameters(); //Load

	CurrentTimeStep = 0;
	int ArrivalTime = 1;


	pGUI->PrintMessage("Input accepted. Attempting to draw. Please click.");
	pGUI->waitForClick();

	AddAllListsToDrawingList();



	pGUI->UpdateInterface(CurrentTimeStep, BCastle.GetCurrentHealth(), BCastle.getCStat(), //Fighter -> Healer -> Freezer -> Count, Active -> Frosted -> Killed
		ActiveFighters, ActiveHealers, ActiveFreezers, ActiveCount,
		FrozenFighters, FrozenHealers, FrozenFreezers, FrostedCount,
		KilledFighters, KilledFreezers, KilledHealers, KilledCount);

	pGUI->PrintMessage("Now activating. Please click.");
	pGUI->waitForClick();
	while (KilledCount != EnemyCount && BCastle.GetCurrentHealth() > 0) //&& BCastle.GetHealth() > 0) //condition m7tag yt8ayar
	{
		CurrentTimeStep++;
		activate();
		//Sleep(500);
		MoveAll();

		BCastle.unfreeze();

		ActAll(); //Means to act for all enemies

		UnfreezeAll();

		//I think castle act should be here
		BCastle.Act_C(fighterspq, healersstack, freezersqueue,CurrentTimeStep);


		pGUI->ResetDrawingList();
		AddAllListsToDrawingList();

		CalculateCounts();

		pGUI->UpdateInterface(CurrentTimeStep, BCastle.GetCurrentHealth(), BCastle.getCStat(), //Fighter -> Healer -> Freezer -> Count, Active -> Frosted -> Killed
			ActiveFighters, ActiveHealers, ActiveFreezers, ActiveCount,
			FrozenFighters, FrozenHealers, FrozenFreezers, FrostedCount,
			KilledFighters, KilledFreezers, KilledHealers, KilledCount);
		//Sleep(250);
		pGUI->waitForClick();
	}
	GameOver();
}
void Battle::checkHeal(Healer* ptr)
{
	double x = ptr->GetDistance();
	if (ptr->getMoveDirection())
	{
		//minus 2
		Queue<Enemy*> tempQ;
		Enemy *F;
		while (!freezersqueue.isEmpty())
		{
			freezersqueue.dequeue(F);
			if (x - 2 >= F->GetDistance() && F->GetDistance() <= x)
			{
				ptr->sethealead(F);
				ptr->Act();
			}
			tempQ.enqueue(F);


		}
		while (!tempQ.isEmpty())
		{
			tempQ.dequeue(F);
			freezersqueue.enqueue(F);
		}


		Stack<Enemy*> tempS;
		Enemy*S;
		while (!healersstack.isEmpty())
		{
			S = healersstack.peek();
			healersstack.pop();
			if (x - 2 >= S->GetDistance() && S->GetDistance() <= x)
			{
				ptr->sethealead(S);
				ptr->Act();
			}
			tempS.push(S);

		}
		while (!tempS.isEmpty())
		{
			S = tempS.peek();
			tempS.pop();
			healersstack.push(S);
		}

		PriorityQueue<Enemy*> tempPQ;
		Enemy *Fight;
		while (!fighterspq.isEmpty())
		{
			fighterspq.remove(Fight);
			int d = Fight->calculatePriority();
			if (x - 2 >= Fight->GetDistance() && Fight->GetDistance() <= x)
			{
				ptr->sethealead(Fight);
				ptr->Act();
			}
			tempPQ.add(Fight, d);

		}
		while (!tempPQ.isEmpty())
		{
			tempPQ.remove(Fight);
			int d = Fight->calculatePriority();
			fighterspq.add(Fight, d);
		}
	}
	else
	{
		//plus 2
		Queue<Enemy*> tempQ;
		Enemy *F;
		while (!freezersqueue.isEmpty())
		{
			freezersqueue.dequeue(F);
			if (x + 2 >= F->GetDistance() && F->GetDistance() >= x)
			{
				ptr->sethealead(F);
				ptr->Act();
			}

			tempQ.enqueue(F);

		}
		while (!tempQ.isEmpty())
		{
			tempQ.dequeue(F);
			freezersqueue.enqueue(F);
		}


		Stack<Enemy*> tempS;
		Enemy*S;
		while (!healersstack.isEmpty())
		{
			S = healersstack.peek();
			healersstack.pop();
			if (x + 2 >= S->GetDistance() && S->GetDistance() >= x)
			{
				ptr->sethealead(S);
				ptr->Act();
			}
			tempS.push(S);

		}
		while (!tempS.isEmpty())
		{
			S = tempS.peek();
			tempS.pop();
			healersstack.push(S);
		}

		PriorityQueue<Enemy*> tempPQ;
		Enemy *Fight;
		while (!fighterspq.isEmpty())
		{

			fighterspq.remove(Fight);
			int d = Fight->calculatePriority();
			if (x + 2 >= Fight->GetDistance() && Fight->GetDistance() >= x)
			{
				ptr->sethealead(Fight);
				ptr->Act();
			}
			tempPQ.add(Fight, d);

		}
		while (!tempPQ.isEmpty())
		{
			tempPQ.remove(Fight);
			int d = Fight->calculatePriority();
			fighterspq.add(Fight, d);
		}
	}
}
void Battle::GameOver()
{
	if (BCastle.GetCurrentHealth() <= 0 && KilledCount == EnemyCount)
	{
		pGUI->PrintMessage("DRAW");
		WhoWon = "Game is DRAW";
	}
	else if (BCastle.GetCurrentHealth() <= 0)
	{
		pGUI->PrintMessage("Castle has lost (Enemies have won)");
		WhoWon = "Game is LOSS";
	}
	else if (KilledCount == EnemyCount)
	{
		pGUI->PrintMessage("castle has won");
		WhoWon = "Game is WIN";
	}

	pGUI->waitForClick();
	SaveAll();

	return;

}


void Battle::UnfreezeAll()
{
	Queue<Enemy*> tempQ;
	Enemy *F;
	while (!freezersqueue.isEmpty())
	{
		freezersqueue.dequeue(F);
		tempQ.enqueue(F);
		if (F->GetStatus() == FRST)
		{
			{
				F->unfreeze();
			}
		}
	}
	while (!tempQ.isEmpty())
	{
		tempQ.dequeue(F);
		freezersqueue.enqueue(F);
	}


	Stack<Enemy*> tempS;
	Enemy*S;
	while (!healersstack.isEmpty())
	{
		S = healersstack.peek();
		healersstack.pop();
		tempS.push(S);
		if (S->GetStatus() == FRST)
		{
			{
				S->unfreeze();
			}
		}
	}
	while (!tempS.isEmpty())
	{
		S = tempS.peek();
		tempS.pop();
		healersstack.push(S);
	}

	PriorityQueue<Enemy*> tempPQ;
	Enemy *Fight;
	while (!fighterspq.isEmpty())
	{
		fighterspq.remove(Fight);
		int d = Fight->calculatePriority();
		tempPQ.add(Fight, d);
		if (Fight->GetStatus() == FRST)
		{
			{
				Fight->unfreeze();
			}
		}
	}
	while (!tempPQ.isEmpty())
	{
		tempPQ.remove(Fight);
		int d = Fight->calculatePriority();
		fighterspq.add(Fight, d);
	}
}

//void Battle::KillOneActiveAndOneFrosted()
//{
//	Queue<Enemy*> tempQ;
//	Enemy *F;
//	//int i = 0;
//	bool KilledActive = 0;
//	bool KilledFrosted = 0;
//	while (!freezersqueue.isEmpty())
//	{
//		freezersqueue.dequeue(F);
//		tempQ.enqueue(F);
//		if (F->GetStatus() == ACTV && !KilledActive)
//		{
//
//			F->decHealth(F->getCurrnet_Health());
//			//i++;
//			KilledFreezers++;
//			ActiveFreezers--;
//			ActiveCount--;
//			KilledCount++;
//			KilledActive = 1;
//
//		}
//		if (F->GetStatus() == FRST && !KilledFrosted)
//		{
//			F->decHealth(F->getCurrnet_Health());
//			//i++;
//			FrozenFreezers--;
//			KilledFreezers++;
//			FrostedCount--;
//			KilledCount++;
//			KilledFrosted = 1;
//		}
//	}
//	while (!tempQ.isEmpty())
//	{
//		tempQ.dequeue(F);
//		freezersqueue.enqueue(F);
//	}
//
//
//	Stack<Enemy*> tempS;
//	Enemy*S;
//	while (!healersstack.isEmpty())
//	{
//		S = healersstack.peek();
//		healersstack.pop();
//		tempS.push(S);
//		if (S->GetStatus() == ACTV && !KilledActive)
//		{
//
//			S->decHealth(S->getCurrnet_Health());
//			ActiveHealers--;
//			KilledHealers++;
//			ActiveCount--;
//			KilledCount++;
//			KilledActive = 1;
//
//		}
//		if (S->GetStatus() == FRST && !KilledFrosted)
//		{
//			S->decHealth(S->getCurrnet_Health());
//			FrozenHealers--;
//			KilledHealers++;
//			FrostedCount--;
//			KilledCount++;
//			KilledFrosted = 1;
//		}
//	}
//	while (!tempS.isEmpty())
//	{
//		S = tempS.peek();
//		tempS.pop();
//		healersstack.push(S);
//	}
//
//
//	PriorityQueue<Enemy*> tempPQ;
//	Enemy *Fight;
//	while (!fighterspq.isEmpty())
//	{
//		fighterspq.remove(Fight);
//		int d = Fight->calculatePriority();
//		tempPQ.add(Fight, d);
//		if (Fight->GetStatus() == ACTV && !KilledActive)
//		{
//
//			Fight->decHealth(Fight->getCurrnet_Health());
//			//i++;
//			KilledFighters++;
//			ActiveFighters--;
//			ActiveCount--;
//			KilledCount++;
//			KilledActive = 1;
//
//		}
//		if (Fight->GetStatus() == FRST && !KilledFrosted)
//		{
//			Fight->decHealth(Fight->getCurrnet_Health());
//
//			KilledFighters++;
//			FrozenFighters--;
//			FrostedCount--;
//			KilledCount++;
//			KilledFrosted = 1;
//		}
//	}
//	while (!tempPQ.isEmpty())
//	{
//		tempPQ.remove(Fight);
//		int d = Fight->calculatePriority();
//		fighterspq.add(Fight, d);
//	}
//}


//void Battle::FreezeTwoOfEach()
//{
//	Queue<Enemy*> tempQ;
//	Enemy *F;
//	int i = 0;
//	while (!freezersqueue.isEmpty())
//	{
//		freezersqueue.dequeue(F);
//		tempQ.enqueue(F);
//		if (F->GetStatus() == ACTV)
//		{
//			if (i == 0 || i == 1)
//			{
//				F->freezeme(1);
//				i++;
//				FrozenFreezers++;
//				if (ActiveFreezers > 0)
//					ActiveFreezers--;
//				if (ActiveCount > 0)
//					ActiveCount--;
//				FrostedCount++;
//			}
//		}
//	}
//	while (!tempQ.isEmpty())
//	{
//		tempQ.dequeue(F);
//		freezersqueue.enqueue(F);
//	}
//
//	i = 0;
//
//	Stack<Enemy*> tempS;
//	Enemy*S;
//	while (!healersstack.isEmpty())
//	{
//		S = healersstack.peek();
//		healersstack.pop();
//		tempS.push(S);
//		if (S->GetStatus() == ACTV)
//		{
//			if (i == 0 || i == 1)
//			{
//				S->freezeme(1);
//				i++;
//				FrozenHealers++;
//				if (ActiveHealers > 0)
//				{
//					ActiveHealers--;
//				}
//				if (ActiveCount > 0)
//				{
//					ActiveCount--;
//				}
//
//				FrostedCount++;
//			}
//		}
//	}
//	while (!tempS.isEmpty())
//	{
//		S = tempS.peek();
//		tempS.pop();
//		healersstack.push(S);
//	}
//
//	i = 0;
//
//	PriorityQueue<Enemy*> tempPQ;
//	Enemy *Fight;
//	while (!fighterspq.isEmpty())
//	{
//		fighterspq.remove(Fight);
//		int d = Fight->calculatePriority();
//		tempPQ.add(Fight, d);
//		if (Fight->GetStatus() == ACTV)
//		{
//			if (i == 0 || i == 1)
//			{
//				Fight->freezeme(1);
//				i++;
//				FrozenFighters++;
//				if (ActiveFighters > 0)
//					ActiveFighters--;
//				if (ActiveCount > 0)
//					ActiveCount--;
//				FrostedCount++;
//			}
//		}
//	}
//	while (!tempPQ.isEmpty())
//	{
//		tempPQ.remove(Fight);
//		int d = Fight->calculatePriority();
//		fighterspq.add(Fight, d);
//	}
//	//int i = 0;
//	//int freezerscount;
//	//Queue<Enemy*> tempQ;
//	//Enemy *F;
//	//
//	//Enemy* const * freezerlist=freezersqueue.toArray(freezerscount);
//	//if(!freezersqueue.isEmpty())
//	//{
//	//	cout << freezerlist[i]->GetStatus() << "\n";
//	//	for (int j = 0; j < 2; j++)
//	//	{
//	//		//while (freezerlist[i]->GetStatus() == FRST)
//	//		//{
//	//		//	i++;
//	//		//	if (freezerlist[i] == NULL)
//	//		//		break;
//	//		//}
//	//		if (freezerlist[i] != NULL)
//	//		{
//	//			while (freezerlist[i]->GetStatus() == FRST)
//	//			{
//	//				i++;
//	//				if (freezerlist[i] == NULL)
//	//				return;
//	//			}
//	//		}
//	//		if (freezerlist[i]->GetStatus() == ACTV)
//	//			freezerlist[i]->freezeme(1);
//	//		i++;
//	//	}
//	//}
//
//}
//
//void Battle::UnfreezeTwo()
//{
//	Queue<Enemy*> tempQ;
//	Enemy *F;
//	int i = 0;
//	while (!freezersqueue.isEmpty())
//	{
//		freezersqueue.dequeue(F);
//		tempQ.enqueue(F);
//		if (F->GetStatus() == FRST)
//		{
//			if (i == 0 || i == 1)
//			{
//				F->unfreeze();
//				i++;
//				FrozenFreezers--;
//				ActiveFreezers++;
//				ActiveCount++;
//				FrostedCount--;
//			}
//		}
//	}
//	while (!tempQ.isEmpty())
//	{
//		tempQ.dequeue(F);
//		freezersqueue.enqueue(F);
//	}
//
//	i = 0;
//
//	Stack<Enemy*> tempS;
//	Enemy*S;
//	while (!healersstack.isEmpty())
//	{
//		S = healersstack.peek();
//		healersstack.pop();
//		tempS.push(S);
//		if (S->GetStatus() == FRST)
//		{
//			if (i == 0 || i == 1)
//			{
//				S->unfreeze();
//				i++;
//				if (FrozenHealers > 0)
//					FrozenHealers--;
//				ActiveHealers++;
//				ActiveCount++;
//				if (FrostedCount > 0)
//					FrostedCount--;
//			}
//		}
//	}
//	while (!tempS.isEmpty())
//	{
//		S = tempS.peek();
//		tempS.pop();
//		healersstack.push(S);
//	}
//
//	i = 0;
//
//	PriorityQueue<Enemy*> tempPQ;
//	Enemy *Fight;
//	while (!fighterspq.isEmpty())
//	{
//		fighterspq.remove(Fight);
//		int d = Fight->calculatePriority();
//		tempPQ.add(Fight, d);
//		if (Fight->GetStatus() == FRST)
//		{
//			if (i == 0 || i == 1)
//			{
//				Fight->unfreeze();
//				i++;
//				if (FrozenFighters > 0)
//					FrozenFighters--;
//				ActiveFighters++;
//				ActiveCount++;
//				if (FrostedCount > 0)
//					FrostedCount--;
//			}
//		}
//	}
//	while (!tempPQ.isEmpty())
//	{
//		tempPQ.remove(Fight);
//		int d = Fight->calculatePriority();
//		fighterspq.add(Fight, d);
//	}
//}
void Battle::ActAll()
{
	Queue<Enemy*> tempQ;
	Enemy *F;
	while (!freezersqueue.isEmpty())
	{
		freezersqueue.dequeue(F);
		tempQ.enqueue(F);
		F->setReload(CurrentTimeStep);
		F->Act();


	}
	while (!tempQ.isEmpty())
	{
		tempQ.dequeue(F);
		freezersqueue.enqueue(F);
	}

	Stack<Enemy*> tempS;
	Enemy*S;

	while (!healersstack.isEmpty())
	{
		S = healersstack.peek();
		healersstack.pop();
		tempS.push(S);
		Healer* h = dynamic_cast<Healer*>(S);
		S->setReload(CurrentTimeStep);
		checkHeal(h);
	}
	while (!tempS.isEmpty())
	{
		S = tempS.peek();
		tempS.pop();
		healersstack.push(S);
	}

	PriorityQueue<Enemy*> tempPQ;
	Enemy *Fight;
	while (!fighterspq.isEmpty())
	{
		fighterspq.remove(Fight);
		int d = Fight->calculatePriority();
		tempPQ.add(Fight, d);
		Fight->setReload(CurrentTimeStep);
		Fight->Act();
	}
	while (!tempPQ.isEmpty())
	{
		tempPQ.remove(Fight);
		int d = Fight->calculatePriority();
		fighterspq.add(Fight, d);
	}
}

void Battle::AddToKilledQueue()
{
	Queue<Enemy*> tempQ;
	Enemy*f;
	while (!freezersqueue.isEmpty())
	{
		freezersqueue.dequeue(f);
		if (f->isKilled())
		{
			KilledQueue.enqueue(f);
			f->setKTS(CurrentTimeStep);
			f->setlt(CurrentTimeStep);
			KilledCount++;
		}
		else
			tempQ.enqueue(f);
	}
	Stack<Enemy*> temps;
	while (!healersstack.isEmpty())
	{
		f = healersstack.peek();
		healersstack.pop();
		if (f->isKilled())
		{
			KilledQueue.enqueue(f);
			f->setKTS(CurrentTimeStep);
			f->setlt(CurrentTimeStep);
			KilledCount++;
		}
		else
			temps.push(f);
	}
	PriorityQueue<Enemy*> temppqq;

	while (!fighterspq.isEmpty())
	{

		fighterspq.remove(f);
		if (f->isKilled())
		{
			KilledQueue.enqueue(f);
			f->setKTS(CurrentTimeStep);
			f->setlt(CurrentTimeStep);
			KilledCount++;
		}
		else
		{

			int d = f->calculatePriority();
			temppqq.add(f, d);


		}
	}

	while (!tempQ.isEmpty())
	{

		tempQ.dequeue(f);
		freezersqueue.enqueue(f);

	}
	while (!temps.isEmpty())
	{
		f = temps.peek();
		temps.pop();
		healersstack.push(f);
	}
	while (!temppqq.isEmpty())
	{
		temppqq.remove(f);
		int d = f->calculatePriority();
		fighterspq.add(f, d);


	}

}








void Battle::MoveAll()
{
	Queue<Enemy*> tempQ;
	Enemy *F;
	while (!freezersqueue.isEmpty())
	{
		freezersqueue.dequeue(F);
		tempQ.enqueue(F);
		F->Move();
	}
	while (!tempQ.isEmpty())
	{
		tempQ.dequeue(F);
		freezersqueue.enqueue(F);
	}

	Stack<Enemy*> tempS;
	Enemy*S;
	while (!healersstack.isEmpty())
	{
		S = healersstack.peek();
		healersstack.pop();
		tempS.push(S);
		S->Move();
	}
	while (!tempS.isEmpty())
	{
		S = tempS.peek();
		tempS.pop();
		healersstack.push(S);
	}

	PriorityQueue<Enemy*> tempPQ;
	Enemy *Fight;
	while (!fighterspq.isEmpty())
	{
		fighterspq.remove(Fight);
		int d = Fight->calculatePriority();
		tempPQ.add(Fight, d);
		Fight->Move();
	}
	while (!tempPQ.isEmpty())
	{
		tempPQ.remove(Fight);
		int d = Fight->calculatePriority();
		fighterspq.add(Fight, d);
	}
}



void Battle::activate()
{
	Enemy* pe;
	while (!Q_Inactive.isEmpty())
	{
		//Q_Inactive.dequeue(pe);
		Q_Inactive.peekFront(pe);
		if (pe->GetArrvTime() > CurrentTimeStep)
			return;
		else
		{
			Q_Inactive.dequeue(pe);
			pe->SetStatus(ACTV);
			//ActiveCount++;
		}
		if (pe->getType() == FREEZER)
		{
			freezersqueue.enqueue(pe);
			//ActiveFreezers++;
		}
		else if (pe->getType() == HEALER)
		{
			//Healer* healerpe = dynamic_cast<Healer*>(pe);
			healersstack.push(pe);
			//ActiveHealers++;
		}
		else
		{
			int d = pe->calculatePriority();
			fighterspq.add(pe, d);
			//ActiveFighters++;
		}
		//delete pe;	
	}
}
