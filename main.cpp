/*
COMSC-210 | Lab 29 | Rylan Der
IDE Used: Visual studio code 
*/

#include <map>
#include <array>
#include <list>
#include <iostream>
#include "PlantSpecies.h"
#include "FarmPlot.h"
#include "Util.h"
#include "Weather.h"

using namespace std;

//Define main function
int main() {
    srand(time(0));

    const string FILENAME_SEASON = "data/weatherProfiles/summer.txt";
    const string FILENAME_LOCALE = "data/locationProfiles/tropic.txt";
    const string FILENAME_SPECIES = "data/speciesInfo.txt";
    const string FILENAME_PLANT_DATA = "data/plantData.txt";
    const int SIMULATION_PERIOD = 90;
    const int OUTPUT_INTERVAL = 30;
    const double FERTILIZATION_AMOUNT = 0.1;
    const double WATERING_AMOUNT = 0.003;
    const int NUM_PLANTS = 10;

    //Declare variables
    string name = "Farm";
    int fertilizationInterval = 30;
    int wateringInterval = 1;
    double temperature = 60;
    
    cout << fixed << setprecision(3); 
    
    //Read garden node data into map of crops through constructor
    FarmPlot farm(name, FILENAME_SPECIES, FILENAME_PLANT_DATA, NUM_PLANTS);
    farm.PrintInformation();

    //Read weather node data and output information
    Weather weather(FILENAME_SEASON, FILENAME_LOCALE);
    weather.weatherProfile.Print();
    weather.locationProfile.Print();
    weather.Print();

    //Begin time based simulation: (Total of 90 one day time intervals)
    for (int day = 1; day <= SIMULATION_PERIOD && !farm.HasDied(); day++) {
        Util::CoutLine(Util::LINE_DEFAULT_WIDTH / 5, '_');
        cout << "Day " << day << endl;
        
        //Every fertilization frequency number of time intervals, simulate fertilization events (call UpdateSoil FarmPlot method)
        if (day % fertilizationInterval == 0) {
            farm.Update(0, 0, FERTILIZATION_AMOUNT);
            cout << "Fertilized crops" << endl;
        }
        
        //Every watering frequency number of time intervals, simulate watering events (call UpdateWater FarmPlot method)
        if (day % wateringInterval == 0) {
            farm.Update(0, WATERING_AMOUNT, 0);
            cout << "Watered crops" << endl;
        }
        
        //simulate weather events and random time events
        weather.Cycle();
        weather.Print();
        weather.WeatherFarm(farm);
        
        //Every 7 time intervals (1 week), output map contents and 2D garden plot (Call Print functions for FarmPlot)
        if (day % OUTPUT_INTERVAL == 0) {
            Util::CoutLine(Util::LINE_DEFAULT_WIDTH, '~');
            Util::CoutLine(Util::LINE_DEFAULT_WIDTH, '~');
            cout << "Period " << (day / OUTPUT_INTERVAL) + 1 << endl;
            farm.PrintPlot();
            farm.PrintInformation();
        }

        //simulate growth cycle (call FarmPlot method)
        farm.GrowthCycle(temperature);

    }
    Util::CoutLine(200, '|');
    //After simulation, output garden and plant data
    //(Add some message that simulation is over)
    farm.PrintInformation();
    farm.PrintPlot();
    farm.PrintDead();
}