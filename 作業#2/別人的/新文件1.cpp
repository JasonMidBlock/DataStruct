#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

int main() {
	ifstream ifs;
	string s;
	ifs.open("input201.txt");
	getline(ifs,s);
	
	cout << s;
}
