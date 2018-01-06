
#ifndef SDAL_H
#define SDAL_H
#include <stdexcept>
#include <iostream>
#include <stdio.h>
#include "List.h"


namespace cop3530 {
	template <typename E>
	class SDAL : public List<E> {
	public:
		SDAL(size_t arr_length = 50);
		SDAL(const SDAL &c);
		~SDAL() override;

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
		void expand(void); //this might have to go into private;
		void shrink(void);

	private:
		size_t tail; //or int?
		E* data;
		E* newArr;
		size_t size = 0;
		size_t startSize;
		

	public:
		template <typename DataT>
		class SDAL_Iter {
		public:
			// type aliases required for C++ iterator compatibility
			using value_type = DataT;
			using reference = DataT&;
			using pointer = DataT*;
			using difference_type = std::ptrdiff_t;
			using iterator_category = std::forward_iterator_tag;

			// type aliases for prettier code
			using self_type = SDAL_Iter;
			using self_reference = SDAL_Iter&;
 
		private:
			E* here;
			size_t curr;
			size_t tail;
			
		public:
			explicit SDAL_Iter(E* src = nullptr, size_t i = 0, size_t c = 0, size_t e = 0) : here(&src[i]), curr(c), tail(e) {}
			SDAL_Iter(const SDAL_Iter& src) : here(src.here), curr(src.curr), tail(src.tail) {}
			
			static self_type make_begin(SDAL& n) {
			self_type i(n.data, 0, 0, n.tail);
			return i;
		}
		static self_type make_end(SDAL& n) {
			self_type i(n.data, n.tail, n.tail, n.tail);
			return i;
		}

		reference operator*() const { return *here; }
		DataT* operator->() const { return here; }

		self_reference operator=(SDAL_Iter const& src) {
			if (this != &src) {
				here = src.here;
				curr = src.curr;
				tail = src.tail;
			}
			return (*this);
		}

		self_reference operator++() {
			if (curr != tail) {
				here++;
				curr++;
			}
			return (*this);
		} // preincrement

		self_type operator++(int) {
			self_type tmp(*this);
			if (curr != tail) {
				here++;
				curr++;
			}
			return tmp;
		} // postincrement

		bool operator==(SDAL_Iter<DataT> const& rhs) const {
			return (here == rhs.here);
		}
		bool operator!=(SDAL_Iter<DataT> const& rhs) const {
			return (here != rhs.here);
		}
			
		
		}; //end SDAL_Iter 

	};


template <typename E>
SDAL<E>::SDAL(size_t arr_length) {

	data = new E[arr_length];
	tail = -1;
	size = arr_length;
	startSize = arr_length;
}

template <typename E>
SDAL<E>::SDAL(const SDAL &c) {
	//data = c.data;
	tail = c.tail;
	*data = *c.data;
	startSize = c.startSize;
	size = c.size;
	}

template <typename E>
SDAL<E>::~SDAL() {
	delete[] data;
	}


template <typename E>
void
SDAL<E>::insert(E element, size_t position) {
	if (tail == size - 1) {
		expand();
		}
	if (tail == -1 && position == 0) {
		data[position] = element;
		tail++;
	}
	else if (position == 0) {
		for (int i = tail + 1; i > 0; i--) {
			data[i] = data[i - 1];
		}
		data[0] = element;
		tail++;
	}
	else if (position > tail+1) {
		throw std::runtime_error("SDAL<E>.insert(): THE POSITION IS INVALID");
	}
	else if (position == tail) {
		data[tail + 1] = data[tail];
		data[tail] = element;
		tail++;
	}
	else {
		for (int i = tail + 1; i > position; i--) {
			data[i] = data[i - 1];
		}
		data[position] = element;
		tail++;
		
	} 

	
	
}

template <typename E>
void
SDAL<E>::push_back(E element) {
	if (tail == -1) {
		tail++;
		data[tail] = element;
	}
	else if (tail == size - 1){ //length + 1 == size instead?
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
SDAL<E>::push_front(E element) {
	if (tail == -1) {
		tail++;
		data[tail] = element;
		return;
	}
	if (tail == size - 1) {
		expand();
		}

		for (int i = tail+1; i > 0; i--) { //CHECK THIS
			data[i] = data[i-1];
		}
		data[0] = element;
		tail++;
	

}

template <typename E>
E
SDAL<E>::replace(E element, size_t position) {
	if (position > tail) {
		throw std::runtime_error("SDAL<E>.replace(): OUT OF BOUNDS");
	}
	else if (tail < 0) {
		throw std::runtime_error("SDAL<E>.replace() : NOTHING TO REPLACE");
	}
	else {
		E temp = data[position];
		data[position] = element;
		return temp;
	}
	

}

template <typename E>
E
SDAL<E>::remove(size_t position) { //LOOK OVER LOGIC
	if (position > tail) {
		throw std::runtime_error("SDAL<E>.remove(): OUT OF BOUNDS");
	}
	else if (tail < 0) {
		throw std::runtime_error("SDAL<E>.remove(): NOTHING TO REMOVE");
	}
	E temp = data[position];
	for (int i = position; i < tail; i++) {
			data[i] = data[i+1];
		}
	tail--;
	if (size > 2 * startSize && 2*tail < size) {
		shrink();
		}
	return temp;
}

template <typename E>
E
SDAL<E>::pop_back(void) {
	if (tail < 0) {
		throw std::runtime_error("SDAL<E>.pop_back(): NOTHING TO POP");
	}
	E temp = data[tail];
	
	tail--;
	if (size > 2 * startSize && 2*tail < size) {
		shrink();
		}
	return temp;
}

template <typename E>
E
SDAL<E>::pop_front(void) {
	if (tail < 0) {
		throw std::runtime_error("SDAL<E>.pop_back(): NOTHING TO POP");
	}
	E temp = data[0];
	for (int i = 0; i < tail; i++) {
		data[i] = data[i + 1];
	}
	tail--;
	if (size > 2 * startSize && 2*tail < size) {
		shrink();
		}
	return temp;
}

template <typename E>
E
SDAL<E>::peek_back(void) {
	if (tail < 0) {
		throw std::runtime_error("SDAL<E>.peek_back(): NOTHING TO PEEK");
	}
	E temp = data[tail];
	return temp;
}

template <typename E>
E
SDAL<E>::peek_front(void) {
	if (tail < 0) {
		throw std::runtime_error("SDAL<E>.peek_front(): NOTHING TO PEEK");
	}
	E temp = data[0];
	return temp;
}

template <typename E>
E
SDAL<E>::item_at(size_t position) {
	if (position > tail) {
		throw std::runtime_error("SDAL<E>.item_at(): OUT OF BOUNDS");
	}
	else if (tail < 0) {
		throw std::runtime_error("SDAL<E>.item_at(): NO ELEMENTS IN ARRAY");
	}
	else {
		E temp = data[position];
		return temp;
	}
}

template <typename E>
bool
SDAL<E>::is_empty() {
	return (tail == -1);
}

template <typename E>
bool
SDAL<E>::is_full() {
	return false;
}

template <typename E>
size_t
SDAL<E>::length() {
	if (tail < 0) {
		return 0;
	}
	else {
		return size_t(tail + 1);
	}
}

template <typename E>
void
SDAL<E>::clear() {
	delete[] data;
	data = new E[size];
	tail = -1;
}

template <typename E>
bool
SDAL<E>::contains(E element, bool(*equals_function)(const E&, const E&)) {
	for (unsigned int i = 0; i <= tail; i++) {
		if (equals_function(data[i],element)) {
			return true;
			}
		}
		return false;
}

template <typename E>
void
SDAL<E>::print(std::ostream &os) { //EDIT THIS
	if (tail == -1) {
		os << "<empty list>" << std::endl;
	}
	else {
		os << "[";
		for (unsigned int i = 0; i <= tail; i++) { //might be i < tail + 1
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
E* /*const*/
SDAL<E>::contents() { //check this for error catching and etc.
	E* temp = new E[tail + 1];
	for (int i = 0; i < tail + 1; i++) {
		temp[i] = data[i];
	}
	return temp;
}

template <typename E>
void
SDAL<E>::expand() {

	newArr = new E[int(size*1.5)];
	for (size_t i = 0; i <= tail; i++) {
		newArr[i] = data[i];
		data[i] = 0;
		}
		delete[] data;
		data = new E[int(size*1.5)];
	for (size_t i = 0; i <= tail; i++) {
		data[i] = newArr[i];
		newArr[i] = 0;
		}
		delete[] newArr;
		size = int(size * 1.5);
	}
	
template <typename E>
void
SDAL<E>::shrink() {

	size = int(size * 0.75);

	newArr = new E[size];
	for (size_t i = 0; i < tail; i++) {
		newArr[i] = data[i];
		}
		delete[] data;
		data = new E[size];
	for (size_t i = 0; i < tail; i++) {
		data[i] = newArr[i];
		}
		delete[] newArr;
	}

}
#endif
