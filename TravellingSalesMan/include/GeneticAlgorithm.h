#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H
#include "TravellingPath.h"
#include<bits/stdc++.h>
using namespace std;
enum SelectionType { TOURNAMENT, ROULETTE };

class GeneticAlgorithm
{
    private:
         int generationSize;
         int pathSize;
         int numberOfCities;
         int reproductionSize;
         int maxIterations;
         float mutationRate;
         int tournamentSize;
         int startingCity;
         int targetFitness;
         SelectionType selectionType;
    public :
         GeneticAlgorithm(int numberOfCities, SelectionType selectionType, int startingCity, int targetFitness);
         vector<TravellingPath* > InitialPopulation();
         vector<TravellingPath* > selection(vector<TravellingPath*> population);
         TravellingPath* rouletteSelection(vector<TravellingPath* > population);
         vector<TravellingPath* > pickNRandomElements(vector<TravellingPath* > List, int n);
         TravellingPath* tournamentSelection(vector<TravellingPath* > population);
         TravellingPath* mutate(TravellingPath* path);
         vector<TravellingPath* > createGeneration(vector<TravellingPath* > population);
         vector<TravellingPath* > crossover(vector<TravellingPath* > parents);
         double random(double a,double b);
         bool com(TravellingPath * a,TravellingPath *b);
         TravellingPath* optimize();

};

#endif // GENETICALGORITHM_H
