#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>

void main()
{
	key_t key = ftok("shmfile",65);
	int shmid = shmget(key,1024,0666|IPC_CREAT);
	if(shmid < 0)
	{
		printf("shmget() error! \n");
		return;
	}
	
	unsigned char *buf = (unsigned char*)shmat(shmid,(void*)0,0);
	
	int i=0, j=0;
	for(i-0;i<10;i++)
	{
		memset(buf, i, 10);
		
		printf("[%d] buf dump:\n", i);
		for(j=0;j<10;j++)
		{
			printf("%02x", buf[j]);
		}
		printf("\n");
		
		getchar();
	}
	
	shmdt(buf);	
}