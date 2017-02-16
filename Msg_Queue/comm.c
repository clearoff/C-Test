#include "comm.h"


static int CommMsgQueue(int flag)
{
    key_t key= ftok(PATHNAME,PRJID);
	if(key < 0){
		perror("ftok error\n");
		return -1;
	}
    int ret=msgget(key,flag);
	if(ret < 0){
		perror("msgget error\n");
		return -2;
	}
	return ret;	
}

int CreateMsgQueue()
{
	return  CommMsgQueue(IPC_CREAT |IPC_EXCL |0666);
}

int GetMsgQueue()    //client receive msgqueue use
{
	return  CommMsgQueue(IPC_CREAT);
}

int DeleteMsgQueue(int msqid)
{
	int ret = msgctl(msqid,IPC_RMID,NULL);
	printf("ret:%d\n",ret);
	if(ret < 0){
		perror("delete queue error\n");
		return -1;
	}
	return ret;
}

int SendMessage(int msg_id,long type,const char* buf)
{
	struct MyBuf msg_p;
	msg_p.mType=type;
	strcpy(msg_p.mText,buf);
	int ret = msgsnd(msg_id,&msg_p,BUFSIZE,0);
	if(ret < 0){
		perror("msgsnd error\n");
		return -1;
	}
	return ret;
}
int ReceiveMessage(int msg_id,long type,char* out)
{
	struct MyBuf buf;
	size_t Len=msgrcv(msg_id,&buf,BUFSIZE,type,0);	
	if(Len > 0){
		strncpy(out,buf.mText,BUFSIZE);
		return 0;
	}
	return -1;
}
