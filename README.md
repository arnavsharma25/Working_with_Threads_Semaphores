# Working_with_Threads_Semaphores

Project Description given below.  The following rules apply:

Customer:
1)	50 customers visit the Post Office (1 thread per customer up to 50), all created initially.
2)	Only 10 customers can be inside the Post Office at a time.
3)	Each customer upon creation is randomly assigned one of the following tasks:
a)	buy stamps
b)	mail a letter
c)	mail a package
4)	Times for each task are defined in the task table.


Postal Worker:
1)	3 created initially, one thread each.
2)	Serves next customer in line.
3)	Service time varies depending on customer task.


Scales:
1)	Used by the postal worker when mailing a package.
2)	There is only one, which can only be used one at a time. 
3)	The scales are not a thread.  They are just a resource the postal worker threads use. 


Other rules:
1)	A thread should sleep 1 second in the program for each 60 seconds listed in the table.  
2)	All mutual exclusion and coordination must be achieved with semaphores.  
3)	A thread may not use sleeping as a means of coordination.  
4)	Busy waiting (polling) is not allowed. 
5)	Mutual exclusion should be kept to a minimum to allow the most concurrency.
6)	Each thread should print when it is created and when it is joined.
7)	Each thread should only print its own activities.  The customer threads prints customer actions and the postal worker threads prints postal worker actions.  
8)	Your output must include the same information and the same set of steps as the sample output.


 
Output:

1)	Each step of each task of each thread should be printed to the screen with identifying numbers so it is clear which threads are involved.  
2)	Thread output sample.  The wording in your output should exactly match the sample.

Simulating Post Office with 50 customers and 3 postal workers

-Customer 0 created
-Customer 0 enters post office
…
-Customer 9 created
-Customer 9 enters post office
-Customer 10 created
-Customer 11 created
…
-Customer 49 created
-Postal worker 0 created
-Postal worker 0 serving customer 0
-Postal worker 2 created
-Postal worker 2 serving customer 1
-Postal worker 1 created
-Postal worker 1 serving customer 2
-Customer 0 asks postal worker 0 to buy stamps
-Customer 2 asks postal worker 1 to mail a package
-Customer 1 asks postal worker 2 to mail a package
-Scales in use by postal worker 1
-Postal worker 0 finished serving customer 0
-Customer 0 finished buying stamps
-Postal worker 0 serving customer 3
-Customer 3 asks postal worker 0 to mail a letter
-Customer 0 leaves post office
-Customer 10 enters post office
-Joined customer 0
-Scales released by postal worker 1
-Postal worker 1 finished serving customer 2
-Customer 5 asks postal worker 1 to mail a package
-Scales in use by postal worker 2
-Customer 2 finished mailing a package
-Postal worker 1 serving customer 5
-Customer 2 leaves post office
-Postal worker 0 finished serving customer 3
-Customer 3 finished mailing a letter
-Postal worker 0 serving customer 4
-Customer 4 asks postal worker 0 to mail a letter
-Customer 3 leaves post office
-Scales released by postal worker 2
-Postal worker 2 finished serving customer 1
-Scales in use by postal worker 1
-Customer 1 finished mailing a package
-Customer 1 leaves post office
-Joined customer 1
-Joined customer 2
-Joined customer 3


axs143930.c

Commandline:

1st: gcc axs143930.c -lpthread
2nd: ./a.out

