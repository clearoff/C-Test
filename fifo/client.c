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
	//read com
	int fd=open(_PATH_,O_RDONLY);
	printf("fd:%d\n",fd);
	if(fd<0){
		//perror("open error");
		printf("open error\n");
		exit(1);
	}
	while(1){
		printf("[lzh@localhost client]#");
		fflush(stdout);
		char buf[1024];
		ssize_t Len=read(fd,buf,1024);
		printf("Len:%d\n",Len);
		if(Len > 0){
			//read success
			buf[Len]='\0';
			printf("server say:%s\n",buf);
			continue;
		}
		else if(Len==0){
			printf("Read end of fifo..\n");
			break;
		}
		else{
			perror("write errpr");
			exit(1);
		}
	}
	close(fd);
	return 0;
}
