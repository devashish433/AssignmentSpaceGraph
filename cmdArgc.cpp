#include<bits/stdc++.h>
#include<exception>
using namespace std;
#define ll long long

int precedence(char operate) {
	if (operate == '+' || operate == '-')
		return 1;
	else if (operate == '*' || operate == '/')
		return 2;
	else if (operate == '^')
		return 3;
	return 0;
}

bool isOperand(char x)
{
	if (x == '+' || x == '-' || x == '*' || x == '/' || x == '(' || x == ')' || x == '^')
		return false;
	return true;
}

vector<string> InfixtoPostfix(string s) {
	string string_without_spaces{};
	for (auto x : s)
		if (x != ' ')
			string_without_spaces += x;
	int length = string_without_spaces.size();

	stack<char> Operators;
	Operators.push('#');


	vector<string> result;
	int i = 0, j = 0;
	while (i < length) {

		if (isOperand(string_without_spaces[i])) {
			string this_number{};
			while (i < string_without_spaces.size() && isOperand(string_without_spaces[i]))
				this_number += string_without_spaces[i++];
			result.push_back(this_number);
		}

		else if (string_without_spaces[i] == '(')
			Operators.push(s[i++]);

		else if (string_without_spaces[i] == ')') {
			while (Operators.top() != '#' && Operators.top() != '(') {
				result.push_back(string(1, Operators.top()));
				Operators.pop();
			}
			if (Operators.top() == '(')
				Operators.pop();
			i++;
		}

		else {
			string temporary{};
			while (Operators.top() != '#' &&
			        precedence(Operators.top()) >= precedence(string_without_spaces[i])) {

				temporary = string(1, Operators.top());
				result.push_back(temporary);
				Operators.pop();
			}
			Operators.push(s[i++]);
		}
	}

	while (Operators.top() != '#') {
		result.push_back((Operators.top() == '^' ? "^" : string(1, Operators.top())));
		Operators.pop();
	}


	return result;
}


long long evaluate(vector<string> &postfix) {
	int i = 0;
	stack<string> values;
	cout << postfix.size() << endl;
	while (i < postfix.size()) {


		if (postfix[i].size() == 1 && !isOperand(postfix[i][0])) {
			ll number1 = stoll(values.top(), nullptr, 10);	// Second operand (for binary opeartor)
			values.pop();
			ll number2 = stoll(values.top(), nullptr, 10);	// First Operand (for binary operator)
			values.pop();
			ll result = 0;

			// Our cases for operands
			switch (postfix[i][0]) {
			case '+':
				result = number2 + number1;
				break;
			case '-':
				result = number2 - number1;
				break;
			case '/':
				result = number2 / number1;
				break;
			case '*':
				result = number2 * number1;
				break;
			case '^':
				result = (ll)pow(number2, number1);
				break;

			default:
				break;
			}
			// Pushing the result back to stackafter performing binary operation.
			values.push(to_string(result));
		}
		else
			values.push(postfix[i]);
		i++;
	}
	return stoll(values.top(), nullptr, 10);
}

// inclusion of the InfixtoPostfix function and evaluate.
int main(int argc, char* argv[]) {
    if(argc>0) {
            for(int i=1; i<argc; ++i) {
	auto postfix = InfixtoPostfix(argv[i]);
	for (auto x : postfix)
		cout << x << " ";
	cout << endl;

	auto result = evaluate(postfix);
	std::cout << argv[i];
	std::cout << "=" << result;
	std::cout << "" << endl;
	std::cout << "" << endl;
    }

    }
    else {
        std::cout << "Insufficient amount";
    }
    }

