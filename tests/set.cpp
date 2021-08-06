#include "tests.hpp"

static void set_int_filler(ft::set<int> &input, int count) {
	for (int i = 0; i < count; i++) {
		input.insert(i);
	}
}
static void set_int_filler(std::set<int> &input, int count) {
	for (int i = 0; i < count; i++) {
		input.insert(i);
	}
}
static void set_string_filler(ft::set<std::string> &input, int count) {
	for (int i = 0; i < count; i++) {
		input.insert(std::to_string(i));
	}
}
static void set_string_filler(std::set<std::string> &input, int count) {
	for (int i = 0; i < count; i++) {
		input.insert(std::to_string(i));
	}
}

// static void set_print(ft::set<int> input) {
// 	ft::set<int>::iterator it_begin = input.end();
// 	ft::set<int>::iterator it_end = input.begin();
// 	it_begin--;
// 	while (it_begin != it_end)
// 	{
// 		std::cout << *it_begin << " ";
// 		it_begin--;
// 	}
// 	std::cout << std::endl;
// }

// static void set_print(std::set<int> input) {
// 	std::set<int>::iterator it_begin = input.end();
// 	std::set<int>::iterator it_end = input.begin();
// 	it_begin--;
// 	while (it_begin != it_end)
// 	{
// 		std::cout << *it_begin << " ";
// 		it_begin--;
// 	}
// 	std::cout << std::endl;
// }

static void Constructors(void)
{
	print_header("Constructors / Copy", BLUE);
	int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	ft::set<int> ft_set;
	std::set<int> std_set;

	check("default", (ft_set == std_set));
	ft::set<int> m3(a, a + 3);
	std::set<int> m4(a, a + 3);
	check("range", (m3 == m4));
	ft::set<int> m5(m3);
	std::set<int> m6(m4);
	check("copy", (m3 == m4));
	ft::set<int> ft_set4;
	std::set<int> std_set4;
	set_int_filler(ft_set, 100);
	set_int_filler(std_set, 100);
	ft_set4 = ft_set;
	std_set4 = std_set;
	check("operator =", (ft_set4 == std_set4));
}

static void Modifiers() {
	print_header("Modifiers", BLUE);

	ft::set<int> ft_set;
	std::set<int> std_set;
	set_int_filler(ft_set, 100);
	set_int_filler(std_set, 100);
	check("insert 100 int", (ft_set == std_set));

	ft::set<std::string> ft_set_str;
	std::set<std::string> std_set_str;
	set_string_filler(ft_set_str, 100);
	set_string_filler(std_set_str, 100);
	check("insert 100 string", (ft_set == std_set));

	ft::set<int> ft_set2;
	std::set<int> std_set2;
	set_int_filler(ft_set2, 50);
	set_int_filler(std_set2, 50);
	ft_set.swap(ft_set2);
	std_set.swap(std_set2);
	check("swap", (ft_set == std_set) && (ft_set2 == std_set2));

	ft_set2.erase(10);
	std_set2.erase(10);
	check("erase(10)", ft_set2 == std_set2);
	ft_set2.erase(--ft_set2.end());
	std_set2.erase(--std_set2.end());
	check("erase(--set.end())", ft_set2 == std_set2);
	ft_set2.erase(ft_set2.begin(), ++ft_set2.begin());
	std_set2.erase(std_set2.begin(), ++std_set2.begin());
	check("erase(set.begin(), ++set.begin())", ft_set2 == std_set2);
	
	ft_set.clear();
	std_set.clear();
	check("clear", ft_set == std_set);
}

static void Iterators() {
	print_header("Iterators", BLUE);
	ft::set<int> ft_set;
	std::set<int> std_set;
	set_int_filler(ft_set, 200);
	set_int_filler(std_set, 200);

	check("begin", (*ft_set.begin()), (*std_set.begin()));
	check("begin ++", *(ft_set.begin()++) == *(std_set.begin()++));
	check("end --", *(--ft_set.end()) == *(--std_set.end()));

	check("rbegin", *(ft_set.rbegin()) == *(std_set.rbegin()));
	check("rbegin ++", *(ft_set.rbegin()++) == *(std_set.rbegin()++));
	check("rend --", *(--ft_set.rend()) == *(--std_set.rend()));
}

static void Capacity() {
	print_header("Capacity", BLUE);
	ft::set<std::string> ft_set_str;
	std::set<std::string> std_set_str;

	check("empty", ft_set_str.empty(), std_set_str.empty());
	check("size", ft_set_str.size(), std_set_str.size());
	check("max_size", ft_set_str.max_size(), std_set_str.max_size());
	set_string_filler(ft_set_str, 100);
	set_string_filler(std_set_str, 100);
	check("empty filled", ft_set_str.empty(), std_set_str.empty());
	check("size filled", ft_set_str.size(), std_set_str.size());
	check("max_size filled", ft_set_str.max_size(), std_set_str.max_size());
}

static void Lookup() {
	print_header("Lookup", BLUE);
	ft::set<int> ft_set;
	std::set<int> std_set;

	set_int_filler(ft_set, 100);
	set_int_filler(std_set, 100);
	check("count(5)", ft_set.count(5), std_set.count(5));
	check("find(5)", *(ft_set.find(5)), *(std_set.find(5)));
	check("count(5) first", *ft_set.equal_range(5).first, *std_set.equal_range(5).first);
	check("count(5) second", *ft_set.equal_range(5).second, *std_set.equal_range(5).second);
	check("lower_bound(5)", *(ft_set.lower_bound(5)), *(std_set.lower_bound(5)));
	check("upper_bound(5)", *(ft_set.upper_bound(5)), *(std_set.upper_bound(5)));
}

static void Operators(void)
{
	print_header("Operators", BLUE);
	ft::set<int> ft_set;
	std::set<int> std_set;
	set_int_filler(ft_set, 100);
	set_int_filler(std_set, 100);

	ft::set<int> m3;
	std::set<int> m4;
	m3 = ft_set;
	m4 = std_set;
	check("operator ==", (ft_set == m3), (std_set == m4));
	check("operator !=", (ft_set != m3), (std_set != m4));
	check("operator >", (ft_set > m3), (std_set > m4));
	check("operator <", (ft_set < m3), (std_set < m4));
	check("operator >=", (ft_set >= m3), (std_set >= m4));
	check("operator <=", (ft_set <= m3), (std_set <= m4));
	ft_set.erase(1);
	std_set.erase(1);
	check("operator == after erase", (ft_set == m3), (std_set == m4));
	check("operator != after erase", (ft_set != m3), (std_set != m4));
	check("operator >  after erase", (ft_set > m3), (std_set > m4));
	check("operator <  after erase", (ft_set < m3), (std_set < m4));
	check("operator >= after erase", (ft_set >= m3), (std_set >= m4));
	check("operator <= after erase", (ft_set <= m3), (std_set <= m4));
}

void testSet(void)
{
	print_header("Set", GREEN);
	Constructors();
	Iterators();
	Capacity();
	Modifiers();
	Lookup();
	Operators();
}
