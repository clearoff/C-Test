/*************************************************************************
	> File Name: MySem.h
	> Author: LZH
	> Mail: www.597995302@qq.com 
	> Created Time: 2017年02月16日 星期四 02时47分13秒
 ************************************************************************/

#ifndef __SEM_H__
#define __SEM_H__
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define PATHNAME "."
#define PROJID 0x6666

union semun {

	int val;    /* Value for SETVAL */
	struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
	unsigned short  *array;  /* Array for GETALL, SETALL */
	struct seminfo  *__buf;  /* Buffer for IPC_INFO(Linux-specific) */
};

int CreatSem(int nsems); 
int InitSem(int semid);
int GetSemID();
int P(int semid,int which);
int V(int semid,int which);
int DestorySem(int semid);

#endif //__SEM_H__
