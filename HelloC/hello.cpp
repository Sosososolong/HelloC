#include <iostream>
#include <iomanip>
#include <fstream>
#include "MyArray.h"
using namespace std;

// 封装Array类
int main_myarray(int argc, char* argv[])
{
	MyArray array1(10);
	
	// 赋值操作 
	for (int i = 0; i < array1.GetLen(); i++)
	{
		// array1.SetData(i, i + 10);
		// 类中完成了"[]"的操作符重载
		array1[i] = i + 10;
	}
	cout << "-----------------打印array1------------------" << endl;
	
	for (int i = 0; i < 10; i++)
	{
		// cout << array1.GetData(i) << " ";
		// 类中完成了"[]"的操作符重载
		cout << array1[i] << " ";
	}
	cout << endl;

	// 调用array2的拷贝构造函数(凡是声明初始化写在一行的都要调用构造函数)
	MyArray array2 = array1;
	cout << "-----------------打印array2------------------" << endl;
	for (int i = 0; i < array2.GetLen(); i++)
	{
		cout << array2.GetData(i) << " ";
	}
	cout << endl;

	// 等号构造符
	MyArray array3; // 调用无参构造方法
	array3 = array1; // 调用等号操作符重载函数

	return 0;
}

// 拷贝文件(包含文件读写的基本操作)
void copy_file() {
	char* file_name = "D:/others.project/clang/zerg/HelloC/HelloC/test_file_io.txt";
	char* target_file_name = "D:/others.project/clang/zerg/HelloC/HelloC/test_file_io_bak.txt";
	ifstream ism(file_name, ios::in); //只读方式打开文件
	ofstream osm(target_file_name, ios::out); //写方式打开文件
	// ofstream osm(target_file_name, ios::out | ios::app); // 追加的方式打开文件,没执行一次程序,都会追加内容
	if (!ism)
	{
		cout << "打开文件失败" << endl;
		return;
	}
	// 读文件
	char ch;
	while (ism.get(ch))
	{
		cout << ch;
		osm.put(ch); // 流写入一个字符
	}
	// 关闭文件
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
// 二进制文件读写-对象序列化
void seri_obj_then_save_to_file() {
	// 文本模式读写就是会对换行操作符进行一个转换(windows平台), 在Linux平台文本模式读写和二进制模式读写没有区别
	Person p1(10, 20), p2(30, 40); // 二进制形式存储在内存中
	// 把p1, p2写进文件
	char* target_file_name = "D:/others.project/clang/zerg/HelloC/HelloC/test_file_io_bak.txt";
	ofstream osm(target_file_name, ios::out | ios::binary); // 二进制模式写
	osm.write((char*)&p1, sizeof(Person)); // 二进制方式写文件
	osm.write((char*)&p2, sizeof(Person)); 
	osm.close();
}
void read_binary_file() {
	char* target_file_name = "D:/others.project/clang/zerg/HelloC/HelloC/test_file_io_bak.txt";
	ifstream ism(target_file_name, ios::in | ios::binary);
	Person p1;
	Person p2;
	ism.read((char*)&p1, sizeof(Person)); // 从文件读取数据
	ism.read((char*)&p2, sizeof(Person));	
	p1.Show(); // Age: 10 Id: 20
	p2.Show(); // Age: 30 Id: 40
}


int main(int argc, char* argv[])
{
	read_binary_file();

	return 0;
}