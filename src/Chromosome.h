#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include "Room.h"

class Chromosome {
private:
	
	

public:
	Room  room;
	vector<vector<vector<unsigned int>>>  permutations;
	Chromosome(const vector<vector<vector<unsigned int>>> & permutations,const Room & room);
	Chromosome(Room * initialRoom,const vector<vector<vector<unsigned int>>> & permutations);
	void setPermutations(const vector<vector<vector<unsigned int>>> & permutations);
	void actualizeRoom();
	double evaluationFunction() const;
	void mutate(double probability);
	void crossover(const Chromosome & partner, unsigned int crossoverPoint);
	bool operator<(const Chromosome & chromosome) const;

};

#endif