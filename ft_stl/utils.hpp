#pragma once

#include <cstdlib>
#include <iterator>

namespace ft{
template <class T>
struct less
{
	typedef T		first_argument_type;
	typedef T		second_argument_type;
	typedef bool	result_type;

	bool operator() (const T& x, const T& y) const {return x<y;}
};
template <bool B>
struct enable_if {};
template <>
struct enable_if<true> { typedef int type; };
template <typename T>
struct is_integral { static const bool value = false; };
template <>
struct is_integral<bool> { static const bool value = true; };
template <>
struct is_integral<char> { static const bool value = true; };
template <>
struct is_integral<short> { static const bool value = true; };
template <>
struct is_integral<int> { static const bool value = true; };
template <>
struct is_integral<long> { static const bool value = true; };
template <>
struct is_integral<long long> { static const bool value = true; };
template <>
struct is_integral<unsigned char> { static const bool value = true; };
template <>
struct is_integral<unsigned short> { static const bool value = true; };
template <>
struct is_integral<unsigned int> { static const bool value = true; };

template <>
struct is_integral<unsigned long> { static const bool value = true; };

template <>
struct is_integral<unsigned long long> { static const bool value = true; };
template<class InputIt1, class InputIt2>
bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
							InputIt2 first2, InputIt2 last2)
{
	for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
		if (*first1 < *first2) return true;
		if (*first2 < *first1) return false;
	}
	return (first1 == last1) && (first2 != last2);
}
template<class InputIt1, class InputIt2, class Compare>
bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
							InputIt2 first2, InputIt2 last2,
							Compare comp)
{
	for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
		if (comp(*first1, *first2)) return true;
		if (comp(*first2, *first1)) return false;
	}
	return (first1 == last1) && (first2 != last2);
}

template <class Ite1, class Ite2>
bool	equal(Ite1 first1, Ite1 last1, Ite2 first2) {
	while (first1 != last1) {
		if (*first1 != *first2)
			return false;
		++first1; ++first2;
	}
	return true;
}
template <typename U>
void swap(U& a, U&b) {
	U tmp = a;
	a = b;
	b = tmp;
}
template <class T1, class T2> struct pair
{
public:
	typedef T1 first_type;
	typedef T2 second_type;
	first_type first;
	second_type second;
	pair(): first(T1()), second(T2()){}
	template<class U, class V> pair (const pair<U,V>& pr): first(pr.first), second(pr.second){}
	pair (const first_type& a, const second_type& b): first(a), second(b){}
	pair& operator= (const pair& pr) {first = pr.first; second = pr.second; return *this;}
	~pair(){}
};
template <class T1, class T2>
bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {return lhs.first==rhs.first && lhs.second==rhs.second;}

template <class T1, class T2>
bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {return !(lhs==rhs);}

template <class T1, class T2>
bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second);}

template <class T1, class T2>
bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {return !(rhs<lhs);}

template <class T1, class T2>
bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {return rhs<lhs;}

template <class T1, class T2>
bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs){ return !(lhs<rhs); }

template <class T1,class T2>
pair<T1,T2> make_pair (T1 x, T2 y) {return ( pair<T1,T2>(x,y) );}
template <class T>	struct iterator_traits {
	typedef std::ptrdiff_t	difference_type;
	typedef T				value_type;
	typedef T*				pointer;
	typedef const T*		const_pointer;
	typedef T&				reference;
	typedef const T&		const_reference;
	typedef size_t			size_type;
};
}