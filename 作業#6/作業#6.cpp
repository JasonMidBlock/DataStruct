#include <iostream> 
#include <vector>
#include <string.h> 
#include <stdlib.h>
#include <fstream>
#include <algorithm>

using namespace std;

struct Pok{
	string Num;
	string Name;
	string Type1;
	string Type2;
	int Total;
	int HP;
	int Attack;
	int Defence;
	int SPattack;
	int SPdefence;
	int Speed;
	string Generation;
	string Lengendary;
};

struct Node{
	vector<Pok> pok;
	Node* left;
	Node* right;
};
void startGen(){
	cout << "*** Binary Search Tree on Pokemon ***\n";
	cout << "* 0. QUIT                           *\n";
	cout << "* 1. Read one file to build BST     *\n";
	cout << "* 2. Threshold search on one column *\n";
	cout << "* 3. Delete the max on one column   *\n";
	cout << "*************************************\n";
}


int string_to_int(string s){
	string str;
	for(int i = 0 ; i < s.length(); i++){
		if( isdigit(s[i]) )
			str += s[i];
	}
	
	return atoi(str.c_str());
}

vector<Pok> input_to_vec(ifstream &reader ){
	vector<Pok> datas;
	int i = 1 ;
	string s;
	getline(reader, s);
	Pok temp;
	while( !reader.eof() ){
		getline( reader, temp.Num, '\t' );
		if(reader.peek() == '\t' )
			reader.get();
		else
			getline( reader, temp.Name, '\t' );
		
		if(reader.peek() == '\t')
			reader.get();
		else
			getline( reader, temp.Type1, '\t' );
		
		if(reader.peek() == '\t')
			reader.get();
		else
			getline( reader, temp.Type2, '\t' );
			
		if(reader.peek() == '\t')
			reader.get();
		else{
			getline( reader, s, '\t' );
			temp.Total = string_to_int(s);
		}
			
		
		if(reader.peek() == '\t' )
			reader.get();
		else{
			getline( reader, s, '\t' );
			temp.HP = string_to_int(s);
		}
		
		
		if(reader.peek() == '\t' )
			reader.get();
		else{
			getline( reader, s, '\t' );
			temp.Attack = string_to_int(s);
		}
		
		
		if(reader.peek() == '\t')
			reader.get();
		else{
			getline( reader, s, '\t' );
			temp.Defence = string_to_int(s);
		}
		
		if(reader.peek() == '\t')
			reader.get();
		else{
			getline( reader, s, '\t' );
			temp.SPattack = string_to_int(s);
		}
		
		if(reader.peek() == '\t')
			reader.get();
		else{
			getline( reader, s, '\t' );
			temp.SPdefence = string_to_int(s);
		}
		
		if(reader.peek() == '\t' )
			reader.get();
		else{
			getline( reader, s, '\t' );
			temp.Speed = string_to_int(s);
		}
		
		if(reader.peek() == '\t')
			reader.get();
		else
			getline( reader, temp.Generation, '\t' );
		
		
		if(reader.peek() == '\n' )
			;
		else
			reader >> temp.Lengendary;
		
		
		reader.get() ; // get '\n'
		
		if(reader.eof())
			break;
		datas.push_back(temp);
	}
	
	return datas;
}

void AddNode(Node* &head, Pok pok){
	if(head == NULL)
		return ;
	
	if( head->pok[0].HP > pok.HP ){ 
		if(head->left == NULL) {
			head->left = new Node;
			head->left->right = NULL;
			head->left->left = NULL;
			head->left->pok.push_back(pok);
			return;
		}
		
		AddNode(head->left, pok);
	} 
	else if(head->pok[0].HP < pok.HP ){ 
		if(head->right == NULL) {
			head->right = new Node;
			head->right->right = NULL;
			head->right->left = NULL;
			head->right->pok.push_back(pok);
			return;
		}
		
		AddNode(head->right, pok);	
	} 
	else{
		head->pok.push_back(pok) ;
		return;
	}
}

void find_level(Node* head, int level, int &max){
	if(head == NULL)
		return ;
	if(level > max)
		max = level;
	find_level(head->left, level +1 , max );
	find_level(head->right, level +1, max );
}


void printdata( Node* data ){
	cout << data->pok[0].Num << "\t";
	cout << data->pok[0].Name << "\t";
	cout << data->pok[0].Type1 << "\t";
	cout << data->pok[0].Type2 << "\t";
	cout << data->pok[0].Total << "\t";
	cout << data->pok[0].HP << "\t";
	cout << data->pok[0].Attack << "\t";
	cout << data->pok[0].Defence << "\t";
	cout << data->pok[0].SPattack << "\t";
	cout << data->pok[0].SPdefence << "\t";
	cout << data->pok[0].Speed << "\t";
	cout << data->pok[0].Generation << "\t";
	cout << data->pok[0].Lengendary << "\n";
}

void findbiger(Node* head, int basic, int &counter, int &node){
	if(head == NULL)
		return ;
	node++;
	if( head->pok[0].HP <= basic )
		findbiger( head->right, basic, counter, node);
	else{
		findbiger( head->right, basic, counter, node);
		findbiger( head->left, basic, counter, node );
	}
	
	if( head->pok[0].HP >= basic ){
		counter++;
		cout <<"[" << counter << "]";
		printdata(head);
	}
}

void DelANode(Node* &head, int basic , int &Nodecounter, Node* &temp){
	if(head == NULL)
		return;
	if( head->right == NULL ) {	// is biggest
		if ( head->pok.size() == 1 ){
			printdata(head);
			temp = head->left;
			delete head;
			head = NULL;
		}
		else{
			printdata(head);
			head->pok.erase(head->pok.begin());
			temp = head;
		}
	}
	else{
		DelANode(head->right, basic, Nodecounter, temp);
		head->right = temp;
		temp = head;
	}
}
	

void DelNode(Node* &head, int basic , int &Nodecounter, Node* &temp){
	if( head == NULL )
		return;
	Nodecounter++;
	if( head->pok[0].HP >= basic ){
		DelNode(head->right, basic, Nodecounter, temp);
		DelNode(head->left, basic, Nodecounter, temp);
		delete head;
		head = NULL;
	}
	else{
		DelNode(head->right, basic, Nodecounter, temp);
		if( head->right == NULL )
			head->right = temp;
		temp = head;
	}
}

Node* mission1(){
	string filename;
	ifstream reader;
	
	cout << "Input 601, 602, ...( type 0 to Quit ) : " << endl; 
    cin >> filename; // ask for file name
    if ( filename == "0" ) { // user can quit this mission by typing 0
        return NULL;
	} // if()
    
    filename = "input" + filename + ".txt";
    reader.open( filename.c_str() ); // open file
    
    while ( ! reader.is_open() ) { // checking if the file is open 
    	   		                       // if don't ask user to try again
    	cout << "### " + filename + " does not exist! ###";
    	cout << "Input 601, 602, ...( type 0 to Quit ) : " << endl;
    	cin >> filename;
    	if ( filename == "0" ){
    		return NULL;
    	} // if()
        
    	filename = "input" + filename + ".txt";
       	reader.open( filename.c_str() );
        
	} // while()
    // input file open success
    
    vector<Pok> datas = input_to_vec(reader);
    
    Node* head = NULL;
    bool add = false;
    for(int i = 0 ; i < datas.size(); i++){
    	if(i == 0 ){
    		head = new Node;
    		head->left = NULL;
    		head->right = NULL;
    		head->pok.push_back(datas[i]);
		}
		else
			AddNode(head, datas[i]);
	}
	
	
	cout << "\t\t#\t\tName\t\tType1\t\tHP\t\tAttack\t\tDefence\n";
	for(int i = 0 ; i < datas.size();i++){
		cout << "[" << i +1  << "]\t\t";
		cout << datas[i].Num << "\t\t";
		cout << datas[i].Name << "\t\t";
		cout << datas[i].Type1 << "\t\t";
		cout << datas[i].HP << "\t\t";
		cout << datas[i].Attack << "\t\t";
		cout << datas[i].Defence << "\n";
	}
	
	int max=0;
	find_level(head, 1, max);
	cout << "HP tree height = " << max << "\n";
	return head;
}


void mission2(Node* head){
	if( head == NULL ){
		cout << "must operating mission1 first\n";
		return;
	}
	/*
	string filename;
	ifstream reader;
	
	cout << "Input 601, 602, ...( type 0 to Quit ) : " << endl; 
    cin >> filename; // ask for file name
    if ( filename == "0" ) { // user can quit this mission by typing 0
        return;
	} // if()
    
    filename = "input" + filename + ".txt";
    reader.open( filename.c_str() ); // open file
    
    while ( ! reader.is_open() ) { // checking if the file is open 
    	   		                       // if don't ask user to try again
    	cout << "### " + filename + " does not exist! ###";
    	cout << "Input 601, 602, ...( type 0 to Quit ) : " << endl;
    	cin >> filename;
    	if ( filename == "0" ){
    		return;
    	} // if()
        
    	filename = "input" + filename + ".txt";
       	reader.open( filename.c_str() );
        
	} // while()
    // input file open success
    
    vector<Pok> datas = input_to_vec(reader);
	
	Node* head = NULL;
    for(int i = 0 ; i < datas.size(); i++){
    	if(i == 0 ){
    		head = new Node;
    		head->left = NULL;
    		head->right = NULL;
    		head->pok.push_back(datas[i]);
		}
		else
			AddNode(head, datas[i]);
	} // build tree
	*/
	int basic = 0, counter = 0, node = 0 ;
	cout << "Threshold ( a postive num ) :";
	cin >> basic;
	cout << "#\tName\tType 1\tType 2\tTotal\tHP\tAttack\tDefense\tSp. Atk\tSp. Def\tSpeed\tGeneration\tLegendary\n";
	findbiger(head, basic, counter, node);
	cout << "Number of visited nodes :" << node << "\n";
	
}

Node* mission3(Node* head){
	if( head == NULL ){
		cout << "must operting mission1 first\n";
		return NULL;
	}
	
	/*
	if( head == NULL ){
		string filename;
		ifstream reader;
	
		cout << "Input 601, 602, ...( type 0 to Quit ) : " << endl; 
	    cin >> filename; // ask for file name
    	if ( filename == "0" ) { // user can quit this mission by typing 0
	        	return NULL;
		} // if()
    
    	filename = "input" + filename + ".txt";
    	reader.open( filename.c_str() ); // open file
    
    	while ( ! reader.is_open() ) { // checking if the file is open 
    	   		                       // if don't ask user to try again
    		cout << "### " + filename + " does not exist! ###";
   		 	cout << "Input 601, 602, ...( type 0 to Quit ) : " << endl;
    		cin >> filename;
    		if ( filename == "0" ){
    			return NULL;
    		} // if()
        
    		filename = "input" + filename + ".txt";
       		reader.open( filename.c_str() );
        
		} // while()
    	// input file open success
    
    	vector<Pok> datas = input_to_vec(reader);
    
	    for(int i = 0 ; i < datas.size(); i++){
    		if(i == 0 ){
    			head = new Node;
    			head->left = NULL;
    			head->right = NULL;
    			head->pok.push_back(datas[i]);
			}
			else
				AddNode(head, datas[i]);
		} // build tree
	}
	*/
	int basic = 0, counter = 0, node = 0 ;
	Node* temp = NULL;
	
	cout << "#\tName\tType 1\tType 2\tTotal\tHP\tAttack\tDefense\tSp. Atk\tSp. Def\tSpeed\tGeneration\tLegendary\n";
	// speical case head is biggest
	if(head->right == NULL){
		if ( head->pok.size() == 1 ){
			printdata(head);
			temp = head;
			head = head->left;
			delete temp;
		}
		else{
			printdata(head);
			head->pok.erase(head->pok.begin());
		}
	}
	else
		DelANode(head, basic, counter, temp);
	
	return head;
} 
int main(){
	string command;
	int operation;
	bool end = false;
	Node* head = NULL;
	while ( ! end ) {
		startGen(); // generate the starting article for users to check
		cout << "input a num:";
		cin >> command;
		operation = atoi(command.c_str());
		// do different things based on user command
		switch(operation){
			case 1:
				head = mission1();
				break;
			case 2:
				mission2(head);
				break;
			case 3:
				head = mission3(head);
				break;
			case 0:
				end = true;
				break;
			default: 
				cout << "Command does not exist!" << "\n"; // ¨¾§b 
				break;
		}
	} // while()
	cout << "quitting !" << "\n";
	
}
