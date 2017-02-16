/*************************************************************************
	> File Name: server.c
	> Author: LZH
	> Mail: www.597995302@qq.com 
	> Created Time: 2017年02月15日 星期三 12时33分12秒
 ************************************************************************/

#include "comm.h"


int main()
{
	int ret=CreateMsgQueue();

	if(ret < 0){
		perror("creat error\n");
		exit(1);
	}
	printf("ret:%d\n");
	char buf[1024];	
	while(1){
		printf("server #");
		fflush(stdout);
		sleep(10);
		ssize_t Len=read(0,buf,BUFSIZE);	
		if(Len < 0){
			perror("Read error\n");
			break;
		}
		buf[Len]='\0';
		printf("Debug buf:%s\n",buf);
		int tmp=SendMessage(ret,ServerType,buf);
		if(tmp >= 0){
			//send success
			char out[BUFSIZE*2];
			if(ReceiveMessage(ret,ClientType,out)>=0)
				printf("Client say:%s\n",out);
			else{
				perror("Receive error\n");
				break;
			}
		}
		else{
			perror("send error\n");
			break;
		}
			
	}
	DeleteMsgQueue(ret);
		
	return 0;
}
