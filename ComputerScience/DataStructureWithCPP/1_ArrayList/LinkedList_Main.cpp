#include <iostream>
#include <cstdlib>

using namespace std;

typedef struct _node
{
	int data;
	struct _node *next;
}Node;


int main()
{
	Node *head = NULL;
	Node *tail = NULL;
	Node *cur = NULL;

	Node *newNode = NULL;
	int read_data;

	//save data
	while (1)
	{
		cout << "�ڿ��� �Է� : ";
		cin >> read_data;
		if (read_data < 1)
			break;

		newNode = (Node*)malloc(sizeof(Node));
		newNode->data = read_data;
		newNode->next = NULL;

		if (head == NULL)
			head = newNode;
		else
			tail->next = newNode;
		tail = newNode;
	}
	cout << endl;

	//print all data
	cout << "�Է¹��� �������� ��ü��� !" << endl;
	if (head = NULL)
	{
		cout << "����� �ڿ����� �����ϴ�" << endl;
	}
	else
	{
		cur = head;
		cout << cur->data << " " << endl;

		while (cur->next != NULL)
		{
			cur = cur->next;
			cout << cur->data << " " << endl;
		}
	}
	cout << endl << endl;

	//delete memory
	if (head == NULL)
	{
		return 0;
	}
	else
	{
		Node *delNode = head;
	}
}