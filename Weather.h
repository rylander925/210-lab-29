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
    map<EffectMultipliers, int> severityWeights;
    double baselineTemperature;
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
    LocationProfile locationProfile;

    static const double COLD_TEMP_MULT;
    static const double HOT_TEMP_MULT;
    static const double SNOW_COLD_MULT;
    static const double RAIN_COLD_MULT;
    static const double WIND_COLD_MULT;
    static const double LIGHT_PROBABILITY_MULT; 
    static const double HEAVY_PROBABILITY_MULT;
    static const double LIGHT_TEMP_EXP;
    static const double HEAVY_TEMP_EXP;

    void DayWeatherCycle() {
        //random chance to keep current weather condition, or roll weather conditions again (allowing repeats)
        //roll severity
        if (!RollProbability(persistance)) {
            //Increase probabilities based on geopraphic multipliers
            auto effectiveWeights = weatherProfile.severityWeights;
            effectiveWeights.at(MEDIUM) *= locationProfile.multipliers.at(SEVERITY_COEFFICIENT);
            effectiveWeights.at(HEAVY) *= locationProfile.multipliers.at(SEVERITY_COEFFICIENT);
            
            //Roll modified weights 
           severity = RollWeights(effectiveWeights);
        }

        //roll precipitation
        if (!RollProbability(persistance)) {
            auto effectiveWeights = weatherProfile.precipitationWeights;
            effectiveWeights.at(RAIN) *= locationProfile.multipliers.at(HUMIDITY_COEFFICIENT);
            effectiveWeights.at(SNOW) *= locationProfile.multipliers.at(HUMIDITY_COEFFICIENT);

            precipitation = RollWeights(effectiveWeights);
        }

        //roll wind
        if (!RollProbability(persistance)) {
            auto effectiveWeights = weatherProfile.weatherWeights;
            effectiveWeights.at(WIND) *= locationProfile.multipliers.at(WIND_COEFFICIENT);

            wind = RollWeights(effectiveWeights);
        }

        //roll temperature
        if (!RollProbability(persistance)) {
            auto effectiveWeights = weatherProfile.temperatureWeights;

            //Increase probability of cold based on rain/snow and severity
            switch(precipitation) {
                case SNOW: 
                    effectiveWeights.at(COLD) *= SNOW_COLD_MULT; //allow follow through
                case RAIN: 
                    effectiveWeights.at(COLD) *= RAIN_COLD_MULT;
                    switch(severity) {
                        case LIGHT: effectiveWeights.at(COLD) *= LIGHT_PROBABILITY_MULT; break;
                        case HEAVY: effectiveWeights.at(COLD) *= HEAVY_PROBABILITY_MULT; break;
                    }
                    break;
            }

            //Increase probability of cold based on wind and severity
            if (wind == WIND) {
                effectiveWeights.at(COLD) *= WIND_COLD_MULT;
                switch(severity) {
                    case LIGHT: effectiveWeights.at(COLD) *= LIGHT_PROBABILITY_MULT; break;//will be an integer
                    case HEAVY: effectiveWeights.at(COLD) *= HEAVY_PROBABILITY_MULT; break;
                }
            }

            //Roll temperature event and determine temperature
            switch(RollWeights(effectiveWeights)) {
                double mult = 1;
                case COLD: mult *= COLD_TEMP_MULT; break;
                case HOT:  mult *= HOT_TEMP_MULT;  break;
                default:
                    switch(severity) {
                        case LIGHT: mult = pow(mult, LIGHT_TEMP_EXP); break;
                        case HEAVY: mult = pow(mult, HEAVY_TEMP_EXP); break;
                    }
                    temperature = weatherProfile.baselineTemperature * mult;
            }
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

const double Weather::COLD_TEMP_MULT = 0.85;
const double Weather::HOT_TEMP_MULT = 1.15;
const double Weather::SNOW_COLD_MULT = 5;
const double Weather::RAIN_COLD_MULT = 2;
const double Weather::WIND_COLD_MULT = 1.5;
const double Weather::LIGHT_PROBABILITY_MULT = 0.75;
const double Weather::HEAVY_PROBABILITY_MULT = 2; 
const double Weather::LIGHT_TEMP_EXP = 0.5;
const double Weather::HEAVY_TEMP_EXP = 2;

#endif