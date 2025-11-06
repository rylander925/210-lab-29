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
enum WeatherEvent { WIND, NORMAL };

//Increase severity of event, does not apply to temperate condition
//Values stored as weights of probability, effect is termined in weather function
enum EffectMultipliers { LIGHT, MEDIUM, HEAVY };

//Raise the weights of certain events
enum GeographicMultipliers { TEMPERATURE_COEFFICIENT, HUMIDITY_COEFFICIENT, WIND_COEFFICIENT};

//Define enum of possible age events, maps should be stored as integer weights
enum AgeEvent { DISEASE, EATEN };

//hold weights for climate as a struct for organization purposes
//Pass maps of probabilities; can use an array w/ enums as indeces, but map forces explicit use of names
struct WeatherProfile {
    map<PrecipitationEvent, int> precipitationWeights;
    map<TemperatureEvent, int> temperatureWeights; 
    map<WeatherEvent, int> weatherWeights;
};

//hold weights for locale as a struct for organization purposes
struct LocationProfile {
    map<GeographicMultipliers, double> multipliers;
    map<AgeEvent, int> randomEventWegiths;
};

//Define function to read weights of weather weights
    //Parameters: name of file to read from; should contain one weather profile (i.e. winter.txt separate from spring.txt)
    //Structured to read until file end, with each line as a string of event name then a number (double or int)
    //Attempt to add to the map; map will not add if already added
WeatherProfile ReadWeatherProfile(string filename);

//Define function to read weights of location weights
    //Parameters: name of file to read from; should contain one location (i.e. desert.txt separate from coast.txt)
    //Structured to read until file end, with each line as a string of event name then a number (double or int)
    //Attempt to add to the map; map will not add if already added
LocationProfile ReadLocationProfile(string filename);

//Define function to simulate affects of weather events on nutrient levels for one day
    //Parameters: farm plot, Weather profile and location profile
void WeatherFarm(FarmPlot& farm, WeatherProfile season, LocationProfile locale);

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