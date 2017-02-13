/*************************************************************************
	> File Name: test.c
	> Author: LZH
	> Mail: www.597995302@qq.com 
	> Created Time: 2017年02月13日 星期一 06时28分23秒
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>


int main()
{
	pid_t id=fork();
	printf("Load MyShell\n");
	char buf[1024];
	ssize_t Len;
	char* Argv[10];
	int i=0;
	if(id==0){
			while (1)
			{
				//child
				printf("[lzh@localhost MyShell]#");
				fflush(stdout);   //flush buf
				Len = read(0, buf, 1024);
				if (Len>0)
				{//read Success
					buf[Len - 1] = '\0';
					printf("Debug:%s\n", buf);
					int count = 0;
					char* Start;
					for (Start = buf; *Start != '\0'; Start++)
					{
						Argv[count++] = Start;
						while (*Start != ' '&&*Start != '\0')
						{
							Start++;
						}
						if (*Start == '\0')
						{
							break;
						}
						*Start = '\0';      //*Start==' ',replace 
					}
					printf("count:%d\n", count);
					Argv[count] = NULL;
					for (i = 0; Argv[i] != NULL; i++)
					{
						printf("%d,Debug:%s\n", i, Argv[i]);
					}
					execvp(Argv[0], Argv);
					//	printf("Error\n");
					//	exit(1);
				}
				else
				{//read error ,finish now cycle
					perror("Read Error!\n");
					continue;
				}
				printf("\n");
			}
	}
	else{
			//father
			sleep(1);
			printf("I am father,pid:%d,ppid:%d\n",getpid(),getppid());
			wait(NULL);
	}
	return 0;
}
