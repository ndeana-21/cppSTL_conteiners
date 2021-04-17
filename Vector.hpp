#pragma once

namespace ft {
	template <class T, class Alloc>
	class Vector {
		public:
			Vector();
			~Vector();
			Vector &operator=(const Vector &);
			Vector &operator[](size_t n);
		private:
			T			value_type;
			Alloc		allocator_type;
			reference;
			const_reference;
			pointer;
			const_pointer;
			iterator;
			const_iterator;
			reverse_iterator;
			const_reverse_iterator;
			ptrdiff_t	difference_type;
			size_t		size_type;
	};
};