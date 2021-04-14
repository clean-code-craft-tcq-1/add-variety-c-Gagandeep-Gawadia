#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"
#include "interface.h"

extern int alertRaised[3];
extern char  breachmessage[25];

TEST_CASE("infers the breach according to limits") {
  
  int const NoofTestCases = 6;
  double test_InputMatrix[NoofTestCases][3] = { {0,0,0},  
	                                        {12,10,30},//NORMAL
						{9,10,30},//TOO_LOW
						{35,10,30},//TOO_HIGH
	                                        {10,10,30}, //BOUNDARY_CONDITION
						{30,10,30 }, //BOUNDARY_CONDITION
	                                           };

 double test_OutputMatrix[NoofTestCases] = { { NORMAL  },
					     { NORMAL  },
					     { TOO_LOW },
					     { TOO_HIGH},
					     { NORMAL  },
					     { NORMAL  },
	                                   };
  
  for (int TestCaseNr = 0; TestCaseNr < NoofTestCases; TestCaseNr++){
	
  REQUIRE((inferBreach(test_InputMatrix[TestCaseNr][0], test_InputMatrix[TestCaseNr][1],
			                 test_InputMatrix[TestCaseNr][2]) == test_OutputMatrix[TestCaseNr]));
  }
}

TEST_CASE("checks the if temperature is within limits based on cooling type and alerts if required") {
	typedef struct 
	{ 
		CoolingType coolingType;
		double temperatureInC;
	}test_InputStructure;

	int const NoofTestCases = 3;
	test_InputStructure  test_InputMatrix[NoofTestCases] = { { PASSIVE_COOLING    , 12 },
	                                                         { HI_ACTIVE_COOLING  , 0 },
	                                                         { MED_ACTIVE_COOLING , 50 },
	                                                       };
	double test_OutputMatrix[NoofTestCases] = {  { NORMAL },
                                                     { NORMAL },
	                                             { TOO_HIGH}
						  };
	
	for (int TestCaseNr = 0; TestCaseNr < NoofTestCases; TestCaseNr++){
	
        REQUIRE((classifyTemperatureBreach(test_InputMatrix[TestCaseNr].coolingType, test_InputMatrix[TestCaseNr].temperatureInC) 
			      == test_OutputMatrix[TestCaseNr]));

	}
}

TEST_CASE("infers the breach according to limits based on cooling type ") {
	typedef struct
	{
		AlertTarget alertTarget;
		BatteryCharacter batteryChar;
		double temperatureInC;
	}test_InputStructure;

	
	int const NoofTestCases = 5;
	test_InputStructure  test_InputMatrix[NoofTestCases] = { {TO_CONTROLLER, { PASSIVE_COOLING ,  ""  }, 12},
															 { TO_EMAIL,     { MED_ACTIVE_COOLING, "" }, 60},
															 { TO_EMAIL,     { MED_ACTIVE_COOLING, "" }, 12 },
															 { TO_CONSOLE,   { MED_ACTIVE_COOLING, "" }, 60 },
															 { TO_CONSOLE,   { MED_ACTIVE_COOLING, "" }, 12 },

	};

	const char *output_message[NoofTestCases]            = {"feed_1Normal",
								"anonymousHigh",
								"Normal",
								"Temp is High",
								"Normal"};
	
	
	char * buffer[3]      = { "feed_1","anonymous","Temp is " };
	void(*mock[3])(char*) = { mock_sendtoControllerheader ,mock_sendtoEmailrecipient, mock_sendtoConsoletext };
	

	for (int TestCaseNr = 0; TestCaseNr < NoofTestCases; TestCaseNr++) {
		
		alertRaised[test_InputMatrix[TestCaseNr].alertTarget]=0;

		mock[test_InputMatrix[TestCaseNr].alertTarget](buffer[test_InputMatrix[TestCaseNr].alertTarget]);
	
		checkAndAlert(test_InputMatrix[TestCaseNr].alertTarget, test_InputMatrix[TestCaseNr].batteryChar,
			test_InputMatrix[TestCaseNr].temperatureInC) ;
		
		
	        //Expected result 
		REQUIRE(alertRaised[test_InputMatrix[TestCaseNr].alertTarget] == 1);
		REQUIRE((strcmp(breachmessage, output_message[TestCaseNr]))==0);
		
	}
	
}

