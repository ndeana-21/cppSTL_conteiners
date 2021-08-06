#include "tests.hpp"

static void Constructors(void)
{
	print_header("Constructor", BLUE);
	ft::stack<int> q1;
	std::stack<int> q2;
	ft::stack<std::string> q3;
	std::stack<std::string> q4;
	check("stack int", q1 == q2);
	check("stack string", q3 == q4);
}

static void front_back(void)
{
	print_header("Front / Back / Push / Pop", BLUE);
	ft::stack<int> q1;
	std::stack<int> q2;
	
	q1.push(0);
	q1.push(1);
	q1.push(2);
	q2.push(0);
	q2.push(1);
	q2.push(2);
	check("size()", q1.size() == q2.size());
	check("empty()", q1.empty() == q2.empty());
	check("top()", q1.top(), q2.top());
	q1.pop();
	q2.pop();
	check("size()", q1.size() == q2.size());
	check("top()", q1.top(), q2.top());
}

static void relational_operators() {
	print_header("Relational operators", BLUE);

	ft::stack<int> q1;
	std::stack<int> q2;
	ft::stack<int> q3;
	std::stack<int> q4;

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

void testStack(void)
{
	print_header("stack", GREEN);
	Constructors();
	relational_operators();
	front_back();
}