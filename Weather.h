#ifndef WEATHER_H
#define WEATHER_H

#include <map>
#include <set>
#include <string>
#include <fstream>
#include "FarmPlot.h"
#include "Util.h"

using namespace std;

//Define enum of possible weather events
//Values are stored as weights
enum PrecipitationEvent { RAIN, SNOW, NO_PRECIPITATION };
enum TemperatureEvent { COLD, TEMPERATE, HOT };
enum WeatherEvent { WIND, NO_WEATHER };

//Increase severity of event, does not apply to temperate condition
//Values stored as weights of probability, effect is termined in weather function
enum EffectMultipliers { LIGHT, MEDIUM, HEAVY };

//Raise the weights of certain events
enum GeographicMultipliers { HUMIDITY_COEFFICIENT, WIND_COEFFICIENT, SEVERITY_COEFFICIENT};

//Define enum of possible age events, maps should be stored as integer weights
enum AgeEvent { DISEASE, EATEN, NO_RANDOM_EVENTS };

//hold weights for climate as a struct for organization purposes
//Pass maps of probabilities; can use an array w/ enums as indeces, but map forces explicit use of names
struct WeatherProfile {
    string name;
    map<PrecipitationEvent, int> precipitationWeights;
    map<TemperatureEvent, int> temperatureWeights; 
    map<WeatherEvent, int> weatherWeights;
    map<EffectMultipliers, int> severityWeights;
    double baselineTemperatureMult;
    double persistance;

    WeatherProfile() {
        name = "No name";
        precipitationWeights = {{RAIN, 0}, {SNOW, 0}, {NO_PRECIPITATION, 0}};
        temperatureWeights = {{COLD, 0}, {TEMPERATE, 0}, {HOT, 0}};
        weatherWeights = {{WIND, 0}, {NO_WEATHER, 0}};
        severityWeights = {{LIGHT, 0}, {MEDIUM, 0}, {HEAVY, 0}};
        baselineTemperatureMult = 1.0;
        persistance = 0;
    }

    /**
     * Read weather profile data from file, formatted with weights as integers:
     * name (as string)
     * rain snow no_precipitation
     * cold temperate hot
     * wind no_wind
     * light medium heavy
     * baseLineTemperatureMult (as double)
     * @param filename
     * 
     */
    void ReadProfile(string filename) {
        string rainLine, temperatureLine, weatherLine, severityLine;
        stringstream ss;

        //Open file stream and read contents to variables and lines holding weights
        ifstream infile;
        Util::VerifyFileOpen(infile, filename);
        getline(infile, name);
        getline(infile, rainLine);
        getline(infile, temperatureLine);
        getline(infile, weatherLine);
        getline(infile, severityLine);
        infile >> baselineTemperatureMult;
        infile >> persistance;
        infile.close();

        //Store lines holding weights into stringstream, and read into maps for each map of weights
        ss.str(rainLine);
        for(auto& pair : precipitationWeights) {
            ss >> pair.second;
        }
        ss.clear();
        ss.str("");

        ss.str(temperatureLine);
        for(auto& pair : temperatureWeights) {
            ss >> pair.second;
        }
        ss.clear();
        ss.str("");

        ss.str(weatherLine);
        for(auto& pair : weatherWeights) {
            ss >> pair.second;
        }
        ss.clear();
        ss.str("");

        ss.str(severityLine);
        for(auto& pair : severityWeights) {
            ss >> pair.second;
        }       
    }

    /**
     * Outputs weather profile details
     */
    void Print() {
        auto oldPrecision = cout.precision();
        cout << "Weather profile \"" << name << "\": " << endl;
        cout << "\tTemperature multiplier: " << fixed << setprecision(2) << baselineTemperatureMult << endl;
        cout << "\tWeather persistance: " << persistance * 100 << "%" << endl;
        cout << "\tWeights: " << endl;
        cout << "\t\tLight: " << severityWeights.at(LIGHT) << ", Medium: " << severityWeights.at(MEDIUM) << ", Heavy: " << severityWeights.at(HEAVY) << endl;
        cout << "\t\tRain: " << precipitationWeights.at(RAIN) << ", Snow: " << precipitationWeights.at(SNOW) << ", None: " << precipitationWeights.at(NO_PRECIPITATION) << endl;
        cout << "\t\tCold: " << temperatureWeights.at(COLD) << ", Temperate: " << temperatureWeights.at(TEMPERATE) << ", Hot: " << temperatureWeights.at(HOT) << endl;
        cout << "\t\tWind: " << weatherWeights.at(WIND) << ", None: " << weatherWeights.at(NO_WEATHER) << endl; 
    }
 };

//hold weights for locale as a struct for organization purposes
struct LocationProfile {
    string name;
    double baseTemperature;
    double persistance;
    map<GeographicMultipliers, double> multipliers;
    map<AgeEvent, int> randomEventWeights;

    LocationProfile() {
        name = "No name";
        baseTemperature = 70.0;
        persistance = 0;
        multipliers = {{HUMIDITY_COEFFICIENT, 0}, {WIND_COEFFICIENT, 0}, {SEVERITY_COEFFICIENT, 0}};
        randomEventWeights = {{DISEASE, 0}, {EATEN, 0}, {NO_RANDOM_EVENTS, 0}};
    }

    /**
     * Read location profile data from file, formatted with weights as integers:
     * name (as string)
     * humidityK windK severityK
     * disease eaten none
     * baseline temperature
     * persistance
     * @param filename
     * 
     */
    void ReadProfile(string filename) {
        string multiplierLine, randomEventLine;
        stringstream ss;

        //Open file stream and read contents to variables and lines holding weights
        ifstream infile;
        Util::VerifyFileOpen(infile, filename);
        getline(infile, name);
        getline(infile, multiplierLine);
        getline(infile, randomEventLine);
        infile >> baseTemperature;
        infile >> persistance;
        infile.close();

        //Store lines holding weights into stringstream, and read into maps for each map of weights
        ss.str(multiplierLine);
        for(auto& pair : multipliers) {
            ss >> pair.second;
        }
        ss.clear();
        ss.str("");

        ss.str(randomEventLine);
        for(auto& pair : randomEventWeights) {
            ss >> pair.second;
        }
        ss.clear();
        ss.str("");  
    }

    /**
     * Outputs weather profile details
     */
    void Print() {
        auto oldPrecision = cout.precision();
        cout << "Locale \"" << name << "\": " << endl;
        cout << "\tBase temperature: " << fixed << setprecision(2) << baseTemperature << "F" << endl;
        cout << "\tWeather persistance: " << persistance * 100 << "%" << endl;
        cout << "\tMultipliers: " << endl;
        cout << "\t\tHumidity: " << multipliers.at(HUMIDITY_COEFFICIENT) << ", Wind: " << multipliers.at(WIND_COEFFICIENT) << ", Severity: " << multipliers.at(SEVERITY_COEFFICIENT) << endl;
        cout << "\tRandom events: " << endl;
        cout << "\t\tDisease: " << randomEventWeights.at(DISEASE) << ", Eaten: " << randomEventWeights.at(EATEN) << ", None: " << randomEventWeights.at(NO_RANDOM_EVENTS) << endl; 
    }
};

struct Weather {
    double temperature; //temperature in F
    PrecipitationEvent precipitation;
    WeatherEvent wind; 
    TemperatureEvent temperatureType;
    EffectMultipliers severity;
    WeatherProfile weatherProfile;
    LocationProfile locationProfile;

    //Weights for CycleWeather function
        //Temperature modifiers
            static const double SNOW_TEMP_MULT; //How much snowy weather decreases temperature
            static const double COLD_TEMP_MULT; //How much "COLD" weather decreases from baseline temperature
            static const double HOT_TEMP_MULT;  //How much "HOT"  weather increases from baseline temperature
            //Exponentiates cold/hot multipliers based on light/heavy weather
            static const double LIGHT_TEMP_EXP;
            static const double HEAVY_TEMP_EXP;
            //Daily range (+/-) of temperatures irregardless of other wheather conditions
            static const int DAILY_TEMP_VARIATION = 3;

        //Probability modifiers
            //Multiplies weight of "COLD" weather in snowy, rainy, or windy conditions
            static const double SNOW_COLD_MULT; //Snow compounds with the rain multiplier
            static const double RAIN_COLD_MULT;
            static const double WIND_COLD_MULT;
            //Multiplies probabilities of "COLD" weather further based on "LIGHT" or "HEAVY" wheather (assume temperate is default)
            static const double LIGHT_PROBABILITY_MULT; 
            static const double HEAVY_PROBABILITY_MULT;

            //Increase liklihood that when one weather condition changes, multiple weather conditions change
            static const double BASE_CASCADE_PROBABILITY;


    //Weights for WeatherFarm function
        //Effects of precipitation
            static const double PRECIPITATION_AMOUNT; //% water level gained from 1 day of rain or snow
            static const double SNOW_MULT;            //Multiplier (decrease) during snow
            static const double RAIN_NUTRIENT_GAIN;   //% nutrients gained from 1 day of rain only
        
        //Effects of wind
            static const double WIND_NUTRIENT_DRAIN; //% nutrients drained from 1 day of wind
            static const double WIND_MULT;           //Multiplies effects of dry/freezing weather, compounds with severity

        //Effects of temperatures
            static const double DRY_TEMPERATURE;           //Dry temperature threshold
            static const double FROST_TEMPERATURE;         //Frosty temperature theshold
            static const double TEMPERATURE_WATER_DRAIN;   //% water drained from dry temperatures
            static const double TEMPERATUE_NUTRIENT_DRAIN; //% nutrients lost from dry/frosty temperatures
            static const double WEATHER_DAMAGE;            //% growth lost from dry/frosty temperatures
        
        //Severity multipliers
            static const double HEAVY_MULT;
            static const double LIGHT_MULT;
    
    Weather(string weatherFile, string localeFile) {
        weatherProfile.ReadProfile(weatherFile);
        locationProfile.ReadProfile(localeFile);
        
        //Set initial weather conditions by setting presistance to 0, cycling weather, than reseting persistance
        double oldWeatherPersistance = weatherProfile.persistance;
        double oldLocationPersistance = locationProfile.persistance;
        weatherProfile.persistance = 0;
        locationProfile.persistance = 0;
        Cycle();
        weatherProfile.persistance = oldWeatherPersistance;
        locationProfile.persistance = oldLocationPersistance;
    }

    void Print() {
        static const int PRECISION = 1;
        auto oldPrecision = cout.precision();
        string modifier, rain, miscWeather;
        switch (severity) {
            case (LIGHT): modifier = "Light"; break;
            case (MEDIUM): modifier = "Moderate"; break;
            case (HEAVY): modifier = "Severe"; break;
        }
        switch(precipitation) {
            case (RAIN): rain = "Rainy"; break;
            case (SNOW): rain = "Snowy"; break;
            case (NO_PRECIPITATION): rain = "No rain"; break;
        }
        if (wind == WIND) {
            miscWeather = "Windy";
        } else {
            miscWeather = "No wind";
        }
        cout << "Weather for " << locationProfile.name << " in " << weatherProfile.name << endl;
        cout << "\tConditions: " << modifier << ", " << rain << ", " << miscWeather << endl;
        cout << "\tTemperature: " << fixed << setprecision(1) << temperature << "F" << endl;
    }

    //Define function to simulate affects of weather events on water and nutrient levels for one day
    //Does not determine weather, nor cycle crop growth
    //Parameters: farm plot, Weather profile and location profile
    void WeatherFarm(FarmPlot& farm, bool showFlags = false) {
        double mult, effectiveWindMult, effectivePrecipitation, effectiveNutrients, effectiveGrowth;

        if (showFlags) cout << "Executing Weather::WeatherFarm: " << endl;

        //Calculate a multiplier based on weather severity
        mult = (severity == HEAVY) ? HEAVY_MULT : (severity == LIGHT) ? LIGHT_MULT : 1;

        //Wind multiplier compounds with heavy/light wind NOTE: MAY BE OVERTUNED
        effectiveWindMult = (wind == WIND) ? WIND_MULT * mult : 1;

        //Calculate precipitation from rain/snow
        effectivePrecipitation = (precipitation == NO_PRECIPITATION) ? 0 : PRECIPITATION_AMOUNT * mult * (precipitation == SNOW ? SNOW_MULT : 1.0);
        if (showFlags && precipitation != NO_PRECIPITATION) cout << "\tPrecipitation increased from " << ((precipitation == RAIN) ? "rain" : "snow") << endl;

        //Calculate nutrient gain from rain minus drain from wind
        effectiveNutrients += ((precipitation == RAIN) ? RAIN_NUTRIENT_GAIN * mult : 0);
        effectiveNutrients -= ((wind == WIND) ? WIND_NUTRIENT_DRAIN * mult : 0);
        if (showFlags && wind == WIND) cout << "\tWind drained some nutrients" << endl;

        //Calculate how dry/freezing weather affects nutrients/water levels and plant growth
        effectivePrecipitation -= (temperature >= DRY_TEMPERATURE) ? TEMPERATURE_WATER_DRAIN * mult * effectiveWindMult : 0;
        if (showFlags && temperature >= DRY_TEMPERATURE) cout << "\tDry temperatures caused growth, nutrient, and water loss" << endl;

        effectiveNutrients -= (temperature >= DRY_TEMPERATURE || temperature <= FROST_TEMPERATURE) ? TEMPERATUE_NUTRIENT_DRAIN * mult * effectiveWindMult : 0;
        effectiveGrowth -= (temperature >= DRY_TEMPERATURE || temperature <= FROST_TEMPERATURE) ? WEATHER_DAMAGE * mult * effectiveWindMult : 0;
        if (showFlags && temperature <= FROST_TEMPERATURE) cout << "\tFreezing caused nutrient and growth loss" << endl;

        if (showFlags) cout << "\t(G, W, S): " << "(" << effectiveGrowth << ", " << effectivePrecipitation << ", " << effectiveNutrients << ")" << endl;

        //Update farm based on accumulated growth/precipitation/nutrients
        farm.Update(effectiveGrowth, effectivePrecipitation, effectiveNutrients);
    }


    /**
     * Rolls weather events to determine weather conditions
     */
    void Cycle(bool showFlags = false) {
        double cascadeProbability = 0;
        //random chance to keep current weather condition, or roll weather conditions again (allowing repeats)
        //roll severity
        if (!(RollProbability(weatherProfile.persistance) || RollProbability(locationProfile.persistance)) 
            || RollProbability(cascadeProbability)) {
            if (showFlags) cout << "Severity roll succeeded" << endl;
            cascadeProbability = BASE_CASCADE_PROBABILITY;
            //Increase probabilities based on geopraphic multipliers
            auto effectiveWeights = weatherProfile.severityWeights;
            effectiveWeights.at(MEDIUM) *= locationProfile.multipliers.at(SEVERITY_COEFFICIENT);
            effectiveWeights.at(HEAVY) *= locationProfile.multipliers.at(SEVERITY_COEFFICIENT);
            
            //Roll modified weights 
           severity = RollWeights(effectiveWeights);
        }

        //roll precipitation
        if (!(RollProbability(weatherProfile.persistance) || RollProbability(locationProfile.persistance)) 
            || RollProbability(cascadeProbability)) {
            if (showFlags) cout << "Precipitation roll succeeded" << endl;
            cascadeProbability = BASE_CASCADE_PROBABILITY;

            auto effectiveWeights = weatherProfile.precipitationWeights;
            effectiveWeights.at(RAIN) *= locationProfile.multipliers.at(HUMIDITY_COEFFICIENT);
            effectiveWeights.at(SNOW) *= locationProfile.multipliers.at(HUMIDITY_COEFFICIENT);

            precipitation = RollWeights(effectiveWeights);
        }

        //roll wind
        if (!(RollProbability(weatherProfile.persistance) || RollProbability(locationProfile.persistance)) 
            || RollProbability(cascadeProbability)) {
            if (showFlags) cout << "Wind roll succeeded" << endl;
            cascadeProbability = BASE_CASCADE_PROBABILITY;

            auto effectiveWeights = weatherProfile.weatherWeights;
            effectiveWeights.at(WIND) *= locationProfile.multipliers.at(WIND_COEFFICIENT);

            wind = RollWeights(effectiveWeights);
        }

        //roll temperature
        if (!(RollProbability(weatherProfile.persistance) || RollProbability(locationProfile.persistance)) 
            || RollProbability(pow(cascadeProbability, 0.5))) { //Temperature is most likely to change after another condition changes
            if (showFlags) cout << "Temperature roll succeeded" << endl;
            auto effectiveWeights = weatherProfile.temperatureWeights;
            cascadeProbability = BASE_CASCADE_PROBABILITY;

            //Increase probability of cold based on rain/snow and severity
            switch(precipitation) {
                case SNOW: effectiveWeights.at(COLD) *= SNOW_COLD_MULT; //allow follow through
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

            //Roll temperature event based on modified weights and determine temperature
            double mult = 1;
            temperatureType = RollWeights(effectiveWeights);
            switch(temperatureType) {
                case COLD: mult *= COLD_TEMP_MULT; break;
                case HOT:  mult *= HOT_TEMP_MULT;  break;
            }
            //Modifies multiplier based on severity by exponentiating so unaffected if mult is one
            switch(severity) {
                case LIGHT: mult = pow(mult, LIGHT_TEMP_EXP); break;
                case HEAVY: mult = pow(mult, HEAVY_TEMP_EXP); break;
            }
            if (precipitation == SNOW) mult *= SNOW_TEMP_MULT;
            temperature = locationProfile.baseTemperature * weatherProfile.baselineTemperatureMult * mult;
        }
        //Outside of temperature persistance, add slight variations in temperature each day, in a range of +/- DAILY_TEMP_VARIATION
        temperature += (rand() % (DAILY_TEMP_VARIATION * 2 + 1)) - DAILY_TEMP_VARIATION;
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

//Weights for 
const double Weather::COLD_TEMP_MULT = 0.85;
const double Weather::HOT_TEMP_MULT = 1.15;
const double Weather::SNOW_TEMP_MULT = 0.85;
const double Weather::SNOW_COLD_MULT = 5;
const double Weather::RAIN_COLD_MULT = 2;
const double Weather::WIND_COLD_MULT = 1.5;
const double Weather::LIGHT_PROBABILITY_MULT = 0.75;
const double Weather::HEAVY_PROBABILITY_MULT = 2; 
const double Weather::LIGHT_TEMP_EXP = 0.5;
const double Weather::HEAVY_TEMP_EXP = 2;
const double Weather::BASE_CASCADE_PROBABILITY = 0.60;

const double Weather::PRECIPITATION_AMOUNT = 0.02;
const double Weather::TEMPERATURE_WATER_DRAIN = 0.01;
const double Weather::TEMPERATUE_NUTRIENT_DRAIN = 0.005;
const double Weather::RAIN_NUTRIENT_GAIN = 0.01;
const double Weather::WIND_NUTRIENT_DRAIN = 0.005;
const double Weather::WIND_MULT = 1.5; 
const double Weather::SNOW_MULT = 0.5;
const double Weather::HEAVY_MULT = 2;
const double Weather::LIGHT_MULT = 0.5;
const double Weather::DRY_TEMPERATURE = 80.0;
const double Weather::FROST_TEMPERATURE = 45;
const double Weather::WEATHER_DAMAGE = 0.05;

#endif