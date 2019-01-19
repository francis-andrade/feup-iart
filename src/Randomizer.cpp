#include <vector>
#include <iostream>
#include <algorithm>
#include "Utils.h"
#include "Randomizer.h"

using namespace std;



void generateMatrix(const int lineN,const int columnN,const int elems, vector<vector<unsigned int>> & matrix){
	matrix = vector<vector<unsigned int>>(lineN);
	for(int i=0; i<lineN; i++)
		matrix[i].resize(columnN);

	int aux = 1;
		for(int i=0; i< lineN; i++){
			for(int j=0; j< columnN; j++){
				if(aux <= elems){
					matrix[i][j] = aux;
					aux++;
				}
				else
					matrix[i][j] = 0;
			}
		}
}






void randomizeMatrix(vector<vector<unsigned int>> & matrix){
	vector<int>matrix1d;
	for(unsigned int i=0; i<matrix.size(); i++)
		for(unsigned int j=0; j< matrix[i].size(); j++)
			matrix1d.push_back(matrix[i][j]);
	random_shuffle(matrix1d.begin(), matrix1d.end(), myrandom);
	int inc=0;

	for(unsigned int i=0; i<matrix.size(); i++){
		for(unsigned int j=0; j< matrix[i].size(); j++){
			matrix[i][j] = matrix1d[inc];
			inc++;
		}
	}
}

void randomizeGroups(const int groupsN,const int nSpectators, vector<vector<unsigned int>> & grpMatrix){
	vector<int>matrix1d;
	for(unsigned int i=1; i <= nSpectators; i++)
			matrix1d.push_back(i);

	random_shuffle(matrix1d.begin(), matrix1d.end(), myrandom);

	grpMatrix = vector<vector<unsigned int>>(groupsN);
	for(unsigned int i=0; i<matrix1d.size(); i++){
		if(matrix1d[i] > 0){
			int rand1 = rand() % groupsN;
			grpMatrix[rand1].push_back(matrix1d[i]);
		}
	}

	//eliminates nulls groups
	for(unsigned int i=0; i<grpMatrix.size(); i++){
		if(grpMatrix[i].size() < 1){
			grpMatrix.erase(grpMatrix.begin() + i);
			i--;
		}
	}

}







