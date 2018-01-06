#ifndef BSTRAND_H
#define BSTRAND_H
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
	class BSTRAND {
	private:
		Node<K, V>* root = nullptr;
		
	public:
		BSTRAND();
		~BSTRAND();
		BSTRAND(const BSTRAND& c);
		BSTRAND<K, V, compare, equal>& operator= (const BSTRAND& c);
		Node<K, V>* copy_with_node(const Node<K, V>* root);
		BSTRAND(BSTRAND&& c); 
		BSTRAND<K, V, compare, equal>& operator= (BSTRAND&& c);

		void insert(K key, V value);
		Node<K, V>* insert_with_node(Node<K, V> *& root, K key, V value);
		void remove(K key);
		Node<K, V>* remove_with_node(Node<K, V> *& root, K key);
		V& lookup(K key);
		const V& lookup(K key) const;
		V& lookup_with_node(Node<K, V> *& root, K key);
		const V& lookup_with_node_const(const Node<K, V> * root, K key) const;
		void clear();
		size_t height();
		size_t height_with_node(Node<K, V> *& root);
		bool contains(K key);
		bool is_empty();
		bool is_full();
		size_t size();
		size_t size_with_node(Node<K, V> *& root);
		int balance();
		int balance_with_node(Node<K, V> *& root);

	
	};

	//CONSTRUCTOR
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	BSTRAND<K, V, compare, equal>::BSTRAND() {
		root = nullptr;
	}
	//DESTRUCTOR
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	BSTRAND<K, V, compare, equal>::~BSTRAND() {
		this->clear();
	}

	//COPY CONSTRUCTOR
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	BSTRAND<K, V, compare, equal>::BSTRAND(const BSTRAND& c) {
		root = this->copy_with_node(c.root);
	}

	//COPY ASSIGNMENT
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	BSTRAND<K, V, compare, equal>& BSTRAND<K, V, compare, equal>::operator=(const BSTRAND& c) {
		if (this != &c) {
			this->clear();

			root = this->copy_with_node(c.root);
		}
		return *this;
	}
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	Node<K, V> * BSTRAND<K, V, compare, equal>::copy_with_node(const Node<K, V> * root) {
		if (!root) {
			return nullptr;
		}
		
		class Node<K, V>* temp = new Node<K, V>;
		temp->key = root->key;
		temp->value = root->value;
		temp->left = this->copy_with_node(root->left);
		temp->right = this->copy_with_node(root->right);

		return temp;
	}

	//MOVE CONSTRUCTOR
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	BSTRAND<K, V, compare, equal>::BSTRAND(BSTRAND&& c) {
		root = c.root;
		c.root = nullptr;
	}

	//MOVE ASSIGNMENT
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	BSTRAND<K, V, compare, equal>& BSTRAND<K, V, compare, equal>::operator=(BSTRAND&& c) {
		if (this != &c) {
			this->clear();
			root = c.root;
			c.root = nullptr;
		}
		return *this;
	}

	//INSERT
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	void BSTRAND<K, V, compare, equal>::insert(K key, V value) {
		if (!root) {
			root = new Node<K, V>;
			root->key = key;
			root->value = value;
			return;
		}
		int size = this->size();
		int temp = std::rand() % (size + 1);
		if (temp == 0) {
			root = this->insert_with_node(root, key, value);
		}
		else {
			if (!root) {
				root = new Node<K, V>;
				root->key = key;
				root->value = value;
				return;
			}

			class Node<K, V> *pre = root;
			class Node<K, V> *temp = pre;

			while (temp) {
				pre = temp;
				if (compare(key,temp->key)) {
					temp = temp->left;
					}
				else {
					temp = temp->right;
					}
			}
			if (key == pre->key) {
				pre->key = key;
				pre->value = value;
				return;
			}
			temp = new Node<K, V>;
			temp->key = key;
			temp->value = value;
			if (compare(key, pre->key)) {
				pre->left = temp;
			}
			else {
				pre->right = temp;
			}
		}
	}


	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	Node<K, V> * BSTRAND<K, V, compare, equal>::insert_with_node(Node<K, V> *& root, K key, V value) {
		if (!root) {
			root = new Node<K, V>;
			root->key = key;
			root->value = value;
			return root;
		}
		if (equal(key,root->key)) {
					root->value = value;
				}
		else if (compare(key, root->key)) {
			root->left = this->insert_with_node(root->left, key, value);
			class Node<K, V> *temp = root->left;
			root->left = temp->right;
			temp->right = root;
			root = temp;
		}
		else if (compare(root->key, key)) {
			root->right = this->insert_with_node(root->right, key, value);

			class Node<K, V> *temp = root->right;
			root->right = temp->left;
			temp->left = root;
			root = temp;
		}
		
		return root;
	}

	//REMOVE
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	void BSTRAND<K, V, compare, equal>::remove(K key) {
		root = this->remove_with_node(root, key);
	}


	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	Node<K, V>* BSTRAND<K, V, compare, equal>::remove_with_node(Node<K, V> *& root, K key) {
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
				while (min->left != nullptr) {
					min = min->left;
				}

				root->key = min->key;
				root->value = min->value;
				remove_with_node(root->right, root->key);
			}

		}
		return root;
	}

	//LOOKUP CONST
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	V& BSTRAND<K, V, compare, equal>::lookup(K key) {
		return this->lookup_with_node(root, key);
	}

	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	const V& BSTRAND<K, V, compare, equal>::lookup(K key) const {
		return this->lookup_with_node_const(root, key);
	}

	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	V& BSTRAND<K, V, compare, equal>::lookup_with_node(Node<K, V> *& root, K key) {
		if (!root) {
			throw std::runtime_error("BSTRAND.lookup(): Nothing to look up!");
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

	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	const V& BSTRAND<K, V, compare, equal>::lookup_with_node_const(const Node<K, V> * root, K key) const {
		if (!root) {
			throw std::runtime_error("BSTRAND.lookup(): Nothing to look up!");
		}
		if (equal(key, root->key)) {
			return root->value;
		}
		if (compare(key, root->key)) {
			return this->lookup_with_node_const(root->left, key);
		}
		else {
			return this->lookup_with_node_const(root->right, key);
		}
	}

	//CONTAINS
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	bool BSTRAND<K, V, compare, equal>::contains(K key) {
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
	bool BSTRAND<K, V, compare, equal>::is_empty() {
		if (!root) {
			return true;
		}
		else {
			return false;
		}
	}

	//IS_FULL
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	bool BSTRAND<K, V, compare, equal>::is_full() {
		return false;
	}

	//SIZE
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	size_t BSTRAND<K, V, compare, equal>::size() {
		return this->size_with_node(root);
	}

	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	size_t BSTRAND<K, V, compare, equal>::size_with_node(Node<K, V> *& root) {
		if (!root) {
			return 0;
		}
		size_t temp = 1 + this->size_with_node(root->left) + this->size_with_node(root->right);
		return temp;
	}

	//CLEAR
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	void BSTRAND<K, V, compare, equal>::clear() {
		while (root) {
			this->remove(root->key);
		}
	}

	//HEIGHT
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	size_t BSTRAND<K, V, compare, equal>::height() {
		return this->height_with_node(root);
	}

	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	size_t BSTRAND<K, V, compare, equal>::height_with_node(Node<K, V> *& root) {
		if (!root) {
			return 0;
		}
		size_t ans = std::max(this->height_with_node(root->left), this->height_with_node(root->right)) + 1;
		return ans;
	}

	//BALANCE
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	int BSTRAND<K, V, compare, equal>::balance() {
		return this->balance_with_node(root);
	}

	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	int BSTRAND<K, V, compare, equal>::balance_with_node(Node<K, V> *& root) {
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
