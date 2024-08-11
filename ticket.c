#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int ticketAmount = 2 ;
sem_t mutex;

void* TicketAgent(void* arg)
{
	
	sem_wait(&mutex);	

	int t = ticketAmount;
	if(t>0)
	{
		printf("sold you one ticket\n");

		t--;
	}
	printf("Ticket sold out\n");	
	ticketAmount = t;

	sem_post(&mutex);
	pthread_exit(0);
}

int main()
{
	sem_init(&mutex,0,1);
	pthread_t tid[2];
	for(int i=0;i<2;i++)
	{
		pthread_create(tid+1,NULL,TicketAgent,NULL);
	}
	for(int i=0;i<2;i++)
	{
		pthread_join(tid[i],NULL);
	}
				
	printf("The left ticket is %d\n",ticketAmount);



return 0;
}
