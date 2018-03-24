#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdbool.h>
#define MAXR 100
#define MAXN 100
const int maxn,maxr;
int total_resources[MAXR]={0};
int available[MAXR]={0}; 	//To store the available instances of the ith resource.
int max[MAXN][MAXR]; 		//To store the max number of resources of a given type,the process will allocate. 
int allocated[MAXN][MAXR]; 	//To store the allocated instance of each resource for the following process.
int need[MAXN][MAXR];		//To store the required number of instances of a resource a process needs in order to get completed.
bool is_finished[MAXN];	//To control each thread.
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
		is_finished[i]=false;
}
void menu()
{
	system("clear");
	printf("--------------------------Banker's Alogrithm--------------------------\n");
	printf("1. Check Status\n");
	printf("2. Allocate Resources\n");
	printf("3. See Safe Sequence\n");
	printf("4. Exit\n");
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


	//Available system resources
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
			printf("%d  ",need[i][j]);	
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
	return;
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
	printf("Enter the maximum number of instance's of each resource the processes reqiure = \n");
	for(i=0;i<maxn;i++)
	{
		printf("Enter the resources values for process P%d = ",i);
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
			case 4:
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