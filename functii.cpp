#include "functii.h"
#include <cstdlib>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <string>
functii::functii()
{
	fisier = (char*)malloc(100);
	if (fisier) {
		// Always check that the return value of malloc() is not NULL
		//strcpy(fisier, "files/uf20-01.cnf");
		strcpy_s(fisier, strlen("files/uf20-01.cnf")+1, "files/uf20-01.cnf");
	}
}
functii::~functii()
{
	free(fisier);
}
void functii::setFileToUse(const char* c)
{
	strcpy_s(fisier, strlen(c) + 1, c);
}
double functii::Random()
{
	return (double)((double)(rand() % 100000) / (double)100000);
}

bool functii::openFile(int& variableNumber, int& clauseNumber, std::vector<std::vector<int>>& clause)
{
	std::ifstream fin(fisier);
	//char comment[256];
	//fin.getline(comment,256);
	//cout << comment << '\n';
	std::string problem;
	char p;
	fin >> p >> problem;
	if (p != 'p' || problem != "cnf")
	{
		std::cout << "Bad file" << '\n';
		return 0;
	}
	fin >> variableNumber >> clauseNumber;
	int aux, count = 0;
	clause.resize(clauseNumber);
	while (count < clauseNumber)
	{
		fin >> aux;
		if (aux == 0)
			count++;
		else
			clause[count].push_back(aux);
	}
	//auto temp = clause[clauseNumber - 1];
	//afisareVector(temp);
	return 1;
}