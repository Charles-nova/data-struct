// Huffman_tree.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
#include<stdio.h>
#include<stdlib.h>
#include<string.h> 
#define str_num 27 //一共27个字符 
#define OK 1
#define ERROR 0
#define minlen 20
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10


typedef struct {
	int weight;
	int parent, ichlid, rchild;
}htnode, * huffman_tree; //动态分配数组存储霍夫曼树 

typedef char** huffman_code; //动态分配数组储霍夫曼编码

typedef struct {
	htnode* base;
	htnode* top;
	int stacksize;
}SqStack;

int InitStack(SqStack& s)
{
	s.base = (htnode*)malloc(STACK_INIT_SIZE * sizeof(htnode));
	if (!s.base)exit(OVERFLOW);
	s.top = s.base;
	s.stacksize = STACK_INIT_SIZE;
	return OK;
}

int GetTop(SqStack &stack, htnode * elem) {
	if (stack.top == stack.base)return ERROR;
	*elem = *(stack.top - 1);
	return OK;
}
int Push(SqStack& stack, htnode* node)
{
	if (stack.top - stack.base >= stack.stacksize)
	{
		stack.base = (htnode*)realloc(stack.base, (stack.stacksize + STACKINCREMENT) * sizeof(htnode));
		if (!stack.base) return 0;
		stack.top = stack.base + stack.stacksize;
		stack.stacksize += STACKINCREMENT;
	}
	*stack.top++ = *node;
	return OK;
}

int Pop(SqStack& stack, htnode* node) {
	if (stack.top == stack.base)
		return ERROR;
	*node = *--stack.top;
	return OK;
}



int find_weight(char* str, char* ordered_str, int* weight) {
	//找出权值的函数，并将字符按照字母表顺序排序，weight数组为排序后对应的字符串，不重复
	int count = 0, i = 0, j = 0, k = 0;//记录字符个数
	char* temp = NULL;
	temp = (char*)malloc(str_num * sizeof(char));
	if (temp == NULL) return ERROR;
	temp[0] = ' ';//第一个元素为空格
	for (i = 1; i < str_num; i++)temp[i] = 'a' + i - 1; //按顺序生成所有的字符表 
	for (i = 0, k = 0; i < str_num; i++) {
		count = 0;
		for (j = 0; j < strlen(str); j++) {
			if (temp[i] == str[j])count++;
		}
		if (count != 0) {
			ordered_str[k] = temp[i]; weight[k] = count; k++;
		}
	}
	free(temp);
	return OK;
}

void  select(huffman_tree& HT, int temp_len, int& min1, int& min2) {
	int j=0;
	
	while (OK) {
		if (HT[j].parent != -1)j++;
		else break;
	}
	for (min1=j; j < temp_len; j++) {
		if (HT[j].parent == -1 && HT[j].weight < HT[min1].weight) {
			min1 = j;
		}
	}
	HT[min1].parent = 1;
	j = 0;
	while (1) {
		if (HT[j].parent != -1)j++;
		else break;
	}
	for (min2=j; j < temp_len; j++) {
		if (j != min1 && HT[j].parent == -1) {
			if (HT[j].weight < HT[min2].weight)min2 = j;
		}
	}
	HT[min2].parent = 1;
}
int huffman_coding(huffman_tree& HT, huffman_code& HC, int* weight, int len) {
	//weight 为存放n个字符的权值，（其中字符对应排序好的），构造霍夫曼树HT,并求出len个字符(不重复）的霍夫曼编码 
	int HT_len = 0; char* cd = NULL; //cd临时存放编码
	htnode* p = NULL; int i = 0; int c = 0; int f = 0;//循环变量指针
	int min1 = 0, min2 = 0;
	int start = 0; 
	HT_len = 2 * len - 1;
	HT = (huffman_tree)malloc((HT_len + 1) * sizeof(htnode));
	if (HT == NULL)return ERROR;
	for (p = HT, i = 0; i < len; ++i, ++p, ++weight) *p = { *weight,-1,-1,-1 }; //HT这里没有使用0号位 
	for (; i < HT_len; i++, p++) *p = { -1,-1,-1,-1 };
	for (i = len; i < HT_len; i++) { //建立霍夫曼树 
		//在HT[0---i-1]中选择parent为-1且weight为最小的两个结点，其序号为s1,s2。
		min1 = 0; min2 = 0;
		select(HT, i, min1, min2);
		HT[min1].parent = i; HT[min2].parent = i;
		HT[i].ichlid = min1; HT[i].rchild = min2;
		HT[i].weight = HT[min2].weight + HT[min1].weight;
	}

	//求每个字符的霍夫曼编码
	HC = (huffman_code)malloc((len + 1) * sizeof(char*));
	cd = (char*)malloc(len * sizeof(char));
	if (HC == NULL || cd == NULL) return ERROR;
	cd[len - 1] = '\0';
	for (i = 0; i < len; i++) {
		start = len - 1;
		for (c = i, f = HT[i].parent; f != -1; c = f, f = HT[f].parent) {
			if (HT[f].ichlid == c) cd[--start] = '0';
			else cd[--start] = '1';
		}
		HC[i] = (char*)malloc((len - start+1) * sizeof(char)); //为第i个字符编码分配空间 ,注意0号位置已经使用 
		if (HC[i] == NULL) return ERROR;
		strcpy_s(HC[i],len-start+1, &cd[start]);
	}
	free(cd);//释放空间 
	return OK;
}

void print_info(htnode * p,int depth) {
	int node_degree = 0;
	if (p->ichlid == -1 && p->rchild == -1)node_degree = 0;
	else if (p->ichlid != -1 && p->rchild != -1)node_degree = 2;
	else node_degree = 1;
	printf("%d", p->weight);
	printf("%d", depth);
	printf("%d", node_degree);
}

void root_first(huffman_tree& HT) {
	SqStack stack; htnode* point; htnode node = { 0,0,0,0 };
	int depth = 0; int node_degree = 0; //深度depth，节点的度node_degree
	InitStack(stack);
	point = HT;
	while (point || stack.top != stack.base) {
		if (point) {
			Push(stack,point); depth++;
			print_info(point, depth);
			point = HT+point->ichlid;
		}
		else {
			Pop(stack, point); depth--;
			print_info(point, depth);
			point = HT + point->rchild;
		}
	}
}

void print(char * string) {
	int i = 0;
	for (i = 0; i < strlen(string); i++)
		printf("%c", string[i]);
}
int  code_print(char str[], char* ordered_str, huffman_code& HC) {
	//输出 
	int i = 0, j = 0, k = 0;
	if (strlen(ordered_str) == 1) {
		printf("%c", '0');
		return OK;
	}
	else {
		for (i = 0; i < strlen(str); i++) {
			for (j = 0; j < strlen(ordered_str); j++) {
				if (str[i] == ordered_str[j]) {
					print(HC[j]);
				}
			}
		}
	}
}

int  decode(huffman_tree& HT, int len, char str1[], char deco[], char* ordered_str) {
	int root = 0, i = 0, j = 0,temp1=0, temp_root = 0,parent = 0;
	for (i = 0; i <= 2 * len - 1; i++) {
		if (HT[i].weight > HT[root].weight)root = i;
	}
	temp_root = root;
	if (len == 1) {
		for (i = 0; i < strlen(str1); i++) {
			if (str1[i] == '1') {
				return ERROR;
			}
		}
		for (i = 0; i < strlen(str1); i++) {
			deco[i] = ordered_str[0];
		}
	}
	for (i = 0, j = 0; j < strlen(str1); j++) {
		if (HT[temp_root].ichlid != -1 && HT[temp_root].rchild != -1) {
			temp1 = temp_root;
			if (str1[j] == '0')temp_root = HT[temp_root].ichlid;
			else temp_root = HT[temp_root].rchild;
		}
		if (HT[temp_root].ichlid == -1 && HT[temp_root].rchild == -1) {
			temp1 = temp_root;
			//parent = HT[temp_root].parent;
			//if (str1[j] == '0')temp1 = HT[parent].ichlid;
			//if (str1[j] == '1')temp1 = HT[parent].rchild;
			deco[i] = ordered_str[temp_root]; i++;
			//if (j == strlen(str1) - 1 && (HT[temp_root].ichlid != -1 && HT[temp_root].rchild != -1))
				//return 0;//解码错误 返回ERROR_03;
			temp_root = root;
		}
		if (j == strlen(str1) - 1 && (HT[temp1].ichlid != -1 && HT[temp1].rchild != -1))
			return ERROR;//解码错误 返回ERROR_03;
		
	}
	return OK;
}


int main(int argc, char** argv) {
	huffman_tree HT = NULL; huffman_code HC = NULL;
	char* ordered_str = NULL; char* deco; 
	int flag = OK; int* weight = NULL; int i = 0;
	if (argc != 3) {
		printf("%s","ERROR_01");
		return 0;
	}
	ordered_str = (char*)malloc((strlen(argv[1]) + 2) * sizeof(char));
	deco = (char*)malloc((strlen(argv[2]) + 2) * sizeof(char));
	weight = (int*)malloc((strlen(argv[1]) + 2) * sizeof(int));
	if (ordered_str == NULL || deco == NULL || weight == NULL) {
		printf("%s", "Malloc_ERROR");
		return 0;
	}
	//初始化
	for (i = 0; i < strlen(argv[1]) + 2;i++) {
		ordered_str[i] = '\0';
		weight[i] = '0';
	}
	for (i = 0; i < strlen(argv[2]) + 2;i++) {
		deco[i] = '\0';
	}
	find_weight(argv[1], ordered_str, weight);
	huffman_coding(HT, HC, weight, strlen(ordered_str));
	flag = decode(HT, strlen(ordered_str), argv[2], deco, ordered_str);
	if (strlen(argv[1]) < minlen) {
		printf("%s", "ERROR_02");
		return 0;
	}
	if (flag == ERROR)printf("%s", "ERROR_03");
	else {
		code_print(argv[1], ordered_str, HC);
		printf("%s", " ");
		printf("%s", deco);
	}
	free(deco); free(ordered_str); free(weight);
	free(HT); free(HC);
	return 0;
}


