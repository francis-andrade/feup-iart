#ifndef UTILS_H
#define UTILS_H
#include<iostream>
#include <vector>
using namespace std;

template<class T>
void printBidimensionalVector(const vector<vector<T>> & v) {
	for (unsigned int i = 0; i < v.size(); i++) {
		for (unsigned int j = 0; j < v[i].size(); j++)
			cout << v[i][j] << " ";

		cout << endl;
	}
}



template<class T>
T maxBidimensionalVector(const vector<vector<T>> & v) {
	T maximum = 0;
	for (unsigned int i = 0; i < v.size(); i++)
		for (unsigned int j = 0; j < v[i].size(); j++)
			if (maximum < v[i][j])
				maximum = v[i][j];

	return maximum;

}


void printMatrix(const vector<vector<unsigned int>> & matrix);
void printGroups(const vector<vector<unsigned int>> & matrix);
void printFinalDistributionInformation(const unsigned int sumSquareDistances, const unsigned int groupsPoints, const vector<vector<unsigned int>> & matrix );

int myrandom (int i);

void elementsInGroup(const vector<vector<unsigned int>> & groups, vector<int> & elementsInGroup);


bool isInteger(const string & s);



int convint(const string & s);

#endif
