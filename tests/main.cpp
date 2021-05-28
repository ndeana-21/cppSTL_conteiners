#include <iostream>
#include "tests.hpp"

int main(int argc, char const *argv[]) {
    std::string choice;

    if (argc == 2) {
        choice = std::string(argv[1]);
		if (choice == "list" || choice == "1")
			testList();
		else if (choice == "vector" || choice == "2")
			testVector();
		else if (choice == "map" || choice == "3")
			testMap();
		else if (choice == "stack" || choice == "4")
			testStack();
		else if (choice == "queue" || choice == "5")
			testQueue();
		else {
			testList();
			testVector();
			testMap();
			testStack();
			testQueue();
		}
	}
	else
	{
		testList();
		testVector();
		testMap();
		testStack();
		testQueue();
	}
	return 0;
}
