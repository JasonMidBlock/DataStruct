// 11027240 許展榮 11027241 楊昀祖

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stack>
#include <windows.h>
#include <math.h>

using namespace std;

struct Data{
	string school_code;  
	string school_name;
	string major_code;
	string major_name;
	string type; // 日間 
	string type_c; // 日間 中文 
	string level; //  等級別 
	string level_c; // 等級別 中文 
	string student_number; // 學生數 
	string teacher_number; // 老師數 
	int last; // 上學年度畢業生數
	string city_code; 
	string city_name;
	string type1; // 體系別 數字 
	string type2; // 體系別
};

struct Type{
	int selection;
	int bubble;
	int quick;
	int merge;
	int radix;
};
class File{  // 每一種排列方式存一個class 
	public:
		void selection_sort() {
 		   for (int i=0; i<Datas.size(); i++) {
   		     int min_idx = i;
    		    for (int j=i+1; j<Datas.size(); j++) {
    		        if (Datas[j].last > Datas[min_idx].last) {
    		            min_idx = j;
    		        }
   		     }
   		     // swap
  		      Data temp = Datas[min_idx];
  		      Datas[min_idx] = Datas[i];
  		      Datas[i] = temp;
  		  }
		}

		void bubble_sort(){
			Data temp;
			for(int i = 0 ; i < Datas.size(); i++) {
				for(int j = i + 1 ; j < Datas.size() ; j++){
					if( Datas[j].last > Datas[i].last ){
						temp = Datas[i];
						Datas[i] = Datas[j];
						Datas[j] = temp;
					}
				}
			}
		}
		
		void quick_sort(int left, int right) {
			if ( left >= right ) // wrong bound(sort done)
			    return;
			    
			int memleft = left, memright = right; // let memleft be the base of quick sort
			
			while ( left != right ) {
				while ( left < right && Datas[right].last < Datas[memleft].last ) { // find data bigger than base from right
					right --; // if smaller than base, find next
				} // while() 
				
				while ( left < right && Datas[left].last >= Datas[memleft].last ) { // find data smaller(or same) than base from left
					left ++; // if bigger than base, find next
				}
				
				swap( Datas[left], Datas[right] ); // swap them( bigger than base throw to left else throw to right )
				
			} // while()
			// left == right now (the point of base)
			
			swap( Datas[memleft], Datas[left] ); // change base to the right position
			quick_sort( memleft, left - 1 );  // left is the position of the base now
			                             	  // the base of this time of recursion is in correct position now
			quick_sort( left + 1, memright ); // do recursion for quick sort of the left and right part of data
		}
		
		
		vector<Data> merge_sort(vector<Data> data_list){
			vector<Data> front, last;
			if(data_list.size() <= 1 ) 
				return data_list;
			// base case
			
			// 如果為奇數前面會比較少 
			for(int i = 0 ; i< data_list.size()/2; i++)
				front.push_back(data_list[i]);
			
			for(int i = data_list.size()/2; i < data_list.size() ; i++ ) 
				last.push_back(data_list[i]);
			
			front = merge_sort(front);
			last = merge_sort(last);
			
			// merge
			int j = 0, i = 0 ;
			for(int i = 0 ; i< last.size(); i++){
				while(j < front.size() && front[j].last > last[i].last )
					j++;
				if( j == front.size() ) 
					front.push_back(last[i]);
				else
					front.insert(front.begin() + j, last[i]);
			}
			
			return front;
		}
		
		void radix_sort(){
			vector<Data> t;
			vector< vector<Data> > temp;
			for(int i = 0 ; i < 10 ; i ++)
				temp.push_back(t);
			//初始化 
			
			int max = 1000;
			for(int i = 0 ; i < Datas.size(); i++){
				if(Datas[i].last > max)
					max = Datas[i].last;
			}
			
			// find largest
			int times = 10, time;
			while(max != 0) {
				time = times/10;
				for(int i = 0 ; i < Datas.size() ; i++)
					temp[(Datas[i].last%times)/time].push_back(Datas[i]);
				// 歸類在位數的位置
				
				Datas.clear();
				for(int i = 0; i < temp.size() ; i++){
					for(int j = 0 ; temp[i].size() > j  ; j++){
						Datas.push_back(temp[i][j]);
					}
				}
				// 重新加回Datas 
				
				temp.clear();
				for(int i = 0 ; i < 10 ; i ++)
					temp.push_back(t);
				// 初始化 temp	
				
				times*=10;
				max = max / 10;
			}
			// sort
			
			t = Datas;
			Datas.clear();
			for(int i = t.size() -1; i >= 0 ; i--)
				Datas.push_back(t[i]);
				
		}
		
		
		void input_file( vector<Data> datas){
			Datas.clear();
			for( int i = 0 ; i < datas.size() ; i++ ){
				Datas.push_back(datas[i]);
			}
		}
		
		void showDatas(){
			for(int i = 0 ; i < Datas.size(); i++)
				cout << Datas[i].last << "\n";
		}
		
		void write_file(int time){
			ofstream writer;
			writer.open( name.c_str() );
			writer << name << ": " << time << " ms\n";
			for( int i = 0 ; i < Datas.size() ; i++ ){
				writer << Datas[i].school_code << '\t';
				writer << Datas[i].school_name << '\t';
				writer << Datas[i].major_code <<'\t';
				writer << Datas[i].major_name <<'\t';
				writer << Datas[i].type <<'\t';
				writer << Datas[i].type_c <<'\t';
				writer << Datas[i].level <<'\t';
				writer << Datas[i].level_c <<'\t';
				writer << Datas[i].student_number <<'\t';
				writer << Datas[i].teacher_number <<'\t';
				writer << Datas[i].last <<'\t';
				writer << Datas[i].city_code <<'\t';
				writer << Datas[i].city_name <<'\t';
				writer << Datas[i].type1 <<'\t';
				writer << Datas[i].type2 <<'\t';
				writer << "\n";
			}
			
			writer.close();
		}
		
		
		void setname(string s){
			name = s;
		}
	private:
		string name;
		vector<Data> Datas;
};



void readfile(vector<Data> &datas, ifstream &reader){
	string s;
	Data temp;
	getline(reader, s);
	getline(reader, s);
	getline(reader, s);
	while( !reader.eof() ){
		reader >> temp.school_code ;
		reader >> temp.school_name ;
		reader >> temp.major_code ;
		reader >> temp.major_name ;
		reader >> temp.type ;
		reader >> temp.type_c ;
		reader >> temp.level ;
		reader >> temp.level_c ;
		reader >> temp.student_number ;
		reader >> temp.teacher_number ;
		reader >> temp.last ;
		reader >> temp.city_code ;
		reader >> temp.city_name ;
		reader >> temp.type1 ;
		reader >> temp.type2 ;
		datas.push_back(temp);
	}
	
	return ;
}

void mission1(){
	string filename;
	ifstream reader;
	File bubble, select;
	
	cout << "Input 501, 502, ...( type 0 to Quit ) : " << endl; 
    cin >> filename; // ask for file name
    if ( filename == "0" ) { // user can quit this mission by typing 0
        return;
	} // if()
    
    filename = "input" + filename + ".txt";
    reader.open( filename.c_str() ); // open file
    
    while ( ! reader.is_open() ) { // checking if the file is open 
    	   		                       // if don't ask user to try again
    	cout << "### " + filename + " does not exist! ###";
    	cout << "Input 501, 502, ...( type 0 to Quit ) : " << endl;
    	cin >> filename;
    	if ( filename == "0" ){
    		return;
    	} // if()
        
    	filename = "input" + filename + ".txt";
       	reader.open( filename.c_str() );
        
	} // while()
    // input file open success
    vector< Data > datas;
    readfile(datas, reader);
    reader.close();
    
    bubble.setname( "bubble_sort" + filename.substr(5) );
    bubble.input_file(datas);
    DWORD starttime = GetTickCount();
    bubble.bubble_sort();
    DWORD endtime = GetTickCount();
    bubble.write_file(endtime - starttime );
    
    select.setname( "select_sort" + filename.substr(5) );
    select.input_file(datas);
    starttime = GetTickCount();
    select.selection_sort();
    endtime = GetTickCount();
    select.write_file(endtime - starttime );
}
void mission2(){
	string filename;
	ifstream reader;
	File quick, merge;
	
	cout << "Input 501, 502, ...( type 0 to Quit ) : " << endl;
    cin >> filename; // ask for file name
    if ( filename == "0" ) { // user can quit this mission by typing 0
        return;
    } // if()
    
    filename = "input" + filename + ".txt";
    reader.open( filename.c_str() ); // open file
    
    while ( ! reader.is_open() ) { // checking if the file is open 
    	   		                       // if don't ask user to try again
    	cout << "### " + filename + " does not exist! ###";
    	cout << "Input 501, 502, ...( type 0 to Quit ) : " << endl;
    	cin >> filename;
    	if ( filename == "0" ){
    		return;
       	} // if()
        
    	filename = "input" + filename + ".txt";
        reader.open( filename.c_str() );
        
	} // while()
    // input file open success
    vector< Data > datas, merge_sort;
    readfile(datas, reader);
	reader.close();
	
	quick.setname( "quick_sort" + filename.substr(5) );
    quick.input_file(datas);
    DWORD starttime = GetTickCount();
    quick.quick_sort( 0, datas.size());
    DWORD endtime = GetTickCount();
    quick.write_file(endtime - starttime );
    
    starttime = GetTickCount();
    merge.setname( "merge_sort" + filename.substr(5) );
    starttime = GetTickCount();
    merge_sort = merge.merge_sort(datas);
    endtime = GetTickCount();
    merge.input_file(merge_sort);
    merge.write_file(endtime - starttime );
}

void mission3(){
	string filename;
	ifstream reader;
	File radix;
	
	cout << "Input 501, 502, ...( type 0 to Quit ) : " << endl; 
    cin >> filename; // ask for file name
    if ( filename == "0" ) { // user can quit this mission by typing 0
        return;
	} // if()
    
    filename = "input" + filename + ".txt";
    reader.open( filename.c_str() ); // open file
    
    while ( ! reader.is_open() ) { // checking if the file is open 
    	   		                       // if don't ask user to try again
    	cout << "### " + filename + " does not exist! ###";
    	cout << "Input 501, 502, ...( type 0 to Quit ) : " << endl;
    	cin >> filename;
    	if ( filename == "0" ){
    		return;
    	} // if()
        
    	filename = "input" + filename + ".txt";
       	reader.open( filename.c_str() );
        
	} // while()
    // input file open success
    
    vector< Data > datas;
    readfile(datas, reader);
    reader.close();
    
    radix.setname( "radix_sort" + filename.substr(5) );
    radix.input_file(datas);
    DWORD starttime = GetTickCount();
    radix.radix_sort();
    DWORD endtime = GetTickCount();
    radix.write_file(endtime - starttime );
}

void mission4(){
	string filename, code;
	ifstream reader;
	File bubble, select, quick, merge, radix;
	
	cout << "Input 501, 502, ...( type 0 to Quit ) : " << endl; 
    cin >> filename; // ask for file name
    code = filename;
    if ( filename == "0" ) { // user can quit this mission by typing 0
        return;
	} // if()
    
    filename = "input" + filename + ".txt";
    reader.open( filename.c_str() ); // open file
    
    while ( ! reader.is_open() ) { // checking if the file is open 
       		                       // if don't ask user to try again
    	cout << "### " + filename + " does not exist! ###";
    	cout << "Input 501, 502, ...( type 0 to Quit ) : " << endl;
    	cin >> filename;
    	code = filename;
    	if ( filename == "0" ){
    		return;
    	} // if()
        
    	filename = "input" + filename + ".txt";
       	reader.open( filename.c_str() );
        
	} // while()
    // input file open success
    vector< Data > datas, mergesort;
    readfile(datas, reader);
    reader.close();
    bubble.input_file(datas);
    select.input_file(datas);
 	quick.input_file(datas);
	merge.input_file(datas);
	radix.input_file(datas);   
    
    
    
    Type time;
    DWORD starttime = GetTickCount();
    bubble.bubble_sort();
    DWORD endtime = GetTickCount();
    time.bubble = endtime - starttime;
    
    starttime = GetTickCount();
	select.selection_sort();
	endtime = GetTickCount();
	time.selection = endtime - starttime;
	
	starttime = GetTickCount();
	quick.quick_sort(0, datas.size() -1);
	endtime = GetTickCount();
	time.quick = endtime - starttime;
	
	starttime = GetTickCount();
	merge.merge_sort(datas);
	endtime = GetTickCount();
	time.merge = endtime - starttime;
	
	starttime = GetTickCount();
	radix.radix_sort();
    endtime = GetTickCount();
    time.radix = endtime - starttime;
    
    
    ofstream writer;
    vector<string> temp;
    string s;
    
    reader.open("sort_time.txt");
    if( !reader.is_open() ){	
	    writer.open("sort_time.txt");
    	writer << "\t" << "select sort" << " bubble sort" << " quick sort" << " merge sort" << " radix sort\n";
	    writer << code << "\t" << time.selection << "\t" << time.bubble << "\t" << time.quick << "\t" << time.merge << "\t" << time.radix << "\n";
	} // 初次寫檔案 
	else{
		while(!reader.eof()){
			getline(reader, s);
			temp.push_back(s);
		}
		
		writer.open("sort_time.txt");
		for(int i = 0 ; i < temp.size() ; i++ )
			writer << temp[i] << "\n";
		writer << code << "\t" << time.selection << "\t" << time.bubble << "\t" << time.quick << "\t" << time.merge << "\t" << time.radix << "\n";
		
	}
}


void startGen(){
	cout << "******** Sorting Algorithms *********\n";
	cout << "* 0. QUIT                           *\n";
	cout << "* 1. Selection sort vs. Bubble sort *\n";
	cout << "* 2. Merge sort vs. Quick sort      *\n";
	cout << "* 3. Radix sort                     *\n";
	cout << "* 4. Comparisons on five methods    *\n";
	cout << "*************************************\n";
	cout << "Input a choice(0, 1, 2, 3, 4):";
}

int main(){
	string command;
	int operation;
	bool end = false;
	while ( ! end ) {
		startGen(); // generate the starting article for users to check
		cin >> command;
		operation = atoi(command.c_str());
		// do different things based on user command
		switch(operation){
			case 1:
				mission1();
				break;
			case 2:
				mission2();
				break;
			case 3:
				mission3();
				break;
			case 4:
				mission4();
				break;
			case 0:
				end = true;
				break;
			default: 
				cout << "Command does not exist!" << "\n"; // 防呆 
				break;
		}
	} // while()
	cout << "quitting !" << "\n";
	
} 
