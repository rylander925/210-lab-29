#ifndef PLANTSPECIES_H
#define PLANTSPECIES_H

#include <string>

using namespace std;

//Include details about a partiWcular plant species
//name, ideal water level, ideal nutrient level, display character
class PlantSpecies {
    public:
        //default constructor
        PlantSpecies() :
            name("Unnamed Plant"), displayToken('?'), 
            idealWater(0.5), idealNutrients(0.5), 
            healthyWaterRange(0.10), healthyNutrientRange(0.10),
            tolerableWaterRange(0.30), tolerableNutrientRange(0.30),
            healthyTemperatureRange(10), tolerableTemperatureRange(20) { cout << "Called default constructor for PlantSpecies" << endl; }

        //Partial constructor; healthy water range and nurtrient range set to default levels
        PlantSpecies(string name, char displayToken, double idealWater, double idealNutrients, double idealTemperature) :
              name(name), displayToken(displayToken), 
              idealWater(idealWater), idealNutrients(idealNutrients), 
              healthyWaterRange(0.10), healthyNutrientRange(0.10),
              tolerableWaterRange(0.30), tolerableNutrientRange(0.30),
              healthyTemperatureRange(10), tolerableTemperatureRange(20) {}

        //Complete constructor
        PlantSpecies(string name, char displayToken, 
              double idealWater, double idealNutrients, double idealTemperature,
              double healthyWaterRange, double healthyNutrientRange,
              double tolerableWaterRange, double tolerableNutrientRange,
              double healthyTemperatureRange, double tolerableTemperatureRange) :

              name(name), displayToken(displayToken), 
              idealWater(idealWater), idealNutrients(idealNutrients), 
              healthyWaterRange(healthyWaterRange), healthyNutrientRange(healthyNutrientRange),
              tolerableWaterRange(tolerableWaterRange), tolerableNutrientRange(tolerableNutrientRange),
              healthyTemperatureRange(healthyTemperatureRange), tolerableTemperatureRange(tolerableTemperatureRange) {}

        //Add getters
        string GetName() const { return name; }
        char GetDisplayToken() const { return displayToken; }

        //No setters beyond default values b/c used as key
        
        //Updates a growth cycle for a plant based on its current growth and soil health
        //Increases or decreases growth depending on soil health, and consumes soil health
        void GrowthCycle(double& growth, double& water, double& nutrients) const {
            cout << "FIXME: PlantSpecies.GrowthCycle incomplete" << endl;
            double waterDifference = abs(water - idealWater);
            double nutrientDifference = abs(nutrients - idealNutrients);
            if (waterDifference >= tolerableWaterRange) {
                cout << name << " has improper water levels" << endl;
                growth -= 0.1;
            } else if (waterDifference <= healthyWaterRange) {
                cout << name << "has just enough water " << endl;
                growth += -0.1;
            }

            if (nutrientDifference >= tolerableNutrientRange) {
                cout << name << " has improper nutrient levels" << endl;
                growth -= 0.1;
            } else if (nutrientDifference <= healthyNutrientRange) {
                cout << name << "has just enough nutrients" << endl;
                growth += -0.1;
            }
        }

        //Outputs details about the plant species
        void Print() const {
            cout << "Plant Species: " << name << "FIXME: PlantSpecies.Print incomplete" << endl;
        }

        //Overload operator< for use in map
        bool operator< (const PlantSpecies& otherPlant) const {
            return name < otherPlant.name;
        }
        
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