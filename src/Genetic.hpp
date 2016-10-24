#pragma once

#include <string>
#include <list>


class Genetic
{
public:
	Genetic(const std::string&, unsigned int);

	std::string evolve(unsigned int);

	unsigned int fitness(const std::string&);
private:
	static std::string mate(const std::string&, const std::string&);
	static std::string mutate(std::string);
	static std::string randomString(unsigned int);
	bool phraseCompare(const std::string&, const std::string&);

	std::string phrase;
	std::list<std::string> population;
};
