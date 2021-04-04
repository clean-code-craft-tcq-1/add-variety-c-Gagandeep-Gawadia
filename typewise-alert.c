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

status checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC)
{
	status(*callAlertTarget[])(BreachType) = { sendToController , sendToEmail };
	status taskStatus = FAILURE;
	BreachType breachType = classifyTemperatureBreach(
		batteryChar.coolingType, temperatureInC
	);

	taskStatus = callAlertTarget[alertTarget](breachType);
	return taskStatus;
}

status sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
  return SUCCESS;
}

status sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";
  char* breachMsg[2] = { "too low", "too high" };
 
  if (breachType < NORMAL)
  {
	  printf("To: %s\n", recepient);
	  printf("Hi, the temperature is %s \n",breachMsg[breachType]);
  }
  return SUCCESS;
}


status sendToConsole(BreachType breachType) {
	
	char* breachMsg[2] = { "too low", "too high" };

	if (breachType < NORMAL)
	{
		printf("Hi, the temperature is %s \n", breachMsg[breachType]);
	}
	return SUCCESS;
}
