#pragma once

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
//#include"..\Castle\Castle.h"

class GUI;
class Castle;
// Enemy is the base class of each type of enemy
// Enemy should be an abstract class in next phases
class Enemy
{

protected:
	const int ID;         //Each enemy has a unique ID (sequence number)
	const int ArrvTime;	//arrival time (time it starts to join battle)
	Castle *C_ptr;
	

	ENMY_STATUS status;	    //status of the enemy (inactive, inactive, frosted, killed)
	int Distance;	//Horizontal distance between enemy & the tower of its region
	                //Always positive (ranges from 2 to 60)
	double Health;	//Enemy health
	double current_health;

	//added members
	int reloadPeriod;
	int Speed;
	int power;
	RELOAD R;
	int reloadtime;
	ENMY_TYPE Type;
	int Enemies_count;
	int actual_count;
	double freeze_time;
	
	int KTS;
	int lifetime;
	int ft;
	int FD;
	int KD;
	bool firstshot;

public:
	Enemy(int id, int arrTime, int d = MaxDistance);
	virtual ~Enemy();

	int Enemy::GetID() const;
	ENMY_STATUS GetStatus() const;
	void SetStatus(ENMY_STATUS);
	
	void DecrementDist();

	void SetDistance(int );
	int GetDistance() const;

	int GetArrvTime() const;
	


	// Virtual Functions: ----------------

	virtual void Move() = 0;	//All enemies can move
	virtual void Act() = 0;	//Acting means fighting or healing
	//Aded pure virtual functions;
	virtual void Activate(int t) = 0;
	virtual void setCastlePtr(Castle* ptr);
	virtual Castle* getCastlePtr();
	

	//added functions
	void setspeed(int s);
	void setreloadPeriod(int rp);
	void setPower(int P);
	int getspeed();
	int getreloadPeriod();
	int getPower();
	RELOAD setReload(int t);
	void setType(ENMY_TYPE T);
	ENMY_TYPE getType();
	void increment_health(Enemy * ptr);
	double getCurrnet_Health();
	void setCurrent_Health(double h);
	int CheckforReloadTime();
	virtual void decHealth(double N, int timestep);
	bool isKilled();
	void freezeme(double f, int timestep);
	void unfreeze();
	int getID() const;
	virtual int calculatePriority();

	void setKTS(int num);
	//int getKTS();
	void setlt(int lt);
	int getlt();
	void CheckKTS(int TimeStep);
	int getKD();
	int getFD();
	int getKTS();
	int getLifeTime();

};

