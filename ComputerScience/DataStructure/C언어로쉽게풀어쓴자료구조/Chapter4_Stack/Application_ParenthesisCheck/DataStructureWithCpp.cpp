#include <iostream>
#include "LinkedStack.h"

using namespace std;

using stack = LinkedStack<char>;
class ParenthesisCheck {

private:
	static stack leftStack;
	static bool type_check(char left, char right) {

		if ((left == '(' && right == ')') ||
			(left == '[' && right == ']') ||
			(left == '{' && right == '}')) {
			return true;
		}

		return false;
	}


public:
	static bool CheckValid(const string& s) {
		// 스택을 비워준다
		while (!leftStack.isEmpty())
			leftStack.pop();


		char lastLeft;
		for (char c : s) {

			switch (c)
			{
			case '(':case'[':case'{':
				// 왼쪽 괄호인 경우 => 스택에 저장
				leftStack.push(c);
				break;
			case ')':case'}':case']':
				// 비어 있는 경우 : 괄호 짝이 맞지 않음
				if (leftStack.isEmpty())
					return false;

				lastLeft = leftStack.pop();
				if (!type_check(lastLeft, c))
					return false;
				break;
			default:
				// 괄호가 아닌 경우 pass
				break;
			}

		}

		// 모두 검사하였을 때 스택에는 아무것도 없어야 제대로된 괄호
		return leftStack.isEmpty();
	}

};
stack ParenthesisCheck::leftStack = stack();

int main()
{
	string test1 = "{ A[(i+1)]=0;}";
	string test2 = "{a[(2+10)*u]/3]";

	cout << test1 + " : " << ParenthesisCheck::CheckValid(test1) << endl;
	cout << test2 + " : " << ParenthesisCheck::CheckValid(test2) << endl;

	return 0;
}
