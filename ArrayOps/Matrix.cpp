#include <iostream>
#define MAX_SIZE 10
using namespace std;

// FUNCTION DECLARATIONS
void MultRowAndScalar(float myarray[][MAX_SIZE], int row, float scalar, int size);
void tempRowAdd(int row, float myarray[][MAX_SIZE], float myarray2[][MAX_SIZE], int usedSize, int rowToAdd);
void printMatrix(float matrix[][MAX_SIZE], int size);
void printTemp(float array[], int size);

int main() {

	// get size from user
	cout << "Enter the matrix size." << endl;
	int size;
	cin >> size;
	
	// declare matrices
	float matrix1[MAX_SIZE][MAX_SIZE] = { 0 };
	float matrix2[MAX_SIZE][MAX_SIZE] = { 0 };

	// read in values
	cout << "Enter matrix values row by row." << endl;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cin >> matrix1[i][j];
		}
	}

	// initialize identity matrix 
	for (int i = 0; i < size; i++) {
		matrix2[i][i] = 1.0;
	}

	/*
	// get row specific multipliers
	int multipliers[MAX_SIZE];
	for (int i = 0; i < size; i++) {
		multipliers[i] = matrix1[i][1];
	}
	*/

	//start algorithm
	for (int f = 0; f < size; f++) {  // for every row i
		float scalar = (1 / matrix1[f][f]);
		MultRowAndScalar(matrix1, f, scalar ,size); // multiply row i by the reciprocal of the main diagonol element
		MultRowAndScalar(matrix2, f, scalar ,size); // duplicate with identity matrix
		tempRowAdd(f, matrix1, matrix2, size, f+1);
			
	}
	printMatrix(matrix2, size);
	int c;
	cin >> c;
	
	return 0;
}
  

// FUNCTION DEFINITIONs
// function takes in the row of the outer loop, the main array, the size, and the row of the innre loop
void tempRowAdd(int row, float myarray[][MAX_SIZE], float myarray2[][MAX_SIZE], int usedSize, int rowToAdd)
{
	float tempRow1[MAX_SIZE] = { 0.0 }; // make a new row
	float tempRow2[MAX_SIZE] = { 0.0 }; // make a new row for identity matrix
	for (int i = 0; i < usedSize; i++) {
		tempRow1[i] = myarray[row][row + i] * (-1 * (myarray[row + 1][row]));
		//printTemp(tempRow1, usedSize);
		tempRow2[i] = myarray2[row][row + i] * (-1 * (myarray[row + 1][row]));
		//printTemp(tempRow2, usedSize);

	}
	// add to rowToAdd
	for (int i = 0; i < usedSize; i++) {
		myarray[rowToAdd][i] += tempRow1[i]; // for every column i, add the ith element of the tempRow
		myarray2[rowToAdd][i] += tempRow2[i]; // 
	}
}

void MultRowAndScalar(float myarray[][MAX_SIZE], int row, float scalar, int size)
{
	for (int i = 0; i < size; i++) {
		myarray[row][i] *= scalar;
	}
}

void printMatrix(float matrix[][MAX_SIZE], int size)
{
	cout << "Here is the matrix." << endl << endl;
	for (int i = 0; i < size; i++) {
		for (int k = 0; k < size; k++) {
			cout << matrix[i][k] << '\t';
		}
		cout << endl;
	}
}
void printTemp(float array[],int size) {
	cout << "This is the temp row." << endl;
	for (int i = 0; i < size; i++) {
		cout << array[i] << '\t' ;
	}
	cout << endl;
}