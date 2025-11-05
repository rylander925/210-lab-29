#ifndef SPRINKLER_H
#define SPRINKLER_H

#include <string>
#include <map>
#include <array>
#include <list>
#include "Soil.h"
#include "PlantSpecies.h"

//Contains information about how sprinkler effects the soil around it
class Sprinkler {
    public:
        //Set sprinkler to default values
        Sprinkler();

        //Complete constructor
        Sprinkler(int squareRadius, double saturationLevel);

        //add standard getters and setters

        //water surrounding tiles in 2D garden array
        void Water(map<PlantSpecies, array<list<double>, 3>>);        
        
        private:
            //Display name for the sprinkler
            string name;
            
            //Character to display on 2D array of garden nodes
            char displayToken;
            
            //tiles away from sprinkler that can be watered
            int squareRadius;
            
            //how much water sprinkler adds
            double saturationLevel;
            
            //Position of sprinkler in 2D garden array
            int x;
            int y;
};

#endif