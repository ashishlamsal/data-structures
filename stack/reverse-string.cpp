#include <iostream>
#include <stack>
#include <string>

using namespace std;

string getReverse(const string& str) {
	std::stack<char> Stack;
	string reversed;
	
	// push each character to stack till we reach \0
	for (int i = 0; str[i] != '\0'; i++) {
		Stack.push(str[i]);
	}
	
	// keep popping till the stack becomes empty and add 
	// popped element at the end of the reverse string
	while (!Stack.empty())
	{
		reversed += Stack.top();
		Stack.pop();
	} 
	return reversed;
}

int main() {
	string s1 = "Computer";
	cout << "Reverse of " << s1 << " : " << getReverse(s1);
	return 0;
}