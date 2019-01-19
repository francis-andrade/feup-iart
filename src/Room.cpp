#include "Room.h"
#include "Utils.h"
#include<time.h>
#include <cmath>
#include <algorithm>

unsigned int getSquareDistance(const vector<unsigned int> & position1, const vector<unsigned int> & position2) {
	unsigned int distance = abs((int)position1[0] - (int)position2[0]) + abs((int)position1[1] - (int)position2[1]);
	return distance * distance;
}

Room::Room(const vector<vector<unsigned int>> & distribution, Room * initialRoom, vector<vector<unsigned int>> const *  groups,vector<int> const * elementsInGroup) {
	this->distribution = distribution;
	
	this->groups = groups;
	this->elementsInGroup = elementsInGroup;

	
	unsigned int maxDistributionValue = maxBidimensionalVector(this->distribution);
	this->tickets = vector<vector<unsigned int>>(maxDistributionValue + 1);
	this->tickets[0]={ distribution.size(), distribution.size() };
	
	for (unsigned int i = 0; i < distribution.size(); i++) 
		for (unsigned int j = 0; j < distribution[i].size(); j++) {
			this->tickets[distribution[i][j]] = { i, j };
		}

	this->calculateGroupsPoints();
	this->sumSquareDistances = 0;

	this->initialRoom = initialRoom;
	if (initialRoom == NULL)
		this->initialRoom = new Room(*this);

	this->calculateSquareDistance();
	
}

Room::~Room() {
	
}

Room::Room(const Room & room): distribution(room.distribution), initialRoom(room.initialRoom), tickets(room.tickets), groups(room.groups),
								elementsInGroup(room.elementsInGroup), sumSquareDistances(room.sumSquareDistances), groupsPoints(room.groupsPoints){
}

Room & Room::operator= (const Room & room) {
	this->distribution = room.distribution;
	this->initialRoom = room.initialRoom;
	this->tickets = room.tickets;
	this->groups = room.groups;
	this->elementsInGroup = room.elementsInGroup;
	this->sumSquareDistances = room.sumSquareDistances;
	this->groupsPoints = room.groupsPoints;
	return *this;
}



void Room::trade(const vector<unsigned int> & position1, const vector<unsigned int> & position2) {
	
	
	this->sumSquareDistances = this->sumSquareDistances - getSquareDistance(this->initialRoom->tickets[this->distribution[position1[0]][position1[1]]], position1) - getSquareDistance(this->initialRoom->tickets[this->distribution[position2[0]][position2[1]]], position2)
		+ getSquareDistance(this->initialRoom->tickets[this->distribution[position1[0]][position1[1]]], position2) + getSquareDistance(this->initialRoom->tickets[this->distribution[position2[0]][position2[1]]], position1);
	
	unsigned int subGroupPointsLine;

	if (position1[0] != position2[0])
		subGroupPointsLine = this->groupPointsLine(position1[0]) + this->groupPointsLine(position2[0]);
	else
		subGroupPointsLine = this->groupPointsLine(position1[0]);

	this->tickets[this->distribution[position1[0]][position1[1]]] = position2;
	this->tickets[this->distribution[position2[0]][position2[1]]] = position1;

	unsigned int element1 = this->distribution[position1[0]][position1[1]];
	this->distribution[position1[0]][position1[1]] = this->distribution[position2[0]][position2[1]];
	this->distribution[position2[0]][position2[1]] = element1;

	

	
	if (position1[0] != position2[0])
		this->groupsPoints = this->groupsPoints - subGroupPointsLine + this->groupPointsLine(position1[0]) + this->groupPointsLine(position2[0]);
	else
		this->groupsPoints = this->groupsPoints - subGroupPointsLine + this->groupPointsLine(position1[0]);

}



void Room::getTradePositions(vector<unsigned int> & position1, vector<unsigned int> & position2) const{
	unsigned int nRows = distribution.size();
	unsigned int nColumns = distribution[0].size();

	unsigned int permutatingRow1 = rand() % nRows;
	unsigned int permutatingColumn1 = rand() % nColumns;
	position1 = { permutatingRow1, permutatingColumn1 };

	unsigned int permutatingRow2 = rand() % nRows;
	unsigned int permutatingColumn2 = rand() % nColumns;
	position2 = { permutatingRow2, permutatingColumn2 };
}

void Room::calculateSquareDistance() {
	unsigned int sum = 0;
	for (unsigned int i = 0; i < this->tickets.size(); i++) 
		sum += getSquareDistance(this->tickets[i], initialRoom->tickets[i]);

	sumSquareDistances = sum;
}

void Room::calculateGroupsPoints() {
	unsigned int totalPoints = 0;
	for (unsigned int i = 0; i < this->distribution.size(); i++) 
		totalPoints += groupPointsLine(i);
	
	groupsPoints = totalPoints;
}





unsigned int Room::groupPointsLine(unsigned int lineN) {
	unsigned int totalPoints = 0;
	int currentGroup = -1;
	unsigned int elementsSameGroup = 1;
	for (unsigned int i = 0; i < this->distribution[lineN].size(); i++) {
		if (currentGroup != -1)
			if ((*this->elementsInGroup)[this->distribution[lineN][i]] == currentGroup)
				elementsSameGroup++;
			else {
				totalPoints += elementsSameGroup - 1;
				elementsSameGroup = 1;
			}
		currentGroup = (*this->elementsInGroup)[this->distribution[lineN][i]];
	}
	totalPoints += elementsSameGroup - 1;
	return totalPoints;
}

double Room::evaluationFunction() const {
	unsigned int m = this->distribution.size();
	unsigned int n = this->distribution[0].size();
	double factor = 1 / (sqrt(m*n)*(m*m+n*n));
	return max((double) 0, this->groupsPoints - this->sumSquareDistances*factor);
}

unsigned int Room::getSumSquareDistances() const
{
	return sumSquareDistances;
}

unsigned int Room::getGroupsPoints() const
{
	return groupsPoints;
}

unsigned int Room::getCalculatedSumSquareDistances() const {
	unsigned int sum = 0;
	for (unsigned int i = 0; i < this->tickets.size(); i++)
		sum += getSquareDistance(this->tickets[i], initialRoom->tickets[i]);

	return sum;
}

void Room::simulatedAnnealing(int initialTemperature) {
	int T = initialTemperature;
	while (T > 0) {


		vector<unsigned int> position1, position2;
		getTradePositions(position1, position2);

		unsigned int element1 = this->distribution[position1[0]][position1[1]];
		unsigned int element2 = this->distribution[position2[0]][position2[1]];
		unsigned int befTradeSumSquareDistances = this->sumSquareDistances;
		unsigned int befTradeGroupsPoints = this->groupsPoints;
		double valueCurrent = this->evaluationFunction();

		this->trade(position1, position2);


		double valueNext = this->evaluationFunction();


		double diffValues = valueNext - valueCurrent;
		bool changedState = true;
		if(diffValues < 0){
			double X = ((double)rand() / (double)RAND_MAX);
			if (X > exp(diffValues * 100 * initialTemperature / T)) {//permutates back to the state it was before
				this->sumSquareDistances = befTradeSumSquareDistances;
				this->groupsPoints = befTradeGroupsPoints;
				this->distribution[position1[0]][position1[1]] = element1;
				this->distribution[position2[0]][position2[1]] = element2;
				this->tickets[element1] = position1;
				this->tickets[element2] = position2;
				changedState = false;
			}


		}

		T--;
	}

}

void Room::simulatedAnnealing(int initialTemperature, vector<vector<vector<unsigned int>>> & permutations) {
	int T = initialTemperature;
	while (T > 0) {

		vector<unsigned int> position1, position2;
		getTradePositions(position1, position2);

		unsigned int element1 = this->distribution[position1[0]][position1[1]];
		unsigned int element2 = this->distribution[position2[0]][position2[1]];
		unsigned int befTradeSumSquareDistances = this->sumSquareDistances;
		unsigned int befTradeGroupsPoints = this->groupsPoints;
		double valueCurrent = this->evaluationFunction();

		this->trade(position1, position2);


		double valueNext = this->evaluationFunction();
		

		double diffValues = valueNext - valueCurrent;
		bool changedState = true;
		if(diffValues < 0){
			double X = ((double)rand() / (double)RAND_MAX);
			if (X > exp(diffValues * 100 * initialTemperature / T)) {//permutates back to the state it was before
				this->sumSquareDistances = befTradeSumSquareDistances;
				this->groupsPoints = befTradeGroupsPoints;
				this->distribution[position1[0]][position1[1]] = element1;
				this->distribution[position2[0]][position2[1]] = element2;
				this->tickets[element1] = position1;
				this->tickets[element2] = position2;
				changedState = false;
			}
			
				
		}

		if(changedState && permutations != vector<vector<vector<unsigned int>>>{ { {0, 0, 0} } })
			permutations.push_back({ position1, position2 });
		T--;
	}

}
