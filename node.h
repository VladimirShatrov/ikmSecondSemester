#include <iostream>

using namespace std;

class node;
typedef node* pnode;

class node // ����� - ���� ������������ ��������� ������
{
private:
	int _data; // ���� ������ � ����
	pnode _next; // ���� ������ �� ��������� ����
public:
	void setData(int data) { // ������� � �������
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

	node() { // ����������� �� ��������� - ��������� node �� ��������� -1
		this->_data = -1;
		this->_next = nullptr;
	}

	node(int data, pnode next = nullptr) { // ��������� node � ��������� ������� � ������� �� ���������
		this->_data = data;
		this->_next = next;
	}
};

