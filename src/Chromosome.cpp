#include "Chromosome.h"
#include <cstdlib>

Chromosome::Chromosome(const vector<vector<vector<unsigned int>>> & permutations,const Room & room) :
	permutations(permutations), room(room)
{

}

Chromosome::Chromosome(Room * initialRoom, const vector<vector<vector<unsigned int>>> & permutations) : permutations(permutations), room(*initialRoom) {
	

	this->actualizeRoom();
	
}



void Chromosome::setPermutations(const vector<vector<vector<unsigned int>>> & permutations) {
	this->permutations = permutations;
	actualizeRoom();
}

void Chromosome::actualizeRoom() {

	for (unsigned int i = 0; i < permutations.size(); i++)
		this->room.trade((this->permutations)[i][0], (this->permutations)[i][1]);
}

double Chromosome::evaluationFunction() const {
	return room.evaluationFunction();
}

void Chromosome::mutate(double probability) {
	for (unsigned int i = 0; i < permutations.size() - 1; i++){
		double X = ((double)rand() / (double)RAND_MAX);

		if (X < probability) {
			vector<unsigned int> position = (this->permutations)[i][0];
			(this->permutations)[i + 1][0] = (this->permutations)[i][0];
			(this->permutations)[i+1][0] = position;
		}
	}
}

void Chromosome::crossover(const Chromosome & partner, unsigned int crossoverPoint) {
	if (crossoverPoint >= permutations.size())
		return;

	permutations.erase(permutations.begin() + crossoverPoint, permutations.end());
	if(crossoverPoint < partner.permutations.size())
		permutations.insert(permutations.begin() + crossoverPoint, partner.permutations.begin() + crossoverPoint, partner.permutations.end() );

	this->actualizeRoom();
}

bool Chromosome::operator<(const Chromosome & chromosome) const
{
	return evaluationFunction() < chromosome.evaluationFunction();
}
