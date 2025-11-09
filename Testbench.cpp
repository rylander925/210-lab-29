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
        errorPlant.Print(); //(Doesnt validate temperature)
    } catch (exception& e) {
        cout << e.what() << endl;
    }
}

int main() {
    PlantSpeciesConstruction();
}