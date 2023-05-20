#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <limits>

#include "20_List.cpp"

using namespace std;

int input() {  //ввод с консоли, если не выход 
	long long input;
	while (1) {
		cin >> input;
		if (cin.fail() || cin.peek() != '\n' || abs(input) > std::numeric_limits<int>::max()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else {
			break;
		}
	}
	return int(input);
}class Strings {

public:
	string s1(string s0) {
		string out = "";
		string ERR = "";
		if (s0.size() == 0) {
			return ERR;
		}
		if (!isspace(s0[0])) {
			if (isdigit(s0[0])) {
				if (s0.size() > 1 && (s0[1] == '+' || s0[1] == '-' || s0[1] == '*' || s0[1] == '/')) {
					return ERR;
				}
				out += s0[0];
			}
			else {
				return ERR;
			}
		}
		if (s0.size() == 1) {
			return out;
		}
		else {
			for (int i = 1; i < s0.size(); i++) {
				if (isdigit(s0[i]) || s0[i] == '+' || s0[i] == '-' || s0[i] == '*' || s0[i] == '/') {
					out += s0[i];
					if (isdigit(s0[i]) && i < s0.size() - 1 && (s0[i + 1] == '+' || s0[i + 1] == '-' || s0[i + 1] == '*' || s0[i + 1] == '/')) {
						out += ' ';
					}
					if ((s0[i] == '+' || s0[i] == '-' || s0[i] == '*' || s0[i] == '/') && i < s0.size() - 1 && (isdigit(s0[i + 1]) || s0[i + 1] == '+' || s0[i + 1] == '-' || s0[i + 1] == '*' || s0[i + 1] == '/')) {
						out += ' ';
					}
				}
				else if (isspace(s0[i])) {
					if (isdigit(s0[i - 1]) || s0[i - 1] == '+' || s0[i - 1] == '-' || s0[i - 1] == '*' || s0[i - 1] == '/') {
						out += ' ';
					}
				}
				else {
					return ERR;
				}
			}
			if (out.size() == 0) {
				return ERR;
			}
			if (out[out.size() - 1] == ' ') {
				out.erase(out.size() - 1);
			}
			return out;
		}
	}
};
class Operations {

public:
	double res;
	int ErrorCode;

	Operations() {
		this->res = 0;
		this->ErrorCode = 0;
	}

	void MakeOp(double a, double b, char oper) {
		switch (oper) {
		case '+':
			if ((b > 0 && a > std::numeric_limits<int>::max() - b) || (b < 0 && a < std::numeric_limits<int>::min() - b)) {
				this->ErrorCode = 1;
			}
			else {
				this->res = a + b;  //sum
			}
			break;
		case '-':
			if ((b < 0 && a > std::numeric_limits<int>::max() + b) || (b > 0 && a < std::numeric_limits<int>::min() + b)) {
				this->ErrorCode = 1;
			}
			else {
				this->res = a - b;  //subtraction
			}
			break;
		case '*':
			if (a == 0 || b == 0) {
				this->res = 0;
			}
			else if ((b > 0) && ((a > std::numeric_limits<int>::max() / b) || (a < std::numeric_limits<int>::min() / b))) {
				this->ErrorCode = 1;
			}
			else if ((b < 0) && ((a < std::numeric_limits<int>::max() / b) || (a > std::numeric_limits<int>::min() / b))) {
				this->ErrorCode = 1;
			}
			else {
				this->res = a * b;   //multiplication
			}
			break;
		case '/':
			if (b == 0) {
				this->ErrorCode = 2;
			}
			else if ((b > 0) && ((a > std::numeric_limits<int>::max() * b) || (a < std::numeric_limits<int>::min() * b))) {
				this->ErrorCode = 1;
			}
			else if ((b < 0) && ((a < std::numeric_limits<int>::max() * b) || (a > std::numeric_limits<int>::min() * b))) {
				this->ErrorCode = 1;
			}
			else {
				this->res = a / b;  //division
			}
			break;
		}
	}
	void Clear() {
		this->res = 0;
		this->ErrorCode = 0;
	}
};

int main() {
	20_List Stack;

	Operations Op;
	Strings Q;
	string expr;

	int inp;
	double num1, num2, num = 0;
	bool flag = true;
	bool err = false;

	cout << "Enter the operation!" << endl;
	cout << "1) Count the expression" << endl;
	cout << "2) Exit" << endl;

	while (1) {
		inp = input();
		switch (inp) {
		case 1:
			Stack.DeleteList();
			Op.Clear();
			err = false;
			num = 0;
			cout << "Enter the expression:" << endl;
			cin.ignore();
			getline(cin, expr);
			expr = Q.s1(expr);
			if (expr.size() == 0) {
				cout << "Incorrect expression!" << endl;
				break;
			}
			cout << "You entered: " << expr << endl;
			for (int j = 0; j < expr.size(); j++) {
				if (isdigit(expr[j])) {
					if (num <= std::numeric_limits<int>::max() / 10) {
						num *= 10;
					}
					else {
						cout << "Overflow!" << endl;
						err = true;
						break;
					}
					if (num <= std::numeric_limits<int>::max() - (expr[j] - '0')) {
						num += (expr[j] - '0');
					}
					else {
						cout << "Over flow!" << endl;
						err = true;
						break;
					}
					flag = true;
					if (j == expr.size() - 1) {
						Stack.AddEnd(num, Stack.HeadNode);
						num = 0;
					}
				}
				else if ((expr[j] == '+') || (expr[j] == '-') || (expr[j] == '*') || (expr[j] == '/')) {
					if (Stack.IsEmpty()) {
						cout << "Incorrect expression!" << endl;
						err = true;
						break;
					}
					else {
						num2 = Stack.FindPosition(Stack.ListSize() - 1);
						Stack.DeletePosition(Stack.ListSize() - 1, Stack.HeadNode);
					}
					if (Stack.IsEmpty()) {
						cout << "Incorrect expression!" << endl;
						err = true;
						break;
					}
					else {
						num1 = Stack.FindPosition(Stack.ListSize() - 1);
						Stack.DeletePosition(Stack.ListSize() - 1, Stack.HeadNode);
					}
					Op.MakeOp(num1, num2, expr[j]);
					if (Op.ErrorCode == 0) {
						Stack.AddEnd(Op.res, Stack.HeadNode);
						flag = false;
						Op.Clear();
					}
					else if (Op.ErrorCode == 1) {
						cout << "Over flow!" << endl;
						err = true;
						Op.Clear();
						break;
					}
					else {
						cout << "Unable to divide by zero!" << endl;
						err = true;
						Op.Clear();
						break;
					}
				}
				else {
					if (flag) {
						Stack.AddEnd(num, Stack.HeadNode);
						num = 0;
					}
				}
			}
			if (err) {
				break;
			}
			if (Stack.ListSize() != 1) {
				cout << "The expression is incorrect!" << endl;
				break;
			}
			if (Stack.FindPosition(0) == static_cast<int>(Stack.FindPosition(0))) {
				cout << "Answer is: " << fixed << static_cast<int>(Stack.FindPosition(0)) << endl;
			}
			else {
				cout << "Answer is: " << defaultfloat << Stack.FindPosition(0) << endl;
			}
			break;
		case 2:
			return 0;
		default:
			cout << "Enter another command!" << endl;
			break;
		}
	}
	return 0;
}
