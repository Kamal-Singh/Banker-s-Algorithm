#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdbool.h>
#include<stdlib.h>
#define MAXR 100
#define MAXN 100
const int maxn,maxr;
int total_resources[MAXR]={0};
int available[MAXR]={0}; 	//To store the available instances of the ith resource.
int max[MAXN][MAXR]; 		//To store the max number of resources of a given type,the process will allocate. 
int allocated[MAXN][MAXR]; 	//To store the allocated instance of each resource for the following process.
int need[MAXN][MAXR];		//To store the required number of instances of a resource a process needs in order to get completed.
int  state[MAXN];			//To control each thread.
void init()
{
	//Initialize all the shared data to 0
	for(int i=0;i<MAXN;i++)
	{
		for(int j=0;j<MAXR;j++)
		{
			max[i][j]=0;
			allocated[i][j]=0;
			need[i][j]=0;
		}
	}
	//All the processes in the beginning are unfinished.
	for(int i=0;i<MAXN;i++)
		state[i]=0;
}
void menu()
{
	system("clear");
	printf("--------------------------Banker's Alogrithm--------------------------\n");
	printf("1. Check Status\n");
	printf("2. Allocate Resources\n");
	printf("3. Terminate a process\n");
	printf("4. See Safe Sequence\n");
	printf("5. Exit\n");
	printf("Enter one of the option = ");
}
void getch()
{	
	char c;
	fflush(stdout);
	fflush(stdin);
	read(0, &c, 1);
		return;
}
void status_module()
{
	printf("\n\n\n\tAvailable system resources:\n\t");
	for(int i=0;i<maxr;i++)
		printf("R%d ",i);
	printf("\nFree\t");
	for(int i=0;i<maxr;i++)
		printf("%d  ",available[i]);

	//Currently allocated resources
	printf("\n\n\n\tProcesses (currently allocated resources):\n\t");
	for(int i=0;i<maxr;i++)
		printf("R%d ",i);
	for(int i=0;i<maxn;i++)
	{
		printf("\nP%d\t",i);
		for(int j=0;j<maxr;j++)
			printf("%d  ",allocated[i][j]);	
	}

	//Currently allocated resources
	printf("\n\n\n\tProcesses (maximum resources):\n\t");
	for(int i=0;i<maxr;i++)
		printf("R%d ",i);
	for(int i=0;i<maxn;i++)
	{
		printf("\nP%d\t",i);
		for(int j=0;j<maxr;j++)
			printf("%d  ",max[i][j]);	
	}

	//Resources needed to complete execution by each process
	printf("\n\n\n\tNeed (maximum resources - currently allocated resources):\n\t");
	for(int i=0;i<maxr;i++)
		printf("R%d ",i);
	for(int i=0;i<maxn;i++)
	{
		printf("\nP%d\t",i);
		for(int j=0;j<maxr;j++)
			printf("%d  ",need[i][j]);	
	}
}
void show_status()
{
	system("clear");
	//Total system resources
	printf("\tTotal system resources:\n\t");
	for(int i=0;i<maxr;i++)
		printf("R%d ",i);
	printf("\nFree\t");
	for(int i=0;i<maxr;i++)
		printf("%d  ",total_resources[i]);

	status_module();

	//Available system resources
		printf("\nPress enter to go back......");
	return;
}
void initiate_request()
{
	system("clear");
	int thread_id,res[maxr];
	while(1)
	{
	printf("Enter the process number = ");
	scanf("%d",&thread_id);
	if(!(thread_id>=0 && thread_id<maxn) || state[thread_id]==-1)
	printf("Error! Thread doesn't exist!!!\n");
	else
	break;
	}
	state[thread_id]=1;
	while(state[thread_id]==1);
	return;

}
void request(int thread_id)
{
	int res[maxr];
	status_module();
	printf("\nEnter the values of resources for the process %d = \n",thread_id);
	for(int i=0;i<maxr;i++)
	{
		scanf("%d",&res[i]);
	}
	return;
}
void *generic_thread(void *data)
{
	int pthread_id=(int)data;
	while(1)
	{
		if(state[pthread_id]==0)
		continue;
		else if(state[pthread_id]==1)
		{
			request(pthread_id);
			state[pthread_id]=0;
		}
		else if(state[pthread_id]==2)
		{
			state[pthread_id]==-1;
			pthread_exit(NULL);
		}
	}
}
int main()
{
	int i,j,ch;
	init();
	printf("Enter the number of resources = ");
	scanf("%d",&maxr);
	printf("Enter the number of processes = ");
	scanf("%d",&maxn);
	printf("Enter the maximum instances of each resources type = ");
	for(i=0;i<maxr;i++)
	{
		scanf("%d",&total_resources[i]);
		available[i]=total_resources[i];
	}
	printf("Enter the maximum number of instance's of each resource the processes require = \n");
	for(i=0;i<maxn;i++)
	{
		printf("Enter the resources requirement for process P%d = ",i);
		for(j=0;j<maxr;j++)
			{
				scanf("%d",&max[i][j]);
				need[i][j]=max[i][j];
				if(max[i][j]>available[j])
				{
					printf("Error!! Maximum required instance of a resource cann't be greater than available instance's\n");
					getch();
					return -1;
				}
			}
	}
	pthread_t threads[maxn];
	//Creating maxn threads.
	for(i=0;i<maxn;i++)
		pthread_create(&threads[i],NULL,generic_thread,(void *)i);
	while(1)
	{
		menu();
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
				show_status();
				getch();
				continue;
			case 2:
				initiate_request();
				continue;
			case 5:
				printf("Program terminated press enter to exit.........\n");
				getch();
				return 0;
			default:
				printf("Invalid choice press enter to continue..........\n");
				getch();
				continue;
		}
	}
	return 0;
}