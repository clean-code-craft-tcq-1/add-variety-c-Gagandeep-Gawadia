#pragma once
#include "typewise-alert.h"

void sendToController(BreachType breachType);
void sendToEmail(BreachType breachType);
void sendToConsole(BreachType breachType);
void mock_sendtoControllerheader(char * buffer);
void mock_sendtoEmailrecipient(char * buffer);