//
// Created by ed on 20.12.16.
//

#ifndef LAB_05_FILE_H
#define LAB_05_FILE_H

#include <fstream>
#include <string>

template<class T>
class File {
	public:
		File(const std::string& word);

		void Insert(const T& word);
		bool Contains(const T& word);

	private:
		std::string file_path;
};

template<class T>
File<T>::File(const std::string& path) : file_path(path) {}

template<class T>
void File<T>::Insert(const T& word) {
	std::ofstream file(file_path, std::ios_base::app);
	file << word << std::endl;
}

template<class T>
bool File<T>::Contains(const T& word) {
	std::ifstream file(file_path);
	while (!file.eof()) {
		T item;
		file >> item;
		if (item == word) return true;
	}
	return false;
};

#endif //LAB_05_FILE_H
