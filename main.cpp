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
    const string FILENAME_SEASON = "data/weatherProfiles/spring.txt";
    const string FILENAME_LOCALE = "data/locationProfiles/plains.txt";
    const string FILENAME_SPECIES = "data/speciesInfo.txt";
    const string FILENAME_PLANT_DATA = "data/plantData.txt";
    const int SIMULATION_PERIOD = 90;
    const int OUTPUT_INTERVAL = 7;
    const double FERTILIZATION_AMOUNT = 0.1;
    const double WATERING_AMOUNT = 0.003;

    //Declare variables
    string name = "Farmplot";
    int fertilizationInterval = 30;
    int wateringInterval = 1;
    double temperature = 60;
    
    cout << fixed << setprecision(3); 
    
    //Read garden node data into map of crops through constructor
    FarmPlot farm(name, FILENAME_SPECIES, FILENAME_PLANT_DATA);
    farm.PrintInformation();

    //Read weather node data and output information
    Weather weather(FILENAME_SEASON, FILENAME_LOCALE);
    weather.weatherProfile.Print();
    weather.locationProfile.Print();
    weather.Print();

    //Determine fertilzation frequency from input
    //Add prompt statements and input validation
    //cin >> fertilizationInterval;
    //cin >> wateringInterval;

    //Begin time based simulation: (Total of 90 one day time intervals)
    for (int day = 1; day <= SIMULATION_PERIOD && !farm.HasDied(); day++) {
        //Every 7 time intervals (1 week), output map contents and 2D garden plot (Call Print functions for FarmPlot)
        if (day % OUTPUT_INTERVAL == 0) {
            Util::CoutLine(Util::LINE_DEFAULT_WIDTH, '~');
            Util::CoutLine(Util::LINE_DEFAULT_WIDTH, '~');
            cout << "Period " << (day / OUTPUT_INTERVAL) + 1 << endl;
            farm.PrintInformation(false);
            farm.PrintPlot();
        }
        
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
        
        Util::CoutLine(Util::LINE_DEFAULT_WIDTH / 5, '_');
        cout << "Day " << day + 1 << endl;
        
        //simulate weather events and random time events
        weather.Cycle();
        weather.Print();
        weather.WeatherFarm(farm);

        //simulate growth cycle (call FarmPlot method)
        farm.GrowthCycle(temperature);

    }
    
    //After simulation, output garden and plant data
    //(Add some message that simulation is over)
    farm.PrintInformation(false);
    farm.PrintPlot();
}