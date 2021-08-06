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

static void vector_int_filler(ft::vector<int> &input, int count) {
	for (int i = 0; i < count; i++)
		input.push_back(i);
}
static void vector_int_filler(std::vector<int> &input, int count) {
	for (int i = 0; i < count; i++)
		input.push_back(i);
}
// static void vector_str_filler(ft::vector<std::string> &input, int count) {
// 	for (int i = 0; i < count; i++)
// 		input.push_back(std::to_string(i));
// }
// static void vector_str_filler(std::vector<std::string> &input, int count) {
// 	for (int i = 0; i < count; i++)
// 		input.push_back(std::to_string(i));
// }

static void default_constructor(void) {
	print_header("Default constructors", BLUE);
	
	ft::vector<int> v1;
	std::vector<int> v2;
	check("default", v1 == v2);
	
	ft::vector<int> vf1(3, 100);
	std::vector<int> vf2(3, 100);
	check("fill", vf1 == vf2);

	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v2.push_back(1);
	v2.push_back(2);
	v2.push_back(3);
	ft::vector<int> vr1(v2.begin(), v2.end());
	std::vector<int> vr2(v2.begin(), v2.end());
	check("range", vr1 == vr2);

	ft::vector<int> vc3(v1);
	std::vector<int> vc4(v2);
	check("copy", vc3 == vc4);
}

static void Iterators() {
	print_header("Iterators", BLUE);
	ft::vector<int> v1;
	std::vector<int> v2;
	vector_int_filler(v1, 99);
	vector_int_filler(v2, 99);
	check("empty reserve", *v1.begin(), *v2.begin());
	check("empty reserve", *v1.rbegin(), *v2.rbegin());
	check("empty reserve", *--v1.end(), *--v2.end());
	check("empty reserve", *--v1.rend(), *--v2.rend());

}
static void Capacity() {
	print_header("Capacity", BLUE);
	ft::vector<int> v1;
	std::vector<int> v2;
	check("empty size", v1.size(), v2.size());
	check("empty max_size", v1.max_size(), v2.max_size());
	check("empty empty", v1.size(), v2.size());
	check("empty capacity", v1.capacity(), v2.capacity());
	v1.reserve(10);
	v2.reserve(10);
	check("empty reserve", v1 == v2);
	v1.resize(15);
	v2.resize(15);
	check("empty resize", v1 == v2);
	
	vector_int_filler(v1, 99);
	vector_int_filler(v2, 99);
	check("filled size", v1.size(), v2.size());
	check("filled max_size", v1.max_size(), v2.max_size());
	check("filled empty", v1.size(), v2.size());
	check("filled capacity", v1.capacity(), v2.capacity());
	v1.reserve(10);
	v2.reserve(10);
	check("filled reserve", v1 == v2);
	v1.resize(15);
	v2.resize(15);
	check("filled resize", v1 == v2);
}
static void Element_access() {
	print_header("Element_access", BLUE);
	ft::vector<int> v1;
	std::vector<int> v2;
	vector_int_filler(v1, 99);
	vector_int_filler(v2, 99);
	check("v1[0]", v1[0], v2[0]);
	check("v1[1]", v1[1], v2[1]);
	check("v1[2]", v1[2], v2[2]);
	check("front", v1.front(), v2.front());
	check("back", v1.back(), v2.back());
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
static void Modifiers() {
	print_header("Modifiers", BLUE);
	ft::vector<int> v1;
	std::vector<int> v2;

	vector_int_filler(v1, 100);
	vector_int_filler(v2, 100);
	check("push_back 100 elements", v1 == v2);
	
	v1.pop_back();
	v2.pop_back();
	v1.pop_back();
	v2.pop_back();
	check("pop_back", v1 == v2);
	
	ft::vector<int> v3;
	std::vector<int> v4;
	vector_int_filler(v3, 50);
	vector_int_filler(v4, 50);
	v1.swap(v3);
	v2.swap(v4);
	check("swap first pair", v1 == v2);
	check("swap second pair", v3 == v4);
	
	v1.assign(v3.begin(), v3.end());
	v2.assign(v3.begin(), v3.end());
	check("assign range", v1 == v2);
	v1.assign(100, 100);
	v2.assign(100, 100);
	check("assign fill", v1 == v2);

	v1.insert(v1.begin(), 10);
	v2.insert(v2.begin(), 10);
	check("insert single element", v1 == v2);
	v1.insert(v1.begin(), 10, 10);
	v2.insert(v2.begin(), 10, 10);
	check("insert fill", v1 == v2);
	v1.insert(v1.begin(), v1.end() - 10, v1.end() - 1);
	v2.insert(v2.begin(), v2.end() - 10, v2.end() - 1);
	check("insert range", v1 == v2);
	
	v1.erase(v1.begin());
	v2.erase(v2.begin());
	check("erase single element", v1 == v2);
	v1.erase(v1.begin(), v1.begin() + 10);
	v2.erase(v2.begin(), v2.begin() + 10);
	check("erase range", v1 == v2);

	v1.clear();
	v2.clear();
	check("clear", v1 == v2);
}

static void operators(void) {
	print_header("Operators", BLUE);
	
	ft::vector<int> v1;
	std::vector<int> v2;
	ft::vector<int> v3;
	std::vector<int> v4;
	vector_int_filler(v1, 100);
	vector_int_filler(v2, 100);
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
	print_header("vector", GREEN);

	default_constructor();
	Iterators();
	Capacity();
	Element_access();
	Modifiers();
	operators();
}