//
// Created by lieroz on 12.12.16.
// Modified by ed on 19.12.16.
//

#ifndef LAB_07_BASETREE_H
#define LAB_07_BASETREE_H

#include <cstddef>
#include <deque>
#include <sstream>
#include <iomanip>

#include "Colors.h"

template<class T>
class BaseTree {
	public:
		explicit BaseTree() = default;
		virtual ~BaseTree();

		/**
		 * Adds element to tree.
		 */
		void Insert(const T& _key);

		/**
		 * Removes element from tree.
		 */
		void Remove(const T& _key);

		/**
		 * Returns true if element was found.
		 */
		const T& Search(T _key);

		const size_t get_cmp_count() const;
		const size_t get_nodes_count() const;
		const size_t get_memory_amount() const;

		template<class U>
		friend std::ostream& operator<<(std::ostream&, BaseTree<U>&);

	protected:
		struct Node {
			public:
				T key{};
				size_t level{1};

				Node* left{nullptr};
				Node* right{nullptr};

				explicit Node(const T& _key);

				inline bool operator==(const T& rhs);
				inline bool operator<(const T& rhs);
				inline bool operator>(const T& rhs);

				static const size_t get_cmp_count();
				static void reset_cmp_count();

			private:
				static size_t cmp_count;

		};

		Node* root{};

		virtual Node* _insert(Node*, const T&) = 0;
		virtual Node* _remove(Node*, const T&) = 0;

		virtual const size_t _get_memory_amount() const = 0;

	private:
		void clear_tree(Node*);
		const T& search(Node*, const T&);

		const size_t _get_nodes_count(const Node*) const;

		std::string to_string(const T&);
		void print_branches(std::ostream&, const std::deque<Node*>&, size_t, size_t, size_t, size_t);
		void print_nodes(std::ostream&, const std::deque<Node*>&, size_t, size_t, size_t, size_t);
		void print_leaves(std::ostream&, const std::deque<Node*>&, size_t, size_t, size_t);
		const size_t height(Node*);
		void print_pretty(std::ostream&, Node*, size_t, size_t);
		void print(std::ostream&);
};

template<class T>
inline bool BaseTree<T>::Node::operator==(const T& rhs) {
	++cmp_count;
	return this->key == rhs;
}

template<class T>
inline bool BaseTree<T>::Node::operator<(const T& rhs) {
	++cmp_count;
	return this->key < rhs;
}

template<class T>
inline bool BaseTree<T>::Node::operator>(const T& rhs) {
	++cmp_count;
	return this->key > rhs;
}

template<class T>
const size_t BaseTree<T>::Node::get_cmp_count() {
	return cmp_count;
}

template<class T>
void BaseTree<T>::Node::reset_cmp_count() {
	cmp_count = 0;
}

template<class T>
BaseTree<T>::Node::Node(const T& _key) : key{_key} {}

template<class T>
void BaseTree<T>::Insert(const T& _key) {
	root = _insert(root, _key);
}

template<class T>
void BaseTree<T>::Remove(const T& _key) {
	root = _remove(root, _key);
}

template<class T>
const T& BaseTree<T>::Search(T _key) {
	BaseTree<T>::Node::reset_cmp_count();
	return search(root, _key);
}

template<class T>
size_t BaseTree<T>::Node::cmp_count{};

template<class T>
const size_t BaseTree<T>::get_cmp_count() const {
	return BaseTree<T>::Node::get_cmp_count();
}

template<class T>
const size_t BaseTree<T>::get_nodes_count() const {
	return _get_nodes_count(root);
}

template<class T>
const size_t BaseTree<T>::get_memory_amount() const {
	return _get_memory_amount();
}

template<class T>
void BaseTree<T>::clear_tree(Node* node) {
	if (node != nullptr) {
		clear_tree(node->left);
		clear_tree(node->right);
		delete node;
	}
}

template<class T>
BaseTree<T>::~BaseTree() {
	clear_tree(root);
}

template<class T>
const T& BaseTree<T>::search(Node* node, const T& value) {
	while (node != nullptr) {
		if (*node == value) {
			return node->key;
		} else if (*node < value) {
			node = node->right;
		} else if (*node > value) {
			node = node->left;
		}
	}
	return 0;
}

template<class T>
const size_t BaseTree<T>::_get_nodes_count(const Node* node) const {
	if (node == nullptr) {
		return 0;
	}
	return _get_nodes_count(node->left) + 1 + _get_nodes_count(node->right);
}

template<typename T>
std::string BaseTree<T>::to_string(const T& value) {
	std::ostringstream ss;
	ss << value;
	return ss.str();
}

template<typename T>
void BaseTree<T>::print_branches(std::ostream& out,
                                 const std::deque<Node*>& nodes_queue,
                                 size_t branch_len,
                                 size_t node_space_len,
                                 size_t start_len,
                                 size_t level_node_count) {
	typename std::deque<Node*>::const_iterator iter = nodes_queue.begin();

	for (size_t i{}; i < level_node_count / 2; ++i) {
		out << ((i == 0) ? std::setw(static_cast<int>(start_len - 1)) : std::setw(static_cast<int>(node_space_len - 2)))
		    << "" << ((*iter++) ? "/" : " ");
		out << std::setw(static_cast<int>(2 * branch_len + 2)) << "" << ((*iter++) ? "\\" : " ");
	}
	out << std::endl;
}

template<typename T>
void BaseTree<T>::print_nodes(std::ostream& out,
                              const std::deque<Node*>& nodes_queue,
                              size_t branch_len,
                              size_t node_space_len,
                              size_t start_len,
                              size_t level_node_count) {
	typename std::deque<Node*>::const_iterator iter = nodes_queue.begin();

	for (size_t i{}; i < level_node_count; ++i, ++iter) {
		out << ((i == 0) ? std::setw(static_cast<int>(start_len)) : std::setw(static_cast<int>(node_space_len))) << ""
		    << ((*iter && (*iter)->left) ? std::setfill('_') : std::setfill(' '));
		out << std::setw(static_cast<int>(branch_len + 2))
		    << ((*iter) ? to_string((*iter)->key) : "");
		out << ((*iter && (*iter)->right) ? std::setfill('_') : std::setfill(' '))
		    << std::setw(static_cast<int>(branch_len)) << "" << std::setfill(' ');
	}
	out << std::endl;
}

template<typename T>
void BaseTree<T>::print_leaves(std::ostream& out,
                               const std::deque<Node*>& nodes_queue,
                               size_t indent_space,
                               size_t level,
                               size_t level_node_count) {
	typename std::deque<Node*>::const_iterator iter = nodes_queue.begin();

	for (size_t i{}; i < level_node_count; ++i, ++iter) {
		out << ((i == 0) ? std::setw(static_cast<int>(indent_space + 2)) : std::setw(static_cast<int>(2 * level + 2)))
		    << ((*iter) ? to_string((*iter)->key) : "");
	}
	out << std::endl;
}

template<typename T>
const size_t BaseTree<T>::height(Node* node) {
	if (node == nullptr || (node->left == nullptr && node->right == nullptr)) {
		return 0;
	}

	size_t leftDepth{height(node->left)};
	size_t rightDepth{height(node->right)};

	return leftDepth > rightDepth ?
	       leftDepth + 1 : rightDepth + 1;    // eq of the length of branch for each node of each level
}

template<typename T>
void BaseTree<T>::print_pretty(std::ostream& out, Node* root, size_t level, size_t indent_space) {
	size_t h{height(root) + 1};
	size_t level_node_count{1};

	size_t branch_len{2 * (static_cast<size_t>(pow(2.0, h)) - 1) - (3 - level) * static_cast<size_t>(pow(2.0, h - 1))};
	size_t node_space_len{2 + (level + 1) * static_cast<size_t>(pow(2.0, h))};
	size_t start_len{branch_len + (3 - level) + indent_space};

	std::deque<Node*> nodes_queue;
	nodes_queue.push_back(root);

	for (size_t r{1}; r < h; r++) {
		print_branches(out, nodes_queue, branch_len, node_space_len, start_len, level_node_count);
		branch_len = branch_len / 2 - 1;
		node_space_len = node_space_len / 2 + 1;
		start_len = branch_len + (3 - level) + indent_space;
		print_nodes(out, nodes_queue, branch_len, node_space_len, start_len, level_node_count);

		for (size_t i{}; i < level_node_count; i++) {
			Node* current_node = nodes_queue.front();
			nodes_queue.pop_front();

			if (current_node) {
				nodes_queue.push_back(current_node->left);
				nodes_queue.push_back(current_node->right);
			} else {
				nodes_queue.push_back(nullptr);
				nodes_queue.push_back(nullptr);
			}
		}

		level_node_count *= 2;
	}

	print_branches(out, nodes_queue, branch_len, node_space_len, start_len, level_node_count);
	print_leaves(out, nodes_queue, indent_space, level, level_node_count);
}

template<typename T>
void BaseTree<T>::print(std::ostream& out) {
	print_pretty(out, root, 2, 0);
}

template<typename T>
std::ostream& operator<<(std::ostream& out, BaseTree<T>& tree) {
	out << BOLD CYAN;
	tree.print(out);
	out << RST;
	return out;
}

#endif //LAB_07_BASETREE_H
