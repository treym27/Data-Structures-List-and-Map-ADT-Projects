/*#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "AVL.h"

#include <iostream>

//height can vary in AVL tree by because abs(balance) <=1
using namespace cop3530;

bool comparison_function(const int& a, const int& b) {
	if (a < b) {
		return true;
	}
	else {
		return false;
	}
}

bool equals_function(const int& a, const int& b) {
	if (a == b) {
		return true;
	}
	else {
		return false;
	}
}

SCENARIO("Testing Insertion and Lookup") {
	GIVEN ("List of items, with keys being [1,19,5,18,3,8,9] and values being [A,S,E,R,C,H,I]") {
		AVL<int, char, comparison_function, equals_function> * avl = new AVL<int, char, comparison_function, equals_function>;
		
		avl->insert(1,'A');
		avl->insert(19,'S');
		avl->insert(5,'E');
		avl->insert(18,'R');
		avl->insert(3,'C');
		avl->insert(8,'H');
		avl->insert(9,'I');
		
		WHEN("Looking up 5") {
			char value = avl->lookup(5);
			THEN ("The value should be 'E' ") {
				REQUIRE(value == 'E');
			}
		}
		
		WHEN("Looking up 9") {
			char value = avl->lookup(9);
			THEN ("The value should be 'I' ") {
				REQUIRE(value == 'I');
			}
		}
		
		WHEN("Looking up 1") {
			char value = avl->lookup(1);
			THEN ("The value should be 'A' ") {
				REQUIRE(value == 'A');
			}
		}
		
		WHEN("Looking up 19") {
			char value = avl->lookup(19);
			THEN ("The value should be 'S' ") {
				REQUIRE(value == 'S');
			}
		}
		
		WHEN("Looking up 18") {
			char value = avl->lookup(18);
			THEN ("The value should be 'R' ") {
				REQUIRE(value == 'R');
			}
		}
		
		WHEN("Looking up 3") {
			char value = avl->lookup(3);
			THEN ("The value should be 'C' ") {
				REQUIRE(value == 'C');
			}
		}
		
		WHEN("Looking up 8") {
			char value = avl->lookup(8);
			THEN ("The value should be 'H' ") {
				REQUIRE(value == 'H');
			}
		}
		
		WHEN("Testing insertion of new item with same key 3 but value 'Z'") {
			avl->insert(3,'Z');
			char value = avl->lookup(3);
			THEN("The value should be 'Z', not 'C'") {
				REQUIRE(value == 'Z');
			}
		}
		
		delete avl;
	}
}

SCENARIO("Testing removal") {
	GIVEN ("List of items, with keys being [1,19,5,18,3,8,9] and values being [A,S,E,R,C,H,I]") {
		AVL<int, char, comparison_function, equals_function> * avl = new AVL<int, char, comparison_function, equals_function>;
		
		avl->insert(1,'A');
		avl->insert(19,'S');
		avl->insert(5,'E');
		avl->insert(18,'R');
		avl->insert(3,'C');
		avl->insert(8,'H');
		avl->insert(9,'I');
		
		WHEN("Removing 1") {
			avl->remove(1);
			THEN("Looking up 18 should NOT throw an exception") {
				char value = avl->lookup(18);
				REQUIRE(value == 'R');
			}
		}
		
		WHEN("Removing 18") {
			avl->remove(1);
			THEN("Looking up 9 should NOT throw an exception") {
				char value = avl->lookup(9);
				REQUIRE(value == 'I');
			}
		}
		
		WHEN("Removing 9") {
			avl->remove(9);
			THEN("Looking up 3 should NOT throw an exception") {
				char value = avl->lookup(3);
				REQUIRE(value == 'C');
			}
		}
		
		WHEN("Removing 18") {
			avl->remove(18);
			THEN("Looking up 8 should NOT throw an exception") {
				avl->lookup(8);
			}
		}
		
		WHEN("Removing 19") {
			avl->remove(19);
			THEN("Looking up 18 should NOT throw an exception") {
				avl->lookup(18);
			}
		}
		
		delete avl;
	}
}

SCENARIO("Testing balance") {
	GIVEN("List of items, with int keys and values") {
		AVL<int, int, comparison_function, equals_function> * avl = new AVL<int, int, comparison_function, equals_function>;
		
		WHEN("Testing worst case") {
			for (int i = 1; i < 8; i++) {
				avl->insert(i,i);
			}
			int balance = avl->balance();
			THEN("The balance factor should be 0") {
				REQUIRE(balance == 0);
			}
		}
		
		WHEN("Testing a more normal case") {
			avl->insert(50,50);
			avl->insert(25,25);
			avl->insert(10,10);
			avl->insert(5,5);
			avl->insert(7,7);
			avl->insert(3,3);
			avl->insert(30,30);
			avl->insert(20,20);
			avl->insert(8,8);
			avl->insert(15,15);
			int balance = avl->balance();
			THEN("The abs(balance) should be <= 1") {
				REQUIRE(abs(balance) <= 1);
			}
		}
		
		WHEN("Test another normal case") {
			avl->insert(14,14);
			avl->insert(71,71);
			avl->insert(3,3);
			avl->insert(52,52);
			avl->insert(68,68);
			avl->insert(92,92);
			avl->insert(59,59);
			avl->insert(37,37);
			avl->insert(22,22);
			avl->insert(49,49);
			avl->insert(41,41);
			int balance = avl->balance();
			THEN("The abs(balance) should be <= 1") {
				REQUIRE(abs(balance) <= 1);
			}
		}
		
		delete avl;
	}
}

SCENARIO("Testing bonus methods") {
	GIVEN ("List of items, with keys being [1,19,5,18,3,8,9] and values being [A,S,E,R,C,H,I]") {
		AVL<int, char, comparison_function, equals_function> * avl = new AVL<int, char, comparison_function, equals_function>;
		
		avl->insert(1,'A');
		avl->insert(19,'S');
		avl->insert(5,'E');
		avl->insert(18,'R');
		avl->insert(3,'C');
		avl->insert(8,'H');
		avl->insert(9,'I');
		
		
		WHEN("Checking contains for 8") {
			bool x = avl->contains(8);
			THEN("Contains should return true") {
				REQUIRE(x == true);
			}
		}
		
		WHEN("Checking contains for 22") {
			bool x = avl->contains(22);
			THEN("Contains should return false") {
				REQUIRE(x == false);
			}
		}
		
		WHEN("Checking is_empty") {
			bool x = avl->is_empty();
			THEN("Is_empty should return false") {
				REQUIRE(x == false);
			}
		}
		
		WHEN("Clearing and checking is_empty") {
			avl->clear();
			bool x = avl->is_empty();
			THEN("Is_empty should return true") {
				REQUIRE(x == true);
			}
		}
		
		WHEN("Checking is_full") {
			bool x = avl->is_full();
			THEN("Is_full should return false") {
				REQUIRE(x == false);
			}
		}
		
		WHEN("Checking size") {
			size_t size = avl->size();
			THEN("The size should be 7 (there are 7 items)") {
				REQUIRE(size == 7);
			}
		}
		
		WHEN("Checking height") {
			size_t height = avl->height();
			THEN("Height should be 3 or 4") {
				REQUIRE(height >= 3);
				REQUIRE(height <= 4);
			}
		}
		
		WHEN("Checking balance") {
			int balance = avl->balance();
			THEN("Balance should have absolute value <= 1") {
				REQUIRE(std::abs(balance) <= 1);
			}
		}
		
		WHEN("Removing 3") {
			avl->remove(3);
			int balance = avl->balance();
			THEN("Balance should have absolute value <= 1 ") {
				REQUIRE(abs(balance) <= 1);
			}
		}
		
		WHEN("Removing 3, 5, and 9") {
			avl->remove(3);
			avl->remove(5);
			avl->remove(9);
			int balance = avl->balance();
			THEN("Balance should have absolute value <= 1") {
				REQUIRE(abs(balance) <= 1);
			}
		}
		
		delete avl;
	}
}

SCENARIO("Testing 'big five' methods") {
	GIVEN("List of items, with keys being [1,19,5,18,3,8,9] and values being [A,S,E,R,C,H,I]") {
		AVL<int, char, comparison_function, equals_function> avl;
		
		avl.insert(1,'A');
		avl.insert(19,'S');
		avl.insert(5,'E');
		avl.insert(18,'R');
		avl.insert(3,'C');
		avl.insert(8,'H');
		avl.insert(9,'I');
		
		WHEN("Testing copy constructor") {
			AVL<int, char, comparison_function, equals_function> avl2 = avl;
			THEN("New copy should successfully lookup 18") {
				char value = avl2.lookup(18);
				REQUIRE(value == 'R');
			}
		}
	
		WHEN("Testing copy assignment") {
			AVL<int, char, comparison_function, equals_function> avl2;
			//throw in values different from other to ensure assignment works
			avl2.insert(4,'D');
			avl2.insert(2,'B');
			avl2.insert(26,'Z');
			
			avl2 = avl;
			THEN("New copy should succesfully lookup 18") {
				char value = avl2.lookup(18);
				REQUIRE(value == 'R');
			}
		}
		
		WHEN ("Testing move constructor") {
			AVL<int, char, comparison_function, equals_function> avl2(std::move(avl));
			THEN("New copy should successfully lookup 18") {
				char value = avl2.lookup(18);
				REQUIRE(value == 'R');
			}
		}
		
		WHEN("Testing move assignment") {
			AVL<int, char, comparison_function, equals_function> avl2;
			//throw in values different from other to ensure assignment works
			avl2.insert(4,'D');
			avl2.insert(2,'B');
			avl2.insert(26,'Z');
			
			avl2 = std::move(avl);
			THEN("New copy should succesfully lookup 18") {
				char value = avl2.lookup(18);
				REQUIRE(value == 'R');
			}
		}
	}
}

SCENARIO("Testing constant-ness(?)") {
	GIVEN("A constant BST") {
		AVL<int, char, comparison_function, equals_function> * avl = new AVL<int, char, comparison_function, equals_function>;
		
		avl->insert(1,'A');
		avl->insert(19,'S');
		avl->insert(5,'E');
		avl->insert(18,'R');
		avl->insert(3,'C');
		avl->insert(8,'H');
		avl->insert(9,'I');
		
		AVL<int, char, comparison_function, equals_function> const * avl2 = avl;
		
		WHEN("Looking up the key 8") {
			char value = avl2->lookup(8);
			THEN("It should work and return 'H'") {
				REQUIRE(value == 'H');
			}
		}
	
		delete avl;
	}
}
*/
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "AVL.h"

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

SCENARIO("Testing AVL.insert() & AVL.lookup(). . .") {
	GIVEN("Keys 5, 10, 15, 20, 25, and 30 containing A, B, C, D, E, and F, respectively. . .") {
		AVL<int, char, compare, equal> * BST = new AVL<int, char, compare, equal>;

		
		BST->insert(5, 'A');
		BST->insert(10, 'B');
		BST->insert(15, 'C');
		BST->insert(20, 'D');
		BST->insert(25, 'E');
		BST->insert(30, 'F');

		WHEN("AVL->lookup(15)") {
			char value = BST->lookup(15);
			THEN("The value should be C. . .") {
				REQUIRE(value == 'C');
			}
		}
		
		WHEN("AVL->lookup(10)") {
			char value = BST->lookup(10);
			THEN("The value should be B. . .") {
				REQUIRE(value == 'B');
			}
		}

		WHEN("AVL->lookup(5)") {
			char value = BST->lookup(5);
			THEN("The value should be A. . .") {
				REQUIRE(value == 'A');
			}
		}

		WHEN("AVL->lookup(20)") {
			char value = BST->lookup(20);
			THEN("The value should be D. . .") {
				REQUIRE(value == 'D');
			}
		}

		WHEN("AVL->lookup(25)") {
			char value = BST->lookup(25);
			THEN("The value should be E. . .") {
				REQUIRE(value == 'E');
			}
		}

		WHEN("AVL->lookup(30)") {
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

SCENARIO("Testing AVL.remov(). . .") {
	GIVEN("Keys 5, 3, 7, 2, 9, 1, and 11 containing 5, 10, 15, 20, 25, 30, and 35, respectively. . .") {
		AVL<int, int, compare, equal> * BST = new AVL<int, int, compare, equal>;

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

SCENARIO("Testing AVL->contains(). . .") {
	GIVEN("Keys 5, 10, 15, 20, 25, and 30 containing A, B, C, D, E, and F, respectively. . .") {
		AVL<int,char,compare, equal> *BST = new AVL<int,char,compare, equal>;

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

SCENARIO("Testing AVL->is_full() & AVL->is_empty(). . .") {
	GIVEN("Keys 5, 10, 15, 20, 25, and 30 containing A, B, C, D, E, and F, respectively. . .") {
		AVL<int,char,compare, equal> *BST = new AVL<int,char,compare, equal>;

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

SCENARIO("Testing AVL->height() & AVL->size(). . .") {
	GIVEN("Keys 5, 10, 15, 20, 25, and 30 containing A, B, C, D, E, and F, respectively. . .") {
		AVL<int,char,compare, equal> *BST = new AVL<int,char,compare, equal>;

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

SCENARIO("Testing AVL->balance(). . .") {
	GIVEN("Keys = 5, 10, 15, 20, 25, 30 & Values = 'C', 'B', 'R', 'M', 'P', 'H' (respectively)") {
		AVL<int,char,compare, equal> *BST = new AVL<int,char,compare, equal>;

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
			THEN("The balance should equal 0. . .") {
				REQUIRE(value == 0);
		}

		delete BST;
	}
}
}

SCENARIO("Testing AVL->clear(). . .") {
	GIVEN("Keys = 5, 10, 15, 20, 25, 30 & Values = 'C', 'B', 'R', 'M', 'P', 'H' (respectively)") {
		AVL<int,char,compare, equal> *BST = new AVL<int,char,compare, equal>;

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
		AVL<int, char, compare, equal> BST;
		
		BST.insert(5,'A');
		BST.insert(10,'B');
		BST.insert(15,'C');
		BST.insert(20,'D');
		BST.insert(25,'E');
		BST.insert(30,'F');
		
		WHEN("Checking the copy constructor. . .") {
			AVL<int, char, compare, equal> CCBST = BST;
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
			AVL<int, char, compare, equal> CABST = BST;
			
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
			AVL<int, char, compare, equal> MABST;
			
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
			AVL<int, char, compare, equal> MCBST(std::move(BST));
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

