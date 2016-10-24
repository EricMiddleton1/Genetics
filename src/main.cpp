#include "Genetic.hpp"

#include <iostream>

using namespace std;

int main() {
	string phrase;
	unsigned int populationSize;

	cout << "Please enter desired phrase: ";
	cin >> phrase;

	cout << "Please enter desired population size: ";
	cin >> populationSize;

	cout << "Generating genetic pool with size " << populationSize << std::endl;

	Genetic genetic(phrase, populationSize);

	string bestPerformer = genetic.evolve(0);

	cout << "Initial best phrase: " << bestPerformer
		<< "(fitness rating " << genetic.fitness(bestPerformer) << ")\n" << endl;
	
	
	cout << "Please enter the number of epochs to run, or 0 to quit" << endl;

	for(;;) {
		unsigned int epochs;

		cout << '>';
		cin >> epochs;

		if(epochs == 0)
			break;

		cout << "Running " << epochs << " epochs..." << endl;

		genetic.evolve(epochs);
	}

	return 0;
}
