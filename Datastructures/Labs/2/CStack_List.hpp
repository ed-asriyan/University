#ifndef __CSTACK_LIST_HPP_DEF__
#define __CSTACK_LIST_HPP_DEF__

#include <iostream>
#include <sstream>

// Stack with dynamically cycled buffer
template <class T>
class CStackList {
	private:

		// Private data
		struct Node {
			T data;

			Node* next;
			Node* prev;
		};

		Node* head;
		Node* tail;

		int stack_size;

	public:

		// Constructors & destructors
		CStackList() {
			head       = nullptr;
			tail       = nullptr;
			stack_size       = 0;
		}

		~CStackList() {
			Node* p = head;

			while (p != nullptr) {
				head = head->next;
				delete p;
				p = head;
			}

			head       = nullptr;
			tail       = nullptr;
			stack_size =       0;
		}

		// Operators overloading
		CStackList& operator=(const CStackList&);
		T& operator[](const int);

		template <class U>
		friend std::ostream& operator<<(std::ostream&, const CStackList<U>&);

		template <class U>
		friend std::istream& operator>>(std::istream&, CStackList<U>&);

		// Public methods
		void Push(const T&);
		T Pop();
		void TrackMemory(std::ostream&);

		// Getters & setters
		int size() const;
		bool is_empty() const;
		T top() const;
};

// Operators overloading
template <class T>
CStackList<T>& CStackList<T>::operator=(const CStackList<T>& stack) {
	if (this != &stack) {
		Node* iter;
		for (iter = stack.head; iter; iter = iter->next) {
			this->Push(iter->data);
		}
	}

	return *this;
}

template <class T>
T& CStackList<T>::operator[](const int index) {
	Node* current = head;
	for (int i = 0; i < index; ++i) {
		current = current->next;
	}

	return current->data;
}

template <class T>
std::ostream& operator<<(std::ostream& out, const CStackList<T>& stack) {
	typename CStackList<T>::Node* iter;
	for (iter = stack.head; iter; iter = iter->next) {
		out << iter->data << ' ';
	}

	return out;
}

template <class T>
std::istream& operator>>(std::istream& in, CStackList<T>& stack) {
	T item;
	std::string input;
	while (std::getline(in, input) && !input.empty()) {

		std::stringstream stream(input);
		while (!stream.eof()) {
			stream >> item;

			if (!static_cast<T>(item)) {
				throw std::invalid_argument("INVALID ARGUMENT TYPE!!!");
			}

			stack.Push(item);
		}

		if (std::is_same<T, char>::value) {
			stack.Pop();
		}
	}

	return in;
}

// Public methods
template <class T>
void CStackList<T>::Push(const T& item) {
	Node* node = new Node;;

	node->data = item;

	if (tail) {
		tail->next = node;
	}

	node->next = nullptr;
	node->prev = tail;
	tail = node;

	if (head == nullptr) {
		head = node;
	}

	++stack_size;
}

template <class T>
T CStackList<T>::Pop() {
	if (is_empty()) {
		throw std::range_error("EMPTY STACK!!!");
	}

	Node* temp = tail->prev;

	if (head != tail){
		temp->next = nullptr;
	}

	T result = tail->data;

	delete tail;

	if (head != tail){
		tail = temp;
	} else {
		head = tail = nullptr;
	}

	--stack_size;

	return result;
}

template <class T>
void CStackList<T>::TrackMemory(std::ostream& out) {
	for (struct Node* iter = head; iter; iter = iter->next) {
		out << iter << ' ';
	}

	out << std::endl;
}

// Getters & setters
template <class T> 
int CStackList<T>::size() const {
	return stack_size;
}

template <class T>
bool CStackList<T>::is_empty() const {
	return stack_size == 0;
}

template <class T>
T CStackList<T>::top() const {
	return tail->data;
}

#endif // __CSTACK_LIST_HPP_DEF__