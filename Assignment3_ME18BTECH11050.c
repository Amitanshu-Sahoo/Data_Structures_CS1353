#include<stdio.h>
#include<stdlib.h>
#include<time.h>


struct tracknode{
	int lo ;		                                                    // Stores lower index
	int hi ;		                                                    // Stores higher index
	int ln ;		                                                    // Stores the line number to which the function call must return after execution
	struct tracknode* prev ;		                                    // Pointer for self referencing the structure
};

typedef struct tracknode tn ;		                                    // Used to create an alias name tn for the structure tracknode 
int p = 0 ;			                                                    // The variable is used to make proper indentations in the program

tn* tnpush(tn* head, int low, int high, int linenumber) ;		        // This function pushes a node into the recursion status stack
tn* tnpop(tn* head) ;		                                            // This function pops a node from the recursion status stack
int partition(int array[], int low,int high, int pivot) ;		        // This is the partition function used in the quicksort algorithm
void quicksort(int array[], int low, int high, tn* head) ;      		// Function prototype for quicksort algorithm
void print(tn* head, int p) ;		                                    // This function prints the whole stack showing the stack status

void print(tn* head, int p)
{
	tn* temp = NULL ;                                                   // The temp pointer is the temporary pointer required to print the whole stack
	temp = (struct tracknode*)malloc(sizeof(struct tracknode)) ;
	
	temp = head ;
	
	printf("\n") ;
	for(int i = p ;i > 1; --i){		                                    // Tabs are added in loop based on the value of p whose value depends on the level of recursion
		printf("\t") ;}
		
	printf("{") ;

	while(temp->prev != NULL)                                           // This while loop prints the whole stack
	{
		printf("(%d, %d, %d)",temp->lo,temp->hi,temp->ln) ;
		temp = temp->prev ;
		if(temp->ln != -1){
			printf(", ") ; }
	}
	printf("}") ;
	
	
}

tn* tnpush(tn* head, int low, int high, int linenumber)		            // Function definition for tracknode stack push function
{
	tn* newnode = NULL ;		                                        // Node to be added in the stack 
	newnode = (struct tracknode*)malloc(sizeof(struct tracknode)) ;
		
    newnode->prev = head ;

	newnode->lo = low ;		                                            // Assigning all the variables to the structure data
	newnode->hi = high ;
	newnode->ln = linenumber ;
	
	return newnode ;
	
}

tn* tnpop(tn* head)		                                                // Function definition for tracknode stack pop function
{
	tn* temp = NULL ;
	temp = (struct tracknode*)malloc(sizeof(struct tracknode)) ;		// Popping out the last node in the stack
	temp = head ;
	if(temp->prev != NULL){
	head = temp->prev ;
	temp->prev = NULL ;}
	
	free(temp) ;		// Freeing the structure pointer
	return head ;
	
}

int partition(int array[], int low,int high, int pivot)		            // Function definition of partition function 
{ 

    int s ;		// swapping the values using a third variable
	s = array[high] ;
	array[high] = array[pivot] ;
	array[pivot] = s ;

	int t = low-1 ;		//Index of smaller element
	
	for(int i = low; i<high; ++i){
		if(array[i]<array[high]){		// If current element is smaller than the pivot element value
			t = t + 1 ;			
			s = array[i] ;
	        array[i] = array[t] ;
	        array[t] = s ;	}
	}
	
	s = array[high] ;
	array[high] = array[t+1] ;
	array[t+1] = s ;
	return t+1 ;
}

void quicksort(int array[], int low, int high, tn* head)		        // Function definition of quicksort function
{																		// array[] - It is the array to be sorted
	srand(time(0)) ;																	// low - it is the starting index
	if(low>high){														// high - it is the ending index
		return ; }
	else{
		
		int piv =  low + rand()%(high-low+1) ;							// randomly choosing the pivot point among the values in the array 
		
		int q = partition(array,low,high,piv) ;							// Partitioning places the pivot element at the right place
        
		p+=1;															// Incrementing p for stack push
		head = tnpush(head,low,q-1,__LINE__+2) ;	                            // Pushing a node into the stack for quicksort function call
		print(head,p) ;									                // Printing the stack status after push
		quicksort(array,low,q-1,head) ;									// Quicksort call
		head = tnpop(head) ;										    // Poping a node from the stack marking the end of quicksort function call
		p-=1 ;															// Decrementing p for stack pop
		print(head ,p) ;                                                // Printing the stack status after pop	
		
		p+=1 ;															// Incrementing p for stack push
		head = tnpush(head,q+1,high,__LINE__+2) ;								// Pushing a node into the stack for quicksort function call
		print(head,p) ;                                                 // Printing the stack status after push
		quicksort(array,q+1,high,head) ;                                // Quicksort call
		head = tnpop(head) ;										    // Poping a node from the stack marking the end of quicksort function call
		p-=1 ;															// Decrementing p for stack pop	
		print(head ,p) ;												// Printing the stack status after pop		
		
		}		
}

int main()		                                                        // Main function
{
	int n ;		                                                        // variable to store number of elements in the unsorted array
	printf("This program tells the instantaneous recursion stack status. Please enter the number of numbers you want to sort \n") ;
	scanf(" %d", &n) ;
	printf("\n") ;
 
	int ar[n] ;		                                                    // Array declaration
	
	for(int i=0; i<n; ++i){		                                        // Taking value input from the user into the array
		printf("no.%d -",i+1) ;
		scanf(" %d", &ar[i]) ;}
	
	printf("\nEntered array :- \n") ;		                            // Printing the entered array
	printf("[") ;
	for(int j=0; j<n; ++j){
		printf(" %d ",ar[j]) ;}
	printf("]\n\n") ;
		
	tn* head = NULL ;		                                            // Declaration and Memory allocation of the head of the stack
	head = (struct tracknode*)malloc(sizeof(struct tracknode)) ;
	head->prev = NULL ;
	head->ln = -1 ;
	
	print(head,p) ;
	p+=1 ;																// Incrementing p for stack push
	head = tnpush(head,0,n-1,__LINE__+2) ;                                     // Pushing a node into the stack for quicksort function call
	print(head ,p) ;											        // Printing the stack status after push
	quicksort(ar,0,n-1,head) ;                                          // Quicksort call
	head = tnpop(head) ;											    // Poping a node from the stack marking the end of quicksort function call
	p-=1 ;	                                                            // Decrementing p for stack pop
	print(head,p) ;														// Printing the stack status after pop
	
    printf("\n\nSorted array :- \n") ;		                            // Printing the sorted array
    printf("[") ;
	for(int j=0; j<n; ++j){
		printf(" %d ",ar[j]) ;}
	printf("]") ;
}
