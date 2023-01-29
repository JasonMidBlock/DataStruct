// 11027240 許展榮  11027241 楊昀祖 
#include <iostream> 
#include <stack>
#include <stdlib.h>
#include <vector>
#include <string>
using namespace std;

class Stack{
	private:
		vector<string> s;
		vector<char> ch;
		vector<int> i;
	public:
		string s_top(){
			return s[s.size() -1];
		}
		void s_push(string str){
			s.push_back(str);
		}
		void s_pop(){
			s.pop_back();
		}
		bool s_empty(){
			if(s.empty())
				return true;
			return false;
		}
		
		char c_top(){
			return ch[ch.size() -1];
		}
		void c_push(char c){
			ch.push_back(c);
		}
		void c_pop(){
			ch.pop_back();
		}
		bool c_empty(){
			if(ch.empty())
				return true;
			return false;
		}
		
		
		
		int i_top(){
			return i[i.size() -1];
		}
		void i_push(int n){
			i.push_back(n);
		}
		void i_pop(){
			i.pop_back();
		}
		bool i_empty(){
			if(i.empty())
				return true;
			return false;
		}
};

struct Node{
	string str;
	Node* next;
	
};

void genIO();
bool step1(string str);
void step2(string str);
void step3(Node *head);

void Node_push(string s, Node* &head);
string Node_top(Node* head );
void Node_pop(Node* &head);
void Node_Show(Node* head);
bool Node_empty(Node* head);

bool Input_Operation_Is_Ok(string s);
bool Input_Num_Is_Ok(string s);




int main(){
	
	int command;
	string s, str;
	bool end = false;
	do{
		genIO();
		cout << "Input a choice(0, 1):";
		getline(cin ,s); // 整行讀入到 s
		while(!Input_Operation_Is_Ok(s)){
			cout << "input a choice:";
			getline(cin ,s); // 整行讀入到 s
		}
		
		command = atoi(s.c_str());
		switch(command){
			case 0:
				end = true;
				break;
			case 1:
				cout << "Input an infix expression:"; 
				getline(cin, str);
				step2(str); // step1 in step2
				break;
			default: 
				cout << "Error Operation\n\n";
				break;
		}
	}while(!end);
	
}

bool Input_Operation_Is_Ok(string s){
	// judge operation input is legal
	if(Input_Num_Is_Ok(s)){
		if( s == "0" || s == "1" )
			return 1;
	}
	return false;
}

bool Input_Num_Is_Ok(string s){
	// judge if input is a number
	for(int i=0; i< s.length(); i++){
		if( !isdigit(s[i]) )
			return false;
	}
    return true;
}
bool char_is_brackets(char c){
	if(c == '(' || c == ')')
		return true;
	return false;
}

bool char_is_operation(char c ){
	if(c == '+' || c == '-' || c == '*' || c == '/')
		return true;
	return false;
}

bool char_is_legal(char c){
	if(char_is_brackets(c) || char_is_operation(c) || c == ' '|| c == '\t')
		return true;
	if( isdigit(c) )
		return true;
		
	return false;
}

void Node_push(Node * &head, string s){
	Node* temp = head ;
	Node* tail = new Node;
	tail -> str = s ;
	tail -> next = NULL;
	if(head == NULL){
		head = tail;
	}
	else {
		while(temp -> next != NULL){
			temp = temp -> next;
		}
		temp -> next = tail;
	}
}

string Node_top(Node* head){
	while(head -> next != NULL)
		head = head -> next;
	return head -> str;
}

void Node_Show(Node* head){
	Node* temp= head;
	while(temp != NULL){
		cout << temp -> str;
		if(temp -> next != NULL)
			cout << ", ";
		temp = temp -> next;
	}
}
void Node_pop(Node* &head){
	int i = 0;
	Node* temp = head;
	if ( head == NULL ){
		head = NULL;
	}
	else if( head -> next == NULL ) {
		head = NULL;
	}
	else {
		while(temp -> next -> next != NULL){
			temp = temp -> next;
		}
		temp -> next = NULL;
	}
}

bool Node_empty(Node* head){
	if(head == NULL)
		return true;
	return false;
}

void genIO(){
	cout << "* Arithmetic Expression Evaluator *\n";
	cout << "* 0. QUIT                         *\n";
	cout << "* 1. Infix2postfix Evaluation     *\n";
	cout << "***********************************\n\n";
}


bool step1(string str){
	char last= '\0';
	// str.length() 不包括 '\n'
	bool space_after_digit = false;
	string s;
	Stack sta;
	//stack<char> brackets;
	
	if(char_is_operation(str[0])){
		cout << "Error 3: there is one extra operator.\n\n";
		return false;
	}
	
	for(int i =0;i< str.length(); i++){
		if(str[i] != ' '&& str[i] != '\t'){
			if( !char_is_legal(str[i]) ){
				cout << "Error 1: "<< str[i] << "is not a legitimate character.\n\n";
				return false;
			}
			else if(char_is_brackets(str[i])){
				if(str[i] == '('){
					if(isdigit(last)){
						cout << "Error 3: there is one extra operand.\n\n";
						return false;
					}
					sta.c_push(str[i]);  // brackets.push(str[i]);
					
				}
				else{
					if(last == '('){
						cout << "Error 3: it is not infix in the parentheses.\n\n";
						return false;
					}
					
					if( !sta.c_empty() ) {  // !brackets.empty()
						sta.c_pop(); // brackets.pop();
					}
					else{
						cout << "Error 2: there is one extra close paenthesis.\n\n";
						return false;
					}
					
				}
				last = str[i];
			}
			else {  // c is legal
				if(char_is_operation(str[i]) && last == '('){
					cout << "Error 3: it is not infix in the parentheses.\n\n";
					return false;
				}
				if(char_is_operation(last) && char_is_operation(str[i])){
					cout << "Error 3: there is one extra operator.\n\n";
					return false;;
				}
				if( last == ')' && isdigit(str[i])){
					cout << "Error 3: there is one extra operand.\n\n";
					return false;
				}
				
				last = str[i];
			}
		}
	}
	
	if(!sta.c_empty()) {   // !brackets.empty()
		cout << "Error 2: there is one extra open parenthesis.\n\n";
		return false;
	}
		
	cout << "It is a legitimate infix express.\n\n";
	
	return true;
}

void step2(string str){
	string temp;
	vector<string> s;
	Stack sta;
	if(!step1(str))
		return ;
	Node* Postfix = NULL;
	
	for(int i =0 ;i< str.length(); i++){
		if(str[i] == ' ')
		;
		else if(isdigit(str[i])){
			temp += str[i];
		}
		else if(char_is_operation(str[i]) || char_is_brackets(str[i]) ){
			if(temp != ""){
				s.push_back(temp);
				temp = "";
			}
			temp.push_back(str[i]);
			s.push_back(temp);
			temp = "";
		}
		// if the last char is digit push back last string
		if(i == str.length() -1 && temp != ""){
			s.push_back(temp);
			temp = "";
		}
	}
	
	

	temp = "";
	
	
	for(int i =0 ;i< s.size(); i++) {
		if(char_is_operation(s[i][0]) || char_is_brackets(s[i][0])){
			if(sta.s_empty())
				sta.s_push(s[i]);
			else if(s[i] == "+" || s[i] == "-" ){
				if(sta.s_top() == "(")
					sta.s_push(s[i]);
				else{
					while( !sta.s_empty() && sta.s_top() != "(" ){
						Node_push(Postfix, sta.s_top());
						sta.s_pop();
					}
					
					sta.s_push(s[i]);
				}
			}
			else if(s[i] == "*" || s[i] == "/"){
				if(sta.s_top() == "(" || sta.s_top() == "+" || sta.s_top()  == "-" )
					sta.s_push(s[i]);
				else{
					
					while(!sta.s_empty() && (sta.s_top() == "*" || sta.s_top() == "/") ){
						
						Node_push(Postfix, sta.s_top());
						sta.s_pop();
					}
					
					sta.s_push(s[i]);
				}
			}
			else if(s[i] == "("){
				sta.s_push(s[i]);
			}
			else{ // s[i] == )
				while(sta.s_top() != "("){
					Node_push(Postfix, sta.s_top());
					sta.s_pop();
					
				}
				// pop (
				sta.s_pop();
			}
		}
		else{ // if s[i] is number
			Node_push(Postfix, s[i]);
		}
	}
	

	while(!sta.s_empty()){
		Node_push(Postfix, sta.s_top());
		sta.s_pop();
	}
	
	
	Node_Show(Postfix);
	cout << "\n";
	step3(Postfix);
	return;
}

void step3(Node * head){
	// stack<int> nums;
	Stack sta;
	int num1, num2;
	while(head != NULL){
		if( head-> str == "+"){
			num1 = sta.i_top();     // nums.top();
			sta.i_pop();   // nums.pop();
			num2 = sta.i_top();     // nums.top();
			sta.i_pop();   // nums.pop();
			num1 += num2;
			sta.i_push(num1); // nums.push(num1);
		}
		else if(head-> str == "-"){
			num1 = sta.i_top();// nums.top();
			sta.i_pop(); // nums.pop();
			num2 = sta.i_top(); // nums.top();
			sta.i_pop(); // nums.pop();
			num1 = num2 - num1;
			sta.i_push(num1); // nums.push(num1);
		}
		else if(head-> str == "*"){
			num1 = sta.i_top(); // nums.top();
			sta.i_pop(); // nums.pop();
			num2 = sta.i_top(); // nums.top();
			sta.i_pop(); // nums.pop();
			num1 = num1 * num2;
			sta.i_push(num1); // nums.push(num1);
		}
		else if(head-> str == "/"){
			num1 = sta.i_top(); // nums.top();
			sta.i_pop(); // nums.pop();
			num2 = sta.i_top(); // nums.top();
			if(num1 == 0){
				cout << "### Error: Divided by ZERO! ###\n";
				cout << "### It cannot be successfully evaluated! ###\n";
				return;
			}
			sta.i_pop(); // nums.pop();
			num1 = num2 / num1;
			sta.i_push(num1); // nums.push(num1);
		}
		else
			sta.i_push(atoi(head->str.c_str())); // nums.push(atoi(head->str.c_str()));
		
		head = head -> next;
	}
	
	cout << "Answer = " << sta.i_top() << "\n\n";  // nums.top()
	
	sta.i_pop(); // nums.pop();
	if(!sta.i_empty()) // nums.empty()
		cout << "it must have something wrong\n";
	
}
