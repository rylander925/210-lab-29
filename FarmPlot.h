#ifndef FARMPLOT_H
#define FARMPLOT_H

#include <map>
#include <array>
#include <list>
#include <string>
#include "PlantSpecies.h"

using namespace std;

class FarmPlot {
    public: 
        //Define function to read garden node data
            //Parameters: Acts on map of crops, filename

        //Define function to output plant information
            //Parameters: None; acts on map of crops

        //Define function to visually output garden as a 2D rectangular plot
            //Parameters: None; acts on map of crops

    private:
        //Declare map holding plant details
        map<PlantSpecies, array<list<double>, 3>> crops;

        string name;
};

#endif