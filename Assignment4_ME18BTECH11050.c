#include<stdio.h>                                                       
#include<stdlib.h>
#include<time.h>

struct jobnode{			//Structure to store the jobs                                                      
	int job_no ;			//This variable stores the job number 
	int job_time ;			//This variable stores the total time left for the job to be serviced
	int time_left ;			//This is a special variable that stores the time left in a single cycle of service .Its value is initialised to 50 if job_time > 50 and to job time if job time is less than 50
	struct jobnode* next ;			// The next and prev structure pointers point respectively to the next and previous nodes in the queue
	struct jobnode* prev ; };

typedef struct jobnode jns ;			// Typedef to create an alias name jns for the structure

jns* queue_create(int n,int p) ;			// Function to create a queue
jns* enqueue(jns* newnode,jns* rear) ;			//Function to enqueue a node to the rear of the queue
jns* dequeue(jns* front) ;			//Function to dequeue a node from the front of the queue
void print(jns* front) ;			//Function to print the queue showing the job time left
void rr_scheduling(jns* front) ;			//Function to carry out the round robin scheduling and print the status of the queue at 50us interval
int power(int m, int n) ;			//Function to calculate  m to the power n 

int power(int m, int n)			// Function definition 
{
	int s =1 ;                                                          //Simple function just to find out the vale of m to the power n
	for(int i =1 ;i<=n; ++i){
		s = s*m ; }
	return s ;
}

jns* queue_create(int n,int p)			//Function definition.The variable n represents the number of nodes to be ceated in the queue. p represents the start point of the count in job_number variable.
{
	jns* front = NULL ;                                                 // Front node of the queue is declared here
	front = (struct jobnode*)malloc(sizeof(struct jobnode)) ;
	srand(time(0)) ;
	front->job_time = rand()%301 ;                                      //Since it is the first node of the queue the next and prev pointers are initially set to NULL
	front->next = NULL ;                                                //Other variables such as the job_no ,time_left, job_time are initialised
	front->prev = NULL ;
	front->job_no = 1 + p ;                                             //Job number is also updated dependent on the value of p
	if(front->job_time <50){                                            //time_left variable is updated based on the condition given in the if statement as explained in the earlier comments.
		front->time_left = front->job_time ;}
	else{
		front->time_left = 50 ;}
	if(n==1){                                                           //If the number of nodes to be made in the queue is 1 then the execution of the program is stopped here and the front node is returned
		return front ;                                                  //If not then the else statement is followed to add more nodes
	}
	else{
	jns* rear = NULL ;                                                  //rear node is made in the same way as the front node and initially added behind the front node
	rear = (struct jobnode*)malloc(sizeof(struct jobnode)) ;            
	
	rear->job_time = rand()%301 ;
	rear->next = front;
	rear->prev = NULL ;
	rear->job_no = 2 + p ;
	front->prev = rear ;
	if(rear->job_time <50){
		rear->time_left = rear->job_time ;}
	else{
		rear->time_left = 50 ;}
	
	for(int i = p ;i< p + n-2; ++i){                                    //This loop adds further nodes to the queue if n is greter than 2.
		jns* newnode = NULL ;                                           //The enqueue function is used in this purpose . The new node is enqueued at the rear and the enqueued node is denoted as rear.
		newnode = (struct jobnode*)malloc(sizeof(struct jobnode)) ;
	    newnode->job_time = rand()%301 ;
	    newnode->job_no =i+3 ;
		rear = enqueue(newnode,rear) ;}
	    
	return front ;}
}

jns* enqueue(jns* newnode,jns* rear)			//Function definitiion
{   
	if(newnode == NULL){                                                //If the newnode given in the function is NULL, the rear node of the queue is itself returned
		return rear ;}
	else{	
	if(newnode->job_time < 50){                                         //The time_left variable of the newnode is updated in the manner described above
		newnode->time_left = newnode->job_time ;}
	else{
		newnode->time_left = 50 ;}
		
	newnode->next = rear ;                                              //The next pointer of the newnode is pointed to the rear node
	rear->prev = newnode ;                                              //and the prev pointer of rear node is pointed to the newnode
	newnode->prev = NULL ;                                              //prev pointer of the newnode is kept NULL as it is now the rear most node of the queue.
	return newnode ;}                                                   //newnode is then returned
}

jns* dequeue(jns* front)			//Function definition
{
	if(front->next ==NULL && front->prev==NULL){                        //If the node to be dequeued is the last node in the queue the function simply returns back the last node.
		return front ;
	}
	else{
		jns* temp = NULL ;                                              //This temp node takes the front value of the front node to be deleted
		temp = (struct jobnode*)malloc(sizeof(struct jobnode)) ;        //It then assigns the front node to its own previous node.
		                                                                //After this temp->prev is initialised to NULL as the temp is being dequeued .
		temp = front ;                                                  //the next pointer of the previous node to which is now the front node still points to the temp variable
        front = temp->prev ;                                            //It is set to null depending on whether the dequeued variable will be enqueued at the rear or not
		temp->prev = NULL ;
		
		return front;	
	}
}

void print(jns* front)			//Function definition
{
	jns* temp = NULL ;
	temp = (struct jobnode*)malloc(sizeof(struct jobnode)) ;

	temp = front ;                                                      // This function simply prints the job done in the present status .
	while(temp->prev != NULL){
		printf("J[%d]:%d ;",temp->job_no,temp->job_time) ;
		temp = temp->prev ;}
	    printf("J[%d]:%d ",temp->job_no,temp->job_time) ;	
}

void rr_scheduling(jns* front)			//Function definition
{
	jns* node_temp = NULL ;                                             //The node_temp node helps in enqueueing the dequeued front node to the rear of the queue
	node_temp = (struct jobnode*)malloc(sizeof(struct jobnode)) ;
	jns* rear = NULL ;                                                  //This node is set to the last element of the queue
	rear = (struct jobnode*)malloc(sizeof(struct jobnode)) ;
	jns* adder = NULL ;                                                 //This node helps in adding new nodes to the queue after 200us interval as per the question
	adder = (struct jobnode*)malloc(sizeof(struct jobnode)) ;
	int quanta = 50 ;                                                   //This variable stores the smallest fraction of time after which the status of queue has to be printed
	int p = 0 ;                                                         //The variable p is used to keep track of the number of quantas passed
	int m = 0 ;                                                         //The variable m helps in deciding the number of new nodes to be added at the end of every 200us interval
	int g = 0 ;                                                         //This variable stores the number of new nodes to be added at the end of 200us intervals
	int length ;                                                        //Stores the current length of the queue
	printf("The initial job queue :- ");                           
	print(front) ;                                                      //Printing the initial queue status
	
	rear = front ;
	while(rear->prev != NULL){                                          //Assigning the rear node to the end of the queue
		rear = rear->prev ;  }
		length = rear->job_no ;

	while(1){                                                           //This endless loop terminates when there is no node left in the queue 
		
		if(quanta == 0){                                                //This if statement prints the queue status at the end of every quanta and updates the quanta of time for the next  
			p += 1 ;                                                    //iteration untill the queue is exhausted
			printf("\n\nQueue at the end of %d us :", p*50) ;
			print(front) ;
			quanta = 50 ;  }
			
		if(p != 0 && p%4 == 0 && m!=7){                                 //This if statement adds the new nodes to the queue depending upon the value of the variables described above
			g = 64/power(2,m) ;                                         //g here is stroing the number of new nodes to be added .It is in the order 64 then 32 then 16 then 8 and so on uptil 1
			adder = queue_create(g,length) ;                            //Adder is assigned the new queue of nodes
			length = length + g ;
			m += 1 ;
			adder->next = rear ;                                        //Here the adder is linked to the rear of the old queue and the red node is assigned to the end of the updated queue
			rear->prev = adder ;
			while(rear->prev != NULL){
				rear = rear->prev ;}	
		}
			
		while(quanta != 0){
			if(front->time_left < quanta){                              //If time left for a job to be serviced if less than the present time in the quanta then this part of 
				quanta = quanta - front->time_left ;                    //the program is run .
				front->job_time =  front->job_time - front->time_left ; //Here the time is deducted from the quanta and since service time of the job is over for the present time_left
				front->time_left = 0 ;                                  //variable is assigned to 0.
				if(front->job_time > 0){                                
		            front = dequeue(front) ;                            //If the total job time is still greater than 0,the node is dequeued and enqueued at the end 
		            node_temp = front->next ; 
		            rear = enqueue(node_temp,rear) ;
		            front->next = NULL ;
				}
				else if(front->job_time <= 0 && front->next == NULL && front->prev == NULL){
					printf("\n\nEmpty") ;                                 //If the job at hand happens to be the last node and its total job time is over then "Empty" is printed and returned
					return ; }
				else{                                                   //Else if the job time of the job is over then the node is permanently dequeued.
					front = dequeue(front) ;
					front->next = NULL ; }
				}
			else if(front->time_left > quanta){                         //If time left is greater then the quanta time available in hand then quanta time is deducted from the time_left variable  
				front->time_left =  front->time_left - quanta ;         //,quanta is set to 0 . The node is not dequeued as its service time is still left.
				front->job_time = front->job_time - quanta ;
				quanta = 0 ; }
			else{                                                       //If the time_left and quanta are equal then both are set to zero and the further procedure on the node is carried as in the  
				front->job_time = front->job_time - front->time_left ;  //first case.
				front->time_left = 0 ;
				quanta = 0 ;
				if(front->job_time > 0){
		            front = dequeue(front) ;
		            node_temp = front->next ; 
		            rear = enqueue(node_temp,rear) ;
		            front->next = NULL ;
				}
				else if(front->job_time <= 0 && front->next == NULL && front->prev == NULL){
					printf("\n\nEmpty") ;
					return ; }
				else{
					front = dequeue(front) ; 
					front->next = NULL ;}
				}
			}			
          }
}

int main()
{
	jns* start = NULL ;                                                 //In the main function the job queue is created and scheduled using the rr scheduling function.
	start = (struct jobnode*)malloc(sizeof(struct jobnode)) ;
	start = queue_create(100,0) ;
	print(start) ;
    rr_scheduling(start) ;    
}

