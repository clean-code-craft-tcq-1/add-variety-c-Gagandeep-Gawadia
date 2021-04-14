
#include "interface.h"

#include <stdio.h>

 int alertRaised[3];
 char * mock_header = NULL;
 char * mock_recipient = NULL;

 void mock_sendtoControllerheader(char * buffer)
 {
	 mock_header = buffer;
 }
 void mock_sendtoEmailrecipient(char * buffer)
 {
	 mock_recipient = buffer;
 }

void sendToController(BreachType breachType) {

	printf("%s : %x\n", mock_header, breachType);

	alertRaised[TO_CONTROLLER] = 1;
	
}

void sendToEmail(BreachType breachType) {

	char* breachMsg[2] = { "too low", "too high" };

	if (breachType < NORMAL)
	{
		printf("To: %s\n", mock_recipient);
		printf("Hi, the temperature is %s \n", breachMsg[breachType]);
		
	}
	alertRaised[TO_EMAIL] = 1;
}

void sendToConsole(BreachType breachType) {

	char* breachMsg[2] = { "too low", "too high" };

	if (breachType < NORMAL)
	{
		printf("Hi, the temperature is %s \n", breachMsg[breachType]);
		
	}
	alertRaised[TO_CONSOLE] = 1;
}
