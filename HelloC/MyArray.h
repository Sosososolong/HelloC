#pragma once

class MyArray
{
public:
	MyArray();
	MyArray(int len);
	// 拷贝构造 实现深拷贝
	MyArray(const MyArray& another);

	~MyArray();

	void SetData(int index, int data);
	int GetData(int index);
	int GetLen();
	// 操作符重载 赋值符号
	MyArray& operator=(const MyArray& another);
	// 操作符重载 中括号
	int& operator[](int index);
private:
	int len;
	int* space;
};
