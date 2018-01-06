#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "CBL.h"

#include <iostream>

using namespace cop3530;
bool equals_function (const int& one, const int& two) {
	if (one == two) {
		return true;
	}
	else {
		return false;
	}
}

SCENARIO("Testing the functions. . .") {
	GIVEN ("A list of integers of length == 5. . .") {
		
	//	List<int> * CBL = new CBL<int>(5);
		CBL<int> CBL;
		CBL.push_back(5);
		CBL.push_front(17);
		CBL.insert(0,0);
		CBL.insert(2,2);
		CBL.print(std::cout);
		
		WHEN ("Checking length. . .") {
			size_t length = CBL.length();
			THEN ("Length should be 4") {
				REQUIRE(length == 4);
			}
		}
		
		WHEN("Checking if empty. . .") {
			bool empty = CBL.is_empty();
			THEN("Returns false. . .") {
				REQUIRE(empty == false);
			}
		}
		
		WHEN("Peeking front. . .") {
			size_t front = CBL.peek_front();
			THEN ("THe front should equal 0. . .") {
				REQUIRE(front == 0);
			}
		}
		
		WHEN("Peeking back. . .") {
			size_t back = CBL.peek_back();
			THEN ("The back should equal 5. . .") {
				REQUIRE(back == 5);
			}
		}
		
		WHEN("Peeking at the 1 position. . .") {
			size_t ret = CBL.item_at(1);
			THEN("It should equal 17. . .") {
				REQUIRE(ret == 17);
			}
		}
		
		WHEN("Using contents. . .") {
			int * t_arr = CBL.contents();
			size_t length = CBL.length();
			THEN ("Array == [0,17,2,5]. . . .") {
				size_t arr[4] = {0,17,2,5};
				for(size_t i = 0; i < length; i++) {
					REQUIRE(t_arr[i] == arr[i]);
				}
			}
			delete[] t_arr;
		}
		
		WHEN("Replacing 7 at position 2.  .") {
			CBL.replace(7,2);
			size_t item = CBL.item_at(2);
			THEN ("Item at position 2 should be 7") {
				REQUIRE(item == 7);
			}
		}
		
		WHEN("Removing position 0. . .") {
			size_t ret = CBL.remove(0);
			THEN("The value should equal 0. . .") {
				REQUIRE(ret == 0);
			}
		}
		
		WHEN("Popping the front. . .") {
			size_t front = CBL.pop_front();
			THEN("The front should be 1") {
				REQUIRE(front == 0);
			}
		}
		
		WHEN("Popping the back. . .") {
			size_t back = CBL.pop_back();
			THEN("REturns 5. . .") {
				REQUIRE(back == 5);
			}
		}
		
		WHEN("Clearing. . .") {
			CBL.clear();
			size_t len = CBL.length();
			THEN("The length should be 0") {
				REQUIRE(len == 0);
			}
		}

		
	}
}

SCENARIO("Testing the circular compatability. . .") {
	GIVEN("A arbitrary CBL. . .") {

		CBL<int> CBL;
		CBL.push_back(3);
		CBL.push_back(6);
		CBL.pop_front();
		CBL.push_back(1);
		CBL.pop_front();
		CBL.push_back(2);
		CBL.pop_front();
		CBL.push_back(9);
		CBL.pop_front();
		CBL.print(std::cout);
		
		WHEN("Push 7 back on the tail index. . .") {
			CBL.push_back(7);
			size_t tail = CBL.peek_back();
			THEN("Tail value should be 5") {
				REQUIRE(tail == 7);
			}
		}

		
		WHEN("Inserting 10 at position 2. . .") {
			CBL.insert(10,0);
			size_t ret = CBL.item_at(0);
			THEN("Returns 10. . .") {
				REQUIRE(ret == 10);
			}
		}

	}
}

SCENARIO("Testing the expand ability. . .") {
	GIVEN("AN arbitraty SBL of size 5. . .") {
		
		CBL<int> CBL(5);
		CBL.push_back(3);
		CBL.push_front(1);
		CBL.insert(0,0);
		CBL.insert(2,2);
		CBL.print(std::cout);
		
		WHEN("Pushing 4 to back") {
			CBL.push_back(22);
			size_t ret = CBL.peek_back();
			THEN ("It should return 22. . .") {
				REQUIRE(ret == 22);
			}
		}
		
		WHEN("Pushing back. . .") {
			CBL.push_back(1);
			CBL.push_back(1);
			CBL.push_back(1);
			CBL.push_back(1);
			size_t ret = CBL.peek_back();
			THEN("1 should be returned. . .") {
				REQUIRE(ret == 1);
			}
		}

	}
}

SCENARIO("Testing the shrink ability. . .") {
	GIVEN("An arbitrary CBL of size 3. . .") {
		
		//List<int> * CBL = new CBL<int>(3);
		CBL<int> CBL(3);
		CBL.push_back(2);
		CBL.push_back(7);
		CBL.push_back(1);
		CBL.push_front(1);
		CBL.insert(0,0);
		CBL.print(std::cout);
		
	/*	WHEN("Array is forced to expand and then shrink. . .") {
			CBL.push_back(2);
			CBL.push_back(2);
			CBL.push_back(3);
			CBL.push_back(4);
			CBL.pop_back();
			CBL.pop_back();
			CBL.pop_back();
			CBL.pop_back();
			size_t item = CBL.pop_back();
			THEN("The back of the list should be 2") {
				REQUIRE(item == 2);
			}
		} */
	}
}
