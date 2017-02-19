/*************************************************************************
	> File Name: product_consumer.c
	> Author: LZH
	> Mail: 597995302@qq.com 
	> Created Time: Sun 19 Feb 2017 12:46:44 AM PST
 ************************************************************************/

#include "myList.h"
#include <pthread.h>

pthread_mutex_t mylock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t mycond=PTHREAD_COND_INITIALIZER;
//pthread_mutex_t mylock=PTHREAD_MUTEX_INITIALIZER;

void* pthread_Product(void* arg)
{
	Node_p head=(Node_p)arg;
	while(1)
	{
		usleep(123456);
		pthread_mutex_lock(&mylock);
		int data=rand()%1000;
		PushHead(head,data);
		printf("I am producter,%d\n",data);
		pthread_cond_signal(&mycond);		
		//ShowList(arg);
		pthread_mutex_unlock(&mylock);
	}
}

void* pthread_Consumer(void* arg)
{
	Node_p head=(Node_p)arg;
	int data=0;
	while(1)
	{
		pthread_mutex_lock(&mylock);
		//sleep(1);
		if(IsEmpty(head))
		{
			pthread_cond_wait(&mycond,&mylock);
		}
		PopHead(head,&data);
		//ShowList(head);
		//sleep(1);
		printf("I am consumer,%d\n",data);
		pthread_mutex_unlock(&mylock);
	}
}

void test()
{
	printf("product_consumer...\n");
	
	Node_p head;
	ListInit(&head);
	printf("head->data:%d\n",head->data);
	int i=0;
	while(i<10)
	{
		PushHead(head,i);
		i++;
		ShowList(head);
	}
	int data;
	while(i>0)
	{
		PopHead(head,&data);
		i--;
		ShowList(head);
		printf("IsEmpty?%d\n",IsEmpty(head));
	}
	
	DestroyList(head);
	ShowList(head);

	//return 0;
}


int main()
{
	Node_p head=NULL;
	ListInit(&head);

	pthread_t tid1,tid2;
	int ret1=pthread_create(&tid1,NULL,pthread_Product,(void*)head);
	int ret2=pthread_create(&tid2,NULL,pthread_Consumer,(void*)head);
	printf("ret1:%d,ret2:%d\n",ret1,ret2);	
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	pthread_mutex_destroy(&mylock);
	pthread_cond_destroy(&mycond);
	
	return 0;
}

