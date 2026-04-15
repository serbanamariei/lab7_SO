#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc, char * argv[])
{
	pid_t pid1=getpid();
	pid_t pid2=fork();
	//int status;
	if(pid2==0)
	{
		pid_t pid21=fork();
		if(pid21==0)
		{
			printf("\nSUNT PROCES 21:\n");
			printf("pid proces 1(bunicul meu): %d\n",pid1);
			printf("pid proces 2(parintele meu): %d\n",getppid());
			exit(0);
		}
		else
		{
			waitpid(pid21,NULL,0);	
		}

		pid_t pid22=fork();
		if(pid22==0)
		{
			printf("\nSUNT PROCES 22:\n");
			printf("pid proces 1(bunicul meu): %d\n",pid1);
			printf("pid proces 2(parintele meu): %d\n", getppid());
			exit(0);
		}
		else
		{
			waitpid(pid22,NULL,0);
		}

		pid_t pid23=fork();
		if(pid23==0)
		{
			printf("\nSUNT PROCES 23:\n");
                        printf("pid proces 1(bunicul meu): %d\n",pid1);
                        printf("pid proces 2(parintele meu): %d\n", getppid());
                        exit(0);
		}
		else
		{
			waitpid(pid23,NULL,0);
		}

		exit(0);
	}
	else
	{
		waitpid(pid2,NULL,0); 
	}

	pid_t pid3=fork();
	if(pid3==0)
	{
		pid_t pid31=fork();
		if(pid31==0)
		{
			printf("\nSUNT PROCES 31:\n");
			printf("pid proces 1(bunicul meu): %d\n",pid1);
			printf("pid proces 3(parintele meu): %d\n",getppid());
			exit(0);
		}
		else
		{
			waitpid(pid31,NULL,0);
		}

		pid_t pid32=fork();
		if(pid32==0)
                {
                        printf("\nSUNT PROCES 32:\n");
                        printf("pid proces 1(bunicul meu): %d\n",pid1);
                        printf("pid proces 3(parintele meu): %d\n",getppid());
                        exit(0);
                }
                else
                {
                        waitpid(pid32,NULL,0);
                }

		                pid_t pid33=fork();
                if(pid33==0)
                {
                        printf("\nSUNT PROCES 33:\n");
                        printf("pid proces 1(bunicul meu): %d\n",pid1);
                        printf("pid proces 3(parintele meu): %d\n",getppid());
                        exit(0);
                }
                else
                {
                        waitpid(pid33,NULL,0);
                }

		
		exit(0);
	}
	else
	{
		waitpid(pid3,NULL,0);
	}
	return 0;
}

