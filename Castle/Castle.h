#pragma once
#include"..\Generic_DS\PriorityQueue.h"
#include "..\Defs.h"
#include"..\Fighter.h"
#include"..\Healer.h"
#include"..\Freezer.h"
#include"..\Generic_DS\Stack.h"
#include"..\Generic_DS\Queue.h"
class Castle
{
	double Health;
	double current_health;
	CASTLE_STAT CS=ACTIVE;
	int Freeze;
	int MaxHits;//N read from input file
	int CastlePower;
	int FD;
	bool firstshot;

	
public:
	Castle();
	void SetHealth(double h);
	double GetHealth() const;
	double GetCurrentHealth();

	void decHealth(double D);
	CASTLE_STAT getCStat();
	void setCStat(CASTLE_STAT C);
	void incrementChealth();//to inc health if a healer gets killed within 5m 
	void Act_C(PriorityQueue<Enemy*>&aPqueue,Stack<Enemy*>&aStack,Queue<Enemy*>&aQueue, int timestep);//will have 3 lists as a parameter (one for each enemy DS)
	void checkFreeze();
	void incFreeze(int F);
	void setMaxHits(int N);
	int getMaxHits();
	void setPower(int P);
	void decFreeze(int f);
	int getfreeze();
	void unfreeze();
	void startFreeze();
	void setFD(int FFDD);
	int getFd();
	
	
};

