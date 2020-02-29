#pragma once

class MyArray
{
public:
	MyArray();
	MyArray(int len);
	// �������� ʵ�����
	MyArray(const MyArray& another);

	~MyArray();

	void SetData(int index, int data);
	int GetData(int index);
	int GetLen();
	// ���������� ��ֵ����
	MyArray& operator=(const MyArray& another);
	// ���������� ������
	int& operator[](int index);
private:
	int len;
	int* space;
};
