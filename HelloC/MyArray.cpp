#include "MyArray.h"
#include <iostream>
using namespace std;


MyArray::MyArray()
{
	cout << "�����޲ι��캯��: MyArray()" << endl;
	this->len = 0;
	this->space = NULL;
}

MyArray::MyArray(int len)
{
	if (len <= 0)
	{
		this->len = 0;
		return;
	}
	else {
		this->len = len;
		// ��space���ٿռ�
		this->space = new int[this->len];
		cout << "MyArray::MyArray(int len)..." << endl;
	}	
}

// �������캯�� ִ�� MyArray array2 = array1; ʱ����
MyArray::MyArray(const MyArray& another)
{
	if (another.len > 0)
	{
		this->len = another.len;
		this->space = new int[another.len];
		for (int i = 0; i < this->len; i++)
		{
			this->space[i] = another.space[i];
		}
		cout << "�����˿������캯��" << endl;
	}
	else {
		this->len = 0;
		this->space = NULL;
		return;
	}
}

// ����
MyArray::~MyArray()
{
	if (this->space != NULL)
	{
		delete[]this->space;
		this->space = NULL;
		this->len = 0;
	}
	cout << "MyArray::~MyArray(int len)..." << endl;

}

void MyArray::SetData(int index, int data)
{
	if (this->space != NULL)
	{
		this->space[index] = data;
	}
}

int MyArray::GetData(int index)
{
	return this->space[index];
}

int MyArray::GetLen()
{
	return this->len;
}

// ִ��array3 = array1; ʱ���ô˺���, ���������˵ȺŲ����������������, ��ôarray3��space��ָ��array1��space��ָ��Ŀռ�, array3�ͷź�(�󴴽����ͷ�), array1��space�ͳ���Ұָ��
MyArray& MyArray::operator=(const MyArray& another)
{
	if (this == &another)
	{
		return *this;
	}
	// ���array3����ĳ�Ա�Ѿ���ֵ��, �ȳ�ʼ��, �ͷŵ���Ӧ�Ķѿռ�
	if (this->space != NULL)
	{
		delete[] this->space;
		this->space == NULL;
		this->len = 0;
	}
	if (another.len > 0)
	{
		this->len = another.len;
		this->space = new int[another.len];
		for (int i = 0; i < this->len; i++)
		{
			this->space[i] = another.space[i];
		}
		cout << "�����˵ȺŲ���������" << endl;
	}
	return *this;
}

int& MyArray::operator[](int index)
{
	return this->space[index];
}
