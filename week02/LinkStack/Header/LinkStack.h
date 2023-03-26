#pragma once
#include<stdlib.h>
#include<stdio.h>

#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED



typedef int ElemType;     

typedef  struct StackNode		
{
	ElemType data;
	struct StackNode* next;
}StackNode, * LinkStackPtr;

typedef  struct  LinkStack  
{
	LinkStackPtr top;	  
	int	count;			  
}LinkStack;


typedef enum Status {
	ERROR = 0,
	SUCCESS = 1
}Status;


//��ʼ��ջ
Status initStack(LinkStack** s) {
	//���ջΪ��
	if (*s == NULL) {
		LinkStack* p = (LinkStack*)malloc(sizeof(LinkStack));
		//ջ�г�ʼԪ��Ϊ0
		p->count = 0;
		//��ʼջ��ΪNULL
		p->top = NULL;
		//��ջ��ʼ��
		*s = p;
	}
	//ջ��Ϊ��
	if((*s)->top!=NULL) {
		LinkStack* l = *s;
		LinkStackPtr p1 = l->top;
		LinkStackPtr p2 = p1->next;
		//���ջ
		while (p1 != NULL) {
			free(p1);
			p1 = p2;
			if (p2 != NULL)
				p2 = p2->next;
		}
		//��ʼ��
		(*s)->top = NULL;
		(*s)->count = 0;
	}
	return SUCCESS;
}


//��ʾ��ʼ��
Status remindInit(LinkStack* s) {
	return s == NULL ? SUCCESS : ERROR;
}


//�ж�ջ�Ƿ�Ϊ��
Status isEmpty(LinkStack *s) {
	//�жϳ�ʼ��
	if (remindInit(s)) {
		printf("the linkstack is not inited\n");
		return ERROR;
	}
	//�ж�ջ��Ԫ�ظ����Ƿ�Ϊ0
	return s->count == 0 ? SUCCESS : ERROR;
}


//�õ�ջ��Ԫ�أ���Ԫ�ش�ŵ�e��
Status getTopStack(LinkStack *s, ElemType* e) {
	//�жϳ�ʼ��
	if (remindInit(s)) {
		printf("the linkstack is not inited\n");
		return ERROR;
	}
	//��ջ
	if (s->top == NULL)
		return ERROR;
	//��Ԫ��
	*e = s->top->data;
	return SUCCESS;
}


//���ջ
Status clearStack(LinkStack *s) {
	//�жϳ�ʼ��
	if (remindInit(s)) {
		printf("the linkstack is not inited\n");
		return ERROR;
	}
	//��ջ
	if (s->top == NULL)
		return ERROR;
	//�ǿ�ջ
	LinkStackPtr p1 = s->top;
	LinkStackPtr p2 = p1->next;
	//ջ�ײ��ᱻfree
	while (p1->next != NULL) {
		free(p1);
		p1 = p2;
		p2 = p2->next;
	}
	return SUCCESS;
}


//����ջ
Status destoryStack(LinkStack **s) {
	LinkStack* l = *s;
	//�жϳ�ʼ��
	if (remindInit(l)) {
		printf("the linkstack is not inited\n");
		return ERROR;
	}
	//��ջ
	if (l->top == NULL) {
		*s = NULL;
		return SUCCESS;
	}	
	//�ǿ�ջ,�����
	LinkStackPtr p1 = l->top;
	LinkStackPtr p2 = p1->next;
	while (p1 != NULL) {
		free(p1);
		p1 = p2;
		if (p2 != NULL)
			p2 = p2->next;
	}
	//ջ���������
	*s = NULL;
	return SUCCESS;
}


//���ջ�Ĵ�С
Status stackLength(LinkStack *s,int *e) {
	//�жϳ�ʼ��
	if (remindInit(s)) {
		printf("the linkstack is not inited\n");
		return ERROR;
	}
	//ֱ�ӷ���ջ�Ĵ�С
	*e = s->count;
	return SUCCESS;
}


//��ջ
Status pushStack(LinkStack *s,ElemType e) {
	//�жϳ�ʼ��
	if (remindInit(s)) {
		printf("the linkstack is not inited\n");
		return ERROR;
	}
	//����ջ�ڵ�
	LinkStackPtr p = (StackNode*)malloc(sizeof(StackNode));
	//�ڵ��������e
	p->data = e;
	//�ڵ���뵽ջ��
	p->next = s->top;
	//ջ���ƶ��µ�ջ���ڵ�
	s->top = p;
	//ջ��Ԫ��+1
	s->count++;
	return SUCCESS;
}


//��ջ������ջ��Ԫ�ش�ŵ�e��
Status popStack(LinkStack *s, ElemType *e) {
	//�жϳ�ʼ��
	if (remindInit(s)) {
		printf("the linkstack is not inited\n");
		return ERROR;
	}
	//��ջ����ִ�г�ջ����
	if (s->top == NULL)
		return ERROR;
	//��ų�ջ��Ԫ��
	*e = s->top->data;
	//�ͷ�ջ��Ԫ��
	LinkStackPtr p = s->top;
	//�ƶ�ջ��Ԫ��
	s->top = p->next;
	//ջԪ��--
	s->count--;
	//�ͷ�
	free(p);
	return SUCCESS;
}



#endif








