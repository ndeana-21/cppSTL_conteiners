#pragma once

#include <memory>
#include <limits>

namespace ft {
	template <class T, class Alloc=std::allocator<T>>
	class List {
		public:
			typedef T			value_type;
			typedef Alloc		allocator_type;
			typedef T			&reference;
			typedef const T		&const_reference;
			typedef pointer;
			typedef const_pointer;
			typedef iterator;
			typedef const_iterator;
			typedef reverse_iterator;
			typedef const_reverse_iterator;
			typedef ptrdiff_t	difference_type;
			typedef size_t		size_type;
			
			List();
			~List();
			List &operator=(const List &);
		private:
	};
};

//ITERATOR:
// begin
// end
// rbegin
// rend

// empty
// size
// max_size

// front
// back

// assign
// push_front
// pop_front
// push_back
// pop_back
// insert
// erase
// swap
// resize
// clear

// splice
// remove
// remove_if
// unique
// merge
// sort
// reverse

//get_allocator
