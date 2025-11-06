/*
COMSC-210 | Lab 29 | Rylan Der
IDE Used: Visual studio code 
*/

//Include necessary headers, including for custom data types
#include <map>
#include <array>
#include <list>
#include "PlantSpecies.h"
#include "FarmPlot.h"

using namespace std;

//Define function to simulate affects of weather events on nutrient levels for one day
//Pass a map of probabilities, which change based on season
    //Parameters: farm plot, map of weights
void WeatherFarm(FarmPlot& farm, map<string, double> weatherProbabilities);

//Define function to simulate random garden events (distinct from weather)
    //Parameters: farm plot
void AgeFarm(FarmPlot& farm, map<string, double> timeProbabilities);

//Define function to simulate watering event
    //Parameters: farm plot, water amount
void WaterFarm(FarmPlot& farm);
    

//Define function to simulate plant growth
    //Parameters: farm plot

//Define main function
    /*
        Read garden node data into map of crops, array of sprinklers, and 2D array of garden nodes

        Determine season

        Determine fertilzation frequency

        Begin time based simulation: (Total of 90 one day time intervals)
            For each interval:
                simulate weather events and random time events
                simulate growth cycle (call FarmPlot method)

            Every 7 time intervals (1 week), output map contents and 2D garden plot (Call Print functions for FarmPlot)
            Every fertilization frequency number of time intervals, simulate fertilization events (call UpdateSoil FarmPlot method)
            Every watering frequency number of time intervals, simulate watering events (call UpdateWater FarmPlot method)
        
        After simulation, output garden and plant data
    */