#pragma once

class CCar
{
public:
	CCar() = default;

	~CCar() = default;

	int GetSpeed() const;

	int GetGear() const;

	bool IsEngineOn() const;

	int GetDirection() const;

	bool TurnOnEngine();

	bool TurnOffEngine();

	bool SetGear(int gear);

	bool SetSpeed(int speed);
private:
	bool m_engineOnTurn = false;
	int m_currentGear = 0;
	int m_currentSpeed = 0;
};

