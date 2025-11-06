#ifndef PLANTSPECIES_H
#define PLANTSPECIES_H

#include <string>

using namespace std;

//Include details about a partiWcular plant species
//name, ideal water level, ideal nutrient level, display character
class PlantSpecies {
    public:
        //default constructor
        PlantSpecies();

        //Partial constructor; healthy water range and nurtrient range set to default levels
        PlantSpecies(string name, char displayToken, double idealWater, double idealNutrients, double idealTemperature);

        //Complete constructor
        PlantSpecies(string name, char displayToken, 
              double idealWater, double idealNutrients, 
              double healthyWaterRange, double healthyNutrientRange,
              double tolerableWaterRange, double tolerableNurtientRange);

        //Add standard getters and setters
        
        //Updates a growth cycle for a plant based on its current growth and soil health
        //Increases or decreases growth depending on soil health, and consumes soil health
        void GrowthCycle(double& growth, double& water, double& nutrients);

        //Outputs details about the plant species
        void Print();
        
    private:
        //name of plant species
        string name;

        //character to display when printing the 2D garden array
        char displayToken;

        //water level where plant can grow
        double idealWater;

        //nutrient level where plant can grow
        double idealNutrients;
        
        //In fahrenheight, ideal temp plant can grow
        double idealTemperature;

        //Amount above and below water level/nutrient levels that plant can grow
        double healthyWaterRange;
        double healthyNutrientRange;

        //Amount above and below water/nutrient levels that plant can survive
        double tolerableWaterRange;
        double tolerableNutrientRange;

        //Amount above and below ideal temp where plant can grow
        //wind/extreme weather events, will move temperatures towards extremes 
        double healthyTemperatureRange;
        
        //Amount above and below ideal temp where plant can survive
        double tolerableTemperatureRange;
};

#endif