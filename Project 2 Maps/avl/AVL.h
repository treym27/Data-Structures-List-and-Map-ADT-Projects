#ifndef AVL_H
#define AVL_H
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
	class AVL {
		
	private:
		Node<K, V> * root = nullptr;
		
	public:
		AVL();
		~AVL();
		AVL(const AVL& cc);
		AVL<K, V, compare, equal>& operator= (const AVL& ca); 
		Node<K, V> * copy_with_node(const Node<K, V>* root); 
		AVL(AVL&& mc);
		AVL<K, V, compare, equal>& operator= (AVL&& other);

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

	
	};

	//CONSTRUCTOR
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	AVL<K, V, compare, equal>::AVL() {
		root = nullptr;
	}
	//DESTRUCTOR
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	AVL<K, V, compare, equal>::~AVL() {
		this->clear();
	}

	//COPY CONSTRUCTOR
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	AVL<K, V, compare, equal>::AVL(const AVL& cc) {
		root = this->copy_with_node(cc.root);
	}

	//COPY ASSIGNMENT
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	AVL<K, V, compare, equal>& AVL<K, V, compare, equal>::operator=(const AVL& ca) {
		if (this != &ca) {
			this->clear();

			root = this->copy_with_node(ca.root);
		}
		return *this;
	}
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	Node<K, V> * AVL<K, V, compare, equal>::copy_with_node(const Node<K, V> * root) {
		if (!root) {
			return nullptr;
		}
		class Node<K, V> *temp = new Node<K, V>; ////EEEE
		temp->key = root->key;
		temp->value = root->value;
		temp->left = nullptr;
		temp->right = nullptr;

		temp->left = this->copy_with_node(root->left);
		temp->right = this->copy_with_node(root->right);

		return temp;
	}

	//MOVE CONSTRUCTOR
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	AVL<K, V, compare, equal>::AVL(AVL&& mc) {
		root = mc.root;
		mc.root = nullptr;
	}

	//MOVE ASSIGNMENT
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	AVL<K, V, compare, equal>& AVL<K, V, compare, equal>::operator=(AVL&& ma) {
		if (this != &ma) {
			this->clear();
			root = ma.root;
			ma.root = nullptr;
		}
		return *this;
	}

	//INSERT
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	void AVL<K, V, compare, equal>::insert(K key, V value) {
		root = this->insert_with_node(root, key, value);
	}

	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	Node<K, V> * AVL<K, V, compare, equal>::insert_with_node(Node<K, V> *& root, K key, V value) {
		if (!root) {
			root = new Node<K, V>;
			root->key = key;
			root->value = value;
			root->left = nullptr;
			root->right = nullptr;
		}
		else {
		
		if (compare(root->key, key)) {
			root->right = this->insert_with_node(root->right, key, value);
			int root_bal = this->balance_with_node(root);
			int right_bal = this->balance_with_node(root->right);
			if (right_bal <= 0 && root_bal <= -2) {
				class Node<K, V> *temp = root->right;
				root->right = temp->left;
				temp->left = root;
				root = temp;
			}
			if (right_bal >= 1 && root_bal <= -2) {
				class Node<K, V> *temp = root->right->left;
				root->right->left = temp->right;
				temp->right = root->right;
				root->right = temp;
				temp = root->right;
				root->right = temp->left;
				temp->left = root;
				root = temp;
			}

		}
		else if (compare(key, root->key)) {
			root->left = this->insert_with_node(root->left, key, value);
			int root_bal = this->balance_with_node(root);
			int left_bal = this->balance_with_node(root->left);
			if (left_bal >= 0 && root_bal >= 2) {
				class Node<K, V> *temp = root->left;
				root->left = temp->right;
				temp->right = root;
				root = temp;
			}
			if (left_bal <= -1 && root_bal >= 2) {
				class Node<K, V> *temp, *temp2;
				temp = root->left->right;
				root->left->right = temp->left;
				temp->left = root->left;
				root->left = temp;

				temp = root->left;
				root->left = temp->right;
				temp->right = root;
				root = temp;
			}
		}

			
		else {
			root->value = value;
		}
	}
		return root;
	}

	//--remove
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	void AVL<K, V, compare, equal>::remove(K key) {
		root = this->remove_with_node(root, key);
	}

	//--remove_with_node
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	Node<K, V>* AVL<K, V, compare, equal>::remove_with_node(Node<K, V> *& root, K key) {
		class Node<K, V> *temp;
		if (!root) {
			return root;
		}
		else {
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
				class Node<K, V> *temp2 = root->right;
				while (temp2->left) {
					temp2 = temp2->left;
				}
				root->key = temp2->key;
				root->value = temp2->value;
				root->right = remove_with_node(root->right, root->key);
			}
		}

		if (!root) {
			return root;
		}
		int root_bal = this->balance_with_node(root);
		int right_bal = 0;
		int left_bal = 0;
		if (root->right) {
			right_bal = this->balance_with_node(root->right);
		}
		if (root->left) {
			left_bal = this->balance_with_node(root->left);
		}

		if (root_bal <= -2 && right_bal <= 0) {
			class Node<K, V> *temp = root->right;
			root->right = temp->left;
			temp->left = root;
			root = temp;
		}
		else if (root_bal <= -2 && right_bal >= 1) {
			class Node<K, V> *temp = root->right->left;
			root->right->left = temp->right;
			temp->right = root->right;
			root->right = temp;

			temp = root->right;
			root->right = temp->left;
			temp->left = root;
			root = temp;
		}
		else if (root_bal >= 2 && left_bal >= 0) {
			class Node<K, V> *temp = root->left;
			root->left = temp->right;
			temp->right = root;
			root = temp;
		}
		else if (root_bal >= 2 && left_bal <= -1) {
			class Node<K, V> *temp = root->left->right;
			root->left->right = temp->left;
			temp->left = root->left;
			root->left = temp;
			temp = root->left;
			root->left = temp->right;
			temp->right = root;
			root = temp;
		}
		else {

		}
		return root;
	}
}

	//LOOKUP CONST
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	V& AVL<K, V, compare, equal>::lookup(K key) {
		return this->lookup_with_node(root, key);
	}


	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	const V& AVL<K, V, compare, equal>::lookup(K key) const {
		return this->lookup2(root, key);
	}


	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	V& AVL<K, V, compare, equal>::lookup_with_node(Node<K, V> *& root, K key) {
		if (!root) {
			throw std::runtime_error("AVL.lookup(): Nothing to look up!");

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
	const V& AVL<K, V, compare, equal>::lookup2(const Node<K, V> * root, K key) const {
		if (!root) {
			throw std::runtime_error("AVL.lookup2(): Nothing to look up!");

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
	bool AVL<K, V, compare, equal>::contains(K key) {
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
	bool AVL<K, V, compare, equal>::is_empty() {
		if (!root) {
			return true;
		}
		else {
			return false;
		}
	}

	//IS_FULL
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	bool AVL<K, V, compare, equal>::is_full() {
		return false;
	}

	//SIZE
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	size_t AVL<K, V, compare, equal>::size() {
		return this->size_with_node(root);
	}

	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	size_t AVL<K, V, compare, equal>::size_with_node(Node<K, V> *& root) {
		if (!root) {
			return 0;
		}
		size_t temp = 1;
		temp += this->size_with_node(root->left);
		temp += this->size_with_node(root->right);
		return temp;
	}

	//CLEAR
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	void AVL<K, V, compare, equal>::clear() {
		while (root) {
			this->remove(root->key);
		}
	}

	//HEIGHT
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	size_t AVL<K, V, compare, equal>::height() {
		return this->height_with_node(root);
	}

	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	size_t AVL<K, V, compare, equal>::height_with_node(Node<K, V> *& root) {
		if (!root) {
			return 0;
		}
		size_t temp = 1;
		temp += std::max(this->height_with_node(root->left), this->height_with_node(root->right));
		return temp;
	}

	//BALANCE
	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	int AVL<K, V, compare, equal>::balance() {
		return this->balance_with_node(root);
	}

	template <typename K, typename V, bool(*compare)(const K&, const K&), bool(*equal)(const K&, const K&)>
	int AVL<K, V, compare, equal>::balance_with_node(Node<K, V> *& root) {
		if (!root) {
			return 0;
		}
		int left_height = this->height_with_node(root->left);
		int right_height = this->height_with_node(root->right);
		return left_height - right_height;
	}
}
#endif
