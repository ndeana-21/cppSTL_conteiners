#pragma once

namespace ft {
	template <class T, class Container>
	class Stack {
		public:
			Stack();
			~Stack();
		private:
			typedef T			value_type;
			typedef Container	container_type;
			typedef size_t		size_type;
	};
};