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

    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    int count[alphabet.size()];
    int i2 = 0, i3 = 0;
    bool b2, b3;
    char curr;
    
    //for each element in codes
    for (vector<string>::iterator it = codes.begin(); it != codes.end(); ++it)
    {
	string code = *it;
	
	//set all elements in count to 0 
	for (int a = 0; a < 26; a++) count[a] = 0;
	
	//for each character in code
	for (int j = 0; j < 26; j++)
	{
	    //for each character in alphabet
	    for (int o = 0; o < 26; o++)
	    {
		if(code[j] == alphabet[o])
		{
		    count[o]++;
		    break;
		}
	    }
	}
	
	b2 = b3 = false;
	
	//for each element in count
	for (int c = 0; c < 26; c++)
	{
	    b2 = (count[c] == 2) ? true : b2;
	    b3 = (count[c] == 3) ? true : b3;
	}
	
	//increment if found
	i2 += b2;
	i3 += b3;
    }
    
    int checksum = i2*i3;
    cout << (checksum) << endl;
    
    return 0;
    while(1);
}
