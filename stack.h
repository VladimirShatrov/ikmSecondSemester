#include <iostream>
#include "list.h"

using namespace std;

class stack: public list // класс стек наследуется от односвязного линейного списка
{
public:
	pnode top() { // получение верхнего элемента стека
		pnode node = this->getHead();
		this->setHead(node->getNext());
		node->setNext(nullptr);
		return node;
	}
};

