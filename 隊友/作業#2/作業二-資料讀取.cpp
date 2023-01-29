# include <iostream>
# include <fstream>
# include <string.h>
# include <stdlib.h>

using namespace std;

void startGen();
void cleanchar( char target[128] );
void mission1();
void mission2();
void mission3();
void mission4();

class FOM {

    public :

    void mission1() {
	
	    ifstream reader;
    	ofstream writer;

        cout << "Input 201, 202, ...( type 0 to Quit ) : " << endl; 
        string filename;
        cin >> filename; // ask for file name
        if ( filename == "0" ) { // user can quit this mission by typing 0
            return;
        } // if()
    
    	filename = "input" + filename + ".txt";
    	reader.open( filename.c_str() ); // open file
    
    	while ( ! reader.is_open() ) { // checking if the file is open 
    	   		                       // if don't ask user to try again
    		cout << "### " + filename + " does not exist! ###";
    		cout << "Input 201, 202, ...( type 0 to Quit ) : " << endl;
    		cin >> filename;
    		if ( filename == "0" ){
    		  return;
       	 	} // if()
        
    		filename = "input" + filename + ".txt";
        	reader.open( filename.c_str() );
        
		} // while()
    // input file open success
    
    	filename = "copy" + filename.substr(5); // name of copied file
    	writer.open( filename.c_str() ); // start writing data into copy file 
    
    	char data[512]; // for get data from file reading

    	for ( int i = 0 ; i < 3 ; i ++ )
        	reader.getline( data, sizeof(data) ); // clean the first three line thet we don't need
        
    	int count = 0; // for counting how many data is in the copied file   
        
    	while ( ! reader.eof() ) { // read remained datas and copy them into the copied file
        	reader.getline( data, sizeof(data) );
        	count += 1;
        	writer << data << endl;
    	} // while() 
    
    	cout << "Number of records = " << count << endl;
    
   		 writer.close();
    	reader.close();
		return;
	
	} // mission1

	void mission2() {
	
		ifstream reader;
		ofstream writer;

    	cout << "Input 201, 202, ...( type 0 to Quit ) : " << endl;
    	string filename;
    	cin >> filename; // ask for filename
   	 	if ( filename == "0" ) { // user can quit this mission by typing 0
     	   return;
    	} // if()

    	filename = "copy" + filename + ".txt";
    	reader.open( filename.c_str() ); // open file
    
    	while ( ! reader.is_open() ) { // checking if the file is open 
    	                           	   // if don't ask user to try again
    		cout << "### " + filename + " does not exist! ###";
    		cout << "Input 201, 202, ...( type 0 to Quit ) : " << endl;
    		cin >> filename;
    		if ( filename == "0" ){
    	 	    return;
        	}	 // if()
        
    		filename = "copy" + filename + ".txt"; // name of copied file
        	reader.open( filename.c_str() ); // start writing data into copy file 
        
		} // while()
    // input file open success
    	reader.close();
    	rename( filename.c_str() , "temp.txt" ); // rename the file needed
        reader.open( "temp.txt" );               // because the file will be cleaned when the writer open it
    
    	char bound[100] = "\0"; 
    
    	do { // ask for lower bound of students
    		cout << "Input a lower bound on the number of students: ";
        	cin >> bound;
        	if ( atoi( bound ) < 0 || atoi( bound ) > 9999 ) // ¨¾§b try again! 
    	    	cout << "### It is NOT in [0,9999] ###" << endl;
		} while( atoi( bound ) < 0 || atoi( bound ) > 9999 );

    	int bounds = atoi( bound ); // on 7th position ( bound of students )
    
    	do { // ask for lower bound of graduates
    		cout << "Input a lower bound on the number of graduates: ";
        	cin >> bound;
        	if ( atoi( bound ) < 0 || atoi( bound ) > 9999 ) // ¨¾§b try again!
    	    	cout << "### It is NOT in [0,9999] ###" << endl;
		} while( atoi( bound ) < 0 || atoi( bound ) > 9999 );

    	int boundg = atoi( bound );  // on 9th position ( bound of graduates )
    
    	// start reading copied file
    	writer.open( filename.c_str() );
    	string data;
    	char eater[128] = "\0"; 
    	int count = 0,  tester = 0;
    
    	while ( ! reader.eof() ) {
    	
    		data.clear();
    	
    		for ( int i = 0 ; i < 7 ; i ++ ) { // read to the data of students
           	 	reader.getline( eater, sizeof(eater), '\t' );
           	 	data = data + eater + '\t';
       	 	} // for()
        
        	if ( atoi( eater ) < bounds ) { // checking bound
        		reader.getline( eater, sizeof( eater ) );
            	continue;  // quitting this line if bound not OK
        	} // if()
        
        	for ( int i = 0 ; i < 2 ; i ++ ) { // read to the data of graduates
        		reader.getline( eater, sizeof( eater ), '\t' );
            	data = data + eater + '\t';
			} // for
        
        	if ( atoi( eater ) < boundg ) { // checking bound
		    	reader.getline( eater, sizeof( eater ) );
            	continue;  // quitting this line if bound not OK
        	} // if()
        
        	reader.getline( eater, sizeof( eater ) ); // get the remain line
        	data = data + eater;
        
        	count += 1;
        	writer << data << endl;
        
    	} // while() 
    
    	cout << "Number of records = " << count << endl;
    
    	writer.close();
    	reader.close();
    
    	remove( "temp.txt" ); // remove the file that do not need ( after closing )

		return;
	} // mission2

	void cleanchar( char target[128] ) {
		for ( int i = 0 ; i < 128 ; i ++ ) {
			target[i] = '\0';
		} // for()
	} // cleanchar

	void mission3() {
		ifstream reader1, reader2; // reader1 for the first typing file // reader2 for the second typing file
		ofstream writer1, writer2; // writer1 for the merged file // writer2 save the data need to be put after file one
                                                              // ends ( part of second typing file's data )
    	cout << "Input ( first file ) 201, 202, ...( type 0 to Quit ) : " << endl;
    	string filename1, name1;
    	cin >> filename1; // ask for file name
    	name1 = filename1;
    	if ( filename1 == "0" ) { // user can quit this mission by typing 0
        	return;
    	} // if()
    
    	filename1 = "copy" + filename1 + ".txt";
    	reader1.open( filename1.c_str() ); // open file
    
    	while ( ! reader1.is_open() ) { // checking if the file is open 
    	                            // if don't ask user to try again
    		cout << "### " + filename1 + " does not exist! ###";
    		cout << "Input ( first file ) 201, 202, ...( type 0 to Quit ) : " << endl;
    		cin >> filename1;
    		if ( filename1 == "0" ){
    	  	    return;
        	} // if()
        
    		filename1 = "copy" + filename1 + ".txt";
        	reader1.open( filename1.c_str() );
        
		} // while()

    	cout << "Input ( second file ) 201, 202, ...( type 0 to Quit ) : " << endl;
    	string filename2, name2;
    	cin >> filename2; // ask for file name
    	name2 = filename2;
    	if ( filename2 == "0" ) { // user can quit this mission by typing 0
    	    return;
    	} // if()
    
    	filename2 = "copy" + filename2 + ".txt";
    	reader2.open( filename2.c_str() ); // open file
    
    	while ( ! reader2.is_open() ) { // checking if the file is open 
    	                            	// if don't ask user to try again
    		cout << "### " + filename2 + " does not exist! ###";
    		cout << "Input ( second file ) 201, 202, ...( type 0 to Quit ) : " << endl;
    		cin >> filename2;
    		if ( filename2 == "0" ){
    	  	    return;
        	} // if()
        
    		filename2 = "copy" + filename2 + ".txt";
        	reader2.open( filename2.c_str() );
        
		} // while()
	
	// two copy files open success
		string mergefilename = "output" + name1 + "_" + name2 + ".txt";
		writer1.open( mergefilename.c_str() ); // merged file
		writer2.open( "temp.txt" ); // save the data need to be at the end
	
		string data1, data2;
    	char eater1s[128] = "\0", eater2s[128] = "\0"; // school code
    	char eater1d[128] = "\0", eater2d[128] = "\0"; // department code
    	int count = 0;
    	char check[128]; // check if need to insert data2 into data1
    
    	reader1.getline( eater1s, sizeof( eater1s ) , '\t' ); // get the first school code for file1
    	reader2.getline( eater2s, sizeof( eater2s ) , '\t' ); // get the first school code for file2
    
    	while ( ! reader1.eof() && ! reader2.eof() ) {
        
    		if ( strcmp( eater1s, eater2s ) < 0 ) { // file1's school code is smaller than file2's
    			writer1 << eater1s << "\t";         // insert file1's data 
    			reader1.getline( eater1s, sizeof( eater1s ) ); // get the whole line
    			writer1 << eater1s << "\n";
    			count += 1;
    			reader1.getline( eater1s, sizeof( eater1s ), '\t' ); // get the next school code( or eof )
			} // if()
    		else if ( strcmp( eater1s, eater2s ) == 0 ) { // same school code // compare the department code 
            	if ( strcmp( eater1d, "\0" ) != 0 ) { // if department code cleared , get one 
					reader1.getline( eater1d, sizeof( eater1d ), '\t' );
					data1 = data1 + eater1s + "\t" + eater1d + "\t";
					reader1.getline( eater1d, sizeof( eater1d ), '\t' ); // get department code
					data1 = data1 + eater1d + "\t";
				} // if()
			
				if ( strcmp( eater2d, "\0" ) != 0 ) { // if department code cleared , get one 
					reader2.getline( eater2d, sizeof( eater2d ), '\t' );
					data2 = data2 + eater2s + "\t" + eater2d + "\t";
					reader2.getline( eater2d, sizeof( eater2d ), '\t' ); // get department code
					data2 = data2 + eater2d + "\t";
				} // if()
            
           		if ( strcmp( eater1d, eater2d ) <= 0 ) { // file1's department code is smaller( or same )
				                                     // insert file1's data
					if ( data1.empty() ) 
						data1 = data1 + eater1s + "\t";
				
					reader1.getline( eater1d, sizeof( eater1d ) );
					data1 = data1 + eater1d + "\n";
					writer1 << data1; 
					data1.clear();
					cleanchar( eater1d ); // clear the department code inserted
					strcpy( check, eater1s ); // save file1's school code now for checking
				                          // if file2's data need to insert after
					reader1.getline( eater1s, sizeof( eater1s ), '\t' ); // get the next school code( or eof )
				
				} // if()
				else{ // file1's department code is bigger
			     	 // insert file2's data
			    	if ( data2.empty() ) 
                   	    data2 = data2 + eater2s + "\t";
				
					reader2.getline( eater2d, sizeof( eater2d ) );
					data2 = data2 + eater2d + "\n";
					writer1 << data2;
					data2.clear();
					cleanchar( eater2d ); // clear the department code inserted
					reader2.getline( eater2s, sizeof( eater2s ), '\t' ); // get the next school code( or eof )
				} // else
			
				count += 1;
            
			} // else if()
			else { // file1's school code is bigger than file2's
		      	   // check which file file2's data need to insert
		    	if ( strcmp( check, eater2s ) == 0 ) { // insert to writer1( merged file )
		    	
		    		writer1 << eater2s << "\t";
    		    	reader2.getline( eater2s, sizeof( eater2s ) ); // get the whole line
    		    	writer1 << eater2s << "\n";
    		    	count += 1;
    		    	reader2.getline( eater2s, sizeof( eater2s ), '\t' ); // get the next school code( or eof )
		    	
				} // if()
				else { // insert to writer2( put after file one ended )
			   	 	writer2 << eater2s << "\t";
    		    	reader2.getline( eater2s, sizeof( eater2s ) ); // get the whole line
    		    	writer2 << eater2s << "\n";
    		    	count += 1;
    		    	reader2.getline( eater2s, sizeof( eater2s ), '\t' ); // get the next school code( or eof )
    	    	} // else
    	    
			} // else
    	
		} // while()


		while ( strcmp( check, eater2s ) == 0 ) { // last check // check the last file1 and other file2 data 
		    	writer1 << eater2s << "\t" ;
    	    	reader2.getline( eater2s, sizeof( eater2s ) ); // get the whole line
    	    	writer1 << eater2s << "\n";
    	    	reader2.getline( eater2s, sizeof( eater2s ), '\t' ); // get the next school code( or eof )
		} // while()
		writer2.close();
		
		if ( reader1.eof() ) { // file one find eof first
			reader1.close();
			reader1.open( "temp.txt" );
			while( ! reader1.eof() ) { // insert data need to put after file one end
				reader1.getline( eater1s, sizeof( eater1s ) );
				if ( ! reader1.eof() )
			    	writer1 << eater1s << endl;
			} // while()

			writer1 << eater2s << "\t" ;
	  		while( ! reader2.eof() ) { // insert remain data of file two
		    	reader2.getline( eater2s, sizeof( eater2s ) );
		    	writer1 << eater2s << endl;
		    	count += 1;
			} // while()
		} // if()
		
		else if ( reader2.eof() ) { // file two find eof first
			writer1 << eater1s << "\t";
			while( ! reader1.eof() ) { // insert the remain data of file one
				reader1.getline( eater1s, sizeof( eater1s ) );
		    	writer1 << eater1s << endl;
		    	count += 1;
			} // while
		
			reader2.close();
			reader2.open( "temp.txt" );
			while( ! reader2.eof() ) { // insert data need to put after file one end
				reader2.getline( eater2s, sizeof( eater2s ) );
				writer1 << eater2s << endl;
			} // while()
		
		} // else if
    
    	reader1.close();
		reader2.close();
		writer1.close();
	
		remove( "temp.txt" ); // remove file do not need
		cout << "Number of records = " << count << endl;
	
    	return;
	} // mission3

void mission4() { // ·Ó¶¶§Ç±Æ... // not using in this case
	
	ifstream reader1, reader2;
	ofstream writer;

    cout << "Input ( first file ) 201, 202, ...( type 0 to Quit ) : " << endl;
    string filename1, name1;
    cin >> filename1;
    name1 = filename1;
    if ( filename1 == "0" ) {
        return;
    } // if()
    
    filename1 = "copy" + filename1 + ".txt";
    reader1.open( filename1.c_str() );
    
    while ( ! reader1.is_open() ) {
    	
    	cout << "### " + filename1 + " does not exist! ###";
    	cout << "Input ( first file ) 201, 202, ...( type 0 to Quit ) : " << endl;
    	cin >> filename1;
    	if ( filename1 == "0" ){
    	  return;
        } // if()
        
    	filename1 = "copy" + filename1 + ".txt";
        reader1.open( filename1.c_str() );
        
	} // while()

    cout << "Input ( second file ) 201, 202, ...( type 0 to Quit ) : " << endl;
    string filename2, name2;
    cin >> filename2;
    name2 = filename2;
    if ( filename2 == "0" ) {
        return;
    } // if()
    
    filename2 = "copy" + filename2 + ".txt";
    reader2.open( filename2.c_str() );
    
    while ( ! reader2.is_open() ) {
    	
    	cout << "### " + filename2 + " does not exist! ###";
    	cout << "Input ( first file ) 201, 202, ...( type 0 to Quit ) : " << endl;
    	cin >> filename2;
    	if ( filename2 == "0" ){
    	  return;
        } // if()
        
    	filename2 = "copy" + filename2 + ".txt";
        reader2.open( filename2.c_str() );
        
	} // while()
	
	// two copy files open success
	string mergefilename = "output" + name1 + "_" + name2 + ".txt";
	writer.open( mergefilename.c_str() );
	
	string data1, data2;
    char eater1s[128] = "\0", eater2s[128] = "\0"; // school code
    char eater1d[128] = "\0", eater2d[128] = "\0"; // department code
    int count = 0;
    
    reader1.getline( eater1s, sizeof( eater1s ) , '\t' );
    reader2.getline( eater2s, sizeof( eater2s ) , '\t' );
    
    while ( ! reader1.eof() && ! reader2.eof() ) {
    	
    	if ( strcmp( eater1s, eater2s ) < 0 ) {
    		writer << eater1s << "\t";
    		reader1.getline( eater1s, sizeof( eater1s ) ); // get the whole line
    		writer << eater1s << "\n";
    		count += 1;
    		reader1.getline( eater1s, sizeof( eater1s ), '\t' ); // get the next school code( or eof )
		} // if()
		else if ( strcmp( eater1s, eater2s ) == 0 ) {
			if ( strcmp( eater1d, "\0" ) != 0 ) {
				reader1.getline( eater1d, sizeof( eater1d ), '\t' );
				data1 = data1 + eater1s + "\t" + eater1d + "\t";
				reader1.getline( eater1d, sizeof( eater1d ), '\t' ); // get department code
				data1 = data1 + eater1d + "\t";
			} // if()
			
			if ( strcmp( eater2d, "\0" ) != 0 ){
				reader2.getline( eater2d, sizeof( eater2d ), '\t' );
				data2 = data2 + eater2s + "\t" + eater2d + "\t";
				reader2.getline( eater2d, sizeof( eater2d ), '\t' ); // get department code
				data2 = data2 + eater2d + "\t";
			} // if()
			
			if ( strcmp( eater1d, eater2d ) <= 0 ) {
				
				if ( data1.empty() ) 
					data1 = data1 + eater1s + "\t";
				
				reader1.getline( eater1d, sizeof( eater1d ) );
				data1 = data1 + eater1d + "\n";
				writer << data1; 
				data1.clear();
				cleanchar( eater1d );
				reader1.getline( eater1s, sizeof( eater1s ), '\t' ); // get the next school code( or eof )
			} // if()
			else{ // strcmp( eater1d, eater2d ) > 0
			
			    if ( data2.empty() ) 
                    data2 = data2 + eater2s + "\t";
				
				reader2.getline( eater2d, sizeof( eater2d ) );
				data2 = data2 + eater2d + "\n";
				writer << data2;
				data2.clear();
				cleanchar( eater2d );
				reader2.getline( eater2s, sizeof( eater2s ), '\t' ); // get the next school code( or eof )
			} // else
			
			count += 1;
			
		} // else if()
		else { // strcmp( eater1s, eater2s ) > 0
			writer << eater2s << "\t";
    		reader2.getline( eater2s, sizeof( eater2s ) ); // get the whole line
    		writer << eater2s << "\n";
    		count += 1;
    		reader2.getline( eater2s, sizeof( eater2s ), '\t' ); // get the next school code( or eof )
		} // else
    	
	} // while()
	
	if ( reader1.eof() ) {
		writer << eater2s << "\t";
	  	while( ! reader2.eof() ) {
		    reader2.getline( eater2s, sizeof( eater2s ) );
		    writer << eater2s << endl;
		    count += 1;
		} // while()
	} // if()
	else if ( reader2.eof() ) {
		writer << eater1s << '\t';
		while( ! reader1.eof() ) {
			reader1.getline( eater1s, sizeof( eater1s ) );
		    writer << eater1s << endl;
		    count += 1;
		} // while
	} // else if
	
	reader1.close();
	reader2.close();
	writer.close();
	
	count -= 1; 
	
	cout << "Number of records = " << count << endl;
	
    return;
} // mission4

}; // class FOM


void startGen() {
	cout << endl;
	cout << "***  File Object Manipulator  ***" << endl;
	cout << "* 0. QUIT                       *" << endl;
	cout << "* 1. COPY (Read & Save a file)  *" << endl;
	cout << "* 2. FILTER (Reduce a file)     *" << endl;
	cout << "* 3. MERGE (Join two files)     *" << endl;
	cout << "*********************************" << endl;
	cout << "Input a choice(0, 1, 2, 3): ";
} // startGen

int main(int argc, char** argv) {
	
	char command = 'a';
	FOM domission;

	
	while ( command != '0' ) {
		
		startGen(); // generate the starting article for users to check
		
		cin >> command; // read in user command
		cout << endl;
		cout << endl;
		
		// do different things based on user command
		if ( command == '1' ) { 
			domission.mission1(); // COPY (Read & Save a file)
		} // if()
		else if ( command == '2' ) {
			domission.mission2(); // FILTER (Reduce a file)
		} // else if()
		else if ( command == '3' ) {
			domission.mission3(); // MERGE (Join two files)
		} // else if()
		else if ( command != '0' ){
			cout << "Command does not exist!" << endl; // ¨¾§b 
		}
		
	} // while()
	
	cout << "quitting File Object Manipulator!" << endl;
	
	return 0;

} // main


