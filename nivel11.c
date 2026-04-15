#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc, char * argv[])
{
	pid_t pid_parinte=getpid();
	pid_t pid_copil1=fork();
	pid_t pid_copil2;
	int status;
	if(pid_copil1==0)
	{
		pid_copil2=fork();
		if(pid_copil2==0)
		{			
		}
		else
		{
			printf("pid copil 2: %d\n",pid_copil2);
			printf("%d\n",pid_parinte-pid_copil2);
			exit(pid_copil2-pid_parinte);
		}
	}
	else
	{
		waitpid(pid_copil1,&status,0);
		int pid_aux=WEXITSTATUS(status);
		printf("pid copil1: %d\n",pid_copil1);
		printf("pid aux: %d\n",pid_aux);
		printf("pid copil2: %d\n",pid_parinte+pid_aux); 
	}
	return 0;
}

