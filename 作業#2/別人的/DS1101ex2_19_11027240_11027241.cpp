#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdio>
using namespace std;

struct ALL{
	string school_code;
	string school_name;
	string major_code;
	string major_name;
	string level;
	int student_number;
	int teacher_number;
	int last;
	int city_code;
	string city_name;
	string type1;
	string type2;
};

class Readfile {
	public :
		void Input_Data( ifstream &ifs);
		void Output_Data();
		string file_name;
		vector<ALL> datas;
		string All_Number(string s);
};


void showmission(){
	cout << "***  File Object Manipulator  ***\n";
    cout << "\* 0. QUIT                       *\n";
	cout << "* 1. COPY (Read & Save a file)  *\n";
	cout << "* 2. FILTER (Reduce a file)     *\n";
	cout << "* 3. MERGE (Join two files)     *\n";
	cout << "*********************************\n\n";
}


void mission1(Readfile name);
void mission2(Readfile name);
void Input_Data(Readfile name, ifstream ifs);
void Write_Data(ofstream& file,Readfile data);
void filter(ofstream &file, Readfile data, int student, int last, string filename );

bool Input_Num_Is_Ok(string s);

int Input_A_positive_Num();
int Input_require_last();
int Input_require_students();


void Readfile::Output_Data(){
	for(int i=0 ;i < datas.size() ;i++){
		cout << datas[i].school_code << " ";
		cout << datas[i].school_name << " ";
		cout << datas[i].major_code << " ";
		cout << datas[i].major_name << " ";
		cout << datas[i].level << " ";
		cout << datas[i].student_number << " ";
		cout << datas[i].teacher_number << " ";
		cout << datas[i].last << " ";
		cout << datas[i].city_code << " ";
		cout << datas[i].city_name << " ";
		cout << datas[i].type1 << " ";
		cout << datas[i].type2 << " ";
		cout << "\n";
	}
	cout << "\n";
}

void Readfile::Input_Data(ifstream &ifs){
	string s, s1, s2, s3;
	char c;
	ALL temp;
	while (ifs >> s) {
        temp.school_code = s;
        ifs >> s;
    	temp.school_name = s;
        ifs >> s;
        temp.major_code = s;
        ifs >> s;
        temp.major_name = s;
        ifs >> s;
    if ((int)s[0] >= (int)'A' && (int)s[0] <= 'Z' ){
        ifs >> s1;
        ifs >> s2; 
        ifs >> s3;
        s = s + " " + s1 + " " + s2 + " " + s3;
		temp.level = s;
		ifs >> s;
	}    
		s = All_Number(s);
		temp.student_number = atoi(s.c_str());
		
		ifs >> s;
		s = All_Number(s);
		temp.teacher_number =atoi(s.c_str());
		
		ifs >> s;
		s = All_Number(s);
		temp.last = atoi(s.c_str());
		
		ifs >> s;
		s = All_Number(s);
		temp.city_code =atoi(s.c_str());
		
		ifs >> s;
		s = All_Number(s);
		temp.city_name =s;
		
		ifs >> s;
		temp.type1 = s;
		
		ifs >> s;
		temp.type2 =s;
		
		datas.push_back(temp);

    }
    ifs.close();
}


string Readfile::All_Number(string s){
	string str;
	for(int i =0 ;i< s.length(); i++){
		if(isdigit(s[i]))
			str += s[i];
	}
	return str;
}

void Write_Data(ofstream &file, Readfile data){
	for(int i =0 ;i< data.datas.size(); i++){
		file << data.datas[i].school_code << "\t";
		file << data.datas[i].school_name << "\t";
		file << data.datas[i].major_code << "\t";
		file << data.datas[i].major_name << "\t";
		file << data.datas[i].level << "\t";
		file << data.datas[i].student_number << "\t";
		file << data.datas[i].teacher_number << "\t";
		file << data.datas[i].last << "\t";
		file << data.datas[i].city_code << "\t";		
		file << data.datas[i].city_name << "\t";
		file << data.datas[i].type1 << "\t";
		file << data.datas[i].type2 << "\t";
		file << "\n";
	}
	
	file.close();
}


void mission1(Readfile name){
	string filename;
	do{
		cout << "Input 201, 202, ...[0]Quit): ";
		cin >> filename;
		if(filename == "0")
			return ;
		ifstream ifs;
		ifs.open(filename.c_str());
		if(!ifs.is_open()){   // try the second way to open file
			filename = filename + ".txt";
			filename = "input" + filename;
			ifs.open(filename.c_str());
		
		}
		if (!ifs.is_open()) { // the file still not open
    		cout << "Failed to open file.\n\n";
    	}
    	
    	else {                // success open file
        	string s;
        	getline(ifs, s);
        	getline(ifs, s);
        	getline(ifs, s);
        	
        	name.file_name = filename;
        	name.Input_Data(ifs);
        	
        	ofstream copy;
        	

        	string copyfilename; 
        	
			for(int i =0 ;i <filename.length(); i++ ){
				if(isdigit(filename[i])){
					copyfilename = copyfilename + filename[i];
				}
			}

			copyfilename = copyfilename + ".txt";
			copyfilename = "copy" + copyfilename;
        	name.file_name = copyfilename;
        	copy.open(copyfilename.c_str());
			Write_Data(copy, name);   // ¼g¶iÀÉ®×¸Ì 
			cout << "Total number of records = "<< name.datas.size() << "\n";
        	cout << "// creat " << name.file_name << "\n";
			name.Output_Data();
        	break;
		}
		
	}while(true);
}

void filter(ofstream &file, Readfile data, int student, int last, string filename ){
	string s;
	file.open(filename.c_str());
	
	for(int i =0 ; i< data.datas.size() ;i++){
		if(data.datas[i].student_number >= student && data.datas[i].last >= last){
			file << data.datas[i].school_code << "\t";
			file << data.datas[i].school_name << "\t";
			file << data.datas[i].major_code << "\t";
			file << data.datas[i].major_name << "\t";
			file << data.datas[i].level << "\t";
			file << data.datas[i].student_number << "\t";
			file << data.datas[i].teacher_number << "\t";
			file << data.datas[i].last << "\t";
			file << data.datas[i].city_code << "\t";
			file << data.datas[i].city_name << "\t";
			file << data.datas[i].type1 << "\t";
			file << data.datas[i].type2 << "\t";
			file << "\n";
		}
	}
	
	file.close();
}

void mission2(Readfile name){
	string filename;
	do{
		cout << "Input 201, 202, ...[0]Quit): ";
		cin >> filename;
		if(filename == "0")
			return ;
		ifstream ifs;
		ifs.open(filename.c_str());
		if(!ifs.is_open()){
			filename = filename + ".txt";
			filename = "copy" + filename;
			ifs.open(filename.c_str());
		}
		if(!ifs.is_open()){
			cout << "Failed to open file.\n\n";
		}
		else{
			name.Input_Data(ifs);    // input data to "name"

			
			int student, last;
			student = Input_require_students();
			last = Input_require_last();
			ofstream ofs;
			
			filter(ofs, name, student, last, filename );
			
			ifs.open(filename.c_str());
			
			// copy file input in Readfile "copy"
			Readfile copy;
			copy.Input_Data(ifs);
			
			// and Output Readfile copy 's data
			cout << "Total number of records = " << copy.datas.size() << "\n";
			cout << "// over write " << filename << "\n";
			copy.Output_Data();
			cout << "\n";
			

			
			break;
		}
		
	}while(true);
}

Readfile mergefile(Readfile file1, Readfile file2){  // *
	Readfile file3;
	int num1  =0;
	int num2  =0;
	int times =0;

	
	for(; num1 < file1.datas.size(); num1++){
		
		while(atoi(file1.datas[num1].school_code.c_str()) > atoi(file2.datas[num2].school_code.c_str()))
			num2++;
			
		if(file1.datas[num1].school_code == file2.datas[num2].school_code ){
			file3.datas.push_back(file1.datas[num1]);
			file3.datas.push_back(file2.datas[num2]);
			file2.datas.erase(file2.datas.begin() + num2);
			num2++;
		}
		else{
			file3.datas.push_back(file1.datas[num1]);
		}
		
	}
	
	for(; num2 < file2.datas.size() ;num2 ++){
		file3.datas.push_back(file2.datas[num2]);
	}
	
	
	
	return file3;
}


void mission3(){
	Readfile file1, file2;
	string s1, s2;
	ifstream ifs;
	while(true){
		cout << "Input 1st file - 201, 202, ...[0]Quit):";
		cin >> s1;
		if (atoi(s1.c_str()) == 0)
			return;
		ifs.open(s1.c_str());
		if(!ifs.is_open()){
			s1 = s1 + ".txt";
			s1 = "copy" + s1;
			ifs.open(s1.c_str());
		}
		if(ifs.is_open())
			break;
	}  // open 1st file
		
	file1.file_name = s1;
	file1.Input_Data(ifs);
	
		
	while(true){
		cout << "Input 2nd file - 201, 202, ...[0]Quit):  ";
		cin >> s2;
		if (atoi(s2.c_str() ) == 0)
			return;
		ifs.open(s2.c_str());
		if(!ifs.is_open()){
			s2 = s2 + ".txt";
			s2 = "copy" + s2;
			ifs.open(s2.c_str());
		}
		if(ifs.is_open())
			break;
	} // open 2nd file
		
	file2.file_name = s2;
	file2.Input_Data(ifs);
	
	Readfile file3 = mergefile(file1, file2);
	cout << "output\n";
	cout << "Total number of records = "<< file3.datas.size() << "\n";
	
	string file3_name = "output";
	for(int i =0 ; i< file1.file_name.length(); i++){
		if(isdigit(file1.file_name[i]))
			file3_name += file1.file_name[i];
	}
	file3_name += '_';
	
	for(int i =0 ; i< file2.file_name.length(); i++){
		if(isdigit(file2.file_name[i]))
			file3_name += file2.file_name[i];
	}
	
	file3_name += ".txt";
	file3.file_name = file3_name;
	cout << "// creat " << file3.file_name << "\n";
	
	ofstream ofs;
	ofs.open(file3_name.c_str());
	file3.file_name = file3_name;
	
	Write_Data( ofs, file3);
	file3.Output_Data();
	
}




bool Input_Num_Is_Ok(string s){
	// judge if input is a number
	for(int i=0; i< s.length(); i++){
		if( !isdigit(s[i]) )
			return false;
	}
    return true;
}

string All_number(string s){
	string str;
	for(int i =0 ;i< s.length(); i++){
		
	}
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
		cout << "Threshould on number of graduates : ";
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
		showmission();
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


