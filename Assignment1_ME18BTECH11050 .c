#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node{    // This structure defines the individual necleotides in the molecules
  char DNA ;    // This variable stores the necleotide data
  struct node* next ;    //This pointer points to the next nucleotide in the chain
  struct node* prev ;    //This pointer points to the previous nucleotide in the chain
  struct node* across ;    //This pointer points to the nucleotide across it in the adjacent chain of the molecule
};

struct molID{    //This structure is being used to store the molecule ID of individual molecules
int ID;    //This variable stores the ID number of the individual molecules starting from 1
int split ;    //This variable stores the split condition of a certain molecules .If the molecules has been split then its value is set to 1
struct node* headID ;    //This pointer points to the first nucleotide in the alpha chain of the molecule
struct molID* nextID ;    //This pointer points to the next molecule ID
struct molID* prevID ;    //This pointer points to the previous molecule ID
};

typedef struct node nn;    //Typedef statements have been used to give the structure an alias name to be used in the program from now on
typedef struct molID ID;
int position ;

struct molID* createchain();    //This is the function declaration for the function to create an initial chain
void addmolecule(struct molID* moleculeid);    //This is the function declaration to add new molecules to the existing chain of molecules
int insert(struct molID* MID, char chain ,char dna, int p);    ////Function declaration to insert a nucleotide in a given molecule in a given chain ID and position
void del(struct molID* MID,int p);    //Function declaration to delete a certain nucleotide from a certain position in a specified molecule
void split(struct molID* MID);    //Function declaration to split a given molecules at a given position
void print(struct molID* MID);    //Function declaration to print a certain specified molecule
void printallchains(struct molID* MID);    //Function declaration to print all the chains available in the molecule

int insert(struct molID* MID, char chain, char dna, int p)    //Function Definition. MID stands for molecule ID , chain stands for chain ID like alpha or beta. dna stands for nucleotide.
{                                                              //p stands for position
  int k = 0;    //This variable helps to identify if a desired user input position is present in the molecule or not
//**************************************************************************************************************************************************************************************************
  if(p == 1)                                                                  //There are two cases to take into account while inserting a nucleotide in a molecule.If the insertion is in the
  {                                                                           //first positon the pointer manipulation for this case will be different than in the other case in this program .
    nn* temp1 = NULL ;                                                        //As will be evident from the code of createchain below, this program while creating a new molecule creates to dummy
    nn* temp2 = NULL ;                                                        //neuceotide structure and marks them as the 0th position in the beginning.This helps the program while handling
    temp1 = (struct node*)malloc(sizeof(struct node)) ;                       //insertion and deletion in the extremum case i.e. at the end of the molecule. Hence only two cases of insertion come
    temp2 = (struct node*)malloc(sizeof(struct node)) ;                       //come into picture and not three.

    temp1 = MID->headID ;                                                     //When the position is 1 , 2 pointers named temp1 and temp2 are allocated to the initial first position of the
    temp2 = temp1->across ;                                                   //molecules each to the first nucleotide of the alpha and beta chain respectively.2 other pointer structure named
                                                                              //newnode1 and newnode2 are assigned the value of the nucleotide to be inserted in the first poisition .
    nn* newnode1 = NULL ;
    nn* newnode2 = NULL ;
    newnode1 = (struct node*)malloc(sizeof(struct node)) ;
    newnode2 = (struct node*)malloc(sizeof(struct node)) ;
//**************************************************************************************************************************************************************************************************
    temp1->prev = newnode1 ;    //Previous pointers of temp1 and temp2 are pointed to newnode                                                // This area carries out the pointer manipulation between temp1, temp2, newnode1, newnode2 .
    temp2->prev = newnode2 ;
    newnode1->next = temp1 ;    //Next pointers of newnodes are pointed to temp
    newnode2->next = temp2 ;
    newnode1->across = newnode2 ;    //Across pointers of the newnode point to each other
    newnode2->across = newnode1 ;
    newnode1->prev = NULL ;    //Previous pointers of newnodes are assigned to NULL as they now become the starting nucleotides of alpha and beta chain.
    newnode2->prev = NULL ;

    MID->headID = newnode1 ;    // Since newnode1 is now the first nucleotide of the alpha chain, the head ID will now point it.
//***************************************************************************************************************************************************************************************************
      if( chain == 'a')
  {                                                                            //This part of the program compare the adjacent nucleotide in the alpha chain and beta chain.
    if(dna == 'A'){                                                            //If the nucleotide in the alpha chain is A then the corresponding nucleotide in the beta chain
      newnode1->DNA = dna ;                                                    // will be T and so on .
      newnode2->DNA = 'T' ; }
    else if(dna == 'T'){
      newnode1->DNA = dna ;
      newnode2->DNA = 'A' ; }
    else if(dna == 'C'){
      newnode1->DNA = dna ;
      newnode2->DNA = 'G' ; }
    else{
      newnode1->DNA = dna ;
      newnode2->DNA = 'C' ;}
  }
  else
  {
    if(dna == 'A'){
      newnode2->DNA = dna ;
      newnode1->DNA = 'T' ; }
    else if(dna == 'T'){
      newnode2->DNA = dna ;
      newnode1->DNA = 'A' ; }
    else if(dna == 'C'){
      newnode2->DNA = dna ;
      newnode1->DNA = 'G' ; }
    else{
      newnode2->DNA = dna ;
      newnode1->DNA = 'C' ;}
  }
//***************************************************************************************************************************************************************************************************
  }
//***************************************************************************************************************************************************************************************************
  else
  {                                                                            //For the case when position is not equal to 1, 4 temp pointers are assigned .temp1 and temp2 are assigned the
    nn* temp1 = NULL ;                                                         // nucleotides in the previous position to the desired position and temp3 and temp4 are assigned the position at
    nn* temp2 = NULL ;                                                         // the desired position .
    nn* temp3 = NULL ;
    nn* temp4 = NULL ;
    temp1 = (struct node*)malloc(sizeof(struct node)) ;
    temp2 = (struct node*)malloc(sizeof(struct node)) ;
    temp3 = (struct node*)malloc(sizeof(struct node)) ;
    temp4 = (struct node*)malloc(sizeof(struct node)) ;

    temp1 = MID->headID ;

    while(temp1->next!=NULL)
    {
        temp1=temp1->next;
        k=k+1;
    }

    if(p>k+1)                                                                  //This condition checks if the desired position is present in the molecule or not .If not then the function
    {                                                                          // simply flags an error message and returns to main
        printf("The desired position does not exist in the molecule \n");
        return 0;
    }
    temp1= MID->headID;
    for(int j=2;j<p;j++)
    {
        temp1=temp1->next;
    }

//***************************************************************************************************************************************************************************************************
    nn* newnode1 = NULL ;                                                     //This part of the function deals with the pointer manipulation between the newnodes and the 4 temp nodes in the position and the
    nn* newnode2 = NULL ;                                                     //position - 1 points . The next pointer of temp1 and temp2 point to the new node . the previous pointer of newnodes point to temp1 and temp2
    newnode1 = (struct node*)malloc(sizeof(struct node)) ;                    //respectively . Then the previous pointers of temp3 and temp 4 point to the newnodes 1 and 2 .The next pointers of newnode point to
    newnode2 = (struct node*)malloc(sizeof(struct node)) ;                    //temp3 and temp4 .In this way the two newnodes enter into the desired position.The newnodes and wrapped otgether with the across pointers themselves.
    temp2 = temp1->across ;

    newnode1->prev = temp1 ;
    newnode2->prev = temp2 ;
    newnode1->next = temp1->next ;
    newnode2->next = temp2->next ;
    newnode1->across = newnode2 ;
    newnode2->across = newnode1 ;
    temp3 = temp1->next ;
    temp4 = temp2->next ;
    temp1->next = newnode1 ;
    temp2->next = newnode2 ;
    temp3->prev = newnode1 ;
    temp4->prev = newnode2 ;
//****************************************************************************************************************************************************************************************************
      if( chain == 'a')                                                      //This part of the program compare the adjacent nucleotide in the alpha chain and beta chain.
  {                                                                          // nucleotides in the previous position to the desired position and temp3 and temp4 are assigned the position at
    if(dna == 'A'){                                                          // the desired position.
      newnode1->DNA = dna ;
      newnode2->DNA = 'T' ; }
    else if(dna == 'T'){
      newnode1->DNA = dna ;
      newnode2->DNA = 'A' ; }
    else if(dna == 'C'){
      newnode1->DNA = dna ;
      newnode2->DNA = 'G' ; }
    else{
      newnode1->DNA = dna ;
      newnode2->DNA = 'C' ;}
  }
  else
  {
    if(dna == 'A'){
      newnode2->DNA = dna ;
      newnode1->DNA = 'T' ; }
    else if(dna == 'T'){
      newnode2->DNA = dna ;
      newnode1->DNA = 'A' ; }
    else if(dna == 'C'){
      newnode2->DNA = dna ;
      newnode1->DNA = 'G' ; }
    else{
      newnode2->DNA = dna ;
      newnode1->DNA = 'C' ;}
  }
  }
  return 1 ;

}

void del(struct molID* MID, int p)
{//****************************************************************************************************************************************************************************************
  int k = 0;
  if(p==1)
  {                                                                           //This function comes in a single part handling two cases .If deletion is at position 1 or the other
     nn* temp1 = NULL ;                                                       //Three pointers temp1 ,temp2, temp3 .In the first case temp1 is assigned to the position just before the position
     nn* temp2 = NULL ;                                                       //to be deleted . After that temp2 is assigned to the across nucleotide of temp1 . Then the next nucleotide of temp2 is
     nn* temp3 = NULL ;                                                       //assigned to temp1 .The pointers between temp1 and temp2 are assigned to NULL.Then temp1 and temp2 go to their
     temp1 = (struct node*)malloc(sizeof(struct node)) ;                      //across nucleotide and the connection between them is also broken by assignment to NULL.Then since temp1 is present at
     temp2 = (struct node*)malloc(sizeof(struct node)) ;                      //the second level in the chain ,it is linked to the head ID thereby eliminating the first molecule .
     temp3 = (struct node*)malloc(sizeof(struct node)) ;
     temp1 = MID->headID ;
     temp2 = temp1->across ;
     temp1 = temp2->next ;
     temp1->prev = NULL ;
     temp2->next = NULL ;
     temp1 = temp1->across ;
     temp2 = temp2->across ;
     temp1->prev = NULL ;
     temp2->next = NULL ;
     MID->headID = temp1 ;
     temp3 = temp2->across ;
     temp2->across = NULL ;
     temp3->across = NULL ;
   }
   else
   {
     nn* temp1 = NULL ;                                                     //In the second case a similar operation is done.temp1 is traversed to the position just before the position to be
     nn* temp2 = NULL ;                                                     //deleted .with the help of temp1 ,temp3 is assigned to the position which has to be deleted and the position
     nn* temp3 = NULL ;                                                     //after that is assigned to temp2 .The next and previous pointers of temp1 and temp2 are linked to each other and the pointers
     temp1 = (struct node*)malloc(sizeof(struct node)) ;                    //in the level of temp3 is assigned to NULL .As a result the desired position is segregated from the chain .Hence it gets technically
     temp2 = (struct node*)malloc(sizeof(struct node)) ;                    //deleted
     temp3 = (struct node*)malloc(sizeof(struct node)) ;
     temp1 = MID->headID ;

     while(temp1->next != NULL)    // This while loop counts the number of nucleotide levels in the chain and.
     {
       temp1 = temp1->next ;
       k = k+1 ;
     }

     if(k<p)    //This if statement checks if the desired position to be deleted exists in the chain or not.If not it returns void from the function.
     {
       printf("The desired position is not present in the DNA\n") ;
       return ;
     }

     temp1 = MID->headID ;

     for(int j=2 ; j<p ; ++j)    //Here temp1 is being traversed to the position just before the position to be deleted .
     {
       temp1 = temp1->next ;
     }

     temp2 = temp1->across ;    //This the part where the above mentioned pointer manipulations are taking place
     temp3 = temp2->next ;
     temp2 = temp3->next ;
     temp1 = temp1->across ;
     temp2->prev = temp1 ;
     temp1->next = temp2 ;
     temp3->next = NULL ;
     temp3->prev = NULL ;
     temp1 = temp1->across ;
     temp2 = temp2->across ;
     temp3 = temp3->across ;
     temp2->prev = temp1 ;
     temp1->next = temp2 ;
     temp3->next = NULL ;
     temp3->prev = NULL ;
     temp2 = temp3->across ;
     temp2->across = NULL ;
     temp3->across = NULL ;

   }
     printf("\nThe nucleotide has been deleted from Molecule %d at position %d.\n\n",MID->ID ,p) ;

}

void split(struct molID* MID)    //Function Definition
{//*******************************************************************************************************************************************************************************************
  ID* N = NULL ;                                                                    //This part of the code cretes the new molecule ID in which the split molecules has to be stored.
  N = (struct molID*)malloc(sizeof(struct molID)) ;                         
  N->nextID = NULL ;
  N->prevID = NULL ;
  N->headID = NULL;
//********************************************************************************************************************************************************************************************
  if(MID->nextID == NULL)                                                           // This part of the program deals with the insertion of the molecule module created in the previous part
  {                                                                                 // into the molecules chain . If the last molecule in the chain is being split then the pointer manipulation
    MID->nextID = N ;                                                               // is different than in the case when the split is taking place somewhere in the middle of the molecule .
    N->nextID = NULL ;                                                              // Hence this if else condition statements are being used to take care of the position of the molecules where the
    N->prevID = MID ;                                                               // split is taking place.
  }
  else
  {
    ID* temp = NULL ;
    temp = (struct molID*)malloc(sizeof(struct molID)) ;
    N->nextID = MID->nextID ;
    N->prevID = MID ;
    MID->nextID = N ;
    temp = N->nextID ;
    temp->prevID = N ;
  }
//********************************************************************************************************************************************************************************************
  nn* tempA = NULL ;                                                               //This part of the code makes two pointers to point to the alpha and beta chain of the molecule  
  nn* tempB = NULL ;                                                               //The new molecule head pointer is pointed to the beta chain of the molecule being split
  tempA = (struct node*)malloc(sizeof(struct node)) ;                              //The beta chain of the old molecue becomes the 
  tempB = (struct node*)malloc(sizeof(struct node)) ;
  tempA = MID->headID ;
  tempB = tempA->across ;
  N->headID = tempB ;
//********************************************************************************************************************************************************************************************
  while(tempA->next != NULL)                                                      //This part of the code breaks the old linkages between the nucleotides in the old molecular chain
  {                
	  tempA->across = NULL ;
	  tempB->across = NULL ;
	  tempA = tempA->next ;
	  tempB = tempB->next ;
  }
  
  tempA->across = NULL ;
  tempB->across = NULL ;
//*********************************************************************************************************************************************************************************************
  nn* newnodeA = NULL ;                                                         //This part of the code deals with the construction of the new molecular chains over the existing chains 
  nn* newnodeB = NULL ;                                                         //newnodeA and newnodeB are the new nodes that are being added to each chain of the molecule 
  nn* temp1A = NULL ;                                                           //temp1A and and temp1B are pointers that have a single function of establishing backward connection 
  nn* temp1B = NULL ;                                                           //between the new nucleotides being added  . 
  newnodeA = (struct node*)malloc(sizeof(struct node)) ;                         
  newnodeB = (struct node*)malloc(sizeof(struct node)) ;
  temp1A = (struct node*)malloc(sizeof(struct node)) ;
  temp1B = (struct node*)malloc(sizeof(struct node)) ;
  
  while(tempA->prev != NULL) 
  {
	  newnodeA->DNA = tempB->DNA ;
	  newnodeB->DNA = tempA->DNA ;
	  
	  tempA->across = newnodeA ;
	  newnodeA->across = tempA ;
	  tempB->across = newnodeB ;
	  newnodeB->across = tempB ;
	  
	  temp1A = newnodeA ;
	  temp1B = newnodeB ;
	  
	  newnodeA->prev = (struct node*)malloc(sizeof(struct node)) ;
	  newnodeB->prev = (struct node*)malloc(sizeof(struct node)) ;
	  newnodeA = newnodeA->prev ;
	  newnodeB = newnodeB->prev ;
	  
	  if(temp1A->DNA == ' ')
	  {
		  temp1A->next = NULL ;
		  temp1B->next = NULL ;
	  }
	  
	  newnodeB->next = temp1B ;
	  newnodeA->next = temp1A ;
	  
	  tempA = tempA->prev ;
	  tempB = tempB->prev ;
  }
//*********************************************************************************************************************************************************************************************
      newnodeA->DNA = tempB->DNA ;                                                  //This part of the code deals with pointer manipulations of the last remaining linkages in the chain.
      newnodeB->DNA = tempA->DNA ;                                                  //This is necessary because the above loop is exited as soon as the temp->next points to NULL.As a result 
      newnodeA->across = tempA ;                                                    //the last nucleotide pointer manipulation is ignored in the above while loop.
      newnodeB->across = tempB ;
      tempA->across = newnodeA ;
      tempB->across = newnodeB ;
      newnodeA->prev = NULL ;
      newnodeB->prev = NULL ;
      N->headID = newnodeB ;
//*********************************************************************************************************************************************************************************************
  MID->split = 1;                                                                  //Due to the split activity the numbering of the molecule ID in disordered .This part of the function                                                                    //renumbers the molecules correctly starting from the split point
  int b ;
  N->ID = MID->ID + 1;    // Assigns the new molecule the next number in the ID .From here all the ID numbers of the molecules are incremented by 1
  ID* temph = NULL ;
  temph = (struct molID*)malloc(sizeof(struct molID)) ;
  temph = N ;

  while(temph->nextID != NULL)
  {
    b = temph->ID ;
    temph = temph->nextID ;
    temph->ID = b + 1 ;
  }
  printf("\nMolecule %d has been split as desired and is stored in Molecule ID %d .\n\n",MID->ID,MID->ID+1) ;


}

void print(struct molID* MID)    //Function Definition for print
{
  nn* temp1 = NULL ;                                                                //temp1 and temp2 print the nucleotides of alpha and beta position respectively
  nn* temp2 = NULL ;
  temp1 = (struct node*)malloc(sizeof(struct node)) ;
  temp2 = (struct node*)malloc(sizeof(struct node)) ;

  temp1 = MID->headID ;    //temp1 is assigned to the first nucleotide in the alpha chain
  temp2 = temp1->across ;    //Temp2 is assigned to the second nucleotide in the beta chain
  int k = 1 ;     //k stores the number of nodes in the chain
  if(MID->split == 1)    //This if statement is activated to exclusively print the molecules which has been split by denoting them as split molecules
  {
    printf("This molecule has been split and the new molecules is stored in molecule ID %d \n",MID->ID+1) ;
    printf(" alpha--> ") ;
    while(temp1->next != NULL)    //This while loop prints all the nucleotides in the alpha chain
    {
      printf("%c", temp1->DNA ) ;
      printf("-") ;
      k = k+1 ;
      temp1 = temp1->next ;
    }
    printf("%c  \n",temp1->DNA ) ;
    
    for(int j=9;j>0;--j)
    {
       printf(" ");
    }

    for(int i = k-1; i>0; --i)    //This for loop prints the bars between the alpha and beta chains
    {
      printf(" |");
    }
    printf("\n");
    printf(" beta-->  ");
    while(temp2->next != NULL)    //This while loop prints all the nucleotides in the beta chain
    {
      printf("%c", temp2->DNA) ;
      printf("-");
      temp2 = temp2->next ;
    }
    printf("%c",temp2->DNA) ;
  }
  else    //This else statement does the same thing as above exactly except that it only prints the molecules that have not been split
  {
    printf(" alpha--> ") ;
    while(temp1->next != NULL)
    {
      printf("%c", temp1->DNA ) ;
      printf("-") ;
      k = k+1 ;
      temp1 = temp1->next ;
    }
    printf("%c \n",temp1->DNA ) ;
    for(int j=9;j>0;--j)
    {
       printf(" ");
    }
    for(int i = k-1; i>0; --i)
    {
      printf(" |");
    }
    printf("\n");
    printf(" beta-->  ");
    while(temp2->next != NULL)
    {
      printf("%c", temp2->DNA) ;
      printf("-");
      temp2 = temp2->next ;
    }
    printf("%c",temp2->DNA) ;

  }
}

void printallchains(struct molID* MID)    //Function definition for print all chains
{
  ID* temp = NULL ;    //  This pointer traverses the molecule ID series starting from the first ID
  temp = (struct molID*)malloc(sizeof(struct molID)) ;
  temp = MID ;

  while(temp->nextID != NULL )    //This while goes until the last ID present and calls the print function at each ID to print the molecular chain.
  {
    printf(" MOLECULE ID = %d :- \n", temp->ID);
    print(temp) ;
    printf("\n") ;
    temp = temp->nextID ;
  }

  printf(" MOLECULE ID = %d :- \n", temp->ID);    //This part prints the molecule in the last ID .THis is done because the previous loop does not print the last ID
  print(temp) ;
  printf("\n") ;
}

struct molID* createchain()    // Function definition of create chain .This function returns the head ID of the first molecule in the series of molecules .
{

//*******************************************************************************************************************************************************
ID* moleculeid = NULL ;    //Initial headnode defined in the main function to start the work of DNA construction
ID* molhead = NULL ;    //MOlhead will always contain the address of the starting molecule ID node
moleculeid = (struct molID*)malloc(sizeof(struct molID));
molhead = (struct molID*)malloc(sizeof(struct molID));

nn* newnode1 = NULL ;    // Defining the two starting nodes of the first DNA sequence to be used and also initialising them with certain values
nn* newnode2 = NULL ;
newnode1 = (struct node*)malloc(sizeof(struct node));
newnode2 = (struct node*)malloc(sizeof(struct node));

moleculeid->headID = newnode1 ;    //The address of the first node of the alpha chain is stored in the head ID.
moleculeid->prevID = NULL ;
moleculeid->nextID = NULL ;
moleculeid->ID = 1;
molhead = moleculeid ;    //Since the first molecule is being created , the head ID is stored in the pointer molhead

newnode1->across = newnode2 ;    // newnode1 pointer manipulation
newnode1->next = NULL;
newnode1->prev = NULL;
newnode1->DNA  = ' ' ;    //These two nodes are the first nodes established by the program while creating the molecule and hence are dummy nodes .The dummy nodes helps to eliminate one of the
                          // extremum case (end case) while inserting and deleting as they are assigned 0th position
newnode2->across = newnode1 ;    //newnodes2 pointer manipulation .
newnode2->next = NULL ;
newnode2->prev = NULL ;
newnode2->DNA  = ' '  ;
//*********************************************************************************************************************************************************

char str[1000] ;
printf(" Enter the initial chain of nucleotides in the molecule.\n Dont use any special characters ,small letters etc.\n Type in only the correct nuceotides in capital letters.\n") ;
scanf("%s",str);
int sl = strlen(str);                                                                 // This part of the function deals with the user input of initial molecules to be input the molecule
                                                                                      //being created.The input is taken in an array .Then the inputs stored in the array are fed in a
for(int j=0; j<sl; ++j)                                                               //consecutive fashion to the linked list using the insert function earlier made .The insertion of the
{                                                                                     //consecutive nucleotides takes place in the last position .
  while(str[j] != 'A' && str[j] != 'T' && str[j] != 'C' && str[j] != 'G')
  {
    printf("Enter an approapriate nucleotide at the position %d ", j+1);
    scanf(" %c", &str[j]);
  }
}

for(int i=0; i<=sl-1;++i)
{
  insert(moleculeid,'a',str[i],i+1);    //Insert function being used to create the chain of nucleotides as discussed earlier.
}
//*********************************************************************************************************************************************************
//print(moleculeid);
   printf("\nThe initial molecule has been created with molecule ID 1.\n\n") ;

return molhead ;    // The head molecule ID is returned

}

void addmolecule(struct molID* moleculeid)  //Function definition for add molecule .This function definition adds a new molecule to the series of molecules .
{
                                                                                  //The working of this function is equivalent to the working of the  createchain function except that here a node
  ID* temp = NULL ;                                                               //molecule ID is added and hence certain pointer manipulation has to take place.The temp variable in this part
  temp = (struct molID*)malloc(sizeof(struct molID));                             //of the function traverses to the last position of the series of molecules where the new molecule is to be added
  temp = moleculeid ;

  while(temp->nextID != NULL)
  {
    temp = temp->nextID ;
  }

//**************************************************************************************************************************************************************************
  ID* tempm = NULL ;                                                             //The structure pointer tempm is the new molecule ID to be inserted in the series of molecules
  tempm = (struct molID*)malloc(sizeof(struct molID));                           //The pointer manipulation done here places the new molecule ID at the end of the series of molecules.
  temp->nextID =tempm  ;
  tempm->prevID = temp ;
  tempm->nextID = NULL;
  tempm->headID = NULL;
  temp = tempm ;

  nn* newnode1 = NULL ;    // Defining the two starting nodes of the first DNA sequence to be used and also initialising them with certain values
  nn* newnode2 = NULL ;
  newnode1 = (struct node*)malloc(sizeof(struct node));
  newnode2 = (struct node*)malloc(sizeof(struct node));

  temp->headID = newnode1 ;                                                     //Here the first node of the alpha chain of the new molecules is being point to by the tempm molecule.
                                                                                //As mentioned previously the newnodes being created here are the dummy nodes used for initialization
  newnode1->across = newnode2 ;
  newnode1->next = NULL;
  newnode1->prev = NULL;
  newnode1->DNA  = ' ' ;

  newnode2->across = newnode1 ;
  newnode2->next = NULL ;
  newnode2->prev = NULL ;
  newnode2->DNA  = ' '  ;
//*****************************************************************************************************************************************************************************
  char str[1000] ;
  printf(" Enter the initial chain of nucleotides in the molecule.\n Dont use any special characters ,small letters etc.\n Type in only the correct nuceotides in capital letters.\n ") ;
  scanf("%s",str);
  int sl = strlen(str);
                                                                                             // This part of the function is same as in the cretechain function as explained above
  for(int j=0; j<sl; ++j)
  {
    while(str[j] != 'A' && str[j] != 'T' && str[j] != 'C' && str[j] != 'G')
    {
      printf("Enter an approapriate nucleotide at the position %d ", j+1);
      scanf(" %c", &str[j]);
    }
  }

  for(int i=0; i<=sl-1;++i)
  {
    insert(temp,'a',str[i],i+1);
  }
//******************************************************************************************************************************************************************************
  temp = moleculeid ;
  while(temp->prevID != NULL)                                                                // This part of the function deals with numbering of the last molecule ID .
  {                                                                                          //The pointer temp is first made to go to the first position of series of molecules and then made to
    temp = temp->prevID ;                                                                    //traverse to the last while the variable l counts the number of iterations .The variable l value is then the
  }                                                                                          //molecule ID of the newly added molecule

  int l = 1;
  while(temp->nextID != NULL)
  {
    temp->ID = l;
    l = l+1 ;
    temp = temp->nextID ;
  }

  temp->ID = l ;
  printf("\nThe molecule has been added with the molecule ID %d\n\n", tempm->ID ) ;

  //*********************************************************************************************************************************************************************************
}

int main()
{
  int n = 1 ;    // This variable controls the while loop below
  ID* B = NULL ;    //This pointer is assigned as the molecule ID head of the seires of molecule to be made
  B = (struct molID*)malloc(sizeof(struct molID)) ;
  int x = 0 ;
  while(n==1)    // While loop for the options menu starts here
  {
    int choice ;
    printf("Choose the desired function.\nRemember you cant choose addmolecule() option unless you create an initial molecule using createchain() \n\n");
    printf("1.Create New Chain \n2.Add a molecule \n3.Insert Nucleotide \n4.Delete Nucleotide \n5.Split Molecule \n6.Print A Molecule \n7.Print all chains \n8.Exit \n");
    scanf("%d", &choice);    //Takes the user input for the options in the menu

    while(choice>8 || choice<1)
    {
      printf("Enter a valid choice \n");
      scanf(" %d", &choice);
    }

    switch(choice)
    {
      case 1: if(x==0)    // First switch acticates the createchain() function to create the first molecule .However it can be used only once .Hence if else condition has been used to stop
              {           //user from calling the function more than once
                x = 1 ;
                B = createchain();    //Createchain function is called here
              }
              else
              {
                printf("\n\nYou cannot call this function more than once .It establishes only the first molecule \n\n");
              }
      break ;
      case 2: if(x==0)    //This case activates the add molecule function .This function can only be called after the createchain function is called for once .
              {
                printf("\n\nYou first have to create the first molecule using the createchain function \n\n");
              }
              else    //This else statement is activated when the createchain function is called once
              {
                addmolecule(B) ;    //Addmolecule() function is called here
              }
      break ;

      case 3: { 
		        int j ,z;
		        if(x==0)    //This case activates the insert function .This function can only be called after the createchain function is called for once .
                {
                  printf("\n\nYou first have to create the first molecule using the createchain function \n\n");
                }
                else   //This else statement is activated when the createchain function is called once
                {
                int id ;
                int t=1 ;
                printf("Enter the molecule ID where you want to insert the nucleotide.Just a number (excluding 0). \n");    //User input for the molecule ID is being asked
                scanf(" %d", &id);
                ID* temp = NULL ;
                temp = (struct molID*)malloc(sizeof(struct molID));
                while(t==1)
                {
                temp = B ;
                int s = 1 ;
                while(temp->nextID != NULL)    // This while loop checks the length of the molecule ID series
                {
                  temp=temp->nextID ;
                  s+=1 ;
                }

                if(id>s)    //This if statement checks if the user input position is greater than the number of positions available in the molecular series
                {
                  printf("The molecule does not exist. \n Enter valid position. \n") ;    //Error message if the above statement is true
                  scanf(" %d", &id);
                }
                else    //If the appropriate position in the molecule ID is entered this else statement is executed
                {
                  t=0 ;
                }
                }
                {
                  temp = B ;    //Temp traverses to molecule in which insertion function has to work
                  for(int i=1 ; i<id; ++i)
                  {
                    temp = temp->nextID ;
                  }

                  char dna ;    //User input of dna to be inserted
                  printf("Enter the nucletide .\nA for Adenine.\nC for Cytosine.\nT for Thymine.\nG for Guanine.\n") ;
                  scanf(" %c", &dna);
                  while(dna != 'A' && dna != 'T' && dna != 'C' && dna != 'G')    //Error check to stop user from entering anything other than the appropriate DNA nucleotide
                  {
                    printf("Enter the correct nucleotide. \n");
                    scanf(" %c", &dna);
                  }

                  char chainid ;    //User input of the chain ID
                  printf("Enter the chain ID. a for alpha and b for beta :") ;
                  scanf(" %c", &chainid) ;
                  while(chainid != 'a' && chainid != 'b')    //Error check to stop user from entering anything other than the appropriate chain ID as mentioned above
                  {
                    printf("\nEnter the correct chain ID . a for alpha and b for beta ");
                    scanf(" %c", &chainid) ;
                  }

                  int position ;    //User input of the position in the chain where the molecule has to be inserted
                  printf("\nEnter the position .");
                  scanf(" %d", &position);
                  j = position ;
                  while(position <= 0)    //Mild error check to detect the position entered is number greater than 0.However if the position exists in the chain or not is checked inside the insert function
                  {
                    printf("\nEnter a valid position");
                    scanf(" %d", &position);
                  }

                  z = insert(temp,chainid,dna,position);    //Insert() function is called here
                }
                if(z==1){
                printf("The nucleotide has been inserted in the position %d in the molecule %d.\n\n",j,temp->ID) ;}
                }
                }
      break;

      case 4: { if(x==0)    //This case activates the delete function .This function can only be called after the createchain function is called for once .
                {
                  printf("\n\nYou first have to create the first molecule using the createchain function \n\n");
                }
                else    //This else statement is activated when the createchain function is called once
                {
                int id ;
                int t=1 ;
                printf("Enter the molecule ID where you want to delete the nucleotide.Just a number (excluding 0). \n");
                scanf(" %d", &id);
                ID* temp = NULL ;
                temp = (struct molID*)malloc(sizeof(struct molID));
                while(t==1)
                {
                  temp = B ;
                  int s = 1 ;
                  while(temp->nextID != NULL)    // This while loop checks the length of the molecule ID series
                  {
                    temp=temp->nextID ;
                    s+=1 ;
                  }

                  if(id>s)    //This if statement checks if the user input position is greater than the number of positions available in the molecular series
                  {
                    printf("The molecule does not exist. \n Enter valid position. \n") ;    //Error message if the above statement is true
                    scanf(" %d", &id);
                  }
                  else    //If the appropriate position in the molecule ID is entered this else statement is executed
                  {
                    t=0 ;
                  }
                }
                  temp = B ;    //Temp traverses to molecule in which insertion function has to work
                  for(int i=1 ; i<id; ++i)
                  {
                    temp = temp->nextID ;
                  }

                  int position ;
                  printf("\nEnter the position .");
                  scanf(" %d", &position);
                  while(position <= 0)
                    {
                      printf("\nEnter a valid position");
                      scanf(" %d", &position);
                    }

                  del(temp,position);    //Del() function is called here
                }
                }
      break;

      case 5: { if(x==0)    //This case activates the split function .This function can only be called after the createchain function is called for once .
                {
                  printf("\n\nYou first have to create the first molecule using the createchain function \n\n");
                }
                else    //This else statement is activated when the createchain function is called once
                {
                int id ;
                int t=1 ;
                printf("Enter the molecule ID where you want to split the nucleotide.Just a number (excluding 0). \n");
                scanf(" %d", &id);
                ID* temp = NULL ;
                temp = (struct molID*)malloc(sizeof(struct molID));
                while(t==1)
                {
                  temp = B ;
                  int s = 1 ;
                  while(temp->nextID != NULL)    // This while loop checks the length of the molecule ID series
                  {
                    temp=temp->nextID ;
                    s+=1 ;
                  }

                  if(id>s)    //This if statement checks if the user input position is greater than the number of positions available in the molecular series
                  {
                    printf("The molecule does not exist. \n Enter valid position. \n") ;    //Error message if the above statement is true
                    scanf(" %d", &id);
                  }
                  else    //If the appropriate position in the molecule ID is entered this else statement is executed
                  {
                    t=0 ;
                  }
                }
                  temp = B ;    //Temp traverses to molecule in which insertion function has to work
                  for(int i=1 ; i<id; ++i)
                  {
                    temp = temp->nextID ;
                  }

                 split(temp);    //Split() function called here
              }
              }
      break ;

      case 6: { if(x==0)    //This case activates the print function .This function can only be called after the createchain function is called for once .
                {
                  printf("\n\nYou first have to create the first molecule using the createchain function \n\n");
                }
                else    //This else statement is activated when the createchain function is called once
                {
                int id ;
                int t=1 ;
                printf("Enter the molecule ID where you want to delete the nucleotide.Just a number (excluding 0). \n");
                scanf(" %d", &id);
                ID* temp = NULL ;
                temp = (struct molID*)malloc(sizeof(struct molID));
                while(t==1)
                {
                  temp = B ;
                  int s = 1 ;
                  while(temp->nextID != NULL)    // This while loop checks the length of the molecule ID series
                  {
                    temp=temp->nextID ;
                    s+=1 ;
                  }

                  if(id>s)    //This if statement checks if the user input position is greater than the number of positions available in the molecular series
                  {
                    printf("The molecule does not exist. \n Enter valid position. \n") ;    //Error message if the above statement is true
                    scanf(" %d", &id);
                  }
                  else    //If the appropriate position in the molecule ID is entered this else statement is executed
                  {
                    t=0 ;
                  }
                }
                  temp = B ;    //Temp traverses to molecule in which insertion function has to work
                  for(int i=1 ; i<id; ++i)
                  {
                    temp = temp->nextID ;
                  }

                  print(temp);    //Print() function called here
              }
              }
      break;

      case 7:  if(x==0)    //This case activates the add printallchains() function .This function can only be called after the createchain function is called for once .
               {
                 printf("\n\nYou first have to create the first molecule using the createchain function \n\n");
               }
               else
               {
                 printallchains(B);    //Printallchains() function called here
               }
      break;

      case 8: n = 0 ;
      break;
    }
    }
  }





