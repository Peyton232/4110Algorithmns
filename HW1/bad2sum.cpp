#include <iostream>
#include <fstream>
using namespace std;

bool sumToTarget(int arr[], int k)
{
    for (int i = 0; i < k; i++)
    {
        for (int j = i + 1; j < k; j++)
        {
            if (arr[i] + arr[j] == 0)
            {
                if (arr[i] == 0)
                {
                }
                else
                {
                    cout << i + 1 << " " << j + 1;
                    return true;
                }
            }
        }
    }
    cout << "-1";
    return false;
}

int main()
{

    //variables
    int k;   //number of arrrays (k <= 20)
    int n;   //length of each array (n <= 10^4)
    int num; //generic number placeholder

    //read k and n from file
    ifstream fin;
    //fin.open ("rosalind_2sum.txt");
    //fin.open("example.txt");
    //fin.open("rosalind_2sum_798_2_dataset.txt");
    //fin.open("stress.txt");
    //fin.open("rosalind_2sum (2).txt");
    fin.open("current.txt");
    fin >> k >> n;

    //array
    int arr[n];

    //do ammount of times of rows
    for (int i = 0; i < k; i++)
    {
        //put into array
        for (int j = 0; j < n; j++)
        {
            fin >> num;
            arr[j] = num;
        }

        //call function
        sumToTarget(arr, n);
        cout << endl;
    }

    return 0;
}