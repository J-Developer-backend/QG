#include<stdio.h>
#include<string.h>
#include "LinkStack.h"


//ջ����ջ,����ջ����ֵ
int pop(LinkStack* L) {
	if (isEmpty(L))
		return -1;
	ElemType data = -1;
	ElemType* e = &data;
	popStack(L, e);
	return *e;
}


char in[1024] = "";
//��ӡ����
bool printError() {
	printf("input data error\n---------------------------\n");
	return false;
}
//�������ݴ���
bool checkInput(char* s, ElemType* data) {
	//�ַ������̻����
	if (strlen(s) == 0 || strlen(s) > 11)
		return printError();
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
			return printError();
		//�ۼ����
		temp = temp * 10 + s[i] - '0';
	}
	//�жϷ�Χ�Ƿ����
	if (temp >= 2147483648 || temp < -2147483648)
		return printError();
	*data = (int)(temp * index);
	return true;
}

//ջ����
void testLinkStack() {
	//����ջ
	LinkStack* L = NULL;
	while(true){
		system("cls");
		printf("1.init linkstack\n");
		printf("2.isEmpyt\n");
		printf("3.getTopStack\n");
		printf("4.clearStack\n");
		printf("5.destoryStack\n");
		printf("6.stackLength\n");
		printf("7.putStack\n");
		printf("8.popStack\n");
		printf("9.back\n");
		int commend;
		int* p = &commend;
		do {
			printf("input the commend:\n");
			gets_s(in);
		} while (!checkInput(in, p));	
		system("cls");
		switch (commend) {
			//��ʼ��ջ
		case 1: {
			LinkStack** LL = &L;
			Status s = initStack(LL);
			printf("Status:%d\n", s);
			break;
		}
			  //�ж�ջ�Ƿ�Ϊ��
		case 2: {
			Status s = isEmpty(L);
			printf("Status:%d\n", s);
			break;
		}
			  //��ȡջ��Ԫ��
		case 3: {
			ElemType data = 0;
			ElemType* e = &data;
			stackLength(L, e);
			if (*e != 0) {
				getTopStack(L, e);
				printf("the topstack is %d\n", *e);
			}
			else
				printf("the stacklength is %d\n",*e);
			break;
		}
			  //���ջ
		case 4: {
			Status s = clearStack(L);
			printf("Status:%d\n", s);
			break;
		}
			  //����ջ
		case 5: {
			LinkStack** LL = &L;
			Status s = destoryStack(LL);
			printf("Status:%d\n", s);
			break;
		}
			  //��ȡջ�ĳ���
		case 6: {
			int length = 0;
			int* e = &length;
			Status s = stackLength(L, e);
			if (e != NULL)
			printf("Status:%d\nthe length is %d\n", s,*e);
			break;
		}
			  //��ջ
		case 7: {
			Status a = remindInit(L);
			if (!a) {
				int e = 0;
				int* q = &e;
				do {
					printf("input the push data\n");
					gets_s(in);
				} while (!checkInput(in, q));
				Status s = pushStack(L, *q);
				printf("Status:%d\n", s);
			}
			else
				printf("the linkstack is not inited\n");
			break;
		}
			  //��ջ
		case 8: {
			ElemType data = 0;
			ElemType* e = &data;
			stackLength(L, e);
			if (*e != 0) {
				Status s = popStack(L, e);
				printf("Status:%d\nthe popstack is %d\n",s , *e);
			}
			else
				printf("the stacklength is %d\n", *e);
			break;
		}
			  //����
		case 9: {
			return;
		}
		}
		system("pause");
	}
}

//�����ж�
bool isBracket(char s) {
	if (s == '(' || s == ')')
		return true;
	return false;
}

//����������ж�
bool isSymbol(char s) {
	char c[4] = { '+','-','*','/' };
	for (int i = 0; i < 4; i++) {
		if (s == c[i])
			return true;
	}
	return false;
}

//�����ж�
bool isNum(char s) {
	if (s >= '0' && s <= '9')
		return true;
	return false;
}

//�ַ���ת����
int toInt(char* s) {
	int num = 0;
	for (int i = 0; s[i] != '\0' && isNum(s[i]); i++) {
		num = num * 10 + s[i] - '0';
	}
	return num;
}

//����������ʽ���
bool checkS(char* s) {
	if (strlen(s) == 0) 
		return false;
	for (int i = 0, j = 0; s[i] != '\0'; i++) {
		if (s[i] == ' ' || isNum(s[i]) || isBracket(s[i]) || isSymbol(s[i]))
			continue;
		else 
			return false;
	}
	return true;
}

//����
int calculate(char s, int n, int m) {
	if (s == '+')
		return n + m;
	else if (s == '-')
		return n - m;
	else if (s == '*')
		return n * m;
	else if (s == '/')
		return n / m;
}

//�����������
void test() {
	system("cls");
	LinkStack* L = NULL;
	LinkStack** LL = &L;
	initStack(LL);
	char s[1024] = "";
	//�����
	char rule[6] = { '(','+','-','*','/',')' };
	//��ź�׺���ʽ
	char* ss[1024] = {NULL};
		do {
			printf("input the expression:\n");
			gets_s(s);
		} while (!checkS(s));
		ElemType data = -1;
		ElemType* e = &data;
		//��׺���ʽ����
		int k = 0;
		for (int i = 0; s[i] != '\0'; i++) {
			//���Կո�
			if (s[i] == ' ')
				continue;
			//��ֵ
			if (isNum(s[i])) {
				ss[k] = (char*)malloc(sizeof(char)*1024);
				for (int j = 0; s[i] != '\0';j++,i++) {
					if (s[i] == ' ')
						continue;
					if (isBracket(s[i]) || isSymbol(s[i])) {
						break;
					}
					ss[k][j] = s[i];
					ss[k][j+1] = '\0';
				}				
				i--;
				k++;
			}
			//����
			else {
				int loc = -1;
				for (int j = 0; j < 6; j++)
					if (rule[j] == s[i]) {
						loc = j;
						break;
					}						
				// (
				if (loc == 0) {
					pushStack(L,loc);
					continue;
				}
				// )
				else if (loc == 5) {
					int index;
					while (true) {
						index = pop(L);
						if (index == 0 || index == -1) {
							break;
						}
						ss[k] = (char*)malloc(sizeof(char) * 1024);
						ss[k][0] = rule[index];
						ss[k][1] = '\0';
						k++;
					}
					//�����쳣����
					if (index == -1) {
						printf("expression error, ) doesnot have a ( to set\n");
						system("pause");
						return;
					}
				}
				//+ - 
				else if(loc == 1 || loc == 2){
					int index ;
					while (true) {
						index = pop(L);
						if (index == 0 || index == -1 )
							break;
						ss[k] = (char*)malloc(sizeof(char) * 1024);
						ss[k][0] = rule[index];
						ss[k][1] = '\0';
						k++;
					}
					if (index == 0)
						pushStack(L, 0);
					pushStack(L, loc);
				}
				// *  /
				else {
					int index;
					while (true) {
						index = pop(L);
						if (index <3)
							break;
						ss[k] = (char*)malloc(sizeof(char) * 1024);
						ss[k][0] = rule[index];
						ss[k][1] = '\0';
						k++;
					}	
					pushStack(L, index);
					pushStack(L, loc);
				}
			}			
		}
		while (!isEmpty(L)) {
			popStack(L, e);
			ss[k] = (char*)malloc(sizeof(char) * 1024);
			ss[k][0] = rule[*e];
			ss[k][1] = '\0';
			k++;
		}
		printf("��׺���ʽ:\n"); 
		for (int i = 0; ss[i] != NULL; i++) 	
			printf("%s  ", ss[i]);		
		printf("\n");
		system("pause");
		for (int i = 0; ss[i] != NULL; i++) {
			//��ֵ��ջ
			if (isNum(ss[i][0])) {
				int num = toInt(ss[i]);
				pushStack(L, num);
			}
			//��������
			else if (isSymbol(ss[i][0])) {
				int p[2] = { 0,0 };
				for (int j = 0; j < 2; j++) {
					if (isEmpty(L)) {
						printf("expression error\n");
						system("pause");
						return;
					}
					popStack(L, e);
					p[j] = *e;
				}
				int rs = calculate(ss[i][0], p[1], p[0]);
				pushStack(L, rs);
			}
			//�����쳣
			else if(isBracket(ss[i][0])) {
				printf("( or ) erroe\n");
				system("pause");
				return;
			}		
		}
		if (isEmpty(L)) {
			printf("expression error\n");
			system("pause");
			return;
		}
		popStack(L, e);
		if (!isEmpty(L)) {
			printf("expression error\n");
			system("pause");
			return;
		}
		printf("���:%d\n", *e);
		system("pause");
}


int main() {
	while (true) {
		system("cls");
		printf("1.test linkstack\n");
		printf("2.test ����������ʽ��ֵ\n");
		printf("3.exit\n");
		int commend = 0;
		int* p = &commend;
		do {
			printf("input the commend:\n");
			gets_s(in);
		} while (!checkInput(in, p));
		system("cls");
		switch (*p) {
		
		case 1: {
			testLinkStack();
			break;
		}
		case 2: {
			test();
			break;
		}
		case 3: {
			exit(0);
		}
		}
	}
}