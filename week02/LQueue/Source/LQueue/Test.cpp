#include<stdio.h>
#include<string.h>
#include "LQueue.h"

//类型选择
int setType() {
	char ss[1024] = "";
	printf("1.int\n2.char\n3.double\nchoose the type you want to input:\n");
	//getchar();
	while (1) {
		gets_s(ss);
		if ((ss[0] == '1' || ss[0] == '2' || ss[0] == '3') && strlen(ss) == 1)
			break;		
		printf("please input the rigth choice\n");
	}		
	return ss[0] - '0';
}

//int
bool setInt(void *p) {
	char ss[1024] = "";
	long num = 0;
	int index = 1;
	gets_s(ss);
	if (ss[0] == '-')
		index = -1;
	for (int i = 0; ss[i] != '\0'; i++) {
		if (ss[i] > '9' || ss[i] < '0')
			return false;
		num = num * 10 + ss[i] - '0';
	}
	num = num * index;
	if (num < -32768 || num >32767)
	{
		printf("over the limit\n");
		return false;
	}
	memcpy(p, &num, sizeof(int));
	return true;
}

//char
bool setChar(void* p) {
	char ss[1024] = "";
	gets_s(ss);
	if (strlen(ss) != 1)
		return false;
	memcpy(p, &ss[0], sizeof(char));
	return true;
}

//double
bool setDouble(void* p) {
	char ss[1024] = "";
	double num1 = 0;
	double index = 1.0;
	int flag = 0;
	gets_s(ss);
	if (ss[0] == '-')
		index = -1.0;
	if (ss[0] == '.')
		return false;
	int i = 0;
	for (; ss[i] != '\0'; i++) {
		if ((ss[i] > '9' || ss[i] < '0') && ss[i]!='.')
			return false;
		if (ss[i] == '.') {
			flag++;
			if (ss[i + 1] == '\0')
				return false;
			break;
		}
		num1 = num1 * 10 + ss[i] - '0';
	}
	double num2 = 0;
	i++;
	for (; ss[i] != '\0'; i++) {
		if ((ss[i] > '9' || ss[i] < '0') || ss[i] == '.')
			return false;
		num2 = num2 * 10 + ss[i] - '0';
	}
	while (num2 > 1)
		num2 = num2 / 10;
	double d = (num1 + num2) * index;
	memcpy(p, &d, sizeof(double));
	return true;
}


int main() {
	LQueue* Q = (LQueue*)malloc(sizeof(LQueue));
	Q->front = NULL;
	Q->rear = NULL;
	Q->length = 0;
	while (1) {
		printf("1.InitLQueue\n");
		printf("2.DestoryLQueue\n");
		printf("3.IsEmptyLQueue\n");
		printf("4.GetHeadLQueue\n");
		printf("5.LengthLQueue\n");
		printf("6.EnLQueue\n");
		printf("7.DeLQueue\n");
		printf("8.ClearLQueue\n");
		printf("9.TraverseLQueue\n");
		printf("10.exit\n");
		printf("please input the commend:\n");
		int commend = 0;
		char ch[1024] = "";
		while (1) {
			gets_s(ch);
			if (strlen(ch) == 1 && ch[0] > '0' && ch[0] < '9' + 2)
				break;
			printf("please input rigth commend\n");
		}
		commend = ch[0] - '0';
		system("cls");
		switch (commend) {
		//初始化
		case 1: {
			InitLQueue(Q);
			printf("initlqueue over\n");
			system("pause");
			break;
		}
		 //销毁
		case 2: {
			DestoryLQueue(Q);
			printf("destorylqueue over\n");
			system("pause");
			break;
		}
		//判空
		case 3: {
			Status s = IsEmptyLQueue(Q);
			printf("Status:%d\n", s);
			system("pause");
			break;
		}
		//获取队头
		case 4: {
			void* e =malloc(0);
			int s = GetHeadLQueue(Q, e);
			printf("the headlqueue is:\n");
			if (s != -1)
				LPrint(e, s);
			system("pause");
			break;
		}
		//队列长度
		case 5: {
			int len = LengthLQueue(Q);
			printf("the length of the lqueue is %d\n",len);
			system("pause");
			break;
		}
		//入队
		case 6: {
			void* data = malloc(0);
			int b = setType();
			int byte = 0;
			bool flag = false;
			while(!flag)
			{
				printf("please input data :\n");
				if (b == 1) {
					flag = setInt(data);
					byte = sizeof(int);
				}
				else if (b == 2) {
					flag = setChar(data);
					byte = sizeof(char);
				}
				else if (b == 3) {
					flag = setDouble(data);
					byte = sizeof(double);
				}
			}
			void* d = malloc(0);
			memcpy(d, data, byte);
			Status s = EnLQueue(Q, d,byte);
			printf("Status:%d\n", s);
			system("pause");
			break;
		}
		//出队
		case 7: {
			Status s = DeLQueue(Q);
			printf("Status:%d\n", s);
			system("pause");
			break;
		}
		//清空队列
		case 8: {
			ClearLQueue(Q);
			printf("clear the lqueue over\n");
			system("pause");
			break;
		}
		//遍历
		case 9: {			
			Status s = TraverseLQueue(Q, LPrint);
			printf("Status:%d\n", s);
			system("pause");
			break;
		}		
		//退出
		case 10: {
			exit(0);
		}
		}
		system("cls");
	}	
}