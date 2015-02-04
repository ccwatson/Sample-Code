//Program by Chadwyck Watson
//*******************************************
//This program will take integers from the user
//to encrypt using the RC4 encryption method. It
//will also take 5 integers from the user to act
//as the key for the encryption.
//********************************************

#include <iostream>
#include <stdlib.h>

#include <math.h> 
using namespace std;


//This function produces a
//pseudorandom key stream by cycleing
//going through S from S[0] to S[255]
//and then going through another permutation
int *PRN(int S [], int K[])
{
	int prnIndexPtrI = 0 , counter = 0;
	int prnIndexPtrJ = 0;
	int temp = 0;

	while (counter < 5)
	{
		prnIndexPtrI = (prnIndexPtrI + 1) % 255;
		prnIndexPtrJ = (prnIndexPtrJ + S[prnIndexPtrI]) % 255;

		temp = S[prnIndexPtrI];
		S[prnIndexPtrI] = S[prnIndexPtrJ];
		S[prnIndexPtrJ] = temp;
		K[counter] = (S[prnIndexPtrI] + S[prnIndexPtrJ]) % 255;
		
		counter++;
	}

	return K;
}

//Takes each value in the correspoinding position
// of the keysteam and state vector and XOR's them
//to create the cypher text which is then sent to output
void Cypher(int K[],int plainText[])
{
	cout << "Cypher Numbers " << endl;
	int cypher[5] = {};
	
	for ( int x = 0; x <= 4; x++ ) 
	{
		cypher[x] = K[x] ^ plainText[x];

		cout << cypher[x] << " ";
	}
	cout << endl;
}

int *Seed(int i, int S [], int T [])
{
	int j = 0;
	int temp = 0;
	for( i = 0; i <= 255; i++)
	{
		j = (j + S[i] + T[i]) % 255; 
		temp = S[i];
		S[i] = S[j];
		S[j] = temp;
	}
	return S;
}

//The program will start by initilizeing the key stream, 
//the state vector and the temporary
//vector as well as the integer array
//for the plain text numbers
int main()
{
	int i = 0, mainClassTemp, *y = 0;
	int key[5] = {};
	int S [256] ={};
	int tempVector[256];
	int plainText [5] = {};
	int K[5] = {};

	//Asks user for an array of 5 initegers to encrypt
	cout << "Type in 5 integers That will be encypted" << endl;
	for(mainClassTemp = 0; mainClassTemp < 5; mainClassTemp++)
	{
		cin >> plainText[mainClassTemp];
		while(cin.fail())//checks for integer
		{
			cout << "Error: not an integer. Enter an integer" << endl;
			cin.clear();
			cin.ignore(256,'\n');
			cin >> plainText[mainClassTemp];
		}
	}

	//User inputs the 5 integers that will be used as the key
	cout << "Type in 5 integers that will be used for the key in the encryption" << endl;
	for(mainClassTemp = 0; mainClassTemp < 5; mainClassTemp++)
	{
		cin >> key[mainClassTemp];

		while(cin.fail())//checks for integer
		{
			cout << "Error: not an integer. Enter an integer" << endl;
			cin.clear();
			cin.ignore(256,'\n');
			cin >> plainText[mainClassTemp];
		}
	}
	
	// Initilizes the state Vector and the
	//temporary Vector
	for (i = 0; i <= 255; i++)
	{
		S[i] = i;
		tempVector[i] = key[i % 5];
	}

	//Feeds the state vector and
	//temporary Vector into the
	//key scheduling algorithm
	y = Seed(i,S,tempVector);

	//Takes the values we get from
	//the Seed function and assigns them to
	//the state vector.
	for ( int x = 0; x <= 4; x++ )   
      S[x] = *(y + x);

	y = 0;

	//Sends the state vector and the
	//key vector to the Pseudo Random Number Generation
	y = PRN(S,K);


	//prints out the pseudo random stream that is later
	//used in the Cypher function
	cout << "Pseudo Random Numbers Generated from plain text: " << endl;
	for ( int x = 0; x <= 4; x++ ) 
	{
      K[x] = *(y + x);
	 cout << K[x] << " ";
	}
	cout << endl;

	//Sends the Key stream and plainText
	//to the cypher function
	Cypher(K,plainText);
}