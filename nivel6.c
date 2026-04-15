#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

pid_t citeste(char *prefix, int index)
{
        char nume[50];
        sprintf(nume,"%s_%d.pid",prefix,index);
        FILE *f=fopen(nume,"r");
        pid_t pid;
        if(f)
        {
                if(fscanf(f,"%d",&pid)!=1) pid=0;
                fclose(f);
        }
        return pid;
}

void scrie(char *prefix, int index, pid_t pid)
{
        char nume[50];
        sprintf(nume,"%s_%d.pid",prefix,index);
        FILE *f=fopen(nume,"w");
        if(f)
        {
                fprintf(f,"%d",pid);
                fclose(f);
        }
}

int main()
{
	for(int i=0;i<3;++i)
	{
		if(fork()==0)
		{
			for(int j=0;j<3;++j)
			{
				int id=3*i+j;
				if(fork()==0)
				{
					scrie("copil",id,getpid());
					exit(0);
				}
			}
			exit(0);
		}
	}

	for(int i=0;i<9;++i)
	{
		while(citeste("copil",i)<=0) usleep(1000);
	}

	for(int i=0;i<9;++i)
	{
		pid_t pid=citeste("copil",i);
		printf("PID copil %d: %d\n",i,pid);
	}
	return 0;
}
