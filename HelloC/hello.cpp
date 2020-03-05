#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <fstream>
#include <set>
#include <map>
#include <functional>
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

#pragma region C语言动态数组的实现
typedef struct Dynamic_Array
{
	int* pAddr;
	int capacity;
	int size;
}Dynamic_Array;

// 动态数组的初始化
Dynamic_Array* Dynamic_Array_Init() {
	Dynamic_Array* arr = NULL;
	arr = (Dynamic_Array*)malloc(sizeof(Dynamic_Array));
	if (arr)
	{
		arr->capacity = 20;
		arr->size = 0;
		arr->pAddr = (int*)malloc(sizeof(int) * arr->capacity);		
	}
	return arr;
}

// 打印
void Print_Array(Dynamic_Array* arr) {
	if (arr == NULL)
	{
		return;
	}

	for (int i = 0; i < arr->size; i++)
	{
		printf("%d ", *(arr->pAddr + i));
	}
	printf("\n");
}

// 释放动态数组的内存
void FreeSpace_Array(Dynamic_Array* arr) {
	if (arr->pAddr != NULL)
	{
		free(arr->pAddr);
	}
	free(arr);
}

// 清空数组
void Clear_Array(Dynamic_Array* arr) {
	if (arr == NULL)
	{
		return;
	}
	arr->size = 0;

}

// 获得动态数组的容量
int Capacity_Array(Dynamic_Array* arr) {
	if (arr == NULL)
	{
		return -1;
	}
	return arr->capacity;
}

// 获得动态数组的当前元素个数
int Count_Array(Dynamic_Array* arr) {
	if (arr == NULL)
	{
		return -1;
	}
	return arr->size;
}

// 获得动态数组某个位置的元素
int GetValue_Array(Dynamic_Array* arr, int pos) {
	if (arr == NULL)
	{
		return -1;
	}
	return arr->pAddr[pos];
}

// 插入
void PushBack_Array(Dynamic_Array* arr, int value) {
	if (arr == NULL)
	{
		return;
	}
	if (arr->size == arr->capacity)
	{
		// 新开辟一块2倍的空间
		int* tmp = (int*)malloc(sizeof(int) * arr->capacity * 2);
		if (tmp == NULL)
		{
			return;
		}
		// 拷贝数据
		memcpy(tmp, arr->pAddr, arr->capacity * sizeof(int));
		// 释放数组就空间, 重新指向新空间
		free(arr->pAddr);
		arr->pAddr = tmp;		
		// 更新容量
		arr->capacity = arr->capacity * 2;
	}
	arr->pAddr[arr->size] = value;
	arr->size++;
}

// 根据位置删除元素
void RemoveByPos_Array(Dynamic_Array* arr, int pos) {
	if (arr == NULL)
	{
		return;
	}
	if (pos < 0 || pos >= arr->size)
	{
		return;
	}
	for (int i = pos; i < arr->size - 1; i++)
	{
		arr->pAddr[i] = arr->pAddr[i + 1];
	}
	arr->size--;
}

// 根据值删除元素
void RemoveByValue_Array(Dynamic_Array* arr, int value) {
	if (arr == NULL)
	{
		return;
	}
	// 找值的位置
	int pos = -1;
	for (int i = 0; i < arr->size; i++)
	{
		if (arr->pAddr[i] == value)
		{
			pos = i;
			break;
		}
	}
	RemoveByPos_Array(arr, pos);
}

// 测试
void test_dynamic_array() {
	Dynamic_Array* arr = Dynamic_Array_Init();
	for (int i = 0; i < 20; i++)
	{
		PushBack_Array(arr, i);
	}
	for (int i = 0; i < 20; i++)
	{
		PushBack_Array(arr, 20 + i);
	}
	RemoveByPos_Array(arr, 2);
	RemoveByValue_Array(arr, 3);
	Print_Array(arr);
	FreeSpace_Array(arr);
}
#pragma endregion

#pragma region C语言单向链表的实现-线性表的链式存储-不连续的内存空间组成
// 链表节点结构体
typedef struct LINKNODE {
	void* data; // 指向任何类型的数据
	struct LINKNODE* next;
}LinkNode;
// 链表结构体,存储一个链表节点作为链表头, 通过这个链表头就可以找到其余所有的元素
typedef struct LINKLIST {
	LinkNode* head;
	int size; // 元素个数
	// 链表每加一个节点都会新开辟一个空间,不需要容量的概念
}LinkList;
// 创建一个打印函数 指针, 用户调用api的时候根据数据类型实现符合此函数指针类型的函数
typedef void(*PRINTLINKNODE)(void*);

// 初始化链表
LinkList* Init_LinkList() {
	LinkList* list = (LinkList*)malloc(sizeof(LinkList));
	if (list != NULL)
	{
		list->size = 0;
		list->head = (LinkNode*)malloc(sizeof(LinkNode));
		if (list->head != NULL)
		{
			list->head->data = NULL;
			list->head->next = NULL;
			return list;
		}
	}		
}

// 指定位置插入
void Insert_LinkList(LinkList* list, int pos, void* data) {
	if (list == NULL || data == NULL )
	{
		return;
	}
	if (pos < 0 || pos > list->size)
	{
		pos = list->size;
	}
	// 创建新的节点
	LinkNode* new_node = (LinkNode*)malloc(sizeof(LinkNode));
	if (new_node == NULL)
	{
		return;
	}
	new_node->data = data;
	new_node->next = NULL;
	if (pos == 0)
	{
		list->head = new_node;
	}
	else {
		// 查找pos的前一个节点
		LinkNode* pre_node = list->head;
		for (int i = 0; i < pos - 1; i++)
		{
			pre_node = pre_node->next;
		}
		// 新节点入链表
		new_node->next = pre_node->next;
		pre_node->next = new_node;
	}
	list->size++;
}

// 删除指定位置的值
void RemoveByPos_LinkList(LinkList* list, int pos) {
	if (list == NULL)
	{
		return;
	}
	if (pos < 0 || pos >= list->size)
	{
		return;
	}
	// 查找pos的前一个节点
	LinkNode* pre_node = list->head;
	for (int i = 0; i < pos - 1; i++)
	{
		pre_node = pre_node->next;
	}
	// 让前一个节点链向下一个节点, 再释放掉当前节点
	LinkNode* current_node = pre_node->next;
	pre_node->next = current_node->next;
	free(current_node);

	list->size--;
}

// 获取链表的长度
int Size_LinkList(LinkList* list) {
	return list->size;
}

// 查找
int Find_LinkList(LinkList* list, void* data) {
	if (list == NULL || data == NULL)
	{
		return -1;
	}
	// 遍历查找
	LinkNode* node = list->head;
	//bool f = node->data == data;
	int i = 0;
	while (node)
	{
		if (node->data == data)
		{
			break;
		}		
		/*f = node->data == data;*/				
		node = node->next;
		if (node == NULL)
		{		
			return -1;
		}
		i++;
	}
	return i;
}

// 返回第一个节点
void* Front_LinkList(LinkList* list) {
	return list->head;
}

// 打印链表节点
void Print_LinkList(LinkList* list, PRINTLINKNODE print) {
	if (list == NULL)
	{
		return;
	}
	LinkNode* node = list->head;
	while (node)
	{
		print(node->data);
		node = node->next;
	}
}

// 释放链表内存
void FreeSpace_LinkList(LinkList* list) {
	if (list == NULL)
	{
		return;
	}
	LinkNode* node = list->head;	
	while (node != NULL)
	{
		LinkNode* tmp_next = node->next;
		free(node);
		node = tmp_next;
	}

	free(list);
}

// 定义打印Person实例的函数
void Print_Person(void* data) {
	Person* p = (Person*)data;
	printf("年龄: %d, 编号: %d\n", p->age, p->id);
}

// 测试
void test_link_list() {
	LinkList* list = Init_LinkList();
	Person p1(18, 1), p2(19, 2), p3(20, 3), p4(22, 4);
	// 数据插入链表
	Insert_LinkList(list, 0, &p1);
	Insert_LinkList(list, 1, &p2);
	Insert_LinkList(list, 2, &p3);
	Insert_LinkList(list, 3, &p4);

	Print_LinkList(list, Print_Person);

	FreeSpace_LinkList(list);
}
#pragma endregion

#pragma region C语言实现企业链表
// 企业链表节点
typedef struct ADLINKNODE{
	struct ADLINKNODE* next;
}AdLinkNode;
// 企业链表
typedef struct ADLINKLIST {
	// head虽然和链表的单位元素类型一致, 但是head不存放数据, head.next为链表的第一个元素
	AdLinkNode head;
	int size;
}AdLinkList;
// 打印函数指针
typedef void(*PRINTADNODE)(AdLinkNode*);
// 比较函数指针
typedef int(*COMPARENODE)(AdLinkNode*, AdLinkNode*);

// 初始化链表;
AdLinkList* Init_AdLinkList() {
	AdLinkList* list = (AdLinkList*)malloc(sizeof(AdLinkList));
	if (list == NULL)
	{
		return NULL;
	}
	list->head.next = NULL;
	list->size = 0;
	return list;
}

// 插入链表
void Insert_AdLinkList(AdLinkList* list, int pos, AdLinkNode* data) {
	if (list == NULL || data == NULL)
	{
		return;
	}
	if (pos<0 || pos > list->size)
	{
		pos = list->size;
	}
	// 查找插入位置的前一个元素(索引是pos-1)
	AdLinkNode* prev_node = &(list->head);
	for (int i = 0; i < pos; i++)
	{
		prev_node = prev_node->next;
	}
	// 插入新节点
	data->next = prev_node->next;
	prev_node->next = data;	

	list->size++;
}

// 删除
void Remove_AdLinkList(AdLinkList* list, int pos) {
	if (list == NULL)
	{
		return;
	}
	if (pos < 0 || pos >= list->size)
	{
		return;
	}
	// 链表head.next指向链表的第一个元素
	AdLinkNode* pCurrent = &(list->head);
	// 循环后, 得到索引是(pos-1)的元素节点
	for (int i = 0; i < pos; i++)
	{
		pCurrent = pCurrent->next;
	}
	// 删除节点
	pCurrent->next = pCurrent->next->next;
	list->size--;
}

// 查找
int Find_AdLinkList(AdLinkList* list, AdLinkNode* data, COMPARENODE compare) {
	if (list == NULL || data == NULL)
	{
		return -1;
	}
	// 从第一个元素开始比较
	AdLinkNode* current_node = list->head.next; 
	int index = 0;
	int f = -1;
	while (current_node)
	{
		if (compare(current_node, data) == 0)
		{
			f = index;
			break;
		}
		current_node = current_node->next;
		index++;
	}
	return f;
}

// 返回链表大小
int Size_AdLinkList(AdLinkList* list) {
	return 0;
}

// 打印
void Print_AdLinkList(AdLinkList* list, PRINTADNODE print) {
	if (list == NULL)
	{
		return;
	}
	AdLinkNode* pCurrent = list->head.next;
	while (pCurrent)
	{
		print(pCurrent);
		pCurrent = pCurrent->next;
	}
}

// 释放
void FreeSpace_AdLinkList(AdLinkList* list) {
	if (list == NULL)
	{
		return;
	}
	free(list);
}

// 测试
typedef struct STUDENT {
	AdLinkNode node;
	char name[64];
	int age;
}Student;

void MyPrint(AdLinkNode* data) {
	Student* s = (Student*)data;
	printf("姓名: %s, 年龄: %d\n", s->name, s->age);
}

int MyCompare(AdLinkNode* node1, AdLinkNode* node2) {
	Student* s1 = (Student*)node1;
	Student* s2 = (Student*)node2;
	if (s1->age == s2->age && strcmp(s1->name, s2->name) == 0)
	{
		return 0;
	}
	return -1;
}

void test_advance_linklist() {
	// 创建链表
	AdLinkList* list = Init_AdLinkList();
	// 创建数据
	Student s1, s2, s3, s4, s5;
	strcpy(s1.name, "zhangsan");
	strcpy(s2.name, "lisi");
	strcpy(s3.name, "wangwu");
	strcpy(s4.name, "zhaoliu");
	strcpy(s5.name, "tianqi");
	s1.age = 10;
	s2.age = 12;
	s3.age = 14;
	s4.age = 16;
	s5.age = 18;
	// 将节点插入链表
	Insert_AdLinkList(list, 0, (AdLinkNode*)&s1);
	Insert_AdLinkList(list, 1, (AdLinkNode*)&s2);
	Insert_AdLinkList(list, 2, (AdLinkNode*)&s3);
	Insert_AdLinkList(list, 3, (AdLinkNode*)&s4);
	Insert_AdLinkList(list, 4, (AdLinkNode*)&s5);
	Print_AdLinkList(list, MyPrint);
	Student finded_student;
	strcpy(finded_student.name, "wangwu");
	finded_student.age = 14;

	int index = Find_AdLinkList(list, (AdLinkNode*)&finded_student, MyCompare);
	printf("pos: %d\n", index);
	FreeSpace_AdLinkList(list);
}
#pragma endregion



int main(int argc, char* argv[])
{
	test_advance_linklist();
	return 0;
}