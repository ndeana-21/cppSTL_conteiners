#pragma once

#include <iostream>
#include <memory>
#include <limits>
#include "VectorIterator.hpp"
#include "Utils.hpp"

namespace ft {
	template <typename T, typename A = std::allocator<T> >
	class Vector {
		public:
			typedef T                                   value_type;
			typedef A                                   allocator_type;
			typedef T&                                  reference;
			typedef const T&                            const_reference;
			typedef T*                                  pointer;
			typedef const T*                            const_pointer;
			typedef ft::VectorIterator<T>               iterator;
			typedef ft::ConstVectorIterator<T>          const_iterator;
			typedef ft::ReverseVectorIterator<T>        reverse_iterator;
			typedef ft::ConstReverseVectorIterator<T>   const_reverse_iterator;
			typedef unsigned long                       size_type;
		private:
			size_type       _length;
			size_type       _size;
			pointer         _container;
			allocator_type  _allocator;
		public:
			explicit Vector(const allocator_type &allocator = allocator_type())
					: _length(0), _size(0), _container(0), _allocator(allocator)
			{
			    _container = _allocator.allocate(0);
			};
			explicit Vector(size_type n, const_reference &value = value_type(),
					const allocator_type &allocator = allocator_type())
					: _length(0), _size(0), _container(0), _allocator(allocator)
			{
				_container = _allocator.allocate(0);
				assign(n, value);
			};
			template <class InputIterator>
			Vector(InputIterator begin, InputIterator end,
					const allocator_type &allocator = allocator_type(),
					typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
					: _length(0), _size(0), _container(0), _allocator(allocator)
			{
				_container = _allocator.allocate(0);
				assign(begin, end);
			};
			Vector(const Vector &other)
					: _length(other._length), _size(other._size), _allocator(other._allocator)
			{
			    if (this != &other) {
					_length = other._length;
					_size = other._size;
					_allocator = other._allocator;
					_container = _allocator.allocate(_size);
					for (size_t i = 0; i < _length; i++)
						_allocator.construct(_container + i, *(other._container + i));
				}
			};

			~Vector(void) {
				if (_container) {
					clear();
					_allocator.deallocate(_container, _size);
				}
			};

			void reserve(size_type n){
				if (n > _size) {
					pointer	tmp;

					tmp  = _allocator.allocate(n);
					for (size_t i = 0; i < _length; i++)
						tmp[i] = _container[i];
					_allocator.deallocate(_container, _size);
					_size = n;
					_container = tmp;
				}
			};

			void push_back(const value_type &value) {
			    if (_size == 0){
					_container = _allocator.allocate(1);
					_length = 1;
					_size = 1;
					_allocator.construct(_container, value);
				}
				else
					insert(end(), value);
			};
			void pop_back(void) {
				if (_length)
					_allocator.destroy(_container + (--_length));
			};

			iterator insert(iterator position, const value_type & val){
				if (_size == 0){
					_size = 1;
					_length = 1;
					_container = _allocator.allocate(1);
					_allocator.construct(_container, val);
					return iterator(_container);
				}
				pointer new_conteiner = 0;
				size_type newPos = position.operator->() - _container;
				size_type new_size;
				if (_length + 1 > _size)
					new_size = _size * 2;
				else
					new_size = _size;
				new_conteiner = _allocator.allocate(new_size);
				size_type i = 0;
				for (; i < newPos; ++i){
					_allocator.construct(new_conteiner + i, *(_container + i));
				}
				_allocator.construct(new_conteiner + newPos, val);
				i++;
				for (; i < _length + 1; ++i){
					_allocator.construct(new_conteiner + i, *(_container + i - 1));
				}
				for (size_type k = 0; k < _length; ++k)
					_allocator.destroy(_container + k);
				_allocator.deallocate(_container, _size);
				_container = new_conteiner;
				_size = new_size;
				_length++;
				return (iterator(_container + newPos));
			}

			void insert(iterator position, size_type n, const value_type &val){
				if (_size == 0){
					_size = n;
					_length = n;
					_container= _allocator.allocate(n);
					for (size_type i = 0; i < n; i++){
						_allocator.construct((_container + i), val);
					}
					return ;
				}
				pointer new_conteiner = 0;
				size_type newPos = position.operator->() - _container;
				size_type new_size;
				if (_length + n > _size)
					new_size = (_length + n) * 2;
				else
					new_size = _size;
				new_conteiner = _allocator.allocate(new_size);
				size_type i = 0;
				for (; i < newPos; i++){
					_allocator.construct(new_conteiner + i, *(_container + i));
				}
				size_type j = 0;
				for (; j < n; ++j, ++i){
					_allocator.construct(new_conteiner + j + newPos, val);
				}
				for (; i < _length + n + 1; ++i){
					_allocator.construct(new_conteiner + i, *(_container + i - n));
				}
				for (size_t k = 0; k < _length; ++k){
					_allocator.destroy(_container + k);
				}
				_allocator.deallocate(_container, _size);
				_container = new_conteiner;
				_size = new_size;
				_length = _length + n;
			}

			template<class InputIterator>
			void insert(iterator position, InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0){
				size_t len = last - first;
				if (_size == 0) {
					_length = len;
					_size = len;
					_container = _allocator.allocate(len);
					for (size_t i = 0; i < len; i++){
						_allocator.construct(_container + i, *first);
						first++;
					}
					return ;
				}
				size_type newPos = position.operator->() - _container;
				size_type new_size;
				if (_length + len > _size) {
					new_size = _size * 2;
				}
				else
					new_size = _size;
				pointer new_conteiner = _allocator.allocate(new_size);
				size_type i = 0;
				for (; i < newPos; i++) {
					_allocator.construct(new_conteiner + i, *(_container + i));
				}
				for (size_t j = i; j <= len; ++j,++i) {
					_allocator.construct(new_conteiner + j, *first);
					first++;
				}
				for (; i < _length + len + 1; ++i) {
					_allocator.construct(new_conteiner + i, *(_container + i - len));
				}
				for (size_t k = 0; k < _length; ++k) {
					_allocator.destroy(_container + k);
				}
				_allocator.deallocate(_container, _size);
				_container = new_conteiner;
				_size = new_size;
				_length = _length + len;
			}

			iterator erase(iterator position) {
				iterator cursor = position;
				while (cursor + 1 != end()) {
					*cursor = *(cursor + 1);
					cursor++;
				}
				_length--;
				return (iterator(position));
			};

			iterator erase(iterator begin, iterator end) {
				while (begin != end) {
					erase(begin);
					end--;
				}
				return (iterator(begin));
			};

			void clear(void) {
			    while (this->_length)
				    pop_back();
			};

			template <class InputIterator>
			void assign(InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
			{
				clear();
                while (first != last) {
                    push_back(*first);
                    first++;
                }
			};

			void assign(size_type n, const value_type &val)
			{
				if (n < 0)
					throw std::length_error("ft error");
				clear();
                while (n > 0) {
                    push_back(val);
                    n--;
                }
			};

			void resize(size_type n, value_type value = value_type()) {
				while (n < _length)
                    pop_back();
                if (n > _size)
                    reserve(n);
                while (n > _length) {
					push_back(value);
				}
			};

			void swap(Vector &other) {
				ft::swap(_container, other._container);
				ft::swap(_size, other._size);
				ft::swap(_length, other._length);
			};

			Vector &operator=(const Vector &other) {
				if (_container != 0)
					_allocator.deallocate(_container, _size);
				_allocator = other._allocator;
				_size = 0;
				_length = 0;
				_container = _allocator.allocate(0);
				assign(other.begin(), other.end());
				return (*this);
			};

			reference operator[](size_type n) {return (_container[n]);};
			const_reference operator[](size_type n) const {return (_container[n]);};

			iterator begin(void) {return (iterator(_container));};
			const_iterator begin(void) const {return (const_iterator(_container));};
			reverse_iterator rbegin(void) {return (reverse_iterator(_container + _length - 1));};
			const_reverse_iterator rbegin(void) const {return (const_reverse_iterator(_container + _length - 1));};

			iterator end(void) {return (iterator(_container + _length));};
			const_iterator end(void) const {return (const_iterator(_container + _length));};
			reverse_iterator rend(void) {return (reverse_iterator(_container - 1));};
			const_reverse_iterator rend(void) const {return (const_reverse_iterator(_container - 1));};

			reference front(void) {return _container[0];};
			const_reference front(void) const {return _container[0];};

			reference back(void) {return _container[_length - 1];};
			const_reference back(void) const {return _container[_length - 1];};

			size_type size(void) const {return (_length);};
			size_type max_size(void) const {return (_allocator.max_size()); };
			size_type capacity(void) const {return (_size);};

			bool empty(void) const {return (_length == 0);};

			reference at(size_type n) {
				if (n >= _length || n < 0)
					throw std::length_error("index out-of-bounds");
				return _container[n];
			};

			const_reference at(size_type n) const {
				if (n >= _length || n < 0)
					throw std::length_error("index out-of-bounds");
				return _container[n];
			};
	};

	template <class T, class Alloc>
	void swap(Vector<T, Alloc> &x, Vector<T, Alloc> &y) {
		x.swap(y);
	};

	template<class T, class Alloc>
	bool operator==(const Vector<T, Alloc> &a, const Vector<T, Alloc> &b) {
	    if (a.size() != b.size())
			return (false);
		unsigned long i = -1;
		while (++i < a.size()) {
			if (a[i] != b[i])
				return (false);
		}
		return (true);
	};

	template <class T, class Alloc>
	bool operator<(const Vector<T,Alloc> &a, const Vector<T,Alloc> &b) {
		size_t		i;
		size_t		n;

		if (a.size() > b.size())
			n = b.size();
		else
			n = a.size();
		i = 0;
		while (i < n) {
			if (a.at(i) != b.at(i))
				return (a.at(i) < b.at(i));
			i++;
		}
		return (a.size() < b.size());
	}

	template <class T, class Alloc>
	bool operator>(const Vector<T,Alloc> &a, const Vector<T,Alloc> &b) {
		return (!(a < b) && !(a == b));
	}

	template <class T, class Alloc>
	bool operator<=(const Vector<T,Alloc> &a, const Vector<T,Alloc> &b) {
		return (a < b || a == b);
	}

	template<class T, class Alloc>
	bool operator!=(const Vector<T, Alloc> &a, const Vector<T, Alloc> &b) {
		return (!(a == b));
	};

	template <class T, class Alloc>
	bool operator>=(const Vector<T,Alloc> &a, const Vector<T,Alloc> &b) {
		return (!(a < b));
	}
};