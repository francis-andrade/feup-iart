#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include "Chromosome.h"

class GeneticAlgorithm {
private:
	vector<Chromosome  > population;
	void selection(unsigned int nElitist);
	void crossover(unsigned int crossoverPoint, unsigned int i, unsigned int j);
	void crossing(double probability);
	void mutation(double probability);
public:
	GeneticAlgorithm();	
	void addChromosome(const vector<vector<vector<unsigned int>>> & permutations, const Room & room);
	void addChromosome(const vector<vector<vector<unsigned int>>> & permutations, Room * initialRoom);
	Room & performAlgorithm(unsigned int nElitist, unsigned int noGenerations, double crossProb, double mutationProb);
	

};

#endif
