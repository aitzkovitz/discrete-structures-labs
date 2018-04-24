// Aaron Itzkovitz
// OLA4
// main.cpp
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <math.h>

int binaryToInt(int* binary, int size){											// function to convert from binary to base 10
	int sum = 0;
	int j = 0;
	for (int i = size - 1; i >= 0; i--) {
		sum += (pow(2, i) * binary[j++]);
	}
	return sum;
}
int errors(const std::string& bitsToCheck) {									// function checks for errors, returns 0 or error location			
	int parityGroups[4][7] = { { 1,3,5,7,9,11,13 },{ 2,3,6,7,10,11 },				
							{ 4,5,6,7,12,13 },{ 8,9,10,11,12,13 } };			// parity group locations
	int errorIndex[4] = { 0 };													// binary number to represent, location of error
	for (int i = 3; i >= 0 ; i--) {												// go through parity groups and add up ones in each group
		int sum = 0;				
		for (int x = 0; x < 7; x++) {	
			int j = parityGroups[i][x];					
			if (j != 0) {
				sum += (bitsToCheck[j - 1] - '0');								
			}
		}
		errorIndex[ 3 - i ] = (!(sum % 2 == 0));								// add a one or zero to corresponding parity group location
	}	
	int errors = binaryToInt(errorIndex, 4);									// convert binary error location to decimal
	return errors;	
}

int main() {
	std::ifstream inFile ("packets.dat");
	std::string recCode, transCode;
	while (inFile >> recCode) {													// while not at file end
		int error = errors(recCode);											// find error location
		int recCodeInts[13] = { 0 };											
		for (int i = 0; i < 13; i++) {											// turn string into int array
			recCodeInts[i] = recCode[i] - '0';
		}
		if (error) {															// corect error location
			recCodeInts[error - 1] = abs(recCodeInts[error - 1] - 1);				
		}
		int newIndices[] = { 3, 5, 6, 7, 9, 10, 11, 12, 13 };		
		int gray[9] = { 0 };
		int j = 0;
		for (int i = 0; i < 9; i++) {											// convert to gray
			int f = newIndices[i];
			gray[j++] = recCodeInts[f - 1];
		}	
		int excess127[9] = { 0 };												
		excess127[0] = gray[0];													
		for (int k = 1; k < 9; k++) {											// convert to excess 127
			int sum = 0;
			for (int j = k - 1; j >= 0; j--) {									// add up ones to left of current bit
				sum += gray[j];													
			}
			excess127[k] = abs(gray[k] - (sum % 2));						// if even ones, flip bit 
		}																														
		int decimal = binaryToInt(excess127, 9) - 127;							// convert from excess 127						
		std::cout << char(decimal);												// char cast
	}
	std::cout << '\n';
	inFile.close();																// close file
	return 0;
}

