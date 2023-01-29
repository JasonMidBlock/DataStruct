# include <iostream>
# include <vector>
# include <fstream>
# include <string.h>
# include <iomanip> // setw

using namespace std;

// 11027240許展榮 11027241楊昀祖

struct intset {
	int visits;
	int printed;
};

struct poke { // pokemon
    int no;        // 編號 
	string name;
	string type1;
	string type2;
	int total;
	int hp;
	int atk;
	int def;
	int spatk;
	int spdef;
	int spd; 
	int gen;      // 世代 
	bool legend; // 傳奇 
	
};

struct data{
	int HP;
	vector<int> no;
};

struct pokenode { // pokemon node
    pokenode( int no ) {
    	left = NULL;
    	right = NULL;
    	nos.push_back( no );
	}
	vector<int> nos; // 編號
	pokenode *left;
	pokenode *right;
};

class poketree { // pokemontree
    public:
    	
    	poketree() {	
    	    treetop = NULL;
		} // poketree()
		
		void inputdata( string filename ) {
			origindata.clear();
			ifstream reader;
			reader.open( filename.c_str() );
			string tmpstr;
			getline( reader,tmpstr ); // 吃掉第一行
			poke apoke;
			while ( ! reader.eof() ) {
			    reader >> apoke.no;
				reader.get(); // get the '\t'
				getline( reader, apoke.name, '\t' );
				reader >> apoke.type1;
				reader.get(); // get the '\t'
				getline( reader, apoke.type2, '\t' );
				reader >> apoke.total;
				reader >> apoke.hp;
				reader >> apoke.atk;
				reader >> apoke.def;
				reader >> apoke.spatk;
				reader >> apoke.spdef;
				reader >> apoke.spd;
				reader >> apoke.gen;
				reader >> tmpstr;
				if ( strcmp( tmpstr.c_str(), "FALSE" ) == 0 )
				    apoke.legend = false;
				else
				    apoke.legend = true; 
				    
				reader.get(); // get the '\n';
				if( ! reader.eof() )
				    origindata.push_back(apoke);

		    } // while()
			 
		} // inputdata()
		
		void buildtree() {
			
			treetop = NULL;
			for ( int i = 0 ; i < origindata.size() ; i ++ ) {
				insertanode( origindata[i] );
			} // for()
			
		} // buildtree
		
		void insertanode( poke nodedata ) {
			if ( treetop == NULL ) { // special case : no data on tree now
			    treetop = new pokenode( nodedata.no );
			} // if()
			else {
				tmpuse = treetop; // reset tmpuse to the top
				while ( 1 ) {
					if ( nodedata.hp > origindata[findorigin(tmpuse -> nos[0])].hp ) { // 輸入的寶可夢hp較此節點大(向右 
						if ( tmpuse -> right == NULL ) {                    // no bigger data
							tmpuse -> right = new pokenode( nodedata.no ); // gen new node 
							return;                                    // go out from loop
						}
						
						tmpuse = tmpuse -> right;
						
					} // if()
					else if ( nodedata.hp < origindata[findorigin(tmpuse -> nos[0])].hp ) { // 輸入的寶可夢hp較此節點小(向左 
						if ( tmpuse -> left == NULL ) {                    // no smaller data
							tmpuse -> left = new pokenode( nodedata.no ); // gen new node 
							return;                                   // go out from loop
						}
						
						tmpuse = tmpuse -> left;
						
					} // else if()
					else { // hp相等! 
						tmpuse -> nos.push_back( nodedata.no ); // 存入hp至節點 
						return;
					} // else
					
				}
			}
		} // insertnode
		
		int findorigin( int no ) {
			for ( int i = 0 ; i < origindata.size() ; i ++ ) {
				if ( origindata[i].no == no )
				    return i;
			} // for()
			
		} // findorigin
		
		void printdata() {
			cout << "        #       Name                            Type 1          HP      Attack  Defense" << endl;
			for ( int i = 0 ; i < origindata.size() ; i ++ ) {
				cout << "[" << right << setw(3) << i + 1 << "]   " << left << setw(8) << origindata[i].no << left << setw(32) << origindata[i].name;
				cout << left << setw(16) << origindata[i].type1 << left << setw(8) << origindata[i].hp;
				cout << left << setw(8) << origindata[i].atk << left << setw(8) << origindata[i].def << endl; 
			}
			
		} // printdata()
		
		
		void printmission2( int pos, int i ) { // i for 流水號 - 1 
			cout << "[" << right << setw(3) << i + 1 << "]   " << left << setw(8) << origindata[pos].no << left << setw(32) << origindata[pos].name;
			cout << left << setw(16) << origindata[pos].type1 << left << setw(8) << origindata[pos].total << left << setw(8) << origindata[pos].hp;
			cout << left << setw(8) << origindata[pos].atk << left << setw(8) << origindata[pos].def << endl;
		}
		
		int calheight( pokenode *tmp ) { // calculate tree height
			if ( tmp -> left == NULL && tmp -> right == NULL )
			    return 1;
			
			int lefth = 0 , righth = 0;
            if ( tmp -> left != NULL )
			    lefth = calheight( tmp -> left );
			    
			if ( tmp -> right != NULL )
			    righth = calheight( tmp -> right );
			    
			if ( lefth > righth )
			    return lefth + 1;
			return righth + 1;
			    
		} // calheight
		
		pokenode *gettreetop() {
			return treetop;
		}
		
		int biggest() {
			tmpuse = treetop;
			while ( tmpuse -> right != NULL )
				tmpuse = tmpuse -> right;
			
			return origindata[ findorigin(tmpuse -> nos[0]) ].hp;
			
		}
		
		void delbiggest() {
			tmpuse = treetop;
			pokenode *prev = treetop;
			while ( tmpuse -> right != NULL ) { // go to the biggest
				prev = tmpuse;
				tmpuse = tmpuse -> right;
			} // while()
			
			if ( prev == tmpuse ) { // treetop is the biggest
			    printmission3( findorigin(tmpuse -> nos[0]) ); // print the data on tree
			    tmpuse -> nos.erase( tmpuse -> nos.begin() );           // then pop
			    if ( tmpuse -> nos.empty() ) { // node empty now - delete
				    tmpuse = tmpuse -> left;
				    delete prev; // delete empty node
				    treetop = tmpuse;
				} // if()
				
			} // if()
			else { // treetop is not the biggest (no need to change treetop)
			    printmission3( findorigin(tmpuse -> nos[0]) );
			    tmpuse -> nos.erase( tmpuse -> nos.begin() );
			    if ( tmpuse -> nos.empty() ) { // node empty now - delete
			        prev -> right = tmpuse -> left;
			        delete tmpuse; // delete empty node
			    } // if()
				
			} // else
			
		} // delbiggest
		
		void printmission3( int pos ) {
			cout << "#       Name           Type 1  Type 2  Total   HP      Attack  Defense Sp. Atk Sp. Def Speed   Generation  Legendary" << endl;
			cout << left << setw(8) << origindata[pos].no << left << setw(15) << origindata[pos].name << left << setw(8) << origindata[pos].type1;
			cout << left << setw(8) << origindata[pos].type2 << left << setw(8) << origindata[pos].total << left << setw(8) << origindata[pos].hp;
			cout << left << setw(8) << origindata[pos].atk << left << setw(8) << origindata[pos].def << left << setw(8) << origindata[pos].spatk;
			cout << left << setw(8) << origindata[pos].spdef << left << setw(8) << origindata[pos].spd << left << setw(12) << origindata[pos].gen;
			if ( origindata[pos].legend = true )
			    cout << "True    " << endl;
			else
			    cout << "False   " << endl;
		} // printmission3
		
		void findbigger( pokenode *tmp, int key, intset &set ) {
			set.visits += 1; // +1 visit when visit
		    if ( origindata[ findorigin(tmp -> nos[0]) ].hp > key )	{ // hp > key print!
		    	if ( tmp -> right != NULL ) { // go to the bigger node if exist
		    		findbigger( tmp -> right, key, set );
				}
		    	
		    	for ( int i = 0 ; i < tmp -> nos.size() ; i ++ ) {
		    		printmission2( findorigin(tmp -> nos[i]), set.printed ); // find and print the origin data
		    		set.printed += 1;
				} // for()
				
				if ( tmp -> left != NULL ) { // go to the smaller node if exist
		    		findbigger( tmp -> left, key, set );
				}
		    	
			} // if()
			else { // hp <= key no need to go left and don't print if hp < key
			    if ( tmp -> right != NULL ) {
			        findbigger( tmp -> right, key, set ); // go to the bigger node if exist
				} // if()
				
				if ( origindata[ findorigin(tmp -> nos[0]) ].hp == key ) {
					for ( int i = 0 ; i < tmp -> nos.size() ; i ++ ) {
		    		    printmission2( findorigin(tmp -> nos[i]), set.printed ); // find and print the origin data
		    		    set.printed += 1;
				    } // for()
				    
				} // if()
				
			} // else
			    
		} // findbigger()
		
		bool isNULL() {
			if ( treetop == NULL )
			    return 1;
			return 0;
		} // isNULL()
		
		void goes() { // for debug
			tmpuse = treetop;
			int i = 0;
			while(i !=  -1 ){
				cout << "node data is : " << origindata[findorigin(tmpuse -> nos[0])].hp << endl;
				cin >> i;
				cin.get();
				if ( i == 1 )
				    tmpuse = tmpuse -> right;
				else
				    tmpuse = tmpuse -> left;    
				
			}
		}
		
    private:
    	vector<poke> origindata;
    	pokenode *treetop;
    	pokenode *tmpuse;
};

void startGen();
void mission1( poketree &tree );
void mission2( poketree tree );
void mission3( poketree &tree );


int main(int argc, char** argv) {
    
    char command[100] = "\0";
    poketree tree; 
	while ( command[0] != '0' ) {
		
		startGen(); // generate the starting article for users to check
		cin.getline( command, 100 ); // read in user command
		cout << endl;
		
		// do different things based on user command
		if ( command[0] == '1' ) { 
			mission1( tree ); 
		} // if()
		else if ( command[0] == '2' ) {
			mission2( tree );
		} // else if()
		else if ( command[0] == '3' ) {
			mission3( tree );
		} // else if()
		else if ( command[0] == '5' ) {
			tree.goes();
		}
		else if ( command[0] != '0' ){
			cout << "Command does not exist!" << endl; // 防呆 
		}
		
		
	} // while()
	
	cout << "quitting !" << endl;
	
	return 0;
    
    
} // main  

void mission1( poketree &tree ) {
	ifstream reader;
	string filename;
	while ( ! reader.is_open() ) { // checking if the file is open 
    	   		                  // if don't ask user to try again
        cout << "Input 601, 602, ...( type 0 to Quit ) : " << endl;
    	cin >> filename;
    	if ( filename == "0" )
    		return;

    	filename = "input" + filename + ".txt";
        reader.open( filename.c_str() );
        if( ! reader.is_open() )
            cout << "### " + filename + " does not exist! ###";
	} // while()
	reader.close();
	cin.get(); // get the '\n'
	tree.inputdata( filename ); // input data to vector
	tree.printdata();          // print them out
	tree.buildtree();         // build the tree
	cout << "HP tree height = " << tree.calheight( tree.gettreetop() ) << endl;
	
} // mission1

void mission2( poketree tree ) {
	if ( tree.isNULL() ) { // 防呆 
	    cout << "----- Execute Mission 1 first! -----" << endl;
	    return;
	} // if()
	
	int key;
	intset set{ 0, 0 };
	cout << "Threshold (a positive integer): ";
	cin >> key;
	cin.get(); // get the '\n'
	cout << key << endl;
	int biggest = tree.biggest();
	while ( key < 1 || key > biggest ) { // 最大值提示 
		cout << "### It is NOT in [1," << biggest << "]. ###" << endl;
		cout << "Try again: ";
		cin >> key;
		cin.get();
	} // while()
	cout << "        #       Name                            Type 1          Total   HP      Attack  Defense" << endl;
	tree.findbigger( tree.gettreetop(), key, set ); 
	cout << "Number of visited nodes = " << set.visits << endl;
} // mission2

void mission3( poketree &tree ) {
	if ( tree.isNULL() ) { // 防呆 
	    cout << "----- Execute Mission 1 first! -----" << endl;
	    return;
	} // if()
	int i = 0;
	tree.delbiggest();
	if ( ! tree.isNULL() )
	    i = tree.calheight( tree.gettreetop() );
	cout << "HP tree height = " << i;
} // mission3



void startGen() {
	cout << endl;
	cout << "*** Binary Search Tree on Pokemon ***" << endl;
	cout << "* 0. QUIT                           *" << endl;
	cout << "* 1. Read one file to build BST     *" << endl;
	cout << "* 2. Threshold search on one column *" << endl;
	cout << "* 3. Delete the max on one column   *" << endl;
	cout << "* 4. Convert into balanced BST      *" << endl;
	cout << "*************************************" << endl;
	cout << "Input a choice(0, 1, 2, 3): ";
} // startGen


void show(pokenode* node, int no, vector<vector<data>> &datas, int level) {
	if (node == NULL)
		return ;
	show(node->left, no, datas, )
}
