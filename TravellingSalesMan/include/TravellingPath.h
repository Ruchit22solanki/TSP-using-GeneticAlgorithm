#ifndef TRAVELLINGPATH_H
#define TRAVELLINGPATH_H
#include<bits/stdc++.h>
using namespace std;
class TravellingPath
{
    private:
        vector<int > path;
        int startingCity;
        int fitness;
      public :
        static int numberOfCities;
        static int travelCost[350][350];
        TravellingPath(int startingCity);
        TravellingPath(vector<int> permutationOfCities, int startingCity);
        vector<int> getpath();
        int getStartingCity();
        int getFitness();
        void setFitness(int fitness);
        int calculateFitness();
        void PrintPath();
        vector<int> RandomSuffle();
};

#endif // TRAVELLINGPATH_H
