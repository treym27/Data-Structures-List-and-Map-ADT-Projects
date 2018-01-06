#pragma once
#ifndef CDAL_H
#define CDAL_H
#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include "List.h"

using namespace cop3530;

namespace cop3530 {
	template <typename E>
	class CDAL : public List<E> {
	public:
		CDAL();
		~CDAL();
		
	public:
		void insert(E element, size_t position) override;
		void push_back(E element) override;
		void push_front(E element) override;
		E replace(E element, size_t position) override;
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
		E* contents(void) override;


	private:
		struct Node {
			E data[50];
			Node* next;

			
		};
		int arrTail;
		Node* head;
		Node* tail;

	/*template <typename DataT>
	class CDAL_Iter {
		public:
		//type aliases required for C++ iterator compatibility
		//using size_t = std::size_t;
		using value_type = DataT;
		using reference = DataT&;
		using pointer = DataT*;
		using difference_type = std::ptrdiff_t;
		using iterator_category = std::forward_iterator_tag;
		
		//type aliases for prettier(!) code
		using self_type = CDAL_Iter;
		using self_reference = CDAL_Iter&;
		
		private:
		Node<E> * here;
		DataT * iter_array;
		
		public:
		//constructor
		explicit CDAL_Iter(Node<E> * start = nullptr, DataT * array = nullptr) : here(start), iter_array(array) {}
		
		//operations
		reference operator*() const {
			return *iter_array;
		}
		pointer operator->() const {
			return &(operator*());
		}
		
		//copy and assignment
		CDAL_Iter( const CDAL_Iter& src) : here (src.here), iter_array(src.iter_array) {}
		self_reference operator = ( CDAL_Iter<DataT> const& src) {
			if (this == &src) {
				return (*this);
			}
			here = src.here;
			iter_array = src.iter_array;
			return *this;
		}
		//preincrement
		self_reference operator++() {
			if (here) {
				if (here->tail_index == 50) {
					here = here->next;
					iter_array = here->array;
				}
				++iter_array;
			}
			return *this;
		} 
		//postincrement
		self_type operator++(int) {
			self_type tmp = *this;
			++(*this);
			return tmp;
		} 
		
		bool operator == ( CDAL_Iter<DataT> const& rhs) const {
			return (here == rhs.here && iter_array = rhs.iter_array);
		}
		bool operator != ( CDAL_Iter<DataT> const& rhs) const {
			return (here != rhs.here || iter_array != rhs.iter_array);
		}
	};
	
	public: 
	//iter type aliases after iter code
	using iterator = CDAL_Iter<E>;
	using const_iterator = CDAL_Iter<E const>;
	
	//methods to create iters
	iterator begin() {
		iterator i(head, head->array);
		return i;
	}
	iterator end() { 
		iterator i(tail, tail->array+50);
		return i;
	}
	
	const_iterator begin() const {
		const_iterator i(head, head->array);
		return i;
	}
	const_iterator end() const {
		const_iterator i(tail, tail->array+50);
		return i;
	}
	*/	
		
		};
	



template <typename E>
CDAL<E>::CDAL() {
	head = nullptr;
	tail = nullptr;
	arrTail = -1;
}

template <typename E>
CDAL<E>::~CDAL() {

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
void
CDAL<E>::insert(E element, size_t position) { 

	Node* temp;
	if (!head && position != 0) {
		throw std::runtime_error("CDAL<E>.insert(): NO HEAD; CANNOT INSERT IN A POSITION OTHER THAN 0.");
	}
	else if (position > (arrTail+1)) {
		throw std::runtime_error("CDAL<E>.insert(): POSITION IS INVALID.");
	}
	else if (position == (arrTail+1)) {
		push_back(element);
		return;
		} 
	else if (!head && position == 0) {
		temp = new Node();
		head = temp;
		tail = temp;
		temp->data[0] = element;
		temp->next = nullptr;
		head->next = nullptr;
		tail->next = nullptr;
		}

	else {
		E data_2;
		temp = head;
		int ncount = 1;
		for (size_t i = 0; i < (position / 50); i++) {
			temp = temp->next;
			ncount++;
			}
		if (!temp->next) { //!temp->next

				data_2 = temp->data[arrTail%50];
				for (unsigned int i = (arrTail%50); i > (position%50); i--) { //i made it arrt+1...
					temp->data[i] = temp->data[i-1];
					}
					temp->data[position%50] = element;
				if ((arrTail+1) % 50 == 0) {
					Node* temp2 = new Node();
					
					temp->next = temp2;
					temp = temp2;
					temp->data[0] = data_2;
					
					}
				else {
					temp->data[(arrTail%50)+1] = data_2;
					}
				
			}
		else {

        E data_1 = temp->data[49]; 
        for (size_t i = 49; i > (position % 50); i--) {
            temp->data[i] = temp->data[i-1];
        }
        temp->data[position%50] = element;
        
        while (temp->next->next) {
            temp = temp->next;
            ncount++;
            data_2 = temp->data[49];
            if (ncount*50 < arrTail) {
				for (size_t i = 49; i > 0; i--) {
					temp->data[i] = temp->data[i-1];
			}
		}
			else if (ncount*50 > arrTail) {
				for (size_t i = (arrTail%50); i > 0; i--) {
					temp->data[i] = temp->data[i-1];
					}
				}

        temp->data[0] = data_1;
        data_1 = data_2;
        } 
	

        temp = temp->next;

        data_2 = temp->data[(arrTail%50)]; //whot
	

        for (unsigned int i = 49; i > 0; i--) {
            temp->data[i] = temp->data[i-1];
        }

        temp->data[0] = data_1;
         if((arrTail+1) % 50 == 0) {
            Node* temp3 = new Node();
            temp3->data[0] = data_2; //swapped data_1 t data_2???...
            temp->next = temp3;
            //temp = temp->next;
            tail = temp3; 
        

        }
         else {
            temp->data[(arrTail+1)%50] = data_2; //(arrTail+1) % 50

        } 
        
  
	

	
}
}

	arrTail++;
    return;
}

template <typename E>
void
CDAL<E>::push_back(E element) {
	if (!head) {
		Node* temp = new Node();
		head = temp;
		tail = head;
		head->data[0] = element;
	}
	else if ((arrTail+1) % 50 == 0) {
		Node* temp = new Node();
		temp->data[0] = element;
		tail->next = temp;
		tail = tail->next;
	}
	else {
		Node* temp = head;
		for (size_t i = 0; i < ((arrTail+1) / 50); i++) {
			temp = temp->next;
			}
		temp->data[(arrTail+1) % 50] = element;
	}
	arrTail++;
	return;
}

template <typename E>
void
CDAL<E>::push_front(E element) {
	if (!head) {
		Node* temp = new Node();
		temp->data[0] = element;
		temp->next = nullptr;
		head = temp;
		tail = temp;
		arrTail++;
		return;
	}

	else {
		insert(element, 0); 
		}
		return;

}

template <typename E>
E
CDAL<E>::replace(E element, size_t position) {
	if (!head) {
		throw std::runtime_error("CDAL<E>.replace(): Nothing to replace!");
	}
	else if (position > arrTail || position < 0) {
		throw std::runtime_error("CDAL<E>.replace(): out of bounds!");
	}

	Node* temp = head;
	for (size_t i = 0; i < position / 50; i++) {
		temp = temp->next;
	}
	E ans = temp->data[position % 50];
	temp->data[position % 50] = element;
	return ans;
}

template <typename E>
E
CDAL<E>::remove(size_t position) { 
	if (position > arrTail || position < 0) {
		throw std::runtime_error("CDAL<E>.remove(): out of bounds!");
	}

	Node* temp = head;
	E ans;
	for (int i = 0; i < (position / 50); i++) { 
		temp = temp->next;
	}
	if (position == arrTail) { 
		ans = temp->data[arrTail % 50];
		//arrTail--;
	}
		
	else {
		ans = temp->data[position % 50];
		if (!temp->next) {
			for (unsigned int i = position; i < arrTail; i++) {
				temp->data[i] = temp->data[i+1];
				}

			}

		
		
	arrTail--;
	return ans;
}
}

template <typename E>
E
CDAL<E>::pop_back() {
	if (head == NULL) {
		throw std::runtime_error("CDAL<E>.pop_back(): NOTHING TO REMOVE");
	}
	Node* temp = head;
	for (unsigned int i = 0; i < arrTail / 50; i++) {
		temp = temp->next;
	}
	
	
	E ans = temp->data[arrTail % 50];
	if (arrTail % 50 == 0) { 
		delete temp;
		}
	arrTail--;
	return ans;
}

template <typename E>
E
CDAL<E>::pop_front() {
	if (head == NULL) {
		throw std::runtime_error("CDAL<E>.pop_back(): NOTHING TO REMOVE");
	}
	E data = remove(0);
	//arrTail--;
	return data;
}

template <typename E>
E
CDAL<E>::item_at(size_t position) {
	Node* temp = head;

	for (unsigned int i = 0; i < position / 50; i++) {
		temp = temp->next;
		}
		return temp->data[position % 50]; //value may be off by one?
}

template <typename E>
E
CDAL<E>::peek_back() {
	if (head == NULL) {
		throw std::runtime_error("CDAL<E>.peek_back(): NOTHING TO PEEK");
	}
	Node* temp = head;
	while (temp->next) {
		temp = temp->next;
		}
		return temp->data[arrTail % 50]; //value may be off by one?
}

template <typename E>
E
CDAL<E>::peek_front() {
	if (head == NULL) {
		throw std::runtime_error("CDAL<E>.peek_front(): NOTHING TO PEEK");
	}
	return head->data[0];
}

template <typename E>
bool
CDAL<E>::is_empty() {
	if (arrTail == -1) {
		return true;
	}
	else {
	return false; 
}

}

template <typename E>
bool
CDAL<E>::is_full() {
	return false;
}

template <typename E>
size_t
CDAL<E>::length() { //or would it just return arrTail?
	return arrTail+1;
}

template <typename E>
void
CDAL<E>::clear() {
	
	Node* temp = head;
	while (temp) {
		head = head->next;
		delete temp;
		temp = head;
		}
		head = nullptr;
		tail = nullptr;
		arrTail = -1;
}

template <typename E>
bool
CDAL<E>::contains(E element, bool(*equals_function)(const E&, const E&)){ 
	Node* temp = head;
	while (temp->next) {
		for (unsigned int i = 0; i < 49; i++) { //MIGHT NEED TO CHANGE TO 50...
			if (equals_function(temp->data[i], element)) {
				return true;
			}
			else {
				temp = temp->next;
			}
		}
		for (unsigned int i = 0; i < arrTail % 50; i++) {
			if (equals_function(temp->data[i], element)) {
				return true;
			}
			}
		return false;
	}
}

template <typename E>
void
CDAL<E>::print(std::ostream &os) {
	if (arrTail < 0) {
		os << "<empty list>" << std::endl;
	}
	else {
		Node* temp = head;
		os << "[";
		for (unsigned int i = 0; i <= arrTail; i++) { //might be i < tail + 1
			if (i % 50 == 0 && i > 0) {
				temp = temp->next;
				}
			if (i == arrTail) {
				os << temp->data[i % 50] << "]" << std::endl;
			}
			else {
				os << temp->data[i % 50] << ", ";
			}
		}

}
return;
}

template <typename E>
E*
CDAL<E>::contents() { 
	if (arrTail == 0) {
		throw std::runtime_error("CDAL<E>.contents(): This list contains nothing!");
	}
	E* arr = new E[arrTail];
	Node* temp = head;
	
	}
}




#endif
