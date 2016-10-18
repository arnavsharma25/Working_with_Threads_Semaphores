#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h> 
#include <string.h>
#include <semaphore.h>
#include <pthread.h>
#include <time.h>

int pfds[2],pfds1[2],pfds2[3],result,true=1;
sem_t cust_ready,office_full,mutexcustomerID,mutexpostworkerID,mutexpostworkerorder,mutexscale,mutex1,mutex2,postworker,workdone[50],PWworktype[50],postworkerorderopen[3];

void *customerfunction();
void *postworkerfunction();
void scales();

int main()
{	
	//Pipes
	fflush(stdout);
	result=pipe(pfds);
   	if(result==-1)
   		exit(1);
   	result=pipe(pfds1);
   	if(result==-1)
   		exit(1);
   	result=pipe(pfds2);
   	if(result==-1)
   		exit(1);
   	fflush(stdout);

   	
	pthread_t postworkerthread[3],custthread[50];  //Initializing Threads
	int i;
	for(i=0;i<50;i++) //Intializing Semaphores
		sem_init(&workdone[i],0,0);
	i=0;
	for(i=0;i<3;i++)
		sem_init(&postworkerorderopen[i],0,0);
	i=0;
	for(i=0;i<50;i++)
		sem_init(&PWworktype[i],0,0);
	sem_init(&cust_ready,0,0);   //Intializing semaphores
	sem_init(&postworker,0,0);
	sem_init(&office_full,0,10);
	sem_init(&mutexcustomerID,0,1);
	sem_init(&mutexpostworkerID,0,1);
	sem_init(&mutexpostworkerorder,0,1);
	sem_init(&mutexscale,0,1);
	sem_init(&mutex1,0,1);
	sem_init(&mutex2,0,1);
	    
    int cust_num,threadfail,custID[50],pwID[3],pwnum,*out; //Creating Threads

    for(cust_num=0;cust_num<50;cust_num++)
    {	
    fflush(stdout);
    custID[cust_num]=cust_num;
	printf("Customer %d created\n",custID[cust_num]); //Printing out which customer would be created
	fflush(stdout);
    	threadfail=pthread_create(&custthread[cust_num],NULL,customerfunction,&custID[cust_num]);   //Customer Thread
    	if (threadfail)
    	{
         	printf("Thread fail; return code from pthread_create() is %d\n", threadfail); //If thread fails print this message
         	exit(1);
      	}
    }
    for(pwnum=0;pwnum<3;pwnum++)
    {
    	pwID[pwnum]=pwnum;
    	threadfail=pthread_create(&postworkerthread[pwnum],NULL,postworkerfunction,&pwID[pwnum]);   //Postal Worker Thread
    	if (threadfail)
    	{
         	printf("Thread fail; return code from pthread_create() is %d\n", threadfail);   //If thread fails print this message
         	exit(1);
      	}
    }
    for(cust_num=0;cust_num<50;cust_num++)
    {
    	pthread_join(custthread[cust_num],(void*)&out);       //Join Thread i.e. when customers leave
    	if(*out==cust_num)
      		printf("Joined Customer %d \n",*out);
    }
}

void sleeptime(int a)
{
	sleep(a);
}

void *postworkerfunction(void* threadid) //function for postworker
{
	int postworkerID1,PWservingCustID,yy;
	fflush(stdout);
	postworkerID1=*(int*)threadid;   //
	fflush(stdout);
	printf("Postal Worker %d created\n",postworkerID1);   //printing of postworker number when created
	fflush(stdout);


	do
	{
		sem_post(&postworker);  //Sending signal saying that postal worker is ready and running
		sem_wait(&cust_ready);  //waiting on customer to be ready
		fflush(stdout);
		sem_wait(&mutexcustomerID);  //mutual exclusion for customer ID
		read(pfds[0], &PWservingCustID, sizeof(int));  //Reading postal worker customer ID from customer function
		sem_post(&mutexcustomerID);  //mutual exclusion for customer ID
		printf("Postal worker %d serving customer %d\n",postworkerID1,PWservingCustID);  //printing postal worker ID along with the ID of serving customer
		fflush(stdout);
		sem_wait(&mutexpostworkerID);  // mutual exclusion for writing data
		write(pfds1[1], &postworkerID1, sizeof(postworkerID1));  //Writing postel worker ID to customer function
		sem_post(&PWworktype[PWservingCustID]);  //sending signal and releasing by saying that postal worker ID has been sent
		sem_post(&mutexpostworkerID);   //mutual exclusion
		sem_wait(&postworkerorderopen[postworkerID1]);   // waiting on postal worker order number open
		sem_wait(&mutexpostworkerorder);  //mutual exclusion
		read(pfds2[0], &yy, sizeof(yy));   // reading the work order from customer function
		sem_post(&mutexpostworkerorder);  //mutual exclusion for reading from customer function
		if(yy==0)   //checking of the recieved order is for mailing package,mailing letter,buying stamps
			sleeptime(1.5);  //if mailing letter wait for 1.5 seconds	
		else if(yy==1)
			sleeptime(1);   //if buying stamps wait for 1 second
		else if(yy==2)
			scales(postworkerID1);  //if mailing package wait for 2 seconds
		
		printf("Postal worker %d finished serving Customer %d\n",postworkerID1,PWservingCustID);  //printing on which postal worker finished serving which customer
		
		sem_post(&workdone[PWservingCustID]); //sendings signal that postal worker has finished doing its work



		fflush(stdout);
	}while(!0);

}

//Scales function
void scales(int postID)
{
	sem_wait(&mutexscale);  //mutual exclusion for scaling
	printf("Scales in use by postal worker %d\n",postID); //printing on scales used by postal worker
	fflush(stdout);
	sleeptime(2);  //is scales used then sleep for 2 seconds
	printf("Scales released by postal worker %d\n",postID);  //printing on scales released
	sem_post(&mutexscale); //mutual exclusion for scaling
	fflush(stdout);
}
void workorder(int customerID, int postworker_ID, int tasknumber)
{
	if(tasknumber==0)   //randomly number created related to task
		printf("Customer %d asks postal worker %d to mail a letter \n",customerID,postworker_ID);
	else if(tasknumber==1)
		printf("Customer %d asks postal worker %d to buy stamps \n",customerID,postworker_ID);
	else if(tasknumber==2)
		printf("Customer %d asks postal worker %d to mail a package \n",customerID,postworker_ID);
	fflush(stdout);
}
void workcompletion(int customer_ID, int tasknumber)
{
	if(tasknumber==0)  
		printf("Customer %d finished mailing letter \n",customer_ID);
	else if(tasknumber==1)
		printf("Customer %d finished buying stamps \n",customer_ID);
	else if(tasknumber==2)
		printf("Customer %d finished mailing package \n",customer_ID);
	fflush(stdout);
}
//Customer function
void *customerfunction(void* threadid)
{
	int custID,randtask,postworkerID;
	fflush(stdout);
	custID=*(int*)threadid;
	sem_wait(&office_full);  //waiting on for post office to get full
	printf("Customer %d enters post office\n",custID);   //printing on which customer enters the post office
	fflush(stdout);
	sem_wait(&postworker);  //waiting for postal worker 
	sem_wait(&mutexcustomerID);   //waiting on mutual exclusion for writing data to postworker function
	int x;
	x=custID;
	write(pfds[1],&x,sizeof(x));  //writing customer ID to postalworker function
	randtask=rand()%3;     //Randomly Creating numbers between 0 to 2
	sem_post(&cust_ready);   //waiting customer to be ready
	sem_post(&mutexcustomerID);   //mutual exclusion for reading data
	sem_wait(&PWworktype[x]);   //waiting for customer to send signal for asking for work type of postal worker
	sem_wait(&mutexpostworkerID);  //mutual exclusion for reading ID of postal worker
	read(pfds1[0],&postworkerID,sizeof(postworkerID));
	//(pfds1[0], &postworkerID, sizeof(postworkerID));
	sem_post(&mutexpostworkerID);  //mutual exclusion for reading ID of postal worker
	fflush(stdout);
	//Work order for customer
	workorder(custID,postworkerID,randtask);
	fflush(stdout);
	sem_wait(&mutexpostworkerorder);  //mutual exclusion for waiting on writing onto postworker function
	write(pfds2[1], &randtask, sizeof(randtask)); //writing task number
	sem_post(&postworkerorderopen[postworkerID]);  //sending signal stating that postworker work is open
	sem_post(&mutexpostworkerorder);  //mutual exclusion for waiting on writing onto postworker function
	sem_wait(&workdone[custID]);  //waiting on for customer to compete its work
	workcompletion(custID,randtask);  // printing on when the customer has finished mailing package, buying or mailing letter
	fflush(stdout);
	printf("Customer %d leaves post office\n",custID);   //printing when customer leaves post office
	fflush(stdout);
	sem_post(&office_full);   //sending signal when then office capcaity is full
	pthread_exit(threadid);  //exit the thread when the work is complete

}
