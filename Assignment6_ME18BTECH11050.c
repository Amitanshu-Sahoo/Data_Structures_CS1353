#include<stdio.h>
#include<stdlib.h>

struct node{		// structure to represent a node in the tree
	unsigned int key ;		// this variable stores the key of the node
	struct node* right_c ;		// pointer to point the right child of the node
	struct node* left_c ;		// pointer to point the left child of the node
	struct node* parent ;		// pointer to point the parent of the node 
};

typedef struct node tn ;		// alias name for the structure 'tn'

FILE* ptr2 ;		// globally declared file pointer to be used in the print functions
int router = 0;		// this variable helps to establish the root node in the tree through the insert function
int x=0;		// this variable helps in counting the number of nodes in the tree in the counter function

int right_child(tn* parent,tn* child) ;		// returns 1 if the child is the right child of the parent 
int left_child(tn* parent,tn* child) ;		// returns 1 if the child is the left child of the parent 
tn* MIN(tn* root) ;		// finds the node with the minimum key value
tn* MAX(tn* root) ;		// finds the node with the maximum key value
tn* predecessor(tn* feed_node) ;		// finds the predecessor node of the node passed in argument
void inorder(tn* root) ;		// function prints the inorder traversal of the tree to the desired file
void preorder(tn* root) ;		// function prints the preorder traversal of the tree to the desired file
void postorder(tn* root) ;		// function prints the postorder traversal of the tree to the desired file
void counter(tn* root);		// counts the number of nodes in the tree rooted at 'root'
int insert(tn* root, unsigned int key_val) ;		// inserts the 'key_val' into the tree
int delete(tn* root, unsigned int key_val) ;		// deleted the'key_val' from the tree if it exists
void print(tn* root) ;		// prints the inorder, preorder and postorder traversal to the desired file
void print_subtree(tn* root, unsigned int key_val) ;		// prints the inorder, preorder and postorder traversal of the subtree rooted at 'key_val' node
tn* node_finder(tn* root ,unsigned int key_val) ;		// finds the desired node in the tree and returns the node
int find(tn* root ,unsigned int key_val) ;		// returns 1 if the desired node is found in the tree
int CalculateImbalance(tn* root, unsigned int key_val) ;		// Calculates the imbalance between the left and right subtree rooted at the 'root'

tn* MIN(tn* root){		//  function definition
	tn* min = NULL ;
	min = (struct node*)malloc(sizeof(struct node)) ;
	min = root ;
	while(min->left_c != NULL){		// since the minimum value of the tree is located at the very left side, the min pointer travels to the left most node of the tree
		min = min->left_c ;}
	return min ;
}

tn* MAX(tn* root){		// function definition
	tn* max = NULL ;
	max = (struct node*)malloc(sizeof(struct node)) ;
	max = root ;
	while(max->right_c != NULL){		// since the largest key value is present at the very right side of the tree,the max pointer travels to the very right of the tree
		max = max->right_c ;}
	return max ;
}

int right_child(tn* parent_of, tn* child){		// function definition
	if(parent_of->right_c == child && child->parent == parent_of){		// this function simply tells if the child is the right child of the given parent by a single if statement
		return 1 ;}
	else{
		return 0 ;}
}

int left_child(tn* parent_of, tn* child){		// function definition
	if(parent_of->left_c == child && child->parent == parent_of){		// this function simply tells if the child is the right child of the given parent by a single if statement
		return 1 ;}
	else{
		return 0 ;}
}

tn* predecessor(tn* feed_node){		 //function definition
	if(feed_node->left_c != NULL){		// if the feed node contains a left child then the predecessor of the feed node is the maximum element of the left subtree rooted at the feed node
		tn* predecessor_node = NULL ;
		predecessor_node = MAX(feed_node->left_c) ;
		return predecessor_node ;
	}
	else if(feed_node->left_c == NULL){		// if the left child is not present then the predecessor of thr feed node is the forst ancestor of the feed node to have 
		tn* predecessor_node = NULL;		// the feed node or an ancestor of the feed node as its right child 
		tn* child_node = NULL ;
		child_node = feed_node ;
		while(child_node != NULL){		// this while loop finds out the parent that contains the child node as its right child 
			if(right_child(child_node->parent,child_node)){
				predecessor_node = child_node->parent ;
				return predecessor_node ;
			}
			else{
				child_node = child_node->parent ;
			}
		}
		if(child_node==NULL){			// if such a parent is not found then the node does not have a predecessor in the tree
			return NULL ;
		}	
	}
	return NULL ;
}

void inorder(tn* root){		// function definition
	if(root==NULL){		// if  the entered root is null then the function simply returns
		return ;
	}
	else{		// else the function recursively carries out the inorder traversal and prints the key value of the nodes to the file pointed by the ptr2 pointer
	    inorder(root->left_c);
	    fprintf(ptr2," %u",root->key) ;
	    inorder(root->right_c) ;
	}
}

void preorder(tn* root){		// function definition
	if(root==NULL){		// if the entered root is null then the function simply returns 
		return ;
	}
	else{		// else the function recursively carries out the preorder traversal and prints  the key value of the nodes to the file pointed by the ptr2 pointer
	    fprintf(ptr2," %u",root->key) ;
	    preorder(root->left_c);
	    preorder(root->right_c) ;
	}
}

void postorder(tn* root){		// function definition
	if(root==NULL){		// if the entered root is null then the function simply returns
		return ;
	}
	else{		// else the function recursively carries out the postorder traversal and prints the key value of the nodes to the file pointed by the ptr2 pointer
	    postorder(root->left_c);
	    postorder(root->right_c) ;
	    fprintf(ptr2," %u",root->key) ;
	}
}

void counter(tn* root){		// function definition
        if(root ==  NULL){		// if the entered root is null then the function simply returns
			return ;
		}
		else{		// else the function recursively counts the number of nodes in the tree by incrementing the global variable x until null pointer is reached
		    ++x ;
		    counter(root->left_c);
		    counter(root->right_c);}
}

int insert(tn* root, unsigned int key_val){		// function definition
	if(root->parent==NULL && router == 0){		// this if statement works only once during the first insertion to establish the route node.Once that is done the router variable is assigned 1
		root->key = key_val ;
        router = 1 ;
		return 1;
	}
	if(root->key < key_val){		// if the key to be inserted has a greater value than the key of the present node this if statement is executed
		if(root->right_c==NULL){		// if the right child of the present node is null the new node is inserted as the right child
			tn* newnode = NULL ;
			newnode = (struct node*)malloc(sizeof(struct node)) ;
			newnode->right_c = NULL ;
			newnode->left_c = NULL ;
			newnode->parent = root ;
			root->right_c = newnode ;
			newnode->key = key_val ;
			return 1 ;
		}
		else{
			return insert(root->right_c,key_val) ;		// if the present node does have right child, the insert function is recursively called with the right subtree of the present node and the key to be inserted
		}	
	}
	else if(root->key > key_val){		 // if the key to be inserted has a  smaller  value than the key of the present node this if statement is executed
			if(root->left_c==NULL){		// if the left child of the present node is null the new node is inserted as the left child
			tn* newnode =NULL ;
			newnode = (struct node*)malloc(sizeof(struct node)) ;
			newnode->right_c = NULL ;
			newnode->left_c = NULL ;
			newnode->parent = root ;
			root->left_c = newnode ;
			newnode->key = key_val ;
			return 1 ;
		}
		else{
			return insert(root->left_c,key_val) ;		// if the present node does have a left child, the insert function is recursively called with left subtree of the present node and the key to be inserted
		}
	}
	else{		// if the insertion of the node is successfull then 1 is returned. Else 0 is returned
		return 0 ;
	}
}

int delete(tn* root, unsigned int key_val){		// function definition
	
	tn* root_key = NULL ;	
	root_key = node_finder(root,key_val) ;			// finding the node to be deleted
	
	if(root_key == NULL){		// if the node to be deleted does not exist then the node_finder will return NULL to root_key
		return 0 ;
	}
	
	if(root_key->right_c==NULL && root_key->left_c == NULL){							// if node to be deleted as is a leaf
		if(root_key->parent!=NULL){																	// first subcase is when the parent is not NULL i.e. the leaf is not the last node in the tree aka root
		    tn* parent =  root_key->parent ;														// the node is simply depointed from its parent in this case	                                     
		    if(left_child(parent,root_key)){		
			   parent->left_c = NULL ;
		   }
		   else{
			   parent->right_c = NULL ;		
		   }
		   root_key->parent = NULL ;		 
		   free(root_key) ; 		 
		   return 1 ;	}
		else{
			root = NULL ;																						// if the node to be deleted is the root node in this case ,the function simply returns -2 to main											
			return -2 ;																						// where the root node is made NULL
		}	
	}
	else if((root_key->right_c == NULL && root_key->left_c != NULL)){			// this case occurs when the node to be deleted does not have a right child but has a left child
        tn* predes = NULL ;		                                                                        // predecessor of the node is found and replaced in the place of the node to be deleted 
        predes = predecessor(root_key) ;	                                                        // the process is recursive . predecessor in the process are replaced by their predecessor	
        root_key->key = predes->key ;                                                                // untills it falls to one of the base cases .
		return delete(predes,predes->key) ;
		
	}
	else if((root_key->right_c != NULL && root_key->left_c == NULL)){			// if the node to be deleted has a right child and not a left child then the 	
		if(root_key->parent!=NULL){																	// parent of the node to be deleted is linked to the child of the node to be deleted 
		    tn* grand_parent = NULL ;                              									// and the node to be deleted is made free . This happens for the subcase when the 
		    tn* child = NULL ;																				// the node to be deleted is not the root node
		    child = root_key->right_c ;
		    grand_parent = root_key->parent ;
		    child->parent = grand_parent ;
		    if(right_child(grand_parent,root_key)){
			    grand_parent->right_c = child ;
		    } 
		    else{
			    grand_parent->left_c = child ;
		   } 
		    root_key->parent = NULL ;
		    root_key->right_c = NULL ;
		    free(root_key) ;
		    return 1 ;}
		else{																									// if the node to be deleted in such a case is the root node the function simply returns -3
			return -3 ;																						// to the main where the only child of the root node is made the new root node 
		  }
	}
	else if(root_key->right_c != NULL && root_key->left_c != NULL){	
		tn* predes = NULL ;			
		predes = predecessor(root_key) ;
		root_key->key = predes->key ;																									
		return delete(predes,predes->key) ;																																								
	}
	else{
		return 0 ;
	}
}

void print(tn* root){		// function definition
	if(root==NULL){
		fprintf(ptr2,"\nThe tree does not exist") ;
		return ;
	}
	fprintf(ptr2,"\nInorder :") ;			// the print function just brings together the functionality of the inorder, preorder and postorder traversal function into a single function
	inorder(root) ;
	fprintf(ptr2,"\nPreorder :") ;
	preorder(root) ;
	fprintf(ptr2,"\nPostorder :") ;
	postorder(root) ;
}

void print_subtree(tn* root,unsigned int key_val){		// function definition
	
	tn* key_root = NULL ;		// it is same as the print function but has the capability to start the printing from any node that is taken as the root of the subtree to be printed
	key_root = (struct node*)malloc(sizeof(struct node)) ;
	key_root = node_finder(root,key_val) ;
    if(key_root==NULL){
		fprintf(ptr2,"\nThe root does not exist") ;
		return ;
	}
	print(key_root) ;
}

tn* node_finder(tn* root, unsigned int key_val){		// function definition
	
	tn* finder = NULL ;
	finder = (struct node*)malloc(sizeof(struct node)) ;
	finder = root ;

	while(1){																																						// given a key value the node_finder function finds and returns the desired node. If the key value of the node matches with key value of 
		                         																																				// desire then the node is returned . Else the while loop goes on until the finder pointer reaches the end of the tree.
		if(finder->key == key_val){																												// In the while loop the finder pointer goes on comparing with nodes at every level and decides its next movement.
			return finder ;																																		// NULL is returned the required node is not present in the tree. 
		}
		
		if((finder->key > key_val) && finder->left_c != NULL){
			finder = finder->left_c;
		}
		else if((finder->key > key_val) && finder->left_c != NULL){
			return NULL ;
		}
		else if((finder->key < key_val) && finder->right_c != NULL){
			finder = finder->right_c;
		}
		else{
			return NULL;
		}
	}
}

int find(tn* root ,unsigned int key_val){		// function definition
	tn* finder = NULL ;
	finder = (struct node*)malloc(sizeof(struct node)) ;
	finder = root ;
	int level = -1 ;
	while(1){																																			    	// This function has totally the same functionality as the node_finder function.The only difference is that
		level+=1 ;                                                                                                             									// this function does return the node itself .Rather it returns the level of the node if the node is found 
																																											// if the desired node is not present in the tree the function returns -1
		if(finder->key == key_val){
			return level ;
		}
		
		if((finder->key > key_val) && finder->left_c != NULL){
			finder = finder->left_c;
		}
		else if((finder->key > key_val) && finder->left_c == NULL){
			return -1 ;
		}
		else if((finder->key < key_val) && finder->right_c != NULL){
			finder = finder->right_c;
		}
		else{
			return -1;
		}
	}
}

int CalculateImbalance(tn* root, unsigned int key_val){		// fnction definition
	tn* root_key = NULL ;
	root_key = node_finder(root,key_val);											// root_key is the node whose no. of nodes in the left and right subtree have to be found 
	if(root_key==NULL){		// if the node_finder function returns null, it means that the node is not present in the tree and -10000 is returned
		return -10000;
	}
	else{		// if the node is present then the nmber of nodes in the left and right sbtree are calculated using the counter as described above
		counter(root_key->left_c);
		int left = x ;
		x = 0 ;		// after calculating the number of nodes in the left subtree and storing the value in 'left' variable x is reinitialized to 0 for use in counting the no. of nodes in the right subtree.
		counter(root_key->right_c);
		int right = x ; 		// the 'right' variable stores the number of variables in the right subtree
		x = 0 ;	
		int imbalance = left-right ;				// imbalance is calculated as left - right. negative value means there are more nodes in the right subtree .postive value means left subtree has more nodes
		return imbalance ;					// the imbalance variable is then returned
	}
}

int main(){
	
	FILE* ptr1 = fopen("input.txt","r");		// this file pointer reads from the input text file .
	ptr2 = fopen("output.txt","w");		// this file pointer writes to the output text file
	tn* root = NULL;		// this pointer is the root of the tree to be constructed
	root = (struct node*)malloc(sizeof(struct node)) ;
	root->parent = NULL ;
	root->right_c = NULL ;
	root->left_c = NULL ;
	int N ;		// N is the number of operations that have to be done
	fscanf(ptr1,"%d",&N);		// extracting the value of  N from the input file
	//printf("\n N %d",N);
	int i = 0;		// while loop iterator
	int option ;		// stores the case nmber (corresponding to a specific function) to be executed
	unsigned int key_input ;		// for taking the key value from the input file
	int flag;		// variable for storing the return value of some functions
	while(i < N){
		fscanf(ptr1,"%d",&option) ;		// scanning the input file for the option number
		//printf("\n OPT %d",option);
		switch(option){		// switch case to choose the option
			
			case 1:{		// insert function
				fscanf(ptr1,"%u",&key_input) ;		// taking the key value to be inserted from the file
				//printf("\n%u",key_input) ;
				flag = insert(root,key_input) ;		// inserting the key into the tree
				if(flag==1){		// flag = 1 means successfully inserted and true is printed to the file, else false is printed to the file
					fprintf(ptr2,"\ntrue");
				}
				else{
					fprintf(ptr2,"\nfalse");
				}	
				
			}
			break ;
			case 2:{		// delete function
				fscanf(ptr1,"%u",&key_input) ;		 // taking the key value to be inserted from the file
				//printf("\n%u",key_input) ;
				flag = delete(root,key_input) ;		// deleting the key
				if(flag==1){		// flag=1 means successfully deleted and true is printed to the file, else false is printed to the file
					fprintf(ptr2,"\ntrue");
				}
				else if(flag==-2){		// when root node is the only remaining node to be deleted 
					root = NULL ;
					fprintf(ptr2,"\ntrue") ;
				}
				else if(flag==-3){		// when the root node having only right child is to be deleted
					tn* del = root ;
					root = root->right_c ;
					root->parent = NULL ;
					del->right_c = NULL ;
					free(del) ;
				}
				else{
					fprintf(ptr2,"\nfalse");
				}
			}
			break ;
			case 3:{		// find funtion
				fscanf(ptr1,"%u",&key_input) ;		// taking the key value to be found in the tree  from the file
				//printf("\n%u",key_input) ;
				flag = find(root,key_input) ;		// finding the key
				if(flag==-1){				// flag=-1 means  node was not present in the tree and false is printed .else true is printed along with the depth of the node
					fprintf(ptr2,"\nfalse") ;
				}
				else{
					fprintf(ptr2,"\ntrue, depth = %d",flag) ;
				}
				
			}
			break ;
			case 4:{		// printing the entire tree
				print(root);
			}
			break ;
			case 5:{		// printing the subtree
				fscanf(ptr1,"%u",&key_input) ;		// scanning for key value from which the printing has to start
				//printf("\n%u",key_input) ;
				print_subtree(root,key_input) ;
				
			}
			break ;
			case 6:{		// finding the imbalance
				fscanf(ptr1,"%u",&key_input) ;		// taking the key input of the node whose subtrees have to be evaluated for imabalance
				//printf("\n%u",key_input) ;
				int flag = CalculateImbalance(root,key_input) ;		// calculating the imbalance
				if(flag == -10000){		// flag=-10000 means that the subtree root  node was not found at all and 'tree absent' is printed. else imbalance value is printed to the file.
					fprintf(ptr2,"\ntree absent") ;
				}
				else{
					fprintf(ptr2,"\nImbalance = %d",flag) ;
				}	
			    }
			    break ;
			
		}
		
		++i ;
	}

	fclose(ptr1);				// files are closed at the end of the program
	fclose(ptr2);
}


