#include "simAling.h"
#include <iostream>
simAling::simAling(const char* c)
{
	setFileToUse(c);
	openFile(variableNumber, clauseNumber, clause);
}
simAling::simAling()
{
	openFile(variableNumber, clauseNumber, clause);
}

simAling::~simAling()
{
    clause.clear();
    clause.shrink_to_fit();
}

void simAling::setParameters(int variableNumber, int clauseNumber, std::vector<std::vector<int>> clause)
{
    this->variableNumber = variableNumber;
    this->clauseNumber = clauseNumber;
    this->clause = clause;
}

void simAling::showParameters()
{
    printf("\nvariableNumber e: %d, clauseNumber e: %d\n", variableNumber, clauseNumber);
}

int simAling::solutionScore(std::vector<char>& bits)
{
    int satisfiedClauses = 0;
    for (int i = 0; i < clauseNumber; ++i)
    {
        bool ok = 1;
        for (int j = 0; j < clause[i].size(); ++j)
            if (clause[i][j] > 0)
            {
                if (bits[clause[i][j] - 1] == 1)
                {
                    satisfiedClauses++;
                    ok = 0;
                    break;
                }
            }
            else if (bits[abs(clause[i][j]) - 1] == 0)
            {
                satisfiedClauses++;
                ok = 0;
                break;
            }
    }
    return satisfiedClauses;

}

float simAling::Sa()
{
	if (variableNumber == 0)
		return -1;
	std::vector<char>bits;
	std::vector<int>selectCandidates;
	srand(clock());
	for (int i = 0; i < variableNumber; ++i)
	{
		bits.push_back(rand() % 2);
	}
	double temperature = 100;
	int max = solutionScore(bits);
	int minValue = max;
	std::cout << max << '\n';
	int plateaucounter = 0;
	int plateauvalue = clauseNumber - max;
	while (plateaucounter < 100 && temperature > 0.0000001)
	{
		for (int i = 0; i < 5000; ++i)
		{
			int position = rand() % variableNumber;
			bits[position] = !bits[position];
			int aux = solutionScore(bits);
			if (aux > max)
				max = aux;
			else if (Random() < exp(-1 * abs(aux - max) / temperature))
			{
				max = aux;
			}
			else
				bits[position] = !bits[position];
		}
		temperature *= .95;
		int unsat = clauseNumber - max;
		if (unsat == 0)
		{
			return 100;
		}
		if (unsat < minValue)
			minValue = unsat;
		if (plateauvalue == unsat)
			plateaucounter++;
		else
		{
			plateaucounter = 0;
			plateauvalue = unsat;
		}
	}
	double rez = max;
	rez /= clauseNumber;
	rez *= 100;
	return rez;
}
