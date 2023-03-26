#pragma once
#include<stdio.h>
#include<stdlib.h>
/***************************************************************************************
 *    File Name                :    LQueue.h
 *    CopyRight                :
 *
 *    SYSTEM                    :   Mac OS
 *    Create Data                :    2020.4.2
 *    Author/Corportation        :   Chuan Shi
 *
 *
 *--------------------------------Revision History--------------------------------------
 *    No    version        Data            Revised By            Item            Description
 *
 *
 ***************************************************************************************/

 /**************************************************************
  *    Multi-Include-Prevent Section
  **************************************************************/
#ifndef LQUEUE_H_INCLUDED
#define LQUEUE_H_INCLUDED

  /**************************************************************
   *    Struct Define Section
   **************************************************************/
   //��ʽ���нṹ
typedef struct node
{
    void* data;                   //������ָ��
    struct node* next;            //ָ��ǰ������һ���
    int byte;
} Node;

typedef struct Lqueue
{
    Node* front;                   //��ͷ
    Node* rear;                    //��β
    size_t length;            //���г���
} LQueue;

typedef enum
{
    FALSE = 0, TRUE = 1
} Status;
char type;
char datatype[30];

/**************************************************************
 *    Prototype Declare Section
 **************************************************************/


 /**
  *  @name        : void InitLQueue(LQueue *Q)
  *    @description : ��ʼ������
  *    @param         Q ����ָ��Q
  *  @notice      : None
  */
void InitLQueue(LQueue* Q) {
    if (Q == NULL)
        return;
    //ͷ�ڵ�
    Node* p = (Node*)malloc(sizeof(Node));
    p->next = NULL;
    Q->front = p;
    Q->rear = p;
    Q->length = 0;
};

/**
 *  @name        : void DestoryLQueue(LQueue *Q)
 *    @description : ���ٶ���
 *    @param         Q ����ָ��Q
 *  @notice      : None
 */
void DestoryLQueue(LQueue* Q) {
    //δ��ʼ��
    if (Q->front == NULL) {
        printf("the lqueue is not inited\n");
        return;
    }
       //���
    Node* p = Q->front->next;
    while (p != NULL) {
        Node* t = p->next;
        free(p);
        p = t; 
    }
    //����ͷ�ڵ�
    p = Q->front;
    free(p);
    Q->front = NULL;
    Q->rear = NULL;
    Q->length = 0;
};

/**
 *  @name        : Status IsEmptyLQueue(const LQueue *Q)
 *    @description : �������Ƿ�Ϊ��
 *    @param         Q ����ָ��Q
 *    @return         : ��-TRUE; δ��-FALSE
 *  @notice      : None
 */
Status IsEmptyLQueue(const LQueue* Q) {
    //δ��ʼ��
    if (Q->front == NULL && Q->rear == NULL)
    {
        printf("the lqueue is not inited\n");
        return FALSE;
    }
    return (Q->front == Q->rear) ? TRUE : FALSE;
};

/**
 *  @name        : Status GetHeadLQueue(LQueue *Q, void *e)
 *    @description : �鿴��ͷԪ��
 *    @param         Q e ����ָ��Q,��������ָ��e
 *    @return         : �ɹ�-TRUE; ʧ��-FALSE
 *  @notice      : �����Ƿ��
 */
size_t GetHeadLQueue(LQueue* Q, void* e) {
    //δ��ʼ��
    if (Q->front == NULL && Q->rear == NULL) {
        printf("the lqueue is not inited\n");
        return -1;
    }
    //�ն���
    if (Q->front->next == NULL) {
        printf("the lqueue is empty\n");
        return -1;
    }
    //��ͷ
    Node* p = Q->front->next;
    memcpy(e, p->data, p->byte);
    return p->byte;
};

/**
 *  @name        : int LengthLQueue(LQueue *Q)
 *    @description : ȷ�����г���
 *    @param         Q ����ָ��Q
 *    @return         : �ɹ�-TRUE; ʧ��-FALSE
 *  @notice      : None
 */
int LengthLQueue(LQueue* Q) {  
    //δ��ʼ��
    if (Q->front == NULL && Q->rear == NULL) {
        printf("the lqueue is not inited\n");
        return 0;
    }
    return Q->length;
};

/**
 *  @name        : Status EnLQueue(LQueue *Q, void *data)
 *    @description : ��Ӳ���
 *    @param         Q ����ָ��Q,�������ָ��data
 *    @return         : �ɹ�-TRUE; ʧ��-FALSE
 *  @notice      : �����Ƿ�Ϊ��
 */
Status EnLQueue(LQueue* Q, void* data,int byte) { 
    //δ��ʼ��
    if (Q->front == NULL) {
        printf("the lqueue is not inited\n");
        return FALSE;
    }
    Node* p = (Node*)malloc(sizeof(Node));
    if (p == NULL)
        return FALSE;
    p->next = NULL;
    p->data = (void *)malloc(byte);
    memcpy(p->data, data, byte);
    p->byte = byte;
    //�ն���
    if (Q->front->next == NULL) {
        Q->front->next = p;
        Q->rear = p;
    }
    //�ǿ�
    else {
        Q->rear->next = p;
        Q->rear = p;
    }
    Q->length++;
    return TRUE;
};

/**
 *  @name        : Status DeLQueue(LQueue *Q)
 *    @description : ���Ӳ���
 *    @param         Q ����ָ��Q
 *    @return         : �ɹ�-TRUE; ʧ��-FALSE
 *  @notice      : None
 */
Status DeLQueue(LQueue* Q) {  
    //�ѳ�ʼ��
    if (Q->front != NULL) {
        Node* p = Q->front;
        if (p->next != NULL) {
            //ֻ��һ���ڵ�
            if (Q->rear == p->next) {
                p->next = NULL;
                Q->rear = p; 
                free(p->next);             
            }
            //�ж���ڵ�
            else {
                Node* t = p->next;
                p->next = t->next;
                free(t);
            }
            Q->length--;
            return TRUE;
        }
        //�ն���
        else {
            printf("the lqueue is empty\n");
            return FALSE;
        }      
    }
    //δ��ʼ��
    else {
        printf("the lqueue is not inited\n");
        return FALSE;
    }
};

/**
 *  @name        : void ClearLQueue(AQueue *Q)
 *    @description : ��ն���
 *    @param         Q ����ָ��Q
 *  @notice      : None
 */
void ClearLQueue(LQueue* Q) {
    //δ��ʼ��
    if (Q->front == NULL) {
        printf("the lqueue is not inited\n");
        return;
    }
    //�ն���
    if (Q->front->next == NULL) {
        printf("the lqueue is empty\n");
        return;
    }
    //���
    Node* p = Q->front->next;
    while (p != NULL) {
        Node* t = p->next;
        free(p);
        p = t;
    }
    Q->front->next = NULL;  
    Q->rear = Q->front;
    Q->length = 0;
};

/**
 *  @name        : Status TraverseLQueue(const LQueue *Q, void (*foo)(void *q))
 *    @description : ������������
 *    @param         Q ����ָ��Q����������ָ��foo
 *    @return         : None
 *  @notice      : None
 */
Status TraverseLQueue(const LQueue* Q, void (*foo)(void* q,int byte)) {
    //δ��ʼ��
    if (Q->front == NULL ) {
        printf("the lqueue is not inited\n");
        return FALSE;
    }
    //�ն���
    if (Q->front->next == NULL) {
        printf("the lqueue is empty\n");
        return FALSE;
    }
    //����
    Node* p = Q->front->next;
    while (p != NULL) {
        Node* t = p->next;
        foo(p->data,p->byte);
        p = t;
    }
};

/**
 *  @name        : void LPrint(void *q)
 *    @description : ��������
 *    @param         q ָ��q

 *  @notice      : None
 */
void LPrint(void* q,int byte) {
    //���������
    if (byte == sizeof(int)) {
        printf("%d\n", *(int*)q);
    }
    else if (byte == sizeof(double)) {
        printf("%.10lf\n", *(double*)q);
    }
    else if (byte == sizeof(char)) {
        printf("%c\n", *(char*)q);
    }
   

};

/**************************************************************
 *    End-Multi-Include-Prevent Section
 **************************************************************/
#endif; // LQUEUE_H_INCLUDED

