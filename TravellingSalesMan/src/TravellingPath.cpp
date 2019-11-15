#include "TravellingPath.h"
int TravellingPath::numberOfCities=0;
int TravellingPath::travelCost[350][350]={{0}};
TravellingPath::TravellingPath(int startingCity)
{

        this->startingCity=startingCity;
        this->path = RandomSuffle();
        this->fitness = calculateFitness();

}
TravellingPath::TravellingPath(vector<int> permutationOfCities,int startingCity)
{


        this->startingCity=startingCity;
        this->path = permutationOfCities;
        this->fitness = calculateFitness();
}
void TravellingPath::PrintPath()
{
    for(int i=0;i<this->path.size();i++)
    {
       cout<<path[i]<<" ";
    }
    cout<<endl;
}
vector<int> TravellingPath::RandomSuffle()
{
       vector<int> result;
       for(int i=0;i<TravellingPath::numberOfCities;i++)
       {
              if(i!=startingCity)
              {
                  result.push_back(i);
              }
       }

      unsigned seed = rand();
      shuffle(result.begin(), result.end(), default_random_engine(seed));
      return result;
}

vector<int> TravellingPath::getpath()
{
        return this->path;
}
int TravellingPath::getStartingCity()
{
        return this->startingCity;
}
int TravellingPath::getFitness()
{
        return this->fitness;
}
void TravellingPath::setFitness(int fitness)
{
        this->fitness = fitness;
}
int TravellingPath::calculateFitness()
{
        int fitness = 0;
        int currentCity = this->startingCity;
        for (int i=0;i<path.size();i++)
        {
            fitness +=travelCost[currentCity][path[i]];
            currentCity = path[i];
        }
        fitness +=travelCost[path[numberOfCities-2]][startingCity];
        return fitness;
}


