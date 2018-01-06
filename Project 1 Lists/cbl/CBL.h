
#ifndef CBL_H
#define CBL_H
#include <iostream>
#include <stdexcept>

#include "List.h"

namespace cop3530 {
	template <typename E>
	class CBL : public List<E> { 
	public:
		CBL(size_t arr_length = 50);
		~CBL() override;

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
		E* /*const*/ contents(void) override;
		void expand(); 
		void shrink();
		
	private:
		int head;
		int tail; //or int?
		E* data;
		E* newArr;
		size_t size = 0;
		size_t startSize;
		

	};

	template <typename E>
	CBL<E>::CBL(size_t arr_length) {
		head = -1;
		tail = -1;
		size = arr_length;
		data = new E[size];
		
		startSize = arr_length;

			}

	template <typename E>
	CBL<E>::~CBL() {
		delete[] data;
	
		
	}


	template <typename E>
	void
	CBL<E>::insert(E element, size_t position) {

		if (head == -1 && tail == -1 && position != 0) {
			throw std::runtime_error("CBL<E>.insert(): OUT OF BOUNDS.");
		}
		else if (position < 0 || position > size) {
			throw std::runtime_error("CBL<E>.insert(): OUT OF BOUNDS.");
		}
		else if (position > (tail + 1) && position < (head - 1)) {
			throw std::runtime_error("CBL<E>.insert(): OUT OF BOUNDS.");
		}
		else if (head == -1 && tail == -1 && position == 0) {
			data[position] = element;
			head++;
			tail++;
			//return;
		}
		else if ((position % size) == (tail % size)) { 
			data[(tail % size) + 1] = data[tail % size];
			data[tail] = element;
			tail++;
			//return;
		}
		else {
			for (unsigned int i = (tail + 1); i > position; i--) {
				data[i] = data[i - 1];
			}
			data[position] = element;
			tail++;
		}
		if (length() == (size-1)) {
			expand();
		} 
		return; 
		
		
	}

	template <typename E>
	void
	CBL<E>::push_back(E element) {
		if (head == -1 && tail == -1) {
			head++;
			tail++;
			data[tail] = element;
		}
		else if (length() == (size-1)) { 
			expand();
			data[tail + 1] = element;
			tail++;
		}
		else {
			data[tail + 1] = element;
			tail++;
		}

	}

	template <typename E>
	void
	CBL<E>::push_front(E element) { 
		if (((tail + 1) % size) == (head % size)) {
			expand();
		}
		if (head == -1 && tail == -1) {
			tail++;
			head++;
			data[head] = element;
			return;
		}
		insert(element,0);
	}

	template <typename E>
	E
	CBL<E>::replace(E element, size_t position) {
		if (position > tail) {
			throw std::runtime_error("CBL<E>.replace(): OUT OF BOUNDS");
		}
		else if (tail < 0) {
			throw std::runtime_error("CBL<E>.replace() : NOTHING TO REPLACE");
		}
		else {
			E temp = data[position];
			data[position] = element;
			return temp;
		}
	}

	template <typename E>
	E
	CBL<E>::remove(size_t position) { //LOOK OVER LOGIC
		E fix = data[tail];
		if (position > tail) {
			throw std::runtime_error("CBL<E>.remove(): OUT OF BOUNDS");
		}
		else if (tail < 0) {
			throw std::runtime_error("CBL<E>.remove(): NOTHING TO REMOVE");
		}
		E temp = data[position];
		for (int i = position; i < tail; i++) {
			data[i] = data[i+1];
		}
		tail--;
		if (size > 2 * startSize && 2 * tail < size) {
			shrink();
		}
		if (position != tail) {
			data[tail+1] = fix; 
			}
		return temp;
	}

	template <typename E>
	E
	CBL<E>::pop_back(void) {
		if (tail < 0) {
			throw std::runtime_error("CBL<E>.pop_back(): NOTHING TO POP");
		}
		E temp = data[tail % size];

		tail--;
		if (size > (2 * startSize) && (2 * (tail - head)) < size) {
			shrink();
		}
		return temp;
	}

	template <typename E>
	E
	CBL<E>::pop_front(void) {
		if (tail < 0) {
			throw std::runtime_error("CBL<E>.pop_back(): NOTHING TO POP");
		}
		E temp = data[head % size];
		for (int i = (head % size); i < (tail % size); i++) {
			data[i] = data[i + 1];
		}
		tail--;
		if (size > 2 * startSize && (2 * (tail-head)) < size) {
			shrink();
		}
		return temp;
	}

	template <typename E>
	E
	CBL<E>::peek_back(void) {
		if (tail < 0) {
			throw std::runtime_error("CBL<E>.peek_back(): NOTHING TO PEEK");
		}
		E temp = data[tail % size];
		return temp;
	}

	template <typename E>
	E
	CBL<E>::peek_front(void) {
		if (tail < 0) {
			throw std::runtime_error("CBL<E>.peek_front(): NOTHING TO PEEK");
		}
		E temp = data[head % size];
		return temp;
	}

	template <typename E>
	E
	CBL<E>::item_at(size_t position) {
		if (position > (tail + 1) && position < (head - 1)) {
			throw std::runtime_error("CBL<E>.item_at(): OUT OF BOUNDS");
		}
		else if (tail < 0) {
			throw std::runtime_error("CBL<E>.item_at(): NO ELEMENTS IN ARRAY");
		}
		else {
			E temp = data[position];
			return temp;
		}
	}

	template <typename E>
	bool
	CBL<E>::is_empty() {
		return (head == -1 && tail == -1);
	}

	template <typename E>
	bool
	CBL<E>::is_full() {
		return false;
	}

	template <typename E>
	size_t
	CBL<E>::length() {
		if (tail < 0) {
			return 0;
		}
		else {
			return (tail-head+1);
		}
	}

	template <typename E>
	void
	CBL<E>::clear() {
		//delete[] data;
		tail = -1;
		head = -1;
	}

	template <typename E>
	bool
	CBL<E>::contains(E element, bool(*equals_function)(const E&, const E&)) {
		for (unsigned int i = head; i <= tail; i++) {
			if (equals_function(data[i], element)) {
				return true;
			}
		}
		return false;
	}

	template <typename E>
	void
	CBL<E>::print(std::ostream &os) {
		if (tail < 0) {
			os << "<empty list>" << std::endl;
		}
		else {
			os << "[";
			for (unsigned int i = 0; i <= tail; i++) {
				if (i == tail) {
					os << data[i] << "]" << std::endl;
				}
				else {
					os << data[i] << ", ";
				}
			}
		}
	}

template <typename E>
E*
CBL<E>::contents() { 
	E* temp = new E[tail + 1];
	for (int i = (head % size); i < (tail % size) + 1; i++) {
		temp[i] = data[i];
	}
	return temp;
}

	template <typename E>
	void
	CBL<E>::expand() {
		E dataTail = data[tail];
		size_t oldSize = size;
		size = int(1.5 * size);
		E* newArr = new E[size];
		
		size_t i = head;
		while (i % oldSize != tail) {
			newArr[i % size] = data[i % oldSize];
			i++;
			}
			
		
		newArr[tail] = dataTail;	
		tail = (i % size);
		delete[] data;
		
		data = newArr;


	}

	template <typename E>
	void
	CBL<E>::shrink() {
		size = size * 0.75;
		E* newArr = new E[size];
		for (size_t i = 0; i < tail; i++) {
			newArr[i] = data[i];
		}
		delete[] data;
		data = newArr;

	
	}

}


#endif
