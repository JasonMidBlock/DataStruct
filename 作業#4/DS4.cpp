// 11027240 �\�i�a  11027241 ������ 
# include <iostream>
# include <fstream>
# include <stdlib.h>
# include <string.h>
# include <cmath>
# include <vector>
# include <windows.h>
using namespace std;

struct Order{ 
	int OID;  // �q��s�� 
	int Arrival;  // �U��ɶ� 
	int Duration;  // �Ӯ� 
	int Timeout;  // ���~�h�[ 
};

struct Timeout_Order {	
	int OID;         // �q��s�� 
	int Delay;      // ���~�ɶ� 
	int Departure; // �����ɨ� 
};


struct Abort_Order{
	int OID;      // �q��s�� 
	int Delay;  // ���~�ɶ�
	int Abort; // �����ɨ� 
};

struct CAbort_Order {
	
	int OID;      // �q��s�� 
	int CID;     // �p�v�s�� 
	int Delay;  // ���~�ɶ� 
	int Abort; // �����ɨ� 
	
};

struct CTimeout_Order {
	
	int OID;          // �q��s�� 
	int CID;         // �p�v�s�� 
	int Delay;      // ���~�ɶ� 
	int Departure; // �����ɨ� 
};


class chefqueue{
	public:
		void push( Order data ) {
			if ( orders.size() != 4 )
		    	orders.push_back( data );
		    
		} // push
		
		Order pop() {
			Order out;
			if ( orders.empty() ) {
				cout << "can't pop when empty!";
				return out;
			} // if()
			
			out = orders[0];
			orders.erase( orders.begin() );
			return out;
		} // pop
		
		bool isEmpty() {
			if ( orders.size() == 0 )
			    return true;
			return false;
		} // isEmpty
		
		bool isFull() {
			if ( orders.size() == 4 )
			    return true;
			return false;
			
		} // isFull
		
		int gettime() {
			return time;
		} // gettime
		
		void settime( int times ) {
			time = times ;
		} // settime
		
		int ordercount() {
			return orders.size();
		} // ordercount

		int processorder() {
		    
		    if ( time >= orders[0].Timeout )
		        return 1;
		    else if ( time + orders[0].Duration > orders[0].Timeout )
		        return 2;

			// ���q��S��Timeout�BAbort���ܴNpop�B��s���m�ɶ�
		    time += orders[0].Duration;
		    pop();
		    return 0;
			    
		} // processorder
		
		bool complement(int order_arrive){
			if (order_arrive >= time + orders[0].Duration )
				return true;
				
			return false;
		}
		
		Order peek(){
			return orders[0];
		}
		
	private:
		int chef_num;
		int time;
		vector<Order> orders;
		
};


class Kitchen{
	
	private:
		vector<chef> chefs;
};
void writefile( string filename, vector<Order> orders );
vector<Order> shellsort( vector<Order> orders );
vector<Order> in_to_vec( string filename ) ;
void writefile_to_one(vector<Abort_Order> abort_list, vector<Timeout_Order> timeout_list, string filename, int orders) ;
void startGen();


void mission1(){
	ifstream ifs;
	string filename;
	vector<Order> orders;
	do {  
    	cout << "Input 201, 202, ...( type 0 to Quit ) : ";
    	cin >> filename;
    	cin.get(); // read the '\n'
    	if ( filename == "0" ) {
    		return;
       	} // if()
        
    	filename = "input" + filename + ".txt";
        ifs.open( filename.c_str() ); // try to open file
        
        if ( ! ifs.is_open() )
            cout << "### " + filename + " does not exist! ###";
        
	} while ( ! ifs.is_open() ); // checking if the file is open
	
	
	chefqueue one;
	DWORD starttime = GetTickCount();
    orders = in_to_vec( filename ); // read data into vector of Order form
    DWORD endtime = GetTickCount();
    cout << "Reading data : " << ( endtime - starttime ) << " ms" << endl;
	
	starttime = GetTickCount();
    orders = shellsort( orders ); // do shellsort
    endtime = GetTickCount();
    cout << "Sorting data : " << ( endtime - starttime ) << " ms" << endl;
	
	filename = "sort" + filename.substr(5); // name of copied file
    starttime = GetTickCount();
    writefile( filename, orders ); // write into new file
    endtime = GetTickCount();
    cout << "Writing data : " << ( endtime - starttime ) << " ms" << endl;
}


void mission2(){
	vector<Order> order_list;
	vector<Abort_Order> abort_list;
	Abort_Order abort;
	vector<Timeout_Order> timeout_list;
	Timeout_Order timeout;
	ifstream reader;
    string filename, s;
    
    int states = 0;
    do {  
    	cout << "Input 201, 202, ...( type 0 to Quit ) : " << endl;
    	cin >> filename;
    	cin.get(); // read the '\n'
    	if ( filename == "0" ) {
    		return;
       	} // if()
        
    	filename = "sort" + filename + ".txt";
        reader.open( filename.c_str() ); // try to open file
        
        if ( ! reader.is_open() )
            cout << "### " + filename + " does not exist! ###";
        
	} while ( ! reader.is_open() ); // checking if the file is open
	 
	 chefqueue one;
	 Order now, done;
	 int orders = 0;
	 getline(reader, s);
	// time is start
	 while(!reader.eof()){
	 	reader >> now.OID >> now.Arrival >> now.Duration >> now.Timeout;
	 	orders++;
	 	while( one.gettime() > now.Arrival && !reader.eof() ) {
			abort.OID = now.OID;
         	abort.Delay = one.gettime() - now.Arrival;
			abort.Abort = one.gettime();
			abort_list.push_back( abort );
			reader >> now.OID >> now.Arrival >> now.Duration >> now.Timeout;
			orders++;
		} // while
		
		if(one.isEmpty()){
			one.settime(now.Arrival);
		}
		
		
		if ( one.isFull() ){ 
			if ( !one.complement(now.Arrival) ) {  // �p�G�q���F���ɶ��S�W�L�{�b�q�槹�����ɶ�
				abort.OID = now.OID;        // �N�q���Jabort_list�� 
         		abort.Delay = 0;
				abort.Abort = now.Arrival;
				abort_list.push_back( abort );
			}
			else{ // �p�G�q���F���ɶ��W�L�{�b�q�槹�����ɶ� 
				done = one.pop();
				one.settime( one.gettime() + done.Duration);
				if ( one.gettime() > done.Timeout ){
					timeout.OID = done.OID;
					timeout.Delay = one.gettime() - done.Timeout;
					timeout.Departure = done.Arrival + done.Duration + timeout.Delay;
					timeout_list.push_back(timeout);
				}
				// �B�z�s�@�������q��^^^
				
				while( !one.isEmpty() && one.peek().Timeout < one.gettime() ){
					done = one.pop();
					abort.OID = done.OID;        // �N�q���Jabort_list�� 
         			abort.Delay = one.gettime() - ( done.Arrival + done.Duration );
					abort.Abort = one.gettime();
					abort_list.push_back( abort );
				} // while
				
				one.push(now);
				// �B�z�J�C�����q��^^^ 
			}
		}
		else
			one.push(now);
	 }
	 
	 while( !one.isEmpty()){
	 	done = one.pop();
	 	if ( one.gettime() > done.Timeout ) {
			abort.OID = done.OID;        // �N�q���Jabort_list�� 
        	abort.Delay = one.gettime() - done.Arrival;
			abort.Abort = one.gettime();
			abort_list.push_back( abort );
		}
		else {
			one.settime( one.gettime() + done.Duration); // �N�q�氵��
			if ( one.gettime() > done.Timeout ) {
				timeout.OID = done.OID ;
				timeout.Delay = one.gettime() - ( done.Arrival + done.Duration );
				timeout.Departure = done.Arrival + done.Duration + timeout.Delay;
				timeout_list.push_back(timeout);
			} 
		}
	} // while // �B�z�J�C�����q��^^^

		
	 /*
	 while(!reader.eof()){
	 	reader >> now.OID >> now.Arrival >> now.Duration >> now.Timeout;
	 	orders ++ ;
		while( now.Arrival >= one.gettime() && ! one.isEmpty() ){
			states = one.processorder();
			if ( states == 1 ) { // �J�C���X�ɹO�� write into abort list
			    done = one.pop();
				abort.OID = done.OID;
         	    abort.Delay = one.gettime() - done.Arrival;
				abort.Abort = one.gettime();
				abort_list.push_back( abort );
			} // if()
			else if ( states == 2 ) { // �����ɹO�� write into departure list
				done = one.pop();
				timeout.OID = done.OID;
				timeout.Delay = one.gettime() - done.Arrival;
				timeout.Departure = done.Arrival + timeout.Delay + done.Duration;
				timeout_list.push_back( timeout );
				one.settime( one.gettime() + done.Duration );
			} // else if()
		} // while ^^^ �J�C�D�Ū��ɭԳB�z 
		
		if ( one.isEmpty() && now.Arrival >= one.gettime() ) { // �J�C���� ��s���m�ɶ�(�����T�w���m�ɶ� <= �U��ɨ�)  
			one.settime( now.Arrival );
		}
		
		// �w�S�����m�p�v(�μp�v�������m) �N�q���J�J�C ^^^
		
		if(one.isFull()){
			abort.OID = now.OID;
			abort.Delay = 0;
			abort.Abort = now.Arrival;
			abort_list.push_back(abort);
		}
		else {
			one.push(now);
		}
	}
	

	while( !one.isEmpty() ) {
		states = one.processorder();
		if ( states == 1 ) { // �J�C���X�ɹO�� write into abort list
			done = one.pop();
			abort.OID = done.OID;
            abort.Delay = one.gettime() - done.Arrival;
			abort.Abort = one.gettime();
			abort_list.push_back( abort );
		} // if()
		else if ( states == 2 ) { // �����ɹO�� write into departure list
			done = one.pop();
			timeout.OID = done.OID;
			timeout.Delay = one.gettime() - done.Arrival;
			timeout.Departure = done.Arrival + timeout.Delay + done.Duration;
			timeout_list.push_back( timeout );
			one.settime( one.gettime() + done.Duration );
		} // else if()
	}
	*/
	// �B�z�J�C�����q�� ^^^
	filename = "one" + filename.substr(4);
	writefile_to_one(abort_list, timeout_list, filename, orders); // writeone( filename, Abort_list, Timeout_list, ordercount );

}



void mission3(){
	Order now, done;
	
	chef one, two;
	
	vector<Order> order_list;
	vector<Abort_Order> abort_list;
	Abort_Order abort;
	vector<Timeout_Order> timeout_list;
	Timeout_Order timeout;
	ifstream reader;
    string filename, s;
    
    do {  
    	cout << "Input 201, 202, ...( type 0 to Quit ) : " << endl;
    	cin >> filename;
    	cin.get(); // read the '\n'
    	if ( filename == "0" ) {
    		return;
       	} // if()
        
    	filename = "one" + filename + ".txt";
        reader.open( filename.c_str() ); // try to open file
        
        if ( ! reader.is_open() )
            cout << "### " + filename + " does not exist! ###";
        
	} while ( ! reader.is_open() ); // checking if the file is open
	
	while( !reader.eof() ) {
		reader >> now.OID >> now.Arrival >> now.Duration >> now.Timeout;
		orders++;
		while( one.gettime() > now.Arrival && two.gettime() > now.Arrival && !reader.eof() ) {
			abort.OID = now.OID;
         	abort.Delay = one.gettime() - now.Arrival;
			abort.Abort = one.gettime();
			abort_list.push_back( abort );
			reader >> now.OID >> now.Arrival >> now.Duration >> now.Timeout;
			orders++;
		} // while
		
		if(one.isEmpty()){ // case 1
			one.settime(now.Arrival);
			one.push(now);
		}
			
		else if( two.isEmpty() ){  // case2
			two.settime(now.Arrival);
			two.push(now);
		}
			
		else{ // ��Ӽp�v���ëD�Ŷ� 
			if ( one.ordercount() < two.ordercount()) 
				one.push(now);
			
			else if(one.ordercount() > two.ordercount())
				two.push(now);
			else{ // one.ordercount() == two.ordercount()
				if( one.isFull() && two.isFull() ){
					
				} // �ˬd���p�v���b�����������S����k����
				else{
					one.push(now);
				} 
			}
			
		}
		
	}
	
	
}




int main(){
	 
    cout << "\n";
    char command[100] = "\0";
	while ( command[0] != '0' ) {
		
		startGen(); // generate the starting article for users to check
		cout << "input a choice : ";
		cin.getline( command, 100 ); // read in user command
		cout << "\n";
		
		// do different things based on user command
		if ( command[0] == '1' ) { 
			mission1(); 
		} // if()
		else if ( command[0] == '2' ) {
			mission2();
		} // else if()
		else if ( command[0] == '3' ) {
			mission3();
		} // else if()
		else if ( command[0] != '0' ){
			cout << "Command does not exist!" << "\n"; // ���b 
		}
		
	} // while()
	
	cout << "quitting !" << "\n";
	
}


vector<Order> shellsort( vector<Order> orders ) {
	
	for ( int steplen = orders.size() ; steplen >= 1 ; steplen = steplen / 2 ) {
		for ( int times = 1 ; times * steplen < orders.size() ; times ++ ) {
		    for ( int i = times * steplen ; i < orders.size() ; i ++ ) {
			    if ( orders[i].Arrival < orders[i - steplen].Arrival ) {
	                swap( orders[i], orders[i - steplen]);
	            } // if()
	            else if ( orders[i].Arrival == orders[i - steplen].Arrival ) { // same Arrival time 
	            	if ( orders[i].OID < orders[i - steplen].OID )            // check OID 
	            	    swap( orders[i], orders[i - steplen]);
				}
	        
	        } // for()
	    } // for()
	
	
	} // for 
	
	return orders;
	
} // shellsort


void writefile( string filename, vector<Order> orders ) {
	
	ofstream writer;
	writer.open( filename.c_str() ); // start writing data into sort file 
	writer << "OID\tArrival\tDuration\tTimeOut\n";
	for ( int i = 0 ; i < orders.size() ; i ++ ) {
		writer << orders[i].OID << '\t' << orders[i].Arrival << '\t' << orders[i].Duration << '\t' << orders[i].Timeout;  
		if ( i != orders.size() - 1 )
		    writer << endl;
	} // for
	writer.close();
	

} // writefile

vector<Order> in_to_vec( string filename ) {

	ifstream reader;
	reader.open( filename.c_str() );
	vector<Order> out;
	Order order;
	bool find = false;
	char tmp[100];
	reader.getline( tmp ,sizeof(tmp) ); // clean the letter
	
	while ( ! reader.eof() ) {
	    reader >> order.OID >> order.Arrival >> order.Duration >> order.Timeout; // get whole line
	    for ( int i =0 ; i < out.size() ; i++ ){
	    	if ( out[i].OID == order.OID )
	    		find = true;
		}
		if ( !find )
	    	out.push_back( order ); // insert data
	    find = false;
    } // while()
    
    return out;
	
} // in_to_vec


void writefile_to_one(vector<Abort_Order> abort_list, vector<Timeout_Order> timeout_list, string filename, int orders) {
	ofstream writer;
	writer.open(filename.c_str());
	writer << "\t[ Abort list ]\n";
	writer << "\tOID\t" << "Delay\t" << "Abort\n";
	int total_delay;
	for(int i = 0 ; i < abort_list.size() ; i ++) {
		writer << "[" << i+1 << "]\t" << abort_list[i].OID << "\t" << abort_list[i].Delay <<  "\t" << abort_list[i].Abort << "\n";
		total_delay += abort_list[i].Delay;
	}
	writer << "\n";	
	
	
	writer << "\t[ Timeout list ]\n";
	writer << "\tOID\t" << "Delay\t" << "Departure\n";
	for(int i = 0 ; i < timeout_list.size() ; i ++) {
		writer << "[" << i+1 << "]\t" << timeout_list[i].OID << "\t" << timeout_list[i].Delay <<  "\t" << timeout_list[i].Departure << "\n";
		total_delay += timeout_list[i].Delay;
	}
	writer << "\n";
	
	writer << "\t[ Total Delay ]\n";
	writer << total_delay << "  min\n";
	
	float present = ((float)( abort_list.size() + timeout_list.size() ) / (float)orders ) * 100 ;
	present = round(present * 100 ) / 100;
	writer << "\t[Failure Pecentage]\n";
	writer << "\t" << present << "%\n\n";
	writer.close();	 
}

void startGen() {
	cout << "* Kitchen simulator *" << endl;
    cout << "* 0. QUIT                         *" << endl;
    cout << "* 1. Sort orders                  *" << endl;
    cout << "* 2. Kitchen with one chef        *" << endl;
    cout << "* 3. Kitchen with two chefs       *" << endl;
    cout << "***********************************" << endl;
} // startGen
