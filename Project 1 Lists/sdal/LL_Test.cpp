#include <iostream>
#include <cstdio>
#include "List.h"
#include "SSLL.h"
#include "PSLL.h"
#include "SDAL.h"
#include "CDAL.h"
#include "CBL.h"
#include <stdio.h>

using namespace cop3530;

bool SSLL_test() {
	bool outcome = false;
	SSLL<int> LL;
	LL.insert(2,0);
	LL.insert(3,1);
	LL.insert(4,2);
	LL.push_front(1);
	LL.push_back(5);
	if (LL.peek_front() != 1 || LL.peek_back() != 5) {
		return false;
		}
	if (LL.length() != 5) {
		return false;
		}
	LL.replace(5,0);
	LL.replace(4,1);
	LL.replace(3,2);
	LL.replace(2,3);
	LL.replace(1,4);
	if (LL.item_at(0) != 5 || LL.item_at(1) != 4 || LL.item_at(2) != 3 || LL.item_at(3) != 2 || LL.item_at(4) != 1) {
		return false;
		}
	if (LL.length() != 5) {
		return false;
		}
	LL.remove(0);
	LL.remove(0);
	LL.remove(0);
	
	if (LL.length() != 2) {
		return false;
		}
	if (LL.item_at(0) != 2 || LL.item_at(1) != 1) {
		return false;
		}
	LL.clear();
	if (!LL.is_empty()) {
		return false;
		}
	for (int i = 100; i > 0; i--) {
		LL.push_front(i);
		}
	LL.print(std::cout);
	std::cout << LL.length() << std::endl;

	return true;
	
	}
	
bool PSLL_test() {
bool outcome = false;
	PSLL<int> LL;
	LL.insert(2,0);
	LL.insert(3,1);
	LL.insert(4,2);
	LL.push_front(1);
	LL.push_back(5);
	if (LL.peek_front() != 1 || LL.peek_back() != 5) {
		return false;
		}
	if (LL.length() != 5) {
		return false;
		}
	LL.replace(5,0);
	LL.replace(4,1);
	LL.replace(3,2);
	LL.replace(2,3);
	LL.replace(1,4);
	if (LL.item_at(0) != 5 || LL.item_at(1) != 4 || LL.item_at(2) != 3 || LL.item_at(3) != 2 || LL.item_at(4) != 1) {
		return false;
		}
	if (LL.length() != 5) {
		return false;
		}
	LL.remove(0);
	LL.remove(0);
	LL.remove(0);
	
	if (LL.length() != 2) {
		return false;
		}
	if (LL.item_at(0) != 2 || LL.item_at(1) != 1) {
		return false;
		}
    LL.clear();
	if (!LL.is_empty()) {
		return false;
		} 
	for (int i = 100; i > 0; i--) {
		LL.push_front(i);
		}
	LL.print(std::cout);

	return true;
	}
	
bool CBL_test() {
	CBL<int> LL (50);
	LL.insert(2,0);
	LL.insert(3,1);
	LL.insert(4,2);
	LL.push_front(1);
	LL.push_back(5);
	if (LL.peek_front() != 1 || LL.peek_back() != 5) {
		return false;
		}
	if (LL.length() != 5) {
		return false;
		}
	LL.replace(5,0);
	LL.replace(4,1);
	LL.replace(3,2);
	LL.replace(2,3);
	LL.replace(1,4);
	if (LL.item_at(0) != 5 || LL.item_at(1) != 4 || LL.item_at(2) != 3 || LL.item_at(3) != 2 || LL.item_at(4) != 1) {
		return false;
		}
	if (LL.length() != 5) {
		return false;
		}
	LL.remove(0);
	LL.remove(0);
	LL.remove(0);
	
	if (LL.length() != 2) {
		return false;
		}
	if (LL.item_at(0) != 2 || LL.item_at(1) != 1) {
		return false;
		}
	LL.clear();
	if (!LL.is_empty()) {
		return false;
		} 
	for (int i = 100; i > 0; i--) {
		LL.push_front(i);
		}
	LL.print(std::cout);
	std::cout << LL.length() << std::endl;

	return true;
	}
	
bool SDAL_test() {
	SDAL<int> LL;
	LL.insert(2,0);
	LL.insert(3,1);
	LL.insert(4,2);
	LL.push_front(1);
	LL.push_back(5);
	if (LL.peek_front() != 1 || LL.peek_back() != 5) {
		return false;
		}
	if (LL.length() != 5) {
		return false;
		}
	LL.replace(5,0);
	LL.replace(4,1);
	LL.replace(3,2);
	LL.replace(2,3);
	LL.replace(1,4);
	if (LL.item_at(0) != 5 || LL.item_at(1) != 4 || LL.item_at(2) != 3 || LL.item_at(3) != 2 || LL.item_at(4) != 1) {
		return false;
		}
	if (LL.length() != 5) {
		return false;
		}
	LL.remove(0);
	LL.remove(0);
	LL.remove(0);
	
	if (LL.length() != 2) {
		return false;
		}
	if (LL.item_at(0) != 2 || LL.item_at(1) != 1) {
		return false;
		}
	LL.clear();
	if (!LL.is_empty()) {
		return false;
		} 
	for (int i = 100; i > 0; i--) {
		LL.push_front(i);
		} 
	LL.print(std::cout);
	std::cout << LL.length() << std::endl;

	return true;
	}
	
bool CDAL_test() {
	CDAL<int> LL;
	LL.insert(2,0);
	LL.insert(3,1);
	LL.insert(4,2);
	LL.push_front(1);
	LL.push_back(5);
	if (LL.peek_front() != 1 || LL.peek_back() != 5) {
		return false;
		}
	if (LL.length() != 5) {
		return false;
		}
	LL.replace(5,0);
	LL.replace(4,1);
	LL.replace(3,2);
	LL.replace(2,3);
	LL.replace(1,4);
	if (LL.item_at(0) != 5 || LL.item_at(1) != 4 || LL.item_at(2) != 3 || LL.item_at(3) != 2 || LL.item_at(4) != 1) {
		return false;
		}
	if (LL.length() != 5) {
		return false;
		}
	LL.remove(0);
	LL.remove(0);
	LL.remove(0);
	
	if (LL.length() != 2) {
		return false;
		}
	if (LL.item_at(0) != 2 || LL.item_at(1) != 1) {
		return false;
		} 
	LL.clear();
	if (!LL.is_empty()) {
		return false;
		} 
	for (int i = 100; i > 0; i--) {
		LL.push_front(i);
		}
	LL.print(std::cout);
	std::cout << LL.length() << std::endl;

	return true;
	}
	
int main() {
bool result_SSLL = SSLL_test();
	if (result_SSLL == true) {
		std::cout << "success!" << std::endl;
		}
	else {
		std::cout << "failure!" << std::endl;
		} 
		
    bool result_PSLL = PSLL_test();
	if (result_PSLL == true) {
		std::cout << "success!" << std::endl;
		}
	else {
		std::cout << "failure!" << std::endl;
		} 
	
		bool result_CBL = CBL_test();
	if (result_CBL == true) {
		std::cout << "success!" << std::endl;
		}
	else {
		std::cout << "failure!" << std::endl;
		} 
		
	bool result_SDAL = SDAL_test();
	if (result_SDAL == true) {
		std::cout << "success!" << std::endl;
		}
	else {
		std::cout << "failure!" << std::endl;
		} 
		//return 0;
	bool result_CDAL = CDAL_test();
	if (result_CDAL == true) {
		std::cout << "success!" << std::endl;
		}
	else {
		std::cout << "failure!" << std::endl;
		}  
		return 0; 

	

}






