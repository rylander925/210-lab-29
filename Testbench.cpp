#include <map>
#include <array>
#include <list>
#include <iostream>
#include "PlantSpecies.h"
#include "FarmPlot.h"
#include "Util.h"

//PlantSpecies
void PlantSpeciesConstruction() {
    PlantSpecies defaultPlant;
    PlantSpecies partialPlant("Partial Plant", 'P', 0.11, 0.12, 13);
    PlantSpecies completePlant("Complete Plant", 'C', 0.21, 0.22, 23, 0.24, 0.25, 26, 0.27, 0.28, 29, 0.30, 0.31, 0.32, 0.33);
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
    PlantSpecies defaultPlant;
    defaultPlant.Print();
    double growth = 0;
    double water = 0;
    double nutrients = 0;
    double temperature = 0;

    //test with everything set to 0, should decrease 3 times
    cout << "Testing with everything set to 0, expected should decrease growth 3 times" << endl;
    defaultPlant.GrowthCycle(growth, water, nutrients, temperature, true);
}

int main() {
    PlantSpeciesConstruction();
}