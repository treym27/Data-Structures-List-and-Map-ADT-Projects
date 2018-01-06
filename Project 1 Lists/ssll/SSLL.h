
//#pragma once
#ifndef SSLL_H
#define SSLL_H
#include <stdexcept>
#include <stdio.h>
#include "List.h"
#include <iostream>


using namespace cop3530;

namespace cop3530 {
	template <typename E>
	class SSLL : public List<E> {

	private:
		struct Node {
			E data;
			Node* next;
		};
		Node* head;
		Node* tail;
		Node* tailCheck;
		

	public:
		SSLL();
		SSLL(const SSLL &c);
		~SSLL() override;
	//	SSLL<E>& operator= (const SSLL* c);
		SSLL(SSLL& other);
		//SSLL<E>& operator= (SSLL&& m);

		void insert(E element, size_t position) override;
		void push_back(E element) override;
		void push_front(E element) override;
		E replace(E element, size_t position) override;
		E remove(size_t position) override;
		E pop_back() override;
		E pop_front() override;
		E peek_back() override;
		E peek_front() override;
		E item_at(size_t position) override;
		bool is_empty() override;
		bool is_full() override;
		size_t length() override;
		void clear() override;
		bool contains(E element, bool(*equals_function)(const E&, const E&)) override;
		void print(std::ostream & os) override;
		E* /*const*/ contents() override;

	public:
		template <typename DataT>
		class SSLL_Iter
		{
		public:
			// type aliases required for C++ iterator compatibility
			using value_type = DataT;
			using reference = DataT&;
			using pointer = DataT*;
			using difference_type = std::ptrdiff_t;
			using iterator_category = std::forward_iterator_tag;

			// type aliases for prettier code
			using self_type = SSLL_Iter;
			using self_reference = SSLL_Iter&;

		private:
			Node* here;

		public:
			explicit SSLL_Iter(Node* start = nullptr) : here(start) {}
			SSLL_Iter(const SSLL_Iter& src) : here(src.here) {}

			reference operator*() const {
				return here->data;
			}
			pointer operator->() const {
				return &(operator*());
			}

			self_reference operator=(SSLL_Iter<E> const& src) {
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

			self_type operator++(int) {
				SSLL_Iter temp(*this);
				here = here->next;
				return temp;
			} // postincrement

			bool operator==(SSLL_Iter<E> const& rhs) const {
				return(here == rhs.here);

			}
			bool operator!=(SSLL_Iter<E> const& rhs) const {
				return (here != rhs.here);

			}
		
		}; // end SSLL_Iter 
		

	};
		
 
    template <typename L>
    SSLL<L>::SSLL() {
        head = nullptr;
        tail = nullptr;
    }

  
    template <typename L>
    SSLL<L>::SSLL(const SSLL &c) {
        *head = *c.head;
        *tail = *c.tail;
    }

 
 
    template <typename L>
    SSLL<L>::~SSLL() {
        clear();
        delete head;
    }




	template <typename E>
	void
	SSLL<E>::insert(E element, size_t position) {
		Node* temp = new Node();
		temp->data = element;

		if (position != 0 && head == NULL || position < 0) {
			throw std::runtime_error("SSLL<E>.insert(): INVALID POSITION");
		}
		else if (length() < position) {
			throw std::runtime_error("SSLL<E>.insert(): POSITION IS OUT OF BOUNDS.");
			}
		else if (position == 0  && head == NULL) {
			head = temp;
			tail = temp; //ehhhh
			temp->next = nullptr;
		}
		else if (position == 0) { //CHECK THIS
			temp->next = head;
			head = temp;
		}
		else {
			Node* temp2 = head;
			size_t i = 0;
			while (++i != position) { //size_t???
				temp2 = temp2->next;
			}
			temp->next = temp2->next;
			temp2->next = temp;
		}
		tailCheck = head;
		while (tailCheck->next) {
			tailCheck = tailCheck->next;
			}
			tail = tailCheck;
	}
	
	

	template <typename E>
	void
	SSLL<E>::push_back(E element) { //FINAL
		
		Node* temp = new Node();
		temp->data = element;
		temp->next = nullptr;
		Node* temp2 = head;
		if (!head) {
			head = temp;
			tail = head;
		}
		else {
			tail->next = temp;
			tail = temp;
		}
		Node* tailCheck = head;
		while (tailCheck->next) {
			tailCheck = tailCheck->next;
			}
			tail = tailCheck;
	}

	template <typename E>
	void
		SSLL<E>::push_front(E element) { //FINAL
		Node* temp = new Node();
		temp->data = element;
		temp->next = nullptr;

		if (!head) {
			head = temp;
			tail = temp;
			//tail->next = nullptr;
		}
		else {
			temp->next = head;
			head = temp;
		}
	}

	template <typename E>
	E
	SSLL<E>::replace(E element, size_t position) { //FINAL
		Node* temp = head;
		for (size_t i = 0; i < position; i++) { //size_t???
			temp = temp->next;
			if (!temp) {
				throw std::runtime_error("SSLL<E>.replace: OUT OF BOUNDS");
			}
		}
		E data = temp->data;
		temp->data = element;
		return data;
	}

	template <typename E>
	E
	SSLL<E>::remove(size_t position) { //logic is sound

		
		if (head == NULL) {
			throw std::runtime_error("SSLL<E>.remove(): NOTHING TO REMOVE");
		}
		Node* temp = head;
		Node* temp2 = head;
		E data;
		if (position == 0) {	

		data = pop_front();
			return data;
		}
		else {
			size_t i = 0;
			while (i++ != position) { //originally has pos - 1 but this is wrong?
				temp2 = temp;
				temp = temp->next;
				if (!temp){
					throw std::runtime_error("SSLL<E>.remove: OUT OF BOUNDS");
					}
			}

			if (!temp->next) {
				data = pop_back();
				return data;
				}
			data = temp->data;
			temp2->next = temp->next;
			delete temp;
			return data;
		}
	}

	template <typename E>
	E
	SSLL<E>::pop_back() {
		if (head == NULL) {
			throw std::runtime_error("SSLL<E>.pop_back():NOTHING TO POP");
		}
		Node* temp = head;
		while (temp->next->next != NULL) {
			temp = temp->next;
		}
		Node* temp2 = temp->next;
		temp->next = temp2->next;


		E ans = temp2->data;
		delete temp2; //find a potential way to replace free
		
		tailCheck = head;
		while (tailCheck->next) {
			tailCheck = tailCheck->next;
			}
			tail = tailCheck;
			//delete tailCheck;

		return ans;
	}

	template <typename E>
	E
	SSLL<E>::pop_front(void) {
		if (head == NULL) {
			throw std::runtime_error("SSLL<E>.pop_front(): NOTHING TO POP");
		}

		E ans = head->data;

		Node* temp = head;
		head = temp->next;
		delete temp;

		return ans;
	}

	template <typename E>
	E
	SSLL<E>::peek_back(void) {
		if (head == NULL) {
			throw std::runtime_error("SSLL<E>.peek_back(): NOTHING TO PEEK");
		}
		return tail->data;

	}

	template <typename E>
	E
	SSLL<E>::peek_front(void) {
		if (head == NULL) {
			throw std::runtime_error("SSLL<E>.peek_front(): NOTHING TO PEEK");
		}
		return head->data;
	}

	template <typename E>
	E
	SSLL<E>::item_at(size_t position) { //'look back' at this

		if (head == NULL) {
			throw std::runtime_error("SSLL<E>.item_at(): the list is empty!");
		}
		Node* temp = head;
		for (size_t i = 0; i < position; i++) {
			temp = temp->next;
			if (temp == NULL) {
				throw std::runtime_error("SSLL<E>.item_at(): INVALID POSITION");
			}
		}
		E data = temp->data;
		return data;
		


	}

	template <typename E>
	bool
	SSLL<E>::is_empty(void) {
		return (head == NULL);
	}

	template <typename E>
	bool
	SSLL<E>::is_full(void) {
		return false;
	}

	template <typename E>
	size_t
	SSLL<E>::length(void) {
		size_t len = 0;
		Node* curr = head;
		while (curr) {
			++len;
			curr = curr->next;
		}
		return len;
	}

	template <typename E>
	void
	SSLL<E>::clear(void) { //this may be flawed
	
		Node* curr = head;
		Node* pre = head;

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
	equals_function(E a, E b) {
		return a == b;
	}

	template <typename E>
	bool
		SSLL<E>::contains(E element, bool(*equals_function)(const E&, const E&)) {
		Node* temp = head;
		while (temp != NULL) {
			if (equals_function(temp->data, element)) {
				return true;
			}
			else {
				temp = temp->next;
			}
		}
		return false;
	}

	template <typename E>
	void
	SSLL<E>::print(std::ostream &os) { //'look at this again'
		if (!head) {
			os << "<empty list>" << endl;
		}
		else {
			Node* tester = head;

			os << "[";
				while (tester != NULL) {
					if (tester == tail) {
						os << tester->data << "]" << endl;
						break;
					}
					else {
						os << tester->data << ", ";
						tester = tester->next;
					}
			}
		}
	} 
	
	template <typename E>
	E* /*const*/
	SSLL<E>::contents(void) { 
		if (!head) {
			throw std::runtime_error("SSLL<E>.contents(): The list contains nothing!");
		}
		Node* temp = head;
		E* data = new E[length()]; //is length appropriate here? I guess we'll find out
		int i =0;
		while (temp) { //run through this on paper to make sure it doesnt go over
			data[i] = temp->data;
			temp = temp->next;
			i++;
		}
		//delete temp;
		return data;
	}


} 

#endif

