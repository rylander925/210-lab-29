#include <map>
#include <array>
#include <list>
#include <iostream>
#include "PlantSpecies.h"
#include "FarmPlot.h"
#include "Util.h"
#include "Token.h"
#include "Weather.h"

//PlantSpecies
void PlantSpeciesConstruction() {
    PlantSpecies defaultPlant;
    PlantSpecies partialPlant("Partial Plant", Token('P'), 0.11, 0.12, 13);
    PlantSpecies templatePlant("Template Plant", Token('T'), DESERT, FLOWER);
    PlantSpecies completePlant("Complete Plant", Token('C', 50, 175, 50), 0.21, 0.22, 23, 0.24, 0.25, 26, 0.27, 0.28, 29, 0.30, 0.31, 0.32, 0.33);
    defaultPlant.Print();
    partialPlant.Print();
    templatePlant.Print();
    completePlant.Print();
    //Check error messages
    try {
        PlantSpecies errorPlant("Error Plant", 'E', 1000, 10000, 1000);
        errorPlant.Print(); //(Doesnt validate temperature)
    } catch (exception& e) {
        cout << e.what() << endl;
    }
    
    try {
        PlantSpecies errorPlant("Error Plant", 'E', 0.1, 10000, 1000);
        errorPlant.Print(); 
    } catch (exception& e) {
        cout << e.what() << endl;
    }
}

void PlantSpeciesGrowthCycle() {
    PlantSpecies plant;
    plant.Print();
    double growth = 0;
    double water = 0;
    double nutrients = 0;
    double temperature = 0;

    //test with everything set to 0, should decrease 3 times
    cout << "Testing with everything set to 0, expected should decrease growth 3 times; water and nutrients should not be decremented" << endl;
    cout << "Growth: " << growth << ", Water: " << water << ", Nutrients: " << nutrients << ", Temp: " << temperature << endl; 
    plant.GrowthCycle(growth, water, nutrients, temperature, true);
    cout << "Growth: " << growth << ", Water: " << water << ", Nutrients: " << nutrients << ", Temp: " << temperature << endl; 

    Util::CoutLine();
    cout << "test with everything set to ideal values, growth set to 0, should increase 3 times, and water/nutrients should be decremented" << endl;
    growth = 0;
    water = plant.GetIdealWater();
    nutrients = plant.GetIdealNutrient();
    temperature = plant.GetIdealTemperature();

    cout << "Growth: " << growth << ", Water: " << water << ", Nutrients: " << nutrients << ", Temp: " << temperature << endl; 
    plant.GrowthCycle(growth, water, nutrients, temperature, true);
    cout << "Growth: " << growth << ", Water: " << water << ", Nutrients: " << nutrients << ", Temp: " << temperature << endl; 

    Util::CoutLine();
    cout << "test with everything set to ideal values, growth set to 1, growth should not increase" << endl;
    growth = 1;
    water = plant.GetIdealWater();
    nutrients = plant.GetIdealNutrient();
    temperature = plant.GetIdealTemperature();

    cout << "Growth: " << growth << ", Water: " << water << ", Nutrients: " << nutrients << ", Temp: " << temperature << endl; 
    plant.GrowthCycle(growth, water, nutrients, temperature, true);
    cout << "Growth: " << growth << ", Water: " << water << ", Nutrients: " << nutrients << ", Temp: " << temperature << endl; 

    Util::CoutLine();
    cout << "test with everything set to boundry healthy, growth should increase 3 times" << endl;
    growth = 0.5;
    water = plant.GetIdealWater() - plant.GetHealthyWaterRange();
    nutrients = plant.GetIdealNutrient() - plant.GetHealthyNutrientRange();
    temperature = plant.GetIdealTemperature() - plant.GetHealthyTemperatureRange();

    cout << "Growth: " << growth << ", Water: " << water << ", Nutrients: " << nutrients << ", Temp: " << temperature << endl; 
    plant.GrowthCycle(growth, water, nutrients, temperature, true);
    cout << "Growth: " << growth << ", Water: " << water << ", Nutrients: " << nutrients << ", Temp: " << temperature << endl; 

    Util::CoutLine();
    cout << "Run again, water and nutrients should be tolerable, growth should increase 1 times due to temperature" << endl;
    cout << "Growth: " << growth << ", Water: " << water << ", Nutrients: " << nutrients << ", Temp: " << temperature << endl; 
    plant.GrowthCycle(growth, water, nutrients, temperature, true);
    cout << "Growth: " << growth << ", Water: " << water << ", Nutrients: " << nutrients << ", Temp: " << temperature << endl; 

    Util::CoutLine();
    cout << "test with everything set to boundry tolerable, growth should not increase or decrease" << endl;
    growth = 0.5;
    water = plant.GetIdealWater() - plant.GetTolerableWaterRange();
    nutrients = plant.GetIdealNutrient() - plant.GetTolerableNutrientRange();
    temperature = plant.GetIdealTemperature() - plant.GetTolerableTemperatureRange();

    cout << "Growth: " << growth << ", Water: " << water << ", Nutrients: " << nutrients << ", Temp: " << temperature << endl; 
    plant.GrowthCycle(growth, water, nutrients, temperature, true);
    cout << "Growth: " << growth << ", Water: " << water << ", Nutrients: " << nutrients << ", Temp: " << temperature << endl; 

    Util::CoutLine();
    cout << "Run again, water and nutrients should be intolerable, growth should decrease 2 times" << endl;
    cout << "Growth: " << growth << ", Water: " << water << ", Nutrients: " << nutrients << ", Temp: " << temperature << endl; 
    plant.GrowthCycle(growth, water, nutrients, temperature, true);
    cout << "Growth: " << growth << ", Water: " << water << ", Nutrients: " << nutrients << ", Temp: " << temperature << endl; 

}

void FarmPlotConstruction() {
    //initialize by default and with partial constructor
    FarmPlot defaultPlot;
    FarmPlot filePlot("File plot", "data/speciesinfo.txt", "data/plantData.txt");

    //display information to verify correct read
    defaultPlot.PrintInformation();
    filePlot.PrintInformation();
    filePlot.PrintPlot();
}

void FarmPlotGrowthCycle() {
    double temp = 50;
    //Initialize a farm plot, display initial data
    FarmPlot filePlot("File plot", "data/reducedSpeciesInfo.txt", "data/reducedPlantData.txt");
    filePlot.PrintInformation();
    filePlot.PrintPlot();
    
    //run growth cycles, showing details of plants when they die
    for (int i = 0; i < 10; i++) {
        Util::CoutLine();
        cout << "Cycle " << i + 1 << endl;
        filePlot.GrowthCycle(temp, true);
        filePlot.PrintPlot();
    }

    //show information after to verify all negative growth plants died
    //Plants with restrictive conditions should be dead
    filePlot.PrintInformation();
}

void FarmPlotUpdate() {
    double growth = 0, water = -0, soil = -0.01;
    //Initialize a farm plot, display initial data
    FarmPlot filePlot("File plot", "data/reducedSpeciesInfo.txt", "data/reducedPlantData.txt");
    filePlot.PrintInformation();
    filePlot.PrintPlot();
    
    //run growth cycles, showing details of plants when they die
    for (int i = 0; i < 10; i++) {
        Util::CoutLine();
        cout << "Cycle " << i + 1 << endl;
        filePlot.Update(growth, water, soil);
        filePlot.PrintPlot();
    }

    //show information after to verify all negative growth plants died
    //Plants with restrictive conditions should be dead
    filePlot.PrintInformation();
}

void WeatherProfileRead() {
    //Initialize and display profiles for each season; verify weights make sense 
    WeatherProfile defaultWeather, winter, spring, summer, fall;
    winter.ReadProfile("data/weatherProfiles/winter.txt");
    spring.ReadProfile("data/weatherProfiles/spring.txt");
    summer.ReadProfile("data/weatherProfiles/summer.txt");
    fall.ReadProfile("data/weatherProfiles/fall.txt");
    defaultWeather.Print();
    winter.Print();
    spring.Print();
    summer.Print();
    fall.Print();
}

void LocationProfileRead() {
    //Initialize and display profiles for each location; verify weights make sense 
    LocationProfile defaultLocale, plains, forest, coast, desert, tropic;
    plains.ReadProfile("data/locationProfiles/plains.txt");
    forest.ReadProfile("data/locationProfiles/forest.txt");
    coast.ReadProfile("data/locationProfiles/coast.txt");
    desert.ReadProfile("data/locationProfiles/desert.txt");
    tropic.ReadProfile("data/locationProfiles/tropic.txt");
    defaultLocale.Print();
    plains.Print();
    forest.Print();
    coast.Print();
    desert.Print();
    tropic.Print();
}

void WeatherCycles() {
    //Initialize a weather object and display basic information
    const string LOCATION_FILE = "data/locationProfiles/coast.txt";
    const string WEATHER_FILE = "data/weatherProfiles/fall.txt";
    Weather weather(WEATHER_FILE, LOCATION_FILE);
    weather.weatherProfile.Print();
    weather.locationProfile.Print();

    //Run through 20 weather cycles, displaying information
    for (int i = 0; i < 20; i++) {
        weather.Print();
        weather.Cycle(true);
    }

    //Display weather profile again to ensure nothing changed
    weather.weatherProfile.Print();
    weather.locationProfile.Print();
}

void WeatherEffects() {
    //Initialize a weather object and display basic information
    const string LOCATION_FILE = "data/locationProfiles/coast.txt";
    const string WEATHER_FILE = "data/weatherProfiles/fall.txt";
    Weather weather(WEATHER_FILE, LOCATION_FILE);
    weather.weatherProfile.Print();
    weather.locationProfile.Print();

    //Initialize a farm plot and display basic information
    FarmPlot filePlot("File plot", "data/reducedSpeciesInfo.txt", "data/reducedPlantData.txt");
    filePlot.PrintInformation();
    filePlot.PrintPlot();

    
    //Run through weather cycles, display information, and weather the farm
    //Show farm information after each cycle
    for (int i = 0; i < 3; i++) {
        weather.Cycle();
        weather.Print();
        for (int j = 0; j < 5; j++) {
            weather.WeatherFarm(filePlot, true);
        }
        filePlot.PrintInformation();
    }

    //Display weather profile again to ensure nothing changed
    weather.weatherProfile.Print();
    weather.locationProfile.Print();
}

int main() {
    WeatherEffects();
}