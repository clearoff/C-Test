/*************************************************************************
	> File Name: Mypipe.c
	> Author: LZH
	> Mail: www.597995302@qq.com 
	> Created Time: 2017年02月14日 星期二 06时30分03秒
 ************************************************************************/

#include<stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>

int main()
{
	//create pipe
	int fd[2]={0,0};
	if(pipe(fd)!=0){
		//create false
		perror("pipe");
		exit(1);
	}
	// pipe create success
	pid_t id=fork();
	if(id==0){
		//child -->write fd[1]
		printf("Child\n");
		sleep(2);
		const char* msg="Hello,leap\n";
		close(fd[0]);
		int count=5;
		while(1){
			ssize_t size=write(fd[1],msg,strlen(msg));
			printf("size:%d\n",size);
			if(count--){
				sleep(1);
			}
			printf("child is writing...\n");
		}
		close(fd[1]);
	}
	else{
		//father -->read fd[0]
		printf("Father\n");
		sleep(2);
		close(fd[1]);
		char buf[1024];
		int count=3;
		while(count--){
			ssize_t Len=read(fd[0],buf,1024);
			//printf("Len::%d\n",Len);
			printf("Father is reading...\n");
			if(Len>0){
				//read success
				buf[Len]='\0';
				printf("child say:%s",buf);
			}
			else if(Len==0){
				//read end of file
				printf("Read the end of pipe\n");
			}
			else{
				perror("read");
				exit(1);
			}
		}
		close(fd[0]);
		int status=0;
		pid_t _pid=waitpid(id,&status,0);
		if(_pid==id){
			printf("Wait success for child\n");
			printf("Exit code:%d,Exit signal:%d\n",(status>>8)&0xff,status&0xff);
		}
		else{
			perror("wait");
		}
		exit(0);
	}
	return 0;
}
