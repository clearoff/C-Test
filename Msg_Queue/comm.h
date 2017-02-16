/*************************************************************************
	> File Name: comm.h
	> Author: LZH
	> Mail: www.597995302@qq.com 
	> Created Time: 2017年02月15日 星期三 12时34分18秒
 ************************************************************************/

#ifndef _COMM_
#define _COMM_
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define PATHNAME	"."
#define PRJID	0x6666
#define BUFSIZE 128

#define ServerType 1
#define ClientType 2

struct MyBuf{
	long mType;
	char mText[BUFSIZE];
};


int CreateMsgQueue();
int GetMsgQueue();    //client receive msgqueue use
int DeleteMsgQueue(int msqid);
int SendMessage(int msg_id,long type,const char* buf);
int ReceiveMessage(int msg_id,long type,char* out);

#endif //_COMM_
