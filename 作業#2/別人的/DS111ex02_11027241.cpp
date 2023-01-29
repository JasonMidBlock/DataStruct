#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdio>
using namespace std;

class Readfile {
	public :
		void Input_Data( ifstream &ifs);
		void Output_Data();
		string file_name;
		vector<string> school_code;
		vector<string> school_name;
		vector<string> major_code;
		vector<string> major_name;
		vector<string> day_e;
		vector<string> day_c;
		vector<string> type_e;
		vector<string> type_c;
		vector<int> student_number;
		vector<int> teacher_number;
		vector<int> last;
		vector<string> city_code;
		vector<string> city_name;
		vector<string> type1;
		vector<string> type2;
};

void mission1(Readfile name);
void mission2(Readfile name);
void Write_Data(ofstream& file,Readfile data);
void filter(ofstream &file, Readfile data, int student, int last, string filename );

bool Input_Num_Is_Ok(string s);

int Input_A_positive_Num();
int Input_require_last();
int Input_require_students();


void Readfile::Output_Data(){
	for(int i=0 ;i < school_code.size() ;i++){
		cout << school_code[i] << "\t";
		cout << school_name[i] << "\t";
		cout << major_code[i] << "\t";
		cout << major_name[i] << "\t";
		cout << day_e[i] << "\t";
		cout << day_c[i] << "\t";
		cout << type_e[i] << "\t";
		cout << type_c[i] << "\t";
		cout << student_number[i] << "\t";
		cout << teacher_number[i] << "\t";
		cout << last[i] << "\t";
		cout << city_code[i] << "\t";
		cout << city_name[i] << "\t";
		cout << type1[i] << "\t";
		cout << type2[i] << "\t";
		cout << "\n";
	}
}

void Readfile::Input_Data(ifstream &ifs){
	string s;
	int i;
	char c;
	while (ifs >> s) {
        school_code.push_back(s);
        if( ifs.peek()) 
        ifs >> s ;
        school_name.push_back(s);
        ifs >> s;
        major_code.push_back(s);
        ifs >> s;
        major_name.push_back(s);
        ifs >> s;
		day_e.push_back(s);
		ifs >> s;
		day_c.push_back(s);
		ifs >> s;
		type_e.push_back(s);
		ifs >> s;
		type_c.push_back(s);
		ifs >> i;
		student_number.push_back(i);
		ifs >> i;
		teacher_number.push_back(i);
		ifs >> i;
		last.push_back(i);
		ifs >> s;
		city_code.push_back(s);
		ifs >> s;
		city_name.push_back(s);
		ifs >> s;
		type1.push_back(s);
		ifs >> s;
		type2.push_back(s);	
    }
    
    
    ifs.close();
}

void Write_Data(ofstream &file, Readfile data){
	/*
	string filename; 
	for(int i =0 ;i <s.length(); i++ ){
		if(isdigit(s[i])){
			filename = filename + s[i];
		}
	}
	
	filename = filename + ".txt";
	filename = "copy" + filename;
	file.open(filename.c_str());
	data.file_name = filename;
	*/
	for(int i =0 ;i< data.school_code.size(); i++){
		file << data.school_code[i] << "\t";
		file << data.school_name[i] << "\t";
		file << data.major_code[i] << "\t";
		file << data.major_name[i] << "\t";
		file << data.day_e[i] << "\t";
		file << data.day_c[i] << "\t";
		file << data.type_e[i] << "\t";
		file << data.type_c[i] << "\t";
		file << data.student_number[i] << "\t";
		file << data.teacher_number[i] << "\t";
		file << data.last[i] << "\t";
		file << data.city_code[i] << "\t";		
		file << data.city_name[i] << "\t";
		file << data.type1[i] << "\t";
		file << data.type2[i] << "\t";
		file << "\n";
	}
	
	file.close();
}


void mission1(Readfile name){
	string s;
	ifstream ifs;
	string filename;
	cin >> filename;
	
	ifs.open(filename.c_str());
	while( !ifs.is_open() ) {
		filename = "input" + filename + ".txt" ;
		ifs.open(filename.c_str());
		if ( !ifs.is_open()) {
			cout << "### " << filename <<" does not exist! ###" << endl;
			cin >> filename ;
		}
	}
	
	getline(ifs, s);
	getline(ifs, s);
	getline(ifs, s);
	Readfile copy;
	copy.Input_Data(ifs);
	ofstream ofs;
	filename[0] = 'c';
	filename[1] = 'o';
	filename[2] = 'p';
	filename[3] = 'y';
	for ( int i = 4 ; i < filename.length() ; i++ ) {
		filename[i] = filename[i+1] ;
	} // for
	
	filename[filename.length()] = '\0' ;
		
	
	ofs.open(filename.c_str()) ;
	Write_Data( ofs, copy ) ;
	copy.Output_Data();
	cout << "Number of records = " << copy.school_code.size() << endl;
	/*
	
	*/
}

void filter(ofstream &file, Readfile data, int student, int last, string filename ){
	string s;
	file.open(filename.c_str());
	
	for(int i =0 ; i< data.school_code.size() ;i++){
		if(data.student_number[i] >= student && data.last[i] >= last){
			file << data.school_code[i] << "\t";
			file << data.school_name[i] << "\t";
			file << data.major_code[i] << "\t";
			file << data.major_name[i] << "\t";
			file << data.day_e[i] << "\t";
			file << data.day_c[i] << "\t";
			file << data.type_e[i] << "\t";
			file << data.type_c[i] << "\t";
			file << data.student_number[i] << "\t";
			file << data.teacher_number[i] << "\t";
			file << data.last[i] << "\t";
			file << data.city_code[i] << "\t";
			file << data.city_name[i] << "\t";
			file << data.type1[i] << "\t";
			file << data.type2[i] << "\t";
			file << "\n";
		}
	}
	
	file.close();
}

void mission2(Readfile name){
	string s;
	ifstream ifs;
	int student, last;
	string filename;
	cin >> filename;
	
	ifs.open(filename.c_str());
	while( !ifs.is_open() ) {
		filename = "copy" + filename + ".txt" ;
		ifs.open(filename.c_str());
		if ( !ifs.is_open()) {
			cout << "### " << filename <<" does not exist! ###" << endl;
			cin >> filename ;
		}
	}
	
	cout << "Input a lower bound on the number of students: " ;
	cin >> student ;
	cout << "Input a lower bound on the number of graduates: " ;
	cin >> last ;
	
	Readfile copy;
	copy.Input_Data(ifs);
	ifs.close();
	ofstream ofs;
	filter( ofs, copy, student, last, filename );
	Write_Data( ofs, copy ) ;
	copy.Output_Data();
	cout << "Number of records = " << copy.school_code.size() << endl;
	
}

Readfile mergefile(Readfile file1, Readfile file2){
	Readfile file3;
	int num1  =0;
	int num2  =0;
	int times =0; 
	while(num1 < file1.school_code.size() || num2 < file2.school_code.size()){
		//如果file2先跑完 
		if(num2 == file2.school_name.size() ){
			file3.school_code.push_back(file1.school_code[num1]);
			file3.school_name.push_back(file1.school_name[num1]);
			file3.major_code.push_back(file1.major_code[num1]);
			file3.major_name.push_back(file1.major_name[num1]);
			file3.major_code.push_back(file1.major_code[num1]);
			file3.day_e.push_back(file1.day_e[num1]);
			file3.day_c.push_back(file1.day_c[num1]);
			file3.type_e.push_back(file1.type_e[num1]);
			file3.type_c.push_back(file1.type_c[num1]);
			file3.student_number.push_back(file1.student_number[num1]);
			file3.teacher_number.push_back(file1.teacher_number[num1]);
			file3.last.push_back(file1.last[num1]);
			file3.city_code.push_back(file1.city_code[num1]);
			file3.city_name.push_back(file1.city_name[num1]);
			file3.type1.push_back(file1.type1[num1]);
			file3.type2.push_back(file1.type2[num1]);
			num1++;
		}
		//如果file1先跑完
		else if(num1 == file1.school_name.size()){
			file3.school_code.push_back(file2.school_code[num2]);
			file3.school_name.push_back(file2.school_name[num2]);
			file3.major_code.push_back(file2.major_code[num2]);
			file3.major_name.push_back(file2.major_name[num2]);
			file3.major_code.push_back(file2.major_code[num2]);
			file3.day_e.push_back(file2.day_e[num2]);
			file3.day_c.push_back(file2.day_c[num2]);
			file3.type_e.push_back(file2.type_e[num2]);
			file3.type_c.push_back(file2.type_c[num2]);
			file3.student_number.push_back(file2.student_number[num2]);
			file3.teacher_number.push_back(file2.teacher_number[num2]);
			file3.last.push_back(file2.last[num2]);
			file3.city_code.push_back(file2.city_code[num2]);
			file3.city_name.push_back(file2.city_name[num2]);
			file3.type1.push_back(file2.type1[num2]);
			file3.type2.push_back(file2.type2[num2]);
			num2++;
		}
		else if( atoi(file1.school_code[num1].c_str()) <= atoi(file2.school_code[num2].c_str())){
			file3.school_code.push_back(file1.school_code[num1]);
			file3.school_name.push_back(file1.school_name[num1]);
			file3.major_code.push_back(file1.major_code[num1]);
			file3.major_name.push_back(file1.major_name[num1]);
			file3.major_code.push_back(file1.major_code[num1]);
			file3.day_e.push_back(file1.day_e[num1]);
			file3.day_c.push_back(file1.day_c[num1]);
			file3.type_e.push_back(file1.type_e[num1]);
			file3.type_c.push_back(file1.type_c[num1]);
			file3.student_number.push_back(file1.student_number[num1]);
			file3.teacher_number.push_back(file1.teacher_number[num1]);
			file3.last.push_back(file1.last[num1]);
			file3.city_code.push_back(file1.city_code[num1]);
			file3.city_name.push_back(file1.city_name[num1]);
			file3.type1.push_back(file1.type1[num1]);
			file3.type2.push_back(file1.type2[num1]);
			num1++;
		}
		
		else{
			file3.school_code.push_back(file2.school_code[num2]);
			file3.school_name.push_back(file2.school_name[num2]);
			file3.major_code.push_back(file2.major_code[num2]);
			file3.major_name.push_back(file2.major_name[num2]);
			file3.major_code.push_back(file2.major_code[num2]);
			file3.day_e.push_back(file2.day_e[num2]);
			file3.day_c.push_back(file2.day_c[num2]);
			file3.type_e.push_back(file2.type_e[num2]);
			file3.type_c.push_back(file2.type_c[num2]);
			file3.student_number.push_back(file2.student_number[num2]);
			file3.teacher_number.push_back(file2.teacher_number[num2]);
			file3.last.push_back(file2.last[num2]);
			file3.city_code.push_back(file2.city_code[num2]);
			file3.city_name.push_back(file2.city_name[num2]);
			file3.type1.push_back(file2.type1[num2]);
			file3.type2.push_back(file2.type2[num2]);
			num2++;
		}
	}
	
	
	return file3;
}


void mission3(){
	Readfile file1, file2, file3;
	string s;
	ifstream ifs;
	int student, last;
	string filename;
	cin >> filename;
	
	ifs.open(filename.c_str());
	while( !ifs.is_open() ) {
		filename = "copy" + filename + ".txt" ;
		ifs.open(filename.c_str());
		if ( !ifs.is_open()) {
			cout << "### " << filename <<" does not exist! ###" << endl;
			cin >> filename ;
		}
	}

    file1.Input_Data(ifs);
    ifs.close();
	ifs.open(filename.c_str());    
    file3.Input_Data(ifs);
    
    cin >> filename;
	ifs.open(filename.c_str());
	while( !ifs.is_open() ) {
		filename = "copy" + filename + ".txt" ;
		ifs.open(filename.c_str());
		if ( !ifs.is_open()) {
			cout << "### " << filename <<" does not exist! ###" << endl;
			cin >> filename ;
		}
	}

    file2.Input_Data(ifs);
    
    for ( int i = 0 ; i < file2.school_code.size() ; i++ ){
    	bool yesno = false ;
    	for ( int j = 0 ; j < file1.school_code.size() ; j++ ) {
    		// cout << i << " " << j;
    		
    		if ( file1.school_code[j] == file2.school_code[i] && file1.major_code[j] == file2.major_code[i] ) {
    			
    			
    			file3.school_code.insert( file3.school_code.begin()+j, file2.school_code[i] ) ;
    
      			file3.school_name.insert( file3.school_name.begin()+j, file2.school_name[i] ) ;
		     	file3.major_code.insert( file3.major_code.begin()+j, file2.major_code[i] ) ;
    			file3.major_name.insert( file3.major_name.begin()+j, file2.major_name[i] ) ;
    			file3.day_e.insert( file3.day_e.begin()+j, file2.day_e[i] ) ;
    			file3.day_c.insert( file3.day_c.begin()+j, file2.day_c[i] ) ;
    			file3.type_e.insert( file3.type_e.begin()+j, file2.type_e[i] ) ;
    			file3.type_c.insert( file3.type_c.begin()+j, file2.type_c[i] ) ;
    			file3.student_number.insert( file3.student_number.begin()+j, file2.student_number[i] ) ;
    			file3.teacher_number.insert( file3.teacher_number.begin()+j, file2.teacher_number[i] ) ;
    			file3.last.insert( file3.last.begin()+j, file2.last[i] ) ;
    			file3.city_code.insert( file3.city_code.begin()+j, file2.city_code[i] ) ;
    			file3.city_name.insert( file3.city_name.begin()+j, file2.city_name[i] ) ;
    			file3.type1.insert( file3.type1.begin()+j, file2.type1[i] ) ;
    			file3.type2.insert( file3.type2.begin()+j, file2.type2[i] ) ;
 				yesno = true ;
 				break;
			}	// if
			

    		
		}  // for
		
		if ( !yesno ) {
		
			file3.school_code.push_back( file2.school_code[i] ) ;
    		file3.school_name.push_back( file2.school_name[i] ) ;
			file3.major_code.push_back( file2.major_code[i] ) ;
    		file3.major_name.push_back( file2.major_name[i] ) ;
    		file3.day_e.push_back( file2.day_e[i] ) ;
    		file3.day_c.push_back( file2.day_c[i] ) ;
    		file3.type_e.push_back( file2.type_e[i] ) ;
    		file3.type_c.push_back( file2.type_c[i] ) ;
    		file3.student_number.push_back( file2.student_number[i] ) ;
   		 	file3.teacher_number.push_back( file2.teacher_number[i] ) ;
   		 	file3.last.push_back( file2.last[i] ) ;
   		 	file3.city_code.push_back( file2.city_code[i] ) ;
   		 	file3.city_name.push_back( file2.city_name[i] ) ;
   		 	file3.type1.push_back( file2.type1[i] ) ;
  		  	file3.type2.push_back( file2.type2[i] ) ;
		} // if
    	
    	cout << 'a' << i;
	} // for
	

	ifs.close();
	ofstream ofs;
	Write_Data( ofs, file3 ) ;
	file3.Output_Data();
	cout << "Number of records = " << file3.school_code.size() << endl;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
}




bool Input_Num_Is_Ok(string s){
	// judge if input is a number
	for(int i=0; i< s.length(); i++){
		if( !isdigit(s[i]) )
			return false;
	}
    return true;
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

int Input_require_students(){
	// translate string to int ans return it
	string s;
	do{
		cout << "Threshould on number of student : ";
		cin >> s;
		cout << '\n';
	}while(!Input_Num_Is_Ok(s) || atoi(s.c_str()) <= 0 );
	
	return atoi(s.c_str()); 
}

int Input_require_last(){
	// translate string to int ans return it
	string s;
	do{
		cout << "Threshould on number of student : ";
		cin >> s;
		cout << '\n';
	}while(!Input_Num_Is_Ok(s) || atoi(s.c_str()) <= 0 );
	
	return atoi(s.c_str()); 
}

int main(){
	int operation;
	string s;
	bool end = false;
	while(!end){
	
		do{
			cout << "Please input mission number: ";
			cin >> s;
			cout << '\n';
		}while( !Input_Num_Is_Ok(s) || atoi(s.c_str()) < 0);
		
		operation = atoi(s.c_str());
		Readfile file;
		switch(operation) {
			case 1:
				mission1(file);
				break;
			case 2:
				mission2(file);
				break;
			case 3:
				mission3();
				break;
			case 0:
				end = true;
				break;
			defult:
				cout << "Input error mission number\n\n";	
				break;
		}
			
	}
	
}


