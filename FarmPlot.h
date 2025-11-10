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
        FarmPlot(string name, string speciesFilename, string plantDataFilename, int defaultPlantNumber = 0){
            this->name = name;
            ReadData(speciesFilename, plantDataFilename, defaultPlantNumber);
        }

        //Standard name getter
        string GetName() const { return name; }

        //Standard name setter
        void SetName(string name) { this->name = name; }

        //Hide map data from direct access for now

        /**
         * Read data from files into map of crops
         * @param speciesFilename File containing information about plant species. Formatted as "name \n tokenCharacter R G B biomeType plantType \n"
         * @param plantDataFilename File containing information about intial plant conditions for each species. Formatted as "numPlants growth water soil"
         * @param setDefaultPlantNumber If specified as a number greater than 0, will use that default number of plants instead of number in file data
         */
        void ReadData(string speciesFilename, string plantDataFilename, int setDefaultPlantNumber = 0) {
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
                
                //move data from stringstream to dummy variables, according to their format
                speciesSS.str(speciesLine);
                speciesSS >> tokenCharacter >> R >> G >> B >> biomeClass >> plantType;
                plantDataSS.str(plantDataLine);
                plantDataSS >> numPlants >> growth >> water >> soil;

                //If parameter specifies plant number ,use that instead
                if (setDefaultPlantNumber > 0) {
                    numPlants = setDefaultPlantNumber;
                }

                //instantiate an array of lists holding plant data for each species
                array<list<double>, 3> dataArray;
                dataArray.at(GROWTH) = list<double>(numPlants, growth);
                dataArray.at(WATER) = list<double>(numPlants, water);
                dataArray.at(SOIL) = list<double>(numPlants, soil);

                //insert species information and plant data into map
                crops.insert(make_pair(PlantSpecies(name, Token(tokenCharacter, R, G, B), BIOME_MAP.at(biomeClass), PLANT_MAP.at(plantType)), dataArray));

                //clear streams for next plant
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
        void PrintInformation(bool showDead = false, bool showDetail = false) const {
            const static int TABLE_ROWS = 3;
            const static int TABLE_DATA_WIDTH = 10;

            cout << "Farm plot \"" << name << "\" information:" << endl;
            for (const auto& cropPair : crops) {
                if (!cropPair.second.at(GROWTH).empty() || showDead) {
                    Util::CoutLine(TABLE_DATA_WIDTH * cropPair.second.at(0).size() + Util::TABLE_DEFAULT_WIDTH);
                    
                    //Display information about plant species
                    if (showDetail) cropPair.first.Print();
                    else cout << cropPair.first.GetName() << " (" << cropPair.first.GetDisplayToken() << ")" << endl;

                    if (cropPair.second.at(GROWTH).empty()) {
                        cout << "All plants died" << endl;
                    } else {
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
                    }
                    Util::CoutLine(TABLE_DATA_WIDTH * cropPair.second.at(0).size() + Util::TABLE_DEFAULT_WIDTH);
                }
            }
        }

        /**
         * Outputs list if dead crops
         * @param columns Number of columns when displaying list of crops
         * @param width Width occupied by each dead crop
         */
        void PrintDead(int columns = 10, int width = 20) {
            //input in streamstream first to update number of dead crops at the top
            stringstream deadCropList;

            //keep track of number of dead crops
            int numCrops = 0;

            //iterate through crops and add name of dead crops to  stringstream
            for (const auto& cropPair : crops) {
                if (cropPair.second.at(GROWTH).empty()) {
                    deadCropList << setw(width) << cropPair.first.GetName();
                    numCrops++;
                    
                    //add a newline every number of columns
                    if (numCrops % columns == 0) deadCropList << endl;
                }
            }
            cout << "List of " << numCrops << " dead crops: " << endl;
            cout << deadCropList.str() << endl;
        }

        /**
         * Returns true of all crops have died
         * @return Bool that is true if all crops have died
         */
        bool HasDied() {
            bool output = true;
            for (const auto& cropPair : crops) {
                if (!cropPair.second.at(GROWTH).empty()) output = false;
            }
            return output;
        }

        /**
         * Outputs number of each plant species as a histogram
         * @param showDead If true, will show labels of dead crops. If false, will only show living crops
         */
        void PrintPlot(bool showDead = false) const {
            cout << "Plot of " << (showDead ? "" : "living") << " crops:" << endl;
            for (const auto& cropPair : crops) {
                if (!cropPair.second.at(GROWTH).empty() || showDead) {
                    cout << setw(15) << cropPair.first.GetName() << '\t';
                    for (int i = 0; i < cropPair.second.at(0).size(); i++)
                        cout << cropPair.first.GetDisplayToken();
                    cout << endl;
                }
            }
        }

        /** Change water levels, nutrient levels, and growth associated with all plants, removing dead crops (Negative input value to decrease)
         * @param growthValue Amount to change growth values (may be negative)
         * @param waterValue Amount to change water values (may be negative)
         * @param soilValue Amount to change soil values (may be negative)
         * @param showFlags If true, shows when plants die, as well as a message when function is called
         */
        void Update(double growthValue, double waterValue, double soilValue, bool showFlags = false) {
            if (showFlags) cout << "Called FarmPlot::Update()" << endl;

            //Increments values of all crops of all species
            for (auto& cropPair : crops) {
                list<double>::iterator growthIt = cropPair.second.at(GROWTH).begin(),
                                       waterIt = cropPair.second.at(WATER).begin(),
                                       soilIt = cropPair.second.at(SOIL).begin();
                while(waterIt != cropPair.second.at(WATER).end()) { //only one conditional for now, assumes each list has equal size
                    //increment crops by input values
                    *growthIt += growthValue;
                    *waterIt += waterValue;
                    *soilIt += soilValue;
                    
                    //Check and adjust to valid ranges. negative growth values will accounted for when killing plants
                    (*growthIt > 1) ? *growthIt = 1 : false;
                    (*waterIt > 1) ? *waterIt = 1 : (*waterIt < 0) ? *waterIt = 0 : false;
                    (*soilIt > 1) ? *soilIt = 1 : (*soilIt < 0) ? *soilIt = 0 : false;

                    //remove dead crops
                    if (*growthIt < 0) {
                        //display message when crops died if showDeathFlags is set
                        if (showFlags) cout << "A " << cropPair.first.GetName() << " has died. (G,W,S): (" << *growthIt << ", " << *waterIt << ", " << *soilIt << ")" << endl;
                        //erase crop at associated position and increment iterator
                        cropPair.second.at(GROWTH).erase(growthIt++);
                        cropPair.second.at(WATER).erase(waterIt++);
                        cropPair.second.at(SOIL).erase(soilIt++);
                    } else { //traverse normally if crop is not dead
                        growthIt++;
                        waterIt++;
                        soilIt++;
                    }
                }
            }
        }

        /**
         * Updates plant growth, water, and soil by a 1 day cycle
         * Call respective GrowthCycle function in PlantSpecies for data of each crop
         * Plant harm will decrease growth value, and negative growth value will kill plant, removing it from the list of data
         * @param temperature Temperature to run growth cycle at, determining growth/damage to plants
         * @param showDeathFlag If true, display a message whenever a plant dies, along with its health information
         * @param showGrowthFlag If true, displays a message with every update to growth levels (from PlantSpecies::GrowthCycle()), as well as when function is called
         */
        void GrowthCycle(double temperature, double updateProbability = DEFAULT_UPDATE_PROBABILITY,  bool showDeathFlag = false, bool showGrowthFlags = false) {
            if (showGrowthFlags) cout << "Called FarmPlot::GrowthCycle()" << endl;

            //Calls update function on each crop, removing them from the list if they die
            for (auto& cropPair : crops) {
                list<double>::iterator waterIt = cropPair.second.at(WATER).begin(),
                                       soilIt = cropPair.second.at(SOIL).begin(),
                                       growthIt = cropPair.second.at(GROWTH).begin(); 
                while(waterIt != cropPair.second.at(WATER).end()) { //only one conditional for now, assumes each list has equal size
                    if (Util::RollProbability(updateProbability)) { //don't update probabilities every single time
                        //update crops by running a growth cycle
                        cropPair.first.GrowthCycle(*growthIt,*waterIt, *soilIt, temperature, showGrowthFlags);
                    }

                    //remove dead crops
                    if (*growthIt < 0) {
                        //display message when crops died if showDeathFlags is set
                        if (showDeathFlag) cout << "A " << cropPair.first.GetName() << " has died. (G,W,S): (" << *growthIt << ", " << *waterIt << ", " << *soilIt << ")" << endl;

                        //erase crop at associated position and increment iterator
                        cropPair.second.at(GROWTH).erase(growthIt++);
                        cropPair.second.at(WATER).erase(waterIt++);
                        cropPair.second.at(SOIL).erase(soilIt++);
                    } else { //traverse normally if crop is not dead
                        growthIt++;
                        waterIt++;
                        soilIt++;
                    }
                }
            }
        }

        //Enum for readability of the map's value array's list indeces, publicly accessible
        enum CropData {GROWTH, WATER, SOIL};
    private:
        const static double DEFAULT_UPDATE_PROBABILITY;
        //Declare map holding plant details
        //list array holds double of growth, water level, and soil health in that order
        map<PlantSpecies, array<list<double>, 3>> crops;

        string name;
};

const double FarmPlot::DEFAULT_UPDATE_PROBABILITY = 0.3;

#endif