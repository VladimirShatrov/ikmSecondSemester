#include <iostream>
#include "list.h"

using namespace std;

class stack: public list // ����� ���� ����������� �� ������������ ��������� ������
{
public:
	pnode top() { // ��������� �������� �������� �����
		pnode node = this->getHead();
		this->setHead(node->getNext());
		node->setNext(nullptr);
		return node;
	}
};

