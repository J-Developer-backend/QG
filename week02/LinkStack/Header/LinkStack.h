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


//初始化栈
Status initStack(LinkStack** s) {
	//如果栈为空
	if (*s == NULL) {
		LinkStack* p = (LinkStack*)malloc(sizeof(LinkStack));
		//栈中初始元素为0
		p->count = 0;
		//初始栈顶为NULL
		p->top = NULL;
		//将栈初始化
		*s = p;
	}
	//栈不为空
	if((*s)->top!=NULL) {
		LinkStack* l = *s;
		LinkStackPtr p1 = l->top;
		LinkStackPtr p2 = p1->next;
		//清空栈
		while (p1 != NULL) {
			free(p1);
			p1 = p2;
			if (p2 != NULL)
				p2 = p2->next;
		}
		//初始化
		(*s)->top = NULL;
		(*s)->count = 0;
	}
	return SUCCESS;
}


//提示初始化
Status remindInit(LinkStack* s) {
	return s == NULL ? SUCCESS : ERROR;
}


//判断栈是否为空
Status isEmpty(LinkStack *s) {
	//判断初始化
	if (remindInit(s)) {
		printf("the linkstack is not inited\n");
		return ERROR;
	}
	//判断栈的元素个数是否为0
	return s->count == 0 ? SUCCESS : ERROR;
}


//得到栈顶元素，把元素存放到e中
Status getTopStack(LinkStack *s, ElemType* e) {
	//判断初始化
	if (remindInit(s)) {
		printf("the linkstack is not inited\n");
		return ERROR;
	}
	//空栈
	if (s->top == NULL)
		return ERROR;
	//有元素
	*e = s->top->data;
	return SUCCESS;
}


//清空栈
Status clearStack(LinkStack *s) {
	//判断初始化
	if (remindInit(s)) {
		printf("the linkstack is not inited\n");
		return ERROR;
	}
	//空栈
	if (s->top == NULL)
		return ERROR;
	//非空栈
	LinkStackPtr p1 = s->top;
	LinkStackPtr p2 = p1->next;
	//栈底不会被free
	while (p1->next != NULL) {
		free(p1);
		p1 = p2;
		p2 = p2->next;
	}
	return SUCCESS;
}


//销毁栈
Status destoryStack(LinkStack **s) {
	LinkStack* l = *s;
	//判断初始化
	if (remindInit(l)) {
		printf("the linkstack is not inited\n");
		return ERROR;
	}
	//空栈
	if (l->top == NULL) {
		*s = NULL;
		return SUCCESS;
	}	
	//非空栈,先清空
	LinkStackPtr p1 = l->top;
	LinkStackPtr p2 = p1->next;
	while (p1 != NULL) {
		free(p1);
		p1 = p2;
		if (p2 != NULL)
			p2 = p2->next;
	}
	//栈底随后销毁
	*s = NULL;
	return SUCCESS;
}


//检测栈的大小
Status stackLength(LinkStack *s,int *e) {
	//判断初始化
	if (remindInit(s)) {
		printf("the linkstack is not inited\n");
		return ERROR;
	}
	//直接返回栈的大小
	*e = s->count;
	return SUCCESS;
}


//入栈
Status pushStack(LinkStack *s,ElemType e) {
	//判断初始化
	if (remindInit(s)) {
		printf("the linkstack is not inited\n");
		return ERROR;
	}
	//创建栈节点
	LinkStackPtr p = (StackNode*)malloc(sizeof(StackNode));
	//节点存入数据e
	p->data = e;
	//节点插入到栈顶
	p->next = s->top;
	//栈顶移动新的栈顶节点
	s->top = p;
	//栈的元素+1
	s->count++;
	return SUCCESS;
}


//出栈，将出栈的元素存放到e中
Status popStack(LinkStack *s, ElemType *e) {
	//判断初始化
	if (remindInit(s)) {
		printf("the linkstack is not inited\n");
		return ERROR;
	}
	//空栈不能执行出栈操作
	if (s->top == NULL)
		return ERROR;
	//存放出栈的元素
	*e = s->top->data;
	//释放栈顶元素
	LinkStackPtr p = s->top;
	//移动栈顶元素
	s->top = p->next;
	//栈元素--
	s->count--;
	//释放
	free(p);
	return SUCCESS;
}



#endif








