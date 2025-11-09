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
    PlantSpecies completePlant("Complete Plant", 'C', 0.21, 0.22, 23, 0.24, 0.25, 26, 0.27, 0.28, 29);
    defaultPlant.Print();
    partialPlant.Print();
    completePlant.Print();
}

int main() {
    PlantSpeciesConstruction();
}