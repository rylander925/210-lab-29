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

//Define enum of possible weather events
//Values are stored as weights
enum PrecipitationEvent { RAIN, SNOW, NEITHER };
enum TemperatureEvent { COLD, HOT, TEMPERATE };
enum ClimateEvent { WIND, NORMAL };

//Increase severity of event, does not apply to temperate condition
//Values stored as weights of probability, effect is termined in weather function
enum EffectMultipliers { LIGHT, MEDIUM, HEAVY };

//Raise the power of probabilities by 1/k, where k is the probability
//High k is more probable, low k is imporbable
//(k=2 is rolling with advantage, k=1/2 is rolling with disadvantage)
enum GeographicMultipliers { TEMPERATURE_COEFFICIENT, HUMIDITY_COEFFICIENT, WIND_COEFFICIENT};

//Define enum of possible age events
enum AgeEvent { DISEASE, EATEN };

//Define function to simulate affects of weather events on nutrient levels for one day
//Pass maps of probabilities; can use an array and use enums as indeces, but map forces explicit use of names
    //Parameters: farm plot, map of weights
void WeatherFarm(FarmPlot& farm, map<ClimateEvent, double> weatherProbabilities);


const map<AgeEvent, 

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