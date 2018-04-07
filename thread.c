void make_copy(int temp_available[maxr],int temp_allocated[maxn][maxr],int temp_need[maxn][maxr])
{
	for(int i=0;i<maxn;i++)
	{
		for(int j=0;j<maxr;j++)
			{
			temp_allocated[i][j]=allocated[i][j];
			temp_need[i][j]=need[i][j];
		}
	}
	for(int i=0;i<maxr;i++)
		temp_available[i]=available[i];
}
void terminate(int thread_id)
{
	for(int i=0;i<maxr;i++)
	{
		available[i]+=allocated[thread_id][i];
		allocated[thread_id][i]=0;
	}
		return;
}
void begin_termination()
{
	system("clear");
	status_module();
	int thread_id;
	while(1)
	{
		printf("\nEnter the process id you want to eliminate:");
		scanf("%d",&thread_id);
		if(!(thread_id>=0 && thread_id<maxn) || state[thread_id]==-1)
			printf("Error! Thread doesn't exist!!!\n");
		else
			break;
	}
	state[thread_id]=2;
	while(state[thread_id]==2);
	printf("Process Terminated!!!");
	getch();
	return;
}
void check_termination(int thread_id)
{
	for(int i=0;i<maxr;i++)
	{
		if(need[thread_id][i]!=0)
			return;
	}
	printf("The process P%d has completed! It will be now terminate.",thread_id);
	getch();
	state[thread_id]=2;
	while(state[thread_id]==2);
	return;
}
bool safety_algorithm(int temp_available[maxr],int temp_allocated[maxn][maxr],int temp_need[maxn][maxr])
{
	bool is_finished[maxn],found;
	int count=0,safe_sequence[maxn],terminated=0;
	for(int i=0;i<maxn;i++)
	{
		if(state[i]!=-1)
			is_finished[i]=false;
		else
			{
				is_finished[i]=true;
				safe_sequence[count++]=i;
			}
	}
	terminated=count;
	while(count<maxn)
	{
		found=false;
		for(int i=0;i<maxn;i++)
		{
			if(!is_finished[i])
			{
				int j;
                for (j=0;j<maxr;j++)
                    if (temp_need[i][j]>temp_available[j])
                        {
                        	printf("%d %d",temp_need[i][j],temp_available[j]);
                        	break;
                        }
                if (j==maxr)
                {
                    for (int k=0;k<maxr;k++)
                        temp_available[k]+=temp_allocated[i][k];
                    safe_sequence[count++]=i;
                    is_finished[i]=true;
                    found=true;
				}
			}
		}
		if(found==false)
		{
			return false;
		}
	}
	printf("\nThe Safe Sequence is:\n");
	for(int i=terminated;i<maxn;i++)
	{
		printf("%d ",safe_sequence[i]);
		if(i!=maxr-1 || (maxn-terminated)!=1)
			printf("-> ");
	}
	return true;
}
void show_safe_state()
{
	int temp_available[maxr],temp_allocated[maxn][maxr],temp_need[maxn][maxr];
	make_copy(temp_available,temp_allocated,temp_need);	
	safety_algorithm(temp_available,temp_allocated,temp_need);
	return;
}
void check_request(int thread_id,int res[])
{
	int temp_available[maxr],temp_allocated[maxn][maxr],temp_need[maxn][maxr];
	make_copy(temp_available,temp_allocated,temp_need);	
	for(int i=0;i<maxr;i++)
	{
		temp_allocated[thread_id][i]+=res[i];
		temp_need[thread_id][i]-=res[i];
		temp_available[i]-=res[i];
	}
	if(safety_algorithm(temp_available,temp_allocated,temp_need))
	{
		printf("\nResources allocated!!\n");
		for(int i=0;i<maxr;i++)
		{
			allocated[thread_id][i]+=res[i];
			need[thread_id][i]-=res[i];
			available[i]-=res[i];
	   }	
	}
	else
	{
		printf("\nThe Request is denied, as granting the request doesn't leave the system in a safe state!!");
	}
	return;
}
void request(int thread_id)
{
	int res[maxr];
	status_module();
	printf("\nEnter the values of resources for the process P%d = \n",thread_id);
	for(int i=0;i<maxr;i++)
	{
		while(1)
		{
		scanf("%d",&res[i]);
		if(res[i]>need[thread_id][i])
			printf("Error!! Process is requesting more resources than defined!!\nPlease Enter again!=\n");	
		else
			break;
		}
	}
	check_request(thread_id,res);
	getch();
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
	check_termination(thread_id);
	return;
}
void *generic_thread(void *data)
{
	int pthread_id=(int *)data;
	while(1)
	{
		if(state[pthread_id]==1)
		{
			request(pthread_id);
			state[pthread_id]=0;
		}
		else if(state[pthread_id]==2)
		{
			terminate(pthread_id);
			state[pthread_id]=-1;
			pthread_exit(NULL);
		}
	}
}