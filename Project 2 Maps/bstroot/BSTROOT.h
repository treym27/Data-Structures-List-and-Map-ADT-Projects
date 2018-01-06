#ifndef BSTROOT_H
#define BSTROOT_H
#include <stdexcept>

namespace cop3530 {

	template <typename K, typename V>
	class Node {
	public:
		K key;
		V value;
		Node<K, V> * left = nullptr;
		Node<K, V> * right = nullptr;
	};


	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	class BSTROOT {
	public:
		BSTROOT();
		~BSTROOT();
		BSTROOT(const BSTROOT& other);
		BSTROOT<K, V, compare, equal>& operator= (const BSTROOT& other); 
		Node<K, V> * copy_with_node(const Node<K, V>* root);
		BSTROOT(BSTROOT&& other);
		BSTROOT<K, V, compare, equal>& operator= (BSTROOT&& other);

		void insert(K key, V value);
		Node<K, V> * insert_with_node(Node<K, V> *& root, K key, V value);
		void remove(K key);
		Node<K, V> * remove_with_node(Node<K, V> *& root, K key);
		V& lookup(K key);
		const V& lookup(K key) const;
		V& lookup_with_node(Node<K, V> *& root, K key);
		const V& lookup2(const Node<K, V> * root, K key) const;

		bool contains(K key);
		bool is_empty();
		bool is_full();
		size_t size();
		size_t size_with_node(Node<K, V> *& root);
		void clear();
		size_t height();
		size_t height_with_node(Node<K, V> *& root);
		int balance();
		int balance_with_node(Node<K, V> *& root);

	private:
		Node<K, V> * root = nullptr;
	};

	//CONSTRUCTOR
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	BSTROOT<K, V, compare, equal>::BSTROOT() {
		root = nullptr;
	}
	//DESTRUCTOR
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	BSTROOT<K, V, compare, equal>::~BSTROOT() {
		this->clear();
	}

	//COPY CONSTRUCTOR
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	BSTROOT<K, V, compare, equal>::BSTROOT(const BSTROOT& other) {
		root = this->copy_with_node(other.root);
	}

	//COPY ASSIGNMENT
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	BSTROOT<K, V, compare, equal>& BSTROOT<K, V, compare, equal>::operator=(const BSTROOT& other) {
		if (this != &other) {
			this->clear();
			root = this->copy_with_node(other.root);
		}
		return *this;
	}

	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	Node<K, V> * BSTROOT<K, V, compare, equal>::copy_with_node(const Node<K, V> * root) {
		if (!root) {
			return nullptr;
		}

		class Node<K, V> *temp = new Node<K, V>;
		temp->key = root->key;
		temp->value = root->value;

		temp->left = this->copy_with_node(root->left);
		temp->right = this->copy_with_node(root->right);

		return temp;
	}

	//MOVE CONSTRUCTOR
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	BSTROOT<K, V, compare, equal>::BSTROOT(BSTROOT&& other) {
		root = other.root;
		other.root = nullptr;
	}

	//MOVE ASSIGNMENT
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	BSTROOT<K, V, compare, equal>& BSTROOT<K, V, compare, equal>::operator=(BSTROOT&& other) {
		if (this != &other) {
			this->clear();
			root = other.root;
			other.root = nullptr;
		}
		return *this;
	}

	//INSERT
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	void BSTROOT<K, V, compare, equal>::insert(K key, V value) {
		root = this->insert_with_node(root, key, value);
	}


	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	Node<K, V> * BSTROOT<K, V, compare, equal>::insert_with_node(Node<K, V> *& root, K key, V value) {
		if (!root) {
			root = new Node<K, V>;
			root->key = key;
			root->value = value;
			return root;
		}

		if (compare(key, root->key)) {
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
		else {
			root->value = value;
		}
		return root;
	}

	//REMOVE
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	void BSTROOT<K, V, compare, equal>::remove(K key) {
		root = this->remove_with_node(root, key);
	}

	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	Node<K, V>* BSTROOT<K, V, compare, equal>::remove_with_node(Node<K, V> *& root, K key) {
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

				class Node<K, V> *iop = root->right;
				while (iop->left) {
					iop = iop->left;
				}

				root->key = iop->key;
				root->value = iop->value;
				remove_with_node(root->right, root->key);
			}

		}
		return root;
	}

	//LOOKUP CONST
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	V& BSTROOT<K, V, compare, equal>::lookup(K key) {
		return this->lookup_with_node(root, key);
	}

	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	const V& BSTROOT<K, V, compare, equal>::lookup(K key) const {
		return this->lookup2(root, key);
	}

	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	V& BSTROOT<K, V, compare, equal>::lookup_with_node(Node<K, V> *& root, K key) {
		if (!root) {
			throw std::runtime_error("key does not exist in BST");

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
	const V& BSTROOT<K, V, compare, equal>::lookup2(const Node<K, V> * root, K key) const {
		if (!root) {
			throw std::runtime_error("key does not exist in BST");

		}
		if (equal(key, root->key)) {
			return root->value;
		}
		if (compare(key, root->key)) {
			return this->lookup2(root->left, key);
		}
		else {
			return this->lookup2(root->right, key);
		}
	}

	//CONTAINS
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	bool BSTROOT<K, V, compare, equal>::contains(K key) {
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
	bool BSTROOT<K, V, compare, equal>::is_empty() {
		if (!root) {
			return true;
		}
		else {
			return false;
		}
	}

	//IS_FULL
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	bool BSTROOT<K, V, compare, equal>::is_full() {
		return false;
	}

	//SIZE
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	size_t BSTROOT<K, V, compare, equal>::size() {
		return this->size_with_node(root);
	}

	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	size_t BSTROOT<K, V, compare, equal>::size_with_node(Node<K, V> *& root) {
		if (!root) {
			return 0;
		}
		size_t temp = 1 + this->size_with_node(root->left) + this->size_with_node(root->right);
		return temp;
	}

	//CLEAR
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	void BSTROOT<K, V, compare, equal>::clear() {
		while (root) {
			this->remove(root->key);
		}
	}

	//HEIGHT
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	size_t BSTROOT<K, V, compare, equal>::height() {
		return this->height_with_node(root);
	}


	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	size_t BSTROOT<K, V, compare, equal>::height_with_node(Node<K, V> *& root) {
		if (!root) {
			return 0;
		}
		size_t ans = std::max(this->height_with_node(root->left), this->height_with_node(root->right)) + 1;
		return ans;
	}

	//BALANCE
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	int BSTROOT<K, V, compare, equal>::balance() {
		return this->balance_with_node(root);
	}

	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	int BSTROOT<K, V, compare, equal>::balance_with_node(Node<K, V> *& root) {
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
