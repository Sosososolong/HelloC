#include <stdio.h>
#include <stdlib.h>
// #include "hello.h"
#include <string.h>
#include <time.h>
#define MAX 51
// 用随机字母填充字符数组, 字符数组的总长度(包含结束符)为宏定义MAX
// str 需要填充的字符数组的首地址 
void fill_rand_string(char* str)
{
	srand((unsigned int)time(NULL)); //随机种子
	int i = 0;
	for (i = 0; i < MAX - 1; i++)
	{
		// rand() % 26, 得到0~25的一个随机数
		*(str + i) = rand() % 26 + 'a';
	}

	*(str + MAX - 1) = '\0';
}
struct Student
{
	int age;
	char name[50];
	int score;
};
enum
{
	pink, red, green, white, yellow
};
/*选择排序*/
int choose_sort(int* int_array, int n)
{
	int a[] = { 2, 10, 8, 7, 5, 4, 1, 3, 6, 9 };
	int temp = 0;
	// printf("排序前:");
	// for (int i = 0; i < n; i++)
	// {
	//     printf("%d ", a[i]);
	// }
	// printf("\n");

	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (a[i] > a[j])
			{
				temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}
		}
	}
	// printf("排序后:");
	for (int i = 0; i < n; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
	return 1;
}

// 查看某个字符串(src)中包含子字符串(substr)的个数(count)
int str_contains(char* src, const char* substr, int* count) {
	while (src = strstr(src, substr))
	{
		(*count)++;
		src = src + strlen(substr);
		if (*src == 0)
		{
			break;
		}
	}
	return 0;
}

/*
查询笔记中带关键字的片段笔记
*/
int found_snippet(const char* file_name, const char* keyword)
{	
	FILE* fp = fopen(file_name, "r");
	char buf[600] = { 0 };
	while (1)
	{		
		fgets(buf, sizeof(buf), fp);
		
		// int count1 = 0;
		int count2 = 0;
		// 如果是"====xxx===="这样的标题行, 查看是否包含关键字
		// str_contains(buf, "====", &count1);
		str_contains(buf, keyword, &count2);
		// if (count1 > 0 && count2 > 0)
		if (count2 > 0)
		{
			printf("%s", buf);
			while (1)
			{
				fgets(buf, sizeof(buf), fp);
				int count3 = 0;
				str_contains(buf, "====", &count3);
				if (count3 > 0 || feof(fp)) // 如果遇到下一个标题了跳出打印循环, 
				{
					printf("===============end==================\n\n");
					break;
				}

				printf("%s", buf);
			}
		}
		if (feof(fp))
		{
			break;
		}		
	}
	return 0;
}

// 去处字符串inbuf首尾的空格, 去除空格后的字符串为outbuf, 成功返回0
int trim_space(char* inbuf, char* outbuf) {
	if (inbuf == NULL || outbuf == NULL)
	{
		return -1;
	}

	char* p = inbuf;
	int begin = 0;
	int end = strlen(p) - 1;
	int n = 0; // 非空元素个数
	if (end < 0)
	{
		return -2;
	}
	//从左往右移动, 如果当前字符为空, 而且没有结束
	while (p[begin] == ' ' && p[begin] != 0)
	{
		begin++; //指针位置向右边移动一位
	}
	//从右往左移动, 如果当前字符为空
	while (p[end] == ' ' && end > 0) // >0放止空串的时候减到最左边还减
	{
		end--; // 往左移动
	}
	if (end == 0) // 空串会减到0为止
	{
		return -2;
	}

	n = end - begin + 1; // 非空元素个数        
	strncpy(outbuf, p + begin, n);
	outbuf[n] = 0;
	return 0;
}

// 根据键值对字符串("key1 =  value1")的键, 获取值(去空格)
int get_value_by_key(char* key_value_buf, char* key_buf, char* value_buf, int* value_buf_len)
{
	/*
	key_value_buf = "key1 =     value1";
	key_buf = "key1";
	*/
	if (key_buf == NULL || key_value_buf == NULL || value_buf == NULL || value_buf_len == NULL)
	{
		return -1;
	}
	char* p = NULL;
	// 查找匹配键值, "key1 =     value1"找"key1"
	p = strstr(key_value_buf, key_buf);
	if (p == NULL)
	{
		return -2;
	}
	// 找到key_buf, 重新设置起点, 跳过"key1", 即"key1 =     value1" => " =     value1";
	p = p + strlen(key_buf);
	// 查找"="
	p = strstr(p, "=");
	if (p == NULL)
	{
		return -3;
	}
	// 找到"="
	// p = p + 1;
	p++;
	int ret = trim_space(p, value_buf);
	if (ret != 0)
	{
		printf("trim_space error: %d\n", ret);
		return ret;
	}
	// 获取长度
	*value_buf_len = strlen(value_buf);
	return 0;
}

#pragma region 在堆区创建一个长度为3的二维数组(三个字符串), 打印数组, 最后释放堆区内存

// 堆区创建一个二维数组(3个字符串)并返回
char** get_mem(int n)
{
	n = 3;
	char** buf = (char**)malloc(n * sizeof(char*)); // char* buf[3]
	if (buf == NULL)
	{
		return -1;
	}
	for (int i = 0; i < n; i++)
	{
		buf[i] = malloc(30 * sizeof(char));
		char str[30];
		sprintf(str, "test%d%d", i, i);
		strcpy(buf[i], str);
	}
	return buf;
}

// 打印二位数组
void print_buf(char** buf, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%s, ", buf[i]);
	}
	printf("\n");
}

// 释放堆区空间
void free_buf(char** buf, int n)
{
	for (int i = 0; i < n; i++)
	{
		free(buf[i]);
		buf[i] = NULL;
	}
	if (buf != NULL)
	{
		free(buf);
		buf = NULL;
	}
}
#pragma endregion

// 在字符串(src)中找到匹配的子字符串(sub), 然后用另一个字符串(new_sub)替换子字符串(sub), (dst)为输出参数
int replace_substr(char* src, char** dst, char* sub, char* new_sub)
{
	if (src == NULL || dst == NULL || sub == NULL || new_sub == NULL)
	{
		return -1;
	}
	char* start = src;
	char* p = NULL;
	char tmp[512] = { 0 };
	int len = 0;
	do
	{
		p = strstr(start, sub);
		if (p != NULL)
		{
			len = 0;
			len = p - start;
			if (len > 0)
			{
				strncat(tmp, start, len);
			}
			strncat(tmp, new_sub, strlen(new_sub));
			// 重新设置起点位置
			start = p + strlen(sub);
		}
		else
		{
			strcat(tmp, start);
			break;
		}
	} while (*start != '\0');
	// 新字符串要传到主函数中, 所以此子函数调用结束不能释放, 需要在对空间开辟内存空间, 然后由主函数手动释放
	char* buf = (char*)malloc(strlen(tmp) + 1);
	strcpy(buf, tmp);

	// 间接赋值
	*dst = buf;
	return 0;
}

// 用一个字符(c)分割字符串(str), 放到数组(buf)中, 并返回数组的长度(n)
int split_string(const char* str, char c, char buf[10][30], int* count)
{
	if (str == NULL || count == NULL)
	{
		return -1;
	}
	// str = "sfjlsf,sfa,abcd,3dedd,sss,aaa"
	const char* start = str;
	char* p = NULL;
	int i = 0;
	do
	{
		p = strchr(start, c);
		if (p != NULL)
		{
			int len = p - start;
			strncpy(buf[i], start, len);
			// 结束符
			buf[i][len] = 0;
			i++;
			// 重新设置起点位置
			start = p + 1;
		}
		else
		{
			strcpy(buf[i], start);
			i++;
			break;
		}
	} while (*start != 0);
	if (i == 0)
	{
		return -2;
	}
	*count = i;
	return 0;
}

int main(int argc, char* argv[])
{	
	if (argc == 3)
	{
		// 查找笔记片段
		found_snippet(argv[1], argv[2]);
		return 0;
	}
	int a[][4] = { 1,2,3,4,5,6,7,8,9,10,11,12 };
	printf("a: %d, a+1: %d\n", (int)a, (int)(a + 1));
	printf("a+1=%d, *(a+1) = %d\n", (int)(a+1), (int)(*(a+1)));

	

	// system("pause");
	return 0;
}
