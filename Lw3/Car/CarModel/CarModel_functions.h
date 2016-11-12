#pragma once

#include "..\Car\Car.h"

void GetInfo(std::ostream & output, CCar & car);

void EngineOn(std::ostream & output, CCar & car);

void EngineOff(std::ostream & output, CCar & car);

bool SetGear(CCar & car, int value);

bool SetSpeed(CCar & car, int value);