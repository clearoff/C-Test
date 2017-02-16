/*************************************************************************
	> File Name: MySem.c
	> Author: LZH
	> Mail: www.597995302@qq.com 
	> Created Time: 2017年02月16日 星期四 02时49分08秒
 ************************************************************************/

#include "MySem.h"

int InitSem(int semid)
{
	union semun un;
	un.val=1;
	int ret = semctl(semid,0,SETVAL,un);
	if(ret < 0){
		perror("semctl ...\n");
		return -1;
	}
	return 0;
}

static int CommSem(int nsems,int flags)
{
	key_t _k=ftok(PATHNAME,PROJID);
	if(_k < 0){
		perror("ftok error..\n");
		return -1;
	}
    int semid=semget(_k,nsems, flags);
	if(semid < 0){
		perror("semget error..\n");
		return -2;
	}

	return semid;
}

int CreatSem(int nsems)
{
  return  CommSem(nsems,IPC_CREAT | IPC_EXCL |0666);
}

int GetSemID()
{
	return CommSem(0,0);
}

int SemOp(int semid,int op,int num)
{
	struct sembuf buf;
	buf.sem_op=op;
	buf.sem_num=num;
	buf.sem_flg=0;
	int ret = semop(semid,&buf,1);
	if(ret < 0){
		perror("Semop..\n");
		return -1;
	}
	return 0;
}

int P(int semid,int which)
{
	return SemOp(semid,-1,which);
}

int V(int semid,int which)
{
	return  SemOp(semid,1,which);
}

int DestorySem(int semid)
{
	int ret = semctl(semid,0,IPC_RMID);
	if(ret < 0){
		perror("semctl..\n");
	}
	return 0;
}
