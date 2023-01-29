# include <iostream>
# include <stdlib.h>
# include <string.h>

using namespace std;

void startGen();
bool charOK( char data );
bool expressionOK( char data[100] );
void changetoStack( char data[100] );
void mission1();
void mission2();
void mission3();

int getISP( char a ) {
	if ( a == '+' || a  == '-' )
		return 1;
	if ( a == '*' || a == '/' )
		return 2;
	if ( a == '(' )
		return 0;
		        
	return -1;
} // getISP
		
int getICP( char a ) {
	if ( a == '+' || a == '-' )
		return 1;
	if ( a == '*' || a == '/' )
	    return 2;
	if ( a == '(' )
	    return 4;
		        
	return -1;
} // getICP

const int NUMBER = 982137;
const int OPERATOR = 287493;
const int NOT_CORRECT = 102938;

struct item{
    int type;
	int num;
	char oper;
	item *next;
};

class Stack{
	public:
		
		Stack() {
			firstitem = NULL;
		} // Stack
		
	 	bool isEmpty() {
	 		if ( firstitem == NULL )
	 		    return true;
	 		else
	 		    return false;
		} // isEmpty()
		
		int getnumber() {
			return firstitem -> num;
		}
		
		char getoper() { // get operator
			    return firstitem -> oper;
		} // get()
		
		void push( int number ) { // insert a number
			item *temp;
			temp = firstitem;
			firstitem = new item;
			firstitem -> type = NUMBER;
			firstitem -> num = number;
			firstitem -> next = temp;
		} // push( int number )
		
		void push( char oper ) { // insert an operator
			item *temp;
			temp = firstitem;
			firstitem = new item;
			firstitem -> type = OPERATOR;
			firstitem -> oper = oper;
			firstitem -> next = temp;
		} // push( char oper )
		
		void pop() { // delete data 
		
			if ( isEmpty() ) {
			    cout << "can't pop while the stack is empty!" << endl;
			    return;
			} // if()
		    
		    item *temp = firstitem -> next;
		    delete firstitem; // release memory when deleting things
		    firstitem = temp;
			
			return;
			
		} // pop()
		
		int popnum() {
					
			if ( isEmpty() ) {
			    cout << "can't pop while the stack is empty!" << endl;
			    return -1;
			} // if()
		    
		    int out = firstitem -> num;
		    
		    item *temp = firstitem -> next;
		    delete firstitem; // release memory when deleting things
		    firstitem = temp;
			
			return out;
			
		} // popnum()
		
	private:
	    item *firstitem;
	
};

int main(int argc, char** argv) {
    
    cout << "._.-._. You can do mission1 by type a and mission2 by type b ._.-._." << endl;
    cout << endl;
    char command[100] = "\0";
	while ( command[0] != '0' ) {
		
		startGen(); // generate the starting article for users to check
		
		cin.getline( command, 100 ); // read in user command
		cout << endl;
		
		// do different things based on user command
		if ( command[0] == 'a' ) { 
			mission1(); 
		} // if()
		else if ( command[0] == 'b' ) {
			mission2();
		} // else if()
		else if ( command[0] == '1' ) {
			mission3();
		} // else if()
		else if ( command[0] != '0' ){
			cout << "Command does not exist!" << endl; // 防呆 
		}
		
	} // while()
	
	cout << "quitting !" << endl;
	
	return 0;
    
    
} // main  

bool charOK( char data ) {
	if ( data == ' ' || data == '+' || data == '-' || data == '*' || data == '/' || data == '(' || data == ')' )
	    return true;
	else if ( data >= '0' && data <= '9' ) 
	    return true;
	else
	    return false;
} // charOK

bool expressionOK( char data[100] ) {  // 0不是正整數 
	int brackets = 0;
	bool prev_is_oper = true; // ignore '(' , ')';
	bool has_back_brac = false;
	bool prev_is_zero = false;
	char now = 'a';
	int size = 0;
		
	for ( int i = 0 ; data[i] != '\0' ; i ++ )
	    size ++;
	
	for ( int i = 0 ; i < size ; i ++ ) {
		now = data[i];
		
		if ( ! charOK(now) ) {
		    cout << "Error 1: " << now << "is not a legitimate character." << endl;
		    return false; // error1
	    } // if()
	    else if ( now == '0' )
	        prev_is_zero = true;
		else if ( now >= '0' && now <= '9' ) {
			
			prev_is_zero = false; 
			prev_is_oper = false;
			if ( has_back_brac == true ) { // ')' 後面要接 ')' 或運算子 
			    cout << "Error 3 : there is one extra operand." << endl;
			    return false; // error3
		    } // if
		    
		} // else if()
		else if ( now == '(' ) {
			
			brackets += 1;
			
			if ( i != 0 && ! prev_is_oper ) {
			    cout << "Error3 : there is one extra operand." << endl;
			    return false; // error3
			} // if()
			    
	    } // else if()	
		else if ( now == ')' ) {
			
			if ( prev_is_zero && prev_is_oper ) {
			    cout << "Error 1 : 0 is not a positive integer." << endl;
			    return false; // error1
			} // if()
			
		    brackets -= 1;
		    has_back_brac = true;
		    
	    } // else if()
		else if ( brackets < 0 ) {
		    cout << "Error 2 : there is one extra close parenthesis." << endl;
		    return false; // error2 
		} // else if()
		else if ( now == '+' || now == '-' || now == '*' || now == '/' ) {
			
			if ( prev_is_zero && prev_is_oper ) {
			    cout << "Error 1 : 0 is not a positive integer." << endl;
			    return false; // error1
			} // if()
			
			if ( prev_is_oper || i == size - 1 ) {
			    cout << "Error 3 : there is one extra operator." << endl;
			    return false; // error3
			} // if()
			
			prev_is_oper = true;
			has_back_brac = false;
			
		} // else if()
		
	} // for
	
	if ( now == '0' && prev_is_oper ) {
	    cout << "Error 1 : 0 is not a positive integer." << endl;
	    return false; // error1
    } // if()
    
	if ( brackets != 0 ) {
	    cout << "Error 2 : there is one extra open parenthesis." << endl;
		return false; // error2
    } // if()
    
    cout << "It is a legitimate infix expression." << endl;
	return true;
	
} // expressionOK

void mission1() {
	char data[100];
	cout << "Input an infix expression: ";
	cin.getline( data, 100 );

    expressionOK(data);
	
} // mission1

item *changetoitem( char data[100] ) { // change the char array to a linked list of item
	int i = 0, anumber = 0;
	item *anitem = new item{0,0,'0',NULL};
	item *head = anitem;
	
	while ( data[i] != '\0' ) {
		anitem -> next = new item;
		if( data[i] >= '0' && data[i] <= '9' ) { // the next item is an number
			
			do{
			    anumber = anumber * 10 + ( data[i] - '0' );
			    i ++;
		    } while( data[i] >= '0' && data[i] <= '9' );
		    
		    anitem -> next -> type = NUMBER;
		    anitem -> next -> num = anumber;
		    anitem -> next -> next = NULL;
		    
		} // if()
		else{ // data[i] is an operator or brace
		    anumber = 0;
		    anitem -> next -> type = OPERATOR;
		    anitem -> next -> oper = data[i];
		    anitem -> next -> next = NULL;
		    i ++;	
		} // else
		
		anitem = anitem -> next;
	} // while()
	
	item* out = head -> next;
	delete head;
	return out;
	
} // changetoitem()

item *changetoRPN( char data[100] ) {
	
	Stack oper_Stack;
	item *newdata = NULL;
	item *temp = NULL;
	item *anitem = new item{0,0,'0',NULL};
	item *head = anitem;
	
    newdata = changetoitem( data );
	
    while ( newdata != NULL ) {
    	if ( newdata -> type == NUMBER ) { // case number : write into the list
    		anitem -> next = new item{ newdata -> type, newdata -> num, newdata -> oper, NULL };
    		anitem = anitem -> next;
		} // if()
		else if( newdata -> oper == ')' ) { // case close brace : write things in stack into the list utill open brace
			do {
				anitem -> next = new item{ OPERATOR, 0, oper_Stack.getoper(), NULL };
				anitem = anitem -> next;
				oper_Stack.pop();
			} while ( oper_Stack.getoper() != '(' );
			
			oper_Stack.pop(); // pop the '('
			
		}  // else if()
		else { // case operator : compare the ICP and ISP
			if ( oper_Stack.isEmpty() || ( getICP(newdata -> oper) > getISP(oper_Stack.getoper()) ) ) { 
			// stack is empty or ICP > ISP : push operator into stack
				oper_Stack.push( newdata -> oper );
			} // if()
			else { // ICP <= ISP : write things in stack into the list till ICP > ISP or the stack is empty
			       //              than push into stack
			    do {
			  	    anitem -> next = new item{ OPERATOR, 0, oper_Stack.getoper(), NULL };
			  	    anitem = anitem -> next;
			  	    oper_Stack.pop();
			    } while( ! oper_Stack.isEmpty() && ( getICP(anitem -> oper) <= getISP(oper_Stack.getoper()) ) );
				
				oper_Stack.push( newdata -> oper );
				
			} // else
			
		} // else
    	
    // end one insert : realease memory of data won't use 
    	temp = newdata;
    	newdata = newdata -> next;
    	delete temp;
	} // while
	
	while ( ! oper_Stack.isEmpty() ) { 
		anitem -> next = new item{ OPERATOR, 0, oper_Stack.getoper(), NULL };
		anitem = anitem -> next;
		oper_Stack.pop();
	} // while()
	
	temp = head;
	head = head -> next;
	delete temp;
	return head;
	
} // changetoStack

void printRPN( item *RPN ) {
	
	cout << "Postfix expression:";
	while ( RPN != NULL ) {
		if ( RPN -> type == NUMBER )
		    cout << " " << RPN -> num;
		else
		    cout << " " << RPN -> oper;
		    
		if ( RPN -> next != NULL ) 
		    cout << ",";
		    
		RPN = RPN -> next;
	} // while()
	
	cout << endl;
	
}

void mission2() {
	char data[100];
	cout << "Input an infix expression:";
	cin.getline( data, 100 );
	
	item *RPN = NULL;
	
	if ( expressionOK(data) ) 
		RPN = changetoRPN(data);

    printRPN( RPN );

	return;
} // mission2

int calculateRPN( item *RPN ) {
	
	Stack NUM_Stack;
	int num1, num2;
	
	while ( RPN != NULL ) {
	
	    if ( RPN -> type == NUMBER ) {
		    NUM_Stack.push( RPN -> num );
	    } // if()
	    else{ // RPN -> type == OPERATOR
	        num1 = NUM_Stack.popnum();
	        num2 = NUM_Stack.popnum();
	        if ( RPN -> oper == '+' ) {
	        	NUM_Stack.push( num2 + num1 );
			} // if()
	        else if ( RPN -> oper == '-' ) {
	        	NUM_Stack.push( num2 - num1 );
			} // else if
			else if ( RPN -> oper == '*' ) {
				NUM_Stack.push( num2 * num1 );
			} // else if
			else { // RPN -> oper == '/' specialcase when divide zero
			    if ( num1 == 0 ) {
			    	cout << "### Error: Divided by ZERO! ###" << endl;
                    cout << "### It cannot be successfully evaluated! ###" << endl;
			    	return NOT_CORRECT;
				} // if()
				
			    NUM_Stack.push( num2 / num1 );
			} // else
			
	    } // else
	
	    RPN = RPN -> next;
    } // while()
	
	return NUM_Stack.popnum();
	
} // calculateRPN 

void mission3() {
	char data[100];
	cout << "Input an infix expression:";
	cin.getline( data, 100 );
	
	item *RPN = NULL;
	
	if ( expressionOK(data) ) { //check expression
		RPN = changetoRPN( data ); // change the char array to RPN
		printRPN( RPN ); // print it!
		int answer = calculateRPN(RPN); // calculate the answer
		if ( answer != NOT_CORRECT ) 
		    cout << "Answer : " << answer << endl;
	} // if()

    cout << endl;
	return;
} // mission3

void startGen() {
	cout << "* Arithmetic Expression Evaluator *" << endl;
    cout << "* 0. QUIT                         *" << endl;
    cout << "* 1. Infix2postfix Evaluation     *" << endl;
    cout << "***********************************" << endl;
} // startGen
