#pragma once

namespace ft
{
    template<bool B, class T = void>
    struct enable_if {};

    template<class T>
    struct enable_if<true, T>
    { typedef T type; };

    template <class T>
	struct	is_integral{static const bool value = false;};

	template<>
	struct	is_integral<bool>{static const bool value = true;};

	template<>
	struct	is_integral<char>{static const bool value = true;};

	template<>
	struct	is_integral<short>{static const bool value = true;};

	template<>
	struct	is_integral<int>{static const bool value = true;};

	template<>
	struct	is_integral<long>{static const bool value = true;};

	template<>
	struct	is_integral<long long>{static const bool value = true;};

	template<>
	struct	is_integral<unsigned char>{static const bool value = true;};

	template<>
	struct	is_integral<unsigned short>{static const bool value = true;};

	template<>
	struct	is_integral<unsigned int>{static const bool value = true;};

	template<>
	struct	is_integral<unsigned long>{static const bool value = true;};

	template<>
	struct	is_integral<unsigned long long>{static const bool value = true;};
	
	template <typename T>
	void	swap(T &a, T &b) {
		T tmp = a;
		a = b;
		b = tmp;
	};

	template <class T>
	struct Node {
		T data;
		Node *prev;
		Node *next;
	};

	template <class Key, class T>
	struct BNode {
		std::pair<Key, T> pair;
		BNode *left;
		BNode *right;
		BNode *parent;
		bool end;
	};
};