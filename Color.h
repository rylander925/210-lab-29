#ifndef COLOR_H
#define COLOR_H

struct Color {
    Color() : R(0), G(0), B(0) {}
    Color(int R, int G, int B) {
        //ensure proper ranges
        this->R = (R <= MAX) ? (R >= 0 ? R : 0) : MAX;
        this->G = (G <= MAX) ? (G >= 0 ? G : 0) : MAX;
        this->B = (B <= MAX) ? (B >= 0 ? B : 0) : MAX;
    }
    int R;
    int G;
    int B;
    static const int MAX = 255;
};

#endif