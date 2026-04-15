#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

void scriePID(char *numeFisier, pid_t pid)
{
	FILE *f=fopen(numeFisier,"w");
	if(f!=0)
	{
		fprintf(f,"%d",pid);
		fclose(f);
	}
}

pid_t citestePID(char *numeFisier)
{
	pid_t pid=0;
	FILE *f=fopen(numeFisier,"r");
	if(f)
	{
		fscanf(f,"%d",&pid);
		fclose(f);
	}
	return pid;
}

int main(int argc, char * argv[])
{
	pid_t pid1=getpid();
	pid_t pid2=fork();
	if(pid2==0)
	{
		int pid_unchi=0;
		while(pid_unchi<=0)
		{
			pid_unchi=citestePID("pid3.pid");
			usleep(100000);
		}
		
		for(int i=0;i<3;++i)
		{
			if(fork()==0)
			{
				printf("PID UNCHI P2 = %d\n",pid_unchi);
				exit(0);
			}
		}
		exit(0);
	}

	pid_t pid3=fork();
	if(pid3==0)
	{
		int pid_unchi=0;
		while(pid_unchi<=0)
		{
			pid_unchi=citestePID("pid2.pid");
			usleep(100000);
		}
		for(int i=0;i<3;++i)
		{
			if(fork()==0)
			{
				printf("PID UNCHI P3 = %d\n",pid_unchi);
				exit(0);
			}
		}
		exit(0);
	}
	
	scriePID("pid2.pid",pid2);
	scriePID("pid3.pid",pid3);

	printf("\n\nPID PROCES 2: %d\n",pid2);
	printf("PID PROCES 3: %d\n",pid3);

	waitpid(pid2,NULL,0);
	waitpid(pid3,NULL,0);

	unlink("pid2.pid");
	unlink("pid3.pid");

	return 0;
}

