#ifndef SOIL_H
#define SOIL_H

//Store details about water/nutrient levels and update functions
class Soil {
    public:
        //by default set to 0
        Soil();

        //complete constructor
        Soil(double water, double nutrients);

        //Add standard getters and setters

        //Increments/decremenets water based on water change, restricting valid ranges (0-1)
        void Update(double waterChange, double nutrientChange);
    private:
        //Percentage as a fraction, from 0-1;
        double water;
        double nutrients;
};

#endif