#pragma once
#ifndef PSLL_H
#define PSLL_H
#include <stdexcept>
#include "List.h"

using namespace std;

namespace cop3530 {
	
	template <typename E>
	class Node {
		public:
			E data;
			Node<E>* next;
				
		};
	
	template <typename E>
	class PSLL : public List<E> {
	public:
		PSLL();
		PSLL(const PSLL &c);
		~PSLL() override;

		void insert(E element, size_t position) override;
		void push_back(E element) override;
		void push_front(E element) override;
		E replace(E element, size_t position) override; //NEED TO MAKE THIS RETURN THE DATA
		E remove(size_t position) override;
		E pop_back(void) override;
		E pop_front(void) override;
		E peek_back(void) override;
		E peek_front(void) override;
		E item_at(size_t position) override;
		bool is_empty(void) override;
		bool is_full(void) override;
		size_t length(void) override;
		void clear(void) override;
		bool contains(E element, bool(*equals_function)(const E&, const E&)) override;
		void print(std::ostream & os) override;
		E* /*const*/ contents(void) override;

	private:
		
		Node<E>* head;
		Node<E>* tail;
		Node<E>* freeHead;
		int freeHead_count;

	public:
		template <typename DataT>
		class PSLL_Iter {
		public:
			// type aliases required for C++ iterator compatibility
			using value_type = DataT;
			using reference = DataT&;
			using pointer = DataT*;
			using difference_type = std::ptrdiff_t;
			using iterator_category = std::forward_iterator_tag;

			// type aliases for prettier code
			using self_type = PSLL_Iter;
			using self_reference = PSLL_Iter&;

		private:
			Node<E>* here;

		public:
			explicit PSLL_Iter(Node<E>* start = nullptr) : here(start) {}
			PSLL_Iter(const PSLL_Iter& src) : here(src.here) {}

			reference operator*() const {
				return here->data;
			}
			pointer operator->() const {
				return &(operator*());
			}

			self_reference operator=(PSLL_Iter<E> const& src) {
				if (this == &src) {
					return (*this);
				}
				here = src.here;
				return *this;
			}

			self_reference operator++() {
				here = here->next;
				return *this;
			} // preincrement

			self_type operator++(int) { //if there's a problem, good chance this is the problem
				PSLL_Iter temp(*this);
				here = here->next;
				return temp;
			} // postincrement

			bool operator==(PSLL_Iter<E> const& rhs) const {
				return(here == rhs.here);

			}
			bool operator!=(PSLL_Iter<E> const& rhs) const {
				return (here != rhs.here);

			}
		
		}; 
	};



template <typename E>
PSLL<E>::PSLL() {
	head = tail = freeHead = nullptr;
	freeHead_count = 0;
}

template <typename E>
PSLL<E>::PSLL(const PSLL &c) {
	*head = *c.head;
	*tail = *c.tail;
	*freeHead = *c.freeHead;
	freeHead_count = c.freeHead_count;
	}

template <typename E>
PSLL<E>::~PSLL() {
	Node<E>* curr = head;
	Node<E>* pre = head;

		while (pre) {
			curr = curr->next;
			delete pre;
			pre = curr;
		}
		head = nullptr;
		tail = nullptr;
		delete head;
		delete tail;
		delete curr;
		delete pre;
		
	Node<E>* curr2 = freeHead;
	Node<E>* pre2 = freeHead;
	
	while (pre2) {
		curr2 = curr2->next;
		delete pre2;
		pre2 = curr2;
		}
		
		head = nullptr;
		delete head;
		delete curr;
		delete pre;
	
	}


template <typename E>
void
PSLL<E>::insert(E element, size_t position) { //adjust this for psll
	Node<E>* temp;
	if (head == nullptr && position == 0) {
		
		if (freeHead) {
			temp = freeHead;
			freeHead = freeHead->next;
			
			freeHead_count--;
		}
		else {
			temp = new Node<E>();
		}
		temp->data = element;
		temp->next = nullptr;
		head = temp;
		tail = temp;
		return;
	}
	if (freeHead) {
		temp = freeHead;
		freeHead = freeHead->next;
		temp->data = element;
	}
	else {
		temp = new Node<E>();
		temp->data = element;
	}

	if (position == 0) {
		temp->next = head;
		head = temp;
	}
	else {
		Node<E>* temp2 = head;
		for (size_t i = 0; i < position-1; i++) {
			temp2 = temp2->next;
		}
		temp->next = temp2->next;
		temp2->next = temp;
	}
	Node<E>* tailCheck = head;
		while (tailCheck->next) {
			tailCheck = tailCheck->next;
			}
			tail = tailCheck;
}

template <typename E>
void
PSLL<E>::push_back(E element) {
	Node<E>* temp;
	if (freeHead) {
		temp = freeHead;
		temp->data = element;
		temp->next = nullptr;
		freeHead = freeHead->next;
		
		freeHead_count--;
	}
	else {
		temp = new Node<E>();
		temp->data = element;
		temp->next = nullptr;
	}

	if (!head) {
		head = temp;
		temp = tail;
	}
	else {
		tail->next = temp;
		temp = tail; //or tail = temp?
	}
	Node<E>* tailCheck = head;
		while (tailCheck->next) {
			tailCheck = tailCheck->next;
			}
	tail = tailCheck;
	
}

template <typename E>
void
PSLL<E>::push_front(E element) {

	insert(element,0);
	

}

template <typename E>
E
PSLL<E>::replace(E element, size_t position) { //WRITE IN CATCHES
	Node<E>* temp = head;
	for (size_t i = 0; i < position; i++) {
		temp = temp->next;
	}
	E data = temp->data;
	temp->data = element;
	return data;
}

template <typename E>
E //PROBABLY SHOULD CHANGE TO E INSTEAD OF SIZE_T
PSLL<E>::remove(size_t position) { 
	Node<E>* temp = head;
	Node<E>* pre = head;

	if (position == 0) {
	
		E data = pop_front();
		return data;
	}
	else {
		size_t i = 0;
		while (i++ != position) {
			pre = temp;
			temp = temp->next;
		}
		if (!temp->next) {
				E data = pop_back();
				return data;
				}
		pre->next = temp->next;
		E data = temp->data;
		if (freeHead_count < 50) {
			temp->next = freeHead;
			freeHead = temp;
			freeHead_count++;
		}
		else {
			delete temp;
		}

		return data;
	}


}

template <typename E>
E
PSLL<E>::pop_back(void) { //
	Node<E>* pre = head;
	Node<E>* temp = head->next;

	while (temp->next) {
		pre = pre->next;
		temp = temp->next;
	}
	E data = temp->data;
	tail = pre;
	if (freeHead_count < 50) {
		pre->next = nullptr;
		temp->next = freeHead;
		freeHead = temp;
		freeHead_count++;
	}
	else {
		delete temp;
	}
	Node<E>* tailCheck = head;
		while (tailCheck->next) {
			tailCheck = tailCheck->next;
			}
	tail = tailCheck;
	return data;
}

template <typename E>
E
PSLL<E>::pop_front(void) {
	Node<E>* temp = head;
	E data = head->data;

	if (head == tail) {
		if (freeHead_count < 50) {
		head->next = freeHead;
		freeHead = head;
		head = nullptr;
		tail = nullptr;
		freeHead_count++;
			}
		else {
			head = nullptr;
			tail = nullptr;
			delete temp;
				
			}
		return data;
	}
	else {
		if (freeHead_count < 50) {
		head = head->next;
		temp->next = freeHead;
		freeHead = temp;
		freeHead_count++;
		}
		else {
		head = temp->next;
		delete temp;	
		}
		return data;
	}
}

template <typename E>
E
PSLL<E>::peek_back(void) {
	E data = tail->data;
	return data;
}

template <typename E>
E
PSLL<E>::peek_front(void) {
	E data = head->data;
	return data;
}

template <typename E>
E
PSLL<E>::item_at(size_t position) {
	if (head == NULL) {
		throw std::runtime_error("SSLL<E>.item_at(): the list is empty!");
	}
	Node<E>* curr = head;
	for (size_t i = 0; i < position; i++) {
		curr = curr->next;
		if (curr == NULL) {
			throw std::runtime_error("SSLL<E>.item_at(): INVALID POSITION");
		}
	}
	return curr->data;


}

template <typename E>
bool
PSLL<E>::is_empty() {
	return (head == NULL);
}

template <typename E>
bool
PSLL<E>::is_full() {
	return false;
}

template <typename E>
size_t
PSLL<E>::length() {
	size_t len = 0;
	Node<E>* curr = head;
	while (curr) {
		++len;
		curr = curr->next;
	}
	return len;
}

template <typename E>
void
PSLL<E>::clear(void) {

		Node<E>* curr = head;
		Node<E>* pre = head;

		while (pre) {
			curr = curr->next;
			delete pre;
			pre = curr;
		}
		head = nullptr;
		tail = nullptr;
		delete head;
		delete tail;
		delete curr;
		delete pre;
	}



template <typename E>
bool
PSLL<E>::contains(E element, bool(*equals_function)(const E&, const E&)) { //'look over this'
	Node<E>* temp = head;

	while (temp != NULL) {
		if (equals_function(temp->data, element)) {
			return true;
		}
		temp = temp->next;
	}

	return false;
}

template <typename E>
void
PSLL<E>::print(std::ostream &os) {
	if (head == NULL) {
		os << "<empty list>" << endl;
	}
	else {
		Node<E>* temp2 = head;

		os << "[";
		while (temp2 != NULL) {
			if (temp2 == tail) {
				os << temp2->data << "]" << endl;
				break;
			}
			else {
				os << temp2->data << ", ";
				temp2 = temp2->next;
			}
		}
	}
}

	template <typename E>
	E* /*const*/
	PSLL<E>::contents(void) {
		if (!head) {
			throw std::runtime_error("PSLL<E>.contents(): The list contains nothing!");
		}
		Node<E>* temp = head;
		E* data = new E[length()]; //is length appropriate here? I guess we'll find out

		for (size_t i = 0; i < length(); i++) { //run through this on paper to make sure it doesnt go over
			data[i] = temp->data;
			temp = temp->next;
		}
		//delete temp;
		return data;

	}





}

#endif
