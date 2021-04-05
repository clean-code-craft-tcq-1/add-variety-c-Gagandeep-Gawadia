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
