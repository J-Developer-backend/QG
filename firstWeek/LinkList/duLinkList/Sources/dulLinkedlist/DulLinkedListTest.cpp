#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "dulLinkedList.h"
//��������ʱ���������
void visit(ElemType e) {
	printf("%d->", e);

}
//���������ж�Ӧ�ڵ��ָ��
DuLNode* findNode(DuLinkedList L,ElemType e) {

	if (L == NULL || L->next == NULL)
		return NULL;
	DuLNode* p = L->next;
	while (p != NULL && p->data != e)
		p = p->next;
	if (p == NULL)
		return NULL;
	return p;
}
//��ӡ����
bool printError() {
	printf("----------------------------\ninput data error\n");
		return false;
}
//�������ݴ���
bool checkInput(char* s,ElemType* data) {
	//�ַ������̻����
	if (strlen(s) == 0 || strlen(s)>11)
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
	*data = (int)(temp*index);
	return true;
}
int main() {
	char s[1024] = "";
	DuLNode* head = NULL;
	DuLinkedList* L = &head;
	DuLNode* p = NULL;
	ElemType data;
	ElemType* DATA = &data;
	void (*V)(ElemType e) = &visit;
	bool flag = true;
	while (true) {
		//�˵��б�
		printf("1.InitList_DuL\n2.DestroyList_DuL\n3.InsertBeforeList_DuL\n");
		printf("4.InsertAfterList_DuL\n5.DeleteList_DuL\n6.TraverseList_DuL\n7.exit\n");
		gets_s(s);
		flag = checkInput(s, DATA);
		printf("----------------------------------------------------\n");
		if (flag)
		switch (data) {
			//InitList_DuL��������
		case 1:
			printf("\tInitList_DuL\n");
			printf("Status:%d\tInitList_DuL\n", InitList_DuL(L));
			head = *L;
			break;
			//DestroyList_DuL��������
		case 2:
			printf("\tDestroyList_DuL\n");
			DestroyList_DuL(L);
			printf("Status:1\tDestroyList_DuL\n");
			break;
			//InsertBefore_DuL��������
		case 3:
		{
			printf("\tInsertBeforeList_DuL\n");
			//�����ʼ���ж�
			if (head == NULL) {
				printf("the dullinkedlist is not inited\n");
				break;
			}
			printf("input the node that you want to insert a node on its front\n");
			//����ڵ㣬�ڸýڵ�ǰ�����ڵ�
			do {
				gets_s(s);
			} while (!checkInput(s, DATA));
			//������Ϊ0�����
			if (head == NULL || head->next == NULL) {
				p = (DuLNode*)malloc(sizeof(DuLNode));
				p->data = data;
				p->next = NULL;
				p->prior = head;
				head->next = p;
				printf("insert success\n");
				break;
			}
			//����ڵ�Ĵ������ж�
			if ((p = findNode(head, data)) != NULL) {
				printf("input the node that you want to insert \n");
				//�����½ڵ�
				do {
					gets_s(s);
				} while (!checkInput(s, DATA));
				//��װ�½ڵ�
				DuLNode* q  = (DuLNode*)malloc(sizeof(DuLNode));
				q->data = data;
				q->next = NULL;
				q->prior = NULL;
				printf("Status:%d\tInsertBeforList\n",InsertBeforeList_DuL(p, q));
			}
			else {
				
				printf("cannot find the note\n");
			}				
			break;
		}
			//InsertAfterList_DuL��������
		case 4:
		{
			printf("\tInsertAfterList_DuL\n");
			//�����ʼ���ж�
			if (head == NULL) {
				printf("the dullinkedlist is not inited\n");
				break;
			}
			printf("input the node that you want to insert a node on its back\n");
			//����ڵ㣬�ڸýڵ��������½ڵ�
			do {
				gets_s(s);
			} while (!checkInput(s, DATA));
			//������Ϊ0�����
			if (head == NULL || head->next == NULL) {
				//��װ�ڵ�
				p = (DuLNode*)malloc(sizeof(DuLNode));
				p->data = data;
				p->next = NULL;
				p->prior = head;
				head->next = p;
				printf("insert success\n");
				break;
			}
			//����ڵ�������ж�
			if ((p = findNode(head, data)) != NULL) {
				printf("input the node that you want to insert \n");
				//�����½ڵ�
				do {
					gets_s(s);
				} while (!checkInput(s, DATA));
				//��װ�½ڵ�
				DuLNode* q = (DuLNode*)malloc(sizeof(DuLNode));
				q->data = data;
				q->next = NULL;
				q->prior = NULL;
				printf("Status:%d\tInsertAfterList_DuL\n", InsertAfterList_DuL(p, q));
			}
			else
				printf("cannot find the note\n");
			break;
		}
			//DeleteList_DuL��������
		case 5:
			printf("\tDeleteList_DuL\n");
			printf("input the node that you want to delete before\n");
			//����ڵ㣬ɾ���ýڵ����ĵ�һ���ڵ�
			do {
				gets_s(s);
			} while (!checkInput(s, DATA));
			//�ڵ�������ж�
			if ((p = findNode(head, data)) != NULL) {
				ElemType* e = &data;
				printf("Status:%d\tDeleteList_DuL\tDeleteNode:%d\n",DeleteList_DuL(p,e),*e);
			}
			else
				printf("cannot find the note\n");
			break;
			//TraverseList_DuL��������
		case 6:
			printf("\tTraverseList_DuL\n");
			TraverseList_DuL(head, V);
			break;
			//�˳�����
		case 7:
			exit(0);
			//ָ���쳣����
		default :
			printf("the commender error\n");
		}
		printf("----------------------------------------------------\n");
	}
}