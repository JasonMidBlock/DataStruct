#include <iostream> 
#include <fstream>

using namespace std;



int main(){
	ifstream out;
	out.open("input201.txt");
	string s;
	out >> s;
	out >> s;
	cout << s;
	out.close();
	
}
