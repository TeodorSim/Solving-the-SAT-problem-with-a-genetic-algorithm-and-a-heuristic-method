#pragma once
#include <vector>
class functii
{
	char* fisier;
public:
	functii();
	~functii();
	void setFileToUse(const char* c);

	virtual void setParameters(int variableNumber, int clauseNumber, std::vector<std::vector<int>> clause)=0;
	virtual void showParameters()=0;
	virtual int solutionScore(std::vector<char>& bits)=0;

	double Random();
	bool openFile(int& variableNumber, int& clauseNumber, std::vector<std::vector<int>>& clause);
};

