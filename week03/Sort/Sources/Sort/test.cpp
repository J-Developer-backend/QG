#include<stdio.h>
#include<string.h>
#include<time.h>
#include<Windows.h>
#include"Sort.h"
#include"ð���Ż�.h"

//��ͬ������������
int a1[10000] = { 0 };
int a2[50000] = { 0 };
int a3[100000] = { 0 };
int a4[100] = { 0 };
int temp[100000] = { 0 };
int* arrs[5] = { a1,a2,a3,a4,temp };
int type[4] = { 10000,50000,100000,100 };
void testMenu();


//�������ݴ���
bool checkInput(char* s, int* data) {
	//�ַ������̻����
	if (strlen(s) == 0 || strlen(s) > 11)
		return false;
	int index = 1;
	int i = 0;
	//���Ŷ϶�
	if (s[0] == '-') {
		i++;
		index = -1;
	}
	long temp = 0;
	//��������
	for (; s[i] != '\0'; i++) {
		if (s[i] > '9' || s[i] < '0')
			return false;
		//�ۼ����
		temp = temp * 10 + s[i] - '0';
	}
	//�жϷ�Χ�Ƿ����
	if (temp >= 2147483648 || temp < -2147483648)
		return false;
	*data = (int)(temp * index);
	return true;
}

//������������ļ���
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

//ת��Ϊ����
int toInt(char* s) {
	int num = 0;
	for (int i = 0; s[i] != '\0' && s[i]!='\n'; i++)
		num = num * 10 + s[i] - '0';
	return num;
}

//���ļ������ݵ�������
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

//����
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
		printf("��%dС����Ϊ%d \n", k, rs);
	if (commend == 11)
		printf("��%d�����Ϊ%d \n", k,rs);
}

//ȷ����k��/С�е�k
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

//������������
void manyDataTest(int commend) {
	printf("������������:\n");
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
			printf("����%d��������ʱ:%d ms\n", n , clock() - start);
		else
			printf("��%d�������ҵ���Ӧ������ʱ:%d ms\n", n, clock() - start);
	}
	system("pause");
	system("cls");
}


//����С����������
void someDataTests(int commend) {
	int  k = -1;
	if (commend == 11 || commend == 10)
		k = inputK(100);
	printf("����С����������:(100������)\n");

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
	printf("1000��������ʱ:%d ms\n", time);
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
	printf("100000��������ʱ:%d ms\n", time);
	system("pause");
	system("cls");
}

//������ѡ��˵�
int dataTypeMenu() {
	system("cls");
	printf("1.������������\n");
	printf("2.����С����������\n");
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

//���Բ˵�
void testMenu() {
	int* p = NULL;
	int size = 0;
	int k = 0;
	while (true) {
		printf("1.InsertSort����������\n");
		printf("2.MergeSort���鲢����\n");
		printf("3.QuickSort_Recursion�����ŵݹ�棩\n");
		printf("4.QuickSort�����ŷǵݹ�棩\n");
		printf("5.QuickSort_Random�����ŵݹ�����棩\n");
		printf("6.Partition�����������ᣩ\n");
		printf("7.CountSort����������\n");
		printf("8.RadixCountSort����������\n");
		printf("9.ColorSort����ɫ����\n");
		printf("10.FindSmallNumber���ҵ�kС��\n");
		printf("11.FindBigNumber���ҵ�k��\n");
		printf("12.BubblSort1��ð���Ż�1��\n");
		printf("13.BubblSort2��ð���Ż�2��\n");
		printf("14.BubblSort3��ð���Ż�3��\n");
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
