#ifndef PLANTSPECIES_H
#define PLANTSPECIES_H

#include <string>
#include <array>
#include <exception>
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

        //Complete constructor
        PlantSpecies(string name, char displayToken, 
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

        //Add getters for name and display token
        string GetName() const { return name; }
        char GetDisplayToken() const { return displayToken; }
        
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
            if (lessThanEqualTo(waterDifference, tolerableWaterRange)  && lessThanEqualTo(nutrientDifference, tolerableNutrientRange) && lessThanEqualTo(temperatureDifference, tolerableTemperatureRange)) {
                //Allow plant to grow for each healthy condition, up to a maximum of 1 (100%)
                if (lessThanEqualTo(waterDifference, healthyWaterRange)) {
                    if (showMessages) cout << name << " has just enough water " << endl;
                    growth += (growth < 1) ? cycleGrowthIncrease : 0;
                }
                if (lessThanEqualTo(nutrientDifference, healthyNutrientRange)) {
                    if (showMessages) cout << name << " has just enough nutrients " << endl;
                    growth += (growth < 1) ? cycleGrowthIncrease : 0;
                }
                if (lessThanEqualTo(temperatureDifference, healthyTemperatureRange)) {
                    if (showMessages) cout << name << " is at just the right temperature " << endl;
                    growth += (growth < 1) ? cycleGrowthIncrease : 0;
                }
            } else {
                if (showMessages) cout << "Some intolerable conditions present" << endl;
                //Decrease for each intolerable condition
                //allow growth to decrease to negative numbers b/c farmPlot should remove negative values
                if (greaterThan(waterDifference, tolerableWaterRange)) {
                    if (showMessages) cout << name << " has improper water levels" << endl;
                    growth -= cycleGrowthDecrease; 
                }
                if (greaterThan(nutrientDifference, tolerableNutrientRange)) {
                    if (showMessages) cout << name << " has improper nutrient levels" << endl;
                    growth -= cycleGrowthDecrease;
                }
                if (greaterThan(temperatureDifference, tolerableTemperatureRange)) {
                    if (showMessages) cout << name << " is at an improper temperature" << endl;
                    growth -= cycleGrowthDecrease;
                }
            }

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
        //Add comparison operators within a range epsilon to eliminate effect of floating point imprecision
        static const double DEFAULT_EPSILON;
        bool lessThan(double a, double b, double epsilon = DEFAULT_EPSILON) const { return (b - a) > epsilon; }
        bool greaterThan(double a, double b, double epsilon = DEFAULT_EPSILON) const { return lessThan(b, a, epsilon); }
        bool lessThanEqualTo(double a, double b, double epsilon = DEFAULT_EPSILON) const { return !greaterThan(a, b, epsilon); }
        bool greaterThanEqualTo(double a, double b, double epsilon = DEFAULT_EPSILON) const { return !lessThan(a, b, epsilon); }

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

const double PlantSpecies::DEFAULT_EPSILON = 0.00001;

#endif