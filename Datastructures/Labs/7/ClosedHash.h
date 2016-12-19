//
// Created by lieroz on 12.12.16.
// Modified by ed on 19.12.16.
//

#ifndef LAB_07_CLOSEDHASH_H
#define LAB_07_CLOSEDHASH_H

#include "BaseHash.h"

template<class T, class HASH_FUNC>
class ClosedHash : public BaseHash<T, HASH_FUNC> {
	public:
		explicit ClosedHash() = default;
		~ClosedHash();

	private:
		typedef typename BaseHash<T, HASH_FUNC>::Node Node;

		void rehash() override;

		void _insert(const T&) override;
		void _remove(const T&) override;
		const T& _search(const T&) const override;

		void print(std::ostream&) const override;

		const size_t _get_memory_amount() const override;
};

template<class T, class HASH_FUNC>
ClosedHash<T, HASH_FUNC>::~ClosedHash() {
	for (size_t i{}; i < BaseHash<T, HASH_FUNC>::table.size(); ++i) {
		Node* node{BaseHash<T, HASH_FUNC>::table[i]};

		while (node != nullptr) {
			Node* temp{node};
			node = node->next;
			delete temp;
		}
	}
}

template<class T, class HASH_FUNC>
void ClosedHash<T, HASH_FUNC>::rehash() {
	std::vector<Node*> old_table{BaseHash<T, HASH_FUNC>::table};
	BaseHash<T, HASH_FUNC>::table.resize(old_table.size() * 2, nullptr);

	BaseHash<T, HASH_FUNC>::table_size = 0;

	for (size_t hash{}; hash < old_table.size(); ++hash) {
		if (old_table[hash] != nullptr) {
			Node* p_crawl{old_table[hash]};

			while (p_crawl != nullptr) {
				_insert(p_crawl->key);
				p_crawl = p_crawl->next;
			}
		}
	}
}

template<class T, class HASH_FUNC>
void ClosedHash<T, HASH_FUNC>::_insert(const T& _key) {
	size_t hash{BaseHash<T, HASH_FUNC>::hash_func(_key, BaseHash<T, HASH_FUNC>::table.size())};

	if (BaseHash<T, HASH_FUNC>::table[hash] == nullptr) {
		++BaseHash<T, HASH_FUNC>::table_size;
	}

	for (Node* p_crawl{BaseHash<T, HASH_FUNC>::table[hash]}; p_crawl != nullptr; p_crawl = p_crawl->next) {

		if (p_crawl->key == _key) {
			return;
		}
	}

	Node* new_node{new Node(_key)};
	new_node->next = BaseHash<T, HASH_FUNC>::table[hash];
	BaseHash<T, HASH_FUNC>::table[hash] = new_node;
}

template<class T, class HASH_FUNC>
void ClosedHash<T, HASH_FUNC>::_remove(const T& _key) {
	size_t hash{BaseHash<T, HASH_FUNC>::hash_func(_key, BaseHash<T, HASH_FUNC>::table.size())};

	if (BaseHash<T, HASH_FUNC>::table[hash] == nullptr) {
		return;
	}

	Node* node = BaseHash<T, HASH_FUNC>::table[hash];

	if (node->key == _key) {
		BaseHash<T, HASH_FUNC>::table[hash] = node->next;

		if (node->next == nullptr) {
			--BaseHash<T, HASH_FUNC>::table_size;
		}

		delete node;
		return;
	}

	for (Node* next_node{node->next}; next_node != nullptr; node = next_node, next_node = next_node->next) {
		if (next_node->key == _key) {
			node->next = next_node->next;
			delete next_node;
			return;
		}
	}
}

template<class T, class HASH_FUNC>
const T& ClosedHash<T, HASH_FUNC>::_search(const T& _key) const {
	size_t hash{BaseHash<T, HASH_FUNC>::hash_func(_key, BaseHash<T, HASH_FUNC>::table.size())};

	for (Node* node{BaseHash<T, HASH_FUNC>::table[hash]}; node != nullptr; node = node->next) {
		if (*node == _key) {
			return node->key;
		}
	}

	return 0;
}

template<class T, class HASH_FUNC>
const size_t ClosedHash<T, HASH_FUNC>::_get_memory_amount() const {
	size_t allocated_memory{};

	for (size_t i{}; i < BaseHash<T, HASH_FUNC>::table.size(); ++i) {
		Node* node{BaseHash<T, HASH_FUNC>::table[i]};

		while (node != nullptr) {
			allocated_memory += sizeof(Node) - sizeof(bool);
			node = node->next;
		}
	}

	return allocated_memory;
}

template<class T, class HASH_FUNC>
void ClosedHash<T, HASH_FUNC>::print(std::ostream& out) const {
	for (size_t i{}; i < BaseHash<T, HASH_FUNC>::table.size(); ++i) {
		if (BaseHash<T, HASH_FUNC>::table[i] != nullptr) {
			out << BOLD YELLOW << '[' << i << "] : ";

			for (Node* p_crawl{BaseHash<T, HASH_FUNC>::table[i]}; p_crawl != nullptr; p_crawl = p_crawl->next) {
				out << '{' << p_crawl->key << "} -> ";
			}

			out << BOLD RED << "nullptr" << RST << std::endl;
		}
	}
}

#endif // LAB_07_CLOSEDHASH_H