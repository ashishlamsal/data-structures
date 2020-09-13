#include <iostream>
#include <stack>
#include <string>
using namespace std;

bool checkParenthesis(const std::string &infix)
{
	int open = 0, close = 0;
	for (int i = 0; infix[i] != '\0'; i++)
	{
		if (infix[i] == '(')
			open++;
		if (infix[i] == ')')
		{
			close++;
			if (close > open)
				return false;
		}
	}
	if (open == close)
		return true;
	return false;
}

bool isValid(char ch)
{
	return (
		(ch >= 'a' && ch <= 'z') ||
		(ch >= 'A' && ch <= 'Z') ||
		ch == '(' || ch == ')' ||
		ch == '+' || ch == '-' ||
		ch == '/' || ch == '*' ||
		ch == '^');
}

bool validate(const std::string &infix)
{
	for (int i = 0; infix[i] != '\0'; i++)
	{
		if (!isValid(infix[i]))
			return false;
	}

	if (!checkParenthesis(infix))
		return false;
	return true;
}

int priorityNumber(char Operator)
{
	if (Operator == '^')
		return 4;
	if (Operator == '*' || Operator == '/')
		return 3;
	if (Operator == '+' || Operator == '-')
		return 2;
	if (Operator == '(')
		return 1;
	return 0;
}

// returns True if priority of currentOperator is higher
bool checkPriority(char currentOperator, char topOperator)
{
	if (priorityNumber(currentOperator) > priorityNumber(topOperator))
		return true;
	else if (priorityNumber(currentOperator) == priorityNumber(topOperator))
	{
		if (currentOperator == '^')
			return true;
	}
	return false;
}

bool isOperand(char ch)
{
	return (
		(ch >= 'a' && ch <= 'z') ||
		(ch >= 'A' && ch <= 'Z'));
}

std::string infix2prefix(const std::string &infix)
{
	std::stack<char> operatorStack;
	std::string postfix;

	// reverse the infix expression
	std::string reversed;
	for (int i = infix.length() - 1; i >= 0; i--) {
		if (infix[i] == '(')
			reversed +=')';
		else if (infix[i] == ')')
			reversed +='(';
		else
			reversed += infix[i];
	}

	// traverse the reversed infix expression
	for (int i =0; reversed[i]!='\0'; i++) 
	{
		const char& currentChar = reversed[i];
		// if character is operand, append to postfix
		if (isOperand(currentChar))
			postfix += currentChar;
		else // if character is operator
		{
			// if operator is '('
			if (currentChar == '(')
			{
				operatorStack.push(currentChar);
				continue;
			}
			// if stack is empty and operator is not ')'
			if (operatorStack.empty())
			{
				if (currentChar != ')')
					operatorStack.push(currentChar);
			}
			else
			{
				// priority of currentOperator is higher than top
				if (checkPriority(currentChar, operatorStack.top()))
					operatorStack.push(currentChar);

				else // priority of currentOperator is lower
				{
					// append top element to postfix till
					// stack is empty or '(' is encountered.
					while (!operatorStack.empty())
					{
						if (operatorStack.top() == '(')
						{
							operatorStack.pop();
							break;
						}
						postfix += operatorStack.top();
						operatorStack.pop();
					}
					// finally push current operator other than ')' to stack
					if (currentChar != ')')
						operatorStack.push(currentChar);
				}
			}
		}
	}
	// transfer remaining items in stack to postfix
	while (!operatorStack.empty())
	{
		postfix += operatorStack.top();
		operatorStack.pop();
	}

	std::string prefix;
	for (int i = postfix.length() - 1; i >= 0; i--)
		prefix += postfix[i];
	return prefix;
}

int main()
{
	std::string infix_expression = "(a^b*(c+(d*e)-f))/g";
	//std::string infix_expression = "a^b^c";

	if (!validate(infix_expression))
	{
		cout << "Invalid expression" << endl;
		return -1;
	}
	cout << "Infix expression: " << infix_expression << endl;

	std::string prefix = infix2prefix(infix_expression);
	cout << "Prefix expression: " << prefix << endl;
	return 0;
}