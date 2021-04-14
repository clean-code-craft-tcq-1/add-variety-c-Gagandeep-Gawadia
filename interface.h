#pragma once
#include "typewise-alert.h"

void sendToController(BreachType breachType);
void sendToEmail(BreachType breachType);
void sendToConsole(BreachType breachType);

//Adding mock function declaration and keeping them separate purposely
void mock_sendtoControllerheader(char * buffer);
void mock_sendtoEmailrecipient(char * buffer);
void mock_sendtoConsoletext(char * buffer);
