# include <iostream>
# include <fstream>
# include <stdlib.h>
# include <string.h>
# include <vector>
# include <windows.h>

// 11027240_11027241 DS第四次作業 
using namespace std;

const int INVALID_NAME = 912464;
const int SUCCESS = 823123;
const int FAIL = 123741;
const int ABORT = 723745;
const int DEPARTURE = 782351;
const int DONE_PROCESS = 155498;
const int BAD_ARRIVAL = 984751;

struct Order {
	
	int OID;         // 訂單編號 
	int Arrival;    // 下單時刻 
	int Duration;  // 製作耗時
	int Timeout;  // 逾時時刻 
	
};

struct Abort_Order {
	
	int OID;     // 訂單編號 
	int Delay;  // 延誤時間 
	int Abort; // 取消時刻 
	
};

struct Timeout_Order {
	
	int OID;         // 訂單編號 
	int Delay;      // 延誤時間 
	int Departure; // 完成時刻 
};

struct CAbort_Order {
	
	int OID;      // 訂單編號 
	int CID;     // 廚師編號 
	int Delay;  // 延誤時間 
	int Abort; // 取消時刻 
	
};

struct CTimeout_Order {
	
	int OID;          // 訂單編號 
	int CID;         // 廚師編號 
	int Delay;      // 延誤時間 
	int Departure; // 完成時刻 
};
void startGen();
vector<Order> in_to_vec( string filename );
vector<Order> shellsort( vector<Order> orders );
void writefile( string filename, vector<Abort_Order> Abort_list, vector<Timeout_Order> Timeout_list, int ordercount );
void mission1();
void writeone();
void mission2();
void mission3();

class chefqueue {
	public:
		chefqueue(){
			orders.clear();
			orders.reserve( 3 );
			idletime = 0;
		} // chefqueue
		
		chefqueue( int chef_num ) {
			orders.clear();
			orders.reserve( 3 );
			idletime = 0;
			chefnum = chef_num;
		} // chefqueue
		
		int push( Order data ) {
			if ( orders.size() == 3 )
			    return FAIL;
			    
		    orders.push_back( data );
		    return SUCCESS;
		    
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
		
		int processorder() { // process an order from chef , when failed return failed type and do nothing
			if ( orders.empty() ) { // debug info( assumed i don't call this func. when empty )
			    cout << "No order now when" << idletime << endl;
			    return -1;
		    } // if()
		    
		    if ( idletime >= orders[0].Timeout )
		        return ABORT;
		    else if ( idletime + orders[0].Duration > orders[0].Timeout )
		        return DEPARTURE;

		    idletime += orders[0].Duration;
		    pop();
		    return 0;
			    
		} // processorder
		
		bool isEmpty() {
			if ( orders.size() == 0 )
			    return true;
			return false;
		} // isEmpty
		
		bool isFull() {
			
			if ( orders.size() == 3 )
			    return true;
			return false;
			
		} // isFull
		
		int getidle() {
			return idletime;
		} // getidle
		
		void setidle( int order_arrival ) {
			idletime = order_arrival;
		} // setidle
		
		int ordercount() {
			return orders.size();
		} // ordercount
		
		int getchefnum() {
			return chefnum;
		} // getchefnum
		
	private:
		vector<Order> orders;
		int idletime;
		int chefnum;
};

class Kitchen{
	public:
		Kitchen( int chefcount ) {
			cheflist.reserve( chefcount );
			for ( int i = 1 ; i <= chefcount ; i ++ ) {
				chefqueue tmp(i);
				cheflist.push_back( tmp );
			} // for()
		} // kitchen
		
		bool FullOrder() {
			for ( int i = 0 ; i < cheflist.size() ; i ++ ) {
				if ( ! cheflist[i].isFull() )
				    return false;
			} // for()
			
			return true;
			
		} // FullOrder
		
		bool Allidle() {
			for ( int i = 0 ; i < cheflist.size() ; i ++ ) {
			    if ( ! cheflist[i].isEmpty() )
			        return false;
			} // for() 
			
			return true; 
		} // Allidle
		
		int getidle( int chefnum ) {
			return cheflist[chefnum - 1].getidle();
		} // getidle
		
		void setidle( int chefnum, int idle_time ) {
			cheflist[chefnum - 1].setidle( idle_time );
		} // setidle
		
		int findchef( int arrival_time ) { // find chef by SQF and return its chefnum 找訂單該給誰 
			int minorder = 3;             
			int returnnum = -1;
			
			for ( int i = 0 ; i < cheflist.size() ; i ++ ) { // 先找閒置廚師 
			    if ( cheflist[i].ordercount() == 0 && arrival_time >= cheflist[i].getidle() ) {
			    	return cheflist[i].getchefnum();
				} // if()
				
			} // for()
			
			for ( int i = 0 ; i < cheflist.size() ; i ++ ) { // 沒有閒置的廚師  找最小貯列 
				if ( cheflist[i].ordercount() < minorder ) {
					minorder = cheflist[i].ordercount();
					returnnum = cheflist[i].getchefnum();
				} // if
				
			} // for()
			
			if ( minorder == 3 ) // 貯列全滿 
			    return ABORT;
			return returnnum;
		} // findchef
		
		void giveorder( int chef_num, Order order ) { // assume i always give order when the queue isn't full
			cheflist[chef_num - 1].push( order );
		} // giveorder
		
		int leastidle_order() { // find the least idle time chef with order of cheflist and return its chefnum
			int leastidle = 99999999;
			int chef_num = FAIL;
			for ( int i = 0 ; i < cheflist.size() ; i ++ ) {
				if ( cheflist[i].getidle() < leastidle && ! cheflist[i].isEmpty() ) {
					leastidle = cheflist[i].getidle();
					chef_num = cheflist[i].getchefnum();
				} // if()
				
			} // for()
			
			return chef_num;
			
		} // leastidle
		
		void update_idle( int arrival_time ) {
			for ( int i = 0 ; i < cheflist.size() ; i ++ ) {
				if ( cheflist[i].isEmpty() && arrival_time >= cheflist[i].getidle() ) { // 貯列為空 更新閒置時間(必須確定閒置時間 <= 下單時刻)  
			        cheflist[i].setidle( arrival_time );
		        } // if()
				
			} // for()
			
		} // update_idle
		
		int processchef( int arrival_time, int chefnum ) { // assume not empty when this func. call
			if ( arrival_time < cheflist[chefnum - 1].getidle() )
			    return BAD_ARRIVAL;
			else {
				return cheflist[chefnum - 1].processorder();
			} // else
		} // processchef
		
		Order popfrom( int chefnum ) {
			return cheflist[chefnum - 1].pop();
		} // popfrom
		
	private:
		vector<chefqueue> cheflist;
	
};

int main(int argc, char** argv) {
    
    cout << endl;
    char command[100] = "\0";
	while ( command[0] != '0' ) {
		
		startGen(); // generate the starting article for users to check
		cout << "input a choice : ";
		cin.getline( command, 100 ); // read in user command
		cout << endl;
		
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
			cout << "Command does not exist!" << endl; // 防呆 
		}
		
	} // while()
	
	cout << "quitting !" << endl;
	
	return 0;
    
    
} // main  

vector<Order> in_to_vec( string filename ) {
    // change data in file into vector of order 
	ifstream reader;
	reader.open( filename.c_str() );
	vector<Order> out;
	Order order;
	
	char tmp[100];
	reader.getline( tmp ,sizeof(tmp) ); // clean the letter
	
	while ( ! reader.eof() ) {
	
	    reader >> order.OID >> order.Arrival >> order.Duration >> order.Timeout; // get whole line
	    if ( out.empty() || order.OID != out.back().OID )
	        out.push_back( order ); // insert data
	    
    } // while()
    
    return out;
	
} // in_to_vec

vector<Order> shellsort( vector<Order> orders ) {
	
	for ( int steplen = orders.size() / 2 ; steplen >= 1 ; steplen = steplen / 2 ) {
		for(int i = 0 ; i < orders.size(); i++ )
			cout << orders[i].OID << " " << orders[i].Arrival << " " << orders[i].Timeout << "\n";
		for ( int start = steplen ; start < orders.size() ; start ++ ) {
		    for ( int now = start ; now >= steplen ; now -= steplen ) {
			    if ( orders[now].Arrival < orders[now - steplen].Arrival ) {
	                swap( orders[now], orders[now - steplen]);
	            } // if()
	            else if ( orders[now].Arrival == orders[now - steplen].Arrival ) { // same Arrival time 
	            	if ( orders[now].OID < orders[now - steplen].OID ) {            // check OID 
	            	    swap( orders[now], orders[now - steplen]);
	            	} // if()
				}
				else {
					break;
				} // else
	        
	        } // for()
	    } // for()
		cout << "\n";
	
	} // for 
	
	return orders;
	
} // shellsort

void writefile( string filename, vector<Order> orders ) {
	// 將排序好的資料寫入檔案 
	ofstream writer;
	writer.open( filename.c_str() ); // start writing data into sort file 
	writer << "OID\tArrival\tDuration\tTimeOut" << endl;
	for ( int i = 0 ; i < orders.size() ; i ++ ) {
		writer << orders[i].OID << '\t' << orders[i].Arrival << '\t' << orders[i].Duration << '\t' << orders[i].Timeout;  
		if ( i != orders.size() - 1 )
		    writer << endl;
	} // for
	writer.close();
	
} // writefile

void mission1() {
	
	ifstream reader;
    
    vector<Order> orders;
    string filename;
    
    do {  
    	cout << "Input 201, 202, ...( type 0 to Quit ) : " << endl;
    	cin >> filename;
    	cin.get(); // read the '\n'
    	if ( filename == "0" ) {
    		return;
       	} // if()
        
    	filename = "input" + filename + ".txt";
        reader.open( filename.c_str() ); // try to open file
        
        if ( ! reader.is_open() )
            cout << "### " + filename + " does not exist! ###";
        
	} while ( ! reader.is_open() ); // checking if the file is open
	
	reader.close();
	
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
    
};

void writeone( string filename, vector<Abort_Order> Abort_list, vector<Timeout_Order> Timeout_list, int ordercount ) {
	// 將Abortlist,timeoutlist寫入檔案
	int delaytime = 0;
	float failed = 0;
	ofstream writer;
	writer.open( filename.c_str() );
	writer << '\t' << "[Abort List]" << endl;
	writer << '\t' << "OID" << '\t' << "Delay" << '\t' << "Abort" << endl;
	
	for ( int i = 0 ; i < Abort_list.size() ; i ++ ) {
		failed ++;
		delaytime += Abort_list[i].Delay;
	    writer << '[' << i + 1 << ']' << '\t' << Abort_list[i].OID << '\t' << Abort_list[i].Delay << '\t' << Abort_list[i].Abort << endl;
	} // for 
	
	writer << '\t' << "[Timeout List]" << endl;
	writer << '\t' << "OID" << '\t' << "Delay" << '\t' << "Departure" << endl;
	for ( int i = 0 ; i < Timeout_list.size() ; i ++ ) {
		failed ++;
		delaytime += Timeout_list[i].Delay;
	    writer << '[' << i + 1 << ']' << '\t' << Timeout_list[i].OID << '\t' << Timeout_list[i].Delay << '\t' << Timeout_list[i].Departure << endl;
	} // for 
	
	writer << "[Total Delay]" << endl;
	writer << delaytime << "min." << endl;
	int change = ( failed / ordercount ) * 10000;
	int one = ( failed / ordercount ) * 100000;
	int two = ( failed / ordercount ) * 10000;
	two = two * 10;
	if ( one - two >= 5 )   // 四捨五入 
	    change += 1;
	failed = (float)change / 100;
	writer << "[Failure Pecentage]" << endl;
	writer << failed << "%";
	writer.close();
	
} // writeone

void writetwo( string filename, vector<CAbort_Order> Abort_list, vector<CTimeout_Order> Timeout_list, int ordercount ) {
	// 將Abortlist,timeoutlist寫入檔案 
	int delaytime = 0;
	float failed = 0;
	ofstream writer;
	writer.open( filename.c_str() );
	writer << '\t' << "[Abort List]" << endl;
	writer << '\t' << "OID" << '\t' << "CID" << '\t' << "Delay" << '\t' << "Abort" << endl;
	
	for ( int i = 0 ; i < Abort_list.size() ; i ++ ) {
		failed ++;
		delaytime += Abort_list[i].Delay;
	    writer << '[' << i + 1 << ']' << '\t' << Abort_list[i].OID << '\t' << Abort_list[i].CID << '\t' << Abort_list[i].Delay << '\t' << Abort_list[i].Abort << endl;
	} // for 
	
	writer << '\t' << "[Timeout List]" << endl;
	writer << '\t' << "OID" << '\t' << "CID" << '\t' << "Delay" << '\t' << "Departure" << endl;
	for ( int i = 0 ; i < Timeout_list.size() ; i ++ ) {
		failed ++;
		delaytime += Timeout_list[i].Delay;
	    writer << '[' << i + 1 << ']' << '\t' << Timeout_list[i].OID << '\t' << Timeout_list[i].CID << '\t' << Timeout_list[i].Delay << '\t' << Timeout_list[i].Departure << endl;
	} // for 
	
	writer << "[Total Delay]" << endl;
	writer << delaytime << "min." << endl;
	int change = ( failed / ordercount ) * 10000;
	int one = ( failed / ordercount ) * 100000;
	int two = ( failed / ordercount ) * 10000;
	two = two * 10;
	if ( one - two >= 5 )   // 四捨五入 
	    change += 1;
	failed = (float)change / 100;
	writer << "[Failure Pecentage]" << endl;
	writer << failed << "%";
	writer.close();
	
} // writetwo

void mission2() {
	ifstream reader;
    string filename;
    Order ordernow;
    Order badorder;
    
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
	 
	// filename checked
	vector<Order> order_list;
	vector<Abort_Order> Abort_list;
	Abort_Order abort_order;
	vector<Timeout_Order> Timeout_list;
	Timeout_Order timeout_order;
	chefqueue chef(1);
	int check = 0, ordercount = 0;
	
	char tmp[100];
	reader.getline( tmp ,sizeof(tmp) ); // clean the letter
	while( ! reader.eof() ) {
		reader >> ordernow.OID >> ordernow.Arrival >> ordernow.Duration >> ordernow.Timeout; // get an order
		ordercount += 1;
		order_list.push_back( ordernow );
	}
	
	for ( int i = 0 ; i < ordercount ; i ++ ) {
		
		ordernow = order_list[i];
		while ( ordernow.Arrival >= chef.getidle() && ! chef.isEmpty() ) { 
		// 有廚師閒置 process閒置廚師的訂單 直到貯列為空或廚師現在非閒置 
			check = chef.processorder();
			if ( check == ABORT ) { // 貯列取出時逾時 write into abort list
			    badorder = chef.pop();
			    abort_order.OID = badorder.OID;
                abort_order.Delay = chef.getidle() - badorder.Arrival;
				abort_order.Abort = chef.getidle();
				Abort_list.push_back( abort_order );
			} // if()
			else if ( check == DEPARTURE ) { // 做完時逾時 write into departure list
				badorder = chef.pop();
				timeout_order.OID = badorder.OID;
				timeout_order.Delay = chef.getidle() - badorder.Arrival;
				timeout_order.Departure = badorder.Arrival + timeout_order.Delay + badorder.Duration;
				Timeout_list.push_back( timeout_order );
				chef.setidle( chef.getidle() + badorder.Duration );
			} // else if()
			
		} // while()
		
		if ( chef.isEmpty() && ordernow.Arrival >= chef.getidle() ) { // 貯列為空 更新閒置時間(必須確定閒置時間 <= 下單時刻)  
			chef.setidle( ordernow.Arrival );
		} // if()
		
		// 已沒有閒置廚師(或廚師全部閒置) 將訂單放入貯列
		check = chef.push( ordernow );
		if ( check == FAIL ) { // 貯列全滿 write into abort list
			abort_order.OID = ordernow.OID;
            abort_order.Delay = 0;
			abort_order.Abort = ordernow.Arrival;
			Abort_list.push_back( abort_order );
		}
		 
	} // for()
	
	while ( ! chef.isEmpty() ) { 
		// 訂單讀取完畢 process訂單 直到貯列為空
			check = chef.processorder();
			if ( check == ABORT ) { // 貯列取出時逾時 write into abort list
			    badorder = chef.pop();
			    abort_order.OID = badorder.OID;
                abort_order.Delay = chef.getidle() - badorder.Arrival;
				abort_order.Abort = chef.getidle();
				Abort_list.push_back( abort_order );
			} // if()
			else if ( check == DEPARTURE ) { // 做完時逾時 write into departure list
				badorder = chef.pop();
				timeout_order.OID = badorder.OID;
				timeout_order.Delay = chef.getidle() - badorder.Arrival;
				timeout_order.Departure = badorder.Arrival + timeout_order.Delay + badorder.Duration;
				Timeout_list.push_back( timeout_order );
				chef.setidle( chef.getidle() + badorder.Duration );
			} // else if()
			
	} // while()
	
	filename = "one" + filename.substr(4); // name of copied file
	writeone( filename, Abort_list, Timeout_list, ordercount );
	
} // mission2

void mission3() {
	ifstream reader;
    string filename;
    Order ordernow;
    Order badorder;
    
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
	 
	// filename checked
	vector<Order> order_list;
	vector<CAbort_Order> Abort_list;
	CAbort_Order abort_order;
	vector<CTimeout_Order> Timeout_list;
	CTimeout_Order timeout_order;
	Kitchen kitchen(2);
	int check = 0, ordercount = 0, chefnum = 0;
	
	char tmp[100];
	reader.getline( tmp ,sizeof(tmp) ); // clean the letter
	while( ! reader.eof() ) {
		reader >> ordernow.OID >> ordernow.Arrival >> ordernow.Duration >> ordernow.Timeout; // get an order
		ordercount += 1;
		order_list.push_back( ordernow );
	}
	
	for ( int i = 0 ; i < ordercount ; i ++ ) {
		
		ordernow = order_list[i];
	    check = 0; // reset the BAD_ARRIVAL ( or other
	
		while ( check != BAD_ARRIVAL ) { 
		// 有廚師閒置 process閒置廚師的訂單 直到貯列全為空或廚師現在全都非閒置 
		    chefnum = kitchen.leastidle_order();
		    
		    if ( chefnum == FAIL ) // 找不到有order的廚師 
		        break;
		    
			check = kitchen.processchef( ordernow.Arrival, chefnum );
			
			if ( check == ABORT ) { // 貯列取出時逾時 write into abort list
			    badorder = kitchen.popfrom( chefnum );
			    abort_order.OID = badorder.OID;
			    abort_order.CID = chefnum;
                abort_order.Delay = kitchen.getidle( chefnum ) - badorder.Arrival;
				abort_order.Abort = kitchen.getidle( chefnum );
				Abort_list.push_back( abort_order );
			} // if()
			else if ( check == DEPARTURE ) { // 做完時逾時 write into departure list
				badorder = kitchen.popfrom( chefnum );
				timeout_order.OID = badorder.OID;
				timeout_order.CID = chefnum;
				timeout_order.Delay = kitchen.getidle( chefnum ) - badorder.Arrival;
				timeout_order.Departure = badorder.Arrival + timeout_order.Delay + badorder.Duration;
				Timeout_list.push_back( timeout_order );
				kitchen.setidle( chefnum, kitchen.getidle( chefnum ) + badorder.Duration );
			} // else if()
			
		} // while()
		
		kitchen.update_idle( ordernow.Arrival ); // 更新貯列為空的廚師閒置時間(必須確定閒置時間 <= 下單時刻)  
	
		// 已沒有閒置廚師(或廚師全部閒置) 將訂單放入貯列
		chefnum = kitchen.findchef( ordernow.Arrival );
		if ( chefnum == ABORT ) { // 貯列全滿 write into abort list
			abort_order.OID = ordernow.OID;
			abort_order.CID = 0;
            abort_order.Delay = 0;
			abort_order.Abort = ordernow.Arrival;
			Abort_list.push_back( abort_order );
		}
		else {
		    kitchen.giveorder( chefnum, ordernow );
	    } // else
	    
	} // while()
	
	while ( ! kitchen.Allidle() ) { 
		// 訂單讀取完畢 process訂單 直到貯列為空
		    chefnum = kitchen.leastidle_order();
		    
			check = kitchen.processchef( 99999999, chefnum );
			if ( check == ABORT ) { // 貯列取出時逾時 write into abort list
			    badorder = kitchen.popfrom( chefnum );
			    abort_order.OID = badorder.OID;
			    abort_order.CID = chefnum;
                abort_order.Delay = kitchen.getidle( chefnum ) - badorder.Arrival;
				abort_order.Abort = kitchen.getidle( chefnum );
				Abort_list.push_back( abort_order );
			} // if()
			else if ( check == DEPARTURE ) { // 做完時逾時 write into departure list
				badorder = kitchen.popfrom( chefnum );
				timeout_order.OID = badorder.OID;
				timeout_order.CID = chefnum;
				timeout_order.Delay = kitchen.getidle( chefnum ) - badorder.Arrival;
				timeout_order.Departure = badorder.Arrival + timeout_order.Delay + badorder.Duration;
				Timeout_list.push_back( timeout_order );
				kitchen.setidle( chefnum, kitchen.getidle( chefnum ) + badorder.Duration );
			} // else if()
			
	} // while()
	//
	filename = "two" + filename.substr(4); // name of copied file
	writetwo( filename, Abort_list, Timeout_list, ordercount );
} // mission3

void startGen() {
	cout << "**** Simulate FIFO Queues by SQF *****" << endl;
    cout << "* 0. Quit                            *" << endl;
    cout << "* 1. Sort a file                     *" << endl;
    cout << "* 2. Simulate one FIFO queue         *" << endl;
    cout << "* 3. Simulate two queues by SQF      *" << endl;
    cout << "**************************************" << endl;
} // startGen

