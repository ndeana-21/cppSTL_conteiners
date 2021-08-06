#pragma once

#include <cstdlib>
#include <iterator>
#include <limits>

#include "utils.hpp"
#include "reverse_iterator.hpp"
#include "rbtree.hpp"

namespace ft{
template < class Key, class T, class Compare = ft::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
class map
{
public:
	typedef Key											key_type;
	typedef T											mapped_type;
	typedef ft::pair<const key_type, mapped_type>		value_type;
	typedef Compare										key_compare;
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
	
	class value_compare
	{
		friend class map;
	protected:
		Compare comp;
		value_compare (Compare c) : comp(c) {} 
	public:
		typedef bool result_type;
		typedef value_type first_argument_type;
		typedef value_type second_argument_type;
		bool operator() (const value_type& x, const value_type& y) const {return comp(x.first, y.first);}
	};

private:
	key_compare comp;
	ft::rbtree<ft::pair<const Key, T>, value_compare> _tree;
	allocator_type _alloc;
	static bool keys_equal(const ft::pair<const Key, T> &p1, const ft::pair<const Key, T> &p2) {Compare comp; return !(comp(p1.first, p2.first) || comp(p2.first, p1.first));}
	static bool key_gr_eq(const ft::pair<const Key, T> &p1, const ft::pair<const Key, T> &p2) {Compare comp; return (!comp(p2.first, p1.first));}
	static bool key_sm(const ft::pair<const Key, T> &p1, const ft::pair<const Key, T> &p2 ){Compare comp; return comp(p1.first, p2.first);}

public:
	explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()):comp(comp), _tree(value_compare(comp)), _alloc(alloc){}
	template <class InputIterator>
	map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()): comp(comp), _tree(first, last, value_compare(comp)), _alloc(alloc){}
	map (const map& x): _tree(x._tree){}
	~map(){}
	
	pair<iterator,bool> insert (const value_type& val) {
		size_type length_before = size();
		iterator it = _tree.insert(val);
		bool elementInserted = size() > length_before;
		return ft::make_pair<iterator, bool>(it, elementInserted);
	}
	iterator insert (iterator position, const value_type& val) {return _tree.insert(position, val);}
	template <class InputIterator>
	void insert (InputIterator first, InputIterator last){ _tree.insert(first, last);}

	void erase (iterator position){ _tree.erase(position);}
	size_type erase (const key_type& k) {return _tree.eraseIf(keys_equal, ft::make_pair<key_type, mapped_type>(k, mapped_type()));}
	void erase (iterator first, iterator last) {_tree.erase(first, last);}
	
	void swap (map& x) {_tree.swap(x._tree);}
	void clear() {_tree.clear();}
	
	bool empty() const {return _tree.empty();}
	size_type size() const {return _tree.size();}
	size_type max_size() const {return _tree.max_size();}
	key_compare key_comp() const {return key_compare();}
	value_compare value_comp() const {return value_compare(Compare());}

	iterator find (const key_type& k) {return _tree.find(keys_equal, ft::make_pair<key_type, mapped_type>(k, mapped_type()));}
	const_iterator find (const key_type& k) const {return _tree.find(keys_equal, ft::make_pair<key_type, mapped_type>(k, mapped_type()));}
	
	size_type count (const key_type& k) const {return _tree.countIf(keys_equal, ft::make_pair<key_type, mapped_type>(k, mapped_type()));}
	
	iterator lower_bound (const key_type& k) {return _tree.find(key_gr_eq, ft::make_pair<key_type, mapped_type>(k, mapped_type()));}
	const_iterator lower_bound (const key_type& k) const {return _tree.find(key_gr_eq, ft::make_pair<key_type, mapped_type>(k, mapped_type()));}
	
	iterator upper_bound (const key_type& k) {return _tree.find(key_sm, ft::make_pair<key_type, mapped_type>(k, mapped_type()));}
	const_iterator upper_bound (const key_type& k) const {return _tree.find(key_sm, ft::make_pair<key_type, mapped_type>(k, mapped_type()));}
	
	pair<const_iterator,const_iterator> equal_range (const key_type& k) const {return ft::make_pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k));}
	pair<iterator,iterator> equal_range (const key_type& k) {return ft::make_pair<iterator, iterator>(lower_bound(k), upper_bound(k));}

	iterator begin() {return _tree.begin();}
	const_iterator begin() const {return _tree.begin();}
	
	iterator end() {return _tree.end();}
	const_iterator end() const {return _tree.end();}
	
	reverse_iterator rbegin() {return _tree.rbegin();}
	const_reverse_iterator rbegin() const {return _tree.rbegin();}
	
	reverse_iterator rend() {return _tree.rend();}
	const_reverse_iterator rend() const {return _tree.rend();}
	
	mapped_type &operator[] (const key_type& k) { return ((insert(ft::make_pair<key_type, mapped_type>(k, mapped_type()))).first).base()->data.second;}
	map& operator= (const map& x){
		_tree.operator=(x._tree);
		return (*this);
	}
};

template <class Key, class T, class Compare, class Alloc>
void	swap(map<Key, T, Compare, Alloc> &x, map<Key, T, Compare, Alloc> &y) {x.swap(y);}

template <class Key, class T, class Compare, class Alloc>
bool	operator==(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) {
	if (lhs.size() != rhs.size())
		return false;
	return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template <class Key, class T, class Compare, class Alloc>
bool	operator!=(const map<Key, T, Compare, Alloc> &lhs,
	const map<Key, T, Compare, Alloc> &rhs) {return !(lhs == rhs);}

template <class Key, class T, class Compare, class Alloc>
bool	operator< (const map<Key, T, Compare, Alloc> &lhs,
	const map<Key, T, Compare, Alloc> &rhs) {return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());}

template <class Key, class T, class Compare, class Alloc>
bool	operator<=(const map<Key, T, Compare, Alloc> &lhs,
	const map<Key, T, Compare, Alloc> &rhs) {return !(rhs < lhs);}

template <class Key, class T, class Compare, class Alloc>
bool	operator> (const map<Key, T, Compare, Alloc> &lhs,
	const map<Key, T, Compare, Alloc> &rhs) {return (rhs < lhs);}

template <class Key, class T, class Compare, class Alloc>
bool	operator>=(const map<Key, T, Compare, Alloc> &lhs,
	const map<Key, T, Compare, Alloc> &rhs) {return !(lhs < rhs);}
}