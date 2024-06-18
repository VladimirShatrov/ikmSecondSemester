#include <iostream>
#include "node.h"

using namespace std;

class list { // класс односвязный линейный список
private:
	pnode _head; // голова списка - ссылка на объект класса node
public:
	void setHead(pnode head) { // сеттеры и геттеры
		this->_head = head;
	}
	pnode getHead() {
		return this->_head;
	}

	list() { // конструктор по умолчанию - создается список первый элемент которого -1
		this->_head = new node();
	}

	list(pnode head) { // создается список голова которого заданный node
		this->_head = head;
	}

	list(int data) { // создается список голова которого хранит data
		this->_head = pnode(data);
	}

	void push_forward(int x) { // добоваления node в начало списка
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
