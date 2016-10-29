#include "stdafx.h"
#include "Car.h"

bool IsInRange(int value, int startValue, int finishValue)
{
	return ((finishValue >= value) && (startValue <= value));
}

bool IsSpeedInGear(int gear, int speed)
{
	return ((gear == -1) && (IsInRange(speed, 0, 20))) ||
		((gear == 0) && (speed == 0)) ||
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
		switch (gear)
		{
			case -1:
			{
				if ((m_currentSpeed == 0) && ((m_currentGear == 0) || (m_currentGear == 1)))
				{
					m_currentGear = gear;
					return true;
				}
				break;
			}
			case 0:
			{
				m_currentGear = gear;
				return true;
				break;
			}
			case 1:
			{
				if (((m_currentSpeed >= 0) && (m_currentSpeed <= 30)))
				{
					m_currentGear = gear;
					return true;
				}
				break;
			}
			case 2:
			{
				if ((m_currentSpeed >= 20) && (m_currentSpeed <= 50))
				{
					m_currentGear = gear;
					return true;
				}
				break;
			}
			case 3:
			{
				if ((m_currentSpeed >= 30) && (m_currentSpeed <= 60))
				{
					m_currentGear = gear;
					return true;
				}
				break;
			}
			case 4:
			{
				if ((m_currentSpeed >= 40) && (m_currentSpeed <= 90))
				{
					m_currentGear = gear;
					return true;
				}
				break;
			}
			case 5:
			{
				if ((m_currentSpeed >= 50) && (m_currentSpeed <= 150))
				{
					m_currentGear = gear;
					return true;
				}
				break;
			}
		}
	}
	return false;
}


bool CCar::SetSpeed(int speed)
{
	if (m_engineOnTurn && IsSpeedInGear(m_currentGear, speed))
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
	if (m_currentSpeed < 0)
	{
		return -m_currentSpeed;
	}
	return m_currentSpeed;
}


int CCar::GetGear() const
{
	return m_currentGear;
}


bool CCar::IsEngineOn() const
{
	return m_engineOnTurn;
}


int CCar::GetDirection() const
{
	if (m_currentSpeed > 0)
	{
		return 1;
	}
	else if (m_currentSpeed < 0)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}
