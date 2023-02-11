#include <iostream>
#include "AG.hpp"
#include "simAling.h"
#include <string>
#include <vector>
#include <fstream>

//#include "readFile.h"
#define ITERATII 10
using namespace std;

char *fisierName = (char*)"files/uf75-01.cnf";

/* In the following funcitons, an instance of a class is created multiple times.
    To assure that the results are reliable, the algorithm is executed by ITERATII times*/
void startSA() {
    //printf("START\n");
    simAling a(fisierName);
    a.showParameters();
    clock_t start, stop;
    int temp = 0;
    float percentage = 0;
    double mediumTime = 0;
    for (int i = 1; i <= ITERATII; i++) {
        start = clock();
        temp=a.Sa();
        stop = clock();
        if (temp == -1) {
            percentage = 0;
            break;
        }
        printf("For the iteration: %d, the SA algorithm took: %f, had a clause rate of:%f and was: ", i, (double)((double)(stop - start) / (double)(CLOCKS_PER_SEC)), (double)temp);
        mediumTime = mediumTime + (double)((double)(stop - start) / (double)(CLOCKS_PER_SEC));
        if (mediumTime != (double)((double)(stop - start) / (double)(CLOCKS_PER_SEC))) {
            mediumTime /= 2;
        }
        if (temp == 100)
            cout << "successful.\n";
        else
            cout << "Unsuccessful.\n";
        percentage += temp;
    }
    percentage /= ITERATII*100;
    percentage *= 100;
    cout << "\nRezultatul total: " << percentage;
    printf("\nTimpul mediu: %f", mediumTime);
    return;
}
void startGA() {
    aGenetic a(fisierName);
    clock_t start, stop;
    a.showParameters();
    float percentage = 0;
    double mediumTime = 0;
    for (int i = 0; i < ITERATII/2; i++) {
        start = clock();
        int temp = a.GA();
        stop = clock();
        if (temp == -1) {
            percentage = 0;
            break;
        }
        printf("For the iteration: %d, the GA algorithm took: %f, had a clause rate of:%f and was: ", i,(double)((double)(stop - start) / (double)(CLOCKS_PER_SEC)), (double)(temp));
        mediumTime = mediumTime + (double)((double)(stop - start) / (double)(CLOCKS_PER_SEC));
        if (mediumTime != (double)((double)(stop - start) / (double)(CLOCKS_PER_SEC))) {
            mediumTime /= 2;
        }
        if (temp == 100)
            cout << "successful.\n";
        else
            cout << "Unsuccessful.\n";
        percentage += temp;
    }
    percentage /= (ITERATII/2*100);
    percentage *= 100;
    cout << "\nRezultatul total: " << percentage;
    printf("\nTimpul mediu: %f", mediumTime);
    //cout << "ATAT";
}

int main() {
    /* Start(GA)/(SA) is a function that starts the function of one of the algorithms,
        counts the succes rate over multiple execution (10 or 30),
        counts the time of every execution 
        and deliver the results.*/
    fisierName = (char*)"files/uf225-01.cnf";
    startGA();
    //printf("-----------------\n--------------\n");
    //startSA();
    return 0;
}
