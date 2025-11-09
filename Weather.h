#ifndef WEATHER_H
#define WEATHER_H

#include <map>
#include <set>
#include <string>
#include <fstream>
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

struct Weather {
    double persistance;
    double temperature;
    PrecipitationEvent precipitation;
    WeatherEvent wind;
    EffectMultipliers severity;
    WeatherProfile weatherProfile;
    LocationProfile LocationProfile;

    void DayCycle() {
        //random chance to keep current weather condition, or roll weather conditions again (allowing repeats)
        if (RollProbability(persistance)) {
            
        }
        
    }

    /**
     * Given a map of events with associated integer weights, rolls a random event
     * @param weights Map of events with an integer representing the 'weight' of that event occuring relative to other events
     * @return Key associated with rolled event
     * @note Assumes events are mutually exclusive
     */
    template <typename T>
    T RollWeights (map<T, int> weights) {
        int total = 0;
        int num;
        T result;
        for (auto pair : weights) total += pair.second;
        num = rand() % total;           //number from 0 to total - 1
        for (auto pair : weights) { 
            num -= pair.second;         //since max is total - 1, negative val indicates num is in current weight range 
            if (num < 0) {
                result = pair.first;
                break;                  //store resulting range, and exit loop; uses break to make use of ranged based for loop
            }
        }
        return result;
    }

    /**
     * Given the weights of a true or false condition, rolls true or false
     * @param trueWeight Weight of true probability occuring, as an integer representing relative likelihood
     * @param falseWeight Weight of false probability occuring
     * @return Bool based on result of the roll
     */
    bool RollWeights (int trueWeight, int falseWeight) {
        return (rand() % (trueWeight + falseWeight) ) < trueWeight;
    }

    /**
     * Rolls a probability
     * @param probability Fraction from (0, 1) of probability occuring
     * @param decimals Decimal places considered in the probability, e.g. for 0.12345, a decimal of 2 will roll 12%, and a default decimal of 5 will roll 12.345%.
     * @return Bool based on result of roll
     */
    bool RollProbability(double probability, int decimals = 5) {
        int mult = pow(10, decimals); //represents decimal places of probability to consider
        return RollWeights(mult * probability, mult * (1 - probability)); //rolls probability by converting to weights, and rolling the weights
    }
};

#endif