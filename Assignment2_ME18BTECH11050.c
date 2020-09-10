
#include<stdio.h>
#include<stdlib.h>


struct matnode{  //Structure to denote each node in the matrix
   int v ;  //Stores the value in the node
   int row ;  //stores the row in which the element is present
   int col ;  //stores the column in which the matrix is present
   struct matnode* next ;	//Pointer to point to the next element in the row
   struct matnode* below ;	//Pointer to point to the below element in the column
};

typedef struct matnode mn ;  //typedef to create alias

struct matnode* creatematrix(FILE *ptr);    //Function to read the matrix from a file and create the linked list matrix                                //Function prototypes
void multiply(mn* head1, mn* head2, FILE* ptr);    //Function to multiply two matrices
void symmetry(mn* head) ;    //Function to find if a certain matrix is symmetric
int findelement(int i , int j, mn* head) ;    //Function to find the (i,j) element in the matrix
int matcomp(mn* head1,mn* head2) ;    //Function to compare the column dimension of first matrix with the row dimension of the second matrix.(utility function used in the multiplication function)
int square(mn* head) ;    //Used to check if the matrix is a square matrix or not
void print(mn* head) ;    //Function to print the read matrix


struct matnode* creatematrix(FILE *ptr)		//Function definition of creatematrix
{
	int b;		// variable to read the integer element from the file
	int l=1 , k=1 ;		//Variable to keep track of the row and column of the present element being read
	int y ;		//Variable that stores the nnumber of columns in the matrix
	int j = 0;		//Utility variable used to stop certain parts of the function from executing until the first semicolon is detected in the file
	int t ;		// Variable to store the return value from the scan function 
	char c ;		// variable to read the character element from the file		
//***************************************************************************************************************************************************************************
	mn* head = NULL ;                                                   //This part of the function initializes four pointer nodes head,temp1,temp2,temp3 .These pointer will 
	mn* temp1 = NULL ;                                                  //be used manipulate the linkedlist matrix while creating them.Initially the first node of the matrix 
	mn* temp2 = NULL ;                                                  //has been created as can be seen.
	mn* temp3 = NULL ;
	head = (struct matnode*)malloc(sizeof(struct matnode)) ;
	temp1 = (struct matnode*)malloc(sizeof(struct matnode)) ;           //Initially temp1,temp2 and temp3 are assigned to the head pointer to start from there .
	temp2 = (struct matnode*)malloc(sizeof(struct matnode)) ;
	temp3 = (struct matnode*)malloc(sizeof(struct matnode)) ;
	temp1 = head ;
	temp2 = head ;
	temp3 = head ;

	temp1->row = 1 ;
	temp1->col = 1 ;
//*************************************************************************************************************************************************************************** 
	while(1)                                                            //This while loop carries out the whole function of making the matrix including all the error checks
	{                                                                   //in the matrix.
		t = fscanf(ptr,"%d",&b);                                        //This statement takes the integer input from the file
                                                                        
		if(temp1->row == 1 && temp1->col == 1)                          //This if statement is executed only once in the first to decide upon the future course of action
		{                                                               //after this
			if(t == -1)                                                 //If there is some error in the file in the starting then the function returns with discripancy message
			{
				printf("\nDiscripancy in the text file format\n");
				return NULL ;
			}                                                           //****************************************************************************************************
			else                                                        //If there is no discrepancy in the starting of the file then this else statent is run which enters
			{                                                           //the data into the first node and then goes for the character check
				temp1->v = b ;

				t = fscanf(ptr,"%c",&c) ;                               //Character check
                                                                        //****************************************************************************************************
				if(c==',')
				{
					temp1->next = (struct matnode*)malloc(sizeof(struct matnode)) ;
					temp1->below = NULL ;                               //If there is a comma after the first element then a node is created next to the present node and the 
					temp1 = temp1->next ;                               //below pointer of the next node is made null.Count of the column and the row is kept
					temp1->row = 1;
					temp1->col = 2;
					l = 2;
				}                                                       //***************************************************************************************************
				else if(c == ';')                                       //If semicolon is present then a new node is created below the existing node and the next pointer is 
				{                                                       //made null. Count of the column and row is kept
					temp1->next = NULL ;
					temp1->below = (struct matnode*)malloc(sizeof(struct matnode)) ;
					temp1 = temp1->below ;
					k = 2 ;
					y = l ;
					temp1->row = k ;
					temp1->col = l ;
					temp2 = temp1 ;
					
				}                                                       //****************************************************************************************************
				else
				{
					t = fscanf(ptr,"%c",&c);
					if(feof(ptr))
					{                                                   //If comma and semiclon are not present then this part of the function checks if the file has ended 
						temp1->next = NULL ;                            //If the file end then the function establishes remaning pointer relationships between  nodes and 
						temp1->below = NULL ;                           //returns head .If the end of file is not reached and the comma and semicolon are absent , that means
						{                                               // there will be some discrepancy with file text format and is inconsistent with the given format.
							temp1 = head ;
							temp2 = head ;
							temp3 = head ;
							while(temp3->below != NULL)
							{
								temp1 = temp3 ;
								temp2 = temp3 ;

								temp2 = temp2->below ;
								while(temp1->next != NULL)
								{
									temp1 = temp1->next ;
									temp2 = temp2->next ;
									temp1->below = temp2 ;
								}

								temp3 = temp3->below ;
							}
						}
						return head ;
					}                                                   //******************************************************************************************************
					else                                                //This else statement is executed if there is no comma,semicolon or end of file character and the end of
					{                                                   //first integer.
						printf("\nDiscrepancy in the text file format\n") ;
						return NULL ;
					}
				}

			}
		}                                                               //******************************************************************************************************
		else                                                            //This else statement is always executed after the first iteration .  
		{
			if(t==-1)                                                   //This checks if the an integer has been read or not .If not, then there is discrepancy in the file
			{                                                           //format
				printf("\nDiscrepancy in the text file format\n") ;
				return NULL ;
			}                                                      
			else                                                        //******************************************************************************************************
			{
				temp1->v = b ;                                          //If there is no fault then this else statement is executed.It inputs the value of the matrix at the current 
				temp1->below = NULL ;                                   //temp1 position.The function then scans for the character.

				t = fscanf(ptr,"%c",&c) ;

				if(c == ',')                                            //If comma is present then the below pointer is made null and a new node is created next to the present node
				{
					temp1->next = (struct matnode*)malloc(sizeof(struct matnode)) ;
					temp1 = temp1->next ;
					l = l + 1 ;
					temp1->col = l ;
					temp1->row = k ;
				}                                                       //******************************************************************************************************
				else if(c == ';')                                       //If comma is present,this part of the function first checks if this is the first iteration of this else
				{                                                       //statement.If this is the first time run then the variable y is updated with the number of columns
                                                                        //This variable y denotes the number of columns in the first row.In the subsequent iteration if semicolon 
					if(j==1)                                            //is detected and at the same time if the number of columns in the subsequent row dont match with number
					{                                                   //of columns in the first row ,then an error message is shown.
						if( l != y )
					    {
						    printf("\nDiscrepancy in the text file format\n");
						    return NULL ;
					    }

					else
					{
						temp1->next = NULL ;
						temp1 = temp2 ;
						temp1->below = (struct matnode*)malloc(sizeof(struct matnode)) ;
						temp1 = temp1->below ;
						k = k + 1 ;
						y = l ;
						l = 1 ;
						temp1->row = k ;
						temp1->col = l ;
						temp1->below = NULL ;
						j = 1;
						temp2 = temp1 ;
					}
				   }
				   else
				   {

						   temp1->next = NULL ;
						   temp1 = temp2 ;
						   temp1->below = (struct matnode*)malloc(sizeof(struct matnode)) ;
						   temp1 = temp1->below ;
						   k = k + 1 ;
						   y = l ;
						   l = 1 ;
						   temp1->row = k ;
						   temp1->col = l ;
						   temp1->below = NULL ;
						   j = 1;
						   temp2 = temp1 ;
					}

				}                                                       //*******************************************************************************************************
				else
				{
					if(j==1)
					{
					   if(l != y )
					   {
						   printf("\nDiscrepancy in the text file format\n");
						   return NULL ;
					   }

					else
					{
						t = fscanf(ptr,"%c",&c) ;
						if(feof(ptr))
						{
							temp1->next = NULL ;                        //This part of the function is executed after atleast one semicolon is detedted in the file and if no comma and semicolon
							temp1->below = NULL ;                       //are there.If number of columns in the present row is not equal to y then an error message is displayed .
							                                            //else remaining pointer relationships are established and head pointer is return if end of file is detected.
							{                                           //If end of file is not detected then error message is displayed .
							      //temp1 = head ;
							      //temp2 = head ;
							      temp3 = head ;
							      while(temp3->below != NULL)
							      {
								      temp1 = temp3 ;
								      temp2 = temp3 ;

								      temp2 = temp2->below ;
								      while(temp1->next != NULL)
								      {
									      temp1 = temp1->next ;
									      temp2 = temp2->next ;
									      temp1->below = temp2 ;
								      }

						         		  temp3 = temp3->below ;
							      }
						   }
							return head ;
						}
						else
						{
							printf("\nDiscrepancy in the file format\n") ;
							return NULL ;
						}
					}
				   }                                                    //************************************************************************************************************                                   
				   else{                                                //This else statement is executed only if no semicolon is detected in the file as of .This function of 
						    t = fscanf(ptr,"%c",&c) ;                   //these statements are same as those of just the above ones but they work only in a single row matrix
						    if(feof(ptr))                               
					        {
						       temp1->next = NULL ;
						       temp1->below = NULL ;

							   {   

							      temp3 = head ;
							      while(temp3->below != NULL)
							      {
								      temp1 = temp3 ;
								      temp2 = temp3 ;

								      temp2 = temp2->below ;
								      while(temp1->next != NULL)
								      {
									      temp1 = temp1->next ;
									      temp2 = temp2->next ;
									      temp1->below = temp2 ;
								      }

						         		  temp3 = temp3->below ;
							      }
						       }

							   return head ;
					     	}
						    else
						    {
							    printf("\nDiscrepancy in the file format\n") ;
							    return NULL ;
						    }
					 }
				}
			}
		}
	}
}
//*************************************************************************************************************************************************************************************
int findelement(int i , int j , mn* head)		//Function definition of findelement
{
	mn* welement = NULL ;                                               //This function finds the value of the matrix node in the position (i,j) by pointer traversal from the head 
	welement = (struct matnode*)malloc(sizeof(struct matnode)) ;        //position.
	welement = head ;

	while( welement->row != i){
		welement = welement->below ;}

	while( welement->col != j){
		welement = welement->next ;}

	return welement->v ;                                                //It returns the value.This function helps in the symmetry function.
}

int square(mn* head)		//Function definition of square function
{
	mn* temp = NULL ;                                                   //This function traverses to the very last node of the created matrix and compares the row and column number. 
	temp = (struct matnode*)malloc(sizeof(struct matnode)) ;            //If they are same then the function returns 1 telling that the matrix is square.If not, it returns 0 telling
	temp = head ;                                                       //that the matrix is not square.

	while(temp->below != NULL){
		temp = temp->below ;}

	while(temp->next != NULL){
		temp = temp->next ;}

	if(temp->row == temp->col){
		return temp->row ;}
	else{
		return 0 ;}
}

int matcomp(mn* head1, mn* head2)		//Function definition of matcomp function
{                                                                       
	mn* temp1 = NULL ;                                                  //The function traverses to the end of both the entered matrices.It compares the column number of the first 
	temp1 = (struct matnode*)malloc(sizeof(struct matnode)) ;           //matrix with the row number of the second matrix .If they are same it returns 1 meaning they are multipliable.
	temp1 = head1 ;                                                     //else it returns 0.

	while(temp1->below != NULL){
		temp1 = temp1->below ;}

	while(temp1->next != NULL){
		temp1 = temp1->next ;}
		
	mn* temp2 = NULL ;
	temp2 = (struct matnode*)malloc(sizeof(struct matnode)) ;
	temp2 = head2 ;
	
	while(temp2->below != NULL){
		temp2 = temp2->below ;}
		
	while(temp2->next != NULL){
		temp2 = temp2->next ;}
		
	if(temp1->col != temp2->row){
		return 0 ;}
	else{
		return 1;}
}

void symmetry(mn* head)		//Function definition of symmetric function
{
	int m ;                                                             //This function checks if the matrix is symmetric or not .
	int z = 1 ;
	m = square(head) ;

	if(m==0){                                                           //This statement checks if the matrix is square or not .If the matrix is not square then it can never 
		printf("\nThe matrix is not a square matrix .Hence it is a non symmetric matrix\n");		//be symmetric.
		return ;}
	else{                                                                  
		for(int i = 1; i <= m; ++i){                                    //If the matrix is a square matrix then the (i,j) element of the matrix is compared with the (j,i) element 
			for(int j = 1; j <= m; ++j){                                //of the matrix when i!=j .If all the comparisons are true, the value of z becomes 1 and message is printed 
				if( i == j ){                                           //telling that the matrix is symmetric.
					continue ;}
					else{
						if( findelement(i,j,head) != findelement(j,i,head) ){
							printf("\nThe matrix is not a symmetric matrix \n");
							z = 0 ;
							return ;
						}
					}
			}
		}
	}

	if(z==1)
	{
		printf("\nThe matrix is symmetric \n") ;
		return ;
	}



}

void print(mn* head)		//Function definition of print function
{
	mn* rowt = NULL ;                                                   //The function traverses to each element of the matrix row after row printing them as 
	mn* colt = NULL ;                                                   //a matrix.
	rowt = (struct matnode*)malloc(sizeof(struct matnode)) ;
	colt = (struct matnode*)malloc(sizeof(struct matnode)) ;

	rowt = head ;
	colt = head ;

	while(rowt->below != NULL)
	{
		while(colt->next != NULL){
			printf("%d, \t",colt->v) ;
			colt = colt->next ;}
			
		printf("%d",colt->v) ;
		printf("\n") ;
		rowt = rowt->below ;
		colt = rowt ;
	}
	    while(colt->next != NULL){
			printf("%d, \t",colt->v) ;
			colt = colt->next ;}
		printf("%d",colt->v) ;
}

void multiply(mn* head1, mn* head2, FILE* ptr)		//Function definition of multiply function
{
	mn* p1 = NULL ;                                                     //This function multiplies two matrices .The pointers p1 and p2 are assigned to the head point of
	mn* p2 = NULL ;                                                     //of the first matrix and the pointer p3 and p4 are assigned to the head pointer of the the second 
	mn* p3 = NULL ;                                                     //matrix .The pointer p2 traverses through the first column of the first matrix while pr traverses
	mn* p4 = NULL ;                                                     //the first row of the second matrix .p1 traverses each row of the first matrix with the increment in 
	int sum ;                                                           //p2 .Similarly p3 traverses each column of the second matrix with traversal of p4. 
	p1 = (struct matnode*)malloc(sizeof(struct matnode)) ;
	p2 = (struct matnode*)malloc(sizeof(struct matnode)) ;              //The pointers p1 and p3 are continuosly changed to reflect carry out the multiplication .When the
	p3 = (struct matnode*)malloc(sizeof(struct matnode)) ;              //multiplication of a single row of the first matrix is done with each column of the second matrix
	p4 = (struct matnode*)malloc(sizeof(struct matnode)) ;              //pointer p4 comes back to the first column and the pointer p2 goes to the next row .

	p1 = head1 ;
	p2 = head1 ;
	p3 = head2 ;
	p4 = head2 ;

	while(p2->below != NULL)
	{
		while(p4->next != NULL){
			sum = 0 ;
			while(p1->next != NULL){
				sum = sum + p1->v*p3->v ;
				p1 = p1->next ;
				p3 = p3->below ;}
				
			sum = sum + p1->v*p3->v ;
			fprintf(ptr,"%d \t",sum) ;
			p4 = p4->next ;
			p3 = p4 ;
			p1 = p2 ;}
			
			sum = 0 ;
			while(p1->next != NULL){
				sum = sum + p1->v*p3->v ;
				p1 = p1->next ;
				p3 = p3->below ;
			}
			sum = sum + p1->v*p3->v ;
			fprintf(ptr,"%d \t\n",sum) ;
			p4 = p4->next ;
			p2 = p2->below ;
			p1 = p2 ;
			p3 = head2 ;
			p4 = head2 ;
	}
	   		while(p4->next != NULL){
			sum = 0 ;
			while(p1->next != NULL){
				sum = sum + p1->v*p3->v ;
				p1 = p1->next ;
				p3 = p3->below ;
			}
			sum = sum + p1->v*p3->v ;
			fprintf(ptr,"%d \t",sum) ;
			p4 = p4->next ;
			p3 = p4 ;
			p1 = p2 ;
		    }
			sum = 0 ;
			while(p1->next != NULL){
				sum = sum + p1->v*p3->v ;
				p1 = p1->next ;
				p3 = p3->below ;
			}
			sum = sum + p1->v*p3->v ;
			fprintf(ptr,"%d \t\n",sum) ;
			/*p4 = p4->next ;
			p2 = p2->below ;
			p1 = p2 ;
			p3 = head2 ;
			p4 = head2 ;*/

}

int main()
{	
	int choice = 0;
	while(choice != 4)                                                  //This while displays the list of operation that the user wants to carry out.
	{
		printf("\nSelect the desired operation (Enter the option number) :\n1. Check if the matrix is Square.\n2. Check if the matrix is Symmetric.\n3. Multiply two matrices.\n4. Exit.\n") ;
		scanf(" %d",&choice) ;                                          //Input from the user
		
		switch(choice)
		{
			case 1: {                                                   //THe first case deals with the square operation
				char string1[20] ;                                      //string to take user input of the file name 
				printf("\nEnter the file name where the matrix is stored\n") ;
				scanf(" %s", string1) ;                                 //User input
				
				FILE* sptr = fopen(string1,"r") ;                       //Opening the file to read 
				if(sptr == NULL){                                       //Error check if the file is null
					printf("\nThe file does not exist\n") ;
				    break ;}
				mn* shead = NULL ;                                      //Structure pointer where the matrix is to be made
				shead = (struct matnode*)malloc(sizeof(struct matnode)) ;
				
				shead = creatematrix(sptr) ;                            //Matrix creation
				if(shead==NULL){                                        //Error check if the matrix is not created due to discrepancy in the file format
					break ;}
				int r1 = square(shead) ;                                //Use of square function
				
				if(r1==0){
					printf("\nThe matrix is not square matrix\n") ;}
				else{
					printf("\nThe matrix is a square matrix\n") ;}
			        }
			break ;
			case 2: {
				char string2[20] ;                                      //string to take user input of the file name
				printf("\nEnter the file name where the matrix is stored\n") ;
				scanf(" %s", string2) ;                                 //User input
				
				FILE* syptr = fopen(string2,"r") ;                      //Opening the file to read 
				if(syptr == NULL){                                      //Error check if the file is null
					printf("\nThe file does not exist\n") ;
				    break ;}
				mn* syhead = NULL ;
				syhead = (struct matnode*)malloc(sizeof(struct matnode)) ;		//Structure pointer where the matrix is to be made
				syhead = creatematrix(syptr) ;                          //Matrix creation
				if(syhead==NULL){                                       //Error check if the matrix is not created due to discrepancy in the file format
					break ;}	
				symmetry(syhead) ;                                      //Use of symmetry function
				    }
		    break ;
			case 3: {
	            
				char fmatrix[20] ;                                      //string to take user input of the file name
				printf("\nEnter the file name where the matrix 1 is stored") ;
				scanf(" %s", fmatrix) ;                                 //User input
				
				char smatrix[20] ;                                      //string to take user input of the file name
				printf("\nEnter the file name where the matrix 2 is stored") ;
				scanf(" %s", smatrix) ;                                 //User input
				
				char rmatrix[20] ;                                      //string to take user input of the file name
				printf("\nEnter the file name where the resultant matrix is to be stored") ;
				scanf(" %s", rmatrix) ;                                 //User input
				
				mn* headr1 = NULL ;
                mn* headr2 = NULL ;
                headr1 = (struct matnode*)malloc(sizeof(struct matnode)) ;		//Structure pointer where the matrix is to be made
                headr2 = (struct matnode*)malloc(sizeof(struct matnode)) ;		//Structure pointer where the matrix is to be made

                FILE* ptr1 = fopen(fmatrix,"r") ;                       //Opening the file to read 
                if(ptr1 == NULL){                                       //Error check if the file is null
					printf("\nThe file does not exist\n") ;
				    break ;}
                headr1 = creatematrix(ptr1) ;                           //Matrix creation
                if(headr1==NULL){                                       //Error check if the matrix is not created due to discrepancy in the file format
					printf("(First matrix)\n") ;
					break ;}
                fclose(ptr1) ;
                 
                FILE* ptr2 = fopen(smatrix,"r") ;                       //Opening the file to read 
                if(ptr2 == NULL){                                       //Error check if the file is null
					printf("\nThe file does not exist\n") ;
				    break ;}
                headr2 = creatematrix(ptr2) ;                           //Matrix creation
                if(headr2==NULL){                                       //Error check if the matrix is not created due to discrepancy in the file format
					printf("(Second matrix)\n") ;
					break ;}
                fclose(ptr2) ;
                
                int k = matcomp(headr1,headr2) ;
                if(k==0){
					printf("\nThe matrices cannot be multiplied due to inconsistent dimensions \n") ;
				}
				else{
				FILE* ptr3 = fopen(rmatrix, "w") ;                      //Opening the file to write
				multiply(headr1,headr2,ptr3) ;                          //Use of multiply function
				fclose(ptr3) ;
				printf("\nThe matrices have been multiplied and stored in desired file\n") ;
			    }	
				}
			
		   break ;	 
		   case 4: choice = 4 ;                                         //This case is for exiting the function
		   break ;
		}
	}	
}
