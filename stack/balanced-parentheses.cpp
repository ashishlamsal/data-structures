#include <iostream>
#include <string>
#include <stack>

class Expression
{
private:
	std::string input;
	std::stack<char> m_stack;
public:
	Expression(const std::string&);
	bool isBalanced();
};

Expression::Expression(const std::string& input) :input(input) {}

bool Expression::isBalanced() {
	// iterate over the input expression
	for (std::string::iterator ch = input.begin(); ch != input.end(); ch++) {
		if (*ch == '(' || *ch == '<' || *ch == '{' || *ch == '[')
			m_stack.push(*ch);

		if (*ch == ')' || *ch == '>' || *ch == '}' || *ch == ']') {
			if (m_stack.empty())
				return false;
			char top = m_stack.top();
			if (
				(*ch == ')' && top != '(') ||
				(*ch == '>' && top != '<') ||
				(*ch == '}' && top != '{') ||
				(*ch == ']' && top != '[')
			)
				return false;
			m_stack.pop();
		}
	}
	// check if stack is empty at the end of iteration
	if (m_stack.empty())
		return true;
}

int main() {
	std::string expression = "([a])+b";
	Expression e1(expression);

	if (e1.isBalanced())
		std::cout << expression << " is balanced." << std::endl;
	else
		std::cout << expression << " is not balanced." << std::endl;
	return 0;
}