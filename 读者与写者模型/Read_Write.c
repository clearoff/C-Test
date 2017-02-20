/*************************************************************************
	> File Name: Read_Write.c
	> Author: LZH
	> Mail: 597995302@qq.com 
	> Created Time: Sun 19 Feb 2017 10:56:59 PM PST
 ************************************************************************/
#include "myList.h"
#include<pthread.h>

//int pthread_rwlock_destroy(pthread_rwlock_t *rwlock);
//int pthread_rwlock_init(pthread_rwlock_t *restrict rwlock,const pthread_rwlockattr_t *restrict attr);

pthread_rwlock_t lock;

void* Pthread_Write(void* arg)
{
	Node_p head=(Node_p)arg;
	while(1)
	{	
		sleep(1);
		int ret=pthread_rwlock_wrlock(&lock);
		if(ret!=0){
			perror("wrlock error..\n");
			return (void*) -1;
		}
		int data1=rand()%1000;
		int data2=rand()%1000;
		PushHead(head,data1);
		PushHead(head,data2);
		sleep(1);
		printf("Writer write data:%d,%d to list.\n",data1,data2);
		pthread_rwlock_unlock(&lock);
	}
	return (void*) 0;
}

void* Pthread_Read1(void* arg)
{
	Node_p head=(Node_p)arg;
	while(1)
	{	
		sleep(1);
		int ret=pthread_rwlock_rdlock(&lock);
		if(ret!=0){
			perror("rdlock error..\n");
			return (void*) -1;
		}
		int data=0;
		PopHead(head,&data);
		sleep(1);
		printf("Reader1 receive data:%d from list.\n",data);
		pthread_rwlock_unlock(&lock);
	}
	return (void*) 0;
}

void* Pthread_Read2(void* arg)
{
	Node_p head=(Node_p)arg;
	while(1)
	{	
		sleep(1);
		int ret=pthread_rwlock_rdlock(&lock);
		if(ret!=0){
			perror("rdlock error..\n");
			return (void*) -1;
		}
		int data=0;
		PopHead(head,&data);
		sleep(1);
		printf("Reader2 receive data:%d from list.\n",data);
		pthread_rwlock_unlock(&lock);
	}
	return (void*) 0;
}

int main()
{
	printf("Read and Write model...\n");
	Node_p head;
	ListInit(&head);
	printf("lock:%d\n",lock);
	pthread_t tid1,tid2,tid3;
	pthread_rwlock_init(&lock,NULL);
	pthread_create(&tid1,NULL,Pthread_Write,(void*)head);
	pthread_create(&tid2,NULL,Pthread_Read1,(void*)head);
	pthread_create(&tid3,NULL,Pthread_Read2,(void*)head);

	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	pthread_join(tid3,NULL);
	
	pthread_rwlock_destroy(&lock);
	return 0;
}
