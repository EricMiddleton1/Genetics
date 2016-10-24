#include "Genetic.hpp"

using namespace std;

#include <functional>
#include <iostream>

#include <cstdlib>

Genetic::Genetic(const std::string& _phrase, unsigned int _populationSize)
	: phrase(_phrase) {
	//Generate population
	for(; _populationSize > 0; --_populationSize) {
		population.push_back(randomString(phrase.length()));
	}

	//Sort the population
	population.sort([this](const string& str1, const string& str2) {
		return phraseCompare(str1, str2);
	});
}

string Genetic::evolve(unsigned int maxEpochs) {
	cout << "[Genetic] Current best phrase: " << *population.begin()
		<< " (fitness rating " << fitness(*population.begin()) << ')' << endl;

	unsigned int epochs;
	for(epochs = 0; epochs < maxEpochs; ++epochs) {
		//Mate the top two performers
		auto first = population.begin();
		auto second = population.begin();
		advance(second, 1);

		string eliteOffspring = mate(*first, *second);

		//Mate two random performers
		first = population.begin();
		second = population.begin();
		advance(first, rand() % population.size());
		advance(second, rand() % population.size());

		string randOffspring = mate(*first, *second);

		//Randomly mutate 1% of the population
		for(unsigned int i = 0; i < (population.size()/100); ++i) {
			unsigned int selection = rand() % population.size();
			auto pick = population.begin();
			advance(pick, selection);

			*pick = mutate(*pick);
		}

		//Add new offspring into the population
		population.push_back(eliteOffspring);
		population.push_back(randOffspring);

		//Resort the population
		population.sort([this](const string& str1, const string& str2) {
			return phraseCompare(str1, str2);
		});


		//Remove the two lowest performers
		first = population.begin();
		advance(first, population.size() - 2);
		population.erase(first, population.end());

		//Finish the loop early if we have the ideal phrase
		if(fitness(*population.begin()) == 0) {
			epochs++;
			break;
		}
	}

	cout << "[Genetic] New best phrase: " << *population.begin()
		<< "(fitness rating " << fitness(*population.begin()) << ") after "
		<< epochs << " iterations" << endl;

	return *population.begin();
}

unsigned int Genetic::fitness(const string& candidate) {
	unsigned int diff = 0;

	for(unsigned int i = 0; i < phrase.length(); ++i) {
		diff += abs(candidate[i] - phrase[i]);
	}

	return diff;
}

string Genetic::mutate(string candidate) {
	//Replace a randomly selected character with a random new one
	unsigned int index = rand() % candidate.length();

	candidate[index] = (rand() % 26 + 'a');

	return candidate;
}

string Genetic::mate(const string& str1, const string& str2) {
	//Mate by swapping around the center of the string
	return str1.substr(0, str1.length()/2) + str2.substr(str1.length()/2 + 1, string::npos);
}

string Genetic::randomString(unsigned int length) {
	string str;

	for(; length > 0; --length) {
		str += static_cast<char>((rand() % 26) + 'a');
	}

	return str;
}

bool Genetic::phraseCompare(const string& str1, const string& str2) {
	return fitness(str1) <= fitness(str2);
}
