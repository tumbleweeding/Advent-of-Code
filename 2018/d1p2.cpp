#include <stdio.h>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
    int currFreq = 0;
    vector<int> changes;
    vector<int> prevFreq;

    
    ifstream infile;
    infile.open("d1.txt");

    if(!infile.is_open())
    {
	printf( "File unavailable" );
	exit(1);
    }

    int input;
    int i = 0;
    while (infile >> input) changes.push_back(input);

    infile.close();

    for (int i = 0, j = 0;; i = (++j % changes.size()))
    {
	currFreq += changes[i];
//	printf( "Current %i: + %i = %i\n", i, changes[i], currFreq);
	if(find(prevFreq.begin(), prevFreq.end(), currFreq) != prevFreq.end())
	{
	    printf( "Final value: %i\n", currFreq );
	    return 0;
	}
	prevFreq.push_back(currFreq);
    }
}
