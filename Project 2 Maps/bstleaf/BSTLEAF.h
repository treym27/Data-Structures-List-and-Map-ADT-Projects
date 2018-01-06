#ifndef	BSTLEAF_H
#define BSTLEAF_H
#include <stdexcept>

namespace cop3530 {


	template <typename K, typename V>
	class Node {
	public:
		K key;
		V value;
		Node<K, V>* left = nullptr;
		Node<K, V>* right = nullptr;
	};

	
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	class BSTLEAF {
		
	private:
		Node<K, V> * root;	
		
	public:
		BSTLEAF();
		~BSTLEAF();
		BSTLEAF(const BSTLEAF& c);
		BSTLEAF<K, V, compare, equal>& operator= (const BSTLEAF& c);
		Node<K, V> * copy_with_node(const Node<K, V>* root); 
		BSTLEAF(BSTLEAF&& c);
		BSTLEAF<K, V, compare, equal>& operator= (BSTLEAF&& c);
		
		int balance_with_node(Node<K, V> *& root);
		int balance();
		void insert(K key, V value);
		void remove(K key);
		Node<K, V> * remove_with_node(Node<K, V> *& root, K key);
		V& lookup(K key);
		V& lookup_with_node(Node<K, V> *& root, K key);
		bool contains(K key);
		size_t size_with_node(Node<K, V> *& root);
		void clear();
		size_t height();
		size_t height_with_node(Node<K, V> *& root);
		bool is_empty();
		bool is_full();
		size_t size();
	
	};

	//CONSTRUCTOR
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	BSTLEAF<K, V, compare, equal>::BSTLEAF() {
		root = nullptr;
	}
	//DESTRUCTOR
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	BSTLEAF<K, V, compare, equal>::~BSTLEAF() {
		this->clear();
	}

	//COPY CONSTRUCTOR
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	BSTLEAF<K, V, compare, equal>::BSTLEAF(const BSTLEAF& c) {
		root = this->copy_with_node(c.root);
	}

	//COPY ASSIGNMENT
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	BSTLEAF<K, V, compare, equal>& BSTLEAF<K, V, compare, equal>::operator=(const BSTLEAF& c) {
		if (this != &c) {
			this->clear();

			root = this->copy_with_node(c.root);
		}
		return *this;
	}

	//--do_copy helper
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	Node<K, V> * BSTLEAF<K, V, compare, equal>::copy_with_node(const Node<K, V> * root) {
		if (!root) {
			return nullptr;
		}
		class Node<K, V> *temp;
		temp = new Node<K, V>;
		temp->key = root->key;
		temp->value = root->value;
		temp->left = this->copy_with_node(root->left);
		temp->right = this->copy_with_node(root->right);

		return temp;
	}

	//MOVE CONSTRUCTOR
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	BSTLEAF<K, V, compare, equal>::BSTLEAF(BSTLEAF&& c) {
		root = c.root;
		c.root = nullptr;
	}

	//MOVE ASSIGNMENT
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	BSTLEAF<K, V, compare, equal>& BSTLEAF<K, V, compare, equal>::operator=(BSTLEAF&& c) {
		if (this != &c) {
			this->clear();
			root = c.root;
			c.root = nullptr;
		}
		return *this;
	}

	//INSERT
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	void BSTLEAF<K, V, compare, equal>::insert(K key, V value) {
		if (!root) {
			root = new Node<K, V>();
			root->left = nullptr;
			root->right = nullptr;
			root->key = key;
			root->value = value;
			return;
		}
		else {
			Node<K, V>* tracker = root;
			while (key != tracker->key) {

				if (key < tracker->key) {
					if (!tracker->left) {
						tracker->left = new Node<K, V>();
						tracker->left->key = key;
						tracker->left->value = value;
						return;
					}
					else {
						tracker = tracker->left;
					}
				}
				else if (key > tracker->key) {
					if (!tracker->right) {
						tracker->right = new Node<K, V>();
						tracker->right->key = key;
						tracker->right->value = value;
						return;
					}
					else {
						tracker = tracker->right;
					}
				}
				if (key == tracker->key) {
					tracker->value = value;
					return;
				}
			}
		}
	}

	//REMOVE
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	void BSTLEAF<K, V, compare, equal>::remove(K key) {
		root = this->remove_with_node(root, key);
	}

	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	Node<K, V>* BSTLEAF<K, V, compare, equal>::remove_with_node(Node<K, V> *& root, K key) {
		class Node<K, V> *temp;
		if (!root) {
			return nullptr;
		}
		
		if (compare(key, root->key)) {
			root->left = remove_with_node(root->left, key);
		}
		if (compare(root->key, key)) {
			root->right = remove_with_node(root->right, key);
		}
		if (equal(key, root->key)) {
			temp = root;
			if (root->right == nullptr) {
				root = root->left;
				delete temp;
			}
			else {

				class Node<K, V> *min = root->right;
				while (min->left) {
					min = min->left;
				}

				root->key = min->key;
				root->value = min->value;
				remove_with_node(root->right, root->key);
			}

		}
		
		return root;
	}

	//LOOKUP
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	V& BSTLEAF<K, V, compare, equal>::lookup(K key) {
		return this->lookup_with_node(root, key);
	}

	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	V& BSTLEAF<K, V, compare, equal>::lookup_with_node(Node<K, V> *& root, K key) {
		if (!root) {
			throw std::runtime_error("BSTLEAF.lookup() Nothing to look up!");

		}
		if (equal(key, root->key)) {
			return root->value;
		}
		if (compare(key, root->key)) {
			return this->lookup_with_node(root->left, key);
		}
		else {
			return this->lookup_with_node(root->right, key);
		}
	}

	//CONTAINS
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	bool BSTLEAF<K, V, compare, equal>::contains(K key) {
		try {
			this->lookup_with_node(root, key);
		}
		catch (...) {
			return false;
		}
		return true;
	}

	//IS_EMPTY
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	bool BSTLEAF<K, V, compare, equal>::is_empty() {
		if (!root) {
			return true;
		}
		else {
			return false;
		}
	}

	//IS_FULL
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	bool BSTLEAF<K, V, compare, equal>::is_full() {
		return false;
	}

	//SIZE
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	size_t BSTLEAF<K, V, compare, equal>::size() {
		return this->size_with_node(root);
	}

	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	size_t BSTLEAF<K, V, compare, equal>::size_with_node(Node<K, V> *& root) {
		if (!root) {
			return 0;
		}
		size_t temp = 1 + this->size_with_node(root->left) + this->size_with_node(root->right);
		return temp;
	}

	//CLEAR
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	void BSTLEAF<K, V, compare, equal>::clear() {
		//should work by just calling remove on root
		while (root) {
			remove(root->key); //this->
		}
	}

	//HEIGHT
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	size_t BSTLEAF<K, V, compare, equal>::height() {
		return this->height_with_node(root);
	}

	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	size_t BSTLEAF<K, V, compare, equal>::height_with_node(Node<K, V> *& root) {
		if (!root) {
			return 0;
		}
		size_t ans = std::max(this->height_with_node(root->left), this->height_with_node(root->right)) + 1;
		return ans;
	}

	//BALANCE
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	int BSTLEAF<K, V, compare, equal>::balance() {
		return this->balance_with_node(root);
	}

	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	int BSTLEAF<K, V, compare, equal>::balance_with_node(Node<K, V> *& root) {
		if (!root) {
			return 0;
		}
		int h_left = this->height_with_node(root->left);
		int h_right = this->height_with_node(root->right);
		int diff = h_left - h_right;
		return diff;
	}

}
#endif

