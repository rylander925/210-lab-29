#ifndef PLANT_H
#define PLANT_H

#include <string>

//Include details about a particular plant species
//name, ideal water level, ideal nutrient level, display character
class Plant {
    public:
    private:
        //name of plant species
        string name;

        //character to display when printing the 2D garden array
        char displayToken;

        //water level where plant can grow
        double idealWater;

        //nutrient level where plant can grow
        double idealNutrients;

        //Amount above and below water level/nutrient levels that plant can grow
        double healthyWaterRange;
        double healthyNutrientRange;

        //Amount above and below water/nutrient levels that plant can survive
        double tolerableWaterRange;
        double tolerableNutrientRange;
}

#endif