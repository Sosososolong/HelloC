#include "MyArray.h"
#include <iostream>
using namespace std;


MyArray::MyArray()
{
	cout << "调用无参构造函数: MyArray()" << endl;
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
		// 给space开辟空间
		this->space = new int[this->len];
		cout << "MyArray::MyArray(int len)..." << endl;
	}	
}

// 拷贝构造函数 执行 MyArray array2 = array1; 时调用
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
		cout << "调用了拷贝构造函数" << endl;
	}
	else {
		this->len = 0;
		this->space = NULL;
		return;
	}
}

// 析构
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

// 执行array3 = array1; 时调用此函数, 如果不定义此等号操作符重载深拷贝对象, 那么array3的space将指向array1的space所指向的空间, array3释放后(后创建先释放), array1的space就成了野指针
MyArray& MyArray::operator=(const MyArray& another)
{
	if (this == &another)
	{
		return *this;
	}
	// 如果array3对象的成员已经有值了, 先初始化, 释放掉对应的堆空间
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
		cout << "调用了等号操作符重载" << endl;
	}
	return *this;
}

int& MyArray::operator[](int index)
{
	return this->space[index];
}
