#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <vector>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;


void operation_choice();
bool Input_Operation_Is_Ok(string s);
int Input_A_positive_Num();

void mission1();
bool Input_Num_Is_Ok(string s);
void mission1_all_possible(int target, vector<int> passed, int num, int &total);
bool not_passed(int target, vector<int> passed);
void get_passed(vector<int> passed);

void mission2();
void mission2_all_possible(int target, vector<int> nums, vector<int> passed, int &total);

void mission3();
void mission3_all_possible(int target, int num, vector<int> passed, int &total);

void mission4();
void mission4_all_possible(int target, int num, vector<int> passed, int &total, int N);


int main(int argc, char** argv) {
	string s;
	bool end = false;
	while( !end ){    // when user input '0' all operation end  
		operation_choice();
		              // output operation choice
		              
		cin >> s;     // input which mission
		while( !Input_Operation_Is_Ok(s) ){
			cout << "Error Operation\n\n";
			operation_choice();
			cin >> s;
		}
// if input error do this loop^^^

		if( atoi(s.c_str()) ==0 )
			end = true;
			
		else if( atoi(s.c_str()) ==1 )
			mission1();
		
		else if(atoi(s.c_str()) ==2)  
			mission2();
		
		else if(atoi(s.c_str()) ==3)
			mission3();
		else if(atoi(s.c_str()) ==4)
			mission4();
		else;
	}
	
}

void operation_choice(){
	// output operation choice
	cout << "** Permutation Generator **\n";
	cout << "* 0. Quit                 *\n";
	cout << "* 1. N numbers from 1..N  *\n";
	cout << "* 2. M numbers from input *\n";
	cout << "* 3. M numbers from 1..9  *\n";
	cout << "* 4. M numbers from 1..N  *\n";
	cout << "***************************\n";
	cout << "Input a choice(0, 1, 2, 3, 4):";
}


bool Input_Operation_Is_Ok(string s){
	// judge operation input is legal
	if(Input_Num_Is_Ok(s)){
		if( atoi(s.c_str()) ==0 || atoi(s.c_str()) == 1 || atoi(s.c_str()) == 2 || atoi(s.c_str()) == 3 || atoi(s.c_str()) == 4 )
			return 1;
	}
	return false;
}

int Input_A_positive_Num(){
	// translate string to int ans return it
	string s;
	do{
		cout << "input num : ";
		cin >> s;
		cout << '\n';
	}while(!Input_Num_Is_Ok(s) || atoi(s.c_str()) <= 0 );
	
	return atoi(s.c_str()); 
}

void mission1(){
	int num;
	int times =0;
	int total =0;
	vector<int> passed;
	do {
		num = Input_A_positive_Num();
		
		// output error meassage
		if(num > 9)
			cout << "You need input [1 - 9]\n\n";
		
	}while(num > 9);
	
	mission1_all_possible(0, passed, num, total);
	cout << "\nMission 1 : " << total << " permutations\n"; 
	cout << "L = " << num << "\n\n";
}

bool Input_Num_Is_Ok(string s){
	// judge if input is a number
	for(int i=0; i< s.length(); i++){
		if( !isdigit(s[i]) )
			return false;
	}
    return true;
}

void mission1_all_possible(int target, vector<int> passed, int num, int &total){
	// at start target is 0, not need add to passed
	if(target != 0)
		passed.push_back(target);
	
	for(int i=1 ; i <= num; i++){
		if(not_passed(i, passed)){
			mission1_all_possible(i, passed, num, total);
		}
	}
	
	if(passed.size() == num ){
	// if size of passed equal num then output the passed
		cout << '[' << total+1 << ']' <<  " " ;
		get_passed(passed);
		cout << " \n";
		total++;
	}
}

void get_passed(vector<int> passed){
	// output all passed
	for(int i =0 ; i < passed.size() ; i++ ) 
		cout << passed[i] << " ";
}

bool not_passed(int target, vector<int> passed){
	// if target not in passed then return true, on the contrary return false
	for(int i =0 ; i < passed.size() ; i++ ){
		if(target == passed[i])
			return false;
	}
	
	return true;
}

void mission2(){
	clock_t  Begin, End;
	
	int num;
	int input =0;
	int total =0;
	vector<int> nums, passed;
	do{
		num = Input_A_positive_Num();
		if(num <2 || num >9)
			cout << "Your input number not in [2 - 9]\n\n" ;
	}while( num <2 || num >9);
	
	for(int i =0; i< num; i++){
		input = Input_A_positive_Num();
		
		// input num already in nums then input num again and output error meassage
		if(!not_passed(input, nums) ){
			i--;
			cout << "### Duplicate! Still need " << num - nums.size() << " numbers! ###\n\n" ;
		}
		
		// input > 0, if input > 999999 need input again and output error meassage
		else if(input > 999999){
			i--;
			cout << "Input number [1 - 999999]\n\n";
		}
		// input num not in nums add it in nums
		else
			nums.push_back(input);
	}
						// add all input nums in list
	Begin = clock();    // time start
	mission2_all_possible(0, nums, passed, total);
	cout << '\n';
	cout << "Mission 2: "<< total << " permutations\n" ;
	End = clock();      // tiem end
	cout << "T = "<< double(End - Begin) / CLK_TCK * 1000 << "ms\n\n";
	// calculate time
	
}


void mission2_all_possible(int target, vector<int> nums, vector<int> passed, int &total){
	// At begin target is 0, which not need push in passed
	if(target != 0)
		passed.push_back(target);
	for(int i =0; i <nums.size(); i++){
		// test all possible in list
		// if it not in passed
		// let this number be target of the next function
		if(not_passed(nums[i], passed)){
			mission2_all_possible(nums[i], nums, passed, total);
		}
	}
	
	
	if(passed.size() == nums.size() ){
		// if size of passed equal size of nums, output passed
		cout << '[' << total+1 << ']' <<  " " ;
		get_passed(passed);
		cout << " \n";
		total++;
	}
	
}


void mission3(){
	clock_t  Begin, End;
	int num, total;
	vector<int> passed; 
	num = Input_A_positive_Num();
	
	while(num > 9 || num < 1){
		cout << "It is NOT in [1 - 9]\n\n";
		num = Input_A_positive_Num();
	}
// if input error, then do this loop ^^^


	Begin = clock();
	mission3_all_possible(0, num, passed, total);
	End = clock();
	
	// calculate time 
	cout << "T = "<< double(End - Begin) / CLK_TCK * 1000 << "ms\n\n";
}

void mission3_all_possible(int target, int num, vector<int> passed, int &total){
	// begin target is 0, don't add in passed
	if(target != 0)
		passed.push_back(target);
	
	
	for(int i =1; i <=9; i++ ){
		// test all num from 1 to num
		// if it not in passed
		// let this number be the target of the next function
		if(not_passed(i, passed))
			mission3_all_possible(i, num, passed, total);
	}
	
	if(passed.size() == num){
		cout << '[' << total+1 << ']' <<  " " ;
		get_passed(passed);
		cout << " \n";
		total++;
	}
}


void mission4(){
	clock_t  Begin, End;
	int num, total;
	vector<int> passed; 
	int N = Input_A_positive_Num();
	
	while(N> 9 || N < 1){
		cout << "It is NOT in [1 - 9]\n\n";
		N = Input_A_positive_Num();
	}
	// if input error, then do this loop ^^^
	
	
	num = Input_A_positive_Num();
	while(num > N){
		cout << "This is number is too big XD\n";
		num = Input_A_positive_Num();
	}
	
	// if input error, then do this loop ^^^


	
	Begin = clock();
	mission4_all_possible(0, num, passed, total, N);
	End = clock();
	
	// calculate time 
	cout << "T = "<< double(End - Begin) / CLK_TCK * 1000 << "ms\n\n";
}

void mission4_all_possible(int target, int num, vector<int> passed, int &total, int N){
	// begin target is 0, don't add in passed
	if(target != 0)
		passed.push_back(target);
	
	
	for(int i =1; i <=N; i++ ){
		// test all num from 1 to num
		// if it not in passed
		// let this number be the target of the next function
		if(not_passed(i, passed))
			mission4_all_possible(i, num, passed, total, N);	
	}
	
	if(passed.size() == num){
		cout << '[' << total+1 << ']' <<  " " ;
		get_passed(passed);
		cout << " \n";
		total++;
	}
}
