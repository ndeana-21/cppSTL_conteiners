#pragma once

#include <cstdlib>

#include "utils.hpp"
#include "vector_iterator.hpp"
#include "reverse_iterator.hpp"

namespace ft{
template<class T, class Alloc = std::allocator<T> > 
class vector
{
public:
	typedef T											value_type;
	typedef Alloc										allocator_type;
	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::const_reference	const_reference;
	typedef typename allocator_type::pointer			pointer;
	typedef typename allocator_type::const_pointer		const_pointer;
	typedef typename allocator_type::difference_type	difference_type;
	typedef typename allocator_type::size_type			size_type;
	typedef ft::vector_iterator<T>						iterator;
	typedef ft::vector_iterator<const T>				const_iterator;
	typedef ft::reverse_iterator<iterator>				reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
private:
	pointer			_ptr;
	allocator_type 	_alloc;
	size_type		_size;
	size_type		_capacity;
public:
	explicit vector(allocator_type const & _alloc = allocator_type()):  _ptr(0),_alloc(_alloc), _size(0), _capacity(0) {}
	vector(size_type n, value_type const & val = value_type(),
			allocator_type const & alloc = allocator_type()):_alloc(alloc),_size(n),_capacity(n) {
		_ptr = _alloc.allocate(n);	
		
		for (size_type i = 0; i < n; i++)
			_alloc.construct(_ptr + i, val);
	}
	template <class InputIt>
	vector (InputIt first, InputIt last,
			allocator_type const & alloc = allocator_type(),
			typename ft::enable_if<!ft::is_integral<InputIt>::value>::type* = 0) : _alloc(alloc) {
		_size = 0;
		
		for (InputIt i = first; i != last; i++)
			_size++;
		_capacity = _size;
		_ptr = _alloc.allocate(_capacity);
		for (size_type i = 0; i < _size; i++, first++)
			_alloc.construct(_ptr + i, *first);
	}
	vector(const vector & vec) : _ptr(vec._ptr), _alloc(vec._alloc),
									_size(vec._size), _capacity(vec._capacity) {
		_ptr = _alloc.allocate(_capacity);
		pointer first = (pointer)vec.begin().operator->();
		
		for (size_type i = 0; i < _size; i++, first++)
			_alloc.construct(_ptr + i, *first);
	}
	~vector() {
		for (size_type i = 0; i < _size; i++)
			_alloc.destroy(_ptr + i);
		_alloc.deallocate(_ptr, _capacity);
	}
	
	iterator erase (iterator first, iterator last) {
		if (last <= first)
			return last;
		difference_type dist = last - first;
		for (iterator i = first; i != last; i++)
			_alloc.destroy(i.operator->());
		for (iterator i = last; i != end(); i++ ) {
			_alloc.construct((i - dist).operator->(), *i);  
			_alloc.destroy(i.operator->());					
		}
		_size -= dist;
		return first;
	}
	iterator erase (iterator position) {return (erase(position, position + 1));}
	const_iterator erase (iterator position) const {return (erase(position, position + 1));}

	void reserve (size_type n) {
		if (n <= _capacity || n == 0)
			return;
		pointer _ptr = _alloc.allocate(n);
		for (size_type i = 0; i < _size; i++) {
			_alloc.construct(_ptr + i, this->_ptr[i]); 
		}
		this->~ vector();
		this->_ptr = _ptr;
		_capacity = n;
	}
	
	void	assign(size_type n, const value_type &val) {
		if (n < 0)
			throw std::length_error("ft error");
		clear();
		while (n > 0) {
			push_back(val);
			n--;
		}
	}
	template <class InputIterator>
	void assign (InputIterator first, InputIterator last,
			typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0) {
		
		clear();
		while (first != last) {
			push_back(*first);
			first++;
		}
	}
	
	iterator insert (iterator position, const value_type& val) {
		difference_type move = position - begin();
		size_type n = 1;
		
		if (_capacity < _size + n)
			reserve(std::max(_size * 2, _size + n));
		position = begin() + move;
		for (iterator ptr = end() + n - 1; ptr >= position + n; ptr--) {
			_alloc.construct(ptr.base(), *(ptr - n));
			_alloc.destroy(ptr.base() - n);
		}
		for (iterator ptr = position + n - 1; ptr >= position; --ptr)
			_alloc.construct(ptr.base(), val);
		_size += n;
		return position;
	}
	void insert (iterator position, size_type n, const value_type& val) {
		difference_type move = position - begin();
		if (n == 0 || move < 0)
			return;
		if (_capacity < _size + n)
			reserve(std::max(_size * 2, _size + n));
		position = begin() + move;
		for (iterator ptr = end() + n - 1; ptr >= position + n; ptr--) {
			_alloc.construct(ptr.base(), *(ptr - n));
			_alloc.destroy(ptr.base() - n);
		}
		for (iterator ptr = position + n - 1; ptr >= position; --ptr)
			_alloc.construct(ptr.base(), val);
		_size += n;
	}
	template <class InputIterator>
	void insert (iterator position, InputIterator f, InputIterator l,
			typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0) {
		vector<T> vec(f, l);
		iterator first = vec.begin();
		iterator last = vec.end();
		difference_type dist = 0;
		difference_type pos = position - begin();
		
		for (iterator i = first; i != last; i++)
			dist++;
		if (_capacity < _size + dist)
			reserve(std::max(_size * 2, _size + dist));
		position = begin() + pos;
		for (iterator ptr = _ptr + dist + _size - 1; ptr >= position + dist; ptr--) {
			_alloc.construct(ptr.base(), *(ptr - dist));
			_alloc.destroy(ptr.base() - dist);
		}
		for (iterator ptr = position ; ptr != position + dist; ptr++, first++)
			_alloc.construct(ptr.base(), *first);
		_size += dist;
	}

	void swap(vector<T> & y) {
		ft::swap(_alloc, y._alloc);
		ft::swap(_ptr, y._ptr);
		ft::swap(_size, y._size);
		ft::swap(_capacity, y._capacity);
	}

	void clear() {
		erase(begin(),end());
		_size = 0;
	}
	void resize (size_type n, value_type val = value_type()) {
		if (n >= _size)
			insert(end(), n - _size,val);
		else
			erase(begin() + n, end());
	}

	vector &operator = (const vector & vec) {
		if (_capacity)
			clear();
		insert(begin(),vec.begin(),vec.end());
		return *this;
	}

	void push_back(const value_type & value) {insert(end(), value);}
	void pop_back() {erase(end() - 1);}

	size_type capacity() const { return _capacity;}
	
	bool empty() const { return _size == 0;}
	
	reference operator[](size_type position) {return *(_ptr + position);}
	const_reference operator[](size_type position) const{return *(_ptr + position);}
	
	reference at(size_type position) {
		if (position < 0 || position >= size())
			throw std::out_of_range("Index is out of range");
		return *(_ptr + position);
	}
	const_reference at(size_type position) const{
		if (position < 0 || position >= size())
			throw std::out_of_range("Index is out of range");
		return *(_ptr + position);
	}
	reference front() {return *begin();}
	const_reference front() const {return *begin();}
	reference back(){return *(end() - 1);}
	const_reference back() const {return *(end() - 1);}

	iterator begin(){ return _ptr;}
	const_iterator begin() const { return _ptr;}
	
	iterator end(){ return begin() + _size;}
	const_iterator end() const { return begin() + _size;}
	
	reverse_iterator rbegin(){ return reverse_iterator(end());}
	const_reverse_iterator rbegin() const { return reverse_iterator(end());}
	
	reverse_iterator rend(){ return reverse_iterator(begin());}
	const_reverse_iterator rend() const { return reverse_iterator(begin());}
	
	size_type size() const { return _size;}
	size_type max_size() const { return _alloc.max_size();}
};

template <typename T>
void swap (ft::vector<T> & x, ft::vector<T>& y) {x.swap(y);}

template <class T, class Alloc>
bool operator== (const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs) {
	if (lhs.size() != rhs.size())
		return (false);
	typename ft::vector<T>::const_iterator first1 = lhs.begin();
	typename ft::vector<T>::const_iterator first2 = rhs.begin();
	while (first1 != lhs.end()) {
		if (first2 == rhs.end() || *first1 != *first2)
			return (false);
		++first1;
		++first2;
	}
	return (true);
}
template <class T, class Alloc>
bool operator!= (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {return (!(rhs == lhs));}
template <class T, class Alloc>
bool operator< (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));}
template <class T, class Alloc>
bool operator<= (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {return (!(rhs < lhs));}
template <class T, class Alloc>
bool operator>  (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs){return (rhs < lhs);}
template <class T, class Alloc>
bool operator>= (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {return (!(lhs < rhs));}
}
