/*************************************************************************
	> File Name: server.c
	> Author: LZH
	> Mail: www.597995302@qq.com 
	> Created Time: 2017年02月14日 星期二 15时32分01秒
 ************************************************************************/

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>


#define _PATH_ "./Myfifo"

int main()
{
	//write com
	umask(0);
	int ret=mkfifo(_PATH_,0666|S_IFIFO);
	printf("ret:%d\n",ret);
	if(ret<0){
		//perror("mkfifo error");
		printf("Mkfifo error\n");
		exit(1);
	}
	//create success
	int id=open(_PATH_,O_WRONLY);
	printf("id:%d\n",id);
	while(1){
		printf("[lzh@localhost server]#");
		fflush(stdout);
		if(id < 0){
			perror("open..");
			exit(1);
		}
		else{
		char buf[1024];
		ssize_t Len=read(0,buf,1024);
		printf("Len:%d\n",Len);
		if(Len > 0){
			//read success
			buf[Len]='\0';
			ssize_t Size=write(id,buf,strlen(buf));
			printf("Send %d bytes to client\n",Size);
		}
		else{
			perror("write errpr");
			exit(1);
		}
		}
	}
	close(id);
	return 0;
}
