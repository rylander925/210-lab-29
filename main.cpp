/*
COMSC-210 | Lab 29 | Rylan Der
IDE Used: Visual studio code 
*/

//Include necessary headers, including for custom data types
#include <map>
#include <array>
#include <list>
#include <iostream>
#include "PlantSpecies.h"
#include "FarmPlot.h"

using namespace std;

//Define enum of possible weather events
//Values are stored as weights
enum PrecipitationEvent { RAIN, SNOW, NO_PRECIPITATION };
enum TemperatureEvent { COLD, HOT, TEMPERATE };
enum WeatherEvent { WIND, NO_WEATHER };

//Increase severity of event, does not apply to temperate condition
//Values stored as weights of probability, effect is termined in weather function
enum EffectMultipliers { LIGHT, MEDIUM, HEAVY };

//Raise the weights of certain events
enum GeographicMultipliers { TEMPERATURE_COEFFICIENT, HUMIDITY_COEFFICIENT, WIND_COEFFICIENT, SEVERITY_COEFFICIENT};

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
int main() {
    const string FILENAME_SEASON;
    const string FILENAME_LOCALE;
    const string FILENAME_FARM;
    const int SIMULATION_PERIOD = 90;
    const int OUTPUT_INTERVAL = 7;
    //Declare variables
    WeatherProfile season;
    LocationProfile locale;
    string name;
    int fertilizationInterval;
    int wateringInterval;

    //Read garden node data into map of crops through constructor
    FarmPlot farm(name, FILENAME_FARM);

    //Read location and weather profile data
    season = ReadWeatherProfile(FILENAME_SEASON);
    locale = ReadLocationProfile(FILENAME_LOCALE);

    //Determine fertilzation frequency from input
    //Add prompt statements and input validation
    cin >> fertilizationInterval;
    cin >> wateringInterval;

    //Begin time based simulation: (Total of 90 one day time intervals)
    for (int day = 1; day <= SIMULATION_PERIOD; day++) {
        //For each interval:
            //simulate weather events and random time events
            WeatherFarm(farm, season, locale);

            //simulate growth cycle (call FarmPlot method)
            farm.GrowthCycle();

        //Every 7 time intervals (1 week), output map contents and 2D garden plot (Call Print functions for FarmPlot)
        if (day % OUTPUT_INTERVAL == 0) {
            //Add counter for # of output intervals
            farm.PrintInformation();
            farm.PrintPlot();
        }

        //Every fertilization frequency number of time intervals, simulate fertilization events (call UpdateSoil FarmPlot method)
        //Every watering frequency number of time intervals, simulate watering events (call UpdateWater FarmPlot method)
        //(Takes same format as above display interval)
    }
    
    //After simulation, output garden and plant data
    //(Add some message that simulation is over)
    farm.PrintInformation();
    farm.PrintPlot();
}

WeatherProfile ReadWeatherProfile(string filename) {
    WeatherProfile season;

    cout << "Reading weather profile..." << "...add implementation" << endl;

    //Verify file open and read
    
    //dummy weights for now
    season.precipitationWeights = {{RAIN, 1}, {SNOW, 1}, {NO_PRECIPITATION, 1}};
    season.weatherWeights = {{WIND, 1}, {NO_WEATHER, 1}};
    season.temperatureWeights = {{COLD, 1}, {HOT, 1}, {TEMPERATE, 1}};

    return season;
}

LocationProfile ReadLocationProfile(string filename) {
    LocationProfile locale;

    cout << "Reading location profile..." << "...add implementation" << endl;

    //Verify file open and read
    
    //dummy weights for now
    locale.multipliers = {{TEMPERATURE_COEFFICIENT, 1}, {HUMIDITY_COEFFICIENT, 1}, {WIND_COEFFICIENT, 1}, {SEVERITY_COEFFICIENT, 1}};
    locale.randomEventWegiths = {{EATEN, 1}, {DISEASE, 1}};

    return locale;
}

//Define function to simulate affects of weather events on nutrient levels for one day
    //Parameters: farm plot, Weather profile and location profile
void WeatherFarm(FarmPlot& farm, WeatherProfile season, LocationProfile locale) {
    cout << "Weathering farm..." << "...add implementation" << endl;
}