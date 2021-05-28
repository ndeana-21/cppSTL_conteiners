#include "tests.hpp"

template <typename T>
static void print_vector(T vec, std::string type) {
	typename T::iterator it;

	std::cout << BOLD << type << ", size: " << vec.size() << ", empty: " << vec.empty() << ", capacity: " << vec.capacity() << RESET << std::endl;
	it = vec.begin();
	while (it != vec.end()) {
		std::cout << *it;
		if (it + 1 != vec.end())
			std::cout << " - ";
		++it;
	}
	std::cout << std::endl;
}

template <typename T>
static void print_vector_reverse(T vec, std::string type) {
	typename T::iterator it;

	std::cout << BOLD << type << ", size: " << vec.size() << ", empty: " << vec.empty() << ", capacity: " << vec.capacity() << RESET << std::endl;
	it = vec.rbegin();
	while (it != vec.rend()) {
		std::cout << *it;
		if (it + 1 != vec.rend())
			std::cout << " - ";
		++it;
	}
	std::cout << std::endl;
}

static void default_constructor(void) {
	print_header("Default constructors", BLUE);
	
	ft::Vector<int> v1;
	std::vector<int> v2;
	check("default", v1 == v2);
	
	ft::Vector<int> vf1(3, 100);
	std::vector<int> vf2(3, 100);
	check("fill", vf1 == vf2);

	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v2.push_back(1);
	v2.push_back(2);
	v2.push_back(3);
	ft::Vector<int> vr1(v2.begin(), v2.end());
	std::vector<int> vr2(v2.begin(), v2.end());
	check("range", vr1 == vr2);

	ft::Vector<int> vc3(v1);
	std::vector<int> vc4(v2);
	check("copy", vc3 == vc4);
}

static void push_back(void) {
	print_header("Push back", BLUE);

	{
		ft::Vector<std::string> vs1;
		std::vector<std::string> vs2;
		ft::Vector<int> vi1;
		std::vector<int> vi2;
		
		vi1.push_back(1);
		vi2.push_back(1);
		check("1 element int", vi1 == vi2);

		vs1.push_back("test");
		vs2.push_back("test");
		check("1 element string", vs1 == vs2);
		
		for(int i = 0; i < 1000; i++) {
			vs1.push_back("test");
			vs2.push_back("test");
			vi1.push_back(i);
			vi2.push_back(i);
		}
		check("1000 elements int", vs1 == vs2);
		check("1000 elements string", vs1 == vs2);
	}

}

static void max_size(void) {
	print_header("Max size", BLUE);
	
	ft::Vector<int> v1;
	std::vector<int> v2;
    check("empty", v1.max_size(), v2.max_size());
	
	v1.push_back(10);
	v2.push_back(10);
	check("fill", v1.max_size(), v2.max_size());
}

static void resize(void) {
	print_header("Resize", BLUE);
	
	ft::Vector<std::string> v1;
	std::vector<std::string> v2;
	v1.resize(10);
	v2.resize(10);
	check("std constructor", (v1 == v2));
	
	v1.resize(2, "42");
	v2.resize(2, "42");
	check("val", (v1 == v2));
}

static void access_operator(void) {
	print_header("[] operator, at()", BLUE);
	
	ft::Vector<int> v1;
	std::vector<int> v2;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v2.push_back(1);
	v2.push_back(2);
	v2.push_back(3);
	check("v1[0] == v2[0]", v1[0], v2[0]);
	check("v1[1] == v2[1]", v1[1], v2[1]);
	check("v1[2] == v2[2]", v1[2], v2[2]);
	try {
		v1.at(100);
		std::cout << FAIL << " v1.at(100)" << std::endl;
	} catch (std::exception &e) {
		std::cout << SUCCESS << " v1.at(100): " << e.what() << std::endl;
	}
	try {
		v2.at(100);
		std::cout << FAIL << " v2.at(100)" << std::endl;
	} catch (std::exception &e) {
		std::cout << SUCCESS << " v2.at(100): " << e.what() << std::endl;
	}
	try {
		v1.at(-1);
		std::cout << FAIL << " v.at(-1)" << std::endl;
	} catch (std::exception &e) {
		std::cout << SUCCESS << " v1.at(-1): " << e.what() << std::endl;
	}
	try {
		v2.at(-1);
		std::cout << FAIL << " v2.at(-1)" << std::endl;
	} catch (std::exception &e) {
		std::cout << SUCCESS << " v2.at(-1): " << e.what() << std::endl;
	}
}

static void front_back(void) {
	print_header("Front / Back", BLUE);
	
	ft::Vector<int> v1;
	std::vector<int> v2;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v2.push_back(1);
	v2.push_back(2);
	v2.push_back(3);
	check("front()", v1.front(), v2.front());
	check("back()", v1.back(), v2.back());
}

static void insert(void) {
	print_header("Insert", BLUE);
	
	std::vector<int> test;
	
	test.push_back(1);
	test.push_back(2);
	test.push_back(3);
	test.push_back(4);
	test.push_back(5);
	test.push_back(6);
	test.push_back(7);
	test.push_back(8);
	test.push_back(9);
	test.push_back(0);
	test.push_back(1);
	test.push_back(2);
	test.push_back(3);
	test.push_back(4);

	ft::Vector<int> v1;
	std::vector<int> v2;
	

	v1.insert(v1.begin(), 42);
	v2.insert(v2.begin(), 42);
	check("begin(), 42", v1 == v2);
	
	v1.insert(v1.end(), 21);
	v2.insert(v2.end(), 21);
	check("end(), 21", v1 == v2);
	
	v1.insert(v1.begin(), 10);
	v2.insert(v2.begin(), 10);
	check("begin(), 10", v1 == v2);
	
	v1.insert(v1.begin() + 1, 11);
	v2.insert(v2.begin() + 1, 11);
	check("begin() + 1, 11", v1 == v2);
	
	v1.insert(v1.begin() + 2, 3, 0);
	v2.insert(v2.begin() + 2, 3, 0);
	check("begin() + 2, 3, 0", v1 == v2);
	
	v1.insert(v1.begin() + 1, test.begin(), test.end());
	v2.insert(v2.begin() + 1, test.begin(), test.end());
	check("v1.begin() + 1, test.begin(), test.end()", v1 == v2);
}

static void assign(void) {
	print_header("Assign", BLUE);
	std::string test[] = {"Here", "is", "Jonny", "&"};
	int inttest[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

	ft::Vector<std::string> v1;
	std::vector<std::string> v2;
	
	ft::Vector<int> vi1;
	std::vector<int> vi2;
	
	vi1.assign(inttest, inttest + 10);
	vi2.assign(inttest, inttest + 10);
	check("int iterators", v1 == v2);

	vi1.assign(10, 10);
	vi2.assign(10, 10);
	check("int assign(10, 10)", v1 == v2);

	v1.assign(test, test + 4);
	v2.assign(test, test + 4);
	check("string iterators", v1 == v2);
	
	v1.assign(10, "&");
	v2.assign(10, "&");
	check("string assign(10, \"&\")", v1 == v2);
}

static void erase(void) {
	print_header("Erase / Clear", BLUE);
	
	int test[] = {1, 2, 3, 4};
	ft::Vector<int> v1;
	std::vector<int> v2;
	v1.assign(test, test + 4);
	v2.assign(test, test + 4);
	v1.erase(v1.begin() + 2);
	v2.erase(v2.begin() + 2);
	check("v1 == v2", v1 == v2);
	
	v1.clear();
	v2.clear();
	check("v1 == v2", v1 == v2);
}

static void swap(void) {
	print_header("Swap", BLUE);
	
	ft::Vector<int> v1;
	std::vector<int> v2;
	ft::Vector<int> v3;
	std::vector<int> v4;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v2.push_back(1);
	v2.push_back(2);
	v2.push_back(3);
	v3.push_back(42);
	v3.push_back(43);
	v4.push_back(42);
	v4.push_back(43);
	v1.swap(v3);
	v2.swap(v4);
	check("v1 == v2", v1 == v2);
	check("v3 == v4", v3 == v4);
}

static void operators(void) {
	print_header("Operators", BLUE);
	
	ft::Vector<int> v1;
	std::vector<int> v2;
	ft::Vector<int> v3;
	std::vector<int> v4;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v2.push_back(1);
	v2.push_back(2);
	v2.push_back(3);
	v3 = v1;
	v4 = v2;
	check("v1 == v2", (v1 == v3), (v2 == v4));
	check("v1 != v2", (v1 != v3), (v2 != v4));
	check("v1 > v2", (v1 > v3), (v2 > v4));
	check("v1 < v2", (v1 < v3), (v2 < v4));
	check("v1 >= v2", (v1 >= v3), (v2 >= v4));
	check("v1 <= v2", (v1 <= v3), (v2 <= v4));
	
	v1.push_back(42);
	v2.push_back(42);
	check("v1 == v2", (v1 == v3), (v2 == v4));
	check("v1 != v2", (v1 != v3), (v2 != v4));
	check("v1 > v2", (v1 > v3), (v2 > v4));
	check("v1 < v2", (v1 < v3), (v2 < v4));
	check("v1 >= v2", (v1 >= v3), (v2 >= v4));
	check("v1 <= v2", (v1 <= v3), (v2 <= v4));
	
	v3.push_back(43);
	v4.push_back(43);
	check("v1 == v2", (v1 == v3), (v2 == v4));
	check("v1 != v2", (v1 != v3), (v2 != v4));
	check("v1 > v2", (v1 > v3), (v2 > v4));
	check("v1 < v2", (v1 < v3), (v2 < v4));
	check("v1 >= v2", (v1 >= v3), (v2 >= v4));
	check("v1 <= v2", (v1 <= v3), (v2 <= v4));
}

void	testVector(void) {
	print_header("Vector", GREEN);

	default_constructor();
	push_back();
	resize();
	assign();
	max_size();
	front_back();
	access_operator();
	insert();
	erase();
	swap();
	operators();
}