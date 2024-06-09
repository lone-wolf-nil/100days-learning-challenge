#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

void main()
{
	key_t key = ftok("shmfile",65);
	int shmid = shmget(key,1024,0666|IPC_CREAT);
	if(shmid<0)
	{
		printf("shmget() error! \n");
		return;
	}
	
	unsigned char *buf = (unsigned char*) shmat(shmid,(void*)0,0);
	int j=0;
	while(1)
	{
		for(j=0;j<10;j++)
		{
			printf("%02x", buf[j]);
		}
		printf("\n\n");
		sleep(2);
	}
	shmdt(buf);
	shmctl(shmid,IPC_RMID,NULL);
}