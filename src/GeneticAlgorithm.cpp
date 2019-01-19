#include "GeneticAlgorithm.h"
#include <algorithm>

GeneticAlgorithm::GeneticAlgorithm() {
	
}

void GeneticAlgorithm::addChromosome(const vector<vector<vector<unsigned int>>> & permutations,const Room & room) {
	Chromosome chromo(permutations, room);
	population.push_back(chromo);
}

void GeneticAlgorithm::addChromosome(const vector<vector<vector<unsigned int>>> & permutations, Room * initialRoom) {
	Chromosome chromo(initialRoom, permutations);
	population.push_back(chromo);
}



void GeneticAlgorithm::selection(unsigned int nElitist) {
	sort(population.begin(), population.end());

	double sumEvals = 0;

	for (unsigned int i = 0; i < population.size() ; i++) 
		sumEvals += population[i].evaluationFunction();


	if (nElitist < population.size()) {
		vector<Chromosome> newPopulation;
		vector<double> probabilities;
		double cumProb = 0;
		for (unsigned int i = 0; i < population.size() ; i++) {
			probabilities.push_back(cumProb + population[i].evaluationFunction() / sumEvals);
		}

		for (unsigned int i = 0; i < population.size() - nElitist; i++) {
			double X = ((double)rand() / (double)RAND_MAX);

			for (unsigned int j = 0; j < probabilities.size(); j++) {
				if (X <= probabilities[j])
					newPopulation.push_back(population[j]);
			}
		}

		for (unsigned int i = population.size() - nElitist; i < population.size(); i++)
			newPopulation.push_back(population[i]);
	}


}

void GeneticAlgorithm::crossover(unsigned int crossoverPoint, unsigned int posFirstParent, unsigned int posSecondParent) {

	if (population[posFirstParent].permutations.size() <= crossoverPoint || population[posSecondParent].permutations.size() <= crossoverPoint)
		return;

	vector<vector<vector<unsigned int>>> firstPermutations = population[posFirstParent].permutations;
	vector<vector<vector<unsigned int>>> secondPermutations = population[posSecondParent].permutations;
	
	vector<vector<vector<unsigned int>>> newFirstPermutations, newSecondPermutations;

	newFirstPermutations.insert(newFirstPermutations.begin(), firstPermutations.begin(), firstPermutations.begin() + crossoverPoint);
	newFirstPermutations.insert(newFirstPermutations.begin() + crossoverPoint, secondPermutations.begin() + crossoverPoint, secondPermutations.end());

	newSecondPermutations.insert(newSecondPermutations.begin(), secondPermutations.begin(), secondPermutations.begin() + crossoverPoint);
	newSecondPermutations.insert(newSecondPermutations.begin() + crossoverPoint, firstPermutations.begin() + crossoverPoint, firstPermutations.end());

	population[posFirstParent].setPermutations(newFirstPermutations);
	population[posSecondParent].setPermutations(newSecondPermutations);
}

void GeneticAlgorithm::crossing(double probability) {
	vector<unsigned int> crossingIndices;

	for (unsigned int i = 0; i < population.size(); i++) {
		double X = ((double)rand() / (double)RAND_MAX);
		if (X <= probability)
			crossingIndices.push_back(i);

	}

	for (unsigned int i = 0; i+1 < crossingIndices.size(); i = i + 2){
		unsigned int crossoverPoint = rand() % population[i].permutations.size();
		crossover(crossoverPoint, i, i + 1);
	}


}

void GeneticAlgorithm::mutation(double probability) {
	for (unsigned int i = 0; i < population.size(); i++)
		population[i].mutate(probability);
}

Room & GeneticAlgorithm::performAlgorithm(unsigned int nElitist, unsigned int noGenerations, double crossProb, double mutationProb) {

	for (unsigned int i = 0; i < noGenerations; i++) {
		selection(nElitist);
		crossing(crossProb);
		mutation(mutationProb);
	}

	return max_element(population.begin(), population.end())->room;
}
