#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <vector>

using namespace std;

#define INITIALTEMPERATURE 10000
#define NCHROMOSOMES 10
#define NELITIST 5
#define NGENERATIONS 10
#define CROSS_PROBABILITY 0.1
#define MUTATION_PROBABILITY 0.0001

void simulatedAnnealing(const vector<vector<unsigned int>> & initialDistribution, const vector<vector<unsigned int>> & groups);
void geneticAlgorithmSimulatedAnnealing(const vector<vector<unsigned int>> & initialDistribution, const vector<vector<unsigned int>> & groups);
void geneticAlgorithm(const vector<vector<unsigned int>> & initialDistribution, const vector<vector<unsigned int>> & groups);


#endif
