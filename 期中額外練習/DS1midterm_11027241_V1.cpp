
#include <iostream>		// cin, cout, endl
#include <cstdlib>		// system

using namespace std;		// naming space of standard library 

#define MAX_NO	9	        // constant limit on data amount
#define NOT_FOUND	-1	// the number is not found
#define BIG_INT	unsigned

class Fib {
    // private data members
private:
    BIG_INT	data[MAX_NO];					// a seires of numbers
    
public:
	// public member functions
	void put(int num, int postition){
    	data[postition] = num;
	}
	int get(int postition){
		return data[postition];	
	}
    
    Fib() {									// constructor to initialize data
	put(1, 0);
	put(1, 1);						// first numbers		
	for (int j=1; (j+1) < MAX_NO; j++) {// fibonacci series
	    put( get(j-1) + get(j), j+1);
	    cout << endl << "[" << j+2 << "] " << data[j+1];
	}	// end for
    }	// constructor
    // function declaration
    int bsearch(BIG_INT, int, int);			// find the position of a number
    
    
    
};	// Fib class

int main(void) {
    int command = 0, pos;
    Fib	anObj;								// call constructor to initialize data
			
    do {
	BIG_INT	goal;						// a number of search
	
    	cout << endl << "Input a number: ";	// prompt message
    	cin.clear();
    	cin >> goal;						// get a number to search
	if ((pos = anObj.bsearch(goal, 0, MAX_NO-1))
	    == NOT_FOUND)					// function call
	    cout << "The number " << goal << " is NOT found!" << endl;
	else
	    cout << endl << "The number " << goal << " is found at position " << pos << "." << endl;
	cout << endl << "Quit (type 0) or not? ";	// prompt message
	cin.clear();
	cin >> command;
    } while (command != 0);					// '0': stop the program
    system("pause");						// pause the display
    return 0;
}	// end main

int Fib::bsearch(BIG_INT g, int first, int last) {
	
    // cout << endl << first << ", " << last;
    if (first <= last) {
	int	mid = first + (last - first)/2;	// middle position
		
	if (g == get(mid))
	    return mid+1;					// found: exit the loop
	else if (g < get(mid))				// search the left half
	    bsearch(g, first, mid-1);
	else	
	    bsearch(g, mid+1, last); 	// search the right half
    }	// end if
    else
	return NOT_FOUND;
}	// end Fib::bsearch
