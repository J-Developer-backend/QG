#include<stdio.h>
#include<string.h>
#include "Linkedlist.h"
//遍历链表是调用的打印函数
void visit(ElemType e) {
	printf("%d->", e);
}
//返回链表中对应data的节点
LNode* findList(LinkedList L,ElemType data) {
	if (L == NULL)
		return NULL;
	LNode* p = L->next;
	while (p->data != data) {
		p = p->next;
	}
	if (p->data == data)
		return p;
	else
		return NULL;
}
//打印错误
bool printError() {
	printf("----------------------------\ninput data error\n");
	return false;
}
//输入数据处理
bool checkInput(char* s, ElemType* data) {
	//字符串过短或过长
	if (strlen(s) == 0 || strlen(s) > 11)
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
	*data = (int)(temp * index);
	return true;
}

int main() {
	char s[1024] = "";
	LinkedList head = NULL;
	LinkedList* L = &head ;
	ElemType data;
	ElemType* DATA = &data;
	LNode* p = NULL;
	void (*V)(ElemType e) = &visit;
	bool flag = true;
	while (true) {
		//函数测试菜单
		printf("1.InitList\n2.DestroyList\n3.InsertList\n4.DeleteList\n5.TraverseList\n");
		printf("6.SearchList\n7.ReverseList\n8.IsLoopList\n9.ReverseEvenList\n10.FindMidNode\n11.exit\n");
		gets_s(s);
		flag = checkInput(s, DATA);
		printf("-----------------------------------------------\n");
		if(flag)
		switch (data) {
			//InitList函数测试
		case 1:
			printf("\tInitList\n");
			printf("Status:%d\tInitList\n",InitList(L));
			break;
			//DestroyList函数测试
		case 2:
			printf("\tDestroyList\n");
			DestroyList(L);
			printf("Status:1\tDestroyList\n" );
			break;
			//InsertList函数测试
		case 3:
		{
			printf("\tInsertList\n");
			//初始化判断
			if (head == NULL) {
				printf("list is not inited\n");
				break;

			}		
			printf("input the node that you want to insert after\n");
			//输入节点，在该节点后面插入
			do{
				gets_s(s);
			} while (!checkInput(s, DATA));
			if (head->next != NULL) {
				//节点存在性判断
				if (SearchList(head, data)) {
					p = findList(head, data);
					printf("input the node you want to insert\n");
					//输入要插入的节点
					do {
						gets_s(s);
					} while (!checkInput(s, DATA));

				}		
				else {
					printf("cannot find the node\n");
					break;
				}
			}
			else
				p = head;	
			//封装新节点
			LNode* q = (LNode*)malloc(sizeof(LNode));
			q->data = data;
			q->next = NULL;
			printf("Status:%d\tInsertList\n", InsertList(p, q));
			TraverseList(head, V);
			printf("\n");
			break;
		}
			//DeleteList函数测试
		case 4:
		{
			printf("\tDeleteList\n");
			printf("input the node that you want to delete before\n");
			do {
				gets_s(s);
			} while (!checkInput(s, DATA));
			//输入节点的存在性判断
			if (SearchList(head, data))
				p = findList(head, data);
			else {
				printf("cannot find the node\n");
				break;
			}
			ElemType* e = &data;
			printf("Status:%d\tDelete:ist\tdeleteNode:%d\n", DeleteList(p, e), *e);
			break;
		}
			//TraverseList函数测试
		case 5:
			printf("\tTraversList\n");
			TraverseList(head, V);
			printf("\n");
			break;
			//SearchList函数测试
		case 6:
			printf("\tSearchList\n");
			printf("input the node you want to search\n");
			do {
				gets_s(s);
			} while (!checkInput(s, DATA));

			printf("Status:%d\tSearchList\n", SearchList(head, data));
			break;
			//ReverseEvenList函数测试
		case 7:
			printf("\tReverseEvenList\n");
			ReverseList(L);
			head = *L;
			TraverseList(head, V);
			break;
			//IsLoopList函数测试
		case 8:
			printf("\tIsLoopList\n");
			printf("Status:%d\tIsLoopList\n", IsLoopList(head));
			break;
			//ReverseEvenList函数测试
		case 9:
			printf("\tReverseEvenList\n");
			head = ReverseEvenList(L);
			TraverseList(head, V);
			break;
			//FindMidNode函数测试
		case 10:
		{
			printf("\tFindMidNode\n");
			p = FindMidNode(L);
			if (p == NULL) {
				printf("the linkedlist is not inited\n");
				break;
			}
			printf("Status:1\tFindMidList\tMidList:%d\n", p->data);
			TraverseList(head, V);
			break;
		}
			//退出
		case 11:
			exit(0);
			break;
			//命令出错
		default:
			printf("the commender error\n");
		}
		printf("-----------------------------------------------\n");
	}
}