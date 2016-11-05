#include "stdafx.h"
#include "Car.h"

bool IsInRange(int value, int startValue, int finishValue)
{
	return ((finishValue >= value) && (startValue <= value));
}

bool IsSpeedInGear(int gear, int speed)
{
	return ((gear == -1) && (IsInRange(speed, 0, 20))) ||
		((gear == 1) && (IsInRange(speed, 0, 30))) ||
		((gear == 2) && (IsInRange(speed, 20, 50))) ||
		((gear == 3) && (IsInRange(speed, 30, 60))) ||
		((gear == 4) && (IsInRange(speed, 40, 90))) ||
		((gear == 5) && (IsInRange(speed, 50, 150)));
}

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
		m_engineOnTurn = false;
		return true;
	}
	return false;
}


bool CCar::SetGear(int gear)
{
	if (gear == m_currentGear)
	{
		return true;
	}
	if (m_engineOnTurn)
	{
		if (gear == 0)
		{
			m_currentGear = 0;
			return true;
		}
		else if (gear == -1)
		{
			if ((m_currentGear == 0 || m_currentGear == 1) && (m_currentSpeed == 0))
			{
				m_currentGear = -1;
				return true;
			}
		}
		else if (IsSpeedInGear(gear, m_currentSpeed))
		{
			m_currentGear = gear;
			return true;
		}
	}
	return false;
}


bool CCar::SetSpeed(int speed)
{
	if (m_engineOnTurn && (IsSpeedInGear(m_currentGear, speed) || (m_currentGear == 0 && abs(m_currentSpeed) >= speed)))
	{
		if (m_currentGear == -1)
		{
			speed = -speed;
		}
		m_currentSpeed = speed;
		return true;
	}
	return false;
}


int CCar::GetSpeed() const
{
	return abs(m_currentSpeed);
}


int CCar::GetGear() const
{
	return m_currentGear;
}


bool CCar::IsEngineOn() const
{
	return m_engineOnTurn;
}


std::string CCar::GetDirection() const
{
	if (m_currentSpeed > 0)
	{
		return "forward";
	}
	else if (m_currentSpeed < 0)
	{
		return "reverse";
	}
	else
	{
		return "stand";
	}
}
