#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "dulLinkedList.h"
//遍历链表时的输出函数
void visit(ElemType e) {
	printf("%d->", e);

}
//返回链表中对应节点的指针
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
//打印错误
bool printError() {
	printf("----------------------------\ninput data error\n");
		return false;
}
//输入数据处理
bool checkInput(char* s,ElemType* data) {
	//字符串过短或过长
	if (strlen(s) == 0 || strlen(s)>11)
		return printError();
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
			return printError();
		//累计求和
		temp = temp * 10 + s[i] - '0';
	}
	//判断范围是否合理
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
		//菜单列表
		printf("1.InitList_DuL\n2.DestroyList_DuL\n3.InsertBeforeList_DuL\n");
		printf("4.InsertAfterList_DuL\n5.DeleteList_DuL\n6.TraverseList_DuL\n7.exit\n");
		gets_s(s);
		flag = checkInput(s, DATA);
		printf("----------------------------------------------------\n");
		if (flag)
		switch (data) {
			//InitList_DuL函数测试
		case 1:
			printf("\tInitList_DuL\n");
			printf("Status:%d\tInitList_DuL\n", InitList_DuL(L));
			head = *L;
			break;
			//DestroyList_DuL函数测试
		case 2:
			printf("\tDestroyList_DuL\n");
			DestroyList_DuL(L);
			printf("Status:1\tDestroyList_DuL\n");
			break;
			//InsertBefore_DuL函数测试
		case 3:
		{
			printf("\tInsertBeforeList_DuL\n");
			//链表初始化判断
			if (head == NULL) {
				printf("the dullinkedlist is not inited\n");
				break;
			}
			printf("input the node that you want to insert a node on its front\n");
			//输入节点，在该节点前面插入节点
			do {
				gets_s(s);
			} while (!checkInput(s, DATA));
			//链表长度为0的情况
			if (head == NULL || head->next == NULL) {
				p = (DuLNode*)malloc(sizeof(DuLNode));
				p->data = data;
				p->next = NULL;
				p->prior = head;
				head->next = p;
				printf("insert success\n");
				break;
			}
			//输入节点的存在性判断
			if ((p = findNode(head, data)) != NULL) {
				printf("input the node that you want to insert \n");
				//输入新节点
				do {
					gets_s(s);
				} while (!checkInput(s, DATA));
				//封装新节点
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
			//InsertAfterList_DuL函数测试
		case 4:
		{
			printf("\tInsertAfterList_DuL\n");
			//链表初始化判断
			if (head == NULL) {
				printf("the dullinkedlist is not inited\n");
				break;
			}
			printf("input the node that you want to insert a node on its back\n");
			//输入节点，在该节点后面插入新节点
			do {
				gets_s(s);
			} while (!checkInput(s, DATA));
			//链表长度为0的情况
			if (head == NULL || head->next == NULL) {
				//封装节点
				p = (DuLNode*)malloc(sizeof(DuLNode));
				p->data = data;
				p->next = NULL;
				p->prior = head;
				head->next = p;
				printf("insert success\n");
				break;
			}
			//输入节点存在性判断
			if ((p = findNode(head, data)) != NULL) {
				printf("input the node that you want to insert \n");
				//输入新节点
				do {
					gets_s(s);
				} while (!checkInput(s, DATA));
				//封装新节点
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
			//DeleteList_DuL函数测试
		case 5:
			printf("\tDeleteList_DuL\n");
			printf("input the node that you want to delete before\n");
			//输入节点，删除该节点后面的第一个节点
			do {
				gets_s(s);
			} while (!checkInput(s, DATA));
			//节点存在性判断
			if ((p = findNode(head, data)) != NULL) {
				ElemType* e = &data;
				printf("Status:%d\tDeleteList_DuL\tDeleteNode:%d\n",DeleteList_DuL(p,e),*e);
			}
			else
				printf("cannot find the note\n");
			break;
			//TraverseList_DuL函数测试
		case 6:
			printf("\tTraverseList_DuL\n");
			TraverseList_DuL(head, V);
			break;
			//退出测试
		case 7:
			exit(0);
			//指令异常处理
		default :
			printf("the commender error\n");
		}
		printf("----------------------------------------------------\n");
	}
}