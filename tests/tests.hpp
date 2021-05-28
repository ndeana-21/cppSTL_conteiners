#pragma once

#include <stdlib.h>
#include <iostream>

#include <list>
#include <vector>
#include <map>
#include <stack>
#include <queue>
#include <utility>

#include "../ft_stl/List.hpp"
#include "../ft_stl/Vector.hpp"
#include "../ft_stl/Map.hpp"
#include "../ft_stl/Stack.hpp"
#include "../ft_stl/Queue.hpp"

#define RESET "\e[0m"
#define BOLD "\e[1m"
#define RED "\e[91m"
#define GREEN "\e[92m"
#define BLUE "\e[94m"

#define SUCCESS "✅"
#define FAIL "❌"

void    testList(void);
void    testVector(void);
void    testMap(void);
void    testStack(void);
void    testQueue(void);

inline void print_header(std::string str, std::string color)
{
	int margin = (40 - str.length()) / 2;
	int width = (margin * 2 + str.length()) + 2;
	std::cout << color << std::endl;
	std::cout << std::string(width, '*') << std::endl;
	std::cout << "*" << std::string(margin, ' ') << str << std::string(margin, ' ') << "*" << std::endl;
	std::cout << std::string(width, '*') << std::endl;
	std::cout << RESET;
};

template <typename T>
inline void check(std::string name, T a, T b)
{
	if (a == b)
		std::cout << SUCCESS << " " << name << std::endl;
	else
		std::cout << FAIL << name << std::endl;
};

inline void check(std::string name, bool good)
{
	if (good)
		std::cout << SUCCESS << " " << name << std::endl;
	else
		std::cout << FAIL << name << std::endl;
};

template <typename T>
bool operator==(ft::Vector<T> &a, std::vector<T> &b)
{
	if (a.size() != b.size())
		return (false);
	if (a.empty() != b.empty())
		return (false);
	for (size_t i = 0; i < a.size(); i++)
	{
		if (a[i] != b[i])
			return (false);
	}
	return (true);
};

template <typename T>
bool operator==(ft::List<T> &a, std::list<T> &b)
{
	if (a.size() != b.size())
		return (false);
	if (a.empty() != b.empty())
		return (false);
	typename ft::List<T>::iterator it = a.begin();
	typename std::list<T>::iterator it2 = b.begin();
	while (it != a.end())
	{
		if (*it != *it2)
			return (false);
		++it;
		++it2;
	}
	return (true);
};

template <typename T, typename S>
bool operator==(ft::Map<T, S> &a, std::map<T, S> &b)
{
	if (a.size() != b.size())
		return (false);
	if (a.empty() != b.empty())
		return (false);
	typename ft::Map<T, S>::iterator it = a.begin();
	typename std::map<T, S>::iterator it2 = b.begin();
	while (it != a.end())
	{
		if (it->first != it2->first || it->second != it2->second)
			return (false);
		++it;
		++it2;
	}
	return (true);
};