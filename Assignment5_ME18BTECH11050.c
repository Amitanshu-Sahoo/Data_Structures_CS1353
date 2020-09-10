#include<stdio.h>                                                       
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#define MAX_LIMIT 100                                                   // Macro definition of the max limit of the string

struct symbol{                                                          // Structure for the node
	float num ;                                                         // This variable stores number value
	char sym ;                                                          // This variable stores symbol value
	int flag ;                                                          // This variable helps in identifying the type of variable stored in the structure . 0 for operands, 1 for operators, 2 for brackets 
	int pos ;                                                           // This variable stores the position of the node in the stack
	struct symbol* down ;                                               // self referencial structure 
};

typedef struct symbol ip ;                                              // Creating an alias name for the structure
                                          
float power(float m,int n) ;                                            // Function definition for power 
ip* push(ip* newnode, ip* head) ;                                       // Function definition for pushing node in the stack 
ip* pop(ip* head) ;                                                     // Function definition for poping node from the stack
ip* invert_stack(ip* head) ;                                            // Function definition for inverting the node order in the stack
ip* position_specify(ip* head) ;                                        // Function definition for specifying the position of the nodes in the stack
void print(ip* head) ;                                                  // Function definition for printing the contents of the stack
int bracket_match(ip* head) ;                                           // Function definition for checking the balance of the brackets in the stack
int expression_check(char array[],ip* head) ;                           // Function definition for cheking the entered expression in the stack
void postfix_exp(ip* head) ;                                            // Function definition for converting the infix to postfix expression in the stack
void evaluation(ip* head) ;                                             // Function definition for evaluating the contents in the postfix stack

ip* position_specify(ip* head){
	int p = 0 ;                                                         // Iterative variable that initiaizes the position of the nde in the loop
	ip* count = NULL ;                                                  // Temporary node head which helps in assigning the position value in the loop
	count =(struct symbol*)malloc(sizeof(struct symbol)) ;
	count = head ; 
	while(count != NULL){                                               // Assigning the position variable in each node in the loop
		p+=1 ;
		count->pos = p ;
		count = count->down ;}
		return head ;
}

ip* infix_constructor(char array[]){                                         

int length = strlen(array) ;                                            // Finding the length of the array 
ip* head_is_t = NULL ;                                                  // This node will form the infix stack in reverse order 
int i = 0 ;
while(i < length){
	if(array[i]=='{' || array[i]=='[' || array[i]=='(' || array[i]==')' || array[i]==']' || array[i]=='}'){		// If brackets are encountered they are straight away pushed into the stack
		ip* newnode = NULL ;                                                                                    // This is done by making a newnode and pushing the newnode into the head_is_t 
		newnode = (struct symbol*)malloc(sizeof(struct symbol)) ;                                               // stack after filling up all the information
		newnode->flag = 2 ;
		newnode->sym = array[i] ;
		newnode->num = -1 ;
		head_is_t = push(newnode,head_is_t) ;
		++i ;
	}
	else if(array[i]=='+' || array[i]=='-' || array[i]=='*' || array[i]=='/' || array[i]=='^'){                 // If operators are encountered they are treated in the same way as brackets
		ip* newnode = NULL ;
		newnode = (struct symbol*)malloc(sizeof(struct symbol)) ;
		newnode->flag = 1 ;
		newnode->sym = array[i] ;
		newnode->num = -1 ;
		head_is_t = push(newnode,head_is_t) ;
		++i ;
	}
	else if(isdigit(array[i]) != 0 || array[i] == '.'){                 // Complication arises if a digit is encountered in the problem 
		int j = i ;                                                     // index is transferred to another variable for manipulation.
		int p = 0 ;                                                     // p = 1 if a dot operator is encountered and 0 if not
		int int_count = 0 ;                                             // Variable counts the number of digits before the decimal point
		int dec_count = 0 ;	                                            // Variable counts the number of digits after the decimal point
		while(isdigit(array[j]) != 0 || array[j] == '.'){               // This loop counts the number of digits in the number before and after the decimal point
				
			if(array[j] == '.'){                                        // This if statement checks if the number has a decimal point.
				p += 1 ;                                                
				++j ;}	                                                
			if(p>1){                                                            // if p becomes greater than 1 then the number of decimal points in the number is greater than 1 which is an error .
				printf("\nERROR!!More than one dot operator in a number") ;     // Hence the function returns
				return NULL ;}
			if(isdigit(array[j]) != 0 && p == 1){
				++dec_count ;                                           // if p becomes one dec_count variable is incremented
		    	++j ;}	
			if(isdigit(array[j]) != 0 && p == 0){                       // until decimal point is not detected int_count variable is incremented
				++int_count ;
				++j ;}
		}
		i = j ;                                                         // The actual iterator is incremented to the position just after the number ends
		j-=1 ;                                                          // The j iterator is set to the last digit of the number
		float sum = 0 ;                                                 // Sum variable stores the sum of the manipulation which is the whole number in itself
			
		if(p==1){	                                                    // This if statement is for decimal numbers
			float dec[dec_count] ;                                      // This array stores the int type of the char digit after the decimal point
			float num[int_count] ;                                      // This array stores the int type of the char digit before the decimal point
			int l = dec_count - 1 ;                                     // l and m are counters for the while loop below
			int m = int_count - 1 ;
			int pw = 0 ;                                                // pw stands for power of place value of the digit.
			while(l != -1){
				dec[l] = (float)(array[j] - '0') ;                      //This while loop iteratively converts the digits after decimal place from character to float .The adjacent line does the work
                sum = sum + dec[l]/power(10,l+1) ;                      //The place value of the digit is then calculated and added to the sum
				--l ; 
				--j ;	}
			j-=1 ;
	        while(m!=-1){
			    num[m] = (float)(array[j]- '0') ;                       // This while loop does the samework as the while loop above 
				sum = sum + power(10,pw)*num[m] ;                        // but for the digits before decimal places
				++pw ; 
				--m ;
				--j ;}
        }

        if(p==0){	                                                    //This if statement is for non decimal numbers
			float num[int_count] ;
			int m = int_count - 1 ;                                     // Same function as the just above if statement but only for the numbers which do not have decimal points
			int pw = 0 ;
		     while(m!=-1){
				num[m] = (float)(array[j]- '0') ;
				sum = sum + power(10,pw)*num[m] ;
				++pw ; 
				--m ;
				--j ;}
	       }

      ip* newnode = NULL ;                                              // Once the above operations above are done ,the sum now stores the number
      newnode = (struct symbol*)malloc(sizeof(struct symbol)) ;         // A new node is ade and the number is assigned in it and passed to the head_is_t stack
      newnode->flag = 0 ;
      newnode->num = sum ;
      newnode->sym = '#' ;
      head_is_t = push(newnode,head_is_t) ;	
	}
}
ip* head_infix = NULL ;                                                 // head_is_t stack stores the expreession but in reverse order and hence is not fruitful for manipulation
head_infix = invert_stack(head_is_t) ;                                  // invert stack function inverts the node order of the stack and stores it in anew stack named head_infix
head_infix = position_specify(head_infix) ;                             // Position in the head infix stacks are assigned and is sent for checking using expression_check function
int k = expression_check(array,head_infix) ;              
if(k==0){
	return NULL ;                                                       //If there is any error the expression check function returns 0 and then the program is stopped there
}
return head_infix ;                                                     // If there is no error in the head_infix stack it is returned

}

int bracket_match(ip* head){
	
	ip* check_brackets  = NULL ;                                        // The balancing of brackets is done in this function by using stacks
	ip* temp = NULL ;                                                   // This function takes up the infix stack  and assigns it to the temp node which would carry out the further computation
	temp = (struct symbol*)malloc(sizeof(struct symbol)) ;              //The idea of the function is simple as described in the below comments
	temp = head ;
	
	while(temp!=NULL){
		if(temp->flag == 2 && (temp->sym=='[' || temp->sym=='{' || temp->sym=='(')){        // Push the node to check_brackets stack if it contains an opening bracket
			if(temp->down!= NULL){                                                          // The exceptions being that the node should not be the last node to contain an opening bracket
				ip* newnode = NULL ;                                                        //If that is the case then the else case handles the error
				newnode = (struct symbol*)malloc(sizeof(struct symbol)) ;
				newnode->flag = temp->flag ;
				newnode->sym = temp->sym ;
				newnode->num = temp->num ;
				newnode->pos = temp->pos ;
			    check_brackets = push(newnode,check_brackets) ;
			    temp = temp->down ;
			}
			else{
				printf("\nERROR !! There is a mismatch of '%c' at the position %d." , temp->sym, temp->pos) ;
				return 0 ;
			}
		}
		else if(temp->flag == 2 && (temp->sym==']' || temp->sym=='}' || temp->sym==')')){			
			if(check_brackets!=NULL){                                                               
				if((temp->sym==']' && check_brackets->sym=='[') || (temp->sym=='}' && check_brackets->sym=='{') || (temp->sym==')' && check_brackets->sym=='(')){
					check_brackets = pop(check_brackets) ;                                          
					temp = temp->down ;                                                                      // If a closing bracket is seen then first the head node of check_brackets stack is checked
				}                                                                                            // If the head node contains the opposite bracket it is popped.
				else{                                                                                        // If it does not contain an opposite bracket it is popped.
					printf("\nERROR !! There is a mismatch of '%c' at the position %d." , check_brackets->sym, check_brackets->pos) ;
					return 0 ;                                                                               // The above happens if the check_brackets stack is not NULL
			    }                                                                                             
		    }
		    else{                                                                                            // If the check brackets stack is NULL and closing bracket is detected then error 
				printf("\nERROR !! There is a mismatch of '%c' at the position %d." , temp->sym, temp->pos) ;// message is displayed.
				return 0 ;
			}

	    }
	    else{                                                           // If brackets are not detected in a node then the iteration simply goes forward
			temp = temp->down ;
		}	
    }
    
    if(check_brackets == NULL){                                         // If at the end check_brackets atck is NULL it means all the brackets are balanced and 1 is returned                        
		return 1;                                                       // If it is not NULL then 0 is returned with an error message.
	}
	else{
		printf("\nERROR !! There is a mismatch of '%c' at the position %d." , check_brackets->sym, check_brackets->pos) ;
		return 0 ;
	}	
}

int expression_check(char array[],ip* head){  
	int length =  strlen(array) ;                                       
	int i = 0 ;
	int s = bracket_match(head) ;                                       // First the bracket balance is checked .If the bracket is not balanced then 0 is rturned from the bracket match function
	if(s==0){                                                           // and the program is stopped. Else the while loop below is run 
		return 0 ;}

	while(i < length){
		
		if((i==0 || i==length-1) && (array[i]=='+' || array[i]=='-' || array[i]=='^' || array[i]=='*' || array[i]=='/' )){           // If the starting and ending of an operation contains an operator
			if(i==0){                                                                                                                // it is an error and error message is displayed.  
			printf("\nERROR!! Operator symbol is occuring at the starting of the expression") ;}                                      
			else{                                                                                                                    
			    printf("\nERROR!! Operator symbol is occuring at the end of the expression") ;}                                      
			return 0 ;}		                                                                                                         
		else if((i==0 || i==length-1) && (array[i]=='.')){                                                                           // If the starting and ending of an operation contains a dot
			if(i==0){                                                                                                                // operator it is an error and error message is displayed.
			printf("\nERROR!! The dot operator for decimal numbers comes at the starting of the string") ;}               
			else{
				printf("\nERROR!! The dot operator for decimal numbers comes at the ending of the string") ;}
		    return 0 ;}
		    
		if( isdigit(array[i])!=0 && (array[i-1]==']' || array[i-1]=='}' || array[i-1]==')')){                                         
			printf("There is a closing bracket just before the  number at position %d", i+1) ; return 0 ;}                            // If a number is there in the ith position and closing/opening bracket
			                                                                                                                          // is there in the just before/after it respectively, it is an error 
		else if(isdigit(array[i])!=0 && (array[i+1]=='[' || array[i+1]=='{' || array[i+1]=='(')){                                     // and error message is displayed.
			printf("There is a opening bracket just after the  number at position %d", i+1) ; return 0 ;} 
			                              
	    else if( array[i]=='+' || array[i]=='-' || array[i]=='/' || array[i]=='*' || array[i]=='^' ){                                 // If two mathematical operators are side by side then it is an 
			if(array[i+1]=='+' || array[i+1]=='-' || array[i+1]=='/' || array[i+1]=='*' || array[i+1]=='^'){                          // error and error message is  displayed.
				printf("ERROR!! two operators occuring together at position %d and %d",i+1,i+2) ; return 0 ;}                         // If opening/closing brackets are present just after/before
			else if(array[i+1]=='}' || array[i+1]==']' || array[i+1]==')'){                                                           // the operator then it is an error and error message is displayed.
				printf("ERROR!! Misplaced operator at position %d",i+1) ; return 0 ;}                                                   
			else if(array[i-1]=='{' || array[i-1]=='[' || array[i-1]=='('){
				printf("ERROR!! Misplaced operator at position %d",i+1) ; return 0 ;}
			else if(array[i+1]=='.'){
				printf("ERROR!! Misplaced dot operator at position %d",i+2) ; return 0 ;}
			}	
			
		else if( array[i]=='.' ){                                                                                                      // If opening/closing brackets are present just after/before                     
			if(array[i-1]=='}' || array[i-1]==']' || array[i-1]==')' || array[i-1]=='{' || array[i-1]=='[' || array[i-1]=='('){                                                                 // the dot operator then it is an error and error message 
				printf("ERROR!! Misplaced dot operator at position %d",i+1) ; return 0 ;}                                                // is displayed.
			else if( array[i+1]=='}' || array[i+1]==']' || array[i+1]==')'|| array[i+1]=='{' || array[i+1]=='[' || array[i+1]=='(' ||array[i+1]=='+' || array[i+1]=='-' || array[i+1]=='/' || array[i+1]=='*' || array[i+1]=='^'){
				printf("ERROR!! Misplaced dot operator at position %d",i+1) ; return 0 ;}
			}
		++i ;
	}
	return 1;                                                           // If there is no error then 1 is returned 	
}

ip* push(ip* newnode, ip* head){
	if(head == NULL){                                                   // If the stack is NULL then head is NULL.In that case newnode->down is assigned to NULL and returned to head.
		newnode->down = NULL ;
		return newnode ;}
	else{                                                               // Else the newnode->down is pointed to head of the stack and is returned to head.
		newnode->down = head ;
		return newnode ;}
}

ip* pop(ip* head){
	if(head==NULL){                                                     // If the head is NULL that means the stack is NULL and NULL is returned to the head.
		return NULL ;}
	else{                                                               // Else a temp variable is assigned to the head .The head is assigned to head->down and temp->down is assigned to NULL 
		ip* temp = NULL ;                                               // and temp is freed. Head is returned to head.
		temp = (struct symbol*)malloc(sizeof(struct symbol)) ;
		temp = head ;
		head = head->down ;
		temp->down = NULL ;
		free(temp) ;
		return head ;}
}

ip* invert_stack(ip* head){
	
	ip* temp = NULL ;                                                   // The temp node is assigned to the head of the stack that is going to be inverted .
	temp = (struct symbol*)malloc(sizeof(struct symbol)) ;
	temp = head ;
	
	ip* head_new = NULL ;                                               // This is the head node of the new stack going to be formed after inversion
	ip* newnode =  NULL ;                                               // This node will help by passing one node at a time from the head stack to the head_new stack.
	
	while(temp != NULL){
		newnode = (struct symbol*)malloc(sizeof(struct symbol)) ;
		newnode->flag = temp->flag ;
		newnode->num = temp->num ;
		newnode->sym = temp->sym ;
		head_new = push(newnode,head_new) ;                             // The newnode is pushed to the head_new stack along with all the information of the node.
		temp = pop(temp) ;                                              // The same node is popped from the head stack using temp.
		newnode = NULL ;}
	return head_new ;                                                   // The head_new stack is then returned
}

void print(ip* head){
	
	ip* temp = NULL ;                                                   // The temp variable is assigned to the head of the stack for further operations.
	temp = (struct symbol*)malloc(sizeof(struct symbol)) ;
	temp = head ;
	
	while(temp != NULL){                                                // While stack is not over 
		if(temp->flag == 1 || temp->flag == 2){                         // If flag is 1 or 2 then an operator or bracket is present .Hence temp->sym is printed.
			printf("%c ",temp->sym) ;
			temp = temp->down ;}
		else if(temp->flag == 0){                                       // If flag is 0 then number is present .Hence temp->num is printed.
			printf("%.2f ",temp->num) ;
			temp = temp->down ;}
	}
}

float power(float m, int n){
	float s =1 ;                                                        // Simple function to find the value of m to the power n.                                      
	for(int i =1 ;i<=n; ++i){
		s = s*m ; }
	return s ;
}

void postfix_exp(ip* head){	

ip* temp_is = NULL ;                                                    // temp_is assigned to head of the infix stack and is used further in the operations and manipulations                                     
ip* head_ops = NULL ;                                                   // head_ops is the head node of the stack that will store the operators and brackets only
ip* head_pfs = NULL ;                                                   // head_pfs is the head node of the stack that will store the postfix expression
temp_is = (struct symbol*)malloc(sizeof(struct symbol)) ;
temp_is = head;

while(temp_is != NULL){
	if(temp_is->flag == 0){                                             // If an operand (number) is detected in the infix stack, A newnode is made and all the information of temp_is 
		ip* newnode = NULL ;                                            // is passed to the newnode and newnode is pushed to the head_pfs stack
		newnode = (struct symbol*)malloc(sizeof(struct symbol)) ;
		newnode->flag = temp_is->flag ;
		newnode->num = temp_is->num ;
		newnode->sym = temp_is->sym ;
		
		head_pfs = push(newnode,head_pfs) ;
		temp_is = temp_is->down ; 
	}
	else if(temp_is->flag == 1 && (temp_is->sym == '+' || temp_is->sym == '-')){                                                  // If '+' or '-' operator is detected
		while(head_ops!=NULL){                                                                                                    // If head_ops stack is not null then the head of the head_ops stack
		if(head_ops->sym == '*' || head_ops->sym == '+' || head_ops->sym == '-' || head_ops->sym == '/' || head_ops->sym == '^'){ // is analysed .If it is another operator of higher or same precedence
			ip* newnode = NULL ;                                                                                                  // then head_ops is popped and node is pushed into head_pfs stack .
			newnode = (struct symbol*)malloc(sizeof(struct symbol)) ;                                                             // This is continued until the while conditon
   			newnode->flag = head_ops->flag ;                                                                                      // is satisfied .Else we break out of the while loop                                                      
			newnode->num = head_ops->num ;                                                                                        
			newnode->sym = head_ops->sym ;
			head_pfs = push(newnode,head_pfs) ;
			head_ops = pop(head_ops) ;
		}
		else{
			break;}		
	}
		ip* newnode = NULL ;                                                                                                      //A newnode is made and informations of temp_is is passed to it
 		newnode = (struct symbol*)malloc(sizeof(struct symbol)) ;                                                                 // and the newnode is pushed to the head_ops stack
		newnode->flag = temp_is->flag ;
		newnode->sym = temp_is->sym ;
		newnode->num = temp_is->num ;
		head_ops = push(newnode,head_ops) ;
		temp_is = temp_is->down ;
    }
	else if(temp_is->flag == 1 && (temp_is->sym == '*' || temp_is->sym == '/')){                                                  // Idea is same is this else if statement as the above one
		while(head_ops!=NULL){                                                                                                    // If an operator of higher precedence is encountered in the head_ops
		if(head_ops->sym == '^' || head_ops->sym == '*' || head_ops->sym == '/'){                                                 // stack it is popped and the node is pushed to head_pfs.Then a 
			ip* newnode = NULL ;                                                                                                  // newnode is assgned the values of temp_is and is pushed to the head_ops
			newnode = (struct symbol*)malloc(sizeof(struct symbol)) ;                                                             // stack.                     
			newnode->flag = head_ops->flag ;
			newnode->num = head_ops->num ;
			newnode->sym = head_ops->sym ;
			head_pfs = push(newnode,head_pfs) ;
			head_ops = pop(head_ops) ;
		}
		else{
			break ;}
	}
		ip* newnode = NULL ;
		newnode = (struct symbol*)malloc(sizeof(struct symbol)) ;
		newnode->flag = temp_is->flag ;
		newnode->sym = temp_is->sym ;
		newnode->num = temp_is->num ;
		head_ops = push(newnode,head_ops) ;
		temp_is = temp_is->down ;
    }
	else if(temp_is->flag == 1 && temp_is->sym == '^'){                                                                           // Same idea as the above if else statement.
		ip* newnode = NULL ;
		newnode = (struct symbol*)malloc(sizeof(struct symbol)) ;
		newnode->flag = temp_is->flag ;
		newnode->sym = temp_is->sym ;
		newnode->num = temp_is->num ;
		head_ops = push(newnode,head_ops) ;
		temp_is = temp_is->down ;
    }
	else if(temp_is->flag == 2 && (temp_is->sym == '[' || temp_is->sym == '{' || temp_is->sym == '(')){                           // If an opening bracket is encountered it is simply pushed to the 
		ip* newnode = NULL ;                                                                                                      // head_ops stack.
		newnode = (struct symbol*)malloc(sizeof(struct symbol)) ;                                                                 
		newnode->flag = temp_is->flag ;                                                                                           
		newnode->sym = temp_is->sym ;
		newnode->num = temp_is->num ;
		head_ops = push(newnode,head_ops) ;
		temp_is = temp_is->down ;
    }
	else if(temp_is->flag == 2 && (temp_is->sym == ']' || temp_is->sym == '}' || temp_is->sym == ')')){                           //If a closing bracket is encountered the head_ops stack is popped        
		while(head_ops!=NULL){                                                                                                    //until the opposite opening bracket is encountered and all the nodes 
		if(head_ops->sym != '[' && head_ops->sym != '{' && head_ops->sym != '('){                                                 //in between are transferred (pushed) to head_pfs by the newnode method
			ip* newnode = NULL ;                                                                                                  // as described above.The opening bracket is also popped from the 
			newnode = (struct symbol*)malloc(sizeof(struct symbol)) ;                                                             // head_ops stack but is not pushed to the head_pfs stack.
			newnode->flag = head_ops->flag ;
			newnode->num = head_ops->num ;
			newnode->sym = head_ops->sym ;
			head_pfs = push(newnode,head_pfs) ;
			head_ops = pop(head_ops) ;
		}
		else{
			break ;}
	}
	    temp_is = temp_is->down ;
		head_ops = pop(head_ops) ;
	}
}

while(head_ops!=NULL){                                                                                                             //After all the operations if the head_ops stack is not NULL,
	ip* newnode = NULL ;                                                                                                           // all its contents are popped and pushed to the head_pfs stack 
	newnode = (struct symbol*)malloc(sizeof(struct symbol)) ;                                                                      // until it is NULL.
	newnode->flag = head_ops->flag ;
	newnode->num = head_ops->num ;
	newnode->sym = head_ops->sym ;
	head_pfs = push(newnode,head_pfs) ;
	head_ops = pop(head_ops);
}                                                                                                                                   //The head pfs stack now contains the postfix expression
ip* postfix_stack = NULL ;                                                                                                          //in reverse order.The invert_stack function inverts inverts the 
postfix_stack = (struct symbol*)malloc(sizeof(struct symbol)) ;                                                                     //head_pfs stack and stores it in the postfix_stack.
postfix_stack = invert_stack(head_pfs) ;
printf("\nPostfix expression is: ") ;
print(postfix_stack) ;                                                                                                              //Postfix stack is now printed and evaluated using evaluation
printf("\nResult of evaluation is: ") ;
evaluation(postfix_stack) ;                                                                                                         //function.
}

void evaluation(ip* head){
	
	ip* temp = NULL ;                                                   // This temp variable is assigned to the head of the postfix stack                                            
	temp = (struct symbol*)malloc(sizeof(struct symbol)) ;
	temp = head ;                                                      
	ip* op_stack = NULL ;                                               //op_stack stands for operation stack .This stack would store the result of each calculation
	float op1 = 0 ;                                                     //At the end the stack would be having the final result
	float op2 = 0 ;                                                     //op1 and op2 store the operands in the head and the operand in the node below the head of the op_stack
	
	while(temp!=NULL){
		if(temp->flag == 0){                                            //If an operand is encountered in the postfix stack ,It is pushed to the op_stack.
			op1 = op2 ;                                                 // op2 stores the value of the operand and op1 stores the previous value of op2
			op2 = temp->num ;
			ip* newnode = NULL ;
			newnode = (struct symbol*)malloc(sizeof(struct symbol)) ;
			newnode->flag = temp->flag ;
			newnode->num = temp->num ;
			newnode->sym = temp->sym ;
			op_stack = push(newnode,op_stack) ;
			temp = temp->down ;}
		else if(temp->flag == 1){                                       // If an operator is detected in the postfix, stack the first nodes of the op_stack are popped as they contain the operand
			                                                            // on which the operator would work upon.By detecting the operator by if ,else if statements the opeartion is carried out 
			float result ;                                              // on op2 and op1 as they contained the first two values of the op_stack that were popped out. The result 
			if(temp->sym == '+'){                                       // is then stored in a new node and the new node is pushed to the op_stack.
				result = op1+op2 ;}                                     // The procedure is repeated until the postfix stack is exhausted.At the end, the final result is present in the op_stack 
			else if(temp->sym == '-'){                                  // which is printed.
				result = op1-op2 ;}
			else if(temp->sym == '*'){
				result = op1*op2 ;}
			else if(temp->sym == '/'){
				result = op1/op2 ;}
			else if(temp->sym == '^'){
				result = power(op1,op2) ;}
				
			ip* newnode = NULL ;
			newnode = (struct symbol*)malloc(sizeof(struct symbol)) ;
			newnode->flag = 0 ;
			newnode->num = result ;
			newnode->sym = '#' ;
			op_stack = pop(op_stack) ;
			op_stack = pop(op_stack) ;
			op_stack = push(newnode,op_stack) ;
			ip* t = NULL ;
			t = (struct symbol*)malloc(sizeof(struct symbol)) ;
			t = op_stack ;
			op2 = t->num ;
			if(t->down!=NULL){	
			    t = t->down ;
			    op1 = t->num ;}
			else{
				op1 = 0 ;}
			temp = temp->down ;	}
	}
	print(op_stack) ;
}

int main(){
	
	char str[MAX_LIMIT] ;                                               // String is initialised for taking inputs.
	int f = 1 ;
	while(f!=0){
	printf("This programme converts infix expression to postfix expression and evaluates its value.") ;                     
	printf("\nEnter the infix expression (only positive decimal numbers are allowed) without any space in between.\n") ;
    scanf("%s",str) ;                                                   // Input is taken
	ip* value = NULL ;
	value = infix_constructor(str) ;                                    // String is passed to the infix constructor function 
	if(value!=NULL){
	postfix_exp(value) ;}                                               // Value stack is then passed to postfix_exp  function for postfix conversion and evaluation.
	
	printf("\n\nDo you want to continue ??.Enter 1 if yes and 0 if no\n") ;
	scanf(" %d", &f) ;
    }
}

