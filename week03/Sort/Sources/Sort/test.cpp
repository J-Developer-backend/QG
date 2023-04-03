#include<stdio.h>
#include<string.h>
#include<time.h>
#include<Windows.h>
#include"Sort.h"
#include"冒泡优化.h"

//不同数量级的数组
int a1[10000] = { 0 };
int a2[50000] = { 0 };
int a3[100000] = { 0 };
int a4[100] = { 0 };
int temp[100000] = { 0 };
int* arrs[5] = { a1,a2,a3,a4,temp };
int type[4] = { 10000,50000,100000,100 };
void testMenu();


//输入数据处理
bool checkInput(char* s, int* data) {
	//字符串过短或过长
	if (strlen(s) == 0 || strlen(s) > 11)
		return false;
	int index = 1;
	int i = 0;
	//符号断定
	if (s[0] == '-') {
		i++;
		index = -1;
	}
	long temp = 0;
	//检查合理性
	for (; s[i] != '\0'; i++) {
		if (s[i] > '9' || s[i] < '0')
			return false;
		//累计求和
		temp = temp * 10 + s[i] - '0';
	}
	//判断范围是否合理
	if (temp >= 2147483648 || temp < -2147483648)
		return false;
	*data = (int)(temp * index);
	return true;
}

//生成随机数到文件中
void productData(int n,int m) {
	FILE* fp;
	FILE** p = &fp;
	fopen_s(p, "data.txt", "w");
	srand((unsigned)time(NULL));
	if(m!=3)
		while (n--) {
			int a = rand() % m;
			fprintf(fp, "%d%c", a, ' ');
		}
	else
		while (n--) {
			int a = rand() % m;
			fprintf(fp, "%d%c", a, '\n');
		}
	fclose(fp);
}

//转换为整数
int toInt(char* s) {
	int num = 0;
	for (int i = 0; s[i] != '\0' && s[i]!='\n'; i++)
		num = num * 10 + s[i] - '0';
	return num;
}

//读文件的数据到数组中
void toArray(int n) {
	FILE* fp;
	FILE** p = &fp;
	fopen_s(p, "data.txt", "r");
	char c = ' ';
	for (int i = 0; i < type[n]; i++) {
		int j = 0;
		char ch[5] = "";
		while ((c = fgetc(fp)) != -1 && c != ' ') {
			if (c == '\n')
				break;
			ch[j] = c;
			j++;
		}
		arrs[n][i] = toInt(ch);
	}
	fclose(fp);
}

//排序
void sortRun(int commend ,int i ,int n , int k = -1) {
	int rs = 0;
	switch (commend) {
	case 1: {
		insertSort(arrs[i], n);
		break;
	}
	case 2: {
		MergeSort(arrs[i], 0, n - 1, temp);
		break;
	}
	case 3: {
		QuickSort_Recursion(arrs[i], 0, n - 1);
		break;
	}
	case 4: {
		QuickSort(arrs[i], n);
		break;
	}
	case 5: {
		QuickSort_Random(arrs[i], n);
		break;
	}
	case 6: {
		Partition(arrs[i], 0, n - 1);
		break;
	}
	case 7: {
		CountSort(arrs[i], n, 9999);
		break;
	}
	case 8: {
		RadixCountSort(arrs[i], n);
		break;
	}
	case 9: {
		ColorSort(arrs[i], n);
		break;
	}
	case 10: {
		rs = FindSmallNumber(arrs[i], n, k);
		break;
	}
	case 11: {
		rs = FindBigNumber(arrs[i], n, k);
		break;
	}
	case 12: {
		BubblSort1(arrs[i], n);
		break;
	}
	case 13: {
		BubblSort2(arrs[i], n);
		break;
	}
	case 14: {
		BubblSort3(arrs[i], n);
		break;
	}
	case 15: {
		exit(0);
	}
	}
	if(commend == 10)
		printf("第%d小的数为%d \n", k, rs);
	if (commend == 11)
		printf("第%d大的数为%d \n", k,rs);
}

//确定第k大/小中的k
int inputK(int n) {
	char s[1024] = "";
	int k = 0;
	bool b = true;
	do {
		printf("please iuput the k\n");
		gets_s(s);
		b = checkInput(s, &k) && k > 0 && k <= n;
	} while (!b);
	system("pause");
	system("cls");
	return k;
}

//大数据量测试
void manyDataTest(int commend) {
	printf("大数据量测试:\n");
	for (int i = 0; i < 3; i++) {
		int n = type[i];
		int  k = -1;
		if (commend == 11 || commend == 10)
			k = inputK(n);
		if (commend == 9)
			productData(n, 3);
		else
			productData(n, 10000);
		toArray(i);
		clock_t start = clock();
		sortRun(commend, i, n, k);
		if (commend != 10 && commend != 11)
			printf("排序%d个数据用时:%d ms\n", n , clock() - start);
		else
			printf("从%d个数据找到对应数据用时:%d ms\n", n, clock() - start);
	}
	system("pause");
	system("cls");
}


//大量小数据量测试
void someDataTests(int commend) {
	int  k = -1;
	if (commend == 11 || commend == 10)
		k = inputK(100);
	printf("大量小数据量测试:(100个数据)\n");

	clock_t time = 0;
	for (int i = 0; i < 1000; i++) {
		if (commend == 9)
			productData(100, 3);
		else
			productData(100, 10000);
		toArray(3);
		clock_t start = clock();
		sortRun(commend, 3, 100,k);
		time = time + clock() - start;
	}
	printf("1000次排序用时:%d ms\n", time);
	system("pause");
	time = 0;
	for (int i = 0; i < 100000; i++) {
		if (commend == 9)
			productData(100, 3);
		else
			productData(100, 10000);
		toArray(3);
		clock_t start = clock();
		sortRun(commend, 3, 100,k);
		time = time + clock() - start;
	}
	printf("100000次排序用时:%d ms\n", time);
	system("pause");
	system("cls");
}

//数据量选择菜单
int dataTypeMenu() {
	system("cls");
	printf("1.大数据量测试\n");
	printf("2.大量小数据量测试\n");
	printf("3.back\n");
	int commend = 0;
	int m = 0;
	char s[1024] = "";
	bool b = true;
	do {
		printf("please input the commend:\n");
		gets_s(s);
		b = checkInput(s, &commend) && (commend > 0 && commend < 4);
	} while (!b);
	system("cls");
	if (commend == 3)
		testMenu();
	else
		return commend;
	return -1;
}

//测试菜单
void testMenu() {
	int* p = NULL;
	int size = 0;
	int k = 0;
	while (true) {
		printf("1.InsertSort（插入排序）\n");
		printf("2.MergeSort（归并排序）\n");
		printf("3.QuickSort_Recursion（快排递归版）\n");
		printf("4.QuickSort（快排非递归版）\n");
		printf("5.QuickSort_Random（快排递归随机版）\n");
		printf("6.Partition（快排三枢轴）\n");
		printf("7.CountSort（计数排序）\n");
		printf("8.RadixCountSort（基数排序）\n");
		printf("9.ColorSort（颜色排序）\n");
		printf("10.FindSmallNumber（找第k小）\n");
		printf("11.FindBigNumber（找第k大）\n");
		printf("12.BubblSort1（冒泡优化1）\n");
		printf("13.BubblSort2（冒泡优化2）\n");
		printf("14.BubblSort3（冒泡优化3）\n");
		printf("15.exit\n");
		int commend = 0;
		char s[1024] = "";
		bool b = true;
		do {
			printf("please input the commend:\n");
			gets_s(s);
			b = (checkInput(s, &commend)) && ((commend > 0 && commend < 16));
		} while (!b);
		system("cls");
		int type = dataTypeMenu();
		if (type == 1)
			manyDataTest(commend);
		else if (type == 2)
			someDataTests(commend);
	}
}

int main() {
	testMenu();
}
