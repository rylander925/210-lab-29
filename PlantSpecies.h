#ifndef PLANTSPECIES_H
#define PLANTSPECIES_H

#include <string>
#include <array>
#include "Util.h"

using namespace std;

//Include details about a partiWcular plant species
//name, ideal water level, ideal nutrient level, display character
class PlantSpecies {
    public:
        //default constructor
        PlantSpecies() :
            name("Unnamed Plant"), displayToken('?'), 
            idealWater(0.5), idealNutrients(0.5), idealTemperature(60)
            { cout << "Called default constructor for PlantSpecies" << endl; }

        //Partial constructor; specify name, token, and ideal levels--ranges set to default levels
        PlantSpecies(string name, char displayToken, double idealWater, double idealNutrients, double idealTemperature) : 
            name(name), displayToken(displayToken), 
            idealWater(idealWater), idealNutrients(idealNutrients), idealTemperature(idealTemperature) 
        {}

        //Complete constructor
        PlantSpecies(string name, char displayToken, 
              double idealWater, double idealNutrients, double idealTemperature,
              double healthyWaterRange, double healthyNutrientRange, double healthyTemperatureRange,
              double tolerableWaterRange, double tolerableNutrientRange, double tolerableTemperatureRange) 
              :
              name(name), displayToken(displayToken), 
              idealWater(idealWater), idealNutrients(idealNutrients), idealTemperature(idealTemperature),
              healthyWaterRange(healthyWaterRange), healthyNutrientRange(healthyNutrientRange), healthyTemperatureRange(healthyTemperatureRange),
              tolerableWaterRange(tolerableWaterRange), tolerableNutrientRange(tolerableNutrientRange), tolerableTemperatureRange(tolerableTemperatureRange) 
        {}

        //Add getters for name and display token
        string GetName() const { return name; }
        char GetDisplayToken() const { return displayToken; }
        
        //Add getters for ranges and weights if needed
        double GetHealthyWaterRange() const { return healthyWaterRange; }
        double GetHealthyNutrientRange() const { return healthyNutrientRange; }
        double GetHealthyTemperatureRange() const { return healthyTemperatureRange; }
        double GetTolerableWaterRange() const { return tolerableWaterRange; }
        double GetTolerableNutrientRange() const { return tolerableNutrientRange; }
        double GetTolerableTemperatureRange() const { return tolerableTemperatureRange; }

        double GetCycleGrowthIncrease() const { return cycleGrowthIncrease; }
        double GetCycleGrowthDecrease() const { return cycleGrowthDecrease; }
        double GetCycleWaterDecrease() const { return cycleWaterDecrease; }
        double GetCycleNutrientDecrease() const { return cycleNutrientDecrease; }

        //Add setters to change ranges and cycle weights if needed
        void SetHealthyRanges(double water, double nutrient, double temperature) {
            healthyWaterRange = water;
            healthyNutrientRange = nutrient;
            healthyTemperatureRange = temperature;
        }

        void SetTolerableRanges(double water, double nutrient, double temperature) {
            tolerableWaterRange = water;
            tolerableNutrientRange = nutrient;
            tolerableTemperatureRange = temperature;
        }

        void SetCycleWeights(double growthIncrease, double growthDecrease, double waterDecrease, double nutrientDecrease) {
            cycleGrowthIncrease = growthIncrease;
            cycleGrowthDecrease = growthDecrease;
            cycleWaterDecrease = waterDecrease;
            cycleNutrientDecrease = nutrientDecrease;
        }
        
        //Updates a growth cycle for a plant based on its current growth and soil health
        //Increases or decreases growth depending on soil health, and consumes soil health
        void GrowthCycle(double& growth, double& water, double& nutrients) const {
            cout << "FIXME: PlantSpecies.GrowthCycle incomplete" << endl;
            double waterDifference = abs(water - idealWater);
            double nutrientDifference = abs(nutrients - idealNutrients);
            
            //Decrease, not change, or increase growth if according to water level 
            if (waterDifference >= tolerableWaterRange) {
                cout << name << " has improper water levels" << endl;
                growth -= cycleGrowthDecrease;
            } else if (waterDifference <= healthyWaterRange) {
                cout << name << "has just enough water " << endl;
                growth += cycleGrowthIncrease;
            }

            //Decrease, not change, or increase growth if according to nutrient level 
            if (nutrientDifference >= tolerableNutrientRange) {
                cout << name << " has improper nutrient levels" << endl;
                growth -= cycleGrowthDecrease;
            } else if (nutrientDifference <= healthyNutrientRange) {
                cout << name << " has just enough nutrients" << endl;
                growth += cycleGrowthIncrease;
            }

            //Decrease water levels
            water -= cycleWaterDecrease;
            nutrients -= cycleNutrientDecrease;
        }

        /**
         * Outputs details about the plant species formatted as a table
         * @test
         */
        void Print() const {
            const static int TABLE_HEADER_WIDTH = 20;
            const static int TABLE_WIDTH = 15;
            const static char TABLE_CHAR = '-';
            const static int ROWS = 3;
            const static int COLUMNS = 3;

            //width of line above and below data display
            int lineWidth = COLUMNS * TABLE_WIDTH + TABLE_HEADER_WIDTH;

            //Output is enclosed by lines
            Util::CoutLine(lineWidth, TABLE_CHAR);
            cout << "Plant Species \"" << name << "\" (" << displayToken << ") Care Information: " << endl;
            
            //Display details as table
            array<string, COLUMNS> columnTitles = {"Ideal", "Healthy (+\\-)", "Tolerable (+\\-)"};
            array<string, ROWS> rowTitles = {"Water", "Nutrients", "Temperature (F)"}; 
            array<array<double, COLUMNS>, ROWS> tableData = { array<double, COLUMNS>{idealWater, healthyWaterRange, tolerableWaterRange},
                                                              array<double, COLUMNS>{idealNutrients, healthyNutrientRange, tolerableNutrientRange},
                                                              array<double, COLUMNS>{idealTemperature, healthyTemperatureRange, tolerableTemperatureRange}
                                                            };
            Util::CoutTable(columnTitles, rowTitles, tableData, TABLE_WIDTH, TABLE_HEADER_WIDTH);

            cout << endl;
            cout << "Growth rate / decrease: " << cycleGrowthIncrease << " / " << cycleGrowthDecrease << endl;
            cout << "Water / nutrient consumption: " << cycleWaterDecrease << " / " << cycleNutrientDecrease << endl;

            Util::CoutLine(lineWidth, TABLE_CHAR);
        }

        //Overload operator< for use in map
        bool operator< (const PlantSpecies& otherPlant) const {
            return name < otherPlant.name;
        }
        
    private:
        //Basic information
        //name of plant species
        string name;

        //character to display when printing the 2D garden array
        char displayToken;

        //levels where plant can grow
        double idealWater;       //As a percent
        double idealNutrients;   //As a percent
        double idealTemperature; //In fahrenheight, ideal temp plant can grow
        
        //Weights for plant survival, initialized by default, but can be modified through explicit changes
        //Amount above and below water level/nutrient levels that plant can grow
        double healthyWaterRange = 0.1;
        double healthyNutrientRange = 0.1;
        double healthyTemperatureRange = 10;
        
        //Amount above and below water/nutrient levels that plant can survive
        double tolerableWaterRange = 0.2;
        double tolerableNutrientRange = 0.3;
        double tolerableTemperatureRange = 20;

        //How much plant grows/shrinks per growth cycle
        //May change from constant values to custom per plant later
        double cycleGrowthIncrease = 0.05;
        double cycleGrowthDecrease = 0.1;
        double cycleWaterDecrease = 0.05;
        double cycleNutrientDecrease = 0.005;
};

#endif