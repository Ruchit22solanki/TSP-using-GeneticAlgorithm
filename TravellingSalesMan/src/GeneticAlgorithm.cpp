#include "GeneticAlgorithm.h"

inline double GeneticAlgorithm::random(double a,double b)
{
        unsigned seed=rand();
        default_random_engine generator(seed);

        uniform_real_distribution<double> distribution(a, b);
        double r= distribution(generator);
        return r;
}
GeneticAlgorithm::GeneticAlgorithm(int numberOfCities, SelectionType selectionType, int startingCity, int targetFitness)
{
        this->numberOfCities = numberOfCities;
        this->pathSize = numberOfCities-1;
        this->selectionType = selectionType;
        this->startingCity = startingCity;
        this->targetFitness = targetFitness;

        generationSize = 1000;
        reproductionSize = 500;
        maxIterations = 50;
        mutationRate = 0.28f;
        tournamentSize =200;
}
vector<TravellingPath* > GeneticAlgorithm::InitialPopulation()
{
        vector<TravellingPath*> population;
        for(int i=0; i<generationSize; i++)
        {
            population.push_back(new TravellingPath(startingCity));
        }
        return population;
}
vector<TravellingPath* > GeneticAlgorithm::selection(vector<TravellingPath* > population)
{
        vector<TravellingPath* > selected;

        for(int i=0; i<reproductionSize; i++)
        {
            if(selectionType == ROULETTE)
            {
                selected.push_back(rouletteSelection(population));

            }
            else if(selectionType ==TOURNAMENT)
            {
                selected.push_back(tournamentSelection(population));


            }
        }

        return selected;
}
TravellingPath* GeneticAlgorithm::rouletteSelection(vector<TravellingPath* > population)
{
        long long int totalsum=0;
        for(int i=0;i<population.size();i++)
        {
               totalsum+=population[i]->getFitness();
        }

        double r=random(0,1);
        double currentSum = 0;
        for(int i=0;i<population.size();i++)
        {
            currentSum += (double) 1/((double)population[i]->getFitness()*totalsum);
            if(currentSum>=r)
            {

                return population[i];
            }
        }
        int selectRandom = random(0,generationSize);
        return population[selectRandom];
}
vector<TravellingPath* > GeneticAlgorithm::pickNRandomElements(vector<TravellingPath* > List, int n)
{

        int length = List.size();
        vector<TravellingPath* > result;
        if (length < n)
            return result;

        for (int i = length - 1; i >= length - n; --i)
        {
            swap(List[i],List[random(0,i+1)]);
        }
        for(int i=length-n;i<length;i++)
        result.push_back(List[i]);
        return result;
}
TravellingPath* GeneticAlgorithm::tournamentSelection(vector<TravellingPath* > population)
{
        vector<TravellingPath* > selected = pickNRandomElements(population,tournamentSize);
        int fitness=INT_MAX;
        TravellingPath *mn=new TravellingPath(0);
        for(int i=0;i<selected.size();i++)
        {
              if(selected[i]->getFitness()<fitness)
              {
                   mn=selected[i];
                   fitness=selected[i]->getFitness();
              }
        }
        return mn;

}
TravellingPath* GeneticAlgorithm::mutate(TravellingPath* path)
 {

        double mutate= random(0,1);
        if(mutate<mutationRate)
        {
            vector<int> newPath = path->getpath();
            swap(newPath[random(0,pathSize)],newPath[random(0,pathSize)]);
            return new TravellingPath(newPath,startingCity);
        }
        return path;
}
vector<TravellingPath *> GeneticAlgorithm::createGeneration(vector<TravellingPath *> population)
{
        vector<TravellingPath*> generation;
        int currentGenerationSize = 0;
        while(currentGenerationSize < generationSize)
        {
            vector<TravellingPath*> parents = pickNRandomElements(population,2);
            vector<TravellingPath*> children = crossover(parents);
            children[0]=mutate(children[0]);
            children[1]=mutate(children[1]);
            for(int i=0;i<children.size();i++)
            {
                generation.push_back(children[i]);
            }
            currentGenerationSize+=2;
        }
        return generation;
}
vector<TravellingPath *> GeneticAlgorithm::crossover(vector<TravellingPath *> parents)
{
        int breakpoint= random(0,pathSize);
        vector<TravellingPath *> children ;
        vector<int> parent1Genome(parents[0]->getpath());
        vector<int> parent2Genome(parents[1]->getpath());

        for(int i = 0; i<breakpoint; i++)
        {
            int newVal = parent2Genome[i];
            int indexOfnewValue=find(parent1Genome.begin(), parent1Genome.end(), newVal)-parent1Genome.begin();
            swap(parent1Genome[indexOfnewValue],parent1Genome[i]);
        }
        children.push_back(new TravellingPath(parent1Genome,startingCity));
        parent1Genome = parents[0]->getpath();

        for(int i = breakpoint; i<pathSize; i++)
        {
            int newVal = parent1Genome[i];
            int indexOfnewValue=find(parent2Genome.begin(), parent2Genome.end(), newVal)-parent2Genome.begin();
            swap(parent2Genome[i],parent2Genome[indexOfnewValue]);
        }
        children.push_back(new TravellingPath(parent2Genome,startingCity));

        return children;
}
TravellingPath* GeneticAlgorithm::optimize()
{
        vector<TravellingPath* > population = InitialPopulation();


        TravellingPath *globalBestGenome = population[0];
        int Fitness=population[0]->getFitness();
        int counter=0;
        int i=0;
        while(1)
        {
               cout<<"After Iteration "<<i<<endl;
               globalBestGenome->PrintPath();
               cout<<"Travelling Cost :"<<globalBestGenome->getFitness()<<endl;
               cout<<endl;

            vector<TravellingPath*> selected = selection(population);
            population = createGeneration(selected);

            for(int j=0;j<population.size();j++)
            {
                  if(population[j]->getFitness()<globalBestGenome->getFitness())
                  {
                       globalBestGenome=population[j];
                  }
            }
            if(Fitness==globalBestGenome->getFitness())
                   counter++;
            else
            {
                Fitness=globalBestGenome->getFitness();
                counter=0;
            }
            i++;
            if(counter==maxIterations)
                   break;
            if(globalBestGenome->getFitness() < targetFitness)
                break;
        }
        return globalBestGenome;
}


