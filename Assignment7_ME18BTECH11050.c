#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct node{		// structure to represent a node in the tree
	unsigned int key ;		// this variable stores the key of the node
	unsigned int size ;     // stores the size of the tree rooted at the given node
	struct node* right_c ;		// pointer to point the right child of the node
	struct node* left_c ;		// pointer to point the left child of the node
	struct node* parent ;		// pointer to point the parent of the node
};

typedef struct node tn ;		// alias name for the structure 'tn'

FILE* ptr2 ;		// globally declared file pointer to be used in the print functions
int router = 0;		// this variable helps to establish the root node in the tree through the insert function
int router_2 = 0 ;
int x=0;		// this variable helps in counting the number of nodes in the tree in the counter function

int right_child(tn* parent,tn* child) ;		// returns 1 if the child is the right child of the parent
int left_child(tn* parent,tn* child) ;		// returns 1 if the child is the left child of the parent
tn* MIN(tn* root) ;		// finds the node with the minimum key value
tn* MAX(tn* root) ;		// finds the node with the maximum key value
tn* successor(tn* feed_node) ;		// finds the successor node of the node passed in the argument
tn* predecessor(tn* feed_node) ;		// finds the predecessor node of the node passed in argument
void inorder(tn* root) ;		// function prints the inorder traversal of the tree to the desired file
void preorder(tn* root) ;		// function prints the preorder traversal of the tree to the desired file
void postorder(tn* root) ;		// function prints the postorder traversal of the tree to the desired file
void counter(tn* root);		// counts the number of nodes in the tree rooted at 'root'
int insert_at_leaf(tn* root, unsigned int key_val) ;		// inserts the 'key_val' into the tree
tn* insert_at_root(tn* root, unsigned int key_val) ;        // inserts the 'key_val' in to the tree at the root
tn* insert(tn* root, unsigned int key_val) ;        // auxillary function used in insert_at_root function
int probabilistic_insert(tn* root, unsigned int key_val) ;      // carries out one of the twp types of insert based on probability
tn* delete(tn* root, unsigned int key_val) ;		// deleted the'key_val' from the tree if it exists
void print(tn* root) ;		// prints the inorder, preorder and postorder traversal to the desired file
void print_subtree(tn* root, unsigned int key_val) ;		// prints the inorder, preorder and postorder traversal of the subtree rooted at 'key_val' node
tn* node_finder(tn* root ,unsigned int key_val) ;		// finds the desired node in the tree and returns the node
int find(tn* root ,unsigned int key_val) ;		// returns 1 if the desired node is found in the tree
int CalculateImbalance(tn* root, unsigned int key_val) ;		// Calculates the imbalance between the left and right subtree rooted at the 'root'
void update_size(tn* root) ;        // updates the size of the tree rooted at each node
tn* rotate(tn* pivot) ;     // the function rotates the pivot with respect to its parent
tn* join(tn* left, tn* right) ;     // Auxillary function used in delete
tn* go_to_root(tn* node) ;      // takes the input pointer to the root of the tree and returns the root

tn* go_to_root(tn* node){       // function definition
    if(node==NULL){     // if node doesnt exist, NULL is returned
        return NULL ;
    }
    while(node->parent != NULL){    // this loop travels the node to the root
        node = node->parent ;
    }
    return node ;       // root is returned
}

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

tn* successor(tn* feed_node){		// function definition

	if(feed_node->right_c != NULL){		// if the feed node contains a right child then the successor of the feed node is the minimum element of the right subtree rooted at the feed node
		tn* successor_node = NULL ;
		successor_node = MIN(feed_node->right_c) ;
		return successor_node ;
	}
	else if(feed_node->right_c == NULL){		// if the right child is not present then the successor of the feed node is the first ancestor of the feed node to have
		tn* successor_node = NULL;              // the feednode or an ancestor of the feed node as its left child
		tn* child_node = NULL ;
		child_node = feed_node ;
		while(child_node != NULL){		// this while loop finds out the parent that contains the child node as its left child
			if(left_child(child_node->parent,child_node)){
				successor_node = child_node->parent ;
				return successor_node ;
				}
			else{
				child_node = child_node->parent ;
				}
		}
		if(child_node==NULL){		// if such a parent is not found then the node does not have a successor in the tree
			return NULL ;
			}
	}
	return NULL ;
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

void update_size(tn* root){     // function definition
    if(root==NULL){                 // the function works by updating the size of the tree rooted at each node
        return ;
    }
    else{
        counter(root) ;         // counts the number of nodes in the tree rooted at the root
        root->size = x ;         // updating the size variable
        x = 0 ;                 // the variable x has to be set to 0 after each iteration as it is a global variable
        update_size(root->left_c) ;     // recursively updating the size at each node
        update_size(root->right_c) ;
    }
}

int insert_at_leaf(tn* root, unsigned int key_val){		// function definition
	if(root->parent==NULL && router == 0){		// this if statement works only once during the first insertion to establish the route node.Once that is done the router variable is assigned 1
		root->key = key_val ;
        router = 1 ;
		return -1;
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
			return -1 ;
		}
		else{
            update_size(root) ;     // updating the size of the tree at each node rooted at root before using probabilistic insert
			return probabilistic_insert(root->right_c,key_val) ;		// if the present node does have right child, the insert function is recursively called with the right subtree of the present node and the key to be inserted
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
			return -1 ;
		}
		else{
            update_size(root) ;     // updating the size of the tree at each node rooted at root before using probabilistic insert
			return probabilistic_insert(root->left_c,key_val) ;		// if the present node does have a left child, the insert function is recursively called with left subtree of the present node and the key to be inserted
		}
	}
	else{		// if the insertion of the node is successfull then 1 is returned. Else 0 is returned
		return -2 ;
	}
}

tn* insert(tn* root, unsigned int key_val){     // function definition
    if(root->parent==NULL && router == 0){		// this if statement works only once during the first insertion to establish the route node.Once that is done the router variable is assigned 1
		root->key = key_val ;
        router = 1 ;
		return root;
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
			return newnode ;
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
			return newnode ;
		}
		else{
			return insert(root->left_c,key_val) ;		// if the present node does have a left child, the insert function is recursively called with left subtree of the present node and the key to be inserted
		}
	}
	else{		// if the insertion of the node is successfull then 1 is returned. Else 0 is returned
		return NULL ;
	}
}

tn* insert_at_root(tn* root, unsigned int key_val){     // function definition

    tn* pivot = NULL ;
    pivot = insert(root, key_val) ;     // firstly we insert the node which has to be made the root of the subtree at the leaf

    if(pivot->parent == NULL){      // if the node inserted is the root the pivot is simply returned
        return pivot ;
    }

    if(root->parent !=  NULL){                // if the subtree in which the node is inserted is not the main tree then this "if" block is followed
        tn* connector = NULL ;                // the parent of the subtree root is stored in the connector variable. if the connector and the root have a
        connector = root->parent ;            // right child and parent relationship , the connectors right child pointer is made null and the parent of the
                                              // root is made null . Then the subtree rooted at the root is rotated about the pivot in order to make the pivot
        if(right_child(connector,root)){      // the root of the subtree. After that the pivot (which is now the root of the subtree) becomes the right child
            connector->right_c = NULL ;       // of the connector and the connector becomes the parent of the pivot.
            root->parent = NULL ;             // Same function is carried out if the connector and the root have a left child and parent relationship.
            pivot = rotate(pivot) ;           // The two functions are carried out in the nested if else block.
            connector->right_c = pivot ;
            pivot->parent = connector ;
        }
        else{
            connector->left_c = NULL ;
            root->parent = NULL ;
            pivot = rotate(pivot) ;
            connector->left_c = pivot ;
            pivot->parent = connector ;
        }
       return go_to_root(pivot) ;   // After the root insertion the function returns the root of the main tree.
    }
    else{                                     // If the subtree in which the node to be inserted is actually the main tree, then this "else" statement is followed
       pivot = rotate(pivot) ;
       return go_to_root(pivot) ;
    }
}

tn* rotate(tn* pivot){      // function definition

    if(pivot->parent == NULL){      // If the pivot is already the root of the subtree in which it is inserted then the function returns the pivot
        return pivot ;}

    tn* parent_node = NULL ;        // If the above "if" statement does not work then the pivot has a parent and hence has to be rotated
    parent_node = pivot->parent ;

    if(left_child(parent_node,pivot)){                              // If the pivot is the left child of its parent then ,the right subtree of the pivot
        parent_node->left_c = NULL ;                                // (if it exists) is made the left subtree (left child) of the parent of the pivot .
        parent_node->left_c = pivot->right_c ;                      // the right child pointer of the pivot is set to null . The parent of the pivot is then
        pivot->right_c = NULL ;                                     // made the right child of the pivot . parent's parent is made the parent of the pivot
        pivot->right_c = parent_node ;                              // (if the parent's parent exists) .
        pivot->parent = NULL ;                                      // Same procedure is followed if the pivot is the right child of its parent.
        pivot->parent =  parent_node->parent ;                      // The outer most if else block carry out this function.

        if(parent_node->parent != NULL){        // based on this if else block the relationship between paremt_node's parent and the parent_node is
                if(left_child(parent_node->parent, parent_node)){   // established and the pivot is assigned as the child of the parent_node's parent.
                    parent_node->parent->left_c = NULL ;
                    parent_node->parent->left_c = pivot ;}
                else{
                    parent_node->parent->right_c = NULL ;
                    parent_node->parent->right_c = pivot ;}
        }
        parent_node->parent = NULL ;
        parent_node->parent = pivot ;
        if(parent_node->left_c != NULL){
			parent_node->left_c->parent = parent_node;}
		}
    else{                                                           // Same functionality as the above if statement.
        parent_node->right_c = NULL ;
        parent_node->right_c =pivot->left_c ;
        pivot->left_c = NULL ;
        pivot->left_c = parent_node ;
        pivot->parent = NULL ;
        pivot->parent = parent_node->parent ;

        if(parent_node->parent != NULL){
                if(left_child(parent_node->parent, parent_node)){
                    parent_node->parent->left_c = NULL ;
                    parent_node->parent->left_c = pivot ;
                }
                else{
                    parent_node->parent->right_c = NULL ;
                    parent_node->parent->right_c = pivot ;
                }
        }
        parent_node->parent = NULL ;
        parent_node->parent = pivot ;
        if(parent_node->right_c != NULL){
			parent_node->right_c->parent = parent_node;}
    }
                                // Rotate is a recursive function and the will execute recursively until the pivot becomes the root of the subtree
    return rotate(pivot) ;      // in which it is inserted.
}

int probabilistic_insert(tn* root_node, unsigned int key_val){      // function definition
    srand(time(0)) ;
    int t ;                                        // This function generates a random number based on the size of the subtree in which insertion has to take
    t = rand()%(root_node->size) ;                 // place and stores it in the variable t. If t == 0 (which will happen with probability 1/root->size)
                                                   // then the key of the root_node is returned and insertion at the root_node is carried out in the main function.
    if(t==0){                                      // For any other value insertion at leaf is carried out.
        return root_node->key ;}
    else{
        return insert_at_leaf(root_node,key_val) ;}
}

tn* delete(tn* root, unsigned int key_val){		// function definition

    tn* T = node_finder(root,key_val) ;     // The node to be deleted is found

    if(T == NULL){      // If T is null that means the node does not exist in the tree
        return root ;
    }
    else if(T->parent!= NULL){                       // If T is not NULL and has a parent then parent_node is stored and T's relationship with its parent is broken based on the
        tn* parent_node = T->parent ;                // condition if it is the right child or the left child of its parent . Then the subtree which is now rooted at T
        if(right_child(parent_node,T)){              // is now used in the join function .The join function after joining the right and left subtree of T returns either the right
            parent_node->right_c = NULL ;            // or the left child of T which is stored in the variable temp. Since temp is a child of T , its relationship with T
            T->parent = NULL ;                       // is broken and T's parent is now assigned as temp's parent and temp is assigned as the child of T's parent in the same
            tn* temp = join(T->left_c,T->right_c) ;  // orientation as T was . This eliminates T from the tree , The parent, right child and left child pointer of the
            if(T->right_c!= NULL){                   // node T is assigned NULL and T itself is assigned NULL.
                    T->right_c = NULL ;}
            if(T->left_c!=NULL){
                    T->left_c = NULL ;}
            T = NULL ;
            if(temp!=NULL){
                temp->parent = NULL ;
                parent_node->right_c = temp ;
                temp->parent = parent_node ;
                return go_to_root(temp) ;
            }
            else{
                return root ;
            }
        }
        else{                                       // This 'else' block has the same function as explained above as the "if" block and runs when T
            parent_node->left_c = NULL ;            // is the left child of its parent.
            T->parent = NULL ;
            tn* temp = join(T->left_c, T->right_c) ;
            T->right_c = NULL ;
            T->left_c = NULL ;
            T = NULL ;
            if(temp!=NULL){
                temp->parent = NULL ;
                parent_node->left_c = temp ;
                temp->parent = parent_node ;
                return go_to_root(temp) ;
            }
            else{
                return root ;
            }
        }
    }
    else if(T->parent == NULL){                     // If T does not have a parent that means tree is the root .In this case we don't need to
        tn* temp = join(T->left_c, T->right_c) ;    // store the parent of T. The rest of the function is similar to above.
        if(T->right_c!= NULL){
                T->right_c = NULL ;
        }
        if(T->left_c!=NULL){
                T->left_c = NULL ;}
        T = NULL ;
        if(temp!=NULL){
            temp->parent = NULL ;
            return temp ;}
        else{
            return NULL ;
        }
    }
}

tn* join(tn* left, tn* right){      // function definition

    int m, n, r, total ;
    if(left==NULL){         // if the left pointer is null them m is set to 0 else it is set to left->size value
        m = 0;}
    else{
        m = left->size ;}

    if(right==NULL){        // if the right pointer is null them n is set to 0 else it is set to right->size value
        n = 0 ;}
    else{
        n = right->size ;}

    total = m+n ;           // total stores the value of m+n

    if(total==0){           // if both the right and left pointer are NULL the total is 0 and NULL is returned
        return NULL ;}

    srand(time(0)) ;
    r = rand()%(total) ;    // r stores a random number from 0 to total-1

    if(r<m){        // r is less than m with a probability m/(m+n) .
        left->right_c = join(left->right_c,right) ;     // This function works recursively
        if(left->right_c != NULL){
            tn* child = left->right_c ;             // This if statement sets the left pointers child's parent pointer to left to ensure the two way
            child->parent =left ;}                  // child parent connection
        return left ;}
    else{
        right->left_c = join(left,right->left_c) ;
        if(right->left_c != NULL){                  // This if statement sets the right pointers child's parent pointer to right to ensure the two way
            tn* child = right->left_c ;             // child parent connection
            child->parent = right ;}
        return right ;}
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

int CalculateImbalance(tn* root, unsigned int key_val){		// function definition
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
	if(ptr1==NULL){
        printf("\ninput file not found ") ;
        return 0 ;
	}
	ptr2 = fopen("output.txt","w");		// this file pointer writes to the output text file
    if(ptr2==NULL){
        printf("\noutput file not found ") ;
        return 0 ;
	}
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
	tn* newnode = NULL ;
	while(i < N){
		fscanf(ptr1,"%d",&option) ;		// scanning the input file for the option number
		switch(option){		// switch case to choose the option

			case 1:{		// insert function
			    fscanf(ptr1,"%u",&key_input) ;
			    update_size(root) ;
			    int flag = probabilistic_insert(root,key_input) ;

			    if(flag==-1){
                    fprintf(ptr2,"\ntrue") ;
			    }
			    else if(flag==-2){
                    fprintf(ptr2,"\nfalse") ;
			    }
			    else{
                    tn* root_node = NULL ;
                    root_node = node_finder(root,flag) ;
                    root = insert_at_root(root_node,key_input) ;
                    fprintf(ptr2,"\ntrue") ;
			    }

			}
			break ;
			case 2:{		// delete function
				fscanf(ptr1,"%u",&key_input) ;		 // taking the key value to be inserted from the
				update_size(root) ;
				int b = root->size ;
				root = delete(root,key_input) ;		// deleting the key
				update_size(root) ;
				int a = 0 ;
				if(root!=NULL){
                    a = root->size ;}
				if(root!= NULL && (a!=b)){		// flag=1 means successfully deleted and true is printed to the file, else false is printed to the file
					fprintf(ptr2,"\ntrue");
				}
				else if(root==NULL && b==1){
					fprintf(ptr2,"\ntrue") ;
				}
				else{
                    fprintf(ptr2,"\nfalse") ;
				}
			}
			break ;
			case 3:{		// find funtion
				fscanf(ptr1,"%u",&key_input) ;		// taking the key value to be found in the tree  from the file
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
				print_subtree(root,key_input) ;

			}
			break ;
			case 6:{		// finding the imbalance
				fscanf(ptr1,"%u",&key_input) ;		// taking the key input of the node whose subtrees have to be evaluated for imabalance
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


