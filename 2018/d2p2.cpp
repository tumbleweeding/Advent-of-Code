#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

int main()
{
     vector<string> codes;
    
    ifstream infile;
    infile.open("d2.txt");

    if(!infile.is_open())
    {
	printf( "File unavailable" );
	exit(1);
    }

    string input;
    while (infile >> input) codes.push_back(input);

    infile.close();

    int count;

    for (int i = 0; i < codes.size(); i++)
    {
	for (int j = i; j < codes.size(); j++)
	{
	    count = 0;
	    for (int k = 0; k < 26; k++)
	    {
		if (codes[i][k] == codes [j][k]) count++;
	    }
	    if(count == 25)
	    {
		cout << "Solution is: ";
		for (int o = 0; o < 26; o++)
		{
		    if (codes[i][o] == codes[j][o])
		    {
			cout << codes[i][o];
		    }
		}
	    }
	}
    }
    
    return 0;
}
