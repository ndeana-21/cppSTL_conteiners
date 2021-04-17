#pragma once

namespace ft {
	template <class Key, class T, class Compare, class Alloc>
	class Map {
		public:
			Map();
			~Map();
			Map &operator=(const Map &);
		private:
			Key			key_type;
			T			value_type;
			key_compare;
			value_compare;
			allocator_type;
			reference;
			const_reference;
			pointer;
			const_pointer;
			iterator;
			const_iterator;
			reverse_iterator;
			ptrdiff_t	const_reverse_iterator;
			size_t		size_type;
	};
};