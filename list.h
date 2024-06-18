#include <iostream>
#include "node.h"

using namespace std;

class list { // ����� ����������� �������� ������
private:
	pnode _head; // ������ ������ - ������ �� ������ ������ node
public:
	void setHead(pnode head) { // ������� � �������
		this->_head = head;
	}
	pnode getHead() {
		return this->_head;
	}

	list() { // ����������� �� ��������� - ��������� ������ ������ ������� �������� -1
		this->_head = new node();
	}

	list(pnode head) { // ��������� ������ ������ �������� �������� node
		this->_head = head;
	}

	list(int data) { // ��������� ������ ������ �������� ������ data
		this->_head = pnode(data);
	}

	void push_forward(int x) { // ����������� node � ������ ������
		pnode newNode = new node(x);
		newNode->setNext(this->_head);
		this->_head = newNode;
	}

	friend ostream& operator<< (ostream& out, const list& list) {
		pnode p = list._head;
		while (p != nullptr) {
			if (p->getData() != -1)
				out << p->getData() << " ";
			p = p->getNext();
		}
		return out;
	}
	
};
