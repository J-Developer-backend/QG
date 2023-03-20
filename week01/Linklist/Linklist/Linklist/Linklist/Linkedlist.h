#pragma once
#include<stdlib.h>
#include<stdio.h>
/***************************************************************************************
 *	File Name				:	linkedList.h
 *	CopyRight				:	2020 QG Studio
 *	SYSTEM					:   win10
 *	Create Data				:	2020.3.28
 *
 *
 *--------------------------------Revision History--------------------------------------
 *	No	version		Data			Revised By			Item			Description
 *
 *
 ***************************************************************************************/

 /**************************************************************
*	Multi-Include-Prevent Section
**************************************************************/
#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED

/**************************************************************
*	Macro Define Section
**************************************************************/

#define OVERFLOW -1

/**************************************************************
*	Struct Define Section
**************************************************************/

// define element type
typedef int ElemType;

// define struct of linked list
typedef struct LNode {
	ElemType data;
	struct LNode* next;
} LNode, * LinkedList;

// define Status
typedef enum Status {
	ERROR,
	SUCCESS

} Status;


/**************************************************************
*	Prototype Declare Section
**************************************************************/

/**
 *  @name        : Status InitList(LinkList *L);
 *	@description : initialize an empty linked list with only the head node without value
 *	@param		 : L(the head node)
 *	@return		 : Status
 *  @notice      : None
 */
Status InitList(LinkedList* L) {
	LinkedList p = (LinkedList)malloc(sizeof(LNode));		//创建头节点
	p->next = NULL;
	*L = p;
	return SUCCESS;
};

/**
 *  @name        : void DestroyList(LinkedList *L)
 *	@description : destroy a linked list, free all the nodes
 *	@param		 : L(the head node)
 *	@return		 : None
 *  @notice      : None
 */
void DestroyList(LinkedList* L) {
	if ((*L) == NULL || (*L)->next == NULL)
		return;
	LNode* p1 = (*L)->next;
	LNode* p2 = NULL;
	while (p1 != NULL) {							
		p2 = p1->next;
		free(p1);						//逐个删除
		p1 = p2;
	}
	(*L)->next = NULL;
};

/**
 *  @name        : Status InsertList(LNode *p, LNode *q)
 *	@description : insert node q after node p
 *	@param		 : p, q
 *	@return		 : Status
 *  @notice      : None
 */
Status InsertList(LNode* p, LNode* q) {
	if (p == NULL)
		return ERROR;
	LNode* nextNode = p->next;			//记录p下一个节点
	p->next = q;							//插入q节点
	q->next = nextNode;					
	return SUCCESS;
};

/**
 *  @name        : Status DeleteList(LNode *p, ElemType *e)
 *	@description : delete the first node after the node p and assign its value to e
 *	@param		 : p, e
 *	@return		 : Status
 *  @notice      : None
 */
Status DeleteList(LNode* p, ElemType* e) {
	if (p == NULL)
		return ERROR;
	LNode* p1 = p->next;
	//记录数据
	*e = p1->data;
	p->next = p1->next;
	//删除节点
	free(p1);
	return SUCCESS;
};

/**
 *  @name        : void TraverseList(LinkedList L, void (*visit)(ElemType e))
 *	@description : traverse the linked list and call the funtion visit
 *	@param		 : L(the head node), visit
 *	@return		 : None
 *  @notice      : None
 */
void TraverseList(LinkedList L, void (*visit)(ElemType e)) {
	if (L == NULL || L->next == NULL)
		return;
	LinkedList p1 = L->next;
	while (p1 != NULL) {
		//调用visit指向的函数
		visit(p1->data);					
		p1 = p1->next;
	}
	printf("\n");
};
/**
 *  @name        : Status SearchList(LinkedList L, ElemType e)
 *	@description : find the first node in the linked list according to e
 *	@param		 : L(the head node), e
 *	@return		 : Status
 *  @notice      : None
 */
Status SearchList(LinkedList L, ElemType e) {
	if (L == NULL || L->next == NULL)
		return ERROR;
	LNode* p1 = L->next;
	while (p1 != NULL && p1->data != e) {
		p1 = p1->next;
	}
	if (p1 == NULL)
		return ERROR;
	return SUCCESS;
};
/**
 *  @name        : Status ReverseList(LinkedList *L)
 *	@description : reverse the linked list
 *	@param		 : L(the head node)
 *	@return		 : Status
 *  @notice      : None
 */
Status ReverseList(LinkedList* L ) {
	if ((*L) == NULL || (*L)->next == NULL)
		return ERROR;
	//l1 , l2 为相邻节点， l3 为辅助节点
	LNode* l1 = (*L)->next;
	if (l1->next == NULL)
		return ERROR;
	LNode* l2 = l1->next;
	l1->next = NULL;
	LNode* l3 = NULL;
	while (l2 != NULL) {
		l3 = l2->next;
		//反转
		l2->next = l1;
		//移动l1
		l1 = l2;
		//移动l2
		l2 = l3;
	}
	(*L)->next = l1;
	return SUCCESS;
};
/**
 *  @name        : Status IsLoopList(LinkedList L)
 *	@description : judge whether the linked list is looped
 *	@param		 : L(the head node)
 *	@return		 : Status
 *  @notice      : None
 */
Status IsLoopList(LinkedList L) {

	if (L == NULL || L->next == NULL)
		return ERROR;
	//慢指针
	LNode* p1 = L;
	//快指针
	LNode* p2 = L->next;
	while (p2!=NULL && p2->next != NULL && p1 != p2) {
		p1 = p1->next;
		p2 = p2->next->next;
	}
	if (p2 == NULL || p2->next == NULL)
		return ERROR;
	return SUCCESS;

};
/**
 *  @name        : LNode* ReverseEvenList(LinkedList *L)
 *	@description : reverse the nodes which value is an even number in the linked list, input: 1 -> 2 -> 3 -> 4  output: 2 -> 1 -> 4 -> 3
 *	@param		 : L(the head node)
 *	@return		 : LNode(the new head node)
 *  @notice      : choose to finish
 */
LNode* ReverseEvenList(LinkedList* L) {
	if ((*L) == NULL || (*L)->next == NULL)
		return NULL;
	//新头节点
	LNode* newHead = (LNode*)malloc(sizeof(LNode));
	newHead->next = NULL;
	//每两个节点为一组
	LNode* p1 = (*L)->next;
	LNode* p2 = p1->next;
	LNode* p3 = newHead;
	while (p2 != NULL ) {
		LNode* n1 = (LNode*)malloc(sizeof(LNode));
		LNode* n2 = (LNode*)malloc(sizeof(LNode));
		p3->next = n1;
		n1->data = p2->data;
		n1->next = n2;
		n2->data = p1->data;
		n2->next = NULL;
		p3 = n2;
		if (p2->next == NULL)
			break;
		p1 = p2->next;
		p2 = p2->next->next;
	}
	//奇链表处理
	if (p2 == NULL) {
		LNode* n = (LNode*)malloc(sizeof(LNode));
		n->data = p1->data;
		n->next = NULL;
		p3->next = n;
	}
	return newHead;
};

/**
 *  @name        : LNode* FindMidNode(LinkedList *L)
 *	@description : find the middle node in the linked list
 *	@param		 : L(the head node)
 *	@return		 : LNode
 *  @notice      : choose to finish
 */
LNode* FindMidNode(LinkedList* L) {
	if ((*L) == NULL || (*L)->next == NULL)
		return NULL;
	//慢指针
	LNode* p1 = (*L)->next;
	//快指针
	LNode* p2 = p1->next;
	while (p2 != NULL && p2->next!=NULL) {
		p1 = p1->next;
		p2 = p2->next->next;
	}
	return p1;
};

/**************************************************************
*	End-Multi-Include-Prevent Section
**************************************************************/
#endif
