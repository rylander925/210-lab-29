#include <map>
#include <array>
#include <list>
#include <iostream>
#include "PlantSpecies.h"
#include "FarmPlot.h"
#include "Util.h"
#include "Color.h"

//PlantSpecies
void PlantSpeciesConstruction() {
    PlantSpecies defaultPlant;
    PlantSpecies partialPlant("Partial Plant", 'P', 0.11, 0.12, 13);
    PlantSpecies completePlant("Complete Plant", 'C', Token(255, 255, 255), 0.21, 0.22, 23, 0.24, 0.25, 26, 0.27, 0.28, 29, 0.30, 0.31, 0.32, 0.33);
    defaultPlant.Print();
    partialPlant.Print();
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

int main() {
    PlantSpeciesGrowthCycle();
}