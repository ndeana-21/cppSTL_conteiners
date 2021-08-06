#include <iostream>
#include "tests.hpp"

#include "unistd.h"

int main(int argc, char const *argv[]) {
    std::string choice;

    if (argc == 2) {
        choice = std::string(argv[1]);
		if (choice == "vector" || choice == "vec" || choice == "1")
			testVector();
		else if (choice == "map" || choice == "2")
			testMap();
		else if (choice == "stack" || choice == "3")
			testStack();
		else if (choice == "set" || choice == "4")
			testSet();
		else {
			testVector();
			testMap();
			testStack();
			testSet();
		}
	}
	else
	{
		testVector();
		testMap();
		testStack();
		testSet();
	}
	return 0;
}
