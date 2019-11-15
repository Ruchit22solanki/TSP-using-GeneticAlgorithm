#include<bits/stdc++.h>
#include<random>
#include  "TravellingPath.h"
#include   "GeneticAlgorithm.h"
using namespace std;
void PrintCost(int numberofCities)
{
     for(int i=0;i<numberofCities;i++)
     {
         for(int j=0;j<numberofCities;j++)
         {
             cout<<TravellingPath::travelCost[i][j];
             if(TravellingPath::travelCost[i][j]>9)
                cout<<" ";
             else
                cout<<"  ";
         }
         cout<<endl;
     }
}
int main()
{
     srand((unsigned) time(NULL));
     int  numberofCities;
     cout<<"Enter The Number Of Cities "<<endl;
     cin>>numberofCities;
     TravellingPath::numberOfCities=numberofCities;
     int startingCity;
city:cout<<"Enter The StartingCity"<<endl;
     cin>>startingCity;
     if(startingCity<0 || startingCity>=numberofCities)
     {
          goto city;
     }
     int flag;
     cout<<"Enter the Flag"<<endl;
     cin>>flag;
     for(int i=0;i<numberofCities;i++)
     {
        for(int j=i;j<numberofCities;j++)
        {

             if(flag==0)
             {
                 if(i==j)
                 TravellingPath::travelCost[i][j]=0;
                 else
                 {
                    int cost= rand() % 99 + 1;
                    TravellingPath::travelCost[i][j]=cost;
                    TravellingPath::travelCost[j][i]=cost;
                 }
             }
             else if(flag==1)
             {
                 if(i==j)
                 TravellingPath::travelCost[i][j]=0;
                 else
                 {

                     cout<<"enter a cost of traveling city "<<i<<" to "<<j<<endl;
                     cin>>TravellingPath::travelCost[i][j];
                     TravellingPath::travelCost[j][i]=TravellingPath::travelCost[i][j];
                 }
             }
             else if(flag==2)
             {
                     fstream cost;
                     cost.open("TravellingCost.txt",fstream::in);
                     if (!cost)
                     {
                            cout << "Cannot open file.\n";
                            return 0;
                     }
                     for (int i=0;i<numberofCities;i++)
                     {
                            for (int j=0;j<numberofCities;j++)
                              cost >> TravellingPath::travelCost[i][j];
                     }
                      cost.close();
            }
        }
     }
     if(flag==0 || flag==1)
     {
         fstream cost;
         cost.open("TravellingCost.txt",fstream::out);
         if (!cost)
         {
                cout << "Cannot open file.\n";
                return 0;
         }
         for (int i=0;i<numberofCities;i++)
         {
                for (int j=0;j<numberofCities;j++)
                {
                  cost << TravellingPath::travelCost[i][j];
                  if(TravellingPath::travelCost[i][j]>9)
                    cost<<" ";
                  else
                    cost<<"  ";
                }
                cost<<"\n";
          }
          cost.close();
     }
     cout<<"---------------------Travelling Cost--------------------"<<endl;
     //PrintCost(numberofCities);
     cout<<"--------------------------------------------------------"<<endl;
     GeneticAlgorithm *geneticAlgorithm =new GeneticAlgorithm(numberofCities,SelectionType::TOURNAMENT,startingCity, 0);
     TravellingPath* result = geneticAlgorithm->optimize();
     cout<<"------------------------Final Minimum Cost Path----------------"<<endl;
     result->PrintPath();
     cout<<"Travelling cost :"<<result->getFitness()<<endl;
     cout<<"---------------------------------------------------------------"<<endl;
     delete geneticAlgorithm;


}
