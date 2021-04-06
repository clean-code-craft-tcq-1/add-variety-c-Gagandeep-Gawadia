#pragma once

typedef enum {
  PASSIVE_COOLING,
  HI_ACTIVE_COOLING,
  MED_ACTIVE_COOLING
} CoolingType;

typedef enum {
  TOO_LOW,
  TOO_HIGH,
  NORMAL
} BreachType;

BreachType inferBreach(double value, double lowerLimit, double upperLimit);
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);

typedef enum {
  TO_CONTROLLER,
  TO_EMAIL,
  TO_CONSOLE
} AlertTarget;

typedef struct {
  CoolingType coolingType;
  char brand[48];
} BatteryCharacter;


typedef enum {
	SUCCESS,
	FAILURE
} status;


status checkAndAlert(
  AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);

status sendToController(BreachType breachType);
status sendToEmail(BreachType breachType);
status sendToConsole(BreachType breachType);
