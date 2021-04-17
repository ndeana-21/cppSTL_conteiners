#pragma once

namespace ft {
	template <class T, class Container>
	class Queue {
		public:
			Queue();
			~Queue();
		private:
			T			value_type;
			Container	container_type;
			size_t		size_type;
	};
};