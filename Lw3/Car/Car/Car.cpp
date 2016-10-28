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
	switch (m_currentGear)
	{
		case -1: 
		{
			if ((speed > 0) && (speed < 20))
			{
				m_currentSpeed = speed;
				return true;
			}
			break;
		}
		case 0:
		{
			if (!speed)
			{
				m_currentSpeed = speed;
				return true;
			}
			break;
		}
		case 1:
		{
			if ((speed > 0) && (speed < 30))
			{
				m_currentSpeed = speed;
				return true;
			}
			break;
		}
		case 2:
		{
			if ((speed > 20) && (speed < 50))
			{
				m_currentSpeed = speed;
				return true;
			}
			break;
		}
		case 3:
		{
			if ((speed > 30) && (speed < 60))
			{
				m_currentSpeed = speed;
				return true;
			}
			break;
		}
		case 4:
		{
			if ((speed > 40) && (speed < 90))
			{
				m_currentSpeed = speed;
				return true;
			}
			break;
		}
		case 5:
		{
			if ((speed > 50) && (speed < 150))
			{
				m_currentSpeed = speed;
				return true;
			}
			break;
		}
	}
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
