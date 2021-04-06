#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

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

	int const NoofTestCases = 3;
	test_InputStructure  test_InputMatrix[NoofTestCases] = { {TO_CONSOLE  , { PASSIVE_COOLING ,  ""  }, 12},
								 {TO_CONTROLLER,{ HI_ACTIVE_COOLING, ""  }, 12},
								 {TO_EMAIL     ,{ MED_ACTIVE_COOLING, "" }, 12},
	};
	double test_OutputMatrix[NoofTestCases] = {  { SUCCESS },
		                                     { SUCCESS },
						     { FAILURE },

	};

	for (int TestCaseNr = 0; TestCaseNr < NoofTestCases; TestCaseNr++) {
		REQUIRE((checkAndAlert(test_InputMatrix[TestCaseNr].alertTarget, test_InputMatrix[TestCaseNr].batteryChar,
			test_InputMatrix[TestCaseNr].temperatureInC) == test_OutputMatrix[TestCaseNr]))<< "Test case failed in iteration : %d"<< TestCaseNr+1;
	}
	
}

TEST_CASE("returns success when sendToEmail is executed ") {
	
	BreachType breachType[3] = {TOO_HIGH,TOO_LOW,NORMAL};
	
	for (int TestCaseNr = 0;TestCaseNr < 3;TestCaseNr++) {
		REQUIRE((sendToEmail(breachType[TestCaseNr]) == SUCCESS));
	}
}

TEST_CASE("returns success when sendToConsole is executed ") {
	
	BreachType breachType[3] = {TOO_HIGH,TOO_LOW,NORMAL};
	
	for (int TestCaseNr = 0;TestCaseNr < 3;TestCaseNr++) {
		REQUIRE((sendToConsole(breachType[TestCaseNr]) == SUCCESS));
	}
}

TEST_CASE("returns success when sendToController is executed ") {
	
	BreachType breachType[3] = {TOO_HIGH,TOO_LOW,NORMAL};
	
	for (int TestCaseNr = 0;TestCaseNr < 3;TestCaseNr++) {
		REQUIRE((sendToController(breachType[TestCaseNr]) == SUCCESS));
	}
}
