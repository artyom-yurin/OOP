#include "stdafx.h"
#include "car_function_tests.h"
#include "Car.h"
#include <assert.h>

void TestTurnOnEngine()
{
	CCar car;
	assert(car.TurnOnEngine());
	assert(!car.TurnOnEngine());
}

void TestTurnOffEngine()
{
	CCar car;
	car.TurnOnEngine();
	assert(car.TurnOffEngine());
	car.TurnOnEngine();
	car.SetSpeed(10);
	assert(!car.TurnOffEngine());
	car.SetSpeed(0);
	car.SetGear(1);
	assert(!car.TurnOffEngine());
}

void TestSetSpeed()
{
	CCar car;
	assert(car.SetSpeed(10));
	car.SetGear(1);
	assert(!car.SetSpeed(40));
}

void TestSetGear()
{
	CCar car;
	car.TurnOnEngine();
	assert(car.SetGear(1));
	car.SetSpeed(19);
	assert(!car.SetGear(2));
	car.SetSpeed(0);
	assert(car.SetGear(-1));
	car.SetSpeed(1);
	assert(!car.SetGear(1));
	assert(car.SetGear(0));
}

void TestGetInfo()
{
	CCar car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(2);
	car.SetSpeed(35);
	assert(car.GetGear() == 2);
	assert(car.GetSpeed() == 35);
	assert(car.GetEngineStatus());
	assert(car.GetDirection() == 1);
}
