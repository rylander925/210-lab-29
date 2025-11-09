#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>

using namespace std;

struct Token {
    Token() : character('?'), R(MAX), G(MAX), B(MAX) {}
    Token(char C) : Token() { character = C; }
    Token(char C, int R, int G, int B) {
        //ensure proper ranges
        character = C;
        this->R = (R <= MAX) ? (R >= 0 ? R : 0) : MAX;
        this->G = (G <= MAX) ? (G >= 0 ? G : 0) : MAX;
        this->B = (B <= MAX) ? (B >= 0 ? B : 0) : MAX;
    }
    char character;
    int R;
    int G;
    int B;
    static const int MAX = 255;

    //Prints to console ANSI code to set text to a given RGB Value
    void ColorText() { cout << "\033[38;2;" << R << ";" << G << ";" << B << "m"; }

    //Prints to console ANSI code to reset text formatting
    void ResetText() { cout << "\033[0m"; }
};

#endif