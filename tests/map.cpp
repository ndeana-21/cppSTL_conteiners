#include "tests.hpp"

template <class T>
static void print_map(T &map)
{
	typename T::iterator it = map.begin();
	std::cout << " --- map of size " << map.size() << " ---" << std::endl;
	while (it != map.end())
	{
		std::cout << it->first << ": " << it->second << std::endl;
		++it;
	}
	std::cout << " --- " << std::endl;
}

static void Constructors(void)
{
	print_header("Constructors / Copy", BLUE);
	ft::pair<int, int> a[] = {ft::make_pair(0, 1), ft::make_pair(1, 0), ft::make_pair(2, 1)};
	std::pair<int, int> b[] = {std::make_pair(0, 1), std::make_pair(1, 0), std::make_pair(2, 1)};
	ft::map<int, int> m1;
	std::map<int, int> m2;
	check("(default) m1 == m2", (m1 == m2));

	ft::map<int, int> m3(a, a + 3);
	std::map<int, int> m4(b, b + 3);
	check("(range) m3 == m4", (m3 == m4));

	ft::map<int, int> m5(m3);
	std::map<int, int> m6(m4);
	check("(copy) m5 == m6", (m3 == m4));

	ft::map<int, int> m7;
	std::map<int, int> m8;
	m7[0] = 1;
	m7[1] = 2;
	m7[2] = 3;
	m8[0] = 1;
	m8[1] = 2;
	m8[2] = 3;
	check("(copy) m7 == m8", (m7 == m8));

	ft::map<int, int> m9;
	std::map<int, int> m10;
	m9 = m7;
	m10 = m8;
	check("(copy) m9 == m10", (m9 == m10));
}

static void Iterators() {
	print_header("Iterators", BLUE);
	ft::map<std::string, int> m1;
	std::map<std::string, int> m2;
	m1["a"] = 1;
	m1["b"] = 42;
	m1["c"] = 42;
	m1["d"] = 42;
	m2["a"] = 1;
	m2["b"] = 42;
	m2["c"] = 42;
	m2["d"] = 42;

	check("begin first", (*m1.begin()).first == (*m2.begin()).first);
	check("begin second", (*m1.begin()).second == (*m2.begin()).second);
	check("end first", (*--m1.end()).first == (*--m2.end()).first);
	check("end second", (*(--m1.end())).second == (*(--m2.end())).second);
	check("rbegin first", (*m1.rbegin()).first == (*m2.rbegin()).first);
	check("rbegin second", (*m1.rbegin()).second == (*m2.rbegin()).second);
	check("rend first", (*--m1.rend()).first == (*--m2.rend()).first);
	check("rend second", (*(--m1.rend())).second == (*(--m2.rend())).second);
}

static void Capacity() {
	print_header("Capacity", BLUE);
	ft::map<std::string, int> m1;
	std::map<std::string, int> m2;
	check("empty empty", m1.empty() == m2.empty());
	check("size empty", m1.size() == m2.size());
	check("max_size empty", m1.max_size() == m2.max_size());
	m1["a"] = 1;
	m1["b"] = 42;
	m1["c"] = 42;
	m1["d"] = 42;
	m2["a"] = 1;
	m2["b"] = 42;
	m2["c"] = 42;
	m2["d"] = 42;
	check("empty filled", m1.empty() == m2.empty());
	check("size filled", m1.size() == m2.size());
	check("max_size filled", m1.max_size() == m2.max_size());
}

static void access_operator(void)
{
	print_header("[] operator", BLUE);
	ft::map<std::string, int> m1;
	std::map<std::string, int> m2;
	m1["a"] = 1;
	m1["b"] = 0;
	m1["c"] = 42;
	m1["d"] = -5;
	m1["d"] = 11;
	m1["test"] = 100;
	m2["a"] = 1;
	m2["b"] = 0;
	m2["c"] = 42;
	m2["d"] = -5;
	m2["d"] = 11;
	m2["test"] = 100;
	check("m1 == m2", m1 == m2);
	check("m1['a'] == m2['a']", m1["a"], m2["a"]);
	check("m1['d'] == m2['d']", m1["d"], m2["d"]);
	check("m1['test'] == m2['test']", m1["test"], m2["test"]);
	check("m1['z'] == m2['z']", m1["z"], m2["z"]);
}

static void Modifiers() {
	print_header("Modifiers", BLUE);
	ft::map<std::string, int> m1;
	std::map<std::string, int> m2;
	m1["a"] = 1;
	m1["b"] = 42;
	m1["c"] = 42;
	m1["d"] = 42;
	m2["a"] = 1;
	m2["b"] = 42;
	m2["c"] = 42;
	m2["d"] = 42;

	m1.erase("a");
	m2.erase("a");
	check("erase by key", m1 == m2);
	m1.erase(++m1.begin());
	m2.erase(++m2.begin());
	check("erase by iterator", m1 == m2);
	m1.erase(++m1.begin(), --m1.end());
	m2.erase(++m2.begin(), --m2.end());
	check("erase by range iterators", m1 == m2);

	ft::map<std::string, int> ft_swap1;
	std::map<std::string, int> std_swap1;
	ft::map<std::string, int> ft_swap2;
	std::map<std::string, int> std_swap2;
	ft_swap1["a"] = 1;
	ft_swap1["b"] = 2;
	ft_swap1["c"] = 3;
	std_swap1["a"] = 1;
	std_swap1["b"] = 2;
	std_swap1["c"] = 3;
	ft_swap2["a"] = 42;
	ft_swap2["b"] = 21;
	std_swap2["a"] = 42;
	std_swap2["b"] = 21;
	ft_swap1.swap(ft_swap2);
	std_swap1.swap(std_swap2);
	check("swap first pair", ft_swap1 == std_swap1);
	check("swap second pair", ft_swap2 == std_swap2);

	m1.insert(ft::make_pair("y", 0));
	m2.insert(std::make_pair("y", 0));
	m1.insert(ft::make_pair("z", 54));
	m2.insert(std::make_pair("z", 54));
	check("insert single element", m1 == m2);
	m1.insert(++m1.begin(), ft::make_pair("x", 5));
	m2.insert(++m2.begin(), std::make_pair("x", 5));
	check("insert with hint", m1 == m2);
	m1.insert(ft_swap1.begin(), ft_swap1.end());
	m2.insert(std_swap1.begin(), std_swap1.end());
	check("insert range", m1 == m2);

	m1.clear();
	m2.clear();
	check("m1 == m2", m1 == m2);
}

static void Operators(void)
{
	print_header("Operators", BLUE);
	ft::map<std::string, int> m1;
	std::map<std::string, int> m2;
	m1["a"] = 1;
	m1["b"] = 42;
	m1["c"] = 42;
	m1["d"] = 42;
	m2["a"] = 1;
	m2["b"] = 42;
	m2["c"] = 42;
	m2["d"] = 42;

	check("find first", m1.find("a")->first, m2.find("a")->first);
	check("find second", m1.find("a")->second, m2.find("a")->second);

	check("count('a')", m1.count("a"), m2.count("a"));
	check("count('b')", m1.count("b"), m2.count("b"));
	check("count('z')", m1.count("z"), m2.count("z"));

	check("lower_bound first", m1.lower_bound("a")->first, m2.lower_bound("a")->first);
	check("lower_bound second", m1.lower_bound("c")->second, m2.lower_bound("c")->second);
	
	check("upper_bound first", m1.upper_bound("a")->first, m2.upper_bound("a")->first);
	check("upper_bound second", m1.upper_bound("c")->second, m2.upper_bound("c")->second);
	
	ft::pair<ft::map<std::string, int>::iterator, ft::map<std::string, int>::iterator> a = m1.equal_range("a");
	std::pair<std::map<std::string, int>::iterator, std::map<std::string, int>::iterator> b = m2.equal_range("a");
	check("equal_range first->first", a.first->first, b.first->first);
	check("equal_range first->second", a.first->second, b.first->second);
	check("equal_range second->first", a.second->first, b.second->first);
	check("equal_range second->second", a.second->second, b.second->second);

	ft::map<std::string, int> m3;
	std::map<std::string, int> m4;
	m3 = m1;
	m4 = m2;
	check("m1 == m2", (m1 == m3), (m2 == m4));
	check("m1 != m2", (m1 != m3), (m2 != m4));
	check("m1 > m2", (m1 > m3), (m2 > m4));
	check("m1 < m2", (m1 < m3), (m2 < m4));
	check("m1 >= m2", (m1 >= m3), (m2 >= m4));
	check("m1 <= m2", (m1 <= m3), (m2 <= m4));
	m1["e"] = 1;
	m2["e"] = 1;
	check("m1 == m2", (m1 == m3), (m2 == m4));
	check("m1 != m2", (m1 != m3), (m2 != m4));
	check("m1 > m2", (m1 > m3), (m2 > m4));
	check("m1 < m2", (m1 < m3), (m2 < m4));
	check("m1 >= m2", (m1 >= m3), (m2 >= m4));
	check("m1 <= m2", (m1 <= m3), (m2 <= m4));
	m3["e"] = 3;
	m4["e"] = 3;
	check("m1 == m2", (m1 == m3), (m2 == m4));
	check("m1 != m2", (m1 != m3), (m2 != m4));
	check("m1 > m2", (m1 > m3), (m2 > m4));
	check("m1 < m2", (m1 < m3), (m2 < m4));
	check("m1 >= m2", (m1 >= m3), (m2 >= m4));
	check("m1 <= m2", (m1 <= m3), (m2 <= m4));
}

void testMap(void)
{
	print_header("map", GREEN);
	Constructors();
	Iterators();
	Capacity();
	access_operator();
	Modifiers();
	Operators();
}
