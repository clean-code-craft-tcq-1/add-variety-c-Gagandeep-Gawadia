#include "typewise-alert.h"
#include <stdio.h>

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

BreachType classifyTemperatureBreach(
    CoolingType coolingType, double temperatureInC) {
  int lowerLimit = 0;
  int upperLimit = 0;
  int limitsTable[3][2] = {{0,35},  // PASSIVE_COOLING
                           {0,45},  // HI_ACTIVE_COOLING
                           {0,40}}; // MED_ACTIVE_COOLING

  lowerLimit = limitsTable[coolingType][0];
  upperLimit = limitsTable[coolingType][1];

  return inferBreach(temperatureInC, lowerLimit, upperLimit);
}

void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC)
{
	void (*callAlertTarget[])(BreachType) = { sendToController , sendToEmail , sendToConsole};
	
	BreachType breachType = classifyTemperatureBreach(
		batteryChar.coolingType, temperatureInC
	);

	callAlertTarget[alertTarget](breachType);
	
}


