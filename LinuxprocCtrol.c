/*************************************************************************
	> File Name: test.c
	> Author: LZH
	> Mail: www.597995302@qq.com 
	> Created Time: 2017年01月17日 星期二 20时00分16秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include <sys/types.h>
 #include <sys/wait.h>


int main()
{
	/*
	int id=fork();    //creat child proc
	if(id==0)
	{
		//child proc
		while(1){
		printf("I am child,id::%d\n",getpid());
		sleep(1);
		}
		exit(0);
	}
	else
	{
		//father proc
		int status=0;
		int wait_id=wait(&status);
		if(wait_id>0)
		{
		  printf("child proc has success dead!,id::%d\n",wait_id);
		}
		else
		{
			printf("child proc has false dead!.ret::%d\n",wait_id);
		}
	}
	*/
	/*
	int ret=wait(NULL);
	printf("ret:;%d\n",ret);
	*/
/*
	//waitpid use
	int id=fork();
	int count=10;
	if(id==0)
	{
		//child proc
		while(count--)
		{
			sleep(1);
			printf("CHild proc.id:: %d\n",getpid());
		}
		exit(11);
	}
	else{
		//father proc
		int status=0;
		int ret=waitpid(id,&status,0);    //option = 0
		if(ret>0){
			if(WIFEXITED(status))
			{
				printf("child proc return normal,exit code:%d\n",\
						WEXITSTATUS(status));
				printf("Child proc dead success,ret=%d,status=%d\n",\
					(status>>8)&0xff,(status&0xff));
			}
			else{
				//retuen val is false
				printf("child proc return unnormal\n");
				if(WIFSIGNALED(status))
				{
				  printf("child proc is killed by signal,signal code is %d\n",WTERMSIG(status));
				}
				else{
					printf("child proc is not killed bu signal\n");
				}
			}
		}
		else{
			printf("Child proc dead false,ret=%d\n",ret);
		}
		printf("Status::%d\n",status);
	}
	*/
	int id=fork();
	int count=10;
	if(id==0){
		//child proc
		while(count--){
			printf("I am child proc,ID:%d\n",getpid());
			sleep(1);
		}
		exit(9);        //exit code 
	}
	else{
		// father proc
		int status=0;
		int ret=0;
		do{
			printf("Do other thing and check child proc status\n");
			sleep(1);
		}while((ret=waitpid(id,&status,WNOHANG))==0);
		if(ret>0){
			printf("child proc dead\n");
			if(WIFEXITED(status)){
				printf("child proc dead normal.exit code:%d\n"\
						,WEXITSTATUS(status));
			}
			else{
				if(WIFSIGNALED(status)){
					printf("child proc is killed by signal,signal code is \
							%d\n",WTERMSIG(status));
				}
				else{
					printf("child proc is killed by other things\n");
				}
			}
		}
		
	}
	return 0;
}
