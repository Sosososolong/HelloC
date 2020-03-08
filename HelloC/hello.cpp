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

#pragma region C���Զ�̬�����ʵ��
typedef struct Dynamic_Array
{
	int* pAddr;
	int capacity;
	int size;
}Dynamic_Array;

// ��̬����ĳ�ʼ��
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

// ��ӡ
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

// �ͷŶ�̬������ڴ�
void FreeSpace_Array(Dynamic_Array* arr) {
	if (arr->pAddr != NULL)
	{
		free(arr->pAddr);
	}
	free(arr);
}

// �������
void Clear_Array(Dynamic_Array* arr) {
	if (arr == NULL)
	{
		return;
	}
	arr->size = 0;

}

// ��ö�̬���������
int Capacity_Array(Dynamic_Array* arr) {
	if (arr == NULL)
	{
		return -1;
	}
	return arr->capacity;
}

// ��ö�̬����ĵ�ǰԪ�ظ���
int Count_Array(Dynamic_Array* arr) {
	if (arr == NULL)
	{
		return -1;
	}
	return arr->size;
}

// ��ö�̬����ĳ��λ�õ�Ԫ��
int GetValue_Array(Dynamic_Array* arr, int pos) {
	if (arr == NULL)
	{
		return -1;
	}
	return arr->pAddr[pos];
}

// ����
void PushBack_Array(Dynamic_Array* arr, int value) {
	if (arr == NULL)
	{
		return;
	}
	if (arr->size == arr->capacity)
	{
		// �¿���һ��2���Ŀռ�
		int* tmp = (int*)malloc(sizeof(int) * arr->capacity * 2);
		if (tmp == NULL)
		{
			return;
		}
		// ��������
		memcpy(tmp, arr->pAddr, arr->capacity * sizeof(int));
		// �ͷ�����Ϳռ�, ����ָ���¿ռ�
		free(arr->pAddr);
		arr->pAddr = tmp;		
		// ��������
		arr->capacity = arr->capacity * 2;
	}
	arr->pAddr[arr->size] = value;
	arr->size++;
}

// ����λ��ɾ��Ԫ��
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

// ����ֵɾ��Ԫ��
void RemoveByValue_Array(Dynamic_Array* arr, int value) {
	if (arr == NULL)
	{
		return;
	}
	// ��ֵ��λ��
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

// ����
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

#pragma region C���Ե��������ʵ��-���Ա����ʽ�洢-���������ڴ�ռ����
// ����ڵ�ṹ��
typedef struct LINKNODE {
	void* data; // ָ���κ����͵�����
	struct LINKNODE* next;
}LinkNode;
// ����ṹ��,�洢һ������ڵ���Ϊ����ͷ, ͨ���������ͷ�Ϳ����ҵ��������е�Ԫ��
typedef struct LINKLIST {
	LinkNode* head;
	int size; // Ԫ�ظ���
	// ����ÿ��һ���ڵ㶼���¿���һ���ռ�,����Ҫ�����ĸ���
}LinkList;
// ����һ����ӡ���� ָ��, �û�����api��ʱ�������������ʵ�ַ��ϴ˺���ָ�����͵ĺ���
typedef void(*PRINTLINKNODE)(void*);

// ��ʼ������
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

// ָ��λ�ò���
void Insert_LinkList(LinkList* list, int pos, void* data) {
	if (list == NULL || data == NULL )
	{
		return;
	}
	if (pos < 0 || pos > list->size)
	{
		pos = list->size;
	}
	// �����µĽڵ�
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
		// ����pos��ǰһ���ڵ�
		LinkNode* pre_node = list->head;
		for (int i = 0; i < pos - 1; i++)
		{
			pre_node = pre_node->next;
		}
		// �½ڵ�������
		new_node->next = pre_node->next;
		pre_node->next = new_node;
	}
	list->size++;
}

// ɾ��ָ��λ�õ�ֵ
void RemoveByPos_LinkList(LinkList* list, int pos) {
	if (list == NULL)
	{
		return;
	}
	if (pos < 0 || pos >= list->size)
	{
		return;
	}
	// ����pos��ǰһ���ڵ�
	LinkNode* pre_node = list->head;
	for (int i = 0; i < pos - 1; i++)
	{
		pre_node = pre_node->next;
	}
	// ��ǰһ���ڵ�������һ���ڵ�, ���ͷŵ���ǰ�ڵ�
	LinkNode* current_node = pre_node->next;
	pre_node->next = current_node->next;
	free(current_node);

	list->size--;
}

// ��ȡ����ĳ���
int Size_LinkList(LinkList* list) {
	return list->size;
}

// ����
int Find_LinkList(LinkList* list, void* data) {
	if (list == NULL || data == NULL)
	{
		return -1;
	}
	// ��������
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

// ���ص�һ���ڵ�
void* Front_LinkList(LinkList* list) {
	return list->head;
}

// ��ӡ����ڵ�
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

// �ͷ������ڴ�
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

// �����ӡPersonʵ���ĺ���
void Print_Person(void* data) {
	Person* p = (Person*)data;
	printf("����: %d, ���: %d\n", p->age, p->id);
}

// ����
void test_link_list() {
	LinkList* list = Init_LinkList();
	Person p1(18, 1), p2(19, 2), p3(20, 3), p4(22, 4);
	// ���ݲ�������
	Insert_LinkList(list, 0, &p1);
	Insert_LinkList(list, 1, &p2);
	Insert_LinkList(list, 2, &p3);
	Insert_LinkList(list, 3, &p4);

	Print_LinkList(list, Print_Person);

	FreeSpace_LinkList(list);
}
#pragma endregion

#pragma region C����ʵ����ҵ����
// ��ҵ����ڵ�
typedef struct ADLINKNODE{
	struct ADLINKNODE* next;
}AdLinkNode;
// ��ҵ����
typedef struct ADLINKLIST {
	// head��Ȼ������ĵ�λԪ������һ��, ����head���������, head.nextΪ����ĵ�һ��Ԫ��
	AdLinkNode head;
	int size;
}AdLinkList;
// ��ӡ����ָ��
typedef void(*PRINTADNODE)(AdLinkNode*);
// �ȽϺ���ָ��
typedef int(*COMPARENODE)(AdLinkNode*, AdLinkNode*);

// ��ʼ������;
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

// ��������
void Insert_AdLinkList(AdLinkList* list, int pos, AdLinkNode* data) {
	if (list == NULL || data == NULL)
	{
		return;
	}
	if (pos<0 || pos > list->size)
	{
		pos = list->size;
	}
	// ���Ҳ���λ�õ�ǰһ��Ԫ��(������pos-1)
	AdLinkNode* prev_node = &(list->head);
	for (int i = 0; i < pos; i++)
	{
		prev_node = prev_node->next;
	}
	// �����½ڵ�
	data->next = prev_node->next;
	prev_node->next = data;	

	list->size++;
}

// ɾ��
void Remove_AdLinkList(AdLinkList* list, int pos) {
	if (list == NULL)
	{
		return;
	}
	if (pos < 0 || pos >= list->size)
	{
		return;
	}
	// ����head.nextָ������ĵ�һ��Ԫ��
	AdLinkNode* pCurrent = &(list->head);
	// ѭ����, �õ�������(pos-1)��Ԫ�ؽڵ�
	for (int i = 0; i < pos; i++)
	{
		pCurrent = pCurrent->next;
	}
	// ɾ���ڵ�
	pCurrent->next = pCurrent->next->next;
	list->size--;
}

// ����
int Find_AdLinkList(AdLinkList* list, AdLinkNode* data, COMPARENODE compare) {
	if (list == NULL || data == NULL)
	{
		return -1;
	}
	// �ӵ�һ��Ԫ�ؿ�ʼ�Ƚ�
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

// ���������С
int Size_AdLinkList(AdLinkList* list) {
	return 0;
}

// ��ӡ
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

// �ͷ�
void FreeSpace_AdLinkList(AdLinkList* list) {
	if (list == NULL)
	{
		return;
	}
	free(list);
}

// ����
typedef struct STUDENT {
	AdLinkNode node;
	char name[64];
	int age;
}Student;

void MyPrint(AdLinkNode* data) {
	Student* s = (Student*)data;
	printf("����: %s, ����: %d\n", s->name, s->age);
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
	// ��������
	AdLinkList* list = Init_AdLinkList();
	// ��������
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
	// ���ڵ��������
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

#pragma region C����ʵ��ѭ������-������ҵ����
// ѭ������ڵ�
typedef struct CIRCLELINKNODE {
	struct CIRCLELINKNODE* next;
}CircleLinkNode;

// ѭ������
typedef struct CIRCLELINKLIST {
	// head����������, ��ʼ����ʱ��, headָ���Լ�, head.nextΪ����ĵ�һ��Ԫ�ؽڵ�
	CIRCLELINKNODE head;
	int size;
}CircleLinkList;

// �ȽϺ��� ָ��(�ص�����)
typedef int(*COMPARECIRCLELINKNODE)(CircleLinkNode*, CircleLinkNode*);

// ��ӡ���� ָ��(�ص�����)
typedef void(*PRINTCIRCLELINKNODE)(CircleLinkNode*);

#define CIRCLELINKLIST_TRUE 1
#define CIRCLELINKLIST_FALSE 0

// ��ʼ������
CircleLinkList* Init_CircleLinkList() {
	CircleLinkList* list = (CircleLinkList*)malloc(sizeof(CircleLinkList));
	if (list == NULL)
	{
		return NULL;
	}
	list->head.next = &(list->head);
	list->size = 0;
	return list;
}

// ���뺯��
void Insert_CircleLinkList(CircleLinkList* list, int pos, CircleLinkNode* data) {
	if (list == NULL || data == NULL)
	{
		return;
	}
	if (pos<0 || pos > list->size)
	{
		pos = list->size;
	}
	// ����Ҫ����λ�õ���һ���ڵ�, ����Ϊ(pos-1)�Ľڵ�
	CircleLinkNode* prev_node = &(list->head);
	for (int i = 0; i < pos; i++)
	{
		prev_node = prev_node->next;
	}

	data->next = prev_node->next;
	prev_node->next = data;
	list->size++;
}

// ��õ�һ��Ԫ��
CircleLinkNode* Front_CircleLinkList(CircleLinkList* list) {
	if (list == NULL || list->size <= 0)
	{
		return NULL;
	}
	return list->head.next;
}

// ����λ��ɾ��
void RemoveByPos_CircleLinkList(CircleLinkList* list, int pos) {
	if (list == NULL)
	{
		return;
	}
	if (pos < 0 || pos >= list->size)
	{
		return;
	}
	CircleLinkNode* prev_node = &(list->head);
	for (int i = 0; i < pos; i++)
	{
		prev_node = prev_node->next;
	}
	// ���浱ǰ�ڵ�, �˽ڵ㲻�ǿ�������, ����������ò�Ҫ�ͷŵ�, ���еĽڵ㶼���û�malloc������, ���û�ȥ������
	CircleLinkNode* current_node = prev_node->next;
	prev_node->next = prev_node->next->next;
	/*free(current_node);*/
	list->size--;
}

// ����ֵɾ��
void RemoveByValue_CircleLinkList(CircleLinkList* list, CircleLinkNode* data, COMPARECIRCLELINKNODE compare) {
	if (list == NULL || data == NULL)
	{
		return;
	}
	CircleLinkNode* current_node = list->head.next;
	CircleLinkNode* prev_node = &(list->head);
	while (current_node != &(list->head))
	{		
		if (compare(current_node, data) == CIRCLELINKLIST_TRUE)
		{
			prev_node->next = current_node->next;
			list->size--;
			break;
		}
		prev_node = current_node;
		current_node = current_node->next;
	}
}

// ��ȡ����ĳ���
int Size_CircleLinkList(CircleLinkList* list) {
	if (list == NULL)
	{
		return -1;
	}
	return list->size;
}

// �ж��Ƿ�Ϊ��
int IsEmpty_CircleLinkList(CircleLinkList* list) {
	if (list->size == 0)
	{
		return CIRCLELINKLIST_TRUE;
	}
	else {
		return CIRCLELINKLIST_FALSE;
	}
}

// �������ݵ�����
int Find_CircleLinkList(CircleLinkList* list, CircleLinkNode* data, COMPARECIRCLELINKNODE compare) {
	if (list == NULL || data == NULL)
	{
		return -1;
	}
	CircleLinkNode* current_node = list->head.next;
	int index = 0;
	while (current_node != &(list->head))
	{
		if (compare(current_node, data) == CIRCLELINKLIST_TRUE)
		{
			return index;
		}
		current_node = current_node->next;
		index++;
	}
	return -1;
}

// ��ӡ�ڵ�
void Print_CircleLinkList(CircleLinkList* list, PRINTCIRCLELINKNODE print) {
	if (list == NULL)
	{
		return;
	}
	CircleLinkNode* current_node = list->head.next;
	while (current_node != &(list->head))
	{
		print(current_node);
		current_node = current_node->next;
	}
}

// �ͷ��ڴ�, ֻ�ͷſ���Լ�malloc�����Ŀռ�, ��CircleLinkList�Ŀռ�, �ڵ�ռ������û�������, ���û�����
void FreeSpace_CircleLinkList(CircleLinkList* list) {
	if (list == NULL)
	{
		return;
	}
	free(list);
}

// ����
// �����Զ�������
typedef struct TEACHER {
	CircleLinkNode node;
	char name[64];
	int age;
}Teacher;
// ������ϴ�ӡ����ָ��ĺ���
void PrintCircleLinkNode(CircleLinkNode* data) {
	if (data == NULL)
	{
		return;
	}
	Teacher* t = (Teacher*)data;
	printf("name: %s, age: %d\n", t->name, t->age);
}
// ������ϱȽϽڵ㺯��ָ��ĺ���
int CompareCircleLinkNode(CircleLinkNode* data1, CircleLinkNode* data2) {
	if (data1 == NULL || data2 == NULL)
	{
		return CIRCLELINKLIST_FALSE;
	}
	Teacher* t1 = (Teacher*)data1;
	Teacher* t2 = (Teacher*)data2;
	if (strcmp(t1->name, t2->name) == 0 && t1->age == t2->age)
	{
		return CIRCLELINKLIST_TRUE;
	}
	else {
		return CIRCLELINKLIST_FALSE;
	}
}
void test_ciclelinklist() {
	CircleLinkList* list = Init_CircleLinkList();
	Teacher t1, t2, t3, t4, t5;
	strcpy(t1.name, "zhangsan");
	strcpy(t2.name, "lisi");
	strcpy(t3.name, "wangwu");
	strcpy(t4.name, "zhaoliu");
	strcpy(t5.name, "tianqi");
	t1.age = 21;
	t2.age = 22;
	t3.age = 23;
	t4.age = 24;
	t5.age = 25;
	// ����������
	Insert_CircleLinkList(list, 0, (CircleLinkNode*)&t1);
	Insert_CircleLinkList(list, 1, (CircleLinkNode*)&t2);
	Insert_CircleLinkList(list, 2, (CircleLinkNode*)&t3);
	Insert_CircleLinkList(list, 3, (CircleLinkNode*)&t4);
	Insert_CircleLinkList(list, 4, (CircleLinkNode*)&t5);

	Teacher t;
	t.age = 23;
	strcpy(t.name, "wangwu");
	// RemoveByValue_CircleLinkList(list, (CircleLinkNode*)&t, CompareCircleLinkNode);
	int wangwu_pos = Find_CircleLinkList(list, (CircleLinkNode*)&t, CompareCircleLinkNode);
	printf("wangwu's index is %d\n", wangwu_pos);

	Print_CircleLinkList(list, PrintCircleLinkNode);
	FreeSpace_CircleLinkList(list);
}
#pragma endregion

#pragma region Լɪ������a���Ƴ��ɵ�ѭ�������ٲ����µ�ѭ������bѭ��������ʱ��ע�����һ��Ԫ�ص�nextָ�����list->head,�����ǵ�һ��Ԫ��
typedef struct NUMBER {
	CircleLinkNode node;
	int num;
}Number;
#define M 8
#define N 3
int CompareNumber(CircleLinkNode* data1, CircleLinkNode* data2) {
	Number* num1 = (Number*)data1;
	Number* num2 = (Number*)data2;
	if (num1->num == num2->num)
	{
		return CIRCLELINKLIST_TRUE;
	}
	else {
		return CIRCLELINKLIST_FALSE;
	}
}
void PrintNumber(CircleLinkNode* data) {
	Number* num = (Number*)data;
	printf("%d\n", num->num);
}
void test_yuesefu() {
	// m����Χ��һ��Ȧ, ��������n���˳���
	CircleLinkList* list = Init_CircleLinkList();
	Number num[M];
	for (int i = 0; i < M; i++)
	{
		num[i].num = i + 1;
		Insert_CircleLinkList(list, i, (CircleLinkNode*)&num[i]);
	}
	
	CircleLinkList* out_list = Init_CircleLinkList();
	CircleLinkNode* prev_node;
	CircleLinkNode* node = &(list->head);
	while (list->size > 1)
	{
		for (int i = 0; i < N; i++)
		{
			prev_node = node;
			node = node->next;
			// ���һ��Ԫ�ص�ʱ��, Ĭ��ָ��list->head, ��Ҫ�жϲ��л�����һ��Ԫ��
			if (node == &(list->head))
			{
				node = node->next;
			}
		}	
		
		// ��Ҫ���Ƴ�, Ȼ�������Ƴ���node��ӵ��µ�ѭ����·����, �Ȳ���Ļ�, �Ƴ��ͻ��������
		RemoveByValue_CircleLinkList(list, node, CompareNumber); 
		Insert_CircleLinkList(out_list, out_list->size, node); // TODO: ...

		node = prev_node;
	}
	Insert_CircleLinkList(out_list, out_list->size, list->head.next);

	cout << "result: " << endl;
	Print_CircleLinkList(out_list, PrintNumber); // 3 6 1 5 2 8 4 7
}

#pragma endregion


int main(int argc, char* argv[])
{
	test_yuesefu();
	// m����Χ��һ��Ȧ, ��������n���˳���
	/*CircleLinkList* list = Init_CircleLinkList();
	Number num[M];
	for (int i = 0; i < M; i++)
	{
		num[i].num = i + 1;
		Insert_CircleLinkList(list, i, (CircleLinkNode*)&num[i]);
	}
	CircleLinkList* out_list = Init_CircleLinkList();
	CircleLinkNode* node = list->head.next->next->next;
	Insert_CircleLinkList(out_list, out_list->size, node);*/
	return 0;
}