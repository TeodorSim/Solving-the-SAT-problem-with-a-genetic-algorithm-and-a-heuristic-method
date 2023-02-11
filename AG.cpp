#include "AG.hpp"
#include <map>
#include <time.h>
#include <chrono>
#include <iostream>
#include <random>
using namespace std;
#define ITERATII 1000
#define MUTATION_PROBABILITY 0.01
#define CROSSOVER_PROBABILITY 0.7
#define POP_SIZE 100
aGenetic::aGenetic(const char *c){
    popS = 200;
    crossPlty = 0.7;
    mutationPlty  = 0.01;
    setFileToUse(c);
    openFile(variableNumber, clauseNumber, clause);
    printf("\npopulation of: %d\n", clause.size());
}
aGenetic::aGenetic()
{
    popS = 200;
    crossPlty = 0.7;
    mutationPlty = 0.01;
    openFile(variableNumber, clauseNumber, clause);
}
aGenetic::~aGenetic(){
    clause.clear();
    clause.shrink_to_fit();
}
void aGenetic::setParameters(int variableNumber, int clauseNumber, vector<vector<int>> clause){
    this->variableNumber = variableNumber;
    this->clauseNumber = clauseNumber;
    this->clause = clause;
 }
void aGenetic::showParameters(){
    printf("\nvariableNumber e: %d, clauseNumber e: %d\n", variableNumber, clauseNumber);
}

double aGenetic::getMinim(){
    //return minimClasa;
    return 0.0;
}


double aGenetic::candidat(vector<bool> candidat, int begin, int end){
    return 0.0;
}

vector<double> aGenetic::transform(vector<bool> &bitToBeTransformed){
    /*
    vector<double> rezultat;
    for(int i=0; i<dimensiune; i++){
        double x=candidat(bitToBeTransformed, i*lungime, i*lungime+lungime);
        rezultat.push_back(x);
    }
    return rezultat;
    */
    return {};
}

void aGenetic::afisare(vector<bool> &k){
    printf("\nafisare bool: \n");
    for(auto x:k)
        cout<<x<<", ";
}
double aGenetic::FitnessOf(int& solution)
{
    return solution;
}
void aGenetic::transform2(vector<vector<bool>>& population, vector<double>& solutions)
{
    /*
    solutions.clear();
    for (int i = 0; i < popS; ++i)
    {
        //revizuire transform
        auto aux = transform(population[i]);
        solutions.push_back(functionToUse(functionUsed, aux));
    }
    */
}


void aGenetic::mutate(vector<vector<char>>& population)
{
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    mt19937_64 mt_rand(seed);
    std::uniform_real_distribution<double> subUnitValueGen(0.0, 1.0);
    for (int i = 0; i < popS; ++i)
        for (int ii = 0; ii < variableNumber; ++ii)
        {
            double pMutation = subUnitValueGen(mt_rand);
            if (pMutation < mutationPlty)
                population[i][ii] = !population[i][ii];
        }
}
void aGenetic::greedyMutate(vector<vector<char>>& population, vector<int>& solutions)
{
    for (int i = 0; i < popS; ++i)
    {
        for (int j = 0; j < variableNumber; ++j)
        {
            population[i][j] = !population[i][j];
            if (solutions[i] > solutionScore(population[i]))
                population[i][j] = !population[i][j];
        }
    }
}
void aGenetic::multiGreedyMutate(vector<vector<char>>& population, vector<int>& solutions)
{

    for (int i = 0; i < popS; ++i)
    {
        int counter = 0;
        bool imprv = 1;
        while (imprv != 0)
        {
            for (int ii = 0; ii < variableNumber; ++ii)
            {
                population[i][ii] = !population[i][ii];
                auto aux = solutionScore(population[i]);
                if (solutions[i] >= aux)
                    population[i][ii] = !population[i][ii];
                else {
                    solutions[i] = aux;
                    imprv = 0;
                }

            }
            if (imprv == 0)
            {
                imprv = 1;
                counter++;
            }
            else imprv = 0;
        }
    }
}

void aGenetic::crossover(vector<vector<char>>& population)
{
    srand((unsigned int)rand());
    double r;
    map<double, vector<char>> ordering;
    vector<double> probabilityOf;
    for (int i = 0; i < popS; ++i){
        r = (double)(rand() % 998 + 1) / 1000;
        ordering.insert_or_assign(r, population[i]);
    }
    population.clear();

    for (auto i = ordering.rbegin(); i != ordering.rend(); i++) {
        population.push_back(i->second);
        probabilityOf.push_back(i->first);
    }
    std::uniform_int_distribution<int> ValueGen(1, variableNumber - 1);
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937_64 mt_rand(seed);
    for (int i = 0; i < popS; i = i + 2)
    {
        if (probabilityOf[i + 1] < crossPlty)
        {
            int cutpoint = ValueGen(mt_rand);
            for (int ii = cutpoint; ii < variableNumber; ++ii)
                swap(population[i][ii], population[i + 1][ii]);
        }
        else
            break;
    }
}

void aGenetic::uniformCrossover(vector<vector<char>>& population)
{
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937_64 mt_rand(seed);
    std::uniform_real_distribution<double> subUnitValueGen(0.0, 1.0);
    vector<double> probabilityOf;
    map<double, vector<char>> ordering;
    for (int i = 0; i < popS; ++i) {
        //probabilityOf.push_back(subUnitValueGen(mt_rand));
        ordering.insert_or_assign(subUnitValueGen(mt_rand), population[i]);
    }
    
    population.clear();
    for (auto i = ordering.rbegin(); i != ordering.rend(); i++) {
        population.push_back(i->second);
        probabilityOf.push_back(i->first);
    }
    std::uniform_int_distribution<int> ValueGen(1, variableNumber - 1);
    for (int i = 0; i < popS; i = i + 2)
    {
        for (int j = 0; j < variableNumber; ++j)
        {
            if (Random() < 0.5)
                swap(population[i][j], population[i + 1][j]);
        }
    }
}

int aGenetic::minimOf(vector<int>& solutions)
{
    int aux = INT_MIN;
    for (int i = 0; i < solutions.size(); ++i)
        if (aux < solutions[i])
            aux = solutions[i];
    return aux;
}

int aGenetic::solutionScore(vector<char>& bits)
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
void aGenetic::computeSolution(vector<vector<char>>& population, vector<int>& solutions)
{
    solutions.clear();
    for (int i = 0; i < popS; ++i)
    {
        solutions.push_back(solutionScore(population[i]));
    }
}

vector<vector<char>> aGenetic::select(vector<vector<char>>& population, vector<int>& solutions)
{
    vector<double> fitness;
    int T = 0;
    /*fitness of every candidate*/
    for (int i = 0; i < popS; ++i)
    {
        fitness.push_back(FitnessOf(solutions[i]));
        T += fitness[i];
    }
    //cout <<"Sum="<< T<<'\n';
    vector<double> probabilityOf;
    for (int i = 0; i < popS; ++i)
    {
        probabilityOf.push_back(fitness[i] / T);
    }
    vector<double> q;
    q.push_back(0);
    for (int i = 0; i < popS; ++i)
    {
        q.push_back(q[i] + probabilityOf[i]);
    }
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937_64 mt_rand(seed);
    std::uniform_real_distribution<double> subUnitValueGen(0.0, 1.0);
    vector < vector <char>> newPopulation;
    for (int i = 0; i < popS; ++i)
    {
        double r = subUnitValueGen(mt_rand);
        for (int j = 0; j < population.size(); ++j)
            if (q[j] < r && r <= q[j + 1])
            {
                newPopulation.push_back(population[j]);
                break;
            }
    }
    return newPopulation;
}
float aGenetic::GA()
{
    //validating the info's:
    if (variableNumber == 0) {
        printf("Nu au fost introduse date corecte pentru SAT!\n");
        return -1;
    }
    int t = 0;
    int SAT, maxiSAT=-1;
    vector<char>bits;
    vector<vector<char>>population;
    srand(clock());
    for (int i = 0; i < popS; ++i)
    {
        bits.clear();
        for (int ii = 0; ii < variableNumber; ++ii)
        {
            bits.push_back(rand() % 2);
        }
        population.push_back(bits);
    } /*Random population initialization*/
    //printCurrentPop(population,variableNumber);
    vector<int> solutions;
    int min = 0;
    computeSolution(population, solutions);
    while (t < ITERATII)
    {
        ++t;
        auto aux = select(population, solutions);
        population.clear();
        for (int i = 0; i < aux.size(); ++i)
            population.push_back(aux[i]);
        //crossover(population);
        uniformCrossover(population);
        mutate(population);
        greedyMutate(population, solutions);
        //multiGreedyMutate(population, solutions);
        computeSolution(population, solutions);
        if ((SAT = minimOf(solutions)) == clauseNumber)
        {
            //cout << "Solution found\n";
            return 100.0;
            //break;
        }
        else
        {
            if (SAT > min)
                min = SAT;
            if (SAT > maxiSAT)
                maxiSAT = SAT;
        }
    }
    double rez =maxiSAT;
    rez /= clauseNumber;
    rez *= 100;
    return rez;
}