#include <iostream>
#include <iomanip>
#include <fstream>
#include "MyArray.h"
using namespace std;

// ��װArray��
int main_myarray(int argc, char* argv[])
{
	MyArray array1(10);
	
	// ��ֵ���� 
	for (int i = 0; i < array1.GetLen(); i++)
	{
		// array1.SetData(i, i + 10);
		// ���������"[]"�Ĳ���������
		array1[i] = i + 10;
	}
	cout << "-----------------��ӡarray1------------------" << endl;
	
	for (int i = 0; i < 10; i++)
	{
		// cout << array1.GetData(i) << " ";
		// ���������"[]"�Ĳ���������
		cout << array1[i] << " ";
	}
	cout << endl;

	// ����array2�Ŀ������캯��(����������ʼ��д��һ�еĶ�Ҫ���ù��캯��)
	MyArray array2 = array1;
	cout << "-----------------��ӡarray2------------------" << endl;
	for (int i = 0; i < array2.GetLen(); i++)
	{
		cout << array2.GetData(i) << " ";
	}
	cout << endl;

	// �ȺŹ����
	MyArray array3; // �����޲ι��췽��
	array3 = array1; // ���õȺŲ��������غ���

	return 0;
}

// �����ļ�(�����ļ���д�Ļ�������)
void copy_file() {
	char* file_name = "D:/others.project/clang/zerg/HelloC/HelloC/test_file_io.txt";
	char* target_file_name = "D:/others.project/clang/zerg/HelloC/HelloC/test_file_io_bak.txt";
	ifstream ism(file_name, ios::in); //ֻ����ʽ���ļ�
	ofstream osm(target_file_name, ios::out); //д��ʽ���ļ�
	// ofstream osm(target_file_name, ios::out | ios::app); // ׷�ӵķ�ʽ���ļ�,ûִ��һ�γ���,����׷������
	if (!ism)
	{
		cout << "���ļ�ʧ��" << endl;
		return;
	}
	// ���ļ�
	char ch;
	while (ism.get(ch))
	{
		cout << ch;
		osm.put(ch); // ��д��һ���ַ�
	}
	// �ر��ļ�
	ism.close();
	osm.close();
}

class Person {
public:
	Person() {}
	Person(int age, int id) :age(age), id(id) {}
	void Show() {
		cout << "Age: " << this->age << " Id: " << this->id << endl;
	}
public:
	int age;
	int id;
};
// �������ļ���д-�������л�
void seri_obj_then_save_to_file() {
	// �ı�ģʽ��д���ǻ�Ի��в���������һ��ת��(windowsƽ̨), ��Linuxƽ̨�ı�ģʽ��д�Ͷ�����ģʽ��дû������
	Person p1(10, 20), p2(30, 40); // ��������ʽ�洢���ڴ���
	// ��p1, p2д���ļ�
	char* target_file_name = "D:/others.project/clang/zerg/HelloC/HelloC/test_file_io_bak.txt";
	ofstream osm(target_file_name, ios::out | ios::binary); // ������ģʽд
	osm.write((char*)&p1, sizeof(Person)); // �����Ʒ�ʽд�ļ�
	osm.write((char*)&p2, sizeof(Person)); 
	osm.close();
}
void read_binary_file() {
	char* target_file_name = "D:/others.project/clang/zerg/HelloC/HelloC/test_file_io_bak.txt";
	ifstream ism(target_file_name, ios::in | ios::binary);
	Person p1;
	Person p2;
	ism.read((char*)&p1, sizeof(Person)); // ���ļ���ȡ����
	ism.read((char*)&p2, sizeof(Person));	
	p1.Show(); // Age: 10 Id: 20
	p2.Show(); // Age: 30 Id: 40
}


int main(int argc, char* argv[])
{
	read_binary_file();

	return 0;
}