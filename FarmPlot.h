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
        //Default constructor
        FarmPlot();

        //Standard full constructor
        FarmPlot(string name, map<PlantSpecies, array<list<double>, 3>> plotData);

        //Constructor instantiates a framplot with a given name by reading data from specified file
        FarmPlot(string name, string filename);

        //Standard name getter
        string GetName() const;

        //Standard name setter
        void SetName(string name);

        //Hide map data from direct access for now

        //Define function to read garden node data
            //Parameters: filename
        void ReadData(string filename);

        //Define function to output plant information
            //Parameters: None; acts on map of crops
        void PrintInformation() const;

        //Define function to visually output garden as a 2D rectangular plot
            //Parameters: None; acts on map of crops
        void PrintPlot() const;

        //Define function to change water level associated with all plants, by summing input value
        //(Negative input value to decrease)
            //Parameters: double with amount to increase water level
        void UpdateWater(double waterValue);

        //Define function to change soil health associated with all plants
        //(Negative input value to decrease)
            //Parameters: double with amount to increase soil health
        void UpdateSoil(double fertilizerValue);

        //Define function to change growth level associated with all plants
        //(Negative input value to decrease)
            //Parameters: double with amount to increase growth level
        void UpdateGrowth(double growthValue);

        //Updates plant growth, water, and soil by a 1 day cycle
        //Will call respective update function in PlantSpecies for data of each crop
        void GrowthCycle();

        //Enum for readability of the map's value array's list indeces, publicly accessible
        enum CropData {GROWTH, WATER, SOIL};
    private:
        //Declare map holding plant details
        //list array holds double of growth, water level, and soil health in that order
        map<PlantSpecies, array<list<double>, 3>> crops;

        string name;
};

#endif