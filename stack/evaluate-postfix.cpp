// 3. Evaluate the postfix expression
#include <iostream>
#include <cmath>
#include <string>
#include <stack>

class Postfix
{
private:
    std::stack<char> Stack;
    std::string postfix;
    float value[256];

private:
    bool isOperator(char ch);
    float calculateValues(float operand1, float operand2, char Operator);

public:
    Postfix(const std::string &postfix);
    void getValues();
    float evaluatePostfix();
};

Postfix::Postfix(const std::string &postfix): postfix(postfix) {}

bool Postfix::isOperator(char ch)
{
	return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

void Postfix::getValues()
{
	for (int i = 0; postfix[i] != '\0'; i++)
	{
		const char &currentChar = postfix[i];
		if (!isOperator(currentChar))
		{
			std::cout << "Enter value of " << currentChar << " : ";
			std::cin >> value[currentChar];
		}
	}
}

float Postfix::calculateValues(float operand1, float operand2, char Operator)
{
	if (Operator == '+')
		return (operand1 + operand2);
	if (Operator == '-')
		return (operand1 - operand2);
	if (Operator == '*')
		return (operand1 * operand2);
	if (Operator == '/')
		return (operand1 / operand2);
	if (Operator == '^')
		return pow(operand1, operand2);
}

float Postfix::evaluatePostfix()
{
	for (int i = 0; postfix[i] != '\0'; i++)
	{
		const char &currentChar = postfix[i];
		if (isOperator(currentChar))
		{
			float operand2 = Stack.top();
			Stack.pop();
			float operand1 = Stack.top();
			Stack.pop();
			float result = calculateValues(operand1, operand2, currentChar);
			Stack.push(result);
		}
		else
			Stack.push(value[currentChar]);
	}
	return Stack.top();
}

int main()
{
	std::string postfix_expression = "ab+cd-*";
    Postfix p(postfix_expression);
    std::cout << "Postfix expression : " << postfix_expression << std::endl;
    p.getValues();
	std::cout << "Result : " << p.evaluatePostfix() << std::endl;
	return 0;
}