#include <iostream>
#include <vector>
using namespace std;


void initialInformation();
int askForInput(const string & askMessage, const string & errorMessage,int min, int max, bool & leaveprogram);
void chooseAlgorithm(vector<vector<unsigned int>> & distribution, vector<vector<unsigned int>> & groups, bool  & leaveprogram);
