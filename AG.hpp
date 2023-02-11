#pragma once
#include <vector>
#include <time.h>
#include <chrono>
#include "functii.h"

using namespace std;
class aGenetic:public functii {
    int popS;
    float crossPlty, mutationPlty;
    int variableNumber, clauseNumber;
    std::vector<std::vector<int>> clause;
public:
    aGenetic(const char*);
    aGenetic();
    ~aGenetic();
    void setParameters(int variableNumber, int clauseNumber, vector<vector<int>> clause);
    void showParameters();

    void afisare(vector<bool>& k);
    vector<double> transform(vector<bool>& bitToBeTransformed);
    void transform2(vector<vector<bool>>& population, vector<double>& solutions);
    double candidat(vector<bool> candidat, int begin, int end);
    double getMinim();


    double FitnessOf(int& solution);
    
    void multiGreedyMutate(vector<vector<char>>& population, vector<int>& solutions);
    void greedyMutate(vector<vector<char>>& population, vector<int>& solutions);
    void mutate(vector<vector<char>>& population);

    vector<vector<char>> select(vector<vector<char>>& population, vector<int>& solutions);
    void uniformCrossover(vector<vector<char>>& population);
    void crossover(vector<vector<char>>& population);
    int minimOf(vector<int>& solutions);
    int solutionScore(vector<char>& bits);
    void computeSolution(vector<vector<char>>& population, vector<int>& solutions);

    float GA();

};


