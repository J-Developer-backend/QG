#pragma once
#include<stdio.h>
#include<stdlib.h>
//
// Created by eke_l on 2021/4/21.
//

#ifndef BINARYSORTTREE_BINARY_SORT_TREE_H
#define BINARYSORTTREE_BINARY_SORT_TREE_H

#define true 1
#define false 0
#define succeed 1
#define failed 0
#define Status int

typedef int ElemType;

typedef struct Node {
    ElemType value;
    struct Node* left, * right;
}Node, * NodePtr;

typedef struct BinarySortTree {
    NodePtr root = NULL;
} BinarySortTree, * BinarySortTreePtr;


//辅助栈节点
typedef struct StackNode {
    NodePtr data;
    StackNode* next;
}StackNode,*StackNodePtr;

//辅助栈
typedef struct Stack {
    StackNodePtr head;
}Stack,*StackPtr;

//辅助队列节点
typedef struct QueueNode {
    NodePtr data;
    QueueNode* next;
}QueueNode,*QueueNodePtr;

//辅助队列
typedef struct Queue {
    QueueNodePtr head;
    QueueNodePtr end;
    int n;
}Queue, * QueuePtr;

/**
 * BST initialize
 * @param BinarySortTreePtr BST
 * @return is complete
 */
Status BST_init(BinarySortTreePtr BST) {
    //根节点
    Node* p = (Node*)malloc(sizeof(Node));
    p->left = NULL;
    p->right = NULL;
    BST->root = p;
    printf("BinarySortTree is inited succeed\n");
    return succeed;
};

/**
 * BST insert
 * @param BinarySortTreePtr BST
 * @param ElemType value to insert
 * @return is successful
 */
Status BST_insert(BinarySortTreePtr BST, ElemType value) {
    //未初始化
    if (BST->root == NULL) {
        printf("the BinarySortTree is not inited\n");
        return failed;
    }
    NodePtr p = BST->root;
    //辅助指针
    NodePtr p1 = NULL;
    //插入的节点
    NodePtr p2 = (NodePtr)malloc(sizeof(Node));
    p2->left = NULL;
    p2->right = NULL;
    p2->value = value;
    //只有根节点
    if (p->left == NULL && p->right == NULL) {
        //默认存第一个节点到根节点的左支
        p->left = p2;
        return succeed;
    }
    else {
        //第一个节点
        p = p->left;
        //插入
        while (true) {
            if ( p->value > value) {
                p1 = p->left;
                if (p1 == NULL) {
                    p->left = p2;
                    printf("insert succeed\n");
                    return succeed;
                }
            }
            else if ( p->value < value) {
                p1 = p->right;
                if (p1 == NULL) {
                    p->right = p2;
                    printf("insert succeed\n");
                    return succeed;
                }
            }
            else if ( p->value == value) {
                printf("the value is already existed\n");
                free(p2);
                return failed;
            }
            p = p1;
        }
    }
};

/**
 * BST delete
 * @param BinarySortTreePtr BST
 * @param ElemType the value for Node which will be deleted
 * @return is successful
 */
Status BST_delete(BinarySortTreePtr BST, ElemType value) {
    //未初始化
    if (BST->root == NULL) {
        printf("the BinarySortTree is not inited\n");
        return failed;
    }
    NodePtr p = BST->root;
    //辅助指针
    NodePtr p1 = NULL;
    //只有根节点
    if (p->left == NULL && p->right == NULL) {
        printf("the BinarySortTree is empty\n");
        return failed;
    }
    else {
        //第一个节点
        p = p->left;
        //根节点就是要删除的节点
        if (p->value == value) {
            //只有一个节点
            if (p->left == NULL && p->right == NULL) {
                BST->root->left = NULL;
            }
            //根节点只有右子树
            else if (p->left == NULL && p->right != NULL) {
                BST->root->left = p->right;
                free(p);
            }
            //根节点只有左子树
            else if (p->left != NULL && p->right == NULL) {
                BST->root->left = p->left;
                free(p);
            }
            //根节点有右子树和左子树
            else if (p->left != NULL && p->right != NULL) {
                NodePtr p2 = p->left->right;
                //左子树没有右子树
                if (p2 == NULL) {
                    p2 = p->left;
                    p->value = p2->value;
                    p->left = p2->left;
                    free(p2);
                }
                //左子树有右子树
                else {
                    NodePtr p3 = p->left;
                    while (p2->right != NULL) {
                        p3 = p2;
                        p2 = p2->right;
                    }
                    p3->right = p2->left;
                    p->value = p2->value;
                    free(p2);
                }
            }
            printf("the value is deleted succeed\n");
            return succeed;
        }
        //在其他节点找到并删除
        while (true) {
            if (p->value > value) {
                p1 = p->left;
                //在p的左支找到
                if (p1 != NULL && p1->value == value) {
                    //删除叶子节点
                    if (p1->left == NULL && p1->right == NULL) {
                        p->left = NULL;
                        free(p1);
                    }
                    //删除的节点只有右子树
                    else if (p1->left == NULL && p1->right != NULL) {
                        p->left = p1->right;
                        free(p1);
                    }
                    //删除的节点只有左子树
                    else if (p1->left != NULL && p1->right == NULL) {
                        p->left = p1->left;
                        free(p1);
                    }
                    //删除的节点有右子树和左子树
                    else if (p1->left != NULL && p1->right != NULL) {
                        NodePtr p2 = p1->left->right;
                        //左子树没有右子树
                        if (p2 == NULL) {
                            p2 = p1->left;
                            p1->value = p2->value;
                            p1->left = p2->left;
                            free(p2);
                        }
                        //左子树有右子树
                        else {
                            NodePtr p3 = p1->left;
                            while (p2->right != NULL) {
                                p3 = p2;
                                p2 = p2->right;
                            }
                            p3->right = p2->left;
                            p1->value = p2->value;
                            free(p2);
                        }
                    }
                    printf("the value is deleted succeed\n");
                    return succeed;
                }
            }
            else if (p->value < value) {
                p1 = p->right;
                //在p的右支找到
                if (p1 != NULL && p1->value == value) {
                    //删除叶子节点
                    if (p1->left == NULL && p1->right == NULL) { 
                        p->right = NULL;
                        free(p1);
                    }
                    //删除的节点只有右子树
                    else if (p1->left == NULL && p1->right != NULL) {
                        p->right = p1->right;
                        free(p1);
                    }
                    //删除的节点只有左子树
                    else if (p1->left != NULL && p1->right == NULL) {
                        p->right = p1->left;
                        free(p1);
                    }
                    //删除的节点有右子树和左子树
                    else if (p1->left != NULL && p1->right != NULL) {
                        NodePtr p2 = p1->left->right;
                        //左子树没有右子树
                        if (p2 == NULL) {
                            p2 = p1->left;
                            p1->value = p2->value;
                            p1->left = p2->left;
                            free(p2);
                        }
                        //左子树有右子树
                        else {
                            NodePtr p3 = p1->left;
                            while (p2->right != NULL) {
                                p3 = p2;
                                p2 = p2->right;
                            }
                            p3->right = p2->left;
                            p1->value = p2->value;
                            free(p2);
                        }
                    }
                    printf("the value is deleted succeed\n");
                    return succeed;
                }
            }
            if (p1 == NULL) {
                printf("the value is not exsited\n");
                return failed;
            }
            p = p1;
        }
    }

};

/**
 * BST search
 * @param BinarySortTreePtr BST
 * @param ElemType the value to search
 * @return is exist
 */
Status BST_search(BinarySortTreePtr BST, ElemType value) {
    //未初始化
    if (BST->root == NULL) {
        printf("the BinarySortTree is not inited\n");
        return failed;
    }
    NodePtr p = BST->root;
    //只有根节点
    if (p->left == NULL && p->right == NULL) {
        printf("the BinarySortTree is empty\n");
        return failed;
    }
    else {
        //第一个节点
        p = p->left;
        //查询
        while (p != NULL && p->value != value) {
            if (p->value > value) 
                p = p->left;           
            else if (p->value < value) 
                p = p->right;           
        }
        //没找到
        if (p == NULL) {
            printf("cannot search the value\n");
            return failed;
        }
        //找到
        if (p->value == value) {
            printf("the value is exsited\n");
            return succeed;
        }
    }
};

//初始化辅助栈
void InitStack(StackPtr s) {
    StackNodePtr p = (StackNodePtr)malloc(sizeof(StackNode));
    p->next = NULL;
    s->head = p;
}

//进栈
void pushStack(StackPtr s ,NodePtr* data) {
    StackNodePtr head = s->head;
    if (head == NULL)
        return;
    StackNodePtr p = (StackNodePtr)malloc(sizeof(StackNode));
    p->data = *data;
    p->next = head->next;
    head->next = p;
}

//弹栈
Status outStack(StackPtr s , NodePtr* data) {
    if (s->head == NULL || s->head->next == NULL)
        return failed;
    StackNodePtr p1 = s->head;
    StackNodePtr p2 = p1->next;
    *data = p2->data;
    p1->next = p2->next;
    free(p2);
    return succeed;
}

/**
 * BST preorder traversal without recursion
 * @param BinarySortTreePtr BST
 * @param (*visit) callback
 * @return is successful
 */
Status BST_preorderI(BinarySortTreePtr BST, void (*visit)(NodePtr)) {
    //未初始化
    if (BST->root == NULL) {
        printf("the BinarySortTree is not inited\n");
        return failed;
    }
    NodePtr p = BST->root;
    //只有根节点
    if (p->left == NULL && p->right == NULL) {
        printf("the BinarySortTree is empty\n");
        return failed;
    }
    else {
        //第一个节点
        p = p->left;
        StackPtr s = (StackPtr)malloc(sizeof(Stack));
        InitStack(s);
        while (p != NULL || s->head->next != NULL) {
            if (p != NULL) {
                visit(p);
                pushStack(s, &p);
                p = p->left;
            }
            else {
                outStack(s, &p);
                p = p->right;
            }      
        }
        return succeed;
    }
};

/**辅助函数
 * BST preorder traversal with recursion
 * @param BinarySortTreePtr BST
 * @param (*visit) callback
 * @return is successful
 */
void BST_preorder(NodePtr p , void (*visit)(NodePtr)) {
    if (p == NULL)
        return;
    visit(p);
    BST_preorder(p->left,visit);
    BST_preorder(p->right, visit);
}

/**
 * BST preorder traversal with recursion
 * @param BinarySortTreePtr BST
 * @param (*visit) callback
 * @return is successful
 */
Status BST_preorderR(BinarySortTreePtr BST, void (*visit)(NodePtr)) {
    //未初始化
    if (BST->root == NULL) {
        printf("the BinarySortTree is not inited\n");
        return failed;
    }
    NodePtr p = BST->root;
    //只有根节点
    if (p->left == NULL && p->right == NULL) {
        printf("the BinarySortTree is empty\n");
        return failed;
    }
    else {
        //第一个节点
        p = p->left;
        BST_preorder(p, visit);
        return succeed;
    }
};

/**
 * BST inorder traversal without recursion
 * @param BinarySortTreePtr BST
 * @param (*visit) callback
 * @return is successful
 */
Status BST_inorderI(BinarySortTreePtr BST, void (*visit)(NodePtr)) {
    //未初始化
    if (BST->root == NULL) {
        printf("the BinarySortTree is not inited\n");
        return failed;
    }
    NodePtr p = BST->root;
    //只有根节点
    if (p->left == NULL && p->right == NULL) {
        printf("the BinarySortTree is empty\n");
        return failed;
    }
    else {
        //第一个节点
        p = p->left;
        StackPtr s = (StackPtr)malloc(sizeof(Stack));
        InitStack(s);
        while (p != NULL || s->head->next != NULL) {
            if (p != NULL) {
                pushStack(s, &p);
                p = p->left;
            }
            else {
                outStack(s, &p);
                visit(p);
                p = p->right;
            }
        }
        return succeed;
    }
};

/**辅助函数
 * BST inorder traversal with recursion
 * @param BinarySortTreePtr BST
 * @param (*visit) callback
 * @return is successful
 */
void BST_inorder(NodePtr p, void (*visit)(NodePtr)) {
    if (p == NULL)
        return;
    BST_inorder(p->left, visit);
    visit(p);
    BST_inorder(p->right, visit);
}

/**
 * BST inorder traversal with recursion
 * @param BinarySortTreePtr BST
 * @param (*visit) callback
 * @return is successful
 */
Status BST_inorderR(BinarySortTreePtr BST, void (*visit)(NodePtr)) {
    //未初始化
    if (BST->root == NULL) {
        printf("the BinarySortTree is not inited\n");
        return failed;
    }
    NodePtr p = BST->root;
    //只有根节点
    if (p->left == NULL && p->right == NULL) {
        printf("the BinarySortTree is empty\n");
        return failed;
    }
    else {
        //第一个节点
        p = p->left;
        BST_inorder(p, visit);
        return succeed;
    }
};

/**
 * BST postorder traversal without recursion
 * @param BinarySortTreePtr BST
 * @param (*visit) callback
 * @return is successful
 */
Status BST_postorderI(BinarySortTreePtr BST, void (*visit)(NodePtr)) {

    //未初始化
    if (BST->root == NULL) {
        printf("the BinarySortTree is not inited\n");
        return failed;
    }
    NodePtr p = BST->root;
    //只有根节点
    if (p->left == NULL && p->right == NULL) {
        printf("the BinarySortTree is empty\n");
        return failed;
    }
    else {
        //第一个节点
        p = p->left;
        //辅助指针
        NodePtr ptr = NULL;
        StackPtr s = (StackPtr)malloc(sizeof(Stack));
        InitStack(s);
        while (p != NULL || s->head->next != NULL) {
            if (p != NULL) {
                pushStack(s, &p);
                p = p->left;
            }
            else {
                outStack(s, &p);
                if (p->right == NULL || p->right == ptr) {
                    visit(p);
                    ptr = p;
                    p = NULL;
                }
                else {
                    pushStack(s,&p);
                    p = p->right;
                }
            }
        }
        return succeed;
    }
};

/**辅助函数
 * BST postorder traversal with recursion
 * @param BinarySortTreePtr BST
 * @param (*visit) callback
 * @return is successful
 */
void BST_postorder(NodePtr p, void (*visit)(NodePtr)) {
    if (p == NULL)
        return;
    BST_postorder(p->left, visit);
    BST_postorder(p->right, visit);
    visit(p);
}

/**
 * BST postorder traversal with recursion
 * @param BinarySortTreePtr BST
 * @param (*visit) callback
 * @return is successful
 */
Status BST_postorderR(BinarySortTreePtr BST, void (*visit)(NodePtr)) {
    //未初始化
    if (BST->root == NULL) {
        printf("the BinarySortTree is not inited\n");
        return failed;
    }
    NodePtr p = BST->root;
    //只有根节点
    if (p->left == NULL && p->right == NULL) {
        printf("the BinarySortTree is empty\n");
        return failed;
    }
    else {
        //第一个节点
        p = p->left;
        BST_postorder(p, visit);
        return succeed;
    }
};

//初始化辅助队列
void initQueue(QueuePtr q) {
    QueueNodePtr head = (QueueNodePtr)malloc(sizeof(QueueNode));
    QueueNodePtr end = (QueueNodePtr)malloc(sizeof(QueueNode));
    head->next = NULL;
    end->next = head;
    q->head = head;
    q->end = end;
    q->n = 0;
}

//入队
void pushQueue(QueuePtr q, NodePtr* p) {
    if (q->head == NULL || q->end == NULL)
        return;
    QueueNodePtr node = (QueueNodePtr)malloc(sizeof(QueueNode));
    node->next = NULL;
    node->data = *p;
    QueueNodePtr end = q->end;
    QueueNodePtr p1 = end->next;
    p1->next = node;
    end->next = node;
}

//出队
void outQueue(QueuePtr q, NodePtr* p) {
    if (q->head->next == NULL)
        return;
    QueueNodePtr p1 = q->head->next;
    QueueNodePtr p2 = p1->next;
    q->head->next = p2;
    *p = p1->data;
    if (q->end->next == p1)
        q->end->next = q->head;
    free(p1);
}

/**
 * BST level order traversal
 * @param BinarySortTreePtr BST
 * @param (*visit) callback
 * @return is successful
 */
Status BST_levelOrder(BinarySortTreePtr BST, void (*visit)(NodePtr)) {
    //未初始化
    if (BST->root == NULL) {
        printf("the BinarySortTree is not inited\n");
        return failed;
    }
    NodePtr p = BST->root;
    //只有根节点
    if (p->left == NULL && p->right == NULL) {
        printf("the BinarySortTree is empty\n");
        return failed;
    }
    else {
        //第一个节点
        p = p->left;
        QueuePtr q = (QueuePtr)malloc(sizeof(Queue));
        initQueue(q);
        pushQueue(q, &p);
        while ( q->head->next != NULL) {
            outQueue(q, &p);
            visit(p);
            if(p->left != NULL)
                pushQueue(q, &(p->left));
            if(p->right != NULL)
                pushQueue(q, &(p->right));            
        }
        return succeed;
    }
};

#endif //BINARYSORTTREE_BINARY_SORT_TREE_H

