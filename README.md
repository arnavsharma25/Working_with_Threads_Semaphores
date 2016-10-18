# Working_with_Threads_Semaphores

Project Description given below.  The following rules apply:<br />

Customer:<br />
1)	50 customers visit the Post Office (1 thread per customer up to 50), all created initially.<br />
2)	Only 10 customers can be inside the Post Office at a time.<br />
3)	Each customer upon creation is randomly assigned one of the following tasks:<br />
a)	buy stamps<br />
b)	mail a letter<br />
c)	mail a package<br />
4)	Times for each task are defined in the task table.<br />


Postal Worker:<br />
1)	3 created initially, one thread each.<br />
2)	Serves next customer in line.<br />
3)	Service time varies depending on customer task.<br />


Scales:<br />
1)	Used by the postal worker when mailing a package.<br />
2)	There is only one, which can only be used one at a time.<br /> 
3)	The scales are not a thread.  They are just a resource the postal worker threads use.<br />


Other rules:<br />
1)	A thread should sleep 1 second in the program for each 60 seconds listed in the table.<br />
2)	All mutual exclusion and coordination must be achieved with semaphores.<br />
3)	A thread may not use sleeping as a means of coordination.<br />
4)	Busy waiting (polling) is not allowed.<br />
5)	Mutual exclusion should be kept to a minimum to allow the most concurrency.<br />
6)	Each thread should print when it is created and when it is joined.<br />
7)	Each thread should only print its own activities.  The customer threads prints customer actions and the postal worker threads prints postal worker actions.<br />
8)	Your output must include the same information and the same set of steps as the sample output.<br />


 
Output:<br />
<br />
1)	Each step of each task of each thread should be printed to the screen with identifying numbers so it is clear which threads are involved.<br />
2)	Thread output sample.  The wording in your output should exactly match the sample.<br />
<br />
Simulating Post Office with 50 customers and 3 postal workers<br />
<br />
-Customer 0 created<br />
-Customer 0 enters post office<br />
…<br />
-Customer 9 created<br />
-Customer 9 enters post office<br />
-Customer 10 created<br />
-Customer 11 created<br />
…<br />
-Customer 49 created<br />
-Postal worker 0 created<br />
-Postal worker 0 serving customer 0<br />
-Postal worker 2 created<br />
-Postal worker 2 serving customer 1<br />
-Postal worker 1 created<br />
-Postal worker 1 serving customer 2<br />
-Customer 0 asks postal worker 0 to buy stamps<br />
-Customer 2 asks postal worker 1 to mail a package<br />
-Customer 1 asks postal worker 2 to mail a package<br />
-Scales in use by postal worker 1<br />
-Postal worker 0 finished serving customer 0<br />
-Customer 0 finished buying stamps<br />
-Postal worker 0 serving customer 3<br />
-Customer 3 asks postal worker 0 to mail a letter<br />
-Customer 0 leaves post office<br />
-Customer 10 enters post office<br />
-Joined customer 0<br />
-Scales released by postal worker 1<br />
-Postal worker 1 finished serving customer 2<br />
-Customer 5 asks postal worker 1 to mail a package<br />
-Scales in use by postal worker 2<br />
-Customer 2 finished mailing a package<br />
-Postal worker 1 serving customer 5<br />
-Customer 2 leaves post office<br />
-Postal worker 0 finished serving customer 3<br />
-Customer 3 finished mailing a letter<br />
-Postal worker 0 serving customer 4<br />
-Customer 4 asks postal worker 0 to mail a letter<br />
-Customer 3 leaves post office<br />
-Scales released by postal worker 2<br />
-Postal worker 2 finished serving customer 1<br />
-Scales in use by postal worker 1<br />
-Customer 1 finished mailing a package<br />
-Customer 1 leaves post office<br />
-Joined customer 1<br />
-Joined customer 2<br />
-Joined customer 3<br />
<br />
<br />
axs143930.c<br />
<br />
Commandline:<br />
<br />
1st: gcc axs143930.c -lpthread<br />
2nd: ./a.out<br />
<br />
