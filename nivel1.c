#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc, char * argv[])
{
	pid_t pid_parinte=getpid();
	pid_t pid=fork();
	if(pid==0)
	{
		pid_t pid1=fork();
		if(pid1==0)
		{
			printf("pid proces parinte = %d\n",pid_parinte);
			printf("pid proces copil1 = %d\n",getppid());
		}
		else
		{
			waitpid(pid1,NULL,0);
		}
	}
	else
	{
		waitpid(pid,NULL,0);
	}
	return 0;
}

