#include "MySem.h"

int main()
{
	int semid=CreatSem(10);
	printf("Semid:%d\n",semid);
	InitSem(semid);	
	pid_t id = fork();
	if(id==0){
		while(1){
			P(semid,0);
			usleep(5300);
			printf("A ");
			fflush(stdout);
			usleep(5000);
			printf("A ");
			usleep(10000);
			fflush(stdout);
			V(semid,0);
		}
	}
	else{
		while(1){
			P(semid,0);
			usleep(10300);
			printf("B ");
			fflush(stdout);
			usleep(10000);
			printf("B ");
			usleep(10000);
			fflush(stdout);
			V(semid,0);
		}
	}
	DestorySem(semid);	
	return 0;
}
