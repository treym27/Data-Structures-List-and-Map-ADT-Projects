#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "BSTROOT.h"

#include <iostream>

using namespace cop3530;

bool compare(const int& a, const int& b) {
	if (a < b) {
		return true;
	}
	else {
		return false;
	}
}

bool equal(const int& a, const int& b) {
	if (a == b) {
		return true;
	}
	else {
		return false;
	}
}

SCENARIO("Testing BSTROOT.insert() & BSTROOT.lookup(). . .") {
	GIVEN("Keys 5, 10, 15, 20, 25, and 30 containing A, B, C, D, E, and F, respectively. . .") {
		BSTROOT<int, char, compare, equal> * BST = new BSTROOT<int, char, compare, equal>;

		
		BST->insert(5, 'A');
		BST->insert(10, 'B');
		BST->insert(15, 'C');
		BST->insert(20, 'D');
		BST->insert(25, 'E');
		BST->insert(30, 'F');

		WHEN("BSTROOT->lookup(15)") {
			char value = BST->lookup(15);
			THEN("The value should be C. . .") {
				REQUIRE(value == 'C');
			}
		}
		
		WHEN("BSTROOT->lookup(10)") {
			char value = BST->lookup(10);
			THEN("The value should be B. . .") {
				REQUIRE(value == 'B');
			}
		}

		WHEN("BSTROOT->lookup(5)") {
			char value = BST->lookup(5);
			THEN("The value should be A. . .") {
				REQUIRE(value == 'A');
			}
		}

		WHEN("BSTROOT->lookup(20)") {
			char value = BST->lookup(20);
			THEN("The value should be D. . .") {
				REQUIRE(value == 'D');
			}
		}

		WHEN("BSTROOT->lookup(25)") {
			char value = BST->lookup(25);
			THEN("The value should be E. . .") {
				REQUIRE(value == 'E');
			}
		}

		WHEN("BSTROOT->lookup(30)") {
			char value = BST->lookup(30);
			THEN("The value should be F. . .") {
				REQUIRE(value == 'F');
			}
		}

		WHEN("Testing overwriting of a value. . .") {
			BST->insert(25, 'G');
			char value = BST->lookup(25);
			THEN("The value should be G. . .") {
				REQUIRE(value == 'G');
			}
		}

		delete BST;
	}
}

SCENARIO("Testing BSTROOT.remov(). . .") {
	GIVEN("Keys 5, 3, 7, 2, 9, 1, and 11 containing 5, 10, 15, 20, 25, 30, and 35, respectively. . .") {
		BSTROOT<int, int, compare, equal> * BST = new BSTROOT<int, int, compare, equal>;

		BST->insert(5, 5);
		BST->insert(3, 10);
		BST->insert(7, 15);
		BST->insert(2, 20);
		BST->insert(9, 25);
		BST->insert(1, 30);
		BST->insert(11, 35);

		WHEN("Removing key 5. . .") {
			BST->remove(5);
			THEN("Looking up other values should still work. . .") {
				int value = BST->lookup(3);
				int value2 = BST->lookup(7);
				int value3 = BST->lookup(2);
				int value4 = BST->lookup(9);
				int value5 = BST->lookup(1);
				int value6 = BST->lookup(11);
				REQUIRE(value == 10);
				REQUIRE(value2 == 15);
				REQUIRE(value3 == 20);
				REQUIRE(value4 == 25);
				REQUIRE(value5 == 30);
				REQUIRE(value6 == 35);
			}
		}

		WHEN("Removing key 3. . .") {
			BST->remove(3);
			THEN("Looking up other values should still work. . .") {
				int value2 = BST->lookup(7);
				int value3 = BST->lookup(2);
				int value4 = BST->lookup(9);
				int value5 = BST->lookup(1);
				int value6 = BST->lookup(11);
				REQUIRE(value2 == 15);
				REQUIRE(value3 == 20);
				REQUIRE(value4 == 25);
				REQUIRE(value5 == 30);
				REQUIRE(value6 == 35);
			}
		}

		WHEN("Removing key 7. . .") {
			BST->remove(7);
			THEN("Looking up other values should still work. . .") {
				int value3 = BST->lookup(2);
				int value4 = BST->lookup(9);
				int value5 = BST->lookup(1);
				int value6 = BST->lookup(11);
				REQUIRE(value3 == 20);
				REQUIRE(value4 == 25);
				REQUIRE(value5 == 30);
				REQUIRE(value6 == 35);
			}
		}

		WHEN("Removing key 2. . .") {
			BST->remove(2);
			THEN("Looking up other values should still work. . .") {
				int value4 = BST->lookup(9);
				int value5 = BST->lookup(1);
				int value6 = BST->lookup(11);
				REQUIRE(value4 == 25);
				REQUIRE(value5 == 30);
				REQUIRE(value6 == 35);
			}
		}

		WHEN("Removing key 9. . .") {
			BST->remove(9);
			THEN("Looking up other values should still work. . .") {
				int value5 = BST->lookup(1);
				int value6 = BST->lookup(11);
				REQUIRE(value5 == 30);
				REQUIRE(value6 == 35);
			}
		}
		WHEN("Checking if root is still valid. . .") {
			int value = BST->lookup(1);
			THEN("The root's value should be 30. . .") {
				REQUIRE(value == 30);
				}
			}

		delete BST;
	}
}

SCENARIO("Testing BSTROOT->contains(). . .") {
	GIVEN("Keys 5, 10, 15, 20, 25, and 30 containing A, B, C, D, E, and F, respectively. . .") {
		BSTROOT<int,char,compare, equal> *BST = new BSTROOT<int,char,compare, equal>;

		BST->insert(5, 'A');
		BST->insert(10, 'B');
		BST->insert(15, 'C');
		BST->insert(20, 'D');
		BST->insert(25, 'E');
		BST->insert(30, 'F');

		WHEN("Checking the tree for 'Cat' at key 5. . .") {
			bool value = BST->contains(5);
			THEN("The char 'Cat' should be found here. . .") {
				REQUIRE(value == true); //FAILED
			}
		}

		WHEN("Checking the tree for 'B' at key 10. . .") {
			bool value = BST->contains(10);
			THEN("The char 'B' should be found here. . .") {
				REQUIRE(value == true); //FAILED
			}
		}

		WHEN("Checking the tree for 'Rat' at key 15. . .") {
			bool value = BST->contains(5);
			THEN("The char 'Cat' should be found here. . .") {
				REQUIRE(value == true); //FAILED
			}
		}

		delete BST;
	}
}

SCENARIO("Testing BSTROOT->is_full() & BSTROOT->is_empty(). . .") {
	GIVEN("Keys 5, 10, 15, 20, 25, and 30 containing A, B, C, D, E, and F, respectively. . .") {
		BSTROOT<int,char,compare, equal> *BST = new BSTROOT<int,char,compare, equal>;

		BST->insert(5, 'A');
		BST->insert(10, 'B');
		BST->insert(15, 'C');
		BST->insert(20, 'D');
		BST->insert(25, 'E');
		BST->insert(30, 'F');
		
		

		WHEN("Checking if the tree is full. . .") {
			bool value = BST->is_full();
			THEN("It should not be full and return false. . .") {
				REQUIRE(value == false);
			}
		}

		WHEN("Checking to see if the tree is empty. . .") {
			bool value = BST->is_empty();
			THEN("It should not be empty and return false. . .") {
				REQUIRE(value == false);
			}
		} 

		delete BST;
	}
}

SCENARIO("Testing BSTROOT->height() & BSTROOT->size(). . .") {
	GIVEN("Keys 5, 10, 15, 20, 25, and 30 containing A, B, C, D, E, and F, respectively. . .") {
		BSTROOT<int,char,compare, equal> *BST = new BSTROOT<int,char,compare, equal>;

		BST->insert(5, 'A');
		BST->insert(10, 'B');
		BST->insert(15, 'C');
		BST->insert(20, 'D');
		BST->insert(25, 'E');
		BST->insert(30, 'F');

		WHEN("Checking the size of the tree. . .") {
			size_t value = BST->size();
			THEN("The size of the tree should equal 6. . .") {
				REQUIRE(value == 6);
			}
		}

		WHEN("Checking the height of the tree. . .") {
			int value = BST->height();
			THEN("The height of the tree should equal 6. . .") {
				REQUIRE(value <= 6);
				REQUIRE(value > 1); //FAILED
			}
		}

		delete BST;
	}
}

SCENARIO("Testing BSTROOT->balance(). . .") {
	GIVEN("Keys = 5, 10, 15, 20, 25, 30 & Values = 'C', 'B', 'R', 'M', 'P', 'H' (respectively)") {
		BSTROOT<int,char,compare, equal> *BST = new BSTROOT<int,char,compare, equal>;

		BST->insert(5, 'C');
		BST->insert(10, 'B');
		BST->insert(15, 'R');
		BST->insert(20, 'M');
		BST->insert(25, 'P');
		BST->insert(30, 'H');

		WHEN("Checking the height of the tree. . .") {
			int value = BST->height();
			THEN("The height of the tree should equal 6. . .") {
				REQUIRE(value <= 6);
				REQUIRE(value > 1); //FAILED
			}
		}

		WHEN("Balancing the tree. . .") {
			int value = BST->balance();
			THEN("The balance should equal 5. . .") {
				REQUIRE(value == 5);
		}

		delete BST;
	}
}
}

SCENARIO("Testing BSTROOT->clear(). . .") {
	GIVEN("Keys = 5, 10, 15, 20, 25, 30 & Values = 'C', 'B', 'R', 'M', 'P', 'H' (respectively)") {
		BSTROOT<int,char,compare, equal> *BST = new BSTROOT<int,char,compare, equal>;

		BST->insert(5, 'C');
		BST->insert(10, 'B');
		BST->insert(15, 'R');
		BST->insert(20, 'M');
		BST->insert(25, 'P');
		BST->insert(30, 'H');

		WHEN("Checking to see if the tree is empty. . .") {
			bool value = BST->is_empty();
			THEN("It should not be empty and return false. . .") {
				REQUIRE(value == false);
			}
		}

		WHEN("Clearing the tree. . .") {
			BST->clear();
			bool value = BST->is_empty();
			THEN("The tree should be empty and is_empty should return true. . .") {
				REQUIRE(value == true);
			}
		}

		delete BST;
	}
}


SCENARIO("Testing the big five. . .") {
	GIVEN("Keys 5, 10, 15, 20, 25, and 30 containing A, B, C, D, E, and F, respectively. . .") {
		BSTROOT<int, char, compare, equal> BST;
		
		BST.insert(5,'A');
		BST.insert(10,'B');
		BST.insert(15,'C');
		BST.insert(20,'D');
		BST.insert(25,'E');
		BST.insert(30,'F');
		
		WHEN("Checking the copy constructor. . .") {
			BSTROOT<int, char, compare, equal> CCBST = BST;
			THEN("Looking up values. . .") {
				char value = CCBST.lookup(5);
				char value2 = CCBST.lookup(10);
				char value3 = CCBST.lookup(15);
				char value4 = CCBST.lookup(20);
				char value5 = CCBST.lookup(25);
				char value6 = CCBST.lookup(30);
				REQUIRE(value == 'A');
				REQUIRE(value2 == 'B');
				REQUIRE(value3 == 'C');
				REQUIRE(value4 == 'D');
				REQUIRE(value5 == 'E');
				REQUIRE(value6 == 'F');
			}
		}
	
		WHEN("Checking the copy assignment. . .") {
			BSTROOT<int, char, compare, equal> CABST = BST;
			
			THEN("Looking up values. . .") {
				char value = CABST.lookup(5);
				char value2 = CABST.lookup(10);
				char value3 = CABST.lookup(15);
				char value4 = CABST.lookup(20);
				char value5 = CABST.lookup(25);
				char value6 = CABST.lookup(30);
				REQUIRE(value == 'A');
				REQUIRE(value2 == 'B');
				REQUIRE(value3 == 'C');
				REQUIRE(value4 == 'D');
				REQUIRE(value5 == 'E');
				REQUIRE(value6 == 'F');
			}
		}
		
		WHEN("Checking the move assignment. . .") {
			BSTROOT<int, char, compare, equal> MABST;
			
			MABST = std::move(BST);
			THEN("Looking up values. . .") {
				char value = MABST.lookup(5);
				char value2 = MABST.lookup(10);
				char value3 = MABST.lookup(15);
				char value4 = MABST.lookup(20);
				char value5 = MABST.lookup(25);
				char value6 = MABST.lookup(30);
				REQUIRE(value == 'A');
				REQUIRE(value2 == 'B');
				REQUIRE(value3 == 'C');
				REQUIRE(value4 == 'D');
				REQUIRE(value5 == 'E');
				REQUIRE(value6 == 'F');
			}
		}
		
		WHEN ("Checking the move constructor. . .") {
			BSTROOT<int, char, compare, equal> MCBST(std::move(BST));
			THEN("Looking up values. . .") {
				char value = MCBST.lookup(5);
				char value2 = MCBST.lookup(10);
				char value3 = MCBST.lookup(15);
				char value4 = MCBST.lookup(20);
				char value5 = MCBST.lookup(25);
				char value6 = MCBST.lookup(30);
				REQUIRE(value == 'A');
				REQUIRE(value2 == 'B');
				REQUIRE(value3 == 'C');
				REQUIRE(value4 == 'D');
				REQUIRE(value5 == 'E');
				REQUIRE(value6 == 'F');
			}
		}
		
		
	}
}



