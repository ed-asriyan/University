#include <iostream>
#include <fstream>
#include <stdexcept>
#include "bigDecimal.h"

bool isValid(char ch){
	char valid[] = "0123456789"
				   "-+eE.";

	int size = sizeof(valid);
	for (int i = 0; i < size; ++i){
		if (ch == valid[i]) return true;
	}

	return false;
}

std::string readFromStream(std::istream& stream){
	std::string str;
	stream >> str;

	int ePos = 0;
	int size = str.size();
	for (int i = 0; i < size; ++i){
		if (!isValid(str[i]))
			throw std::invalid_argument("Only '0123456789eE-+.' symbols can be input!!!");
		if (str[i] == 'e' || str[i] == 'E') ePos = i;
	}

	int eLen = 0;
	int dotLen = 0;

	if (ePos)
		eLen = size - ePos + 1;

	if (size - eLen - dotLen > BASE_LEN)
		throw std::range_error("Legth of base must be equal to or less than 30!!!");

	if (ePos)
		if (size - ePos - 2 > POW_LEN)
			throw std::range_error("Power must be in [-99999, 99999] range!!!");

	return str;
}

int main(const int argc, const char** argv){
	std::string strNum_1, strNum_2;
	try{
		if (argc < 2){
			std::cout << "Enter dividend: ";
			strNum_1 = readFromStream(std::cin);

			std::cout << "Enter delimiter: ";
			strNum_2 = readFromStream(std::cin);
		} else if (argc == 2){
			std::ifstream file;
			file.open(argv[1]);
			if (file.is_open()){
				strNum_1 = readFromStream(file);
				strNum_2 = readFromStream(file);
			}

			file.close();
		} else{
			throw std::invalid_argument("'argc' can't be more than 2!!!");
		}
	} catch (std::exception& ex){
		std::cerr << "Exception was caught: " << ex.what() << std::endl;
	} catch (...){
		std::cerr << "Unexpected exception!!!" << std::endl;
	}

	try{
		BigDecimal dividend(strNum_1);
		BigDecimal delimiter(strNum_2);

		BigDecimal result = dividend / delimiter;

		std::cout << "Result of division: " << result;
	} catch (std::exception& ex){
		std::cerr << "Exception was caught: " << ex.what() << std::endl;
	} catch (...){
		std::cerr << "Unexpected exception!!!" << std::endl;
	}

	return 0;
}
