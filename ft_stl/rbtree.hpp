#pragma once

#include "utils.hpp"
#include "reverse_iterator.hpp"

namespace ft
{
typedef enum
{
	black,
	red
} 		color_type;

template <typename T>
class node
{
public:
	node *parent;
	node *left;
	node *right;
	T data;
	color_type color;

	node(void): parent(NULL), left(NULL), right(NULL), data(), color(black) {}
	node(const T &data, color_type color, node<T> *left = NULL,
		node<T> *right = NULL, node<T> *parent = NULL): parent(parent),
		left(left), right(right), data(data), color(color) {}
	~node(){};
	node(const node<T> &src): parent(src.parent), left(src.left),
		right(src.right), data(src.data), color(src.color) {}
	
	node<T> &operator=(const node<T> &rhs){
		left = rhs.left;
		right = rhs.right;
		parent = rhs.parent;
		data = rhs.data;
		color = rhs.color;
		
		return (*this);
	}
};

template <class T>
class rbtree_iterator
{
public:
	typedef ft::node<T>										node;
	typedef T												value_type;
	typedef typename iterator_traits<T>::size_type			size_type;
	typedef typename iterator_traits<T>::difference_type	difference_type;
	typedef typename iterator_traits<T>::pointer			pointer;
	typedef typename iterator_traits<T>::reference			reference;
	typedef std::bidirectional_iterator_tag					iterator_category;
private:
	node *tNull;
	node *min;
	node *max;
	node *ptr;
public:
	rbtree_iterator(void){}
	rbtree_iterator(node *ptr, node *tNull, node *min, node *max): tNull(tNull),min(min), max(max), ptr(ptr) {}
	rbtree_iterator(const rbtree_iterator &src): tNull(src.tNull), min(src.min), max(src.max), ptr(src.ptr) {}
	~rbtree_iterator() {}
	rbtree_iterator &operator=(const rbtree_iterator &rhs) {
		ptr = rhs.ptr;
		tNull = rhs.tNull;
		min = rhs.min;
		max = rhs.max;
		return *this;
	}

	node *base() const {return ptr;}
	node *maxptr() const {return max;}
	node *minptr() const {return min;}
	node *null() const {return tNull;}

	reference operator*(void) const {return this->ptr->data;}
	pointer operator->(void) const {return &this->ptr->data;}
	bool check_endings(node *e){return (e == tNull);}
	rbtree_iterator &operator++() {
		if (ptr == NULL || check_endings(ptr))
			ptr = min;
		else if (!check_endings(ptr->right)) {
			ptr = ptr->right;
			
			while (!check_endings(ptr) && !check_endings(ptr->left))
				ptr = ptr->left;
		}
		else {
			node *tmp = ptr;
			ptr = ptr->parent;
			
			while (!check_endings(ptr) && tmp == ptr->right) {
				tmp = ptr;
				ptr = ptr->parent;
			}
		}
		return (*this);
	}
	rbtree_iterator &operator--() {
		if (!ptr || check_endings(ptr))
			ptr = max;
		else if (!check_endings(ptr->left)) {
			ptr = ptr->left;
			
			while (!check_endings(ptr) && !check_endings(ptr->right))
				ptr = ptr->right;
		}
		else {
			node *tmp;
			tmp = ptr;
			ptr = ptr->parent;
			
			while (!check_endings(ptr) && tmp == ptr->left) {
				tmp = ptr;
				ptr = ptr->parent;
			}
		}
		return (*this);
	}
	rbtree_iterator operator++(int) {
		rbtree_iterator copy = *this;
		
		++(*this);
		return (copy);
	}
	rbtree_iterator operator--(int) {
		rbtree_iterator copy = *this;
		
		--(*this);
		return (copy);
	}

	bool operator==(const rbtree_iterator &rhs) const {return this->ptr == rhs.ptr;}
	bool operator!=(const rbtree_iterator &rhs) const {return this->ptr != rhs.ptr;}
};

template <class T>
class rbtree_const_iterator {
public:
	typedef ft::node<T>										node;
	typedef const T											value_type;
	typedef typename iterator_traits<T>::size_type			size_type;
	typedef typename iterator_traits<T>::difference_type	difference_type;
	typedef const T*										pointer;
	typedef const T&										reference;
	typedef std::bidirectional_iterator_tag					iterator_category;
private:
	node *tNull;
	node *min;
	node *max;
	node *ptr;
public:
	rbtree_const_iterator(void){}
	rbtree_const_iterator(node *ptr, node *tNull, node *min, node *max):
		tNull(tNull),min(min), max(max), ptr(ptr){}
	rbtree_const_iterator(const rbtree_const_iterator &src):
		tNull(src.tNull), min(src.min), max(src.max), ptr(src.ptr){}
	rbtree_const_iterator(const rbtree_iterator<T> &src):
		tNull(src.null()), min(src.minptr()), max(src.maxptr()), ptr(src.base()) {}
	~rbtree_const_iterator(){}
	
	rbtree_const_iterator &operator=(const rbtree_const_iterator &rhs) {
		ptr = rhs.ptr;
		tNull = rhs.tNull;
		min = rhs.min;
		max = rhs.max;
		
		return *this;
	}

	node *base() const {return ptr;}
	reference operator*(void) const {return this->ptr->data;}
	pointer operator->(void) const {return &this->ptr->data;}
	bool check_endings(node *e) {return (e == tNull);}
	rbtree_const_iterator &operator++() {
		if (ptr == NULL || check_endings(ptr))
			ptr = min;
		else if (!check_endings(ptr->right)) {
			ptr = ptr->right;
			
			while (!check_endings(ptr) && !check_endings(ptr->left))
				ptr = ptr->left;
		}
		else {
			node *tmp;
			tmp = ptr;
			ptr = ptr->parent;
			
			while (!check_endings(ptr) && tmp == ptr->right) {
				tmp = ptr;
				ptr = ptr->parent;
			}
		}
		return (*this);
	}
	
	rbtree_const_iterator &operator--() {
		if (!ptr || check_endings(ptr))
			ptr = max;
		else if (!check_endings(ptr->left)) {
			ptr = ptr->left;
			
			while (!check_endings(ptr) && !check_endings(ptr->right))
				ptr = ptr->right;
		}
		else {
			node *tmp;
			tmp = ptr;
			ptr = ptr->parent;
			
			while (!check_endings(ptr) && tmp == ptr->left) {
				tmp = ptr;
				ptr = ptr->parent;
			}
		}
		return (*this);
	}
	rbtree_const_iterator operator++(int) {
		rbtree_const_iterator copy = *this;
		
		++(*this);
		return (copy);
	}
	rbtree_const_iterator operator--(int) {
		rbtree_const_iterator copy = *this;
		
		--(*this);
		return (copy);
	}

	bool operator==(const rbtree_const_iterator &rhs) const {return this->ptr == rhs.ptr;}
	bool operator!=(const rbtree_const_iterator &rhs) const {return this->ptr != rhs.ptr;}
};

template <class T, class Compare, class Alloc = std::allocator<node<T> > >
class rbtree
{
public:
	typedef node<T> *nodePtr;
	typedef Alloc										allocator_type;
	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::const_reference	const_reference;
	typedef typename allocator_type::pointer			pointer;
	typedef typename allocator_type::const_pointer		const_pointer;
	typedef typename allocator_type::difference_type	difference_type;
	typedef typename allocator_type::size_type			size_type;
	typedef node<T>*									const_nodePtr;
	typedef rbtree_iterator<T>							iterator;
	typedef rbtree_const_iterator<T>					const_iterator;
	typedef ft::reverse_iterator<iterator>				reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
private:
	nodePtr			_root;
	nodePtr			tNull;
	size_type		length;
	Compare			cmp;
	allocator_type	_alloc;
public:
	explicit rbtree(const Compare &comp = Compare(),
		const allocator_type &alloc = allocator_type()) : length(0), cmp(comp), _alloc(alloc) {
		tNull =_alloc.allocate(1);
		_alloc.construct(tNull, node<T>());
		_root = tNull;
	}
	template <class InputIterator>
	rbtree(InputIterator first, InputIterator last, const Compare &comp = Compare(),
		const allocator_type &alloc = allocator_type()): length(0), cmp(comp), _alloc(alloc) {
		tNull =_alloc.allocate(1);
		_alloc.construct(tNull, node<T>());
		_root = tNull;
		insert(first, last);
	}
	rbtree(const rbtree &src): length(0), cmp(src.cmp) {
		tNull =_alloc.allocate(1);
		_alloc.construct(tNull, node<T>());
		_root = tNull;
		copy_branch(src._root, src.tNull);
	}
	~rbtree() {
		clear();
		_alloc.destroy(tNull);
		_alloc.deallocate(tNull, 1);
	}
	rbtree &operator=(const rbtree &rhs) {
		if (this != &rhs) {
			clear();
			copy_branch(rhs._root, rhs.tNull);
		}
		return (*this);
	}

	iterator insert(const T &data) {return insert_data(_root, data);}
	iterator insert(iterator, const T &data){return insert_data(_root, data);}
	template <class InputIterator>
	void insert(InputIterator first, InputIterator last) {
		for (InputIterator it = first; it != last; it++)
			insert(*it);
	}

	void erase(iterator position) {return delete_node(position.base());}
	void erase(iterator first, iterator last) {
		iterator it = first;
		while (it != last)
			erase(it++);
	}
	template <typename Predicate>
	size_type eraseIf(Predicate pred, const T &data) {
		nodePtr node;
		size_type initalLength = size();
		node = this->_root;
		
		while (node && node != tNull) {
			if (pred(node->data, data)) {
				delete_node(node);
				node = this->_root;
			}
			else if (cmp(data, node->data))
				node = node->left;
			else if (cmp(node->data, data))
				node = node->right;
		}
		return initalLength - size();
	}

	void swap(rbtree<T, Compare> &x) {
		nodePtr tmp_root = _root;
		nodePtr tmp_tNull = tNull;
		size_type tmp_length = size();

		_root = x._root;
		tNull = x.tNull;
		length = x.length;

		x._root = tmp_root;
		x.tNull = tmp_tNull;
		x.length = tmp_length;
	}

	template <typename Predicate>
	iterator find(Predicate pred, const T &data) {
		for (iterator it = begin(); it != end(); it++) {
			if (pred(data, *it))
				return it;
		}
		return end();
	}
	template <typename Predicate>
	const_iterator find(Predicate pred, const T &data) const {
		for (const_iterator it = begin(); it != end(); it++)
			if (pred(data, *it))
				return it;
		return end();
	}

	template <typename Predicate>
	size_type countIf(Predicate pred, const T &data) const {return countIfRec(this->_root, pred, data);}

	void clear() {
		while (!empty())
			erase(begin());
	}

	iterator begin() {
		nodePtr min = minimum();
		return iterator(min, this->tNull, min, maximum());
	}
	const_iterator begin() const {
		const_nodePtr min = reinterpret_cast<const_nodePtr>(minimum());
		const_nodePtr max = reinterpret_cast<const_nodePtr>(maximum());
		const_nodePtr tNull = reinterpret_cast<const_nodePtr>(this->tNull);
		return const_iterator(min, tNull, min, max);
	}

	iterator end() {
		nodePtr max = maximum();
		return ++iterator(max, this->tNull, minimum(), max);
	}
	const_iterator end() const {
		const_nodePtr min = reinterpret_cast<const_nodePtr>(minimum());
		const_nodePtr max = reinterpret_cast<const_nodePtr>(maximum());
		const_nodePtr tNull = reinterpret_cast<const_nodePtr>(this->tNull);
		return ++const_iterator(max, tNull, min, max);
	}

	reverse_iterator rbegin() {return reverse_iterator(end());}
	const_reverse_iterator rbegin() const {const_reverse_iterator(end());}

	reverse_iterator rend() {return reverse_iterator(begin());}
	const_reverse_iterator rend() const {return const_reverse_iterator(begin());}
	bool empty() const {return (size() == 0);}
	size_type size() const {return length;}
	size_type max_size() const { return _alloc.max_size();}

	nodePtr get_parent(nodePtr n) {return n == NULL ? NULL : n->parent;}
	nodePtr get_ded(nodePtr n){ return get_parent(get_parent(n));}
	nodePtr getSibling(nodePtr n) {
		nodePtr parent = get_parent(n);
		if (!parent)
			return NULL;
		if (parent->left == n)
			return parent->right;
		return parent->left;
	}
	nodePtr get_uncle(nodePtr n) {return getSibling(get_parent(n));}

	nodePtr minimum() const {return minimum(this->_root);}
	nodePtr maximum() const {return maximum(this->_root);}

	nodePtr minimum(nodePtr n) const {
		if (!n || n == tNull)
			return NULL;
		while (n->left != tNull)
			n = n->left;
		return n;
	}
	nodePtr maximum(nodePtr n) const {
		if (!n || n == tNull)
			return NULL;
		while (n->right != tNull)
			n = n->right;
		return n;
	}

	void left(nodePtr x) {
		nodePtr y = x->right;
		x->right = y->left;
		if (y->left != tNull)
			y->left->parent = x;
		y->parent = get_parent(x);
		if (get_parent(x) == NULL || get_parent(x) == tNull)
			_root = y;
		else if (x == get_parent(x)->left)
			get_parent(x)->left = y;
		else
			get_parent(x)->right = y;
		y->left = x;
		x->parent = y;
	}
	void right(nodePtr x) {
		nodePtr y = x->left;
		x->left = y->right;

		if (y->right != tNull)
			y->right->parent = x;
		y->parent = x->parent;
		if (get_parent(x) == NULL || get_parent(x) == tNull)
			_root = y;
		else if (get_parent(x)->right == x)
			get_parent(x)->right = y;
		else
			get_parent(x)->left = y;
		y->right = x;
		x->parent = y;
	}

	nodePtr make_node(const T &data, nodePtr parent) {
		nodePtr out = _alloc.allocate(1);
		
		++length;
		_alloc.construct(out, node<T>(data, red, tNull, tNull, parent));
		return out;
	}

	iterator insert_data(nodePtr recRoot, const T &data) {
		iterator it = insert_fix(recRoot, data);
		insert_check(it.base());
		recRoot = it.base();
		
		while (get_parent(recRoot) && get_parent(recRoot) != tNull)
			recRoot = get_parent(recRoot);
		this->_root = recRoot;
		return it;
	}
	iterator insert_fix(nodePtr recRoot, const T &data) {
		if (recRoot != NULL && recRoot != tNull) {
			if (cmp(data, recRoot->data)) {
				if (recRoot->left != tNull)
					return insert_fix(recRoot->left, data);
				else {
					recRoot->left = make_node(data, recRoot);
					return iterator(recRoot->left, tNull, minimum(), maximum());
				}
			}
			else if (cmp(recRoot->data, data)) {
				if (recRoot->right != tNull)
					return insert_fix(recRoot->right, data);
				else {
					recRoot->right = make_node(data, recRoot);
					return iterator(recRoot->right, tNull, minimum(), maximum());
				}
			}
			else
				return iterator(recRoot, tNull, minimum(), maximum());
		}
		else
			return iterator(make_node(data, recRoot), tNull, minimum(), maximum());
	}
	void insert_check(nodePtr n) {
		if (get_parent(n) == NULL || get_parent(n) == tNull)
			n->color = black;
		else if (get_parent(n)->color == black)
			return ;
		else if (get_uncle(n) != NULL && get_uncle(n)->color == red) {
			get_parent(n)->color = black;
			get_uncle(n)->color = black;
			get_ded(n)->color = red;
			insert_check(get_ded(n));
		}
		else
			insert_node(n);
	}
	void insert_node(nodePtr n) {
		nodePtr parent = get_parent(n);
		nodePtr grandParent = get_ded(n);
		if (n == parent->right && parent == grandParent->left) {
			left(parent);
			n = n->left;
		}
		else if (n == parent->left && parent == grandParent->right) {
			right(parent);
			n = n->right;
		}
		parent = get_parent(n);
		grandParent = get_ded(n);
		if (n == parent->left)
			right(grandParent);
		else
			left(grandParent);
		parent->color = black;
		grandParent->color = red;
	}

	void replace_node(nodePtr u, nodePtr v) {
		if (u->parent == NULL || u->parent == tNull)
			_root = v;
		else if (u == get_parent(u)->left)
			get_parent(u)->left = v;
		else
			get_parent(u)->right = v;
		v->parent = u->parent;
	}

	void delete_node(nodePtr node) {
		nodePtr x, y = NULL;
		nodePtr removable = node;
		
		if (removable == NULL || removable == tNull)
			return;
		y = removable;
		color_type originalColor = removable->color;
		if (removable->left == tNull) {
			x = removable->right;
			replace_node(removable, removable->right);
		}
		else if (removable->right == tNull) {
			x = removable->left;
			replace_node(removable, removable->left);
		}
		else {
			y = minimum(removable->right);
			originalColor = y->color;
			x = y->right;
			if (get_parent(y) == removable)
				x->parent = y;
			else {
				replace_node(y, y->right);
				y->right = removable->right;
				y->right->parent = y;
			}
			replace_node(removable, y);
			y->left = removable->left;
			y->left->parent = y;
			y->color = removable->color;
		}
		_alloc.destroy(removable);
		_alloc.deallocate(removable, 1);
		length--;
		if (originalColor == black)
			delete_check(x);
	}
	void delete_check(nodePtr x) {
		nodePtr s;
		
		if (x == tNull)
			return ;
		while (x != _root && x->color == black) {
			if (x == x->parent->left) {
				s = x->parent->right;
				if (s->color == red) {
					s->color = black;
					x->parent->color = red;
					left(x->parent);
					s = x->parent->right;
				}
				if (s->left && s->right && s->left->color == black && s->right->color == black) {
					s->color = red;
					x = x->parent;
				}
				else {
					if (s->right && s->right->color == black) {
						s->left->color = black;
						s->color = red;
						right(s);
						s = x->parent->right;
					}
					s->color = x->parent->color;
					x->parent->color = black;
					s->right->color = black;
					left(x->parent);
					x = _root;
				}
			}
			else {
				s = x->parent->left;
				if (s->color == red) {
					s->color = black;
					x->parent->color = red;
					right(x->parent);
					s = x->parent->left;
				}
				if (s->right->color == black && s->right->color == black) {
					s->color = red;
					x = x->parent;
				}
				else {
					if (s->left->color == black) {
						s->right->color = black;
						s->color = red;
						left(s);
						s = x->parent->left;
					}
					s->color = x->parent->color;
					x->parent->color = black;
					s->left->color = black;
					right(x->parent);
					x = _root;
				}
			}
		}
		x->color = black;
	}

	void copy_branch(nodePtr srcRoot, nodePtr srcTnull) {
		if (!srcRoot || srcRoot == srcTnull)
			return;
		copy_branch(srcRoot->left, srcTnull);
		insert(srcRoot->data);
		copy_branch(srcRoot->right, srcTnull);
	}

	template <typename Predicate>
	size_type countIfRec(nodePtr recRoot, Predicate pred, const T &data) const {
		size_type count = 0;
		if (!recRoot || recRoot == tNull)
			return 0;
		count += countIfRec(recRoot->left, pred, data);
		count += countIfRec(recRoot->right, pred, data);
		if (pred(data, recRoot->data))
			count++;
		return count;
	}
};
}
