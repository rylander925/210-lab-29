#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <iomanip>
#include <string>
#include <array>
#include <list>
#include <fstream>

using namespace std;

class Util {
    public:
    /**
     * Outputs a line of characters
     * @param width Number of characters in the line
     * @param lineChar Characters composing line
     */
    static void CoutLine(int width = LINE_DEFAULT_WIDTH, char lineChar = LINE_DEFAULT_CHAR) {
        char oldFill = cout.fill();
        cout << setfill(lineChar) << setw(width) << "" << setfill(oldFill) << endl;
    }

    /**
     * Outputs a formatted table
     * @param columnHeaders Title above each column
     * @param rowHeaders Title in front of each row
     * @param data Data in each column, as a 2D array of [rows][columns]
     * @param dataWidth Spacing between each data value
     * @param headerWidth Spacing between row header and first  data value
     * @note Sets cout to left alignment
     */
    template<typename T, size_t columns, size_t rows>
    static void CoutTable(array<string, columns> columnHeaders, array<string, rows> rowHeaders, array<array<T, columns>, rows> data, int dataWidth = TABLE_DEFAULT_WIDTH, int headerWidth = TABLE_DEFAULT_WIDTH) {
        //Output first row with headers
        cout << left; //Set cout to left
        cout << setw(headerWidth) << ""; //first column left blank for row lables
        for (string header : columnHeaders) cout << setw(dataWidth) << header;
        cout << endl;

        //Output data for rest of the rows
        for (int rowNum = 0; rowNum < rows; rowNum++) {
            //Output row title
            cout << setw(headerWidth) << rowHeaders.at(rowNum);

            //followed by data in the row
            for (T val : data.at(rowNum)) cout << setw(dataWidth) << val;
            cout << endl;
        }
    }

    /**
     * Outputs a formatted table with variable columns using lists
     * @param columnHeaders Title above each column
     * @param rowHeaders Title in front of each row
     * @param data Data in each column, as a 2D data structure of an array of lists
     * @param dataWidth Spacing between each data value
     * @param headerWidth Spacing between row header and first  data value
     * @note Sets cout to left alignment
     */
    template<typename T, size_t rows>
    static void CoutTable(list<string> columnHeaders, array<string, rows> rowHeaders, array<list<T>, rows> data, int dataWidth = TABLE_DEFAULT_WIDTH, int headerWidth = TABLE_DEFAULT_WIDTH) {
        //Output first row with headers
        cout << left; //Set cout to left
        cout << setw(headerWidth) << ""; //first column left blank for row lables
        for (string header : columnHeaders) cout << setw(dataWidth) << header;
        cout << endl;

        //Output data for rest of the rows
        for (int rowNum = 0; rowNum < rows; rowNum++) {
            //Output row title
            cout << setw(headerWidth) << rowHeaders.at(rowNum);

            //followed by data in the row
            for (T val : data.at(rowNum)) cout << setw(dataWidth) << val;
            cout << endl;
        }
    }
    
    /**
     * Attempts to open a file and throws an error if file fails to open.
     * @param filestream Filestream to open file at
     * @param filename File to open
     * @note Opens file; make sure to close the file
     */
    static void VerifyFileOpen(ifstream& filestream, string filename) {
        filestream.open(filename);
        if (!filestream.is_open()) {
            cout << "ERROR: File open error for file \"" << filename << "\"" << endl; 
            throw ios_base::failure("File open error");
            }
    }
    static const int TABLE_DEFAULT_WIDTH = 20;
    static const int LINE_DEFAULT_WIDTH = 100;
    static const char LINE_DEFAULT_CHAR = '=';

    //Add comparison operators within a range epsilon to eliminate effect of floating point imprecision
    static const double DEFAULT_EPSILON;
    static bool lessThan(double a, double b, double epsilon = DEFAULT_EPSILON) { return (b - a) > epsilon; }
    static bool greaterThan(double a, double b, double epsilon = DEFAULT_EPSILON) { return lessThan(b, a, epsilon); }
    static bool lessThanEqualTo(double a, double b, double epsilon = DEFAULT_EPSILON) { return !greaterThan(a, b, epsilon); }
    static bool greaterThanEqualTo(double a, double b, double epsilon = DEFAULT_EPSILON) { return !lessThan(a, b, epsilon); }
};

const double Util::DEFAULT_EPSILON = 0.00001;

#endif