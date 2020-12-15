#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h> 
#include<iostream>

#define OK 1
#define NEXTSIZE 100
#define OVERFLOW 1 





typedef struct {
	char* ch;
	int length;
}Hstring;

int StrAssign(Hstring &T, char* chars) {
	int i = 0;
	if (T.ch) T.ch=NULL;
	T.length = strlen(chars);
	if (!T.length) T.ch = NULL;
	else {
		if (!(T.ch = (char*)malloc(T.length * sizeof(char))))
			exit(OVERFLOW);
		for(i = 0; i < T.length; i++) {
			T.ch[i] = chars[i];
		}
	}
	return OK;
}
int str_compare(Hstring s, Hstring t) {
	//如果s>t返回值大于零，相等返回0；s<t返回小于零
	int i = 0;
	for (i = 0; i < s.length && i < t.length; i++) {
		if (s.ch[i] != t.ch[i]) return s.ch[i] - t.ch[i];
	}
	return s.length - t.length;
}
void  clear_str(Hstring& h) {
	//将h清理空串
	if (h.ch) {
		free(h.ch);
		h.ch = NULL;
	}
	h.length = 0;
}


int index_kmp(Hstring a, Hstring b) {
	//利用kmp模式匹配算法求出字符匹配的位置
	//其中b非空
	//先求出next数组，再进行匹配
	if (a.length < b.length)
		return -1;
	int i = 1, j = 0;
	int next[50] = { 0 };
	next[1] = 0; j = 0;
	while (i <= b.length) {
		if (j == 0 || b.ch[i - 1] == b.ch[j - 1]) {
			i++; j++;
			next[i] = j;
		}
		else j = next[j];
	}
	i = 1; j = 1;
	while (i <= a.length && j <= b.length) {
		if (j == 0 || a.ch[i - 1] == b.ch[j - 1]) {
			i++; j++;
		}
		else j = next[j];
	}
	if (j > b.length)
		return i - b.length;
	else return -1;

}
/*int main() {
	Hstring x, y;
	int ans = 0;
	char m[50] = { '\0' }, n[50] = { '\0' };
	scanf_s("%s",m,50); scanf_s("%s", n,50);
	x.ch = m; y.ch = n;
	x.length = strlen(m);
	y.length = strlen(n);
	ans = index_kmp(x, y);
	printf("%d", ans);
	return 0;

}*/
int main(int argc,char *argv[]) {
	// 参数数量错误
	if (argc != 3) {
		printf("%s", "ERROR_01");
		return 0;
	}
	int ans = 0;
	Hstring str1, str2; 
	str1.ch=NULL;
	str2.ch=NULL;
	str1.length=0;
	str2.length=0;
	StrAssign(str1, argv[1]);
	StrAssign(str2, argv[2]);
	ans = index_kmp(str1, str2);
	printf("%d", ans);
	clear_str(str1);
	clear_str(str2);
	return 0;
}
