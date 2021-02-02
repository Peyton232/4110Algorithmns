#include <iostream>
#include <fstream>
using namespace std;

//hash using tablesize then raplace last didgit with a 1 or 0 to signify negative or positive number
class HashTable
{
private:
	int *table;
	int *indexTable;
	int moduloValue;
	int returnIndex;

	//hash function to hash each value and then store data
	int getHash(int key)
	{
		return key % moduloValue;	//modulo by table size
	}

public:
	//constructor
	HashTable(int k)
	{
		moduloValue = k;
		table = new (nothrow) int[k];
		indexTable = new (nothrow) int[k];

		//initialize empty array
		for (int i = 0; i < k; i++)
		{
			table[i] = -2000000;
			indexTable[i] = -2000000;
		}
	}

	//deconstructor
	~HashTable()
	{
		delete[] table;
		delete[] indexTable;
	}

	//get index function
	int getReturnIndex()
	{
		return returnIndex;
	}

	//insert data into table and see if a pair has been found
	bool insertElement(int key, int index)
	{
		int modifier = 1; //modifier to make negative numbers psoitve, this is faster than using the math library
		if (key < 0)
		{
			modifier = -1;
		}

		//find index to insert value
		int hashValue = getHash(modifier * key);

		//check for collisions and insert or linear probe
		bool found = false;
		while (!found)
		{
			if (table[hashValue] == (key * -1))
			{
				returnIndex = indexTable[hashValue];

				//test pair
				//cout << endl << "[" << key << " " << table[hashValue] << "]" << endl;

				return true; //pair found
			}
			else if (table[hashValue] == -2000000)
			{
				//if cell is empty
				table[hashValue] = key;
				indexTable[hashValue] = index;
				found = true;
			}
			else
			{
				//linear probing
				hashValue++;
				if (hashValue == moduloValue)
				{
					hashValue = 0;
				}
			}
		}
		return false;	//pair not found
	}

	//realisticly should put remove element here but actually never needed for this algorithmn so it will be omitted

	void printAll()
	{
		//traverse each spot in array
		for (int i = 0; i < moduloValue; i++)
		{
			cout << "Index " << i << ": ";
			cout << table[i] << endl;
		}
	}
};

int main()
{
	//variables
	int k;	 //number of arrrays (k <= 20)
	int n;	 //length of each array (n <= 10^4)
	int num; //generic number placeholder

	/*
	//vs code could not handle this
	ofstream fout;
	fout.open("stres2.txt");
	fout << 100 << " " << 2000000 << endl;

	for (int i = 0; i < 100; i++){
		for (int j = 0; j < 2000000; j++){
			fout << j << " ";
		}
		fout << endl;
	}
	*/

	//read k and n from file
	ifstream fin;

	//open output file
	//ofstream fout;
	//fout.open("output.txt");

	//open input file
	//fin.open ("rosalind_2sum.txt");
	//fin.open("example.txt");
	//fin.open("stress.txt");
	//fin.open("rosalind_2sum (2).txt");
	fin.open("current.txt");
	fin >> k >> n;

	//algorithmn
	HashTable sum2(n);

	//parse through all the given arrays
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < n; j++)
		{

			//get number from data
			fin >> num;

			//check if 2 sum condition has been met
			if (sum2.insertElement(num, j))
			{
				cout << sum2.getReturnIndex() + 1 << " " << j + 1;

				//exhaust rest of numbers in file
				for (int k = j + 1; k < n; k++)
				{
					fin >> num;
				}
				j = n;
			}

			//if a pair is never found then return -1
			if (j == (n - 1))
			{
				cout << "-1";
			}
		}
		//reconstruct hash table
		cout << endl;
		sum2.~HashTable();		  // destruct
		new (&sum2) HashTable(n); // reconstruct
	}

	//close file
	fin.close();
	return 0;
}