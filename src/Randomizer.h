#include <vector>
#include <iostream>

using namespace std;

void generateMatrix(const int lineN, const int columnN,const int elems, vector<vector<unsigned int>> & matrix);
void randomizeMatrix(vector<vector<unsigned int>> & matrix);
void randomizeGroups(const int groupsN,const int nSpectators, vector<vector<unsigned int>> & grpMatrix);
vector<int> getUserInfo();
void printGroups(const vector<vector<unsigned int>> & matrix);
