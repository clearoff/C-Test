/*************************************************************************
	> File Name: myList.h
	> Author: LZH
	> Mail: 597995302@qq.com 
	> Created Time: Sun 19 Feb 2017 01:09:24 AM PST
 ************************************************************************/

#ifndef __LIST_H__
#define __LIST_H__

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef struct Node{
	int data;
	struct Node* next;
}Node,*Node_p,**Node_pp;

Node_p AllocNode(int data);
void ListInit(Node_pp head);
int IsEmpty(Node_p list);
void PushHead(Node_p list,int data);
void DelNode(Node_p node);
void PopHead(Node_p list,int *data);
void ShowList(Node_p list);
void DestroyList(Node_p list);
#endif //__LIST_H__
