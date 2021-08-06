#pragma once

#include <limits>

#include "utils.hpp"
#include "rbtree.hpp"

namespace ft
{
template <typename T, typename Compare = ft::less<T>, class Alloc = std::allocator<T> >
class set
{
public:
	typedef T											key_type;
	typedef T											value_type;
	typedef Compare										key_compare;
	typedef Compare										value_compare;
	typedef Alloc										allocator_type;
	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::const_reference	const_reference;
	typedef typename allocator_type::pointer			pointer;
	typedef typename allocator_type::const_pointer		const_pointer;
	typedef typename allocator_type::difference_type	difference_type;
	typedef typename allocator_type::size_type			size_type;
	typedef rbtree_iterator<value_type>					iterator;
	typedef rbtree_const_iterator<value_type>			const_iterator;
	typedef ft::reverse_iterator<iterator>				reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

private:
	typedef rbtree<T, Compare>	_tree_type;
	typedef set<T, Compare>		_Self;

	_tree_type _tree;
	static bool keys_equal(const T &p1, const T &p2) {Compare comp; return !(comp(p1, p2) || comp(p2, p1));}
	static bool key_gr_eq(const T &p1, const T &p2) {Compare comp; return (!comp(p2, p1));}
	static bool key_sm(const T &p1, const T &p2 ) {Compare comp; return comp(p1, p2);}
			
public:
	set(const Compare &comp = Compare()): _tree(comp) {}
	template <typename InputIt>
	set(InputIt first, InputIt last, const value_compare &comp = value_compare()): _tree(first, last, comp) {}
	set(const _Self &o) : _tree(o._tree) {}
	~set() {}

	_Self &operator=(const _Self &o ){_tree = o._tree; return *this;}

	iterator begin(){return _tree.begin();}
	const_iterator begin() const{return _tree.begin();}

	iterator end(){return _tree.end();}
	const_iterator end() const{return _tree.end();}

	reverse_iterator rbegin(){return _tree.rbegin();}
	const_reverse_iterator rbegin() const{return _tree.rbegin();}

	reverse_iterator rend(){return _tree.rend();}
	const_reverse_iterator rend() const{return _tree.rend();}

	bool empty() const{return _tree.empty();}
	size_type size() const{return _tree.size();}
	size_type max_size() const	{return _tree.max_size();}
	
	void clear() {_tree.clear();}

	pair<iterator, bool> insert(const value_type &val) {
		size_type length_before = size();
		iterator it = _tree.insert(val);
		bool elementInserted = size() > length_before;
		
		return ft::make_pair<iterator, bool>(it, elementInserted);
	}
	iterator insert(iterator hint, const value_type &val) {return _tree.insert(hint, val);}
	template <typename InputIt>
	void insert(InputIt first, InputIt last) {_tree.insert(first, last);}

	void erase(iterator first, iterator last) {_tree.erase(first, last);}
	void erase(iterator position) {_tree.erase(position);}
	size_type erase(const key_type &k) {
		iterator ite = find(k);
		
		if (ite == end())
			return 0;
		_tree.erase(ite);
		return 1;
	}

	
	iterator		find (const key_type& k) {return _tree.find(keys_equal, k);}
	const_iterator	find (const key_type& k) const {return _tree.find(keys_equal, k);}
	
	iterator		lower_bound (const key_type& k) {return _tree.find(key_gr_eq, k);}
	const_iterator	lower_bound (const key_type& k) const {return _tree.find(key_gr_eq, k);}
	
	iterator		upper_bound (const key_type& k) {return _tree.find(key_sm, k);}
	const_iterator	upper_bound (const key_type& k) const {return _tree.find(key_sm, k);}
	
	pair<const_iterator,const_iterator>	equal_range (const key_type& k) const {return ft::make_pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k));}
	pair<iterator,iterator>				equal_range (const key_type& k) {return ft::make_pair<iterator, iterator>(lower_bound(k), upper_bound(k));}
	
	void			swap(_Self &x){_tree.swap(x._tree);}
	size_type		count (const key_type& k) const {return _tree.countIf(keys_equal, k);}
	key_compare		key_comp() const{return key_compare();}
	value_compare	value_comp() const{return value_compare();}
};

template <typename T, typename Compare>
void swap(set<T, Compare> &x, set<T, Compare> &y) {x.swap(y);}

template <typename T, typename Compare>
bool operator==(const set<T, Compare> &lhs, const set<T, Compare> &rhs) {
	if (lhs.size() != rhs.size())
		return false;
	return equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <typename T, typename Compare>
bool operator!=(const set<T, Compare> &lhs, const set<T, Compare> &rhs) {return !(lhs == rhs);}

template <typename T, typename Compare>
bool operator<(const set<T, Compare> &lhs, const set<T, Compare> &rhs) {return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());}

template <typename T, typename Compare>
bool operator>=(const set<T, Compare> &lhs, const set<T, Compare> &rhs) {return !(lhs < rhs);}

template <typename T, typename Compare>
bool operator>(const set<T, Compare> &lhs, const set<T, Compare> &rhs) {return rhs < lhs;}

template <typename T, typename Compare>
bool operator<=(const set<T, Compare> &lhs, const set<T, Compare> &rhs) {return !(lhs > rhs);}
} 