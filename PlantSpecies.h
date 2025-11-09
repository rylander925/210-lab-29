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
            idealWater(0.5), idealNutrients(0.5), idealTemperature(60),
            healthyWaterRange(0.10), healthyNutrientRange(0.10), healthyTemperatureRange(10),
            tolerableWaterRange(0.30), tolerableNutrientRange(0.30), tolerableTemperatureRange(20) 
            { cout << "Called default constructor for PlantSpecies" << endl; }

        //Partial constructor; specify name, token, and ideal levels--ranges set to default levels
        PlantSpecies(string name, char displayToken, double idealWater, double idealNutrients, double idealTemperature) : PlantSpecies() { 
                this->name = name;
                this->displayToken = displayToken;
                this->idealWater = idealWater;
                this->idealNutrients = idealNutrients;
                this->idealTemperature = idealTemperature;
        }

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

            Util::CoutLine(lineWidth, TABLE_CHAR);
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