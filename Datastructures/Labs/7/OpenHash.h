//
// Created by lieroz on 12.12.16.
// Modified by ed on 19.12.16.
//

#ifndef LAB_07_OPENHASH_H
#define LAB_07_OPENHASH_H

#include "BaseHash.h"

template<class T, class HASH_FUNC>
class OpenHash : public BaseHash<T, HASH_FUNC> {
	public:
		explicit OpenHash() = default;
		~OpenHash();

	private:
		typedef typename BaseHash<T, HASH_FUNC>::Node Node;

		void rehash() override;
		void clear_table();

		void _insert(const T&) override;
		void _remove(const T&) override;
		const T& _search(const T&) const override;

		const size_t _get_memory_amount() const override;

		void print(std::ostream&) const override;
};

template<class T, class HASH_FUNC>
OpenHash<T, HASH_FUNC>::~OpenHash() {
	clear_table();
}

template<class T, class HASH_FUNC>
void OpenHash<T, HASH_FUNC>::clear_table() {
	for (size_t i{}; i < BaseHash<T, HASH_FUNC>::table.size(); ++i) {
		delete BaseHash<T, HASH_FUNC>::table[i];
	}
}

template<class T, class HASH_FUNC>
void OpenHash<T, HASH_FUNC>::rehash() {
	size_t new_size{BaseHash<T, HASH_FUNC>::table.size() * 2};
	std::vector<Node*> new_table{new_size, nullptr};

	for (size_t i{}; i < BaseHash<T, HASH_FUNC>::table.size(); ++i) {
		if (BaseHash<T, HASH_FUNC>::table[i] != nullptr && !BaseHash<T, HASH_FUNC>::table[i]->is_deleted) {
			size_t hash{BaseHash<T, HASH_FUNC>::hash_func(BaseHash<T, HASH_FUNC>::table[i]->key, new_size)};
			size_t j{};

			while (new_table[hash] != nullptr && j < new_size) {
				hash = (hash + (j * j)) % new_size;
				++j;
			}

			new_table[hash] = new Node(BaseHash<T, HASH_FUNC>::table[i]->key);
		}
	}

	clear_table();
	BaseHash<T, HASH_FUNC>::table = new_table;
}

template<class T, class HASH_FUNC>
void OpenHash<T, HASH_FUNC>::_insert(const T& _key) {
	size_t hash{BaseHash<T, HASH_FUNC>::hash_func(_key, BaseHash<T, HASH_FUNC>::table.size())};
	ssize_t deleted_node_index{-1};
	size_t i{};

	while (BaseHash<T, HASH_FUNC>::table[hash] != nullptr && i < BaseHash<T, HASH_FUNC>::table.size()) {
		if (BaseHash<T, HASH_FUNC>::table[hash]->key == _key && !BaseHash<T, HASH_FUNC>::table[hash]->is_deleted) {
			return;
		}

		if (BaseHash<T, HASH_FUNC>::table[hash]->is_deleted && deleted_node_index < 0) {
			deleted_node_index = hash;
		}

		hash = (hash + (i * i)) % BaseHash<T, HASH_FUNC>::table.size();
		++i;
	}

	if (deleted_node_index >= 0) {
		BaseHash<T, HASH_FUNC>::table[deleted_node_index]->key = _key;
		BaseHash<T, HASH_FUNC>::table[deleted_node_index]->is_deleted = false;
	} else {
		BaseHash<T, HASH_FUNC>::table[hash] = new Node(_key);
	}

	++BaseHash<T, HASH_FUNC>::table_size;
}

template<class T, class HASH_FUNC>
void OpenHash<T, HASH_FUNC>::_remove(const T& _key) {
	size_t hash{BaseHash<T, HASH_FUNC>::hash_func(_key, BaseHash<T, HASH_FUNC>::table.size())};
	size_t i{};

	while (BaseHash<T, HASH_FUNC>::table[hash] != nullptr && i < BaseHash<T, HASH_FUNC>::table.size()) {
		if (BaseHash<T, HASH_FUNC>::table[hash]->key == _key && !BaseHash<T, HASH_FUNC>::table[hash]->is_deleted) {
			BaseHash<T, HASH_FUNC>::table[hash]->is_deleted = true;
			--BaseHash<T, HASH_FUNC>::table_size;
			return;
		}

		hash = (hash + (i * i)) % BaseHash<T, HASH_FUNC>::table.size();
		++i;
	}
}

template<class T, class HASH_FUNC>
const T& OpenHash<T, HASH_FUNC>::_search(const T& _key) const {
	size_t hash{BaseHash<T, HASH_FUNC>::hash_func(_key, BaseHash<T, HASH_FUNC>::table.size())};
	size_t i{};

	while (BaseHash<T, HASH_FUNC>::table[hash] != nullptr && i < BaseHash<T, HASH_FUNC>::table.size()) {
		if (*BaseHash<T, HASH_FUNC>::table[hash] == _key && !BaseHash<T, HASH_FUNC>::table[hash]->is_deleted) {
			return BaseHash<T, HASH_FUNC>::table[hash]->key;
		}

		hash = (hash + (i * i)) % BaseHash<T, HASH_FUNC>::table.size();
		++i;
	}

	return 0;
}

template<class T, class HASH_FUNC>
const size_t OpenHash<T, HASH_FUNC>::_get_memory_amount() const {
	return (sizeof(Node) - sizeof(Node*)) * BaseHash<T, HASH_FUNC>::table_size;
}

template<class T, class HASH_FUNC>
void OpenHash<T, HASH_FUNC>::print(std::ostream& out) const {
	for (size_t i{}; i < BaseHash<T, HASH_FUNC>::table.size(); ++i) {
		if (BaseHash<T, HASH_FUNC>::table[i] != nullptr && !BaseHash<T, HASH_FUNC>::table[i]->is_deleted) {
			out << BOLD YELLOW << '[' << i << "] : {" << BaseHash<T, HASH_FUNC>::table[i]->key << '}' << RST
			    << std::endl;
		}
	}
}

#endif // LAB_07_OPENHASH_H