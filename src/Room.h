#ifndef ROOM_H
#define ROOM_H

#include <vector>

using namespace std;

class Room {
private:
	

	vector<vector<unsigned int>> tickets;
	vector<vector<unsigned int>> const * groups;
	vector<int> const * elementsInGroup;
	unsigned int sumSquareDistances;
	unsigned int groupsPoints;
	Room * initialRoom;
public:
	vector<vector<unsigned int>> distribution;
	Room(const vector<vector<unsigned int>> & distribution, Room * initialRoom,const vector<vector<unsigned int>> * const groups,const vector<int> * const elementsInGroup);
	Room(Room * initialRoom,const vector<vector<unsigned int>> * const groups,const vector<int> * const elementsInGroup) : Room(vector<vector<unsigned int>>(), initialRoom, groups, elementsInGroup) {};
	~Room();
	Room(const Room & room);
	Room & operator=(const Room & room);
	Room * getInitialRoom() { return initialRoom; };
	vector<vector<unsigned int>> getDistribution() const{ return this->distribution; };
	vector<vector<unsigned int>> getTickets() const{ return this->tickets; };
	void trade(const vector<unsigned int>& position1, const vector<unsigned int>& position2);
	void getTradePositions(vector<unsigned int> & position1, vector<unsigned int> & position2) const;
	void calculateSquareDistance();
	void calculateGroupsPoints();
	unsigned int groupPointsLine(unsigned int lineN);
	double evaluationFunction() const;
	unsigned int getSumSquareDistances() const;
	unsigned int getGroupsPoints() const;
	unsigned int getCalculatedSumSquareDistances() const;
	void simulatedAnnealing(int initialTemperature);
	void simulatedAnnealing(int initialTemperature, vector<vector<vector<unsigned int>>> & permutations);
 };




#endif
