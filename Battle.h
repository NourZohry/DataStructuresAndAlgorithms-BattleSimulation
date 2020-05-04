#pragma once

#include "Enemies\Enemy.h"
#include "Castle\Castle.h"
#include "Generic_DS\Queue.h"
#include "GUI\GUI.h"
#include"Generic_DS/PriorityQueue.h"
#include"Generic_DS/Stack.h"
#include<fstream>
#include<string.h>


// it is the controller of the project
class Battle
{
private:
	GUI* pGUI;
	Castle BCastle;
	int EnemyCount;	//the actual number of enemies in the game
	int ActiveCount, FrostedCount, KilledCount;	//no. of enemies (Active, Frosted, killed so far)
	int CurrentTimeStep;
	int ActiveFighters;
	int ActiveHealers;
	int ActiveFreezers;
	int FrozenFighters;
	int FrozenHealers;
	int FrozenFreezers;
	int KilledFighters;
	int KilledFreezers;
	int KilledHealers;
	

	Queue<Enemy*> Q_Inactive;		//Queue of inactive enemies

	PriorityQueue<Enemy*> fighterspq;
	Stack<Enemy*> healersstack;
	Queue<Enemy*> freezersqueue;

	Queue<Enemy*> KilledQueue;

	string WhoWon;


	


	bool SilentModeIsOn;

	
public:
	
	Battle();
	void AddAllListsToDrawingList();		//Add enemy lists (inactive, active,.....) to drawing list to be displayed on user interface
	Castle * GetCastle(); //vip
	void RunSimulation();
	

	void readparameters();
	void Addenemy(Enemy *ptr);
	void simulation();
	void activate();
	void MoveAll();

	//void FreezeTwoOfEach();
	//void UnfreezeTwo();
	//void KillOneActiveAndOneFrosted(); //Not used in the main game but we decided to keep them commented just in case

	void ActAll();
	void UnfreezeAll();
	void CalculateCounts();
	void CheckStatus(Enemy *ptr);
	void GameOver();
	void checkHeal(Healer* ptr);

	void simulationloop();
	void StartSimulation();
	void InteractiveMode();
	void StepMode();
	void SilentMode();

	void AddToKilledQueue();

	void SaveAll();
	void CheckKTSAll();

};

