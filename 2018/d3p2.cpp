#include <stdio.h>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

struct claim
{
    int ID, x, y, w, h;
};

struct dims
{
    int x, y;
};

bool operator==(const dims& a, const dims& b)
{
    return (a.x == b.x && a.y == b.y);
}

claim GetClaimData(string claimLine)
{
    int ID, x, y, w, h;
    char pnd, at, comm, col, ex;

    stringstream ss(claimLine);
    ss >> pnd >> ID >> at >> x >> comm >> y >> col >> w >> ex >> h;

    claim thisClaim = {ID, x, y, w, h};
//    printf("ID: %i, X: %i, Y: %i, W: %i, H: %i\n", ID, x, y, w, h);
    return thisClaim;
}

dims FindDimensions(vector<claim> claims)
{
    int x = 0, y = 0;
    for (vector<claim>::iterator cit = claims.begin(); cit != claims.end(); ++cit)
    {
	claim curr = *cit;
	int cx = curr.x + curr.w;
	x = (cx > x) ? cx : x;

	int cy = curr.y + curr.h;
	y = (cy > y) ? cy : y;
    }
    
    dims dim = {x, y};

    return dim;
}

int IDofNotOverlappingClaim(vector<claim> claims, vector< vector<int> > material)
{    
    for (vector<claim>::iterator cit = claims.begin(); cit != claims.end(); ++cit)
    {
	int count = 0;
	claim c = *cit;
	for (int i = c.x; i < (c.x + c.w); i++)
	{
	    for (int j = c.y; j < (c.y + c.h); j++)
	    {
		count += material[i][j];
	    }
	}
	if (count == (c.w * c.h)) return c.ID;
    }
}

int main()
{
    vector<claim> claims;
    vector<dims> claimed;
    
    ifstream infile;
    infile.open("d3.txt");
    if(!infile.is_open())
    {
	printf("Error opening file.\n");
	return 1;
    }

    string claimLine;

    while(!infile.eof())
    {
	getline(infile, claimLine);
	claims.push_back(GetClaimData(claimLine));
    }

    infile.close();

    dims dim = FindDimensions(claims);
    vector< vector<int> > material;
    material.resize(dim.x, vector<int>(dim.y, 0));
    for (int i = 0; i < dim.x; i++)
    {
	for (int j = 0; j < dim.y; j++)
	{
	    material[i][j] = 0;
	}
    }

    //for each claim
    for (vector<claim>::iterator cit = claims.begin(); cit != claims.end(); ++cit)
    {
	claim thisClaim = *cit;
	for (int x = thisClaim.x; x < (thisClaim.x + thisClaim.w); x++)
	{
	    for (int y = thisClaim.y; y < (thisClaim.y + thisClaim.h); y++)
	    {
		material[x][y]++;
	    }
	}
    }
    printf("%i", IDofNotOverlappingClaim(claims, material));

    return 0;
}
