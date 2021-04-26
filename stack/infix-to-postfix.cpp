#include <iostream>
#include <stack>
#include <string>
using namespace std;

class Expression {
private:
    std::stack<char> operatorStack;
    std::string infix;
    std::string postfix;

private:
    bool checkParenthesis();
    bool isValid(char ch);
    int priorityNumber(char Operator);
    bool checkPriority(char currentOperator, char topOperator);
    bool isOperand(char ch);

public:
    Expression(const std::string &infix);
    bool validate();
    std::string infix2postfix();
};

Expression::Expression(const std::string &infix) : infix(infix) {}

bool Expression::checkParenthesis() {
    int open = 0, close = 0;
    for (int i = 0; infix[i] != '\0'; i++) {
        if (infix[i] == '(')
            open++;
        if (infix[i] == ')') {
            close++;
            if (close > open)
                return false;
        }
    }
    if (open == close)
        return true;
    return false;
}

bool Expression::isValid(char ch) {
    return (
        (ch >= 'a' && ch <= 'z') ||
        (ch >= 'A' && ch <= 'Z') ||
        ch == '(' || ch == ')' ||
        ch == '+' || ch == '-' ||
        ch == '/' || ch == '*' ||
        ch == '^');
}

bool Expression::validate() {
    for (int i = 0; infix[i] != '\0'; i++) {
        if (!isValid(infix[i]))
            return false;
    }
    if (!checkParenthesis())
        return false;
    return true;
}

int Expression::priorityNumber(char Operator) {
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

bool Expression::checkPriority(char currentOperator, char topOperator) {
    // returns True if priority of currentOperator is higher
    if (priorityNumber(currentOperator) > priorityNumber(topOperator))
        return true;
    // return True for right to left associativity of ^ operator
    else if (priorityNumber(currentOperator) == priorityNumber(topOperator)) {
        if (currentOperator == '^')
            return true;
    }
    return false;
}

bool Expression::isOperand(char ch) {
    return (
        (ch >= 'a' && ch <= 'z') ||
        (ch >= 'A' && ch <= 'Z'));
}

std::string Expression::infix2postfix() {
    // traverse the infix expression
    for (int i = 0; infix[i] != '\0'; i++) {
        const char& currentChar = infix[i];

        // if character is operand, append to postfix
        if (isOperand(currentChar))
            postfix += currentChar;

        // if character is operator
        else {
            if (currentChar == ')') {
                // pop the stack till '(' is encountered
                while (operatorStack.top() != '(') {
                    postfix += operatorStack.top();
                    operatorStack.pop();
                }
                // pop the '(' from stack
                operatorStack.pop();
            }
            else if (operatorStack.empty() ||       // stack is empty
                operatorStack.top() == '(' ||       // stacktop is '('
                currentChar == '(') {               // character is '('
                operatorStack.push(currentChar);
            }
            else {
                // priority of currentOperator is higher than top
                if (checkPriority(currentChar, operatorStack.top()))
                    operatorStack.push(currentChar);

                else {
                    // append top element to postfix till
					// stack is empty or '(' is encountered.
                    while (!operatorStack.empty() &&
                        operatorStack.top() != '(' &&
                        !checkPriority(currentChar, operatorStack.top())) {

                        postfix += operatorStack.top();
                        operatorStack.pop();
                    }
                    // finally push current operator to stack
                    operatorStack.push(currentChar);
                }
            }
        }
    }

    // transfer remaining items in stack to postfix
    while (!operatorStack.empty()) {
        postfix += operatorStack.top();
        operatorStack.pop();
    }
    return postfix;
}

int main() {
    // std::string infix_expression = "(a^b*(c+(d*e)-f))/g";
    std::string infix_expression = "k+l-m*n+(o^p)*w/u/v*t+q^j^a";
    Expression e1(infix_expression);
    if (!e1.validate()) {
        cout << "Invalid expression" << endl;
        return -1;
    }
    cout << "Infix expression: " << infix_expression << endl;

    std::string postfix = e1.infix2postfix();
    cout << "Postfix expression: " << postfix << endl;
    return 0;
}