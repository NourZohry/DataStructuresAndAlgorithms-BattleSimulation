#include "Enemy.h"


Enemy::Enemy(int id, int arrTime, int d) :ID(id), ArrvTime(arrTime), reloadtime(arrTime), current_health(Health)
{
	SetDistance(d);
	Enemies_count = 10;// should be read from the file or simulation mch 3arf el sraaa7a ab2o shoofha fe el pdf
	actual_count = 0;
	KTS = 0;
	firstshot = true;
}

Enemy::~Enemy()
{
}

int Enemy::GetID() const
{
	return ID;
}


void Enemy::SetStatus(ENMY_STATUS s)
{
	status = s;
}


ENMY_STATUS Enemy::GetStatus() const
{
	return status;
}


void Enemy::DecrementDist()
{
	if (Distance > MinDistance)
		Distance--;
}

void Enemy::SetDistance(int d)
{
	if (d >= MinDistance && d <= MaxDistance)
		Distance = d;
	else
		Distance = MaxDistance;
}

int Enemy::GetDistance() const
{
	return Distance;
}

int Enemy::GetArrvTime() const
{
	return ArrvTime;
}
//Added functions
void Enemy::setspeed(int s)
{
	Speed = s;
}
void Enemy::setreloadPeriod(int rp)
{
	reloadPeriod = rp;
}
void Enemy::setPower(int P)
{
	power = P;
}
int Enemy::getspeed()
{
	return Speed;
}
int Enemy::getreloadPeriod()
{
	return reloadPeriod;
}
int Enemy::getPower()
{
	return power;
}
RELOAD Enemy::setReload(int t)
{
	if (reloadtime == t)
	{
		R = NORELOADING;
		reloadtime += reloadPeriod;
		return R;
	}
	else
	{
		R = RELOADING;
		return R;
	}
}
void Enemy::setType(ENMY_TYPE T)
{
	Type = T;
}
ENMY_TYPE Enemy::getType()
{
	return Type;
}
void Enemy::increment_health(Enemy * ptr)
{
	double x = ptr->getCurrnet_Health();
	double y = current_health;
	double z = abs(ptr->GetDistance() - Distance) + 1;
	double heal = (x / y) * (1.0 / z);
	//current_health += heal;
	ptr->setCurrent_Health(ptr->getCurrnet_Health() + heal);

}
double Enemy::getCurrnet_Health()
{
	return current_health;
}
void Enemy::setCurrent_Health(double h)
{
	current_health = h;
}
int Enemy::CheckforReloadTime()
{
	return 0;
}
bool Enemy::isKilled()
{
	switch (status)
	{
	case KILD:
		return true;
		
	}
	return false;
}
void Enemy::decHealth(double N,int timestep)
{
	if (firstshot)
	{
		FD = timestep - ArrvTime;
		ft = timestep;
		firstshot = false;
	}
	current_health -= N;
	if (current_health <= 0)
	{
		status = KILD;
	}
}
void Enemy::setCastlePtr(Castle* ptr)
{
	C_ptr = ptr;
}
Castle* Enemy::getCastlePtr()
{
	return C_ptr;
}
void Enemy::freezeme(double f,  int timestep)
{
	if (firstshot)
	{
		FD = timestep - ArrvTime;
		ft = timestep;
		firstshot=false;
	}
	if (status == FRST)
		return;
	freeze_time = f;
	status = FRST;

}
void Enemy::unfreeze()
{
	if (status == FRST)
	{
		if (freeze_time <= 0)
		{
			status = ACTV;
			freeze_time = 0;
		}
		else
			freeze_time -= 1;

	}
}

int Enemy::getID() const
{
	return ID;
}
int Enemy::calculatePriority()
{
	double statconst = 1;
	if (GetStatus() == FROZEN)
	{
		statconst = 0.5;

	}
	return ((getPower() / GetDistance())* getCurrnet_Health())*statconst;
}


void Enemy::setKTS(int num)
{
	KTS = num;
	KD = KTS - ft;
}
int Enemy::getKD()
{
	return KD;
}
int Enemy::getFD()
{
	return FD;
}
int Enemy::getKTS()
{
	return KTS;
}
int Enemy::getLifeTime()
{
	return lifetime;
}

void Enemy::CheckKTS(int TimeStep)
{

	if (isKilled())
	{
		KTS = TimeStep;
	}
		
}
void Enemy:: setlt(int lt)
{
	lifetime = lt - ArrvTime;
}

int Enemy:: getlt()
{
	return lifetime;
}