#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <iomanip>
#include <string>
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
     */
    template<typename T, size_t columns, size_t rows>
    static void CoutTable(string columnHeaders[columns], string rowHeaders[rows], T data[rows][columns], int width = TABLE_DEFAULT_WIDTH) {
        //Output first row with headers
        cout << setw(width) << ""; //first column left blank for row lables
        for (string header : columnHeaders) cout << setw(width) << header;
        cout << endl;

        for (T rowData[] : data) {
            for (T value : rowData) {
                
            }
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
    private:
        static const int TABLE_DEFAULT_WIDTH = 20;
        static const int LINE_DEFAULT_WIDTH = 50;
        static const char LINE_DEFAULT_CHAR = '=';
};

#endif