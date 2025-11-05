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
    //Parameters: farm plot, season

//Define function to simulate random garden events (distinct from weather)
    //Parameters: farm plot

//Define function to simulate watering event
    //Parameters: farm plot, water amount
    
//Define function to simulate fertilzation event
    //Parameters: farm plot, fertilizer amount

//Define function to simulate plant growth
    //Parameters: farm plot

//Define main function
    /*
        Read garden node data into map of crops, array of sprinklers, and 2D array of garden nodes

        Determine season

        Determine fertilzation frequency

        Begin time based simulation: (Total of 90 one day time intervals)
            For each interval:
                Water crops, simulate weather events, simulate sprinklers

            Every 7 time intervals (1 week), output map contents and 2D garden plot
            Every fertilization frequency number of time intervals, simulate fertilization events
        
        After simulation, output garden and plant data
    */