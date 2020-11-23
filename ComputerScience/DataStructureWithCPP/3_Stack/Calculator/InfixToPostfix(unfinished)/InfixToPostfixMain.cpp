#include "InfixToPostfix.h"

int main()
{
	char *exp = "1+2*3";
	/*Conv_to_rpn_exp(exp);
	cout << exp << endl;*/


	char *exp2 = "(1+2)*3";
	Conv_to_rpn_exp(exp2); cout << exp2 << endl;
	char *exp3 = "((1-2)+3)*(5-2)";
	Conv_to_rpn_exp(exp3); cout << exp3 << endl;
	

	

	return 0;
}