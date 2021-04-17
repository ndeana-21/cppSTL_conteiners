#pragma once

#include <memory>
#include <limits>

namespace ft {
	template <class T>
	class ListIterator {
		public:
			typedef iterator;
			typedef const_iterator;
			typedef reverse_iterator;
			typedef const_reverse_iterator;
			
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
