#ifndef PLANTSPECIES_H
#define PLANTSPECIES_H

#include <string>
#include <array>
#include <iostream>
#include <exception>
#include "Util.h"
#include "Token.h"

using namespace std;

enum BiomeClass { PLAIN, COAST, FOREST, TROPIC, DESERT };
enum PlantTypeModifier{ PLANT, FLOWER, TREE };

//Include details about a partiWcular plant species
//name, ideal water level, ideal nutrient level, display character
class PlantSpecies {
    public:
        static const map<string, BiomeClass> biomeClassMap;
        static const map<string, PlantTypeModifier> plantTypeMap;
        //default constructor
        PlantSpecies() :
            name("Unnamed Plant"), displayToken('?'), 
            idealWater(0.5), idealNutrients(0.5), idealTemperature(60)
            { cout << "Called default constructor for PlantSpecies" << endl; }

        //Partial constructor; specify name, token, and ideal levels--ranges set to default levels
        PlantSpecies(string name, Token displayToken, double idealWater, double idealNutrients, double idealTemperature) : 
            name(name), displayToken(displayToken), idealTemperature(idealTemperature)
        {
            this->idealWater = (idealWater <= 1 && idealWater >= 0) ? idealWater : -1; //set to error value to flag
            this->idealNutrients = (idealNutrients <= 1 && idealNutrients >= 0) ? idealNutrients : -1;

            if (this->idealWater < 0) {
                throw invalid_argument("idealWater set to value outside 0-1");
            }
            if (this->idealNutrients < 0) {
                throw invalid_argument("idealNutrients set to value outside 0-1");
            }
        }

        PlantSpecies(string name, Token displayToken, BiomeClass biomeClass, PlantTypeModifier plantType) : 
            name(name), displayToken(displayToken)
        {
            SetPlantType(biomeClass, plantType);
        }

        //Complete constructor
        PlantSpecies(string name, Token displayToken, 
              double idealWater, double idealNutrients, double idealTemperature,
              double healthyWaterRange, double healthyNutrientRange, double healthyTemperatureRange,
              double tolerableWaterRange, double tolerableNutrientRange, double tolerableTemperatureRange,
              double cycleGrowthIncrease, double cycleGrowthDecrease, double cycleWaterDecrease, double cycleSoilDecrease) : PlantSpecies(name, displayToken, idealWater, idealNutrients, idealTemperature)
        {
            //Probably will not use much, so doesn't bother checking for invalid ranges
            this->healthyWaterRange = healthyWaterRange; 
            this->healthyNutrientRange = healthyNutrientRange; 
            this->healthyTemperatureRange = healthyTemperatureRange;
            this->tolerableWaterRange = tolerableWaterRange;
            this->tolerableNutrientRange = tolerableNutrientRange;
            this->tolerableTemperatureRange = tolerableTemperatureRange;

            this->cycleGrowthIncrease = cycleGrowthIncrease;
            this->cycleGrowthDecrease = cycleGrowthDecrease;
            this->cycleWaterDecrease = cycleWaterDecrease;
            this->cycleNutrientDecrease = cycleNutrientDecrease;
        }

        /**
         * Presets for growth weights
         * @param biomeClass Preset type
         * May move to store weights in a file
         */
        void SetPlantType(BiomeClass biomeName, PlantTypeModifier plantTypeName) {
            switch(biomeName) {
                case(PLAIN): //'default' values
                    idealWater = 0.5;
                    idealNutrients = 0.5;
                    idealTemperature = 70;

                    healthyWaterRange = 0.15;
                    healthyNutrientRange = 0.15;
                    healthyTemperatureRange = 10;

                    tolerableWaterRange = 0.2;
                    tolerableNutrientRange = 0.25;
                    tolerableTemperatureRange = 20;

                    cycleGrowthIncrease = 0.03;
                    cycleGrowthDecrease = 0.1;
                    cycleWaterDecrease = 0.01;
                    cycleNutrientDecrease = 0.002;
                    break;
                case(COAST): //more water required, cooler temperatures, more hearty
                    idealWater = 0.6;
                    idealNutrients = 0.4;
                    idealTemperature = 60;

                    healthyWaterRange = 0.1;
                    healthyNutrientRange = 0.2;
                    healthyTemperatureRange = 10;

                    tolerableWaterRange = 0.15;
                    tolerableNutrientRange = 0.3;
                    tolerableTemperatureRange = 15;

                    cycleGrowthIncrease = 0.02;
                    cycleGrowthDecrease = 0.05;
                    cycleWaterDecrease = 0.02;
                    cycleNutrientDecrease = 0.001;
                    break;
                case(FOREST): //slightly more water, more hearty esp in nutrients
                    idealWater = 0.55;
                    idealNutrients = 0.5;
                    idealTemperature = 70;

                    healthyWaterRange = 0.2;
                    healthyNutrientRange = 0.25;
                    healthyTemperatureRange = 15;

                    tolerableWaterRange = 0.25;
                    tolerableNutrientRange = 0.3;
                    tolerableTemperatureRange = 20;

                    cycleGrowthIncrease = 0.02;
                    cycleGrowthDecrease = 0.05;
                    cycleWaterDecrease = 0.01;
                    cycleNutrientDecrease = 0.002;
                    break;
                case(TROPIC): //more water, higher temperatures, low tolerance, grows faster
                    idealWater = 0.9;
                    idealNutrients = 0.6;
                    idealTemperature = 75;

                    healthyWaterRange = 0.1;
                    healthyNutrientRange = 0.1;
                    healthyTemperatureRange = 5;

                    tolerableWaterRange = 0.2;
                    tolerableNutrientRange = 0.3;
                    tolerableTemperatureRange = 10;

                    cycleGrowthIncrease = 0.05;
                    cycleGrowthDecrease = 0.1;
                    cycleWaterDecrease = 0.02;
                    cycleNutrientDecrease = 0.003;
                    break;
                case(DESERT): //most hearty, grow slower
                    idealWater = 0.4;
                    idealNutrients = 0.4;
                    idealTemperature = 75;

                    healthyWaterRange = 0.25;
                    healthyNutrientRange = 0.25;
                    healthyTemperatureRange = 25;

                    tolerableWaterRange = 0.3;
                    tolerableNutrientRange = 0.3;
                    tolerableTemperatureRange = 45;

                    cycleGrowthIncrease = 0.02;
                    cycleGrowthDecrease = 0.05;
                    cycleWaterDecrease = 0.005;
                    cycleNutrientDecrease = 0.001;
                    break;
            }
            switch(plantTypeName) {
                //plant is 'default', leave unchanged
                case (FLOWER): //slightly less resistant
                    idealWater += 0.05;
                    idealNutrients += 0.05;
                    healthyWaterRange -= 0.05;
                    healthyNutrientRange -= 0.05;
                    tolerableWaterRange -= 0.05;
                    tolerableNutrientRange -= 0.05;
                    break;
                case (TREE): //more resistant, grow slower
                    healthyWaterRange += 0.05;
                    healthyNutrientRange += 0.05;
                    healthyTemperatureRange += 5;
                    tolerableWaterRange += 0.05;
                    tolerableNutrientRange += 0.05;
                    tolerableTemperatureRange += 5;
                    cycleGrowthIncrease /= 4;
                    break;
            }
        }
        
        //Add getters for name and display token
        string GetName() const { return name; }
        Token GetDisplayToken() const { return displayToken; }
        
        //Add getters for ranges and weights if needed
        double GetIdealWater() const { return idealWater; }
        double GetIdealNutrient() const { return idealNutrients; }
        double GetIdealTemperature() const { return idealTemperature; }

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
        
        /**
         * Updates growth, water, and nutrients based off water, nutrient, and temperature levels.
         * Will not grow unless all conditions are tolerable, and in that case will grow for each healthy condition
         * Will shrink for every intolerable condition
         * @param growth Current growth value of plant
         * @param water Current water level of plant
         * @param nutrients Current nutrient level of plant
         * @param temperature Current temperature of plant
         * @param showMessages If true, will show messages about plant conditions
         */
        void GrowthCycle(double& growth, double& water, double& nutrients, double temperature, bool showMessages = false) const {
            double waterDifference = abs(water - idealWater);
            double nutrientDifference = abs(nutrients - idealNutrients);
            double temperatureDifference = abs(temperature - idealTemperature);

            //Check for tolerable ranges; only allow plant to grow if all conditions are tolerable
            if (Util::lessThanEqualTo(waterDifference, tolerableWaterRange)  && Util::lessThanEqualTo(nutrientDifference, tolerableNutrientRange) && Util::lessThanEqualTo(temperatureDifference, tolerableTemperatureRange)) {
                //Allow plant to grow for each healthy condition, up to a maximum of 1 (100%)
                if (Util::lessThanEqualTo(waterDifference, healthyWaterRange)) {
                    if (showMessages) cout << name << " has just enough water " << endl;
                    growth += cycleGrowthIncrease;
                }
                if (Util::lessThanEqualTo(nutrientDifference, healthyNutrientRange)) {
                    if (showMessages) cout << name << " has just enough nutrients " << endl;
                    growth += cycleGrowthIncrease;
                }
                if (Util::lessThanEqualTo(temperatureDifference, healthyTemperatureRange)) {
                    if (showMessages) cout << name << " is at just the right temperature " << endl;
                    growth += cycleGrowthIncrease;
                }
            } else {
                //Decrease for each intolerable condition
                //allow growth to decrease to negative numbers b/c farmPlot should remove negative values
                if (Util::greaterThan(waterDifference, tolerableWaterRange)) {
                    if (showMessages) cout << name << " has improper water levels" << endl;
                    growth -= cycleGrowthDecrease; 
                }
                if (Util::greaterThan(nutrientDifference, tolerableNutrientRange)) {
                    if (showMessages) cout << name << " has improper nutrient levels" << endl;
                    growth -= cycleGrowthDecrease;
                }
                if (Util::greaterThan(temperatureDifference, tolerableTemperatureRange)) {
                    if (showMessages) cout << name << " is at an improper temperature" << endl;
                    growth -= cycleGrowthDecrease;
                }
            }
            //adjust growth back down to < 1 if it has grown greater
            (growth > 1) ? growth = 1 : false;
            //(No need to check fro negative growth, because FarmPlot::GrowthCycle() will kill negative growth crops)
            //Decrease water levels
            water -= (water > 0) ? cycleWaterDecrease : 0;
            nutrients -= (nutrients > 0) ? cycleNutrientDecrease : 0;
        }

        /**
         * Outputs details about the plant species formatted as a table
         */
        void Print() const {
            const static int TABLE_HEADER_WIDTH = 20;
            const static int TABLE_WIDTH = 15;
            const static char TABLE_CHAR = '-';
            const static int ROWS = 3;
            const static int COLUMNS = 3;

            //width of line above and below data display
            int lineWidth = COLUMNS * TABLE_WIDTH + TABLE_HEADER_WIDTH;

            //Store original precision to reset precision back later
            auto originalPrecision = cout.precision();

            //Output is enclosed by lines
            Util::CoutLine(lineWidth, TABLE_CHAR);
            cout << "Plant Species \"" << name << "\" (" << displayToken << ") Care Information: " << endl;
            
            //Display details as table
            array<string, COLUMNS> columnTitles = {"Ideal", "Healthy (+\\-)", "Tolerable (+\\-)"};
            array<string, ROWS> rowTitles = {"Water", "Nutrients", "Temperature (F)"}; 
            array<array<double, COLUMNS>, ROWS> tableData = 
                { 
                    array<double, COLUMNS>{idealWater, healthyWaterRange, tolerableWaterRange},
                    array<double, COLUMNS>{idealNutrients, healthyNutrientRange, tolerableNutrientRange},
                    array<double, COLUMNS>{idealTemperature, healthyTemperatureRange, tolerableTemperatureRange}
                };

            cout << fixed << setprecision(2);
            Util::CoutTable(columnTitles, rowTitles, tableData, TABLE_WIDTH, TABLE_HEADER_WIDTH);
            cout << endl;

            //Output details about cycle growth/resource consumption
            cout << fixed << setprecision(3);
            cout << "Growth rate / decrease: " << cycleGrowthIncrease << " / " << cycleGrowthDecrease << endl;
            cout << "Water / nutrient consumption: " << cycleWaterDecrease << " / " << cycleNutrientDecrease << endl;

            Util::CoutLine(lineWidth, TABLE_CHAR);

            cout << setprecision(originalPrecision);
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
        Token displayToken;

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
        double cycleGrowthDecrease = 0.05;
        double cycleWaterDecrease = 0.02;
        double cycleNutrientDecrease = 0.005;
};
#endif