#include "stdafx.h"
#include "Car.h"


CCar::CCar() = default;


CCar::~CCar() = default;


bool CCar::TurnOnEngine()
{
	if (!m_engineOnTurn)
	{
		m_engineOnTurn = true;
		return true;
	}
	return false;
}


bool CCar::TurnOffEngine()
{
	return false;
}


bool CCar::SetGear(int gear)
{
	return false;
}


bool CCar::SetSpeed(int speed)
{
	return false;
}


int CCar::GetSpeed() const
{
	return 0;
}


int CCar::GetGear() const
{
	return 0;
}


bool CCar::GetEngineStatus() const
{
	return false;
}


int CCar::GetDirection() const
{
	return 0;
}
