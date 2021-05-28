#include "tests.hpp"

template <typename T>
bool operator==(ft::Queue<T> &a, std::queue<T> &b)
{
	if (a.size() != b.size())
		return (false);
	if (a.empty() != b.empty())
		return (false);
	
	ft::Queue<T> testA = a;
	std::queue<T> testB = b;

	for (size_t i = a.size(); i > 0; i--)
	{
		if (testA.front() != testB.front())
			return (false);
		testA.pop();
		testB.pop();
	}
	return (true);
};

static void constructors(void)
{
	print_header("Constructor", BLUE);

	ft::Queue<int> q1;
	std::queue<int> q2;
	ft::Queue<std::string> q3;
	std::queue<std::string> q4;
	check("Queue int", q1 == q2);
	check("Queue string", q3 == q4);
}

static void front_back(void)
{
	print_header("Front / Back / Empty / Size", BLUE);

	ft::Queue<int> q1;
	std::queue<int> q2;

	check("empty() empty", q1.empty() == q2.empty());
	q1.push(0);
	q1.push(1);
	q1.push(2);
	q2.push(0);
	q2.push(1);
	q2.push(2);
	check("push()", q1 == q2);
	check("size()", q1.size() == q2.size());
	check("empty() fill", q1.empty() == q2.empty());
	check("front()", q1.front(), q2.front());
	check("back()", q1.back(), q2.back());
	
	q1.pop();
	q2.pop();
	check("pop()", q1 == q2);
	check("size()", q1.size() == q2.size());
	check("front()", q1.front(), q2.front());
	check("back()", q1.back(), q2.back());
}

static void operators_comp() {
	print_header("Relational operators", BLUE);

	ft::Queue<int> q1;
	ft::Queue<int> q3;
	std::queue<int> q2;
	std::queue<int> q4;

	check("q1 == q2 empty", (q1 == q3), (q2 == q4));
	check("q1 != q2 empty", (q1 != q3), (q2 != q4));
	check("q1 >  q2 empty", (q1 > q3), (q2 > q4));
	check("q1 <  q2 empty", (q1 < q3), (q2 < q4));
	check("q1 >= q2 empty", (q1 >= q3), (q2 >= q4));
	check("q1 <= q2 empty", (q1 <= q3), (q2 <= q4));
	
	q1.push(0);
	q1.push(1);
	q1.push(2);
	q1.push(3);
	q1.push(4);
	q2.push(0);
	q2.push(1);
	q2.push(2);
	q2.push(3);
	q2.push(4);
	check("q1 == q2 after push", (q1 == q3), (q2 == q4));
	check("q1 != q2 after push", (q1 != q3), (q2 != q4));
	check("q1 >  q2 after push", (q1 > q3), (q2 > q4));
	check("q1 <  q2 after push", (q1 < q3), (q2 < q4));
	check("q1 >= q2 after push", (q1 >= q3), (q2 >= q4));
	check("q1 <= q2 after push", (q1 <= q3), (q2 <= q4));
	
	q3 = q1;
	q4 = q2;
	check("q1 == q2 after equal", (q1 == q3), (q2 == q4));
	check("q1 != q2 after equal", (q1 != q3), (q2 != q4));
	check("q1 >  q2 after equal", (q1 > q3), (q2 > q4));
	check("q1 <  q2 after equal", (q1 < q3), (q2 < q4));
	check("q1 >= q2 after equal", (q1 >= q3), (q2 >= q4));
	check("q1 <= q2 after equal", (q1 <= q3), (q2 <= q4));
}

void testQueue(void)
{
	print_header("Queue", GREEN);
	constructors();
	operators_comp();
	front_back();
}