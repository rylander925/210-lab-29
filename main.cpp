/*
COMSC-210 | Lab 29 | Rylan Der
IDE Used: Visual studio code 
*/

//Include necessary headers, including for custom data types
#include <map>
#include <array>
#include <list>
#include "PlantSpecies.h"
#include "Soil.h"
#include "Sprinkler.h"

using namespace std;

//Define function to simulate affects of weather events on nutrient levels for one day
    //Parameters: map of crops, season

//Define function to simulate sprinklers
    //Parameters: map of crops, array of sprinklers, 2D array of garden nodes

//Define function to simulate plant growth
    //Parameters: map of crops

//Define function to simulate random garden events
    //Parameters: map of crops

//Define function to simulate fertilzation event

//Define function to read garden node data
    //Parameters: map of crops, array of sprinklers, 2D array of garden nodes, filename

//Define function to output plant data
    //Parameters: map of crops

//Define function to output garden as a 2D rectangular plot

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