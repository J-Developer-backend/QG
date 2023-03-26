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
   //链式队列结构
typedef struct node
{
    void* data;                   //数据域指针
    struct node* next;            //指向当前结点的下一结点
    int byte;
} Node;

typedef struct Lqueue
{
    Node* front;                   //队头
    Node* rear;                    //队尾
    size_t length;            //队列长度
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
  *    @description : 初始化队列
  *    @param         Q 队列指针Q
  *  @notice      : None
  */
void InitLQueue(LQueue* Q) {
    if (Q == NULL)
        return;
    //头节点
    Node* p = (Node*)malloc(sizeof(Node));
    p->next = NULL;
    Q->front = p;
    Q->rear = p;
    Q->length = 0;
};

/**
 *  @name        : void DestoryLQueue(LQueue *Q)
 *    @description : 销毁队列
 *    @param         Q 队列指针Q
 *  @notice      : None
 */
void DestoryLQueue(LQueue* Q) {
    //未初始化
    if (Q->front == NULL) {
        printf("the lqueue is not inited\n");
        return;
    }
       //清空
    Node* p = Q->front->next;
    while (p != NULL) {
        Node* t = p->next;
        free(p);
        p = t; 
    }
    //销毁头节点
    p = Q->front;
    free(p);
    Q->front = NULL;
    Q->rear = NULL;
    Q->length = 0;
};

/**
 *  @name        : Status IsEmptyLQueue(const LQueue *Q)
 *    @description : 检查队列是否为空
 *    @param         Q 队列指针Q
 *    @return         : 空-TRUE; 未空-FALSE
 *  @notice      : None
 */
Status IsEmptyLQueue(const LQueue* Q) {
    //未初始化
    if (Q->front == NULL && Q->rear == NULL)
    {
        printf("the lqueue is not inited\n");
        return FALSE;
    }
    return (Q->front == Q->rear) ? TRUE : FALSE;
};

/**
 *  @name        : Status GetHeadLQueue(LQueue *Q, void *e)
 *    @description : 查看队头元素
 *    @param         Q e 队列指针Q,返回数据指针e
 *    @return         : 成功-TRUE; 失败-FALSE
 *  @notice      : 队列是否空
 */
size_t GetHeadLQueue(LQueue* Q, void* e) {
    //未初始化
    if (Q->front == NULL && Q->rear == NULL) {
        printf("the lqueue is not inited\n");
        return -1;
    }
    //空队列
    if (Q->front->next == NULL) {
        printf("the lqueue is empty\n");
        return -1;
    }
    //队头
    Node* p = Q->front->next;
    memcpy(e, p->data, p->byte);
    return p->byte;
};

/**
 *  @name        : int LengthLQueue(LQueue *Q)
 *    @description : 确定队列长度
 *    @param         Q 队列指针Q
 *    @return         : 成功-TRUE; 失败-FALSE
 *  @notice      : None
 */
int LengthLQueue(LQueue* Q) {  
    //未初始化
    if (Q->front == NULL && Q->rear == NULL) {
        printf("the lqueue is not inited\n");
        return 0;
    }
    return Q->length;
};

/**
 *  @name        : Status EnLQueue(LQueue *Q, void *data)
 *    @description : 入队操作
 *    @param         Q 队列指针Q,入队数据指针data
 *    @return         : 成功-TRUE; 失败-FALSE
 *  @notice      : 队列是否为空
 */
Status EnLQueue(LQueue* Q, void* data,int byte) { 
    //未初始化
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
    //空队列
    if (Q->front->next == NULL) {
        Q->front->next = p;
        Q->rear = p;
    }
    //非空
    else {
        Q->rear->next = p;
        Q->rear = p;
    }
    Q->length++;
    return TRUE;
};

/**
 *  @name        : Status DeLQueue(LQueue *Q)
 *    @description : 出队操作
 *    @param         Q 队列指针Q
 *    @return         : 成功-TRUE; 失败-FALSE
 *  @notice      : None
 */
Status DeLQueue(LQueue* Q) {  
    //已初始化
    if (Q->front != NULL) {
        Node* p = Q->front;
        if (p->next != NULL) {
            //只有一个节点
            if (Q->rear == p->next) {
                p->next = NULL;
                Q->rear = p; 
                free(p->next);             
            }
            //有多个节点
            else {
                Node* t = p->next;
                p->next = t->next;
                free(t);
            }
            Q->length--;
            return TRUE;
        }
        //空队列
        else {
            printf("the lqueue is empty\n");
            return FALSE;
        }      
    }
    //未初始化
    else {
        printf("the lqueue is not inited\n");
        return FALSE;
    }
};

/**
 *  @name        : void ClearLQueue(AQueue *Q)
 *    @description : 清空队列
 *    @param         Q 队列指针Q
 *  @notice      : None
 */
void ClearLQueue(LQueue* Q) {
    //未初始化
    if (Q->front == NULL) {
        printf("the lqueue is not inited\n");
        return;
    }
    //空队列
    if (Q->front->next == NULL) {
        printf("the lqueue is empty\n");
        return;
    }
    //清空
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
 *    @description : 遍历函数操作
 *    @param         Q 队列指针Q，操作函数指针foo
 *    @return         : None
 *  @notice      : None
 */
Status TraverseLQueue(const LQueue* Q, void (*foo)(void* q,int byte)) {
    //未初始化
    if (Q->front == NULL ) {
        printf("the lqueue is not inited\n");
        return FALSE;
    }
    //空队列
    if (Q->front->next == NULL) {
        printf("the lqueue is empty\n");
        return FALSE;
    }
    //遍历
    Node* p = Q->front->next;
    while (p != NULL) {
        Node* t = p->next;
        foo(p->data,p->byte);
        p = t;
    }
};

/**
 *  @name        : void LPrint(void *q)
 *    @description : 操作函数
 *    @param         q 指针q

 *  @notice      : None
 */
void LPrint(void* q,int byte) {
    //分类型输出
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

