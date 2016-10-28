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
	if ((m_engineOnTurn) && (m_currentSpeed == 0) && (m_currentGear == 0)) 
	{
		m_currentDirection = 0;
		m_engineOnTurn = false;
		return true;
	}
	return false;
}


bool CCar::SetGear(int gear)
{
	m_currentGear = gear;
	return false;
}


bool CCar::SetSpeed(int speed)
{
	m_currentSpeed = speed;
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
