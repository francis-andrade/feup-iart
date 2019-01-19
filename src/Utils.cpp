#include "Utils.h"
#include <vector>



int myrandom (int i) { return rand()%i;}

void elementsInGroup(const vector<vector<unsigned int>> & groups, vector<int> & elementsInGroup) {
	unsigned int maxElement = maxBidimensionalVector(groups);
	vector<int> newElements(maxElement + 1);
	elementsInGroup = newElements;
	for (unsigned int i = 0; i < elementsInGroup.size(); i++)
		elementsInGroup[i] = -1;

	for (unsigned int i = 0; i < groups.size(); i++)
		for (unsigned int j = 0; j < groups[i].size(); j++) {
			elementsInGroup[groups[i][j]] = i;
		}

}

/*
This functions checks if a string is an integer
parameter: const string &s-The function will check if this string is an integer
return value- true if string is an integer and false if not
source:http://stackoverflow.com/questions/2844817/how-do-i-check-if-a-c-string-is-an-int
*/
bool isInteger(const string & s)
{
	if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;

	char * p;
	strtol(s.c_str(), &p, 10);

	return (*p == 0);
}


/*
This function converts a string to an integer and returns -1 if string is not an integer
parameter: string s-string that is going to be converted
return value - integer that corresponds to the string
*/
int convint(const string & s) {
	if (!isInteger(s)) {
		return -1;
	}
	else {
		return stoi(s);
	}
}


void printMatrix(const vector<vector<unsigned int>> & matrix){
	for(int i=0; i<matrix.size(); i++){
		for(int j=0; j< matrix[i].size(); j++){
			if(matrix[i][j]/10 < 1)
				cout <<"   "<< matrix[i][j]<<" ";
			else if(matrix[i][j] / 100 < 1)
				cout <<"  "<< matrix[i][j]<<" ";
			else if(matrix[i][j] / 1000 < 1)
				cout <<" "<< matrix[i][j]<<" ";
			else
				cout << matrix[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
}

void printGroups(const vector<vector<unsigned int>> & matrix){
	for(unsigned int i=0; i<matrix.size(); i++){
		cout << "{ ";
		for(unsigned int j=0; j<matrix[i].size(); j++){
			cout << matrix[i][j] << " ";
		}
		cout << "} " << endl;
	}
}

void printFinalDistributionInformation(const unsigned int sumSquareDistances, const unsigned int groupsPoints, const vector<vector<unsigned int>> & distribution ){
	cout<<"Final Distribution: "<<endl;
	printMatrix(distribution);
	cout<<"\nSum Square Distances: "<<sumSquareDistances<<endl;
	cout<<"Groups Points: "<<groupsPoints<<endl;

}

