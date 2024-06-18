#include <iostream>

using namespace std;

class node;
typedef node* pnode;

class node // класс - узел односвязного линейного списка
{
private:
	int _data; // поле данных в узле
	pnode _next; // поле ссылки на следующий узел
public:
	void setData(int data) { // сеттеры и геттеры
		this->_data = data;
	}
	void setNext(pnode next) {
		this->_next = next;
	}
	int getData() {
		return this->_data;
	}
	pnode getNext() {
		return this->_next;
	}

	node() { // конструктор по умолчанию - создается node со значением -1
		this->_data = -1;
		this->_next = nullptr;
	}

	node(int data, pnode next = nullptr) { // создается node с заданными данными и ссылкой на следующий
		this->_data = data;
		this->_next = next;
	}
};

