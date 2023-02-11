#pragma once
#include <vector>
#include "functii.h"
class simAling:public functii
{
	int variableNumber=0, clauseNumber=0;
	std::vector<std::vector<int>> clause{};
public:
	simAling(const char *c);
	simAling();
	~simAling();

	void setParameters(int variableNumber, int clauseNumber, std::vector<std::vector<int>> clause);
	void showParameters();
	int solutionScore(std::vector<char>& bits);
	float Sa();
};