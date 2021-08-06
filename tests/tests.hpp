#pragma once

#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <utility>
#include <string>

#include <vector>
#include <map>
#include <stack>
#include <set>

#include "vector.hpp"
#include "map.hpp"
#include "stack.hpp"
#include "set.hpp"

#define RESET "\e[0m"
#define BOLD "\e[1m"
#define RED "\e[91m"
#define GREEN "\e[92m"
#define BLUE "\e[94m"

#define SUCCESS "✅"
#define FAIL "❌"


void    testVector(void);
void    testMap(void);
void    testStack(void);
void    testSet(void);

static std::clock_t	g_timer = std::clock();
static std::clock_t	g_timerFT = std::clock();
static std::clock_t	g_timerSTD = std::clock();

namespace ftt 
{
inline void reset() {
	g_timer = std::clock();
}

inline void STL_set() {
	g_timerSTD = std::clock() - g_timer;
	reset();
}

inline void FT_set() {
	g_timerFT = std::clock() - g_timer;
	reset();
}

inline void result_print() {
	if (g_timerFT <= g_timerSTD)
		std::cout << GREEN;
	else
		std::cout << RED;
	std::cout << "ft " << g_timerFT << " vs " << g_timerSTD << " stl" << RESET << std::endl;
}

}

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

// template <typename T, typename B>
// inline void check(std::string name, T a, B b)
// {
// 	if (a == b)
// 		std::cout << SUCCESS << " " << name << std::endl;
// 	else
// 		std::cout << FAIL << name << std::endl;
// };

inline void check(std::string name, bool good)
{
	if (good)
		std::cout << SUCCESS << " " << name << std::endl;
	else
		std::cout << FAIL << name << std::endl;
};





template <typename T>
bool operator==(ft::vector<T> &ft_vec, std::vector<T> &std_vec)
{
	if (ft_vec.size() != std_vec.size())
		return (false);
	if (ft_vec.empty() != std_vec.empty())
		return (false);
	for (size_t i = 0; i < ft_vec.size(); i++)
	{
		if (ft_vec[i] != std_vec[i])
			return (false);
	}
	return (true);
};

template <typename T, typename S>
bool operator==(ft::map<T, S> &ft_map, std::map<T, S> &std_map)
{
	if (ft_map.size() != std_map.size())
		return (false);
	if (ft_map.empty() != std_map.empty())
		return (false);
	typename ft::map<T, S>::iterator ft_it = ft_map.begin();
	typename std::map<T, S>::iterator std_it = std_map.begin();
	while (ft_it != ft_map.end() || std_it != std_map.end())
	{
		if (ft_it->first != std_it->first || ft_it->second != std_it->second)
			return (false);
		++ft_it;
		++std_it;
	}
	return (true);
};

template <typename T>
bool operator==(ft::stack<T> &ft_stack, std::stack<T> &std_stack)
{
	if (ft_stack.size() != std_stack.size())
		return (false);
	if (ft_stack.empty() != std_stack.empty())
		return (false);
	ft::stack<T> testA = ft_stack;
	std::stack<T> testB = std_stack;
	for (size_t i = testB.size(); i > 0; i--)
	{
		if (testA.top() != testB.top())
			return (false);
		testB.pop();
		testA.pop();
	}
	return (true);
};

template <typename T>
bool operator==(ft::set<T> &ft_set, std::set<T> &std_set)
{
	if (ft_set.size() != std_set.size())
		return (false);
	if (ft_set.empty() != std_set.empty())
		return (false);
	typename ft::set<T>::iterator ft_it = ft_set.begin();
	typename std::set<T>::iterator std_it = std_set.begin();
	while (ft_it != ft_set.end())
	{
		if (*(ft_it) != *(std_it))
			return (false);
		++ft_it;
		++std_it;
	}
	return (true);
};
