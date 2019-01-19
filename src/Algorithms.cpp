#include "Algorithms.h"
#include "Utils.h"
#include <cmath>
#include<time.h>
#include "GeneticAlgorithm.h"

void simulatedAnnealing(const vector<vector<unsigned int>> & initialDistribution,const vector<vector<unsigned int>> & groups) {
	vector<int> elements;
	elementsInGroup(groups, elements);

	Room room(initialDistribution, NULL, &groups, &elements);
	cout<<"Starting Simulated Annealing..."<<endl;
	room.simulatedAnnealing(INITIALTEMPERATURE);
	printFinalDistributionInformation(room.getSumSquareDistances(), room.getGroupsPoints(), room.distribution);
}

void geneticAlgorithmSimulatedAnnealing(const vector<vector<unsigned int>> & initialDistribution, const vector<vector<unsigned int>> & groups) {
	vector<int> elements;
	elementsInGroup(groups, elements);

	GeneticAlgorithm ga;

	cout<<"Starting Simulated Annealing..."<<endl;
	for (unsigned int i = 0; i < NCHROMOSOMES; i++) {
		Room room(initialDistribution, NULL, &groups, &elements);
		vector<vector<vector<unsigned int>>> permutations;
		room.simulatedAnnealing(INITIALTEMPERATURE, permutations);
		ga.addChromosome(permutations, room);
	}

	cout << "Starting Genetic Algorithm..." << endl;
	Room room = ga.performAlgorithm(NELITIST, NGENERATIONS, CROSS_PROBABILITY, MUTATION_PROBABILITY);

	printFinalDistributionInformation(room.getSumSquareDistances(), room.getGroupsPoints(), room.distribution);
}
	
void geneticAlgorithm(const vector<vector<unsigned int>> & initialDistribution, const vector<vector<unsigned int>> & groups) {
	vector<int> elements;
	elementsInGroup(groups, elements);

	GeneticAlgorithm ga;
	Room room(initialDistribution, NULL, &groups, &elements);
	for (unsigned int i = 0; i < NCHROMOSOMES; i++) {
	
		vector<vector<vector<unsigned int>>> permutations;
		for (unsigned int j = 0; j < INITIALTEMPERATURE; j++) {
			vector<unsigned int> position1, position2;
			room.getTradePositions(position1, position2);
			permutations.push_back({ position1, position2 });
		}
		
		ga.addChromosome(permutations, & room);
	}

	cout << "Starting Genetic Algorithm..." << endl;
	Room newRoom = ga.performAlgorithm(NELITIST, NGENERATIONS, CROSS_PROBABILITY, MUTATION_PROBABILITY);

	printFinalDistributionInformation(newRoom.getSumSquareDistances(), newRoom.getGroupsPoints(), newRoom.distribution);
}
