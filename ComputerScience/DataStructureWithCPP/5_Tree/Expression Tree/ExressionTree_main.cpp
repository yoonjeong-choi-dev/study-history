#include "ExpressionTree.h"

int main()
{
	char *exp = "12+7*";


	/*char *exp =(char*)malloc(sizeof(char) * 20);
	cout << "input : "; cin >> exp;
*/
	btree_node *etree = Make_exp_tree(exp);

	cout << "Prefix" << endl;
	Show_prefix_exp(etree);
	cout << endl;

	cout << "Infix" << endl;
	Show_infix_exp2(etree);
	cout << endl;

	cout << "Postfix" << endl;
	Show_postfix_exp(etree);
	cout << endl;

	cout << Evaluate_exp_tree(etree) << endl;

	return 0;
}