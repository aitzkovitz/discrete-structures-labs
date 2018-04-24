// Aaron Itzkovitz
// huffmainTree.coo
// OLA 2
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
void preOrderTraverse(int index, string& codeString);
const int COLUMNS = 4;												
const int MAX_CODE = 10;
const int MAX_ROWS = 23;
int inputTree[MAX_ROWS][COLUMNS] = { 0 };
string codeNumbers[MAX_CODE];
int j = 0;

int main(){
	// open file object
	ifstream infile;
	infile.open("tree.dat");
	int numOfNodes, rootIndex;
	infile >> rootIndex >> numOfNodes;
	// read in array
	for (int i = 0; i < numOfNodes; i++){
		for (int k = 0; k < COLUMNS; k++) {
			infile >> inputTree[i][k];
		}
	}
	string codeString = "";
	preOrderTraverse(rootIndex, codeString);
	infile.close();
	return 0;
}
// precondition: j = 0, codeString.length() = 0
// postcondition: codeNumbers is full of Codes
void preOrderTraverse(int index, string& codeString){
if (inputTree[index][2] == -1 && inputTree[index][3] == -1){
	codeNumbers[j] = codeString;												//+= (inputTree[index][0] - '0')
	cout << char(inputTree[index][0]) << " = " << codeString << endl;
	j++;
	codeString.pop_back();
}else {
	codeString += '0';															//updateCodeString with 0
	preOrderTraverse(inputTree[index][2], codeString);
	codeString += '1';
	preOrderTraverse(inputTree[index][3], codeString);
	if (codeString.length() != 0) codeString.pop_back();
	}
}

