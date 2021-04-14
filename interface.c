
#include "interface.h"
#include <stdio.h>
#include <string.h>

 int alertRaised[3];
 char * mock_header = NULL;
 char * mock_recipient = NULL;
 char * mock_text = NULL;
 char breachmessage[25] = "Normal";
 char* breachMsg[3] = { "Low", "High","Normal" };

 void concatenateAlertMsg(char *s1, char* s2);

 void  concatenateAlertMsg(char *s1, char* s2)
 {
	 int length = 0; 
	 while (*s1 != '\0') {
		 breachmessage[length] = *s1;
		 ++length;
		 s1++;
	 }
	 // concatenate strings
	 for (int j = 0; *s2 != '\0'; s2++, ++length) {
		 breachmessage[length] = *s2;
	 }
       
	 // terminating the string
	 breachmessage[length] = '\0';
 }
//Mock functions 
//To mock the header in case of controller alert
 void mock_sendtoControllerheader(char * buffer)
 {
	 mock_header = buffer;
 }

//To mock the recipient in case of e-mail alert for testing purpose
 void mock_sendtoEmailrecipient(char * buffer)
 {
	 mock_recipient = buffer;
 }

//Mocking text in case of console print for uniformlity
 void mock_sendtoConsoletext(char * buffer)
 {
	 mock_text = buffer;
 }

void sendToController(BreachType breachType) {

	printf("%s : %s\n", mock_header, breachMsg[breachType]);
	concatenateAlertMsg(mock_header, breachMsg[breachType]);
	alertRaised[TO_CONTROLLER] = 1;
	
}

void sendToEmail(BreachType breachType) {

	if (breachType < NORMAL)
	{
		printf("To: %s\n", mock_recipient);
		printf("Hi, the temperature is %s \n", breachMsg[breachType]);
		concatenateAlertMsg(mock_recipient, breachMsg[breachType]);
		
	}
	else
	{
		concatenateAlertMsg( "", breachMsg[breachType]);
	}
	
	alertRaised[TO_EMAIL] = 1;
}

void sendToConsole(BreachType breachType) {

	if (breachType < NORMAL)
	{
		printf("Hi, the temperature is %s \n", breachMsg[breachType]);
		concatenateAlertMsg(mock_text, breachMsg[breachType]);

	}
	else
	{
               concatenateAlertMsg("", breachMsg[breachType]);
	}
	alertRaised[TO_CONSOLE] = 1;
}
