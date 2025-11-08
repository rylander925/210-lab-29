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
        static void CoutLine(int width = 50, char lineChar = '=') {
            char oldFill = cout.fill();
            cout << setfill(lineChar) << setw(width) << "" << setfill(oldFill) << endl;
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
};

#endif