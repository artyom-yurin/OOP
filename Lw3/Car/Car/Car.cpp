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
	if ((m_engineOnTurn) && (m_currentDirection == 0) && (m_currentGear == 0)) 
	{
		m_engineOnTurn = false;
		return true;
	}
	return false;
}


bool CCar::SetGear(int gear)
{
	if (m_engineOnTurn)
	{
		if (gear == m_currentGear)
		{
			return true;
		}
		switch (gear)
		{
			case -1:
			{
				if ((!m_currentSpeed) && (!m_currentGear || (m_currentGear == 1)))
				{
					m_currentGear = gear;
					m_currentDirection = -1;
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
				if (((m_currentSpeed >= 0) && (m_currentSpeed <= 30) && (m_currentDirection == 1)) || (m_currentSpeed == 0 && ((m_currentDirection = 0) || (m_currentDirection = -1))))
				{
					m_currentGear = gear;
					return true;
				}
				break;
			}
			case 2:
			{
				if ((m_currentSpeed >= 20) && (m_currentSpeed <= 50) && (m_currentDirection == 1))
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
	if (m_engineOnTurn)
	{
		switch (m_currentGear)
		{
			case -1:
			{
				if ((speed >= 0) && (speed <= 20))
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
					m_currentDirection = 0;
					m_currentSpeed = speed;
					return true;
				}
				break;
			}
			case 1:
			{
				if ((speed >= 0) && (speed <= 30))
				{
					if (speed)
					{
						m_currentDirection = 1;
					}
					else
					{
						m_currentDirection = 0;
					}
					m_currentSpeed = speed;
					return true;
				}
				break;
			}
			case 2:
			{
				if ((speed >= 20) && (speed <= 50))
				{
					m_currentSpeed = speed;
					return true;
				}
				break;
			}
			case 3:
			{
				if ((speed >= 30) && (speed <= 60))
				{
					m_currentSpeed = speed;
					return true;
				}
				break;
			}
			case 4:
			{
				if ((speed >= 40) && (speed <= 90))
				{
					m_currentSpeed = speed;
					return true;
				}
				break;
			}
			case 5:
			{
				if ((speed >= 50) && (speed <= 150))
				{
					m_currentSpeed = speed;
					return true;
				}
				break;
			}
		}
	}
	return false;
}


int CCar::GetSpeed() const
{
	return m_currentSpeed;
}


int CCar::GetGear() const
{
	return m_currentGear;
}


bool CCar::GetEngineStatus() const
{
	return m_engineOnTurn;
}


int CCar::GetDirection() const
{
	return m_currentDirection;
}
