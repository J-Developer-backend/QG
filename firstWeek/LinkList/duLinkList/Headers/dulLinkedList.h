#pragma once
#include<stdlib.h>
/***************************************************************************************
 *	File Name				:	duLinkedList.h
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

#ifndef DULINKEDLIST_H_INCLUDED
#define DULINKEDLIST_H_INCLUDED

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
typedef struct DuLNode {
	ElemType data;
	struct DuLNode* prior, * next;
} DuLNode, * DuLinkedList;

// define status
typedef enum Status {
	ERROR,
	SUCCESS,
} Status;


/**************************************************************
*	Prototype Declare Section
**************************************************************/

/**
 *  @name        : Status InitList_DuL(DuLinkedList *L)
 *	@description : initialize an empty linked list with only the head node
 *	@param		 : L(the head node)
 *	@return		 : Status
 *  @notice      : None
 */
Status InitList_DuL(DuLinkedList* L) {
	DuLinkedList p = (DuLinkedList)malloc(sizeof(DuLNode));
	if (p == NULL)
		return ERROR;
	p->next = NULL;
	p->prior = NULL;
	*L = p;
	return SUCCESS;
};

/**
 *  @name        : void DestroyList_DuL(DuLinkedList *L)
 *	@description : destroy a linked list
 *	@param		 : L(the head node)
 *	@return		 : status
 *  @notice      : None
 */
void DestroyList_DuL(DuLinkedList* L) {
	if (*L == NULL || (*L)->next == NULL)
		return;
	DuLNode* p1 = (*L)->next;
	DuLNode* p2 = NULL;
	while (p1 != NULL) {
		p2 = p1->next;
		free(p1);
		p1 = p2;
	}
	(*L)->prior = NULL;
	(*L)->next = NULL;
};

/**
 *  @name        : Status InsertBeforeList_DuL(DuLNode *p, LNode *q)
 *	@description : insert node q before node p
 *	@param		 : p, q
 *	@return		 : status
 *  @notice      : None
 */
Status InsertBeforeList_DuL(DuLNode* p, DuLNode* q) {
	if (p == NULL)
		return ERROR;
	DuLNode* prior = p->prior;
	prior->next = q;
	q->prior = prior;
	q->next = p;
	p->prior = q;
	return SUCCESS;
};

/**
 *  @name        : Status InsertAfterList_DuL(DuLNode *p, DuLNode *q)
 *	@description : insert node q after node p
 *	@param		 : p, q
 *	@return		 : status
 *  @notice      : None
 */
Status InsertAfterList_DuL(DuLNode* p, DuLNode* q) {
	if (p == NULL)
		return ERROR;
	DuLNode* next = p->next;
	if(next!=NULL)
	next->prior = q;
	q->next = next;
	q->prior = p;
	p->next = q;
	return SUCCESS;
};

/**
 *  @name        : Status DeleteList_DuL(DuLNode *p, ElemType *e)
 *	@description : delete the first node after the node p and assign its value to e
 *	@param		 : p, e
 *	@return		 : status
 *  @notice      : None
 */
Status DeleteList_DuL(DuLNode* p, ElemType* e) {
	if (p == NULL || p->next==NULL)
		return ERROR;
	DuLNode* q = p->next->next;
	DuLNode* deletedNode = p->next;
	p->next = q;
	if(q!=NULL)
	q->prior = p;
	*e = deletedNode->data;
	free(deletedNode);
	return SUCCESS;
};
/**
 *  @name        : void TraverseList_DuL(DuLinkedList L, void (*visit)(ElemType e))
 *	@description : traverse the linked list and call the funtion visit
 *	@param		 : L(the head node), visit
 *	@return		 : Status
 *  @notice      : None
 */
void TraverseList_DuL(DuLinkedList L, void (*visit)(ElemType e)) {
	if (L == NULL || L->next == NULL)
		return;
	DuLNode* p = L->next;
	while (p != NULL) {
		visit(p->data);
		p = p->next;
	
	}
	printf("\n");
};
/**************************************************************
*	End-Multi-Include-Prevent Section
**************************************************************/
#endif

