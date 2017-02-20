/*************************************************************************
	> File Name: myList.c
	> Author: LZH
	> Mail: 597995302@qq.com 
	> Created Time: Sun 19 Feb 2017 01:12:16 AM PST
 ************************************************************************/

#include "myList.h"

Node_p AllocNode(int data)
{
	Node_p NewNode=(Node_p)malloc(sizeof(Node));
	if(NewNode==NULL)
	{
		perror("malloc..\n");
		return ;
	}
	NewNode->data=data;
	NewNode->next=NULL;

	return NewNode;
}

int IsEmpty(Node_p list)
{
	assert(list);
	if(list->next!=NULL)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

void ListInit(Node_pp head)
{
	*head=AllocNode(0);	
}

void PushHead(Node_p list,int data)
{
	assert(list);

	Node_p NewNode=AllocNode(data);
	NewNode->next=list->next;
	list->next=NewNode;
}

void DelNode(Node_p node)
{
	assert(node);
	free(node);
	node=NULL;
}

void PopHead(Node_p list,int *data)
{
	assert(data);
	if(IsEmpty(list))
	{
		printf("the list empty..\n");
		return;
	}
	Node_p dNode=list->next;
	list->next=dNode->next;
	*data=dNode->data;
	DelNode(dNode);
}

void ShowList(Node_p list)
{	
	assert(list);
	Node_p cur=list->next;
	while(cur)
	{
		printf("%d ",cur->data);
		cur=cur->next;
	}
	printf("\n");
}


void DestroyList(Node_p list)
{
	assert(list);
	int data=0;
	while(list->next)
	{
		PopHead(list,&data);
	}
	
	free(list);
	list=NULL;
	printf("list is destroy...\n");
}
