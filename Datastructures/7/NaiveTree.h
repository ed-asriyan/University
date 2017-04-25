//
// Created by lieroz on 12.12.16.
// Modified by ed on 19.12.16.
//

#ifndef LAB_07_NAIVETREE_H
#define LAB_07_NAIVETREE_H

#include "BaseTree.h"

template<class T>
class NaiveTree : public BaseTree<T> {
	public:
		explicit NaiveTree() = default;
		~NaiveTree() = default;

	private:
		typedef typename BaseTree<T>::Node Node;

		Node* _insert(Node*, const T&) override;
		Node* find_min(Node*);
		Node* _remove(Node*, const T&) override;

		const size_t _get_memory_amount() const override;
};

template<class T>
typename BaseTree<T>::Node* NaiveTree<T>::_insert(Node* node, const T& value) {
	if (node == nullptr) {
		return new Node(value);
	} else if (value < node->key) {
		node->left = _insert(node->left, value);
	} else if (value > node->key) {
		node->right = _insert(node->right, value);
	}
	return node;
}

template<class T>
typename BaseTree<T>::Node* NaiveTree<T>::find_min(Node* node) {
	return node->left ? find_min(node->left) : node;
}

template<class T>
typename BaseTree<T>::Node* NaiveTree<T>::_remove(Node* node, const T& value) {
	if (node == nullptr) {
		throw typename BaseTree<T>::ItemNotFoundException();
	}

	if (value < node->key) {
		node->left = _remove(node->left, value);
	} else if (value > node->key) {
		node->right = _remove(node->right, value);
	} else {

		if (node->left == nullptr) {
			Node* temp{node->right};
			delete node;
			return temp;
		} else if (node->right == nullptr) {
			Node* temp{node->left};
			delete node;
			return temp;
		}

		Node* temp{find_min(node->right)};
		node->key = temp->key;
		node->right = _remove(node->right, temp->key);
	}

	return node;
}

template<class T>
const size_t NaiveTree<T>::_get_memory_amount() const {
	const size_t nodes_count = this->get_nodes_count();
	return (sizeof(Node) - sizeof(size_t)) * nodes_count;
}

#endif // LAB_07_NAIVETREE_H