#include <iostream>
#include <vector> 
#include <algorithm>
#include <windows.h>

using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void startGen();
void dorecursion( int deepth, int numarray[], int &counts, int len, vector<int> notusing );
void chooser( int numarray[] , int pos, int len, int &counts, vector<int> notusing );
void mission1();
bool isDuplicate( int numarray[], int nums, int len );
void mission2();
void mission3();

int main(int argc, char** argv) {
	int command = -1;
	while ( command != 0 ) {
		
		startGen(); // generate the starting article for users to check
		
		cin >> command; // read in user command
		cout << endl;
		cout << endl;
		
		// do different things based on user command
		if ( command == 1 ) { 
			mission1(); // arrangement by recursion ( from 1 - x )
		} // if()
		else if ( command == 2 ) {
			mission2(); // arrangement by recursion ( using user type-in )
		} // else if()
		else if ( command == 3 ) {
			mission3(); // arrangement and combination ( choosing from 1 - 9 ) 
		} // else if()
		else if ( command != 0 ){
			cout << "Command does not exist!" << endl; // ¨¾§b 
		}
		
	} // while()
	
	cout << "quitting Permutation Generator!" << endl;
	
	return 0;
} // main

void dorecursion( int deepth, int numarray[], int &counts, int len, vector<int> notusing ) {
	
	if ( deepth == 1 ) { // special case that the user type 1 *means we don't need to do a recursion
		cout << numarray[0] << endl;
		counts += 1;
		return;
	} // if
	else if ( deepth == 2 ) { // the smallest element of the recursion
	
		// counting times and print the two possibility of the arrangement
		for ( int times = 0 ; times < 2 ; times ++ ) { 
		    counts ++;
	    	cout << "[" << counts << "] ";
		
		    for ( int i = 0 ; i < len ; i ++ ){
		        cout << numarray[i];
		        if ( i < len - 1 )
		            cout << ",";
	        } // for()
	    
	        cout << endl;
	    
	        swap( numarray[notusing[0] - 1], numarray[notusing[1] - 1] );
	        
	    } // for
	    
		return;
		
	} // else if()
	else if ( deepth > 2 ) { // the case we need to do recursion
        int mem = 0; // to memorize the (marked)one that do not use in the smaller recursion
        
		for ( int i = 0 ; i < deepth ; i ++ ) { // let the marked one go through all the places didn't mark
			// when i is 0 *means we don't need to change anything
			if ( i != 0 ) { 
			    swap( numarray[notusing[0] - 1], numarray[notusing[i] - 1] );
		    } // if()
		    
		    mem = notusing[i]; // memorize the marked one because we will erase it when doing smaller recursion
		    notusing.erase( notusing.begin() + i );
		    
		    
		    dorecursion( deepth - 1, numarray, counts, len , notusing ); // do the smaller recursion
		    
		    
		    notusing.insert( notusing.begin() + i, mem ); // put the marked one back
		    
		    if ( i != 0 ) { 
			    swap( numarray[notusing[0] - 1], numarray[notusing[i] - 1] );
		    } // if()
		    
	    } // for()
	
	} // else if()
	
} // dorecursion

void mission1() {
	
	int nums = 0;
	cout << "Input a number : ";
	cin >> nums;
	
	// ¨¾§b 
	while ( nums < 1 || nums > 9 ) {
	    cout << "### It is NOT in [1,9] ###" << endl;  //error message
	    cin >> nums;
    } // while()
    
	int numarray[nums]; // generate an array from 1 - x
	for ( int i = 0 ; i < nums ; i ++ ) {
		numarray[i] = i + 1;
	} // for
	
	vector<int> notusing(numarray, numarray + nums); 
	// generate a vector for position in the numarray that do not use in the smaller recursion
	
	numarray[nums] = '\0'; // ensure the last element of the array
	int counts = 0; // start counting 
	dorecursion( nums, numarray, counts, nums, notusing ); // do the recursion of arrangement
	
	// sending required final message of mission1
	cout << "Mission 1: " << counts << " permutation";
	if( nums != 1 )
	    cout << "s";
	cout << endl;
	
	cout << "L = " << nums << endl;
	
	return;
	
	
} // mission1

bool isDuplicate( int numarray[], int nums, int len ){
	for ( int i = 0 ; i < len ; i ++ ) {
		if ( nums == numarray[i] )
		  return true;
	} // for()
	
	return false;
} // isDuplicate

void mission2() {
	
	int nums = 0;
	cout << "Please input how many numbers you wants to do arrangement : ";
	cin >> nums;
	
	//¨¾§b 
	while ( nums < 2 || nums > 9 ) {
		cout << "### It is NOT in [2,9] ###" << endl;
		cin >> nums;
	}
	
	int numarray[nums];
	vector<int> notusing;
	for ( int i = 0 ; i < nums ; i ++ ) { // ask user to set the number user wants
		notusing.push_back(i + 1); 
		// generate a vector for position in the numarray that do not use in the smaller recursion by the way
	}  // for
	
	// inserting user type-in data
	int trans = 0;
	
	for ( int j = 0 ; j < nums ; j ++ ) {
		cout << "Please input the " << j + 1 << " number : ";
		cin >> trans;
		
		if ( trans < 1 || trans > 999999) { // ¨¾§b1¸¹  : ¼Æ¦r¤£¦b½d³ò 
			cout << "### It is NOT in [1,999999] ###" << endl;
			j -= 1;
		} // if()
		else if ( isDuplicate( numarray, trans, nums ) ) { // ¨¾§b2¸¹ : ­«½Æ¼Æ¦r 
			cout << "### Duplicate! Please try again! ###" << endl;
			j -= 1;
		} // else if()
		else {
			numarray[j] = trans;
		} // else
		
		
    } // for() 
		
	cout << endl;
	
	numarray[nums] = '\0'; // ensure the last element of the array
	int counts = 0; // start counting 
	
	DWORD starttime = GetTickCount(); // start calculating time
	dorecursion( nums, numarray, counts, nums, notusing ); // do the recursion of arrangement
	DWORD endtime = GetTickCount(); // end calculating time
	
	// sending required final message of mission2
	cout << "Mission 2: " << counts << " permutation";
	if( nums != 1 )
	    cout << "s";
	cout << endl;

	cout << "T = " << ( endtime - starttime ) << " ms" << endl;
	
	return;
	
} // mission2

void chooser( int numarray[] , int pos, int len, int &counts, vector<int> notusing ) {
	// choosing all possible combination of 1 - 9 choosing int(len) numbers
	// pos should start from len - 1
	
	if ( pos == 0 && numarray[pos] == 9 - len + pos + 2 ) { // the first one is on ceil
		return;
	} // if()
	else if ( pos != len - 1 && numarray[pos] < 9 - len + pos + 2 ) { 
	// the last one now(not the true one) not on ceil
		numarray[pos] += 1;
		
		for ( int i = pos ; i < len - 1 ; i ++ ) { // reset numarray to new numbers 
			numarray[i + 1] = numarray[i] + 1;
		} // for
		
		chooser( numarray, len - 1, len, counts, notusing ); // go back to the true last one
		
	} // else if()
	else if ( numarray[pos] < 9 - len + pos + 2 ) { // the true last one not on ceil 
	// do the arrangement recursion for this choose of combination
	
		dorecursion( len, numarray, counts, len, notusing );
    	numarray[pos] ++;
    	chooser( numarray , pos, len, counts, notusing );
		
	} // else if()
    else if ( numarray[pos] == 9 - len + pos + 2 ) { // last one now on ceil *check prier one
    	
    	chooser( numarray, pos - 1, len, counts, notusing );
    	
	} // else if()
   

} // chooser

void mission3(){
	
	int nums = 0;
	cout << "Input a number : ";
	cin >> nums;
	
	// ¨¾§b 
	while ( nums < 1 || nums > 9 ) {
	    cout << "### It is NOT in [1,9] ###" << endl;  //error message
	    cin >> nums;
    } // while()
    
    int numarray[nums];
    int counts = 0; // start counting
    // generate a vector for position in the numarray that do not use in the smaller recursion
    vector<int> notusing;
    
    // starting set
	for ( int i = 0 ; i < nums ; i ++ ) {
		numarray[i] = i + 1;
		notusing.push_back(i + 1); 
	}  // for()
	

	
    DWORD starttime = GetTickCount(); // start calculating time	
    
	chooser( numarray, nums - 1, nums, counts, notusing  ); // the main part of mission3
	
	DWORD endtime = GetTickCount(); // end calculating time
	
	// sending required final message of mission3
	cout << "Mission 3: " << counts << " permutation";
	if( nums != 1 )
	    cout << "s";
	cout << endl;

	cout << "T = " << ( endtime - starttime ) << " ms" << endl;
	
	return;
	
} // mission3

void startGen() {
	cout << endl;
	cout << "** Permutation Generator **" << endl;
	cout << "* 0. Quit                 *" << endl;
	cout << "* 1. N numbers from 1..N  *" << endl;
	cout << "* 2. M numbers from input *" << endl;
	cout << "* 3. M numbers from 1..9  *" << endl;
	cout << "***************************" << endl;
	cout << "Input a choice(0, 1, 2, 3): ";
} // startGen
