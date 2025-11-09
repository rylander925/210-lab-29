#ifndef FARMPLOT_H
#define FARMPLOT_H

#include <map>
#include <fstream>
#include <array>
#include <list>
#include <string>
#include <sstream>
#include <cmath>
#include "Token.h"
#include "Util.h"
#include "PlantSpecies.h"

using namespace std;

class FarmPlot {
    public: 
        //Default constructor
        FarmPlot() : name("Unnamed Farm") {
            cout << "Called farmplot default constructor" << endl;
            //fill with dummy values
            array<list<double>, 3> defaultArray;

            defaultArray.fill(list<double>(3, 1));

            crops.insert(make_pair(PlantSpecies(), defaultArray));
        }

        //Standard full constructor
        FarmPlot(string name, map<PlantSpecies, array<list<double>, 3>> plotData);

        //Constructor instantiates a framplot with a given name by reading data from specified file
        FarmPlot(string name, string speciesFilename, string plantDataFilename){
            this->name = name;
            ReadData(speciesFilename, plantDataFilename);
        }

        //Standard name getter
        string GetName() const { return name; }

        //Standard name setter
        void SetName(string name) { this->name = name; }

        //Hide map data from direct access for now

        //Define function to read garden node data
            //Parameters: filename
        void ReadData(string speciesFilename, string plantDataFilename) {
            static const map<string, BiomeClass> BIOME_MAP = {{"plain", PLAIN}, {"coast", COAST}, {"forest", FOREST}, {"tropic", TROPIC}, {"desert", DESERT}};
            static const map<string, PlantTypeModifier> PLANT_MAP = {{"plant", PLANT}, {"flower", FLOWER}, {"tree", TREE}};

            //various input streams
            ifstream speciesFile, plantDataFile;
            stringstream speciesSS, plantDataSS;
            
            //dummy variables for species data
            string speciesLine, name, biomeClass, plantType;
            char tokenCharacter;
            int R, G, B;

            //dummy variables for plant data
            string plantDataLine;
            int numPlants;
            double growth, water, soil;

            //Open files 
            Util::VerifyFileOpen(speciesFile, speciesFilename);
            Util::VerifyFileOpen(plantDataFile, plantDataFilename);

            //Read information about plant species into a plant species object 
                //File formatting for species: 
                //  name
                //  tokenCharacter R G B biomeClass plantType
                //File formatting for plant data:
                //  numPlants growth water soil
            while(getline(speciesFile, name) && getline(plantDataFile, plantDataLine)) {
                getline(speciesFile, speciesLine);

                speciesSS.str(speciesLine);
                speciesSS >> tokenCharacter >> R >> G >> B >> biomeClass >> plantType;

                plantDataSS.str(plantDataLine);
                plantDataSS >> numPlants >> growth >> water >> soil;

                array<list<double>, 3> dataArray;
                dataArray.at(GROWTH) = list<double>(numPlants, growth);
                dataArray.at(WATER) = list<double>(numPlants, water);
                dataArray.at(SOIL) = list<double>(numPlants, soil);

                crops.insert(make_pair(PlantSpecies(name, Token(tokenCharacter, R, G, B), BIOME_MAP.at(biomeClass), PLANT_MAP.at(plantType)), dataArray));
                speciesSS.str("");
                speciesSS.clear();
                plantDataSS.str("");
                plantDataSS.clear();
            }

            speciesFile.close();
            plantDataFile.close();
        }

        /**
         * Outputs information of each plant species and each plant associated with each plant species as a table
         */
        void PrintInformation() const {
            const static int TABLE_ROWS = 3;
            const static int TABLE_DATA_WIDTH = 10;

            cout << "Printing crop information: " << endl;
            for (auto cropPair : crops) {
                Util::CoutLine();
                
                //Display information about plant species
                cropPair.first.Print();
                
                //Display as Horizontal table for now, for ease of use with Util::CoutTable
                int tableColumns = cropPair.second.at(GROWTH).size(); //Assumed each column has equal # of values (which it should if created properly)
                
                //Create row headers with data labels
                array<string, TABLE_ROWS> rowHeaders = {"Growth", "Water", "Nutrients"};

                //Create column headers to display plant #
                list<string> columnHeaders; 
                for (int i = 0; i < tableColumns; i++) columnHeaders.push_back("#" + to_string(i+1));

                //Output table
                cout << fixed << setprecision(3);
                Util::CoutTable(columnHeaders, rowHeaders, cropPair.second, TABLE_DATA_WIDTH);

                Util::CoutLine();
            }
        }

        //Define function to visually output garden as a 2D rectangular plot
            //Parameters: None; acts on map of crops
        void PrintPlot() const {
            cout << "Plot of crops:" << endl;
            for (auto cropPair : crops) {
                for (int i = 0; i < cropPair.second.at(0).size(); i++)
                    cout << cropPair.first.GetDisplayToken();
                cout << endl;
            }
        }

        //Define function to change water levels, nutrient levels, and growth associated with all plants
        //(Negative input value to decrease)
            //Parameters: double with amount to increase water level
        void Update(double waterValue, double fertilizerValue, double growthValue) {
            cout << "Called FarmPlot.Update" << endl;

            //visit each pair and update respective values
        }

        //Updates plant growth, water, and soil by a 1 day cycle
        //Will call respective update function in PlantSpecies for data of each crop
        //Plant harm will decrease growth value
        //Negative growth value will kill plant
        void GrowthCycle(double temperature) {
            cout << "Called FarmPlot.GrowthCycle" << endl;
            for (auto& cropPair : crops) {
                for (list<double>::iterator waterIt = cropPair.second.at(WATER).begin(),
                                            soilIt = cropPair.second.at(SOIL).begin(),
                                            growthIt = cropPair.second.at(GROWTH).begin(); 
                     waterIt != cropPair.second.at(WATER).end(); //only one conditional for now, assumes each list has equal size
                     waterIt++, soilIt++, growthIt++
                    ) 
                {
                    cropPair.first.GrowthCycle(*growthIt,*waterIt, *soilIt, temperature);
                }
            }
        }

        //Enum for readability of the map's value array's list indeces, publicly accessible
        enum CropData {GROWTH, WATER, SOIL};
    private:
        //Declare map holding plant details
        //list array holds double of growth, water level, and soil health in that order
        map<PlantSpecies, array<list<double>, 3>> crops;

        string name;
};

#endif