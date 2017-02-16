/*************************************************************************
	> File Name: server.c
	> Author: LZH
	> Mail: www.597995302@qq.com 
	> Created Time: 2017年02月15日 星期三 12时33分12秒
 ************************************************************************/

#include "comm.h"


int main()
{
	int ret = GetMsgQueue();    //client receive msgqueue use
	printf("ret:%d\n");
	char buf[BUFSIZE*2];	
	while(1){
		printf("Client #");
		fflush(stdout);
		if(ReceiveMessage(ret,ServerType,buf) >= 0){
			printf("Server say:%s\n",buf);
			const char* msg="Client receive it\n";
			if(SendMessage(ret,ClientType,msg)>=0){
				printf("Send server success\n");
			}
			else{
				perror("Send server error\n");
				break;
			}
		}
		else{
			perror("Receive msg error\n");
			break;
		}	
	}
	exit(1);
}
