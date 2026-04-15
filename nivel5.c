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
	pid_t pid_bunic=getpid();

	for(int i=0;i<3;++i)
	{
		pid_t pid_parinte=fork();
		if(pid_parinte==0)
		{
			int id_parinte=i;
			scrie("parinte",id_parinte,getpid());
			for(int j=0;j<3;++j)
			{
				pid_t pid_copil=fork();
				if(pid_copil==0)
				{
					int id_copil=id_parinte*3+j;
					scrie("copil",id_copil,getpid());
					
					while(citeste("copil",8)<=0 || citeste("parinte",2)<=0) 
					{
                        			usleep(10000);
                    			}

					printf("PID proces 1: %d\n",pid_bunic);
					printf("PID proces parinte: %d\n",getppid());
					
					for(int k=0;k<9;++k)
					{
						pid_t pid_frate=citeste("copil",k);
						if(pid_frate!=getpid() && pid_frate>0)
						{
							printf("PID frate %d: %d\n",k,pid_frate); 
						}
					}

					for(int k=0;k<3;++k)
					{
						pid_t pid_unchi=citeste("parinte",k);
						if(pid_unchi!=getppid() && pid_unchi>0)
						{
							printf("PID unchi %d: %d\n",k,pid_unchi);
						}
					}
					printf("\n");
					exit(0);
				}
			}

			for(int i=0;i<3;++i) wait(NULL);
                        exit(0);
		}
	}

	for(int i=0;i<3;++i) wait(NULL);

	return 0;
}
