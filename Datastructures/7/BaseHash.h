//
// Created by lieroz on 12.12.16.
// Modified by ed on 19.12.16.
//

#ifndef LAB_07_BASEHASH_H
#define LAB_07_BASEHASH_H

#include <cstddef>

#include "Colors.h"

template<class T, class HASH_FUNC>
class BaseHash {
	public:
		class ItemNotFoundException : public std::exception {};

		explicit BaseHash() = default;
		virtual ~BaseHash() = default;

		/**
		 * Inserts element into a hash table.
		 */
		void Insert(const T& _key);

		/**
		 * Removes element from hash table
		 */
		void Remove(const T& _key);

		/**
		 * Searches hash table for element
		 */
		const T& Search(const T& _key) const;

		const size_t get_cmp_count() const;
		const size_t get_memory_amount() const;

		template<class U, class F>
		friend std::ostream& operator<<(std::ostream& out, const BaseHash<U, F>& hash_table);

	protected:
		const size_t INIT_SIZE = 1024;
		const double REHASH_FACTOR = 0.72;

		struct Node {
			public:
				T key{};
				bool is_deleted{false};
				Node* next{nullptr};

				explicit Node(const T& _key);

				static const size_t get_cmp_count();
				static void reset_cmp_count();

				inline bool operator==(const T& rhs);

			private:
				static size_t cmp_count;
		};

		HASH_FUNC hash_func;
		size_t table_size{};
		std::vector<Node*> table{INIT_SIZE, nullptr};

		virtual void rehash() = 0;

		virtual void _insert(const T&) = 0;
		virtual void _remove(const T&) = 0;
		virtual const T& _search(const T&) const = 0;

		virtual const size_t _get_memory_amount() const = 0;

		virtual void print(std::ostream&) const = 0;
};

template<class T, class HASH_FUNC>
BaseHash<T, HASH_FUNC>::Node::Node(const T& _key) : key{_key} {}

template<class T, class HASH_FUNC>
inline bool BaseHash<T, HASH_FUNC>::Node::operator==(const T& rhs) {
	++cmp_count;
	return this->key == rhs;
}

template<class T, class HASH_FUNC>
const size_t BaseHash<T, HASH_FUNC>::Node::get_cmp_count() {
	return cmp_count;
}

template<class T, class HASH_FUNC>
void BaseHash<T, HASH_FUNC>::Node::reset_cmp_count() {
	cmp_count = 0;
}

template<class T, class HASH_FUNC>
void BaseHash<T, HASH_FUNC>::Insert(const T& _key) {
	if (static_cast<double>(BaseHash<T, HASH_FUNC>::table_size) /
		static_cast<double>(BaseHash<T, HASH_FUNC>::table.size()) >= BaseHash<T, HASH_FUNC>::REHASH_FACTOR) {
		rehash();
	}
	_insert(_key);
}

template<class T, class HASH_FUNC>
void BaseHash<T, HASH_FUNC>::Remove(const T& _key) {
	_remove(_key);
}

template<class T, class HASH_FUNC>
size_t BaseHash<T, HASH_FUNC>::Node::cmp_count{};

template<class T, class HASH_FUNC>
const T& BaseHash<T, HASH_FUNC>::Search(const T& _key) const {
	BaseHash<T, HASH_FUNC>::Node::reset_cmp_count();
	return _search(_key);
}

template<class U, class F>
std::ostream& operator<<(std::ostream& out, const BaseHash<U, F>& hash_table) {
	hash_table.print(out);
	return out;
}

template<class T, class HASH_FUNC>
const size_t BaseHash<T, HASH_FUNC>::get_cmp_count() const {
	return BaseHash<T, HASH_FUNC>::Node::get_cmp_count();
}

template<class T, class HASH_FUNC>
const size_t BaseHash<T, HASH_FUNC>::get_memory_amount() const {
	return _get_memory_amount();
}

#endif //LAB_07_BASEHASH_H
